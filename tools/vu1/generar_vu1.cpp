// GOW-Port: genera C++ para el microcódigo de VU1 capturado con GOW_VU1_CAPTURA (micromemorias de 16 KB).
// Uso: generar_vu1 <carpeta de salida> <micromemoria.bin>...  (escribe programa0.cpp ... programa12.cpp)
//
// Cada par de instrucciones se escribe ya decodificado (como lo decodifica el intérprete) y se ejecuta con
// VU1Interpreter::stepPairT, que hace los mismos pasos que el intérprete; el despachador comprueba en cada
// par que las dos palabras de la micromemoria son las compiladas y, si no, interpreta ese par.
//
// Bloques: desde cada cabecera (destino de salto o par siguiente a un final de bloque) hasta el hueco de
// retardo del primer salto, el par siguiente a un bit E o un par con bit D/T. Un bloque solo se usa si sus
// palabras coinciden todas, no hay un salto pendiente y queda presupuesto de ciclos de sobra. Dentro de un
// bloque se conoce lo que viene después de cada par, así que se pueden omitir los flags MAC/estado de una
// FMAC que otra FMAC posterior del bloque reemplaza antes de que nadie los lea (análisis de vida).
//
// La micromemoria y el C++ generado salen de los datos del juego: no se publican.
#include "runtime/ps2_memory.h"
#include "runtime/ps2_vu1.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

struct VU1CompiledGenerator
{
    using Pair = VU1Interpreter::DecodedInstructionPair;
    // GOW-Port: constantes privadas del intérprete para los tiempos estáticos (esta estructura es friend).
    static constexpr auto kPipeFdiv = VU1Interpreter::PipelineFdiv;
    static constexpr auto kPipeEfu = VU1Interpreter::PipelineEfu;
    static constexpr auto kPipeXgkick = VU1Interpreter::PipelineXgkick;
    static constexpr uint32_t kAccLatency = VU1Interpreter::kAccForwardLatency;
    // GOW-Port: latencia máxima con la que cualquier instrucción deja listo un VF / VI (barrido del decodificador
    // con todos los códigos de operación). Un ciclo "listo" se fija como emisión + latencia y la emisión es
    // anterior a la entrada del bloque, así que ready <= E - 1 + L: una guarda con límite >= L - 1 no puede fallar.
    struct MaxLatency
    {
        uint32_t vf = 0, vi = 0, fdiv = 0;
    };
    static MaxLatency maxWriteLatency(const VU1Interpreter &vu)
    {
        MaxLatency m;
        const auto take = [&](const VU1Interpreter::InstructionUsage &u)
        {
            if (u.vfWrite.reg != 0u && u.vfWrite.lanes != 0u)
                m.vf = std::max<uint32_t>(m.vf, u.vfLatency != 0u ? u.vfLatency : u.latency);
            if ((u.viWrite & 0xFFFEu) != 0u)
                m.vi = std::max<uint32_t>(m.vi, u.viLatency != 0u ? u.viLatency : u.latency);
            if (u.pipeline == VU1Interpreter::PipelineFdiv && !u.waitQ)
                m.fdiv = std::max<uint32_t>(m.fdiv, u.latency);
        };
        // Registros 2/3 (no nulos) y DEST = xyzw; se barren el código de operación y los campos bajos.
        for (uint32_t op = 0; op < 128u; ++op)
            for (uint32_t low = 0; low < 2048u; ++low)
                take(vu.decodeLowerUsage((op << 25) | (0xFu << 21) | (2u << 16) | (3u << 11) | low));
        for (uint32_t low = 0; low < 2048u; ++low)
            take(vu.decodeUpperUsage((0xFu << 21) | (2u << 16) | (3u << 11) | low));
        return m;
    }
    using Usage = VU1Interpreter::InstructionUsage;

    static Pair decode(const VU1Interpreter &vu, const uint8_t *code, uint32_t pc)
    {
        return vu.decodeInstructionPair(code, pc);
    }

    static bool isBranch(const Pair &p)
    {
        return !p.iBit && p.lowerUsage.pipeline == VU1Interpreter::PipelineBranch;
    }

    static void usage(std::ostringstream &out, const char *name, const Usage &u)
    {
        const Usage d{};
        for (int i = 0; i < 2; ++i)
            if (u.vfRead[i].reg != 0 || u.vfRead[i].lanes != 0)
                out << " p." << name << ".vfRead[" << i << "] = {" << int(u.vfRead[i].reg) << ", " << int(u.vfRead[i].lanes) << "};";
        if (u.vfWrite.reg != 0 || u.vfWrite.lanes != 0)
            out << " p." << name << ".vfWrite = {" << int(u.vfWrite.reg) << ", " << int(u.vfWrite.lanes) << "};";
#define FIELD(f)          \
    if (u.f != d.f)       \
        out << " p." << name << "." #f " = " << int(u.f) << ";";
        FIELD(vfReadCount)
        FIELD(viRead)
        FIELD(viWrite)
        FIELD(accRead)
        FIELD(accWrite)
        FIELD(latency)
        FIELD(vfLatency)
        FIELD(viLatency)
        FIELD(waitQ)
        FIELD(waitP)
        FIELD(readsClip)
        FIELD(writesClip)
        FIELD(delaysNextBranchRead)
        FIELD(reserved)
#undef FIELD
        if (u.pipeline != d.pipeline)
            out << " p." << name << ".pipeline = static_cast<VU1CompiledAccess::Pipeline>(" << int(u.pipeline) << ");";
    }

