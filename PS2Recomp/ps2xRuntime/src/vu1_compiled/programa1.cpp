// Generado por tools/vu1/generar_vu1.cpp a partir del microcódigo del juego. No publicar.
#include "runtime/ps2_vu1.h"
#include "ps2_vu1_compiled.inl"
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Mismo modo de coma flotante que el intérprete de VU (MSVC no expande en línea entre modos distintos).
#if defined(_MSC_VER)
#pragma float_control(precise, on, push)
#pragma fp_contract(off)
#endif

using P = VU1CompiledAccess::P;
using C = VU1CompiledAccess::C;

namespace vu1c_gen
{
    struct Kp0000_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0000_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0000_0, false>(vu, c);
    }
    struct Kp0060_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0060_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0060_0, false>(vu, c);
    }
    struct Kp00C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00C0_0, false>(vu, c);
    }
    struct Kp0120_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12026801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0120_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0120_0, false>(vu, c);
    }
    struct Kp0180_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12830010u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0180_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0180_0, false>(vu, c);
    }
    struct Kp01E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01E0_0, false>(vu, c);
    }
    struct Kp0240_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e240bfu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0240_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0240_0, false>(vu, c);
    }
    struct Kp02A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30043000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02A0_0, false>(vu, c);
    }
    struct Kp0300_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0300_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0300_0, false>(vu, c);
    }
    struct Kp0360_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0360_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0360_0, false>(vu, c);
    }
    struct Kp03C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c0a73fu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {20, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 24; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03C0_0, false>(vu, c);
    }
    struct Kp0420_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50000000u; p.upper = 0x8021093cu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0420_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0420_0, false>(vu, c);
    }
    struct Kp0480_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80031af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0480_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0480_0, false>(vu, c);
    }
    struct Kp04E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f79eu; p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfWrite = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E0_0, false>(vu, c);
    }
    struct Kp0540_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8121233du; p.upper = 0x18422beu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfWrite = {1, 9}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {4, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0540_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0540_0, false>(vu, c);
    }
    struct Kp05A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cbef47u; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {11, 1}; p.upperUsage.vfWrite = {29, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05A0_0, false>(vu, c);
    }
    struct Kp0600_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea296au; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0600_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0600_0, false>(vu, c);
    }
    struct Kp0660_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0660_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0660_0, false>(vu, c);
    }
    struct Kp06C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec5052u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {10, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06C0_0, false>(vu, c);
    }
    struct Kp0720_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58002955u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0720_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0720_0, false>(vu, c);
    }
    struct Kp0780_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022033cu; p.upper = 0x1c118eau; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0780_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0780_0, false>(vu, c);
    }
    struct Kp07E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x1f715ceu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {23, 2}; p.upperUsage.vfWrite = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07E0_0, false>(vu, c);
    }
    struct Kp0840_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef13ceu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0840_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0840_0, false>(vu, c);
    }
    struct Kp08A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08A0_0, false>(vu, c);
    }
    struct Kp0900_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12063001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0900_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0900_0, false>(vu, c);
    }
    struct Kp0960_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000803u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0960_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0960_0, false>(vu, c);
    }
    struct Kp09C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8426045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C0_0, false>(vu, c);
    }
    struct Kp0A20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10040000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A20_0, false>(vu, c);
    }
    struct Kp0A80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A80_0, false>(vu, c);
    }
    struct Kp0AE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AE0_0, false>(vu, c);
    }
    struct Kp0B40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e16800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B40_0, false>(vu, c);
    }
    struct Kp0BA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BA0_0, false>(vu, c);
    }
    struct Kp0C00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C00_0, false>(vu, c);
    }
    struct Kp0C60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c18f0u; p.upper = 0x1dff93du; p.lowerUsage.viRead = 4104; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 14}; p.upperUsage.vfWrite = {31, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C60_0, false>(vu, c);
    }
    struct Kp0CC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4004acu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {18, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC0_0, false>(vu, c);
    }
    struct Kp0D20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x197ecedu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D20_0, false>(vu, c);
    }
    struct Kp0D80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a4234u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1280; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D80_0, false>(vu, c);
    }
    struct Kp0DE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80014235u; p.upper = 0x2ffu; p.lowerUsage.viRead = 258; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DE0_0, false>(vu, c);
    }
    struct Kp0E40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f45810u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {20, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E40_0, false>(vu, c);
    }
    struct Kp0EA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13eb0fffu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EA0_0, false>(vu, c);
    }
    struct Kp0F00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b1feu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F00_0, false>(vu, c);
    }
    struct Kp0F60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f521bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {21, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F60_0, false>(vu, c);
    }
    struct Kp0FC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC0_0, false>(vu, c);
    }
    struct Kp1020_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a6e58u; p.upperUsage.vfRead[0] = {13, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {25, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1020_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1020_0, false>(vu, c);
    }
    struct Kp1080_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x1f61abeu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1080_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1080_0, false>(vu, c);
    }
    struct Kp10E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {14, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10E0_0, false>(vu, c);
    }
    struct Kp1140_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58002891u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1140_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1140_0, false>(vu, c);
    }
    struct Kp11A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9096800u; p.upper = 0x1f61abeu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A0_0, false>(vu, c);
    }
    struct Kp1200_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x2ffu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1200_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1200_0, false>(vu, c);
    }
    struct Kp1260_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1260_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1260_0, false>(vu, c);
    }
    struct Kp12C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10850000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C0_0, false>(vu, c);
    }
    struct Kp1320_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1320_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1320_0, false>(vu, c);
    }
    struct Kp1380_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10070004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1380_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1380_0, false>(vu, c);
    }
    struct Kp13E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84d6045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13E0_0, false>(vu, c);
    }
    struct Kp1440_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1440_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1440_0, false>(vu, c);
    }
    struct Kp14A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb017000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16386; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A0_0, false>(vu, c);
    }
    struct Kp1500_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1500_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1500_0, false>(vu, c);
    }
    struct Kp1560_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000037u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1560_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1560_0, false>(vu, c);
    }
    struct Kp15C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007a6u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C0_0, false>(vu, c);
    }
    struct Kp1620_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e507ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1620_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1620_0, false>(vu, c);
    }
    struct Kp1680_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1680_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1680_0, false>(vu, c);
    }
    struct Kp16E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802613fcu; p.upper = 0x1800ddeu; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {23, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16E0_0, false>(vu, c);
    }
    struct Kp1740_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x56003fu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1740_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1740_0, false>(vu, c);
    }
    struct Kp17A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x810153fdu; p.upper = 0x1cf91ffu; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {18, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17A0_0, false>(vu, c);
    }
    struct Kp1800_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10060000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1800_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1800_0, false>(vu, c);
    }
    struct Kp1860_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1860_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1860_0, false>(vu, c);
    }
    struct Kp18C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80273bfdu; p.upper = 0x900342u; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.viRead = 128; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {16, 2}; p.upperUsage.vfWrite = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18C0_0, false>(vu, c);
    }
    struct Kp1920_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806623fcu; p.upper = 0x510342u; p.lowerUsage.vfRead[0] = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {17, 2}; p.upperUsage.vfWrite = {13, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1920_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1920_0, false>(vu, c);
    }
    struct Kp1980_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10250000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1980_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1980_0, false>(vu, c);
    }
    struct Kp19E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806653fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {10, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19E0_0, false>(vu, c);
    }
    struct Kp1A40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802e13fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A40_0, false>(vu, c);
    }
    struct Kp1AA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eaaaaabu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p1AA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA0_0, false>(vu, c);
    }
    struct Kp1B00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e73fffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 128; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B00_0, false>(vu, c);
    }
    struct Kp1B60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e04acbu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B60_0, false>(vu, c);
    }
    struct Kp1BC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x88d03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BC0_0, false>(vu, c);
    }
    struct Kp1C20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500a1723u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1028; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C20_0, false>(vu, c);
    }
    struct Kp1C80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C80_0, false>(vu, c);
    }
    struct Kp1CE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8215000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CE0_0, false>(vu, c);
    }
    struct Kp1D40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8224000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D40_0, false>(vu, c);
    }
    struct Kp1DA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca0abeu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA0_0, false>(vu, c);
    }
    struct Kp1E00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3890au; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E00_0, false>(vu, c);
    }
    struct Kp1E60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80020870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E60_0, false>(vu, c);
    }
    struct Kp1EC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500f0004u; p.upper = 0x1cf11ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EC0_0, false>(vu, c);
    }
    struct Kp1F20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5275u; p.upper = 0x2ffu; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F20_0, false>(vu, c);
    }
    struct Kp1F80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f06acu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F80_0, false>(vu, c);
    }
    struct Kp1FE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FE0_0, false>(vu, c);
    }
    struct Kp2040_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2040_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2040_0, false>(vu, c);
    }
    struct Kp20A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e31800u; p.upper = 0x1c0425cu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20A0_0, false>(vu, c);
    }
    struct Kp2100_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2100_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2100_0, false>(vu, c);
    }
    struct Kp2160_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007c3u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2160_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2160_0, false>(vu, c);
    }
    struct Kp21C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32000u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C0_0, false>(vu, c);
    }
    struct Kp2220_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fau; p.upper = 0x18002fcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2220_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2220_0, false>(vu, c);
    }
    struct Kp2280_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x1c0191cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2280_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2280_0, false>(vu, c);
    }
    struct Kp22E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22E0_0, false>(vu, c);
    }
    struct Kp2340_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1c4197du; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2340_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2340_0, false>(vu, c);
    }
    struct Kp23A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e807ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23A0_0, false>(vu, c);
    }
    struct Kp2400_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1007387fu; p.upper = 0x18b2eecu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {11, 12}; p.upperUsage.vfWrite = {27, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2400_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2400_0, false>(vu, c);
    }
    struct Kp2460_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x11cd9bdu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 8}; p.upperUsage.vfRead[1] = {28, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2460_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2460_0, false>(vu, c);
    }
    struct Kp24C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80610bfcu; p.upper = 0x1802ac0u; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {11, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C0_0, false>(vu, c);
    }
    struct Kp2520_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed529bu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2520_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2520_0, false>(vu, c);
    }
    struct Kp2580_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80012974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2580_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2580_0, false>(vu, c);
    }
    struct Kp25E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25E0_0, false>(vu, c);
    }
    struct Kp2640_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0683cu; p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2640_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2640_0, false>(vu, c);
    }
    struct Kp26A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26A0_0, false>(vu, c);
    }
    struct Kp2700_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2700_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2700_0, false>(vu, c);
    }
    struct Kp2760_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b000001u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p2760_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2760_0, false>(vu, c);
    }
    struct Kp27C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80600c3eu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27C0_0, false>(vu, c);
    }
    struct Kp2820_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81cb037du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2820_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2820_0, false>(vu, c);
    }
    struct Kp2880_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0429cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_0, false>(vu, c);
    }
    struct Kp28E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_0, false>(vu, c);
    }
    struct Kp2940_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p2940_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_0, false>(vu, c);
    }
    struct Kp29A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A0_0, false>(vu, c);
    }
    struct Kp2A00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A00_0, false>(vu, c);
    }
    struct Kp2A60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A60_0, false>(vu, c);
    }
    struct Kp2AC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AC0_0, false>(vu, c);
    }
    struct Kp2B20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B20_0, false>(vu, c);
    }
    struct Kp2B80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B80_0, false>(vu, c);
    }
    struct Kp2BE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_0, false>(vu, c);
    }
    struct Kp2C40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_0, false>(vu, c);
    }
    struct Kp2ED0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2ED0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2ED0_0, false>(vu, c);
    }
    struct Kp2F30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_0, false>(vu, c);
    }
    struct Kp2F90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_0, false>(vu, c);
    }
    struct Kp3220_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3220_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3220_0, false>(vu, c);
    }
    struct Kp3280_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_0, false>(vu, c);
    }
    struct Kp32E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E0_0, false>(vu, c);
    }
    struct Kp3340_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3340_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3340_0, false>(vu, c);
    }
    struct Kp33A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p33A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33A0_0, false>(vu, c);
    }
    struct Kp35C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_0, false>(vu, c);
    }
    struct Kp3620_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3620_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3620_0, false>(vu, c);
    }
    struct Kp3680_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3680_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_0, false>(vu, c);
    }
    struct Kp36E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E0_0, false>(vu, c);
    }
    struct Kp38E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_0, false>(vu, c);
    }
    struct Kp3940_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_0, false>(vu, c);
    }
    struct Kp39A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_0, false>(vu, c);
    }
    struct Kp3A00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A00_0, false>(vu, c);
    }
    struct Kp3A60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A60_0, false>(vu, c);
    }
    struct Kp3AC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AC0_0, false>(vu, c);
    }
    struct Kp0028_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8896015u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0028_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0028_1, false>(vu, c);
    }
    struct Kp0090_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800050b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0090_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0090_1, false>(vu, c);
    }
    struct Kp00F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e30800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00F0_1, false>(vu, c);
    }
    struct Kp0150_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c08f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0150_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0150_1, false>(vu, c);
    }
    struct Kp01B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01B8_1, false>(vu, c);
    }
    struct Kp0218_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb613eu; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0218_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0218_1, false>(vu, c);
    }
    struct Kp0278_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e118ffu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0278_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0278_1, false>(vu, c);
    }
    struct Kp02E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ec601eu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02E0_1, false>(vu, c);
    }
    struct Kp0340_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f0800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0340_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0340_1, false>(vu, c);
    }
    struct Kp03A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03A0_1, false>(vu, c);
    }
    struct Kp0400_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010006u; p.upper = 0x1ec617du; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0400_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0400_1, false>(vu, c);
    }
    struct Kp0460_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0460_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0460_1, false>(vu, c);
    }
    struct Kp04C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04C0_1, false>(vu, c);
    }
    struct Kp0520_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1e0f27fu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0520_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0520_1, false>(vu, c);
    }
    struct Kp0580_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0580_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0580_1, false>(vu, c);
    }
    struct Kp05E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff1248u; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05E0_1, false>(vu, c);
    }
    struct Kp0640_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0640_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0640_1, false>(vu, c);
    }
    struct Kp06A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06A0_1, false>(vu, c);
    }
    struct Kp0700_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0700_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0700_1, false>(vu, c);
    }
    struct Kp0760_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e4426au; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0760_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0760_1, false>(vu, c);
    }
    struct Kp07C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e438fcu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07C0_1, false>(vu, c);
    }
    struct Kp0820_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x124f98cu; p.upperUsage.vfRead[0] = {31, 9}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfWrite = {6, 9}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 9; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0820_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0820_1, false>(vu, c);
    }
    struct Kp0880_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0880_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0880_1, false>(vu, c);
    }
    struct Kp08E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08E0_1, false>(vu, c);
    }
    struct Kp0940_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0083cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0940_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0940_1, false>(vu, c);
    }
    struct Kp09A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81060b3du; p.upper = 0x634958u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfWrite = {6, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfWrite = {5, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09A0_1, false>(vu, c);
    }
    struct Kp0A08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A08_1, false>(vu, c);
    }
    struct Kp0A68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34011000u; p.upper = 0x1000169u; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A68_1, false>(vu, c);
    }
    struct Kp0AD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AD0_1, false>(vu, c);
    }
    struct Kp0B30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81050b3cu; p.upper = 0x10101c2u; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfWrite = {5, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B30_1, false>(vu, c);
    }
    struct Kp0B90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x808503bdu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B90_1, false>(vu, c);
    }
    struct Kp0BF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10930bfu; p.upperUsage.vfRead[0] = {6, 8}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BF0_1, false>(vu, c);
    }
    struct Kp0C50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2739eau; p.upperUsage.vfRead[0] = {7, 1}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C50_1, false>(vu, c);
    }
    struct Kp0CB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8208du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB0_1, false>(vu, c);
    }
    struct Kp0D10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D10_1, false>(vu, c);
    }
    struct Kp0D70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81f23b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfWrite = {18, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D70_1, false>(vu, c);
    }
    struct Kp0DD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f96001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {25, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DD0_1, false>(vu, c);
    }
    struct Kp0E30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x3b06ceu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {27, 2}; p.upperUsage.vfWrite = {27, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E30_1, false>(vu, c);
    }
    struct Kp0E90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E90_1, false>(vu, c);
    }
    struct Kp0EF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e4217cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EF0_1, false>(vu, c);
    }
    struct Kp0F50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e07d3u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F50_1, false>(vu, c);
    }
    struct Kp0FB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8105fbbcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {31, 8}; p.lowerUsage.vfRead[1] = {5, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0FB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB0_1, false>(vu, c);
    }
    struct Kp1010_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x250144u; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1010_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1010_1, false>(vu, c);
    }
    struct Kp1070_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e4e3bcu; p.upper = 0x1c018dcu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1070_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1070_1, false>(vu, c);
    }
    struct Kp10D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D0_1, false>(vu, c);
    }
    struct Kp1130_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1130_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1130_1, false>(vu, c);
    }
    struct Kp1190_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3e0e9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1190_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1190_1, false>(vu, c);
    }
    struct Kp11F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x40003fu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F0_1, false>(vu, c);
    }
    struct Kp1250_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0773u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1250_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1250_1, false>(vu, c);
    }
    struct Kp12B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B0_1, false>(vu, c);
    }
    struct Kp1310_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20089eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1310_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1310_1, false>(vu, c);
    }
    struct Kp1378_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b9007u; p.upper = 0x10798cdu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1378_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1378_1, false>(vu, c);
    }
    struct Kp13E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x40003fu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13E0_1, false>(vu, c);
    }
    struct Kp1440_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0735u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1440_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1440_1, false>(vu, c);
    }
    struct Kp14A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A0_1, false>(vu, c);
    }
    struct Kp1500_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c319ffu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1500_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1500_1, false>(vu, c);
    }
    struct Kp1560_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fc90fdbu; p.upper = 0x802701dau; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1560_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1560_1, false>(vu, c);
    }
    struct Kp15C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc2255de0u; p.upper = 0x81e0399eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C0_1, false>(vu, c);
    }
    struct Kp1620_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e23b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1620_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1620_1, false>(vu, c);
    }
    struct Kp1680_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b9007u; p.upper = 0x10798cdu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1680_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1680_1, false>(vu, c);
    }
    struct Kp16E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16E0_1, false>(vu, c);
    }
    struct Kp1740_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1740_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1740_1, false>(vu, c);
    }
    struct Kp17A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c41afeu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17A0_1, false>(vu, c);
    }
    struct Kp1800_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1800_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1800_1, false>(vu, c);
    }
    struct Kp1860_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x29024eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {9, 2}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1860_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1860_1, false>(vu, c);
    }
    struct Kp18C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10222u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18C0_1, false>(vu, c);
    }
    struct Kp1920_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8101933cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 8}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1920_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1920_1, false>(vu, c);
    }
    struct Kp1980_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1980_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1980_1, false>(vu, c);
    }
    struct Kp19E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19E0_1, false>(vu, c);
    }
    struct Kp1A40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f20802u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {18, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A40_1, false>(vu, c);
    }
    struct Kp1AA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA0_1, false>(vu, c);
    }
    struct Kp1B00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2988u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B00_1, false>(vu, c);
    }
    struct Kp1B60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x28020eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B60_1, false>(vu, c);
    }
    struct Kp1BC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5201063du; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BC0_1, false>(vu, c);
    }
    struct Kp1C20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C20_1, false>(vu, c);
    }
    struct Kp1C80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8081933cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C80_1, false>(vu, c);
    }
    struct Kp1CE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1CE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CE0_1, false>(vu, c);
    }
    struct Kp1D40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D40_1, false>(vu, c);
    }
    struct Kp1DA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1DA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA0_1, false>(vu, c);
    }
    struct Kp1E00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10035805u; p.upper = 0x1c319ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E00_1, false>(vu, c);
    }
    struct Kp1E60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E60_1, false>(vu, c);
    }
    struct Kp1EC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EC0_1, false>(vu, c);
    }
    struct Kp1F20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F20_1, false>(vu, c);
    }
    struct Kp1F80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F80_1, false>(vu, c);
    }
    struct Kp1FE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e9497cu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FE0_1, false>(vu, c);
    }
    struct Kp2040_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001003fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2040_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2040_1, false>(vu, c);
    }
    struct Kp20A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34d6bf95u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p20A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20A0_1, false>(vu, c);
    }
    struct Kp2100_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb537du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {10, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2100_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2100_1, false>(vu, c);
    }
    struct Kp2160_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1819049u; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 12}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2160_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2160_1, false>(vu, c);
    }
    struct Kp21C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eaa1bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C0_1, false>(vu, c);
    }
    struct Kp2220_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1edb34au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2220_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2220_1, false>(vu, c);
    }
    struct Kp2280_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2280_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2280_1, false>(vu, c);
    }
    struct Kp22E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c10b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4100; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22E0_1, false>(vu, c);
    }
    struct Kp2340_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2340_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2340_1, false>(vu, c);
    }
    struct Kp23A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c119ffu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23A0_1, false>(vu, c);
    }
    struct Kp2400_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e800000u; p.upper = 0x81e008ffu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2400_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2400_1, false>(vu, c);
    }
    struct Kp2460_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2460_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2460_1, false>(vu, c);
    }
    struct Kp24C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C0_1, false>(vu, c);
    }
    struct Kp2870_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e9033cu; p.upper = 0x1e00200u; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_1, false>(vu, c);
    }
    struct Kp28D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e64b3cu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfRead[0] = {9, 15}; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_1, false>(vu, c);
    }
    struct Kp2930_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a002fe9u; p.upper = 0x1e6422au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_1, false>(vu, c);
    }
    struct Kp2B90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_1, false>(vu, c);
    }
    struct Kp2BF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb2b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_1, false>(vu, c);
    }
    struct Kp2C50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C50_1, false>(vu, c);
    }
    struct Kp2CB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB0_0, false>(vu, c);
    }
    struct Kp2D10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2D10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D10_0, false>(vu, c);
    }
    struct Kp2D70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D70_0, false>(vu, c);
    }
    struct Kp2EF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e5293cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_1, false>(vu, c);
    }
    struct Kp2F50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_1, false>(vu, c);
    }
    struct Kp2FB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_1, false>(vu, c);
    }
    struct Kp3010_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3010_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3010_0, false>(vu, c);
    }
    struct Kp3070_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3070_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3070_0, false>(vu, c);
    }
    struct Kp30D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30D0_0, false>(vu, c);
    }
    struct Kp3258_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_1, false>(vu, c);
    }
    struct Kp32B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_1, false>(vu, c);
    }
    struct Kp3318_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_1, false>(vu, c);
    }
    struct Kp3378_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3378_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3378_1, false>(vu, c);
    }
    struct Kp33D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33D8_0, false>(vu, c);
    }
    struct Kp3438_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3438_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3438_0, false>(vu, c);
    }
    struct Kp35B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B8_1, false>(vu, c);
    }
    struct Kp3618_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3618_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_1, false>(vu, c);
    }
    struct Kp3678_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3678_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_1, false>(vu, c);
    }
    struct Kp36D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507efu; p.upper = 0x1c1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D8_1, false>(vu, c);
    }
    struct Kp3758_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e039dfu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3758_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3758_0, false>(vu, c);
    }
    struct Kp38D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_1, false>(vu, c);
    }
    struct Kp3938_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_1, false>(vu, c);
    }
    struct Kp3998_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3998_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_1, false>(vu, c);
    }
    struct Kp39F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F8_1, false>(vu, c);
    }
    struct Kp3A58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3A58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A58_1, false>(vu, c);
    }
    struct Kp3C58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_0, false>(vu, c);
    }
    struct Kp3CB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_0, false>(vu, c);
    }
    struct Kp3D18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_0, false>(vu, c);
    }
    struct Kp3D78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507efu; p.upper = 0x1c1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D78_0, false>(vu, c);
    }
    struct Kp3DD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DD8_0, false>(vu, c);
    }
    struct Kp3E38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3E38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E38_0, false>(vu, c);
    }
    struct Kp2880_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2880_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_2, false>(vu, c);
    }
    struct Kp28E0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28E0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_2, false>(vu, c);
    }
    struct Kp2B88_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B88_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B88_2, false>(vu, c);
    }
    struct Kp2BE8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_2, false>(vu, c);
    }
    struct Kp2C78_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_2, false>(vu, c);
    }
    struct Kp3CB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_1, false>(vu, c);
    }
    struct Kp3D40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D40_1, false>(vu, c);
    }
    struct Kp2890_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_3, false>(vu, c);
    }
    struct Kp28F0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_3, false>(vu, c);
    }
    struct Kp2950_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2950_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_2, false>(vu, c);
    }
    struct Kp29B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507eeu; p.upper = 0x1eb192bu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B0_1, false>(vu, c);
    }
    struct Kp2BC0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_3, false>(vu, c);
    }
    struct Kp2C20_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C20_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C20_3, false>(vu, c);
    }
    struct Kp2C80_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_3, false>(vu, c);
    }
    struct Kp2CE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE8_1, false>(vu, c);
    }
    struct Kp2EF8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_2, false>(vu, c);
    }
    struct Kp2F58_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_2, false>(vu, c);
    }
    struct Kp2FB8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_2, false>(vu, c);
    }
    struct Kp3228_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3228_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3228_1, false>(vu, c);
    }
    struct Kp3288_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_2, false>(vu, c);
    }
    struct Kp32E8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_2, false>(vu, c);
    }
    struct Kp3348_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3348_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3348_2, false>(vu, c);
    }
    struct Kp35B8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35B8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B8_2, false>(vu, c);
    }
    struct Kp3618_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7817u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3618_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_2, false>(vu, c);
    }
    struct Kp3678_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3678_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_2, false>(vu, c);
    }
    struct Kp38E8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_2, false>(vu, c);
    }
    struct Kp3948_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3948_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_2, false>(vu, c);
    }
    struct Kp39A8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_2, false>(vu, c);
    }
    struct Kp3C20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_1, false>(vu, c);
    }
    struct Kp3C80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3C80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_1, false>(vu, c);
    }
    struct Kp3D18_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D18_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_2, false>(vu, c);
    }
    struct Kp2860_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_4, false>(vu, c);
    }
    struct Kp28C0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_4, false>(vu, c);
    }
    struct Kp2920_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_4, false>(vu, c);
    }
    struct Kp2980_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2980_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2980_2, false>(vu, c);
    }
    struct Kp29E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E0_1, false>(vu, c);
    }
    struct Kp2A40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A40_1, false>(vu, c);
    }
    struct Kp2C88_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C88_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C88_3, false>(vu, c);
    }
    struct Kp2F08_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1e2b0cau; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_3, false>(vu, c);
    }
    struct Kp2F68_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7812u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F68_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_3, false>(vu, c);
    }
    struct Kp2FC8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FC8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_3, false>(vu, c);
    }
    struct Kp3240_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_3, false>(vu, c);
    }
    struct Kp32A0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_3, false>(vu, c);
    }
    struct Kp38D8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_3, false>(vu, c);
    }
    struct Kp3938_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_3, false>(vu, c);
    }
    struct Kp3998_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3998_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_3, false>(vu, c);
    }
    struct Kp3C40_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_2, false>(vu, c);
    }
    struct Kp3CA0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3CA0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_2, false>(vu, c);
    }
    struct Kp3D00_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D00_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_3, false>(vu, c);
    }
    struct Kp3D60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D60_1, false>(vu, c);
    }
    struct Kp2860_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_5, false>(vu, c);
    }
    struct Kp28C0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28C0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_5, false>(vu, c);
    }
    struct Kp2920_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_5, false>(vu, c);
    }
    struct Kp2BD0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_5, false>(vu, c);
    }
    struct Kp3658_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_3, false>(vu, c);
    }
    struct Kp38D0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_4, false>(vu, c);
    }
    struct Kp3930_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_4, false>(vu, c);
    }
    struct Kp39C0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39C0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_4, false>(vu, c);
    }
    struct Kp3C70_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_3, false>(vu, c);
    }
    struct Kp3CD0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CD0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_2, false>(vu, c);
    }
    struct Kp28F8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_6, false>(vu, c);
    }
    struct Kp2BA0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_5, false>(vu, c);
    }
    struct Kp2C00_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C00_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_5, false>(vu, c);
    }
    struct Kp2C60_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C60_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_4, false>(vu, c);
    }
    struct Kp2F10_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_4, false>(vu, c);
    }
    struct Kp2F70_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F70_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_4, false>(vu, c);
    }
    struct Kp3000_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3000_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3000_3, false>(vu, c);
    }
    struct Kp3238_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_4, false>(vu, c);
    }
    struct Kp3298_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_4, false>(vu, c);
    }
    struct Kp32F8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32F8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_3, false>(vu, c);
    }
    struct Kp3358_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3358_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_3, false>(vu, c);
    }
    struct Kp33B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p33B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33B8_1, false>(vu, c);
    }
    struct Kp35D0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_3, false>(vu, c);
    }
    struct Kp3630_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8213cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3630_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_4, false>(vu, c);
    }
    struct Kp3698_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3698_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_4, false>(vu, c);
    }
    struct Kp36F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F8_1, false>(vu, c);
    }
    struct Kp39D0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_4, false>(vu, c);
    }
    struct Kp3D08_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D08_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_5, false>(vu, c);
    }
    struct Kp2948_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x187313eu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_4, false>(vu, c);
    }
    struct Kp2C80_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C80_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_6, false>(vu, c);
    }
    struct Kp32F8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_4, false>(vu, c);
    }
    struct Kp35A0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_4, false>(vu, c);
    }
    struct Kp3600_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3600_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3600_4, false>(vu, c);
    }
    struct Kp3660_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_5, false>(vu, c);
    }
    struct Kp3910_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_6, false>(vu, c);
    }
    struct Kp3970_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3970_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3970_4, false>(vu, c);
    }
    struct Kp39D0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_5, false>(vu, c);
    }
    struct Kp3A30_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A30_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A30_2, false>(vu, c);
    }
    struct Kp3C68_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_4, false>(vu, c);
    }
    struct Kp3CC8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_3, false>(vu, c);
    }
    struct Kp3D30_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D30_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D30_4, false>(vu, c);
    }
    struct Kp3D90_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D90_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D90_2, false>(vu, c);
    }
    struct Kp2878_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2878_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_6, false>(vu, c);
    }
    struct Kp28D8_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1b08au; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_7, false>(vu, c);
    }
    struct Kp2970_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2970_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2970_4, false>(vu, c);
    }
    struct Kp2BA8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_6, false>(vu, c);
    }
    struct Kp2C08_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_5, false>(vu, c);
    }
    struct Kp2C68_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C68_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_7, false>(vu, c);
    }
    struct Kp2CC8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC8_2, false>(vu, c);
    }
    struct Kp2F00_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_5, false>(vu, c);
    }
    struct Kp2F60_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F60_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_5, false>(vu, c);
    }
    struct Kp2FC0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_6, false>(vu, c);
    }
    struct Kp3028_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3028_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3028_2, false>(vu, c);
    }
    struct Kp3618_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3618_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_5, false>(vu, c);
    }
    struct Kp39A8_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39A8_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_7, false>(vu, c);
    }
    struct Kp3C50_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_5, false>(vu, c);
    }
    struct Kp3CB0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CB0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB0_5, false>(vu, c);
    }
    struct Kp3D10_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p3D10_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_7, false>(vu, c);
    }
    struct Kp3278_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_5, false>(vu, c);
    }
    struct Kp32D8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32D8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D8_4, false>(vu, c);
    }
    struct Kp3588_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_5, false>(vu, c);
    }
    struct Kp35E8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_5, false>(vu, c);
    }
    struct Kp3680_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3680_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_6, false>(vu, c);
    }
    struct Kp32C8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C8_6, false>(vu, c);
    }
    struct Kp01D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1856041u; p.upper = 0x103210au; p.lowerUsage.vfWrite = {5, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 8}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D0_2d, true>(vu, c);
    }
    struct Kp0238_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055174u; p.upper = 0x62507eu; p.lowerUsage.viRead = 1056; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {10, 3}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 3; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0238_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0238_2d, true>(vu, c);
    }
    struct Kp0510_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1846046u; p.upper = 0x1e7deeau; p.lowerUsage.vfWrite = {4, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {27, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0510_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0510_2d, true>(vu, c);
    }
    struct Kp0600_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea296au; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0600_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0600_2d, true>(vu, c);
    }
    struct Kp06E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x100529eu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {10, 8}; p.upperUsage.vfWrite = {10, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06E0_2d, true>(vu, c);
    }
    struct Kp07A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec1055u; p.upper = 0x1f51abeu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07A0_2d, true>(vu, c);
    }
    struct Kp0820_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4e30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {14, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0820_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0820_2d, true>(vu, c);
    }
    struct Kp0CD8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82117ffu; p.upper = 0x1e08440u; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {17, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD8_2d, true>(vu, c);
    }
    struct Kp0F60_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f521bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {21, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F60_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F60_2d, true>(vu, c);
    }
    struct Kp1008_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aac58u; p.upperUsage.vfRead[0] = {21, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {17, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1008_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1008_2d, true>(vu, c);
    }
    struct Kp10B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4c30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {12, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10B8_2d, true>(vu, c);
    }
    struct Kp1188_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x1f51abeu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1188_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1188_2d, true>(vu, c);
    }
    struct Kp1830_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001081fu; p.upper = 0x1d07afeu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {16, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1830_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1830_2d, true>(vu, c);
    }
    struct Kp1938_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec137du; p.upper = 0x510387u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {14, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1938_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1938_2d, true>(vu, c);
    }
    struct Kp1B60_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e04acbu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B60_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B60_2d, true>(vu, c);
    }
    struct Kp1DF8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e380bdu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF8_2d, true>(vu, c);
    }
    struct Kp2208_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c1a9beu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2208_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2208_2d, true>(vu, c);
    }
    struct Kp2338_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e02980u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2338_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2338_2d, true>(vu, c);
    }
    struct Kp2498_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12073801u; p.upper = 0x1c1a9beu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2498_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2498_2d, true>(vu, c);
    }
    struct Kp2618_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x200a23u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2618_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2618_1d, true>(vu, c);
    }
    struct Kp2918_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_9d, true>(vu, c);
    }
    struct Kp2B98_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_7d, true>(vu, c);
    }
    struct Kp2F88_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F88_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F88_5d, true>(vu, c);
    }
    struct Kp3310_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_8d, true>(vu, c);
    }
    struct Kp35A0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_6d, true>(vu, c);
    }
    struct Kp3680_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3680_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_7d, true>(vu, c);
    }
    struct Kp3900_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_6d, true>(vu, c);
    }
    struct Kp3970_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3970_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3970_5d, true>(vu, c);
    }
    struct Kp3A58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A58_2d, true>(vu, c);
    }
    struct Kp0270_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e219bfu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0270_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0270_2d, true>(vu, c);
    }
    struct Kp0508_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e020ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0508_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0508_2d, true>(vu, c);
    }
    struct Kp0828_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0828_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0828_2d, true>(vu, c);
    }
    struct Kp0938_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x105f96cu; p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0938_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0938_2d, true>(vu, c);
    }
    struct Kp0A10_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8029067cu; p.upper = 0x1c001a0u; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A10_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A10_2d, true>(vu, c);
    }
    struct Kp0AA8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c74a49u; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AA8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AA8_2d, true>(vu, c);
    }
    struct Kp0B40_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x634999u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfWrite = {6, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B40_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B40_2d, true>(vu, c);
    }
    struct Kp0BE0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c7033cu; p.upper = 0x1c0026cu; p.lowerUsage.vfRead[0] = {0, 14}; p.lowerUsage.vfWrite = {7, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BE0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BE0_2d, true>(vu, c);
    }
    struct Kp0C78_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c74949u; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C78_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C78_2d, true>(vu, c);
    }
    struct Kp0CE0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80270b3cu; p.upper = 0x1c70abcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CE0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CE0_2d, true>(vu, c);
    }
    struct Kp0EC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC0_2d, true>(vu, c);
    }
    struct Kp0FF8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1000160u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FF8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FF8_3d, true>(vu, c);
    }
    struct Kp1148_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1148_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1148_2d, true>(vu, c);
    }
    struct Kp12B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B0_2d, true>(vu, c);
    }
    struct Kp1360_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8101933cu; p.upper = 0x18798a9u; p.lowerUsage.vfRead[0] = {18, 8}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1360_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1360_2d, true>(vu, c);
    }
    struct Kp1418_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x4103c0u; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {15, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1418_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1418_2d, true>(vu, c);
    }
    struct Kp1550_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10701c3u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1550_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1550_2d, true>(vu, c);
    }
    struct Kp15C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x42a33457u; p.upper = 0x81e03a5eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C8_2d, true>(vu, c);
    }
    struct Kp1630_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1827a19u; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1630_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1630_2d, true>(vu, c);
    }
    struct Kp16B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b2005u; p.upper = 0x8798ccu; p.lowerUsage.vfRead[0] = {4, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16B0_2d, true>(vu, c);
    }
    struct Kp17D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1295bu; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17D8_2d, true>(vu, c);
    }
    struct Kp1838_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c699a9u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1838_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1838_3d, true>(vu, c);
    }
    struct Kp1980_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1980_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1980_2d, true>(vu, c);
    }
    struct Kp1AC8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5c8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AC8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC8_2d, true>(vu, c);
    }
    struct Kp1B28_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf2a48u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B28_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B28_2d, true>(vu, c);
    }
    struct Kp1C10_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C10_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C10_2d, true>(vu, c);
    }
    struct Kp1D88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1029498u; p.upperUsage.vfRead[0] = {18, 8}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D88_2d, true>(vu, c);
    }
    struct Kp1E50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb2b7du; p.upper = 0x20016cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {5, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p1E50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E50_2d, true>(vu, c);
    }
    struct Kp1F90_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F90_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F90_3d, true>(vu, c);
    }
    struct Kp2090_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xe0006cu; p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfWrite = {1, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2090_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2090_2d, true>(vu, c);
    }
    struct Kp2170_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb37ffu; p.upper = 0x1023968u; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 8}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2170_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2170_2d, true>(vu, c);
    }
    struct Kp2230_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d8ed0bu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {24, 1}; p.upperUsage.vfWrite = {20, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2230_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2230_2d, true>(vu, c);
    }
    struct Kp2378_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80431b3du; p.upper = 0x18de88fu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfWrite = {3, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2378_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2378_2d, true>(vu, c);
    }
    struct Kp2438_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2438_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2438_2d, true>(vu, c);
    }
    struct Kp24A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbf800000u; p.upper = 0x81e631a9u; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p24A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24A8_2d, true>(vu, c);
    }
    struct Kp28A0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c888bfu; p.upperUsage.vfRead[0] = {17, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_7d, true>(vu, c);
    }
    struct Kp2B90_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_7d, true>(vu, c);
    }
    struct Kp2CB0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB0_5d, true>(vu, c);
    }
    struct Kp2EE0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_7d, true>(vu, c);
    }
    struct Kp2FC8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_8d, true>(vu, c);
    }
    struct Kp3088_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3088_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3088_1d, true>(vu, c);
    }
    struct Kp3278_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_7d, true>(vu, c);
    }
    struct Kp32F8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_6d, true>(vu, c);
    }
    struct Kp33C8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33C8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33C8_1d, true>(vu, c);
    }
    struct Kp35F0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_7d, true>(vu, c);
    }
    struct Kp3750_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3750_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3750_1d, true>(vu, c);
    }
    struct Kp3C88_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_6d, true>(vu, c);
    }
    struct Kp3E00_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E00_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E00_1d, true>(vu, c);
    }
    struct Kp2C08_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_6d, true>(vu, c);
    }
    struct Kp2880_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_8d, true>(vu, c);
    }
    struct Kp2968_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2968_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2968_5d, true>(vu, c);
    }
    struct Kp2BE0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_8d, true>(vu, c);
    }
    struct Kp2C60_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C60_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_7d, true>(vu, c);
    }
    struct Kp2EF8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_8d, true>(vu, c);
    }
    struct Kp3288_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_8d, true>(vu, c);
    }
    struct Kp36A8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A8_5d, true>(vu, c);
    }
    struct Kp39F8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F8_4d, true>(vu, c);
    }
    struct Kp3D00_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_10d, true>(vu, c);
    }
    struct Kp2868_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_8d, true>(vu, c);
    }
    struct Kp28D8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_9d, true>(vu, c);
    }
    struct Kp29C0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29C0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C0_3d, true>(vu, c);
    }
    struct Kp2C70_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_10d, true>(vu, c);
    }
    struct Kp32A0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_7d, true>(vu, c);
    }
    struct Kp3928_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_8d, true>(vu, c);
    }
    struct Kp3C70_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_7d, true>(vu, c);
    }
    struct Kp3D58_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D58_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D58_3d, true>(vu, c);
    }
    struct Kp2B98_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_10d, true>(vu, c);
    }
    struct Kp38F0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_8d, true>(vu, c);
    }
    struct Kp3CE8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_6d, true>(vu, c);
    }
    struct Kp2EE8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_8d, true>(vu, c);
    }
    struct Kp2FD8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_6d, true>(vu, c);
    }
    struct Kp3270_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_8d, true>(vu, c);
    }
    struct Kp3358_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3358_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_5d, true>(vu, c);
    }
    struct Kp35D0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_8d, true>(vu, c);
    }
    struct Kp3650_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3650_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_7d, true>(vu, c);
    }
    struct Kp39B0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_10d, true>(vu, c);
    }
    struct Kp32F0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_7d, true>(vu, c);
    }
    struct Kp38F8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_7d, true>(vu, c);
    }
    struct Kp39D8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_6d, true>(vu, c);
    }
    struct Kp3C58_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_6d, true>(vu, c);
    }
    struct Kp3CD8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_8d, true>(vu, c);
    }
    struct Kp3DB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DB0_2d, true>(vu, c);
    }
    struct Kp2928_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_11d, true>(vu, c);
    }
    struct Kp2BB8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_9d, true>(vu, c);
    }
    struct Kp2C98_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C98_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C98_6d, true>(vu, c);
    }
    struct Kp2F18_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F18_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_6d, true>(vu, c);
    }
    struct Kp2F98_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F98_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_7d, true>(vu, c);
    }
    struct Kp3070_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3070_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3070_2d, true>(vu, c);
    }
    struct Kp3CD0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_6d, true>(vu, c);
    }
    struct Kp35B0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_8d, true>(vu, c);
    }
    struct Kp2FA8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_7d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
