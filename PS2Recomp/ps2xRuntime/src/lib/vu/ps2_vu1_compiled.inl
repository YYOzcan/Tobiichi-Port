// GOW-Port: paso de VU1 especializado para microcódigo compilado (tools/vu1/generar_vu1.cpp).
// stepPairT<T> hace exactamente lo mismo que stepPair con el par T::value, pero como el par es una
// constante, cada decisión que depende de la decodificación se resuelve al compilar ("if constexpr") y
// solo queda el trabajo de ese par. Solo se usa con escrituras directas de registros (m_directRegisterWrites).
// Las operaciones FMAC frecuentes se especializan (upperT); el resto llama al intérprete.
#ifndef PS2_VU1_COMPILED_INL
#define PS2_VU1_COMPILED_INL

#include <atomic>
#include "ps2_vu1_step.inl"

#include <cmath>
#include <utility>
#include <cstring>
#if defined(_MSC_VER) || defined(__SSE4_1__)
#include <immintrin.h>
#define VU1C_SIMD 1
#else
#define VU1C_SIMD 0
#endif

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
    inline bool productSumFlagsFast(float result, float product, uint8_t &laneFlags)
    {
        uint32_t r = 0u, p = 0u;
        std::memcpy(&r, &result, sizeof(r));
        std::memcpy(&p, &product, sizeof(p));
        const int er = static_cast<int>((r >> 23) & 0xFFu);
        const int ep = static_cast<int>((p >> 23) & 0xFFu);
        // GOW-Port: también ep > 0xFD, como epOk en el camino SSE: con redondeo hacia cero un producto que
        // desborda queda en el máximo (exponente 0xFE) y la suma puede parecer normal sin serlo.
        if (er < 2 || er > 0xFD || er < ep - 20 || ep > 0xFD)
            return false;
        laneFlags = (r & 0x80000000u) != 0u ? 0x2u : 0u;
        return true;
    }
}
#if defined(_MSC_VER)
#define VU1C_NOINLINE __declspec(noinline)
#else
#define VU1C_NOINLINE __attribute__((noinline))
#endif

namespace vu1c
{
    enum class Kind : int
    {
        Other,
        Nop,
        Add,
        Sub,
        Madd,
        Msub,
        Mul,
        Opmsub,
        Opmula,
        Max,
        Mini,
    };
    enum class Source : int
    {
        Vector,
        Broadcast,
        Q,
        I,
    };

    struct UpperInfo
    {
        Kind kind = Kind::Other;
        Source source = Source::Vector;
        bool toAcc = false;
        uint32_t bc = 0;
    };

    constexpr UpperInfo classify(uint32_t upper)
    {
        const uint32_t op = upper & 0x3Fu;
        UpperInfo r{};
        if (op < 0x3Cu)
        {
            const uint32_t code = op;
            if (code <= 0x03u) r = {Kind::Add, Source::Broadcast, false, code & 3u};
            else if (code <= 0x07u) r = {Kind::Sub, Source::Broadcast, false, code & 3u};
            else if (code <= 0x0Bu) r = {Kind::Madd, Source::Broadcast, false, code & 3u};
            else if (code <= 0x0Fu) r = {Kind::Msub, Source::Broadcast, false, code & 3u};
            else if (code <= 0x13u) r = {Kind::Max, Source::Broadcast, false, code & 3u};
            else if (code <= 0x17u) r = {Kind::Mini, Source::Broadcast, false, code & 3u};
            else if (code <= 0x1Bu) r = {Kind::Mul, Source::Broadcast, false, code & 3u};
            else
            {
                switch (code)
                {
                case 0x1C: r = {Kind::Mul, Source::Q, false, 0}; break;
                case 0x1D: r = {Kind::Max, Source::I, false, 0}; break;
                case 0x1E: r = {Kind::Mul, Source::I, false, 0}; break;
                case 0x1F: r = {Kind::Mini, Source::I, false, 0}; break;
                case 0x20: r = {Kind::Add, Source::Q, false, 0}; break;
                case 0x21: r = {Kind::Madd, Source::Q, false, 0}; break;
                case 0x22: r = {Kind::Add, Source::I, false, 0}; break;
                case 0x23: r = {Kind::Madd, Source::I, false, 0}; break;
                case 0x24: r = {Kind::Sub, Source::Q, false, 0}; break;
                case 0x25: r = {Kind::Msub, Source::Q, false, 0}; break;
                case 0x26: r = {Kind::Sub, Source::I, false, 0}; break;
                case 0x27: r = {Kind::Msub, Source::I, false, 0}; break;
                case 0x28: r = {Kind::Add, Source::Vector, false, 0}; break;
                case 0x29: r = {Kind::Madd, Source::Vector, false, 0}; break;
                case 0x2A: r = {Kind::Mul, Source::Vector, false, 0}; break;
                case 0x2B: r = {Kind::Max, Source::Vector, false, 0}; break;
                case 0x2C: r = {Kind::Sub, Source::Vector, false, 0}; break;
                case 0x2D: r = {Kind::Msub, Source::Vector, false, 0}; break;
                case 0x2E: r = {Kind::Opmsub, Source::Vector, false, 0}; break;
                case 0x2F: r = {Kind::Mini, Source::Vector, false, 0}; break;
                default: break;
                }
            }
            return r;
        }
        const uint32_t special = (upper & 3u) | ((upper >> 4) & 0x7Cu);
        if (special <= 0x03u) return {Kind::Add, Source::Broadcast, true, special & 3u};
        if (special <= 0x07u) return {Kind::Sub, Source::Broadcast, true, special & 3u};
        if (special <= 0x0Bu) return {Kind::Madd, Source::Broadcast, true, special & 3u};
        if (special <= 0x0Fu) return {Kind::Msub, Source::Broadcast, true, special & 3u};
        if (special >= 0x18u && special <= 0x1Bu) return {Kind::Mul, Source::Broadcast, true, special & 3u};
        switch (special)
        {
        case 0x1C: return {Kind::Mul, Source::Q, true, 0};
        case 0x1E: return {Kind::Mul, Source::I, true, 0};
        case 0x20: return {Kind::Add, Source::Q, true, 0};
        case 0x21: return {Kind::Madd, Source::Q, true, 0};
        case 0x22: return {Kind::Add, Source::I, true, 0};
        case 0x23: return {Kind::Madd, Source::I, true, 0};
        case 0x24: return {Kind::Sub, Source::Q, true, 0};
        case 0x25: return {Kind::Msub, Source::Q, true, 0};
        case 0x26: return {Kind::Sub, Source::I, true, 0};
        case 0x27: return {Kind::Msub, Source::I, true, 0};
        case 0x28: return {Kind::Add, Source::Vector, true, 0};
        case 0x29: return {Kind::Madd, Source::Vector, true, 0};
        case 0x2A: return {Kind::Mul, Source::Vector, true, 0};
        case 0x2C: return {Kind::Sub, Source::Vector, true, 0};
        case 0x2D: return {Kind::Msub, Source::Vector, true, 0};
        case 0x2E: return {Kind::Opmula, Source::Vector, true, 0};
        case 0x2F:
        case 0x30: return {Kind::Nop, Source::Vector, false, 0};
        default: return {};
        }
    }

    // applyDest con la máscara constante.
    // GOW-Port: un único store de 16 bytes (mezcla de carriles). Varios stores de 4 bytes seguidos de la
    // lectura de 16 bytes del registro en el par siguiente impedían el reenvío store->load.
    template <uint32_t Dest>
    VU1_STEP_INLINE void applyDestT(float *dst, const float *src)
    {
        if constexpr (Dest == 0u)
            return;
#if defined(_MSC_VER) || defined(__SSE4_1__)
        else if constexpr (Dest == 0xFu)
            _mm_storeu_ps(dst, _mm_loadu_ps(src));
        else
        {
            constexpr int lanes = ((Dest & 8u) ? 1 : 0) | ((Dest & 4u) ? 2 : 0) | ((Dest & 2u) ? 4 : 0) | ((Dest & 1u) ? 8 : 0);
            _mm_storeu_ps(dst, _mm_blend_ps(_mm_loadu_ps(dst), _mm_loadu_ps(src), lanes));
        }
#else
        else
        {
            if constexpr ((Dest & 8u) != 0u) dst[0] = src[0];
            if constexpr ((Dest & 4u) != 0u) dst[1] = src[1];
            if constexpr ((Dest & 2u) != 0u) dst[2] = src[2];
            if constexpr ((Dest & 1u) != 0u) dst[3] = src[3];
        }
#endif
    }
    // GOW-Port: store de VU1 con DEST constante, escrito en el acto. queueStore lo encolaba con un ciclo de
    // latencia, pero el mismo paso avanza ese ciclo y commitReadyPipelines lo escribe antes de que nada más
    // lea la memoria (el siguiente par, PATH1 o el VIF): el resultado es el mismo.
    template <uint32_t Dest>
    VU1_STEP_INLINE void storeT(uint8_t *target, const uint32_t words[4])
    {
        if constexpr (Dest == 0xFu)
            std::memcpy(target, words, 16u);
        else if constexpr (Dest != 0u)
        {
            uint32_t merged[4];
            std::memcpy(merged, target, 16u);
            if constexpr ((Dest & 8u) != 0u) merged[0] = words[0];
            if constexpr ((Dest & 4u) != 0u) merged[1] = words[1];
            if constexpr ((Dest & 2u) != 0u) merged[2] = words[2];
            if constexpr ((Dest & 1u) != 0u) merged[3] = words[3];
            std::memcpy(target, merged, 16u);
        }
    }
    // Especiales de la unidad superior sin flags MAC: ITOF0..15 (0x10-0x13), FTOI0..15 (0x14-0x17), ABS
    // (0x1D) y CLIP (0x1F). Devuelve la especial o 0 si es otra instrucción.
    constexpr uint32_t simpleSpecial(uint32_t upper)
    {
        if ((upper & 0x3Fu) < 0x3Cu)
            return 0u;
        const uint32_t special = (upper & 3u) | ((upper >> 4) & 0x7Cu);
        return (special >= 0x10u && special <= 0x17u) || special == 0x1Du || special == 0x1Fu ? special : 0u;
    }
    // Igual que vuFloatToInt de ps2_vu1_upper.cpp.
    inline int32_t floatToInt(float value, float scale)
    {
        const double scaled = static_cast<double>(value) * static_cast<double>(scale);
        if (scaled >= static_cast<double>(std::numeric_limits<int32_t>::max()))
            return std::numeric_limits<int32_t>::max();
        if (scaled <= static_cast<double>(std::numeric_limits<int32_t>::min()))
            return std::numeric_limits<int32_t>::min();
        return static_cast<int32_t>(scaled);
    }
#if VU1C_SIMD
    // normalizeOperand en los cuatro carriles: exponente 0 -> cero con signo; exponente 255 -> máximo con signo.
    VU1_STEP_INLINE __m128 normalize4(__m128 v)
    {
        // GOW-Port: sin blendv. Con a = |bits|: exponente 0 (a < 0x00800000) -> 0; exponente 255 (Inf/NaN,
        // a >= 0x7F800000) -> min(a, 0x7F7FFFFF) = máximo; el resto queda igual. Luego se repone el signo.
        // Bit a bit igual que la versión anterior; 6 operaciones simples en lugar de 7 con dos blendv.
        const __m128i bits = _mm_castps_si128(v);
        const __m128i abs = _mm_and_si128(bits, _mm_set1_epi32(0x7FFFFFFF));
        const __m128i sign = _mm_xor_si128(bits, abs);
        const __m128i clamped = _mm_min_epi32(abs, _mm_set1_epi32(0x7F7FFFFF));
        const __m128i keep = _mm_cmpgt_epi32(abs, _mm_set1_epi32(0x007FFFFF));
        return _mm_castsi128_ps(_mm_or_si128(sign, _mm_and_si128(clamped, keep)));
    }
    VU1_STEP_INLINE __m128i exponent4(__m128 v)
    {
        return _mm_and_si128(_mm_srli_epi32(_mm_castps_si128(v), 23), _mm_set1_epi32(0xFF));
    }
    // Carriles activos de una máscara DEST (x = carril 0) como bits de movemask / blend.
    constexpr int laneBits(uint32_t dest)
    {
        return ((dest & 8u) ? 1 : 0) | ((dest & 4u) ? 2 : 0) | ((dest & 2u) ? 4 : 0) | ((dest & 1u) ? 8 : 0);
    }
#endif
    // Bits de MAC de una máscara de carriles en orden de componente (bit 0 = x), como laneForComponent: x = 8.
    // VU1_STEP_INLINE: MSVC la dejaba como llamada en los bloques compilados.
    VU1_STEP_INLINE constexpr uint32_t reverse4(uint32_t m)
    {
        return ((m & 1u) << 3) | ((m & 2u) << 1) | ((m & 4u) >> 1) | ((m & 8u) >> 3);
    }
    constexpr uint32_t crossLeft(uint32_t c) { return c == 0 ? 1u : c == 1 ? 2u : c == 2 ? 0u : 3u; }
    constexpr uint32_t crossRight(uint32_t c) { return c == 0 ? 2u : c == 1 ? 0u : c == 2 ? 1u : 3u; }
    // GOW-Port: MAC (bits 0-3 Z, 4-7 S en orden de componente) y estado (Z = bit 0, S = bit 1) de una FMAC a
    // partir de las máscaras de carriles de movemask (bit 0 = x): índice z | (s << 4), valor mac | (estado << 8).
    // Una consulta en lugar de invertir los bits de cada máscara en cada FMAC.
    struct MacStatusTable
    {
        uint16_t v[256];
    };
    constexpr MacStatusTable makeMacStatusTable()
    {
        MacStatusTable t{};
        for (uint32_t i = 0; i < 256u; ++i)
        {
            const uint32_t z = i & 0xFu, s = i >> 4;
            t.v[i] = static_cast<uint16_t>((reverse4(z) | (reverse4(s) << 4)) | (((s != 0u ? 0x2u : 0u) | (z != 0u ? 0x1u : 0u)) << 8));
        }
        return t;
    }
    inline constexpr MacStatusTable kMacStatus = makeMacStatusTable();

