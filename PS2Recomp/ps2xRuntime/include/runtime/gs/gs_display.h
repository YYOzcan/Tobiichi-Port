#pragma once
// GOW-Port: native display and GS-status service (no-emulation step 5, docs/native-port.md).
// The game's display setup and its GS FINISH handshake are native calls on this interface instead of
// stores/loads to the GS privileged registers (0x12000000 / 0x12001000). The state lives in the GS state
// block (PS2Memory::gs()) that GS::buildPresentationRequestUnlocked copies into each Present request.
// Kept out of the precompiled header on purpose.
#include <cstdint>

class PS2Memory;

// What the two CRTC read circuits show: the values the GS display registers would hold (same bit layout,
// so the presentation code decodes them unchanged).
struct GSDisplayState
{
    uint64_t pmode = 0;    // EN1/EN2, MMOD, AMOD, SLBG, ALP (circuit merge)
    uint64_t smode2 = 0;   // INT (interlace), FFMD (field mode)
    uint64_t dispfb1 = 0;  // circuit 1 frame buffer (FBP, FBW, PSM, DBX, DBY)
    uint64_t display1 = 0; // circuit 1 display area (DX, DY, MAGH, MAGV, DW, DH)
    uint64_t dispfb2 = 0;
    uint64_t display2 = 0;
    uint64_t bgcolor = 0;
};

namespace ps2_gs_display
{
    // Takes effect for the next presentation, after the GS worker drew everything queued before the call
    // (the same ordering the register writes had).
    void setDisplay(PS2Memory &memory, const GSDisplayState &state);
    GSDisplayState display(const PS2Memory &memory);

    // GS status (CSR: FIELD, FINISH, ...), as the game's display code reads it.
    uint64_t status(PS2Memory &memory);

    // GS FINISH event (raised by the FINISH register in the game's GIF packets; delivered as INTC 0 while
    // unmasked in IMR): pending test and acknowledge.
    bool finishPending(PS2Memory &memory);
    void ackFinish(PS2Memory &memory);
}
