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
    struct Kp0020_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000006u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0020_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0020_0, false>(vu, c);
    }
    struct Kp0080_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0080_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0080_0, false>(vu, c);
    }
    struct Kp00E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800d06bcu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00E0_0, false>(vu, c);
    }
    struct Kp0140_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f55811u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0140_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0140_0, false>(vu, c);
    }
    struct Kp01A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01A0_0, false>(vu, c);
    }
    struct Kp0200_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1896040u; p.upper = 0x180295eu; p.lowerUsage.vfWrite = {9, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfWrite = {5, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0200_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0200_0, false>(vu, c);
    }
    struct Kp0260_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10060010u; p.upper = 0x62307eu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 3}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 3; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0260_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0260_0, false>(vu, c);
    }
    struct Kp02C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12810001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02C0_0, false>(vu, c);
    }
    struct Kp0320_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5201000cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0320_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0320_0, false>(vu, c);
    }
    struct Kp0380_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0380_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0380_0, false>(vu, c);
    }
    struct Kp03E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800420f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03E0_0, false>(vu, c);
    }
    struct Kp0440_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ec5810u; p.upper = 0x1e0a1feu; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0440_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0440_0, false>(vu, c);
    }
    struct Kp04A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58005804u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04A0_0, false>(vu, c);
    }
    struct Kp0500_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc604au; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0500_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0500_0, false>(vu, c);
    }
    struct Kp0560_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8065133du; p.upper = 0x480180u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {5, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {8, 8}; p.upperUsage.vfWrite = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0560_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0560_0, false>(vu, c);
    }
    struct Kp05C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800007bfu; p.upper = 0x2ffu; p.lowerUsage.waitP = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05C0_0, false>(vu, c);
    }
    struct Kp0620_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec3051u; p.upper = 0x1f4340au; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0620_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0620_0, false>(vu, c);
    }
    struct Kp0680_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed364au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {25, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0680_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0680_0, false>(vu, c);
    }
    struct Kp06E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x100529eu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {10, 8}; p.upperUsage.vfWrite = {10, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06E0_0, false>(vu, c);
    }
    struct Kp0740_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b000000u; p.upper = 0x81e0ef62u; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfWrite = {29, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0740_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0740_0, false>(vu, c);
    }
    struct Kp07A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec1055u; p.upper = 0x1f51abeu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07A0_0, false>(vu, c);
    }
    struct Kp0800_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0800_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0800_0, false>(vu, c);
    }
    struct Kp0860_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa8903a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0860_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0860_0, false>(vu, c);
    }
    struct Kp08C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80035af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2056; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08C0_0, false>(vu, c);
    }
    struct Kp0920_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0920_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0920_0, false>(vu, c);
    }
    struct Kp0980_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001014bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0980_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0980_0, false>(vu, c);
    }
    struct Kp09E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800110b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09E0_0, false>(vu, c);
    }
    struct Kp0A40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12021001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A40_0, false>(vu, c);
    }
    struct Kp0AA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001003fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AA0_0, false>(vu, c);
    }
    struct Kp0B00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80022970u; p.upper = 0x2ffu; p.lowerUsage.viRead = 36; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B00_0, false>(vu, c);
    }
    struct Kp0B60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84a03a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B60_0, false>(vu, c);
    }
    struct Kp0BC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BC0_0, false>(vu, c);
    }
    struct Kp0C20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8846800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C20_0, false>(vu, c);
    }
    struct Kp0C80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fa1812u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {26, 15}; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C80_0, false>(vu, c);
    }
    struct Kp0CE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e07c00u; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CE0_0, false>(vu, c);
    }
    struct Kp0D40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000006u; p.upper = 0x1dfc0bcu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D40_0, false>(vu, c);
    }
    struct Kp0DA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e307ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DA0_0, false>(vu, c);
    }
    struct Kp0E00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa2317ffu; p.upper = 0x2ffu; p.lowerUsage.viRead = 12; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E00_0, false>(vu, c);
    }
    struct Kp0E60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c0a73fu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {20, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 24; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E60_0, false>(vu, c);
    }
    struct Kp0EC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50000000u; p.upper = 0x8021093cu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0EC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC0_0, false>(vu, c);
    }
    struct Kp0F20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e001816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F20_0, false>(vu, c);
    }
    struct Kp0F80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00300au; p.upper = 0x1f628bdu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {22, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F80_0, false>(vu, c);
    }
    struct Kp0FE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8048033du; p.upper = 0x1c00243u; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {8, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FE0_0, false>(vu, c);
    }
    struct Kp1040_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e66054u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1040_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1040_0, false>(vu, c);
    }
    struct Kp10A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00382du; p.upper = 0x5730bfu; p.lowerUsage.viRead = 128; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {23, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10A0_0, false>(vu, c);
    }
    struct Kp1100_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e003021u; p.upper = 0x4f30bfu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1100_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1100_0, false>(vu, c);
    }
    struct Kp1160_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x43099bu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1160_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1160_0, false>(vu, c);
    }
    struct Kp11C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000090u; p.upper = 0x5730bfu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {23, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11C0_0, false>(vu, c);
    }
    struct Kp1220_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9096800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1220_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1220_0, false>(vu, c);
    }
    struct Kp1280_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9056801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1280_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1280_0, false>(vu, c);
    }
    struct Kp12E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800066fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12E0_0, false>(vu, c);
    }
    struct Kp1340_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb016000u; p.upper = 0x400002ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.eBit = true; p.upperNop = true; return p; }();
    };
    bool p1340_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1340_0, false>(vu, c);
    }
    struct Kp13A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13A0_0, false>(vu, c);
    }
    struct Kp1400_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50050003u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1400_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1400_0, false>(vu, c);
    }
    struct Kp1460_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x2ffu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1460_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1460_0, false>(vu, c);
    }
    struct Kp14C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000072du; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14C0_0, false>(vu, c);
    }
    struct Kp1520_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e107ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1520_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1520_0, false>(vu, c);
    }
    struct Kp1580_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1580_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1580_0, false>(vu, c);
    }
    struct Kp15E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E0_0, false>(vu, c);
    }
    struct Kp1640_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84e03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1640_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1640_0, false>(vu, c);
    }
    struct Kp16A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A0_0, false>(vu, c);
    }
    struct Kp1700_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1700_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1700_0, false>(vu, c);
    }
    struct Kp1760_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80610bfcu; p.upper = 0x1d70be9u; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {15, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1760_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1760_0, false>(vu, c);
    }
    struct Kp17C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a7ab1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 33792; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17C0_0, false>(vu, c);
    }
    struct Kp1820_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x1cf8afeu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 14}; p.upperUsage.vfRead[1] = {15, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1820_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1820_0, false>(vu, c);
    }
    struct Kp1880_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa8503a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1880_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1880_0, false>(vu, c);
    }
    struct Kp18E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x46000000u; p.upper = 0x8023393cu; p.upperUsage.vfRead[0] = {7, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p18E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18E0_0, false>(vu, c);
    }
    struct Kp1940_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec1b7du; p.upper = 0x510301u; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {17, 4}; p.upperUsage.vfWrite = {12, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1940_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1940_0, false>(vu, c);
    }
    struct Kp19A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10850000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19A0_0, false>(vu, c);
    }
    struct Kp1A00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100203ecu; p.upper = 0x20006cu; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A00_0, false>(vu, c);
    }
    struct Kp1A60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010010u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A60_0, false>(vu, c);
    }
    struct Kp1AC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80013074u; p.upper = 0x2ffu; p.lowerUsage.viRead = 66; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1AC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC0_0, false>(vu, c);
    }
    struct Kp1B20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500c0003u; p.upper = 0x1e111bcu; p.lowerUsage.viRead = 4096; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B20_0, false>(vu, c);
    }
    struct Kp1B80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52025ff2u; p.upper = 0x1e18acau; p.lowerUsage.viRead = 2052; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B80_0, false>(vu, c);
    }
    struct Kp1BE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BE0_0, false>(vu, c);
    }
    struct Kp1C40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C40_0, false>(vu, c);
    }
    struct Kp1CA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8215000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CA0_0, false>(vu, c);
    }
    struct Kp1D00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107fau; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D00_0, false>(vu, c);
    }
    struct Kp1D60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c24000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 14}; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D60_0, false>(vu, c);
    }
    struct Kp1DC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x103183du; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC0_0, false>(vu, c);
    }
    struct Kp1E20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E20_0, false>(vu, c);
    }
    struct Kp1E80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1e07c00u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E80_0, false>(vu, c);
    }
    struct Kp1EE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x380a0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EE0_0, false>(vu, c);
    }
    struct Kp1F40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500907e6u; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F40_0, false>(vu, c);
    }
    struct Kp1FA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA0_0, false>(vu, c);
    }
    struct Kp2000_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1e02980u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2000_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2000_0, false>(vu, c);
    }
    struct Kp2060_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0690u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2060_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2060_0, false>(vu, c);
    }
    struct Kp20C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C0_0, false>(vu, c);
    }
    struct Kp2120_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a9bfu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2120_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2120_0, false>(vu, c);
    }
    struct Kp2180_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f066cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2180_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2180_0, false>(vu, c);
    }
    struct Kp21E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21E0_0, false>(vu, c);
    }
    struct Kp2240_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0665u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2240_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2240_0, false>(vu, c);
    }
    struct Kp22A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22A0_0, false>(vu, c);
    }
    struct Kp2300_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2300_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2300_0, false>(vu, c);
    }
    struct Kp2360_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32000u; p.upper = 0x18002fcu; p.lowerUsage.vfRead[0] = {4, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2360_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2360_0, false>(vu, c);
    }
    struct Kp23C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x56003fu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23C0_0, false>(vu, c);
    }
    struct Kp2420_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2420_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2420_0, false>(vu, c);
    }
    struct Kp2480_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x1d708a9u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2480_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2480_0, false>(vu, c);
    }
    struct Kp24E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8107333du; p.upper = 0x460041u; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfWrite = {7, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24E0_0, false>(vu, c);
    }
    struct Kp2540_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2540_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2540_0, false>(vu, c);
    }
    struct Kp25A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001054cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25A0_0, false>(vu, c);
    }
    struct Kp2600_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2600_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2600_0, false>(vu, c);
    }
    struct Kp2660_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2660_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2660_0, false>(vu, c);
    }
    struct Kp26C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26C0_0, false>(vu, c);
    }
    struct Kp2720_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef0801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2720_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2720_0, false>(vu, c);
    }
    struct Kp2780_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2780_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2780_0, false>(vu, c);
    }
    struct Kp27E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27E0_0, false>(vu, c);
    }
    struct Kp2840_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_0, false>(vu, c);
    }
    struct Kp28A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_0, false>(vu, c);
    }
    struct Kp2900_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2900_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_0, false>(vu, c);
    }
    struct Kp2960_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2960_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_0, false>(vu, c);
    }
    struct Kp29C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10222u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C0_0, false>(vu, c);
    }
    struct Kp2A20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1c0109cu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A20_0, false>(vu, c);
    }
    struct Kp2A80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A80_0, false>(vu, c);
    }
    struct Kp2AE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e4217cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AE0_0, false>(vu, c);
    }
    struct Kp2B40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0455u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B40_0, false>(vu, c);
    }
    struct Kp2BA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_0, false>(vu, c);
    }
    struct Kp2C00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f1u; p.upper = 0x1e2b10au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_0, false>(vu, c);
    }
    struct Kp2C60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_0, false>(vu, c);
    }
    struct Kp2EF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_0, false>(vu, c);
    }
    struct Kp2F50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_0, false>(vu, c);
    }
    struct Kp2FB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_0, false>(vu, c);
    }
    struct Kp3240_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_0, false>(vu, c);
    }
    struct Kp32A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_0, false>(vu, c);
    }
    struct Kp3300_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3300_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_0, false>(vu, c);
    }
    struct Kp3360_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3360_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3360_0, false>(vu, c);
    }
    struct Kp3580_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_0, false>(vu, c);
    }
    struct Kp35E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_0, false>(vu, c);
    }
    struct Kp3640_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3640_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_0, false>(vu, c);
    }
    struct Kp36A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A0_0, false>(vu, c);
    }
    struct Kp3700_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3700_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3700_0, false>(vu, c);
    }
    struct Kp3900_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_0, false>(vu, c);
    }
    struct Kp3960_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3960_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3960_0, false>(vu, c);
    }
    struct Kp39C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_0, false>(vu, c);
    }
    struct Kp3A20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A20_0, false>(vu, c);
    }
    struct Kp3A80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A80_0, false>(vu, c);
    }
    struct Kp3AE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3AE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AE0_0, false>(vu, c);
    }
    struct Kp0048_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c4a70u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4608; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0048_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0048_1, false>(vu, c);
    }
    struct Kp00B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00B0_1, false>(vu, c);
    }
    struct Kp0110_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8021137cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.viLatency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0110_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0110_1, false>(vu, c);
    }
    struct Kp0170_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10026020u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0170_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0170_1, false>(vu, c);
    }
    struct Kp01D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e30800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D8_1, false>(vu, c);
    }
    struct Kp0238_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0238_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0238_1, false>(vu, c);
    }
    struct Kp0298_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xa0ffdeu; p.upperUsage.vfRead[0] = {31, 5}; p.upperUsage.vfWrite = {31, 5}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0298_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0298_1, false>(vu, c);
    }
    struct Kp0300_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000807u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0300_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0300_1, false>(vu, c);
    }
    struct Kp0360_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e34b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {9, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0360_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0360_1, false>(vu, c);
    }
    struct Kp03C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f6u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03C0_1, false>(vu, c);
    }
    struct Kp0420_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0420_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0420_1, false>(vu, c);
    }
    struct Kp0480_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0480_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0480_1, false>(vu, c);
    }
    struct Kp04E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e02122u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E0_1, false>(vu, c);
    }
    struct Kp0540_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0540_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0540_1, false>(vu, c);
    }
    struct Kp05A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05A0_1, false>(vu, c);
    }
    struct Kp0600_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0600_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0600_1, false>(vu, c);
    }
    struct Kp0660_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3426au; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {3, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0660_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0660_1, false>(vu, c);
    }
    struct Kp06C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff1a0bu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 1}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06C0_1, false>(vu, c);
    }
    struct Kp0720_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e04a50u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0720_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0720_1, false>(vu, c);
    }
    struct Kp0780_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e90800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0780_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0780_1, false>(vu, c);
    }
    struct Kp07E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p07E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07E0_1, false>(vu, c);
    }
    struct Kp0840_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0840_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0840_1, false>(vu, c);
    }
    struct Kp08A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010040u; p.upper = 0x1843a0au; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p08A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08A0_1, false>(vu, c);
    }
    struct Kp0900_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010795u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0900_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0900_1, false>(vu, c);
    }
    struct Kp0960_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p0960_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0960_1, false>(vu, c);
    }
    struct Kp09C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e428bcu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C0_1, false>(vu, c);
    }
    struct Kp0A28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000au; p.upper = 0x105f87du; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A28_1, false>(vu, c);
    }
    struct Kp0A90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c62199u; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A90_1, false>(vu, c);
    }
    struct Kp0AF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df1a49u; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AF0_1, false>(vu, c);
    }
    struct Kp0B50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6349dau; p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {7, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B50_1, false>(vu, c);
    }
    struct Kp0BB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BB0_1, false>(vu, c);
    }
    struct Kp0C10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34011000u; p.upper = 0x1000169u; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C10_1, false>(vu, c);
    }
    struct Kp0C70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c531bdu; p.upperUsage.vfRead[0] = {6, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C70_1, false>(vu, c);
    }
    struct Kp0CD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df10bcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD0_1, false>(vu, c);
    }
    struct Kp0D30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e7426cu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D30_1, false>(vu, c);
    }
    struct Kp0D90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D90_1, false>(vu, c);
    }
    struct Kp0DF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x38c606u; p.upperUsage.vfRead[0] = {24, 3}; p.upperUsage.vfWrite = {24, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0DF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DF0_1, false>(vu, c);
    }
    struct Kp0E50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E50_1, false>(vu, c);
    }
    struct Kp0EB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EB0_1, false>(vu, c);
    }
    struct Kp0F10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb237du; p.upper = 0x1c0109cu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F10_1, false>(vu, c);
    }
    struct Kp0F70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F70_1, false>(vu, c);
    }
    struct Kp0FD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD0_1, false>(vu, c);
    }
    struct Kp1030_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3333cu; p.upper = 0x1e52108u; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1030_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1030_1, false>(vu, c);
    }
    struct Kp1090_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb2b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1090_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1090_1, false>(vu, c);
    }
    struct Kp10F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10F0_1, false>(vu, c);
    }
    struct Kp1150_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1150_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1150_1, false>(vu, c);
    }
    struct Kp11B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb237du; p.upper = 0x1c018dcu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11B0_1, false>(vu, c);
    }
    struct Kp1210_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103beu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 13; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1210_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1210_1, false>(vu, c);
    }
    struct Kp1270_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1270_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1270_1, false>(vu, c);
    }
    struct Kp12D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2f0bdau; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D0_1, false>(vu, c);
    }
    struct Kp1338_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1338_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1338_1, false>(vu, c);
    }
    struct Kp1398_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1804u; p.upper = 0x18798adu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1398_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1398_1, false>(vu, c);
    }
    struct Kp1400_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103beu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 13; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1400_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1400_1, false>(vu, c);
    }
    struct Kp1460_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1460_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1460_1, false>(vu, c);
    }
    struct Kp14C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2f0bdau; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14C0_1, false>(vu, c);
    }
    struct Kp1520_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1520_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1520_1, false>(vu, c);
    }
    struct Kp1580_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b400000u; p.upper = 0x81e039feu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1580_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1580_1, false>(vu, c);
    }
    struct Kp15E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e231aau; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E0_1, false>(vu, c);
    }
    struct Kp1640_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8740c0u; p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1640_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1640_1, false>(vu, c);
    }
    struct Kp16A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1804u; p.upper = 0x18798adu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A0_1, false>(vu, c);
    }
    struct Kp1700_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1700_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1700_1, false>(vu, c);
    }
    struct Kp1760_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e20224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1760_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1760_1, false>(vu, c);
    }
    struct Kp17C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025067cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17C0_1, false>(vu, c);
    }
    struct Kp1820_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1a002fcu; p.upperUsage.vfRead[0] = {0, 13}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 13; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1820_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1820_1, false>(vu, c);
    }
    struct Kp1880_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c841ffu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1880_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1880_1, false>(vu, c);
    }
    struct Kp18E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e6e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {6, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18E0_1, false>(vu, c);
    }
    struct Kp1940_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1940_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1940_1, false>(vu, c);
    }
    struct Kp19A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818b0b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19A0_1, false>(vu, c);
    }
    struct Kp1A00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A00_1, false>(vu, c);
    }
    struct Kp1A60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A60_1, false>(vu, c);
    }
    struct Kp1AC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5c1bcu; p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC0_1, false>(vu, c);
    }
    struct Kp1B20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2a08u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B20_1, false>(vu, c);
    }
    struct Kp1B80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c631ffu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B80_1, false>(vu, c);
    }
    struct Kp1BE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb0b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BE0_1, false>(vu, c);
    }
    struct Kp1C40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C40_1, false>(vu, c);
    }
    struct Kp1CA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CA0_1, false>(vu, c);
    }
    struct Kp1D00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D00_1, false>(vu, c);
    }
    struct Kp1D60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef0800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D60_1, false>(vu, c);
    }
    struct Kp1DC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC0_1, false>(vu, c);
    }
    struct Kp1E20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e7397cu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E20_1, false>(vu, c);
    }
    struct Kp1E80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1818858u; p.upperUsage.vfRead[0] = {17, 12}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E80_1, false>(vu, c);
    }
    struct Kp1EE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EE0_1, false>(vu, c);
    }
    struct Kp1F40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80339bbcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {19, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F40_1, false>(vu, c);
    }
    struct Kp1FA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA0_1, false>(vu, c);
    }
    struct Kp2000_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2000_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2000_1, false>(vu, c);
    }
    struct Kp2060_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb7b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {15, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2060_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2060_1, false>(vu, c);
    }
    struct Kp20C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x8180383cu; p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p20C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C0_1, false>(vu, c);
    }
    struct Kp2120_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802803fdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {8, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2120_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2120_1, false>(vu, c);
    }
    struct Kp2180_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x180089eu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2180_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2180_1, false>(vu, c);
    }
    struct Kp21E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eba8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {11, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21E0_1, false>(vu, c);
    }
    struct Kp2240_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d9ed4bu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {25, 1}; p.upperUsage.vfWrite = {21, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2240_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2240_1, false>(vu, c);
    }
    struct Kp22A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22A0_1, false>(vu, c);
    }
    struct Kp2300_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ed0222u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {13, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2300_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2300_1, false>(vu, c);
    }
    struct Kp2360_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4de883u; p.upperUsage.vfRead[0] = {29, 2}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2360_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2360_1, false>(vu, c);
    }
    struct Kp23C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000a95u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23C0_1, false>(vu, c);
    }
    struct Kp2420_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a7fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2420_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2420_1, false>(vu, c);
    }
    struct Kp2480_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eda6de1u; p.upper = 0x81e03a3fu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2480_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2480_1, false>(vu, c);
    }
    struct Kp2830_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8081043cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2830_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2830_1, false>(vu, c);
    }
    struct Kp2890_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_1, false>(vu, c);
    }
    struct Kp28F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c211ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_1, false>(vu, c);
    }
    struct Kp2950_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e048eu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2950_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_1, false>(vu, c);
    }
    struct Kp2BB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c211ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_1, false>(vu, c);
    }
    struct Kp2C10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1eb216bu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_1, false>(vu, c);
    }
    struct Kp2C70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_1, false>(vu, c);
    }
    struct Kp2CD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD0_0, false>(vu, c);
    }
    struct Kp2D30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D30_0, false>(vu, c);
    }
    struct Kp2D90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D90_0, false>(vu, c);
    }
    struct Kp2F10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_1, false>(vu, c);
    }
    struct Kp2F70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_1, false>(vu, c);
    }
    struct Kp2FD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_1, false>(vu, c);
    }
    struct Kp3030_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3030_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3030_0, false>(vu, c);
    }
    struct Kp3090_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3090_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3090_0, false>(vu, c);
    }
    struct Kp30F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p30F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30F0_0, false>(vu, c);
    }
    struct Kp3278_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_1, false>(vu, c);
    }
    struct Kp32D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D8_1, false>(vu, c);
    }
    struct Kp3338_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3338_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_1, false>(vu, c);
    }
    struct Kp3398_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3398_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3398_1, false>(vu, c);
    }
    struct Kp33F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33F8_0, false>(vu, c);
    }
    struct Kp3578_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3578_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3578_1, false>(vu, c);
    }
    struct Kp35D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_1, false>(vu, c);
    }
    struct Kp3638_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3638_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_1, false>(vu, c);
    }
    struct Kp3698_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3698_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_1, false>(vu, c);
    }
    struct Kp3718_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3718_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3718_0, false>(vu, c);
    }
    struct Kp3778_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3778_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3778_0, false>(vu, c);
    }
    struct Kp38F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1e2b0cau; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_1, false>(vu, c);
    }
    struct Kp3958_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7812u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3958_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_1, false>(vu, c);
    }
    struct Kp39B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_1, false>(vu, c);
    }
    struct Kp3A18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A18_1, false>(vu, c);
    }
    struct Kp3C18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C18_0, false>(vu, c);
    }
    struct Kp3C78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_0, false>(vu, c);
    }
    struct Kp3CD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_0, false>(vu, c);
    }
    struct Kp3D38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_0, false>(vu, c);
    }
    struct Kp3D98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D98_0, false>(vu, c);
    }
    struct Kp3DF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e039dfu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DF8_0, false>(vu, c);
    }
    struct Kp2840_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_2, false>(vu, c);
    }
    struct Kp28A0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_2, false>(vu, c);
    }
    struct Kp2900_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x42093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_2, false>(vu, c);
    }
    struct Kp2BA8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_2, false>(vu, c);
    }
    struct Kp2C08_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_2, false>(vu, c);
    }
    struct Kp2C98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C98_1, false>(vu, c);
    }
    struct Kp3D00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_1, false>(vu, c);
    }
    struct Kp2850_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e5293cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_3, false>(vu, c);
    }
    struct Kp28B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_3, false>(vu, c);
    }
    struct Kp2910_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2910_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_3, false>(vu, c);
    }
    struct Kp2970_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2970_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2970_2, false>(vu, c);
    }
    struct Kp29D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D0_1, false>(vu, c);
    }
    struct Kp2BE0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_3, false>(vu, c);
    }
    struct Kp2C40_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8213cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C40_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_2, false>(vu, c);
    }
    struct Kp2CA8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CA8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA8_2, false>(vu, c);
    }
    struct Kp2D08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D08_1, false>(vu, c);
    }
    struct Kp2F18_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F18_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_2, false>(vu, c);
    }
    struct Kp2F78_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_2, false>(vu, c);
    }
    struct Kp2FD8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_2, false>(vu, c);
    }
    struct Kp3248_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_2, false>(vu, c);
    }
    struct Kp32A8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_2, false>(vu, c);
    }
    struct Kp3308_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_2, false>(vu, c);
    }
    struct Kp3578_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3578_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3578_2, false>(vu, c);
    }
    struct Kp35D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_2, false>(vu, c);
    }
    struct Kp3638_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3638_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_2, false>(vu, c);
    }
    struct Kp3698_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3698_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_2, false>(vu, c);
    }
    struct Kp3908_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3908_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3908_2, false>(vu, c);
    }
    struct Kp3968_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3968_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_2, false>(vu, c);
    }
    struct Kp39D0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39D0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_2, false>(vu, c);
    }
    struct Kp3C40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1e6393cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_1, false>(vu, c);
    }
    struct Kp3CA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1eb216bu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_1, false>(vu, c);
    }
    struct Kp3D38_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D38_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_2, false>(vu, c);
    }
    struct Kp2880_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_4, false>(vu, c);
    }
    struct Kp28E0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28E0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_4, false>(vu, c);
    }
    struct Kp2940_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2940_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_3, false>(vu, c);
    }
    struct Kp29A0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29A0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A0_2, false>(vu, c);
    }
    struct Kp2A00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A00_1, false>(vu, c);
    }
    struct Kp2A60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A60_1, false>(vu, c);
    }
    struct Kp2CA8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CA8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA8_3, false>(vu, c);
    }
    struct Kp2F28_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_3, false>(vu, c);
    }
    struct Kp2F88_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F88_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F88_3, false>(vu, c);
    }
    struct Kp2FE8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE8_2, false>(vu, c);
    }
    struct Kp3260_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_3, false>(vu, c);
    }
    struct Kp32C0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C0_3, false>(vu, c);
    }
    struct Kp38F8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_3, false>(vu, c);
    }
    struct Kp3958_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3958_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_3, false>(vu, c);
    }
    struct Kp39B8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_3, false>(vu, c);
    }
    struct Kp3C60_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_3, false>(vu, c);
    }
    struct Kp3CC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_1, false>(vu, c);
    }
    struct Kp3D20_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D20_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_3, false>(vu, c);
    }
    struct Kp3D80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D80_1, false>(vu, c);
    }
    struct Kp2880_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_5, false>(vu, c);
    }
    struct Kp28E0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_5, false>(vu, c);
    }
    struct Kp2B90_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_4, false>(vu, c);
    }
    struct Kp2BF0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2BF0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_4, false>(vu, c);
    }
    struct Kp3678_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3678_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_3, false>(vu, c);
    }
    struct Kp38F0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_4, false>(vu, c);
    }
    struct Kp3950_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3950_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_4, false>(vu, c);
    }
    struct Kp3C30_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_3, false>(vu, c);
    }
    struct Kp3C90_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f1u; p.upper = 0x1e2b10au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_3, false>(vu, c);
    }
    struct Kp3CF0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_3, false>(vu, c);
    }
    struct Kp2918_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2918_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_6, false>(vu, c);
    }
    struct Kp2BC0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_5, false>(vu, c);
    }
    struct Kp2C20_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C20_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C20_4, false>(vu, c);
    }
    struct Kp2C80_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2C80_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_5, false>(vu, c);
    }
    struct Kp2F30_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_4, false>(vu, c);
    }
    struct Kp2FC0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_4, false>(vu, c);
    }
    struct Kp3020_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3020_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3020_1, false>(vu, c);
    }
    struct Kp3258_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_4, false>(vu, c);
    }
    struct Kp32B8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e0211fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_4, false>(vu, c);
    }
    struct Kp3318_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_4, false>(vu, c);
    }
    struct Kp3378_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3378_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3378_2, false>(vu, c);
    }
    struct Kp3590_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_3, false>(vu, c);
    }
    struct Kp35F0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_3, false>(vu, c);
    }
    struct Kp3650_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3650_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_4, false>(vu, c);
    }
    struct Kp36B8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B8_2, false>(vu, c);
    }
    struct Kp3910_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_5, false>(vu, c);
    }
    struct Kp39F0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39F0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_3, false>(vu, c);
    }
    struct Kp2900_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2900_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_7, false>(vu, c);
    }
    struct Kp2C40_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C40_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_4, false>(vu, c);
    }
    struct Kp2FA0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FA0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_4, false>(vu, c);
    }
    struct Kp3318_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3318_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_5, false>(vu, c);
    }
    struct Kp35C0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_4, false>(vu, c);
    }
    struct Kp3620_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3620_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3620_4, false>(vu, c);
    }
    struct Kp38D0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_5, false>(vu, c);
    }
    struct Kp3930_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_5, false>(vu, c);
    }
    struct Kp3990_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3990_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_5, false>(vu, c);
    }
    struct Kp39F0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_4, false>(vu, c);
    }
    struct Kp3C28_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_4, false>(vu, c);
    }
    struct Kp3C88_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_4, false>(vu, c);
    }
    struct Kp3CE8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_4, false>(vu, c);
    }
    struct Kp3D50_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D50_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D50_3, false>(vu, c);
    }
    struct Kp3DB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DB0_1, false>(vu, c);
    }
    struct Kp2898_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_6, false>(vu, c);
    }
    struct Kp2930_8
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_8(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_8, false>(vu, c);
    }
    struct Kp2990_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2990_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_3, false>(vu, c);
    }
    struct Kp2BC8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_6, false>(vu, c);
    }
    struct Kp2C28_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C28_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_6, false>(vu, c);
    }
    struct Kp2C88_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C88_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C88_4, false>(vu, c);
    }
    struct Kp2CE8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e0215fu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE8_2, false>(vu, c);
    }
    struct Kp2F20_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_6, false>(vu, c);
    }
    struct Kp2F80_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F80_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_4, false>(vu, c);
    }
    struct Kp2FE8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FE8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE8_4, false>(vu, c);
    }
    struct Kp3048_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3048_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3048_2, false>(vu, c);
    }
    struct Kp3660_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_6, false>(vu, c);
    }
    struct Kp39D0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39D0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_6, false>(vu, c);
    }
    struct Kp3C70_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_5, false>(vu, c);
    }
    struct Kp3CD0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_5, false>(vu, c);
    }
    struct Kp3238_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_5, false>(vu, c);
    }
    struct Kp3298_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3298_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_5, false>(vu, c);
    }
    struct Kp32F8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32F8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_5, false>(vu, c);
    }
    struct Kp35A8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_5, false>(vu, c);
    }
    struct Kp3608_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3608_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_5, false>(vu, c);
    }
    struct Kp2FA8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_5, false>(vu, c);
    }
    struct Kp3318_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_7, false>(vu, c);
    }
    struct Kp01F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800403bdu; p.upper = 0x1c2a8bdu; p.lowerUsage.vfRead[0] = {4, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F0_2d, true>(vu, c);
    }
    struct Kp0448_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ed5811u; p.upper = 0x1e06327u; p.lowerUsage.vfWrite = {13, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0448_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0448_2d, true>(vu, c);
    }
    struct Kp0550_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x109604eu; p.upper = 0x18840e9u; p.lowerUsage.vfWrite = {9, 8}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {8, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0550_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0550_2d, true>(vu, c);
    }
    struct Kp0620_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec3051u; p.upper = 0x1f4340au; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0620_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0620_2d, true>(vu, c);
    }
    struct Kp0700_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18ab498u; p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0700_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0700_2d, true>(vu, c);
    }
    struct Kp07C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x5630bfu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07C0_2d, true>(vu, c);
    }
    struct Kp0C98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f66040u; p.upper = 0x1dfc8bdu; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C98_2d, true>(vu, c);
    }
    struct Kp0EE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ed5811u; p.upper = 0x1e06327u; p.lowerUsage.vfWrite = {13, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE8_2d, true>(vu, c);
    }
    struct Kp0FA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec360au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {24, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FA0_2d, true>(vu, c);
    }
    struct Kp1058_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x5430bfu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1058_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1058_2d, true>(vu, c);
    }
    struct Kp10D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed134eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D8_2d, true>(vu, c);
    }
    struct Kp11A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5630bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A8_2d, true>(vu, c);
    }
    struct Kp18B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80265bfdu; p.upper = 0x4000c3u; p.lowerUsage.vfWrite = {6, 1}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {3, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B0_2d, true>(vu, c);
    }
    struct Kp1A90_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c34801u; p.upper = 0x208900u; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {17, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A90_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A90_2d, true>(vu, c);
    }
    struct Kp1DB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2096cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB8_2d, true>(vu, c);
    }
    struct Kp2070_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c1a9bfu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2070_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2070_2d, true>(vu, c);
    }
    struct Kp2270_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2270_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2270_2d, true>(vu, c);
    }
    struct Kp23B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x11cd9bdu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 8}; p.upperUsage.vfRead[1] = {28, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23B0_2d, true>(vu, c);
    }
    struct Kp24F0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1450a18u; p.upperUsage.vfRead[0] = {1, 10}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {8, 10}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24F0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24F0_1d, true>(vu, c);
    }
    struct Kp2658_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1608au; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2658_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2658_1d, true>(vu, c);
    }
    struct Kp29D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D8_2d, true>(vu, c);
    }
    struct Kp2C48_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_6d, true>(vu, c);
    }
    struct Kp3240_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_6d, true>(vu, c);
    }
    struct Kp3338_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_5d, true>(vu, c);
    }
    struct Kp35D0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_6d, true>(vu, c);
    }
    struct Kp36B8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B8_3d, true>(vu, c);
    }
    struct Kp3928_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_6d, true>(vu, c);
    }
    struct Kp3A08_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A08_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A08_3d, true>(vu, c);
    }
    struct Kp3A78_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A78_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A78_1d, true>(vu, c);
    }
    struct Kp0290_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x80bfffeau; p.upperUsage.vfRead[0] = {31, 5}; p.upperUsage.vfWrite = {31, 5}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0290_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0290_2d, true>(vu, c);
    }
    struct Kp06B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff10beu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B8_2d, true>(vu, c);
    }
    struct Kp0880_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0880_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0880_2d, true>(vu, c);
    }
    struct Kp0990_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0990_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0990_2d, true>(vu, c);
    }
    struct Kp0A30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10020088u; p.upper = 0x105f945u; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A30_2d, true>(vu, c);
    }
    struct Kp0AC8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8208du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AC8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AC8_2d, true>(vu, c);
    }
    struct Kp0B60_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xe002fcu; p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 7; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B60_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B60_2d, true>(vu, c);
    }
    struct Kp0C38_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x45f9c1u; p.upperUsage.vfRead[0] = {31, 2}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C38_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C38_2d, true>(vu, c);
    }
    struct Kp0CA0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8204cu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 8}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CA0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA0_3d, true>(vu, c);
    }
    struct Kp0D38_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0003fu; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D38_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D38_2d, true>(vu, c);
    }
    struct Kp0FB8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FB8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB8_3d, true>(vu, c);
    }
    struct Kp1020_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5218bu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1020_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1020_2d, true>(vu, c);
    }
    struct Kp1168_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e198cfu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1168_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1168_3d, true>(vu, c);
    }
    struct Kp12D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2f0bdau; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D0_2d, true>(vu, c);
    }
    struct Kp1390_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1390_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1390_2d, true>(vu, c);
    }
    struct Kp14B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B8_2d, true>(vu, c);
    }
    struct Kp1580_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b400000u; p.upper = 0x81e039feu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1580_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1580_2d, true>(vu, c);
    }
    struct Kp15E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x421ed7b7u; p.upper = 0x81e24abeu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E8_2d, true>(vu, c);
    }
    struct Kp1660_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180283cu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1660_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1660_2d, true>(vu, c);
    }
    struct Kp1780_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1780_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1780_2d, true>(vu, c);
    }
    struct Kp17F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf29c8u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F8_2d, true>(vu, c);
    }
    struct Kp1858_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c89a29u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1858_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1858_2d, true>(vu, c);
    }
    struct Kp19C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19C0_2d, true>(vu, c);
    }
    struct Kp1AE8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4d10au; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AE8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AE8_3d, true>(vu, c);
    }
    struct Kp1B48_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c699a9u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B48_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B48_2d, true>(vu, c);
    }
    struct Kp1C90_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C90_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C90_2d, true>(vu, c);
    }
    struct Kp1DD0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD0_3d, true>(vu, c);
    }
    struct Kp1E80_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1818858u; p.upperUsage.vfRead[0] = {17, 12}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E80_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E80_2d, true>(vu, c);
    }
    struct Kp1FB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x81e1990fu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1FB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FB0_2d, true>(vu, c);
    }
    struct Kp20C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18018a7u; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C8_2d, true>(vu, c);
    }
    struct Kp21D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eab28au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {10, 2}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D0_2d, true>(vu, c);
    }
    struct Kp2250_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1daed8bu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {26, 1}; p.upperUsage.vfWrite = {22, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2250_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2250_3d, true>(vu, c);
    }
    struct Kp23F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a7fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F8_2d, true>(vu, c);
    }
    struct Kp2468_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eda6de1u; p.upper = 0x81e73a6au; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2468_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2468_2d, true>(vu, c);
    }
    struct Kp24C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e631a9u; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C8_2d, true>(vu, c);
    }
    struct Kp28C0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x224a47u; p.upperUsage.vfRead[0] = {9, 1}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_7d, true>(vu, c);
    }
    struct Kp2BB8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_7d, true>(vu, c);
    }
    struct Kp2D28_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D28_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D28_1d, true>(vu, c);
    }
    struct Kp2F10_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_6d, true>(vu, c);
    }
    struct Kp2FF0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FF0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_5d, true>(vu, c);
    }
    struct Kp30C0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30C0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30C0_1d, true>(vu, c);
    }
    struct Kp3298_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_6d, true>(vu, c);
    }
    struct Kp3380_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3380_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3380_3d, true>(vu, c);
    }
    struct Kp33E8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33E8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33E8_1d, true>(vu, c);
    }
    struct Kp3668_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_9d, true>(vu, c);
    }
    struct Kp38E0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_6d, true>(vu, c);
    }
    struct Kp3D00_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_8d, true>(vu, c);
    }
    struct Kp2890_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_8d, true>(vu, c);
    }
    struct Kp3D00_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_9d, true>(vu, c);
    }
    struct Kp28A8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_9d, true>(vu, c);
    }
    struct Kp2990_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2990_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_4d, true>(vu, c);
    }
    struct Kp2C00_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_8d, true>(vu, c);
    }
    struct Kp2CE8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE8_3d, true>(vu, c);
    }
    struct Kp2F58_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_6d, true>(vu, c);
    }
    struct Kp35D0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_7d, true>(vu, c);
    }
    struct Kp38E8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_7d, true>(vu, c);
    }
    struct Kp3C30_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_7d, true>(vu, c);
    }
    struct Kp3D28_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D28_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D28_5d, true>(vu, c);
    }
    struct Kp2890_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_10d, true>(vu, c);
    }
    struct Kp2910_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2910_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_8d, true>(vu, c);
    }
    struct Kp29E0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E0_3d, true>(vu, c);
    }
    struct Kp2EF0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_7d, true>(vu, c);
    }
    struct Kp38D0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_7d, true>(vu, c);
    }
    struct Kp39C0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_8d, true>(vu, c);
    }
    struct Kp3C90_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_7d, true>(vu, c);
    }
    struct Kp2840_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_8d, true>(vu, c);
    }
    struct Kp2BD0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_8d, true>(vu, c);
    }
    struct Kp39A8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_8d, true>(vu, c);
    }
    struct Kp2B90_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_9d, true>(vu, c);
    }
    struct Kp2F20_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_8d, true>(vu, c);
    }
    struct Kp3008_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3008_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_5d, true>(vu, c);
    }
    struct Kp3298_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_8d, true>(vu, c);
    }
    struct Kp3380_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3380_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3380_4d, true>(vu, c);
    }
    struct Kp35F0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_8d, true>(vu, c);
    }
    struct Kp36D8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D8_3d, true>(vu, c);
    }
    struct Kp2918_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_10d, true>(vu, c);
    }
    struct Kp3598_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_9d, true>(vu, c);
    }
    struct Kp3928_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_9d, true>(vu, c);
    }
    struct Kp3A10_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A10_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A10_4d, true>(vu, c);
    }
    struct Kp3C80_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_8d, true>(vu, c);
    }
    struct Kp3D68_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D68_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D68_4d, true>(vu, c);
    }
    struct Kp2858_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_11d, true>(vu, c);
    }
    struct Kp2958_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2958_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_6d, true>(vu, c);
    }
    struct Kp2BE8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_10d, true>(vu, c);
    }
    struct Kp2CD0_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD0_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD0_4d, true>(vu, c);
    }
    struct Kp2F40_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F40_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_8d, true>(vu, c);
    }
    struct Kp3028_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3028_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3028_4d, true>(vu, c);
    }
    struct Kp3990_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3990_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_7d, true>(vu, c);
    }
    struct Kp3250_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_9d, true>(vu, c);
    }
    struct Kp35D8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_9d, true>(vu, c);
    }
    struct Kp3320_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_9d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
