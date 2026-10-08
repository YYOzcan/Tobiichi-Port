// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include <cstdint>

namespace GSSharedPresent
{
    struct Frame
    {
        uint32_t texture = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        uint64_t sequence = 0;
        uint64_t renderSequence = 0;
        uint64_t contentHash = 0;
        bool hashValid = false;
    };

    void CaptureHostContext();
    void RestoreHostContext();
    bool Active();
    bool Acquire(Frame &frame);
    void ShutdownHost();
}
