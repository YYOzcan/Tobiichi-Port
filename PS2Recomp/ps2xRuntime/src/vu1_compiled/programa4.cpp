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
    struct Kp0018_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010155u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0018_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0018_0, false>(vu, c);
    }
    struct Kp0078_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48002000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0078_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0078_0, false>(vu, c);
    }
    struct Kp00D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10070001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00D8_0, false>(vu, c);
    }
    struct Kp0138_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f45810u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {20, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0138_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0138_0, false>(vu, c);
    }
    struct Kp0198_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x201000u; p.upperUsage.vfRead[0] = {2, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0198_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0198_0, false>(vu, c);
    }
    struct Kp01F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3a000800u; p.upper = 0x81c2b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p01F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F8_0, false>(vu, c);
    }
    struct Kp0258_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x182007eu; p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0258_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0258_0, false>(vu, c);
    }
    struct Kp02B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010009u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02B8_0, false>(vu, c);
    }
    struct Kp0318_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0318_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0318_0, false>(vu, c);
    }
    struct Kp0378_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000009bu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0378_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0378_0, false>(vu, c);
    }
    struct Kp03D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80052930u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03D8_0, false>(vu, c);
    }
    struct Kp0438_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c5af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6144; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0438_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0438_0, false>(vu, c);
    }
    struct Kp0498_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ff604du; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {31, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0498_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0498_0, false>(vu, c);
    }
    struct Kp04F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fb6049u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {27, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04F8_0, false>(vu, c);
    }
    struct Kp0558_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80640b3du; p.upper = 0x260181u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfWrite = {4, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0558_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0558_0, false>(vu, c);
    }
    struct Kp05B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05B8_0, false>(vu, c);
    }
    struct Kp0618_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec2850u; p.upper = 0x1f428bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {20, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0618_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0618_0, false>(vu, c);
    }
    struct Kp0678_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {13, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0678_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0678_0, false>(vu, c);
    }
    struct Kp06D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbf000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p06D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06D8_0, false>(vu, c);
    }
    struct Kp0738_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b000001u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p0738_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0738_0, false>(vu, c);
    }
    struct Kp0798_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec3054u; p.upper = 0x1f4150eu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0798_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0798_0, false>(vu, c);
    }
    struct Kp07F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec130eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {12, 2}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07F8_0, false>(vu, c);
    }
    struct Kp0858_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb0803a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0858_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0858_0, false>(vu, c);
    }
    struct Kp08B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800130f4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 66; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08B8_0, false>(vu, c);
    }
    struct Kp0918_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0918_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0918_0, false>(vu, c);
    }
    struct Kp0978_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d0155u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0978_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0978_0, false>(vu, c);
    }
    struct Kp09D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09D8_0, false>(vu, c);
    }
    struct Kp0A38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8216045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A38_0, false>(vu, c);
    }
    struct Kp0A98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8826800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A98_0, false>(vu, c);
    }
    struct Kp0AF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520107fau; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AF8_0, false>(vu, c);
    }
    struct Kp0B58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x88903a1u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B58_0, false>(vu, c);
    }
    struct Kp0BB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520106f9u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BB8_0, false>(vu, c);
    }
    struct Kp0C18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C18_0, false>(vu, c);
    }
    struct Kp0C78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f91811u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {25, 15}; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C78_0, false>(vu, c);
    }
    struct Kp0CD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82117ffu; p.upper = 0x1e08440u; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {17, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD8_0, false>(vu, c);
    }
    struct Kp0D38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a9bfcu; p.upper = 0x1c0d83cu; p.lowerUsage.vfRead[0] = {19, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D38_0, false>(vu, c);
    }
    struct Kp0D98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5208000bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D98_0, false>(vu, c);
    }
    struct Kp0DF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DF8_0, false>(vu, c);
    }
    struct Kp0E58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f75813u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {23, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E58_0, false>(vu, c);
    }
    struct Kp0EB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00300cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 64; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EB8_0, false>(vu, c);
    }
    struct Kp0F18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e07be7u; p.upperUsage.vfRead[0] = {15, 15}; p.upperUsage.vfWrite = {15, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F18_0, false>(vu, c);
    }
    struct Kp0F78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f621bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {22, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F78_0, false>(vu, c);
    }
    struct Kp0FD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e00080au; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0FD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD8_0, false>(vu, c);
    }
    struct Kp1038_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e36053u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1038_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1038_0, false>(vu, c);
    }
    struct Kp1098_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f71abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1098_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1098_0, false>(vu, c);
    }
    struct Kp10F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {15, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10F8_0, false>(vu, c);
    }
    struct Kp1158_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c26042u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 14}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1158_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1158_0, false>(vu, c);
    }
    struct Kp11B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f71abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11B8_0, false>(vu, c);
    }
    struct Kp1218_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50050003u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1218_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1218_0, false>(vu, c);
    }
    struct Kp1278_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9017000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1278_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1278_0, false>(vu, c);
    }
    struct Kp12D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050079u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D8_0, false>(vu, c);
    }
    struct Kp1338_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1338_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1338_0, false>(vu, c);
    }
    struct Kp1398_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50070002u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1398_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1398_0, false>(vu, c);
    }
    struct Kp13F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80042130u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F8_0, false>(vu, c);
    }
    struct Kp1458_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58004fcau; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1458_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1458_0, false>(vu, c);
    }
    struct Kp14B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B8_0, false>(vu, c);
    }
    struct Kp1518_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1518_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1518_0, false>(vu, c);
    }
    struct Kp1578_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50080004u; p.upper = 0x2ffu; p.lowerUsage.viRead = 256; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1578_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1578_0, false>(vu, c);
    }
    struct Kp15D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p15D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D8_0, false>(vu, c);
    }
    struct Kp1638_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4000078eu; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1638_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1638_0, false>(vu, c);
    }
    struct Kp1698_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb016000u; p.upper = 0x400002ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.eBit = true; p.upperNop = true; return p; }();
    };
    bool p1698_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1698_0, false>(vu, c);
    }
    struct Kp16F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d03c7u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16F8_0, false>(vu, c);
    }
    struct Kp1758_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800052f0u; p.upper = 0x1d608a9u; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {22, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1758_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1758_0, false>(vu, c);
    }
    struct Kp17B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x380a0000u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17B8_0, false>(vu, c);
    }
    struct Kp1818_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d0886eu; p.upperUsage.vfRead[0] = {17, 14}; p.upperUsage.vfRead[1] = {16, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1818_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1818_0, false>(vu, c);
    }
    struct Kp1878_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb0203a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1878_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1878_0, false>(vu, c);
    }
    struct Kp18D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x818303fdu; p.upper = 0x22313cu; p.lowerUsage.vfWrite = {3, 12}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {6, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18D8_0, false>(vu, c);
    }
    struct Kp1938_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81ec137du; p.upper = 0x510387u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {17, 1}; p.upperUsage.vfWrite = {14, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1938_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1938_0, false>(vu, c);
    }
    struct Kp1998_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0047u; p.upper = 0x1cc72a8u; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {12, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1998_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1998_0, false>(vu, c);
    }
    struct Kp19F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800d0b71u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19F8_0, false>(vu, c);
    }
    struct Kp1A58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3cd0800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A58_0, false>(vu, c);
    }
    struct Kp1AB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010300u; p.upper = 0x1802063u; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB8_0, false>(vu, c);
    }
    struct Kp1B18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B18_0, false>(vu, c);
    }
    struct Kp1B78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10052801u; p.upper = 0x1e180bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B78_0, false>(vu, c);
    }
    struct Kp1BD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80062974u; p.upper = 0x2ffu; p.lowerUsage.viRead = 96; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BD8_0, false>(vu, c);
    }
    struct Kp1C38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a5000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C38_0, false>(vu, c);
    }
    struct Kp1C98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800019f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C98_0, false>(vu, c);
    }
    struct Kp1CF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x82a5000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CF8_0, false>(vu, c);
    }
    struct Kp1D58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0008u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D58_0, false>(vu, c);
    }
    struct Kp1DB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2096cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB8_0, false>(vu, c);
    }
    struct Kp1E18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c001ffu; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E18_0, false>(vu, c);
    }
    struct Kp1E78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e08440u; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {17, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E78_0, false>(vu, c);
    }
    struct Kp1ED8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000006u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1ED8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1ED8_0, false>(vu, c);
    }
    struct Kp1F38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F38_0, false>(vu, c);
    }
    struct Kp1F98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1c1a0adu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F98_0, false>(vu, c);
    }
    struct Kp1FF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7317cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FF8_0, false>(vu, c);
    }
    struct Kp2058_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2058_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2058_0, false>(vu, c);
    }
    struct Kp20B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20B8_0, false>(vu, c);
    }
    struct Kp2118_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e34801u; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {9, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2118_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2118_0, false>(vu, c);
    }
    struct Kp2178_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2178_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2178_0, false>(vu, c);
    }
    struct Kp21D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D8_0, false>(vu, c);
    }
    struct Kp2238_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2238_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2238_0, false>(vu, c);
    }
    struct Kp2298_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2298_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2298_0, false>(vu, c);
    }
    struct Kp22F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x1c0425cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22F8_0, false>(vu, c);
    }
    struct Kp2358_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x816103bcu; p.upper = 0x56003fu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 2}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2358_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2358_0, false>(vu, c);
    }
    struct Kp23B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800639f4u; p.upper = 0x11be00du; p.lowerUsage.viRead = 192; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {28, 8}; p.upperUsage.vfRead[1] = {27, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23B8_0, false>(vu, c);
    }
    struct Kp2418_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2418_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2418_0, false>(vu, c);
    }
    struct Kp2478_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2478_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2478_0, false>(vu, c);
    }
    struct Kp24D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81012b3du; p.upper = 0x4501c5u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24D8_0, false>(vu, c);
    }
    struct Kp2538_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0790u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2538_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2538_0, false>(vu, c);
    }
    struct Kp2598_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80006efcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2598_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2598_0, false>(vu, c);
    }
    struct Kp25F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10021001u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25F8_0, false>(vu, c);
    }
    struct Kp2658_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1608au; p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2658_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2658_0, false>(vu, c);
    }
    struct Kp26B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26B8_0, false>(vu, c);
    }
    struct Kp2718_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee0800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2718_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2718_0, false>(vu, c);
    }
    struct Kp2778_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb737du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {14, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2778_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2778_0, false>(vu, c);
    }
    struct Kp27D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20085eu; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p27D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27D8_0, false>(vu, c);
    }
    struct Kp2838_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2838_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2838_0, false>(vu, c);
    }
    struct Kp2898_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_0, false>(vu, c);
    }
    struct Kp28F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781bu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_0, false>(vu, c);
    }
    struct Kp2958_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f7u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2958_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_0, false>(vu, c);
    }
    struct Kp29B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29B8_0, false>(vu, c);
    }
    struct Kp2A18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80220bfdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A18_0, false>(vu, c);
    }
    struct Kp2A78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00800u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A78_0, false>(vu, c);
    }
    struct Kp2AD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2AD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AD8_0, false>(vu, c);
    }
    struct Kp2B38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B38_0, false>(vu, c);
    }
    struct Kp2B98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_0, false>(vu, c);
    }
    struct Kp2BF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_0, false>(vu, c);
    }
    struct Kp2C58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C58_0, false>(vu, c);
    }
    struct Kp2EE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_0, false>(vu, c);
    }
    struct Kp2F48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_0, false>(vu, c);
    }
    struct Kp2FA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA8_0, false>(vu, c);
    }
    struct Kp3238_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_0, false>(vu, c);
    }
    struct Kp3298_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3298_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3298_0, false>(vu, c);
    }
    struct Kp32F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F8_0, false>(vu, c);
    }
    struct Kp3358_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3358_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3358_0, false>(vu, c);
    }
    struct Kp3578_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3578_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3578_0, false>(vu, c);
    }
    struct Kp35D8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_0, false>(vu, c);
    }
    struct Kp3638_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3638_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3638_0, false>(vu, c);
    }
    struct Kp3698_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3698_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3698_0, false>(vu, c);
    }
    struct Kp36F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c1a8bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F8_0, false>(vu, c);
    }
    struct Kp38F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1a8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_0, false>(vu, c);
    }
    struct Kp3958_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3958_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_0, false>(vu, c);
    }
    struct Kp39B8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e2u; p.upper = 0x1e160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_0, false>(vu, c);
    }
    struct Kp3A18_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A18_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A18_0, false>(vu, c);
    }
    struct Kp3A78_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A78_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A78_0, false>(vu, c);
    }
    struct Kp3AD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3AD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AD8_0, false>(vu, c);
    }
    struct Kp0040_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c52b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 5120; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0040_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0040_1, false>(vu, c);
    }
    struct Kp00A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000806u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00A8_1, false>(vu, c);
    }
    struct Kp0108_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ec593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0108_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0108_1, false>(vu, c);
    }
    struct Kp0168_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb6019u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0168_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0168_1, false>(vu, c);
    }
    struct Kp01D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f4u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01D0_1, false>(vu, c);
    }
    struct Kp0230_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0052u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0230_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0230_1, false>(vu, c);
    }
    struct Kp0290_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f000000u; p.upper = 0x80bfffeau; p.upperUsage.vfRead[0] = {31, 5}; p.upperUsage.vfWrite = {31, 5}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0290_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0290_1, false>(vu, c);
    }
    struct Kp02F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800263fcu; p.upper = 0x1ed613eu; p.lowerUsage.vfRead[0] = {12, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {13, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p02F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02F8_1, false>(vu, c);
    }
    struct Kp0358_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f2u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0358_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0358_1, false>(vu, c);
    }
    struct Kp03B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb5b3du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03B8_1, false>(vu, c);
    }
    struct Kp0418_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eb597du; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0418_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0418_1, false>(vu, c);
    }
    struct Kp0478_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb053800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 160; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0478_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0478_1, false>(vu, c);
    }
    struct Kp04D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3137cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.viLatency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04D8_1, false>(vu, c);
    }
    struct Kp0538_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0538_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0538_1, false>(vu, c);
    }
    struct Kp0598_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0598_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0598_1, false>(vu, c);
    }
    struct Kp05F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05F8_1, false>(vu, c);
    }
    struct Kp0658_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1ff1208u; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0658_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0658_1, false>(vu, c);
    }
    struct Kp06B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff10beu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {31, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B8_1, false>(vu, c);
    }
    struct Kp0718_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x1e04a5fu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0718_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0718_1, false>(vu, c);
    }
    struct Kp0778_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800113fcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0778_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0778_1, false>(vu, c);
    }
    struct Kp07D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p07D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07D8_1, false>(vu, c);
    }
    struct Kp0838_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e62a4bu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {6, 1}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0838_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0838_1, false>(vu, c);
    }
    struct Kp0898_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18430bdu; p.upperUsage.vfRead[0] = {6, 12}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0898_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0898_1, false>(vu, c);
    }
    struct Kp08F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x34010800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08F8_1, false>(vu, c);
    }
    struct Kp0958_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0958_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0958_1, false>(vu, c);
    }
    struct Kp09B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xe002fcu; p.upperUsage.vfRead[0] = {0, 7}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 7; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09B8_1, false>(vu, c);
    }
    struct Kp0A20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x89414fu; p.upperUsage.vfRead[0] = {8, 4}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A20_1, false>(vu, c);
    }
    struct Kp0A88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8039deu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A88_1, false>(vu, c);
    }
    struct Kp0AE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df10bcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AE8_1, false>(vu, c);
    }
    struct Kp0B48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81060b3du; p.upper = 0x634958u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfWrite = {6, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfWrite = {5, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B48_1, false>(vu, c);
    }
    struct Kp0BA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BA8_1, false>(vu, c);
    }
    struct Kp0C08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50050011u; p.upper = 0x850140u; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C08_1, false>(vu, c);
    }
    struct Kp0C68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8225bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C68_1, false>(vu, c);
    }
    struct Kp0CC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c90abcu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CC8_1, false>(vu, c);
    }
    struct Kp0D28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e7493cu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D28_1, false>(vu, c);
    }
    struct Kp0D88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e91000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0D88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D88_1, false>(vu, c);
    }
    struct Kp0DE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fb6003u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {27, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DE8_1, false>(vu, c);
    }
    struct Kp0E48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E48_1, false>(vu, c);
    }
    struct Kp0EA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb837du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {16, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0EA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EA8_1, false>(vu, c);
    }
    struct Kp0F08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F08_1, false>(vu, c);
    }
    struct Kp0F68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F68_1, false>(vu, c);
    }
    struct Kp0FC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC8_1, false>(vu, c);
    }
    struct Kp1028_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e519bfu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1028_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1028_1, false>(vu, c);
    }
    struct Kp1088_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802403fdu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1088_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1088_1, false>(vu, c);
    }
    struct Kp10E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10E8_1, false>(vu, c);
    }
    struct Kp1148_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1148_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1148_1, false>(vu, c);
    }
    struct Kp11A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x1c0109cu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A8_1, false>(vu, c);
    }
    struct Kp1208_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x99cbc4u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1208_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1208_1, false>(vu, c);
    }
    struct Kp1268_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1268_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1268_1, false>(vu, c);
    }
    struct Kp12C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C8_1, false>(vu, c);
    }
    struct Kp1330_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5201074fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1330_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1330_1, false>(vu, c);
    }
    struct Kp1390_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1390_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1390_1, false>(vu, c);
    }
    struct Kp13F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x99cbc4u; p.upperUsage.vfRead[0] = {25, 12}; p.upperUsage.vfWrite = {15, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13F8_1, false>(vu, c);
    }
    struct Kp1458_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1458_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1458_1, false>(vu, c);
    }
    struct Kp14B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B8_1, false>(vu, c);
    }
    struct Kp1518_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e6317cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1518_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1518_1, false>(vu, c);
    }
    struct Kp1578_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e00093u; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1578_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1578_1, false>(vu, c);
    }
    struct Kp15D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e210eau; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15D8_1, false>(vu, c);
    }
    struct Kp1638_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x10740c5u; p.upperUsage.vfRead[0] = {8, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1638_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1638_1, false>(vu, c);
    }
    struct Kp1698_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802203fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1698_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1698_1, false>(vu, c);
    }
    struct Kp16F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f36006u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {19, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16F8_1, false>(vu, c);
    }
    struct Kp1758_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e10223u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1758_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1758_1, false>(vu, c);
    }
    struct Kp17B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800007bfu; p.upper = 0x2ffu; p.lowerUsage.waitP = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p17B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17B8_1, false>(vu, c);
    }
    struct Kp1818_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf2a48u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1818_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1818_1, false>(vu, c);
    }
    struct Kp1878_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c739ffu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1878_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1878_1, false>(vu, c);
    }
    struct Kp18D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x22017fu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18D8_1, false>(vu, c);
    }
    struct Kp1938_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1938_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1938_1, false>(vu, c);
    }
    struct Kp1998_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1998_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1998_1, false>(vu, c);
    }
    struct Kp19F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0679u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19F8_1, false>(vu, c);
    }
    struct Kp1A58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A58_1, false>(vu, c);
    }
    struct Kp1AB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1211bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AB8_1, false>(vu, c);
    }
    struct Kp1B18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf20bdu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {15, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B18_1, false>(vu, c);
    }
    struct Kp1B78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c99a69u; p.upperUsage.vfRead[0] = {19, 14}; p.upperUsage.vfRead[1] = {9, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B78_1, false>(vu, c);
    }
    struct Kp1BD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1097cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BD8_1, false>(vu, c);
    }
    struct Kp1C38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e7e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {7, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C38_1, false>(vu, c);
    }
    struct Kp1C98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C98_1, false>(vu, c);
    }
    struct Kp1CF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CF8_1, false>(vu, c);
    }
    struct Kp1D58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806103bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {1, 8}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D58_1, false>(vu, c);
    }
    struct Kp1DB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x807303fdu; p.upper = 0x1e0d83cu; p.lowerUsage.vfWrite = {19, 3}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB8_1, false>(vu, c);
    }
    struct Kp1E18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e6317cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E18_1, false>(vu, c);
    }
    struct Kp1E78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e129a8u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E78_1, false>(vu, c);
    }
    struct Kp1ED8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1ED8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1ED8_1, false>(vu, c);
    }
    struct Kp1F38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1110485u; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {17, 4}; p.upperUsage.vfWrite = {18, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F38_1, false>(vu, c);
    }
    struct Kp1F98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e90222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1F98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F98_1, false>(vu, c);
    }
    struct Kp1FF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520105b6u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FF8_1, false>(vu, c);
    }
    struct Kp2058_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100b5802u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2058_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2058_1, false>(vu, c);
    }
    struct Kp20B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18308dbu; p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {3, 1}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20B8_1, false>(vu, c);
    }
    struct Kp2118_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c82b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfWrite = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2118_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2118_1, false>(vu, c);
    }
    struct Kp2178_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x8082396cu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfWrite = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2178_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2178_1, false>(vu, c);
    }
    struct Kp21D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eba1bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {11, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D8_1, false>(vu, c);
    }
    struct Kp2238_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8035cb3cu; p.upper = 0x1dccabeu; p.lowerUsage.vfRead[0] = {25, 1}; p.lowerUsage.vfWrite = {21, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2238_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2238_1, false>(vu, c);
    }
    struct Kp2298_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2298_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2298_1, false>(vu, c);
    }
    struct Kp22F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22F8_1, false>(vu, c);
    }
    struct Kp2358_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2de8c7u; p.upperUsage.vfRead[0] = {29, 1}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2358_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2358_1, false>(vu, c);
    }
    struct Kp23B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23B8_1, false>(vu, c);
    }
    struct Kp2418_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a3fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2418_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2418_1, false>(vu, c);
    }
    struct Kp2478_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xc004c9feu; p.upper = 0x81e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2478_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2478_1, false>(vu, c);
    }
    struct Kp2828_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8101043cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2828_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2828_1, false>(vu, c);
    }
    struct Kp2888_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c891bcu; p.upperUsage.vfRead[0] = {18, 14}; p.upperUsage.vfRead[1] = {8, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_1, false>(vu, c);
    }
    struct Kp28E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8046333du; p.upper = 0xc04a1eu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfWrite = {6, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 6}; p.upperUsage.vfWrite = {8, 6}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_1, false>(vu, c);
    }
    struct Kp2948_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2948_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_1, false>(vu, c);
    }
    struct Kp2BA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e50223u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_1, false>(vu, c);
    }
    struct Kp2C08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_1, false>(vu, c);
    }
    struct Kp2C68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_1, false>(vu, c);
    }
    struct Kp2CC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC8_0, false>(vu, c);
    }
    struct Kp2D28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D28_0, false>(vu, c);
    }
    struct Kp2D88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e33803u; p.upper = 0x1c0783cu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D88_0, false>(vu, c);
    }
    struct Kp2F08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_1, false>(vu, c);
    }
    struct Kp2F68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34801u; p.upper = 0x1e0211fu; p.lowerUsage.vfRead[0] = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F68_1, false>(vu, c);
    }
    struct Kp2FC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_1, false>(vu, c);
    }
    struct Kp3028_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3028_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3028_0, false>(vu, c);
    }
    struct Kp3088_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3088_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3088_0, false>(vu, c);
    }
    struct Kp30E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30E8_0, false>(vu, c);
    }
    struct Kp3270_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3270_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3270_1, false>(vu, c);
    }
    struct Kp32D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p32D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_1, false>(vu, c);
    }
    struct Kp3330_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3330_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3330_1, false>(vu, c);
    }
    struct Kp3390_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3390_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3390_1, false>(vu, c);
    }
    struct Kp33F0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1093du; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfWrite = {1, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33F0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33F0_0, false>(vu, c);
    }
    struct Kp3450_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3450_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3450_0, false>(vu, c);
    }
    struct Kp35D0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p35D0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_1, false>(vu, c);
    }
    struct Kp3630_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3630_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_1, false>(vu, c);
    }
    struct Kp3690_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3690_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_1, false>(vu, c);
    }
    struct Kp36F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36F0_1, false>(vu, c);
    }
    struct Kp3770_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3770_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3770_0, false>(vu, c);
    }
    struct Kp38F0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_1, false>(vu, c);
    }
    struct Kp3950_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3950_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_1, false>(vu, c);
    }
    struct Kp39B0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_1, false>(vu, c);
    }
    struct Kp3A10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A10_1, false>(vu, c);
    }
    struct Kp3C10_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C10_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C10_0, false>(vu, c);
    }
    struct Kp3C70_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C70_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C70_0, false>(vu, c);
    }
    struct Kp3CD0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CD0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_0, false>(vu, c);
    }
    struct Kp3D30_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p3D30_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D30_0, false>(vu, c);
    }
    struct Kp3D90_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103fbu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D90_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D90_0, false>(vu, c);
    }
    struct Kp3DF0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3DF0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DF0_0, false>(vu, c);
    }
    struct Kp2838_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080004u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2838_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2838_2, false>(vu, c);
    }
    struct Kp2898_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_2, false>(vu, c);
    }
    struct Kp28F8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_2, false>(vu, c);
    }
    struct Kp2BA0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA0_2, false>(vu, c);
    }
    struct Kp2C00_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C00_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C00_2, false>(vu, c);
    }
    struct Kp2C90_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p2C90_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_2, false>(vu, c);
    }
    struct Kp3CF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_1, false>(vu, c);
    }
    struct Kp2848_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_3, false>(vu, c);
    }
    struct Kp28A8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_3, false>(vu, c);
    }
    struct Kp2908_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2908_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_3, false>(vu, c);
    }
    struct Kp2968_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2968_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2968_2, false>(vu, c);
    }
    struct Kp29C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p29C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C8_1, false>(vu, c);
    }
    struct Kp2BD8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_3, false>(vu, c);
    }
    struct Kp2C38_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C38_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C38_2, false>(vu, c);
    }
    struct Kp2CA0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CA0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_2, false>(vu, c);
    }
    struct Kp2D00_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D00_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D00_1, false>(vu, c);
    }
    struct Kp2F10_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_2, false>(vu, c);
    }
    struct Kp2F70_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F70_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F70_2, false>(vu, c);
    }
    struct Kp2FD0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD0_2, false>(vu, c);
    }
    struct Kp3240_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_2, false>(vu, c);
    }
    struct Kp32A0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f1u; p.upper = 0x1e2b10au; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_2, false>(vu, c);
    }
    struct Kp3300_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c2a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3300_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_2, false>(vu, c);
    }
    struct Kp3360_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3360_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3360_2, false>(vu, c);
    }
    struct Kp35D0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_2, false>(vu, c);
    }
    struct Kp3630_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3630_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3630_2, false>(vu, c);
    }
    struct Kp3690_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3690_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3690_2, false>(vu, c);
    }
    struct Kp3900_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1c1093du; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_2, false>(vu, c);
    }
    struct Kp3960_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3960_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3960_2, false>(vu, c);
    }
    struct Kp39C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e4f169u; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p39C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_2, false>(vu, c);
    }
    struct Kp3C38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_1, false>(vu, c);
    }
    struct Kp3C98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_1, false>(vu, c);
    }
    struct Kp3D30_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D30_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D30_2, false>(vu, c);
    }
    struct Kp2878_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2878_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_4, false>(vu, c);
    }
    struct Kp28D8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_4, false>(vu, c);
    }
    struct Kp2938_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2938_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_3, false>(vu, c);
    }
    struct Kp2998_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2998_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2998_2, false>(vu, c);
    }
    struct Kp29F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29F8_1, false>(vu, c);
    }
    struct Kp2A58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A58_1, false>(vu, c);
    }
    struct Kp2CA0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CA0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_3, false>(vu, c);
    }
    struct Kp2F20_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F20_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_3, false>(vu, c);
    }
    struct Kp2F80_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F80_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_3, false>(vu, c);
    }
    struct Kp2FE0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p2FE0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_3, false>(vu, c);
    }
    struct Kp3258_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3258_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3258_3, false>(vu, c);
    }
    struct Kp32B8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32B8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B8_3, false>(vu, c);
    }
    struct Kp38F0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1e6393cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_3, false>(vu, c);
    }
    struct Kp3950_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1eb216bu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3950_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3950_3, false>(vu, c);
    }
    struct Kp39B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e83eu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_3, false>(vu, c);
    }
    struct Kp3C58_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C58_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C58_2, false>(vu, c);
    }
    struct Kp3CB8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CB8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CB8_3, false>(vu, c);
    }
    struct Kp3D18_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D18_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_3, false>(vu, c);
    }
    struct Kp3D78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e0215fu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D78_1, false>(vu, c);
    }
    struct Kp2878_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2878_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2878_5, false>(vu, c);
    }
    struct Kp28D8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p28D8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_5, false>(vu, c);
    }
    struct Kp2940_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2940_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2940_4, false>(vu, c);
    }
    struct Kp2BE8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_4, false>(vu, c);
    }
    struct Kp3670_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3670_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_3, false>(vu, c);
    }
    struct Kp38E8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38E8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38E8_4, false>(vu, c);
    }
    struct Kp3948_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_4, false>(vu, c);
    }
    struct Kp3C28_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_3, false>(vu, c);
    }
    struct Kp3C88_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_3, false>(vu, c);
    }
    struct Kp3CE8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE8_2, false>(vu, c);
    }
    struct Kp2910_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2910_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_6, false>(vu, c);
    }
    struct Kp2BB8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c3197du; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_5, false>(vu, c);
    }
    struct Kp2C18_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C18_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_4, false>(vu, c);
    }
    struct Kp2C78_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1e0f83cu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_5, false>(vu, c);
    }
    struct Kp2F28_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_4, false>(vu, c);
    }
    struct Kp2FB8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_4, false>(vu, c);
    }
    struct Kp3018_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3018_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3018_1, false>(vu, c);
    }
    struct Kp3250_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_4, false>(vu, c);
    }
    struct Kp32B0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p32B0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_4, false>(vu, c);
    }
    struct Kp3310_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3310_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_4, false>(vu, c);
    }
    struct Kp3370_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3370_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3370_2, false>(vu, c);
    }
    struct Kp3588_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_3, false>(vu, c);
    }
    struct Kp35E8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_3, false>(vu, c);
    }
    struct Kp3648_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3648_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3648_4, false>(vu, c);
    }
    struct Kp36B0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36B0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36B0_3, false>(vu, c);
    }
    struct Kp3710_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3710_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3710_1, false>(vu, c);
    }
    struct Kp39E8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39E8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E8_3, false>(vu, c);
    }
    struct Kp28D8_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28D8_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28D8_6, false>(vu, c);
    }
    struct Kp2960_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2960_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_4, false>(vu, c);
    }
    struct Kp2F78_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_5, false>(vu, c);
    }
    struct Kp3310_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_5, false>(vu, c);
    }
    struct Kp35B8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B8_4, false>(vu, c);
    }
    struct Kp3618_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3618_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3618_4, false>(vu, c);
    }
    struct Kp3680_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3680_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_5, false>(vu, c);
    }
    struct Kp3928_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3928_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3928_5, false>(vu, c);
    }
    struct Kp3988_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7818u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3988_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_4, false>(vu, c);
    }
    struct Kp39E8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e5313cu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39E8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39E8_4, false>(vu, c);
    }
    struct Kp3C20_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x18a1001u; p.upper = 0x189513eu; p.lowerUsage.vfWrite = {10, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {10, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_4, false>(vu, c);
    }
    struct Kp3C80_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_4, false>(vu, c);
    }
    struct Kp3CE0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c12801u; p.upper = 0x1c2117du; p.lowerUsage.vfRead[0] = {5, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CE0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_5, false>(vu, c);
    }
    struct Kp3D48_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3D48_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D48_3, false>(vu, c);
    }
    struct Kp3DA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x27383eu; p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3DA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DA8_1, false>(vu, c);
    }
    struct Kp2890_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2890_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2890_6, false>(vu, c);
    }
    struct Kp2928_8
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2928_8(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2928_8, false>(vu, c);
    }
    struct Kp2988_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2988_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2988_3, false>(vu, c);
    }
    struct Kp2BC0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_6, false>(vu, c);
    }
    struct Kp2C20_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C20_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C20_5, false>(vu, c);
    }
    struct Kp2C80_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C80_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C80_7, false>(vu, c);
    }
    struct Kp2CE0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2CE0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE0_2, false>(vu, c);
    }
    struct Kp2F18_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F18_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_5, false>(vu, c);
    }
    struct Kp2F78_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_6, false>(vu, c);
    }
    struct Kp2FE0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FE0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_5, false>(vu, c);
    }
    struct Kp3040_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3040_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3040_2, false>(vu, c);
    }
    struct Kp3658_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_6, false>(vu, c);
    }
    struct Kp39C0_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_7, false>(vu, c);
    }
    struct Kp3C68_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_5, false>(vu, c);
    }
    struct Kp3CC8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CC8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_4, false>(vu, c);
    }
    struct Kp3230_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e1b08au; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3230_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3230_5, false>(vu, c);
    }
    struct Kp3290_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3290_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_5, false>(vu, c);
    }
    struct Kp32F0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0295fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32F0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32F0_6, false>(vu, c);
    }
    struct Kp35A0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x1e6393cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_5, false>(vu, c);
    }
    struct Kp3600_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1eb216bu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3600_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3600_5, false>(vu, c);
    }
    struct Kp2FA0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FA0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FA0_6, false>(vu, c);
    }
    struct Kp3310_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_7, false>(vu, c);
    }
    struct Kp01E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ea6043u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p01E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01E8_2d, true>(vu, c);
    }
    struct Kp0440_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ec5810u; p.upper = 0x1e0a1feu; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0440_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0440_2d, true>(vu, c);
    }
    struct Kp0548_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81222b3du; p.upper = 0x1852abdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfWrite = {2, 9}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0548_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0548_2d, true>(vu, c);
    }
    struct Kp0618_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec2850u; p.upper = 0x1f428bdu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {20, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0618_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0618_2d, true>(vu, c);
    }
    struct Kp06F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18aac58u; p.upperUsage.vfRead[0] = {21, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {17, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06F8_2d, true>(vu, c);
    }
    struct Kp07B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000fu; p.upper = 0x1f61abeu; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07B8_2d, true>(vu, c);
    }
    struct Kp0C90_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f56042u; p.upper = 0x1dfc0bcu; p.lowerUsage.vfWrite = {21, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C90_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C90_2d, true>(vu, c);
    }
    struct Kp0EE0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ec5810u; p.upper = 0x1e0a1feu; p.lowerUsage.vfWrite = {12, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE0_2d, true>(vu, c);
    }
    struct Kp0F98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec28bdu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F98_2d, true>(vu, c);
    }
    struct Kp1050_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800601f0u; p.upper = 0x1f41abeu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1050_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1050_2d, true>(vu, c);
    }
    struct Kp10D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4d30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10D0_2d, true>(vu, c);
    }
    struct Kp11A0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9096800u; p.upper = 0x1f61abeu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {22, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11A0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11A0_2d, true>(vu, c);
    }
    struct Kp18A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802553fdu; p.upper = 0x800083u; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 5}; p.upperUsage.vfWrite = {2, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18A8_2d, true>(vu, c);
    }
    struct Kp1A88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c24001u; p.upper = 0x2080c0u; p.lowerUsage.vfWrite = {2, 14}; p.lowerUsage.viRead = 256; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {16, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {3, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A88_2d, true>(vu, c);
    }
    struct Kp1DB0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ca092au; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {10, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DB0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DB0_2d, true>(vu, c);
    }
    struct Kp2000_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x1e02980u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2000_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2000_2d, true>(vu, c);
    }
    struct Kp2268_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e617ffu; p.upper = 0x56003fu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {22, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2268_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2268_2d, true>(vu, c);
    }
    struct Kp23A8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0195cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23A8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23A8_2d, true>(vu, c);
    }
    struct Kp24E8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x860200u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24E8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24E8_1d, true>(vu, c);
    }
    struct Kp2650_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e158bdu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2650_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2650_1d, true>(vu, c);
    }
    struct Kp29D0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80620bfcu; p.upper = 0x1e1c0bcu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D0_3d, true>(vu, c);
    }
    struct Kp2BE8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_7d, true>(vu, c);
    }
    struct Kp3238_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3238_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3238_6d, true>(vu, c);
    }
    struct Kp3328_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3328_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3328_5d, true>(vu, c);
    }
    struct Kp35C0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C0_7d, true>(vu, c);
    }
    struct Kp36A8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A8_4d, true>(vu, c);
    }
    struct Kp3920_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_6d, true>(vu, c);
    }
    struct Kp39A0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39A0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39A0_7d, true>(vu, c);
    }
    struct Kp3A70_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A70_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A70_1d, true>(vu, c);
    }
    struct Kp0288_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8040fffeu; p.upper = 0x1e427e9u; p.lowerUsage.vfRead[0] = {31, 2}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 44; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {31, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 31; return p; }();
    };
    bool p0288_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0288_2d, true>(vu, c);
    }
    struct Kp06B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06B0_2d, true>(vu, c);
    }
    struct Kp0878_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x1010181u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfWrite = {6, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0878_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0878_2d, true>(vu, c);
    }
    struct Kp0988_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81050b3cu; p.upper = 0x10101c2u; p.lowerUsage.vfRead[0] = {1, 8}; p.lowerUsage.vfWrite = {5, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0988_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0988_2d, true>(vu, c);
    }
    struct Kp0A28_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1005000au; p.upper = 0x105f87du; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A28_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A28_2d, true>(vu, c);
    }
    struct Kp0AC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0103cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AC0_2d, true>(vu, c);
    }
    struct Kp0B58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B58_2d, true>(vu, c);
    }
    struct Kp0C30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8039deu; p.upperUsage.vfRead[0] = {7, 4}; p.upperUsage.vfWrite = {7, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C30_2d, true>(vu, c);
    }
    struct Kp0C98_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0083cu; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C98_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C98_3d, true>(vu, c);
    }
    struct Kp0D30_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e7426cu; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D30_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D30_2d, true>(vu, c);
    }
    struct Kp0EE0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EE0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EE0_3d, true>(vu, c);
    }
    struct Kp1018_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e519bcu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1018_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1018_3d, true>(vu, c);
    }
    struct Kp1160_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1988bu; p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1160_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1160_3d, true>(vu, c);
    }
    struct Kp12C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e60222u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12C8_2d, true>(vu, c);
    }
    struct Kp1378_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38b9007u; p.upper = 0x10798cdu; p.lowerUsage.vfRead[0] = {18, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 8}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1378_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1378_2d, true>(vu, c);
    }
    struct Kp14B0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14B0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14B0_2d, true>(vu, c);
    }
    struct Kp1568_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x14039e6u; p.upperUsage.vfRead[0] = {7, 10}; p.upperUsage.vfWrite = {7, 10}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1568_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1568_2d, true>(vu, c);
    }
    struct Kp15E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e231aau; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E0_2d, true>(vu, c);
    }
    struct Kp1648_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18519dbu; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1648_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1648_2d, true>(vu, c);
    }
    struct Kp1778_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1778_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1778_2d, true>(vu, c);
    }
    struct Kp17F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ce2988u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17F0_2d, true>(vu, c);
    }
    struct Kp1850_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x28020eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfWrite = {8, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1850_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1850_2d, true>(vu, c);
    }
    struct Kp19B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c9e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19B8_2d, true>(vu, c);
    }
    struct Kp1AE0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4c8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AE0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AE0_2d, true>(vu, c);
    }
    struct Kp1B40_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x26018eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {6, 2}; p.upperUsage.vfWrite = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B40_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B40_2d, true>(vu, c);
    }
    struct Kp1C58_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C58_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C58_2d, true>(vu, c);
    }
    struct Kp1DC8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC8_3d, true>(vu, c);
    }
    struct Kp1E78_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e129a8u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E78_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E78_2d, true>(vu, c);
    }
    struct Kp1FA8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ea0223u; p.upper = 0x1e198cbu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FA8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA8_2d, true>(vu, c);
    }
    struct Kp20C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x47800000u; p.upper = 0x8180383cu; p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p20C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C0_2d, true>(vu, c);
    }
    struct Kp21C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eaa8bdu; p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {10, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21C8_2d, true>(vu, c);
    }
    struct Kp2248_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8036d33cu; p.upper = 0x1dcd2beu; p.lowerUsage.vfRead[0] = {26, 1}; p.lowerUsage.vfWrite = {22, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2248_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2248_2d, true>(vu, c);
    }
    struct Kp23F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e05a3fu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23F0_2d, true>(vu, c);
    }
    struct Kp2458_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0123fu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2458_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2458_3d, true>(vu, c);
    }
    struct Kp24C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e059feu; p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24C0_2d, true>(vu, c);
    }
    struct Kp28B8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c24a43u; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_8d, true>(vu, c);
    }
    struct Kp2BA8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e50223u; p.upper = 0x1e1d08au; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_7d, true>(vu, c);
    }
    struct Kp2CD0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD0_3d, true>(vu, c);
    }
    struct Kp2F08_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x24203eu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F08_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F08_6d, true>(vu, c);
    }
    struct Kp2FE8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE8_5d, true>(vu, c);
    }
    struct Kp30B0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p30B0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30B0_1d, true>(vu, c);
    }
    struct Kp3290_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_7d, true>(vu, c);
    }
    struct Kp3378_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3378_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3378_3d, true>(vu, c);
    }
    struct Kp33E0_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33E0_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33E0_1d, true>(vu, c);
    }
    struct Kp3660_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3660_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3660_8d, true>(vu, c);
    }
    struct Kp38D8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_7d, true>(vu, c);
    }
    struct Kp3CF8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_8d, true>(vu, c);
    }
    struct Kp2850_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_8d, true>(vu, c);
    }
    struct Kp3CF8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_9d, true>(vu, c);
    }
    struct Kp28A0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_8d, true>(vu, c);
    }
    struct Kp2988_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2988_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2988_4d, true>(vu, c);
    }
    struct Kp2BF8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_8d, true>(vu, c);
    }
    struct Kp2CE0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CE0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CE0_3d, true>(vu, c);
    }
    struct Kp2F50_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F50_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F50_7d, true>(vu, c);
    }
    struct Kp3590_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c0195cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3590_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3590_7d, true>(vu, c);
    }
    struct Kp38D8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_8d, true>(vu, c);
    }
    struct Kp3C28_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C28_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C28_6d, true>(vu, c);
    }
    struct Kp3D18_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D18_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D18_5d, true>(vu, c);
    }
    struct Kp2888_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_8d, true>(vu, c);
    }
    struct Kp2908_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2908_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_7d, true>(vu, c);
    }
    struct Kp29D8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29D8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29D8_3d, true>(vu, c);
    }
    struct Kp2EE8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EE8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EE8_7d, true>(vu, c);
    }
    struct Kp3310_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_9d, true>(vu, c);
    }
    struct Kp39B8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B8_8d, true>(vu, c);
    }
    struct Kp3C88_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_7d, true>(vu, c);
    }
    struct Kp3D70_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3D70_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D70_3d, true>(vu, c);
    }
    struct Kp2BC0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_9d, true>(vu, c);
    }
    struct Kp3948_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b0cau; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3948_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3948_7d, true>(vu, c);
    }
    struct Kp2908_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2908_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_8d, true>(vu, c);
    }
    struct Kp2F10_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F10_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F10_7d, true>(vu, c);
    }
    struct Kp3000_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3000_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3000_5d, true>(vu, c);
    }
    struct Kp3290_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3290_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3290_8d, true>(vu, c);
    }
    struct Kp3378_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3378_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3378_4d, true>(vu, c);
    }
    struct Kp35E8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_8d, true>(vu, c);
    }
    struct Kp36D0_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36D0_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36D0_4d, true>(vu, c);
    }
    struct Kp3CD8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CD8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_7d, true>(vu, c);
    }
    struct Kp3588_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_8d, true>(vu, c);
    }
    struct Kp3920_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_9d, true>(vu, c);
    }
    struct Kp3A08_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A08_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A08_4d, true>(vu, c);
    }
    struct Kp3C78_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_9d, true>(vu, c);
    }
    struct Kp3D58_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D58_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D58_4d, true>(vu, c);
    }
    struct Kp2850_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8025f33cu; p.upper = 0x1c5d8bcu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {5, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2850_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2850_9d, true>(vu, c);
    }
    struct Kp2948_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2948_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_7d, true>(vu, c);
    }
    struct Kp2BE0_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e517ffu; p.upper = 0x1e52129u; p.lowerUsage.vfWrite = {5, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE0_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE0_10d, true>(vu, c);
    }
    struct Kp2CC8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CC8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CC8_4d, true>(vu, c);
    }
    struct Kp2F38_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_9d, true>(vu, c);
    }
    struct Kp3018_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3018_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3018_4d, true>(vu, c);
    }
    struct Kp3988_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3988_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3988_8d, true>(vu, c);
    }
    struct Kp3248_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_10d, true>(vu, c);
    }
    struct Kp35D0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e488bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D0_9d, true>(vu, c);
    }
    struct Kp3318_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3318_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3318_10d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
