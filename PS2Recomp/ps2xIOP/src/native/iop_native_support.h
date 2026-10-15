#pragma once

// GOW-Port: helpers for the generated IRX code (tools/iop/iopn_gen.py). Each one is the exact counterpart of the same
// case in iopExecute (emulator/core/iop_cpu_exec.h).

#include "emulator/core/iop_cpu_exec.h"
#include "emulator/core/iop_memory.h"
#include "native/iop_native.h"

#include <cstdint>
#include <limits>

namespace ps2x::iop::detail
{
    inline constexpr uint32_t kLwlMask[4] = {0x00FFFFFFu, 0x0000FFFFu, 0x000000FFu, 0x00000000u};
    inline constexpr uint32_t kLwlShift[4] = {24u, 16u, 8u, 0u};
    inline constexpr uint32_t kLwrMask[4] = {0x00000000u, 0xFF000000u, 0xFFFF0000u, 0xFFFFFF00u};
    inline constexpr uint32_t kLwrShift[4] = {0u, 8u, 16u, 24u};

    inline void iopDiv(IopCpuState &cpu, uint32_t a, uint32_t b)
    {
        const int32_t lhs = static_cast<int32_t>(a), rhs = static_cast<int32_t>(b);
        if (rhs == 0)
        {
            cpu.lo = lhs >= 0 ? 0xFFFFFFFFu : 1u;
            cpu.hi = static_cast<uint32_t>(lhs);
        }
        else if (lhs == std::numeric_limits<int32_t>::min() && rhs == -1)
        {
            cpu.lo = static_cast<uint32_t>(lhs);
            cpu.hi = 0u;
        }
        else
        {
            cpu.lo = static_cast<uint32_t>(lhs / rhs);
            cpu.hi = static_cast<uint32_t>(lhs % rhs);
        }
    }

    inline void iopDivu(IopCpuState &cpu, uint32_t a, uint32_t b)
    {
        if (b == 0u)
        {
            cpu.lo = 0xFFFFFFFFu;
            cpu.hi = a;
        }
        else
        {
            cpu.lo = a / b;
            cpu.hi = a % b;
        }
    }

    inline void iopSwl(IopMemory &memory, uint32_t address, uint32_t value)
    {
        const uint32_t aligned = address & ~3u, old = memory.load32(aligned);
        uint32_t result = old;
        switch (address & 3u)
        {
        case 0u: result = (old & 0xFFFFFF00u) | (value >> 24u); break;
        case 1u: result = (old & 0xFFFF0000u) | (value >> 16u); break;
        case 2u: result = (old & 0xFF000000u) | (value >> 8u); break;
        case 3u: result = value; break;
        }
        memory.store32(aligned, result);
    }

    inline void iopSwr(IopMemory &memory, uint32_t address, uint32_t value)
    {
        const uint32_t aligned = address & ~3u, old = memory.load32(aligned);
        uint32_t result = old;
        switch (address & 3u)
        {
        case 0u: result = value; break;
        case 1u: result = (old & 0x000000FFu) | (value << 8u); break;
        case 2u: result = (old & 0x0000FFFFu) | (value << 16u); break;
        case 3u: result = (old & 0x00FFFFFFu) | (value << 24u); break;
        }
        memory.store32(aligned, result);
    }
}
