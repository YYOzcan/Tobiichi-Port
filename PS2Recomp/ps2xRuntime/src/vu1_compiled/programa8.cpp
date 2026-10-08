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
    struct Kp0038_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000003u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0038_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0038_0, false>(vu, c);
    }
    struct Kp0098_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0098_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0098_0, false>(vu, c);
    }
    struct Kp00F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010010u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00F8_0, false>(vu, c);
    }
    struct Kp0158_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90a6045u; p.upper = 0x1d4a0eau; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0158_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0158_0, false>(vu, c);
    }
    struct Kp01B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x20022cu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01B8_0, false>(vu, c);
    }
    struct Kp0218_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8047033du; p.upper = 0x20422cu; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {7, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {8, 1}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0218_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0218_0, false>(vu, c);
    }
    struct Kp0278_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80041874u; p.upper = 0x1e2282du; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0278_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0278_0, false>(vu, c);
    }
    struct Kp02D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02D8_0, false>(vu, c);
    }
    struct Kp0338_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0338_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0338_0, false>(vu, c);
    }
    struct Kp0398_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x580051b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0398_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0398_0, false>(vu, c);
    }
    struct Kp03F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010a70u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03F8_0, false>(vu, c);
    }
    struct Kp0458_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ef5813u; p.upper = 0x1e06b67u; p.lowerUsage.vfWrite = {15, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0458_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0458_0, false>(vu, c);
    }
    struct Kp04B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8027033cu; p.upper = 0x1c00783u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {30, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04B8_0, false>(vu, c);
    }
    struct Kp0518_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1856047u; p.upper = 0x1e7e72au; p.lowerUsage.vfWrite = {5, 12}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {28, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0518_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0518_0, false>(vu, c);
    }
    struct Kp0578_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000807u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0578_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0578_0, false>(vu, c);
    }
    struct Kp05D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x43800000u; p.upper = 0x802152aau; p.upperUsage.vfRead[0] = {10, 1}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {10, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p05D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05D8_0, false>(vu, c);
    }
    struct Kp0638_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f5344au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {21, 2}; p.upperUsage.vfWrite = {17, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0638_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0638_0, false>(vu, c);
    }
    struct Kp0698_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee368au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {14, 2}; p.upperUsage.vfWrite = {26, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0698_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0698_0, false>(vu, c);
    }
    struct Kp06F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aac58u; p.upperUsage.vfRead[0] = {21, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {17, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06F8_0, false>(vu, c);
    }
    struct Kp0758_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f7a2u; p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfWrite = {30, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0758_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0758_0, false>(vu, c);
    }
    struct Kp07B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x1f61abeu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B8_0, false>(vu, c);
    }
    struct Kp0818_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {14, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0818_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0818_0, false>(vu, c);
    }
    struct Kp0878_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0878_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0878_0, false>(vu, c);
    }
    struct Kp08D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10021001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08D8_0, false>(vu, c);
    }
    struct Kp0938_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0938_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0938_0, false>(vu, c);
    }
    struct Kp0998_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000803u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0998_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0998_0, false>(vu, c);
    }
    struct Kp09F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09F8_0, false>(vu, c);
    }
    struct Kp0A58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A58_0, false>(vu, c);
    }
    struct Kp0AB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x11040000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AB8_0, false>(vu, c);
    }
    struct Kp0B18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800152b5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B18_0, false>(vu, c);
    }
    struct Kp0B78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f45810u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {20, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B78_0, false>(vu, c);
    }
    struct Kp0BD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800152b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1026; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BD8_0, false>(vu, c);
    }
    struct Kp0C38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C38_0, false>(vu, c);
    }
    struct Kp0C98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f66040u; p.upper = 0x1dfc8bdu; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C98_0, false>(vu, c);
    }
    struct Kp0CF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800b5234u; p.upper = 0x3d9bc2u; p.lowerUsage.viRead = 3072; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 1}; p.upperUsage.vfRead[1] = {29, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CF8_0, false>(vu, c);
    }
    struct Kp0D58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x102e03efu; p.upper = 0x1cf99ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D58_0, false>(vu, c);
    }
    struct Kp0DB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84803a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DB8_0, false>(vu, c);
    }
    struct Kp0E18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E18_0, false>(vu, c);
    }
    struct Kp0E78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80052930u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E78_0, false>(vu, c);
    }
    struct Kp0ED8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c5af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6144; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0ED8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0ED8_0, false>(vu, c);
    }
    struct Kp0F38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e56050u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F38_0, false>(vu, c);
    }
    struct Kp0F98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F98_0, false>(vu, c);
    }
    struct Kp0FF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8027f33cu; p.upper = 0x18004e6u; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FF8_0, false>(vu, c);
    }
    struct Kp1058_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8866800u; p.upper = 0x5430bfu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1058_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1058_0, false>(vu, c);
    }
    struct Kp10B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4c30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {12, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10B8_0, false>(vu, c);
    }
    struct Kp1118_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1118_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1118_0, false>(vu, c);
    }
    struct Kp1178_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x805430bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {20, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1178_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1178_0, false>(vu, c);
    }
    struct Kp11D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p11D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11D8_0, false>(vu, c);
    }
    struct Kp1238_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1238_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1238_0, false>(vu, c);
    }
    struct Kp1298_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80050870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1298_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1298_0, false>(vu, c);
    }
    struct Kp12F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x90a6045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12F8_0, false>(vu, c);
    }
    struct Kp1358_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800066fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1358_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1358_0, false>(vu, c);
    }
    struct Kp13B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13B8_0, false>(vu, c);
    }
    struct Kp1418_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100303a2u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1418_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1418_0, false>(vu, c);
    }
    struct Kp1478_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9056801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1478_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1478_0, false>(vu, c);
    }
    struct Kp14D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000072au; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14D8_0, false>(vu, c);
    }
    struct Kp1538_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1538_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1538_0, false>(vu, c);
    }
    struct Kp1598_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80004170u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1598_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1598_0, false>(vu, c);
    }
    struct Kp15F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80053134u; p.upper = 0x2ffu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15F8_0, false>(vu, c);
    }
    struct Kp1658_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800058f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1658_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1658_0, false>(vu, c);
    }
    struct Kp16B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f56042u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16B8_0, false>(vu, c);
    }
    struct Kp1718_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80012974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1718_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1718_0, false>(vu, c);
    }
    struct Kp1778_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500f0004u; p.upper = 0x1cf11ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1778_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1778_0, false>(vu, c);
    }
    struct Kp17D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a4a75u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1536; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17D8_0, false>(vu, c);
    }
    struct Kp1838_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080020u; p.upper = 0x1cf80eeu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {16, 14}; p.upperUsage.vfRead[1] = {15, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1838_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1838_0, false>(vu, c);
    }
    struct Kp1898_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x810b7b3cu; p.upper = 0x1d189ffu; p.lowerUsage.vfRead[0] = {15, 8}; p.lowerUsage.vfWrite = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1898_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1898_0, false>(vu, c);
    }
    struct Kp18F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52060003u; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18F8_0, false>(vu, c);
    }
    struct Kp1958_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e004fu; p.upper = 0x1cd72a8u; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {13, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1958_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1958_0, false>(vu, c);
    }
    struct Kp19B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x84103a0u; p.upper = 0x22017fu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19B8_0, false>(vu, c);
    }
    struct Kp1A18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806513fcu; p.upper = 0x811043u; p.lowerUsage.vfRead[0] = {2, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 4}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A18_0, false>(vu, c);
    }
    struct Kp1A78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500c0010u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A78_0, false>(vu, c);
    }
    struct Kp1AD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52010004u; p.upper = 0x181097cu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AD8_0, false>(vu, c);
    }
    struct Kp1B38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e35801u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B38_0, false>(vu, c);
    }
    struct Kp1B98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010802u; p.upper = 0x2000ecu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B98_0, false>(vu, c);
    }
    struct Kp1BF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a1000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BF8_0, false>(vu, c);
    }
    struct Kp1C58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8215000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C58_0, false>(vu, c);
    }
    struct Kp1CB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80050874u; p.upper = 0x2ffu; p.lowerUsage.viRead = 34; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CB8_0, false>(vu, c);
    }
    struct Kp1D18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82b3800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D18_0, false>(vu, c);
    }
    struct Kp1D78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c08b5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D78_0, false>(vu, c);
    }
    struct Kp1DD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104f90au; p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD8_0, false>(vu, c);
    }
    struct Kp1E38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38010000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E38_0, false>(vu, c);
    }
    struct Kp1E98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x219bc2u; p.upperUsage.vfRead[0] = {19, 1}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E98_0, false>(vu, c);
    }
    struct Kp1EF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a0bfcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EF8_0, false>(vu, c);
    }
    struct Kp1F58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2220800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F58_0, false>(vu, c);
    }
    struct Kp1FB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fau; p.upper = 0x1c4197du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FB8_0, false>(vu, c);
    }
    struct Kp2018_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2018_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2018_0, false>(vu, c);
    }
    struct Kp2078_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c1a0adu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2078_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2078_0, false>(vu, c);
    }
    struct Kp20D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0681u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20D8_0, false>(vu, c);
    }
    struct Kp2138_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2138_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2138_0, false>(vu, c);
    }
    struct Kp2198_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4001e2u; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2198_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2198_0, false>(vu, c);
    }
    struct Kp21F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5217du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21F8_0, false>(vu, c);
    }
    struct Kp2258_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0edu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2258_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2258_0, false>(vu, c);
    }
    struct Kp22B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1803a00u; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22B8_0, false>(vu, c);
    }
    struct Kp2318_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2318_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2318_0, false>(vu, c);
    }
    struct Kp2378_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2378_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2378_0, false>(vu, c);
    }
    struct Kp23D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30073800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23D8_0, false>(vu, c);
    }
    struct Kp2438_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x13e60780u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2438_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2438_0, false>(vu, c);
    }
    struct Kp2498_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12073801u; p.upper = 0x1c1a9beu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2498_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2498_0, false>(vu, c);
    }
    struct Kp24F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1460b18u; p.upperUsage.vfRead[0] = {1, 10}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {12, 10}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24F8_0, false>(vu, c);
    }
    struct Kp2558_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb7000u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {14, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2558_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2558_0, false>(vu, c);
    }
    struct Kp25B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25B8_0, false>(vu, c);
    }
    struct Kp2618_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x200a23u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2618_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2618_0, false>(vu, c);
    }
    struct Kp2678_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5217du; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2678_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2678_0, false>(vu, c);
    }
    struct Kp26D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26D8_0, false>(vu, c);
    }
    struct Kp2738_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00222u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2738_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2738_0, false>(vu, c);
    }
    struct Kp2798_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x616015u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 3}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2798_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2798_0, false>(vu, c);
    }
    struct Kp27F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27F8_0, false>(vu, c);
    }
    struct Kp2858_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_0, false>(vu, c);
    }
    struct Kp28B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_0, false>(vu, c);
    }
    struct Kp2918_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_0, false>(vu, c);
    }
    struct Kp2978_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e048eu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2978_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_0, false>(vu, c);
    }
    struct Kp29D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D8_0, false>(vu, c);
    }
    struct Kp2A38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A38_0, false>(vu, c);
    }
    struct Kp2A98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A98_0, false>(vu, c);
    }
    struct Kp2AF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80220bfdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2AF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AF8_0, false>(vu, c);
    }
    struct Kp2B58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B58_0, false>(vu, c);
    }
    struct Kp2BB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1e2b0cau; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_0, false>(vu, c);
    }
    struct Kp2C18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7812u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_0, false>(vu, c);
    }
    struct Kp2C78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_0, false>(vu, c);
    }
    struct Kp2F08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_0, false>(vu, c);
    }
    struct Kp2F68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_0, false>(vu, c);
    }
    struct Kp2FC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_0, false>(vu, c);
    }
    struct Kp3258_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_0, false>(vu, c);
    }
    struct Kp32B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_0, false>(vu, c);
    }
    struct Kp3318_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_0, false>(vu, c);
    }
    struct Kp3378_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3378_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3378_0, false>(vu, c);
    }
    struct Kp3598_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_0, false>(vu, c);
    }
    struct Kp35F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_0, false>(vu, c);
    }
    struct Kp3658_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3658_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_0, false>(vu, c);
    }
    struct Kp36B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B8_0, false>(vu, c);
    }
    struct Kp38B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p38B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38B8_0, false>(vu, c);
    }
    struct Kp3918_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3918_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3918_0, false>(vu, c);
    }
    struct Kp3978_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3978_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3978_0, false>(vu, c);
    }
    struct Kp39D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_0, false>(vu, c);
    }
    struct Kp3A38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A38_0, false>(vu, c);
    }
    struct Kp3A98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A98_0, false>(vu, c);
    }
    struct Kp0000_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d0233u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0000_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0000_1, false>(vu, c);
    }
    struct Kp0060_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0060_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0060_1, false>(vu, c);
    }
    struct Kp00C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb613eu; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p00C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00C8_1, false>(vu, c);
    }
    struct Kp0128_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010007u; p.upper = 0x1ec617du; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0128_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0128_1, false>(vu, c);
    }
    struct Kp0188_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000806u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0188_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0188_1, false>(vu, c);
    }
    struct Kp01F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F0_1, false>(vu, c);
    }
    struct Kp0250_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e1601fu; p.upper = 0x1e000d3u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0250_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0250_1, false>(vu, c);
    }
    struct Kp02B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010010u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02B8_1, false>(vu, c);
    }
    struct Kp0318_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed697du; p.upperUsage.vfRead[0] = {13, 15}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0318_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0318_1, false>(vu, c);
    }
    struct Kp0378_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ec593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0378_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0378_1, false>(vu, c);
    }
    struct Kp03D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800217f2u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03D8_1, false>(vu, c);
    }
    struct Kp0438_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9016016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0438_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0438_1, false>(vu, c);
    }
    struct Kp0498_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800852b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1280; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0498_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0498_1, false>(vu, c);
    }
    struct Kp04F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3a95ff6cu; p.upper = 0x81e0203cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p04F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04F8_1, false>(vu, c);
    }
    struct Kp0558_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0483cu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0558_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0558_1, false>(vu, c);
    }
    struct Kp05B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff1248u; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05B8_1, false>(vu, c);
    }
    struct Kp0618_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f0000u; p.upper = 0x81ff1248u; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0618_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0618_1, false>(vu, c);
    }
    struct Kp0678_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0678_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0678_1, false>(vu, c);
    }
    struct Kp06D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1ff1a49u; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06D8_1, false>(vu, c);
    }
    struct Kp0738_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31003u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0738_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0738_1, false>(vu, c);
    }
    struct Kp0798_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1011000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0798_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0798_1, false>(vu, c);
    }
    struct Kp07F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800007bfu; p.upper = 0x2ffu; p.lowerUsage.waitP = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p07F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07F8_1, false>(vu, c);
    }
    struct Kp0858_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0858_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0858_1, false>(vu, c);
    }
    struct Kp08B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5001079eu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08B8_1, false>(vu, c);
    }
    struct Kp0918_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c51048u; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0918_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0918_1, false>(vu, c);
    }
    struct Kp0978_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31003u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0978_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0978_1, false>(vu, c);
    }
    struct Kp09D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806047beu; p.upper = 0x8842beu; p.lowerUsage.vfRead[0] = {8, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 12; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09D8_1, false>(vu, c);
    }
    struct Kp0A40_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x294a68u; p.upperUsage.vfRead[0] = {9, 1}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A40_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A40_1, false>(vu, c);
    }
    struct Kp0AA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c74a49u; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AA8_1, false>(vu, c);
    }
    struct Kp0B08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p0B08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B08_1, false>(vu, c);
    }
    struct Kp0B68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e428bcu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B68_1, false>(vu, c);
    }
    struct Kp0BC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x89414fu; p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BC8_1, false>(vu, c);
    }
    struct Kp0C28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x808529eau; p.upperUsage.vfRead[0] = {5, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0C28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C28_1, false>(vu, c);
    }
    struct Kp0C88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c749cbu; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 1}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C88_1, false>(vu, c);
    }
    struct Kp0CE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df10beu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CE8_1, false>(vu, c);
    }
    struct Kp0D48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8397cu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D48_1, false>(vu, c);
    }
    struct Kp0DA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3437du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DA8_1, false>(vu, c);
    }
    struct Kp0E08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d3ce6au; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {19, 14}; p.upperUsage.vfWrite = {25, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E08_1, false>(vu, c);
    }
    struct Kp0E68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e07f0u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E68_1, false>(vu, c);
    }
    struct Kp0EC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC8_1, false>(vu, c);
    }
    struct Kp0F28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e07d3u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F28_1, false>(vu, c);
    }
    struct Kp0F88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x456015u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {5, 2}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F88_1, false>(vu, c);
    }
    struct Kp0FE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FE8_1, false>(vu, c);
    }
    struct Kp1048_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1048_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1048_1, false>(vu, c);
    }
    struct Kp10A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1c0211cu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10A8_1, false>(vu, c);
    }
    struct Kp1108_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1108_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1108_1, false>(vu, c);
    }
    struct Kp1168_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e40222u; p.upper = 0x1e198cfu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1168_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1168_1, false>(vu, c);
    }
    struct Kp11C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb937du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {18, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11C8_1, false>(vu, c);
    }
    struct Kp1228_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x4103c0u; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {15, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1228_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1228_1, false>(vu, c);
    }
    struct Kp1288_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1288_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1288_1, false>(vu, c);
    }
    struct Kp12E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x81ef990fu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p12E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12E8_1, false>(vu, c);
    }
    struct Kp1350_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80422b3cu; p.upper = 0x23017fu; p.lowerUsage.vfRead[0] = {5, 2}; p.lowerUsage.vfWrite = {2, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1350_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1350_1, false>(vu, c);
    }
    struct Kp13B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b5809u; p.upper = 0x10798c9u; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13B0_1, false>(vu, c);
    }
    struct Kp1418_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x4103c0u; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfWrite = {15, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1418_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1418_1, false>(vu, c);
    }
    struct Kp1478_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1478_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1478_1, false>(vu, c);
    }
    struct Kp14D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14D8_1, false>(vu, c);
    }
    struct Kp1538_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1538_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1538_1, false>(vu, c);
    }
    struct Kp1598_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x81e03a7fu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1598_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1598_1, false>(vu, c);
    }
    struct Kp15F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e318aau; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15F8_1, false>(vu, c);
    }
    struct Kp1658_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80422b3cu; p.upper = 0x23017fu; p.lowerUsage.vfRead[0] = {5, 2}; p.lowerUsage.vfWrite = {2, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1658_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1658_1, false>(vu, c);
    }
    struct Kp16B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b5809u; p.upper = 0x10798c9u; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16B8_1, false>(vu, c);
    }
    struct Kp1718_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1718_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1718_1, false>(vu, c);
    }
    struct Kp1778_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1778_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1778_1, false>(vu, c);
    }
    struct Kp17D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1295bu; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17D8_1, false>(vu, c);
    }
    struct Kp1838_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c699a9u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1838_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1838_1, false>(vu, c);
    }
    struct Kp1898_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1898_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1898_1, false>(vu, c);
    }
    struct Kp18F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p18F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18F8_1, false>(vu, c);
    }
    struct Kp1958_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1958_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1958_1, false>(vu, c);
    }
    struct Kp19B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19B8_1, false>(vu, c);
    }
    struct Kp1A18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A18_1, false>(vu, c);
    }
    struct Kp1A78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A78_1, false>(vu, c);
    }
    struct Kp1AD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4c1bcu; p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AD8_1, false>(vu, c);
    }
    struct Kp1B38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x53003fu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {19, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B38_1, false>(vu, c);
    }
    struct Kp1B98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c949ffu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B98_1, false>(vu, c);
    }
    struct Kp1BF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BF8_1, false>(vu, c);
    }
    struct Kp1C58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C58_1, false>(vu, c);
    }
    struct Kp1CB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CB8_1, false>(vu, c);
    }
    struct Kp1D18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D18_1, false>(vu, c);
    }
    struct Kp1D78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1110485u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {17, 4}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1D78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D78_1, false>(vu, c);
    }
    struct Kp1DD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD8_1, false>(vu, c);
    }
    struct Kp1E38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E38_1, false>(vu, c);
    }
    struct Kp1E98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1829089u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {18, 12}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E98_1, false>(vu, c);
    }
    struct Kp1EF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e05deu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EF8_1, false>(vu, c);
    }
    struct Kp1F58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F58_1, false>(vu, c);
    }
    struct Kp1FB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FB8_1, false>(vu, c);
    }
    struct Kp2018_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2018_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2018_1, false>(vu, c);
    }
    struct Kp2078_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x8080023eu; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2078_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2078_1, false>(vu, c);
    }
    struct Kp20D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8042033du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {2, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20D8_1, false>(vu, c);
    }
    struct Kp2138_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p2138_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2138_1, false>(vu, c);
    }
    struct Kp2198_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b2ffeu; p.upper = 0x8141acu; p.lowerUsage.vfRead[0] = {5, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {6, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2198_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2198_1, false>(vu, c);
    }
    struct Kp21F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eca8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21F8_1, false>(vu, c);
    }
    struct Kp2258_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8037db3cu; p.upper = 0x1dcdabeu; p.lowerUsage.vfRead[0] = {27, 1}; p.lowerUsage.vfWrite = {23, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2258_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2258_1, false>(vu, c);
    }
    struct Kp22B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22B8_1, false>(vu, c);
    }
    struct Kp2318_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cdc8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2318_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2318_1, false>(vu, c);
    }
    struct Kp2378_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80431b3du; p.upper = 0x18de88fu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfWrite = {3, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 12}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2378_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2378_1, false>(vu, c);
    }
    struct Kp23D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x1c002c3u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {11, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23D8_1, false>(vu, c);
    }
    struct Kp2438_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2438_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2438_1, false>(vu, c);
    }
    struct Kp2498_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2498_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2498_1, false>(vu, c);
    }
    struct Kp2848_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8041043cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 2}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2848_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_1, false>(vu, c);
    }
    struct Kp28A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c938fcu; p.upperUsage.vfRead[0] = {7, 14}; p.upperUsage.vfRead[1] = {9, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_1, false>(vu, c);
    }
    struct Kp2908_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8086333du; p.upper = 0x1e6422au; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfWrite = {6, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2908_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_1, false>(vu, c);
    }
    struct Kp2968_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2968_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2968_1, false>(vu, c);
    }
    struct Kp2BC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e4217cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_1, false>(vu, c);
    }
    struct Kp2C28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1b08au; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_1, false>(vu, c);
    }
    struct Kp2C88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C88_1, false>(vu, c);
    }
    struct Kp2CE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507efu; p.upper = 0x1c1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE8_0, false>(vu, c);
    }
    struct Kp2D48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D48_0, false>(vu, c);
    }
    struct Kp2DA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2DA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2DA8_0, false>(vu, c);
    }
    struct Kp2F28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_1, false>(vu, c);
    }
    struct Kp2F88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p2F88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F88_1, false>(vu, c);
    }
    struct Kp2FE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE8_0, false>(vu, c);
    }
    struct Kp3048_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3048_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3048_0, false>(vu, c);
    }
    struct Kp30A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30A8_0, false>(vu, c);
    }
    struct Kp3230_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_1, false>(vu, c);
    }
    struct Kp3290_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_1, false>(vu, c);
    }
    struct Kp32F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_1, false>(vu, c);
    }
    struct Kp3350_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3350_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3350_1, false>(vu, c);
    }
    struct Kp33B0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33B0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33B0_0, false>(vu, c);
    }
    struct Kp3410_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3410_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3410_0, false>(vu, c);
    }
    struct Kp3590_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_1, false>(vu, c);
    }
    struct Kp35F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_1, false>(vu, c);
    }
    struct Kp3650_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3650_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_1, false>(vu, c);
    }
    struct Kp36B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B0_1, false>(vu, c);
    }
    struct Kp3730_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3730_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3730_0, false>(vu, c);
    }
    struct Kp3790_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3790_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3790_0, false>(vu, c);
    }
    struct Kp3910_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3910_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_1, false>(vu, c);
    }
    struct Kp3970_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3970_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3970_1, false>(vu, c);
    }
    struct Kp39D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p39D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_1, false>(vu, c);
    }
    struct Kp3A30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1b08au; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A30_1, false>(vu, c);
    }
    struct Kp3C30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_0, false>(vu, c);
    }
    struct Kp3C90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_0, false>(vu, c);
    }
    struct Kp3CF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_0, false>(vu, c);
    }
    struct Kp3D50_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D50_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D50_0, false>(vu, c);
    }
    struct Kp3DB0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3DB0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DB0_0, false>(vu, c);
    }
    struct Kp3E10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E10_0, false>(vu, c);
    }
    struct Kp2858_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_2, false>(vu, c);
    }
    struct Kp28B8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_2, false>(vu, c);
    }
    struct Kp2918_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507fbu; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2918_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_2, false>(vu, c);
    }
    struct Kp2BC0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_2, false>(vu, c);
    }
    struct Kp2C20_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C20_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C20_2, false>(vu, c);
    }
    struct Kp2CB0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CB0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB0_1, false>(vu, c);
    }
    struct Kp3D18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1803a00u; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_1, false>(vu, c);
    }
    struct Kp2868_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2868_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2868_3, false>(vu, c);
    }
    struct Kp28C8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e0211fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_3, false>(vu, c);
    }
    struct Kp2928_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_3, false>(vu, c);
    }
    struct Kp2988_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2988_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2988_1, false>(vu, c);
    }
    struct Kp2B98_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_3, false>(vu, c);
    }
    struct Kp2BF8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_3, false>(vu, c);
    }
    struct Kp2C58_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C58_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_2, false>(vu, c);
    }
    struct Kp2CC0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC0_2, false>(vu, c);
    }
    struct Kp2D20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D20_1, false>(vu, c);
    }
    struct Kp2F30_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F30_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_2, false>(vu, c);
    }
    struct Kp2F90_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F90_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_2, false>(vu, c);
    }
    struct Kp2FF0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FF0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_1, false>(vu, c);
    }
    struct Kp3260_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_2, false>(vu, c);
    }
    struct Kp32C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C0_2, false>(vu, c);
    }
    struct Kp3320_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3320_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_2, false>(vu, c);
    }
    struct Kp3590_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_2, false>(vu, c);
    }
    struct Kp35F0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f1u; p.upper = 0x1e2b10au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F0_2, false>(vu, c);
    }
    struct Kp3650_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3650_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3650_2, false>(vu, c);
    }
    struct Kp36B0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p36B0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B0_2, false>(vu, c);
    }
    struct Kp3920_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_2, false>(vu, c);
    }
    struct Kp3980_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3980_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3980_2, false>(vu, c);
    }
    struct Kp39E8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39E8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E8_2, false>(vu, c);
    }
    struct Kp3C58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_1, false>(vu, c);
    }
    struct Kp3CB8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e1b08au; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_2, false>(vu, c);
    }
    struct Kp3D50_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3D50_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D50_1, false>(vu, c);
    }
    struct Kp2898_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_4, false>(vu, c);
    }
    struct Kp28F8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_4, false>(vu, c);
    }
    struct Kp2958_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2958_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_3, false>(vu, c);
    }
    struct Kp29B8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29B8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B8_2, false>(vu, c);
    }
    struct Kp2A18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e039dfu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A18_1, false>(vu, c);
    }
    struct Kp2C60_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C60_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C60_3, false>(vu, c);
    }
    struct Kp2EE0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_3, false>(vu, c);
    }
    struct Kp2F40_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F40_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F40_3, false>(vu, c);
    }
    struct Kp2FA0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x42093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_3, false>(vu, c);
    }
    struct Kp3000_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3000_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3000_2, false>(vu, c);
    }
    struct Kp3278_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3278_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3278_3, false>(vu, c);
    }
    struct Kp3308_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_3, false>(vu, c);
    }
    struct Kp3910_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_3, false>(vu, c);
    }
    struct Kp3970_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3970_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3970_3, false>(vu, c);
    }
    struct Kp39D0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x1c3193fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D0_3, false>(vu, c);
    }
    struct Kp3C78_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_2, false>(vu, c);
    }
    struct Kp3CD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_1, false>(vu, c);
    }
    struct Kp3D38_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D38_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_3, false>(vu, c);
    }
    struct Kp2838_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2838_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2838_4, false>(vu, c);
    }
    struct Kp2898_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_5, false>(vu, c);
    }
    struct Kp28F8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28F8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_5, false>(vu, c);
    }
    struct Kp2BA8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_4, false>(vu, c);
    }
    struct Kp3630_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3630_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_3, false>(vu, c);
    }
    struct Kp3690_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p3690_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_3, false>(vu, c);
    }
    struct Kp3908_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3908_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3908_4, false>(vu, c);
    }
    struct Kp3968_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3968_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_4, false>(vu, c);
    }
    struct Kp3C48_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1e2b0cau; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_3, false>(vu, c);
    }
    struct Kp3CA8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7812u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CA8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_3, false>(vu, c);
    }
    struct Kp3D08_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D08_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_4, false>(vu, c);
    }
    struct Kp2930_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_6, false>(vu, c);
    }
    struct Kp2BD8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_5, false>(vu, c);
    }
    struct Kp2C38_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C38_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C38_3, false>(vu, c);
    }
    struct Kp2EE8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_4, false>(vu, c);
    }
    struct Kp2F48_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_4, false>(vu, c);
    }
    struct Kp2FD8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_4, false>(vu, c);
    }
    struct Kp3038_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507efu; p.upper = 0x1c1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3038_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3038_1, false>(vu, c);
    }
    struct Kp3270_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_4, false>(vu, c);
    }
    struct Kp32D0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32D0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_3, false>(vu, c);
    }
    struct Kp3330_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3330_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3330_3, false>(vu, c);
    }
    struct Kp3390_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3390_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3390_2, false>(vu, c);
    }
    struct Kp35A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A8_3, false>(vu, c);
    }
    struct Kp3608_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3608_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_3, false>(vu, c);
    }
    struct Kp3668_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_4, false>(vu, c);
    }
    struct Kp36D0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D0_2, false>(vu, c);
    }
    struct Kp39A8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_5, false>(vu, c);
    }
    struct Kp3CE0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x42093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfWrite = {2, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_4, false>(vu, c);
    }
    struct Kp2920_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_7, false>(vu, c);
    }
    struct Kp2C58_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C58_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_4, false>(vu, c);
    }
    struct Kp2FC8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_5, false>(vu, c);
    }
    struct Kp3578_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3578_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3578_3, false>(vu, c);
    }
    struct Kp35D8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_4, false>(vu, c);
    }
    struct Kp3638_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3638_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_5, false>(vu, c);
    }
    struct Kp38E8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_5, false>(vu, c);
    }
    struct Kp3948_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_5, false>(vu, c);
    }
    struct Kp39A8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39A8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A8_6, false>(vu, c);
    }
    struct Kp3A08_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A08_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A08_2, false>(vu, c);
    }
    struct Kp3C40_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C40_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C40_4, false>(vu, c);
    }
    struct Kp3CA0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_4, false>(vu, c);
    }
    struct Kp3D00_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c11004u; p.upper = 0x1e0783cu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D00_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D00_6, false>(vu, c);
    }
    struct Kp3D68_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D68_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D68_2, false>(vu, c);
    }
    struct Kp2850_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_6, false>(vu, c);
    }
    struct Kp28B0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_6, false>(vu, c);
    }
    struct Kp2948_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_5, false>(vu, c);
    }
    struct Kp29A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A8_3, false>(vu, c);
    }
    struct Kp2BE0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_6, false>(vu, c);
    }
    struct Kp2C40_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C40_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C40_5, false>(vu, c);
    }
    struct Kp2CA0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0e90bu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CA0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_4, false>(vu, c);
    }
    struct Kp2D00_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507eeu; p.upper = 0x1eb192bu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D00_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D00_2, false>(vu, c);
    }
    struct Kp2F38_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_5, false>(vu, c);
    }
    struct Kp2F98_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F98_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_4, false>(vu, c);
    }
    struct Kp3000_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3000_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3000_4, false>(vu, c);
    }
    struct Kp3060_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3060_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3060_1, false>(vu, c);
    }
    struct Kp3980_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3980_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3980_5, false>(vu, c);
    }
    struct Kp3C28_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_5, false>(vu, c);
    }
    struct Kp3C88_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C88_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_5, false>(vu, c);
    }
    struct Kp3CE8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CE8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_5, false>(vu, c);
    }
    struct Kp3250_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_5, false>(vu, c);
    }
    struct Kp32B0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7814u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32B0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_5, false>(vu, c);
    }
    struct Kp3310_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_6, false>(vu, c);
    }
    struct Kp35C0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_6, false>(vu, c);
    }
    struct Kp3658_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_7, false>(vu, c);
    }
    struct Kp2FC0_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC0_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC0_7, false>(vu, c);
    }
    struct Kp3330_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3330_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3330_6, false>(vu, c);
    }
    struct Kp0210_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8048033du; p.upper = 0x2041ecu; p.lowerUsage.vfRead[0] = {0, 15}; p.lowerUsage.vfWrite = {8, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {8, 1}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0210_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0210_2d, true>(vu, c);
    }
    struct Kp0460_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b1feu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0460_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0460_2d, true>(vu, c);
    }
    struct Kp05A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2bef46u; p.upperUsage.vfRead[0] = {29, 1}; p.upperUsage.vfRead[1] = {11, 2}; p.upperUsage.vfWrite = {29, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p05A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05A8_2d, true>(vu, c);
    }
    struct Kp0658_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {12, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0658_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0658_2d, true>(vu, c);
    }
    struct Kp0778_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x43099bu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0778_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0778_2d, true>(vu, c);
    }
    struct Kp07F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec130eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07F8_2d, true>(vu, c);
    }
    struct Kp0CB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8077b33cu; p.upper = 0x197b7eau; p.lowerUsage.vfRead[0] = {22, 3}; p.lowerUsage.vfWrite = {23, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {31, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB0_2d, true>(vu, c);
    }
    struct Kp0F00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b1feu; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F00_2d, true>(vu, c);
    }
    struct Kp0FB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed364au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {13, 2}; p.upperUsage.vfWrite = {25, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FB8_2d, true>(vu, c);
    }
    struct Kp1070_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5530bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1070_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1070_2d, true>(vu, c);
    }
    struct Kp1160_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x43099bu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 2}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {6, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1160_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1160_2d, true>(vu, c);
    }
    struct Kp16D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8077b33cu; p.upper = 0x197b06au; p.lowerUsage.vfRead[0] = {22, 3}; p.lowerUsage.vfWrite = {23, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {22, 12}; p.upperUsage.vfRead[1] = {23, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16D8_2d, true>(vu, c);
    }
    struct Kp1908_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2018e2u; p.upperUsage.vfRead[0] = {3, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1908_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1908_2d, true>(vu, c);
    }
    struct Kp1AB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9063045u; p.upper = 0x1801a3fu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB0_2d, true>(vu, c);
    }
    struct Kp1DD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104203du; p.upperUsage.vfRead[0] = {4, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD0_2d, true>(vu, c);
    }
    struct Kp2110_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e703bcu; p.upper = 0x1803a00u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {7, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2110_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2110_2d, true>(vu, c);
    }
    struct Kp22D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a0edu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22D0_2d, true>(vu, c);
    }
    struct Kp2450_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4001e2u; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2450_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2450_2d, true>(vu, c);
    }
    struct Kp2508_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5428au; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfWrite = {10, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2508_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2508_1d, true>(vu, c);
    }
    struct Kp2858_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_7d, true>(vu, c);
    }
    struct Kp2AA8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AA8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AA8_1d, true>(vu, c);
    }
    struct Kp2EE0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE0_6d, true>(vu, c);
    }
    struct Kp3270_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_7d, true>(vu, c);
    }
    struct Kp3358_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3358_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_4d, true>(vu, c);
    }
    struct Kp35E8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_6d, true>(vu, c);
    }
    struct Kp36D0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p36D0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D0_3d, true>(vu, c);
    }
    struct Kp3940_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_6d, true>(vu, c);
    }
    struct Kp3A28_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A28_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A28_3d, true>(vu, c);
    }
    struct Kp3AA0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3AA0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AA0_1d, true>(vu, c);
    }
    struct Kp04E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e02122u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E0_2d, true>(vu, c);
    }
    struct Kp07B0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e70800u; p.upper = 0x103092cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 8}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfWrite = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07B0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B0_3d, true>(vu, c);
    }
    struct Kp0910_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0083cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0910_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0910_2d, true>(vu, c);
    }
    struct Kp09A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x6349dau; p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {7, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09A8_2d, true>(vu, c);
    }
    struct Kp0A80_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x808529eau; p.upperUsage.vfRead[0] = {5, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0A80_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A80_2d, true>(vu, c);
    }
    struct Kp0AE0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80290b3cu; p.upper = 0x1c90abcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AE0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AE0_2d, true>(vu, c);
    }
    struct Kp0BB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8029067cu; p.upper = 0x1c001a0u; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BB8_2d, true>(vu, c);
    }
    struct Kp0C50_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2739eau; p.upperUsage.vfRead[0] = {7, 1}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C50_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C50_2d, true>(vu, c);
    }
    struct Kp0CB8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CB8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CB8_3d, true>(vu, c);
    }
    struct Kp0E00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x39ce46u; p.upperUsage.vfRead[0] = {25, 3}; p.upperUsage.vfWrite = {25, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0E00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E00_2d, true>(vu, c);
    }
    struct Kp0FD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0cau; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD0_2d, true>(vu, c);
    }
    struct Kp1048_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1048_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1048_2d, true>(vu, c);
    }
    struct Kp11F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x40003fu; p.upperUsage.vfRead[0] = {0, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11F0_2d, true>(vu, c);
    }
    struct Kp12E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x81ef990fu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p12E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12E8_2d, true>(vu, c);
    }
    struct Kp13A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b2005u; p.upper = 0x8798ccu; p.lowerUsage.vfRead[0] = {4, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13A8_2d, true>(vu, c);
    }
    struct Kp14D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14D8_2d, true>(vu, c);
    }
    struct Kp1598_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x81e03a7fu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1598_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1598_2d, true>(vu, c);
    }
    struct Kp1600_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e332bdu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1600_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1600_2d, true>(vu, c);
    }
    struct Kp1678_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b8801u; p.upper = 0x8798c8u; p.lowerUsage.vfRead[0] = {17, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 4}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfWrite = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1678_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1678_2d, true>(vu, c);
    }
    struct Kp1798_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2d10au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1798_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1798_2d, true>(vu, c);
    }
    struct Kp1810_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2a08u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {8, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1810_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1810_2d, true>(vu, c);
    }
    struct Kp18F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {6, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18F0_2d, true>(vu, c);
    }
    struct Kp1AA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AA0_2d, true>(vu, c);
    }
    struct Kp1B00_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2988u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B00_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B00_2d, true>(vu, c);
    }
    struct Kp1B60_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x28020eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B60_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B60_3d, true>(vu, c);
    }
    struct Kp1CC8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1CC8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CC8_2d, true>(vu, c);
    }
    struct Kp1DE8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x81e1990fu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1DE8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DE8_3d, true>(vu, c);
    }
    struct Kp1E98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1829089u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {18, 12}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E98_2d, true>(vu, c);
    }
    struct Kp2010_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x800062u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfWrite = {1, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2010_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2010_2d, true>(vu, c);
    }
    struct Kp2148_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e14128u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2148_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2148_2d, true>(vu, c);
    }
    struct Kp21E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ebb2cau; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {11, 2}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21E8_2d, true>(vu, c);
    }
    struct Kp2318_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cdc8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2318_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2318_2d, true>(vu, c);
    }
    struct Kp2410_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b400000u; p.upper = 0x81e00a3eu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2410_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2410_2d, true>(vu, c);
    }
    struct Kp2480_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eda6de1u; p.upper = 0x81e03a3fu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2480_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2480_2d, true>(vu, c);
    }
    struct Kp2860_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8065a3fcu; p.upper = 0x1d139dbu; p.lowerUsage.vfRead[0] = {20, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 14}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {7, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_8d, true>(vu, c);
    }
    struct Kp28D8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81284b3cu; p.upper = 0x1e1c8bdu; p.lowerUsage.vfRead[0] = {9, 9}; p.lowerUsage.vfWrite = {8, 9}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_8d, true>(vu, c);
    }
    struct Kp2C78_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_8d, true>(vu, c);
    }
    struct Kp2D40_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D40_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D40_1d, true>(vu, c);
    }
    struct Kp2F38_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_6d, true>(vu, c);
    }
    struct Kp3020_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3020_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3020_3d, true>(vu, c);
    }
    struct Kp3248_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_7d, true>(vu, c);
    }
    struct Kp32B0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_6d, true>(vu, c);
    }
    struct Kp3398_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3398_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3398_3d, true>(vu, c);
    }
    struct Kp3418_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3418_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3418_1d, true>(vu, c);
    }
    struct Kp3718_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3718_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3718_1d, true>(vu, c);
    }
    struct Kp3988_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3988_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_7d, true>(vu, c);
    }
    struct Kp3DC0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DC0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DC0_1d, true>(vu, c);
    }
    struct Kp2BA0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_9d, true>(vu, c);
    }
    struct Kp2840_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_7d, true>(vu, c);
    }
    struct Kp2928_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_9d, true>(vu, c);
    }
    struct Kp2BB0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_8d, true>(vu, c);
    }
    struct Kp2C18_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C18_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_6d, true>(vu, c);
    }
    struct Kp2D08_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D08_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D08_2d, true>(vu, c);
    }
    struct Kp2FC8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_9d, true>(vu, c);
    }
    struct Kp3640_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3640_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_7d, true>(vu, c);
    }
    struct Kp3978_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3978_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3978_5d, true>(vu, c);
    }
    struct Kp3C60_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62969u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C60_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C60_7d, true>(vu, c);
    }
    struct Kp3D48_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D48_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D48_4d, true>(vu, c);
    }
    struct Kp28A8_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_10d, true>(vu, c);
    }
    struct Kp2990_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2990_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2990_5d, true>(vu, c);
    }
    struct Kp29F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29F8_2d, true>(vu, c);
    }
    struct Kp2F98_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F98_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F98_6d, true>(vu, c);
    }
    struct Kp38E8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_8d, true>(vu, c);
    }
    struct Kp3C38_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_8d, true>(vu, c);
    }
    struct Kp3D18_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D18_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_6d, true>(vu, c);
    }
    struct Kp2860_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2860_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2860_11d, true>(vu, c);
    }
    struct Kp2BE8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_9d, true>(vu, c);
    }
    struct Kp3C30_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_8d, true>(vu, c);
    }
    struct Kp2BB0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_9d, true>(vu, c);
    }
    struct Kp2F38_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_8d, true>(vu, c);
    }
    struct Kp3230_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_7d, true>(vu, c);
    }
    struct Kp3318_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_9d, true>(vu, c);
    }
    struct Kp35A0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_8d, true>(vu, c);
    }
    struct Kp3608_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3608_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3608_6d, true>(vu, c);
    }
    struct Kp36F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F8_2d, true>(vu, c);
    }
    struct Kp2930_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2930_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2930_9d, true>(vu, c);
    }
    struct Kp3628_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3628_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_5d, true>(vu, c);
    }
    struct Kp3940_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3940_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3940_8d, true>(vu, c);
    }
    struct Kp3C28_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_8d, true>(vu, c);
    }
    struct Kp3C98_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_7d, true>(vu, c);
    }
    struct Kp3D80_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D80_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D80_3d, true>(vu, c);
    }
    struct Kp2888_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_9d, true>(vu, c);
    }
    struct Kp2970_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2970_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2970_5d, true>(vu, c);
    }
    struct Kp2C00_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_9d, true>(vu, c);
    }
    struct Kp2EE8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_9d, true>(vu, c);
    }
    struct Kp2F58_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F58_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_7d, true>(vu, c);
    }
    struct Kp3040_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3040_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3040_3d, true>(vu, c);
    }
    struct Kp3C28_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_9d, true>(vu, c);
    }
    struct Kp32E0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e1a8bdu; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E0_6d, true>(vu, c);
    }
    struct Kp3668_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_10d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
