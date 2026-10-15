#pragma once
#include <cstdint>
#include <functional>

// Debug aid: log the guest pc/ra of every write to an EE RAM range (Windows only; no-op elsewhere).
namespace eewatch
{
    using GuestPcProvider = std::function<void(uint32_t &pc, uint32_t &ra)>;
    void install(uint8_t *rdram, uint32_t guestAddress, uint32_t length, GuestPcProvider provider);
}
