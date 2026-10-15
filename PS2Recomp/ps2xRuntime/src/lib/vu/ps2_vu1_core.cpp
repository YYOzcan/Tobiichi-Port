#include <chrono>
#include "runtime/ps2_vu1.h"
#include "runtime/ps2_vu1_native.h"
#include "runtime/gs/ps2_gif_arbiter.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/ps2_memory.h"
#include "ps2_vu1_detail.h"
#include "ps2_vu1_step.inl"

#include <algorithm>
#include <bit>
#include <atomic>
#include <cfenv>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <limits>
#include <string>
#include <ps2_log.h>
#include "runtime/ps2_perf.h"

// GOW-Port: la aritmética de VU no depende de /fp:fast. El runtime se compila con /fp:fast, que deja al
// compilador fusionar a*b+c en FMA según dónde esté el código: el intérprete y el microcódigo compilado
// (o dos versiones del intérprete) podían dar resultados distintos. Aquí cada operación se redondea por
// separado, como en las FMAC de la PS2 (y en PCSX2).
#if defined(_MSC_VER)
#pragma float_control(precise, on, push)
#pragma fp_contract(off)
#endif

namespace
{
    // GOW-Port: GOW_XGKICK_IMMEDIATE se lee una vez (-1 = sin leer). getenv recorre el entorno
    // completo; leerlo en cada XGKICK ocupaba un tercio del hilo del juego (ucrtbase!strchr).
    std::atomic<int> g_xgkickImmediate{-1};

    bool xgkickImmediate()
    {
        int value = g_xgkickImmediate.load(std::memory_order_relaxed);
        if (value < 0)
        {
            const char *setting = std::getenv("GOW_XGKICK_IMMEDIATE");
            value = (setting && std::strcmp(setting, "1") == 0) ? 1 : 0;
            g_xgkickImmediate.store(value, std::memory_order_relaxed);
        }
        return value != 0;
    }

    constexpr uint8_t laneForComponent(uint32_t component)
    {
        return static_cast<uint8_t>(1u << (3u - component));
    }
}

void VU1Interpreter::addVfRead(InstructionUsage &usage, uint8_t reg, uint8_t lanes)
{
    if (lanes == 0u)
        return;
    for (uint32_t index = 0; index < usage.vfReadCount; ++index)
    {
        if (usage.vfRead[index].reg == reg)
        {
            usage.vfRead[index].lanes |= lanes;
            return;
        }
    }
    if (usage.vfReadCount < usage.vfRead.size())
        usage.vfRead[usage.vfReadCount++] = {reg, lanes};
}

void VU1Interpreter::addVfWrite(InstructionUsage &usage, uint8_t reg, uint8_t lanes)
{
    if (reg == 0u || lanes == 0u)
        return;
    if (usage.vfWrite.reg == 0u)
        usage.vfWrite = {reg, lanes};
    else if (usage.vfWrite.reg == reg)
        usage.vfWrite.lanes |= lanes;
}

uint8_t VU1Interpreter::vfReadLanes(const InstructionUsage &usage, uint8_t reg)
{
    for (uint32_t index = 0; index < usage.vfReadCount; ++index)
    {
        if (usage.vfRead[index].reg == reg)
            return usage.vfRead[index].lanes;
    }
    return 0u;
}

VU1Interpreter::VU1Interpreter(Unit unit)
    : m_unit(unit)
{
    reset();
}

void VU1Interpreter::setDirectRegisterWrites(bool enabled)
{
    m_directRegisterWrites = enabled && m_unit == Unit::VU1;
    m_decodedCodeCacheValid = false; // recalcula m_statusUnread
    m_statusUnread = false;
    m_statusQuiet = false;
}

void VU1Interpreter::resetScheduler()
{
    commitReadyFlags(); // GOW-Port: las ya listas se habrían confirmado en su ciclo
    m_lastRunHitBudget = false; // GOW-Port
    m_nextCommitCycle = ~0ull;
    m_flagPipeline = {};
    m_fdiv = {};
    m_efu = {};
    m_storePipeline = {};
    m_vfWritePipeline = {};
    m_viWritePipeline = {};
    m_accWritePipeline = {};
    m_storePending = m_vfPending = m_viPending = m_accPending = 0u;
    m_flagHead = m_flagCount = 0u;
    m_xgkick.reset();
    m_vfReady = {};
    m_viReady = {};
    m_accReady = {};
    if (m_native) // GOW-Port: native backend bookkeeping of these arrays (ps2_vu1_native.inl)
    {
        m_native->arraysReadyBy = 0u;
        m_native->exitCycle = m_cycle;
    }
    m_vfLatestWrite = {};
    m_viLatestWrite = {};
    m_accLatestWrite = {};
    m_nextWriteSequence = 0;
    m_efuResourceReady = 0;
    m_workingClip = m_state.clip;
    m_viBranchBackupValue = 0;
    m_viBranchBackupReg = 0;
    m_viBranchBackupValid = false;
    m_stopRequested = false;
    m_pendingHaltD = false;
    m_pendingHaltT = false;
}

void VU1Interpreter::reset()
{
    std::memset(&m_state, 0, sizeof(m_state));
    m_state.vf[0][3] = 1.0f;
    m_state.q = 1.0f;
    m_state.r = 0x3F800000u;
    m_cycle = 0;
    resetScheduler();
}

float VU1Interpreter::broadcast(const float *vf, uint8_t bc)
{
    return normalizeOperand(vf[bc & 3u]);
}