    // GOW-Port: instrucciones inferiores que lowerT trata en línea: la misma lista que su cadena de if constexpr
    // (si se añade un caso allí, hay que añadirlo aquí). Las demás llaman a execLower.
    constexpr bool lowerInline(uint32_t instr)
    {
        const uint32_t opHi = (instr >> 25) & 0x7Fu;
        const uint32_t funct = instr & 0x3Fu;
        const uint32_t funct2 = (instr & 0x3u) | ((instr >> 4) & 0x7Cu);
        if (instr == 0x00000000u || instr == 0x8000033Cu)
            return true;
        switch (opHi)
        {
        case 0x00u: case 0x01u: case 0x04u: case 0x05u: case 0x08u: case 0x09u: // LQ SQ ILW ISW IADDIU ISUBIU
        case 0x12u: case 0x18u: case 0x1Au: case 0x1Cu:                         // FCAND FMEQ FMAND FCGET
        case 0x20u: case 0x21u: case 0x24u: case 0x25u:                         // B BAL JR JALR
        case 0x28u: case 0x29u: case 0x2Cu: case 0x2Du: case 0x2Eu: case 0x2Fu: // IBxx
            return true;
        default:
            break;
        }
        if (opHi != 0x40u)
            return false;
        if (funct == 0x30u || funct == 0x31u || funct == 0x32u || funct == 0x34u || funct == 0x35u) // IADD ... IOR
            return true;
        return funct >= 0x3Cu && (funct2 == 0x30u || funct2 == 0x31u || funct2 == 0x34u || funct2 == 0x35u ||
                                  funct2 == 0x3Bu || funct2 == 0x38u || funct2 == 0x3Cu || funct2 == 0x3Du);
    }
    // Inferiores en línea que escriben VF[ft]: LQ, MOVE, MR32, LQI y MFIR. ¿Lo hacen en VF0?
    constexpr bool lowerInlineWritesVf0(uint32_t instr)
    {
        const uint32_t opHi = (instr >> 25) & 0x7Fu;
        const uint32_t funct = instr & 0x3Fu;
        const uint32_t funct2 = (instr & 0x3u) | ((instr >> 4) & 0x7Cu);
        if (((instr >> 16) & 0x1Fu) != 0u || instr == 0x00000000u || instr == 0x8000033Cu)
            return false;
        if (opHi == 0x00u)
            return true;
        return opHi == 0x40u && funct >= 0x3Cu && (funct2 == 0x30u || funct2 == 0x31u || funct2 == 0x34u || funct2 == 0x3Du);
    }
    // ¿Puede la instrucción superior escribir VF0? (FMAC con fd = 0, ITOF/FTOI/ABS con ft = 0 o execUpper.)
    constexpr bool upperMayWriteVf0(uint32_t upper)
    {
        const UpperInfo info = classify(upper);
        if (info.kind == Kind::Nop)
            return false;
        if (const uint32_t special = simpleSpecial(upper); special != 0u)
            return special != 0x1Fu && ((upper >> 16) & 0x1Fu) == 0u; // CLIP no escribe VF
        if (info.kind == Kind::Other)
            return true;
        return !info.toAcc && ((upper >> 6) & 0x1Fu) == 0u;
    }
    // El generador indica con T::clearBranchBackup = false que el par anterior del bloque no guardó un VI para
    // un salto (m_viBranchBackupValid ya es falso).
    template <class T>
    constexpr bool clearBranchBackup()
    {
        if constexpr (requires { T::clearBranchBackup; })
            return T::clearBranchBackup;
        else
            return true;
    }
}

// Una componente de una operación FMAC: calcula como execUpper (operandos normalizados, mismas expresiones
// en float) y aplica normalizeFmacResult a esa componente.
template <uint32_t Upper, uint32_t C>
VU1_STEP_INLINE void VU1Interpreter::fmacLaneT(float &result, uint8_t &laneFlags, uint8_t &productFlags)
{
    constexpr vu1c::UpperInfo info = vu1c::classify(Upper);
    constexpr uint32_t fs = (Upper >> 11) & 0x1Fu;
    constexpr uint32_t ft = (Upper >> 16) & 0x1Fu;
    constexpr bool cross = info.kind == vu1c::Kind::Opmsub || info.kind == vu1c::Kind::Opmula;
    constexpr uint32_t left = cross ? vu1c::crossLeft(C) : C;
    constexpr uint32_t rightLane = cross ? vu1c::crossRight(C) : (info.source == vu1c::Source::Broadcast ? info.bc : C);

    const float vs = normalizeOperand(m_state.vf[fs][left]);
    float right;
    if constexpr (info.source == vu1c::Source::Q)
        right = normalizeOperand(m_state.q);
    else if constexpr (info.source == vu1c::Source::I)
        right = normalizeOperand(m_state.i);
    else
        right = normalizeOperand(m_state.vf[ft][rightLane]);

    if constexpr (info.kind == vu1c::Kind::Max)
    {
        result = (vs > right) ? vs : right;
        return;
    }
    else if constexpr (info.kind == vu1c::Kind::Mini)
    {
        result = (vs < right) ? vs : right;
        return;
    }
    else
    {
        float acc = 0.0f;
        if constexpr (info.kind == vu1c::Kind::Madd || info.kind == vu1c::Kind::Msub || info.kind == vu1c::Kind::Opmsub)
            acc = normalizeOperand(m_state.acc[C]);
        // Bits pegajosos del producto (calculateFmacProductSticky), también en la componente 3 de OPMSUB.
        if constexpr (info.kind == vu1c::Kind::Madd || info.kind == vu1c::Kind::Msub || info.kind == vu1c::Kind::Opmsub)
            productFlags = productStickyFlags(vs, right, vs * right);

        if constexpr (cross && C == 3u)
            result = 0.0f;
        else if constexpr (info.kind == vu1c::Kind::Add)
            result = vs + right;
        else if constexpr (info.kind == vu1c::Kind::Sub)
            result = vs - right;
        else if constexpr (info.kind == vu1c::Kind::Madd)
            result = acc + vs * right;
        else if constexpr (info.kind == vu1c::Kind::Msub || info.kind == vu1c::Kind::Opmsub)
            result = acc - vs * right;
        else
            result = vs * right; // Mul, Opmula

        if constexpr (info.kind == vu1c::Kind::Madd || info.kind == vu1c::Kind::Msub ||
                      (info.kind == vu1c::Kind::Opmsub && C != 3u))
        {
            if (productSumFlagsFast(result, vs * right, laneFlags))
                return;
        }
        // GOW-Port: con un factor cero el producto exacto es ±0 (operandos normalizados) y el resultado en
        // float ya es el exacto: en MUL/OPMULA un cero con el signo de vs XOR right; en MADD/MSUB/OPMSUB
        // ACC ∓ 0, exacto también en float con las mismas reglas de signo, y ACC es cero o normal. Así
        // normalizeFmacExactResult no cambiaría el valor y los flags son Z (si es cero) y S.
        if constexpr (info.kind == vu1c::Kind::Mul || info.kind == vu1c::Kind::Opmula || info.kind == vu1c::Kind::Madd ||
                      info.kind == vu1c::Kind::Msub || (info.kind == vu1c::Kind::Opmsub && C != 3u))
        {
            uint32_t sBits = 0u, rBits = 0u;
            std::memcpy(&sBits, &vs, sizeof(sBits));
            std::memcpy(&rBits, &right, sizeof(rBits));
            if ((sBits & 0x7FFFFFFFu) == 0u || (rBits & 0x7FFFFFFFu) == 0u)
            {
                uint32_t bits = 0u;
                std::memcpy(&bits, &result, sizeof(bits));
                laneFlags = static_cast<uint8_t>(((bits & 0x80000000u) != 0u ? 0x2u : 0u) | ((bits & 0x7FFFFFFFu) == 0u ? 0x1u : 0u));
                return;
            }
        }

        if constexpr (info.kind == vu1c::Kind::Add || info.kind == vu1c::Kind::Sub || info.kind == vu1c::Kind::Mul)
        {
            uint32_t bits = 0u;
            std::memcpy(&bits, &result, sizeof(bits));
            const uint32_t exponent = (bits >> 23) & 0xFFu;
            if (exponent != 0u && exponent < 0xFEu)
            {
                laneFlags = (bits & 0x80000000u) != 0u ? 0x2u : 0u;
                return;
            }
        }
        double exact = 0.0; // GOW-Port: double como en MSVC (ver calculateFmacExactResult)
        if constexpr (cross && C == 3u)
            exact = 0.0;
        else if constexpr (info.kind == vu1c::Kind::Add)
            exact = static_cast<double>(vs) + static_cast<double>(right);
        else if constexpr (info.kind == vu1c::Kind::Sub)
            exact = static_cast<double>(vs) - static_cast<double>(right);
        else if constexpr (info.kind == vu1c::Kind::Madd)
            exact = static_cast<double>(acc) + static_cast<double>(vs) * static_cast<double>(right);
        else if constexpr (info.kind == vu1c::Kind::Msub || info.kind == vu1c::Kind::Opmsub)
            exact = static_cast<double>(acc) - static_cast<double>(vs) * static_cast<double>(right);
        else
            exact = static_cast<double>(vs) * static_cast<double>(right);
        laneFlags = normalizeFmacExactResult(result, exact);
    }
}

