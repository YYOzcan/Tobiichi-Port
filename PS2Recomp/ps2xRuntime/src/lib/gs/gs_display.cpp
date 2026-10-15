// GOW-Port: native display and GS-status service (see runtime/gs/gs_display.h).
#include "runtime/gs/gs_display.h"
#include "runtime/ps2_memory.h"

namespace ps2_gs_display
{
    namespace
    {
        // Only used to attribute the GS worker barrier (PS2X_GS_WORKER_DIAG) like the register accesses did.
        constexpr uint32_t kDisplaySite = 0x12000000u;
        constexpr uint32_t kStatusSite = 0x12001000u;
        constexpr uint64_t kFinish = 0x2ull;
    }

    void setDisplay(PS2Memory &memory, const GSDisplayState &state)
    {
        memory.syncGsWorkerFor(kDisplaySite);
        GSRegisters &gs = memory.gs();
        gs.pmode = state.pmode;
        gs.smode2 = state.smode2;
        gs.dispfb1 = state.dispfb1;
        gs.display1 = state.display1;
        gs.dispfb2 = state.dispfb2;
        gs.display2 = state.display2;
        gs.bgcolor = state.bgcolor;
    }

    GSDisplayState display(const PS2Memory &memory)
    {
        const GSRegisters &gs = memory.gs();
        GSDisplayState state;
        state.pmode = gs.pmode;
        state.smode2 = gs.smode2;
        state.dispfb1 = gs.dispfb1;
        state.display1 = gs.display1;
        state.dispfb2 = gs.dispfb2;
        state.display2 = gs.display2;
        state.bgcolor = gs.bgcolor;
        return state;
    }

    uint64_t status(PS2Memory &memory)
    {
        memory.syncGsWorkerFor(kStatusSite);
        return memory.gs().csr.load(std::memory_order_acquire);
    }

    bool finishPending(PS2Memory &memory)
    {
        memory.syncGsWorkerFor(kStatusSite);
        return (memory.gs().csr.load(std::memory_order_acquire) & kFinish) != 0u;
    }

    void ackFinish(PS2Memory &memory)
    {
        memory.syncGsWorkerFor(kStatusSite);
        memory.gs().csr.fetch_and(~kFinish, std::memory_order_acq_rel);
    }
}
