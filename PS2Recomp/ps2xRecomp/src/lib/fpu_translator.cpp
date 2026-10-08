#include "ps2recomp/Translators/fpu_translator.h"
#include "ps2recomp/code_generator.h"
#include "ps2recomp/codegen_helpers.h"
#include "ps2recomp/instructions.h"
#include "ps2recomp/types.h"

#include <fmt/format.h>
#include <sstream>
#include <cmath>

namespace ps2recomp
{
    FpuTranslator::FpuTranslator(CodeGenerator &codeGenerator)
        : m_codeGenerator(codeGenerator)
    {
    }

    std::string FpuTranslator::translate(const Instruction &inst)
    {
        uint8_t format = inst.rs; // Format field
        uint32_t ft = inst.rt;    // FPU source register
        uint32_t fs = inst.rd;    // FPU source register
        uint32_t fd = inst.sa;    // FPU destination register
        uint32_t function = inst.function;

        switch (format)
        {
        case COP1_MF:
            return fmt::format("{{ uint32_t bits; std::memcpy(&bits, &ctx->f[{}], sizeof(bits)); SET_GPR_U32(ctx, {}, bits); }}", fs, ft);
        case COP1_MT:
            return fmt::format("{{ uint32_t bits = GPR_U32(ctx, {}); std::memcpy(&ctx->f[{}], &bits, sizeof(bits)); }}", ft, fs);
        case COP1_CF:
            if (fs == 31)
                return fmt::format("SET_GPR_U32(ctx, {}, ctx->fcr31);", ft); // FCR31 contains status/control
            if (fs == 0)
                return fmt::format("SET_GPR_U32(ctx, {}, 0x00000000);", ft); // FCR0 is the FPU implementation register
            return fmt::format("SET_GPR_U32(ctx, {}, 0); // Unimplemented FCR{}", ft, fs);
        case COP1_CT:
            if (fs == 31)
                return fmt::format("ctx->fcr31 = GPR_U32(ctx, {}) & 0x0183FFFF;", ft);
            else
                return fmt::format("// CTC1 to FCR{} ignored", fs);
            return "";
        case COP1_BC:
            return "// FPU branch instruction - handled elsewhere";
        case COP1_S:
            switch (function)
            {
            case COP1_S_ADD:
                return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_SUB:
                return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_MUL:
                return fmt::format("ctx->f[{}] = FPU_MUL_S(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_DIV:
                // GOW-Port: sin infinitos; dividir por cero da +/-FLT_MAX y pone D o I en FCR31 (fork de SotC, 8b51cb9).
                return fmt::format("ctx->f[{}] = ps2FpuDivide(ctx->fcr31, ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_SQRT:
                // GOW-Port: R5900 codifica el radicando en FT; FS no es la fuente de SQRT.S.
                return fmt::format("ctx->f[{}] = ps2FpuSqrt(ctx->fcr31, ctx->f[{}]);", fd, ft);
            case COP1_S_ABS:
                return fmt::format("ctx->f[{}] = FPU_ABS_S(ctx->f[{}]);", fd, fs);
            case COP1_S_MOV:
                return fmt::format("ctx->f[{}] = FPU_MOV_S(ctx->f[{}]);", fd, fs);
            case COP1_S_NEG:
                return fmt::format("ctx->f[{}] = FPU_NEG_S(ctx->f[{}]);", fd, fs);
            case COP1_S_ROUND_W:
                return fmt::format("{{ int32_t tmp = FPU_ROUND_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
            case COP1_S_TRUNC_W:
                return fmt::format("{{ int32_t tmp = FPU_TRUNC_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
            case COP1_S_CEIL_W:
                return fmt::format("{{ int32_t tmp = FPU_CEIL_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
            case COP1_S_FLOOR_W:
                return fmt::format("{{ int32_t tmp = FPU_FLOOR_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
            case COP1_S_CVT_W:
                return fmt::format("{{ int32_t tmp = FPU_CVT_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
            case COP1_S_RSQRT:
                // GOW-Port: RSQRT.S calcula FS/sqrt(FT), no la inversa de sqrt(FS).
                return fmt::format("ctx->f[{}] = ps2FpuRsqrt(ctx->fcr31, ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_ADDA:
                return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
            case COP1_S_SUBA:
                return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
            case COP1_S_MULA:
                return fmt::format("FPU_SET_ACC(ctx, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
            case COP1_S_MADD:
                return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
            case COP1_S_MSUB:
                return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
            case COP1_S_MADDA:
                return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
            case COP1_S_MSUBA:
                return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
            case COP1_S_MAX:
                return fmt::format("ctx->f[{}] = std::max(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_MIN:
                return fmt::format("ctx->f[{}] = std::min(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
            case COP1_S_C_F:
                return fmt::format("ctx->fcr31 &= ~0x800000;");
            case COP1_S_C_UN:
                return fmt::format("ctx->fcr31 = (FPU_C_UN_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_EQ:
                return fmt::format("ctx->fcr31 = (FPU_C_EQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_UEQ:
                return fmt::format("ctx->fcr31 = (FPU_C_UEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_OLT:
                return fmt::format("ctx->fcr31 = (FPU_C_OLT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_ULT:
                return fmt::format("ctx->fcr31 = (FPU_C_ULT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_OLE:
                return fmt::format("ctx->fcr31 = (FPU_C_OLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_ULE:
                return fmt::format("ctx->fcr31 = (FPU_C_ULE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_SF:
                return fmt::format("ctx->fcr31 &= ~0x800000;");
            case COP1_S_C_NGLE:
                return fmt::format("ctx->fcr31 = (FPU_C_NGLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_SEQ:
                return fmt::format("ctx->fcr31 = (FPU_C_SEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_NGL:
                return fmt::format("ctx->fcr31 = (FPU_C_NGL_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_LT:
                return fmt::format("ctx->fcr31 = (FPU_C_LT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_NGE:
                return fmt::format("ctx->fcr31 = (FPU_C_NGE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_LE:
                return fmt::format("ctx->fcr31 = (FPU_C_LE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            case COP1_S_C_NGT:
                return fmt::format("ctx->fcr31 = (FPU_C_NGT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
            default:
                return m_codeGenerator.emitUnhandledInstruction(inst, fmt::format("Unhandled FPU.S instruction: function 0x{:X}", function));
            }
        case COP1_W:
            switch (function)
            {
            case COP1_W_CVT_S:
                return fmt::format("{{ int32_t tmp; std::memcpy(&tmp, &ctx->f[{}], sizeof(tmp)); ctx->f[{}] = FPU_CVT_S_W(tmp); }}", fs, fd);
            default:
                return m_codeGenerator.emitUnhandledInstruction(inst, fmt::format("Unhandled FPU.W instruction: function 0x{:X}", function));
            }
        default:
            return m_codeGenerator.emitUnhandledInstruction(inst, fmt::format("Unhandled FPU instruction: format 0x{:X}, function 0x{:X}", format, function));
        }
    }

}
