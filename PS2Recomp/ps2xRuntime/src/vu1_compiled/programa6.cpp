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
    struct Kp0028_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c06bdu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0028_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0028_0, false>(vu, c);
    }
    struct Kp0088_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800066fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0088_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0088_0, false>(vu, c);
    }
    struct Kp00E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80016b70u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p00E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00E8_0, false>(vu, c);
    }
    struct Kp0148_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f65812u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {22, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0148_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0148_0, false>(vu, c);
    }
    struct Kp01A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01A8_0, false>(vu, c);
    }
    struct Kp0208_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e66044u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {6, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0208_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0208_0, false>(vu, c);
    }
    struct Kp0268_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30033000u; p.upper = 0x1e238ffu; p.lowerUsage.viRead = 64; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0268_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0268_0, false>(vu, c);
    }
    struct Kp02C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7805u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p02C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02C8_0, false>(vu, c);
    }
    struct Kp0328_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0328_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0328_0, false>(vu, c);
    }
    struct Kp0388_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50070002u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0388_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0388_0, false>(vu, c);
    }
    struct Kp03E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80031870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03E8_0, false>(vu, c);
    }
    struct Kp0448_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ed5811u; p.upper = 0x1e06327u; p.lowerUsage.vfWrite = {13, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0448_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0448_0, false>(vu, c);
    }
    struct Kp04A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81de3b3cu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {7, 14}; p.lowerUsage.vfWrite = {30, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p04A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04A8_0, false>(vu, c);
    }
    struct Kp0508_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd604bu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0508_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0508_0, false>(vu, c);
    }
    struct Kp0568_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80201fbdu; p.upper = 0x5b00c3u; p.lowerUsage.vfRead[0] = {3, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 18; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(4); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {27, 1}; p.upperUsage.vfWrite = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 3; return p; }();
    };
    bool p0568_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0568_0, false>(vu, c);
    }
    struct Kp05C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8021067cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05C8_0, false>(vu, c);
    }
    struct Kp0628_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec5052u; p.upper = 0x1f521bcu; p.lowerUsage.vfRead[0] = {10, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {21, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0628_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0628_0, false>(vu, c);
    }
    struct Kp0688_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {14, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0688_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0688_0, false>(vu, c);
    }
    struct Kp06E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8027f33cu; p.upper = 0x18004e6u; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {7, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfWrite = {19, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06E8_0, false>(vu, c);
    }
    struct Kp0748_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5e001802u; p.upper = 0x1e039e2u; p.lowerUsage.viRead = 8; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0748_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0748_0, false>(vu, c);
    }
    struct Kp07A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec1853u; p.upper = 0x5530bfu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {21, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07A8_0, false>(vu, c);
    }
    struct Kp0808_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x4d30bfu; p.upperUsage.vfRead[0] = {6, 2}; p.upperUsage.vfRead[1] = {13, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0808_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0808_0, false>(vu, c);
    }
    struct Kp0868_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4a03a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0868_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0868_0, false>(vu, c);
    }
    struct Kp08C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa2b6045u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6144; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08C8_0, false>(vu, c);
    }
    struct Kp0928_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100303ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0928_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0928_0, false>(vu, c);
    }
    struct Kp0988_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80016871u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0988_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0988_0, false>(vu, c);
    }
    struct Kp09E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800066fcu; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(7); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p09E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09E8_0, false>(vu, c);
    }
    struct Kp0A48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80012130u; p.upper = 0x2ffu; p.lowerUsage.viRead = 18; p.lowerUsage.viWrite = 16; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0A48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A48_0, false>(vu, c);
    }
    struct Kp0AA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800110b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 6; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AA8_0, false>(vu, c);
    }
    struct Kp0B08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80073870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0B08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B08_0, false>(vu, c);
    }
    struct Kp0B68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x806b0bfcu; p.upper = 0x22093fu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B68_0, false>(vu, c);
    }
    struct Kp0BC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7805u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0BC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BC8_0, false>(vu, c);
    }
    struct Kp0C28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100300ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C28_0, false>(vu, c);
    }
    struct Kp0C88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f76041u; p.upper = 0x1c0d83cu; p.lowerUsage.vfWrite = {23, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C88_0, false>(vu, c);
    }
    struct Kp0CE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1df17ffu; p.upper = 0x18002fcu; p.lowerUsage.vfWrite = {31, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CE8_0, false>(vu, c);
    }
    struct Kp0D48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x380a0000u; p.upper = 0x1dfc8bdu; p.lowerUsage.viWrite = 1024; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D48_0, false>(vu, c);
    }
    struct Kp0DA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500907e5u; p.upper = 0x2ffu; p.lowerUsage.viRead = 512; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0DA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DA8_0, false>(vu, c);
    }
    struct Kp0E08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007d9u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E08_0, false>(vu, c);
    }
    struct Kp0E68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800a51b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 1024; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E68_0, false>(vu, c);
    }
    struct Kp0EC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbb000000u; p.upper = 0x80200862u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0EC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EC8_0, false>(vu, c);
    }
    struct Kp0F28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ea6052u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F28_0, false>(vu, c);
    }
    struct Kp0F88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f6348au; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {22, 2}; p.upperUsage.vfWrite = {18, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0F88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F88_0, false>(vu, c);
    }
    struct Kp0FE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbf000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p0FE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FE8_0, false>(vu, c);
    }
    struct Kp1048_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e26055u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1048_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1048_0, false>(vu, c);
    }
    struct Kp10A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f715ceu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {23, 2}; p.upperUsage.vfWrite = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10A8_0, false>(vu, c);
    }
    struct Kp1108_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ef13ceu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1108_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1108_0, false>(vu, c);
    }
    struct Kp1168_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022033cu; p.upper = 0x1c118eau; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1168_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1168_0, false>(vu, c);
    }
    struct Kp11C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1f715ceu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {23, 2}; p.upperUsage.vfWrite = {23, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p11C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11C8_0, false>(vu, c);
    }
    struct Kp1228_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1228_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1228_0, false>(vu, c);
    }
    struct Kp1288_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100d6801u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1288_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1288_0, false>(vu, c);
    }
    struct Kp12E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000007u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p12E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12E8_0, false>(vu, c);
    }
    struct Kp1348_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1348_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1348_0, false>(vu, c);
    }
    struct Kp13A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10070001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p13A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13A8_0, false>(vu, c);
    }
    struct Kp1408_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x9096800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 512; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1408_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1408_0, false>(vu, c);
    }
    struct Kp1468_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800018b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1468_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1468_0, false>(vu, c);
    }
    struct Kp14C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p14C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14C8_0, false>(vu, c);
    }
    struct Kp1528_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1528_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1528_0, false>(vu, c);
    }
    struct Kp1588_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800068f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8192; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1588_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1588_0, false>(vu, c);
    }
    struct Kp15E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800012f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p15E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E8_0, false>(vu, c);
    }
    struct Kp1648_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1648_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1648_0, false>(vu, c);
    }
    struct Kp16A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xb0103a0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p16A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A8_0, false>(vu, c);
    }
    struct Kp1708_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800131b4u; p.upper = 0x2ffu; p.lowerUsage.viRead = 66; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1708_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1708_0, false>(vu, c);
    }
    struct Kp1768_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100f0010u; p.upper = 0x1960cadu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfRead[1] = {22, 12}; p.upperUsage.vfWrite = {18, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1768_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1768_0, false>(vu, c);
    }
    struct Kp17C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x58000febu; p.upper = 0x21017fu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17C8_0, false>(vu, c);
    }
    struct Kp1828_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80080874u; p.upper = 0x1d178aeu; p.lowerUsage.viRead = 258; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {15, 14}; p.upperUsage.vfRead[1] = {17, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1828_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1828_0, false>(vu, c);
    }
    struct Kp1888_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0xa4b03a1u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1888_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1888_0, false>(vu, c);
    }
    struct Kp18E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x460003edu; p.upper = 0x80202122u; p.upperUsage.vfRead[0] = {4, 1}; p.upperUsage.vfWrite = {4, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p18E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18E8_0, false>(vu, c);
    }
    struct Kp1948_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x808c833cu; p.upper = 0x9002c0u; p.lowerUsage.vfRead[0] = {16, 4}; p.lowerUsage.vfWrite = {12, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {16, 8}; p.upperUsage.vfWrite = {11, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1948_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1948_0, false>(vu, c);
    }
    struct Kp19A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0045u; p.upper = 0x1cd72acu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {13, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p19A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19A8_0, false>(vu, c);
    }
    struct Kp1A08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A08_0, false>(vu, c);
    }
    struct Kp1A68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80017334u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16386; p.lowerUsage.viWrite = 4096; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A68_0, false>(vu, c);
    }
    struct Kp1AC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010900u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1AC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC8_0, false>(vu, c);
    }
    struct Kp1B28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e118bdu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B28_0, false>(vu, c);
    }
    struct Kp1B88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e35800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {11, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1B88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B88_0, false>(vu, c);
    }
    struct Kp1BE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50050034u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1BE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BE8_0, false>(vu, c);
    }
    struct Kp1C48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1C48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C48_0, false>(vu, c);
    }
    struct Kp1CA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500a101cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 1028; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1CA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CA8_0, false>(vu, c);
    }
    struct Kp1D08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D08_0, false>(vu, c);
    }
    struct Kp1D68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12010400u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D68_0, false>(vu, c);
    }
    struct Kp1DC8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x103f8cau; p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC8_0, false>(vu, c);
    }
    struct Kp1E28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103ffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1E28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E28_0, false>(vu, c);
    }
    struct Kp1E88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500507a4u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E88_0, false>(vu, c);
    }
    struct Kp1EE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x810153fdu; p.upper = 0x1cf91ffu; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {18, 14}; p.upperUsage.vfRead[1] = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1EE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EE8_0, false>(vu, c);
    }
    struct Kp1F48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12060001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 64; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F48_0, false>(vu, c);
    }
    struct Kp1FA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1FA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA8_0, false>(vu, c);
    }
    struct Kp2008_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c4197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2008_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2008_0, false>(vu, c);
    }
    struct Kp2068_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2068_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2068_0, false>(vu, c);
    }
    struct Kp20C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x40000048u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p20C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C8_0, false>(vu, c);
    }
    struct Kp2128_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1c1a0adu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2128_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2128_0, false>(vu, c);
    }
    struct Kp2188_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080003u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2188_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2188_0, false>(vu, c);
    }
    struct Kp21E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0670u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p21E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21E8_0, false>(vu, c);
    }
    struct Kp2248_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2248_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2248_0, false>(vu, c);
    }
    struct Kp22A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0658u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22A8_0, false>(vu, c);
    }
    struct Kp2308_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2308_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2308_0, false>(vu, c);
    }
    struct Kp2368_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f6u; p.upper = 0x1d708a9u; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfRead[1] = {23, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2368_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2368_0, false>(vu, c);
    }
    struct Kp23C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x18002fcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23C8_0, false>(vu, c);
    }
    struct Kp2428_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420f0628u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2428_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2428_0, false>(vu, c);
    }
    struct Kp2488_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x30073800u; p.upper = 0x45396cu; p.lowerUsage.viRead = 128; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 2}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfWrite = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2488_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2488_0, false>(vu, c);
    }
    struct Kp24E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x860200u; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {8, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24E8_0, false>(vu, c);
    }
    struct Kp2548_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8426016u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4096; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2548_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2548_0, false>(vu, c);
    }
    struct Kp25A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800d0b71u; p.upper = 0x2ffu; p.lowerUsage.viRead = 8194; p.lowerUsage.viWrite = 8192; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p25A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp25A8_0, false>(vu, c);
    }
    struct Kp2608_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p2608_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2608_0, false>(vu, c);
    }
    struct Kp2668_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2668_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2668_0, false>(vu, c);
    }
    struct Kp26C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p26C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp26C8_0, false>(vu, c);
    }
    struct Kp2728_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2728_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2728_0, false>(vu, c);
    }
    struct Kp2788_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800059f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2788_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2788_0, false>(vu, c);
    }
    struct Kp27E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80600c3eu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p27E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp27E8_0, false>(vu, c);
    }
    struct Kp2848_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_0, false>(vu, c);
    }
    struct Kp28A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_0, false>(vu, c);
    }
    struct Kp2908_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2908_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_0, false>(vu, c);
    }
    struct Kp2968_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2968_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2968_0, false>(vu, c);
    }
    struct Kp29C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29C8_0, false>(vu, c);
    }
    struct Kp2A28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A28_0, false>(vu, c);
    }
    struct Kp2A88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2A88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A88_0, false>(vu, c);
    }
    struct Kp2AE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x2403ffffu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2AE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2AE8_0, false>(vu, c);
    }
    struct Kp2B48_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B48_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B48_0, false>(vu, c);
    }
    struct Kp2BA8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BA8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BA8_0, false>(vu, c);
    }
    struct Kp2C08_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_0, false>(vu, c);
    }
    struct Kp2C68_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C68_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C68_0, false>(vu, c);
    }
    struct Kp2EF8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81c9433cu; p.upper = 0x1e0f83cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfWrite = {9, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2EF8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2EF8_0, false>(vu, c);
    }
    struct Kp2F58_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F58_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F58_0, false>(vu, c);
    }
    struct Kp2FB8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_0, false>(vu, c);
    }
    struct Kp3248_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_0, false>(vu, c);
    }
    struct Kp32A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c3197du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A8_0, false>(vu, c);
    }
    struct Kp3308_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e7313cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3308_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3308_0, false>(vu, c);
    }
    struct Kp3368_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0215fu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3368_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3368_0, false>(vu, c);
    }
    struct Kp3588_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_0, false>(vu, c);
    }
    struct Kp35E8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E8_0, false>(vu, c);
    }
    struct Kp3648_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3648_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3648_0, false>(vu, c);
    }
    struct Kp36A8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A8_0, false>(vu, c);
    }
    struct Kp3708_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3708_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3708_0, false>(vu, c);
    }
    struct Kp3908_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3908_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3908_0, false>(vu, c);
    }
    struct Kp3968_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0495cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3968_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_0, false>(vu, c);
    }
    struct Kp39C8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39C8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C8_0, false>(vu, c);
    }
    struct Kp3A28_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A28_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A28_0, false>(vu, c);
    }
    struct Kp3A88_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A88_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A88_0, false>(vu, c);
    }
    struct Kp3AE8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3AE8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3AE8_0, false>(vu, c);
    }
    struct Kp0050_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fe6014u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {30, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0050_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0050_1, false>(vu, c);
    }
    struct Kp00B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x50010007u; p.upper = 0x1ec617du; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p00B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp00B8_1, false>(vu, c);
    }
    struct Kp0118_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5a000806u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0118_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0118_1, false>(vu, c);
    }
    struct Kp0178_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80015bfcu; p.upper = 0x1ec593eu; p.lowerUsage.vfRead[0] = {11, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {11, 15}; p.upperUsage.vfWrite = {12, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0178_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0178_1, false>(vu, c);
    }
    struct Kp01E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb601au; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p01E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01E0_1, false>(vu, c);
    }
    struct Kp0240_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f4u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0240_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0240_1, false>(vu, c);
    }
    struct Kp02A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x200840u; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p02A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp02A0_1, false>(vu, c);
    }
    struct Kp0308_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c10b0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4100; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0308_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0308_1, false>(vu, c);
    }
    struct Kp0368_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1eb601bu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {11, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0368_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0368_1, false>(vu, c);
    }
    struct Kp03C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e10800u; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p03C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp03C8_1, false>(vu, c);
    }
    struct Kp0428_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x400007f6u; p.upper = 0x2ffu; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0428_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0428_1, false>(vu, c);
    }
    struct Kp0488_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1001054cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0488_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0488_1, false>(vu, c);
    }
    struct Kp04E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0103cu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p04E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp04E8_1, false>(vu, c);
    }
    struct Kp0548_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e91000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {9, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0548_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0548_1, false>(vu, c);
    }
    struct Kp05A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p05A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp05A8_1, false>(vu, c);
    }
    struct Kp0608_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e21001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {2, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0608_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0608_1, false>(vu, c);
    }
    struct Kp0668_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11000u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0668_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0668_1, false>(vu, c);
    }
    struct Kp06C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0083cu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06C8_1, false>(vu, c);
    }
    struct Kp0728_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0728_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0728_1, false>(vu, c);
    }
    struct Kp0788_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0788_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0788_1, false>(vu, c);
    }
    struct Kp07E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e31002u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {3, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p07E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07E8_1, false>(vu, c);
    }
    struct Kp0848_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0848_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0848_1, false>(vu, c);
    }
    struct Kp08A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x808843bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {8, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p08A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp08A8_1, false>(vu, c);
    }
    struct Kp0908_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0908_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0908_1, false>(vu, c);
    }
    struct Kp0968_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e11001u; p.upper = 0x400262u; p.lowerUsage.vfWrite = {1, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfWrite = {9, 2}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0968_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0968_1, false>(vu, c);
    }
    struct Kp09C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e430bdu; p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p09C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp09C8_1, false>(vu, c);
    }
    struct Kp0A30_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10020088u; p.upper = 0x105f945u; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {31, 8}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A30_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A30_1, false>(vu, c);
    }
    struct Kp0A98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8225bu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfRead[1] = {8, 1}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A98_1, false>(vu, c);
    }
    struct Kp0AF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0AF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AF8_1, false>(vu, c);
    }
    struct Kp0B58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x104003fu; p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B58_1, false>(vu, c);
    }
    struct Kp0BB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8029067cu; p.upper = 0x1c001a0u; p.lowerUsage.vfWrite = {9, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0BB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0BB8_1, false>(vu, c);
    }
    struct Kp0C18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x500107fau; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0C18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C18_1, false>(vu, c);
    }
    struct Kp0C78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c74949u; p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C78_1, false>(vu, c);
    }
    struct Kp0CD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1df1a49u; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {31, 4}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CD8_1, false>(vu, c);
    }
    struct Kp0D38_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0003fu; p.upperUsage.vfRead[0] = {0, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D38_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D38_1, false>(vu, c);
    }
    struct Kp0D98_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x416015u; p.upper = 0x1e0483cu; p.lowerUsage.vfWrite = {1, 2}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0D98_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0D98_1, false>(vu, c);
    }
    struct Kp0DF8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1d3c62au; p.upperUsage.vfRead[0] = {24, 14}; p.upperUsage.vfRead[1] = {19, 14}; p.upperUsage.vfWrite = {24, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0DF8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DF8_1, false>(vu, c);
    }
    struct Kp0E58_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0E58_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0E58_1, false>(vu, c);
    }
    struct Kp0EB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EB8_1, false>(vu, c);
    }
    struct Kp0F18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F18_1, false>(vu, c);
    }
    struct Kp0F78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0e7800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p0F78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0F78_1, false>(vu, c);
    }
    struct Kp0FD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FD8_1, false>(vu, c);
    }
    struct Kp1038_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e3e3bcu; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1038_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1038_1, false>(vu, c);
    }
    struct Kp1098_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb1b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1098_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1098_1, false>(vu, c);
    }
    struct Kp10F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p10F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10F8_1, false>(vu, c);
    }
    struct Kp1158_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1158_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1158_1, false>(vu, c);
    }
    struct Kp11B8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb8b7du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {17, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p11B8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp11B8_1, false>(vu, c);
    }
    struct Kp1218_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18179fdu; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1218_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1218_1, false>(vu, c);
    }
    struct Kp1278_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1278_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1278_1, false>(vu, c);
    }
    struct Kp12D8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12D8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D8_1, false>(vu, c);
    }
    struct Kp1340_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb3000u; p.upper = 0x18579dbu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1340_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1340_1, false>(vu, c);
    }
    struct Kp13A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p13A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp13A0_1, false>(vu, c);
    }
    struct Kp1408_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18179fdu; p.upperUsage.vfRead[0] = {15, 12}; p.upperUsage.vfWrite = {1, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1408_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1408_1, false>(vu, c);
    }
    struct Kp1468_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f10801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {17, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1468_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1468_1, false>(vu, c);
    }
    struct Kp14C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fb504f7u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p14C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14C8_1, false>(vu, c);
    }
    struct Kp1528_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e0115cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1528_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1528_1, false>(vu, c);
    }
    struct Kp1588_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0127fu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1588_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1588_1, false>(vu, c);
    }
    struct Kp15E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x421ed7b7u; p.upper = 0x81e24abeu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p15E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15E8_1, false>(vu, c);
    }
    struct Kp1648_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18519dbu; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfWrite = {7, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1648_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1648_1, false>(vu, c);
    }
    struct Kp16A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x802303fdu; p.upper = 0x180283cu; p.lowerUsage.vfWrite = {3, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p16A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16A8_1, false>(vu, c);
    }
    struct Kp1708_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800c0870u; p.upper = 0x2ffu; p.lowerUsage.viRead = 4098; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1708_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1708_1, false>(vu, c);
    }
    struct Kp1768_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1768_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1768_1, false>(vu, c);
    }
    struct Kp17C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5295bu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p17C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp17C8_1, false>(vu, c);
    }
    struct Kp1828_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x53003fu; p.upperUsage.vfRead[0] = {0, 2}; p.upperUsage.vfRead[1] = {19, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1828_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1828_1, false>(vu, c);
    }
    struct Kp1888_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c949ffu; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1888_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1888_1, false>(vu, c);
    }
    struct Kp18E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c6e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18E8_1, false>(vu, c);
    }
    struct Kp1948_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1948_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1948_1, false>(vu, c);
    }
    struct Kp19A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81eb137du; p.upper = 0x2ffu; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p19A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp19A8_1, false>(vu, c);
    }
    struct Kp1A08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fc6004u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {28, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A08_1, false>(vu, c);
    }
    struct Kp1A68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10075800u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2048; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1A68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A68_1, false>(vu, c);
    }
    struct Kp1AC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c5c8bdu; p.upperUsage.vfRead[0] = {25, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AC8_1, false>(vu, c);
    }
    struct Kp1B28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1cf2a48u; p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfRead[1] = {15, 8}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B28_1, false>(vu, c);
    }
    struct Kp1B88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c739ffu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.writesClip = 1; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B88_1, false>(vu, c);
    }
    struct Kp1BE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x22017fu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1BE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1BE8_1, false>(vu, c);
    }
    struct Kp1C48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C48_1, false>(vu, c);
    }
    struct Kp1CA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1CA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1CA8_1, false>(vu, c);
    }
    struct Kp1D08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x420e0617u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D08_1, false>(vu, c);
    }
    struct Kp1D68_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1f00801u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {16, 15}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1D68_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1D68_1, false>(vu, c);
    }
    struct Kp1DC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC8_1, false>(vu, c);
    }
    struct Kp1E28_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x24000fffu; p.upper = 0x1e0115cu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E28_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E28_1, false>(vu, c);
    }
    struct Kp1E88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e22928u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E88_1, false>(vu, c);
    }
    struct Kp1EE8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1EE8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1EE8_1, false>(vu, c);
    }
    struct Kp1F48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800003bfu; p.upper = 0x2ffu; p.lowerUsage.waitQ = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p1F48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1F48_1, false>(vu, c);
    }
    struct Kp1FA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ea0223u; p.upper = 0x1e198cbu; p.lowerUsage.vfWrite = {10, 15}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FA8_1, false>(vu, c);
    }
    struct Kp2008_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x46000000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p2008_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2008_1, false>(vu, c);
    }
    struct Kp2068_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3f004000u; p.upper = 0x800002ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; p.upperNop = true; return p; }();
    };
    bool p2068_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2068_1, false>(vu, c);
    }
    struct Kp20C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18018a7u; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20C8_1, false>(vu, c);
    }
    struct Kp2128_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80055af0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 2080; p.lowerUsage.viWrite = 2048; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2128_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2128_1, false>(vu, c);
    }
    struct Kp2188_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3831ffeu; p.upper = 0x1e14128u; p.lowerUsage.vfRead[0] = {3, 12}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {1, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2188_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2188_1, false>(vu, c);
    }
    struct Kp21E8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ebb2cau; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {11, 2}; p.upperUsage.vfWrite = {11, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21E8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21E8_1, false>(vu, c);
    }
    struct Kp2248_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8036d33cu; p.upper = 0x1dcd2beu; p.lowerUsage.vfRead[0] = {26, 1}; p.lowerUsage.vfWrite = {22, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {26, 14}; p.upperUsage.vfRead[1] = {28, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2248_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2248_1, false>(vu, c);
    }
    struct Kp22A8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1fd6005u; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {29, 15}; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p22A8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22A8_1, false>(vu, c);
    }
    struct Kp2308_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0d83cu; p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2308_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2308_1, false>(vu, c);
    }
    struct Kp2368_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x21005au; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2368_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2368_1, false>(vu, c);
    }
    struct Kp23C8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x5201053cu; p.upper = 0x2ffu; p.lowerUsage.viRead = 2; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p23C8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23C8_1, false>(vu, c);
    }
    struct Kp2428_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0098fu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2428_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2428_1, false>(vu, c);
    }
    struct Kp2488_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0xbfb504f3u; p.upper = 0x81e049a3u; p.upperUsage.vfRead[0] = {9, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2488_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2488_1, false>(vu, c);
    }
    struct Kp2838_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8041043cu; p.upper = 0x2ffu; p.lowerUsage.vfWrite = {1, 2}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2838_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2838_1, false>(vu, c);
    }
    struct Kp2898_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8022067cu; p.upper = 0x1c8a0beu; p.lowerUsage.vfWrite = {2, 1}; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {8, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_1, false>(vu, c);
    }
    struct Kp28F8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28F8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28F8_1, false>(vu, c);
    }
    struct Kp2958_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2ffu; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2958_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2958_1, false>(vu, c);
    }
    struct Kp2BB8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB8_1, false>(vu, c);
    }
    struct Kp2C18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C18_1, false>(vu, c);
    }
    struct Kp2C78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C78_1, false>(vu, c);
    }
    struct Kp2CD8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD8_0, false>(vu, c);
    }
    struct Kp2D38_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D38_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D38_0, false>(vu, c);
    }
    struct Kp2D98_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c168bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {13, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D98_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D98_0, false>(vu, c);
    }
    struct Kp2F18_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F18_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F18_1, false>(vu, c);
    }
    struct Kp2F78_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F78_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F78_1, false>(vu, c);
    }
    struct Kp2FD8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c4d9bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FD8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FD8_1, false>(vu, c);
    }
    struct Kp3038_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e0215fu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3038_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3038_0, false>(vu, c);
    }
    struct Kp3098_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e741e9u; p.upperUsage.vfRead[0] = {8, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3098_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3098_0, false>(vu, c);
    }
    struct Kp30F8_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p30F8_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30F8_0, false>(vu, c);
    }
    struct Kp3280_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3280_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3280_1, false>(vu, c);
    }
    struct Kp32E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e8213cu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32E0_1, false>(vu, c);
    }
    struct Kp3340_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3340_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3340_1, false>(vu, c);
    }
    struct Kp33A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p33A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp33A0_1, false>(vu, c);
    }
    struct Kp3400_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3400_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3400_0, false>(vu, c);
    }
    struct Kp3580_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_1, false>(vu, c);
    }
    struct Kp35E0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_1, false>(vu, c);
    }
    struct Kp3640_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001cu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3640_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_1, false>(vu, c);
    }
    struct Kp36A0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p36A0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A0_1, false>(vu, c);
    }
    struct Kp3720_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3720_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3720_0, false>(vu, c);
    }
    struct Kp3780_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507e5u; p.upper = 0x1c160bcu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {12, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3780_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3780_0, false>(vu, c);
    }
    struct Kp3900_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_1, false>(vu, c);
    }
    struct Kp3960_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3960_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3960_1, false>(vu, c);
    }
    struct Kp39C0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p39C0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_1, false>(vu, c);
    }
    struct Kp3A20_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A20_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A20_1, false>(vu, c);
    }
    struct Kp3C20_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x189393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {9, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C20_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C20_0, false>(vu, c);
    }
    struct Kp3C80_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C80_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C80_0, false>(vu, c);
    }
    struct Kp3CE0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100e001bu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 16384; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CE0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CE0_0, false>(vu, c);
    }
    struct Kp3D40_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1c0b83cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D40_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D40_0, false>(vu, c);
    }
    struct Kp3DA0_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3DA0_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3DA0_0, false>(vu, c);
    }
    struct Kp3E00_0
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3E00_0(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3E00_0, false>(vu, c);
    }
    struct Kp2848_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_2, false>(vu, c);
    }
    struct Kp28A8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28A8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A8_2, false>(vu, c);
    }
    struct Kp2908_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2908_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2908_2, false>(vu, c);
    }
    struct Kp2BB0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c35001u; p.upper = 0x1e2b10au; p.lowerUsage.vfRead[0] = {10, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BB0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BB0_2, false>(vu, c);
    }
    struct Kp2C10_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C10_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C10_2, false>(vu, c);
    }
    struct Kp2CA0_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2CA0_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CA0_1, false>(vu, c);
    }
    struct Kp3D08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_1, false>(vu, c);
    }
    struct Kp2858_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4d9bcu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2858_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2858_3, false>(vu, c);
    }
    struct Kp28B8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2117du; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B8_3, false>(vu, c);
    }
    struct Kp2918_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2918_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2918_3, false>(vu, c);
    }
    struct Kp2978_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e52129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {5, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2978_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_1, false>(vu, c);
    }
    struct Kp2B88_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2B88_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B88_3, false>(vu, c);
    }
    struct Kp2BE8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BE8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BE8_3, false>(vu, c);
    }
    struct Kp2C48_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_2, false>(vu, c);
    }
    struct Kp2CB0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CB0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB0_2, false>(vu, c);
    }
    struct Kp2D10_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c7e0bdu; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {7, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D10_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D10_1, false>(vu, c);
    }
    struct Kp2F20_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_2, false>(vu, c);
    }
    struct Kp2F80_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F80_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F80_2, false>(vu, c);
    }
    struct Kp2FE0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2093du; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FE0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FE0_2, false>(vu, c);
    }
    struct Kp3250_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e2a8bdu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3250_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3250_2, false>(vu, c);
    }
    struct Kp32B0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4a0f7000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32B0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32B0_2, false>(vu, c);
    }
    struct Kp3310_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x182093du; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3310_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3310_2, false>(vu, c);
    }
    struct Kp3580_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c6297du; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {5, 14}; p.upperUsage.vfWrite = {6, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3580_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3580_2, false>(vu, c);
    }
    struct Kp35E0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35E0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_2, false>(vu, c);
    }
    struct Kp3640_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3640_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3640_2, false>(vu, c);
    }
    struct Kp36A0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36A0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36A0_2, false>(vu, c);
    }
    struct Kp3910_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3910_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3910_2, false>(vu, c);
    }
    struct Kp3970_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3970_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3970_2, false>(vu, c);
    }
    struct Kp39D8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39D8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39D8_2, false>(vu, c);
    }
    struct Kp3C48_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4213fu; p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C48_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C48_1, false>(vu, c);
    }
    struct Kp3CA8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e337ffu; p.upper = 0x1e1a0bcu; p.lowerUsage.vfRead[0] = {6, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CA8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA8_1, false>(vu, c);
    }
    struct Kp3D40_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D40_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D40_2, false>(vu, c);
    }
    struct Kp2888_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_4, false>(vu, c);
    }
    struct Kp28E8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_4, false>(vu, c);
    }
    struct Kp2948_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x48007000u; p.upper = 0x2ffu; p.lowerUsage.viRead = 16384; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2948_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2948_3, false>(vu, c);
    }
    struct Kp29A8_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1108bu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29A8_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29A8_2, false>(vu, c);
    }
    struct Kp2A08_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e8213cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2A08_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2A08_1, false>(vu, c);
    }
    struct Kp2BD0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e403bcu; p.upper = 0x1c04280u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {4, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_4, false>(vu, c);
    }
    struct Kp2CB0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x100103eeu; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2CB0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CB0_3, false>(vu, c);
    }
    struct Kp2F30_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_3, false>(vu, c);
    }
    struct Kp2F90_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2F90_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F90_3, false>(vu, c);
    }
    struct Kp2FF0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 5; return p; }();
    };
    bool p2FF0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_2, false>(vu, c);
    }
    struct Kp3268_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x52050003u; p.upper = 0x1c2093du; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3268_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3268_3, false>(vu, c);
    }
    struct Kp32C8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a9cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C8_3, false>(vu, c);
    }
    struct Kp3900_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3900_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3900_3, false>(vu, c);
    }
    struct Kp3960_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3960_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3960_3, false>(vu, c);
    }
    struct Kp39C0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c4d8bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C0_3, false>(vu, c);
    }
    struct Kp3C68_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1093du; p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {1, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C68_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C68_2, false>(vu, c);
    }
    struct Kp3CC8_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e327ffu; p.upper = 0x1eb192bu; p.lowerUsage.vfRead[0] = {4, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 4; return p; }();
    };
    bool p3CC8_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CC8_1, false>(vu, c);
    }
    struct Kp3D28_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x24203eu; p.upperUsage.vfRead[0] = {4, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D28_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D28_3, false>(vu, c);
    }
    struct Kp3D88_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31000u; p.upper = 0x1c1a0bcu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D88_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D88_1, false>(vu, c);
    }
    struct Kp2888_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2888_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2888_5, false>(vu, c);
    }
    struct Kp28E8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28E8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28E8_5, false>(vu, c);
    }
    struct Kp2B98_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_4, false>(vu, c);
    }
    struct Kp2BF8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0299fu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF8_4, false>(vu, c);
    }
    struct Kp3680_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x188393eu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperVfShadowReg = 8; return p; }();
    };
    bool p3680_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3680_3, false>(vu, c);
    }
    struct Kp38F8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F8_4, false>(vu, c);
    }
    struct Kp3958_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3958_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3958_4, false>(vu, c);
    }
    struct Kp3C38_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e2a0bcu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_3, false>(vu, c);
    }
    struct Kp3C98_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c33000u; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {6, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C98_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C98_3, false>(vu, c);
    }
    struct Kp3CF8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x2ffu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CF8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF8_4, false>(vu, c);
    }
    struct Kp2920_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e32fffu; p.upper = 0x1c2093du; p.lowerUsage.vfRead[0] = {5, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {1, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_6, false>(vu, c);
    }
    struct Kp2BC8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x188393eu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC8_5, false>(vu, c);
    }
    struct Kp2C28_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080001u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C28_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C28_5, false>(vu, c);
    }
    struct Kp2C90_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10010419u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2C90_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_5, false>(vu, c);
    }
    struct Kp2F38_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c010dcu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F38_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F38_4, false>(vu, c);
    }
    struct Kp2FC8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8024f33cu; p.upper = 0x1c448bfu; p.lowerUsage.vfRead[0] = {30, 1}; p.lowerUsage.vfWrite = {4, 1}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {4, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FC8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FC8_4, false>(vu, c);
    }
    struct Kp3028_1
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3028_1(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3028_1, false>(vu, c);
    }
    struct Kp3260_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0e90bu; p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3260_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3260_4, false>(vu, c);
    }
    struct Kp32C0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32C0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32C0_4, false>(vu, c);
    }
    struct Kp3320_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_4, false>(vu, c);
    }
    struct Kp3380_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3380_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3380_2, false>(vu, c);
    }
    struct Kp3598_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0b83cu; p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3598_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3598_3, false>(vu, c);
    }
    struct Kp35F8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_3, false>(vu, c);
    }
    struct Kp3658_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e1318bu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {1, 1}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3658_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3658_4, false>(vu, c);
    }
    struct Kp36C0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36C0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36C0_2, false>(vu, c);
    }
    struct Kp3968_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c04a80u; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3968_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3968_5, false>(vu, c);
    }
    struct Kp3CD0_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3CD0_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD0_3, false>(vu, c);
    }
    struct Kp2910_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2910_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2910_7, false>(vu, c);
    }
    struct Kp2C48_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2b0cau; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C48_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C48_4, false>(vu, c);
    }
    struct Kp2FB8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_5, false>(vu, c);
    }
    struct Kp3320_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31800u; p.upper = 0x1e5213cu; p.lowerUsage.vfRead[0] = {3, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_5, false>(vu, c);
    }
    struct Kp35C8_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35C8_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35C8_4, false>(vu, c);
    }
    struct Kp3628_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1e1a0bcu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3628_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3628_4, false>(vu, c);
    }
    struct Kp38D8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x188393eu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_5, false>(vu, c);
    }
    struct Kp3938_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3938_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3938_5, false>(vu, c);
    }
    struct Kp3998_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f781du; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3998_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_4, false>(vu, c);
    }
    struct Kp39F8_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39F8_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39F8_3, false>(vu, c);
    }
    struct Kp3C30_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c31002u; p.upper = 0x1eb31ebu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {6, 15}; p.upperUsage.vfRead[1] = {11, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C30_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C30_4, false>(vu, c);
    }
    struct Kp3C90_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C90_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C90_4, false>(vu, c);
    }
    struct Kp3CF0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e13803u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {7, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3CF0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CF0_5, false>(vu, c);
    }
    struct Kp3D58_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D58_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D58_2, false>(vu, c);
    }
    struct Kp2840_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c5e83eu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {5, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2840_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2840_6, false>(vu, c);
    }
    struct Kp28A0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p28A0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28A0_6, false>(vu, c);
    }
    struct Kp2938_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2938_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2938_5, false>(vu, c);
    }
    struct Kp2998_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507efu; p.upper = 0x1c1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2998_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2998_3, false>(vu, c);
    }
    struct Kp2BD0_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD0_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD0_7, false>(vu, c);
    }
    struct Kp2C30_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507ebu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C30_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C30_4, false>(vu, c);
    }
    struct Kp2C90_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c317feu; p.upper = 0x1c4e0bdu; p.lowerUsage.vfWrite = {3, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C90_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C90_6, false>(vu, c);
    }
    struct Kp2CF0_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800418f0u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 24; p.lowerUsage.viWrite = 8; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CF0_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CF0_2, false>(vu, c);
    }
    struct Kp2F28_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80010870u; p.upper = 0x1c7d9bcu; p.lowerUsage.viRead = 2; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {7, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_5, false>(vu, c);
    }
    struct Kp2F88_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80030070u; p.upper = 0x1e039dfu; p.lowerUsage.viRead = 8; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F88_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F88_4, false>(vu, c);
    }
    struct Kp2FF0_4
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f7826u; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p2FF0_4(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FF0_4, false>(vu, c);
    }
    struct Kp3050_2
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c3193fu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3050_2(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3050_2, false>(vu, c);
    }
    struct Kp3668_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3668_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3668_6, false>(vu, c);
    }
    struct Kp3C18_3
    {
        static constexpr P value = [] { P p{}; p.lower = 0x10080002u; p.upper = 0x2ffu; p.lowerUsage.viWrite = 256; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p3C18_3(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C18_3, false>(vu, c);
    }
    struct Kp3C78_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507f4u; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C78_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C78_5, false>(vu, c);
    }
    struct Kp3CD8_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e1b08au; p.upperUsage.vfRead[0] = {22, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3CD8_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CD8_5, false>(vu, c);
    }
    struct Kp3240_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0299fu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3240_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3240_5, false>(vu, c);
    }
    struct Kp32A0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x120f780fu; p.upper = 0x2ffu; p.lowerUsage.viRead = 32768; p.lowerUsage.viWrite = 32768; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperNop = true; return p; }();
    };
    bool p32A0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_5, false>(vu, c);
    }
    struct Kp3300_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1e4213cu; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3300_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3300_5, false>(vu, c);
    }
    struct Kp35B0_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35B0_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35B0_5, false>(vu, c);
    }
    struct Kp3610_5
    {
        static constexpr P value = [] { P p{}; p.lower = 0x520507edu; p.upper = 0x1e1a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(6); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3610_5(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3610_5, false>(vu, c);
    }
    struct Kp2FB0_6
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1c2b0cau; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB0_6(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB0_6, false>(vu, c);
    }
    struct Kp3320_7
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3320_7(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3320_7, false>(vu, c);
    }
    struct Kp01F8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3a000800u; p.upper = 0x81c2b08au; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p01F8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp01F8_2d, true>(vu, c);
    }
    struct Kp0450_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee5812u; p.upper = 0x1e0a9feu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0450_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0450_2d, true>(vu, c);
    }
    struct Kp0558_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80640b3du; p.upper = 0x260181u; p.lowerUsage.vfRead[0] = {1, 15}; p.lowerUsage.vfWrite = {4, 3}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {6, 4}; p.upperUsage.vfWrite = {6, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0558_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0558_2d, true>(vu, c);
    }
    struct Kp0628_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3ec5052u; p.upper = 0x1f521bcu; p.lowerUsage.vfRead[0] = {10, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 4096; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {21, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0628_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0628_2d, true>(vu, c);
    }
    struct Kp0708_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18a6618u; p.upperUsage.vfRead[0] = {12, 12}; p.upperUsage.vfRead[1] = {10, 8}; p.upperUsage.vfWrite = {24, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0708_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0708_2d, true>(vu, c);
    }
    struct Kp07E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ec1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {12, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p07E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp07E8_2d, true>(vu, c);
    }
    struct Kp0CA0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x8040bd00u; p.upperUsage.vfRead[0] = {23, 2}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {20, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p0CA0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA0_2d, true>(vu, c);
    }
    struct Kp0EF0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1ee5812u; p.upper = 0x1e0a9feu; p.lowerUsage.vfWrite = {14, 15}; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {21, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0EF0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0EF0_2d, true>(vu, c);
    }
    struct Kp0FA8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ed21bcu; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FA8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FA8_2d, true>(vu, c);
    }
    struct Kp1060_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81f4150eu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfRead[1] = {20, 2}; p.upperUsage.vfWrite = {20, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p1060_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1060_2d, true>(vu, c);
    }
    struct Kp10E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ee1abeu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {14, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p10E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp10E0_2d, true>(vu, c);
    }
    struct Kp16C8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x44fff000u; p.upper = 0x8040bd00u; p.upperUsage.vfRead[0] = {23, 2}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {20, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p16C8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp16C8_2d, true>(vu, c);
    }
    struct Kp18B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x38070000u; p.upper = 0x10f0342u; p.lowerUsage.viWrite = 128; p.lowerUsage.latency = 1; p.lowerUsage.readsClip = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {0, 8}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {13, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p18B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp18B8_2d, true>(vu, c);
    }
    struct Kp1A98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c45001u; p.upper = 0x207880u; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 1024; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {15, 1}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A98_2d, true>(vu, c);
    }
    struct Kp1DC0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x103183du; p.upperUsage.vfRead[0] = {3, 12}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 8; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DC0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DC0_2d, true>(vu, c);
    }
    struct Kp20F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c0425cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20F0_2d, true>(vu, c);
    }
    struct Kp22B8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1803a00u; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {7, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {8, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p22B8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp22B8_2d, true>(vu, c);
    }
    struct Kp23E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c32000u; p.upper = 0x180df00u; p.lowerUsage.vfRead[0] = {4, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {27, 12}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfWrite = {28, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p23E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp23E0_2d, true>(vu, c);
    }
    struct Kp24F8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1460b18u; p.upperUsage.vfRead[0] = {1, 10}; p.upperUsage.vfRead[1] = {6, 8}; p.upperUsage.vfWrite = {12, 10}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24F8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24F8_1d, true>(vu, c);
    }
    struct Kp2768_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x20a066u; p.upperUsage.vfRead[0] = {20, 1}; p.upperUsage.vfWrite = {1, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2768_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2768_1d, true>(vu, c);
    }
    struct Kp29E0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d08au; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E0_2d, true>(vu, c);
    }
    struct Kp2C50_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C50_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C50_7d, true>(vu, c);
    }
    struct Kp3248_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3248_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3248_6d, true>(vu, c);
    }
    struct Kp3348_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3348_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3348_5d, true>(vu, c);
    }
    struct Kp35D8_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0109cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_6d, true>(vu, c);
    }
    struct Kp36C0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36C0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36C0_3d, true>(vu, c);
    }
    struct Kp3930_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x80210bfdu; p.upper = 0x1e0e9cbu; p.lowerUsage.vfWrite = {1, 1}; p.lowerUsage.viRead = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {29, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfWrite = {7, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_6d, true>(vu, c);
    }
    struct Kp3A18_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0b83cu; p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A18_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A18_3d, true>(vu, c);
    }
    struct Kp3A80_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A80_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A80_1d, true>(vu, c);
    }
    struct Kp0298_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0xa0ffdeu; p.upperUsage.vfRead[0] = {31, 5}; p.upperUsage.vfWrite = {31, 5}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0298_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0298_2d, true>(vu, c);
    }
    struct Kp06C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1ff1a0bu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {31, 1}; p.upperUsage.vfWrite = {8, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p06C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp06C0_2d, true>(vu, c);
    }
    struct Kp0888_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x8002fcu; p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 4; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0888_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0888_2d, true>(vu, c);
    }
    struct Kp0998_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087133du; p.upper = 0x634999u; p.lowerUsage.vfRead[0] = {2, 15}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {9, 3}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfWrite = {6, 3}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0998_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0998_2d, true>(vu, c);
    }
    struct Kp0A38_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0026cu; p.upperUsage.vfRead[0] = {0, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0A38_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0A38_2d, true>(vu, c);
    }
    struct Kp0AD0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0AD0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0AD0_2d, true>(vu, c);
    }
    struct Kp0B68_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e428bcu; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0B68_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0B68_2d, true>(vu, c);
    }
    struct Kp0C40_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x5f39c4u; p.upperUsage.vfRead[0] = {7, 2}; p.upperUsage.vfRead[1] = {31, 8}; p.upperUsage.vfWrite = {7, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0C40_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0C40_2d, true>(vu, c);
    }
    struct Kp0CA8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0103cu; p.upperUsage.vfRead[0] = {2, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0CA8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0CA8_3d, true>(vu, c);
    }
    struct Kp0DF0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x38c606u; p.upperUsage.vfRead[0] = {24, 3}; p.upperUsage.vfWrite = {24, 1}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0DF0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0DF0_2d, true>(vu, c);
    }
    struct Kp0FC0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1c0bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p0FC0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp0FC0_3d, true>(vu, c);
    }
    struct Kp1028_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e519bfu; p.upperUsage.vfRead[0] = {3, 15}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1028_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1028_2d, true>(vu, c);
    }
    struct Kp1180_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e9bfu; p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1180_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1180_3d, true>(vu, c);
    }
    struct Kp12D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p12D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp12D8_2d, true>(vu, c);
    }
    struct Kp1398_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3eb1804u; p.upper = 0x18798adu; p.lowerUsage.vfRead[0] = {3, 15}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 2048; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1398_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1398_2d, true>(vu, c);
    }
    struct Kp14C0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2f0bdau; p.upperUsage.vfRead[0] = {1, 1}; p.upperUsage.vfRead[1] = {15, 2}; p.upperUsage.vfWrite = {15, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p14C0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp14C0_2d, true>(vu, c);
    }
    struct Kp1588_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0127fu; p.upperUsage.vfRead[0] = {2, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1588_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1588_2d, true>(vu, c);
    }
    struct Kp15F0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e03a5eu; p.upperUsage.vfRead[0] = {7, 15}; p.upperUsage.vfWrite = {9, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p15F0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp15F0_2d, true>(vu, c);
    }
    struct Kp1668_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8101933cu; p.upper = 0x18798a9u; p.lowerUsage.vfRead[0] = {18, 8}; p.lowerUsage.vfWrite = {1, 8}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {19, 12}; p.upperUsage.vfRead[1] = {7, 12}; p.upperUsage.vfWrite = {2, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 12; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1668_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1668_2d, true>(vu, c);
    }
    struct Kp1788_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e2c1bcu; p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1788_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1788_2d, true>(vu, c);
    }
    struct Kp1800_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1800_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1800_2d, true>(vu, c);
    }
    struct Kp1860_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x29024eu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {9, 2}; p.upperUsage.vfWrite = {9, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1860_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1860_2d, true>(vu, c);
    }
    struct Kp1A90_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1A90_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1A90_3d, true>(vu, c);
    }
    struct Kp1AF0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0183cu; p.upperUsage.vfRead[0] = {3, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1AF0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1AF0_3d, true>(vu, c);
    }
    struct Kp1B50_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x2701ceu; p.upperUsage.vfRead[0] = {0, 1}; p.upperUsage.vfRead[1] = {7, 2}; p.upperUsage.vfWrite = {7, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1B50_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1B50_3d, true>(vu, c);
    }
    struct Kp1C98_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c8e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {8, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1C98_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1C98_2d, true>(vu, c);
    }
    struct Kp1DD8_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1d0beu; p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1DD8_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1DD8_3d, true>(vu, c);
    }
    struct Kp1E88_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e22928u; p.upperUsage.vfRead[0] = {5, 15}; p.upperUsage.vfRead[1] = {2, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1E88_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1E88_2d, true>(vu, c);
    }
    struct Kp1FB8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e2e3bcu; p.upper = 0x1c2e9bfu; p.lowerUsage.vfRead[0] = {28, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {29, 14}; p.upperUsage.vfRead[1] = {2, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p1FB8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp1FB8_2d, true>(vu, c);
    }
    struct Kp20D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x18328e8u; p.upperUsage.vfRead[0] = {5, 12}; p.upperUsage.vfRead[1] = {3, 12}; p.upperUsage.vfWrite = {3, 12}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p20D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp20D0_2d, true>(vu, c);
    }
    struct Kp21D8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1eba1bcu; p.upperUsage.vfRead[0] = {20, 15}; p.upperUsage.vfRead[1] = {11, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p21D8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp21D8_2d, true>(vu, c);
    }
    struct Kp2308_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0d83cu; p.upperUsage.vfRead[0] = {27, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2308_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2308_2d, true>(vu, c);
    }
    struct Kp2400_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3e800000u; p.upper = 0x81e008ffu; p.upperUsage.vfRead[0] = {1, 15}; p.upperUsage.vfRead[1] = {0, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2400_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2400_2d, true>(vu, c);
    }
    struct Kp2470_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3fd744fdu; p.upper = 0x81e02163u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 1; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p2470_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2470_2d, true>(vu, c);
    }
    struct Kp24D0_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8087033cu; p.upper = 0x850304u; p.lowerUsage.vfRead[0] = {0, 4}; p.lowerUsage.vfWrite = {7, 4}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.upperUsage.vfRead[0] = {0, 4}; p.upperUsage.vfRead[1] = {5, 8}; p.upperUsage.vfWrite = {12, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p24D0_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp24D0_2d, true>(vu, c);
    }
    struct Kp28C8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0d83cu; p.upperUsage.vfRead[0] = {27, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28C8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28C8_7d, true>(vu, c);
    }
    struct Kp2BC0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c2e0a9u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {2, 14}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BC0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BC0_7d, true>(vu, c);
    }
    struct Kp2D30_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2D30_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2D30_1d, true>(vu, c);
    }
    struct Kp2F20_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F20_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F20_7d, true>(vu, c);
    }
    struct Kp3008_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e0f83cu; p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3008_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3008_4d, true>(vu, c);
    }
    struct Kp30C8_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c31004u; p.upper = 0x1e390beu; p.lowerUsage.vfRead[0] = {2, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p30C8_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp30C8_1d, true>(vu, c);
    }
    struct Kp32A0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e3c8bdu; p.upperUsage.vfRead[0] = {25, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_6d, true>(vu, c);
    }
    struct Kp3388_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1a8bdu; p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {1, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3388_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3388_3d, true>(vu, c);
    }
    struct Kp3400_1d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3400_1d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3400_1d, true>(vu, c);
    }
    struct Kp3670_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x3c34001u; p.upper = 0x1c2b0cau; p.lowerUsage.vfRead[0] = {8, 14}; p.lowerUsage.vfReadCount = 1; p.lowerUsage.viRead = 8; p.lowerUsage.latency = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {2, 2}; p.upperUsage.vfWrite = {3, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3670_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3670_8d, true>(vu, c);
    }
    struct Kp3920_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3920_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3920_7d, true>(vu, c);
    }
    struct Kp3D60_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D60_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D60_3d, true>(vu, c);
    }
    struct Kp2898_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_8d, true>(vu, c);
    }
    struct Kp3D08_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D08_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D08_8d, true>(vu, c);
    }
    struct Kp28B0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p28B0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp28B0_9d, true>(vu, c);
    }
    struct Kp2B98_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_9d, true>(vu, c);
    }
    struct Kp2C08_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2C08_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2C08_7d, true>(vu, c);
    }
    struct Kp2CF0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CF0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CF0_3d, true>(vu, c);
    }
    struct Kp2FB8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c0b83cu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {23, 14}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2FB8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2FB8_8d, true>(vu, c);
    }
    struct Kp35D8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e303bcu; p.upper = 0x1c0215cu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {3, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {4, 14}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35D8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35D8_7d, true>(vu, c);
    }
    struct Kp38F0_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38F0_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38F0_7d, true>(vu, c);
    }
    struct Kp3C38_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1c5e149u; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {5, 4}; p.upperUsage.vfWrite = {5, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C38_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C38_7d, true>(vu, c);
    }
    struct Kp3D38_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e72129u; p.upperUsage.vfRead[0] = {4, 15}; p.upperUsage.vfRead[1] = {7, 15}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D38_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D38_5d, true>(vu, c);
    }
    struct Kp2898_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x81e203bcu; p.upper = 0x27383eu; p.lowerUsage.vfRead[0] = {0, 1}; p.lowerUsage.vfRead[1] = {2, 1}; p.lowerUsage.vfReadCount = 2; p.lowerUsage.latency = 7; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(3); p.upperUsage.vfRead[0] = {7, 3}; p.upperUsage.vfReadCount = 1; p.upperUsage.accWrite = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2898_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2898_10d, true>(vu, c);
    }
    struct Kp2978_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1708au; p.upperUsage.vfRead[0] = {14, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2978_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2978_5d, true>(vu, c);
    }
    struct Kp29E8_2d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p29E8_2d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp29E8_2d, true>(vu, c);
    }
    struct Kp2F30_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11000u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F30_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F30_7d, true>(vu, c);
    }
    struct Kp38D8_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c417feu; p.upper = 0x1c548bfu; p.lowerUsage.vfWrite = {4, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfRead[1] = {5, 1}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p38D8_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp38D8_9d, true>(vu, c);
    }
    struct Kp39C8_5d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c4e109u; p.upperUsage.vfRead[0] = {28, 14}; p.upperUsage.vfRead[1] = {4, 4}; p.upperUsage.vfWrite = {4, 14}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39C8_5d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39C8_5d, true>(vu, c);
    }
    struct Kp3CA0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3CA0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3CA0_6d, true>(vu, c);
    }
    struct Kp2848_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2848_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2848_9d, true>(vu, c);
    }
    struct Kp2BD8_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BD8_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BD8_8d, true>(vu, c);
    }
    struct Kp39B0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p39B0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp39B0_9d, true>(vu, c);
    }
    struct Kp2B98_11d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x800410b0u; p.upper = 0x1c04a9cu; p.lowerUsage.viRead = 20; p.lowerUsage.viWrite = 4; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {9, 14}; p.upperUsage.vfWrite = {10, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2B98_11d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2B98_11d, true>(vu, c);
    }
    struct Kp2F28_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e481bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {4, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F28_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F28_6d, true>(vu, c);
    }
    struct Kp3010_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x437f8000u; p.upper = 0x81e390cau; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {3, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p3010_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3010_4d, true>(vu, c);
    }
    struct Kp32A0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e388bdu; p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32A0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32A0_8d, true>(vu, c);
    }
    struct Kp3588_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e1708au; p.upperUsage.vfRead[0] = {14, 15}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfWrite = {2, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3588_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3588_7d, true>(vu, c);
    }
    struct Kp35F8_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e41003u; p.upper = 0x1e3d18au; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {26, 15}; p.upperUsage.vfRead[1] = {3, 2}; p.upperUsage.vfWrite = {6, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35F8_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35F8_7d, true>(vu, c);
    }
    struct Kp36E0_3d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c1b0beu; p.upperUsage.vfRead[0] = {22, 14}; p.upperUsage.vfRead[1] = {1, 2}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p36E0_3d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp36E0_3d, true>(vu, c);
    }
    struct Kp2920_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1861001u; p.upper = 0x1c2a0bcu; p.lowerUsage.vfWrite = {6, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {2, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2920_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2920_10d, true>(vu, c);
    }
    struct Kp35A0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e417ffu; p.upper = 0x1e4f169u; p.lowerUsage.vfWrite = {4, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {30, 15}; p.upperUsage.vfRead[1] = {4, 15}; p.upperUsage.vfWrite = {5, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p35A0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35A0_9d, true>(vu, c);
    }
    struct Kp3930_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3930_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3930_8d, true>(vu, c);
    }
    struct Kp3A18_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3A18_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3A18_4d, true>(vu, c);
    }
    struct Kp3C88_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3C88_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3C88_8d, true>(vu, c);
    }
    struct Kp3D70_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3D70_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3D70_4d, true>(vu, c);
    }
    struct Kp2870_10d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1e717ffu; p.upper = 0x1e0f83cu; p.lowerUsage.vfWrite = {7, 15}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {31, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2870_10d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2870_10d, true>(vu, c);
    }
    struct Kp2960_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1e381bcu; p.upperUsage.vfRead[0] = {16, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2960_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2960_6d, true>(vu, c);
    }
    struct Kp2BF0_9d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8000033cu; p.upper = 0x1c0425cu; p.upperUsage.vfRead[0] = {8, 14}; p.upperUsage.vfWrite = {9, 14}; p.upperUsage.vfReadCount = 1; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2BF0_9d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2BF0_9d, true>(vu, c);
    }
    struct Kp2CD8_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1e388bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {17, 15}; p.upperUsage.vfRead[1] = {3, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2CD8_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2CD8_4d, true>(vu, c);
    }
    struct Kp2F48_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1c11004u; p.upper = 0x1e3c1bcu; p.lowerUsage.vfWrite = {1, 14}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {24, 15}; p.upperUsage.vfRead[1] = {3, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p2F48_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp2F48_8d, true>(vu, c);
    }
    struct Kp3030_4d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x8211004u; p.upper = 0x1c1a0bcu; p.lowerUsage.viRead = 4; p.lowerUsage.viWrite = 2; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {20, 14}; p.upperUsage.vfRead[1] = {1, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3030_4d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3030_4d, true>(vu, c);
    }
    struct Kp3998_7d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x12052801u; p.upper = 0x1c2a8bdu; p.lowerUsage.viRead = 32; p.lowerUsage.viWrite = 32; p.lowerUsage.latency = 1; p.lowerUsage.delaysNextBranchRead = 1; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(5); p.upperUsage.vfRead[0] = {21, 14}; p.upperUsage.vfRead[1] = {2, 4}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 14; p.upperUsage.accWrite = 14; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p3998_7d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp3998_7d, true>(vu, c);
    }
    struct Kp32D0_6d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x1871001u; p.upper = 0x1e0b83cu; p.lowerUsage.vfWrite = {7, 12}; p.lowerUsage.viRead = 4; p.lowerUsage.latency = 4; p.lowerUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(2); p.upperUsage.vfRead[0] = {23, 15}; p.upperUsage.vfRead[1] = {0, 8}; p.upperUsage.vfReadCount = 2; p.upperUsage.accWrite = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); return p; }();
    };
    bool p32D0_6d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp32D0_6d, true>(vu, c);
    }
    struct Kp35E0_8d
    {
        static constexpr P value = [] { P p{}; p.lower = 0x4b0000ffu; p.upper = 0x81e4910au; p.upperUsage.vfRead[0] = {18, 15}; p.upperUsage.vfRead[1] = {4, 2}; p.upperUsage.vfWrite = {4, 15}; p.upperUsage.vfReadCount = 2; p.upperUsage.accRead = 15; p.upperUsage.latency = 4; p.upperUsage.pipeline = static_cast<VU1CompiledAccess::Pipeline>(1); p.iBit = true; return p; }();
    };
    bool p35E0_8d(VU1Interpreter &vu, C &c)
    {
        return VU1CompiledAccess::step<Kp35E0_8d, true>(vu, c);
    }
}

#if defined(_MSC_VER)
#pragma float_control(pop)
#endif
