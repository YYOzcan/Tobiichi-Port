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
    struct Kp0008_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000009u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0008_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0008_0, false>(vu, c);
    }
    struct Kp0068_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0068_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0068_0, false>(vu, c);
    }
    struct Kp00C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb016000u; p.upper = 0x400002ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.eBit = true; p.upperNop = true; return p; }();
    };
    bool p00C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00C8_0, false>(vu, c);
    }
    struct Kp0128_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806b0bfcu; p.upper = 0x22093fu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0128_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0128_0, false>(vu, c);
    }
    struct Kp0188_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000002fu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0188_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0188_0, false>(vu, c);
    }
    struct Kp01E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ea6043u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01E8_0, false>(vu, c);
    }
    struct Kp0248_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e24829u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0248_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0248_0, false>(vu, c);
    }
    struct Kp02A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80041874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02A8_0, false>(vu, c);
    }
    struct Kp0308_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0308_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0308_0, false>(vu, c);
    }
    struct Kp0368_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000803u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0368_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0368_0, false>(vu, c);
    }
    struct Kp03C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a51b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03C8_0, false>(vu, c);
    }
    struct Kp0428_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbb000000u; p.upper = 0x80200862u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0428_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0428_0, false>(vu, c);
    }
    struct Kp0488_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e7604cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0488_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0488_0, false>(vu, c);
    }
    struct Kp04E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E8_0, false>(vu, c);
    }
    struct Kp0548_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81222b3du; p.upper = 0x1852abdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfWrite = {2, 9}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0548_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0548_0, false>(vu, c);
    }
    struct Kp05A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2bef46u; p.upperUsage.vfRead[0] = {29, 1}; p.upperUsage.vfRead[1] = {11, 2}; p.upperUsage.vfWrite = {29, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05A8_0, false>(vu, c);
    }
    struct Kp0608_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea31aau; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0608_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0608_0, false>(vu, c);
    }
    struct Kp0668_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec360au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {24, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0668_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0668_0, false>(vu, c);
    }
    struct Kp06C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00080au; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06C8_0, false>(vu, c);
    }
    struct Kp0728_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p0728_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0728_0, false>(vu, c);
    }
    struct Kp0788_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800601f0u; p.upper = 0x1f41abeu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0788_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0788_0, false>(vu, c);
    }
    struct Kp07E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07E8_0, false>(vu, c);
    }
    struct Kp0848_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000175u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0848_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0848_0, false>(vu, c);
    }
    struct Kp08A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10021001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08A8_0, false>(vu, c);
    }
    struct Kp0908_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84d03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0908_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0908_0, false>(vu, c);
    }
    struct Kp0968_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0968_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0968_0, false>(vu, c);
    }
    struct Kp09C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa436045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4104; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C8_0, false>(vu, c);
    }
    struct Kp0A28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001003fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A28_0, false>(vu, c);
    }
    struct Kp0A88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e50b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A88_0, false>(vu, c);
    }
    struct Kp0AE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11031800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AE8_0, false>(vu, c);
    }
    struct Kp0B48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12026801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B48_0, false>(vu, c);
    }
    struct Kp0BA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BA8_0, false>(vu, c);
    }
    struct Kp0C08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C08_0, false>(vu, c);
    }
    struct Kp0C68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fb1813u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {27, 15}; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C68_0, false>(vu, c);
    }
    struct Kp0CC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d6801u; p.upper = 0x6004ecu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {19, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC8_0, false>(vu, c);
    }
    struct Kp0D28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500e0004u; p.upper = 0x1cff1ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {30, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D28_0, false>(vu, c);
    }
    struct Kp0D88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a4a75u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1536; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D88_0, false>(vu, c);
    }
    struct Kp0DE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007ddu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DE8_0, false>(vu, c);
    }
    struct Kp0E48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f55811u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E48_0, false>(vu, c);
    }
    struct Kp0EA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80095af5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2560; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EA8_0, false>(vu, c);
    }
    struct Kp0F08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e073a7u; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfWrite = {14, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F08_0, false>(vu, c);
    }
    struct Kp0F68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f528bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {21, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F68_0, false>(vu, c);
    }
    struct Kp0FC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {14, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC8_0, false>(vu, c);
    }
    struct Kp1028_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a7698u; p.upperUsage.vfRead[0] = {14, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {26, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1028_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1028_0, false>(vu, c);
    }
    struct Kp1088_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x5630bfu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1088_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1088_0, false>(vu, c);
    }
    struct Kp10E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4e30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {14, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10E8_0, false>(vu, c);
    }
    struct Kp1148_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c16041u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1148_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1148_0, false>(vu, c);
    }
    struct Kp11A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5630bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A8_0, false>(vu, c);
    }
    struct Kp1208_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5800303du; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1208_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1208_0, false>(vu, c);
    }
    struct Kp1268_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58004808u; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1268_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1268_0, false>(vu, c);
    }
    struct Kp12C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055174u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1056; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C8_0, false>(vu, c);
    }
    struct Kp1328_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1328_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1328_0, false>(vu, c);
    }
    struct Kp1388_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a39f4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1152; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1388_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1388_0, false>(vu, c);
    }
    struct Kp13E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400005a4u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13E8_0, false>(vu, c);
    }
    struct Kp1448_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84e03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1448_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1448_0, false>(vu, c);
    }
    struct Kp14A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e16800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A8_0, false>(vu, c);
    }
    struct Kp1508_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1508_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1508_0, false>(vu, c);
    }
    struct Kp1568_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a03a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1568_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1568_0, false>(vu, c);
    }
    struct Kp15C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c06bdu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C8_0, false>(vu, c);
    }
    struct Kp1628_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1628_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1628_0, false>(vu, c);
    }
    struct Kp1688_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1688_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1688_0, false>(vu, c);
    }
    struct Kp16E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9056800u; p.upper = 0x4004acu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {18, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16E8_0, false>(vu, c);
    }
    struct Kp1748_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5234u; p.upper = 0x2ffu; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1748_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1748_0, false>(vu, c);
    }
    struct Kp17A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x102f03efu; p.upper = 0x1cf99ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17A8_0, false>(vu, c);
    }
    struct Kp1808_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2220800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1808_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1808_0, false>(vu, c);
    }
    struct Kp1868_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107d7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1868_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1868_0, false>(vu, c);
    }
    struct Kp18C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80c103fdu; p.upper = 0x24213cu; p.lowerUsage.vfWrite = {1, 6}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {4, 1}; p.upperUsage.vfWrite = {4, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18C8_0, false>(vu, c);
    }
    struct Kp1928_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x10f0387u; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {14, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1928_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1928_0, false>(vu, c);
    }
    struct Kp1988_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0049u; p.upper = 0x1cc72acu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {12, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1988_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1988_0, false>(vu, c);
    }
    struct Kp19E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010769u; p.upper = 0x200040u; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19E8_0, false>(vu, c);
    }
    struct Kp1A48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80044271u; p.upper = 0x2ffu; p.lowerUsage.viRead = 272; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A48_0, false>(vu, c);
    }
    struct Kp1AA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800606bdu; p.upper = 0x18011feu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA8_0, false>(vu, c);
    }
    struct Kp1B08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e847ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {8, 15}; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B08_0, false>(vu, c);
    }
    struct Kp1B68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e35fffu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B68_0, false>(vu, c);
    }
    struct Kp1BC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000076bu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BC8_0, false>(vu, c);
    }
    struct Kp1C28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800050f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C28_0, false>(vu, c);
    }
    struct Kp1C88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000010u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C88_0, false>(vu, c);
    }
    struct Kp1CE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800050f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CE8_0, false>(vu, c);
    }
    struct Kp1D48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800040f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D48_0, false>(vu, c);
    }
    struct Kp1DA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca10edu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA8_0, false>(vu, c);
    }
    struct Kp1E08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c018dcu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E08_0, false>(vu, c);
    }
    struct Kp1E68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E68_0, false>(vu, c);
    }
    struct Kp1EC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1003003fu; p.upper = 0x1cf79ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EC8_0, false>(vu, c);
    }
    struct Kp1F28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80034a74u; p.upper = 0x2ffu; p.lowerUsage.viRead = 520; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F28_0, false>(vu, c);
    }
    struct Kp1F88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F88_0, false>(vu, c);
    }
    struct Kp1FE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f069fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FE8_0, false>(vu, c);
    }
    struct Kp2048_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2048_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2048_0, false>(vu, c);
    }
    struct Kp20A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f8u; p.upper = 0x1c010dcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20A8_0, false>(vu, c);
    }
    struct Kp2108_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2108_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2108_0, false>(vu, c);
    }
    struct Kp2168_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2168_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2168_0, false>(vu, c);
    }
    struct Kp21C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fau; p.upper = 0x1c4197du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C8_0, false>(vu, c);
    }
    struct Kp2228_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32800u; p.upper = 0x1d708a9u; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2228_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2228_0, false>(vu, c);
    }
    struct Kp2288_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f8u; p.upper = 0x1ea397cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2288_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2288_0, false>(vu, c);
    }
    struct Kp22E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32800u; p.upper = 0x1d708a9u; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22E8_0, false>(vu, c);
    }
    struct Kp2348_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0425cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2348_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2348_0, false>(vu, c);
    }
    struct Kp23A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0195cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23A8_0, false>(vu, c);
    }
    struct Kp2408_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f3u; p.upper = 0x1c4297du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2408_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2408_0, false>(vu, c);
    }
    struct Kp2468_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800639f4u; p.upper = 0x11be00du; p.lowerUsage.viRead = 192; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {28, 8}; p.upperUsage.vfRead[1] = {27, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2468_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2468_0, false>(vu, c);
    }
    struct Kp24C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p24C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C8_0, false>(vu, c);
    }
    struct Kp2528_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed5adbu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2528_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2528_0, false>(vu, c);
    }
    struct Kp2588_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e000du; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2588_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2588_0, false>(vu, c);
    }
    struct Kp25E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25E8_0, false>(vu, c);
    }
    struct Kp2648_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e150bcu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2648_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2648_0, false>(vu, c);
    }
    struct Kp26A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26A8_0, false>(vu, c);
    }
    struct Kp2708_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2708_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2708_0, false>(vu, c);
    }
    struct Kp2768_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20a066u; p.upperUsage.vfRead[0] = {20, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2768_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2768_0, false>(vu, c);
    }
    struct Kp27C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x616015u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 3}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27C8_0, false>(vu, c);
    }
    struct Kp2828_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2828_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2828_0, false>(vu, c);
    }
    struct Kp2888_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2888_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_0, false>(vu, c);
    }
    struct Kp28E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_0, false>(vu, c);
    }
    struct Kp2948_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_0, false>(vu, c);
    }
    struct Kp29A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A8_0, false>(vu, c);
    }
    struct Kp2A08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2403ffffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A08_0, false>(vu, c);
    }
    struct Kp2A68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A68_0, false>(vu, c);
    }
    struct Kp2AC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c211ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AC8_0, false>(vu, c);
    }
    struct Kp2B28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B28_0, false>(vu, c);
    }
    struct Kp2B88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B88_0, false>(vu, c);
    }
    struct Kp2BE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_0, false>(vu, c);
    }
    struct Kp2C48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_0, false>(vu, c);
    }
    struct Kp2ED8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2ED8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2ED8_0, false>(vu, c);
    }
    struct Kp2F38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_0, false>(vu, c);
    }
    struct Kp2F98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_0, false>(vu, c);
    }
    struct Kp3228_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3228_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3228_0, false>(vu, c);
    }
    struct Kp3288_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3288_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3288_0, false>(vu, c);
    }
    struct Kp32E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_0, false>(vu, c);
    }
    struct Kp3348_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3348_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3348_0, false>(vu, c);
    }
    struct Kp3568_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3568_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3568_0, false>(vu, c);
    }
    struct Kp35C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_0, false>(vu, c);
    }
    struct Kp3628_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p3628_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_0, false>(vu, c);
    }
    struct Kp3688_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3688_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3688_0, false>(vu, c);
    }
    struct Kp36E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E8_0, false>(vu, c);
    }
    struct Kp38E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_0, false>(vu, c);
    }
    struct Kp3948_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_0, false>(vu, c);
    }
    struct Kp39A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_0, false>(vu, c);
    }
    struct Kp3A08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A08_0, false>(vu, c);
    }
    struct Kp3A68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A68_0, false>(vu, c);
    }
    struct Kp3AC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AC8_0, false>(vu, c);
    }
    struct Kp0030_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8286016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0030_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0030_1, false>(vu, c);
    }
    struct Kp0098_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ec593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0098_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0098_1, false>(vu, c);
    }
    struct Kp00F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb6018u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00F8_1, false>(vu, c);
    }
    struct Kp0158_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f5u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0158_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0158_1, false>(vu, c);
    }
    struct Kp01C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0060u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01C0_1, false>(vu, c);
    }
    struct Kp0220_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0220_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0220_1, false>(vu, c);
    }
    struct Kp0280_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6218feu; p.upperUsage.vfRead[0] = {3, 3}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 3; p.upperUsage.accWrite = 3; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0280_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0280_1, false>(vu, c);
    }
    struct Kp02E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10030109u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02E8_1, false>(vu, c);
    }
    struct Kp0348_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0348_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0348_1, false>(vu, c);
    }
    struct Kp03A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb613eu; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p03A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03A8_1, false>(vu, c);
    }
    struct Kp0408_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0408_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0408_1, false>(vu, c);
    }
    struct Kp0468_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0468_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0468_1, false>(vu, c);
    }
    struct Kp04C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x43000000u; p.upper = 0x81e0012cu; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p04C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04C8_1, false>(vu, c);
    }
    struct Kp0528_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0278fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {30, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0528_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0528_1, false>(vu, c);
    }
    struct Kp0588_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0588_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0588_1, false>(vu, c);
    }
    struct Kp05E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05E8_1, false>(vu, c);
    }
    struct Kp0648_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0648_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0648_1, false>(vu, c);
    }
    struct Kp06A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06A8_1, false>(vu, c);
    }
    struct Kp0708_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff10bcu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0708_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0708_1, false>(vu, c);
    }
    struct Kp0768_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1011000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0768_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0768_1, false>(vu, c);
    }
    struct Kp07C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1e44248u; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07C8_1, false>(vu, c);
    }
    struct Kp0828_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0828_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0828_1, false>(vu, c);
    }
    struct Kp0888_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8002fcu; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0888_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0888_1, false>(vu, c);
    }
    struct Kp08E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08E8_1, false>(vu, c);
    }
    struct Kp0948_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c51248u; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0948_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0948_1, false>(vu, c);
    }
    struct Kp09A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6349dau; p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {7, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09A8_1, false>(vu, c);
    }
    struct Kp0A10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8029067cu; p.upper = 0x1c001a0u; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A10_1, false>(vu, c);
    }
    struct Kp0A70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500107fau; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A70_1, false>(vu, c);
    }
    struct Kp0AD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c820cfu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AD8_1, false>(vu, c);
    }
    struct Kp0B38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B38_1, false>(vu, c);
    }
    struct Kp0B98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B98_1, false>(vu, c);
    }
    struct Kp0BF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x860180u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {6, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BF8_1, false>(vu, c);
    }
    struct Kp0C58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2039deu; p.upperUsage.vfRead[0] = {7, 1}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C58_1, false>(vu, c);
    }
    struct Kp0CB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB8_1, false>(vu, c);
    }
    struct Kp0D18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff0a18u; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D18_1, false>(vu, c);
    }
    struct Kp0D78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D78_1, false>(vu, c);
    }
    struct Kp0DD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fa6002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {26, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DD8_1, false>(vu, c);
    }
    struct Kp0E38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d3dee9u; p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {19, 14}; p.upperUsage.vfWrite = {27, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E38_1, false>(vu, c);
    }
    struct Kp0E98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E98_1, false>(vu, c);
    }
    struct Kp0EF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2400003fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EF8_1, false>(vu, c);
    }
    struct Kp0F58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F58_1, false>(vu, c);
    }
    struct Kp0FB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB8_1, false>(vu, c);
    }
    struct Kp1018_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e519bcu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1018_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1018_1, false>(vu, c);
    }
    struct Kp1078_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e5297cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1078_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1078_1, false>(vu, c);
    }
    struct Kp10D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D8_1, false>(vu, c);
    }
    struct Kp1138_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1138_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1138_1, false>(vu, c);
    }
    struct Kp1198_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e4217cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1198_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1198_1, false>(vu, c);
    }
    struct Kp11F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x59c86du; p.upperUsage.vfRead[0] = {25, 2}; p.upperUsage.vfWrite = {1, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F8_1, false>(vu, c);
    }
    struct Kp1258_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1258_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1258_1, false>(vu, c);
    }
    struct Kp12B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B8_1, false>(vu, c);
    }
    struct Kp1318_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e6317cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1318_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1318_1, false>(vu, c);
    }
    struct Kp1380_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1002u; p.upper = 0x111892bu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {17, 8}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1380_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1380_1, false>(vu, c);
    }
    struct Kp13E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x59c86du; p.upperUsage.vfRead[0] = {25, 2}; p.upperUsage.vfWrite = {1, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13E8_1, false>(vu, c);
    }
    struct Kp1448_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1448_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1448_1, false>(vu, c);
    }
    struct Kp14A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A8_1, false>(vu, c);
    }
    struct Kp1508_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c421ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1508_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1508_1, false>(vu, c);
    }
    struct Kp1568_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x14039e6u; p.upperUsage.vfRead[0] = {7, 10}; p.upperUsage.vfWrite = {7, 10}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1568_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1568_1, false>(vu, c);
    }
    struct Kp15C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x42a33457u; p.upper = 0x81e03a5eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C8_1, false>(vu, c);
    }
    struct Kp1628_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18279d8u; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1628_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1628_1, false>(vu, c);
    }
    struct Kp1688_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1002u; p.upper = 0x111892bu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {17, 8}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1688_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1688_1, false>(vu, c);
    }
    struct Kp16E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16E8_1, false>(vu, c);
    }
    struct Kp1748_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1748_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1748_1, false>(vu, c);
    }
    struct Kp17A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3216eu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17A8_1, false>(vu, c);
    }
    struct Kp1808_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf20bdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {15, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1808_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1808_1, false>(vu, c);
    }
    struct Kp1868_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c99a69u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1868_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1868_1, false>(vu, c);
    }
    struct Kp18C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1097cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18C8_1, false>(vu, c);
    }
    struct Kp1928_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e7e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {7, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1928_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1928_1, false>(vu, c);
    }
    struct Kp1988_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1988_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1988_1, false>(vu, c);
    }
    struct Kp19E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19E8_1, false>(vu, c);
    }
    struct Kp1A48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee0803u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A48_1, false>(vu, c);
    }
    struct Kp1AA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA8_1, false>(vu, c);
    }
    struct Kp1B08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf29c8u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B08_1, false>(vu, c);
    }
    struct Kp1B68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c89a29u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B68_1, false>(vu, c);
    }
    struct Kp1BC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BC8_1, false>(vu, c);
    }
    struct Kp1C28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80818b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C28_1, false>(vu, c);
    }
    struct Kp1C88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e8e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {8, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C88_1, false>(vu, c);
    }
    struct Kp1CE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818b937du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CE8_1, false>(vu, c);
    }
    struct Kp1D48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D48_1, false>(vu, c);
    }
    struct Kp1DA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1DA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA8_1, false>(vu, c);
    }
    struct Kp1E08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c421ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E08_1, false>(vu, c);
    }
    struct Kp1E68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x1e100acu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E68_1, false>(vu, c);
    }
    struct Kp1EC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb337du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EC8_1, false>(vu, c);
    }
    struct Kp1F28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10802u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F28_1, false>(vu, c);
    }
    struct Kp1F88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F88_1, false>(vu, c);
    }
    struct Kp1FE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea517cu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FE8_1, false>(vu, c);
    }
    struct Kp2048_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbc15801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2050; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2048_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2048_1, false>(vu, c);
    }
    struct Kp20A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x100085fu; p.upperUsage.vfRead[0] = {1, 8}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20A8_1, false>(vu, c);
    }
    struct Kp2108_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2108_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2108_1, false>(vu, c);
    }
    struct Kp2168_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b5802u; p.upper = 0x18238e8u; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {2, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2168_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2168_1, false>(vu, c);
    }
    struct Kp21C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eaa8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {10, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C8_1, false>(vu, c);
    }
    struct Kp2228_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8034c33cu; p.upper = 0x1dcc2beu; p.lowerUsage.vfRead[0] = {24, 1}; p.lowerUsage.vfWrite = {20, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2228_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2228_1, false>(vu, c);
    }
    struct Kp2288_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2288_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2288_1, false>(vu, c);
    }
    struct Kp22E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee1000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22E8_1, false>(vu, c);
    }
    struct Kp2348_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5001054cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2348_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2348_1, false>(vu, c);
    }
    struct Kp23A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23A8_1, false>(vu, c);
    }
    struct Kp2408_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x81e05963u; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2408_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2408_1, false>(vu, c);
    }
    struct Kp2468_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eda6de1u; p.upper = 0x81e73a6au; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2468_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2468_1, false>(vu, c);
    }
    struct Kp24C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e631a9u; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C8_1, false>(vu, c);
    }
    struct Kp2878_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x22000fffu; p.upper = 0x2ffu; p.lowerUsage.latency = 4; p.lowerUsage.writesClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2878_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_1, false>(vu, c);
    }
    struct Kp28D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81284b3cu; p.upper = 0x1e1c8bdu; p.lowerUsage.vfRead[0] = {9, 9}; p.lowerUsage.vfWrite = {8, 9}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_1, false>(vu, c);
    }
    struct Kp2938_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2938_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_1, false>(vu, c);
    }
    struct Kp2B98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_1, false>(vu, c);
    }
    struct Kp2BF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_1, false>(vu, c);
    }
    struct Kp2C58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_1, false>(vu, c);
    }
    struct Kp2CB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB8_0, false>(vu, c);
    }
    struct Kp2D18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2D18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D18_0, false>(vu, c);
    }
    struct Kp2D78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D78_0, false>(vu, c);
    }
    struct Kp2EF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_1, false>(vu, c);
    }
    struct Kp2F58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_1, false>(vu, c);
    }
    struct Kp2FB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_1, false>(vu, c);
    }
    struct Kp3018_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3018_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3018_0, false>(vu, c);
    }
    struct Kp3078_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3078_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3078_0, false>(vu, c);
    }
    struct Kp30D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30D8_0, false>(vu, c);
    }
    struct Kp3260_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_1, false>(vu, c);
    }
    struct Kp32C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C0_1, false>(vu, c);
    }
    struct Kp3320_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_1, false>(vu, c);
    }
    struct Kp3380_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3380_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3380_1, false>(vu, c);
    }
    struct Kp33E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33E0_0, false>(vu, c);
    }
    struct Kp3440_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3440_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3440_0, false>(vu, c);
    }
    struct Kp35C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_1, false>(vu, c);
    }
    struct Kp3620_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3620_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3620_1, false>(vu, c);
    }
    struct Kp3680_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3680_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_1, false>(vu, c);
    }
    struct Kp36E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E0_1, false>(vu, c);
    }
    struct Kp3760_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3760_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3760_0, false>(vu, c);
    }
    struct Kp38E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_1, false>(vu, c);
    }
    struct Kp3940_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f1u; p.upper = 0x1e2b10au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_1, false>(vu, c);
    }
    struct Kp39A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_1, false>(vu, c);
    }
    struct Kp3A00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3A00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A00_1, false>(vu, c);
    }
    struct Kp3A60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3A60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A60_1, false>(vu, c);
    }
    struct Kp3C60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0429cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_0, false>(vu, c);
    }
    struct Kp3CC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_0, false>(vu, c);
    }
    struct Kp3D20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p3D20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_0, false>(vu, c);
    }
    struct Kp3D80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D80_0, false>(vu, c);
    }
    struct Kp3DE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DE0_0, false>(vu, c);
    }
    struct Kp3E40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3E40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E40_0, false>(vu, c);
    }
    struct Kp2888_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_2, false>(vu, c);
    }
    struct Kp28E8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28E8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_2, false>(vu, c);
    }
    struct Kp2B90_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_2, false>(vu, c);
    }
    struct Kp2BF0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_2, false>(vu, c);
    }
    struct Kp2C80_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C80_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_2, false>(vu, c);
    }
    struct Kp3CE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_1, false>(vu, c);
    }
    struct Kp2838_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2838_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2838_3, false>(vu, c);
    }
    struct Kp2898_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_3, false>(vu, c);
    }
    struct Kp28F8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_3, false>(vu, c);
    }
    struct Kp2958_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2958_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_2, false>(vu, c);
    }
    struct Kp29B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B8_1, false>(vu, c);
    }
    struct Kp2BC8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_3, false>(vu, c);
    }
    struct Kp2C28_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C28_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_3, false>(vu, c);
    }
    struct Kp2C90_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C90_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_3, false>(vu, c);
    }
    struct Kp2CF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CF0_1, false>(vu, c);
    }
    struct Kp2F00_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_2, false>(vu, c);
    }
    struct Kp2F60_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F60_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_2, false>(vu, c);
    }
    struct Kp2FC0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_2, false>(vu, c);
    }
    struct Kp3230_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_2, false>(vu, c);
    }
    struct Kp3290_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_2, false>(vu, c);
    }
    struct Kp32F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x42093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_2, false>(vu, c);
    }
    struct Kp3350_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3350_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3350_2, false>(vu, c);
    }
    struct Kp35C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_2, false>(vu, c);
    }
    struct Kp3620_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3620_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3620_2, false>(vu, c);
    }
    struct Kp3680_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3680_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_2, false>(vu, c);
    }
    struct Kp38F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_2, false>(vu, c);
    }
    struct Kp3950_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3950_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_2, false>(vu, c);
    }
    struct Kp39B0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_2, false>(vu, c);
    }
    struct Kp3C28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_1, false>(vu, c);
    }
    struct Kp3C88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_1, false>(vu, c);
    }
    struct Kp3D20_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D20_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_2, false>(vu, c);
    }
    struct Kp2868_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_4, false>(vu, c);
    }
    struct Kp28C8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_4, false>(vu, c);
    }
    struct Kp2928_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_4, false>(vu, c);
    }
    struct Kp2988_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2988_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2988_2, false>(vu, c);
    }
    struct Kp29E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E8_1, false>(vu, c);
    }
    struct Kp2A48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A48_1, false>(vu, c);
    }
    struct Kp2C90_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C90_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_4, false>(vu, c);
    }
    struct Kp2F10_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_3, false>(vu, c);
    }
    struct Kp2F70_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F70_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_3, false>(vu, c);
    }
    struct Kp2FD0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FD0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_3, false>(vu, c);
    }
    struct Kp3248_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_3, false>(vu, c);
    }
    struct Kp32A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_3, false>(vu, c);
    }
    struct Kp38E0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_3, false>(vu, c);
    }
    struct Kp3940_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_3, false>(vu, c);
    }
    struct Kp39A0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39A0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_3, false>(vu, c);
    }
    struct Kp3C48_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_2, false>(vu, c);
    }
    struct Kp3CA8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e0211fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_2, false>(vu, c);
    }
    struct Kp3D08_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_3, false>(vu, c);
    }
    struct Kp3D68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D68_1, false>(vu, c);
    }
    struct Kp2868_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_5, false>(vu, c);
    }
    struct Kp28C8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28C8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_5, false>(vu, c);
    }
    struct Kp2928_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_5, false>(vu, c);
    }
    struct Kp2BD8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_4, false>(vu, c);
    }
    struct Kp3660_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_3, false>(vu, c);
    }
    struct Kp38D8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_4, false>(vu, c);
    }
    struct Kp3938_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_4, false>(vu, c);
    }
    struct Kp3C18_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C18_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C18_2, false>(vu, c);
    }
    struct Kp3C78_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_3, false>(vu, c);
    }
    struct Kp3CD8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_2, false>(vu, c);
    }
    struct Kp2900_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_6, false>(vu, c);
    }
    struct Kp2BA8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_5, false>(vu, c);
    }
    struct Kp2C08_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C08_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_4, false>(vu, c);
    }
    struct Kp2C68_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_5, false>(vu, c);
    }
    struct Kp2F18_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F18_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_4, false>(vu, c);
    }
    struct Kp2F78_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1b08au; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_4, false>(vu, c);
    }
    struct Kp3008_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3008_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_2, false>(vu, c);
    }
    struct Kp3240_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e5293cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_4, false>(vu, c);
    }
    struct Kp32A0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_4, false>(vu, c);
    }
    struct Kp3300_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3300_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_3, false>(vu, c);
    }
    struct Kp3360_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3360_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3360_3, false>(vu, c);
    }
    struct Kp33C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p33C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33C0_1, false>(vu, c);
    }
    struct Kp35D8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_3, false>(vu, c);
    }
    struct Kp3638_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3638_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_4, false>(vu, c);
    }
    struct Kp36A0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36A0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A0_4, false>(vu, c);
    }
    struct Kp3700_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3700_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3700_1, false>(vu, c);
    }
    struct Kp39D8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x187313eu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_3, false>(vu, c);
    }
    struct Kp3D10_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D10_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_5, false>(vu, c);
    }
    struct Kp2950_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2950_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_4, false>(vu, c);
    }
    struct Kp2EC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2EC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EC8_1, false>(vu, c);
    }
    struct Kp3300_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3300_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_4, false>(vu, c);
    }
    struct Kp35A8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_4, false>(vu, c);
    }
    struct Kp3608_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3608_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_4, false>(vu, c);
    }
    struct Kp3668_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_5, false>(vu, c);
    }
    struct Kp3918_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_5, false>(vu, c);
    }
    struct Kp3978_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p3978_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3978_4, false>(vu, c);
    }
    struct Kp39D8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_4, false>(vu, c);
    }
    struct Kp3A38_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A38_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A38_2, false>(vu, c);
    }
    struct Kp3C70_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_4, false>(vu, c);
    }
    struct Kp3CD0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8213cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_4, false>(vu, c);
    }
    struct Kp3D38_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D38_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_4, false>(vu, c);
    }
    struct Kp3D98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D98_1, false>(vu, c);
    }
    struct Kp2880_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2880_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2880_7, false>(vu, c);
    }
    struct Kp2918_8
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_8(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_8, false>(vu, c);
    }
    struct Kp2978_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2978_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_3, false>(vu, c);
    }
    struct Kp2BB0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_6, false>(vu, c);
    }
    struct Kp2C10_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2C10_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_5, false>(vu, c);
    }
    struct Kp2C70_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C70_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_7, false>(vu, c);
    }
    struct Kp2CD0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD0_2, false>(vu, c);
    }
    struct Kp2F08_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_5, false>(vu, c);
    }
    struct Kp2F68_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F68_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_5, false>(vu, c);
    }
    struct Kp2FC8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_6, false>(vu, c);
    }
    struct Kp3030_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3030_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3030_2, false>(vu, c);
    }
    struct Kp3640_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3640_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_6, false>(vu, c);
    }
    struct Kp39B0_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_7, false>(vu, c);
    }
    struct Kp3C58_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_5, false>(vu, c);
    }
    struct Kp3CB8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CB8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_6, false>(vu, c);
    }
    struct Kp3D20_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D20_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_6, false>(vu, c);
    }
    struct Kp3280_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_5, false>(vu, c);
    }
    struct Kp32E0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E0_5, false>(vu, c);
    }
    struct Kp3590_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_5, false>(vu, c);
    }
    struct Kp35F0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_5, false>(vu, c);
    }
    struct Kp2F90_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F90_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_5, false>(vu, c);
    }
    struct Kp3300_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3300_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_6, false>(vu, c);
    }
    struct Kp01D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x60026cu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {9, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D8_2d, true>(vu, c);
    }
    struct Kp0240_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e240bfu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0240_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0240_2d, true>(vu, c);
    }
    struct Kp0518_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1856047u; p.upper = 0x1e7e72au; p.lowerUsage.vfWrite = {5, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {28, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0518_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0518_2d, true>(vu, c);
    }
    struct Kp0608_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea31aau; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0608_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0608_2d, true>(vu, c);
    }
    struct Kp06E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8027f33cu; p.upper = 0x18004e6u; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06E8_2d, true>(vu, c);
    }
    struct Kp07A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec1853u; p.upper = 0x5530bfu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07A8_2d, true>(vu, c);
    }
    struct Kp0B88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f65812u; p.upper = 0x201000u; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B88_2d, true>(vu, c);
    }
    struct Kp0D60_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800aebfcu; p.upper = 0x1c0d83cu; p.lowerUsage.vfRead[0] = {29, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D60_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D60_2d, true>(vu, c);
    }
    struct Kp0F68_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f528bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {21, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F68_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F68_2d, true>(vu, c);
    }
    struct Kp1010_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18ab498u; p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1010_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1010_2d, true>(vu, c);
    }
    struct Kp10C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec130eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10C0_2d, true>(vu, c);
    }
    struct Kp1190_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x5530bfu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1190_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1190_2d, true>(vu, c);
    }
    struct Kp1838_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080020u; p.upper = 0x1cf80eeu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {16, 14}; p.upperUsage.vfRead[1] = {15, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1838_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1838_2d, true>(vu, c);
    }
    struct Kp1940_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec1b7du; p.upper = 0x510301u; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {17, 4}; p.upperUsage.vfWrite = {12, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1940_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1940_2d, true>(vu, c);
    }
    struct Kp1DA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca0abeu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DA0_2d, true>(vu, c);
    }
    struct Kp1E00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3890au; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E00_2d, true>(vu, c);
    }
    struct Kp2250_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9beu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2250_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2250_2d, true>(vu, c);
    }
    struct Kp2348_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0425cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2348_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2348_2d, true>(vu, c);
    }
    struct Kp24D8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81012b3du; p.upper = 0x4501c5u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24D8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24D8_1d, true>(vu, c);
    }
    struct Kp2640_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0683cu; p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2640_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2640_1d, true>(vu, c);
    }
    struct Kp2920_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_9d, true>(vu, c);
    }
    struct Kp2BA0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_7d, true>(vu, c);
    }
    struct Kp2F90_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F90_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_6d, true>(vu, c);
    }
    struct Kp3318_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_8d, true>(vu, c);
    }
    struct Kp35A8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_6d, true>(vu, c);
    }
    struct Kp3688_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3688_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3688_5d, true>(vu, c);
    }
    struct Kp3908_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3908_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3908_6d, true>(vu, c);
    }
    struct Kp3988_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3988_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_6d, true>(vu, c);
    }
    struct Kp3A60_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A60_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A60_2d, true>(vu, c);
    }
    struct Kp0278_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e118ffu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0278_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0278_2d, true>(vu, c);
    }
    struct Kp0558_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0483cu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0558_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0558_3d, true>(vu, c);
    }
    struct Kp0868_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81050b3cu; p.upper = 0x10101c2u; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfWrite = {5, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0868_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0868_2d, true>(vu, c);
    }
    struct Kp0968_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x400262u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {9, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0968_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0968_2d, true>(vu, c);
    }
    struct Kp0A18_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8931bfu; p.upperUsage.vfRead[0] = {6, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A18_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A18_2d, true>(vu, c);
    }
    struct Kp0AB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0083cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AB0_2d, true>(vu, c);
    }
    struct Kp0B48_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81060b3du; p.upper = 0x634958u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfWrite = {6, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfWrite = {5, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B48_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B48_2d, true>(vu, c);
    }
    struct Kp0BE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x294a68u; p.upperUsage.vfRead[0] = {9, 1}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BE8_2d, true>(vu, c);
    }
    struct Kp0C80_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c731beu; p.upperUsage.vfRead[0] = {6, 14}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C80_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C80_2d, true>(vu, c);
    }
    struct Kp0CE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df10beu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CE8_2d, true>(vu, c);
    }
    struct Kp0EC8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EC8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC8_3d, true>(vu, c);
    }
    struct Kp1000_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1010183u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1000_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1000_3d, true>(vu, c);
    }
    struct Kp1150_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1150_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1150_2d, true>(vu, c);
    }
    struct Kp12B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B8_2d, true>(vu, c);
    }
    struct Kp1368_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80818b3cu; p.upper = 0x180283cu; p.lowerUsage.vfRead[0] = {17, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1368_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1368_2d, true>(vu, c);
    }
    struct Kp14A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14A0_2d, true>(vu, c);
    }
    struct Kp1558_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8701c0u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1558_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1558_2d, true>(vu, c);
    }
    struct Kp15D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e03a1eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D0_2d, true>(vu, c);
    }
    struct Kp1638_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10740c5u; p.upperUsage.vfRead[0] = {8, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1638_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1638_2d, true>(vu, c);
    }
    struct Kp1768_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1768_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1768_2d, true>(vu, c);
    }
    struct Kp17E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17E0_2d, true>(vu, c);
    }
    struct Kp1840_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2701ceu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1840_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1840_2d, true>(vu, c);
    }
    struct Kp1988_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1988_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1988_2d, true>(vu, c);
    }
    struct Kp1AD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5d14au; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AD0_2d, true>(vu, c);
    }
    struct Kp1B30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1a002fcu; p.upperUsage.vfRead[0] = {0, 13}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 13; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B30_2d, true>(vu, c);
    }
    struct Kp1C40_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C40_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C40_2d, true>(vu, c);
    }
    struct Kp1DB8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB8_3d, true>(vu, c);
    }
    struct Kp1E68_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x1e100acu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E68_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E68_2d, true>(vu, c);
    }
    struct Kp1F98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e90222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F98_2d, true>(vu, c);
    }
    struct Kp2098_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x105985bu; p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2098_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2098_2d, true>(vu, c);
    }
    struct Kp2178_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x8082396cu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2178_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2178_2d, true>(vu, c);
    }
    struct Kp2238_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8035cb3cu; p.upper = 0x1dccabeu; p.lowerUsage.vfRead[0] = {25, 1}; p.lowerUsage.vfWrite = {21, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2238_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2238_2d, true>(vu, c);
    }
    struct Kp23D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x1c002c3u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {11, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23D8_2d, true>(vu, c);
    }
    struct Kp2448_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e631eau; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2448_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2448_2d, true>(vu, c);
    }
    struct Kp24B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B0_2d, true>(vu, c);
    }
    struct Kp28A8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c938fcu; p.upperUsage.vfRead[0] = {7, 14}; p.upperUsage.vfRead[1] = {9, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_8d, true>(vu, c);
    }
    struct Kp2B98_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_8d, true>(vu, c);
    }
    struct Kp2CB8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB8_4d, true>(vu, c);
    }
    struct Kp2EF8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_7d, true>(vu, c);
    }
    struct Kp2FD8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_5d, true>(vu, c);
    }
    struct Kp3090_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3090_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3090_1d, true>(vu, c);
    }
    struct Kp3280_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_7d, true>(vu, c);
    }
    struct Kp3300_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3300_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_7d, true>(vu, c);
    }
    struct Kp33D0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33D0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33D0_1d, true>(vu, c);
    }
    struct Kp35F8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_6d, true>(vu, c);
    }
    struct Kp3760_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3760_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3760_1d, true>(vu, c);
    }
    struct Kp3C90_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_6d, true>(vu, c);
    }
    struct Kp3E08_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E08_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E08_1d, true>(vu, c);
    }
    struct Kp2C68_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_8d, true>(vu, c);
    }
    struct Kp2890_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_9d, true>(vu, c);
    }
    struct Kp2978_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2978_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_4d, true>(vu, c);
    }
    struct Kp2BE8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_8d, true>(vu, c);
    }
    struct Kp2CC8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC8_3d, true>(vu, c);
    }
    struct Kp2F00_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_8d, true>(vu, c);
    }
    struct Kp32E8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_7d, true>(vu, c);
    }
    struct Kp36B0_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p36B0_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B0_4d, true>(vu, c);
    }
    struct Kp3A00_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3A00_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A00_4d, true>(vu, c);
    }
    struct Kp3D08_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_9d, true>(vu, c);
    }
    struct Kp2870_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_9d, true>(vu, c);
    }
    struct Kp28E0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28E0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_7d, true>(vu, c);
    }
    struct Kp29C8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29C8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C8_4d, true>(vu, c);
    }
    struct Kp2C78_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_9d, true>(vu, c);
    }
    struct Kp32A8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_7d, true>(vu, c);
    }
    struct Kp3930_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3930_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_7d, true>(vu, c);
    }
    struct Kp3C78_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_7d, true>(vu, c);
    }
    struct Kp3D60_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D60_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D60_4d, true>(vu, c);
    }
    struct Kp2BA0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_10d, true>(vu, c);
    }
    struct Kp3938_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_7d, true>(vu, c);
    }
    struct Kp28F8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_10d, true>(vu, c);
    }
    struct Kp2EF0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_8d, true>(vu, c);
    }
    struct Kp2FE8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE8_6d, true>(vu, c);
    }
    struct Kp3280_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_9d, true>(vu, c);
    }
    struct Kp3368_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3368_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3368_4d, true>(vu, c);
    }
    struct Kp35D8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_8d, true>(vu, c);
    }
    struct Kp36B8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B8_4d, true>(vu, c);
    }
    struct Kp39B8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_9d, true>(vu, c);
    }
    struct Kp32F8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_7d, true>(vu, c);
    }
    struct Kp3900_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_8d, true>(vu, c);
    }
    struct Kp39E0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39E0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E0_5d, true>(vu, c);
    }
    struct Kp3C68_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_7d, true>(vu, c);
    }
    struct Kp3CE8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_7d, true>(vu, c);
    }
    struct Kp2840_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_9d, true>(vu, c);
    }
    struct Kp2930_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_10d, true>(vu, c);
    }
    struct Kp2BC0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_10d, true>(vu, c);
    }
    struct Kp2CA0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_5d, true>(vu, c);
    }
    struct Kp2F28_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_7d, true>(vu, c);
    }
    struct Kp2FA8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_6d, true>(vu, c);
    }
    struct Kp3658_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_9d, true>(vu, c);
    }
    struct Kp3230_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_8d, true>(vu, c);
    }
    struct Kp35C0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_8d, true>(vu, c);
    }
    struct Kp3308_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_9d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