float VU1Interpreter::normalizeResult(float value, uint32_t &laneFlags) const
{
    uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    const uint32_t sign = bits & 0x80000000u;
    const uint32_t magnitude = bits & 0x7FFFFFFFu;
    const uint32_t exponent = (bits >> 23) & 0xFFu;

    laneFlags = sign != 0u ? 0x2u : 0u;
    if (magnitude == 0u)
    {
        laneFlags |= 0x1u;
    }
    else if (exponent == 0u)
    {
        laneFlags |= 0x5u;
        bits = sign;
    }
    else if (exponent == 0xFFu)
    {
        laneFlags |= 0x8u;
        bits = sign | 0x7F7FFFFFu;
    }

    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

int32_t VU1Interpreter::readBranchVi(uint8_t reg) const
{
    if (reg == 0u)
        return 0;
    if (m_viBranchBackupValid &&
        m_viBranchBackupReg == reg)
    {
        return m_viBranchBackupValue;
    }
    return m_state.vi[reg];
}

void VU1Interpreter::recordViWriteForBranch(uint8_t reg, int32_t oldValue)
{
    if (reg == 0u)
        return;
    m_viBranchBackupValue = oldValue;
    m_viBranchBackupReg = reg;
    m_viBranchBackupValid = true;
}

void VU1Interpreter::applyDest(float *dst, const float *result, uint8_t dest)
{
    if (dest & 0x8u)
        dst[0] = result[0];
    if (dest & 0x4u)
        dst[1] = result[1];
    if (dest & 0x2u)
        dst[2] = result[2];
    if (dest & 0x1u)
        dst[3] = result[3];
}

void VU1Interpreter::applyDestAcc(const float *result, uint8_t dest)
{
    applyDest(m_state.acc, result, dest);
}

void VU1Interpreter::normalizeFmacResult(float *result, uint8_t dest,
                                         uint8_t laneFlags[4])
{
    // GOW-Port: decodifica la operación una vez por instrucción (antes calculateFmacExactResult
    // recorría el switch de opcodes en cada componente). Mismas fórmulas en long double.
    enum class Kind : uint8_t { None, Add, Sub, Madd, Msub, Mul, Opmsub, Opmula };
    enum class Source : uint8_t { Broadcast, Q, I, Vector };
    const uint32_t upper = m_currentUpperInstruction;
    const uint8_t op = static_cast<uint8_t>(upper & 0x3Fu);
    const uint8_t code = op >= 0x3Cu ? static_cast<uint8_t>((upper & 3u) | ((upper >> 4) & 0x7Cu)) : op;
    Kind kind = Kind::None;
    Source source = Source::Vector;
    if (code <= 0x03u) { kind = Kind::Add; source = Source::Broadcast; }
    else if (code <= 0x07u) { kind = Kind::Sub; source = Source::Broadcast; }
    else if (code <= 0x0Bu) { kind = Kind::Madd; source = Source::Broadcast; }
    else if (code <= 0x0Fu) { kind = Kind::Msub; source = Source::Broadcast; }
    else if (code >= 0x18u && code <= 0x1Bu) { kind = Kind::Mul; source = Source::Broadcast; }
    else
    {
        switch (code)
        {
        case 0x1Cu: kind = Kind::Mul; source = Source::Q; break;
        case 0x1Eu: kind = Kind::Mul; source = Source::I; break;
        case 0x20u: kind = Kind::Add; source = Source::Q; break;
        case 0x21u: kind = Kind::Madd; source = Source::Q; break;
        case 0x22u: kind = Kind::Add; source = Source::I; break;
        case 0x23u: kind = Kind::Madd; source = Source::I; break;
        case 0x24u: kind = Kind::Sub; source = Source::Q; break;
        case 0x25u: kind = Kind::Msub; source = Source::Q; break;
        case 0x26u: kind = Kind::Sub; source = Source::I; break;
        case 0x27u: kind = Kind::Msub; source = Source::I; break;
        case 0x28u: kind = Kind::Add; break;
        case 0x29u: kind = Kind::Madd; break;
        case 0x2Au: kind = Kind::Mul; break;
        case 0x2Cu: kind = Kind::Sub; break;
        case 0x2Du: kind = Kind::Msub; break;
        case 0x2Eu: kind = op < 0x3Cu ? Kind::Opmsub : Kind::Opmula; break;
        default: break;
        }
    }

    if (kind == Kind::None)
    {
        for (uint32_t component = 0; component < 4u; ++component)
        {
            laneFlags[component] = 0u;
            if ((dest & laneForComponent(component)) == 0u)
                continue;
            uint32_t flags = 0u;
            result[component] = normalizeResult(result[component], flags);
            laneFlags[component] = static_cast<uint8_t>(flags);
        }
        return;
    }

    const uint8_t fs = FS(upper);
    const uint8_t ft = FT(upper);
    long double vs[4];
    long double vt[4];
    long double acc[4];
    for (uint32_t component = 0; component < 4u; ++component)
    {
        vs[component] = static_cast<long double>(normalizeOperand(m_state.vf[fs][component]));
        vt[component] = static_cast<long double>(normalizeOperand(m_state.vf[ft][component]));
        acc[component] = static_cast<long double>(normalizeOperand(m_state.acc[component]));
    }
    long double scalar = 0.0L;
    if (source == Source::Q)
        scalar = static_cast<long double>(normalizeOperand(m_state.q));
    else if (source == Source::I)
        scalar = static_cast<long double>(normalizeOperand(m_state.i));
    else if (source == Source::Broadcast)
        scalar = vt[code & 3u];

    static constexpr uint8_t crossLeft[4] = {1u, 2u, 0u, 3u};
    static constexpr uint8_t crossRight[4] = {2u, 0u, 1u, 3u};
    for (uint32_t component = 0; component < 4u; ++component)
    {
        laneFlags[component] = 0u;
        if ((dest & laneForComponent(component)) == 0u)
            continue;
        // GOW-Port: en ADD/SUB/MUL el resultado en float se redondea hacia cero desde el exacto. Si es normal y
        // no está en el exponente máximo, el exacto no es cero ni desborda ni se queda por debajo del mínimo:
        // el valor no cambia y los flags son solo el signo. Así se evita el cálculo en long double.
        if (kind == Kind::Add || kind == Kind::Sub || kind == Kind::Mul)
        {
            uint32_t bits = 0u;
            std::memcpy(&bits, &result[component], sizeof(bits));
            const uint32_t exponent = (bits >> 23) & 0xFFu;
            if (exponent != 0u && exponent < 0xFEu)
            {
                laneFlags[component] = (bits & 0x80000000u) != 0u ? 0x2u : 0u;
                continue;
            }
        }
        const long double right = source == Source::Vector ? vt[component] : scalar;
        if (kind == Kind::Madd || kind == Kind::Msub)
        {
            const float product = static_cast<float>(vs[component]) * static_cast<float>(right);
            if (productSumFlagsFast(result[component], product, laneFlags[component]))
                continue;
        }
        else if (kind == Kind::Opmsub && component != 3u)
        {
            const float product = static_cast<float>(vs[crossLeft[component]]) * static_cast<float>(vt[crossRight[component]]);
            if (productSumFlagsFast(result[component], product, laneFlags[component]))
                continue;
        }
        long double exact = 0.0L;
        switch (kind)
        {
        case Kind::Add: exact = vs[component] + right; break;
        case Kind::Sub: exact = vs[component] - right; break;
        case Kind::Madd: exact = acc[component] + vs[component] * right; break;
        case Kind::Msub: exact = acc[component] - vs[component] * right; break;
        case Kind::Mul: exact = vs[component] * right; break;
        case Kind::Opmsub:
            exact = component == 3u ? 0.0L : acc[component] - vs[crossLeft[component]] * vt[crossRight[component]];
            break;
        case Kind::Opmula:
            exact = component == 3u ? 0.0L : vs[crossLeft[component]] * vt[crossRight[component]];
            break;
        default: break;
        }
        laneFlags[component] = normalizeFmacExactResult(result[component], exact);
    }
}

bool VU1Interpreter::calculateFmacExactResult(uint32_t component,
                                               long double &result) const
{
    const uint32_t upper = m_currentUpperInstruction;
    const uint8_t op = static_cast<uint8_t>(upper & 0x3Fu);
    const uint8_t special = op >= 0x3Cu
                                ? static_cast<uint8_t>((upper & 3u) | ((upper >> 4) & 0x7Cu))
                                : 0xFFu;
    const uint8_t fs = FS(upper);
    const uint8_t ft = FT(upper);

    const auto operand = [this](float value)
    {
        return static_cast<long double>(normalizeOperand(value));
    };
    const auto vs = [&](uint32_t lane)
    {
        return operand(m_state.vf[fs][lane]);
    };
    const auto vt = [&](uint32_t lane)
    {
        return operand(m_state.vf[ft][lane]);
    };
    const auto acc = [&](uint32_t lane)
    {
        return operand(m_state.acc[lane]);
    };

    const long double q = operand(m_state.q);
    const long double i = operand(m_state.i);

    if (op < 0x3Cu)
    {
        if (op <= 0x03u)
            result = vs(component) + vt(op & 3u);
        else if (op <= 0x07u)
            result = vs(component) - vt(op & 3u);
        else if (op <= 0x0Bu)
            result = acc(component) + vs(component) * vt(op & 3u);
        else if (op <= 0x0Fu)
            result = acc(component) - vs(component) * vt(op & 3u);
        else if (op >= 0x18u && op <= 0x1Bu)
            result = vs(component) * vt(op & 3u);
        else
        {
            switch (op)
            {
            case 0x1Cu:
                result = vs(component) * q;
                break;
            case 0x1Eu:
                result = vs(component) * i;
                break;
            case 0x20u:
                result = vs(component) + q;
                break;
            case 0x21u:
                result = acc(component) + vs(component) * q;
                break;
            case 0x22u:
                result = vs(component) + i;
                break;
            case 0x23u:
                result = acc(component) + vs(component) * i;
                break;
            case 0x24u:
                result = vs(component) - q;
                break;
            case 0x25u:
                result = acc(component) - vs(component) * q;
                break;
            case 0x26u:
                result = vs(component) - i;
                break;
            case 0x27u:
                result = acc(component) - vs(component) * i;
                break;
            case 0x28u:
                result = vs(component) + vt(component);
                break;
            case 0x29u:
                result = acc(component) + vs(component) * vt(component);
                break;
            case 0x2Au:
                result = vs(component) * vt(component);
                break;
            case 0x2Cu:
                result = vs(component) - vt(component);
                break;
            case 0x2Du:
                result = acc(component) - vs(component) * vt(component);
                break;
            case 0x2Eu:
            {
                static constexpr uint8_t left[4] = {1u, 2u, 0u, 3u};
                static constexpr uint8_t right[4] = {2u, 0u, 1u, 3u};
                result = component == 3u
                             ? 0.0L
                             : acc(component) - vs(left[component]) * vt(right[component]);
                break;
            }
            default:
                return false;
            }
        }
        return true;
    }

    if (special <= 0x03u)
        result = vs(component) + vt(special & 3u);
    else if (special <= 0x07u)
        result = vs(component) - vt(special & 3u);
    else if (special <= 0x0Bu)
        result = acc(component) + vs(component) * vt(special & 3u);
    else if (special <= 0x0Fu)
        result = acc(component) - vs(component) * vt(special & 3u);
    else if (special >= 0x18u && special <= 0x1Bu)
        result = vs(component) * vt(special & 3u);
    else
    {
        switch (special)
        {
        case 0x1Cu:
            result = vs(component) * q;
            break;
        case 0x1Eu:
            result = vs(component) * i;
            break;
        case 0x20u:
            result = vs(component) + q;
            break;
        case 0x21u:
            result = acc(component) + vs(component) * q;
            break;
        case 0x22u:
            result = vs(component) + i;
            break;
        case 0x23u:
            result = acc(component) + vs(component) * i;
            break;
        case 0x24u:
            result = vs(component) - q;
            break;
        case 0x25u:
            result = acc(component) - vs(component) * q;
            break;
        case 0x26u:
            result = vs(component) - i;
            break;
        case 0x27u:
            result = acc(component) - vs(component) * i;
            break;
        case 0x28u:
            result = vs(component) + vt(component);
            break;
        case 0x29u:
            result = acc(component) + vs(component) * vt(component);
            break;
        case 0x2Au:
            result = vs(component) * vt(component);
            break;
        case 0x2Cu:
            result = vs(component) - vt(component);
            break;
        case 0x2Du:
            result = acc(component) - vs(component) * vt(component);
            break;
        case 0x2Eu:
        {
            static constexpr uint8_t left[4] = {1u, 2u, 0u, 3u};
            static constexpr uint8_t right[4] = {2u, 0u, 1u, 3u};
            result = component == 3u
                         ? 0.0L
                         : vs(left[component]) * vt(right[component]);
            break;
        }
        default:
            return false;
        }
    }
    return true;
}

uint8_t VU1Interpreter::normalizeFmacExactResult(float &value,
                                                  long double exactResult) const
{
    const bool negative = std::signbit(exactResult);
    const long double magnitude = std::fabs(exactResult);
    const long double maximum = static_cast<long double>(std::numeric_limits<float>::max());
    const long double minimum = static_cast<long double>(std::numeric_limits<float>::min());
    uint8_t flags = negative ? 0x2u : 0u;

    uint32_t bits = negative ? 0x80000000u : 0u;
    if (magnitude == 0.0L)
    {
        flags |= 0x1u;
        std::memcpy(&value, &bits, sizeof(value));
    }
    else if (magnitude > maximum)
    {
        flags |= 0x8u;
        bits |= 0x7F7FFFFFu;
        std::memcpy(&value, &bits, sizeof(value));
    }
    else if (magnitude < minimum)
    {
        flags |= 0x5u;
        std::memcpy(&value, &bits, sizeof(value));
    }

    return flags;
}

uint32_t VU1Interpreter::calculateFmacProductSticky(uint8_t dest) const
{
    uint32_t extraSticky = 0u;
    const uint32_t upper = m_currentUpperInstruction;
    const uint8_t op = static_cast<uint8_t>(upper & 0x3Fu);
    const uint8_t special = op >= 0x3Cu ? static_cast<uint8_t>((upper & 3u) | ((upper >> 4) & 0x7Cu)) : 0xFFu;
    const bool productSum =
        (op >= 0x08u && op <= 0x0Fu) ||
        op == 0x21u || op == 0x23u || op == 0x25u || op == 0x27u ||
        op == 0x29u || op == 0x2Du || op == 0x2Eu ||
        (special >= 0x08u && special <= 0x0Fu) ||
        special == 0x21u || special == 0x23u || special == 0x25u ||
        special == 0x27u || special == 0x29u || special == 0x2Du;
    if (!productSum)
        return 0u;

    const uint8_t fs = FS(upper);
    const uint8_t ft = FT(upper);
    for (uint32_t component = 0; component < 4u; ++component)
    {
        if ((dest & laneForComponent(component)) == 0u)
            continue;
        static constexpr uint8_t crossLeft[4] = {1u, 2u, 0u, 3u};
        static constexpr uint8_t crossRight[4] = {2u, 0u, 1u, 3u};
        const uint8_t leftComponent = op == 0x2Eu ? crossLeft[component] : static_cast<uint8_t>(component);
        const float left = normalizeOperand(m_state.vf[fs][leftComponent]);
        float right = 0.0f;
        if ((op >= 0x08u && op <= 0x0Fu) || (special >= 0x08u && special <= 0x0Fu))
        {
            right = normalizeOperand(m_state.vf[ft][(op >= 0x08u && op <= 0x0Fu ? op : special) & 3u]);
        }
        else if (op == 0x21u || op == 0x25u || special == 0x21u || special == 0x25u)
        {
            right = normalizeOperand(m_state.q);
        }
        else if (op == 0x23u || op == 0x27u || special == 0x23u || special == 0x27u)
        {
            right = normalizeOperand(m_state.i);
        }
        else if (op == 0x2Eu)
        {
            right = normalizeOperand(m_state.vf[ft][crossRight[component]]);
        }
        else
        {
            right = normalizeOperand(m_state.vf[ft][component]);
        }

        const uint8_t productFlags = productStickyFlags(left, right, left * right);
        // Product-sum instructions report Z/S/U/O from the add/subtract result
        // as current flags, while every product condition accumulates into the
        // corresponding sticky flag.
        extraSticky |= productFlags & 0xFu;
    }
    return extraSticky;
}

void VU1Interpreter::updateFmacFlags(const uint8_t laneFlags[4], uint8_t dest,
                                     uint32_t extraSticky)
{
    if (dest == 0u)
        return;

    uint32_t mac = 0u;
    uint32_t status = 0u;
    for (uint32_t component = 0; component < 4u; ++component)
    {
        const uint8_t lane = laneForComponent(component);
        if ((dest & lane) == 0u)
            continue;

        const uint32_t flags = laneFlags[component];
        if ((flags & 0x1u) != 0u)
            mac |= lane;
        if ((flags & 0x2u) != 0u)
            mac |= static_cast<uint32_t>(lane) << 4;
        if ((flags & 0x4u) != 0u)
            mac |= static_cast<uint32_t>(lane) << 8;
        if ((flags & 0x8u) != 0u)
            mac |= static_cast<uint32_t>(lane) << 12;
        status |= flags;
    }

    FlagPipelineEntry *entry = pushFlagEntry();
    if (!entry)
    {
        reportReservedInstruction(true, 0xFFFFFFFFu);
        return;
    }
    entry->mac = mac;
    entry->status = status;
    entry->extraSticky = extraSticky;
    entry->writesMac = true;
    entry->writesStatus = true;
}

void VU1Interpreter::applyFmacDest(float *dst, float *result, uint8_t dest)
{
    uint8_t laneFlags[4]{};
    normalizeFmacResult(result, dest, laneFlags);
    updateFmacFlags(laneFlags, dest, calculateFmacProductSticky(dest));
    applyDest(dst, result, dest);
}

void VU1Interpreter::applyFmacDestAcc(float *result, uint8_t dest)
{
    uint8_t laneFlags[4]{};
    normalizeFmacResult(result, dest, laneFlags);
    updateFmacFlags(laneFlags, dest, calculateFmacProductSticky(dest));
    applyDestAcc(result, dest);
}

VU1Interpreter::FlagPipelineEntry *VU1Interpreter::pushFlagEntry()
{
    if (m_flagCount >= kMaxFlagEntries)
        commitReadyFlags();
    if (m_flagCount >= kMaxFlagEntries)
        return nullptr;
    FlagPipelineEntry &entry = m_flagPipeline[(m_flagHead + m_flagCount) % kMaxFlagEntries];
    ++m_flagCount;
    entry.mac = entry.status = entry.extraSticky = entry.clip = 0u;
    entry.writesMac = entry.writesStatus = entry.writesSticky = entry.writesClip = false;
    entry.valid = true;
    entry.issueCycle = m_cycle;
    entry.readyCycle = m_cycle + kFmacLatency;
    return &entry;
}

void VU1Interpreter::queueFsset(uint16_t immediate)
{
    for (FlagPipelineEntry &entry : m_flagPipeline)
    {
        if (entry.valid && entry.issueCycle == m_cycle)
            entry.writesStatus = false;
    }

    if (FlagPipelineEntry *entry = pushFlagEntry())
    {
        entry->status = static_cast<uint32_t>(immediate) & 0xFC0u;
        entry->writesSticky = true;
        return;
    }
    reportReservedInstruction(false, 0xFFFFFFFEu);
}

void VU1Interpreter::queueClip(uint32_t clip)
{
    m_workingClip = ((m_workingClip << 6) | (clip & 0x3Fu)) & 0xFFFFFFu;
    if (FlagPipelineEntry *entry = pushFlagEntry())
    {
        entry->clip = m_workingClip;
        entry->writesClip = true;
        return;
    }
    reportReservedInstruction(true, 0xFFFFFFFDu);
}

void VU1Interpreter::queueFcset(uint32_t clip)
{
    m_workingClip = clip & 0xFFFFFFu;
    for (FlagPipelineEntry &entry : m_flagPipeline)
    {
        if (entry.valid && entry.issueCycle == m_cycle)
            entry.writesClip = false;
    }
    if (FlagPipelineEntry *entry = pushFlagEntry())
    {
        entry->clip = m_workingClip;
        entry->writesClip = true;
        return;
    }
    reportReservedInstruction(false, 0xFFFFFFFAu);
}

void VU1Interpreter::queueQ(float value, uint32_t latency, uint32_t statusDi)
{
    uint32_t ignoredFlags = 0u;
    value = normalizeResult(value, ignoredFlags);
    m_fdiv.valid = true;
    m_fdiv.readyCycle = m_cycle + latency;
    m_nextCommitCycle = std::min(m_nextCommitCycle, m_fdiv.readyCycle);
    m_fdiv.value = value;
    m_fdiv.statusDi = statusDi & 0x30u;
}

void VU1Interpreter::queueP(float value, uint32_t latency)
{
    uint32_t ignoredFlags = 0u;
    value = normalizeResult(value, ignoredFlags);
    for (ScalarPipelineEntry &entry : m_efu)
    {
        if (!entry.valid)
        {
            entry.valid = true;
            entry.readyCycle = m_cycle + latency;
            m_nextCommitCycle = std::min(m_nextCommitCycle, entry.readyCycle);
            entry.value = value;
            // EFU throughput is one cycle shorter than result visibility.
            m_efuResourceReady = m_cycle + (latency > 0u ? latency - 1u : 0u);
            return;
        }
    }
    reportReservedInstruction(false, 0xFFFFFFF9u);
}

void VU1Interpreter::queueStore(uint32_t address, const uint32_t words[4], uint8_t laneMask)
{
    for (PendingStore &store : m_storePipeline)
    {
        if (!store.valid)
        {
            store.valid = true;
            store.readyCycle = m_cycle + 1u;
            m_nextCommitCycle = std::min(m_nextCommitCycle, store.readyCycle);
            m_storePending |= 1u << static_cast<uint32_t>(&store - m_storePipeline.data());
            store.address = address;
            store.laneMask = laneMask;
            std::copy(words, words + 4, store.words.begin());
            return;
        }
    }
    reportReservedInstruction(false, 0xFFFFFFFCu);
}

void VU1Interpreter::queueVfWrite(uint8_t reg, uint8_t laneMask,
                                  const float value[4], uint32_t latency)
{
    if (reg == 0u || laneMask == 0u)
        return;
    for (PendingVfWrite &write : m_vfWritePipeline)
    {
        if (!write.valid)
        {
            write = {};
            write.valid = true;
            write.readyCycle = m_cycle + latency;
            m_nextCommitCycle = std::min(m_nextCommitCycle, write.readyCycle);
            m_vfPending |= 1u << static_cast<uint32_t>(&write - m_vfWritePipeline.data());
            write.sequence = ++m_nextWriteSequence;
            write.reg = reg;
            write.laneMask = laneMask;
            std::copy(value, value + 4, write.value.begin());
            for (uint32_t component = 0; component < 4u; ++component)
            {
                if ((laneMask & laneForComponent(component)) != 0u)
                    m_vfLatestWrite[reg][component] = write.sequence;
            }
            return;
        }
    }
    reportReservedInstruction(false, 0xFFFFFFF7u);
}

void VU1Interpreter::queueViWrite(uint8_t reg, int32_t value, uint32_t latency)
{
    if (reg == 0u)
        return;
    for (PendingViWrite &write : m_viWritePipeline)
    {
        if (!write.valid)
        {
            write = {};
            write.valid = true;
            write.readyCycle = m_cycle + latency;
            m_nextCommitCycle = std::min(m_nextCommitCycle, write.readyCycle);
            m_viPending |= 1u << static_cast<uint32_t>(&write - m_viWritePipeline.data());
            write.sequence = ++m_nextWriteSequence;
            write.reg = reg;
            write.value = value;
            m_viLatestWrite[reg] = write.sequence;
            return;
        }
    }
    reportReservedInstruction(false, 0xFFFFFFF6u);
}

void VU1Interpreter::queueAccWrite(uint8_t laneMask, const float value[4], uint32_t latency)
{
    if (laneMask == 0u)
        return;
    for (PendingAccWrite &write : m_accWritePipeline)
    {
        if (!write.valid)
        {
            write = {};
            write.valid = true;
            write.readyCycle = m_cycle + latency;
            m_nextCommitCycle = std::min(m_nextCommitCycle, write.readyCycle);
            m_accPending |= 1u << static_cast<uint32_t>(&write - m_accWritePipeline.data());
            write.sequence = ++m_nextWriteSequence;
            write.laneMask = laneMask;
            std::copy(value, value + 4, write.value.begin());
            for (uint32_t component = 0; component < 4u; ++component)
            {
                if ((laneMask & laneForComponent(component)) != 0u)
                    m_accLatestWrite[component] = write.sequence;
            }
            return;
        }
    }
    reportReservedInstruction(true, 0xFFFFFFF5u);
}

void VU1Interpreter::commitReadyPipelines()
{
    if (m_cycle < m_nextCommitCycle)
        return;
    // GOW-Port: caso frecuente (código FMAC denso con escrituras directas): solo hay flags pendientes.
    // Se confirman en orden y el siguiente ciclo es el de la cabeza de la cola, como en el caso general.
    if ((m_storePending | m_vfPending | m_viPending | m_accPending) == 0u && !m_fdiv.valid &&
        !m_efu[0].valid && !m_efu[1].valid)
    {
        while (m_flagCount != 0u)
        {
            FlagPipelineEntry &entry = m_flagPipeline[m_flagHead];
            if (entry.readyCycle > m_cycle)
                break;
            m_flagHead = (m_flagHead + 1u) % kMaxFlagEntries;
            --m_flagCount;
            if (entry.writesMac)
                m_state.mac = entry.mac;
            if (entry.writesStatus)
            {
                const uint32_t current = entry.status & 0xFu;
                m_state.status = (m_state.status & 0xFF0u) | current | ((current | entry.extraSticky) << 6);
            }
            if (entry.writesSticky)
                m_state.status = (m_state.status & 0x03Fu) | (entry.status & 0xFC0u);
            if (entry.writesClip)
                m_state.clip = entry.clip;
            entry.valid = false;
        }
        m_nextCommitCycle = ~0ull; // los flags se confirman al leerlos (commitReadyFlags)
        return;
    }
    while (m_flagCount != 0u)
    {
        FlagPipelineEntry &entry = m_flagPipeline[m_flagHead];
        if (entry.readyCycle > m_cycle)
            break;
        m_flagHead = (m_flagHead + 1u) % kMaxFlagEntries;
        --m_flagCount;

        if (entry.writesMac)
            m_state.mac = entry.mac;
        if (entry.writesStatus)
        {
            const uint32_t current = entry.status & 0xFu;
            m_state.status = (m_state.status & 0xFF0u) | current | ((current | entry.extraSticky) << 6);
        }
        if (entry.writesSticky)
        {
            m_state.status = (m_state.status & 0x03Fu) | (entry.status & 0xFC0u);
        }
        if (entry.writesClip)
            m_state.clip = entry.clip;
        entry.valid = false; // GOW-Port: pushFlagEntry inicializa todos los campos
    }

    if (m_fdiv.valid && m_fdiv.readyCycle <= m_cycle)
    {
        m_state.q = m_fdiv.value;
        const uint32_t currentDi = m_fdiv.statusDi & 0x30u;
        m_state.status = (m_state.status & 0xFCFu) | currentDi | (currentDi << 6);
        m_fdiv.valid = false; // GOW-Port: queueQ escribe todos los campos
    }

    for (ScalarPipelineEntry &entry : m_efu)
    {
        if (entry.valid && entry.readyCycle <= m_cycle)
        {
            m_state.p = entry.value;
            entry.valid = false; // GOW-Port: queueP escribe todos los campos
        }
    }

    for (uint32_t pending = m_storePending; pending != 0u; pending &= pending - 1u)
    {
        const uint32_t index = static_cast<uint32_t>(std::countr_zero(pending));
        PendingStore &store = m_storePipeline[index];
        if (!store.valid || store.readyCycle > m_cycle)
            continue;
        m_storePending &= ~(1u << index);
        if (m_activeVuData && store.address + 16u <= m_activeVuDataSize)
        {
            uint32_t oldWords[4]{};
            std::memcpy(oldWords, m_activeVuData + store.address, sizeof(oldWords));
            for (uint32_t component = 0; component < 4u; ++component)
            {
                if ((store.laneMask & laneForComponent(component)) != 0u)
                    oldWords[component] = store.words[component];
            }
            std::memcpy(m_activeVuData + store.address, oldWords, sizeof(oldWords));
        }
        store = {};
    }

    for (uint32_t pending = m_vfPending; pending != 0u; pending &= pending - 1u)
    {
        const uint32_t index = static_cast<uint32_t>(std::countr_zero(pending));
        PendingVfWrite &write = m_vfWritePipeline[index];
        if (!write.valid || write.readyCycle > m_cycle)
            continue;
        m_vfPending &= ~(1u << index);
        for (uint32_t component = 0; component < 4u; ++component)
        {
            if ((write.laneMask & laneForComponent(component)) != 0u &&
                m_vfLatestWrite[write.reg][component] == write.sequence)
            {
                m_state.vf[write.reg][component] = write.value[component];
            }
        }
        write = {};
    }

    for (uint32_t pending = m_viPending; pending != 0u; pending &= pending - 1u)
    {
        const uint32_t index = static_cast<uint32_t>(std::countr_zero(pending));
        PendingViWrite &write = m_viWritePipeline[index];
        if (!write.valid || write.readyCycle > m_cycle)
            continue;
        m_viPending &= ~(1u << index);
        if (m_viLatestWrite[write.reg] == write.sequence)
            m_state.vi[write.reg] = static_cast<int16_t>(write.value);
        write = {};
    }

    for (uint32_t pending = m_accPending; pending != 0u; pending &= pending - 1u)
    {
        const uint32_t index = static_cast<uint32_t>(std::countr_zero(pending));
        PendingAccWrite &write = m_accWritePipeline[index];
        if (!write.valid || write.readyCycle > m_cycle)
            continue;
        m_accPending &= ~(1u << index);
        for (uint32_t component = 0; component < 4u; ++component)
        {
            if ((write.laneMask & laneForComponent(component)) != 0u &&
                m_accLatestWrite[component] == write.sequence)
            {
                m_state.acc[component] = write.value[component];
            }
        }
        write = {};
    }

    uint64_t next = ~0ull; // sin la cola de flags: se confirman al leerlos (commitReadyFlags)
    for (uint32_t pending = m_storePending; pending != 0u; pending &= pending - 1u)
        next = std::min(next, m_storePipeline[std::countr_zero(pending)].readyCycle);
    for (uint32_t pending = m_vfPending; pending != 0u; pending &= pending - 1u)
        next = std::min(next, m_vfWritePipeline[std::countr_zero(pending)].readyCycle);
    for (uint32_t pending = m_viPending; pending != 0u; pending &= pending - 1u)
        next = std::min(next, m_viWritePipeline[std::countr_zero(pending)].readyCycle);
    for (uint32_t pending = m_accPending; pending != 0u; pending &= pending - 1u)
        next = std::min(next, m_accWritePipeline[std::countr_zero(pending)].readyCycle);
    if (m_fdiv.valid)
        next = std::min(next, m_fdiv.readyCycle);
    for (const ScalarPipelineEntry &entry : m_efu)
        if (entry.valid)
            next = std::min(next, entry.readyCycle);
    m_nextCommitCycle = next;
}

namespace
{
    // GOW-Port: progressXgkick corre en cada ciclo de un XGKICK; leer GOW_VIF_DIAG una vez fuera de la
    // función evita la comprobación de inicialización de un static local en cada llamada.
    const bool g_xgkickTrace = std::getenv("GOW_VIF_DIAG") != nullptr;
}

void VU1Interpreter::progressXgkick()
{
    if (!m_xgkick.active || !m_activeVuData || m_activeVuDataSize == 0u)
        return;

    auto traceRejectedTag = [&](const char *reason, uint32_t offset)
    {
        const bool enabled = g_xgkickTrace;
        static unsigned rejected = 0u;
        if (!enabled || ++rejected > 32u) return;
        uint64_t lo = 0u, hi = 0u;
        std::memcpy(&lo, m_xgkick.packet.data() + offset, 8u);
        std::memcpy(&hi, m_xgkick.packet.data() + offset + 8u, 8u);
        std::fprintf(stderr, "[gow-xgkick:reject] reason=%s pc=0x%X source=0x%X offset=0x%X lo=%016llX hi=%016llX\n",
                     reason, m_state.pc, m_xgkick.sourceAddress, offset,
                     static_cast<unsigned long long>(lo), static_cast<unsigned long long>(hi));
    };

    ++m_xgkick.cycleCredit;
    while (m_xgkick.active && m_xgkick.cycleCredit >= 2u)
    {
        m_xgkick.cycleCredit -= 2u;
        if (m_xgkick.copiedBytes > XgkickPipeline::kBufferSize - 16u)
        {
            traceRejectedTag("buffer-full", m_xgkick.copiedBytes - 16u);
            reportReservedInstruction(false, 0xFFFFFFFBu);
            m_xgkick.active = false;
            return;
        }

        const uint32_t qwordOffset = m_xgkick.copiedBytes;
        const uint32_t position = m_xgkick.sourceAddress + m_xgkick.copiedBytes;
        const uint32_t first = (m_activeVuDataSize & (m_activeVuDataSize - 1u)) == 0u
                                   ? position & (m_activeVuDataSize - 1u)
                                   : position % m_activeVuDataSize;
        if (first + 16u <= m_activeVuDataSize) // GOW-Port: un qword sin dar la vuelta, de una vez
            std::memcpy(m_xgkick.packet.data() + m_xgkick.copiedBytes, m_activeVuData + first, 16u);
        else
            for (uint32_t i = 0; i < 16u; ++i)
            {
                const uint32_t source = (m_xgkick.sourceAddress + m_xgkick.copiedBytes + i) % m_activeVuDataSize;
                m_xgkick.packet[m_xgkick.copiedBytes + i] = m_activeVuData[source];
            }
        m_xgkick.copiedBytes += 16u;

        if (m_xgkick.currentTagEnd == 0u)
        {
            uint64_t tagLo = 0;
            std::memcpy(&tagLo, m_xgkick.packet.data() + qwordOffset, sizeof(tagLo));
            const uint32_t nloop = static_cast<uint32_t>(tagLo & 0x7FFFu);
            const uint32_t format = static_cast<uint32_t>((tagLo >> 58) & 0x3u);
            uint32_t nreg = static_cast<uint32_t>((tagLo >> 60) & 0xFu);
            if (nreg == 0u)
                nreg = 16u;

            if (g_xgkickTrace)
            {
                static unsigned tags = 0u;
                if (++tags <= 96u || (tags % 4096u) == 0u)
                {
                    uint64_t tagHi = 0u;
                    std::memcpy(&tagHi, m_xgkick.packet.data() + qwordOffset + 8u, sizeof(tagHi));
                    std::fprintf(stderr, "[gow-xgkick] tag=%u pc=0x%X source=0x%X offset=0x%X lo=%016llX hi=%016llX\n",
                                 tags, m_state.pc, m_xgkick.sourceAddress, qwordOffset,
                                 static_cast<unsigned long long>(tagLo), static_cast<unsigned long long>(tagHi));
                }
            }

            uint64_t tagBytes = 16u;
            if (format == 0u)
                tagBytes += static_cast<uint64_t>(nloop) * nreg * 16u;
            else if (format == 1u)
                tagBytes += ((static_cast<uint64_t>(nloop) * nreg + 1u) & ~1ull) * 8u;
            else if (format == 2u)
                tagBytes += static_cast<uint64_t>(nloop) * 16u;
            else
            {
                traceRejectedTag("format", qwordOffset);
                reportReservedInstruction(false, 0xFFFFFFF8u);
                m_xgkick.active = false;
                return;
            }

            if (tagBytes > XgkickPipeline::kBufferSize - qwordOffset)
            {
                traceRejectedTag("length", qwordOffset);
                reportReservedInstruction(false, 0xFFFFFFFBu);
                m_xgkick.active = false;
                return;
            }
            m_xgkick.currentTagEnd = qwordOffset + static_cast<uint32_t>(tagBytes);
            m_xgkick.currentTagEop = ((tagLo >> 15) & 1u) != 0u;
            if (m_xgkick.currentTagEop)
                m_xgkick.totalBytes = m_xgkick.currentTagEnd;
        }

        if (m_xgkick.copiedBytes >= m_xgkick.currentTagEnd)
        {
            if (m_xgkick.currentTagEop)
                finishXgkick();
            else
            {
                // The next transferred qword is another GIFtag.
                m_xgkick.currentTagEnd = 0u;
                m_xgkick.currentTagEop = false;
            }
        }
    }
}

namespace
{
    // GOW_VU1N_VERIFY: GIF packets produced by a silent (A/B) run, for comparison.
    bool g_vuVerifyCapture = false;
    std::vector<uint8_t> g_vuVerifyPackets;
}

void VU1Interpreter::finishXgkick()
{
    if (!m_xgkick.active)
        return;
    if (m_verifySilent)
    {
        if (g_vuVerifyCapture)
            g_vuVerifyPackets.insert(g_vuVerifyPackets.end(), m_xgkick.packet.data(), m_xgkick.packet.data() + m_xgkick.totalBytes);
        m_xgkick.active = false;
        return;
    }

    // GOW_VU1_KICKPRIM=<hex prim>: debug, for XGKICK packets with a GIF tag that sets that PRIM (PRE = 1), print the VU1 PC,
    // the source address and how many XYZ2 vertices of those tags kick (ADC = 0) or not
    static const long kickPrim = std::getenv("GOW_VU1_KICKPRIM") ? std::strtol(std::getenv("GOW_VU1_KICKPRIM"), nullptr, 16) : -1;
    if (kickPrim >= 0)
    {
        static int kickShown = 0;
        const uint8_t *pk = m_xgkick.packet.data();
        uint32_t off = 0, kicks = 0, noKicks = 0;
        bool match = false;
        while (off + 16u <= m_xgkick.totalBytes)
        {
            uint64_t lo = 0, hi = 0;
            std::memcpy(&lo, pk + off, 8u);
            std::memcpy(&hi, pk + off + 8u, 8u);
            off += 16u;
            const uint32_t nloop = static_cast<uint32_t>(lo & 0x7FFFu), flg = static_cast<uint32_t>((lo >> 58) & 3u);
            const uint32_t nreg = ((lo >> 60) & 0xFu) ? static_cast<uint32_t>((lo >> 60) & 0xFu) : 16u;
            const bool tagMatch = ((lo >> 46) & 1u) != 0u && static_cast<long>((lo >> 47) & 0x7FFu) == kickPrim;
            match = match || tagMatch;
            if (flg == 0u)
            {
                for (uint32_t i = 0; i < nloop * nreg && off + 16u <= m_xgkick.totalBytes; ++i, off += 16u)
                    if (tagMatch && ((hi >> (4u * (i % nreg))) & 0xFu) == 5u)
                    {
                        uint32_t w3 = 0;
                        std::memcpy(&w3, pk + off + 12u, 4u);
                        ++(((w3 >> 15) & 1u) ? noKicks : kicks);
                    }
            }
            else if (flg == 1u)
                off += ((nloop * nreg * 8u) + 15u) & ~15u;
            else
                off += nloop * 16u;
        }
        if (match && kickShown < 60)
        {
            ++kickShown;
            std::fprintf(stderr, "[vu1-kickprim] pc=0x%X src=0x%X bytes=%u kicked=%u adc=%u\n", m_state.pc, m_xgkick.sourceAddress,
                         m_xgkick.totalBytes, kicks, noKicks);
        }
    }
    if (m_activeMemory)
        m_activeMemory->submitGifPacket(GifPathId::Path1, m_xgkick.packet.data(), m_xgkick.totalBytes);
    else if (m_activeGs)
        m_activeGs->processGIFPacket(m_xgkick.packet.data(), m_xgkick.totalBytes);
    m_xgkick.active = false;
}

void VU1Interpreter::startXgkick(uint32_t qwordAddress)
{
    if (m_unit != Unit::VU1 || !m_activeVuData || m_activeVuDataSize < 16u)
        return;

    const uint32_t sourceAddress = (qwordAddress * 16u) % m_activeVuDataSize;
    m_xgkick.reset();
    m_xgkick.active = true;
    m_xgkick.sourceAddress = sourceAddress;
    m_xgkick.cycleCredit = 1u; // XGKICK's issue cycle counts toward PATH1.
    m_xgkick.issueCycle = m_cycle;
    // Opt-in packet snapshot, following Scotho/socom-unzipped's XGKICK workaround.
    // Capture before later VU instructions re-template the source buffer. Keep
    // the existing bounded parser and circular-memory handling in both modes.
    if (xgkickImmediate())
    {
        m_xgkick.cycleCredit = 0x40000000u;
        progressXgkick();
    }
}

void VU1Interpreter::advanceOneCycle()
{
    ++m_cycle;
    m_state.cycles = m_cycle;
    // LSU commits become visible at the cycle boundary before PATH1 consumes
    // its next qword from VU memory.
    if (m_cycle >= m_nextCommitCycle)
        commitReadyPipelines();
    if (m_xgkick.active)
        progressXgkick();
}

void VU1Interpreter::advanceTo(uint64_t targetCycle)
{
    while (m_cycle < targetCycle)
        advanceOneCycle();
}

bool VU1Interpreter::pipelinesPending() const
{
    if (m_fdiv.valid || m_xgkick.active)
        return true;
    for (const ScalarPipelineEntry &entry : m_efu)
        if (entry.valid)
            return true;
    for (const FlagPipelineEntry &entry : m_flagPipeline)
        if (entry.valid)
            return true;
    for (const PendingStore &store : m_storePipeline)
        if (store.valid)
            return true;
    for (const PendingVfWrite &write : m_vfWritePipeline)
        if (write.valid)
            return true;
    for (const PendingViWrite &write : m_viWritePipeline)
        if (write.valid)
            return true;
    for (const PendingAccWrite &write : m_accWritePipeline)
        if (write.valid)
            return true;
    return false;
}

void VU1Interpreter::flushPipelines()
{
    commitReadyFlags();
    while (pipelinesPending())
    {
        // GOW-Port: al terminar un programa suele quedar solo PATH1 (XGKICK). Ciclo a ciclo, cada ciclo suma
        // un crédito y cada dos se copia un qword, sin nada más que hacer (las demás colas están vacías y no
        // se pueden llenar). Se hace de una vez: n iteraciones de progressXgkick con crédito inicial c0
        // terminan en el ciclo 2n - c0, que es lo que se suma.
        if (m_xgkick.active && m_activeVuData && m_activeVuDataSize != 0u && !m_fdiv.valid && m_flagCount == 0u &&
            (m_storePending | m_vfPending | m_viPending | m_accPending) == 0u && !m_efu[0].valid && !m_efu[1].valid)
        {
            constexpr uint32_t kCredit = 0x40000000u;
            const uint32_t startCredit = m_xgkick.cycleCredit;
            m_xgkick.cycleCredit = kCredit;
            progressXgkick();
            if (!m_xgkick.active)
            {
                const uint64_t iterations = (static_cast<uint64_t>(kCredit) + 1u - m_xgkick.cycleCredit) / 2u;
                m_cycle += 2u * iterations - startCredit;
                m_state.cycles = m_cycle;
                if (m_cycle >= m_nextCommitCycle)
                    commitReadyPipelines();
                commitReadyFlags();
                continue;
            }
            m_xgkick.cycleCredit = startCredit; // no ocurre: el crédito alcanza para cualquier paquete
        }
        advanceOneCycle();
        commitReadyFlags();
    }
}

void VU1Interpreter::commitReadyFlags()
{
    while (m_flagCount != 0u)
    {
        FlagPipelineEntry &entry = m_flagPipeline[m_flagHead];
        if (entry.readyCycle > m_cycle)
            break;
        m_flagHead = (m_flagHead + 1u) % kMaxFlagEntries;
        --m_flagCount;
        if (entry.writesMac)
            m_state.mac = entry.mac;
        if (entry.writesStatus)
        {
            const uint32_t current = entry.status & 0xFu;
            m_state.status = (m_state.status & 0xFF0u) | current | ((current | entry.extraSticky) << 6);
        }
        if (entry.writesSticky)
            m_state.status = (m_state.status & 0x03Fu) | (entry.status & 0xFC0u);
        if (entry.writesClip)
            m_state.clip = entry.clip;
        entry.valid = false;
    }
}

VU1Interpreter::InstructionUsage VU1Interpreter::decodeUpperUsage(uint32_t upper) const
{
    InstructionUsage usage;
    usage.pipeline = PipelineFmac;
    usage.latency = kFmacLatency;

    const uint8_t op = static_cast<uint8_t>(upper & 0x3Fu);
    const uint8_t dest = DEST(upper);
    const uint8_t fs = FS(upper);
    const uint8_t ft = FT(upper);
    const uint8_t fd = FD(upper);

    if (op <= 0x2Fu)
    {
        addVfRead(usage, fs, dest);
        addVfWrite(usage, fd, dest);
        if (op <= 0x1Bu)
            addVfRead(usage, ft, laneForComponent(op & 3u));
        else if (op >= 0x28u)
            addVfRead(usage, ft, op == 0x2Eu ? 0xEu : dest);
        if (op == 0x08u || op == 0x09u || op == 0x0Au || op == 0x0Bu ||
            op == 0x0Cu || op == 0x0Du || op == 0x0Eu || op == 0x0Fu ||
            op == 0x21u || op == 0x23u || op == 0x25u || op == 0x27u ||
            op == 0x29u || op == 0x2Du || op == 0x2Eu)
        {
            usage.accRead = dest;
        }
        return usage;
    }

    if (op >= 0x3Cu)
    {
        const uint8_t special = static_cast<uint8_t>((upper & 3u) | ((upper >> 4) & 0x7Cu));
        const bool writesAcc =
            special <= 0x0Fu ||
            (special >= 0x18u && special <= 0x1Cu) ||
            special == 0x1Eu ||
            (special >= 0x20u && special <= 0x2Au) ||
            (special >= 0x2Cu && special <= 0x2Eu);
        if (writesAcc)
        {
            addVfRead(usage, fs, dest);
            if (special <= 0x1Bu)
                addVfRead(usage, ft, laneForComponent(special & 3u));
            else if ((special >= 0x28u && special <= 0x2Eu))
                addVfRead(usage, ft, special == 0x2Eu ? 0xEu : dest);
            usage.accWrite = dest;
            if ((special >= 0x08u && special <= 0x0Fu) ||
                special == 0x21u || special == 0x23u || special == 0x25u ||
                special == 0x27u || special == 0x29u || special == 0x2Du)
            {
                usage.accRead = dest;
            }
        }
        else if (special >= 0x10u && special <= 0x17u)
        {
            addVfRead(usage, fs, dest);
            addVfWrite(usage, ft, dest);
        }
        else if (special == 0x1Du)
        {
            addVfRead(usage, fs, dest);
            addVfWrite(usage, ft, dest);
        }
        else if (special == 0x1Fu)
        {
            addVfRead(usage, fs, 0xEu);
            addVfRead(usage, ft, 0x1u);
            usage.writesClip = true;
        }
        else if (special != 0x2Fu && special != 0x30u)
        {
            usage.reserved = true;
        }
        return usage;
    }

    usage.reserved = true;
    return usage;
}

VU1Interpreter::InstructionUsage VU1Interpreter::decodeLowerUsage(uint32_t lower) const
{
    InstructionUsage usage;
    if (lower == 0u || lower == 0x8000033Cu)
        return usage;

    const uint8_t opHi = static_cast<uint8_t>((lower >> 25) & 0x7Fu);
    const uint8_t vfT = FT(lower);
    const uint8_t vfS = FS(lower);
    const uint8_t viT = VIT(lower);
    const uint8_t viS = VIS(lower);
    const uint8_t viD = VID(lower);
    const uint8_t dest = DEST(lower);
    auto readVi = [&](uint8_t reg)
    {
        if (reg != 0u)
            usage.viRead |= static_cast<uint16_t>(1u << reg);
    };
    auto writeVi = [&](uint8_t reg)
    {
        if (reg != 0u)
            usage.viWrite |= static_cast<uint16_t>(1u << reg);
    };

    switch (opHi)
    {
    case 0x00:
        usage.pipeline = PipelineLsu;
        usage.latency = 4u;
        readVi(viS);
        addVfWrite(usage, vfT, dest);
        return usage;
    case 0x01:
        usage.pipeline = PipelineLsu;
        usage.latency = 1u;
        readVi(viT);
        addVfRead(usage, vfS, dest);
        return usage;
    case 0x04:
        usage.pipeline = PipelineLsu;
        usage.latency = 4u;
        readVi(viS);
        writeVi(viT);
        return usage;
    case 0x05:
        usage.pipeline = PipelineLsu;
        usage.latency = 1u;
        readVi(viS);
        readVi(viT);
        return usage;
    case 0x08:
    case 0x09:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.delaysNextBranchRead = true;
        readVi(viS);
        writeVi(viT);
        return usage;
    case 0x10:
    case 0x12:
    case 0x13:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.readsClip = true;
        writeVi(1u);
        return usage;
    case 0x11:
        usage.pipeline = PipelineFmac;
        usage.latency = kFmacLatency;
        usage.writesClip = true;
        return usage;
    case 0x14:
    case 0x16:
    case 0x17:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        writeVi(viT);
        return usage;
    case 0x15:
        usage.pipeline = PipelineFmac;
        usage.latency = kFmacLatency;
        return usage;
    case 0x18:
    case 0x1A:
    case 0x1B:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        readVi(viS);
        writeVi(viT);
        return usage;
    case 0x1C:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.readsClip = true;
        writeVi(viT);
        return usage;
    case 0x20:
        usage.pipeline = PipelineBranch;
        return usage;
    case 0x21:
        usage.pipeline = PipelineBranch;
        usage.latency = 1u;
        writeVi(viT);
        return usage;
    case 0x24:
        usage.pipeline = PipelineBranch;
        readVi(viS);
        return usage;
    case 0x25:
        usage.pipeline = PipelineBranch;
        usage.latency = 1u;
        readVi(viS);
        writeVi(viT);
        return usage;
    case 0x28:
    case 0x29:
        usage.pipeline = PipelineBranch;
        readVi(viS);
        readVi(viT);
        return usage;
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
        usage.pipeline = PipelineBranch;
        readVi(viS);
        return usage;
    case 0x40:
        break;
    default:
        usage.reserved = true;
        return usage;
    }

    const uint8_t direct = static_cast<uint8_t>(lower & 0x3Fu);
    if (direct == 0x30u || direct == 0x31u || direct == 0x34u || direct == 0x35u)
    {
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.delaysNextBranchRead = true;
        readVi(viS);
        readVi(viT);
        writeVi(viD);
        return usage;
    }
    if (direct == 0x32u)
    {
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.delaysNextBranchRead = true;
        readVi(viS);
        writeVi(viT);
        return usage;
    }
    if (direct < 0x3Cu)
    {
        usage.reserved = true;
        return usage;
    }

    const uint8_t special = static_cast<uint8_t>((lower & 3u) | ((lower >> 4) & 0x7Cu));
    switch (special)
    {
    case 0x30:
    case 0x31:
        usage.pipeline = PipelineFmac;
        usage.latency = 4u;
        addVfRead(usage, vfS, special == 0x31u ? 0xFu : dest);
        addVfWrite(usage, vfT, dest);
        break;
    case 0x34:
    case 0x36:
        usage.pipeline = PipelineLsu;
        usage.latency = 4u;
        usage.viLatency = 1u;
        usage.delaysNextBranchRead = true;
        readVi(viS);
        writeVi(viS);
        addVfWrite(usage, vfT, dest);
        break;
    case 0x35:
    case 0x37:
        usage.pipeline = PipelineLsu;
        usage.latency = 1u;
        usage.delaysNextBranchRead = true;
        readVi(viT);
        writeVi(viT);
        addVfRead(usage, vfS, dest);
        break;
    case 0x38:
        usage.pipeline = PipelineFdiv;
        usage.latency = 7u;
        addVfRead(usage, vfS, laneForComponent((lower >> 21) & 3u));
        addVfRead(usage, vfT, laneForComponent((lower >> 23) & 3u));
        break;
    case 0x39:
        usage.pipeline = PipelineFdiv;
        usage.latency = 7u;
        addVfRead(usage, vfT, laneForComponent((lower >> 23) & 3u));
        break;
    case 0x3A:
        usage.pipeline = PipelineFdiv;
        usage.latency = 13u;
        addVfRead(usage, vfS, laneForComponent((lower >> 21) & 3u));
        addVfRead(usage, vfT, laneForComponent((lower >> 23) & 3u));
        break;
    case 0x3B:
        usage.pipeline = PipelineFdiv;
        usage.waitQ = true;
        break;
    case 0x3C:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        usage.delaysNextBranchRead = true;
        addVfRead(usage, vfS, laneForComponent((lower >> 21) & 3u));
        writeVi(viT);
        break;
    case 0x3D:
        usage.pipeline = PipelineFmac;
        usage.latency = 4u;
        readVi(viS);
        addVfWrite(usage, vfT, dest);
        break;
    case 0x3E:
        usage.pipeline = PipelineLsu;
        usage.latency = 4u;
        readVi(viS);
        writeVi(viT);
        break;
    case 0x3F:
        usage.pipeline = PipelineLsu;
        usage.latency = 1u;
        readVi(viS);
        readVi(viT);
        break;
    case 0x40:
    case 0x41:
        usage.pipeline = PipelineFmac;
        usage.latency = 4u;
        addVfWrite(usage, vfT, dest);
        break;
    case 0x42:
    case 0x43:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        addVfRead(usage, vfS, laneForComponent((lower >> 21) & 3u));
        break;
    case 0x64:
        if (m_unit == Unit::VU0)
        {
            usage.reserved = true;
            break;
        }
        usage.pipeline = PipelineFmac;
        usage.latency = 4u;
        addVfWrite(usage, vfT, dest);
        break;
    case 0x68:
    case 0x69:
        usage.pipeline = PipelineIalu;
        usage.latency = 1u;
        writeVi(viT);
        break;
    case 0x6C:
        if (m_unit == Unit::VU0)
        {
            usage.reserved = true;
            break;
        }
        usage.pipeline = PipelineXgkick;
        usage.latency = 2u;
        readVi(viS);
        break;
    // GOW-Port: códigos EFU reales y sus latencias, contrastados con LowerOP
    // de PCSX2 32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e.
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7C:
    case 0x7D:
    case 0x7E:
        if (m_unit == Unit::VU0)
        {
            usage.reserved = true;
            break;
        }
        usage.pipeline = PipelineEfu;
        switch (special)
        {
        case 0x70:
            usage.latency = 11u;
            break;
        case 0x71:
        case 0x72:
        case 0x79:
            usage.latency = 18u;
            break;
        case 0x73:
            usage.latency = 24u;
            break;
        case 0x74:
        case 0x75:
        case 0x7D:
            usage.latency = 54u;
            break;
        case 0x76:
        case 0x78:
        case 0x7A:
            usage.latency = 12u;
            break;
        case 0x7C:
            usage.latency = 29u;
            break;
        case 0x7E:
            usage.latency = 44u;
            break;
        default:
            break;
        }
        if (special >= 0x70u && special <= 0x73u)
            addVfRead(usage, vfS, 0xEu);
        else if (special == 0x74u)
            addVfRead(usage, vfS, 0xCu);
        else if (special == 0x75u)
            addVfRead(usage, vfS, 0xAu);
        else if (special == 0x76u)
            addVfRead(usage, vfS, 0xFu);
        else
            addVfRead(usage, vfS, laneForComponent((lower >> 21) & 3u));
        break;
    case 0x7B:
        if (m_unit == Unit::VU0)
        {
            usage.reserved = true;
            break;
        }
        usage.pipeline = PipelineEfu;
        usage.waitP = true;
        break;
    default:
        usage.reserved = true;
        break;
    }
    return usage;
}

VU1Interpreter::DecodedInstructionPair VU1Interpreter::decodeInstructionPair(const uint8_t *vuCode, uint32_t pc) const
{
    DecodedInstructionPair decoded;
    std::memcpy(&decoded.lower, vuCode + pc, sizeof(decoded.lower));
    std::memcpy(&decoded.upper, vuCode + pc + sizeof(decoded.lower), sizeof(decoded.upper));
    decoded.iBit = (decoded.upper & 0x80000000u) != 0u;
    decoded.eBit = (decoded.upper & 0x40000000u) != 0u;
    decoded.mBit = (decoded.upper & 0x20000000u) != 0u;
    decoded.dBit = (decoded.upper & 0x10000000u) != 0u;
    decoded.tBit = (decoded.upper & 0x08000000u) != 0u;
    decoded.upperUsage = decodeUpperUsage(decoded.upper);
    if ((decoded.upper & 0x3Fu) >= 0x3Cu)
    {
        const uint32_t special = (decoded.upper & 0x3u) | ((decoded.upper >> 4) & 0x7Cu);
        decoded.upperNop = special == 0x2Fu || special == 0x30u;
    }
    if (!decoded.iBit)
        decoded.lowerUsage = decodeLowerUsage(decoded.lower);

    const uint8_t upperWriteReg = decoded.upperUsage.vfWrite.reg;
    if (upperWriteReg != 0u && (vfReadLanes(decoded.lowerUsage, upperWriteReg) != 0u || decoded.lowerUsage.vfWrite.reg == upperWriteReg))
    {
        decoded.upperVfShadowReg = upperWriteReg;
        if (decoded.lowerUsage.vfWrite.reg == upperWriteReg)
            decoded.suppressedLowerVf = upperWriteReg;
    }
    return decoded;
}

void VU1Interpreter::rebuildDecodedCodeCache(const uint8_t *vuCode, uint32_t codeSize,
                                             const PS2Memory *memory, uint64_t generation)
{
    const uint32_t pairCount = std::min<uint32_t>(codeSize / 8u, kMaxDecodedPairs);
    for (uint32_t i = 0; i < pairCount; ++i)
        m_decodedCodeCache[i] = decodeInstructionPair(vuCode, i * 8u);

    m_cachedVuCode = vuCode;
    m_cachedMemory = memory;
    m_cachedCodeSize = codeSize;
    m_cachedCodeGeneration = generation;
    m_decodedCodeCacheValid = true;
    // FSAND (0x16), FSEQ (0x14) y FSOR (0x17) son las únicas lecturas del estado en VU1.
    m_statusUnread = m_directRegisterWrites;
    for (uint32_t i = 0; i < pairCount && m_statusUnread; ++i)
    {
        const DecodedInstructionPair &pair = m_decodedCodeCache[i];
        const uint32_t op = pair.lower >> 25;
        if (!pair.iBit && (op == 0x14u || op == 0x16u || op == 0x17u))
            m_statusUnread = false;
    }
    m_statusQuiet = m_statusUnread;
    for (uint32_t i = 0; i < pairCount && m_statusQuiet; ++i)
    {
        const DecodedInstructionPair &pair = m_decodedCodeCache[i];
        if (!pair.iBit && (pair.lower >> 25) == 0x15u) // FSSET
            m_statusQuiet = false;
    }
    // GOW-Port: GOW_VU1C_FLAGS_VIVOS=1 calcula siempre los flags de las FMAC "muertas" de los bloques (diagnostico).
    static const bool liveFlags = std::getenv("GOW_VU1C_FLAGS_VIVOS") != nullptr;
    if (liveFlags)
        m_statusQuiet = false;
}

const VU1Interpreter::DecodedInstructionPair &VU1Interpreter::getDecodedInstructionPairForPc(
    const uint8_t *vuCode, uint32_t codeSize, PS2Memory *memory, uint32_t pc)
{
    if ((pc & 7u) != 0u)
        return m_decodedScratch = decodeInstructionPair(vuCode, pc);

    const bool trackedVu1Code = memory != nullptr &&
                                ((m_unit == Unit::VU1 && vuCode == memory->getVU1Code()) ||
                                 (m_unit == Unit::VU0 && vuCode == memory->getVU0Code()));
    if (!trackedVu1Code)
        return m_decodedScratch = decodeInstructionPair(vuCode, pc);

    const uint64_t generation = m_unit == Unit::VU1 ? memory->getVU1CodeGeneration() : memory->getVU0CodeGeneration();
    if (!m_decodedCodeCacheValid ||
        m_cachedVuCode != vuCode ||
        m_cachedMemory != memory ||
        m_cachedCodeSize != codeSize ||
        m_cachedCodeGeneration != generation)
    {
        rebuildDecodedCodeCache(vuCode, codeSize, memory, generation);
    }
    const uint32_t pairIndex = pc / 8u;
    if (pairIndex >= kMaxDecodedPairs)
        return m_decodedScratch = decodeInstructionPair(vuCode, pc);
    return m_decodedCodeCache[pairIndex];
}

void VU1Interpreter::reportReservedInstruction(bool upper, uint32_t instruction)
{
    RUNTIME_ERROR(
        "[VU" << (m_unit == Unit::VU1 ? "1" : "0")
              << " reserved " << (upper ? "upper" : "lower")
              << "] cycle=" << m_cycle
              << " pc=0x" << std::hex << m_state.pc
              << " instruction=0x" << instruction
              << std::dec << '\n');
    m_stopRequested = true;
}

void VU1Interpreter::execute(uint8_t *vuCode, uint32_t codeSize,
                             uint8_t *vuData, uint32_t dataSize,
                             GS &gs, PS2Memory *memory,
                             uint32_t startPC, uint32_t top, uint32_t itop,
                             uint32_t maxCycles)
{
    resetScheduler();
    m_state.pc = startPC & microAddressMask();
    m_state.ebit = false;
    m_state.haltAfterDelaySlot = false;
    m_state.stoppedByD = false;
    m_state.stoppedByT = false;
    m_state.top = top;
    m_state.itop = itop;
    m_state.branchPending = false;
    m_state.branchTarget = 0;
    m_state.branchDelay = 0;
    m_state.vf[0][0] = 0.0f;
    m_state.vf[0][1] = 0.0f;
    m_state.vf[0][2] = 0.0f;
    m_state.vf[0][3] = 1.0f;
    run(vuCode, codeSize, vuData, dataSize, gs, memory, maxCycles);
}

void VU1Interpreter::resume(uint8_t *vuCode, uint32_t codeSize,
                            uint8_t *vuData, uint32_t dataSize,
                            GS &gs, PS2Memory *memory,
                            uint32_t top, uint32_t itop, uint32_t maxCycles)
{
    m_state.top = top;
    m_state.itop = itop;
    m_state.stoppedByD = false;
    m_state.stoppedByT = false;
    run(vuCode, codeSize, vuData, dataSize, gs, memory, maxCycles);
}

void VU1Interpreter::run(uint8_t *vuCode, uint32_t codeSize,
                         uint8_t *vuData, uint32_t dataSize,
                         GS &gs, PS2Memory *memory, uint32_t maxCycles)
{
    m_activeVuData = vuData;
    m_activeVuDataSize = dataSize;
    m_activeGs = &gs;
    m_activeMemory = memory;

    ps2_perf::Scope perf(ps2_perf::Bucket::Vu); // GOW-Port: VU0/VU1; las llamadas al GS se descuentan.
    const int previousRoundingMode = std::fegetround();
    const bool useVuRounding = std::fesetround(FE_TOWARDZERO) == 0;
    StepContext context{vuCode, codeSize, vuData, dataSize, &gs, memory, m_cycle + maxCycles, false};
    m_lastRunHitBudget = false; // GOW-Port: funciona también con un despachador compilado.
    const uint32_t runStartPc = m_state.pc;
    // GOW_VU1_STARTMAC=1: debug, the MAC and clip flags a startPc 0 program starts with (committed / with pending writes)
    static const bool startMacLog = std::getenv("GOW_VU1_STARTMAC") != nullptr;
    static unsigned startMacShown = 0;
    if (startMacLog && m_unit == Unit::VU1 && m_state.pc == 0u && startMacShown < 4000u && (startMacShown++ % 50u) == 0u)
    {
        VU1Interpreter probe(*this);
        probe.commitEverythingNow();
        std::fprintf(stderr, "[vu1-startmac] ours mac=%x clip=%x (after committing pending: mac=%x clip=%x)\n", m_state.mac & 0xFFFFu,
                     m_state.clip & 0xFFFFFFu, probe.m_state.mac & 0xFFFFu, probe.m_state.clip & 0xFFFFFFu);
    }
    // GOW-Port: GOW_VU1_STATS=1 prints, every 5 s, MSCAL runs, VU1 cycles, interpreted steps and host time in run().
    static const bool vuStats = std::getenv("GOW_VU1_STATS") != nullptr;
    const uint64_t statCycle0 = vuStats ? m_cycle : 0u;
    const auto statT0 = vuStats ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
    uint64_t interpretedSteps = 0u;
    // GOW-Port: native backend first (translated blocks, immediate semantics); the exact engine steps one pair whenever the
    // current pc has no native block and is the fallback for everything else.
    const auto runExact = [&](StepContext &ctx)
    {
        if (CompiledProgramFn program = compiledProgramFor(vuCode, codeSize, memory))
            program(*this, ctx);
        else
            while (stepInterpreted(ctx))
            {
                ++interpretedSteps;
            }
    };
    const auto runNativeLoop = [&](StepContext &ctx) -> bool
    {
        bool usedNative = false;
        for (;;)
        {
            if (runNative(ctx))
                return true;
            if (!m_native || !m_native->enabled)
                return usedNative;
            usedNative = true;
            if (!stepInterpreted(ctx))
                return true;
        }
    };
    if (m_unit == Unit::VU1 && !m_native)
        m_native = new NativeState();
    if (m_unit == Unit::VU1 && m_native && m_native->enabled && vuData && codeSize == PS2_VU1_CODE_SIZE)
        VU1NativeAccess::recordReplay(*this, &context, maxCycles);
    if (m_unit == Unit::VU1 && m_native && m_native->enabled && m_native->verifyLeft != 0u && vuData && codeSize == PS2_VU1_CODE_SIZE)
    {
        --m_native->verifyLeft;
        const uint32_t startPc = m_state.pc;
        std::vector<uint8_t> dataSave(vuData, vuData + dataSize);
        VU1Interpreter saved(*this);
        const bool silentBefore = m_verifySilent;
        m_verifySilent = true;
        g_vuVerifyCapture = true;
        g_vuVerifyPackets.clear();
        StepContext ctxA = context;
        runNativeLoop(ctxA);
        VU1State stateA = m_state;
        std::vector<uint8_t> dataA(vuData, vuData + dataSize);
        flushPipelines(); // finish the asynchronous XGKICK so its packet is captured
        std::vector<uint8_t> packetsA = g_vuVerifyPackets;
        const bool endedA = ctxA.programEnded;
        *this = saved;
        std::memcpy(vuData, dataSave.data(), dataSize);
        m_verifySilent = true;
        g_vuVerifyPackets.clear();
        StepContext ctxB = context;
        m_native->enabled = false;
        // oracle: the cycle-exact interpreter (the generated "compiled" programs are not used as ground truth here)
        while (stepInterpreted(ctxB))
        {
        }
        m_native->enabled = true;
        VU1State stateB = m_state;
        std::vector<uint8_t> dataB(vuData, vuData + dataSize);
        flushPipelines(); // finish the asynchronous XGKICK so its packet is captured
        std::vector<uint8_t> packetsB = g_vuVerifyPackets;
        const bool endedB = ctxB.programEnded;
        g_vuVerifyCapture = false;
        *this = saved;
        std::memcpy(vuData, dataSave.data(), dataSize);
        m_verifySilent = silentBefore;
        const auto close = [](uint32_t a, uint32_t b)
        {
            if (a == b)
                return true;
            float fa, fb;
            std::memcpy(&fa, &a, 4);
            std::memcpy(&fb, &b, 4);
            if (!std::isfinite(fa) || !std::isfinite(fb))
                return false;
            return std::fabs(fa - fb) <= 2e-4f * std::max(1.0f, std::max(std::fabs(fa), std::fabs(fb)));
        };
        // integer-like words (zero exponent: GIF data, the XYZ2 ADC bit, VI-stored values) compare exactly
        const auto same = [&close](uint32_t a, uint32_t b) { return ((a | b) & 0x7F800000u) == 0u ? a == b : close(a, b); };
        static unsigned reports = 0, checked = 0, bad = 0, bisected = 0;
        ++checked;
        std::string why;
        char buf[160];
        if (endedA != endedB)
            why += " ended";
        if (stateA.pc != stateB.pc)
        {
            std::snprintf(buf, sizeof(buf), " pc %x/%x", stateA.pc, stateB.pc);
            why += buf;
        }
        for (int r = 0; r < 32 && why.size() < 300; ++r)
            for (int c = 0; c < 4; ++c)
            {
                uint32_t a, b;
                std::memcpy(&a, &stateA.vf[r][c], 4);
                std::memcpy(&b, &stateB.vf[r][c], 4);
                if (!close(a, b))
                {
                    std::snprintf(buf, sizeof(buf), " vf%d.%d %08x/%08x", r, c, a, b);
                    why += buf;
                }
            }
        for (int r = 1; r < 16; ++r)
            if (stateA.vi[r] != stateB.vi[r])
            {
                std::snprintf(buf, sizeof(buf), " vi%d %x/%x", r, stateA.vi[r], stateB.vi[r]);
                why += buf;
            }
        if ((stateA.mac & 0xF0FFu) != (stateB.mac & 0xF0FFu))
        {
            std::snprintf(buf, sizeof(buf), " mac %x/%x", stateA.mac, stateB.mac);
            why += buf;
        }
        if (stateA.clip != stateB.clip)
        {
            std::snprintf(buf, sizeof(buf), " clip %x/%x", stateA.clip, stateB.clip);
            why += buf;
        }
        {
            uint32_t a, b;
            std::memcpy(&a, &stateA.q, 4);
            std::memcpy(&b, &stateB.q, 4);
            if (!close(a, b))
            {
                std::snprintf(buf, sizeof(buf), " q %08x/%08x", a, b);
                why += buf;
            }
        }
        unsigned memDiff = 0;
        for (uint32_t o = 0; o + 4u <= dataSize; o += 4u)
        {
            uint32_t a, b;
            std::memcpy(&a, dataA.data() + o, 4);
            std::memcpy(&b, dataB.data() + o, 4);
            if (!same(a, b))
            {
                if (memDiff++ < 3u)
                {
                    std::snprintf(buf, sizeof(buf), " mem[%x] %08x/%08x", o, a, b);
                    why += buf;
                }
            }
        }
        if (memDiff)
        {
            std::snprintf(buf, sizeof(buf), " memDiffWords=%u", memDiff);
            why += buf;
        }
        if (packetsA.size() != packetsB.size())
        {
            std::snprintf(buf, sizeof(buf), " packetBytes %zu/%zu", packetsA.size(), packetsB.size());
            why += buf;
        }
        else
        {
            unsigned pd = 0;
            for (size_t o = 0; o + 4u <= packetsA.size(); o += 4u)
            {
                uint32_t a, b;
                std::memcpy(&a, packetsA.data() + o, 4);
                std::memcpy(&b, packetsB.data() + o, 4);
                // integer words (zero exponent: GIF tags, XYZ2 coordinates and the ADC bit, colours) must match exactly;
                // the float tolerance would accept a flipped ADC bit as a tiny denormal difference
                const bool integerWord = ((a | b) & 0x7F800000u) == 0u;
                if ((integerWord ? a != b : !close(a, b)) && pd++ < 2u)
                {
                    std::snprintf(buf, sizeof(buf), " pkt[%zx] %08x/%08x", o, a, b);
                    why += buf;
                }
            }
        }
        if (!why.empty())
        {
            ++bad;
            if (reports++ < 40u || (why.find("0000ffff") != std::string::npos && bisected < 6u))
                std::fprintf(stderr, "[vu1n-verify] run %u (bad %u) startPc=%x MISMATCH:%s\n", checked, bad, startPc, why.c_str());
            if (why.find("0000ffff") != std::string::npos && bisected++ < 6u) // ADC words (0xFFFF) set on one side only
            {
                // bisect: smallest number of native blocks (rest exact) whose result already differs from the pure exact run
                const auto differs = [&](unsigned limit)
                {
                    *this = saved;
                    std::memcpy(vuData, dataSave.data(), dataSize);
                    m_verifySilent = true;
                    g_vuVerifyPackets.clear();
                    m_native->limit = limit;
                    m_native->count = 0u;
                    m_native->trace.clear();
                    StepContext c = context;
                    runNativeLoop(c);
                    m_native->limit = ~0u;
                    bool d = m_state.pc != stateB.pc || (m_state.mac & 0xF0FFu) != (stateB.mac & 0xF0FFu) || m_state.clip != stateB.clip;
                    for (int r = 0; r < 32 && !d; ++r)
                        for (int k = 0; k < 4; ++k)
                        {
                            uint32_t a, b;
                            std::memcpy(&a, &m_state.vf[r][k], 4);
                            std::memcpy(&b, &stateB.vf[r][k], 4);
                            d = d || !close(a, b);
                        }
                    for (int r = 1; r < 16 && !d; ++r)
                        d = m_state.vi[r] != stateB.vi[r];
                    for (uint32_t o = 0; o + 4u <= dataSize && !d; o += 4u)
                    {
                        uint32_t a, b;
                        std::memcpy(&a, vuData + o, 4);
                        std::memcpy(&b, dataB.data() + o, 4);
                        d = !same(a, b);
                    }
                    return d;
                };
                unsigned lo = 0u, hi = 100000u;
                std::fprintf(stderr, "[vu1n-verify]   exact-via-step differs from exact-compiled: %d\n", differs(0u) ? 1 : 0);
                if (differs(hi))
                {
                    while (hi - lo > 1u)
                    {
                        const unsigned mid = (lo + hi) / 2u;
                        (differs(mid) ? hi : lo) = mid;
                    }
                    differs(hi);
                    std::fprintf(stderr, "[vu1n-verify]   first bad block #%u at pc=%x\n", hi, m_native->trace.empty() ? 0u : m_native->trace.back());
                    if (std::getenv("GOW_VU1N_DUMP"))
                    {
                        // the micro memory of the run, to disassemble the bad block
                        char codeName[64];
                        std::snprintf(codeName, sizeof(codeName), "vu1n_bad_%x_run%u.bin", m_native->trace.empty() ? 0u : m_native->trace.back(), checked);
                        if (FILE *cf = std::fopen(codeName, "wb"))
                        {
                            std::fwrite(vuCode, 1, codeSize, cf);
                            std::fclose(cf);
                        }
                        const VU1State &e = m_native->snap;
                        for (int r : {1, 2, 23})
                            std::fprintf(stderr, "[vu1n-verify]   exact-final vf%d = %08x %08x %08x %08x\n", r, *reinterpret_cast<const uint32_t *>(&stateB.vf[r][0]), *reinterpret_cast<const uint32_t *>(&stateB.vf[r][1]), *reinterpret_cast<const uint32_t *>(&stateB.vf[r][2]), *reinterpret_cast<const uint32_t *>(&stateB.vf[r][3]));
                        const auto w = [](float f) { uint32_t b; std::memcpy(&b, &f, 4); return b; };
                        for (int r = 0; r < 32; ++r)
                            std::fprintf(stderr, "[vu1n-verify]   entry vf%d = %08x %08x %08x %08x\n", r, w(e.vf[r][0]), w(e.vf[r][1]), w(e.vf[r][2]), w(e.vf[r][3]));
                        std::fprintf(stderr, "[vu1n-verify]   entry acc = %08x %08x %08x %08x q=%08x mac=%x clip=%x\n", w(e.acc[0]), w(e.acc[1]), w(e.acc[2]), w(e.acc[3]), w(e.q), e.mac, e.clip);
                        for (int r = 0; r < 16; ++r)
                            std::fprintf(stderr, "[vu1n-verify]   entry vi%d = %x\n", r, e.vi[r]);
                    }
                }
                else
                    std::fprintf(stderr, "[vu1n-verify]   no native-block prefix reproduces it (exact-side/ordering difference)\n");
                *this = saved;
                std::memcpy(vuData, dataSave.data(), dataSize);
                m_verifySilent = silentBefore;
            }
        }
        else if (checked % 2000u == 0u)
            std::fprintf(stderr, "[vu1n-verify] %u runs checked, %u mismatches\n", checked, bad);
    }
    if (m_unit == Unit::VU1 && m_native && m_native->enabled && vuData && codeSize == PS2_VU1_CODE_SIZE)
    {
        if (!runNativeLoop(context))
            runExact(context);
    }
    else
        runExact(context);
    if (vuStats)
    {
        static uint64_t runs = 0, cycles = 0, interp = 0, runsInterp = 0; static double ms = 0.0, msInterp = 0.0;
        static auto last = std::chrono::steady_clock::now();
        const double dt = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - statT0).count();
        ++runs; cycles += m_cycle - statCycle0; interp += interpretedSteps; ms += dt;
        if (interpretedSteps) { ++runsInterp; msInterp += dt; }
        if (std::chrono::steady_clock::now() - last > std::chrono::seconds(5))
        {
            std::fprintf(stderr, "[vu1-stats] runs=%llu (interpreted %llu) cycles=%llu interpSteps=%llu ms=%.0f (interp %.0f) ns/cycle=%.1f\n",
                         (unsigned long long)runs, (unsigned long long)runsInterp, (unsigned long long)cycles, (unsigned long long)interp, ms, msInterp, cycles ? ms * 1e6 / cycles : 0.0);
            extern unsigned long long g_vuUpperHist[128], g_vuLowerHist[128];
            for (int pass = 0; pass < 2; ++pass)
            {
                unsigned long long *h = pass ? g_vuLowerHist : g_vuUpperHist; unsigned long long tot = 0;
                for (int i = 0; i < 128; ++i) tot += h[i];
                std::fprintf(stderr, "[vu1-generic-%s] total=%llu top:", pass ? "lower" : "upper", tot);
                for (int k = 0; k < 10; ++k) { int b = 0; for (int i = 1; i < 128; ++i) if (h[i] > h[b]) b = i; if (!h[b]) break; std::fprintf(stderr, " %02x=%llu", b, h[b]); h[b] = 0; }
                std::fprintf(stderr, "\n");
                for (int i = 0; i < 128; ++i) h[i] = 0;
            }
            runs = cycles = interp = runsInterp = 0; ms = msInterp = 0.0; last = std::chrono::steady_clock::now();
        }
    }
    const bool programEnded = context.programEnded;

    if (programEnded)
    {
        flushPipelines();
        m_state.ebit = false;
        m_state.haltAfterDelaySlot = false;
        m_pendingHaltD = false;
        m_pendingHaltT = false;
    }
    m_lastRunHitBudget = !programEnded && !m_stopRequested && m_cycle >= context.budgetEnd; // GOW-Port
    commitReadyFlags(); // GOW-Port: el estado visible tras la ejecución
    m_state.cycles = m_cycle;
    // GOW_VU1_STARTMAC=1 also counts the MAC flag a startPc 0 program ends with (A/B with PCSX2's interpreter)
    static const bool endMacLog = std::getenv("GOW_VU1_STARTMAC") != nullptr;
    static unsigned endMacCount[3] = {}, endMacRuns = 0;
    if (endMacLog && m_unit == Unit::VU1 && runStartPc == 0u && programEnded)
    {
        const uint32_t mac = m_state.mac & 0xFFFFu;
        ++endMacCount[mac == 0x12u ? 0 : mac == 0u ? 1 : 2];
        if (++endMacRuns % 20000u == 0u)
            std::fprintf(stderr, "[vu1-endmac] ours runs=%u mac12=%u mac0=%u other=%u\n", endMacRuns, endMacCount[0], endMacCount[1], endMacCount[2]);
    }
    if (useVuRounding && previousRoundingMode != -1)
        std::fesetround(previousRoundingMode);
}

