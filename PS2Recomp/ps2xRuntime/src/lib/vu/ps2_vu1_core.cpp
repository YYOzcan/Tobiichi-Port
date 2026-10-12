#include "runtime/ps2_vu1.h"
#include "runtime/gs/ps2_gif_arbiter.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/ps2_memory.h"
#include "ps2_vu1_detail.h"
#include "ps2_vu1_step.inl"

#include <algorithm>
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

namespace
{
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
    m_xgkickCycle = 0u;
    m_xgkickEvent = ~0ull;
    m_vfReady = {};
    m_viReady = {};
    m_accReady = {};
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
    m_lastRunHitBudget = false; // GOW-Port
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
    // GOW-Port: un único store de 16 bytes (ver applyDestT en ps2_vu1_compiled.inl).
    vu1StoreLanes(dst, result, dest);
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

    // Fast-path: if all active lanes are strictly normal finite floats (not zero, not denorm, not inf/nan),
    // then underflow, overflow and zero cannot occur. Flags are just sign, and result is unmodified.
    // GOW-Port: también fuera el exponente 0xFE. Con redondeo hacia cero (fesetround en run(); en Linux también
    // cambia el MXCSR) un producto o suma que desborda da el máximo finito (0x7F7FFFFF), no Inf, y quedaba en
    // el camino rápido sin el flag O. Igual que el código compilado (exponente 1..0xFD); con un resultado
    // legítimo de exponente 0xFE el camino exacto deja el mismo valor y solo el signo.
    bool needExact = false;
    if (dest & 0x8u)
    {
        uint32_t bits = 0u;
        std::memcpy(&bits, &result[0], sizeof(bits));
        const uint32_t exp = (bits >> 23) & 0xFFu;
        if (__builtin_expect(exp != 0u && exp < 0xFEu, 1))
            laneFlags[0] = (bits & 0x80000000u) ? 0x2u : 0u;
        else
            needExact = true;
    }
    if (!needExact && (dest & 0x4u))
    {
        uint32_t bits = 0u;
        std::memcpy(&bits, &result[1], sizeof(bits));
        const uint32_t exp = (bits >> 23) & 0xFFu;
        if (__builtin_expect(exp != 0u && exp < 0xFEu, 1))
            laneFlags[1] = (bits & 0x80000000u) ? 0x2u : 0u;
        else
            needExact = true;
    }
    if (!needExact && (dest & 0x2u))
    {
        uint32_t bits = 0u;
        std::memcpy(&bits, &result[2], sizeof(bits));
        const uint32_t exp = (bits >> 23) & 0xFFu;
        if (__builtin_expect(exp != 0u && exp < 0xFEu, 1))
            laneFlags[2] = (bits & 0x80000000u) ? 0x2u : 0u;
        else
            needExact = true;
    }
    if (!needExact && (dest & 0x1u))
    {
        uint32_t bits = 0u;
        std::memcpy(&bits, &result[3], sizeof(bits));
        const uint32_t exp = (bits >> 23) & 0xFFu;
        if (__builtin_expect(exp != 0u && exp < 0xFEu, 1))
            laneFlags[3] = (bits & 0x80000000u) ? 0x2u : 0u;
        else
            needExact = true;
    }
    if (__builtin_expect(!needExact, 1))
        return;

    const uint8_t fs = FS(upper);
    const uint8_t ft = FT(upper);
    double vs[4];
    double vt[4];
    double acc[4];
    for (uint32_t component = 0; component < 4u; ++component)
    {
        vs[component] = static_cast<double>(normalizeOperand(m_state.vf[fs][component]));
        vt[component] = static_cast<double>(normalizeOperand(m_state.vf[ft][component]));
        acc[component] = static_cast<double>(normalizeOperand(m_state.acc[component]));
    }
    double scalar = 0.0;
    if (source == Source::Q)
        scalar = static_cast<double>(normalizeOperand(m_state.q));
    else if (source == Source::I)
        scalar = static_cast<double>(normalizeOperand(m_state.i));
    else if (source == Source::Broadcast)
        scalar = vt[code & 3u];

