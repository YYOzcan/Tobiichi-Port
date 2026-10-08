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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

struct VU1CompiledGenerator
{
    using Pair = VU1Interpreter::DecodedInstructionPair;
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
    std::map<uint32_t, std::vector<std::string>> pairCases;
    std::set<std::tuple<uint32_t, uint32_t, uint32_t>> seenPairs;
    for (const Code &code : codes)
        for (uint32_t pc = 0; pc + 8u <= code.bytes.size(); pc += 8u)
        {
            if (!code.valid[pc / 8u] || !seenPairs.insert({pc, code.lower(pc), code.upper(pc)}).second)
                continue;
            const std::string name = pairFunction(code, pc, false);
            std::ostringstream test;
            test << "                if (lower == 0x" << std::hex << code.lower(pc) << "u && upper == 0x" << code.upper(pc)
                 << "u && inRange(pc))\n" << std::dec
                 << "                {\n                    ++g_stats.compiled;\n                    if (!" << name << "(vu, c))\n"
                 << "                        return;\n                    continue;\n                }\n";
            pairCases[pc].push_back(test.str());
        }

    // Bloques.
    std::map<uint32_t, std::vector<std::string>> blockCases;
    std::set<std::pair<uint32_t, std::vector<uint32_t>>> seenBlocks;
    size_t blockCount = 0, deadCount = 0, fmacCount = 0;
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
            body << "    VU1C_FAST int " << name << "(VU1Interpreter &vu, C &c)\n    {\n"
                 << "        static constexpr uint32_t words[" << words.size() << "] = {";
            for (size_t w = 0; w < words.size(); ++w)
                body << (w ? ", " : "") << "0x" << std::hex << words[w] << "u" << std::dec;
            body << "};\n"
                 << "        if (!VU1CompiledAccess::block(vu, c, " << head << "u, words, sizeof(words)))\n            return 0;\n"
                 << "        g_blockPairs += " << length << "u;\n";
            for (size_t i = 0; i < length; ++i)
            {
                const Pair &p = code.pairs[pcs[i] / 8u];
                const bool plain = i + 1u < length && !VU1CompiledGenerator::isBranch(p) && !p.eBit && !p.dBit && !p.tBit;
                const std::string k = kStruct(code, pcs[i], part);
                body << "        if (!VU1CompiledAccess::step<" << k << ", " << (dead[i] ? "true" : "false") << ", "
                     << (plain ? "true" : "false") << ">(vu, c))\n            return 2;\n";
                if (i + 1u < length && !plain)
                    body << "        if (VU1CompiledAccess::pc(vu) != " << pcs[i + 1u] << "u)\n            return 1;\n";
            }
            body << "        return 1;\n    }\n";
            parts[part] << body.str();
            declarations << "    int " << name << "(VU1Interpreter &vu, C &c);\n";
            std::ostringstream test;
            test << "                if (inRange(pc))\n                {\n                    const int r = " << name << "(vu, c);\n"
                 << "                    if (r == 2)\n                        return;\n                    if (r == 1)\n                        continue;\n                }\n";
            blockCases[head].push_back(test.str());
            ++blockCount;
        }
    }

    const std::string header =
        "// Generado por tools/vu1/generar_vu1.cpp a partir del microcódigo del juego. No publicar.\n"
        "#include \"runtime/ps2_vu1.h\"\n#include \"ps2_vu1_compiled.inl\"\n#include <cstdio>\n#include <cstdlib>\n#include <cstring>\n\n"
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
        << "namespace vu1c_gen\n{\n" << declarations.str()
        << "    void run(VU1Interpreter &vu, C &c)\n    {\n        for (;;)\n        {\n"
        << "            const uint32_t pc = VU1CompiledAccess::pc(vu);\n"
        << "            if (pc + 8u <= c.codeSize)\n            {\n"
        << "                uint32_t lower, upper;\n"
        << "                std::memcpy(&lower, c.vuCode + pc, 4);\n                std::memcpy(&upper, c.vuCode + pc + 4, 4);\n"
        << "                switch (pc)\n                {\n";
    std::set<uint32_t> allPcs;
    for (const auto &[pc, v] : pairCases)
        allPcs.insert(pc);
    for (const auto &[pc, v] : blockCases)
        allPcs.insert(pc);
    for (const uint32_t pc : allPcs)
    {
        out << "                case 0x" << hex4(pc) << ":\n";
        if (const auto it = blockCases.find(pc); it != blockCases.end())
        {
            out << "                if (g_range.blocks)\n                {\n";
            for (const auto &t : it->second)
                out << t;
            out << "                }\n";
        }
        if (const auto it = pairCases.find(pc); it != pairCases.end())
            for (const auto &t : it->second)
                out << t;
        out << "                break;\n";
    }
    out << "                default:\n                    break;\n                }\n            }\n"
        << "            ++g_stats.interpreted;\n"
        << "            if (!VU1CompiledAccess::interpret(vu, c))\n                return;\n        }\n    }\n}\n\n"
        << "static const bool g_registered = (VU1Interpreter::registerCompiledProgram(&vu1c_gen::run), true);\n"
        << footer;
    writeIfChanged(base + "/programa0.cpp", out.str());
    std::printf("[generar_vu1] %zu funciones de par, %zu bloques, %zu de %zu FMAC con flags muertos, %zu imagenes\n",
                pairFns.size(), blockCount, deadCount, fmacCount, codes.size());
    return 0;
}
