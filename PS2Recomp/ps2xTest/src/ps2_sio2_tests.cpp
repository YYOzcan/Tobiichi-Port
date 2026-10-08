// GOW-Port: pruebas de la emulacion del SIO2 y de la memory card (ps2xIOP/src/emulator/core/sio2.*).
#include "MiniTest.h"
#include "../../ps2xIOP/src/emulator/core/iop_memory.h"
#include "../../ps2xIOP/src/emulator/core/sio2.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

using ps2x::iop::detail::IopMemory;
using ps2x::iop::detail::MemoryCard;
using ps2x::iop::detail::Sio2;

namespace
{
    // Un comando por la FIFO, como sio2man sin DMA: SEND3[0], bytes, CTRL |= 1. Devuelve los bytes de respuesta.
    std::vector<uint8_t> transfer(Sio2 &sio2, uint32_t port, const std::vector<uint8_t> &command, size_t responseLength)
    {
        sio2.write32(Sio2::RegCtrl, sio2.read32(Sio2::RegCtrl) | 0xCu);
        sio2.write32(Sio2::RegBase, port | (static_cast<uint32_t>(command.size()) << 8u));
        sio2.write32(Sio2::RegBase + 4u, 0u);
        for (uint8_t value : command)
            sio2.writeFifo(value);
        sio2.write32(Sio2::RegCtrl, sio2.read32(Sio2::RegCtrl) | 1u);
        std::vector<uint8_t> response(responseLength);
        for (uint8_t &value : response)
            value = sio2.readFifo();
        return response;
    }

    std::vector<uint8_t> setPage(Sio2 &sio2, uint8_t command, uint32_t page)
    {
        const uint8_t b0 = static_cast<uint8_t>(page), b1 = static_cast<uint8_t>(page >> 8u);
        const uint8_t b2 = static_cast<uint8_t>(page >> 16u), b3 = static_cast<uint8_t>(page >> 24u);
        return transfer(sio2, 0u, {0x81u, command, b0, b1, b2, b3, static_cast<uint8_t>(b0 ^ b1 ^ b2 ^ b3), 0u, 0u}, 9u);
    }

    std::vector<uint8_t> writeData(Sio2 &sio2, const std::vector<uint8_t> &data)
    {
        std::vector<uint8_t> command = {0x81u, 0x42u, static_cast<uint8_t>(data.size())};
        command.insert(command.end(), data.begin(), data.end());
        command.push_back(0u);
        command.push_back(0u);
        return transfer(sio2, 0u, command, command.size());
    }

    std::vector<uint8_t> readData(Sio2 &sio2, uint8_t length)
    {
        std::vector<uint8_t> command(static_cast<size_t>(length) + 5u, 0u);
        command[0] = 0x81u;
        command[1] = 0x43u;
        command[2] = length;
        return transfer(sio2, 0u, command, command.size());
    }
}