template <uint32_t Upper, bool DeadFlags>
VU1_STEP_INLINE void VU1Interpreter::upperT()
{
    constexpr vu1c::UpperInfo info = vu1c::classify(Upper);
    // GOW-Port: sin escribir m_currentUpperInstruction en NOP ni en los especiales: solo lo leen las funciones
    // de la ruta escalar de FMAC, y fmacScalarT y execUpper lo asignan antes.
    if constexpr (info.kind == vu1c::Kind::Nop)
    {
    }
    else if constexpr (constexpr uint32_t special = vu1c::simpleSpecial(Upper); special != 0u)
    {
        // Copia de los casos de execUpper (ps2_vu1_upper.cpp) con los campos resueltos.
        constexpr uint32_t dest = (Upper >> 21) & 0xFu;
        constexpr uint32_t ft = (Upper >> 16) & 0x1Fu;
        constexpr uint32_t fs = (Upper >> 11) & 0x1Fu;
        if constexpr (special == 0x1Fu) // CLIP
        {
            uint32_t wBits = 0u;
            std::memcpy(&wBits, &m_state.vf[ft][3], sizeof(wBits));
            const int32_t limit = (wBits & 0x7F800000u) != 0u ? static_cast<int32_t>(wBits & 0x7FFFFFFFu) : 0x007FFFFF;
            const auto exceeds = [limit](float value, uint32_t signMask)
            {
                uint32_t bits = 0u;
                std::memcpy(&bits, &value, sizeof(bits));
                bits ^= signMask;
                int32_t orderedBits = 0;
                std::memcpy(&orderedBits, &bits, sizeof(orderedBits));
                return orderedBits > limit;
            };
#if VU1C_SIMD
            // GOW-Port: las seis comparaciones con dos cmpgt sobre x, y, z (bits con y sin el signo invertido) y
            // los dos movemask intercalados con una tabla (bit c -> bit 2c). Igual que exceeds() carril a carril.
            (void)exceeds;
            static constexpr uint8_t kSpread[8] = {0x00, 0x01, 0x04, 0x05, 0x10, 0x11, 0x14, 0x15};
            const __m128i bits = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_state.vf[fs]));
            const __m128i lim = _mm_set1_epi32(limit);
            const int above = _mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(bits, lim))) & 7;
            const int below = _mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(
                _mm_xor_si128(bits, _mm_set1_epi32(static_cast<int>(0x80000000u))), lim))) & 7;
            const uint32_t flags = kSpread[above] | (static_cast<uint32_t>(kSpread[below]) << 1);
#else
            uint32_t flags = 0u;
            if (exceeds(m_state.vf[fs][0], 0x00000000u)) flags |= 0x01u;
            if (exceeds(m_state.vf[fs][0], 0x80000000u)) flags |= 0x02u;
            if (exceeds(m_state.vf[fs][1], 0x00000000u)) flags |= 0x04u;
            if (exceeds(m_state.vf[fs][1], 0x80000000u)) flags |= 0x08u;
            if (exceeds(m_state.vf[fs][2], 0x00000000u)) flags |= 0x10u;
            if (exceeds(m_state.vf[fs][2], 0x80000000u)) flags |= 0x20u;
#endif
            if (m_flagCount < kMaxFlagEntries) [[likely]]
            {
                // GOW-Port: queueClip + pushFlagEntry en línea (mismos campos).
                m_workingClip = ((m_workingClip << 6) | flags) & 0xFFFFFFu;
                FlagPipelineEntry &entry = m_flagPipeline[(m_flagHead + m_flagCount) % kMaxFlagEntries];
                ++m_flagCount;
                entry.mac = entry.status = entry.extraSticky = 0u;
                entry.clip = m_workingClip;
                entry.valid = true;
                entry.writesMac = entry.writesStatus = entry.writesSticky = false;
                entry.writesClip = true;
                entry.issueCycle = m_cycle;
                entry.readyCycle = m_cycle + kFmacLatency;
            }
            else
                queueClip(flags);
        }
#if VU1C_SIMD
        else if constexpr (dest != 0u)
        {
            // GOW-Port: ITOF/FTOI/ABS en los cuatro carriles. Mismo resultado que el bucle de abajo: el escalado
            // es por una potencia de dos (exacto salvo desbordar, y desbordado sigue siendo >= 2^31 o <= -2^31),
            // cvt usa el redondeo del MXCSR igual que static_cast, y cvtt da INT_MIN fuera de rango; se corrige
            // a INT_MAX en el lado positivo como vu1c::floatToInt (2147483647 en double equivale a 2^31 en float).
            const __m128 src = _mm_loadu_ps(m_state.vf[fs]);
            __m128 r;
            if constexpr (special <= 0x13u) // ITOF
            {
                r = _mm_cvtepi32_ps(_mm_castps_si128(src));
                if constexpr (special == 0x11u)
                    r = _mm_div_ps(r, _mm_set1_ps(16.0f));
                else if constexpr (special == 0x12u)
                    r = _mm_div_ps(r, _mm_set1_ps(4096.0f));
                else if constexpr (special == 0x13u)
                    r = _mm_div_ps(r, _mm_set1_ps(32768.0f));
            }
            else if constexpr (special <= 0x17u) // FTOI
            {
                constexpr float scale = special == 0x14u ? 1.0f : special == 0x15u ? 16.0f : special == 0x16u ? 4096.0f : 32768.0f;
                const __m128 scaled = _mm_mul_ps(vu1c::normalize4(src), _mm_set1_ps(scale));
                const __m128i truncated = _mm_cvttps_epi32(scaled);
                const __m128 positiveOverflow = _mm_cmpge_ps(scaled, _mm_set1_ps(2147483648.0f));
                r = _mm_blendv_ps(_mm_castsi128_ps(truncated), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)), positiveOverflow);
            }
            else // ABS
                r = _mm_and_ps(vu1c::normalize4(src), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
            float *target = m_state.vf[ft];
            _mm_storeu_ps(target, _mm_blend_ps(_mm_loadu_ps(target), r, vu1c::laneBits(dest)));
        }
