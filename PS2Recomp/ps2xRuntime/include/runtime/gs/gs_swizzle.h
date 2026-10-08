// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include <cstdint>
#include <cstring>

namespace GSSwizzle
{
    constexpr uint32_t kMemorySize = 4u * 1024u * 1024u;
    constexpr uint32_t kPageBytes = 8192u;

    enum class Kind : uint8_t
    {
        Invalid,
        Bits32,
        Bits24,
        Bits16,
        Bits8,
        Bits4,
    };

    struct Format
    {
        const uint16_t *table = nullptr;
        uint8_t pageShiftX = 0u;
        uint8_t pageShiftY = 0u;
        uint8_t pixelsPerPageShift = 0u;
        uint8_t unpackedShift = 0u;
        uint8_t bitOffset = 0u;
        uint32_t byteMask = 0u;
        Kind kind = Kind::Invalid;
    };

    const Format &GetFormat(uint32_t psm);

    struct Location
    {
        uint32_t byte;
        uint32_t shift;
    };

    inline uint32_t PixelIndex(const Format &f, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
    {
        const uint32_t pagesPerRow = (bw * 64u) >> f.pageShiftX;
        const uint32_t page = (base >> 5u) + (y >> f.pageShiftY) * pagesPerRow + (x >> f.pageShiftX);
        const uint32_t xMask = (1u << f.pageShiftX) - 1u;
        const uint32_t yMask = (1u << f.pageShiftY) - 1u;
        const uint32_t entry = ((base & 31u) << (f.pageShiftX + f.pageShiftY)) + ((y & yMask) << f.pageShiftX) + (x & xMask);
        return (page << f.pixelsPerPageShift) + f.table[entry];
    }

    inline Location Locate(const Format &f, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
    {
        const uint32_t bits = (PixelIndex(f, base, bw, x, y) << f.unpackedShift) + f.bitOffset;
        return {(bits >> 3u) & f.byteMask, bits & 7u};
    }

    struct AxisPart
    {
        uint32_t page = 0u;
        uint32_t entry = 0u;
    };

    inline AxisPart RowPart(const Format &f, uint32_t base, uint32_t bw, uint32_t y)
    {
        const uint32_t pagesPerRow = (bw * 64u) >> f.pageShiftX;
        const uint32_t yMask = (1u << f.pageShiftY) - 1u;
        return {((base >> 5u) + (y >> f.pageShiftY) * pagesPerRow) << f.pixelsPerPageShift,
                ((base & 31u) << (f.pageShiftX + f.pageShiftY)) + ((y & yMask) << f.pageShiftX)};
    }

    inline AxisPart ColumnPart(const Format &f, uint32_t x)
    {
        const uint32_t xMask = (1u << f.pageShiftX) - 1u;
        return {(x >> f.pageShiftX) << f.pixelsPerPageShift, x & xMask};
    }

    inline Location Combine(const Format &f, const AxisPart &row, const AxisPart &column)
    {
        const uint32_t pixel = row.page + column.page + f.table[row.entry + column.entry];
        const uint32_t bits = (pixel << f.unpackedShift) + f.bitOffset;
        return {(bits >> 3u) & f.byteMask, bits & 7u};
    }

    inline uint32_t LoadAt(const Format &f, const uint8_t *source, uint32_t shift)
    {
        switch (f.kind)
        {
        case Kind::Bits32:
        {
            uint32_t v;
            std::memcpy(&v, source, 4u);
            return v;
        }
        case Kind::Bits24:
        {
            uint32_t v;
            std::memcpy(&v, source, 4u);
            return v & 0x00FFFFFFu;
        }
        case Kind::Bits16:
        {
            uint16_t v;
            std::memcpy(&v, source, 2u);
            return v;
        }
        case Kind::Bits8:
            return *source;
        case Kind::Bits4:
            return (static_cast<uint32_t>(*source) >> shift) & 0x0Fu;
        default:
            return 0u;
        }
    }

    inline void StoreAt(const Format &f, uint8_t *target, uint32_t shift, uint32_t value)
    {
        switch (f.kind)
        {
        case Kind::Bits32:
            std::memcpy(target, &value, 4u);
            break;
        case Kind::Bits24:
        {
            uint32_t old;
            std::memcpy(&old, target, 4u);
            const uint32_t merged = (old & 0xFF000000u) | (value & 0x00FFFFFFu);
            std::memcpy(target, &merged, 4u);
            break;
        }
        case Kind::Bits16:
        {
            const uint16_t v = static_cast<uint16_t>(value);
            std::memcpy(target, &v, 2u);
            break;
        }
        case Kind::Bits8:
            *target = static_cast<uint8_t>(value);
            break;
        case Kind::Bits4:
        {
            const uint8_t old = *target;
            *target = static_cast<uint8_t>((old & ~(0x0Fu << shift)) | ((value & 0x0Fu) << shift));
            break;
        }
        default:
            break;
        }
    }

    class TextureCache
    {
    public:
        void Invalidate() noexcept
        {
            m_page = UINT32_MAX;
            m_materialized = false;
        }

        const uint8_t *Resolve(const uint8_t *vram, uint32_t byteAddress) noexcept
        {
            const uint32_t page = byteAddress & ~(kPageBytes - 1u);
            if (page != m_page)
            {
                m_page = page;
                m_materialized = false;
            }
            return m_materialized ? m_bytes + (byteAddress & (kPageBytes - 1u)) : vram + byteAddress;
        }

        void BeforeWrite(const uint8_t *vram, uint32_t byteAddress) noexcept
        {
            if (!m_materialized && (byteAddress & ~(kPageBytes - 1u)) == m_page)
                Materialize(vram);
        }

        void BeforeWriteRange(const uint8_t *vram, uint32_t firstByte, uint32_t lastByte) noexcept
        {
            if (!m_materialized && m_page != UINT32_MAX && m_page >= (firstByte & ~(kPageBytes - 1u)) &&
                m_page <= (lastByte & ~(kPageBytes - 1u)))
                Materialize(vram);
        }

        void Materialize(const uint8_t *vram) noexcept
        {
            if (m_page == UINT32_MAX || m_materialized)
                return;
            std::memcpy(m_bytes, vram + m_page, kPageBytes);
            m_materialized = true;
        }

        bool DematerializeIfClean(const uint8_t *vram) noexcept
        {
            if (m_page == UINT32_MAX || !m_materialized)
                return true;
            if (std::memcmp(m_bytes, vram + m_page, kPageBytes) != 0)
                return false;
            m_materialized = false;
            return true;
        }

        bool Materialized() const noexcept
        {
            return m_page != UINT32_MAX && m_materialized;
        }

        const uint8_t *Bytes() const noexcept
        {
            return m_bytes;
        }

        bool Live() const noexcept
        {
            return m_page != UINT32_MAX && !m_materialized;
        }

        uint32_t Page() const noexcept
        {
            return m_page;
        }

        void Export(const uint8_t *vram, uint32_t &page, uint8_t *bytes) const noexcept
        {
            page = m_page;
            if (m_page == UINT32_MAX)
                std::memcpy(bytes, m_bytes, kPageBytes);
            else
                std::memcpy(bytes, m_materialized ? m_bytes : vram + m_page, kPageBytes);
        }

        void Import(uint32_t page, const uint8_t *bytes) noexcept
        {
            std::memcpy(m_bytes, bytes, kPageBytes);
            m_page = page;
            m_materialized = true;
        }

    private:
        alignas(64) uint8_t m_bytes[kPageBytes]{};
        uint32_t m_page = UINT32_MAX;
        bool m_materialized = false;
    };
}
