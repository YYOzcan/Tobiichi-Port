// Shim for PCSX2's Vif.h: the VU interpreter reads TOP/ITOP (XTOP/XITOP) and two STAT bits.
#pragma once
#include "Common.h"
struct VIFregisters
{
    struct
    {
        bool VEW;
        bool VGW;
    } stat;
    u32 top;
    u32 itop;
};
extern VIFregisters vif0Regs;
extern VIFregisters vif1Regs;
