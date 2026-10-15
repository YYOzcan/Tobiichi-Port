#pragma once
// EE differential tester: runs a guest function on PCSX2's R5900 interpreter (GPL-3.0+) from a snapshot and
// compares the result with what our recompiled code produced. Plain types only (no PCSX2 / runtime headers).
#include <cstdint>
#include <string>
#include <vector>

namespace eeref
{
    struct CpuSnapshot
    {
        uint64_t gpr[32][2];
        uint64_t hi, lo, hi1, lo1;
        uint32_t sa;
        uint32_t f[32];
        uint32_t facc;
        uint32_t fcr31;
        uint32_t vf[32][4];
        uint16_t vi[16];
        uint32_t acc[4];
        uint32_t q;
        uint32_t p, i, r, status, mac, clip; // GOW-Port: VU0 control state (compared after each call)
    };

    struct Result
    {
        bool completed = false; // reached the return address with the entry stack pointer
        std::string stopReason; // why the reference run stopped early
        uint64_t steps = 0;
        std::vector<std::string> differences;
    };

    // ram: 32 MB EE RAM and scratch: 16 KB scratchpad as they were at function entry.
    Result run(const CpuSnapshot &before, const uint8_t *ram, const uint8_t *scratch, uint32_t entryPc,
               uint32_t returnPc, const CpuSnapshot &after, const uint8_t *ramAfter, const uint8_t *scratchAfter,
               uint64_t maxSteps);
}
