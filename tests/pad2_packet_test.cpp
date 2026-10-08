#include "../src/gow_pad2_packet.h"
#include <cassert>
#include <cstdio>

int main()
{
    uint8_t state[32] = {1, 0x73, 0xff, 0xff, 128, 128, 128, 128};
    auto packet = gow_pad2::makePacket(state);
    assert(packet[0] == 255 && packet[1] == 255);
    for (unsigned i = 2; i < 6; ++i) assert(packet[i] == 128);
    for (unsigned i = 6; i < 18; ++i) assert(packet[i] == 0);

    // Cross is bit 14 on the host, but bit 6 after the game's CONCAT11.
    state[3] = 0xbf;
    packet = gow_pad2::makePacket(state);
    assert((((packet[0] << 8) | packet[1]) ^ 0xffff) == 0x40);
    assert(packet[12] == 255);
    for (unsigned i = 6; i < 18; ++i) if (i != 12) assert(packet[i] == 0);

    state[3] = 0xff;
    state[2] = 0xf7;
    packet = gow_pad2::makePacket(state);
    assert((((packet[0] << 8) | packet[1]) ^ 0xffff) == 0x800);

    // Verify each pressure against the game's button-index table at 0x29c610.
    constexpr unsigned gameBits[] = {13, 15, 12, 14, 4, 5, 6, 7, 2, 3, 0, 1};
    for (unsigned i = 0; i < 12; ++i)
    {
        const unsigned wireBit = gameBits[i] ^ 8;
        const uint16_t buttons = static_cast<uint16_t>(0xffffu ^ (1u << wireBit));
        state[2] = static_cast<uint8_t>(buttons);
        state[3] = static_cast<uint8_t>(buttons >> 8);
        packet = gow_pad2::makePacket(state);
        for (unsigned j = 0; j < 12; ++j) assert(packet[6 + j] == (i == j ? 255 : 0));
    }
    state[4] = 0; state[5] = 255; state[6] = 32; state[7] = 192;
    packet = gow_pad2::makePacket(state);
    assert(packet[2] == 0 && packet[3] == 255 && packet[4] == 32 && packet[5] == 192);
    std::puts("libpad2 packet tests passed");
}
