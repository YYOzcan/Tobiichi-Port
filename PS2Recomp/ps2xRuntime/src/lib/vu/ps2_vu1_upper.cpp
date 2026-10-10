#include "runtime/ps2_vu1.h"
#include "ps2_vu1_detail.h"

#include <cmath>
#include <cstring>
#include <limits>
#include <immintrin.h>

namespace
{
    int32_t vuFloatToInt(float value, float scale)
    {
        const double scaled = static_cast<double>(value) * static_cast<double>(scale);
        if (scaled >= static_cast<double>(std::numeric_limits<int32_t>::max()))
            return std::numeric_limits<int32_t>::max();
        if (scaled <= static_cast<double>(std::numeric_limits<int32_t>::min()))
            return std::numeric_limits<int32_t>::min();
        return static_cast<int32_t>(scaled);
    }
    static inline __m128 normalizeSimd(__m128 v)
    {
        const __m128i expMask = _mm_set1_epi32(0x7F800000);
        const __m128i signMask = _mm_set1_epi32(static_cast<int32_t>(0x80000000u));
        const __m128i maxFloat = _mm_set1_epi32(0x7F7FFFFF);

        __m128i vi = _mm_castps_si128(v);
        __m128i exp = _mm_and_si128(vi, expMask);
        __m128i is_denorm = _mm_cmpeq_epi32(exp, _mm_setzero_si128());
        __m128i is_nan_inf = _mm_cmpeq_epi32(exp, expMask);

        __m128i signs = _mm_and_si128(vi, signMask);
        __m128i nan_clamped = _mm_or_si128(signs, maxFloat);

        __m128i res = _mm_blendv_epi8(vi, signs, is_denorm);
        res = _mm_blendv_epi8(res, nan_clamped, is_nan_inf);
        return _mm_castsi128_ps(res);
    }
}

