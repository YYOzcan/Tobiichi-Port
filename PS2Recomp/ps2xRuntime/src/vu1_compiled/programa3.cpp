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
    struct Kp0010_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c06bdu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0010_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0010_0, false>(vu, c);
    }
    struct Kp0070_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800001f0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0070_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0070_0, false>(vu, c);
    }
    struct Kp00D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00D0_0, false>(vu, c);
    }
    struct Kp0130_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c5af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6144; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0130_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0130_0, false>(vu, c);
    }
    struct Kp0190_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800352b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1032; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0190_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0190_0, false>(vu, c);
    }
    struct Kp01F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800403bdu; p.upper = 0x1c2a8bdu; p.lowerUsage.vfRead[0] = {4, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F0_0, false>(vu, c);
    }
    struct Kp0250_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2482du; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0250_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0250_0, false>(vu, c);
    }
    struct Kp02B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02B0_0, false>(vu, c);
    }
    struct Kp0310_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0310_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0310_0, false>(vu, c);
    }
    struct Kp0370_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0370_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0370_0, false>(vu, c);
    }
    struct Kp03D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80063170u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03D0_0, false>(vu, c);
    }
    struct Kp0430_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806b0bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0430_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0430_0, false>(vu, c);
    }
    struct Kp0490_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e604eu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {30, 1}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0490_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0490_0, false>(vu, c);
    }
    struct Kp04F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e001835u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04F0_0, false>(vu, c);
    }
    struct Kp0550_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x109604eu; p.upper = 0x18840e9u; p.lowerUsage.vfWrite = {9, 8}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {8, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0550_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0550_0, false>(vu, c);
    }
    struct Kp05B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2bef47u; p.upperUsage.vfRead[0] = {29, 1}; p.upperUsage.vfRead[1] = {11, 1}; p.upperUsage.vfWrite = {29, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05B0_0, false>(vu, c);
    }
    struct Kp0610_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec204fu; p.upper = 0x1f421bcu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {20, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0610_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0610_0, false>(vu, c);
    }
    struct Kp0670_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0670_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0670_0, false>(vu, c);
    }
    struct Kp06D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8048033du; p.upper = 0x1c00243u; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {8, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06D0_0, false>(vu, c);
    }
    struct Kp0730_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58002005u; p.upper = 0x1e0ffe2u; p.lowerUsage.viRead = 16; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfWrite = {31, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0730_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0730_0, false>(vu, c);
    }
    struct Kp0790_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x5430bfu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0790_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0790_0, false>(vu, c);
    }
    struct Kp07F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4c30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {12, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07F0_0, false>(vu, c);
    }
    struct Kp0850_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0850_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0850_0, false>(vu, c);
    }
    struct Kp08B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e0037fbu; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08B0_0, false>(vu, c);
    }
    struct Kp0910_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84a03a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0910_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0910_0, false>(vu, c);
    }
    struct Kp0970_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000009u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0970_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0970_0, false>(vu, c);
    }
    struct Kp09D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10056800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09D0_0, false>(vu, c);
    }
    struct Kp0A30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800110b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A30_0, false>(vu, c);
    }
    struct Kp0A90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80042971u; p.upper = 0x2ffu; p.lowerUsage.viRead = 48; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A90_0, false>(vu, c);
    }
    struct Kp0AF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa232fffu; p.upper = 0x2ffu; p.lowerUsage.viRead = 40; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AF0_0, false>(vu, c);
    }
    struct Kp0B50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90803a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B50_0, false>(vu, c);
    }
    struct Kp0BB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BB0_0, false>(vu, c);
    }
    struct Kp0C10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400006eeu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C10_0, false>(vu, c);
    }
    struct Kp0C70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f81810u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {24, 15}; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C70_0, false>(vu, c);
    }
    struct Kp0CD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1dfd74au; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfWrite = {29, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD0_0, false>(vu, c);
    }
    struct Kp0D30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1003003fu; p.upper = 0x1cf79ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D30_0, false>(vu, c);
    }
    struct Kp0D90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80034a74u; p.upper = 0x2ffu; p.lowerUsage.viRead = 520; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D90_0, false>(vu, c);
    }
    struct Kp0DF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4803a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DF0_0, false>(vu, c);
    }
    struct Kp0E50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f65812u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E50_0, false>(vu, c);
    }
    struct Kp0EB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b2134u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2064; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EB0_0, false>(vu, c);
    }
    struct Kp0F10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b9feu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F10_0, false>(vu, c);
    }
    struct Kp0F70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f5344au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {17, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F70_0, false>(vu, c);
    }
    struct Kp0FD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee368au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {14, 2}; p.upperUsage.vfWrite = {26, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD0_0, false>(vu, c);
    }
    struct Kp1030_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58002833u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1030_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1030_0, false>(vu, c);
    }
    struct Kp1090_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x1f6158eu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {22, 2}; p.upperUsage.vfWrite = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1090_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1090_0, false>(vu, c);
    }
    struct Kp10F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee138eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {14, 2}; p.upperUsage.vfWrite = {14, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10F0_0, false>(vu, c);
    }
    struct Kp1150_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e36040u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1150_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1150_0, false>(vu, c);
    }
    struct Kp11B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f6158eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {22, 2}; p.upperUsage.vfWrite = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11B0_0, false>(vu, c);
    }
    struct Kp1210_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1210_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1210_0, false>(vu, c);
    }
    struct Kp1270_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800018b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1270_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1270_0, false>(vu, c);
    }
    struct Kp12D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ed0800u; p.upper = 0x82093fu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 4}; p.upperUsage.vfWrite = {2, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D0_0, false>(vu, c);
    }
    struct Kp1330_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1330_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1330_0, false>(vu, c);
    }
    struct Kp1390_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1390_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1390_0, false>(vu, c);
    }
    struct Kp13F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F0_0, false>(vu, c);
    }
    struct Kp1450_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1450_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1450_0, false>(vu, c);
    }
    struct Kp14B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52060003u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B0_0, false>(vu, c);
    }
    struct Kp1510_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80004170u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1510_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1510_0, false>(vu, c);
    }
    struct Kp1570_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9096800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1570_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1570_0, false>(vu, c);
    }
    struct Kp15D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D0_0, false>(vu, c);
    }
    struct Kp1630_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 544; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1630_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1630_0, false>(vu, c);
    }
    struct Kp1690_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1690_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1690_0, false>(vu, c);
    }
    struct Kp16F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068b0u; p.upper = 0x6004ecu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {19, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16F0_0, false>(vu, c);
    }
    struct Kp1750_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5275u; p.upper = 0x219bc2u; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 1}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1750_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1750_0, false>(vu, c);
    }
    struct Kp17B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17B0_0, false>(vu, c);
    }
    struct Kp1810_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00400cu; p.upper = 0x1d182feu; p.lowerUsage.viRead = 256; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {16, 14}; p.upperUsage.vfRead[1] = {17, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1810_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1810_0, false>(vu, c);
    }
    struct Kp1870_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1870_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1870_0, false>(vu, c);
    }
    struct Kp18D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x814203fdu; p.upper = 0x21293cu; p.lowerUsage.vfWrite = {2, 10}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18D0_0, false>(vu, c);
    }
    struct Kp1930_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec0b7du; p.upper = 0x900387u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {16, 1}; p.upperUsage.vfWrite = {14, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1930_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1930_0, false>(vu, c);
    }
    struct Kp1990_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10450000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1990_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1990_0, false>(vu, c);
    }
    struct Kp19F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50060004u; p.upper = 0x82093fu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 4}; p.upperUsage.vfWrite = {2, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19F0_0, false>(vu, c);
    }
    struct Kp1A50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80044ab1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 528; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A50_0, false>(vu, c);
    }
    struct Kp1AB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9063045u; p.upper = 0x1801a3fu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB0_0, false>(vu, c);
    }
    struct Kp1B10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e94fffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B10_0, false>(vu, c);
    }
    struct Kp1B70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e179bcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B70_0, false>(vu, c);
    }
    struct Kp1BD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2220800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BD0_0, false>(vu, c);
    }
    struct Kp1C30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80050874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C30_0, false>(vu, c);
    }
    struct Kp1C90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C90_0, false>(vu, c);
    }
    struct Kp1CF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80050874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CF0_0, false>(vu, c);
    }
    struct Kp1D50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D50_0, false>(vu, c);
    }
    struct Kp1DB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca092au; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB0_0, false>(vu, c);
    }
    struct Kp1E10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c421ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E10_0, false>(vu, c);
    }
    struct Kp1E70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa211800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 10; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E70_0, false>(vu, c);
    }
    struct Kp1ED0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a9bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {19, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1ED0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1ED0_0, false>(vu, c);
    }
    struct Kp1F30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52080005u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F30_0, false>(vu, c);
    }
    struct Kp1F90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9bfu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F90_0, false>(vu, c);
    }
    struct Kp1FF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FF0_0, false>(vu, c);
    }
    struct Kp2050_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000004au; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2050_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2050_0, false>(vu, c);
    }
    struct Kp20B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1803a00u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20B0_0, false>(vu, c);
    }
    struct Kp2110_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e703bcu; p.upper = 0x1803a00u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {7, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2110_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2110_0, false>(vu, c);
    }
    struct Kp2170_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000056u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2170_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2170_0, false>(vu, c);
    }
    struct Kp21D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e103bcu; p.upper = 0x1c010dcu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D0_0, false>(vu, c);
    }
    struct Kp2230_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2230_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2230_0, false>(vu, c);
    }
    struct Kp2290_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32800u; p.upper = 0x1e031c0u; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2290_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2290_0, false>(vu, c);
    }
    struct Kp22F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f8u; p.upper = 0x1c0191cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22F0_0, false>(vu, c);
    }
    struct Kp2350_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1c010dcu; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2350_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2350_0, false>(vu, c);
    }
    struct Kp23B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x11cd9bdu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 8}; p.upperUsage.vfRead[1] = {28, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23B0_0, false>(vu, c);
    }
    struct Kp2410_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80610bfcu; p.upper = 0x1802ac0u; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {11, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2410_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2410_0, false>(vu, c);
    }
    struct Kp2470_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x56003fu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2470_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2470_0, false>(vu, c);
    }
    struct Kp24D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p24D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24D0_0, false>(vu, c);
    }
    struct Kp2530_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802d033cu; p.upper = 0x1ed631bu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {13, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2530_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2530_0, false>(vu, c);
    }
    struct Kp2590_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2590_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2590_0, false>(vu, c);
    }
    struct Kp25F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25F0_0, false>(vu, c);
    }
    struct Kp2650_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e158bdu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2650_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2650_0, false>(vu, c);
    }
    struct Kp26B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a002fe8u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26B0_0, false>(vu, c);
    }
    struct Kp2710_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2710_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2710_0, false>(vu, c);
    }
    struct Kp2770_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80600fbeu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 12; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2770_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2770_0, false>(vu, c);
    }
    struct Kp27D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3d75c28fu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p27D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27D0_0, false>(vu, c);
    }
    struct Kp2830_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2830_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2830_0, false>(vu, c);
    }
    struct Kp2890_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2890_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_0, false>(vu, c);
    }
    struct Kp28F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_0, false>(vu, c);
    }
    struct Kp2950_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2950_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_0, false>(vu, c);
    }
    struct Kp29B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B0_0, false>(vu, c);
    }
    struct Kp2A10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010071u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A10_0, false>(vu, c);
    }
    struct Kp2A70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A70_0, false>(vu, c);
    }
    struct Kp2AD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AD0_0, false>(vu, c);
    }
    struct Kp2B30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B30_0, false>(vu, c);
    }
    struct Kp2B90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_0, false>(vu, c);
    }
    struct Kp2BF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_0, false>(vu, c);
    }
    struct Kp2C50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C50_0, false>(vu, c);
    }
    struct Kp2EE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_0, false>(vu, c);
    }
    struct Kp2F40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_0, false>(vu, c);
    }
    struct Kp2FA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0295fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_0, false>(vu, c);
    }
    struct Kp3230_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_0, false>(vu, c);
    }
    struct Kp3290_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3290_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_0, false>(vu, c);
    }
    struct Kp32F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_0, false>(vu, c);
    }
    struct Kp3350_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3350_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3350_0, false>(vu, c);
    }
    struct Kp3570_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3570_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3570_0, false>(vu, c);
    }
    struct Kp35D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_0, false>(vu, c);
    }
    struct Kp3630_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3630_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_0, false>(vu, c);
    }
    struct Kp3690_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3690_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_0, false>(vu, c);
    }
    struct Kp36F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507eeu; p.upper = 0x1eb192bu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F0_0, false>(vu, c);
    }
    struct Kp38F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_0, false>(vu, c);
    }
    struct Kp3950_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3950_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_0, false>(vu, c);
    }
    struct Kp39B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_0, false>(vu, c);
    }
    struct Kp3A10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A10_0, false>(vu, c);
    }
    struct Kp3A70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A70_0, false>(vu, c);
    }
    struct Kp3AD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AD0_0, false>(vu, c);
    }
    struct Kp0038_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10060000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0038_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0038_1, false>(vu, c);
    }
    struct Kp00A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e1137cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.viLatency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00A0_1, false>(vu, c);
    }
    struct Kp0100_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800050b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0100_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0100_1, false>(vu, c);
    }
    struct Kp0160_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2230800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0160_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0160_1, false>(vu, c);
    }
    struct Kp01C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01C8_1, false>(vu, c);
    }
    struct Kp0228_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0228_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0228_1, false>(vu, c);
    }
    struct Kp0288_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8040fffeu; p.upper = 0x1e427e9u; p.lowerUsage.vfRead[0] = {31, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 44; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {31, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 31; return p; }();
    };
    bool p0288_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0288_1, false>(vu, c);
    }
    struct Kp02F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ea593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p02F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02F0_1, false>(vu, c);
    }
    struct Kp0350_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec633du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {12, 15}; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0350_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0350_1, false>(vu, c);
    }
    struct Kp03B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p03B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03B0_1, false>(vu, c);
    }
    struct Kp0410_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb613eu; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0410_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0410_1, false>(vu, c);
    }
    struct Kp0470_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80012970u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0470_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0470_1, false>(vu, c);
    }
    struct Kp04D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2137cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.viLatency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04D0_1, false>(vu, c);
    }
    struct Kp0530_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e91000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0530_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0530_1, false>(vu, c);
    }
    struct Kp0590_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1e20a6au; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0590_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0590_1, false>(vu, c);
    }
    struct Kp05F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3437du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F0_1, false>(vu, c);
    }
    struct Kp0650_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0650_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0650_1, false>(vu, c);
    }
    struct Kp06B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B0_1, false>(vu, c);
    }
    struct Kp0710_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f0000u; p.upper = 0x81ff1a49u; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0710_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0710_1, false>(vu, c);
    }
    struct Kp0770_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x102097cu; p.upperUsage.vfRead[0] = {1, 8}; p.upperUsage.vfWrite = {2, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0770_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0770_1, false>(vu, c);
    }
    struct Kp07D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p07D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07D0_1, false>(vu, c);
    }
    struct Kp0830_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e618fcu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0830_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0830_1, false>(vu, c);
    }
    struct Kp0890_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18428bcu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0890_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0890_1, false>(vu, c);
    }
    struct Kp08F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010080u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08F0_1, false>(vu, c);
    }
    struct Kp0950_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0950_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0950_1, false>(vu, c);
    }
    struct Kp09B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09B0_1, false>(vu, c);
    }
    struct Kp0A18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8931bfu; p.upperUsage.vfRead[0] = {6, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A18_1, false>(vu, c);
    }
    struct Kp0A80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x808529eau; p.upperUsage.vfRead[0] = {5, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0A80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A80_1, false>(vu, c);
    }
    struct Kp0AE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80290b3cu; p.upper = 0x1c90abcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AE0_1, false>(vu, c);
    }
    struct Kp0B40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x634999u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfWrite = {6, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B40_1, false>(vu, c);
    }
    struct Kp0BA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52010761u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BA0_1, false>(vu, c);
    }
    struct Kp0C00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x102319bu; p.upperUsage.vfRead[0] = {6, 8}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C00_1, false>(vu, c);
    }
    struct Kp0C60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c62199u; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C60_1, false>(vu, c);
    }
    struct Kp0CC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c820cfu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC0_1, false>(vu, c);
    }
    struct Kp0D20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e9417cu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D20_1, false>(vu, c);
    }
    struct Kp0D80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D80_1, false>(vu, c);
    }
    struct Kp0DE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DE0_1, false>(vu, c);
    }
    struct Kp0E40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e07f0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E40_1, false>(vu, c);
    }
    struct Kp0EA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EA0_1, false>(vu, c);
    }
    struct Kp0F00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107d5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F00_1, false>(vu, c);
    }
    struct Kp0F60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F60_1, false>(vu, c);
    }
    struct Kp0FC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC0_1, false>(vu, c);
    }
    struct Kp1020_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5218bu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1020_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1020_1, false>(vu, c);
    }
    struct Kp1080_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107a5u; p.upper = 0x1e6317cu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1080_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1080_1, false>(vu, c);
    }
    struct Kp10E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e07a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10E0_1, false>(vu, c);
    }
    struct Kp1140_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1140_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1140_1, false>(vu, c);
    }
    struct Kp11A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52010781u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A0_1, false>(vu, c);
    }
    struct Kp1200_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x119cbc1u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1200_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1200_1, false>(vu, c);
    }
    struct Kp1260_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1260_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1260_1, false>(vu, c);
    }
    struct Kp12C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C0_1, false>(vu, c);
    }
    struct Kp1328_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e0115cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1328_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1328_1, false>(vu, c);
    }
    struct Kp1388_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b0803u; p.upper = 0x92912bu; p.lowerUsage.vfRead[0] = {1, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 4}; p.upperUsage.vfWrite = {4, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1388_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1388_1, false>(vu, c);
    }
    struct Kp13F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x119cbc1u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F0_1, false>(vu, c);
    }
    struct Kp1450_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1450_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1450_1, false>(vu, c);
    }
    struct Kp14B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B0_1, false>(vu, c);
    }
    struct Kp1510_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20089eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1510_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1510_1, false>(vu, c);
    }
    struct Kp1570_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbe22f983u; p.upper = 0x81e739fdu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1570_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1570_1, false>(vu, c);
    }
    struct Kp15D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e03a1eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D0_1, false>(vu, c);
    }
    struct Kp1630_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1827a19u; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1630_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1630_1, false>(vu, c);
    }
    struct Kp1690_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b0803u; p.upper = 0x92912bu; p.lowerUsage.vfRead[0] = {1, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 4}; p.upperUsage.vfWrite = {4, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1690_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1690_1, false>(vu, c);
    }
    struct Kp16F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16F0_1, false>(vu, c);
    }
    struct Kp1750_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1750_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1750_1, false>(vu, c);
    }
    struct Kp17B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c02f3fu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 24; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17B0_1, false>(vu, c);
    }
    struct Kp1810_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2a08u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1810_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1810_1, false>(vu, c);
    }
    struct Kp1870_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c631ffu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1870_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1870_1, false>(vu, c);
    }
    struct Kp18D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb0b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18D0_1, false>(vu, c);
    }
    struct Kp1930_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1930_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1930_1, false>(vu, c);
    }
    struct Kp1990_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1990_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1990_1, false>(vu, c);
    }
    struct Kp19F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19F0_1, false>(vu, c);
    }
    struct Kp1A50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef0804u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A50_1, false>(vu, c);
    }
    struct Kp1AB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1295bu; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB0_1, false>(vu, c);
    }
    struct Kp1B10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B10_1, false>(vu, c);
    }
    struct Kp1B70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x29024eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {9, 2}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B70_1, false>(vu, c);
    }
    struct Kp1BD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10222u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BD0_1, false>(vu, c);
    }
    struct Kp1C30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8101933cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 8}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C30_1, false>(vu, c);
    }
    struct Kp1C90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C90_1, false>(vu, c);
    }
    struct Kp1CF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CF0_1, false>(vu, c);
    }
    struct Kp1D50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10802u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D50_1, false>(vu, c);
    }
    struct Kp1DB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1DB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB0_1, false>(vu, c);
    }
    struct Kp1E10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20089eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E10_1, false>(vu, c);
    }
    struct Kp1E70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055af0u; p.upper = 0x1e128e8u; p.lowerUsage.viRead = 2080; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E70_1, false>(vu, c);
    }
    struct Kp1ED0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e05deu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1ED0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1ED0_1, false>(vu, c);
    }
    struct Kp1F30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x910480u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {17, 8}; p.upperUsage.vfWrite = {18, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F30_1, false>(vu, c);
    }
    struct Kp1F90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F90_1, false>(vu, c);
    }
    struct Kp1FF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e0115cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FF0_1, false>(vu, c);
    }
    struct Kp2050_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x28b0800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2050_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2050_1, false>(vu, c);
    }
    struct Kp20B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x230225u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20B0_1, false>(vu, c);
    }
    struct Kp2110_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2110_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2110_1, false>(vu, c);
    }
    struct Kp2170_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb37ffu; p.upper = 0x1023968u; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 8}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2170_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2170_1, false>(vu, c);
    }
    struct Kp21D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eab28au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {10, 2}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D0_1, false>(vu, c);
    }
    struct Kp2230_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d8ed0bu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {24, 1}; p.upperUsage.vfWrite = {20, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2230_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2230_1, false>(vu, c);
    }
    struct Kp2290_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e056bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2290_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2290_1, false>(vu, c);
    }
    struct Kp22F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22F0_1, false>(vu, c);
    }
    struct Kp2350_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2350_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2350_1, false>(vu, c);
    }
    struct Kp23B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23B0_1, false>(vu, c);
    }
    struct Kp2410_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b400000u; p.upper = 0x81e00a3eu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2410_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2410_1, false>(vu, c);
    }
    struct Kp2470_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fd744fdu; p.upper = 0x81e02163u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2470_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2470_1, false>(vu, c);
    }
    struct Kp24D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087033cu; p.upper = 0x850304u; p.lowerUsage.vfRead[0] = {0, 4}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24D0_1, false>(vu, c);
    }
    struct Kp2880_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c15800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2880_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_1, false>(vu, c);
    }
    struct Kp28E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40400000u; p.upper = 0x81e1d08au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_1, false>(vu, c);
    }
    struct Kp2940_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2940_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_1, false>(vu, c);
    }
    struct Kp2BA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e1c8bdu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_1, false>(vu, c);
    }
    struct Kp2C00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_1, false>(vu, c);
    }
    struct Kp2C60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_1, false>(vu, c);
    }
    struct Kp2CC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2CC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC0_0, false>(vu, c);
    }
    struct Kp2D20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2D20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D20_0, false>(vu, c);
    }
    struct Kp2D80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D80_0, false>(vu, c);
    }
    struct Kp2F00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_1, false>(vu, c);
    }
    struct Kp2F60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_1, false>(vu, c);
    }
    struct Kp2FC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_1, false>(vu, c);
    }
    struct Kp3020_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3020_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3020_0, false>(vu, c);
    }
    struct Kp3080_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3080_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3080_0, false>(vu, c);
    }
    struct Kp30E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30E0_0, false>(vu, c);
    }
    struct Kp3268_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3268_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3268_1, false>(vu, c);
    }
    struct Kp32C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C8_1, false>(vu, c);
    }
    struct Kp3328_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3328_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3328_1, false>(vu, c);
    }
    struct Kp3388_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3388_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3388_1, false>(vu, c);
    }
    struct Kp33E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33E8_0, false>(vu, c);
    }
    struct Kp3448_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3448_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3448_0, false>(vu, c);
    }
    struct Kp35C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_1, false>(vu, c);
    }
    struct Kp3628_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3628_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_1, false>(vu, c);
    }
    struct Kp3688_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x187313eu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3688_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3688_1, false>(vu, c);
    }
    struct Kp36E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E8_1, false>(vu, c);
    }
    struct Kp3768_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3768_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3768_0, false>(vu, c);
    }
    struct Kp38E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_1, false>(vu, c);
    }
    struct Kp3948_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_1, false>(vu, c);
    }
    struct Kp39A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_1, false>(vu, c);
    }
    struct Kp3A08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A08_1, false>(vu, c);
    }
    struct Kp3C08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C08_0, false>(vu, c);
    }
    struct Kp3C68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_0, false>(vu, c);
    }
    struct Kp3CC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_0, false>(vu, c);
    }
    struct Kp3D28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D28_0, false>(vu, c);
    }
    struct Kp3D88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D88_0, false>(vu, c);
    }
    struct Kp3DE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DE8_0, false>(vu, c);
    }
    struct Kp2828_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2828_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2828_2, false>(vu, c);
    }
    struct Kp2890_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_2, false>(vu, c);
    }
    struct Kp28F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_2, false>(vu, c);
    }
    struct Kp2B98_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_2, false>(vu, c);
    }
    struct Kp2BF8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_2, false>(vu, c);
    }
    struct Kp2C88_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C88_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C88_2, false>(vu, c);
    }
    struct Kp3CF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_1, false>(vu, c);
    }
    struct Kp2840_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_3, false>(vu, c);
    }
    struct Kp28A0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_3, false>(vu, c);
    }
    struct Kp2900_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2900_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_3, false>(vu, c);
    }
    struct Kp2960_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2960_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_2, false>(vu, c);
    }
    struct Kp29C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C0_1, false>(vu, c);
    }
    struct Kp2BD0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_3, false>(vu, c);
    }
    struct Kp2C30_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2C30_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C30_2, false>(vu, c);
    }
    struct Kp2C98_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C98_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C98_2, false>(vu, c);
    }
    struct Kp2CF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CF8_1, false>(vu, c);
    }
    struct Kp2F08_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_2, false>(vu, c);
    }
    struct Kp2F68_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F68_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_2, false>(vu, c);
    }
    struct Kp2FC8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_2, false>(vu, c);
    }
    struct Kp3238_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_2, false>(vu, c);
    }
    struct Kp3298_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_2, false>(vu, c);
    }
    struct Kp32F8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_2, false>(vu, c);
    }
    struct Kp3358_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3358_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_2, false>(vu, c);
    }
    struct Kp35C8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_2, false>(vu, c);
    }
    struct Kp3628_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3628_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_2, false>(vu, c);
    }
    struct Kp3688_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3688_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3688_2, false>(vu, c);
    }
    struct Kp38F8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_2, false>(vu, c);
    }
    struct Kp3958_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3958_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_2, false>(vu, c);
    }
    struct Kp39B8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_2, false>(vu, c);
    }
    struct Kp3C30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_1, false>(vu, c);
    }
    struct Kp3C90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_1, false>(vu, c);
    }
    struct Kp3D28_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D28_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D28_2, false>(vu, c);
    }
    struct Kp2870_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_4, false>(vu, c);
    }
    struct Kp28D0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_4, false>(vu, c);
    }
    struct Kp2930_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_4, false>(vu, c);
    }
    struct Kp2990_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2990_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_2, false>(vu, c);
    }
    struct Kp29F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29F0_1, false>(vu, c);
    }
    struct Kp2A50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A50_1, false>(vu, c);
    }
    struct Kp2C98_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x187313eu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C98_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C98_3, false>(vu, c);
    }
    struct Kp2F18_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F18_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_3, false>(vu, c);
    }
    struct Kp2F78_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7817u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F78_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_3, false>(vu, c);
    }
    struct Kp2FD8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FD8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_3, false>(vu, c);
    }
    struct Kp3250_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_3, false>(vu, c);
    }
    struct Kp32B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_3, false>(vu, c);
    }
    struct Kp38E8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_3, false>(vu, c);
    }
    struct Kp3948_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_3, false>(vu, c);
    }
    struct Kp39A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_3, false>(vu, c);
    }
    struct Kp3C50_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_2, false>(vu, c);
    }
    struct Kp3CB0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB0_2, false>(vu, c);
    }
    struct Kp3D10_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D10_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_3, false>(vu, c);
    }
    struct Kp3D70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3D70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D70_1, false>(vu, c);
    }
    struct Kp2870_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_5, false>(vu, c);
    }
    struct Kp28D0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28D0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_5, false>(vu, c);
    }
    struct Kp2930_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2930_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_5, false>(vu, c);
    }
    struct Kp2BE0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_4, false>(vu, c);
    }
    struct Kp3668_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3668_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_3, false>(vu, c);
    }
    struct Kp38E0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_4, false>(vu, c);
    }
    struct Kp3940_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_4, false>(vu, c);
    }
    struct Kp3C20_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_3, false>(vu, c);
    }
    struct Kp3C80_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_3, false>(vu, c);
    }
    struct Kp3CE0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_3, false>(vu, c);
    }
    struct Kp2908_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2908_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_6, false>(vu, c);
    }
    struct Kp2BB0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_5, false>(vu, c);
    }
    struct Kp2C10_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C10_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_4, false>(vu, c);
    }
    struct Kp2C70_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_5, false>(vu, c);
    }
    struct Kp2F20_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_4, false>(vu, c);
    }
    struct Kp2FB0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FB0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_4, false>(vu, c);
    }
    struct Kp3010_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3010_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3010_2, false>(vu, c);
    }
    struct Kp3248_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_4, false>(vu, c);
    }
    struct Kp32A8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_4, false>(vu, c);
    }
    struct Kp3308_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3308_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_4, false>(vu, c);
    }
    struct Kp3368_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3368_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3368_2, false>(vu, c);
    }
    struct Kp3580_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_3, false>(vu, c);
    }
    struct Kp35E0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_3, false>(vu, c);
    }
    struct Kp3640_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3640_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_4, false>(vu, c);
    }
    struct Kp36A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A8_3, false>(vu, c);
    }
    struct Kp3708_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3708_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3708_1, false>(vu, c);
    }
    struct Kp39E0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39E0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E0_3, false>(vu, c);
    }
    struct Kp2880_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_6, false>(vu, c);
    }
    struct Kp2958_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2958_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_4, false>(vu, c);
    }
    struct Kp2F20_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0429cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_5, false>(vu, c);
    }
    struct Kp3308_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3308_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_5, false>(vu, c);
    }
    struct Kp35B0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_4, false>(vu, c);
    }
    struct Kp3610_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3610_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_4, false>(vu, c);
    }
    struct Kp3670_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p3670_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_5, false>(vu, c);
    }
    struct Kp3920_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_5, false>(vu, c);
    }
    struct Kp3980_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3980_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3980_4, false>(vu, c);
    }
    struct Kp39E0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39E0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E0_4, false>(vu, c);
    }
    struct Kp3A40_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507eeu; p.upper = 0x1eb192bu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A40_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A40_2, false>(vu, c);
    }
    struct Kp3C78_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_4, false>(vu, c);
    }
    struct Kp3CD8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_4, false>(vu, c);
    }
    struct Kp3D40_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D40_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D40_4, false>(vu, c);
    }
    struct Kp3DA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DA0_1, false>(vu, c);
    }
    struct Kp2888_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_6, false>(vu, c);
    }
    struct Kp2920_8
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_8(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_8, false>(vu, c);
    }
    struct Kp2980_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2980_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2980_3, false>(vu, c);
    }
    struct Kp2BB8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_6, false>(vu, c);
    }
    struct Kp2C18_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e0211fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C18_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_5, false>(vu, c);
    }
    struct Kp2C78_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_7, false>(vu, c);
    }
    struct Kp2CD8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD8_2, false>(vu, c);
    }
    struct Kp2F10_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_5, false>(vu, c);
    }
    struct Kp2F70_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F70_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_5, false>(vu, c);
    }
    struct Kp2FD0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_6, false>(vu, c);
    }
    struct Kp3038_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3038_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3038_2, false>(vu, c);
    }
    struct Kp3650_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3650_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_6, false>(vu, c);
    }
    struct Kp39B8_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39B8_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_7, false>(vu, c);
    }
    struct Kp3C60_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_6, false>(vu, c);
    }
    struct Kp3CC0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_4, false>(vu, c);
    }
    struct Kp3228_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3228_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3228_3, false>(vu, c);
    }
    struct Kp3288_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_5, false>(vu, c);
    }
    struct Kp32E8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p32E8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_5, false>(vu, c);
    }
    struct Kp3598_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_5, false>(vu, c);
    }
    struct Kp35F8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_5, false>(vu, c);
    }
    struct Kp2F98_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F98_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_5, false>(vu, c);
    }
    struct Kp3308_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_7, false>(vu, c);
    }
    struct Kp01E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01E0_2d, true>(vu, c);
    }
    struct Kp0428_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbb000000u; p.upper = 0x80200862u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0428_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0428_2d, true>(vu, c);
    }
    struct Kp0520_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1866048u; p.upper = 0x1e7ef69u; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {29, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0520_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0520_2d, true>(vu, c);
    }
    struct Kp0610_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec204fu; p.upper = 0x1f421bcu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {20, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0610_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0610_2d, true>(vu, c);
    }
    struct Kp06F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aa418u; p.upperUsage.vfRead[0] = {20, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {16, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06F0_2d, true>(vu, c);
    }
    struct Kp07B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81f5154eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p07B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B0_2d, true>(vu, c);
    }
    struct Kp0C88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f76041u; p.upper = 0x1c0d83cu; p.lowerUsage.vfWrite = {23, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C88_2d, true>(vu, c);
    }
    struct Kp0EC8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbb000000u; p.upper = 0x80200862u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0EC8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC8_2d, true>(vu, c);
    }
    struct Kp0F90_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {12, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F90_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F90_2d, true>(vu, c);
    }
    struct Kp1018_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a6618u; p.upperUsage.vfRead[0] = {12, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {24, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1018_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1018_2d, true>(vu, c);
    }
    struct Kp10C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10C8_2d, true>(vu, c);
    }
    struct Kp1198_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x1f5154eu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1198_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1198_2d, true>(vu, c);
    }
    struct Kp18A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80244bfdu; p.upper = 0x1000043u; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18A0_2d, true>(vu, c);
    }
    struct Kp1A00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100203ecu; p.upper = 0x20006cu; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A00_2d, true>(vu, c);
    }
    struct Kp1DA8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca10edu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DA8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA8_2d, true>(vu, c);
    }
    struct Kp1F90_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9bfu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F90_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F90_2d, true>(vu, c);
    }
    struct Kp2258_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0edu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2258_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2258_2d, true>(vu, c);
    }
    struct Kp2350_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1c010dcu; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2350_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2350_2d, true>(vu, c);
    }
    struct Kp24E0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8107333du; p.upper = 0x460041u; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfWrite = {7, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24E0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24E0_1d, true>(vu, c);
    }
    struct Kp2648_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e150bcu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2648_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2648_1d, true>(vu, c);
    }
    struct Kp29C8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29C8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C8_3d, true>(vu, c);
    }
    struct Kp2BE0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_7d, true>(vu, c);
    }
    struct Kp3230_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_6d, true>(vu, c);
    }
    struct Kp3320_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_8d, true>(vu, c);
    }
    struct Kp35B0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_6d, true>(vu, c);
    }
    struct Kp3690_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3690_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_5d, true>(vu, c);
    }
    struct Kp3918_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_6d, true>(vu, c);
    }
    struct Kp3998_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3998_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_6d, true>(vu, c);
    }
    struct Kp3A68_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A68_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A68_1d, true>(vu, c);
    }
    struct Kp0280_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6218feu; p.upperUsage.vfRead[0] = {3, 3}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 3; p.upperUsage.accWrite = 3; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0280_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0280_2d, true>(vu, c);
    }
    struct Kp05D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05D0_2d, true>(vu, c);
    }
    struct Kp0870_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0870_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0870_2d, true>(vu, c);
    }
    struct Kp0970_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21002u; p.upper = 0x200240u; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0970_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0970_2d, true>(vu, c);
    }
    struct Kp0A20_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x89414fu; p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A20_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A20_2d, true>(vu, c);
    }
    struct Kp0AB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8204cu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 8}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AB8_2d, true>(vu, c);
    }
    struct Kp0B50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6349dau; p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {7, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B50_2d, true>(vu, c);
    }
    struct Kp0C28_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x808529eau; p.upperUsage.vfRead[0] = {5, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0C28_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C28_2d, true>(vu, c);
    }
    struct Kp0C88_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c749cbu; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C88_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C88_3d, true>(vu, c);
    }
    struct Kp0D18_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff0a18u; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D18_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D18_2d, true>(vu, c);
    }
    struct Kp0ED0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0ED0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0ED0_2d, true>(vu, c);
    }
    struct Kp1010_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x250144u; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1010_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1010_3d, true>(vu, c);
    }
    struct Kp1158_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1158_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1158_2d, true>(vu, c);
    }
    struct Kp12C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C0_2d, true>(vu, c);
    }
    struct Kp1370_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b8801u; p.upper = 0x8798c8u; p.lowerUsage.vfRead[0] = {17, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1370_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1370_2d, true>(vu, c);
    }
    struct Kp14A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A8_2d, true>(vu, c);
    }
    struct Kp1560_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fc90fdbu; p.upper = 0x802701dau; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1560_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1560_2d, true>(vu, c);
    }
    struct Kp15D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e210eau; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D8_2d, true>(vu, c);
    }
    struct Kp1640_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8740c0u; p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1640_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1640_2d, true>(vu, c);
    }
    struct Kp1770_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1770_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1770_2d, true>(vu, c);
    }
    struct Kp17E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce20bdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {14, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17E8_2d, true>(vu, c);
    }
    struct Kp1848_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c799e9u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1848_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1848_2d, true>(vu, c);
    }
    struct Kp1998_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1998_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1998_2d, true>(vu, c);
    }
    struct Kp1AD8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4c1bcu; p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AD8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AD8_2d, true>(vu, c);
    }
    struct Kp1B38_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x53003fu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {19, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B38_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B38_2d, true>(vu, c);
    }
    struct Kp1C48_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C48_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C48_2d, true>(vu, c);
    }
    struct Kp1DC0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC0_3d, true>(vu, c);
    }
    struct Kp1E70_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055af0u; p.upper = 0x1e128e8u; p.lowerUsage.viRead = 2080; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E70_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E70_2d, true>(vu, c);
    }
    struct Kp1FA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA0_2d, true>(vu, c);
    }
    struct Kp20B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18308dbu; p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20B8_2d, true>(vu, c);
    }
    struct Kp21C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eaa1bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C0_2d, true>(vu, c);
    }
    struct Kp2240_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d9ed4bu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {25, 1}; p.upperUsage.vfWrite = {21, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2240_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2240_2d, true>(vu, c);
    }
    struct Kp23E8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b400000u; p.upper = 0x81e00a3eu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p23E8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23E8_3d, true>(vu, c);
    }
    struct Kp2450_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc004c9feu; p.upper = 0x81e2112au; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2450_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2450_3d, true>(vu, c);
    }
    struct Kp24B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B8_2d, true>(vu, c);
    }
    struct Kp28B0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d1084bu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_8d, true>(vu, c);
    }
    struct Kp2BA0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e1c8bdu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_8d, true>(vu, c);
    }
    struct Kp2CC0_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2CC0_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC0_4d, true>(vu, c);
    }
    struct Kp2F00_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_7d, true>(vu, c);
    }
    struct Kp2FE0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_7d, true>(vu, c);
    }
    struct Kp3098_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3098_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3098_1d, true>(vu, c);
    }
    struct Kp3288_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_7d, true>(vu, c);
    }
    struct Kp3368_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3368_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3368_3d, true>(vu, c);
    }
    struct Kp33D8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33D8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33D8_1d, true>(vu, c);
    }
    struct Kp3658_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_8d, true>(vu, c);
    }
    struct Kp3768_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3768_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3768_1d, true>(vu, c);
    }
    struct Kp3C98_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_6d, true>(vu, c);
    }
    struct Kp2848_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_7d, true>(vu, c);
    }
    struct Kp2C70_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_9d, true>(vu, c);
    }
    struct Kp2898_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_9d, true>(vu, c);
    }
    struct Kp2980_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2980_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2980_4d, true>(vu, c);
    }
    struct Kp2BF0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_7d, true>(vu, c);
    }
    struct Kp2CD8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD8_3d, true>(vu, c);
    }
    struct Kp2F48_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_7d, true>(vu, c);
    }
    struct Kp3588_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_6d, true>(vu, c);
    }
    struct Kp38D0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_6d, true>(vu, c);
    }
    struct Kp3C20_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_6d, true>(vu, c);
    }
    struct Kp3D10_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D10_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_9d, true>(vu, c);
    }
    struct Kp2878_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2878_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_7d, true>(vu, c);
    }
    struct Kp28F8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_9d, true>(vu, c);
    }
    struct Kp29D0_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D0_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D0_4d, true>(vu, c);
    }
    struct Kp2C80_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_9d, true>(vu, c);
    }
    struct Kp3308_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_8d, true>(vu, c);
    }
    struct Kp39B0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_8d, true>(vu, c);
    }
    struct Kp3C80_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_7d, true>(vu, c);
    }
    struct Kp3D68_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D68_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D68_3d, true>(vu, c);
    }
    struct Kp2BA8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_10d, true>(vu, c);
    }
    struct Kp3940_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_7d, true>(vu, c);
    }
    struct Kp2900_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_9d, true>(vu, c);
    }
    struct Kp2EF8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_9d, true>(vu, c);
    }
    struct Kp2FF8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FF8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF8_5d, true>(vu, c);
    }
    struct Kp3288_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_9d, true>(vu, c);
    }
    struct Kp3370_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3370_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3370_4d, true>(vu, c);
    }
    struct Kp35E0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_7d, true>(vu, c);
    }
    struct Kp36C8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36C8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36C8_4d, true>(vu, c);
    }
    struct Kp39C0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_9d, true>(vu, c);
    }
    struct Kp3580_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_7d, true>(vu, c);
    }
    struct Kp3910_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_8d, true>(vu, c);
    }
    struct Kp39F8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F8_5d, true>(vu, c);
    }
    struct Kp3C70_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_9d, true>(vu, c);
    }
    struct Kp3CF0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_7d, true>(vu, c);
    }
    struct Kp2848_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_10d, true>(vu, c);
    }
    struct Kp2938_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2938_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_7d, true>(vu, c);
    }
    struct Kp2BD0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_9d, true>(vu, c);
    }
    struct Kp2CB8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB8_5d, true>(vu, c);
    }
    struct Kp2F30_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_9d, true>(vu, c);
    }
    struct Kp2FB0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_7d, true>(vu, c);
    }
    struct Kp3660_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_9d, true>(vu, c);
    }
    struct Kp3238_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_9d, true>(vu, c);
    }
    struct Kp35C8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_7d, true>(vu, c);
    }
    struct Kp3310_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_10d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
