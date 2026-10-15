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
        // GOW-Port: conservar la selección CRTC sin descargar la imagen al host.
        uint32_t displayFbp = 0;
        uint32_t sourceFbp = 0;
        bool usedPreferred = false;
        // GOW-Port: los diagnósticos usan el tick de esta imagen, no otro request posterior.
        uint64_t vsyncTick = 0;
        // GOW-Port: PMODE apagado equivale a PresentationFrame vacío para el host.
        bool blank = false;
    };

    void CaptureHostContext();
    void RestoreHostContext();
    bool Active();
    bool Acquire(Frame &frame);
    void ShutdownHost();
}