#endif
        else
        {
            float result[4];
            for (uint32_t c = 0; c < 4u; ++c)
            {
                if constexpr (special <= 0x13u) // ITOF
                {
                    int32_t iv;
                    std::memcpy(&iv, &m_state.vf[fs][c], 4);
                    if constexpr (special == 0x10u)
                        result[c] = static_cast<float>(iv);
                    else if constexpr (special == 0x11u)
                        result[c] = static_cast<float>(iv) / 16.0f;
                    else if constexpr (special == 0x12u)
                        result[c] = static_cast<float>(iv) / 4096.0f;
                    else
                        result[c] = static_cast<float>(iv) / 32768.0f;
                }
                else if constexpr (special <= 0x17u) // FTOI
                {
                    constexpr float scale = special == 0x14u ? 1.0f : special == 0x15u ? 16.0f : special == 0x16u ? 4096.0f : 32768.0f;
                    const int32_t iv = vu1c::floatToInt(normalizeOperand(m_state.vf[fs][c]), scale);
                    std::memcpy(&result[c], &iv, 4);
                }
                else // ABS
                {
                    result[c] = std::fabs(normalizeOperand(m_state.vf[fs][c]));
                }
            }
            vu1c::applyDestT<dest>(m_state.vf[ft], result);
        }
    }
    else if constexpr (info.kind == vu1c::Kind::Other)
    {
        execUpper(Upper);
    }
    else
    {
        // GOW-Port: m_currentUpperInstruction solo lo leen las funciones de la ruta escalar: se asigna en
        // fmacScalarT y no en cada FMAC del camino rápido.
        constexpr uint32_t dest = (Upper >> 21) & 0xFu;
        constexpr uint32_t fd = (Upper >> 6) & 0x1Fu;
#if VU1C_SIMD
        // Los cuatro carriles con SSE. Mismas operaciones en float que fmacLaneT (cada producto y suma se
        // redondea por separado con el MXCSR del VU), así que el resultado es el mismo bit a bit. Si algún
        // carril activo saldría del camino rápido de los flags (resultado o producto cerca de cero, de los
        // extremos o con cancelación), se rehace todo con el código escalar de abajo.
        constexpr bool cross = info.kind == vu1c::Kind::Opmsub || info.kind == vu1c::Kind::Opmula;
        if constexpr (dest != 0u && !(cross && (dest & 1u) != 0u))
        {
            constexpr uint32_t fs = (Upper >> 11) & 0x1Fu;
            constexpr uint32_t ft = (Upper >> 16) & 0x1Fu;
            constexpr int lanes = vu1c::laneBits(dest);
            constexpr bool productSum = info.kind == vu1c::Kind::Madd || info.kind == vu1c::Kind::Msub ||
                                        info.kind == vu1c::Kind::Opmsub;
            __m128 vs = vu1c::normalize4(_mm_loadu_ps(m_state.vf[fs]));
            if constexpr (cross)
                vs = _mm_shuffle_ps(vs, vs, _MM_SHUFFLE(3, 0, 2, 1));
            __m128 right;
            // GOW-Port: en VU1, Q solo lo escribe la FDIV (normalizeResult en queueQ; empieza en 1,0) e I solo
            // LOI con normalizeOperand: ya están normalizados.
            if constexpr (info.source == vu1c::Source::Q)
                right = _mm_set1_ps(m_state.q);
            else if constexpr (info.source == vu1c::Source::I)
                right = _mm_set1_ps(m_state.i);
            else
            {
                right = vu1c::normalize4(_mm_loadu_ps(m_state.vf[ft]));
                if constexpr (cross)
                    right = _mm_shuffle_ps(right, right, _MM_SHUFFLE(3, 1, 0, 2));
                else if constexpr (info.source == vu1c::Source::Broadcast)
                    right = _mm_shuffle_ps(right, right, _MM_SHUFFLE(info.bc, info.bc, info.bc, info.bc));
            }
            __m128 r;
            __m128 product = _mm_setzero_ps();
            __m128 accValue = _mm_setzero_ps();
            bool fast = true;
            int zeroLanes = 0;   // carriles con flag Z (resultado exactamente cero)
            int zeroProduct = 0; // carriles con producto exactamente cero (un operando es cero)
            if constexpr (info.kind == vu1c::Kind::Max)
                r = _mm_max_ps(vs, right);
            else if constexpr (info.kind == vu1c::Kind::Mini)
                r = _mm_min_ps(vs, right);
            else
            {
                if constexpr (info.kind == vu1c::Kind::Add)
                    r = _mm_add_ps(vs, right);
                else if constexpr (info.kind == vu1c::Kind::Sub)
                    r = _mm_sub_ps(vs, right);
                else if constexpr (productSum)
                {
                    // GOW-Port: ACC solo lo escriben resultados de FMAC ya normalizados (camino rápido con exponente
                    // 1..0xFD o cero, ruta escalar y el intérprete con normalizeFmacResult; empieza en 0), así que
                    // normalize4 sobre ACC no cambia nada.
                    accValue = _mm_loadu_ps(m_state.acc);
                    product = _mm_mul_ps(vs, right);
                    r = info.kind == vu1c::Kind::Madd ? _mm_add_ps(accValue, product) : _mm_sub_ps(accValue, product);
                }
                else
                    r = _mm_mul_ps(vs, right); // Mul, Opmula
                const __m128i absMask = _mm_set1_epi32(0x7FFFFFFF);
                // GOW-Port: los rangos de exponente se comprueban sobre |bits| con una suma y una comparación con
                // signo (rango sin signo desplazado a 0x80000000) en vez de extraer el exponente y comparar dos veces.
                // |r| en [0x01000000, 0x7EFFFFFF] <=> exponente 2..0xFD; en [0x00800000, 0x7EFFFFFF] <=> 1..0xFD.
                const __m128i absR = _mm_and_si128(_mm_castps_si128(r), absMask);
                // Un operando normalizado es cero: el producto exacto es cero con signo (como el redondeado).
                // GOW-Port: comparación en float con 0: los operandos están normalizados (sin subnormales ni
                // NaN), así que solo ±0 es igual a 0 (igual que |bits| == 0, con una operación menos).
                const __m128i opZero = _mm_castps_si128(_mm_or_ps(_mm_cmpeq_ps(vs, _mm_setzero_ps()),
                                                                  _mm_cmpeq_ps(right, _mm_setzero_ps())));
                __m128i ok;
                if constexpr (productSum)
                {
                    // productSumFlagsFast (exponente del resultado 2..0xFD y no mucho menor que el del producto)
                    // y productStickyFlags (exponente del producto 2..0xFD, o producto exactamente cero).
                    const __m128i absP = _mm_and_si128(_mm_castps_si128(product), absMask);
                    const __m128i erNormal = _mm_cmpgt_epi32(_mm_set1_epi32(static_cast<int>(0xFE000000u)),
                                                             _mm_add_epi32(absR, _mm_set1_epi32(0x7F000000)));
                    const __m128i epOk = _mm_cmpgt_epi32(_mm_set1_epi32(static_cast<int>(0xFE000000u)),
                                                         _mm_add_epi32(absP, _mm_set1_epi32(0x7F000000)));
                    // er > ep - 21 <=> |r| + 20*2^23 >= (|p| sin mantisa). Con er >= 0xEB la suma desborda y da falso:
                    // el carril va a la ruta escalar (exacta); solo pasa con resultados de 2^108 o más.
                    const __m128i notSmaller = _mm_cmpgt_epi32(_mm_add_epi32(absR, _mm_set1_epi32(0x0A000001)),
                                                               _mm_and_si128(absP, _mm_set1_epi32(0x7F800000)));
                    // GOW-Port: con un factor cero, ACC ∓ 0 es exacto en float (ACC es cero o normal), así que el
                    // carril vale también con resultado cero o en los extremos; sus flags son Z (si es cero) y S.
                    ok = _mm_or_si128(_mm_and_si128(_mm_and_si128(erNormal, notSmaller), epOk), opZero);
                    const __m128i rZero = _mm_cmpeq_epi32(absR, _mm_setzero_si128());
                    // GOW-Port: primera criba barata. Si todos los carriles pasan ya aquí (lo normal), la
                    // comprobación de factor ±1 de abajo no cambia nada: un carril que pasa con resultado cero solo
                    // puede hacerlo por un factor cero (exponente 0 no está en 2..0xFD), así que Z = resultado cero.
                    if ((_mm_movemask_ps(_mm_castsi128_ps(ok)) & lanes) == lanes) [[likely]]
                    {
                        zeroLanes = _mm_movemask_ps(_mm_castsi128_ps(rZero)) & lanes;
                        zeroProduct = _mm_movemask_ps(_mm_castsi128_ps(opZero)) & lanes;
                    }
                    else
                    {
                        // GOW-Port: con un factor ±1 el producto es exacto (el otro factor normalizado), así que el
                        // resultado en float es la suma exacta redondeada una vez: con exponente 2..0xFD no cambia y
                        // sus flags son el signo, y si ACC cancela exactamente el producto es un cero exacto (+0, Z).
                        const __m128i one = _mm_set1_epi32(0x3F800000);
                        const __m128i exactProduct = _mm_or_si128(
                            _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(vs), absMask), one),
                            _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(right), absMask), one));
                        const __m128 cancelled = info.kind == vu1c::Kind::Madd
                            ? _mm_cmpeq_ps(accValue, _mm_xor_ps(product, _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000u)))))
                            : _mm_cmpeq_ps(accValue, product);
                        const __m128i exactZero = _mm_and_si128(exactProduct, _mm_and_si128(rZero, _mm_castps_si128(cancelled)));
                        ok = _mm_or_si128(ok, _mm_and_si128(exactProduct, _mm_or_si128(erNormal, exactZero)));
                        zeroLanes = _mm_movemask_ps(_mm_castsi128_ps(_mm_and_si128(_mm_or_si128(opZero, exactZero), rZero))) & lanes;
                        zeroProduct = _mm_movemask_ps(_mm_castsi128_ps(opZero)) & lanes;
                    }
                }
                else
                {
                    // Add, Sub, Mul: exponente del resultado 1..0xFD, o cero exacto.
                    // GOW-Port: con FTZ, r==0 tambien puede ocultar una cancelacion subnormal.
                    // Comprobar operandos opuestos/iguales conserva su flag U en el camino escalar.
                    ok = _mm_cmpgt_epi32(_mm_set1_epi32(static_cast<int>(0xFE800000u)), _mm_add_epi32(absR, _mm_set1_epi32(0x7F800000)));
                    __m128i exactZero;
                    if constexpr (info.kind == vu1c::Kind::Add)
                        exactZero = _mm_castps_si128(_mm_cmpeq_ps(vs, _mm_xor_ps(right,
                            _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000u))))));
                    else if constexpr (info.kind == vu1c::Kind::Sub)
                        exactZero = _mm_castps_si128(_mm_cmpeq_ps(vs, right));
                    else
                        exactZero = opZero;
                    ok = _mm_or_si128(ok, exactZero);
                    zeroLanes = _mm_movemask_ps(_mm_castsi128_ps(exactZero)) & lanes;
                }
                fast = (_mm_movemask_ps(_mm_castsi128_ps(ok)) & lanes) == lanes;
            }
            if (fast)
            {
                if constexpr (info.kind != vu1c::Kind::Max && info.kind != vu1c::Kind::Mini)
                {
                    if (DeadFlags && m_statusQuiet)
                    {
                        // GOW-Port: solo los bits pegajosos. S: algún signo en el resultado o en el producto (un
                        // movemask del OR de los dos); Z: algún resultado o producto cero. Igual que antes.
                        const int anySign = _mm_movemask_ps(productSum ? _mm_or_ps(r, product) : r) & lanes;
                        const int anyZero = zeroLanes | zeroProduct;
                        m_state.status |= (static_cast<uint32_t>(anySign != 0) << 7) | (static_cast<uint32_t>(anyZero != 0) << 6);
                    }
                    else if (m_flagCount < kMaxFlagEntries)
                    {
                        const int signs = _mm_movemask_ps(r) & lanes;
                        const uint32_t productSticky =
                            productSum ? ((_mm_movemask_ps(product) & lanes) != 0 ? 0x2u : 0u) | (zeroProduct != 0 ? 0x1u : 0u) : 0u;
                        // GOW-Port: updateFmacFlags + pushFlagEntry en línea (era ~6 % del hilo del juego). En el
                        // camino rápido solo hay Z y S. Máscara SSE: bit 0 = x; MAC: bit 3 = x (orden invertido).
                        static constexpr uint8_t kReverse4[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
                        FlagPipelineEntry &entry = m_flagPipeline[(m_flagHead + m_flagCount) % kMaxFlagEntries];
                        ++m_flagCount;
                        entry.mac = kReverse4[zeroLanes] | (static_cast<uint32_t>(kReverse4[signs]) << 4u);
                        entry.status = (zeroLanes != 0 ? 0x1u : 0u) | (signs != 0 ? 0x2u : 0u);
                        entry.extraSticky = productSticky;
                        entry.clip = 0u;
                        entry.valid = true;
                        entry.writesMac = entry.writesStatus = true;
                        entry.writesSticky = entry.writesClip = false;
                        entry.issueCycle = m_cycle;
                        entry.readyCycle = m_cycle + kFmacLatency;
                    }
                    else
                    {
                        const int signs = _mm_movemask_ps(r) & lanes;
                        const uint32_t productSticky =
                            productSum ? ((_mm_movemask_ps(product) & lanes) != 0 ? 0x2u : 0u) | (zeroProduct != 0 ? 0x1u : 0u) : 0u;
                        // Mismo MAC y status que updateFmacFlags con los flags por carril (Z = bit 0, S = bit 1).
                        const uint32_t z = static_cast<uint32_t>(zeroLanes) & static_cast<uint32_t>(lanes);
                        const uint32_t sg = static_cast<uint32_t>(signs) & static_cast<uint32_t>(lanes);
                        const uint32_t macStatus = vu1c::kMacStatus.v[z | (sg << 4)];
                        pushFmacFlags(macStatus & 0xFFu, macStatus >> 8, productSticky);
                    }
                }
                float *target = info.toAcc ? m_state.acc : m_state.vf[fd];
                _mm_storeu_ps(target, _mm_blend_ps(_mm_loadu_ps(target), r, lanes));
                return;
            }
        }
#endif
        // GOW-Port: la ruta escalar (carriles fuera del camino rápido) va aparte y sin expandir en línea: así
        // cada par compilado lleva solo la ruta SSE y los bloques caben mejor en la caché de instrucciones.
        fmacScalarT<Upper, DeadFlags>();
    }
}

