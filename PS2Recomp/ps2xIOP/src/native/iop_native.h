#pragma once

// GOW-Port: IRX modules compiled ahead of time to native code (tools/iop/iopn_gen.py, docs/native-port.md).
// Each generated module is the image of one IRX as loaded (relocated) at a fixed base; it is used only when the module
// is loaded at that base with the same code bytes (FNV-1a hash of the text section).

#include <cstddef>
#include <cstdint>

namespace ps2x::iop
{
    class IopHost;
}

namespace ps2x::iop::detail
{
    struct IopCpuState;
    class IopMemory;

    class SoundEngine;

    // services of the IOP runtime available to native overrides
    class IopNativeServices
    {
    public:
        virtual ~IopNativeServices() = default;
        // runs the guest function `function(a0, a1)` (with `gp`) after `delayCycles` IOP cycles, like an interrupt
        // handler (used to report transfer completion to the game's driver)
        virtual void callGuestLater(uint32_t function, uint32_t gp, uint32_t a0, uint32_t a1, uint64_t delayCycles) = 0;
        virtual SoundEngine &sound() = 0;
    };

    struct IopNativeCall
    {
        IopCpuState &cpu;
        IopMemory &memory;
        IopHost &host;
        IopNativeServices &services;
    };

    // An IRX function replaced by native C++ (tools/iop/native_overrides.txt lists the same addresses for the code
    // generator). Called like the function: arguments in $a0-$a3 (stack args at $sp+16), result in $v0; the caller
    // then returns to $ra.
    struct IopNativeOverride
    {
        const char *module; // module identifier as in the dumps (e.g. "mc2_d_irx")
        uint32_t offset;    // from the module base
        const char *name;
        void (*handler)(IopNativeCall &call);
    };

    // src/native/iop_native_overrides.cpp
    const IopNativeOverride *iopNativeOverrides(size_t &count);

    struct IopNativeModule
    {
        const char *name;
        uint32_t base;     // physical load address
        uint32_t textSize; // bytes of code covered
        uint64_t hash;     // iopNativeHash of those bytes
        // Runs compiled code from cpu.pc (inside the module, not in a branch delay slot) and returns the number of
        // instructions executed. Returns when the code reaches an import stub (cpu.pc = the stub, not executed), jumps
        // out of the module, raises an exception or has executed at least `budget` instructions.
        uint32_t (*run)(IopCpuState &cpu, IopMemory &memory, uint32_t budget);
    };

    // generated registry (src/native/iopn_registry.cpp)
    const IopNativeModule *iopNativeModules(size_t &count);

    inline uint64_t iopNativeHash(const uint8_t *data, size_t size)
    {
        uint64_t h = 1469598103934665603ull;
        for (size_t i = 0; i < size; ++i)
            h = (h ^ data[i]) * 1099511628211ull;
        return h;
    }
}