    static std::string pairInitializer(const Pair &p)
    {
        std::ostringstream out;
        out << "[] { P p{}; p.lower = 0x" << std::hex << p.lower << "u; p.upper = 0x" << p.upper << "u;" << std::dec;
        usage(out, "lowerUsage", p.lowerUsage);
        usage(out, "upperUsage", p.upperUsage);
#define FLAG(f)   \
    if (p.f)      \
        out << " p." #f " = true;";
        FLAG(iBit)
        FLAG(eBit)
        FLAG(mBit)
        FLAG(dBit)
        FLAG(tBit)
        FLAG(upperNop)
#undef FLAG
        if (p.upperVfShadowReg)
            out << " p.upperVfShadowReg = " << int(p.upperVfShadowReg) << ";";
        if (p.suppressedLowerVf)
            out << " p.suppressedLowerVf = " << int(p.suppressedLowerVf) << ";";
        out << " return p; }()";
        return out.str();
    }
};

namespace
{
    using Pair = VU1CompiledGenerator::Pair;

    // FMAC que deja flags MAC/estado en la cola (las mismas que trata upperT con updateFmacFlags).
    bool writesFmacFlags(uint32_t upper)
    {
        const uint32_t op = upper & 0x3Fu;
        const uint32_t dest = (upper >> 21) & 0xFu;
        if (dest == 0u)
            return false;
        if (op < 0x3Cu)
        {
            if (op <= 0x0Fu || (op >= 0x18u && op <= 0x1Cu) || op == 0x1Eu || (op >= 0x20u && op <= 0x2Au) ||
                op == 0x2Cu || op == 0x2Du || op == 0x2Eu)
                return true;
            return false;
        }
        const uint32_t special = (upper & 3u) | ((upper >> 4) & 0x7Cu);
        return special <= 0x0Fu || (special >= 0x18u && special <= 0x1Cu) || special == 0x1Eu ||
               (special >= 0x20u && special <= 0x2Au) || special == 0x2Cu || special == 0x2Du || special == 0x2Eu;
    }

    // FMAND (0x1A), FMEQ (0x18) y FMOR (0x1B) leen el registro MAC.
    bool readsMac(const Pair &p)
    {
        if (p.iBit)
            return false;
        const uint32_t op = p.lower >> 25;
        return op == 0x18u || op == 0x1Au || op == 0x1Bu;
    }

    struct Code
    {
        std::vector<uint8_t> bytes;
        std::vector<Pair> pairs;
        std::vector<bool> valid;
        uint32_t lower(uint32_t pc) const { uint32_t w; std::memcpy(&w, bytes.data() + pc, 4); return w; }
        uint32_t upper(uint32_t pc) const { uint32_t w; std::memcpy(&w, bytes.data() + pc + 4, 4); return w; }
    };

    std::string hex4(uint32_t v)
    {
        char b[16];
        std::snprintf(b, sizeof(b), "%04X", v);
        return b;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Uso: generar_vu1 <carpeta de salida> <micromemoria.bin>...\n";
        return 2;
    }
    VU1Interpreter vu;
    const VU1CompiledGenerator::MaxLatency maxLat = VU1CompiledGenerator::maxWriteLatency(vu);
    std::printf("[generar_vu1] latencia maxima de escritura: VF %u, VI %u, FDIV %u\n", maxLat.vf, maxLat.vi, maxLat.fdiv);
    std::vector<Code> codes;
    for (int a = 2; a < argc; ++a)
    {
        std::ifstream file(argv[a], std::ios::binary);
        Code code;
        code.bytes.assign((std::istreambuf_iterator<char>(file)), {});
        if (code.bytes.size() != PS2_VU1_CODE_SIZE)
        {
            std::cerr << argv[a] << ": la micromemoria de VU1 debe tener 16384 bytes\n";
            return 1;
        }
        const uint32_t count = static_cast<uint32_t>(code.bytes.size() / 8u);
        code.pairs.resize(count);
        code.valid.resize(count);
        for (uint32_t i = 0; i < count; ++i)
        {
            const uint32_t pc = i * 8u;
            code.pairs[i] = VU1CompiledGenerator::decode(vu, code.bytes.data(), pc);
            code.valid[i] = !(code.lower(pc) == 0u && code.upper(pc) == 0u) &&
                            !code.pairs[i].upperUsage.reserved && !code.pairs[i].lowerUsage.reserved;
        }
        codes.push_back(std::move(code));
    }

