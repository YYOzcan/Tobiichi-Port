#pragma once
// Glue between the borrowed PCSX2 EE interpreter and our differential tester (eeref.cpp).
#include "common/Pcsx2Defs.h"

namespace eeref
{
    void stop(const char *reason);
    void cop2(u32 code);
}

u8 memRead8(u32 addr);
u16 memRead16(u32 addr);
u32 memRead32(u32 addr);
u64 memRead64(u32 addr);
void memRead128(u32 addr, u128 &out);
inline void memRead128(u32 addr, u128 *out) { memRead128(addr, *out); }
void memWrite8(u32 addr, u8 value);
void memWrite16(u32 addr, u16 value);
void memWrite32(u32 addr, u32 value);
void memWrite64(u32 addr, u64 value);
void memWrite128(u32 addr, const u128 &value);
inline void memWrite128(u32 addr, const u128 *value) { memWrite128(addr, *value); }
void cpuException(u32 code, u32 branch);
void intUpdateCPUCycles();
void intEventTest();
void intDoBranch(u32 target);
void intSetBranch();

struct EeRefConfig
{
    struct { bool GoemonTlbHack = false; } Gamefixes;
    struct { bool WaitLoop = false; } Speedhacks;
};
inline EeRefConfig EmuConfig{};
