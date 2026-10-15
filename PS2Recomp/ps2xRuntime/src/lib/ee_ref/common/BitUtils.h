// Shim for PCSX2 common/BitUtils.h (only what MMI.cpp uses).
#pragma once
#include "common/Pcsx2Defs.h"
namespace Common
{
    __fi static u32 CountLeadingSignBits(s32 n)
    {
        if (n < 0)
            n = ~n; // sign bit set: count leading ones as zeros
        if (n == 0)
            return 32;
        return static_cast<u32>(std::countl_zero(static_cast<u32>(n)));
    }
}