    // Funciones por par: (pc, palabras, flags muertos) -> nombre.
    std::map<std::tuple<uint32_t, uint32_t, uint32_t, bool>, std::string> pairFns;
    std::map<uint32_t, uint32_t> variantCount;
    constexpr size_t kParts = 12;
    std::vector<std::ostringstream> parts(kParts);
    std::ostringstream declarations;
    // Par decodificado (pc, palabras) -> nombre del struct K; cada archivo define los que usa.
    std::map<std::tuple<uint32_t, uint32_t, uint32_t>, std::string> kNames;
    std::vector<std::set<std::string>> kInPart(kParts);
    const auto kStruct = [&](const Code &code, uint32_t pc, size_t part) -> std::string
    {
        const auto key = std::make_tuple(pc, code.lower(pc), code.upper(pc));
        auto it = kNames.find(key);
        if (it == kNames.end())
            it = kNames.emplace(key, "K" + hex4(pc) + "_" + std::to_string(variantCount[pc]++)).first;
        if (kInPart[part].insert(it->second).second)
            parts[part] << "    struct " << it->second << "\n    {\n        static constexpr P value = "
                        << VU1CompiledGenerator::pairInitializer(code.pairs[pc / 8u]) << ";\n    };\n";
        return it->second;
    };
    const auto pairFunction = [&](const Code &code, uint32_t pc, bool dead) -> std::string
    {
        const auto key = std::make_tuple(pc, code.lower(pc), code.upper(pc), dead);
        if (const auto it = pairFns.find(key); it != pairFns.end())
            return it->second;
        const size_t part = pairFns.size() % kParts;
        const std::string k = kStruct(code, pc, part);
        const std::string name = "p" + k.substr(1) + (dead ? "d" : "");
        parts[part] << "    VU1C_FAST bool " << name << "(VU1Interpreter &vu, C &c)\n    {\n"
                    << "        return VU1CompiledAccess::step<" << k << ", " << (dead ? "true" : "false") << ">(vu, c);\n    }\n";
        declarations << "    bool " << name << "(VU1Interpreter &vu, C &c);\n";
        pairFns[key] = name;
        return name;
    };

    // Despacho par a par (sin flags muertos) para todas las palabras vistas.
    std::map<uint32_t, std::vector<std::tuple<uint32_t, uint32_t, std::string>>> pairCases;
    std::set<std::tuple<uint32_t, uint32_t, uint32_t>> seenPairs;
    for (const Code &code : codes)
        for (uint32_t pc = 0; pc + 8u <= code.bytes.size(); pc += 8u)
        {
            if (!code.valid[pc / 8u] || !seenPairs.insert({pc, code.lower(pc), code.upper(pc)}).second)
                continue;
            const std::string name = pairFunction(code, pc, false);
            pairCases[pc].emplace_back(code.lower(pc), code.upper(pc), name);
        }

