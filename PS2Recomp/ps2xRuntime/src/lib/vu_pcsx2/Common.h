// Shim replacing PCSX2's Common.h for the borrowed VU1 interpreter (VUops.cpp, VUflags.cpp, VU1microInterp.cpp).
// Only what those files use. PCSX2 code is GPL-3.0+.
#pragma once

#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using uint = unsigned int;

#if !defined(__cpp_lib_bit_cast)
namespace std
{
    template <typename To, typename From>
    inline To bit_cast(const From &from) noexcept
    {
        static_assert(sizeof(To) == sizeof(From), "bit_cast size mismatch");
        To to;
        std::memcpy(&to, &from, sizeof(To));
        return to;
    }
}
#endif
struct alignas(16) u128 { u64 lo, hi; };
struct alignas(16) s128 { s64 lo, hi; };

#if defined(_MSC_VER)
#define __fi __forceinline
#else
#define __fi inline __attribute__((always_inline))
#endif
#define __ri inline

#define pxFail(msg) ((void)0)
#define pxAssert(cond) ((void)0)
#define pxAssume(cond) ((void)0)
#define jNO_DEFAULT \
    default:        \
        break;

struct Pcsx2LogShim
{
    template <typename... Args> void WriteLn(Args &&...) const {}
    template <typename... Args> void Warning(Args &&...) const {}
    template <typename... Args> void Error(Args &&...) const {}
};
inline constexpr Pcsx2LogShim Console{};
inline constexpr Pcsx2LogShim DevCon{};
inline constexpr Pcsx2LogShim DbgCon{};
#define VUM_LOG(...) ((void)0)

// Configuration the interpreter consults: PCSX2 defaults (no overflow clamping hack, no add/sub hack).
#define CHECK_VU_OVERFLOW(vu) (false)
#define CHECK_VUADDSUBHACK (false)
#define CHECK_XGKICKHACK (false)
#define INSTANT_VU1 (true)
#define THREAD_VU1 (false)
#define REC_VU1 (false)

enum
{
    INTC_VU1 = 15,
    DMAC_VIF1 = 1,
};
inline void hwIntcIrq(int) {}
inline void CPU_INT(int, int) {}

#define CPU_LOG(...) ((void)0)

// PCSX2's R5900 register file: the VU interpreter only reads cpuRegs.code (VU0 macro mode) and cpuRegs.cycle.
struct Pcsx2CpuRegsShim
{
    u32 code;
    u32 cycle;
};
extern Pcsx2CpuRegsShim cpuRegs;
