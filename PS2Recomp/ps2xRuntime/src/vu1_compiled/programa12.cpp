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
    struct Kp0058_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8846045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0058_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0058_0, false>(vu, c);
    }
    struct Kp00B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00B8_0, false>(vu, c);
    }
    struct Kp0118_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4d03a0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0118_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0118_0, false>(vu, c);
    }
    struct Kp0178_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010003u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0178_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0178_0, false>(vu, c);
    }
    struct Kp01D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x60026cu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {9, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D8_0, false>(vu, c);
    }
    struct Kp0238_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055174u; p.upper = 0x62507eu; p.lowerUsage.viRead = 1056; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {10, 3}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 3; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0238_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0238_0, false>(vu, c);
    }
    struct Kp0298_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5005000du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0298_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0298_0, false>(vu, c);
    }
    struct Kp02F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02F8_0, false>(vu, c);
    }
    struct Kp0358_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a5070u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0358_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0358_0, false>(vu, c);
    }
    struct Kp03B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03B8_0, false>(vu, c);
    }
    struct Kp0418_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00300cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0418_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0418_0, false>(vu, c);
    }
    struct Kp0478_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e07be7u; p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfWrite = {15, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0478_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0478_0, false>(vu, c);
    }
    struct Kp04D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e039deu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04D8_0, false>(vu, c);
    }
    struct Kp0538_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e005014u; p.upper = 0x1803203u; p.lowerUsage.viRead = 1024; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0538_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0538_0, false>(vu, c);
    }
    struct Kp0598_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000003u; p.upper = 0x1cbef46u; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {11, 2}; p.upperUsage.vfWrite = {29, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0598_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0598_0, false>(vu, c);
    }
    struct Kp05F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea212au; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F8_0, false>(vu, c);
    }
    struct Kp0658_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {12, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0658_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0658_0, false>(vu, c);
    }
    struct Kp06B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0529eu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B8_0, false>(vu, c);
    }
    struct Kp0718_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a7698u; p.upperUsage.vfRead[0] = {14, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {26, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0718_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0718_0, false>(vu, c);
    }
    struct Kp0778_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x43099bu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0778_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0778_0, false>(vu, c);
    }
    struct Kp07D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e003946u; p.upper = 0x5730bfu; p.lowerUsage.viRead = 128; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {23, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07D8_0, false>(vu, c);
    }
    struct Kp0838_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00313au; p.upper = 0x4f30bfu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0838_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0838_0, false>(vu, c);
    }
    struct Kp0898_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80035af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2056; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0898_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0898_0, false>(vu, c);
    }
    struct Kp08F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a0037fdu; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08F8_0, false>(vu, c);
    }
    struct Kp0958_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800d00f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0958_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0958_0, false>(vu, c);
    }
    struct Kp09B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d02abu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09B8_0, false>(vu, c);
    }
    struct Kp0A18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8826800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A18_0, false>(vu, c);
    }
    struct Kp0A78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A78_0, false>(vu, c);
    }
    struct Kp0AD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AD8_0, false>(vu, c);
    }
    struct Kp0B38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84d03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B38_0, false>(vu, c);
    }
    struct Kp0B98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d4a0eau; p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B98_0, false>(vu, c);
    }
    struct Kp0BF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BF8_0, false>(vu, c);
    }
    struct Kp0C58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8236800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C58_0, false>(vu, c);
    }
    struct Kp0CB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180fddeu; p.upperUsage.vfRead[0] = {31, 12}; p.upperUsage.vfWrite = {23, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB8_0, false>(vu, c);
    }
    struct Kp0D18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x340e7000u; p.upper = 0x196ecadu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfRead[1] = {22, 12}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D18_0, false>(vu, c);
    }
    struct Kp0D78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000febu; p.upper = 0x1dfd74au; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfWrite = {29, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D78_0, false>(vu, c);
    }
    struct Kp0DD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DD8_0, false>(vu, c);
    }
    struct Kp0E38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c5af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6144; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E38_0, false>(vu, c);
    }
    struct Kp0E98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010a70u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E98_0, false>(vu, c);
    }
    struct Kp0EF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef5813u; p.upper = 0x1e06b67u; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EF8_0, false>(vu, c);
    }
    struct Kp0F58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f4340au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F58_0, false>(vu, c);
    }
    struct Kp0FB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed364au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {25, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB8_0, false>(vu, c);
    }
    struct Kp1018_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a6618u; p.upperUsage.vfRead[0] = {12, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {24, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1018_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1018_0, false>(vu, c);
    }
    struct Kp1078_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x1f5154eu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1078_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1078_0, false>(vu, c);
    }
    struct Kp10D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed134eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D8_0, false>(vu, c);
    }
    struct Kp1138_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8048033du; p.upper = 0x1c00243u; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {8, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1138_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1138_0, false>(vu, c);
    }
    struct Kp1198_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x1f5154eu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1198_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1198_0, false>(vu, c);
    }
    struct Kp11F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800631b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F8_0, false>(vu, c);
    }
    struct Kp1258_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84e03a0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1258_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1258_0, false>(vu, c);
    }
    struct Kp12B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa8d03a0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12B8_0, false>(vu, c);
    }
    struct Kp1318_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52010006u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1318_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1318_0, false>(vu, c);
    }
    struct Kp1378_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800152b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1378_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1378_0, false>(vu, c);
    }
    struct Kp13D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13D8_0, false>(vu, c);
    }
    struct Kp1438_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 544; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1438_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1438_0, false>(vu, c);
    }
    struct Kp1498_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80050870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1498_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1498_0, false>(vu, c);
    }
    struct Kp14F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F8_0, false>(vu, c);
    }
    struct Kp1558_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84b03a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1558_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1558_0, false>(vu, c);
    }
    struct Kp15B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80014974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 514; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15B8_0, false>(vu, c);
    }
    struct Kp1618_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1618_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1618_0, false>(vu, c);
    }
    struct Kp1678_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800066fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1678_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1678_0, false>(vu, c);
    }
    struct Kp16D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8077b33cu; p.upper = 0x197b06au; p.lowerUsage.vfRead[0] = {22, 3}; p.lowerUsage.vfWrite = {23, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16D8_0, false>(vu, c);
    }
    struct Kp1738_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5005008eu; p.upper = 0x18002fcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1738_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1738_0, false>(vu, c);
    }
    struct Kp1798_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x380a0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1798_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1798_0, false>(vu, c);
    }
    struct Kp17F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500907e5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F8_0, false>(vu, c);
    }
    struct Kp1858_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80680bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1858_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1858_0, false>(vu, c);
    }
    struct Kp18B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38070000u; p.upper = 0x10f0342u; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B8_0, false>(vu, c);
    }
    struct Kp1918_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100c03ecu; p.upper = 0x2010a2u; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1918_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1918_0, false>(vu, c);
    }
    struct Kp1978_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e004bu; p.upper = 0x1cb72a8u; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {11, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1978_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1978_0, false>(vu, c);
    }
    struct Kp19D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c10800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19D8_0, false>(vu, c);
    }
    struct Kp1A38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80043a31u; p.upper = 0x81097fu; p.lowerUsage.viRead = 144; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 4}; p.upperUsage.vfWrite = {1, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A38_0, false>(vu, c);
    }
    struct Kp1A98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c45001u; p.upper = 0x207880u; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A98_0, false>(vu, c);
    }
    struct Kp1AF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x181212cu; p.upperUsage.vfRead[0] = {4, 12}; p.upperUsage.vfRead[1] = {1, 12}; p.upperUsage.vfWrite = {4, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AF8_0, false>(vu, c);
    }
    struct Kp1B58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e148fdu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B58_0, false>(vu, c);
    }
    struct Kp1BB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48000800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BB8_0, false>(vu, c);
    }
    struct Kp1C18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8215000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C18_0, false>(vu, c);
    }
    struct Kp1C78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500107fau; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C78_0, false>(vu, c);
    }
    struct Kp1CD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80001a30u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CD8_0, false>(vu, c);
    }
    struct Kp1D38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c25800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 14}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D38_0, false>(vu, c);
    }
    struct Kp1D98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D98_0, false>(vu, c);
    }
    struct Kp1DF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e380bdu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF8_0, false>(vu, c);
    }
    struct Kp1E58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E58_0, false>(vu, c);
    }
    struct Kp1EB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x340f7800u; p.upper = 0x1970cedu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EB8_0, false>(vu, c);
    }
    struct Kp1F18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5234u; p.upper = 0x2ffu; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F18_0, false>(vu, c);
    }
    struct Kp1F78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F78_0, false>(vu, c);
    }
    struct Kp1FD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000004cu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FD8_0, false>(vu, c);
    }
    struct Kp2038_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32000u; p.upper = 0x1c1a0adu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2038_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2038_0, false>(vu, c);
    }
    struct Kp2098_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2098_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2098_0, false>(vu, c);
    }
    struct Kp20F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1c010dcu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20F8_0, false>(vu, c);
    }
    struct Kp2158_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2158_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2158_0, false>(vu, c);
    }
    struct Kp21B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x4338ecu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 2}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21B8_0, false>(vu, c);
    }
    struct Kp2218_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x56003fu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2218_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2218_0, false>(vu, c);
    }
    struct Kp2278_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e357ffu; p.upper = 0x1d708a9u; p.lowerUsage.vfRead[0] = {10, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2278_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2278_0, false>(vu, c);
    }
    struct Kp22D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x56003fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D8_0, false>(vu, c);
    }
    struct Kp2338_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e02980u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2338_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2338_0, false>(vu, c);
    }
    struct Kp2398_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e60780u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2398_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2398_0, false>(vu, c);
    }
    struct Kp23F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800809f4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 258; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F8_0, false>(vu, c);
    }
    struct Kp2458_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0195cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2458_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2458_0, false>(vu, c);
    }
    struct Kp24B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f3u; p.upper = 0x1c4297du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B8_0, false>(vu, c);
    }
    struct Kp2518_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e53aceu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2518_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2518_0, false>(vu, c);
    }
    struct Kp2578_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e107ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2578_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2578_0, false>(vu, c);
    }
    struct Kp25D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25D8_0, false>(vu, c);
    }
    struct Kp2638_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81080bfdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {8, 8}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2638_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2638_0, false>(vu, c);
    }
    struct Kp2698_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2698_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2698_0, false>(vu, c);
    }
    struct Kp26F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e04deu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26F8_0, false>(vu, c);
    }
    struct Kp2758_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f20226u; p.upper = 0x1f0817cu; p.lowerUsage.vfWrite = {18, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2758_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2758_0, false>(vu, c);
    }
    struct Kp27B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0008u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27B8_0, false>(vu, c);
    }
    struct Kp2818_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2818_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2818_0, false>(vu, c);
    }
    struct Kp2878_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2878_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_0, false>(vu, c);
    }
    struct Kp28D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_0, false>(vu, c);
    }
    struct Kp2938_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2938_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_0, false>(vu, c);
    }
    struct Kp2998_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2998_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2998_0, false>(vu, c);
    }
    struct Kp29F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29F8_0, false>(vu, c);
    }
    struct Kp2A58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0472u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A58_0, false>(vu, c);
    }
    struct Kp2AB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AB8_0, false>(vu, c);
    }
    struct Kp2B18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0455u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B18_0, false>(vu, c);
    }
    struct Kp2B78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B78_0, false>(vu, c);
    }
    struct Kp2BD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_0, false>(vu, c);
    }
    struct Kp2C38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C38_0, false>(vu, c);
    }
    struct Kp2EC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2EC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EC8_0, false>(vu, c);
    }
    struct Kp2F28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_0, false>(vu, c);
    }
    struct Kp2F88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F88_0, false>(vu, c);
    }
    struct Kp3218_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3218_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3218_0, false>(vu, c);
    }
    struct Kp3278_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_0, false>(vu, c);
    }
    struct Kp32D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D8_0, false>(vu, c);
    }
    struct Kp3338_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_0, false>(vu, c);
    }
    struct Kp3398_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3398_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3398_0, false>(vu, c);
    }
    struct Kp35B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B8_0, false>(vu, c);
    }
    struct Kp3618_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3618_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_0, false>(vu, c);
    }
    struct Kp3678_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3678_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_0, false>(vu, c);
    }
    struct Kp36D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e0215fu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D8_0, false>(vu, c);
    }
    struct Kp38D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_0, false>(vu, c);
    }
    struct Kp3938_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_0, false>(vu, c);
    }
    struct Kp3998_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3998_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_0, false>(vu, c);
    }
    struct Kp39F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F8_0, false>(vu, c);
    }
    struct Kp3A58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A58_0, false>(vu, c);
    }
    struct Kp3AB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AB8_0, false>(vu, c);
    }
    struct Kp0020_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90a6015u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0020_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0020_1, false>(vu, c);
    }
    struct Kp0088_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb6017u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0088_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0088_1, false>(vu, c);
    }
    struct Kp00E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f5u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00E8_1, false>(vu, c);
    }
    struct Kp0148_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0148_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0148_1, false>(vu, c);
    }
    struct Kp01B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01B0_1, false>(vu, c);
    }
    struct Kp0210_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0210_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0210_1, false>(vu, c);
    }
    struct Kp0270_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e219bfu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0270_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0270_1, false>(vu, c);
    }
    struct Kp02D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb601du; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02D8_1, false>(vu, c);
    }
    struct Kp0338_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec617du; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0338_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0338_1, false>(vu, c);
    }
    struct Kp0398_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010006u; p.upper = 0x1ec617du; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0398_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0398_1, false>(vu, c);
    }
    struct Kp03F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03F8_1, false>(vu, c);
    }
    struct Kp0458_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9053800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0458_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0458_1, false>(vu, c);
    }
    struct Kp04B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x400002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.eBit = true; p.upperNop = true; return p; }();
    };
    bool p04B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04B8_1, false>(vu, c);
    }
    struct Kp0518_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800080u; p.upper = 0x81e0203cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0518_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0518_1, false>(vu, c);
    }
    struct Kp0578_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0578_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0578_1, false>(vu, c);
    }
    struct Kp05D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff120au; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05D8_1, false>(vu, c);
    }
    struct Kp0638_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0638_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0638_1, false>(vu, c);
    }
    struct Kp0698_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0698_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0698_1, false>(vu, c);
    }
    struct Kp06F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06F8_1, false>(vu, c);
    }
    struct Kp0758_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1ff1a09u; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0758_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0758_1, false>(vu, c);
    }
    struct Kp07B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e80801u; p.upper = 0x1e0383cu; p.lowerUsage.vfWrite = {8, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B8_1, false>(vu, c);
    }
    struct Kp0818_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x12401bcu; p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 9; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0818_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0818_1, false>(vu, c);
    }
    struct Kp0878_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x1010181u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0878_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0878_1, false>(vu, c);
    }
    struct Kp08D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x11f282cu; p.upperUsage.vfRead[0] = {5, 8}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p08D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08D8_1, false>(vu, c);
    }
    struct Kp0938_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x105f96cu; p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0938_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0938_1, false>(vu, c);
    }
    struct Kp0998_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x634999u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfWrite = {6, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0998_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0998_1, false>(vu, c);
    }
    struct Kp09F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52010790u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09F8_1, false>(vu, c);
    }
    struct Kp0A60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50050009u; p.upper = 0x850140u; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A60_1, false>(vu, c);
    }
    struct Kp0AC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8208du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AC8_1, false>(vu, c);
    }
    struct Kp0B28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B28_1, false>(vu, c);
    }
    struct Kp0B88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010044u; p.upper = 0x1c8416eu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B88_1, false>(vu, c);
    }
    struct Kp0BE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x294a68u; p.upperUsage.vfRead[0] = {9, 1}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BE8_1, false>(vu, c);
    }
    struct Kp0C48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2701dau; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C48_1, false>(vu, c);
    }
    struct Kp0CA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0103cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA8_1, false>(vu, c);
    }
    struct Kp0D08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D08_1, false>(vu, c);
    }
    struct Kp0D68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e78b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 15}; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D68_1, false>(vu, c);
    }
    struct Kp0DC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f86000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {24, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DC8_1, false>(vu, c);
    }
    struct Kp0E28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1a002fcu; p.upperUsage.vfRead[0] = {0, 13}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 13; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E28_1, false>(vu, c);
    }
    struct Kp0E88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E88_1, false>(vu, c);
    }
    struct Kp0EE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE8_1, false>(vu, c);
    }
    struct Kp0F48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F48_1, false>(vu, c);
    }
    struct Kp0FA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e20225u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0FA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FA8_1, false>(vu, c);
    }
    struct Kp1008_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x106296fu; p.upperUsage.vfRead[0] = {5, 8}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1008_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1008_1, false>(vu, c);
    }
    struct Kp1068_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e129u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1068_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1068_1, false>(vu, c);
    }
    struct Kp10C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10C8_1, false>(vu, c);
    }
    struct Kp1128_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1128_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1128_1, false>(vu, c);
    }
    struct Kp1188_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1188_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1188_1, false>(vu, c);
    }
    struct Kp11E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11E8_1, false>(vu, c);
    }
    struct Kp1248_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1248_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1248_1, false>(vu, c);
    }
    struct Kp12A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12A8_1, false>(vu, c);
    }
    struct Kp1308_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c421ffu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1308_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1308_1, false>(vu, c);
    }
    struct Kp1370_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b8801u; p.upper = 0x8798c8u; p.lowerUsage.vfRead[0] = {17, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1370_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1370_1, false>(vu, c);
    }
    struct Kp13D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e073eu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13D0_1, false>(vu, c);
    }
    struct Kp1438_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1438_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1438_1, false>(vu, c);
    }
    struct Kp1498_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1498_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1498_1, false>(vu, c);
    }
    struct Kp14F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F8_1, false>(vu, c);
    }
    struct Kp1558_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8701c0u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1558_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1558_1, false>(vu, c);
    }
    struct Kp15B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc2992661u; p.upper = 0x81e738aau; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15B8_1, false>(vu, c);
    }
    struct Kp1618_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e249e9u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1618_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1618_1, false>(vu, c);
    }
    struct Kp1678_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b8801u; p.upper = 0x8798c8u; p.lowerUsage.vfRead[0] = {17, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1678_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1678_1, false>(vu, c);
    }
    struct Kp16D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e06ddu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16D8_1, false>(vu, c);
    }
    struct Kp1738_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1738_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1738_1, false>(vu, c);
    }
    struct Kp1798_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2d10au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1798_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1798_1, false>(vu, c);
    }
    struct Kp17F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf29c8u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F8_1, false>(vu, c);
    }
    struct Kp1858_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c89a29u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1858_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1858_1, false>(vu, c);
    }
    struct Kp18B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B8_1, false>(vu, c);
    }
    struct Kp1918_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80818b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 4}; p.lowerUsage.vfWrite = {1, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1918_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1918_1, false>(vu, c);
    }
    struct Kp1978_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e8e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {8, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1978_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1978_1, false>(vu, c);
    }
    struct Kp19D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818b937du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19D8_1, false>(vu, c);
    }
    struct Kp1A38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A38_1, false>(vu, c);
    }
    struct Kp1A98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A98_1, false>(vu, c);
    }
    struct Kp1AF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce20bdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {14, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AF8_1, false>(vu, c);
    }
    struct Kp1B58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c799e9u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B58_1, false>(vu, c);
    }
    struct Kp1BB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24ffffffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BB8_1, false>(vu, c);
    }
    struct Kp1C18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818b8b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C18_1, false>(vu, c);
    }
    struct Kp1C78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81018b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 8}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C78_1, false>(vu, c);
    }
    struct Kp1CD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CD8_1, false>(vu, c);
    }
    struct Kp1D38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0616u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D38_1, false>(vu, c);
    }
    struct Kp1D98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x100949cu; p.upperUsage.vfRead[0] = {18, 8}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D98_1, false>(vu, c);
    }
    struct Kp1DF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80458bfcu; p.upper = 0x1c2e0a9u; p.lowerUsage.vfRead[0] = {17, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF8_1, false>(vu, c);
    }
    struct Kp1E58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb3b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E58_1, false>(vu, c);
    }
    struct Kp1EB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1822928u; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {2, 12}; p.upperUsage.vfWrite = {4, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EB8_1, false>(vu, c);
    }
    struct Kp1F18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef0800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F18_1, false>(vu, c);
    }
    struct Kp1F78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F78_1, false>(vu, c);
    }
    struct Kp1FD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20089eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FD8_1, false>(vu, c);
    }
    struct Kp2038_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa415800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2050; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2038_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2038_1, false>(vu, c);
    }
    struct Kp2098_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x105985bu; p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2098_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2098_1, false>(vu, c);
    }
    struct Kp20F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb1b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20F8_1, false>(vu, c);
    }
    struct Kp2158_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10031802u; p.upper = 0x18189bcu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 12}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2158_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2158_1, false>(vu, c);
    }
    struct Kp21B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21B8_1, false>(vu, c);
    }
    struct Kp2218_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x1eda8bdu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2218_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2218_1, false>(vu, c);
    }
    struct Kp2278_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0569u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2278_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2278_1, false>(vu, c);
    }
    struct Kp22D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8426016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D8_1, false>(vu, c);
    }
    struct Kp2338_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010020u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2338_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2338_1, false>(vu, c);
    }
    struct Kp2398_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c111ffu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2398_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2398_1, false>(vu, c);
    }
    struct Kp23F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a7fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F8_1, false>(vu, c);
    }
    struct Kp2458_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0123fu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2458_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2458_1, false>(vu, c);
    }
    struct Kp24B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24B8_1, false>(vu, c);
    }
    struct Kp2868_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80000af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2868_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_1, false>(vu, c);
    }
    struct Kp28C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_1, false>(vu, c);
    }
    struct Kp2928_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_1, false>(vu, c);
    }
    struct Kp2B88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B88_1, false>(vu, c);
    }
    struct Kp2BE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb237du; p.upper = 0x1c0109cu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_1, false>(vu, c);
    }
    struct Kp2C48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_1, false>(vu, c);
    }
    struct Kp2CA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA8_0, false>(vu, c);
    }
    struct Kp2D08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D08_0, false>(vu, c);
    }
    struct Kp2D68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e039dfu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D68_0, false>(vu, c);
    }
    struct Kp2EE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_1, false>(vu, c);
    }
    struct Kp2F48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_1, false>(vu, c);
    }
    struct Kp2FA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_1, false>(vu, c);
    }
    struct Kp3008_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3008_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_0, false>(vu, c);
    }
    struct Kp3068_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3068_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3068_0, false>(vu, c);
    }
    struct Kp30C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30C8_0, false>(vu, c);
    }
    struct Kp3250_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_1, false>(vu, c);
    }
    struct Kp32B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_1, false>(vu, c);
    }
    struct Kp3310_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_1, false>(vu, c);
    }
    struct Kp3370_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3370_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3370_1, false>(vu, c);
    }
    struct Kp33D0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33D0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33D0_0, false>(vu, c);
    }
    struct Kp3430_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3430_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3430_0, false>(vu, c);
    }
    struct Kp35B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_1, false>(vu, c);
    }
    struct Kp3610_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3610_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_1, false>(vu, c);
    }
    struct Kp3670_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_1, false>(vu, c);
    }
    struct Kp36D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D0_1, false>(vu, c);
    }
    struct Kp3750_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3750_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3750_0, false>(vu, c);
    }
    struct Kp38D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_1, false>(vu, c);
    }
    struct Kp3930_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_1, false>(vu, c);
    }
    struct Kp3990_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x42093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3990_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_1, false>(vu, c);
    }
    struct Kp39F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_1, false>(vu, c);
    }
    struct Kp3A50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3A50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A50_1, false>(vu, c);
    }
    struct Kp3C50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_0, false>(vu, c);
    }
    struct Kp3CB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB0_0, false>(vu, c);
    }
    struct Kp3D10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_0, false>(vu, c);
    }
    struct Kp3D70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D70_0, false>(vu, c);
    }
    struct Kp3DD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DD0_0, false>(vu, c);
    }
    struct Kp3E30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3E30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E30_0, false>(vu, c);
    }
    struct Kp2878_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2878_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_2, false>(vu, c);
    }
    struct Kp28D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7817u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_2, false>(vu, c);
    }
    struct Kp2B78_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B78_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B78_2, false>(vu, c);
    }
    struct Kp2BE0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BE0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_2, false>(vu, c);
    }
    struct Kp2C70_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C70_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C70_2, false>(vu, c);
    }
    struct Kp3C60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_1, false>(vu, c);
    }
    struct Kp3D38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_1, false>(vu, c);
    }
    struct Kp2888_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_3, false>(vu, c);
    }
    struct Kp28E8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p28E8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_3, false>(vu, c);
    }
    struct Kp2948_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_2, false>(vu, c);
    }
    struct Kp29A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A8_1, false>(vu, c);
    }
    struct Kp2BB8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_3, false>(vu, c);
    }
    struct Kp2C18_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C18_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_3, false>(vu, c);
    }
    struct Kp2C78_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_3, false>(vu, c);
    }
    struct Kp2CE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE0_1, false>(vu, c);
    }
    struct Kp2EF0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_2, false>(vu, c);
    }
    struct Kp2F50_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_2, false>(vu, c);
    }
    struct Kp2FB0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FB0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_2, false>(vu, c);
    }
    struct Kp3010_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3010_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3010_1, false>(vu, c);
    }
    struct Kp3280_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_2, false>(vu, c);
    }
    struct Kp32E0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32E0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E0_2, false>(vu, c);
    }
    struct Kp3340_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p3340_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3340_2, false>(vu, c);
    }
    struct Kp35B0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_2, false>(vu, c);
    }
    struct Kp3610_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3610_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_2, false>(vu, c);
    }
    struct Kp3670_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_2, false>(vu, c);
    }
    struct Kp38E0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E0_2, false>(vu, c);
    }
    struct Kp3940_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3940_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_2, false>(vu, c);
    }
    struct Kp39A0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_2, false>(vu, c);
    }
    struct Kp3C18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C18_1, false>(vu, c);
    }
    struct Kp3C78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_1, false>(vu, c);
    }
    struct Kp3D10_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D10_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_2, false>(vu, c);
    }
    struct Kp2858_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_4, false>(vu, c);
    }
    struct Kp28B8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_4, false>(vu, c);
    }
    struct Kp2918_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_4, false>(vu, c);
    }
    struct Kp2978_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2978_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_2, false>(vu, c);
    }
    struct Kp29D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D8_1, false>(vu, c);
    }
    struct Kp2A38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A38_1, false>(vu, c);
    }
    struct Kp2C80_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_4, false>(vu, c);
    }
    struct Kp2F00_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F00_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F00_3, false>(vu, c);
    }
    struct Kp2F60_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F60_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_3, false>(vu, c);
    }
    struct Kp2FC0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_3, false>(vu, c);
    }
    struct Kp3238_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_3, false>(vu, c);
    }
    struct Kp3298_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_3, false>(vu, c);
    }
    struct Kp38D0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D0_3, false>(vu, c);
    }
    struct Kp3930_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3930_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_3, false>(vu, c);
    }
    struct Kp3990_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3990_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_3, false>(vu, c);
    }
    struct Kp3C38_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_2, false>(vu, c);
    }
    struct Kp3C98_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_2, false>(vu, c);
    }
    struct Kp3CF8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CF8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_3, false>(vu, c);
    }
    struct Kp3D58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D58_1, false>(vu, c);
    }
    struct Kp2858_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_5, false>(vu, c);
    }
    struct Kp28B8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28B8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_5, false>(vu, c);
    }
    struct Kp2918_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_5, false>(vu, c);
    }
    struct Kp2BC8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_4, false>(vu, c);
    }
    struct Kp3650_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3650_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_3, false>(vu, c);
    }
    struct Kp38C8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38C8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38C8_3, false>(vu, c);
    }
    struct Kp3928_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_4, false>(vu, c);
    }
    struct Kp39B8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_4, false>(vu, c);
    }
    struct Kp3C68_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_3, false>(vu, c);
    }
    struct Kp3CC8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CC8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_2, false>(vu, c);
    }
    struct Kp28F0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F0_6, false>(vu, c);
    }
    struct Kp2B98_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_5, false>(vu, c);
    }
    struct Kp2BF8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2BF8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_5, false>(vu, c);
    }
    struct Kp2C58_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C58_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_3, false>(vu, c);
    }
    struct Kp2F08_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_4, false>(vu, c);
    }
    struct Kp2F68_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F68_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_4, false>(vu, c);
    }
    struct Kp2FF8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FF8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF8_3, false>(vu, c);
    }
    struct Kp3230_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_4, false>(vu, c);
    }
    struct Kp3290_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_4, false>(vu, c);
    }
    struct Kp32F0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32F0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_4, false>(vu, c);
    }
    struct Kp3350_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3350_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3350_3, false>(vu, c);
    }
    struct Kp33B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p33B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33B0_1, false>(vu, c);
    }
    struct Kp35C8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_3, false>(vu, c);
    }
    struct Kp3628_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3628_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_3, false>(vu, c);
    }
    struct Kp3690_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3690_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_4, false>(vu, c);
    }
    struct Kp36F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F0_2, false>(vu, c);
    }
    struct Kp39C8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C8_3, false>(vu, c);
    }
    struct Kp3D00_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_5, false>(vu, c);
    }
    struct Kp2940_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2940_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_6, false>(vu, c);
    }
    struct Kp2C78_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C78_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_6, false>(vu, c);
    }
    struct Kp32F0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_5, false>(vu, c);
    }
    struct Kp3598_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_4, false>(vu, c);
    }
    struct Kp35F8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35F8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_4, false>(vu, c);
    }
    struct Kp3658_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_5, false>(vu, c);
    }
    struct Kp3908_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3908_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3908_5, false>(vu, c);
    }
    struct Kp3968_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3968_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_6, false>(vu, c);
    }
    struct Kp39C8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C8_4, false>(vu, c);
    }
    struct Kp3A28_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e0215fu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A28_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A28_2, false>(vu, c);
    }
    struct Kp3C60_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_5, false>(vu, c);
    }
    struct Kp3CC0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3CC0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_3, false>(vu, c);
    }
    struct Kp3D28_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D28_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D28_4, false>(vu, c);
    }
    struct Kp3D88_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D88_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D88_2, false>(vu, c);
    }
    struct Kp2870_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_6, false>(vu, c);
    }
    struct Kp28D0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_6, false>(vu, c);
    }
    struct Kp2968_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2968_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2968_4, false>(vu, c);
    }
    struct Kp2BA0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e5293cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_6, false>(vu, c);
    }
    struct Kp2C00_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_6, false>(vu, c);
    }
    struct Kp2C60_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C60_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_6, false>(vu, c);
    }
    struct Kp2CC0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC0_3, false>(vu, c);
    }
    struct Kp2EF8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_5, false>(vu, c);
    }
    struct Kp2F58_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_5, false>(vu, c);
    }
    struct Kp2FB8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_6, false>(vu, c);
    }
    struct Kp3020_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3020_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3020_2, false>(vu, c);
    }
    struct Kp35C0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0429cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_5, false>(vu, c);
    }
    struct Kp39A0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_6, false>(vu, c);
    }
    struct Kp3C48_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_5, false>(vu, c);
    }
    struct Kp3CA8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CA8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_5, false>(vu, c);
    }
    struct Kp3D08_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_7, false>(vu, c);
    }
    struct Kp3270_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_5, false>(vu, c);
    }
    struct Kp32D0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32D0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_4, false>(vu, c);
    }
    struct Kp3580_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_5, false>(vu, c);
    }
    struct Kp35E0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p35E0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_5, false>(vu, c);
    }
    struct Kp3678_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3678_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_4, false>(vu, c);
    }
    struct Kp3270_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_6, false>(vu, c);
    }
    struct Kp3350_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3350_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3350_4, false>(vu, c);
    }
    struct Kp0230_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10850000u; p.upper = 0x182007eu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0230_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0230_2d, true>(vu, c);
    }
    struct Kp04D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e039deu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04D8_2d, true>(vu, c);
    }
    struct Kp05F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ea212au; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {10, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F8_2d, true>(vu, c);
    }
    struct Kp0678_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0678_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0678_2d, true>(vu, c);
    }
    struct Kp0798_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec3054u; p.upper = 0x1f4150eu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0798_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0798_2d, true>(vu, c);
    }
    struct Kp0818_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {14, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0818_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0818_2d, true>(vu, c);
    }
    struct Kp0CD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1dfd74au; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfWrite = {29, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD0_2d, true>(vu, c);
    }
    struct Kp0F58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f4340au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {16, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F58_2d, true>(vu, c);
    }
    struct Kp1000_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aa418u; p.upperUsage.vfRead[0] = {20, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {16, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1000_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1000_2d, true>(vu, c);
    }
    struct Kp10B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10B0_2d, true>(vu, c);
    }
    struct Kp1180_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x1f4150eu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1180_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1180_2d, true>(vu, c);
    }
    struct Kp1828_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80080874u; p.upper = 0x1d178aeu; p.lowerUsage.viRead = 258; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {17, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1828_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1828_2d, true>(vu, c);
    }
    struct Kp1930_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec0b7du; p.upper = 0x900387u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {16, 1}; p.upperUsage.vfWrite = {14, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1930_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1930_2d, true>(vu, c);
    }
    struct Kp1B58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e148fdu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B58_2d, true>(vu, c);
    }
    struct Kp1DF0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e379bcu; p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF0_2d, true>(vu, c);
    }
    struct Kp2200_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x1c0191cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2200_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2200_2d, true>(vu, c);
    }
    struct Kp2330_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0adu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2330_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2330_2d, true>(vu, c);
    }
    struct Kp2490_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32000u; p.upper = 0x180df00u; p.lowerUsage.vfRead[0] = {4, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {28, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2490_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2490_2d, true>(vu, c);
    }
    struct Kp2610_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x39000000u; p.upper = 0x802001feu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2610_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2610_1d, true>(vu, c);
    }
    struct Kp28B8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_7d, true>(vu, c);
    }
    struct Kp2AD0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AD0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AD0_1d, true>(vu, c);
    }
    struct Kp2F80_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F80_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_5d, true>(vu, c);
    }
    struct Kp3290_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3290_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_6d, true>(vu, c);
    }
    struct Kp3598_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_6d, true>(vu, c);
    }
    struct Kp3678_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3678_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3678_5d, true>(vu, c);
    }
    struct Kp38F8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_6d, true>(vu, c);
    }
    struct Kp3968_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3968_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_7d, true>(vu, c);
    }
    struct Kp3A50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A50_2d, true>(vu, c);
    }
    struct Kp0268_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xc10fcfu; p.upperUsage.vfRead[0] = {1, 7}; p.upperUsage.vfWrite = {31, 6}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 6; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0268_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0268_2d, true>(vu, c);
    }
    struct Kp0500_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f23fu; p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0500_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0500_2d, true>(vu, c);
    }
    struct Kp0820_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x124f98cu; p.upperUsage.vfRead[0] = {31, 9}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfWrite = {6, 9}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 9; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0820_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0820_3d, true>(vu, c);
    }
    struct Kp0930_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8208du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 4}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0930_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0930_2d, true>(vu, c);
    }
    struct Kp09C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e430bdu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C8_2d, true>(vu, c);
    }
    struct Kp0AA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c531bdu; p.upperUsage.vfRead[0] = {6, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AA0_2d, true>(vu, c);
    }
    struct Kp0B38_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086133cu; p.upper = 0x820140u; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B38_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B38_2d, true>(vu, c);
    }
    struct Kp0BD8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10020088u; p.upper = 0x105f945u; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BD8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BD8_2d, true>(vu, c);
    }
    struct Kp0C70_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c531bdu; p.upperUsage.vfRead[0] = {6, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C70_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C70_2d, true>(vu, c);
    }
    struct Kp0CD8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df1a49u; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD8_3d, true>(vu, c);
    }
    struct Kp0EB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EB8_2d, true>(vu, c);
    }
    struct Kp0FF0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2d10au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FF0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FF0_3d, true>(vu, c);
    }
    struct Kp1140_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1140_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1140_2d, true>(vu, c);
    }
    struct Kp1228_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x4103c0u; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {15, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1228_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1228_2d, true>(vu, c);
    }
    struct Kp1358_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180283cu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1358_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1358_2d, true>(vu, c);
    }
    struct Kp13F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x99cbc4u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F8_2d, true>(vu, c);
    }
    struct Kp14F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14F8_2d, true>(vu, c);
    }
    struct Kp15C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc2255de0u; p.upper = 0x81e0399eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15C0_2d, true>(vu, c);
    }
    struct Kp1628_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18279d8u; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1628_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1628_2d, true>(vu, c);
    }
    struct Kp16A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A8_2d, true>(vu, c);
    }
    struct Kp17D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1211bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17D0_2d, true>(vu, c);
    }
    struct Kp1830_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x26018eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfWrite = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1830_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1830_3d, true>(vu, c);
    }
    struct Kp1948_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1948_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1948_2d, true>(vu, c);
    }
    struct Kp1AC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5c1bcu; p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC0_2d, true>(vu, c);
    }
    struct Kp1B20_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2a08u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B20_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B20_2d, true>(vu, c);
    }
    struct Kp1C00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C00_2d, true>(vu, c);
    }
    struct Kp1D80_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x828c59u; p.upperUsage.vfRead[0] = {17, 4}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {17, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D80_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D80_2d, true>(vu, c);
    }
    struct Kp1E48_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb337du; p.upper = 0x105985bu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E48_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E48_2d, true>(vu, c);
    }
    struct Kp1F88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803d03fdu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F88_2d, true>(vu, c);
    }
    struct Kp2088_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180e9e7u; p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2088_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2088_2d, true>(vu, c);
    }
    struct Kp2168_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b5802u; p.upper = 0x18238e8u; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {2, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2168_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2168_2d, true>(vu, c);
    }
    struct Kp2228_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8034c33cu; p.upper = 0x1dcc2beu; p.lowerUsage.vfRead[0] = {24, 1}; p.lowerUsage.vfWrite = {20, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2228_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2228_2d, true>(vu, c);
    }
    struct Kp2370_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1930abeu; p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {19, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2370_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2370_2d, true>(vu, c);
    }
    struct Kp2430_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fd744fdu; p.upper = 0x81e528aau; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2430_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2430_2d, true>(vu, c);
    }
    struct Kp24A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24A0_2d, true>(vu, c);
    }
    struct Kp2898_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022067cu; p.upper = 0x1c8a0beu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_7d, true>(vu, c);
    }
    struct Kp2900_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_8d, true>(vu, c);
    }
    struct Kp2CA8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA8_5d, true>(vu, c);
    }
    struct Kp2D78_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D78_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D78_1d, true>(vu, c);
    }
    struct Kp2F60_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F60_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_6d, true>(vu, c);
    }
    struct Kp3080_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3080_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3080_1d, true>(vu, c);
    }
    struct Kp3268_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3268_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3268_6d, true>(vu, c);
    }
    struct Kp32E8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_6d, true>(vu, c);
    }
    struct Kp33C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33C0_2d, true>(vu, c);
    }
    struct Kp35E8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_7d, true>(vu, c);
    }
    struct Kp3738_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3738_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3738_1d, true>(vu, c);
    }
    struct Kp3C40_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_6d, true>(vu, c);
    }
    struct Kp3DF0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3DF0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DF0_1d, true>(vu, c);
    }
    struct Kp2C00_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_7d, true>(vu, c);
    }
    struct Kp2870_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_8d, true>(vu, c);
    }
    struct Kp2950_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2950_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_6d, true>(vu, c);
    }
    struct Kp2BD8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_7d, true>(vu, c);
    }
    struct Kp2C58_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C58_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_7d, true>(vu, c);
    }
    struct Kp2EF0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_6d, true>(vu, c);
    }
    struct Kp3280_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_8d, true>(vu, c);
    }
    struct Kp36A0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A0_5d, true>(vu, c);
    }
    struct Kp39F0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_5d, true>(vu, c);
    }
    struct Kp3C80_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3C80_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_6d, true>(vu, c);
    }
    struct Kp2860_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_10d, true>(vu, c);
    }
    struct Kp28C8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_8d, true>(vu, c);
    }
    struct Kp29B8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29B8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B8_3d, true>(vu, c);
    }
    struct Kp2C68_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_9d, true>(vu, c);
    }
    struct Kp3298_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_7d, true>(vu, c);
    }
    struct Kp3920_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_8d, true>(vu, c);
    }
    struct Kp3C60_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_8d, true>(vu, c);
    }
    struct Kp3D48_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D48_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D48_5d, true>(vu, c);
    }
    struct Kp2B90_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B90_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B90_8d, true>(vu, c);
    }
    struct Kp38E8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_9d, true>(vu, c);
    }
    struct Kp3CE0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_7d, true>(vu, c);
    }
    struct Kp2EE0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_8d, true>(vu, c);
    }
    struct Kp2FD0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_9d, true>(vu, c);
    }
    struct Kp3260_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_8d, true>(vu, c);
    }
    struct Kp3340_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3340_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3340_5d, true>(vu, c);
    }
    struct Kp35C8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_6d, true>(vu, c);
    }
    struct Kp3648_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3648_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3648_7d, true>(vu, c);
    }
    struct Kp39A8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_9d, true>(vu, c);
    }
    struct Kp32E8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E8_8d, true>(vu, c);
    }
    struct Kp38F0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_9d, true>(vu, c);
    }
    struct Kp39D0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_7d, true>(vu, c);
    }
    struct Kp3C50_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_8d, true>(vu, c);
    }
    struct Kp3CC0_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3CC0_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC0_5d, true>(vu, c);
    }
    struct Kp3DA8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DA8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DA8_2d, true>(vu, c);
    }
    struct Kp2920_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_11d, true>(vu, c);
    }
    struct Kp2BB0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_10d, true>(vu, c);
    }
    struct Kp2C90_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C90_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_7d, true>(vu, c);
    }
    struct Kp2F10_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_8d, true>(vu, c);
    }
    struct Kp2F80_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F80_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_6d, true>(vu, c);
    }
    struct Kp3068_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3068_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3068_2d, true>(vu, c);
    }
    struct Kp3CC8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_5d, true>(vu, c);
    }
    struct Kp3598_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_10d, true>(vu, c);
    }
    struct Kp2FA0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_7d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