    static constexpr uint8_t crossLeft[4] = {1u, 2u, 0u, 3u};
    static constexpr uint8_t crossRight[4] = {2u, 0u, 1u, 3u};
    for (uint32_t component = 0; component < 4u; ++component)
    {
        laneFlags[component] = 0u;
        if ((dest & laneForComponent(component)) == 0u)
            continue;
        const double right = source == Source::Vector ? vt[component] : scalar;
        double exact = 0.0;
        switch (kind)
        {
        case Kind::Add: exact = vs[component] + right; break;
        case Kind::Sub: exact = vs[component] - right; break;
        case Kind::Madd: exact = acc[component] + vs[component] * right; break;
        case Kind::Msub: exact = acc[component] - vs[component] * right; break;
        case Kind::Mul: exact = vs[component] * right; break;
        case Kind::Opmsub:
            exact = component == 3u ? 0.0 : acc[component] - vs[crossLeft[component]] * vt[crossRight[component]];
            break;
        case Kind::Opmula:
            exact = component == 3u ? 0.0 : vs[crossLeft[component]] * vt[crossRight[component]];
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

    // GOW-Port: double, no long double. En MSVC long double es double (la plataforma con la que se
    // validó contra PCSX2); con GCC son 80 bits x87: más lento y con doble redondeo al pasar a double.
    // El producto de dos float es exacto en double.
    const auto operand = [this](float value)
    {
        return static_cast<double>(normalizeOperand(value));
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

    const double q = operand(m_state.q);
    const double i = operand(m_state.i);

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
    const double exact = static_cast<double>(exactResult);
    const bool negative = std::signbit(exact);
    const double magnitude = std::fabs(exact);
    constexpr double maximum = 3.4028234663852886e+38; // std::numeric_limits<float>::max()
    constexpr double minimum = 1.1754943508222875e-38; // std::numeric_limits<float>::min()
    uint8_t flags = negative ? 0x2u : 0u;

    uint32_t bits = negative ? 0x80000000u : 0u;
    if (__builtin_expect(magnitude == 0.0, 0))
    {
        flags |= 0x1u;
        std::memcpy(&value, &bits, sizeof(value));
    }
    else if (__builtin_expect(magnitude > maximum, 0))
    {
        flags |= 0x8u;
        bits |= 0x7F7FFFFFu;
        std::memcpy(&value, &bits, sizeof(value));
    }
    else if (__builtin_expect(magnitude < minimum, 0))
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
    if (dest & 0x8u)
    {
        const uint32_t flags = laneFlags[0];
        if (flags & 0x1u) mac |= 0x8u;
        if (flags & 0x2u) mac |= 0x80u;
        if (flags & 0x4u) mac |= 0x800u;
        if (flags & 0x8u) mac |= 0x8000u;
        status |= flags;
    }
    if (dest & 0x4u)
    {
        const uint32_t flags = laneFlags[1];
        if (flags & 0x1u) mac |= 0x4u;
        if (flags & 0x2u) mac |= 0x40u;
        if (flags & 0x4u) mac |= 0x400u;
        if (flags & 0x8u) mac |= 0x4000u;
        status |= flags;
    }
    if (dest & 0x2u)
    {
        const uint32_t flags = laneFlags[2];
        if (flags & 0x1u) mac |= 0x2u;
        if (flags & 0x2u) mac |= 0x20u;
        if (flags & 0x4u) mac |= 0x200u;
        if (flags & 0x8u) mac |= 0x2000u;
        status |= flags;
    }
    if (dest & 0x1u)
    {
        const uint32_t flags = laneFlags[3];
        if (flags & 0x1u) mac |= 0x1u;
        if (flags & 0x2u) mac |= 0x10u;
        if (flags & 0x4u) mac |= 0x100u;
        if (flags & 0x8u) mac |= 0x1000u;
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
            if (laneMask & 0x8u) m_vfLatestWrite[reg][0] = write.sequence;
            if (laneMask & 0x4u) m_vfLatestWrite[reg][1] = write.sequence;
            if (laneMask & 0x2u) m_vfLatestWrite[reg][2] = write.sequence;
            if (laneMask & 0x1u) m_vfLatestWrite[reg][3] = write.sequence;
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
            if (laneMask & 0x8u) m_accLatestWrite[0] = write.sequence;
            if (laneMask & 0x4u) m_accLatestWrite[1] = write.sequence;
            if (laneMask & 0x2u) m_accLatestWrite[2] = write.sequence;
            if (laneMask & 0x1u) m_accLatestWrite[3] = write.sequence;
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
    // GOW-Port: también con un FDIV pendiente (DIV/SQRT/RSQRT, uno por vértice en la perspectiva): antes iba
    // por el camino general, que recorre todas las colas y recalcula el siguiente ciclo. Mismo orden (flags y
    // después Q con D/I) y mismo siguiente ciclo que el camino general con las demás colas vacías.
    if ((m_storePending | m_vfPending | m_viPending | m_accPending) == 0u &&
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
        if (m_fdiv.valid && m_fdiv.readyCycle <= m_cycle)
        {
            m_state.q = m_fdiv.value;
            const uint32_t currentDi = m_fdiv.statusDi & 0x30u;
            m_state.status = (m_state.status & 0xFCFu) | currentDi | (currentDi << 6);
            m_fdiv.valid = false;
        }
        // los flags se confirman al leerlos (commitReadyFlags)
        m_nextCommitCycle = m_fdiv.valid ? m_fdiv.readyCycle : ~0ull;
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

    if (m_storePending != 0u && m_xgkick.active && m_cycle > m_xgkickCycle + 1u)
        xgkickAdvanceTo(m_cycle - 1u); // GOW-Port: PATH1 copia antes de los stores que se confirman ahora
    for (uint32_t pending = m_storePending; pending != 0u; pending &= pending - 1u)
    {
        const uint32_t index = static_cast<uint32_t>(std::countr_zero(pending));
        PendingStore &store = m_storePipeline[index];
        if (!store.valid || store.readyCycle > m_cycle)
            continue;
        m_storePending &= ~(1u << index);
        if (m_activeVuData && store.address + 16u <= m_activeVuDataSize)
        {
            if (__builtin_expect(store.laneMask == 0xFu, 1))
            {
                std::memcpy(m_activeVuData + store.address, store.words.data(), 16);
            }
            else
            {
                uint32_t *target = reinterpret_cast<uint32_t *>(m_activeVuData + store.address);
                const uint8_t mask = store.laneMask;
                if (mask & 0x8u) target[0] = store.words[0];
                if (mask & 0x4u) target[1] = store.words[1];
                if (mask & 0x2u) target[2] = store.words[2];
                if (mask & 0x1u) target[3] = store.words[3];
            }
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
        const uint8_t mask = write.laneMask;
        if (mask & 0x8u && m_vfLatestWrite[write.reg][0] == write.sequence)
            m_state.vf[write.reg][0] = write.value[0];
        if (mask & 0x4u && m_vfLatestWrite[write.reg][1] == write.sequence)
            m_state.vf[write.reg][1] = write.value[1];
        if (mask & 0x2u && m_vfLatestWrite[write.reg][2] == write.sequence)
            m_state.vf[write.reg][2] = write.value[2];
        if (mask & 0x1u && m_vfLatestWrite[write.reg][3] == write.sequence)
            m_state.vf[write.reg][3] = write.value[3];
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
        const uint8_t mask = write.laneMask;
        if (mask & 0x8u && m_accLatestWrite[0] == write.sequence)
            m_state.acc[0] = write.value[0];
        if (mask & 0x4u && m_accLatestWrite[1] == write.sequence)
            m_state.acc[1] = write.value[1];
        if (mask & 0x2u && m_accLatestWrite[2] == write.sequence)
            m_state.acc[2] = write.value[2];
        if (mask & 0x1u && m_accLatestWrite[3] == write.sequence)
            m_state.acc[3] = write.value[3];
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

// Un ciclo de PATH1 (como antes, en cada ciclo): suma un crédito y copia los qwords que alcancen.
void VU1Interpreter::progressXgkick()
{
    if (!m_xgkick.active || !m_activeVuData || m_activeVuDataSize == 0u)
        return;
    ++m_xgkick.cycleCredit;
    xgkickCopy();
}

// GOW-Port: cuenta los ciclos de PATH1 hasta 'cycle' de una vez. La copia solo depende del número de ciclos y de
// la memoria de datos, así que es igual que avanzar ciclo a ciclo siempre que se llame antes de que la VU escriba
// en su memoria, antes de mirar si hay un envío activo y en cada evento (GIFtag o final, que pueden fallar o
// enviar el paquete): en esos ciclos ocurre lo mismo que antes.
void VU1Interpreter::xgkickAdvanceTo(uint64_t cycle)
{
    if (!m_xgkick.active || !m_activeVuData || m_activeVuDataSize == 0u)
    {
        m_xgkickEvent = ~0ull;
        return;
    }
    if (cycle > m_xgkickCycle)
    {
        const uint64_t credit = m_xgkick.cycleCredit + (cycle - m_xgkickCycle);
        m_xgkick.cycleCredit = static_cast<uint32_t>(std::min<uint64_t>(credit, 0x40000000u));
        m_xgkickCycle = cycle;
        xgkickCopy();
    }
    xgkickScheduleEvent();
}

// Próximo ciclo en que PATH1 copia una GIFtag (currentTagEnd == 0) o el último qword de la etiqueta actual
// (después termina el paquete o la siguiente copia es una GIFtag). La copia j-ésima ocurre cuando el crédito
// llega a 2: ciclo m_xgkickCycle + 2 * (j - copiados + 1) - crédito.
void VU1Interpreter::xgkickScheduleEvent()
{
    if (!m_xgkick.active)
    {
        m_xgkickEvent = ~0ull;
        return;
    }
    const uint64_t copied = m_xgkick.copiedBytes / 16u;
    uint64_t target = m_xgkick.currentTagEnd == 0u ? copied : m_xgkick.currentTagEnd / 16u - 1u;
    if (target < copied)
        target = copied;
    m_xgkickEvent = m_xgkickCycle + 2u * (target - copied + 1u) - std::min<uint64_t>(m_xgkick.cycleCredit, 2u * (target - copied + 1u));
}

void VU1Interpreter::xgkickCopy()
{
    if (!m_xgkick.active || !m_activeVuData || m_activeVuDataSize == 0u)
        return;

    while (m_xgkick.active && m_xgkick.cycleCredit >= 2u)
    {
        // GOW-Port: dentro del cuerpo de una etiqueta cada qword solo se copia (la etiqueta siguiente o el
        // final llegan con el último): los que alcance el crédito se copian de una vez, en tramos contiguos.
        // currentTagEnd es múltiplo de 16 y no pasa de kBufferSize (comprobado al leer la GIFtag).
        if (m_xgkick.currentTagEnd != 0u && m_xgkick.currentTagEnd - m_xgkick.copiedBytes > 16u)
        {
            const uint32_t count = std::min<uint32_t>((m_xgkick.currentTagEnd - m_xgkick.copiedBytes) / 16u - 1u,
                                                      m_xgkick.cycleCredit / 2u);
            m_xgkick.cycleCredit -= 2u * count;
            uint32_t bytes = count * 16u;
            while (bytes != 0u)
            {
                const uint32_t position = m_xgkick.sourceAddress + m_xgkick.copiedBytes;
                const uint32_t first = (m_activeVuDataSize & (m_activeVuDataSize - 1u)) == 0u
                                           ? position & (m_activeVuDataSize - 1u)
                                           : position % m_activeVuDataSize;
                if (first + 16u > m_activeVuDataSize)
                    break; // qword que da la vuelta: lo copia el camino de abajo (sin crédito ya gastado)
                const uint32_t run = std::min<uint32_t>(bytes, (m_activeVuDataSize - first) & ~15u);
                std::memcpy(m_xgkick.packet.data() + m_xgkick.copiedBytes, m_activeVuData + first, run);
                m_xgkick.copiedBytes += run;
                bytes -= run;
            }
            m_xgkick.cycleCredit += 2u * (bytes / 16u); // devuelve el crédito de lo no copiado
            if (m_xgkick.cycleCredit < 2u)
                break;
        }
        m_xgkick.cycleCredit -= 2u;
        if (m_xgkick.copiedBytes > XgkickPipeline::kBufferSize - 16u)
        {
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

            uint64_t tagBytes = 16u;
            if (format == 0u)
                tagBytes += static_cast<uint64_t>(nloop) * nreg * 16u;
            else if (format == 1u)
                tagBytes += ((static_cast<uint64_t>(nloop) * nreg + 1u) & ~1ull) * 8u;
            else // GOW-Port: IMAGE (2) y FLG=3, que el GS trata igual que IMAGE (el frontend ya lo hace)
                tagBytes += static_cast<uint64_t>(nloop) * 16u;

            if (tagBytes > XgkickPipeline::kBufferSize - qwordOffset)
            {
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

void VU1Interpreter::finishXgkick()
{
    if (!m_xgkick.active)
        return;

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
    m_xgkickCycle = m_cycle; // GOW-Port: PATH1 por eventos
    // Opt-in packet snapshot, following Scotho/socom-unzipped's XGKICK workaround.
    // Capture before later VU instructions re-template the source buffer. Keep
    // the existing bounded parser and circular-memory handling in both modes.
    if (xgkickImmediate())
    {
        m_xgkick.cycleCredit = 0x40000000u;
        progressXgkick();
    }
    xgkickScheduleEvent();
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
        xgkickAdvanceTo(m_cycle); // GOW-Port: un ciclo, o los que falten tras código compilado
}

void VU1Interpreter::advanceTo(uint64_t targetCycle)
{
    if (m_cycle >= targetCycle)
        return;

    if (!m_xgkick.active)
    {
        while (m_cycle < targetCycle)
        {
            if (m_nextCommitCycle > targetCycle)
            {
                m_cycle = targetCycle;
                m_state.cycles = targetCycle;
                return;
            }
            if (m_nextCommitCycle > m_cycle)
            {
                m_cycle = m_nextCommitCycle;
                m_state.cycles = m_cycle;
            }
            else
            {
                ++m_cycle;
                m_state.cycles = m_cycle;
            }
            commitReadyPipelines();
        }
        return;
    }

    // GOW-Port (KIexster, vu1-advance-events): en una espera no se ejecuta nada; solo cuentan los ciclos en que
    // algo cambia: un resultado listo (m_nextCommitCycle) o un evento de PATH1 (GIFtag o fin del paquete). Se
    // salta de uno a otro con el mismo orden que ciclo a ciclo (primero el commit y después PATH1); entre eventos
    // PATH1 solo acumula crédito, que xgkickAdvanceTo cuenta de una vez.
    while (m_cycle < targetCycle)
    {
        uint64_t next = std::min(targetCycle, std::max(m_nextCommitCycle, m_cycle + 1u));
        if (m_xgkick.active)
            next = std::min(next, std::max(m_xgkickEvent, m_cycle + 1u));
        m_cycle = next;
        m_state.cycles = m_cycle;
        if (m_cycle >= m_nextCommitCycle)
            commitReadyPipelines();
        if (m_xgkick.active && m_cycle >= m_xgkickEvent)
            xgkickAdvanceTo(m_cycle);
    }
}

bool VU1Interpreter::pipelinesPending() const
{
    if (m_fdiv.valid || m_xgkick.active ||
        m_flagCount != 0u || m_storePending != 0u ||
        m_vfPending != 0u || m_viPending != 0u || m_accPending != 0u)
        return true;
    for (const ScalarPipelineEntry &entry : m_efu)
        if (entry.valid)
            return true;
    return false;
}

void VU1Interpreter::flushPipelines()
{
    xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 al día antes de vaciar
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
                m_xgkickCycle = m_cycle; // GOW-Port: el envío ha terminado en este ciclo
                m_xgkickEvent = ~0ull;
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
    // GOW-Port: decodificar los 2048 pares en cada cambio de microcódigo costaba ~1 % del hilo de VU1 aunque
    // el código compilado no use la caché. Ahora cada par se decodifica la primera vez que se pide.
    m_decodedValid.fill(0u);

    m_cachedVuCode = vuCode;
    m_cachedMemory = memory;
    m_cachedCodeSize = codeSize;
    m_cachedCodeGeneration = generation;
    m_decodedCodeCacheValid = true;
    // FSAND (0x16), FSEQ (0x14) y FSOR (0x17) son las únicas lecturas del estado en VU1.
    m_statusUnread = m_directRegisterWrites;
    // Mismas condiciones que con los pares decodificados: bit I = bit 31 de la palabra superior.
    const auto lowerOp = [vuCode](uint32_t i, bool &iBit)
    {
        uint32_t lower = 0u, upper = 0u;
        std::memcpy(&lower, vuCode + i * 8u, sizeof(lower));
        std::memcpy(&upper, vuCode + i * 8u + 4u, sizeof(upper));
        iBit = (upper & 0x80000000u) != 0u;
        return lower >> 25;
    };
    for (uint32_t i = 0; i < pairCount && m_statusUnread; ++i)
    {
        bool iBit = false;
        const uint32_t op = lowerOp(i, iBit);
        if (!iBit && (op == 0x14u || op == 0x16u || op == 0x17u))
            m_statusUnread = false;
    }
    m_statusQuiet = m_statusUnread;
    for (uint32_t i = 0; i < pairCount && m_statusQuiet; ++i)
    {
        bool iBit = false;
        const uint32_t op = lowerOp(i, iBit);
        if (!iBit && op == 0x15u) // FSSET
            m_statusQuiet = false;
    }
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
    uint64_t &valid = m_decodedValid[pairIndex / 64u];
    const uint64_t bit = 1ull << (pairIndex % 64u);
    if ((valid & bit) == 0u)
    {
        m_decodedCodeCache[pairIndex] = decodeInstructionPair(vuCode, pc);
        valid |= bit;
    }
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
    vu1StoreVf0(m_state.vf[0]);
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
    if (CompiledProgramFn program = compiledProgramFor(vuCode, codeSize, memory))
        program(*this, context);
    else
        while (stepInterpreted(context))
        {
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
    xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 al día tras la ejecución (si se cortó por presupuesto)
    commitReadyFlags(); // GOW-Port: el estado visible tras la ejecución
    m_state.cycles = m_cycle;
    if (useVuRounding && previousRoundingMode != -1)
        std::fesetround(previousRoundingMode);
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

// GOW-Port: ver VU1CompiledAccess::epoch (ps2_vu1_compiled.inl).
std::atomic<uint64_t> g_vu1CompiledEpoch{0};

void VU1Interpreter::registerCompiledProgram(CompiledProgramFn program)
{
    std::fprintf(stderr, "[vu1c] registerCompiledProgram: %p\n", (void*)program);
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
        g_vu1CompiledEpoch.fetch_add(1, std::memory_order_relaxed); // GOW-Port: resoluciones del despachador
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
    auto prog = m_compiledEnabled ? g_compiledProgram.load(std::memory_order_acquire) : nullptr;
    static bool logged = false;
    if (!logged)
    {
        logged = true;
        std::fprintf(stderr, "[vu1c] compiledProgramFor: active=%p (direct=%d enabled=%d)\n",
                     (void*)prog, (int)m_directRegisterWrites, (int)m_compiledEnabled);
    }
    return prog;
}

// GOW-Port: volver a leer las variables de entorno de VU1 (las pruebas cambian GOW_XGKICK_IMMEDIATE).
void ps2Vu1ReloadEnvironmentOptions()
{
    g_xgkickImmediate.store(-1, std::memory_order_relaxed);
}
