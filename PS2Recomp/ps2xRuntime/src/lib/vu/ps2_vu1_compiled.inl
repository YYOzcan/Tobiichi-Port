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
        if (er < 2 || er > 0xFD || er < ep - 20)
            return false;
        laneFlags = (r & 0x80000000u) != 0u ? 0x2u : 0u;
        return true;
    }
}

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
    template <uint32_t Dest>
    VU1_STEP_INLINE void applyDestT(float *dst, const float *src)
    {
        if constexpr ((Dest & 8u) != 0u) dst[0] = src[0];
        if constexpr ((Dest & 4u) != 0u) dst[1] = src[1];
        if constexpr ((Dest & 2u) != 0u) dst[2] = src[2];
        if constexpr ((Dest & 1u) != 0u) dst[3] = src[3];
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
        const __m128i bits = _mm_castps_si128(v);
        const __m128i expMask = _mm_set1_epi32(0x7F800000);
        const __m128i exp = _mm_and_si128(bits, expMask);
        const __m128i sign = _mm_and_si128(bits, _mm_set1_epi32(static_cast<int>(0x80000000u)));
        __m128i r = _mm_blendv_epi8(bits, sign, _mm_cmpeq_epi32(exp, _mm_setzero_si128()));
        r = _mm_blendv_epi8(r, _mm_or_si128(sign, _mm_set1_epi32(0x7F7FFFFF)), _mm_cmpeq_epi32(exp, expMask));
        return _mm_castsi128_ps(r);
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
    constexpr uint32_t crossLeft(uint32_t c) { return c == 0 ? 1u : c == 1 ? 2u : c == 2 ? 0u : 3u; }
    constexpr uint32_t crossRight(uint32_t c) { return c == 0 ? 2u : c == 1 ? 0u : c == 2 ? 1u : 3u; }
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
    if constexpr (info.kind == vu1c::Kind::Nop)
    {
        m_currentUpperInstruction = Upper;
    }
    else if constexpr (constexpr uint32_t special = vu1c::simpleSpecial(Upper); special != 0u)
    {
        // Copia de los casos de execUpper (ps2_vu1_upper.cpp) con los campos resueltos.
        m_currentUpperInstruction = Upper;
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
            uint32_t flags = 0u;
            if (exceeds(m_state.vf[fs][0], 0x00000000u)) flags |= 0x01u;
            if (exceeds(m_state.vf[fs][0], 0x80000000u)) flags |= 0x02u;
            if (exceeds(m_state.vf[fs][1], 0x00000000u)) flags |= 0x04u;
            if (exceeds(m_state.vf[fs][1], 0x80000000u)) flags |= 0x08u;
            if (exceeds(m_state.vf[fs][2], 0x00000000u)) flags |= 0x10u;
            if (exceeds(m_state.vf[fs][2], 0x80000000u)) flags |= 0x20u;
            queueClip(flags);
        }
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
        m_currentUpperInstruction = Upper;
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
            if constexpr (info.source == vu1c::Source::Q)
                right = _mm_set1_ps(normalizeOperand(m_state.q));
            else if constexpr (info.source == vu1c::Source::I)
                right = _mm_set1_ps(normalizeOperand(m_state.i));
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
                    const __m128 acc = vu1c::normalize4(_mm_loadu_ps(m_state.acc));
                    product = _mm_mul_ps(vs, right);
                    r = info.kind == vu1c::Kind::Madd ? _mm_add_ps(acc, product) : _mm_sub_ps(acc, product);
                }
                else
                    r = _mm_mul_ps(vs, right); // Mul, Opmula
                const __m128i er = vu1c::exponent4(r);
                const __m128i absMask = _mm_set1_epi32(0x7FFFFFFF);
                // Un operando normalizado es cero: el producto exacto es cero con signo (como el redondeado).
                const __m128i opZero = _mm_or_si128(
                    _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(vs), absMask), _mm_setzero_si128()),
                    _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(right), absMask), _mm_setzero_si128()));
                __m128i ok;
                if constexpr (productSum)
                {
                    // productSumFlagsFast (exponente del resultado 2..0xFD y no mucho menor que el del producto)
                    // y productStickyFlags (exponente del producto 2..0xFD, o producto exactamente cero).
                    const __m128i ep = vu1c::exponent4(product);
                    ok = _mm_and_si128(_mm_cmpgt_epi32(er, _mm_set1_epi32(1)), _mm_cmplt_epi32(er, _mm_set1_epi32(0xFE)));
                    ok = _mm_and_si128(ok, _mm_cmpgt_epi32(er, _mm_sub_epi32(ep, _mm_set1_epi32(21))));
                    const __m128i epOk = _mm_and_si128(_mm_cmpgt_epi32(ep, _mm_set1_epi32(1)), _mm_cmplt_epi32(ep, _mm_set1_epi32(0xFE)));
                    ok = _mm_and_si128(ok, _mm_or_si128(epOk, opZero));
                    zeroProduct = _mm_movemask_ps(_mm_castsi128_ps(opZero)) & lanes;
                }
                else
                {
                    // Add, Sub, Mul: exponente del resultado 1..0xFD, o cero exacto.
                    // GOW-Port: con FTZ, r==0 tambien puede ocultar una cancelacion subnormal.
                    // Comprobar operandos opuestos/iguales conserva su flag U en el camino escalar.
                    ok = _mm_and_si128(_mm_cmpgt_epi32(er, _mm_setzero_si128()), _mm_cmplt_epi32(er, _mm_set1_epi32(0xFE)));
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
                    const int signs = _mm_movemask_ps(r) & lanes;
                    const uint32_t productSticky =
                        productSum ? ((_mm_movemask_ps(product) & lanes) != 0 ? 0x2u : 0u) | (zeroProduct != 0 ? 0x1u : 0u) : 0u;
                    if (DeadFlags && m_statusQuiet)
                        m_state.status |= ((signs != 0 ? 0x2u : 0u) | (zeroLanes != 0 ? 0x1u : 0u) | productSticky) << 6;
                    else if (m_flagCount < kMaxFlagEntries)
                    {
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
                        const auto laneFlag = [&](int bit) -> uint8_t
                        { return static_cast<uint8_t>(((signs & bit) ? 2u : 0u) | ((zeroLanes & bit) ? 1u : 0u)); };
                        const uint8_t laneFlags[4] = {laneFlag(1), laneFlag(2), laneFlag(4), laneFlag(8)};
                        updateFmacFlags(laneFlags, static_cast<uint8_t>(dest), productSticky);
                    }
                }
                float *target = info.toAcc ? m_state.acc : m_state.vf[fd];
                _mm_storeu_ps(target, _mm_blend_ps(_mm_loadu_ps(target), r, lanes));
                return;
            }
        }
