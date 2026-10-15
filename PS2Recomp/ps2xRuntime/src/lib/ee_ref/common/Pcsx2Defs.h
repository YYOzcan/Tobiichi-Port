// Shim for PCSX2 common/Pcsx2Defs.h (types and attributes only).
#pragma once
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using uint = unsigned int;
union alignas(16) u128
{
    struct { u64 lo, hi; };
    u64 _u64[2];
    u32 _u32[4];
    u16 _u16[8];
    u8 _u8[16];
};
union alignas(16) s128
{
    struct { s64 lo, hi; };
    s64 _s64[2];
    s32 _s32[4];
};

#if defined(_MSC_VER)
#define __fi __forceinline
#define __noinline __declspec(noinline)
#else
#define __fi inline __attribute__((always_inline))
#define __noinline __attribute__((noinline))
#endif
#define __ri inline
#define pxAssert(c) ((void)0)
#define pxAssume(c) ((void)0)
#define pxFail(m) ((void)0)
#define jNO_DEFAULT default: break;
#define CPU_LOG(...) ((void)0)
#define COP0_LOG(...) ((void)0)
#define MMI_LOG(...) ((void)0)
struct EeRefLogShim
{
    template <typename... A> void WriteLn(A &&...) const {}
    template <typename... A> void Warning(A &&...) const {}
    template <typename... A> void Error(A &&...) const {}
};
inline constexpr EeRefLogShim Console{};
inline constexpr EeRefLogShim DevCon{};
inline constexpr EeRefLogShim DbgCon{};
