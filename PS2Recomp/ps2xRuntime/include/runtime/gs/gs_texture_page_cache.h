#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace GSMem
{
    class TexturePageCache
    {
    public:
        static constexpr uint32_t kPageSize = 8192u;

        void Invalidate() noexcept
        {
            m_pageBase = UINT32_MAX;
        }

        // byteAddress is the wrapped, swizzled VRAM address. The returned
        // pointer is valid only until the next miss or invalidation.
        const uint8_t* Resolve(const uint8_t* vram, uint32_t byteAddress) noexcept
        {
            const uint32_t pageBase = byteAddress & ~(kPageSize - 1u);
            if (m_pageBase != pageBase)
            {
                std::memcpy(m_bytes.data(), vram + pageBase, kPageSize);
                m_pageBase = pageBase;
            }
            return m_bytes.data() + (byteAddress & (kPageSize - 1u));
        }

        // GOW-Port: Taylor N. Albarnaz / LightVelox, SotC ac9efa070638ad3b3accd284de6f898d5ab271d1.
        uint32_t PageBase() const noexcept { return m_pageBase; }
        const uint8_t* Bytes() const noexcept { return m_bytes.data(); }
        void Restore(uint32_t pageBase, const uint8_t* bytes) noexcept
        {
            std::memcpy(m_bytes.data(), bytes, kPageSize);
            m_pageBase = pageBase;
        }

    private:
        alignas(64) std::array<uint8_t, kPageSize> m_bytes{};
        uint32_t m_pageBase = UINT32_MAX;
    };
}