// GOW-Port: GOW_VU1C_VERIFICAR. Antes de un bloque compilado se ejecutan sus pares con el interprete desde el
// mismo estado, se guarda el resultado y se restaura todo; al acabar el bloque compilado se compara.
// Se omiten los bloques con XGKICK o con un XGKICK en curso (efectos fuera de VU1).
void VU1Interpreter::verifyBlockStart(StepContext &context, uint32_t pc, const uint32_t *words, size_t bytes)
{
    (void)words;
    if (m_verifyLeft != 0u || context.vuData == nullptr)
        return;
    const uint32_t pairs = static_cast<uint32_t>(bytes / 8u);
    const VU1Interpreter saved = *this;
    const StepContext savedContext = context;
    const std::vector<uint8_t> savedData(context.vuData, context.vuData + context.dataSize);
    uint32_t done = 0;
    m_verifySilent = true;
    while (done < pairs && m_state.pc == pc + done * 8u)
    {
        ++done;
        if (!stepInterpreted(context))
            break;
    }
    m_verifySilent = false;
    const VU1State expected = m_state;
    const uint64_t expectedCycle = m_cycle;
    const bool kickActive = m_xgkick.active;
    const uint32_t kickBytes = m_xgkick.copiedBytes;
    std::vector<uint8_t> kick(m_xgkick.packet.begin(), m_xgkick.packet.begin() + std::min<uint32_t>(kickBytes, XgkickPipeline::kBufferSize));
    std::vector<uint8_t> expectedData(context.vuData, context.vuData + context.dataSize);
    *this = saved;
    context = savedContext;
    std::memcpy(context.vuData, savedData.data(), savedData.size());
    if (done == 0u)
        return;
    m_verifyExpected = expected;
    m_verifyCycle = expectedCycle;
    m_verifyData = std::move(expectedData);
    m_verifyKickActive = kickActive;
    m_verifyKickBytes = kickBytes;
    m_verifyKick = std::move(kick);
    m_verifyHead = pc;
    m_verifyPairs = done;
    m_verifyLeft = done;
}

