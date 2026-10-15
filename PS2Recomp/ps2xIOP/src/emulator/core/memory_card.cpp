#include "memory_card.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace ps2x::iop::detail
{
    void MemoryCard::insert(std::string path)
    {
        m_path = std::move(path);
        m_present = true;
        m_loaded = false;
        m_fileExists = false;
        m_image.clear();
        m_address = 0;
    }

    void MemoryCard::eject()
    {
        m_present = false;
        m_loaded = false;
        m_image.clear();
    }

    void MemoryCard::load()
    {
        if (m_loaded)
            return;
        m_loaded = true;
        m_image.assign(ImageSize, 0xFFu); // sin formatear
        if (m_path.empty())
            return;
        std::ifstream file(m_path, std::ios::binary);
        if (!file)
            return;
        m_fileExists = true;
        file.read(reinterpret_cast<char *>(m_image.data()), static_cast<std::streamsize>(m_image.size()));
    }

    const std::vector<uint8_t> &MemoryCard::image()
    {
        load();
        return m_image;
    }

    void MemoryCard::persist(uint32_t offset, size_t size)
    {
        if (m_path.empty() || size == 0u)
            return;
        if (!m_fileExists)
        {
            // Primera escritura: se crea el archivo con la imagen entera
            std::ofstream file(m_path, std::ios::binary | std::ios::trunc);
            if (!file)
            {
                std::cerr << "[SIO2] no se puede crear la memory card " << m_path << std::endl;
                return;
            }
            file.write(reinterpret_cast<const char *>(m_image.data()), static_cast<std::streamsize>(m_image.size()));
            m_fileExists = static_cast<bool>(file);
            std::cerr << "[SIO2] memory card creada en " << m_path << std::endl;
            return;
        }
        std::fstream file(m_path, std::ios::binary | std::ios::in | std::ios::out);
        if (!file)
            return;
        file.seekp(offset);
        file.write(reinterpret_cast<const char *>(m_image.data() + offset), static_cast<std::streamsize>(size));
    }

    void MemoryCard::read(uint8_t *destination, size_t size)
    {
        load();
        for (size_t i = 0; i < size; ++i)
        {
            const uint32_t offset = m_address + static_cast<uint32_t>(i);
            destination[i] = offset < ImageSize ? m_image[offset] : 0xFFu;
        }
        m_address += static_cast<uint32_t>(size);
    }

    void MemoryCard::write(const uint8_t *source, size_t size)
    {
        load();
        const uint32_t start = m_address;
        if (start >= ImageSize)
        {
            m_address += static_cast<uint32_t>(size);
            return;
        }
        const size_t count = std::min<size_t>(size, ImageSize - start);
        for (size_t i = 0; i < count; ++i)
            m_image[start + i] &= source[i];
        persist(start, count);
        m_address += static_cast<uint32_t>(size);
    }

    void MemoryCard::eraseBlock()
    {
        load();
        const uint32_t start = m_address;
        if (start >= ImageSize)
            return;
        const size_t count = std::min<size_t>(RawPageSize * PagesPerBlock, ImageSize - start);
        std::fill_n(m_image.begin() + start, count, uint8_t{0xFFu});
        persist(start, count);
    }

    void MemoryCardSlots::setPathProvider(std::function<std::string(uint32_t slot)> provider)
    {
        m_pathProvider = std::move(provider);
        m_prepared.fill(false);
    }

    void MemoryCardSlots::reset()
    {
        m_prepared.fill(false);
        for (MemoryCard &card : m_cards)
            card.eject();
    }

    MemoryCard *MemoryCardSlots::card(uint32_t slot)
    {
        slot &= 1u;
        if (!m_prepared[slot] && m_pathProvider)
        {
            m_prepared[slot] = true;
            const std::string path = m_pathProvider(slot);
            if (!path.empty())
            {
                m_cards[slot].insert(path);
                std::cerr << "[memory card] slot " << (slot + 1u) << ": " << path << std::endl;
            }
        }
        return m_cards[slot].present() ? &m_cards[slot] : nullptr;
    }
}