    // Bloques.
    std::map<uint32_t, std::vector<std::pair<std::string, std::vector<uint32_t>>>> blockCases;
    std::set<std::pair<uint32_t, std::vector<uint32_t>>> seenBlocks;
    size_t blockCount = 0, deadCount = 0, fmacCount = 0, staticBlocks = 0;
    for (const Code &code : codes)
    {
        const uint32_t count = static_cast<uint32_t>(code.bytes.size() / 8u);
        std::set<uint32_t> heads;
        for (uint32_t i = 0; i < count; ++i)
        {
            if (!code.valid[i])
                continue;
            const Pair &p = code.pairs[i];
            const uint32_t pc = i * 8u;
            if (i == 0u || !code.valid[i - 1u])
                heads.insert(pc);
            if (VU1CompiledGenerator::isBranch(p))
            {
                const uint32_t op = p.lower >> 25;
                if (op != 0x24u && op != 0x25u) // JR/JALR: destino en un registro
                {
                    const int32_t imm = static_cast<int32_t>(p.lower << 21) >> 21;
                    heads.insert(static_cast<uint32_t>(static_cast<int32_t>(pc) + 8 + imm * 8) & 0x3FFFu);
                }
                heads.insert((pc + 16u) & 0x3FFFu); // tras el hueco de retardo
            }
            if (p.eBit)
                heads.insert((pc + 16u) & 0x3FFFu);
            if (p.dBit || p.tBit)
                heads.insert((pc + 8u) & 0x3FFFu);
        }
        for (const uint32_t head : heads)
        {
            if (head + 8u > code.bytes.size() || !code.valid[head / 8u])
                continue;
            std::vector<uint32_t> pcs;
            for (uint32_t pc = head; pc + 8u <= code.bytes.size() && pcs.size() < 64u; pc += 8u)
            {
                if (!code.valid[pc / 8u])
                    break;
                pcs.push_back(pc);
                const Pair &p = code.pairs[pc / 8u];
                if (p.dBit || p.tBit)
                    break;
                if (VU1CompiledGenerator::isBranch(p) || p.eBit)
                {
                    if (pc + 16u <= code.bytes.size() && code.valid[pc / 8u + 1u])
                        pcs.push_back(pc + 8u);
                    break;
                }
                // Un salto en el par anterior (si se entra a mitad) lo cubre la comprobación de salto pendiente.
            }
            if (pcs.size() < 2u)
                continue;
            std::vector<uint32_t> words;
            for (const uint32_t pc : pcs)
            {
                words.push_back(code.lower(pc));
                words.push_back(code.upper(pc));
            }
            if (!seenBlocks.insert({head, words}).second)
                continue;

            // Vida de los flags de cada FMAC del bloque.
            const size_t length = pcs.size();
            std::vector<bool> dead(length, false);
            for (size_t i = 0; i < length; ++i)
            {
                if (!writesFmacFlags(code.upper(pcs[i])))
                    continue;
                ++fmacCount;
                for (size_t j = i + 1u; j + 4u <= length; ++j)
                {
                    if (readsMac(code.pairs[pcs[j] / 8u]))
                        break; // un lector antes de la siguiente FMAC: vivos
                    if (!writesFmacFlags(code.upper(pcs[j])))
                        continue;
                    bool readerSoon = false;
                    for (size_t r = j + 1u; r <= j + 3u && r < length; ++r)
                        readerSoon = readerSoon || readsMac(code.pairs[pcs[r] / 8u]);
                    if (!readerSoon)
                        dead[i] = true;
                    break;
                }
                deadCount += dead[i] ? 1u : 0u;
            }

            // El bloque es una sola función con los pasos en línea, en el mismo archivo que sus structs K.
            // Los pares intermedios que no saltan ni terminan ("simples") no comprueban saltos ni finales.
            const std::string name = "b" + hex4(head) + "_" + std::to_string(blockCases[head].size());
            const size_t part = blockCount % kParts;
            std::ostringstream body;
            // GOW-Port: etapa 1 del recompilador: tiempos estáticos (VU1CompiledAccess::stepS). Se calcula el ciclo
            // de emisión de cada par relativo a la entrada con las reglas de readyCycleT (latencias de VF/VI/ACC y
            // FDIV escritas en el bloque). Lo que el bloque lee de fuera se comprueba al entrar (guardas): si algo
            // aún no está listo cuando se leería, o el bloque usa EFU/XGKICK, se usa la versión dinámica (_d).
            struct Schedule
            {
                bool ok = true;
                std::vector<uint32_t> issue;
                std::vector<bool> stall;
                uint32_t total = 0;
                std::vector<std::array<uint32_t, 5>> writes; // par, tipo, registro, componente, desplazamiento
                std::map<std::array<uint32_t, 3>, uint32_t> guards; // (tipo, registro, componente) -> límite
            } sched;
            {
                int64_t vfRel[32][4];
                int64_t viRel[16];
                int64_t accRel[4];
                for (auto &r : vfRel)
                    for (auto &v : r)
                        v = -1;
                for (auto &v : viRel)
                    v = -1;
                for (auto &v : accRel)
                    v = -1;
                int64_t fdivRel = -1;
                uint32_t t = 0;
                for (size_t i = 0; i < length && sched.ok; ++i)
                {
                    const Pair &p = code.pairs[pcs[i] / 8u];
                    const auto pipe = p.lowerUsage.pipeline;
                    if (!p.iBit && (pipe == VU1CompiledGenerator::kPipeEfu || pipe == VU1CompiledGenerator::kPipeXgkick || p.lowerUsage.waitP))
                    {
                        sched.ok = false;
                        break;
                    }
                    int64_t r = t;
                    std::vector<std::array<uint32_t, 3>> liveIn;
                    const auto readVf = [&](uint32_t reg, uint32_t lanes)
                    {
                        for (uint32_t lane = 0; lane < 4u; ++lane)
                            if ((lanes & (8u >> lane)) != 0u)
                            {
                                if (vfRel[reg][lane] >= 0)
                                    r = std::max(r, vfRel[reg][lane]);
                                else
                                    liveIn.push_back({0u, reg, lane});
                            }
                    };
                    for (const auto *u : {&p.upperUsage, &p.lowerUsage})
                    {
                        for (uint32_t j = 0; j < u->vfReadCount; ++j)
                            readVf(u->vfRead[j].reg, u->vfRead[j].lanes);
                        for (uint32_t reg = 1u; reg < 16u; ++reg)
                            if ((u->viRead & (1u << reg)) != 0u)
                            {
                                if (viRel[reg] >= 0)
                                    r = std::max(r, viRel[reg]);
                                else
                                    liveIn.push_back({1u, reg, 0u});
                            }
                        for (uint32_t lane = 0; lane < 4u; ++lane)
                            if ((u->accRead & (8u >> lane)) != 0u)
                            {
                                if (accRel[lane] >= 0)
                                    r = std::max(r, accRel[lane]);
                                else
                                    liveIn.push_back({2u, 0u, lane});
                            }
                    }
                    if (pipe == VU1CompiledGenerator::kPipeFdiv || p.lowerUsage.waitQ)
                    {
                        if (fdivRel >= 0)
                            r = std::max(r, fdivRel);
                        else
                            liveIn.push_back({3u, 0u, 0u});
                    }
                    const uint32_t issue = static_cast<uint32_t>(r);
                    sched.issue.push_back(issue);
                    sched.stall.push_back(issue > t);
                    for (const auto &g : liveIn)
                        if (!sched.guards.count(g))
                            sched.guards[g] = issue; // la primera lectura es la más estricta
                    const auto writeVf = [&](uint32_t reg, uint32_t lanes, uint32_t latency)
                    {
                        for (uint32_t lane = 0; lane < 4u; ++lane)
                            if ((lanes & (8u >> lane)) != 0u)
                            {
                                vfRel[reg][lane] = issue + latency;
                                sched.writes.push_back({static_cast<uint32_t>(i), 0u, reg, lane, issue + latency});
                            }
                    };
                    const auto &lw = p.lowerUsage.vfWrite;
                    if (lw.reg != 0u && p.suppressedLowerVf != lw.reg)
                        writeVf(lw.reg, lw.lanes, p.lowerUsage.vfLatency != 0u ? p.lowerUsage.vfLatency : p.lowerUsage.latency);
                    const auto &uw = p.upperUsage.vfWrite;
                    if (uw.reg != 0u)
                        writeVf(uw.reg, uw.lanes, p.upperUsage.vfLatency != 0u ? p.upperUsage.vfLatency : p.upperUsage.latency);
                    for (uint32_t reg = 1u; reg < 16u; ++reg)
                        if ((p.lowerUsage.viWrite & (1u << reg)) != 0u)
                        {
                            const uint32_t latency = p.lowerUsage.viLatency != 0u ? p.lowerUsage.viLatency : p.lowerUsage.latency;
                            viRel[reg] = issue + latency;
                            sched.writes.push_back({static_cast<uint32_t>(i), 1u, reg, 0u, issue + latency});
                        }
                    for (uint32_t lane = 0; lane < 4u; ++lane)
                        if ((p.upperUsage.accWrite & (8u >> lane)) != 0u)
                        {
                            accRel[lane] = issue + VU1CompiledGenerator::kAccLatency;
                            sched.writes.push_back({static_cast<uint32_t>(i), 2u, 0u, lane, issue + VU1CompiledGenerator::kAccLatency});
                        }
                    if (!p.iBit && pipe == VU1CompiledGenerator::kPipeFdiv && !p.lowerUsage.waitQ)
                        fdivRel = issue + p.lowerUsage.latency;
                    t = issue + 1u;
                }
                sched.total = t;
            }
            if (sched.ok)
                ++staticBlocks;

            // Versión dinámica (la de siempre): única si no hay tiempos estáticos; si los hay, respaldo frío.
            const std::string dynName = sched.ok ? name + "_d" : name;
            // Las palabras las compara el despachador una vez por versión de la micromemoria (ver run()).
            body << (sched.ok ? "    [[gnu::noinline, gnu::cold]] int " : "    VU1C_FAST int ") << dynName << "(VU1Interpreter &vu, C &c)\n    {\n"
                 << "        if (!VU1CompiledAccess::blockReady(vu, c, " << head << "u, " << words.size() * 4u << "u))\n            return 0;\n"
                 << "        g_blockPairs += " << length << "u;\n";
            for (size_t i = 0; i < length; ++i)
            {
                const Pair &p = code.pairs[pcs[i] / 8u];
                const bool plain = i + 1u < length && !VU1CompiledGenerator::isBranch(p) && !p.eBit && !p.dBit && !p.tBit;
                const std::string k = kStruct(code, pcs[i], part);
                // GOW-Port: los pares que no abren el bloque se saltan las comprobaciones de entrada (Chained).
                body << "        if (!VU1CompiledAccess::step<" << k << ", " << (dead[i] ? "true" : "false") << ", "
                     << (plain ? "true" : "false") << ", " << (i > 0u ? "true" : "false") << ">(vu, c))\n            return 2;\n";
                if (i + 1u < length && !plain)
                    body << "        if (VU1CompiledAccess::pc(vu) != " << pcs[i + 1u] << "u)\n            return 1;\n";
            }
            body << "        return 1;\n    }\n";
            if (sched.ok)
            {
                const std::string table = "T" + name.substr(1);
                body << "    struct " << table << "\n    {\n        static constexpr uint32_t N = " << sched.writes.size() << ";\n"
                     << "        static constexpr uint32_t e[" << std::max<size_t>(sched.writes.size(), 1u) << "][5] = {";
                for (size_t w = 0; w < sched.writes.size(); ++w)
                {
                    const auto &e = sched.writes[w];
                    body << (w ? ", " : "") << "{" << e[0] << ", " << e[1] << ", " << e[2] << ", " << e[3] << ", " << e[4] << "}";
                }
                if (sched.writes.empty())
                    body << "{0, 0, 0, 0, 0}";
                body << "};\n    };\n";
                // Lo que lee el primer par y aún no está listo lo esperaría el propio par (la espera de readyCycleT
                // ocurre antes de ejecutarlo): el bloque empieza en S = el máximo de esos ciclos, con advanceTo como
                // la espera dinámica. El resto de guardas se comprueba contra S.
                body << "    VU1C_FAST int " << name << "(VU1Interpreter &vu, C &c)\n    {\n"
                     << "        if (!VU1CompiledAccess::blockReady(vu, c, " << head << "u, " << words.size() * 4u << "u))\n            return 0;\n";
                body << "        uint64_t E = VU1CompiledAccess::cycle(vu);\n"
                     << "        const uint64_t E0 = E;\n";
                const auto guardNeeded = [&](const std::array<uint32_t, 3> &g, uint32_t limit)
                {
                    if (g[0] == 0u && g[1] == 0u)
                        return false; // VF0: nunca se marca un "listo"
                    const uint32_t L = g[0] == 0u ? maxLat.vf : g[0] == 1u ? maxLat.vi : g[0] == 2u ? VU1CompiledGenerator::kAccLatency : maxLat.fdiv;
                    return limit + 1u < L;
                };
                for (const auto &[g, limit] : sched.guards)
                {
                    if (limit != 0u || !guardNeeded(g, limit))
                        continue;
                    if (g[0] == 0u)
                        body << "        E = std::max(E, VU1CompiledAccess::vfReadyAt(vu, " << g[1] << "u, " << g[2] << "u));\n";
                    else if (g[0] == 1u)
                        body << "        E = std::max(E, VU1CompiledAccess::viReadyAt(vu, " << g[1] << "u));\n";
                    else if (g[0] == 2u)
                        body << "        E = std::max(E, VU1CompiledAccess::accReadyAt(vu, " << g[2] << "u));\n";
                    else
                        body << "        E = std::max(E, VU1CompiledAccess::fdivReadyCycle(vu));\n";
                }
                body << "        if (E + " << sched.total << "u + 64u >= c.budgetEnd";
                for (const auto &[g, limit] : sched.guards)
                {
                    if (limit == 0u || !guardNeeded(g, limit))
                        continue;
                    if (g[0] == 0u)
                    {
                        // Los cuatro componentes con el mismo límite: una comparación (en el componente 0).
                        const auto lim = [&](uint32_t l) { const auto it = sched.guards.find({0u, g[1], l}); return it == sched.guards.end() ? -1 : static_cast<int64_t>(it->second); };
                        if (lim(0) == limit && lim(1) == limit && lim(2) == limit && lim(3) == limit)
                        {
                            if (g[2] == 0u)
                                body << "\n            || VU1CompiledAccess::vfReady4After(vu, " << g[1] << "u, E + " << limit << "u)";
                            continue;
                        }
                    }
                    if (g[0] == 0u)
                        body << "\n            || VU1CompiledAccess::vfReadyAt(vu, " << g[1] << "u, " << g[2] << "u) > E + " << limit << "u";
                    else if (g[0] == 1u)
                        body << "\n            || VU1CompiledAccess::viReadyAt(vu, " << g[1] << "u) > E + " << limit << "u";
                    else if (g[0] == 2u)
                        body << "\n            || VU1CompiledAccess::accReadyAt(vu, " << g[2] << "u) > E + " << limit << "u";
                    else
                        body << "\n            || !VU1CompiledAccess::fdivReadyBy(vu, E + " << limit << "u)";
                }
                body << ") [[unlikely]]\n            return " << dynName << "(vu, c);\n"
                     << "        g_blockPairs += " << length << "u;\n"
                     << "        if (E != E0)\n            VU1CompiledAccess::stallTo(vu, c, E);\n";
                for (size_t i = 0; i < length; ++i)
                {
                    const Pair &p = code.pairs[pcs[i] / 8u];
                    const bool plain = i + 1u < length && !VU1CompiledGenerator::isBranch(p) && !p.eBit && !p.dBit && !p.tBit;
                    const std::string k = kStruct(code, pcs[i], part);
                    // GOW-Port: la copia de VI para saltos solo la puede haber dejado activa el par anterior del bloque
                    // (o un par de fuera, antes del primero): si no, no hace falta borrarla (idea de KIexster).
                    bool clearBackup = i == 0u;
                    if (i > 0u)
                    {
                        const Pair &prev = code.pairs[pcs[i - 1u] / 8u];
                        clearBackup = (prev.lowerUsage.viWrite & 0xFFFEu) != 0u && prev.lowerUsage.delaysNextBranchRead; // como stepS
                    }
                    body << "        if (const int r = VU1CompiledAccess::stepS<" << k << ", " << (dead[i] ? "true" : "false") << ", "
                         << (plain ? "true" : "false") << ", " << (i > 0u ? "true" : "false") << ", " << sched.issue[i] << "u, "
                         << (sched.stall[i] ? "true" : "false") << ", " << pcs[i] << "u, " << (clearBackup ? "true" : "false")
                         << ">(vu, c, E))\n"
                         << "        {\n            VU1CompiledAccess::flushS<" << table << ">(vu, E, r == 1 ? " << i << "u : " << i + 1u
                         << "u);\n            return 2;\n        }\n";
                    if (i + 1u < length && !plain)
                        body << "        if (VU1CompiledAccess::pc(vu) != " << pcs[i + 1u] << "u)\n        {\n            VU1CompiledAccess::flushS<"
                             << table << ">(vu, E, " << i + 1u << "u);\n            return 1;\n        }\n";
                }
                // Salida normal: solo el último valor de cada hueco, en línea.
                std::map<std::array<uint32_t, 3>, uint32_t> last;
                for (const auto &e : sched.writes)
                    last[{e[1], e[2], e[3]}] = e[4];
                for (const auto &[slot, off] : last)
                {
                    if (slot[0] == 0u)
                    {
                        // Los cuatro componentes con el mismo valor: un solo store (se emite en el componente 0).
                        const auto lane = [&](uint32_t l) { const auto it = last.find({0u, slot[1], l}); return it == last.end() ? -1 : static_cast<int64_t>(it->second); };
                        if (lane(0) == off && lane(1) == off && lane(2) == off && lane(3) == off)
                        {
                            if (slot[2] == 0u)
                                body << "        VU1CompiledAccess::setVfReady4(vu, " << slot[1] << "u, E + " << off << "u);\n";
                            continue;
                        }
                    }
                    if (slot[0] == 0u)
                        body << "        VU1CompiledAccess::setVfReadyAt(vu, " << slot[1] << "u, " << slot[2] << "u, E + " << off << "u);\n";
                    else if (slot[0] == 1u)
                        body << "        VU1CompiledAccess::setViReadyAt(vu, " << slot[1] << "u, E + " << off << "u);\n";
                    else
                        body << "        VU1CompiledAccess::setAccReadyAt(vu, " << slot[2] << "u, E + " << off << "u);\n";
                }
                body << "        VU1CompiledAccess::syncCycles(vu);\n        return 1;\n    }\n";
            }
            parts[part] << body.str();
            declarations << "    int " << name << "(VU1Interpreter &vu, C &c);\n";
            blockCases[head].emplace_back(name, words);
            ++blockCount;
        }
    }

