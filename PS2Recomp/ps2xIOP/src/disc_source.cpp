#include "ps2x/iop/disc_source.h"

#include "ps2x/iop/ps2_path.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <fstream>
#include <map>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace ps2x::iop
{
    namespace
    {
        constexpr uint32_t kSector = DiscSource::kSectorSize;
        constexpr uint32_t kPrimaryVolumeDescriptorLsn = 16u;

        uint32_t readLe32(const uint8_t *source)
        {
            return uint32_t{source[0]} | (uint32_t{source[1]} << 8u) | (uint32_t{source[2]} << 16u) |
                   (uint32_t{source[3]} << 24u);
        }

        // ISO9660 identifier comparison: case-insensitive, version suffix (";1") ignored.
        std::string normalizedComponent(std::string_view value)
        {
            std::string result(value);
            const size_t semicolon = result.rfind(';');
            if (semicolon != std::string::npos)
                result.resize(semicolon);
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char ch)
                           { return static_cast<char>(std::toupper(ch)); });
            return result;
        }

        // "cdrom0:\DIR\NAME;1" → "DIR/NAME"; empty if not a cdrom path.
        std::string normalizedDiscPath(std::string_view guestPath)
        {
            const ParsedPs2Path parsed = parsePs2Path(guestPath);
            if (!parsed || parsed.device != Ps2PathDevice::Cdrom)
                return {};
            std::string result;
            size_t begin = 0u;
            while (begin <= parsed.path.size())
            {
                const size_t end = parsed.path.find('/', begin);
                const size_t length = (end == std::string::npos) ? parsed.path.size() - begin : end - begin;
                const std::string_view component(parsed.path.data() + begin, length);
                begin = (end == std::string::npos) ? parsed.path.size() + 1u : end + 1u;
                if (component.empty() || component == ".")
                    continue;
                if (!result.empty())
                    result += '/';
                result += normalizedComponent(component);
            }
            return result;
        }

        class ImageDisc final : public DiscSource
        {
        public:
            explicit ImageDisc(const std::filesystem::path &path)
                : m_file(path, std::ios::binary)
            {
                std::array<uint8_t, kSector> descriptor{};
                if (!readRaw(uint64_t{kPrimaryVolumeDescriptorLsn} * kSector, descriptor.data(), kSector) ||
                    std::memcmp(descriptor.data() + 1, "CD001", 5) != 0)
                    return;
                m_volumes.push_back({0u, descriptor});
                const uint32_t layer0Sectors = readLe32(descriptor.data() + 80);
                if (readRaw(uint64_t{layer0Sectors} * kSector, descriptor.data(), kSector) &&
                    std::memcmp(descriptor.data() + 1, "CD001", 5) == 0)
                {
                    m_layer1Start = layer0Sectors - kPrimaryVolumeDescriptorLsn;
                    m_volumes.push_back({m_layer1Start, descriptor});
                }
            }

            bool valid() const { return !m_volumes.empty(); }

            bool readSectors(uint32_t lsn, uint32_t count, void *destination) override
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                return readRaw(uint64_t{lsn} * kSector, destination, size_t{count} * kSector);
            }

            std::optional<File> findFile(std::string_view guestPath) override
            {
                const std::string wanted = normalizedDiscPath(guestPath);
                if (wanted.empty())
                    return std::nullopt;
                std::lock_guard<std::mutex> lock(m_mutex);
                // Each layer carries its own tree; extents are relative to the layer origin.
                for (const Volume &volume : m_volumes)
                    if (auto file = findIn(volume, wanted))
                        return file;
                return std::nullopt;
            }

            uint32_t layer1Start() const override { return m_layer1Start; }

        private:
            struct Volume
            {
                uint32_t base = 0;
                std::array<uint8_t, kSector> descriptor{};
            };

            bool readRaw(uint64_t offset, void *destination, size_t size)
            {
                std::memset(destination, 0, size);
                m_file.clear();
                m_file.seekg(static_cast<std::streamoff>(offset));
                m_file.read(static_cast<char *>(destination), static_cast<std::streamsize>(size));
                return static_cast<size_t>(m_file.gcount()) == size;
            }

            std::optional<File> findIn(const Volume &volume, const std::string &wanted)
            {
                const uint8_t *root = volume.descriptor.data() + 156;
                File current{"", volume.base + readLe32(root + 2), readLe32(root + 10), true};
                size_t begin = 0u;
                while (begin < wanted.size())
                {
                    const size_t end = wanted.find('/', begin);
                    const std::string component = wanted.substr(begin, end == std::string::npos ? std::string::npos : end - begin);
                    begin = end == std::string::npos ? wanted.size() : end + 1u;
                    if (!current.directory)
                        return std::nullopt;

                    std::vector<uint8_t> records(current.size);
                    if (!readRaw(uint64_t{current.lsn} * kSector, records.data(), records.size()))
                        return std::nullopt;
                    bool found = false;
                    for (size_t offset = 0u; offset < records.size();)
                    {
                        const uint8_t length = records[offset];
                        if (length == 0u)
                        {
                            offset = (offset / kSector + 1u) * kSector; // records never span sectors
                            continue;
                        }
                        if (length < 34u || offset + length > records.size())
                            break;
                        const uint8_t *record = records.data() + offset;
                        const std::string_view name(reinterpret_cast<const char *>(record + 33),
                                                    std::min<size_t>(record[32], length - 33u));
                        if (record[32] > 1u && normalizedComponent(name) == component)
                        {
                            current = {normalizedComponent(name), volume.base + readLe32(record + 2), readLe32(record + 10),
                                       (record[25] & 2u) != 0u};
                            found = true;
                            break;
                        }
                        offset += length;
                    }
                    if (!found)
                        return std::nullopt;
                }
                return current;
            }

            std::mutex m_mutex;
            std::ifstream m_file;
            std::vector<Volume> m_volumes;
            uint32_t m_layer1Start = 0u;
        };

        class ExtractedDisc final : public DiscSource
        {
        public:
            explicit ExtractedDisc(const std::filesystem::path &root)
                : m_root(root)
            {
                std::ifstream layout(root / ".disc_layout");
                std::string line;
                while (std::getline(layout, line))
                {
                    std::istringstream fields(line);
                    std::string kind;
                    fields >> kind;
                    if (kind == "sectors")
                        fields >> m_sectors;
                    else if (kind == "layer1")
                        fields >> m_layer1Start;
                    else if (kind == "file")
                    {
                        Entry entry;
                        fields >> entry.lsn >> entry.size;
                        std::getline(fields >> std::ws, entry.path);
                        if (!entry.path.empty())
                            m_files.push_back(std::move(entry));
                    }
                }
                std::sort(m_files.begin(), m_files.end(), [](const Entry &a, const Entry &b)
                          { return a.lsn < b.lsn; });

                std::ifstream meta(root / ".disc_meta", std::ios::binary);
                std::array<uint8_t, 4u + kSector> record{};
                while (meta.read(reinterpret_cast<char *>(record.data()), static_cast<std::streamsize>(record.size())))
                {
                    std::array<uint8_t, kSector> &sector = m_meta[readLe32(record.data())];
                    std::memcpy(sector.data(), record.data() + 4u, kSector);
                }
            }

            bool valid() const { return m_sectors != 0u && !m_files.empty(); }

            bool readSectors(uint32_t lsn, uint32_t count, void *destination) override
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                auto *bytes = static_cast<uint8_t *>(destination);
                bool ok = true;
                for (uint32_t i = 0u; i < count;)
                {
                    const uint32_t sector = lsn + i;
                    uint8_t *out = bytes + size_t{i} * kSector;
                    if (sector >= m_sectors)
                    {
                        std::memset(out, 0, size_t{count - i} * kSector);
                        return false;
                    }
                    if (const auto meta = m_meta.find(sector); meta != m_meta.end())
                    {
                        std::memcpy(out, meta->second.data(), kSector);
                        ++i;
                        continue;
                    }
                    const Entry *file = fileAt(sector);
                    if (!file)
                    {
                        std::memset(out, 0, kSector);
                        ++i;
                        continue;
                    }
                    // Read the run of sectors that lies inside this file in one go.
                    const uint32_t fileSectors = (file->size + kSector - 1u) / kSector;
                    const uint32_t run = std::min(count - i, file->lsn + fileSectors - sector);
                    std::memset(out, 0, size_t{run} * kSector);
                    const uint64_t offset = uint64_t{sector - file->lsn} * kSector;
                    const size_t wanted = static_cast<size_t>(std::min<uint64_t>(uint64_t{run} * kSector, file->size - offset));
                    std::ifstream &stream = handle(*file);
                    stream.clear();
                    stream.seekg(static_cast<std::streamoff>(offset));
                    stream.read(reinterpret_cast<char *>(out), static_cast<std::streamsize>(wanted));
                    ok = ok && static_cast<size_t>(stream.gcount()) == wanted;
                    i += run;
                }
                return ok;
            }

            std::optional<File> findFile(std::string_view guestPath) override
            {
                const std::string wanted = normalizedDiscPath(guestPath);
                for (const Entry &entry : m_files)
                {
                    std::string name = entry.path;
                    std::replace(name.begin(), name.end(), '\\', '/');
                    if (normalizedComponent(name) == wanted)
                        return File{wanted.substr(wanted.rfind('/') + 1u), entry.lsn, entry.size, false};
                }
                return std::nullopt;
            }

            uint32_t layer1Start() const override { return m_layer1Start; }

        private:
            struct Entry
            {
                uint32_t lsn = 0;
                uint32_t size = 0;
                std::string path;
            };

            const Entry *fileAt(uint32_t sector) const
            {
                auto it = std::upper_bound(m_files.begin(), m_files.end(), sector, [](uint32_t value, const Entry &entry)
                                           { return value < entry.lsn; });
                if (it == m_files.begin())
                    return nullptr;
                --it;
                const uint32_t sectors = (it->size + kSector - 1u) / kSector;
                return sector < it->lsn + sectors ? &*it : nullptr;
            }

            std::ifstream &handle(const Entry &entry)
            {
                auto it = m_handles.find(entry.lsn);
                if (it == m_handles.end())
                    it = m_handles.emplace(entry.lsn, std::ifstream(m_root / std::filesystem::path(entry.path), std::ios::binary)).first;
                return it->second;
            }

            std::mutex m_mutex;
            std::filesystem::path m_root;
            uint32_t m_sectors = 0u;
            uint32_t m_layer1Start = 0u;
            std::vector<Entry> m_files;
            std::unordered_map<uint32_t, std::array<uint8_t, kSector>> m_meta;
            std::map<uint32_t, std::ifstream> m_handles;
        };
    }

    std::unique_ptr<DiscSource> DiscSource::openImage(const std::filesystem::path &image)
    {
        auto disc = std::make_unique<ImageDisc>(image);
        if (!disc->valid())
            return nullptr;
        return disc;
    }

    std::unique_ptr<DiscSource> DiscSource::openExtracted(const std::filesystem::path &root)
    {
        std::error_code error;
        if (!std::filesystem::is_regular_file(root / ".disc_layout", error))
            return nullptr;
        auto disc = std::make_unique<ExtractedDisc>(root);
        if (!disc->valid())
            return nullptr;
        return disc;
    }
}