void register_ps2_sio2_tests()
{
    MiniTest::Case("PS2Sio2", [](TestCase &tc)
    {
        tc.Run("a present memory card answers the probe with 0x2B and the terminator", [](TestCase &t)
        {
            Sio2 sio2;
            sio2.card(0).insert("");
            const auto response = transfer(sio2, 0u, {0x81u, 0x11u, 0u, 0u}, 4u);
            t.Equals(sio2.read32(Sio2::RegRecv1) & 0xF000u, 0x1000u, "RECV1 should report a connected device");
            t.Equals(response[2], static_cast<uint8_t>(0x2Bu), "third byte should be 0x2B");
            t.Equals(response[3], static_cast<uint8_t>(0x55u), "fourth byte should be the default terminator");
            t.IsTrue(sio2.takeTransferStarted(), "CTRL bit 0 should request the SIO2 interrupt");
            t.Equals(sio2.read32(Sio2::RegIstat), 1u, "ISTAT should flag the finished transfer");
            sio2.write32(Sio2::RegIstat, 1u);
            t.Equals(sio2.read32(Sio2::RegIstat), 0u, "writing ISTAT should acknowledge it");
            t.Equals(sio2.read32(Sio2::RegCtrl) & 1u, 0u, "the start bit should clear once the transfer is done");
        });

        tc.Run("an empty slot and the controller ports read as disconnected", [](TestCase &t)
        {
            Sio2 sio2;
            auto response = transfer(sio2, 0u, {0x81u, 0x11u, 0u, 0u}, 4u);
            t.IsTrue((sio2.read32(Sio2::RegRecv1) & 0xF000u) != 0x1000u, "no card: RECV1 must not report a device");
            t.Equals(response[3], static_cast<uint8_t>(0xFFu), "no card: dead air");
            response = transfer(sio2, 1u, {0x01u, 0x42u, 0u, 0u, 0u}, 5u);
            t.Equals(sio2.read32(Sio2::RegRecv1) & 0x2D000u, 0x2D000u, "missing pad on port 2 should set its bits");
            t.Equals(response[1], static_cast<uint8_t>(0xFFu), "missing pad: dead air");
        });

        tc.Run("get specs reports 512-byte pages, 16-page blocks and 8 MB", [](TestCase &t)
        {
            Sio2 sio2;
            sio2.card(0).insert("");
            std::vector<uint8_t> command(13u, 0u); // 0x81, 0x26 y 11 de relleno
            command[0] = 0x81u;
            command[1] = 0x26u;
            const auto r = transfer(sio2, 0u, command, 13u);
            t.Equals(r[2], static_cast<uint8_t>(0x2Bu), "0x2B header");
            t.Equals(static_cast<uint32_t>(r[3] | (r[4] << 8u)), 512u, "page size");
            t.Equals(static_cast<uint32_t>(r[5] | (r[6] << 8u)), 16u, "pages per block");
            t.Equals(static_cast<uint32_t>(r[7] | (r[8] << 8u) | (r[9] << 16u)), 0x4000u, "page count");
            t.Equals(r[11], static_cast<uint8_t>(0x52u), "XOR of the eight spec bytes");
            t.Equals(r[12], static_cast<uint8_t>(0x55u), "terminator");
        });

        tc.Run("set terminator changes the byte that ends every reply", [](TestCase &t)
        {
            Sio2 sio2;
            sio2.card(0).insert("");
            (void)transfer(sio2, 0u, {0x81u, 0x27u, 0x5Au, 0u, 0u}, 5u);
            const auto r = transfer(sio2, 0u, {0x81u, 0x28u, 0u, 0u, 0u}, 5u);
            t.Equals(r[3], static_cast<uint8_t>(0x5Au), "get terminator should return the new value");
            t.Equals(r[4], static_cast<uint8_t>(0x5Au), "and repeat it as the terminator");
        });

        tc.Run("erase, write and read back a page, and persist it to the card file", [](TestCase &t)
        {
            const std::filesystem::path file = std::filesystem::temp_directory_path() / "ps2x_sio2_test_card.ps2";
            std::filesystem::remove(file);
            std::vector<uint8_t> pattern(128u);
            for (size_t i = 0; i < pattern.size(); ++i)
                pattern[i] = static_cast<uint8_t>(i * 7u + 3u);
            {
                Sio2 sio2;
                sio2.card(0).insert(file.string());
                (void)setPage(sio2, 0x21u, 0x20u);
                (void)transfer(sio2, 0u, {0x81u, 0x82u, 0u, 0u}, 4u);
                (void)setPage(sio2, 0x22u, 0x21u);
                const auto w = writeData(sio2, pattern);
                uint8_t checksum = 0u;
                for (uint8_t value : pattern)
                    checksum ^= value;
                t.Equals(w[w.size() - 2u], checksum, "write reply should echo the XOR of the data");
                (void)setPage(sio2, 0x23u, 0x21u);
                const auto r = readData(sio2, 128u);
                t.IsTrue(std::equal(pattern.begin(), pattern.end(), r.begin() + 4), "read should return the written bytes");
                t.Equals(r[132], checksum, "read reply should carry the XOR of the data");
            }
            t.Equals(static_cast<uint64_t>(std::filesystem::file_size(file)), static_cast<uint64_t>(MemoryCard::ImageSize),
                     "the card file should be a full 8 MB PCSX2 image");
            MemoryCard reloaded;
            reloaded.insert(file.string());
            reloaded.setAddress(0x21u);
            std::vector<uint8_t> data(128u);
            reloaded.read(data.data(), data.size());
            t.IsTrue(data == pattern, "the page should survive in the file");
            std::filesystem::remove(file);
        });

        tc.Run("flash writes only clear bits until the block is erased", [](TestCase &t)
        {
            MemoryCard card;
            card.insert("");
            card.setAddress(0u);
            const uint8_t first = 0xF0u, second = 0x3Cu;
            card.write(&first, 1u);
            card.setAddress(0u);
            card.write(&second, 1u);
            uint8_t value = 0u;
            card.setAddress(0u);
            card.read(&value, 1u);
            t.Equals(value, static_cast<uint8_t>(0x30u), "two writes without erase should AND together");
            card.setAddress(0u);
            card.eraseBlock();
            card.setAddress(0u);
            card.read(&value, 1u);
            t.Equals(value, static_cast<uint8_t>(0xFFu), "erase should restore 0xFF");
        });

        // GOW-Port: los accesos en linea del interprete (ps2recomp-iop-fast.patch) deben comportarse como read*/write*.
        tc.Run("IOP fast loads and stores match the generic memory paths", [](TestCase &t)
        {
            IopMemory memory;
            memory.store32(0x80001000u, 0x11223344u); // KSEG0 -> fisica 0x1000
            t.Equals(memory.read32(0x1000u), 0x11223344u, "store32 should write RAM through the segment mirror");
            t.IsTrue(memory.ownsRamRange(0x1000u, 4u), "store32 should mark the RAM as written");
            memory.store16(0x1006u, 0xBEEFu);
            memory.store8(0x1005u, 0x7Au);
            t.Equals(memory.load16(0x1006u), static_cast<uint16_t>(0xBEEFu), "load16 should read back store16");
            t.Equals(memory.load8(0xA0001005u), static_cast<uint8_t>(0x7Au), "load8 should read back store8 through KSEG1");
            t.IsTrue(memory.ownsRamRange(0x1004u, 4u) == false && memory.ownsRamRange(0x1005u, 3u),
                     "only the bytes actually stored should be marked");
            memory.setInterruptStatus(0x0Fu);
            memory.store32(0x1F801070u, 0x05u); // I_STAT: escribir reconoce bits (AND)
            t.Equals(memory.load32(0x1F801070u), 0x05u, "hardware registers must still use the slow path");
            memory.sio2().card(0).insert("");
            memory.store32(Sio2::RegBase, 4u << 8u);
            memory.store8(Sio2::RegFifoIn, 0x81u);
            memory.store8(Sio2::RegFifoIn, 0x11u);
            memory.store8(Sio2::RegFifoIn, 0u);
            memory.store8(Sio2::RegFifoIn, 0u);
            (void)memory.load8(Sio2::RegFifoOut);
            (void)memory.load8(Sio2::RegFifoOut);
            t.Equals(memory.load8(Sio2::RegFifoOut), static_cast<uint8_t>(0x2Bu), "byte FIFO accesses must reach the SIO2");
        });

        tc.Run("DMA 11 and 12 move a command and its reply through IOP RAM", [](TestCase &t)
        {
            IopMemory memory;
            memory.sio2().card(0).insert("");
            constexpr uint32_t inAddress = 0x1000u, outAddress = 0x2000u;
            const uint8_t probe[8] = {0x81u, 0x11u, 0u, 0u, 0u, 0u, 0u, 0u};
            t.IsTrue(memory.writeRam(inAddress, probe, sizeof(probe)), "command in RAM");
            memory.write32(Sio2::RegCtrl, 0x3BCu | 0xCu);
            memory.write32(Sio2::RegBase, 0u | (4u << 8u)); // puerto 1, 4 bytes
            memory.write32(Sio2::RegBase + 4u, 0u);
            memory.write32(0x1F801540u, inAddress);      // DMA 11 MADR
            memory.write32(0x1F801544u, (1u << 16u) | 2u); // 1 bloque de 2 palabras
            memory.write32(0x1F801548u, 0x01000201u);
            memory.write32(0x1F801550u, outAddress);     // DMA 12 MADR
            memory.write32(0x1F801554u, (1u << 16u) | 2u);
            memory.write32(0x1F801558u, 0x41000200u);
            t.IsFalse(memory.takeDmaStart().has_value(), "the DMA channels themselves raise no interrupt");
            memory.write32(Sio2::RegCtrl, memory.read32(Sio2::RegCtrl) | 1u);
            const auto start = memory.takeDmaStart();
            t.IsTrue(start.has_value() && start->irq == Sio2::IopInterrupt, "CTRL start should schedule IRQ 17");
            uint8_t reply[8]{};
            t.IsTrue(memory.readRam(outAddress, reply, sizeof(reply)), "reply in RAM");
            t.Equals(reply[2], static_cast<uint8_t>(0x2Bu), "DMA 12 should deliver 0x2B");
            t.Equals(reply[3], static_cast<uint8_t>(0x55u), "and the terminator");
            t.Equals(memory.read32(0x1F801548u) & 0x01000000u, 0u, "DMA 11 should be idle again");
            t.Equals(memory.read32(Sio2::RegRecv1) & 0xF000u, 0x1000u, "RECV1 should report the card");
        });
    });
}