void VU1Interpreter::verifyBlockEnd(StepContext &context)
{
    static int reports = 0;
    static unsigned long checked = 0, withKick = 0;
    ++checked;
    withKick += m_verifyKickBytes != 0u ? 1u : 0u;
    if (checked % 5000u == 0u)
        std::fprintf(stderr, "[vu1c-verify] checked %lu blocks (%lu with XGKICK data)\n", checked, withKick);
    if (reports >= 200)
        return;
    const VU1State &e = m_verifyExpected;
    const VU1State &g = m_state;
    char what[160] = {};
    for (int r = 0; r < 32 && !what[0]; ++r)
        for (int l = 0; l < 4; ++l)
            if (std::memcmp(&e.vf[r][l], &g.vf[r][l], 4) != 0)
            {
                std::snprintf(what, sizeof(what), "vf%02d.%c exp=%g got=%g", r, "xyzw"[l], e.vf[r][l], g.vf[r][l]);
                break;
            }
    for (int r = 1; r < 16 && !what[0]; ++r)
        if (static_cast<int16_t>(e.vi[r]) != static_cast<int16_t>(g.vi[r]))
            std::snprintf(what, sizeof(what), "vi%02d exp=%d got=%d", r, e.vi[r], g.vi[r]);
    for (int l = 0; l < 4 && !what[0]; ++l)
        if (std::memcmp(&e.acc[l], &g.acc[l], 4) != 0)
            std::snprintf(what, sizeof(what), "acc.%c exp=%g got=%g", "xyzw"[l], e.acc[l], g.acc[l]);
    if (!what[0] && std::memcmp(&e.q, &g.q, 4) != 0)
        std::snprintf(what, sizeof(what), "q exp=%g got=%g", e.q, g.q);
    if (!what[0] && std::memcmp(&e.p, &g.p, 4) != 0)
        std::snprintf(what, sizeof(what), "p exp=%g got=%g", e.p, g.p);
    if (!what[0] && (e.pc != g.pc || e.clip != g.clip || e.r != g.r))
        std::snprintf(what, sizeof(what), "pc %x/%x mac %x/%x clip %x/%x status %x/%x r %x/%x", e.pc, g.pc, e.mac,
                      g.mac, e.clip, g.clip, e.status, g.status, e.r, g.r);
    if (!what[0] && (e.ebit != g.ebit || e.branchPending != g.branchPending || m_verifyCycle != m_cycle))
        std::snprintf(what, sizeof(what), "ebit %d/%d branch %d/%d cycle %llu/%llu", e.ebit, g.ebit, e.branchPending,
                      g.branchPending, static_cast<unsigned long long>(m_verifyCycle), static_cast<unsigned long long>(m_cycle));
    if (!what[0] && (m_verifyKickActive != m_xgkick.active || m_verifyKickBytes != m_xgkick.copiedBytes))
        std::snprintf(what, sizeof(what), "xgkick active %d/%d copied %u/%u", m_verifyKickActive, m_xgkick.active,
                      m_verifyKickBytes, m_xgkick.copiedBytes);
    if (!what[0])
        for (uint32_t a = 0; a + 4u <= m_verifyKick.size(); a += 4u)
            if (std::memcmp(m_verifyKick.data() + a, m_xgkick.packet.data() + a, 4) != 0)
            {
                uint32_t ev, gv;
                std::memcpy(&ev, m_verifyKick.data() + a, 4);
                std::memcpy(&gv, m_xgkick.packet.data() + a, 4);
                std::snprintf(what, sizeof(what), "xgkick packet +%04x exp=%08x got=%08x (src %04x)", a, ev, gv,
                              m_xgkick.sourceAddress);
                break;
            }
    if (!what[0] && context.vuData != nullptr && m_verifyData.size() == context.dataSize)
        for (uint32_t a = 0; a < context.dataSize; a += 4u)
            if (std::memcmp(m_verifyData.data() + a, context.vuData + a, 4) != 0)
            {
                uint32_t ev, gv;
                std::memcpy(&ev, m_verifyData.data() + a, 4);
                std::memcpy(&gv, context.vuData + a, 4);
                std::snprintf(what, sizeof(what), "mem %04x exp=%08x got=%08x", a, ev, gv);
                break;
            }
    if (!what[0])
        return;
    ++reports;
    std::fprintf(stderr, "[vu1c-verify] block %04x pairs=%u code=%016llx: %s\n", m_verifyHead, m_verifyPairs,
                 static_cast<unsigned long long>(hashMicrocode(context.vuCode, context.codeSize)), what);
}

