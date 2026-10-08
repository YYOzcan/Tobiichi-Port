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
    struct Kp0050_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0050_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0050_0, false>(vu, c);
    }
    struct Kp00B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00B0_0, false>(vu, c);
    }
    struct Kp0110_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e16800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0110_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0110_0, false>(vu, c);
    }
    struct Kp0170_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0170_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0170_0, false>(vu, c);
    }
    struct Kp01D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1856041u; p.upper = 0x103210au; p.lowerUsage.vfWrite = {5, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 8}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D0_0, false>(vu, c);
    }
    struct Kp0230_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10850000u; p.upper = 0x182007eu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0230_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0230_0, false>(vu, c);
    }
    struct Kp0290_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30033000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0290_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0290_0, false>(vu, c);
    }
    struct Kp02F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02F0_0, false>(vu, c);
    }
    struct Kp0350_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0350_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0350_0, false>(vu, c);
    }
    struct Kp03B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e002ffdu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03B0_0, false>(vu, c);
    }
    struct Kp0410_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b2134u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2064; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0410_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0410_0, false>(vu, c);
    }
    struct Kp0470_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b9feu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0470_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0470_0, false>(vu, c);
    }
    struct Kp04D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x43000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p04D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04D0_0, false>(vu, c);
    }
    struct Kp0530_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ea067cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0530_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0530_0, false>(vu, c);
    }
    struct Kp0590_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6312ecu; p.upperUsage.vfRead[0] = {2, 3}; p.upperUsage.vfRead[1] = {3, 3}; p.upperUsage.vfWrite = {11, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0590_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0590_0, false>(vu, c);
    }
    struct Kp05F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0529eu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F0_0, false>(vu, c);
    }
    struct Kp0650_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f6348au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {22, 2}; p.upperUsage.vfWrite = {18, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0650_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0650_0, false>(vu, c);
    }
    struct Kp06B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x43800000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p06B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B0_0, false>(vu, c);
    }
    struct Kp0710_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a6e58u; p.upperUsage.vfRead[0] = {13, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {25, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0710_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0710_0, false>(vu, c);
    }
    struct Kp0770_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e36040u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0770_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0770_0, false>(vu, c);
    }
    struct Kp07D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x1f71abeu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07D0_0, false>(vu, c);
    }
    struct Kp0830_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {15, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0830_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0830_0, false>(vu, c);
    }
    struct Kp0890_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9061001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0890_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0890_0, false>(vu, c);
    }
    struct Kp08F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08F0_0, false>(vu, c);
    }
    struct Kp0950_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80016871u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0950_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0950_0, false>(vu, c);
    }
    struct Kp09B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09B0_0, false>(vu, c);
    }
    struct Kp0A10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e50b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A10_0, false>(vu, c);
    }
    struct Kp0A70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A70_0, false>(vu, c);
    }
    struct Kp0AD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8232fffu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AD0_0, false>(vu, c);
    }
    struct Kp0B30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4a03a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B30_0, false>(vu, c);
    }
    struct Kp0B90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f75813u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {23, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B90_0, false>(vu, c);
    }
    struct Kp0BF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100f7803u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BF0_0, false>(vu, c);
    }
    struct Kp0C50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80032974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 40; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C50_0, false>(vu, c);
    }
    struct Kp0CB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8077b33cu; p.upper = 0x197b7eau; p.lowerUsage.vfRead[0] = {22, 3}; p.lowerUsage.vfWrite = {23, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {31, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB0_0, false>(vu, c);
    }
    struct Kp0D10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e0010u; p.upper = 0x1d7ebe9u; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {15, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D10_0, false>(vu, c);
    }
    struct Kp0D70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a72b1u; p.upper = 0x1dfc8bdu; p.lowerUsage.viRead = 17408; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D70_0, false>(vu, c);
    }
    struct Kp0DD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DD0_0, false>(vu, c);
    }
    struct Kp0E30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806b0bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E30_0, false>(vu, c);
    }
    struct Kp0E90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E90_0, false>(vu, c);
    }
    struct Kp0EF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee5812u; p.upper = 0x1e0a9feu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EF0_0, false>(vu, c);
    }
    struct Kp0F50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f428bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {20, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F50_0, false>(vu, c);
    }
    struct Kp0FB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB0_0, false>(vu, c);
    }
    struct Kp1010_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18ab498u; p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1010_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1010_0, false>(vu, c);
    }
    struct Kp1070_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5530bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1070_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1070_0, false>(vu, c);
    }
    struct Kp10D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4d30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D0_0, false>(vu, c);
    }
    struct Kp1130_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80063170u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1130_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1130_0, false>(vu, c);
    }
    struct Kp1190_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x5530bfu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1190_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1190_0, false>(vu, c);
    }
    struct Kp11F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F0_0, false>(vu, c);
    }
    struct Kp1250_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 544; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1250_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1250_0, false>(vu, c);
    }
    struct Kp12B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e17000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 16384; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B0_0, false>(vu, c);
    }
    struct Kp1310_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1310_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1310_0, false>(vu, c);
    }
    struct Kp1370_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12810001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1370_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1370_0, false>(vu, c);
    }
    struct Kp13D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13D0_0, false>(vu, c);
    }
    struct Kp1430_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1430_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1430_0, false>(vu, c);
    }
    struct Kp1490_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d6801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1490_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1490_0, false>(vu, c);
    }
    struct Kp14F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50080004u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F0_0, false>(vu, c);
    }
    struct Kp1550_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x88503a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1550_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1550_0, false>(vu, c);
    }
    struct Kp15B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15B0_0, false>(vu, c);
    }
    struct Kp1610_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100303a2u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1610_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1610_0, false>(vu, c);
    }
    struct Kp1670_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 544; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1670_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1670_0, false>(vu, c);
    }
    struct Kp16D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3a000800u; p.upper = 0x81800522u; p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfWrite = {20, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p16D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16D0_0, false>(vu, c);
    }
    struct Kp1730_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1e07c00u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1730_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1730_0, false>(vu, c);
    }
    struct Kp1790_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000006u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1790_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1790_0, false>(vu, c);
    }
    struct Kp17F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90803a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F0_0, false>(vu, c);
    }
    struct Kp1850_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802143fdu; p.upper = 0x51180bu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {3, 2}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1850_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1850_0, false>(vu, c);
    }
    struct Kp18B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80265bfdu; p.upper = 0x4000c3u; p.lowerUsage.vfWrite = {6, 1}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {3, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B0_0, false>(vu, c);
    }
    struct Kp1910_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x460003eeu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p1910_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1910_0, false>(vu, c);
    }
    struct Kp1970_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10050400u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1970_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1970_0, false>(vu, c);
    }
    struct Kp19D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19D0_0, false>(vu, c);
    }
    struct Kp1A30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90703a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A30_0, false>(vu, c);
    }
    struct Kp1A90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c34801u; p.upper = 0x208900u; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {17, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A90_0, false>(vu, c);
    }
    struct Kp1AF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18118ecu; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfRead[1] = {1, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AF0_0, false>(vu, c);
    }
    struct Kp1B50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e140bdu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B50_0, false>(vu, c);
    }
    struct Kp1BB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90103a0u; p.upper = 0x400203u; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {8, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BB0_0, false>(vu, c);
    }
    struct Kp1C10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80001a30u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C10_0, false>(vu, c);
    }
    struct Kp1C70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a5000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C70_0, false>(vu, c);
    }
    struct Kp1CD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CD0_0, false>(vu, c);
    }
    struct Kp1D30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f000du; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D30_0, false>(vu, c);
    }
    struct Kp1D90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D90_0, false>(vu, c);
    }
    struct Kp1DF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e379bcu; p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF0_0, false>(vu, c);
    }
    struct Kp1E50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E50_0, false>(vu, c);
    }
    struct Kp1EB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100f0010u; p.upper = 0x1960cadu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {22, 12}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EB0_0, false>(vu, c);
    }
    struct Kp1F10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000fecu; p.upper = 0x21017fu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F10_0, false>(vu, c);
    }
    struct Kp1F70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000004eu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F70_0, false>(vu, c);
    }
    struct Kp1FD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FD0_0, false>(vu, c);
    }
    struct Kp2030_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f8u; p.upper = 0x1c1a9bfu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2030_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2030_0, false>(vu, c);
    }
    struct Kp2090_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2090_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2090_0, false>(vu, c);
    }
    struct Kp20F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0425cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20F0_0, false>(vu, c);
    }
    struct Kp2150_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000046u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2150_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2150_0, false>(vu, c);
    }
    struct Kp21B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21B0_0, false>(vu, c);
    }
    struct Kp2210_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a0edu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2210_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2210_0, false>(vu, c);
    }
    struct Kp2270_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2270_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2270_0, false>(vu, c);
    }
    struct Kp22D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a0edu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D0_0, false>(vu, c);
    }
    struct Kp2330_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0adu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2330_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2330_0, false>(vu, c);
    }
    struct Kp2390_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2390_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2390_0, false>(vu, c);
    }
    struct Kp23F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa271800u; p.upper = 0x1c2a0edu; p.lowerUsage.viRead = 136; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F0_0, false>(vu, c);
    }
    struct Kp2450_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4001e2u; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2450_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2450_0, false>(vu, c);
    }
    struct Kp24B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1007387fu; p.upper = 0x18b2eecu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {11, 12}; p.upperUsage.vfWrite = {27, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B0_0, false>(vu, c);
    }
    struct Kp2510_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e641beu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2510_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2510_0, false>(vu, c);
    }
    struct Kp2570_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9053800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2570_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2570_0, false>(vu, c);
    }
    struct Kp25D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb053800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 160; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25D0_0, false>(vu, c);
    }
    struct Kp2630_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2630_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2630_0, false>(vu, c);
    }
    struct Kp2690_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e347ffu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2690_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2690_0, false>(vu, c);
    }
    struct Kp26F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26F0_0, false>(vu, c);
    }
    struct Kp2750_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f50225u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2750_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2750_0, false>(vu, c);
    }
    struct Kp27B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20085eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p27B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27B0_0, false>(vu, c);
    }
    struct Kp2810_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055970u; p.upper = 0x1c001ecu; p.lowerUsage.viRead = 2080; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2810_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2810_0, false>(vu, c);
    }
    struct Kp2870_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_0, false>(vu, c);
    }
    struct Kp28D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_0, false>(vu, c);
    }
    struct Kp2930_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2930_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_0, false>(vu, c);
    }
    struct Kp2990_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2990_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_0, false>(vu, c);
    }
    struct Kp29F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29F0_0, false>(vu, c);
    }
    struct Kp2A50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A50_0, false>(vu, c);
    }
    struct Kp2AB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AB0_0, false>(vu, c);
    }
    struct Kp2B10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B10_0, false>(vu, c);
    }
    struct Kp2B70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B70_0, false>(vu, c);
    }
    struct Kp2BD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_0, false>(vu, c);
    }
    struct Kp2C30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C30_0, false>(vu, c);
    }
    struct Kp2C90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_0, false>(vu, c);
    }
    struct Kp2F20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_0, false>(vu, c);
    }
    struct Kp2F80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_0, false>(vu, c);
    }
    struct Kp2FE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_0, false>(vu, c);
    }
    struct Kp3270_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_0, false>(vu, c);
    }
    struct Kp32D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_0, false>(vu, c);
    }
    struct Kp3330_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3330_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3330_0, false>(vu, c);
    }
    struct Kp3390_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3390_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3390_0, false>(vu, c);
    }
    struct Kp35B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_0, false>(vu, c);
    }
    struct Kp3610_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3610_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_0, false>(vu, c);
    }
    struct Kp3670_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_0, false>(vu, c);
    }
    struct Kp36D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p36D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D0_0, false>(vu, c);
    }
    struct Kp38D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_0, false>(vu, c);
    }
    struct Kp3930_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_0, false>(vu, c);
    }
    struct Kp3990_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3990_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_0, false>(vu, c);
    }
    struct Kp39F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_0, false>(vu, c);
    }
    struct Kp3A50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A50_0, false>(vu, c);
    }
    struct Kp3AB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AB0_0, false>(vu, c);
    }
    struct Kp0018_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c06bcu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0018_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0018_1, false>(vu, c);
    }
    struct Kp0080_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80000efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0080_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0080_1, false>(vu, c);
    }
    struct Kp00E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c08f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00E0_1, false>(vu, c);
    }
    struct Kp0140_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0140_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0140_1, false>(vu, c);
    }
    struct Kp01A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb613eu; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01A8_1, false>(vu, c);
    }
    struct Kp0208_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010008u; p.upper = 0x1ec617du; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0208_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0208_1, false>(vu, c);
    }
    struct Kp0268_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xc10fcfu; p.upperUsage.vfRead[0] = {1, 7}; p.upperUsage.vfWrite = {31, 6}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 6; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0268_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0268_1, false>(vu, c);
    }
    struct Kp02D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02D0_1, false>(vu, c);
    }
    struct Kp0330_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0330_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0330_1, false>(vu, c);
    }
    struct Kp0390_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0390_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0390_1, false>(vu, c);
    }
    struct Kp03F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000806u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03F0_1, false>(vu, c);
    }
    struct Kp0450_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0450_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0450_1, false>(vu, c);
    }
    struct Kp04B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04B0_1, false>(vu, c);
    }
    struct Kp0510_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f7a7u; p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfWrite = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0510_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0510_1, false>(vu, c);
    }
    struct Kp0570_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0570_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0570_1, false>(vu, c);
    }
    struct Kp05D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05D0_1, false>(vu, c);
    }
    struct Kp0630_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0630_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0630_1, false>(vu, c);
    }
    struct Kp0690_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff1a49u; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0690_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0690_1, false>(vu, c);
    }
    struct Kp06F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06F0_1, false>(vu, c);
    }
    struct Kp0750_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff10bcu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0750_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0750_1, false>(vu, c);
    }
    struct Kp07B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e70800u; p.upper = 0x103092cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 8}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B0_1, false>(vu, c);
    }
    struct Kp0810_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e4194cu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0810_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0810_1, false>(vu, c);
    }
    struct Kp0870_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0870_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0870_1, false>(vu, c);
    }
    struct Kp08D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1000164u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p08D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08D0_1, false>(vu, c);
    }
    struct Kp0930_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8208du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0930_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0930_1, false>(vu, c);
    }
    struct Kp0990_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0990_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0990_1, false>(vu, c);
    }
    struct Kp09F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09F0_1, false>(vu, c);
    }
    struct Kp0A58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x102319bu; p.upperUsage.vfRead[0] = {6, 8}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A58_1, false>(vu, c);
    }
    struct Kp0AC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0103cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AC0_1, false>(vu, c);
    }
    struct Kp0B20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31003u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B20_1, false>(vu, c);
    }
    struct Kp0B80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806047beu; p.upper = 0x8842beu; p.lowerUsage.vfRead[0] = {8, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 12; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B80_1, false>(vu, c);
    }
    struct Kp0BE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c7033cu; p.upper = 0x1c0026cu; p.lowerUsage.vfRead[0] = {0, 14}; p.lowerUsage.vfWrite = {7, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BE0_1, false>(vu, c);
    }
    struct Kp0C40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5f39c4u; p.upperUsage.vfRead[0] = {7, 2}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C40_1, false>(vu, c);
    }
    struct Kp0CA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8204cu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 8}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA0_1, false>(vu, c);
    }
    struct Kp0D00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D00_1, false>(vu, c);
    }
    struct Kp0D60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f12000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 16; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D60_1, false>(vu, c);
    }
    struct Kp0DC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12063001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DC0_1, false>(vu, c);
    }
    struct Kp0E20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x53003fu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {19, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E20_1, false>(vu, c);
    }
    struct Kp0E80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E80_1, false>(vu, c);
    }
    struct Kp0EE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE0_1, false>(vu, c);
    }
    struct Kp0F40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F40_1, false>(vu, c);
    }
    struct Kp0FA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0FA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FA0_1, false>(vu, c);
    }
    struct Kp1000_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1010183u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1000_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1000_1, false>(vu, c);
    }
    struct Kp1060_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1c4e9bfu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1060_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1060_1, false>(vu, c);
    }
    struct Kp10C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10C0_1, false>(vu, c);
    }
    struct Kp1120_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1120_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1120_1, false>(vu, c);
    }
    struct Kp1180_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1180_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1180_1, false>(vu, c);
    }
    struct Kp11E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e077cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11E0_1, false>(vu, c);
    }
    struct Kp1240_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1240_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1240_1, false>(vu, c);
    }
    struct Kp12A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12A0_1, false>(vu, c);
    }
    struct Kp1300_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c319ffu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1300_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1300_1, false>(vu, c);
    }
    struct Kp1368_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80818b3cu; p.upper = 0x180283cu; p.lowerUsage.vfRead[0] = {17, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1368_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1368_1, false>(vu, c);
    }
    struct Kp13C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1ffdu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13C8_1, false>(vu, c);
    }
    struct Kp1430_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1430_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1430_1, false>(vu, c);
    }
    struct Kp1490_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1490_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1490_1, false>(vu, c);
    }
    struct Kp14F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F0_1, false>(vu, c);
    }
    struct Kp1550_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10701c3u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1550_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1550_1, false>(vu, c);
    }
    struct Kp15B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e039e6u; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15B0_1, false>(vu, c);
    }
    struct Kp1610_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e03a3fu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1610_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1610_1, false>(vu, c);
    }
    struct Kp1670_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80818b3cu; p.upper = 0x180283cu; p.lowerUsage.vfRead[0] = {17, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1670_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1670_1, false>(vu, c);
    }
    struct Kp16D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1ffdu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16D0_1, false>(vu, c);
    }
    struct Kp1730_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef0804u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1730_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1730_1, false>(vu, c);
    }
    struct Kp1790_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1790_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1790_1, false>(vu, c);
    }
    struct Kp17F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2988u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F0_1, false>(vu, c);
    }
    struct Kp1850_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x28020eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1850_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1850_1, false>(vu, c);
    }
    struct Kp18B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5201069fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B0_1, false>(vu, c);
    }
    struct Kp1910_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1910_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1910_1, false>(vu, c);
    }
    struct Kp1970_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8081933cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1970_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1970_1, false>(vu, c);
    }
    struct Kp19D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19D0_1, false>(vu, c);
    }
    struct Kp1A30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A30_1, false>(vu, c);
    }
    struct Kp1A90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A90_1, false>(vu, c);
    }
    struct Kp1AF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AF0_1, false>(vu, c);
    }
    struct Kp1B50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2701ceu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B50_1, false>(vu, c);
    }
    struct Kp1BB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BB0_1, false>(vu, c);
    }
    struct Kp1C10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C10_1, false>(vu, c);
    }
    struct Kp1C70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C70_1, false>(vu, c);
    }
    struct Kp1CD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1CD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CD0_1, false>(vu, c);
    }
    struct Kp1D30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x19398aau; p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D30_1, false>(vu, c);
    }
    struct Kp1D90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x808c5cu; p.upperUsage.vfRead[0] = {17, 4}; p.upperUsage.vfWrite = {17, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D90_1, false>(vu, c);
    }
    struct Kp1DF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF0_1, false>(vu, c);
    }
    struct Kp1E50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb2b7du; p.upper = 0x20016cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {5, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p1E50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E50_1, false>(vu, c);
    }
    struct Kp1EB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1819049u; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {18, 12}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EB0_1, false>(vu, c);
    }
    struct Kp1F10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F10_1, false>(vu, c);
    }
    struct Kp1F70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F70_1, false>(vu, c);
    }
    struct Kp1FD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c421ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FD0_1, false>(vu, c);
    }
    struct Kp2030_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x81097fu; p.upperUsage.vfRead[0] = {1, 4}; p.upperUsage.vfWrite = {1, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2030_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2030_1, false>(vu, c);
    }
    struct Kp2090_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xe0006cu; p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfWrite = {1, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2090_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2090_1, false>(vu, c);
    }
    struct Kp20F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80632b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 3}; p.lowerUsage.vfWrite = {3, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20F0_1, false>(vu, c);
    }
    struct Kp2150_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e141a8u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2150_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2150_1, false>(vu, c);
    }
    struct Kp21B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21B0_1, false>(vu, c);
    }
    struct Kp2210_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eda0bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2210_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2210_1, false>(vu, c);
    }
    struct Kp2270_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2270_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2270_1, false>(vu, c);
    }
    struct Kp22D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6007u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D0_1, false>(vu, c);
    }
    struct Kp2330_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2330_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2330_1, false>(vu, c);
    }
    struct Kp2390_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2390_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2390_1, false>(vu, c);
    }
    struct Kp23F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a3fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F0_1, false>(vu, c);
    }
    struct Kp2450_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc004c9feu; p.upper = 0x81e2112au; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2450_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2450_1, false>(vu, c);
    }
    struct Kp24B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B0_1, false>(vu, c);
    }
    struct Kp2860_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8065a3fcu; p.upper = 0x1d139dbu; p.lowerUsage.vfRead[0] = {20, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 14}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_1, false>(vu, c);
    }
    struct Kp28C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x224a47u; p.upperUsage.vfRead[0] = {9, 1}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_1, false>(vu, c);
    }
    struct Kp2920_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80220bfdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2920_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_1, false>(vu, c);
    }
    struct Kp2B80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B80_1, false>(vu, c);
    }
    struct Kp2BE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80220bfdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_1, false>(vu, c);
    }
    struct Kp2C40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_1, false>(vu, c);
    }
    struct Kp2CA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_0, false>(vu, c);
    }
    struct Kp2D00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2D00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D00_0, false>(vu, c);
    }
    struct Kp2D60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2D60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D60_0, false>(vu, c);
    }
    struct Kp2EE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_1, false>(vu, c);
    }
    struct Kp2F40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_1, false>(vu, c);
    }
    struct Kp2FA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_1, false>(vu, c);
    }
    struct Kp3000_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3000_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3000_0, false>(vu, c);
    }
    struct Kp3060_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3060_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3060_0, false>(vu, c);
    }
    struct Kp30C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30C0_0, false>(vu, c);
    }
    struct Kp3248_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_1, false>(vu, c);
    }
    struct Kp32A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_1, false>(vu, c);
    }
    struct Kp3308_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_1, false>(vu, c);
    }
    struct Kp3368_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3368_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3368_1, false>(vu, c);
    }
    struct Kp33C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33C8_0, false>(vu, c);
    }
    struct Kp3428_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3428_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3428_0, false>(vu, c);
    }
    struct Kp35A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_1, false>(vu, c);
    }
    struct Kp3608_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3608_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_1, false>(vu, c);
    }
    struct Kp3668_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_1, false>(vu, c);
    }
    struct Kp36C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36C8_1, false>(vu, c);
    }
    struct Kp3748_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3748_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3748_0, false>(vu, c);
    }
    struct Kp38C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38C8_1, false>(vu, c);
    }
    struct Kp3928_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_1, false>(vu, c);
    }
    struct Kp3988_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3988_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_1, false>(vu, c);
    }
    struct Kp39E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E8_1, false>(vu, c);
    }
    struct Kp3A48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A48_1, false>(vu, c);
    }
    struct Kp3C48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_0, false>(vu, c);
    }
    struct Kp3CA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_0, false>(vu, c);
    }
    struct Kp3D08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_0, false>(vu, c);
    }
    struct Kp3D68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D68_0, false>(vu, c);
    }
    struct Kp3DC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DC8_0, false>(vu, c);
    }
    struct Kp3E28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E28_0, false>(vu, c);
    }
    struct Kp2870_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_2, false>(vu, c);
    }
    struct Kp28D0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28D0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_2, false>(vu, c);
    }
    struct Kp2930_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2930_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_2, false>(vu, c);
    }
    struct Kp2BD8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BD8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_2, false>(vu, c);
    }
    struct Kp2C68_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_2, false>(vu, c);
    }
    struct Kp3C08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C08_1, false>(vu, c);
    }
    struct Kp3D30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D30_1, false>(vu, c);
    }
    struct Kp2880_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_3, false>(vu, c);
    }
    struct Kp28E0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_3, false>(vu, c);
    }
    struct Kp2940_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2940_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_2, false>(vu, c);
    }
    struct Kp29A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A0_1, false>(vu, c);
    }
    struct Kp2BB0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_3, false>(vu, c);
    }
    struct Kp2C10_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C10_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_3, false>(vu, c);
    }
    struct Kp2C70_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_3, false>(vu, c);
    }
    struct Kp2CD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD8_1, false>(vu, c);
    }
    struct Kp2EE8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_2, false>(vu, c);
    }
    struct Kp2F48_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_2, false>(vu, c);
    }
    struct Kp2FA8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FA8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_2, false>(vu, c);
    }
    struct Kp3008_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3008_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_1, false>(vu, c);
    }
    struct Kp3278_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_2, false>(vu, c);
    }
    struct Kp32D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D8_2, false>(vu, c);
    }
    struct Kp3338_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_2, false>(vu, c);
    }
    struct Kp35A8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1e2b0cau; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_2, false>(vu, c);
    }
    struct Kp3608_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7812u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3608_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_2, false>(vu, c);
    }
    struct Kp3668_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3668_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_2, false>(vu, c);
    }
    struct Kp38D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_2, false>(vu, c);
    }
    struct Kp3938_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3938_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_2, false>(vu, c);
    }
    struct Kp3998_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3998_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_2, false>(vu, c);
    }
    struct Kp3A00_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3A00_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A00_2, false>(vu, c);
    }
    struct Kp3C70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_1, false>(vu, c);
    }
    struct Kp3D08_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_2, false>(vu, c);
    }
    struct Kp2850_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_4, false>(vu, c);
    }
    struct Kp28B0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_4, false>(vu, c);
    }
    struct Kp2910_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2910_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_4, false>(vu, c);
    }
    struct Kp2970_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2970_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2970_3, false>(vu, c);
    }
    struct Kp29D0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D0_2, false>(vu, c);
    }
    struct Kp2A30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A30_1, false>(vu, c);
    }
    struct Kp2C78_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_4, false>(vu, c);
    }
    struct Kp2EF8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_3, false>(vu, c);
    }
    struct Kp2F58_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_3, false>(vu, c);
    }
    struct Kp2FB8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_3, false>(vu, c);
    }
    struct Kp3230_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_3, false>(vu, c);
    }
    struct Kp3290_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_3, false>(vu, c);
    }
    struct Kp3320_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3320_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_3, false>(vu, c);
    }
    struct Kp3928_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_3, false>(vu, c);
    }
    struct Kp3988_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3988_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_3, false>(vu, c);
    }
    struct Kp3C30_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e5293cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_2, false>(vu, c);
    }
    struct Kp3C90_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_2, false>(vu, c);
    }
    struct Kp3CF0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CF0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_2, false>(vu, c);
    }
    struct Kp3D50_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D50_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D50_2, false>(vu, c);
    }
    struct Kp2850_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_5, false>(vu, c);
    }
    struct Kp28B0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28B0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_5, false>(vu, c);
    }
    struct Kp2910_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2910_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_5, false>(vu, c);
    }
    struct Kp2BC0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_4, false>(vu, c);
    }
    struct Kp3648_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3648_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3648_3, false>(vu, c);
    }
    struct Kp38B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38B8_1, false>(vu, c);
    }
    struct Kp3920_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3920_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_4, false>(vu, c);
    }
    struct Kp39B0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_4, false>(vu, c);
    }
    struct Kp3C60_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C60_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_4, false>(vu, c);
    }
    struct Kp3CC0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CC0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_2, false>(vu, c);
    }
    struct Kp3D20_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D20_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_4, false>(vu, c);
    }
    struct Kp2B90_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_5, false>(vu, c);
    }
    struct Kp2BF0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2BF0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_5, false>(vu, c);
    }
    struct Kp2C50_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0295fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C50_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C50_4, false>(vu, c);
    }
    struct Kp2F00_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1e6393cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_4, false>(vu, c);
    }
    struct Kp2F60_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1eb216bu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F60_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_4, false>(vu, c);
    }
    struct Kp2FF0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FF0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_3, false>(vu, c);
    }
    struct Kp3050_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3050_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3050_1, false>(vu, c);
    }
    struct Kp3288_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_4, false>(vu, c);
    }
    struct Kp32E8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32E8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_3, false>(vu, c);
    }
    struct Kp3348_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3348_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3348_3, false>(vu, c);
    }
    struct Kp33A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33A8_1, false>(vu, c);
    }
    struct Kp35C0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_3, false>(vu, c);
    }
    struct Kp3620_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3620_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3620_3, false>(vu, c);
    }
    struct Kp3688_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3688_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3688_4, false>(vu, c);
    }
    struct Kp36E8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36E8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E8_2, false>(vu, c);
    }
    struct Kp39C0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_5, false>(vu, c);
    }
    struct Kp3CF8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_5, false>(vu, c);
    }
    struct Kp2938_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2938_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_4, false>(vu, c);
    }
    struct Kp2C70_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_6, false>(vu, c);
    }
    struct Kp32E8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_4, false>(vu, c);
    }
    struct Kp3590_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_4, false>(vu, c);
    }
    struct Kp35F0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35F0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_4, false>(vu, c);
    }
    struct Kp3650_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3650_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_5, false>(vu, c);
    }
    struct Kp3900_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_5, false>(vu, c);
    }
    struct Kp3960_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3960_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3960_5, false>(vu, c);
    }
    struct Kp39C0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_6, false>(vu, c);
    }
    struct Kp3A20_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3A20_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A20_2, false>(vu, c);
    }
    struct Kp3C58_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_4, false>(vu, c);
    }
    struct Kp3CB8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_5, false>(vu, c);
    }
    struct Kp3D20_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D20_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_5, false>(vu, c);
    }
    struct Kp3D80_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D80_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D80_2, false>(vu, c);
    }
    struct Kp2868_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_6, false>(vu, c);
    }
    struct Kp28C8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_6, false>(vu, c);
    }
    struct Kp2960_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2960_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_5, false>(vu, c);
    }
    struct Kp2B98_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_6, false>(vu, c);
    }
    struct Kp2BF8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_6, false>(vu, c);
    }
    struct Kp2C58_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C58_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_5, false>(vu, c);
    }
    struct Kp2CB8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB8_3, false>(vu, c);
    }
    struct Kp2EF0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_5, false>(vu, c);
    }
    struct Kp2F50_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_5, false>(vu, c);
    }
    struct Kp2FB0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_5, false>(vu, c);
    }
    struct Kp3018_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3018_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3018_2, false>(vu, c);
    }
    struct Kp3568_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3568_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3568_1, false>(vu, c);
    }
    struct Kp3998_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3998_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_5, false>(vu, c);
    }
    struct Kp3C40_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_5, false>(vu, c);
    }
    struct Kp3CA0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CA0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_5, false>(vu, c);
    }
    struct Kp3D00_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_7, false>(vu, c);
    }
    struct Kp3268_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3268_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3268_5, false>(vu, c);
    }
    struct Kp32C8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32C8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C8_5, false>(vu, c);
    }
    struct Kp3330_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3330_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3330_5, false>(vu, c);
    }
    struct Kp35D8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_5, false>(vu, c);
    }
    struct Kp3670_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_7, false>(vu, c);
    }
    struct Kp2FE0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FE0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_6, false>(vu, c);
    }
    struct Kp3348_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3348_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3348_4, false>(vu, c);
    }
    struct Kp0228_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8187333cu; p.upper = 0x20109cu; p.lowerUsage.vfRead[0] = {6, 12}; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {2, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0228_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0228_2d, true>(vu, c);
    }
    struct Kp04B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803e033cu; p.upper = 0x1e007ecu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {30, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {31, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04B0_2d, true>(vu, c);
    }
    struct Kp05F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0529eu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F0_2d, true>(vu, c);
    }
    struct Kp0670_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0670_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0670_2d, true>(vu, c);
    }
    struct Kp0790_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x5430bfu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0790_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0790_2d, true>(vu, c);
    }
    struct Kp0810_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed134eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0810_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0810_2d, true>(vu, c);
    }
    struct Kp0CC8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d6801u; p.upper = 0x6004ecu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {19, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC8_2d, true>(vu, c);
    }
    struct Kp0F50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f428bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {20, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F50_2d, true>(vu, c);
    }
    struct Kp0FF8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8027f33cu; p.upper = 0x18004e6u; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FF8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FF8_2d, true>(vu, c);
    }
    struct Kp1088_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x5630bfu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1088_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1088_2d, true>(vu, c);
    }
    struct Kp1178_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x805430bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1178_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1178_2d, true>(vu, c);
    }
    struct Kp1820_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x1cf8afeu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 14}; p.upperUsage.vfRead[1] = {15, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1820_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1820_2d, true>(vu, c);
    }
    struct Kp1928_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x10f0387u; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {14, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1928_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1928_2d, true>(vu, c);
    }
    struct Kp1B50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e140bdu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B50_2d, true>(vu, c);
    }
    struct Kp1DE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c428ccu; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DE8_2d, true>(vu, c);
    }
    struct Kp21A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1c1a0adu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21A8_2d, true>(vu, c);
    }
    struct Kp2328_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9beu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2328_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2328_2d, true>(vu, c);
    }
    struct Kp2488_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30073800u; p.upper = 0x45396cu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 2}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfWrite = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2488_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2488_2d, true>(vu, c);
    }
    struct Kp2520_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed529bu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2520_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2520_1d, true>(vu, c);
    }
    struct Kp28B0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_7d, true>(vu, c);
    }
    struct Kp2AC0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AC0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AC0_1d, true>(vu, c);
    }
    struct Kp2F00_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_6d, true>(vu, c);
    }
    struct Kp3288_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_6d, true>(vu, c);
    }
    struct Kp3580_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_6d, true>(vu, c);
    }
    struct Kp3668_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_8d, true>(vu, c);
    }
    struct Kp38F0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_6d, true>(vu, c);
    }
    struct Kp3958_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3958_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_6d, true>(vu, c);
    }
    struct Kp3A48_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A48_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A48_2d, true>(vu, c);
    }
    struct Kp0260_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xc209bfu; p.upperUsage.vfRead[0] = {1, 6}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 6; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0260_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0260_2d, true>(vu, c);
    }
    struct Kp04F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3a95ff6cu; p.upper = 0x81e0203cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p04F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04F8_2d, true>(vu, c);
    }
    struct Kp0818_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x12401bcu; p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 9; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0818_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0818_3d, true>(vu, c);
    }
    struct Kp0928_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c820fdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0928_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0928_2d, true>(vu, c);
    }
    struct Kp09C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e428bcu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C0_2d, true>(vu, c);
    }
    struct Kp0A98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8225bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A98_2d, true>(vu, c);
    }
    struct Kp0B30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81050b3cu; p.upper = 0x10101c2u; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfWrite = {5, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B30_2d, true>(vu, c);
    }
    struct Kp0BD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000au; p.upper = 0x105f87du; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BD0_2d, true>(vu, c);
    }
    struct Kp0C68_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8225bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C68_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C68_2d, true>(vu, c);
    }
    struct Kp0CD0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df10bcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD0_3d, true>(vu, c);
    }
    struct Kp0E18_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d3d6aau; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {19, 14}; p.upperUsage.vfWrite = {26, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E18_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E18_2d, true>(vu, c);
    }
    struct Kp0FE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FE8_2d, true>(vu, c);
    }
    struct Kp1068_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e129u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1068_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1068_3d, true>(vu, c);
    }
    struct Kp1208_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x99cbc4u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1208_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1208_2d, true>(vu, c);
    }
    struct Kp1340_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb3000u; p.upper = 0x18579dbu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1340_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1340_2d, true>(vu, c);
    }
    struct Kp13F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x119cbc1u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F0_2d, true>(vu, c);
    }
    struct Kp14F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F0_2d, true>(vu, c);
    }
    struct Kp15B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc2992661u; p.upper = 0x81e738aau; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15B8_2d, true>(vu, c);
    }
    struct Kp1618_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e249e9u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1618_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1618_2d, true>(vu, c);
    }
    struct Kp16A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1804u; p.upper = 0x18798adu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A0_2d, true>(vu, c);
    }
    struct Kp17C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5295bu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17C8_2d, true>(vu, c);
    }
    struct Kp1828_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x53003fu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {19, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1828_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1828_3d, true>(vu, c);
    }
    struct Kp1938_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1938_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1938_3d, true>(vu, c);
    }
    struct Kp1AB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1211bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB8_2d, true>(vu, c);
    }
    struct Kp1B18_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf20bdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {15, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B18_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B18_2d, true>(vu, c);
    }
    struct Kp1BF8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BF8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BF8_2d, true>(vu, c);
    }
    struct Kp1D78_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1110485u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {17, 4}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D78_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D78_2d, true>(vu, c);
    }
    struct Kp1E40_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb7b7du; p.upper = 0xe0006cu; p.lowerUsage.vfRead[0] = {15, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfWrite = {1, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E40_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E40_2d, true>(vu, c);
    }
    struct Kp1F80_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F80_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F80_2d, true>(vu, c);
    }
    struct Kp2080_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3b000000u; p.upper = 0x81802a3fu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2080_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2080_2d, true>(vu, c);
    }
    struct Kp2160_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1819049u; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 12}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2160_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2160_2d, true>(vu, c);
    }
    struct Kp2200_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ecb30au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2200_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2200_3d, true>(vu, c);
    }
    struct Kp2368_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x21005au; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2368_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2368_2d, true>(vu, c);
    }
    struct Kp2428_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0098fu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2428_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2428_2d, true>(vu, c);
    }
    struct Kp2498_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2498_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2498_3d, true>(vu, c);
    }
    struct Kp2890_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_7d, true>(vu, c);
    }
    struct Kp28F8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_7d, true>(vu, c);
    }
    struct Kp2C98_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C98_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C98_5d, true>(vu, c);
    }
    struct Kp2D70_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D70_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D70_1d, true>(vu, c);
    }
    struct Kp2F50_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_6d, true>(vu, c);
    }
    struct Kp3078_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3078_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3078_1d, true>(vu, c);
    }
    struct Kp3260_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_7d, true>(vu, c);
    }
    struct Kp32D0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p32D0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_5d, true>(vu, c);
    }
    struct Kp33B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33B8_2d, true>(vu, c);
    }
    struct Kp35A0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_7d, true>(vu, c);
    }
    struct Kp3730_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3730_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3730_1d, true>(vu, c);
    }
    struct Kp3C38_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_6d, true>(vu, c);
    }
    struct Kp3DD8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DD8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DD8_1d, true>(vu, c);
    }
    struct Kp2BF8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_7d, true>(vu, c);
    }
    struct Kp2868_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_7d, true>(vu, c);
    }
    struct Kp2948_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_6d, true>(vu, c);
    }
    struct Kp2BC8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_7d, true>(vu, c);
    }
    struct Kp2C48_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_7d, true>(vu, c);
    }
    struct Kp2D20_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D20_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D20_2d, true>(vu, c);
    }
    struct Kp3240_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_7d, true>(vu, c);
    }
    struct Kp3698_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3698_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_5d, true>(vu, c);
    }
    struct Kp39E8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39E8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E8_5d, true>(vu, c);
    }
    struct Kp3C78_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_6d, true>(vu, c);
    }
    struct Kp2858_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_9d, true>(vu, c);
    }
    struct Kp28C0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_9d, true>(vu, c);
    }
    struct Kp29A8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29A8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A8_4d, true>(vu, c);
    }
    struct Kp2A28_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A28_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A28_2d, true>(vu, c);
    }
    struct Kp3250_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_7d, true>(vu, c);
    }
    struct Kp3918_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_7d, true>(vu, c);
    }
    struct Kp3C50_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_7d, true>(vu, c);
    }
    struct Kp3D30_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D30_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D30_5d, true>(vu, c);
    }
    struct Kp28F0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_7d, true>(vu, c);
    }
    struct Kp38E0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_8d, true>(vu, c);
    }
    struct Kp3CD8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_6d, true>(vu, c);
    }
    struct Kp2C40_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C40_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_6d, true>(vu, c);
    }
    struct Kp2FC8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_10d, true>(vu, c);
    }
    struct Kp3258_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_7d, true>(vu, c);
    }
    struct Kp3338_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_6d, true>(vu, c);
    }
    struct Kp35B8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B8_6d, true>(vu, c);
    }
    struct Kp3638_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3638_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_8d, true>(vu, c);
    }
    struct Kp3710_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3710_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3710_2d, true>(vu, c);
    }
    struct Kp2FC0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_10d, true>(vu, c);
    }
    struct Kp38E8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_10d, true>(vu, c);
    }
    struct Kp39C8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C8_6d, true>(vu, c);
    }
    struct Kp3C48_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_7d, true>(vu, c);
    }
    struct Kp3CB8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_7d, true>(vu, c);
    }
    struct Kp3DA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DA0_2d, true>(vu, c);
    }
    struct Kp28A0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28A0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_10d, true>(vu, c);
    }
    struct Kp2BA8_12d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_12d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_12d, true>(vu, c);
    }
    struct Kp2C88_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C88_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C88_6d, true>(vu, c);
    }
    struct Kp2F08_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_7d, true>(vu, c);
    }
    struct Kp2F78_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_7d, true>(vu, c);
    }
    struct Kp3060_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3060_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3060_2d, true>(vu, c);
    }
    struct Kp3CC0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_6d, true>(vu, c);
    }
    struct Kp3590_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_8d, true>(vu, c);
    }
    struct Kp2F98_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F98_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_8d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