// Ruta escalar de upperT para las FMAC (cuatro fmacLaneT, flags y destino), fuera de línea.
template <uint32_t Upper, bool DeadFlags>
VU1C_NOINLINE void VU1Interpreter::fmacScalarT()
{
    m_currentUpperInstruction = Upper;
    constexpr vu1c::UpperInfo info = vu1c::classify(Upper);
    constexpr uint32_t dest = (Upper >> 21) & 0xFu;
    constexpr uint32_t fd = (Upper >> 6) & 0x1Fu;
        float result[4]{};
        uint8_t laneFlags[4]{};
        uint8_t productFlags[4]{};
        if constexpr ((dest & 8u) != 0u) fmacLaneT<Upper, 0>(result[0], laneFlags[0], productFlags[0]);
        if constexpr ((dest & 4u) != 0u) fmacLaneT<Upper, 1>(result[1], laneFlags[1], productFlags[1]);
        if constexpr ((dest & 2u) != 0u) fmacLaneT<Upper, 2>(result[2], laneFlags[2], productFlags[2]);
        if constexpr ((dest & 1u) != 0u) fmacLaneT<Upper, 3>(result[3], laneFlags[3], productFlags[3]);
        if constexpr (info.kind != vu1c::Kind::Max && info.kind != vu1c::Kind::Mini)
        {
            if constexpr (dest != 0u)
            {
                // DeadFlags: el generador comprobó que, en este bloque, otra FMAC posterior escribe los flags
                // antes de que nadie pueda leer estos. Con m_statusQuiet solo cuentan sus bits pegajosos,
                // que el estado acumula en cualquier orden (y quedan igual al final del bloque).
                // GOW-Port: no leer status ahora no hace muertos sus bits persistentes.
                constexpr bool isProductSum = info.kind == vu1c::Kind::Madd || info.kind == vu1c::Kind::Msub || info.kind == vu1c::Kind::Opmsub;
                const uint32_t productSticky = isProductSum ? calculateFmacProductSticky(static_cast<uint8_t>(dest)) : 0u;
                if (DeadFlags && m_statusQuiet)
                    m_state.status |= static_cast<uint32_t>((laneFlags[0] | laneFlags[1] | laneFlags[2] | laneFlags[3] | productSticky) & 0xFu) << 6;
                else
                {
                    // updateFmacFlags con DEST constante.
                    uint32_t mac = 0u, status = 0u;
                    if constexpr ((dest & 8u) != 0u)
                        mac |= ((laneFlags[0] & 1u) << 3) | ((laneFlags[0] & 2u) << 6) | ((laneFlags[0] & 4u) << 9) | ((laneFlags[0] & 8u) << 12), status |= laneFlags[0];
                    if constexpr ((dest & 4u) != 0u)
                        mac |= ((laneFlags[1] & 1u) << 2) | ((laneFlags[1] & 2u) << 5) | ((laneFlags[1] & 4u) << 8) | ((laneFlags[1] & 8u) << 11), status |= laneFlags[1];
                    if constexpr ((dest & 2u) != 0u)
                        mac |= ((laneFlags[2] & 1u) << 1) | ((laneFlags[2] & 2u) << 4) | ((laneFlags[2] & 4u) << 7) | ((laneFlags[2] & 8u) << 10), status |= laneFlags[2];
                    if constexpr ((dest & 1u) != 0u)
                        mac |= (laneFlags[3] & 1u) | ((laneFlags[3] & 2u) << 3) | ((laneFlags[3] & 4u) << 6) | ((laneFlags[3] & 8u) << 9), status |= laneFlags[3];
                    pushFmacFlags(mac, status, productSticky);
                }
            }
        }
        float *target = info.toAcc ? m_state.acc : m_state.vf[fd];
        vu1c::applyDestT<dest>(target, result);
}

// Instrucciones inferiores frecuentes especializadas. Cada caso es copia exacta del de execLower
// (ps2_vu1_lower.cpp); las demás llaman a execLower. Las huellas de repetir_cadena_vif comprueban que
// coinciden con el intérprete.
template <uint32_t Lower>
VU1_STEP_INLINE void VU1Interpreter::lowerT(StepContext &context, uint32_t upperInstr)
{
    constexpr uint32_t instr = Lower;
    constexpr uint32_t opHi = (instr >> 25) & 0x7Fu;
    constexpr uint32_t funct = instr & 0x3Fu;
    constexpr uint32_t funct2 = (instr & 0x3u) | ((instr >> 4) & 0x7Cu);
    constexpr uint8_t ft = static_cast<uint8_t>((instr >> 16) & 0x1Fu);
    constexpr uint8_t fs = static_cast<uint8_t>((instr >> 11) & 0x1Fu);
    constexpr uint8_t viT = static_cast<uint8_t>((instr >> 16) & 0xFu);
    constexpr uint8_t viS = static_cast<uint8_t>((instr >> 11) & 0xFu);
    constexpr uint8_t viD = static_cast<uint8_t>((instr >> 6) & 0xFu);
    constexpr uint8_t dest = static_cast<uint8_t>((instr >> 21) & 0xFu);
    constexpr int16_t imm11 = static_cast<int16_t>(static_cast<int32_t>(instr << 21) >> 21);
    uint8_t *vuData = context.vuData;
    const uint32_t dataSize = context.dataSize;

    if constexpr (instr == 0x00000000u || instr == 0x8000033Cu)
    {
        return;
    }
    else if constexpr (opHi == 0x00u) // LQ
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<int32_t>(m_state.vi[viS] + imm11)) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            float tmp[4];
            std::memcpy(tmp, vuData + addr, 16);
            vu1c::applyDestT<dest>(m_state.vf[ft], tmp);
        }
    }
    else if constexpr (opHi == 0x01u) // SQ
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<int32_t>(m_state.vi[viT] + imm11)) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            uint32_t words[4]{};
            std::memcpy(words, m_state.vf[fs], sizeof(words));
            if (m_xgkick.active)
                xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 copia antes de que la VU escriba en su memoria
            vu1c::storeT<dest>(vuData + addr, words);
        }
    }
    else if constexpr (opHi == 0x04u) // ILW
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<int32_t>(m_state.vi[viS] + imm11)) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            constexpr int comp = (dest & 0x8) ? 0 : (dest & 0x4) ? 1 : (dest & 0x2) ? 2 : 3;
            uint32_t v;
            std::memcpy(&v, vuData + addr + comp * 4, 4);
            if constexpr (viT != 0)
                m_state.vi[viT] = static_cast<int32_t>(static_cast<int16_t>(v & 0xFFFF));
        }
    }
    else if constexpr (opHi == 0x05u) // ISW
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<int32_t>(m_state.vi[viS] + imm11)) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            const uint32_t val = static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viT] & 0xFFFF));
            const uint32_t words[4] = {val, val, val, val};
            if (m_xgkick.active)
                xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 copia antes de que la VU escriba en su memoria
            vu1c::storeT<dest>(vuData + addr, words);
        }
    }
    else if constexpr (opHi == 0x08u || opHi == 0x09u) // IADDIU / ISUBIU
    {
        constexpr int16_t imm = static_cast<int16_t>(static_cast<int16_t>(instr & 0x7FF) | ((instr >> 10) & 0x7800));
        if constexpr (viT != 0)
        {
            if constexpr (opHi == 0x08u)
                m_state.vi[viT] = static_cast<int16_t>(m_state.vi[viS] + imm);
            else
                m_state.vi[viT] = static_cast<int16_t>(m_state.vi[viS] - imm);
        }
    }
    // GOW-Port: lectores de flags, BAL, JR y JALR, copias de execLower (ps2_vu1_lower.cpp). Eran el 85 % de las
    // llamadas a execLower desde el código compilado.
    else if constexpr (opHi == 0x12u) // FCAND
    {
        // GOW-Port: flags listos en este ciclo (sin llamada si la cabeza de la cola aún no está lista).
        if (m_flagCount != 0u && m_flagPipeline[m_flagHead].readyCycle <= m_cycle)
            commitReadyFlags();
        constexpr uint32_t imm24 = instr & 0xFFFFFFu;
        m_state.vi[1] = ((m_state.clip & imm24) != 0u) ? 1 : 0;
    }
    else if constexpr (opHi == 0x18u) // FMEQ
    {
        if (m_flagCount != 0u && m_flagPipeline[m_flagHead].readyCycle <= m_cycle)
            commitReadyFlags();
        if constexpr (viT != 0)
            m_state.vi[viT] = ((m_state.mac & 0xFFFFu) == static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viS]))) ? 1 : 0;
    }
    else if constexpr (opHi == 0x1Au) // FMAND
    {
        if (m_flagCount != 0u && m_flagPipeline[m_flagHead].readyCycle <= m_cycle)
            commitReadyFlags();
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int32_t>(m_state.mac & static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viS])));
    }
    else if constexpr (opHi == 0x1Cu) // FCGET
    {
        if (m_flagCount != 0u && m_flagPipeline[m_flagHead].readyCycle <= m_cycle)
            commitReadyFlags();
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int32_t>(m_state.clip & 0x0FFFu);
    }
    else if constexpr (opHi == 0x21u) // BAL
    {
        const uint32_t target = (m_state.pc + 8 + imm11 * 8) & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int32_t>((m_state.pc + 16) / 8);
        m_state.branchPending = true;
        m_state.branchTarget = target;
        m_state.branchDelay = 1;
    }
    else if constexpr (opHi == 0x24u || opHi == 0x25u) // JR / JALR
    {
        // JR/JALR leen el VI actual; el valor retrasado se usa solo en las ramas condicionales.
        const uint32_t target = (static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viS])) * 8u) & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
        if constexpr (opHi == 0x25u && viT != 0)
            m_state.vi[viT] = static_cast<int32_t>((m_state.pc + 16) / 8);
        m_state.branchPending = true;
        m_state.branchTarget = target;
        m_state.branchDelay = 1;
    }
    else if constexpr (opHi == 0x20u) // B
    {
        const uint32_t target = (m_state.pc + 8 + imm11 * 8) & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
        m_state.branchPending = true;
        m_state.branchTarget = target;
        m_state.branchDelay = 1;
    }
    else if constexpr (opHi == 0x28u || opHi == 0x29u || (opHi >= 0x2Cu && opHi <= 0x2Fu)) // IBxx
    {
        // GOW-Port: readBranchVi en línea (está en ps2_vu1_core.cpp y cada salto de bucle era una llamada).
        const auto readBranchViInline = [this](uint32_t reg) -> int32_t
        {
            if (reg == 0u)
                return 0;
            if (m_viBranchBackupValid && m_viBranchBackupReg == reg)
                return m_viBranchBackupValue;
            return m_state.vi[reg];
        };
        bool taken;
        if constexpr (opHi == 0x28u)
            taken = static_cast<int16_t>(readBranchViInline(viS)) == static_cast<int16_t>(readBranchViInline(viT));
        else if constexpr (opHi == 0x29u)
            taken = static_cast<int16_t>(readBranchViInline(viS)) != static_cast<int16_t>(readBranchViInline(viT));
        else if constexpr (opHi == 0x2Cu)
            taken = static_cast<int16_t>(readBranchViInline(viS)) < 0;
        else if constexpr (opHi == 0x2Du)
            taken = static_cast<int16_t>(readBranchViInline(viS)) > 0;
        else if constexpr (opHi == 0x2Eu)
            taken = static_cast<int16_t>(readBranchViInline(viS)) <= 0;
        else
            taken = static_cast<int16_t>(readBranchViInline(viS)) >= 0;
        if (taken)
        {
            const uint32_t target = (m_state.pc + 8 + imm11 * 8) & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
            m_state.branchPending = true;
            m_state.branchTarget = target;
            m_state.branchDelay = 1;
        }
    }
    else if constexpr (opHi == 0x40u && funct == 0x30u) // IADD
    {
        if constexpr (viD != 0)
            m_state.vi[viD] = static_cast<int16_t>(m_state.vi[viS] + m_state.vi[viT]);
    }
    else if constexpr (opHi == 0x40u && funct == 0x31u) // ISUB
    {
        if constexpr (viD != 0)
            m_state.vi[viD] = static_cast<int16_t>(m_state.vi[viS] - m_state.vi[viT]);
    }
    else if constexpr (opHi == 0x40u && funct == 0x32u) // IADDI
    {
        constexpr int16_t imm5 = static_cast<int16_t>(static_cast<int32_t>((instr >> 6) & 0x1F) << 27 >> 27);
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int16_t>(m_state.vi[viS] + imm5);
    }
    else if constexpr (opHi == 0x40u && funct == 0x34u) // IAND
    {
        if constexpr (viD != 0)
            m_state.vi[viD] = m_state.vi[viS] & m_state.vi[viT];
    }
    else if constexpr (opHi == 0x40u && funct == 0x35u) // IOR
    {
        if constexpr (viD != 0)
            m_state.vi[viD] = m_state.vi[viS] | m_state.vi[viT];
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x30u) // MOVE
    {
        float tmp[4];
        std::memcpy(tmp, m_state.vf[fs], 16);
        vu1c::applyDestT<dest>(m_state.vf[ft], tmp);
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x31u) // MR32
    {
        float tmp[4] = {m_state.vf[fs][1], m_state.vf[fs][2], m_state.vf[fs][3], m_state.vf[fs][0]};
        vu1c::applyDestT<dest>(m_state.vf[ft], tmp);
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x34u) // LQI
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viS])) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            float tmp[4];
            std::memcpy(tmp, vuData + addr, 16);
            vu1c::applyDestT<dest>(m_state.vf[ft], tmp);
        }
        if constexpr (viS != 0)
            m_state.vi[viS] = static_cast<int16_t>(m_state.vi[viS] + 1);
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x35u) // SQI
    {
        uint32_t addr = static_cast<uint32_t>(static_cast<uint16_t>(m_state.vi[viT])) * 16u;
        addr &= (dataSize - 1);
        if (addr + 16 <= dataSize)
        {
            uint32_t words[4]{};
            std::memcpy(words, m_state.vf[fs], sizeof(words));
            if (m_xgkick.active)
                xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 copia antes de que la VU escriba en su memoria
            vu1c::storeT<dest>(vuData + addr, words);
        }
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int16_t>(m_state.vi[viT] + 1);
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x3Bu) // WAITQ
    {
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x38u) // DIV
    {
        constexpr int fsf = (instr >> 21) & 0x3;
        constexpr int ftf = (instr >> 23) & 0x3;
        const float num = normalizeOperand(m_state.vf[fs][fsf]);
        const float den = normalizeOperand(m_state.vf[ft][ftf]);
        uint32_t statusDi = 0u;
        float result = 0.0f;
        if (den == 0.0f)
        {
            statusDi = num == 0.0f ? 0x10u : 0x20u;
            result = std::signbit(num) != std::signbit(den) ? -std::numeric_limits<float>::max()
                                                            : std::numeric_limits<float>::max();
        }
        else
        {
            result = num / den;
        }
        // GOW-Port: normalizeResult y queueQ en línea (eran dos llamadas por DIV, una por vértice en la
        // perspectiva): exponente 0 -> cero con signo, 255 -> máximo con signo; queueQ volvía a normalizar un
        // valor ya normalizado (no cambia).
        uint32_t bits = 0u;
        std::memcpy(&bits, &result, sizeof(bits));
        const uint32_t exponent = (bits >> 23) & 0xFFu;
        if (exponent == 0u)
            bits &= 0x80000000u;
        else if (exponent == 0xFFu)
            bits = (bits & 0x80000000u) | 0x7F7FFFFFu;
        std::memcpy(&result, &bits, sizeof(bits));
        m_fdiv.valid = true;
        m_fdiv.readyCycle = m_cycle + 7u;
        m_nextCommitCycle = std::min(m_nextCommitCycle, m_fdiv.readyCycle);
        m_fdiv.value = result;
        m_fdiv.statusDi = statusDi & 0x30u;
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x3Cu) // MTIR
    {
        constexpr uint32_t comp = (instr >> 21) & 0x3u;
        uint32_t fval;
        std::memcpy(&fval, &m_state.vf[fs][comp], 4);
        if constexpr (viT != 0)
            m_state.vi[viT] = static_cast<int32_t>(static_cast<int16_t>(fval & 0xFFFF));
    }
    else if constexpr (opHi == 0x40u && funct >= 0x3Cu && funct2 == 0x3Du) // MFIR
    {
        float result[4];
        const int32_t val = static_cast<int32_t>(static_cast<int16_t>(m_state.vi[viS] & 0xFFFF));
        std::memcpy(&result[0], &val, 4);
        result[1] = result[0];
        result[2] = result[0];
        result[3] = result[0];
        vu1c::applyDestT<dest>(m_state.vf[ft], result);
    }
    else
    {
        if (m_xgkick.active)
            xgkickAdvanceTo(m_cycle); // GOW-Port: puede escribir en la memoria de datos o iniciar un XGKICK
        execLower(instr, vuData, dataSize, *context.gs, context.memory, upperInstr);
    }
}

