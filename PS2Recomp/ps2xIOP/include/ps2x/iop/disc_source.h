#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace ps2x::iop
{
    // A PS2 DVD/CD addressed by logical sector (2048 bytes). Both layers of a dual-layer DVD form one linear
    // LSN range, as the drive presents them.
    class DiscSource
    {
    public:
        static constexpr uint32_t kSectorSize = 2048u;

        struct File
        {
            std::string name;
            uint32_t lsn = 0;
            uint32_t size = 0;
            bool directory = false;
        };

        virtual ~DiscSource() = default;

        // Reads whole sectors; sectors past the end of the disc read as zeros and fail.
        [[nodiscard]] virtual bool readSectors(uint32_t lsn, uint32_t count, void *destination) = 0;
        // Looks a "cdrom0:\DIR\NAME;1"-style path up in the disc's file system.
        [[nodiscard]] virtual std::optional<File> findFile(std::string_view guestPath) = 0;
        // First LSN of layer 1 on a dual-layer disc, 0 otherwise.
        [[nodiscard]] virtual uint32_t layer1Start() const = 0;

        // A raw 2048-byte-sector image (.iso).
        [[nodiscard]] static std::unique_ptr<DiscSource> openImage(const std::filesystem::path &image);
        // Files extracted from a disc by tools/iso_extract.py --layout: <root>/.disc_layout lists each file's
        // original LSN and <root>/.disc_meta holds the non-file sectors (volume descriptors, UDF, directories),
        // so the extracted tree reproduces the original disc sector for sector.
        [[nodiscard]] static std::unique_ptr<DiscSource> openExtracted(const std::filesystem::path &root);
    };
}
