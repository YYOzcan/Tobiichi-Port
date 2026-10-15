// Shim for PCSX2's MTVU.h: no VU1 thread.
#pragma once
#include "Vif.h"
struct Pcsx2Vu1ThreadShim
{
    VIFregisters vifRegs;
};
extern Pcsx2Vu1ThreadShim vu1Thread;
