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
    struct Kp0040_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c06bdu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0040_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0040_0, false>(vu, c);
    }
    struct Kp00A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb016800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00A0_0, false>(vu, c);
    }
    struct Kp0100_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800152b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0100_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0100_0, false>(vu, c);
    }
    struct Kp0160_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0160_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0160_0, false>(vu, c);
    }
    struct Kp01C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010028u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01C0_0, false>(vu, c);
    }
    struct Kp0220_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8188533cu; p.upper = 0x1e9296au; p.lowerUsage.vfRead[0] = {10, 12}; p.lowerUsage.vfWrite = {8, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {9, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0220_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0220_0, false>(vu, c);
    }
    struct Kp0280_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0280_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0280_0, false>(vu, c);
    }
    struct Kp02E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02E0_0, false>(vu, c);
    }
    struct Kp0340_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0340_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0340_0, false>(vu, c);
    }
    struct Kp03A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9051001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03A0_0, false>(vu, c);
    }
    struct Kp0400_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13eb0fffu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0400_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0400_0, false>(vu, c);
    }
    struct Kp0460_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b1feu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0460_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0460_0, false>(vu, c);
    }
    struct Kp04C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c001c3u; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04C0_0, false>(vu, c);
    }
    struct Kp0520_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1866048u; p.upper = 0x1e7ef69u; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {29, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0520_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0520_0, false>(vu, c);
    }
    struct Kp0580_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x691898u; p.upperUsage.vfRead[0] = {3, 3}; p.upperUsage.vfRead[1] = {9, 8}; p.upperUsage.vfWrite = {2, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0580_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0580_0, false>(vu, c);
    }
    struct Kp05E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803df33cu; p.upper = 0x60012cu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05E0_0, false>(vu, c);
    }
    struct Kp0640_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f621bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {22, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0640_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0640_0, false>(vu, c);
    }
    struct Kp06A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800007bfu; p.upper = 0x2ffu; p.lowerUsage.waitP = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06A0_0, false>(vu, c);
    }
    struct Kp0700_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18ab498u; p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0700_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0700_0, false>(vu, c);
    }
    struct Kp0760_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c26042u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 14}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0760_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0760_0, false>(vu, c);
    }
    struct Kp07C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x5630bfu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07C0_0, false>(vu, c);
    }
    struct Kp0820_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4e30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {14, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0820_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0820_0, false>(vu, c);
    }
    struct Kp0880_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e107ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0880_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0880_0, false>(vu, c);
    }
    struct Kp08E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa426045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4100; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08E0_0, false>(vu, c);
    }
    struct Kp0940_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80036b74u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8200; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0940_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0940_0, false>(vu, c);
    }
    struct Kp09A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09A0_0, false>(vu, c);
    }
    struct Kp0A00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A00_0, false>(vu, c);
    }
    struct Kp0A60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10012000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A60_0, false>(vu, c);
    }
    struct Kp0AC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80042130u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AC0_0, false>(vu, c);
    }
    struct Kp0B20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4d03a0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B20_0, false>(vu, c);
    }
    struct Kp0B80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f55811u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B80_0, false>(vu, c);
    }
    struct Kp0BE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BE0_0, false>(vu, c);
    }
    struct Kp0C40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1df17ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {31, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C40_0, false>(vu, c);
    }
    struct Kp0CA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x8040bd00u; p.upperUsage.vfRead[0] = {23, 2}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {20, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0CA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA0_0, false>(vu, c);
    }
    struct Kp0D00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5275u; p.upper = 0x1d6efa9u; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {22, 14}; p.upperUsage.vfWrite = {30, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D00_0, false>(vu, c);
    }
    struct Kp0D60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800aebfcu; p.upper = 0x1c0d83cu; p.lowerUsage.vfRead[0] = {29, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D60_0, false>(vu, c);
    }
    struct Kp0DC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DC0_0, false>(vu, c);
    }
    struct Kp0E20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000075au; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E20_0, false>(vu, c);
    }
    struct Kp0E80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800420f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E80_0, false>(vu, c);
    }
    struct Kp0EE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ec5810u; p.upper = 0x1e0a1feu; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE0_0, false>(vu, c);
    }
    struct Kp0F40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e66051u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F40_0, false>(vu, c);
    }
    struct Kp0FA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec360au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {24, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FA0_0, false>(vu, c);
    }
    struct Kp1000_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aa418u; p.upperUsage.vfRead[0] = {20, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {16, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1000_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1000_0, false>(vu, c);
    }
    struct Kp1060_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81f4150eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1060_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1060_0, false>(vu, c);
    }
    struct Kp10C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec130eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10C0_0, false>(vu, c);
    }
    struct Kp1120_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10021001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1120_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1120_0, false>(vu, c);
    }
    struct Kp1180_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x1f4150eu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1180_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1180_0, false>(vu, c);
    }
    struct Kp11E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11E0_0, false>(vu, c);
    }
    struct Kp1240_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e507ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1240_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1240_0, false>(vu, c);
    }
    struct Kp12A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000771u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12A0_0, false>(vu, c);
    }
    struct Kp1300_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1300_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1300_0, false>(vu, c);
    }
    struct Kp1360_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x88f6045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1360_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1360_0, false>(vu, c);
    }
    struct Kp13C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100f7803u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13C0_0, false>(vu, c);
    }
    struct Kp1420_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1420_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1420_0, false>(vu, c);
    }
    struct Kp1480_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10490000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1480_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1480_0, false>(vu, c);
    }
    struct Kp14E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14E0_0, false>(vu, c);
    }
    struct Kp1540_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806653fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {10, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1540_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1540_0, false>(vu, c);
    }
    struct Kp15A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15A0_0, false>(vu, c);
    }
    struct Kp1600_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80054174u; p.upper = 0x2ffu; p.lowerUsage.viRead = 288; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1600_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1600_0, false>(vu, c);
    }
    struct Kp1660_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11e507ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1660_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1660_0, false>(vu, c);
    }
    struct Kp16C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f66040u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16C0_0, false>(vu, c);
    }
    struct Kp1720_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520600ebu; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1720_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1720_0, false>(vu, c);
    }
    struct Kp1780_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1003003fu; p.upper = 0x1cf79ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1780_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1780_0, false>(vu, c);
    }
    struct Kp17E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80034a74u; p.upper = 0x2ffu; p.lowerUsage.viRead = 520; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17E0_0, false>(vu, c);
    }
    struct Kp1840_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80080874u; p.upper = 0x4f09bfu; p.lowerUsage.viRead = 258; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1840_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1840_0, false>(vu, c);
    }
    struct Kp18A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80244bfdu; p.upper = 0x1000043u; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.viRead = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 9}; p.upperUsage.vfWrite = {1, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18A0_0, false>(vu, c);
    }
    struct Kp1900_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x460003ecu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p1900_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1900_0, false>(vu, c);
    }
    struct Kp1960_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e507ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1960_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1960_0, false>(vu, c);
    }
    struct Kp19C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19C0_0, false>(vu, c);
    }
    struct Kp1A20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068f0u; p.upper = 0x82117cu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 4}; p.upperUsage.vfWrite = {2, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A20_0, false>(vu, c);
    }
    struct Kp1A80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800173b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16386; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A80_0, false>(vu, c);
    }
    struct Kp1AE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x181093cu; p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AE0_0, false>(vu, c);
    }
    struct Kp1B40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500e0005u; p.upper = 0x1e139bcu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B40_0, false>(vu, c);
    }
    struct Kp1BA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48000800u; p.upper = 0x20012cu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {4, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BA0_0, false>(vu, c);
    }
    struct Kp1C00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010012u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C00_0, false>(vu, c);
    }
    struct Kp1C60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800050f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C60_0, false>(vu, c);
    }
    struct Kp1CC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a5000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CC0_0, false>(vu, c);
    }
    struct Kp1D20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800060f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D20_0, false>(vu, c);
    }
    struct Kp1D80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa223800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 132; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D80_0, false>(vu, c);
    }
    struct Kp1DE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806303bcu; p.upper = 0x1c309bcu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 8}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DE0_0, false>(vu, c);
    }
    struct Kp1E40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E40_0, false>(vu, c);
    }
    struct Kp1EA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800052f0u; p.upper = 0x1d608a9u; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {22, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EA0_0, false>(vu, c);
    }
    struct Kp1F00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x380a0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F00_0, false>(vu, c);
    }
    struct Kp1F60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007e2u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F60_0, false>(vu, c);
    }
    struct Kp1FC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e103bcu; p.upper = 0x1c010dcu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FC0_0, false>(vu, c);
    }
    struct Kp2020_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e103bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2020_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2020_0, false>(vu, c);
    }
    struct Kp2080_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1c3197du; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2080_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2080_0, false>(vu, c);
    }
    struct Kp20E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20E0_0, false>(vu, c);
    }
    struct Kp2140_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2140_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2140_0, false>(vu, c);
    }
    struct Kp21A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9bfu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21A0_0, false>(vu, c);
    }
    struct Kp2200_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x1c0191cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2200_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2200_0, false>(vu, c);
    }
    struct Kp2260_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c5217du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2260_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2260_0, false>(vu, c);
    }
    struct Kp22C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a9beu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22C0_0, false>(vu, c);
    }
    struct Kp2320_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1803a00u; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2320_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2320_0, false>(vu, c);
    }
    struct Kp2380_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2380_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2380_0, false>(vu, c);
    }
    struct Kp23E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32000u; p.upper = 0x180df00u; p.lowerUsage.vfRead[0] = {4, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {28, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23E0_0, false>(vu, c);
    }
    struct Kp2440_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e807ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2440_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2440_0, false>(vu, c);
    }
    struct Kp24A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa271800u; p.upper = 0x1c2a0edu; p.lowerUsage.viRead = 136; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24A0_0, false>(vu, c);
    }
    struct Kp2500_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e639beu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2500_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2500_0, false>(vu, c);
    }
    struct Kp2560_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2560_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2560_0, false>(vu, c);
    }
    struct Kp25C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e77000u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {14, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 128; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25C0_0, false>(vu, c);
    }
    struct Kp2620_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x880213u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2620_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2620_0, false>(vu, c);
    }
    struct Kp2680_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80250b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2680_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2680_0, false>(vu, c);
    }
    struct Kp26E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26E0_0, false>(vu, c);
    }
    struct Kp2740_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2740_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2740_0, false>(vu, c);
    }
    struct Kp27A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x210846u; p.upperUsage.vfRead[0] = {1, 3}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p27A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27A0_0, false>(vu, c);
    }
    struct Kp2800_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8065a3fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {20, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2800_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2800_0, false>(vu, c);
    }
    struct Kp2860_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_0, false>(vu, c);
    }
    struct Kp28C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_0, false>(vu, c);
    }
    struct Kp2920_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_0, false>(vu, c);
    }
    struct Kp2980_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2980_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2980_0, false>(vu, c);
    }
    struct Kp29E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d08au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E0_0, false>(vu, c);
    }
    struct Kp2A40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A40_0, false>(vu, c);
    }
    struct Kp2AA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2AA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AA0_0, false>(vu, c);
    }
    struct Kp2B00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb237du; p.upper = 0x1c0109cu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B00_0, false>(vu, c);
    }
    struct Kp2B60_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B60_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B60_0, false>(vu, c);
    }
    struct Kp2BC0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_0, false>(vu, c);
    }
    struct Kp2C20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C20_0, false>(vu, c);
    }
    struct Kp2C80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_0, false>(vu, c);
    }
    struct Kp2F10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_0, false>(vu, c);
    }
    struct Kp2F70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_0, false>(vu, c);
    }
    struct Kp2FD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2FD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_0, false>(vu, c);
    }
    struct Kp3260_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_0, false>(vu, c);
    }
    struct Kp32C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C0_0, false>(vu, c);
    }
    struct Kp3320_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_0, false>(vu, c);
    }
    struct Kp3380_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3380_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3380_0, false>(vu, c);
    }
    struct Kp35A0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_0, false>(vu, c);
    }
    struct Kp3600_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3600_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3600_0, false>(vu, c);
    }
    struct Kp3660_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3660_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_0, false>(vu, c);
    }
    struct Kp36C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36C0_0, false>(vu, c);
    }
    struct Kp38C0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38C0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38C0_0, false>(vu, c);
    }
    struct Kp3920_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_0, false>(vu, c);
    }
    struct Kp3980_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8213cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3980_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3980_0, false>(vu, c);
    }
    struct Kp39E0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39E0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E0_0, false>(vu, c);
    }
    struct Kp3A40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A40_0, false>(vu, c);
    }
    struct Kp3AA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3AA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AA0_0, false>(vu, c);
    }
    struct Kp0008_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b0233u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0008_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0008_1, false>(vu, c);
    }
    struct Kp0070_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb0e6016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20480; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0070_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0070_1, false>(vu, c);
    }
    struct Kp00D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p00D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00D0_1, false>(vu, c);
    }
    struct Kp0130_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0130_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0130_1, false>(vu, c);
    }
    struct Kp0190_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c08f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0190_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0190_1, false>(vu, c);
    }
    struct Kp01F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000806u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F8_1, false>(vu, c);
    }
    struct Kp0258_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x626015u; p.upper = 0x1e00114u; p.lowerUsage.vfWrite = {2, 3}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0258_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0258_1, false>(vu, c);
    }
    struct Kp02C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02C0_1, false>(vu, c);
    }
    struct Kp0320_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb513eu; p.upperUsage.vfRead[0] = {10, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0320_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0320_1, false>(vu, c);
    }
    struct Kp0380_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e1137cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.viLatency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0380_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0380_1, false>(vu, c);
    }
    struct Kp03E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ec593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p03E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03E0_1, false>(vu, c);
    }
    struct Kp0440_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10063001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0440_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0440_1, false>(vu, c);
    }
    struct Kp04A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04A0_1, false>(vu, c);
    }
    struct Kp0500_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f23fu; p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0500_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0500_1, false>(vu, c);
    }
    struct Kp0560_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff120eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0560_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0560_1, false>(vu, c);
    }
    struct Kp05C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05C0_1, false>(vu, c);
    }
    struct Kp0620_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1e04a5fu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0620_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0620_1, false>(vu, c);
    }
    struct Kp0680_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0680_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0680_1, false>(vu, c);
    }
    struct Kp06E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3437du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p06E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06E0_1, false>(vu, c);
    }
    struct Kp0740_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0740_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0740_1, false>(vu, c);
    }
    struct Kp07A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x102097cu; p.upperUsage.vfRead[0] = {1, 8}; p.upperUsage.vfWrite = {2, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07A0_1, false>(vu, c);
    }
    struct Kp0800_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803f067cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {31, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0800_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0800_1, false>(vu, c);
    }
    struct Kp0860_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0860_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0860_1, false>(vu, c);
    }
    struct Kp08C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08C0_1, false>(vu, c);
    }
    struct Kp0920_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0103cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0920_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0920_1, false>(vu, c);
    }
    struct Kp0980_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0980_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0980_1, false>(vu, c);
    }
    struct Kp09E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010044u; p.upper = 0x1c8416eu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09E0_1, false>(vu, c);
    }
    struct Kp0A48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10930bfu; p.upperUsage.vfRead[0] = {6, 8}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A48_1, false>(vu, c);
    }
    struct Kp0AB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0083cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AB0_1, false>(vu, c);
    }
    struct Kp0B10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x400262u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {9, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B10_1, false>(vu, c);
    }
    struct Kp0B70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e430bdu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B70_1, false>(vu, c);
    }
    struct Kp0BD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000au; p.upper = 0x105f87du; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BD0_1, false>(vu, c);
    }
    struct Kp0C30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8039deu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C30_1, false>(vu, c);
    }
    struct Kp0C90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e92b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C90_1, false>(vu, c);
    }
    struct Kp0CF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df19cbu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {31, 1}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CF0_1, false>(vu, c);
    }
    struct Kp0D50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802443fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D50_1, false>(vu, c);
    }
    struct Kp0DB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DB0_1, false>(vu, c);
    }
    struct Kp0E10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x3ad686u; p.upperUsage.vfRead[0] = {26, 3}; p.upperUsage.vfWrite = {26, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E10_1, false>(vu, c);
    }
    struct Kp0E70_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E70_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E70_1, false>(vu, c);
    }
    struct Kp0ED0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0ED0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0ED0_1, false>(vu, c);
    }
    struct Kp0F30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F30_1, false>(vu, c);
    }
    struct Kp0F90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F90_1, false>(vu, c);
    }
    struct Kp0FF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2d10au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FF0_1, false>(vu, c);
    }
    struct Kp1050_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e50223u; p.upper = 0x1c3e0e9u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1050_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1050_1, false>(vu, c);
    }
    struct Kp10B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb237du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10B0_1, false>(vu, c);
    }
    struct Kp1110_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f20802u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {18, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1110_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1110_1, false>(vu, c);
    }
    struct Kp1170_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c211ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1170_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1170_1, false>(vu, c);
    }
    struct Kp11D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11D0_1, false>(vu, c);
    }
    struct Kp1230_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c07bdcu; p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfWrite = {15, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1230_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1230_1, false>(vu, c);
    }
    struct Kp1290_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1290_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1290_1, false>(vu, c);
    }
    struct Kp12F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12F0_1, false>(vu, c);
    }
    struct Kp1358_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180283cu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1358_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1358_1, false>(vu, c);
    }
    struct Kp13B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb17ffu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13B8_1, false>(vu, c);
    }
    struct Kp1420_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c07bdcu; p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfWrite = {15, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1420_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1420_1, false>(vu, c);
    }
    struct Kp1480_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1480_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1480_1, false>(vu, c);
    }
    struct Kp14E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef98cbu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14E0_1, false>(vu, c);
    }
    struct Kp1540_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e70224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1540_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1540_1, false>(vu, c);
    }
    struct Kp15A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e011e7u; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15A0_1, false>(vu, c);
    }
    struct Kp1600_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e332bdu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1600_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1600_1, false>(vu, c);
    }
    struct Kp1660_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180283cu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1660_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1660_1, false>(vu, c);
    }
    struct Kp16C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb17ffu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16C0_1, false>(vu, c);
    }
    struct Kp1720_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f20802u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {18, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1720_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1720_1, false>(vu, c);
    }
    struct Kp1780_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1780_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1780_1, false>(vu, c);
    }
    struct Kp17E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17E0_1, false>(vu, c);
    }
    struct Kp1840_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2701ceu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1840_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1840_1, false>(vu, c);
    }
    struct Kp18A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18A0_1, false>(vu, c);
    }
    struct Kp1900_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1900_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1900_1, false>(vu, c);
    }
    struct Kp1960_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1960_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1960_1, false>(vu, c);
    }
    struct Kp19C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19C0_1, false>(vu, c);
    }
    struct Kp1A20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8416016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A20_1, false>(vu, c);
    }
    struct Kp1A80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e50224u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A80_1, false>(vu, c);
    }
    struct Kp1AE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4c8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AE0_1, false>(vu, c);
    }
    struct Kp1B40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x26018eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfWrite = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B40_1, false>(vu, c);
    }
    struct Kp1BA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BA0_1, false>(vu, c);
    }
    struct Kp1C00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C00_1, false>(vu, c);
    }
    struct Kp1C60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818b0b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C60_1, false>(vu, c);
    }
    struct Kp1CC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e9e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {9, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CC0_1, false>(vu, c);
    }
    struct Kp1D20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D20_1, false>(vu, c);
    }
    struct Kp1D80_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x828c59u; p.upperUsage.vfRead[0] = {17, 4}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {17, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D80_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D80_1, false>(vu, c);
    }
    struct Kp1DE0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e70223u; p.upper = 0x1e198cbu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DE0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DE0_1, false>(vu, c);
    }
    struct Kp1E40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb7b7du; p.upper = 0xe0006cu; p.lowerUsage.vfRead[0] = {15, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfWrite = {1, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E40_1, false>(vu, c);
    }
    struct Kp1EA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18128e8u; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {1, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EA0_1, false>(vu, c);
    }
    struct Kp1F00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F00_1, false>(vu, c);
    }
    struct Kp1F60_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x100949cu; p.upperUsage.vfRead[0] = {18, 8}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F60_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F60_1, false>(vu, c);
    }
    struct Kp1FC0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80458bfcu; p.upper = 0x1c2e0a9u; p.lowerUsage.vfRead[0] = {17, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FC0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FC0_1, false>(vu, c);
    }
    struct Kp2020_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb015800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2050; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2020_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2020_1, false>(vu, c);
    }
    struct Kp2080_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3b000000u; p.upper = 0x81802a3fu; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2080_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2080_1, false>(vu, c);
    }
    struct Kp20E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81cb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20E0_1, false>(vu, c);
    }
    struct Kp2140_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180089eu; p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2140_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2140_1, false>(vu, c);
    }
    struct Kp21A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21A0_1, false>(vu, c);
    }
    struct Kp2200_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ecb30au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2200_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2200_1, false>(vu, c);
    }
    struct Kp2260_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1dbedcbu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {27, 1}; p.upperUsage.vfWrite = {23, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2260_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2260_1, false>(vu, c);
    }
    struct Kp22C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0560u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22C0_1, false>(vu, c);
    }
    struct Kp2320_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cdd04au; p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2320_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2320_1, false>(vu, c);
    }
    struct Kp2380_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18de8cbu; p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2380_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2380_1, false>(vu, c);
    }
    struct Kp23E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e800000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p23E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23E0_1, false>(vu, c);
    }
    struct Kp2440_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2440_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2440_1, false>(vu, c);
    }
    struct Kp24A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24A0_1, false>(vu, c);
    }
    struct Kp2850_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520b2ffdu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2080; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2850_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_1, false>(vu, c);
    }
    struct Kp28B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d1084bu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_1, false>(vu, c);
    }
    struct Kp2910_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2403ffffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2910_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_1, false>(vu, c);
    }
    struct Kp2970_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2970_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2970_1, false>(vu, c);
    }
    struct Kp2BD0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2403ffffu; p.upper = 0x1e5297cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_1, false>(vu, c);
    }
    struct Kp2C30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C30_1, false>(vu, c);
    }
    struct Kp2C90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_1, false>(vu, c);
    }
    struct Kp2CF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CF0_0, false>(vu, c);
    }
    struct Kp2D50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D50_0, false>(vu, c);
    }
    struct Kp2DB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2DB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2DB0_0, false>(vu, c);
    }
    struct Kp2F30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_1, false>(vu, c);
    }
    struct Kp2F90_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F90_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_1, false>(vu, c);
    }
    struct Kp2FF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_0, false>(vu, c);
    }
    struct Kp3050_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507eeu; p.upper = 0x1eb192bu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3050_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3050_0, false>(vu, c);
    }
    struct Kp30B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p30B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30B0_0, false>(vu, c);
    }
    struct Kp3238_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_1, false>(vu, c);
    }
    struct Kp3298_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_1, false>(vu, c);
    }
    struct Kp32F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_1, false>(vu, c);
    }
    struct Kp3358_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3358_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_1, false>(vu, c);
    }
    struct Kp33B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33B8_0, false>(vu, c);
    }
    struct Kp3418_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3418_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3418_0, false>(vu, c);
    }
    struct Kp3598_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_1, false>(vu, c);
    }
    struct Kp35F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_1, false>(vu, c);
    }
    struct Kp3658_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_1, false>(vu, c);
    }
    struct Kp36B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B8_1, false>(vu, c);
    }
    struct Kp3738_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3738_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3738_0, false>(vu, c);
    }
    struct Kp3798_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3798_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3798_0, false>(vu, c);
    }
    struct Kp3918_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_1, false>(vu, c);
    }
    struct Kp3978_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3978_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3978_1, false>(vu, c);
    }
    struct Kp39D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_1, false>(vu, c);
    }
    struct Kp3A38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3A38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A38_1, false>(vu, c);
    }
    struct Kp3C38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_0, false>(vu, c);
    }
    struct Kp3C98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_0, false>(vu, c);
    }
    struct Kp3CF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_0, false>(vu, c);
    }
    struct Kp3D58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D58_0, false>(vu, c);
    }
    struct Kp3DB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DB8_0, false>(vu, c);
    }
    struct Kp3E18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E18_0, false>(vu, c);
    }
    struct Kp2860_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_2, false>(vu, c);
    }
    struct Kp28C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C0_2, false>(vu, c);
    }
    struct Kp2920_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_2, false>(vu, c);
    }
    struct Kp2BC8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_2, false>(vu, c);
    }
    struct Kp2C28_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C28_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_2, false>(vu, c);
    }
    struct Kp2CB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB8_1, false>(vu, c);
    }
    struct Kp3D20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_1, false>(vu, c);
    }
    struct Kp2870_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_3, false>(vu, c);
    }
    struct Kp28D0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D0_3, false>(vu, c);
    }
    struct Kp2930_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_3, false>(vu, c);
    }
    struct Kp2990_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2990_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_1, false>(vu, c);
    }
    struct Kp2BA0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_3, false>(vu, c);
    }
    struct Kp2C00_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_3, false>(vu, c);
    }
    struct Kp2C60_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C60_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_2, false>(vu, c);
    }
    struct Kp2CC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC8_1, false>(vu, c);
    }
    struct Kp2ED8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2ED8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2ED8_2, false>(vu, c);
    }
    struct Kp2F38_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_2, false>(vu, c);
    }
    struct Kp2F98_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F98_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_2, false>(vu, c);
    }
    struct Kp2FF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF8_1, false>(vu, c);
    }
    struct Kp3268_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3268_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3268_2, false>(vu, c);
    }
    struct Kp32C8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7817u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32C8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C8_2, false>(vu, c);
    }
    struct Kp3328_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3328_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3328_2, false>(vu, c);
    }
    struct Kp3598_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_2, false>(vu, c);
    }
    struct Kp35F8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_2, false>(vu, c);
    }
    struct Kp3658_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3658_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_2, false>(vu, c);
    }
    struct Kp38C8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38C8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38C8_2, false>(vu, c);
    }
    struct Kp3928_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_2, false>(vu, c);
    }
    struct Kp3988_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3988_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_2, false>(vu, c);
    }
    struct Kp39F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F0_2, false>(vu, c);
    }
    struct Kp3C60_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_2, false>(vu, c);
    }
    struct Kp3CF8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_2, false>(vu, c);
    }
    struct Kp2840_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_4, false>(vu, c);
    }
    struct Kp28A0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_4, false>(vu, c);
    }
    struct Kp2900_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_4, false>(vu, c);
    }
    struct Kp2960_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2960_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_3, false>(vu, c);
    }
    struct Kp29C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C0_2, false>(vu, c);
    }
    struct Kp2A20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A20_1, false>(vu, c);
    }
    struct Kp2C68_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_4, false>(vu, c);
    }
    struct Kp2EE8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_3, false>(vu, c);
    }
    struct Kp2F48_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_3, false>(vu, c);
    }
    struct Kp2FA8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_3, false>(vu, c);
    }
    struct Kp3218_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3218_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3218_1, false>(vu, c);
    }
    struct Kp3280_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3280_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_3, false>(vu, c);
    }
    struct Kp3310_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_3, false>(vu, c);
    }
    struct Kp3918_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_3, false>(vu, c);
    }
    struct Kp3978_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7816u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3978_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3978_3, false>(vu, c);
    }
    struct Kp3C20_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_2, false>(vu, c);
    }
    struct Kp3C80_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_2, false>(vu, c);
    }
    struct Kp3CE0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CE0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_2, false>(vu, c);
    }
    struct Kp3D40_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D40_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D40_3, false>(vu, c);
    }
    struct Kp2840_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_5, false>(vu, c);
    }
    struct Kp28A0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28A0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_5, false>(vu, c);
    }
    struct Kp2900_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0295fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2900_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2900_5, false>(vu, c);
    }
    struct Kp2BB0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1e6393cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_4, false>(vu, c);
    }
    struct Kp3638_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3638_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_3, false>(vu, c);
    }
    struct Kp3698_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3698_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_3, false>(vu, c);
    }
    struct Kp3910_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0429cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_4, false>(vu, c);
    }
    struct Kp3990_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3990_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3990_4, false>(vu, c);
    }
    struct Kp3C50_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C50_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C50_3, false>(vu, c);
    }
    struct Kp3CB0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CB0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB0_3, false>(vu, c);
    }
    struct Kp3D10_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D10_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D10_4, false>(vu, c);
    }
    struct Kp2940_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2940_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_5, false>(vu, c);
    }
    struct Kp2BE0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_5, false>(vu, c);
    }
    struct Kp2C40_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C40_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_3, false>(vu, c);
    }
    struct Kp2EF0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF0_4, false>(vu, c);
    }
    struct Kp2F50_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_4, false>(vu, c);
    }
    struct Kp2FE0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_4, false>(vu, c);
    }
    struct Kp3040_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3040_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3040_1, false>(vu, c);
    }
    struct Kp3278_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_4, false>(vu, c);
    }
    struct Kp32D8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p32D8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D8_3, false>(vu, c);
    }
    struct Kp3338_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_3, false>(vu, c);
    }
    struct Kp3398_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3398_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3398_2, false>(vu, c);
    }
    struct Kp35B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b0beu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_3, false>(vu, c);
    }
    struct Kp3610_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3610_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_3, false>(vu, c);
    }
    struct Kp3670_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_4, false>(vu, c);
    }
    struct Kp36D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D8_2, false>(vu, c);
    }
    struct Kp39B0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_5, false>(vu, c);
    }
    struct Kp3CE8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_3, false>(vu, c);
    }
    struct Kp2928_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_7, false>(vu, c);
    }
    struct Kp2C60_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C60_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_5, false>(vu, c);
    }
    struct Kp2FD0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FD0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_5, false>(vu, c);
    }
    struct Kp3580_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_4, false>(vu, c);
    }
    struct Kp35E0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p35E0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_4, false>(vu, c);
    }
    struct Kp3640_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0295fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3640_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_5, false>(vu, c);
    }
    struct Kp38F0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_5, false>(vu, c);
    }
    struct Kp3950_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3950_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_5, false>(vu, c);
    }
    struct Kp39B0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39B0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_6, false>(vu, c);
    }
    struct Kp3A10_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A10_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A10_2, false>(vu, c);
    }
    struct Kp3C48_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_4, false>(vu, c);
    }
    struct Kp3CA8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_4, false>(vu, c);
    }
    struct Kp3D08_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_6, false>(vu, c);
    }
    struct Kp3D70_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D70_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D70_2, false>(vu, c);
    }
    struct Kp2858_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_6, false>(vu, c);
    }
    struct Kp28B8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_6, false>(vu, c);
    }
    struct Kp2950_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2950_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2950_5, false>(vu, c);
    }
    struct Kp29B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B0_3, false>(vu, c);
    }
    struct Kp2BE8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_6, false>(vu, c);
    }
    struct Kp2C48_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C48_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_5, false>(vu, c);
    }
    struct Kp2CA8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA8_4, false>(vu, c);
    }
    struct Kp2EE0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_5, false>(vu, c);
    }
    struct Kp2F40_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F40_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_5, false>(vu, c);
    }
    struct Kp2FA0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_5, false>(vu, c);
    }
    struct Kp3008_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3008_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_3, false>(vu, c);
    }
    struct Kp3068_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3068_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3068_1, false>(vu, c);
    }
    struct Kp3988_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3988_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_5, false>(vu, c);
    }
    struct Kp3C30_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_5, false>(vu, c);
    }
    struct Kp3C90_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C90_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_5, false>(vu, c);
    }
    struct Kp3CF0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_6, false>(vu, c);
    }
    struct Kp3258_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_5, false>(vu, c);
    }
    struct Kp32B8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32B8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_5, false>(vu, c);
    }
    struct Kp3318_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_6, false>(vu, c);
    }
    struct Kp35C8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_5, false>(vu, c);
    }
    struct Kp3660_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_7, false>(vu, c);
    }
    struct Kp2FC8_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FC8_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_7, false>(vu, c);
    }
    struct Kp3338_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x187313eu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3338_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3338_4, false>(vu, c);
    }
    struct Kp0218_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8047033du; p.upper = 0x20422cu; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {7, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {8, 1}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0218_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0218_2d, true>(vu, c);
    }
    struct Kp0468_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e073a7u; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfWrite = {14, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0468_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0468_2d, true>(vu, c);
    }
    struct Kp05E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x803df33cu; p.upper = 0x60012cu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {29, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfWrite = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05E0_2d, true>(vu, c);
    }
    struct Kp0660_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0660_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0660_2d, true>(vu, c);
    }
    struct Kp0780_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022033cu; p.upper = 0x1c118eau; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0780_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0780_2d, true>(vu, c);
    }
    struct Kp0800_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {13, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0800_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0800_2d, true>(vu, c);
    }
    struct Kp0CB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x180fddeu; p.upperUsage.vfRead[0] = {31, 12}; p.upperUsage.vfWrite = {23, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB8_2d, true>(vu, c);
    }
    struct Kp0F08_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e073a7u; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfWrite = {14, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F08_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F08_2d, true>(vu, c);
    }
    struct Kp0FC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC0_2d, true>(vu, c);
    }
    struct Kp1078_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x1f5154eu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {21, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1078_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1078_2d, true>(vu, c);
    }
    struct Kp1168_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022033cu; p.upper = 0x1c118eau; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1168_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1168_2d, true>(vu, c);
    }
    struct Kp16E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802613fcu; p.upper = 0x1800ddeu; p.lowerUsage.vfRead[0] = {2, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {23, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16E0_2d, true>(vu, c);
    }
    struct Kp1918_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100c03ecu; p.upper = 0x2010a2u; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1918_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1918_2d, true>(vu, c);
    }
    struct Kp1AE8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18110acu; p.upperUsage.vfRead[0] = {2, 12}; p.upperUsage.vfRead[1] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AE8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AE8_2d, true>(vu, c);
    }
    struct Kp1DD8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104f90au; p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD8_2d, true>(vu, c);
    }
    struct Kp2198_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4001e2u; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2198_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2198_2d, true>(vu, c);
    }
    struct Kp22D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x56003fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D8_2d, true>(vu, c);
    }
    struct Kp2458_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0195cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2458_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2458_2d, true>(vu, c);
    }
    struct Kp2510_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e641beu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2510_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2510_1d, true>(vu, c);
    }
    struct Kp2860_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_7d, true>(vu, c);
    }
    struct Kp2AB0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AB0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AB0_1d, true>(vu, c);
    }
    struct Kp2EE8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_6d, true>(vu, c);
    }
    struct Kp3278_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3278_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_6d, true>(vu, c);
    }
    struct Kp3360_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3360_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3360_4d, true>(vu, c);
    }
    struct Kp35F0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_6d, true>(vu, c);
    }
    struct Kp38D8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_6d, true>(vu, c);
    }
    struct Kp3948_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_6d, true>(vu, c);
    }
    struct Kp3A30_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A30_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A30_3d, true>(vu, c);
    }
    struct Kp3AB0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AB0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AB0_1d, true>(vu, c);
    }
    struct Kp04E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0103cu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E8_2d, true>(vu, c);
    }
    struct Kp0808_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0103cu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0808_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0808_3d, true>(vu, c);
    }
    struct Kp0918_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c51048u; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0918_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0918_2d, true>(vu, c);
    }
    struct Kp09B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09B0_2d, true>(vu, c);
    }
    struct Kp0A88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8039deu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A88_2d, true>(vu, c);
    }
    struct Kp0B10_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x400262u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {9, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B10_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B10_2d, true>(vu, c);
    }
    struct Kp0BC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8931bfu; p.upperUsage.vfRead[0] = {6, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BC0_2d, true>(vu, c);
    }
    struct Kp0C58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2039deu; p.upperUsage.vfRead[0] = {7, 1}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C58_2d, true>(vu, c);
    }
    struct Kp0CC0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c820cfu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC0_3d, true>(vu, c);
    }
    struct Kp0E08_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d3ce6au; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {19, 14}; p.upperUsage.vfWrite = {25, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E08_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E08_2d, true>(vu, c);
    }
    struct Kp0FD8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FD8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD8_2d, true>(vu, c);
    }
    struct Kp1050_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e50223u; p.upper = 0x1c3e0e9u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1050_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1050_3d, true>(vu, c);
    }
    struct Kp11F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x59c86du; p.upperUsage.vfRead[0] = {25, 2}; p.upperUsage.vfWrite = {1, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F8_2d, true>(vu, c);
    }
    struct Kp12F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12F0_2d, true>(vu, c);
    }
    struct Kp13E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x40003fu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13E0_2d, true>(vu, c);
    }
    struct Kp14E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef98cbu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14E0_2d, true>(vu, c);
    }
    struct Kp15A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e011e7u; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15A0_2d, true>(vu, c);
    }
    struct Kp1608_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40c90fdau; p.upper = 0x81e342bdu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1608_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1608_2d, true>(vu, c);
    }
    struct Kp1680_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b9007u; p.upper = 0x10798cdu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1680_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1680_2d, true>(vu, c);
    }
    struct Kp17A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c41afeu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17A0_2d, true>(vu, c);
    }
    struct Kp1818_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf2a48u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1818_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1818_2d, true>(vu, c);
    }
    struct Kp1900_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1900_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1900_2d, true>(vu, c);
    }
    struct Kp1AA8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AA8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA8_3d, true>(vu, c);
    }
    struct Kp1B08_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf29c8u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B08_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B08_2d, true>(vu, c);
    }
    struct Kp1B68_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c89a29u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B68_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B68_2d, true>(vu, c);
    }
    struct Kp1CD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1CD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CD0_2d, true>(vu, c);
    }
    struct Kp1DF0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DF0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DF0_3d, true>(vu, c);
    }
    struct Kp1F30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x910480u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {17, 8}; p.upperUsage.vfWrite = {18, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F30_2d, true>(vu, c);
    }
    struct Kp2070_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ed08000u; p.upper = 0x8100023eu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2070_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2070_3d, true>(vu, c);
    }
    struct Kp2150_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e141a8u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2150_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2150_2d, true>(vu, c);
    }
    struct Kp21F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eca1bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {12, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21F0_2d, true>(vu, c);
    }
    struct Kp2358_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2de8c7u; p.upperUsage.vfRead[0] = {29, 1}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2358_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2358_2d, true>(vu, c);
    }
    struct Kp2418_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a3fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2418_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2418_2d, true>(vu, c);
    }
    struct Kp2488_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbfb504f3u; p.upper = 0x81e049a3u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2488_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2488_3d, true>(vu, c);
    }
    struct Kp2870_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e9033cu; p.upper = 0x1e00200u; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_7d, true>(vu, c);
    }
    struct Kp28E0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40400000u; p.upper = 0x81e1d08au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28E0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_6d, true>(vu, c);
    }
    struct Kp2C80_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_8d, true>(vu, c);
    }
    struct Kp2D48_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D48_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D48_1d, true>(vu, c);
    }
    struct Kp2F40_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F40_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_6d, true>(vu, c);
    }
    struct Kp3028_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3028_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3028_3d, true>(vu, c);
    }
    struct Kp3250_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_6d, true>(vu, c);
    }
    struct Kp32B8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_6d, true>(vu, c);
    }
    struct Kp33A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33A8_2d, true>(vu, c);
    }
    struct Kp3590_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_6d, true>(vu, c);
    }
    struct Kp3720_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3720_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3720_1d, true>(vu, c);
    }
    struct Kp3A10_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A10_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A10_3d, true>(vu, c);
    }
    struct Kp3DC8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DC8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DC8_1d, true>(vu, c);
    }
    struct Kp2BA8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_8d, true>(vu, c);
    }
    struct Kp2858_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_8d, true>(vu, c);
    }
    struct Kp2938_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2938_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_6d, true>(vu, c);
    }
    struct Kp2BB8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_8d, true>(vu, c);
    }
    struct Kp2C28_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C28_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_7d, true>(vu, c);
    }
    struct Kp2D10_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D10_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D10_2d, true>(vu, c);
    }
    struct Kp2FD0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_8d, true>(vu, c);
    }
    struct Kp3648_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3648_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3648_6d, true>(vu, c);
    }
    struct Kp3980_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3980_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3980_6d, true>(vu, c);
    }
    struct Kp3C68_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_6d, true>(vu, c);
    }
    struct Kp3D50_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3D50_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D50_4d, true>(vu, c);
    }
    struct Kp28B0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_10d, true>(vu, c);
    }
    struct Kp2998_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2998_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2998_4d, true>(vu, c);
    }
    struct Kp2A10_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2A10_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A10_2d, true>(vu, c);
    }
    struct Kp3240_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_8d, true>(vu, c);
    }
    struct Kp3900_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_7d, true>(vu, c);
    }
    struct Kp3C40_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_7d, true>(vu, c);
    }
    struct Kp3D20_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D20_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D20_7d, true>(vu, c);
    }
    struct Kp28E0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E0_8d, true>(vu, c);
    }
    struct Kp2BF0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2BF0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_8d, true>(vu, c);
    }
    struct Kp3C70_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C70_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_8d, true>(vu, c);
    }
    struct Kp2C30_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C30_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C30_6d, true>(vu, c);
    }
    struct Kp2F40_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2F40_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_7d, true>(vu, c);
    }
    struct Kp3248_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_9d, true>(vu, c);
    }
    struct Kp3328_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3328_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3328_6d, true>(vu, c);
    }
    struct Kp35A8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_7d, true>(vu, c);
    }
    struct Kp3618_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3618_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_7d, true>(vu, c);
    }
    struct Kp3700_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3700_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3700_2d, true>(vu, c);
    }
    struct Kp2C48_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_8d, true>(vu, c);
    }
    struct Kp3630_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3630_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_6d, true>(vu, c);
    }
    struct Kp3950_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3950_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_7d, true>(vu, c);
    }
    struct Kp3C38_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_9d, true>(vu, c);
    }
    struct Kp3CA0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_7d, true>(vu, c);
    }
    struct Kp3D88_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D88_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D88_3d, true>(vu, c);
    }
    struct Kp2890_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_11d, true>(vu, c);
    }
    struct Kp2980_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2980_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2980_5d, true>(vu, c);
    }
    struct Kp2C10_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2C10_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_7d, true>(vu, c);
    }
    struct Kp2EF8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_10d, true>(vu, c);
    }
    struct Kp2F60_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F60_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F60_7d, true>(vu, c);
    }
    struct Kp3048_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3048_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3048_3d, true>(vu, c);
    }
    struct Kp3C38_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_10d, true>(vu, c);
    }
    struct Kp3580_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_8d, true>(vu, c);
    }
    struct Kp3670_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_9d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
