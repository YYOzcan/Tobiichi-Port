// GOW-Port: semantica de las instrucciones MMI de permutacion, valor absoluto, saturacion sin signo y desplazamientos,
// comparada con PCSX2 (pcsx2/MMI.cpp). PEXEW/PROT3W mal ordenados duplicaban Y en la Z de las esferas de visibilidad de
// God of War (0x157F94/0x157FA0) y Clip descartaba los modelos.
#include "MiniTest.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "ps2recomp/code_generator.h"
#include "ps2recomp/instructions.h"
#include "ps2recomp/r5900_decoder.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace
{
    using Words = std::array<uint32_t, 4>;
    using Halves = std::array<uint16_t, 8>;

    __m128i fromWords(const Words &w) { return _mm_setr_epi32(int(w[0]), int(w[1]), int(w[2]), int(w[3])); }
    Words toWords(__m128i v)
    {
        Words w{};
        std::memcpy(w.data(), &v, sizeof(w));
        return w;
    }
    __m128i fromHalves(const Halves &h)
    {
        __m128i v;
        std::memcpy(&v, h.data(), sizeof(v));
        return v;
    }
    Halves toHalves(__m128i v)
    {
        Halves h{};
        std::memcpy(h.data(), &v, sizeof(h));
        return h;
    }

    std::string emit(uint32_t group, uint32_t sa, uint32_t rd, uint32_t rs, uint32_t rt)
    {
        using namespace ps2recomp;
        const std::vector<Section> sections;
        CodeGenerator gen({}, sections);
        R5900Decoder decoder;
        const uint32_t raw = (OPCODE_MMI << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | group;
        return gen.translateInstruction(decoder.decodeInstruction(0x1000, raw, false));
    }
}

void register_ps2_mmi_tests()
{
    MiniTest::Case("PS2Mmi", [](TestCase &tc)
    {
        tc.Run("word permutations follow the R5900 order", [](TestCase &t)
        {
            const __m128i v = fromWords({11u, 22u, 33u, 44u});
            t.IsTrue(toWords(PS2_PEXEW(v)) == Words{33u, 22u, 11u, 44u}, "PEXEW swaps words 0 and 2");
            t.IsTrue(toWords(PS2_PROT3W(v)) == Words{22u, 33u, 11u, 44u}, "PROT3W rotates the low three words");
            t.IsTrue(toWords(PS2_PEXCW(v)) == Words{11u, 33u, 22u, 44u}, "PEXCW swaps words 1 and 2");
        });

        tc.Run("halfword permutations follow the R5900 order", [](TestCase &t)
        {
            const __m128i v = fromHalves({0, 1, 2, 3, 4, 5, 6, 7});
            t.IsTrue(toHalves(PS2_PEXEH(v)) == Halves{2, 1, 0, 3, 6, 5, 4, 7}, "PEXEH swaps halfwords 0/2 and 4/6");
            t.IsTrue(toHalves(PS2_PREVH(v)) == Halves{3, 2, 1, 0, 7, 6, 5, 4}, "PREVH reverses within each doubleword");
            t.IsTrue(toHalves(PS2_PEXCH(v)) == Halves{0, 2, 1, 3, 4, 6, 5, 7}, "PEXCH swaps halfwords 1/2 and 5/6");
            const __m128i rs = fromHalves({10, 11, 12, 13, 14, 15, 16, 17});
            const __m128i rt = fromHalves({20, 21, 22, 23, 24, 25, 26, 27});
            t.IsTrue(toHalves(PS2_PINTH(rs, rt)) == Halves{20, 14, 21, 15, 22, 16, 23, 17}, "PINTH takes the upper half of rs");
            t.IsTrue(toHalves(PS2_PINTEH(rs, rt)) == Halves{20, 10, 22, 12, 24, 14, 26, 16}, "PINTEH takes the even halfwords");
        });

        tc.Run("absolute values saturate the minimum", [](TestCase &t)
        {
            t.IsTrue(toWords(PS2_PABSW(fromWords({0x80000000u, 0xFFFFFFFEu, 5u, 0u}))) == Words{0x7FFFFFFFu, 2u, 5u, 0u},
                     "PABSW clamps 0x80000000 to 0x7FFFFFFF");
            t.IsTrue(toHalves(PS2_PABSH(fromHalves({0x8000, 0xFFFF, 3, 0, 0, 0, 0, 0}))) == Halves{0x7FFF, 1, 3, 0, 0, 0, 0, 0},
                     "PABSH clamps 0x8000 to 0x7FFF");
        });

        tc.Run("variable shifts use rt words 0 and 2 and sign-extend", [](TestCase &t)
        {
            const __m128i rs = fromWords({4u, 99u, 31u, 99u});
            const __m128i rt = fromWords({0x08000001u, 0x12345678u, 0x80000000u, 0x9ABCDEF0u});
            t.IsTrue(toWords(PS2_PSLLVW(rs, rt)) == Words{0x80000010u, 0xFFFFFFFFu, 0u, 0u}, "PSLLVW shifts rt left by rs");
            t.IsTrue(toWords(PS2_PSRLVW(rs, rt)) == Words{0x00800000u, 0u, 1u, 0u}, "PSRLVW shifts rt right logically");
            t.IsTrue(toWords(PS2_PSRAVW(rs, rt)) == Words{0x00800000u, 0u, 0xFFFFFFFFu, 0xFFFFFFFFu}, "PSRAVW shifts arithmetically");
        });

        // GOW-Port: valores literales distintos por lane; incluyen signo y extremos.
        tc.Run("PMULTH writes eight independent signed products and both HI LO banks", [](TestCase &t)
        {
            const __m128i rs = fromHalves({1, 0xFFFE, 3, 0xFFFC, 5, 0xFFFA, 7, 0xFFF8});
            const __m128i rt = fromHalves({11, 12, 13, 14, 15, 16, 17, 18});
            for (const unsigned rd : {3u, 1u, 2u, 0u})
            {
                R5900Context ctx{};
                const Words zeroSentinel{0xAABBCCDD, 22, 33, 44};
                ctx.r[0] = fromWords(zeroSentinel);
                ctx.r[1] = rs; ctx.r[2] = rt;
                ctx.hi = ctx.lo = ctx.hi1 = ctx.lo1 = UINT64_MAX;
                ps2_pmulth(&ctx, GPR_VEC((&ctx), 1), GPR_VEC((&ctx), 2), rd);
                t.Equals(ctx.lo, 0xFFFFFFE80000000Bull, "LO contiene p0=11 y p1=-24");
                t.Equals(ctx.hi, 0xFFFFFFC800000027ull, "HI contiene p2=39 y p3=-56");
                t.Equals(ctx.lo1, 0xFFFFFFA00000004Bull, "LO alto contiene p4=75 y p5=-96");
                t.Equals(ctx.hi1, 0xFFFFFF7000000077ull, "HI alto contiene p6=119 y p7=-144");
                if (rd) t.IsTrue(toWords(ctx.r[rd]) == Words{11,39,75,119}, "rd conserva cuatro productos, también con alias");
                t.IsTrue(toWords(ctx.r[0]) == zeroSentinel, "rd=0 no escribe el registro cero");
                if (rd != 1) t.IsTrue(toHalves(ctx.r[1]) == toHalves(rs), "rs no cambia sin alias");
                if (rd != 2) t.IsTrue(toHalves(ctx.r[2]) == toHalves(rt), "rt no cambia sin alias");
            }
            R5900Context ctx{};
            ps2_pmulth(&ctx, fromHalves({0x8000,0x8000,0x7FFF,0xFFFF,0,0x7FFF,0x8000,1}),
                              fromHalves({0x8000,0x7FFF,0x7FFF,0x8000,0xFFFF,0x8000,0xFFFF,0}), 4);
            t.Equals(ctx.lo, 0xC000800040000000ull, "mínimo por mínimo y mínimo por máximo");
            t.Equals(ctx.hi, 0x000080003FFF0001ull, "máximo por máximo y negativo por mínimo");
            t.Equals(ctx.lo1, 0xC000800000000000ull, "cero y máximo por mínimo");
            t.Equals(ctx.hi1, 0x0000000000008000ull, "mínimo por menos uno, y cero");
            t.IsTrue(toWords(ctx.r[4]) == Words{0x40000000,0x3FFF0001,0,0x8000}, "rd completo, sin truncamiento de 16 bits");
            ctx.r[0] = fromWords({11,22,33,44});
            ctx.r[1] = rs;
            ps2_pmulth(&ctx, GPR_VEC((&ctx), 0), GPR_VEC((&ctx), 1), 5);
            t.IsTrue(!ctx.lo && !ctx.hi && !ctx.lo1 && !ctx.hi1 && toWords(ctx.r[5]) == Words{}, "rs=0 lee cero arquitectónico");
            ps2_pmulth(&ctx, GPR_VEC((&ctx), 1), GPR_VEC((&ctx), 0), 5);
            t.IsTrue(!ctx.lo && !ctx.hi && !ctx.lo1 && !ctx.hi1 && toWords(ctx.r[5]) == Words{}, "rt=0 lee cero arquitectónico");
            ps2_pmulth(&ctx, rs, rs, 6);
            t.IsTrue(toWords(ctx.r[6]) == Words{1,9,25,49}, "rs=rt usa los operandos completos previos");
        });

        tc.Run("PMULTH generator preserves operands aliases and rd zero side effects", [](TestCase &t)
        {
            using namespace ps2recomp;
            for (const unsigned rd : {3u,1u,2u,0u})
            {
                const auto code = emit(MMI_MMI2, MMI2_PMULTH, rd, 1, 2);
                const auto expected = "ps2_pmulth(ctx, GPR_VEC(ctx, 1), GPR_VEC(ctx, 2), " + std::to_string(rd) + ");";
                t.Equals(code, expected, "el código generado conserva rs/rt/rd y los efectos HI/LO");
            }
        });

        tc.Run("the code generator emits the corrected MMI forms", [](TestCase &t)
        {
            using namespace ps2recomp;
            t.IsTrue(emit(MMI_MMI1, MMI1_PABSW, 3, 0, 2).find("PS2_PABSW(GPR_VEC(ctx, 2))") != std::string::npos, "PABSW reads rt");
            t.IsTrue(emit(MMI_MMI1, MMI1_PABSH, 3, 0, 2).find("PS2_PABSH(GPR_VEC(ctx, 2))") != std::string::npos, "PABSH reads rt");
            t.IsTrue(emit(MMI_MMI1, MMI1_PADDUH, 3, 1, 2).find("_mm_adds_epu16") != std::string::npos, "PADDUH saturates");
            t.IsTrue(emit(MMI_MMI1, MMI1_PSUBUH, 3, 1, 2).find("_mm_subs_epu16") != std::string::npos, "PSUBUH saturates");
            t.IsTrue(emit(MMI_MMI2, MMI2_PEXEW, 3, 0, 2).find("PS2_PEXEW(GPR_VEC(ctx, 2))") != std::string::npos, "PEXEW");
            t.IsTrue(emit(MMI_MMI2, MMI2_PROT3W, 3, 0, 2).find("PS2_PROT3W(GPR_VEC(ctx, 2))") != std::string::npos, "PROT3W");
            t.IsTrue(emit(MMI_MMI2, MMI2_PEXEH, 3, 0, 2).find("PS2_PEXEH(GPR_VEC(ctx, 2))") != std::string::npos, "PEXEH");
            t.IsTrue(emit(MMI_MMI2, MMI2_PREVH, 3, 0, 2).find("PS2_PREVH(GPR_VEC(ctx, 2))") != std::string::npos, "PREVH");
            t.IsTrue(emit(MMI_MMI3, MMI3_PEXCH, 3, 0, 2).find("PS2_PEXCH(GPR_VEC(ctx, 2))") != std::string::npos, "PEXCH");
            t.IsTrue(emit(MMI_MMI3, MMI3_PEXCW, 3, 0, 2).find("PS2_PEXCW(GPR_VEC(ctx, 2))") != std::string::npos, "PEXCW");
        });
    });
}