// Un bloque compilado se ejecuta entero en orden: sus palabras coinciden con las de la micromemoria, no
// hay un salto ni un final de programa pendiente y queda presupuesto de ciclos de sobra (el análisis de
// vida de flags supone que se llega al final del bloque).
VU1_STEP_INLINE void VU1Interpreter::pushFmacFlags(uint32_t mac, uint32_t status, uint32_t extraSticky)
{
    static_assert((kMaxFlagEntries & (kMaxFlagEntries - 1u)) == 0u);
    if (m_flagCount >= kMaxFlagEntries)
    {
        commitReadyFlags();
        if (m_flagCount >= kMaxFlagEntries)
        {
            reportReservedInstruction(true, 0xFFFFFFFFu);
            return;
        }
    }
    FlagPipelineEntry &entry = m_flagPipeline[(m_flagHead + m_flagCount) & (kMaxFlagEntries - 1u)];
    ++m_flagCount;
    entry.mac = mac;
    entry.status = status;
    entry.extraSticky = extraSticky;
    entry.clip = 0u;
    entry.writesMac = entry.writesStatus = true;
    entry.writesSticky = entry.writesClip = false;
    entry.valid = true;
    entry.issueCycle = m_cycle;
    entry.readyCycle = m_cycle + kFmacLatency;
}

inline bool VU1Interpreter::blockPreconditions(StepContext &context, uint32_t pc, const uint32_t *words, size_t bytes) const
{
    if (m_state.branchPending || m_state.ebit || m_state.haltAfterDelaySlot || m_stopRequested)
        return false;
    const uint64_t maxBlockCycles = (bytes / 8u) * 4u + 64u;
    if (m_cycle + maxBlockCycles >= context.budgetEnd || pc + bytes > context.codeSize)
        return false;
    return std::memcmp(context.vuCode + pc, words, bytes) == 0;
}

template <class T>
VU1_STEP_INLINE uint64_t VU1Interpreter::readyCycleT() const
{
    constexpr const DecodedInstructionPair &k = T::value;
    uint64_t ready = m_cycle;
    // Lecturas de VF de las dos instrucciones (índices y componentes constantes).
#define VU1C_VF_READS(USAGE)                                                                     \
    if constexpr (k.USAGE.vfReadCount > 0u)                                                      \
    {                                                                                            \
        constexpr uint32_t reg = k.USAGE.vfRead[0].reg, lanes = k.USAGE.vfRead[0].lanes;         \
        if constexpr ((lanes & 8u) != 0u) ready = std::max(ready, m_vfReady[reg][0]);            \
        if constexpr ((lanes & 4u) != 0u) ready = std::max(ready, m_vfReady[reg][1]);            \
        if constexpr ((lanes & 2u) != 0u) ready = std::max(ready, m_vfReady[reg][2]);            \
        if constexpr ((lanes & 1u) != 0u) ready = std::max(ready, m_vfReady[reg][3]);            \
    }                                                                                            \
    if constexpr (k.USAGE.vfReadCount > 1u)                                                      \
    {                                                                                            \
        constexpr uint32_t reg = k.USAGE.vfRead[1].reg, lanes = k.USAGE.vfRead[1].lanes;         \
        if constexpr ((lanes & 8u) != 0u) ready = std::max(ready, m_vfReady[reg][0]);            \
        if constexpr ((lanes & 4u) != 0u) ready = std::max(ready, m_vfReady[reg][1]);            \
        if constexpr ((lanes & 2u) != 0u) ready = std::max(ready, m_vfReady[reg][2]);            \
        if constexpr ((lanes & 1u) != 0u) ready = std::max(ready, m_vfReady[reg][3]);            \
    }                                                                                            \
    if constexpr ((k.USAGE.viRead & 0xFFFEu) != 0u)                                              \
    {                                                                                            \
        for (uint32_t pending = (k.USAGE.viRead & 0xFFFEu); pending != 0u; pending &= pending - 1u) \
            ready = std::max(ready, m_viReady[std::countr_zero(pending)]);                      \
    }                                                                                            \
    if constexpr ((k.USAGE.accRead & 8u) != 0u) ready = std::max(ready, m_accReady[0]);          \
    if constexpr ((k.USAGE.accRead & 4u) != 0u) ready = std::max(ready, m_accReady[1]);          \
    if constexpr ((k.USAGE.accRead & 2u) != 0u) ready = std::max(ready, m_accReady[2]);          \
    if constexpr ((k.USAGE.accRead & 1u) != 0u) ready = std::max(ready, m_accReady[3]);
    VU1C_VF_READS(upperUsage)
    VU1C_VF_READS(lowerUsage)
#undef VU1C_VF_READS
    if constexpr (k.lowerUsage.pipeline == PipelineFdiv || k.lowerUsage.waitQ)
    {
        if (m_fdiv.valid)
            ready = std::max(ready, m_fdiv.readyCycle);
    }
    if constexpr (k.lowerUsage.pipeline == PipelineEfu)
        ready = std::max(ready, m_efuResourceReady);
    if constexpr (k.lowerUsage.waitP)
    {
        for (const ScalarPipelineEntry &entry : m_efu)
            if (entry.valid)
                ready = std::max(ready, entry.readyCycle);
    }
    if constexpr (k.lowerUsage.pipeline == PipelineXgkick)
    {
        if (m_xgkick.active)
            ready = std::max(ready, m_cycle + 1u);
    }
    return ready;
}

