// Shim for PCSX2's VUmicro.h: only the interpreter entry points.
#pragma once
#include "VU.h"
#include "VUops.h"
#include "R5900.h"
extern void vu1Exec(VURegs *VU);
#define IdebugUPPER(VU)
#define IdebugLOWER(VU)