// ============================================================================
// Upper instructions (FMAC pipeline)
// ============================================================================
void VU1Interpreter::execUpper(uint32_t instr)
{
    m_currentUpperInstruction = instr;
    if (__builtin_expect(instr == 0u, 0))
        return;

    const uint8_t op = instr & 0x3Fu;
    const uint8_t dest = DEST(instr);

    if (op >= 0x3Cu)
    {
        const uint8_t specialOp = static_cast<uint8_t>((instr & 0x3u) | ((instr >> 4) & 0x7Cu));
        if (specialOp == 0x2Fu || specialOp == 0x30u)
            return; // NOP
        if (dest == 0u && specialOp != 0x1Fu)
            return; // dest == 0 and not CLIP
    }
    else if (dest == 0u)
    {
        return;
    }

    const uint8_t ft = FT(instr);
    const uint8_t fs = FS(instr);
    const uint8_t fd = FD(instr);

    float *vd = m_state.vf[fd];
    const __m128 v_vs = normalizeSimd(_mm_loadu_ps(m_state.vf[fs]));
    const __m128 v_vt = normalizeSimd(_mm_loadu_ps(m_state.vf[ft]));
    alignas(16) float vs[4];
    alignas(16) float vt[4];
    _mm_store_ps(vs, v_vs);
    _mm_store_ps(vt, v_vt);

    const auto getAcc = [this]() -> __m128 {
        return normalizeSimd(_mm_loadu_ps(m_state.acc));
    };
    const auto getQ = [this]() -> float {
        return normalizeOperand(m_state.q);
    };
    const auto getI = [this]() -> float {
        return normalizeOperand(m_state.i);
    };
    float result[4];

    // Upper opcode decoding (bits 5:0 of upper word)
    switch (op)
    {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03: // ADDbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(bc)));
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07: // SUBbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(bc)));
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B: // MADDbc
    {
        // GOW-Port: sin FMA; la FMAC de la PS2 redondea el producto y luego la suma (igual que MSUB).
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(bc))));
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x0C:
    case 0x0D:
    case 0x0E:
    case 0x0F: // MSUBbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(bc))));
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13: // MAXbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_max_ps(v_vs, _mm_set1_ps(bc)));
        applyDest(vd, result, dest);
        return;
    }
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17: // MINIbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_min_ps(v_vs, _mm_set1_ps(bc)));
        applyDest(vd, result, dest);
        return;
    }
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B: // MULbc
    {
        const float bc = vt[op & 3];
        _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(bc)));
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x1C: // MULq
        _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(getQ())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x1D: // MAXi
        _mm_storeu_ps(result, _mm_max_ps(v_vs, _mm_set1_ps(getI())));
        applyDest(vd, result, dest);
        return;
    case 0x1E: // MULi
        _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(getI())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x1F: // MINIi
        _mm_storeu_ps(result, _mm_min_ps(v_vs, _mm_set1_ps(getI())));
        applyDest(vd, result, dest);
        return;
    case 0x20: // ADDq
        _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(getQ())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x21: // MADDq
        _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getQ()))));
        applyFmacDest(vd, result, dest);
        return;
    case 0x22: // ADDi
        _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(getI())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x23: // MADDi
        _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getI()))));
        applyFmacDest(vd, result, dest);
        return;
    case 0x24: // SUBq
        _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(getQ())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x25: // MSUBq
        _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getQ()))));
        applyFmacDest(vd, result, dest);
        return;
    case 0x26: // SUBi
        _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(getI())));
        applyFmacDest(vd, result, dest);
        return;
    case 0x27: // MSUBi
        _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getI()))));
        applyFmacDest(vd, result, dest);
        return;
    case 0x28: // ADD
        _mm_storeu_ps(result, _mm_add_ps(v_vs, v_vt));
        applyFmacDest(vd, result, dest);
        return;
    case 0x29: // MADD
        _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, v_vt)));
        applyFmacDest(vd, result, dest);
        return;
    case 0x2A: // MUL
        _mm_storeu_ps(result, _mm_mul_ps(v_vs, v_vt));
        applyFmacDest(vd, result, dest);
        return;
    case 0x2B: // MAX
        _mm_storeu_ps(result, _mm_max_ps(v_vs, v_vt));
        applyDest(vd, result, dest);
        return;
    case 0x2C: // SUB
        _mm_storeu_ps(result, _mm_sub_ps(v_vs, v_vt));
        applyFmacDest(vd, result, dest);
        return;
    case 0x2D: // MSUB
        _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, v_vt)));
        applyFmacDest(vd, result, dest);
        return;
    case 0x2E: // OPMSUB
    {
        alignas(16) float accArr[4];
        _mm_store_ps(accArr, getAcc());
        result[0] = accArr[0] - vs[1] * vt[2];
        result[1] = accArr[1] - vs[2] * vt[0];
        result[2] = accArr[2] - vs[0] * vt[1];
        result[3] = 0.0f;
        applyFmacDest(vd, result, dest);
        return;
    }
    case 0x2F: // MINI
        _mm_storeu_ps(result, _mm_min_ps(v_vs, v_vt));
        applyDest(vd, result, dest);
        return;

    // Upper special group (low op 0x3C..0x3F).
    // Like lower1 special, the real selector is not just bits 5:0.  Dobie decodes:
    //   op = (instr & 0x3) | ((instr >> 4) & 0x7C)
    // Several instructions in this group also use FT as the destination, not FD.
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    {
        const uint8_t specialOp = static_cast<uint8_t>((instr & 0x3u) | ((instr >> 4) & 0x7Cu));
        float *vtDest = m_state.vf[ft];

        switch (specialOp)
        {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03: // ADDAbc
        {
            const float bc = vt[specialOp & 3];
            _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(bc)));
            applyFmacDestAcc(result, dest);
            return;
        }
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07: // SUBAbc
        {
            const float bc = vt[specialOp & 3];
            _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(bc)));
            applyFmacDestAcc(result, dest);
            return;
        }
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B: // MADDAbc
        {
            const float bc = vt[specialOp & 3];
            _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(bc))));
            applyFmacDestAcc(result, dest);
            return;
        }
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F: // MSUBAbc
        {
            const float bc = vt[specialOp & 3];
            _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(bc))));
            applyFmacDestAcc(result, dest);
            return;
        }
        case 0x10: // ITOF0
        {
            __m128i iv = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_state.vf[fs]));
            _mm_storeu_ps(result, _mm_cvtepi32_ps(iv));
            applyDest(vtDest, result, dest);
            return;
        }
        case 0x11: // ITOF4
        {
            __m128i iv = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_state.vf[fs]));
            _mm_storeu_ps(result, _mm_mul_ps(_mm_cvtepi32_ps(iv), _mm_set1_ps(1.0f / 16.0f)));
            applyDest(vtDest, result, dest);
            return;
        }
        case 0x12: // ITOF12
        {
            __m128i iv = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_state.vf[fs]));
            _mm_storeu_ps(result, _mm_mul_ps(_mm_cvtepi32_ps(iv), _mm_set1_ps(1.0f / 4096.0f)));
            applyDest(vtDest, result, dest);
            return;
        }
        case 0x13: // ITOF15
        {
            __m128i iv = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_state.vf[fs]));
            _mm_storeu_ps(result, _mm_mul_ps(_mm_cvtepi32_ps(iv), _mm_set1_ps(1.0f / 32768.0f)));
            applyDest(vtDest, result, dest);
            return;
        }
        case 0x14: // FTOI0
            for (int c = 0; c < 4; c++)
            {
                int32_t iv = vuFloatToInt(vs[c], 1.0f);
                std::memcpy(&result[c], &iv, 4);
            }
            applyDest(vtDest, result, dest);
            return;
        case 0x15: // FTOI4
            for (int c = 0; c < 4; c++)
            {
                int32_t iv = vuFloatToInt(vs[c], 16.0f);
                std::memcpy(&result[c], &iv, 4);
            }
            applyDest(vtDest, result, dest);
            return;
        case 0x16: // FTOI12
            for (int c = 0; c < 4; c++)
            {
                int32_t iv = vuFloatToInt(vs[c], 4096.0f);
                std::memcpy(&result[c], &iv, 4);
            }
            applyDest(vtDest, result, dest);
            return;
        case 0x17: // FTOI15
            for (int c = 0; c < 4; c++)
            {
                int32_t iv = vuFloatToInt(vs[c], 32768.0f);
                std::memcpy(&result[c], &iv, 4);
            }
            applyDest(vtDest, result, dest);
            return;
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B: // MULAbc
        {
            const float bc = vt[specialOp & 3];
            _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(bc)));
            applyFmacDestAcc(result, dest);
            return;
        }
        case 0x1C: // MULAq
            _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(getQ())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x1D: // ABS
            _mm_storeu_ps(result, _mm_andnot_ps(_mm_set1_ps(-0.0f), v_vs));
            applyDest(vtDest, result, dest);
            return;
        case 0x1E: // MULAi
            _mm_storeu_ps(result, _mm_mul_ps(v_vs, _mm_set1_ps(getI())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x1F: // CLIP
        {
            uint32_t wBits = 0u;
            std::memcpy(&wBits, &m_state.vf[ft][3], sizeof(wBits));
            const int32_t limit = (wBits & 0x7F800000u) != 0u ? static_cast<int32_t>(wBits & 0x7FFFFFFFu) : 0x007FFFFF;

            const auto exceedsClipPlane = [limit](float value, uint32_t signMask)
            {
                uint32_t bits = 0u;
                std::memcpy(&bits, &value, sizeof(bits));
                bits ^= signMask;
                int32_t orderedBits = 0;
                std::memcpy(&orderedBits, &bits, sizeof(orderedBits));
                return orderedBits > limit;
            };

            uint32_t flags = 0u;
            if (exceedsClipPlane(m_state.vf[fs][0], 0x00000000u))
                flags |= 0x01u;
            if (exceedsClipPlane(m_state.vf[fs][0], 0x80000000u))
                flags |= 0x02u;
            if (exceedsClipPlane(m_state.vf[fs][1], 0x00000000u))
                flags |= 0x04u;
            if (exceedsClipPlane(m_state.vf[fs][1], 0x80000000u))
                flags |= 0x08u;
            if (exceedsClipPlane(m_state.vf[fs][2], 0x00000000u))
                flags |= 0x10u;
            if (exceedsClipPlane(m_state.vf[fs][2], 0x80000000u))
                flags |= 0x20u;
            queueClip(flags);
            return;
        }
        case 0x20: // ADDAq
            _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(getQ())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x21: // MADDAq
            _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getQ()))));
            applyFmacDestAcc(result, dest);
            return;
        case 0x22: // ADDAi
            _mm_storeu_ps(result, _mm_add_ps(v_vs, _mm_set1_ps(getI())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x23: // MADDAi
            _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getI()))));
            applyFmacDestAcc(result, dest);
            return;
        case 0x24: // SUBAq
            _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(getQ())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x25: // MSUBAq
            _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getQ()))));
            applyFmacDestAcc(result, dest);
            return;
        case 0x26: // SUBAi
            _mm_storeu_ps(result, _mm_sub_ps(v_vs, _mm_set1_ps(getI())));
            applyFmacDestAcc(result, dest);
            return;
        case 0x27: // MSUBAi
            _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, _mm_set1_ps(getI()))));
            applyFmacDestAcc(result, dest);
            return;
        case 0x28: // ADDA
            _mm_storeu_ps(result, _mm_add_ps(v_vs, v_vt));
            applyFmacDestAcc(result, dest);
            return;
        case 0x29: // MADDA
            _mm_storeu_ps(result, _mm_add_ps(getAcc(), _mm_mul_ps(v_vs, v_vt)));
            applyFmacDestAcc(result, dest);
            return;
        case 0x2A: // MULA
            _mm_storeu_ps(result, _mm_mul_ps(v_vs, v_vt));
            applyFmacDestAcc(result, dest);
            return;
        case 0x2C: // SUBA
            _mm_storeu_ps(result, _mm_sub_ps(v_vs, v_vt));
            applyFmacDestAcc(result, dest);
            return;
        case 0x2D: // MSUBA
            _mm_storeu_ps(result, _mm_sub_ps(getAcc(), _mm_mul_ps(v_vs, v_vt)));
            applyFmacDestAcc(result, dest);
            return;
        case 0x2E: // OPMULA
            result[0] = vs[1] * vt[2];
            result[1] = vs[2] * vt[0];
            result[2] = vs[0] * vt[1];
            result[3] = 0.0f;
            applyFmacDestAcc(result, dest);
            return;
        case 0x2F:
        case 0x30: // NOP
            return;
        default:
            reportReservedInstruction(true, instr);
            return;
        }
    }

    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    default:
        reportReservedInstruction(true, instr);
        return;
    }
}