    const std::string header =
        "// Generado por tools/vu1/generar_vu1.cpp a partir del microcódigo del juego. No publicar.\n"
        "#include \"runtime/ps2_vu1.h\"\n#include \"ps2_vu1_compiled.inl\"\n#include <cstdio>\n#include <cstdlib>\n#include <array>\n#include <cstring>\n#include <iterator>\n\n"
        "// Mismo modo de coma flotante que el intérprete de VU (MSVC no expande en línea entre modos distintos).\n"
        "#if defined(_MSC_VER)\n#pragma float_control(precise, on, push)\n#pragma fp_contract(off)\n#endif\n\n"
        "using P = VU1CompiledAccess::P;\nusing C = VU1CompiledAccess::C;\n\n"
        "namespace vu1c_gen\n{\n    inline unsigned long long g_blockPairs = 0;\n}\n\n"
        "// Sin comprobaciones de desbordamiento de pila (/GS): los arreglos locales son de tamaño fijo.\n"
        "#if defined(_MSC_VER)\n#define VU1C_FAST __declspec(safebuffers)\n#else\n#define VU1C_FAST\n#endif\n\n";
    const std::string footer = "\n#if defined(_MSC_VER)\n#pragma float_control(pop)\n#endif\n";
    const std::string base = argv[1];
    // Solo se reescribe un archivo si cambia: así la compilación (Ninja con restat) no recompila el código
    // generado cada vez que se reenlaza el generador.
    const auto writeIfChanged = [](const std::string &path, const std::string &text)
    {
        std::ifstream in(path, std::ios::binary);
        const std::string old((std::istreambuf_iterator<char>(in)), {});
        const bool existed = in.is_open();
        in.close();
        if (!existed || old != text)
            std::ofstream(path, std::ios::binary) << text;
    };
    for (size_t k = 0; k < kParts; ++k)
        writeIfChanged(base + "/programa" + std::to_string(k + 1u) + ".cpp",
                       header + "namespace vu1c_gen\n{\n" + parts[k].str() + "}\n" + footer);