template <class T, bool DeadFlags, bool Plain, bool Chained>
VU1_STEP_INLINE bool VU1Interpreter::stepPairT(StepContext &context)
{
    constexpr const DecodedInstructionPair &k = T::value;

    // Igual que compiledPrologue + stepPair.
    // GOW-Port: Chained = par que no es el primero de su bloque. El par anterior acaba de confirmar los
    // pipelines en este mismo ciclo, y blockPreconditions dejó al entrar 16384 ciclos de margen hasta el
    // final del presupuesto (las esperas de abajo lo siguen comprobando).
    if constexpr (Chained)
    {
        if (m_stopRequested)
            return false;
    }
    else
    {
        if (m_cycle >= context.budgetEnd || m_stopRequested)
            return false;
        if (m_cycle >= m_nextCommitCycle)
            commitReadyPipelines();
    }

    if constexpr (k.lowerUsage.pipeline == PipelineXgkick)
    {
        if (m_xgkick.active)
            xgkickAdvanceTo(m_cycle); // GOW-Port: saber si el envío anterior sigue activo
    }
    uint64_t readyCycle = readyCycleT<T>();
    if (readyCycle > m_cycle)
    {
        if (readyCycle >= context.budgetEnd)
        {
            advanceTo(context.budgetEnd);
            return false;
        }
        advanceTo(readyCycle);
        if (m_cycle >= context.budgetEnd)
            return false;
    }

    constexpr uint32_t viWrites = k.lowerUsage.viWrite & 0xFFFEu;
    constexpr uint32_t writtenVi = viWrites != 0u ? static_cast<uint32_t>(std::countr_zero(viWrites)) : 0u;
    int32_t oldVi = 0;
    if constexpr (writtenVi != 0u)
        oldVi = m_state.vi[writtenVi];

    constexpr bool lowerNop = k.lower == 0x00000000u || k.lower == 0x8000033Cu;
    if constexpr (k.iBit)
    {
        upperT<k.upper, DeadFlags>();
        float immediate = 0.0f;
        constexpr uint32_t lowerBits = k.lower;
        std::memcpy(&immediate, &lowerBits, sizeof(immediate));
        m_state.i = normalizeOperand(immediate);
    }
    else if constexpr (k.upperVfShadowReg != 0u)
    {
        constexpr uint32_t sh = k.upperVfShadowReg;
        float oldVf[4];
        float upperVf[4];
        std::memcpy(oldVf, m_state.vf[sh], sizeof(oldVf));
        upperT<k.upper, DeadFlags>();
        std::memcpy(upperVf, m_state.vf[sh], sizeof(upperVf));
        std::memcpy(m_state.vf[sh], oldVf, sizeof(oldVf));
        lowerT<k.lower>(context, k.upper);
        std::memcpy(m_state.vf[sh], upperVf, sizeof(upperVf));
    }
    else
    {
        upperT<k.upper, DeadFlags>();
        if constexpr (!lowerNop)
            lowerT<k.lower>(context, k.upper);
    }

    if constexpr (vu1c::clearBranchBackup<T>())
        m_viBranchBackupValid = false;
    if constexpr (writtenVi != 0u)
        m_state.vi[writtenVi] = static_cast<int16_t>(m_state.vi[writtenVi]);

    // markPairWrites con constantes.
    {
        constexpr VfAccess lowerWrite = k.lowerUsage.vfWrite;
        if constexpr (lowerWrite.reg != 0u && k.suppressedLowerVf != lowerWrite.reg)
        {
            constexpr uint32_t latency = k.lowerUsage.vfLatency != 0u ? k.lowerUsage.vfLatency : k.lowerUsage.latency;
            if constexpr ((lowerWrite.lanes & 8u) != 0u) m_vfReady[lowerWrite.reg][0] = m_cycle + latency;
            if constexpr ((lowerWrite.lanes & 4u) != 0u) m_vfReady[lowerWrite.reg][1] = m_cycle + latency;
            if constexpr ((lowerWrite.lanes & 2u) != 0u) m_vfReady[lowerWrite.reg][2] = m_cycle + latency;
            if constexpr ((lowerWrite.lanes & 1u) != 0u) m_vfReady[lowerWrite.reg][3] = m_cycle + latency;
        }
        constexpr VfAccess upperWrite = k.upperUsage.vfWrite;
        if constexpr (upperWrite.reg != 0u)
        {
            constexpr uint32_t latency = k.upperUsage.vfLatency != 0u ? k.upperUsage.vfLatency : k.upperUsage.latency;
            if constexpr ((upperWrite.lanes & 8u) != 0u) m_vfReady[upperWrite.reg][0] = m_cycle + latency;
            if constexpr ((upperWrite.lanes & 4u) != 0u) m_vfReady[upperWrite.reg][1] = m_cycle + latency;
            if constexpr ((upperWrite.lanes & 2u) != 0u) m_vfReady[upperWrite.reg][2] = m_cycle + latency;
            if constexpr ((upperWrite.lanes & 1u) != 0u) m_vfReady[upperWrite.reg][3] = m_cycle + latency;
        }
        if constexpr (viWrites != 0u)
        {
            constexpr uint32_t latency = k.lowerUsage.viLatency != 0u ? k.lowerUsage.viLatency : k.lowerUsage.latency;
            for (uint32_t pending = viWrites; pending != 0u; pending &= pending - 1u)
                m_viReady[std::countr_zero(pending)] = m_cycle + latency;
        }
        constexpr uint32_t accWrite = k.upperUsage.accWrite;
        if constexpr ((accWrite & 8u) != 0u) m_accReady[0] = m_cycle + kAccForwardLatency;
        if constexpr ((accWrite & 4u) != 0u) m_accReady[1] = m_cycle + kAccForwardLatency;
        if constexpr ((accWrite & 2u) != 0u) m_accReady[2] = m_cycle + kAccForwardLatency;
        if constexpr ((accWrite & 1u) != 0u) m_accReady[3] = m_cycle + kAccForwardLatency;
    }
    if constexpr (writtenVi != 0u && k.lowerUsage.delaysNextBranchRead)
    {
        // GOW-Port: recordViWriteForBranch en línea (era una llamada en cada par que escribe un VI).
        m_viBranchBackupValue = oldVi;
        m_viBranchBackupReg = static_cast<uint8_t>(writtenVi);
        m_viBranchBackupValid = true;
    }

    // GOW-Port: como stepPair, siempre. addVfWrite no registra escrituras a VF0 (la condición anterior, por
    // vfWrite.reg == 0, nunca se cumplía) y execUpper/execLower escriben VF0/VI0 sin comprobarlo: en una
    // racha de pares compilados VF0/VI0 quedaban con basura (VI0 es la base de casi todos los LQ/SQ).
    // Un solo store de 16 bytes: la lectura de 16 bytes de VF0 en el par siguiente no puede reenviarse desde
    // cuatro stores de 4 bytes.
    // GOW-Port (KIexster, vu1-static-stores): solo si el par puede haber escrito VF0 o VI0 (las inferiores en
    // línea nunca escriben VI0).
    constexpr bool mayWriteVf0 = vu1c::upperMayWriteVf0(k.upper) ||
                                 (!k.iBit && (!vu1c::lowerInline(k.lower) || vu1c::lowerInlineWritesVf0(k.lower)));
    constexpr bool mayWriteVi0 = !k.iBit && !vu1c::lowerInline(k.lower);
    if constexpr (mayWriteVf0)
        vu1StoreVf0(m_state.vf[0]);
    if constexpr (mayWriteVi0)
        m_state.vi[0] = 0;

    uint32_t nextPc = m_state.pc + 8u;
    if (nextPc >= context.codeSize)
        nextPc = 0u;
    m_state.pc = nextPc;

    if constexpr (!Plain)
    {
        if (m_state.branchPending)
        {
            if (m_state.branchDelay == 0u)
            {
                m_state.pc = m_state.branchTarget & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
                m_state.branchPending = false;
            }
            else
            {
                --m_state.branchDelay;
            }
        }

        const bool dHalt = k.dBit && m_state.dBitEnabled;
        const bool tHalt = k.tBit && m_state.tBitEnabled;
        const bool haltBit = dHalt || tHalt;
        const bool haltBranch = haltBit && k.lowerUsage.pipeline == PipelineBranch;

        if (m_state.haltAfterDelaySlot)
        {
            m_state.stoppedByD = m_pendingHaltD;
            m_state.stoppedByT = m_pendingHaltT;
            context.programEnded = true;
        }
        else if (m_state.ebit)
            context.programEnded = true;
        else if (haltBit && !haltBranch)
        {
            m_state.stoppedByD = dHalt;
            m_state.stoppedByT = tHalt;
            context.programEnded = true;
        }
        else if (k.eBit)
            m_state.ebit = true;
        else if (haltBranch)
        {
            m_state.haltAfterDelaySlot = true;
            m_pendingHaltD = dHalt;
            m_pendingHaltT = tHalt;
        }
    }

    // advanceOneCycle con las comprobaciones en línea.
    ++m_cycle;
    // GOW-Port: m_state.cycles lo fija run() al terminar; nada lo lee durante la ejecución.
    if (m_cycle >= m_nextCommitCycle)
        commitReadyPipelines();
    if (m_cycle >= m_xgkickEvent)
        xgkickAdvanceTo(m_cycle); // GOW-Port: PATH1 solo en sus eventos
    return !context.programEnded;
}

// Acceso del código generado (repartido en varios archivos) a lo que necesita del intérprete.
// GOW-Port: versión de la micromemoria para el despachador compilado (definida en ps2_vu1_core.cpp).
extern std::atomic<uint64_t> g_vu1CompiledEpoch;

struct VU1CompiledAccess
{
    using P = VU1Interpreter::DecodedInstructionPair;
    using C = VU1Interpreter::StepContext;
    using Pipeline = VU1Interpreter::Pipeline;
    template <class T, bool DeadFlags, bool Plain = false, bool Chained = false>
    static VU1_STEP_INLINE bool step(VU1Interpreter &vu, C &c) { return vu.stepPairT<T, DeadFlags, Plain, Chained>(c); }
    static bool interpret(VU1Interpreter &vu, C &c) { return vu.stepInterpreted(c); }
    static uint32_t pc(const VU1Interpreter &vu) { return vu.m_state.pc; }
    static bool block(const VU1Interpreter &vu, C &c, uint32_t pc, const uint32_t *words, size_t bytes)
    {
        return vu.blockPreconditions(c, pc, words, bytes);
    }
    // GOW-Port: blockPreconditions sin comparar las palabras; el despachador generado ya comprobó que
    // coinciden con la micromemoria en esta versión (epoch).
    static VU1_STEP_INLINE bool blockReady(const VU1Interpreter &vu, C &c, uint32_t pc, size_t bytes)
    {
        if (vu.m_state.branchPending || vu.m_state.ebit || vu.m_state.haltAfterDelaySlot || vu.m_stopRequested)
            return false;
        const uint64_t maxBlockCycles = (bytes / 8u) * 4u + 64u;
        return vu.m_cycle + maxBlockCycles < c.budgetEnd && pc + bytes <= c.codeSize;
    }
    // GOW-Port: cambia cuando puede haber cambiado la micromemoria (compiledProgramFor: nueva versión o
    // nuevo intérprete); invalida las resoluciones del despachador generado.
    static uint64_t epoch() { return g_vu1CompiledEpoch.load(std::memory_order_relaxed); }

