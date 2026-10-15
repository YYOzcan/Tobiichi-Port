#pragma once

#include <cstdint>
#include <functional>

// Runs VU1 microprograms on PCSX2's VU1 interpreter (vu_pcsx2/, GPL-3.0+) instead of our own VU1Interpreter.
// Default; PS2X_VU1_LEGACY=1 selects the old VU1Interpreter. The PCSX2 VU1 register file persists across calls, like the real VU1.
namespace pcsx2vu1
{
    bool enabled();

    struct RunResult
    {
        bool stoppedByD = false;
        bool stoppedByT = false;
        bool finished = false; // reached the E-bit (or a D/T stop)
    };

    using SubmitPath1 = std::function<void(const uint8_t *packet, uint32_t sizeBytes)>;

    // startPc: byte address to start at (MSCAL), or -1 to continue from the current TPC (MSCNT).
    RunResult run(uint8_t *microMem, uint8_t *dataMem, int64_t startPc, uint32_t top, uint32_t itop,
                  bool dBitEnabled, bool tBitEnabled, uint64_t maxCycles, const SubmitPath1 &submit);
}
