#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace gow_pad2
{
    // libpad2 payload: wire-order buttons, RX/RY/LX/LY, then twelve pressures.
    inline std::array<uint8_t, 18> makePacket(const uint8_t (&state)[32])
    {
        std::array<uint8_t, 18> packet{};
        for (std::size_t i = 0; i < 6; ++i) packet[i] = state[i + 2];
        const uint16_t buttons = static_cast<uint16_t>(state[2] | (state[3] << 8));
        constexpr uint16_t pressureBits[] = {0x20, 0x80, 0x10, 0x40, 0x1000, 0x2000,
                                           0x4000, 0x8000, 0x400, 0x800, 0x100, 0x200};
        for (std::size_t i = 0; i < 12; ++i) packet[6 + i] = buttons & pressureBits[i] ? 0 : 255;
        return packet;
    }
}