    std::ostringstream out;
    out << header
        << "namespace\n{\n"
        << "    // GOW_VU1C_DIAG: pares compilados e interpretados al salir. GOW_VU1C_RANGO=inicio-fin (hex): solo usa el\n"
        << "    // código compilado en ese rango de direcciones (para acotar una diferencia con el intérprete).\n"
        << "    // GOW_VU1C_SIN_BLOQUES: sin bloques (solo pares sueltos).\n"
        << "    struct Stats\n    {\n        unsigned long long compiled = 0, interpreted = 0;\n"
        << "        ~Stats()\n        {\n            if (std::getenv(\"GOW_VU1C_DIAG\"))\n"
        << "                std::fprintf(stderr, \"[vu1c] compilados=%llu interpretados=%llu\\n\", compiled + vu1c_gen::g_blockPairs, interpreted);\n        }\n    } g_stats;\n"
        << "    struct Range\n    {\n        uint32_t lo = 0, hi = 0xFFFFFFFFu;\n        bool blocks = true;\n        Range()\n        {\n"
        << "            if (const char *v = std::getenv(\"GOW_VU1C_RANGO\"))\n            {\n"
        << "                char *end = nullptr;\n                lo = static_cast<uint32_t>(std::strtoul(v, &end, 16));\n"
        << "                hi = end && *end == '-' ? static_cast<uint32_t>(std::strtoul(end + 1, nullptr, 16)) : lo;\n            }\n"
        << "            blocks = std::getenv(\"GOW_VU1C_SIN_BLOQUES\") == nullptr;\n        }\n    } g_range;\n"
        << "    inline bool inRange(uint32_t pc) { return pc >= g_range.lo && pc <= g_range.hi; }\n}\n\n"
        << "namespace vu1c_gen\n{\n" << declarations.str() << "}\n\n";

