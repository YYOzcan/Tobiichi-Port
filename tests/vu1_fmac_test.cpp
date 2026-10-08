// GOW-Port: compara el código compilado de VU1 con el intérprete en todas las operaciones FMAC (cada
// variante de fuente, máscaras DEST y operaciones cruzadas) con valores límite: ceros con signo, subnormales,
// FLT_MIN, FLT_MAX, Inf/NaN y valores aleatorios. Cada programa es la FMAC probada, otra FMAC que pisa sus
// flags (flags muertos en el bloque) y el final del programa. Sin microcódigo del juego.
// Uso: vu1_fmac_test --write <micromemoria.bin>  |  vu1_fmac_test [ensayos]
#include "runtime/ps2_memory.h"
#include "runtime/ps2_vu1.h"
#include "runtime/gs/gs_frontend.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <random>
#include <vector>
#if defined(_M_X64) || defined(_M_IX86) || defined(__x86_64__) || defined(__i386__)
#include <xmmintrin.h>
#define GOW_FMAC_MXCSR 1
#else
#define GOW_FMAC_MXCSR 0
#endif

namespace
{
#if GOW_FMAC_MXCSR
struct RestoreMxcsr
{
    unsigned value = _mm_getcsr();
    ~RestoreMxcsr() { _mm_setcsr(value); }
};
#endif
constexpr uint32_t kNop = 0x2ffu, kLowerNop = 0x8000033cu, kEbit = 0x40000000u;
constexpr uint32_t kPairsPerProgram = 7u;
constexpr uint32_t kProgramBytes = kPairsPerProgram * 8u;

uint32_t upper(uint32_t op, uint32_t dest, uint32_t ft, uint32_t fs, uint32_t fd)
{
    return op | (dest << 21) | (ft << 16) | (fs << 11) | (fd << 6);
}
uint32_t special(uint32_t code, uint32_t dest, uint32_t ft, uint32_t fs)
{
    return 0x3Cu | (code & 3u) | ((code >> 2) << 6) | (dest << 21) | (ft << 16) | (fs << 11);
}

// Instrucciones FMAC probadas (vf3/ACC = f(vf1, vf2, ACC, Q, I)).
std::vector<uint32_t> fmacs()
{
    std::vector<uint32_t> out;
    for (uint32_t dest : {0xFu, 0xEu, 0x9u})
    {
        for (uint32_t op = 0x00u; op <= 0x2Fu; ++op)
            out.push_back(upper(op, dest, 2u, 1u, 3u));
        for (uint32_t code : {0x00u, 0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u, 0x08u, 0x09u, 0x0Au, 0x0Bu,
                              0x0Cu, 0x0Du, 0x0Eu, 0x0Fu, 0x18u, 0x19u, 0x1Au, 0x1Bu, 0x1Cu, 0x1Eu, 0x20u, 0x21u,
                              0x22u, 0x23u, 0x24u, 0x25u, 0x26u, 0x27u, 0x28u, 0x29u, 0x2Au, 0x2Cu, 0x2Du, 0x2Eu})
            out.push_back(special(code, dest, 2u, 1u));
    }
    return out;
}

std::vector<uint8_t> program()
{
    std::vector<uint8_t> code(PS2_VU1_CODE_SIZE);
    const auto list = fmacs();
    if (list.size() * kProgramBytes > code.size())
        throw "demasiados programas";
    for (size_t k = 0; k < list.size(); ++k)
    {
        const std::array<std::array<uint32_t, 2>, kPairsPerProgram> pairs{{
            {kLowerNop, list[k]},
            {kLowerNop, upper(0x28u, 0xFu, 5u, 4u, 6u)}, // ADD vf6, vf4, vf5: pisa los flags de la anterior
            {kLowerNop, kNop},
            {kLowerNop, kNop},
            {kLowerNop, kNop},
            {kLowerNop, kNop | kEbit},
            {kLowerNop, kNop},
        }};
        std::memcpy(code.data() + k * kProgramBytes, pairs.data(), sizeof(pairs));
    }
    return code;
}

float bitsToFloat(uint32_t bits)
{
    float f;
    std::memcpy(&f, &bits, sizeof(f));
    return f;
}

struct Inputs
{
    float vf1[4], vf2[4], vf4[4], vf5[4], acc[4], q, i;
    uint32_t status;
};

float pick(std::mt19937 &rng)
{
    static const uint32_t special[] = {
        0x00000000u, 0x80000000u, 0x3F800000u, 0xBF800000u, 0x3F000000u, 0x00800000u, 0x80800000u,
        0x00000001u, 0x807FFFFFu, 0x7F7FFFFFu, 0xFF7FFFFFu, 0x7F800000u, 0xFF800000u, 0x7FC00000u,
        0x1E3CE508u, 0x60AD78EBu, 0x7F000000u, 0x01000000u, 0x00FFFFFFu, 0x40000000u, 0xC0400000u};
    switch (rng() % 4u)
    {
    case 0:
    case 1:
        return bitsToFloat(special[rng() % (sizeof(special) / sizeof(special[0]))]);
    case 2:
        return std::uniform_real_distribution<float>(-4.0f, 4.0f)(rng);
    default:
        return bitsToFloat(static_cast<uint32_t>(rng())); // cualquier patrón de bits
    }
}

Inputs randomInputs(std::mt19937 &rng)
{
    Inputs in{};
    for (int c = 0; c < 4; ++c)
    {
        in.vf1[c] = pick(rng);
        in.vf2[c] = pick(rng);
        in.vf4[c] = pick(rng);
        in.vf5[c] = pick(rng);
        in.acc[c] = pick(rng);
    }
    in.q = pick(rng);
    in.i = pick(rng);
    in.status = (rng() % 4u == 0u) ? (static_cast<uint32_t>(rng()) & 0xFC0u) : 0u;
    return in;
}

VU1State run(PS2Memory &mem, GS &gs, bool compiled, bool queues, uint32_t pc, const Inputs &in)
{
    VU1Interpreter vu;
    vu.setDirectRegisterWrites(!queues);
    vu.setCompiledProgramsEnabled(compiled);
    VU1State &s = vu.state();
    std::memcpy(s.vf[1], in.vf1, 16);
    std::memcpy(s.vf[2], in.vf2, 16);
    std::memcpy(s.vf[4], in.vf4, 16);
    std::memcpy(s.vf[5], in.vf5, 16);
    std::memcpy(s.acc, in.acc, 16);
    s.q = in.q;
    s.i = in.i;
    s.status = in.status;
    vu.execute(mem.getVU1Code(), PS2_VU1_CODE_SIZE, mem.getVU1Data(), PS2_VU1_DATA_SIZE, gs, &mem, pc);
    return vu.state();
}

bool same(const VU1State &x, const VU1State &y)
{
    return std::memcmp(x.vf, y.vf, sizeof(x.vf)) == 0 && std::memcmp(x.acc, y.acc, sizeof(x.acc)) == 0 &&
           std::memcmp(x.vi, y.vi, sizeof(x.vi)) == 0 && x.mac == y.mac && x.status == y.status &&
           x.clip == y.clip && x.pc == y.pc && x.cycles == y.cycles;
}
}