#endif
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
                    updateFmacFlags(laneFlags, static_cast<uint8_t>(dest), productSticky);
            }
        }
        float *target = info.toAcc ? m_state.acc : m_state.vf[fd];
        if constexpr ((dest & 8u) != 0u) target[0] = result[0];
        if constexpr ((dest & 4u) != 0u) target[1] = result[1];
        if constexpr ((dest & 2u) != 0u) target[2] = result[2];
        if constexpr ((dest & 1u) != 0u) target[3] = result[3];
    }
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
            queueStore(addr, words, dest);
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
            queueStore(addr, words, dest);
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
    else if constexpr (opHi == 0x20u) // B
    {
        const uint32_t target = (m_state.pc + 8 + imm11 * 8) & microAddressMask();
        m_state.branchPending = true;
        m_state.branchTarget = target;
        m_state.branchDelay = 1;
    }
    else if constexpr (opHi == 0x28u || opHi == 0x29u || (opHi >= 0x2Cu && opHi <= 0x2Fu)) // IBxx
    {
        bool taken;
        if constexpr (opHi == 0x28u)
            taken = static_cast<int16_t>(readBranchVi(viS)) == static_cast<int16_t>(readBranchVi(viT));
        else if constexpr (opHi == 0x29u)
            taken = static_cast<int16_t>(readBranchVi(viS)) != static_cast<int16_t>(readBranchVi(viT));
        else if constexpr (opHi == 0x2Cu)
            taken = static_cast<int16_t>(readBranchVi(viS)) < 0;
        else if constexpr (opHi == 0x2Du)
            taken = static_cast<int16_t>(readBranchVi(viS)) > 0;
        else if constexpr (opHi == 0x2Eu)
            taken = static_cast<int16_t>(readBranchVi(viS)) <= 0;
        else
            taken = static_cast<int16_t>(readBranchVi(viS)) >= 0;
        if (taken)
        {
            const uint32_t target = (m_state.pc + 8 + imm11 * 8) & microAddressMask();
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
            queueStore(addr, words, dest);
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
        uint32_t ignoredFlags = 0u;
        result = normalizeResult(result, ignoredFlags);
        queueQ(result, 7u, statusDi);
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
        execLower(instr, vuData, dataSize, *context.gs, context.memory, upperInstr);
    }
}

// Un bloque compilado se ejecuta entero en orden: sus palabras coinciden con las de la micromemoria, no
// hay un salto ni un final de programa pendiente y queda presupuesto de ciclos de sobra (el análisis de
// vida de flags supone que se llega al final del bloque).
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

template <class T, bool DeadFlags, bool Plain>
VU1_STEP_INLINE bool VU1Interpreter::stepPairT(StepContext &context)
{
    constexpr const DecodedInstructionPair &k = T::value;

    // Igual que compiledPrologue + stepPair.
    if (m_cycle >= context.budgetEnd || m_stopRequested)
        return false;
    if (m_cycle >= m_nextCommitCycle)
        commitReadyPipelines();

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
        recordViWriteForBranch(static_cast<uint8_t>(writtenVi), oldVi);

    // GOW-Port: como stepPair, siempre. addVfWrite no registra escrituras a VF0 (la condición anterior, por
    // vfWrite.reg == 0, nunca se cumplía) y execUpper/execLower escriben VF0/VI0 sin comprobarlo: en una
    // racha de pares compilados VF0/VI0 quedaban con basura (VI0 es la base de casi todos los LQ/SQ).
    m_state.vf[0][0] = 0.0f;
    m_state.vf[0][1] = 0.0f;
    m_state.vf[0][2] = 0.0f;
    m_state.vf[0][3] = 1.0f;
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
                m_state.pc = m_state.branchTarget & microAddressMask();
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
    m_state.cycles = m_cycle;
    if (m_cycle >= m_nextCommitCycle)
        commitReadyPipelines();
    if (m_xgkick.active)
        progressXgkick();
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
    template <class T, bool DeadFlags, bool Plain = false>
    static VU1_STEP_INLINE bool step(VU1Interpreter &vu, C &c) { return vu.stepPairT<T, DeadFlags, Plain>(c); }
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
};

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif

#endif