    // Candidatos por dirección, en el orden de antes: bloques (con sus palabras) y luego pares.
    std::set<uint32_t> allPcs;
    for (const auto &[pc, v] : pairCases)
        allPcs.insert(pc);
    for (const auto &[pc, v] : blockCases)
        allPcs.insert(pc);
    out << "namespace\n{\n"
        << "    using BlockFn = int (*)(VU1Interpreter &, C &);\n    using PairFn = bool (*)(VU1Interpreter &, C &);\n"
        << "    struct BlockCand { BlockFn fn; const uint32_t *words; uint32_t bytes; };\n"
        << "    struct PairCand { uint32_t lower, upper; PairFn fn; };\n"
        << "    struct PcCands { const BlockCand *blocks; uint32_t blockCount; const PairCand *pairs; uint32_t pairCount; };\n";
    for (const uint32_t pc : allPcs)
    {
        if (const auto it = blockCases.find(pc); it != blockCases.end())
        {
            for (size_t b = 0; b < it->second.size(); ++b)
            {
                out << "    constexpr uint32_t w" << it->second[b].first << "[] = {";
                const auto &w = it->second[b].second;
                for (size_t i = 0; i < w.size(); ++i)
                    out << (i ? ", " : "") << "0x" << std::hex << w[i] << "u" << std::dec;
                out << "};\n";
            }
            out << "    constexpr BlockCand blocks" << hex4(pc) << "[] = {";
            for (const auto &[name, w] : it->second)
                out << "{&vu1c_gen::" << name << ", w" << name << ", " << w.size() * 4u << "u}, ";
            out << "};\n";
        }
        if (const auto it = pairCases.find(pc); it != pairCases.end())
        {
            out << "    constexpr PairCand pairs" << hex4(pc) << "[] = {";
            for (const auto &[lower, upper, name] : it->second)
                out << "{0x" << std::hex << lower << "u, 0x" << upper << "u, " << std::dec << "&vu1c_gen::" << name << "}, ";
            out << "};\n";
        }
    }
    out << "    PcCands makeCands(uint32_t pc)\n    {\n        switch (pc)\n        {\n";
    for (const uint32_t pc : allPcs)
    {
        const bool b = blockCases.count(pc) != 0u, q = pairCases.count(pc) != 0u;
        out << "        case 0x" << hex4(pc) << ": return {" << (b ? "blocks" + hex4(pc) : std::string("nullptr")) << ", "
            << (b ? "std::size(blocks" + hex4(pc) + ")" : std::string("0")) << ", "
            << (q ? "pairs" + hex4(pc) : std::string("nullptr")) << ", "
            << (q ? "std::size(pairs" + hex4(pc) + ")" : std::string("0")) << "};\n";
    }
    out << "        default: return {nullptr, 0u, nullptr, 0u};\n        }\n    }\n"
        // Resolución por versión de la micromemoria (VU1CompiledAccess::epoch): qué bloques tienen las mismas
        // palabras que la micromemoria y qué par coincide. Antes se comparaban en cada entrada (memcmp de cada
        // candidato); con cientos de micromemorias capturadas eso pesaba en los bucles calientes.
        << "    constexpr uint32_t kMaxMatches = 4u;\n"
        // GOW-Port: entrada compacta (32 bytes, dos por línea de caché) con el primer bloque y el par a mano;
        // los demás bloques que coinciden (raro) van aparte.
        << "    struct Resolved\n    {\n        uint64_t epoch = ~0ull;\n        BlockFn first = nullptr;\n        PairFn pair = nullptr;\n"
        << "        uint16_t blockCount = 0;\n"
        << "        bool scan = false; // más de kMaxMatches bloques coinciden: comparar como antes\n    };\n"
        << "    static_assert(sizeof(Resolved) == 32u);\n"
        << "    Resolved g_resolved[16384u / 8u]; // micromemoria de VU1: 16 KB, un par cada 8 bytes\n"
        << "    BlockFn g_resolvedMore[16384u / 8u][kMaxMatches - 1u];\n"
        << "    void resolve(Resolved &r, uint32_t pc, const C &c, uint64_t epoch)\n    {\n"
        << "        r = Resolved{};\n        r.epoch = epoch;\n        const PcCands cands = makeCands(pc);\n"
        << "        for (uint32_t i = 0; i < cands.blockCount; ++i)\n        {\n"
        << "            const BlockCand &b = cands.blocks[i];\n"
        << "            if (pc + b.bytes > c.codeSize || std::memcmp(c.vuCode + pc, b.words, b.bytes) != 0)\n                continue;\n"
        << "            if (r.blockCount == kMaxMatches)\n            {\n                r.scan = true;\n                break;\n            }\n"
        << "            if (r.blockCount == 0u)\n                r.first = b.fn;\n            else\n                g_resolvedMore[pc / 8u][r.blockCount - 1u] = b.fn;\n"
        << "            ++r.blockCount;\n        }\n"
        << "        uint32_t lower, upper;\n        std::memcpy(&lower, c.vuCode + pc, 4);\n        std::memcpy(&upper, c.vuCode + pc + 4, 4);\n"
        << "        for (uint32_t i = 0; i < cands.pairCount; ++i)\n"
        << "            if (cands.pairs[i].lower == lower && cands.pairs[i].upper == upper)\n            {\n"
        << "                r.pair = cands.pairs[i].fn;\n                break;\n            }\n    }\n}\n\n"
        << "namespace vu1c_gen\n{\n"
        << "    void run(VU1Interpreter &vu, C &c)\n    {\n        const uint64_t epoch = VU1CompiledAccess::epoch();\n        for (;;)\n        {\n"
        << "            const uint32_t pc = VU1CompiledAccess::pc(vu);\n"
        << "            if (pc + 8u <= c.codeSize && inRange(pc))\n            {\n"
        << "                Resolved &r = g_resolved[pc / 8u];\n"
        << "                if (r.epoch != epoch)\n                    resolve(r, pc, c, epoch);\n"
        << "                if (g_range.blocks)\n                {\n"
        << "                    int result = 0;\n"
        << "                    if (!r.scan)\n                    {\n"
        << "                        if (r.first)\n                            result = r.first(vu, c);\n"
        << "                        for (uint32_t i = 1; i < r.blockCount && result == 0; ++i)\n"
        << "                            result = g_resolvedMore[pc / 8u][i - 1u](vu, c);\n                    }\n"
        << "                    else\n                    {\n"
        << "                        const PcCands cands = makeCands(pc);\n"
        << "                        for (uint32_t i = 0; i < cands.blockCount && result == 0; ++i)\n"
        << "                            if (pc + cands.blocks[i].bytes <= c.codeSize &&\n"
        << "                                std::memcmp(c.vuCode + pc, cands.blocks[i].words, cands.blocks[i].bytes) == 0)\n"
        << "                                result = cands.blocks[i].fn(vu, c);\n                    }\n"
        << "                    if (result == 2)\n                        return;\n                    if (result == 1)\n                        continue;\n"
        << "                }\n"
        << "                if (r.pair)\n                {\n                    ++g_stats.compiled;\n"
        << "                    if (!r.pair(vu, c))\n                        return;\n                    continue;\n                }\n"
        << "            }\n"
        << "            ++g_stats.interpreted;\n"
        << "            if (!VU1CompiledAccess::interpret(vu, c))\n                return;\n        }\n    }\n}\n\n"
        << "static const bool g_registered = (VU1Interpreter::registerCompiledProgram(&vu1c_gen::run), true);\n"
        << footer;
    writeIfChanged(base + "/programa0.cpp", out.str());
    std::printf("[generar_vu1] %zu funciones de par, %zu bloques (%zu con tiempos estaticos), %zu de %zu FMAC con flags muertos, %zu imagenes\n",
                pairFns.size(), blockCount, staticBlocks, deadCount, fmacCount, codes.size());
    return 0;
}