int main(int argc, char **argv)
{
    if (argc == 3 && std::strcmp(argv[1], "--write") == 0)
    {
        const auto code = program();
        std::ofstream f(argv[2], std::ios::binary);
        f.write(reinterpret_cast<const char *>(code.data()), static_cast<std::streamsize>(code.size()));
        f.close();
        return f ? 0 : 2;
    }
    const unsigned trials = argc == 2 ? static_cast<unsigned>(std::atoi(argv[1])) : 40u;
#if GOW_FMAC_MXCSR
    RestoreMxcsr restore;
    _mm_setcsr(restore.value & ~0x8040u);
#endif
    PS2Memory mem;
    if (!mem.initialize())
        return 2;
    GS gs;
    gs.init(mem.getGSVRAM(), 4u * 1024u * 1024u, &mem.gs());
    const auto code = program();
    std::memcpy(mem.getVU1Code(), code.data(), code.size());
    const auto list = fmacs();
    std::mt19937 rng(12345u);
    unsigned long long cases = 0;
    for (unsigned t = 0; t < trials; ++t)
    {
        const Inputs in = randomInputs(rng);
        for (bool queues : {false, true})
            for (size_t k = 0; k < list.size(); ++k)
            {
                const uint32_t pc = static_cast<uint32_t>(k * kProgramBytes);
                const VU1State ref = run(mem, gs, false, queues, pc, in);
                const VU1State got = run(mem, gs, true, queues, pc, in);
                if (!same(ref, got))
                {
                    std::fprintf(stderr,
                                 "FMAC distinta: instr=%08x colas=%d ensayo=%u mac=%x/%x status=%x/%x "
                                 "vf3=%08x %08x %08x %08x / %08x %08x %08x %08x\n",
                                 list[k], queues, t, ref.mac, got.mac, ref.status, got.status,
                                 *reinterpret_cast<const uint32_t *>(&ref.vf[3][0]), *reinterpret_cast<const uint32_t *>(&ref.vf[3][1]),
                                 *reinterpret_cast<const uint32_t *>(&ref.vf[3][2]), *reinterpret_cast<const uint32_t *>(&ref.vf[3][3]),
                                 *reinterpret_cast<const uint32_t *>(&got.vf[3][0]), *reinterpret_cast<const uint32_t *>(&got.vf[3][1]),
                                 *reinterpret_cast<const uint32_t *>(&got.vf[3][2]), *reinterpret_cast<const uint32_t *>(&got.vf[3][3]));
                    return 1;
                }
                ++cases;
            }
    }
    std::printf("VU1 FMAC: %llu casos exactos (%zu instrucciones, %u ensayos con valores límite)\n", cases, list.size(),
                trials);
#if GOW_FMAC_MXCSR
    // GOW-Port: FTZ/DAZ puede dar cero redondeado sin cancelación exacta. La FMAC
    // posterior pisa Z/S, pero el underflow U debe persistir en status (bit 8).
    _mm_setcsr(_mm_getcsr() | 0x8040u);
    unsigned ftzCases = 0;
    for (uint32_t sign1 : {0u, 0x80000000u})
        for (uint32_t sign2 : {0u, 0x80000000u})
        {
            Inputs in{};
            for (unsigned c = 0; c < 4; ++c)
            {
                in.vf1[c] = bitsToFloat(sign1 | 0x00800000u);
                in.vf2[c] = bitsToFloat(sign2 | 0x00800001u);
                in.vf4[c] = 1.0f;
                in.vf5[c] = 2.0f;
            }
            in.q = in.i = in.vf2[0];
            for (bool queues : {false, true})
                for (size_t k = 0; k < list.size(); ++k)
                {
                    const uint32_t pc = static_cast<uint32_t>(k * kProgramBytes);
                    const VU1State ref = run(mem, gs, false, queues, pc, in);
                    const VU1State got = run(mem, gs, true, queues, pc, in);
                    if (!same(ref, got))
                    {
                        std::fprintf(stderr,
                                     "FMAC FTZ distinta: instr=%08x colas=%d signos=%x/%x status=%x/%x\n",
                                     list[k], queues, sign1, sign2, ref.status, got.status);
                        return 1;
                    }
                    ++ftzCases;
                }
        }
    std::printf("VU1 FMAC FTZ/DAZ: %u casos exactos (cancelaciones subnormales, signos y colas)\n", ftzCases);
#endif
    return 0;
}