bool VU1Interpreter::stepInterpreted(StepContext &context)
{
    if (!compiledPrologue(context))
        return false;
    if (m_state.pc + 8u > context.codeSize)
        return false;
    const DecodedInstructionPair &decoded =
        getDecodedInstructionPairForPc(context.vuCode, context.codeSize, context.memory, m_state.pc);
    if (decoded.upperUsage.reserved || decoded.lowerUsage.reserved)
    {
        reportReservedInstruction(decoded.upperUsage.reserved, decoded.upperUsage.reserved ? decoded.upper : decoded.lower);
        return false;
    }
    return stepPair(decoded, context);
}

namespace
{
    std::atomic<VU1Interpreter::CompiledProgramFn> g_compiledProgram{nullptr};
}

void VU1Interpreter::registerCompiledProgram(CompiledProgramFn program)
{
    g_compiledProgram.store(program, std::memory_order_release);
}

uint64_t VU1Interpreter::hashMicrocode(const uint8_t *code, uint32_t size)
{
    uint64_t hash = 1469598103934665603ull; // FNV-1a
    for (uint32_t i = 0; i < size; ++i)
        hash = (hash ^ code[i]) * 1099511628211ull;
    return hash;
}

VU1Interpreter::CompiledProgramFn VU1Interpreter::compiledProgramFor(uint8_t *vuCode, uint32_t codeSize, PS2Memory *memory)
{
    if (m_unit != Unit::VU1 || !m_directRegisterWrites || memory == nullptr || vuCode != memory->getVU1Code() ||
        codeSize != PS2_VU1_CODE_SIZE)
        return nullptr;
    const uint64_t generation = memory->getVU1CodeGeneration();
    if (generation != m_compiledGeneration)
    {
        m_compiledGeneration = generation;
        // Mantener al día la caché de decodificación (y m_statusUnread) aunque se use el código compilado.
        (void)getDecodedInstructionPairForPc(vuCode, codeSize, memory, 0u);
        // GOW_VU1_CAPTURA=<carpeta>: guarda cada micromemoria distinta (entrada de generar_vu1). Son datos del
        // juego: no se publican.
        static const char *captureDir = std::getenv("GOW_VU1_CAPTURA");
        if (captureDir != nullptr)
        {
            char name[64];
            std::snprintf(name, sizeof(name), "/vu1_%016llx.bin", static_cast<unsigned long long>(hashMicrocode(vuCode, codeSize)));
            const std::string path = std::string(captureDir) + name;
            if (!std::filesystem::exists(path))
            {
                std::FILE *file = std::fopen(path.c_str(), "wb");
                if (file != nullptr)
                {
                    std::fwrite(vuCode, 1, codeSize, file);
                    std::fclose(file);
                }
            }
        }
    }
    return m_compiledEnabled ? g_compiledProgram.load(std::memory_order_acquire) : nullptr;
}

// GOW-Port: volver a leer las variables de entorno de VU1 (las pruebas cambian GOW_XGKICK_IMMEDIATE).
void ps2Vu1ReloadEnvironmentOptions()
{
    g_xgkickImmediate.store(-1, std::memory_order_relaxed);
}

#include "ps2_vu1_native.inl"