    // GOW-Port: bloques con tiempos estáticos (etapa 1 del recompilador de VU1). El generador calcula, para cada
    // par del bloque, el ciclo en que se emite (Issue, relativo al ciclo de entrada E) con las mismas reglas que
    // readyCycleT: latencias de VF/VI/ACC y de FDIV escritas dentro del bloque. El bloque solo entra por aquí si
    // lo que lee de fuera (registros escritos antes del bloque y el FDIV pendiente) ya está listo en el ciclo en
    // que lo leería (guardas generadas); entonces cada par se emite en E + Issue, igual que en el modelo
    // dinámico. Sin la carga de m_cycle y de los ciclos "listo" en cada par: estos se escriben al salir
    // (flushS), con el mismo valor que habría dejado markPairWrites.
    static VU1_STEP_INLINE uint64_t cycle(const VU1Interpreter &vu) { return vu.m_cycle; }
    static VU1_STEP_INLINE uint64_t vfReadyAt(const VU1Interpreter &vu, uint32_t reg, uint32_t lane) { return vu.m_vfReady[reg][lane]; }
    static VU1_STEP_INLINE uint64_t viReadyAt(const VU1Interpreter &vu, uint32_t reg) { return vu.m_viReady[reg]; }
    static VU1_STEP_INLINE uint64_t accReadyAt(const VU1Interpreter &vu, uint32_t lane) { return vu.m_accReady[lane]; }
    static VU1_STEP_INLINE uint64_t fdivReadyCycle(const VU1Interpreter &vu) { return vu.m_fdiv.valid ? vu.m_fdiv.readyCycle : 0u; }
    // Espera del primer par antes de entrar en el bloque estático: lo mismo que stepPairT (comprobación de
    // confirmaciones en el ciclo de entrada y advanceTo hasta el ciclo listo).
    [[gnu::noinline]] static void stallTo(VU1Interpreter &vu, C &, uint64_t target)
    {
        if (vu.m_cycle >= vu.m_nextCommitCycle)
            vu.commitReadyPipelines();
        vu.advanceTo(target);
    }
    static VU1_STEP_INLINE bool fdivReadyBy(const VU1Interpreter &vu, uint64_t limit)
    {
        return !vu.m_fdiv.valid || vu.m_fdiv.readyCycle <= limit;
    }
    // Escrituras de los "listo" del bloque: {par, tipo (0 VF, 1 VI, 2 ACC), registro, componente, desplazamiento}.
    // Se aplican en orden las de los pares < limit (la última de cada hueco gana, como en markPairWrites).
    // Salidas normales: el generador escribe en línea solo el último valor de cada hueco (setReady*); flushS
    // queda para las salidas a mitad de bloque (raras).
    static VU1_STEP_INLINE void setVfReadyAt(VU1Interpreter &vu, uint32_t reg, uint32_t lane, uint64_t v) { vu.m_vfReady[reg][lane] = v; }
    // GOW-Port: los cuatro componentes de un VF a la vez (un store / una comparación de 32 bytes).
    static VU1_STEP_INLINE void setVfReady4(VU1Interpreter &vu, uint32_t reg, uint64_t v)
    {
#if defined(__AVX2__)
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(vu.m_vfReady[reg].data()), _mm256_set1_epi64x(static_cast<long long>(v)));
#else
        vu.m_vfReady[reg] = {v, v, v, v};
#endif
    }
    static VU1_STEP_INLINE bool vfReady4After(const VU1Interpreter &vu, uint32_t reg, uint64_t limit)
    {
#if defined(__AVX2__)
        // Los ciclos caben de sobra en 63 bits: la comparación con signo vale.
        const __m256i r = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(vu.m_vfReady[reg].data()));
        return _mm256_movemask_epi8(_mm256_cmpgt_epi64(r, _mm256_set1_epi64x(static_cast<long long>(limit)))) != 0;
#else
        const auto &r = vu.m_vfReady[reg];
        return std::max(std::max(r[0], r[1]), std::max(r[2], r[3])) > limit;
#endif
    }
    static VU1_STEP_INLINE void setViReadyAt(VU1Interpreter &vu, uint32_t reg, uint64_t v) { vu.m_viReady[reg] = v; }
    static VU1_STEP_INLINE void setAccReadyAt(VU1Interpreter &vu, uint32_t lane, uint64_t v) { vu.m_accReady[lane] = v; }
    static VU1_STEP_INLINE void syncCycles(VU1Interpreter &vu) { vu.m_state.cycles = vu.m_cycle; }
    template <class Table>
    [[gnu::noinline, gnu::cold]] static void flushS(VU1Interpreter &vu, uint64_t entry, uint32_t limit)
    {
        for (uint32_t i = 0; i < Table::N; ++i)
        {
            const auto &e = Table::e[i];
            if (e[0] >= limit)
                break;
            const uint64_t value = entry + e[4];
            if (e[1] == 0u)
                vu.m_vfReady[e[2]][e[3]] = value;
            else if (e[1] == 1u)
                vu.m_viReady[e[2]] = value;
            else
                vu.m_accReady[e[3]] = value;
        }
        vu.m_state.cycles = vu.m_cycle;
    }
    // stepPairT con el ciclo de emisión estático. Devuelve 0 (sigue), 1 (parado antes de ejecutar el par) o
    // 2 (ejecutado y fin del programa).
    template <class T, bool DeadFlags, bool Plain, bool Chained, uint32_t Issue, bool Stall, uint32_t Pc, bool ClearBackup = true>
    static VU1_STEP_INLINE int stepS(VU1Interpreter &vu, C &context, uint64_t entry)
    {
        constexpr const P &k = T::value;
        // GOW-Port: par "libre de PC": intermedio (Plain) y con las dos instrucciones en línea (FMAC/especiales y
        // las inferiores de lowerInline, ninguna lee m_state.pc ni puede terminar el programa). No escribe el PC
        // (el último par del bloque nunca es Plain y lo deja bien; si se para antes de ejecutarse lo escribe la
        // salida) ni mira programEnded. ClearBackup = false: el par anterior del bloque no guardó un VI para un
        // salto (el generador lo sabe), así que m_viBranchBackupValid ya es falso.
        constexpr vu1c::UpperInfo upperInfo = vu1c::classify(k.upper);
        constexpr bool upperInline = upperInfo.kind != vu1c::Kind::Other || vu1c::simpleSpecial(k.upper) != 0u;
        constexpr bool lowerNopS = k.lower == 0x00000000u || k.lower == 0x8000033Cu;
        constexpr bool pcFree = Plain && upperInline && (k.iBit || lowerNopS || vu1c::lowerInline(k.lower));
        if constexpr (!Chained)
        {
            if (vu.m_stopRequested)
            {
                vu.m_state.pc = Pc;
                return 1;
            }
            if (vu.m_cycle >= vu.m_nextCommitCycle)
                vu.commitReadyPipelines();
        }
        else
        {
            if (vu.m_stopRequested)
            {
                vu.m_state.pc = Pc;
                return 1;
            }
        }
        if constexpr (Stall)
            vu.advanceTo(entry + Issue);
        if constexpr (!pcFree)
            vu.m_state.pc = Pc;

        constexpr uint32_t viWrites = k.lowerUsage.viWrite & 0xFFFEu;
        constexpr uint32_t writtenVi = viWrites != 0u ? static_cast<uint32_t>(std::countr_zero(viWrites)) : 0u;
        int32_t oldVi = 0;
        if constexpr (writtenVi != 0u)
            oldVi = vu.m_state.vi[writtenVi];

        constexpr bool lowerNop = k.lower == 0x00000000u || k.lower == 0x8000033Cu;
        if constexpr (k.iBit)
        {
            vu.template upperT<k.upper, DeadFlags>();
            float immediate = 0.0f;
            constexpr uint32_t lowerBits = k.lower;
            std::memcpy(&immediate, &lowerBits, sizeof(immediate));
            vu.m_state.i = vu.normalizeOperand(immediate);
        }
        else if constexpr (k.upperVfShadowReg != 0u)
        {
            constexpr uint32_t sh = k.upperVfShadowReg;
            float oldVf[4];
            float upperVf[4];
            std::memcpy(oldVf, vu.m_state.vf[sh], sizeof(oldVf));
            vu.template upperT<k.upper, DeadFlags>();
            std::memcpy(upperVf, vu.m_state.vf[sh], sizeof(upperVf));
            std::memcpy(vu.m_state.vf[sh], oldVf, sizeof(oldVf));
            vu.template lowerT<k.lower>(context, k.upper);
            std::memcpy(vu.m_state.vf[sh], upperVf, sizeof(upperVf));
        }
        else
        {
            vu.template upperT<k.upper, DeadFlags>();
            if constexpr (!lowerNop)
                vu.template lowerT<k.lower>(context, k.upper);
        }

        if constexpr (ClearBackup)
            vu.m_viBranchBackupValid = false;
        if constexpr (writtenVi != 0u)
            vu.m_state.vi[writtenVi] = static_cast<int16_t>(vu.m_state.vi[writtenVi]);
        if constexpr (writtenVi != 0u && k.lowerUsage.delaysNextBranchRead)
        {
            vu.m_viBranchBackupValue = oldVi;
            vu.m_viBranchBackupReg = static_cast<uint8_t>(writtenVi);
            vu.m_viBranchBackupValid = true;
        }

        // GOW-Port: como stepPairT, solo si el par puede haber escrito VF0 / VI0.
        constexpr bool mayWriteVf0 = vu1c::upperMayWriteVf0(k.upper) ||
                                     (!k.iBit && (!vu1c::lowerInline(k.lower) || vu1c::lowerInlineWritesVf0(k.lower)));
        constexpr bool mayWriteVi0 = !k.iBit && !vu1c::lowerInline(k.lower);
        if constexpr (mayWriteVf0)
            vu1StoreVf0(vu.m_state.vf[0]);
        if constexpr (mayWriteVi0)
            vu.m_state.vi[0] = 0;

        if constexpr (!pcFree)
            vu.m_state.pc = (Pc + 8u) & 0x3FFFu; // micromemoria de VU1: 16 KB (el código compilado solo corre ahí)

        if constexpr (!Plain)
        {
            if (vu.m_state.branchPending)
            {
                if (vu.m_state.branchDelay == 0u)
                {
                    vu.m_state.pc = vu.m_state.branchTarget & 0x3FFFu /* GOW-Port: VU1 (el código compilado solo corre en VU1) */;
                    vu.m_state.branchPending = false;
                }
                else
                {
                    --vu.m_state.branchDelay;
                }
            }

            const bool dHalt = k.dBit && vu.m_state.dBitEnabled;
            const bool tHalt = k.tBit && vu.m_state.tBitEnabled;
            const bool haltBit = dHalt || tHalt;
            const bool haltBranch = haltBit && k.lowerUsage.pipeline == VU1Interpreter::PipelineBranch;

            if (vu.m_state.haltAfterDelaySlot)
            {
                vu.m_state.stoppedByD = vu.m_pendingHaltD;
                vu.m_state.stoppedByT = vu.m_pendingHaltT;
                context.programEnded = true;
            }
            else if (vu.m_state.ebit)
                context.programEnded = true;
            else if (haltBit && !haltBranch)
            {
                vu.m_state.stoppedByD = dHalt;
                vu.m_state.stoppedByT = tHalt;
                context.programEnded = true;
            }
            else if (k.eBit)
                vu.m_state.ebit = true;
            else if (haltBranch)
            {
                vu.m_state.haltAfterDelaySlot = true;
                vu.m_pendingHaltD = dHalt;
                vu.m_pendingHaltT = tHalt;
            }
        }

        const uint64_t next = entry + Issue + 1u;
        vu.m_cycle = next;
        if (next >= vu.m_nextCommitCycle)
            vu.commitReadyPipelines();
        if (next >= vu.m_xgkickEvent)
            vu.xgkickAdvanceTo(next); // GOW-Port: PATH1 solo en sus eventos (como stepPairT)
        if constexpr (pcFree)
            return 0;
        else
            return context.programEnded ? 2 : 0;
    }
};

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif

#endif