// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#include "runtime/gs/gs_swizzle.h"
#include "runtime/gs/ps2_gs_memory.h"

#include <array>

namespace GSSwizzle
{
    namespace
    {
        Format make(GSMem::PixelStorageMode psm, uint8_t shiftX, uint8_t shiftY, uint8_t unpackedShift,
                    uint8_t bitOffset, uint32_t packedBytes, Kind kind)
        {
            Format f;
            f.table = GSMem::PageTableData(psm);
            f.pageShiftX = shiftX;
            f.pageShiftY = shiftY;
            f.pixelsPerPageShift = static_cast<uint8_t>(shiftX + shiftY);
            f.unpackedShift = unpackedShift;
            f.bitOffset = bitOffset;
            f.byteMask = kMemorySize - packedBytes;
            f.kind = kind;
            return f;
        }

        std::array<Format, 64> buildFormats()
        {
            GSMem::InitLookupTables();
            std::array<Format, 64> formats{};
            using GSMem::PixelStorageMode;
            formats[0x00] = make(PixelStorageMode::C32, 6, 5, 5, 0, 4, Kind::Bits32);
            formats[0x01] = make(PixelStorageMode::C24, 6, 5, 5, 0, 4, Kind::Bits24);
            formats[0x02] = make(PixelStorageMode::C16, 6, 6, 4, 0, 2, Kind::Bits16);
            formats[0x0A] = make(PixelStorageMode::C16S, 6, 6, 4, 0, 2, Kind::Bits16);
            formats[0x13] = make(PixelStorageMode::P8, 7, 6, 3, 0, 1, Kind::Bits8);
            formats[0x14] = make(PixelStorageMode::P4, 7, 7, 2, 0, 1, Kind::Bits4);
            formats[0x1B] = make(PixelStorageMode::P8H, 6, 5, 5, 24, 1, Kind::Bits8);
            formats[0x24] = make(PixelStorageMode::P4HL, 6, 5, 5, 24, 1, Kind::Bits4);
            formats[0x2C] = make(PixelStorageMode::P4HH, 6, 5, 5, 28, 1, Kind::Bits4);
            formats[0x30] = make(PixelStorageMode::Z32, 6, 5, 5, 0, 4, Kind::Bits32);
            formats[0x31] = make(PixelStorageMode::Z24, 6, 5, 5, 0, 4, Kind::Bits24);
            formats[0x32] = make(PixelStorageMode::Z16, 6, 6, 4, 0, 2, Kind::Bits16);
            formats[0x3A] = make(PixelStorageMode::Z16S, 6, 6, 4, 0, 2, Kind::Bits16);
            return formats;
        }
    }

    const Format &GetFormat(uint32_t psm)
    {
        static const std::array<Format, 64> formats = buildFormats();
        return formats[psm & 0x3Fu];
    }
}
