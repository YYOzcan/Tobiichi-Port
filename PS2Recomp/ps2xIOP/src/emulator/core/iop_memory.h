#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

#include "sio2.h"
#include "spu2.h"

namespace ps2x::iop::detail
{
    class IopMemory
    {
    public:
        static constexpr uint32_t RamSize = 2u * 1024u * 1024u;
        static constexpr uint32_t ScratchBase = 0x1F800000u;
        static constexpr uint32_t ScratchSize = 0x400u;
        static constexpr uint32_t HardwareBase = 0x1F801000u;
        static constexpr uint32_t HardwareEnd = 0x1F900000u;
        static constexpr uint32_t Spu2Base = 0x1F900000u;
        static constexpr uint32_t Spu2End = 0x1FA00000u;
        static constexpr uint32_t SifBase = 0x1D000000u;
        static constexpr uint32_t SifEnd = 0x1D001000u;
        // GOW-Port: el heap empezaba en 0x120000 (832 KB hasta HeapLimit) y SMPD_IOP.IRX de God of War
        // reserva un bloque de 0x11ADF8 bytes. En un IOP real el heap empieza tras los modulos cargados
        // (los de GoW terminan hacia 0x56000), asi que lo bajamos a 0x70000 (1.5 MB).
        static constexpr uint32_t HeapBase = 0x00070000u;
        static constexpr uint32_t HeapLimit = 0x001F0000u;

        struct Allocation
        {
            uint32_t address = 0;
            uint32_t size = 0;
        };

        struct DmaStart
        {
            int irq = 0;
            uint64_t delayCycles = 0;
        };

        IopMemory();

        void reset();

        [[nodiscard]] uint8_t read8(uint32_t address) const;
        [[nodiscard]] uint16_t read16(uint32_t address) const;
        [[nodiscard]] uint32_t read32(uint32_t address) const;
        // GOW-Port: lectura de instrucciones en linea (el caso normal es RAM alineada); el resto va por read32.
        [[nodiscard]] uint32_t fetch32(uint32_t address) const
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            if ((phys & 3u) == 0u && phys < RamSize)
            {
                uint32_t value;
                std::memcpy(&value, m_ram.data() + phys, sizeof(value));
                return value;
            }
            return read32(address);
        }
        void write8(uint32_t address, uint8_t value);
        void write16(uint32_t address, uint16_t value);
        void write32(uint32_t address, uint32_t value);

        [[nodiscard]] bool readRam(uint32_t address, void *destination, size_t size) const;
        [[nodiscard]] bool writeRam(uint32_t address, const void *source, size_t size);
        [[nodiscard]] bool zeroRam(uint32_t address, size_t size);
        [[nodiscard]] bool ownsRamRange(uint32_t address, size_t size) const;
        [[nodiscard]] bool isHardwareAddress(uint32_t address) const;
        [[nodiscard]] std::string readString(uint32_t address, size_t limit = 1024u) const;

        [[nodiscard]] uint32_t allocate(uint32_t size, uint32_t alignment = 16u, std::optional<uint32_t> fixed = std::nullopt);
        [[nodiscard]] bool freeAllocation(uint32_t address);
        [[nodiscard]] uint32_t maxFreeMemory() const;
        [[nodiscard]] std::optional<Allocation> allocationContaining(uint32_t address) const;

        [[nodiscard]] uint32_t interruptStatus() const noexcept { return m_interruptStatus; }
        [[nodiscard]] uint32_t interruptMask() const noexcept { return m_interruptMask; }
        [[nodiscard]] uint32_t interruptControl() const noexcept { return m_interruptControl; }
        void setInterruptStatus(uint32_t value) noexcept { m_interruptStatus = value; }
        void setInterruptMask(uint32_t value) noexcept { m_interruptMask = value; }
        void setInterruptControl(uint32_t value) noexcept { m_interruptControl = value & 1u; }

        [[nodiscard]] std::optional<DmaStart> takeDmaStart() noexcept;
        [[nodiscard]] bool hasDmaStart() const noexcept { return m_dmaStart.has_value(); } // GOW-Port

        // GOW-Port: accesos del interprete con camino rapido en linea para la RAM (alineados); el resto (registros de
        // hardware, scratchpad, SPU2, SIO2...) sigue por read*/write*, con el mismo comportamiento.
        [[nodiscard]] uint32_t load32(uint32_t address) const { return fetch32(address); }
        [[nodiscard]] uint16_t load16(uint32_t address) const
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            if (phys + 1u < RamSize)
            {
                uint16_t value;
                std::memcpy(&value, m_ram.data() + phys, sizeof(value));
                return value;
            }
            return read16(address);
        }
        [[nodiscard]] uint8_t load8(uint32_t address) const
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            return phys < RamSize ? m_ram[phys] : read8(address);
        }
        void store32(uint32_t address, uint32_t value)
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            if ((phys & 3u) == 0u && phys < RamSize)
            {
                std::memcpy(m_ram.data() + phys, &value, sizeof(value));
                std::memset(m_owned.data() + phys, 1, sizeof(value));
                return;
            }
            write32(address, value);
        }
        void store16(uint32_t address, uint16_t value)
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            if (phys + 1u < RamSize)
            {
                std::memcpy(m_ram.data() + phys, &value, sizeof(value));
                std::memset(m_owned.data() + phys, 1, sizeof(value));
                return;
            }
            write16(address, value);
        }
        void store8(uint32_t address, uint8_t value)
        {
            const uint32_t phys = address & 0x1FFFFFFFu;
            if (phys < RamSize)
            {
                m_ram[phys] = value;
                m_owned[phys] = 1u;
                return;
            }
            write8(address, value);
        }
        [[nodiscard]] std::span<const uint8_t> ram() const noexcept { return m_ram; }
        [[nodiscard]] Spu2 &spu2() noexcept { return m_spu2; }
        [[nodiscard]] Sio2 &sio2() noexcept { return m_sio2; }
        [[nodiscard]] bool sio2Enabled() const noexcept { return m_sio2Enabled; }

        [[nodiscard]] static uint32_t physicalAddress(uint32_t address) noexcept { return address & 0x1FFFFFFFu; }

    private:
        [[nodiscard]] uint32_t readHardware32(uint32_t address) const;
        void writeHardware32(uint32_t address, uint32_t value);
        void markOwned(uint32_t address, size_t size);

        std::vector<uint8_t> m_ram;
        std::vector<uint8_t> m_owned;
        std::vector<uint8_t> m_scratch;
        std::unordered_map<uint32_t, uint32_t> m_hardware;
        std::vector<Allocation> m_allocations;
        uint32_t m_heapCursor = HeapBase;
        uint32_t m_interruptStatus = 0;
        uint32_t m_interruptMask = 0;
        uint32_t m_interruptControl = 1;
        std::optional<DmaStart> m_dmaStart;
        Spu2 m_spu2; // GOW-Port
        mutable Sio2 m_sio2; // GOW-Port: leer la FIFO de salida consume bytes
        bool m_sio2Enabled = true; // GOW_SIO2=0: registros del SIO2 como simples latches (comportamiento anterior)
        void startSio2Dma(uint32_t chcrAddress, uint32_t value);
    };
}
