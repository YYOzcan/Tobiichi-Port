#include "sio2.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr uint8_t kModePad = 0x01u;
        constexpr uint8_t kModeMultitap = 0x21u;
        constexpr uint8_t kModeMemcard = 0x81u;
        constexpr uint32_t kCtrlStart = 0x1u;
    }

    // ---------------------------------------------------------------------------------------------------------------
    // MemoryCard

    void MemoryCard::insert(std::string path)
    {
        m_path = std::move(path);
        m_present = true;
        m_loaded = false;
        m_fileExists = false;
        m_image.clear();
        m_address = 0;
        terminator = 0x55u;
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

    // ---------------------------------------------------------------------------------------------------------------
    // Sio2

    Sio2::Sio2()
    {
        const char *diag = std::getenv("GOW_SIO2_DIAG");
        m_diag = diag != nullptr && diag[0] != '0';
        reset();
    }

    void Sio2::reset()
    {
        m_cmdQueue.fill(0u);
        m_portCtrl.fill(0u);
        m_ctrl = 0x3BCu;
        m_cmdStat = StatDisconnected;
        m_portStat = 0xFu;
        m_fifoStat = 0u;
        m_unknown78 = m_unknown7C = 0u;
        m_istat = 0u;
        m_out.clear();
        softReset();
        m_port = 0u;
        m_transferStarted = false;
        for (MemoryCard &card : m_cards)
            card.terminator = 0x55u;
    }

    void Sio2::softReset()
    {
        m_queueRead = false;
        m_queuePosition = 0u;
        m_commandLength = 0u;
        m_dmaBlockSize = 0u;
        m_queueComplete = false;
        m_in.clear();
        m_cmdStat = 0u;
    }

    void Sio2::setCardPathProvider(std::function<std::string(uint32_t port)> provider)
    {
        m_pathProvider = std::move(provider);
        m_cardPrepared.fill(false);
    }

    void Sio2::prepareCard(uint32_t port)
    {
        if (m_cardPrepared[port] || !m_pathProvider)
            return;
        m_cardPrepared[port] = true;
        const std::string path = m_pathProvider(port);
        if (path.empty())
            return;
        m_cards[port].insert(path);
        std::cerr << "[SIO2] memory card del puerto " << (port + 1u) << ": " << path << std::endl;
    }

    uint32_t Sio2::read32(uint32_t physical)
    {
        const uint32_t offset = physical - RegBase;
        if (offset < 0x40u)
            return m_cmdQueue[offset >> 2u];
        if (offset < 0x60u)
            return m_portCtrl[(offset - 0x40u) >> 2u];
        switch (physical)
        {
        case RegFifoOut:
            return readFifo();
        case RegCtrl:
            return m_ctrl;
        case RegRecv1:
            return m_cmdStat;
        case RegRecv2:
            return m_portStat;
        case RegRecv3:
            return m_fifoStat;
        case 0x1F808278u:
            return m_unknown78;
        case 0x1F80827Cu:
            return m_unknown7C;
        case RegIstat:
            return m_istat;
        default:
            return 0u;
        }
    }

    void Sio2::write32(uint32_t physical, uint32_t value)
    {
        const uint32_t offset = physical - RegBase;
        if (offset < 0x40u)
        {
            m_cmdQueue[offset >> 2u] = value;
            if (offset == 0u)
            {
                softReset(); // una cola nueva: lo que quedara sin leer de la anterior se descarta
                m_out.clear();
            }
            return;
        }
        if (offset < 0x60u)
        {
            m_portCtrl[(offset - 0x40u) >> 2u] = value;
            return;
        }
        switch (physical)
        {
        case RegFifoIn:
            writeFifo(static_cast<uint8_t>(value));
            return;
        case RegCtrl:
            if ((value & kCtrlStart) != 0u)
            {
                // Los comandos ya se procesaron al recibir sus bytes: la transferencia termina en el acto.
                m_istat |= 1u;
                m_transferStarted = true;
            }
            m_ctrl = value & ~kCtrlStart;
            return;
        case RegRecv1:
            m_cmdStat = value;
            return;
        case RegRecv2:
            m_portStat = value;
            return;
        case RegRecv3:
            m_fifoStat = value;
            return;
        case 0x1F808278u:
            m_unknown78 = value;
            return;
        case 0x1F80827Cu:
            m_unknown7C = value;
            return;
        case RegIstat:
            m_istat &= ~value;
            return;
        default:
            return;
        }
    }

    bool Sio2::takeTransferStarted() noexcept
    {
        const bool started = m_transferStarted;
        m_transferStarted = false;
        return started;
    }

    uint8_t Sio2::readFifo()
    {
        if (m_out.empty())
            return 0xFFu;
        const uint8_t value = m_out.front();
        m_out.pop_front();
        return value;
    }

    uint8_t Sio2::popIn()
    {
        if (m_in.empty())
            return 0u;
        const uint8_t value = m_in.front();
        m_in.pop_front();
        return value;
    }

    void Sio2::writeFifo(uint8_t value)
    {
        if (!m_queueRead)
        {
            if (m_queuePosition >= m_cmdQueue.size())
                return;
            const uint32_t command = m_cmdQueue[m_queuePosition];
            m_port = command & 1u;
            m_commandLength = (command >> 8u) & 0x3FFu;
            m_queueRead = true;
            m_queueComplete = m_commandLength == 0u;
            m_in.clear();
        }
        if (m_queueComplete)
            return;
        m_in.push_back(value);
        if ((m_dmaBlockSize == 0u && m_in.size() == m_commandLength) ||
            (m_dmaBlockSize != 0u && m_in.size() == m_dmaBlockSize))
        {
            m_queueRead = false;
            ++m_queuePosition;
            process();
        }
    }

    void Sio2::process()
    {
        const size_t outStart = m_out.size();
        const uint8_t mode = popIn();
        switch (mode)
        {
        case kModeMemcard:
            memcard();
            break;
        case kModePad:
        case kModeMultitap:
        default:
            absentDevice(false);
            break;
        }
        // La respuesta ocupa lo mismo que el comando (y con DMA, bloques enteros)
        const size_t produced = m_out.size() - outStart;
        const size_t expected = m_dmaBlockSize != 0u ? ((produced + m_dmaBlockSize - 1u) / m_dmaBlockSize) * m_dmaBlockSize
                                                     : m_commandLength;
        for (size_t i = produced; i < expected; ++i)
            m_out.push_back(m_dmaBlockSize != 0u ? 0x00u : 0xFFu);
    }

    void Sio2::absentDevice(bool memcard)
    {
        // Nadie responde: todo 0xFF y el bit de "falta el dispositivo" del puerto
        if (memcard)
            m_cmdStat = StatDisconnected;
        else
        {
            m_cmdStat |= (m_cmdStat & 0x100u) ? 0x200u : 0x100u;
            m_cmdStat |= m_port == 0u ? 0x1D000u : 0x2D000u;
        }
        m_out.push_back(0xFFu);
        while (!m_in.empty())
        {
            m_in.pop_front();
            m_out.push_back(0xFFu);
        }
    }

    void Sio2::memcard()
    {
        prepareCard(m_port);
        MemoryCard &card = m_cards[m_port];
        if (!card.present())
        {
            absentDevice(true);
            return;
        }
        m_cmdStat = StatConnected;
        const uint8_t command = popIn();
        m_lastCardCommand = command;
        if (m_diag)
            std::cerr << "[SIO2] mc" << m_port << " cmd=0x" << std::hex << static_cast<int>(command) << std::dec
                      << " len=" << m_commandLength << std::endl;

        // Las dos primeras posiciones corresponden a 0x81 y al comando. El relleno se mide desde aqui.
        const size_t base = m_out.size();
        m_out.push_back(0x00u);
        m_out.push_back(0x00u);
        auto terminator = [&](size_t length)
        {
            while (m_out.size() - base + 2u < length)
                m_out.push_back(0x00u);
            m_out.push_back(0x2Bu);
            m_out.push_back(card.terminator);
        };

        switch (command)
        {
        case 0x11u: // sondeo
        case 0x12u: // fin de escritura/borrado
        case 0x81u: // fin de lectura/escritura
            terminator(4u);
            break;
        case 0x21u: // fijar pagina de borrado, escritura o lectura
        case 0x22u:
        case 0x23u:
        {
            uint32_t page = 0u;
            for (uint32_t i = 0; i < 4u; ++i)
                page |= static_cast<uint32_t>(popIn()) << (i * 8u);
            (void)popIn(); // XOR de los 4 bytes
            card.setAddress(page);
            terminator(9u);
            break;
        }
        case 0x26u: // especificaciones: 512 bytes por pagina, 16 paginas por bloque, 0x4000 paginas
        {
            const uint8_t specs[8] = {0x00u, 0x02u, 0x10u, 0x00u, 0x00u, 0x40u, 0x00u, 0x00u};
            uint8_t checksum = 0u;
            m_out.push_back(0x2Bu);
            for (uint8_t value : specs)
            {
                checksum ^= value;
                m_out.push_back(value);
            }
            m_out.push_back(checksum);
            m_out.push_back(card.terminator);
            break;
        }
        case 0x27u: // fijar terminador
            card.terminator = popIn();
            m_out.push_back(0x00u);
            m_out.push_back(0x2Bu);
            m_out.push_back(card.terminator);
            break;
        case 0x28u: // leer terminador
            m_out.push_back(0x2Bu);
            m_out.push_back(card.terminator);
            m_out.push_back(card.terminator);
            break;
        case 0x42u: // escribir datos en la pagina actual
        {
            const uint8_t length = popIn();
            m_out.push_back(0x00u);
            m_out.push_back(0x2Bu);
            std::vector<uint8_t> data(length);
            uint8_t checksum = 0u;
            for (uint8_t &value : data)
            {
                value = popIn();
                checksum ^= value;
                m_out.push_back(0x00u);
            }
            card.write(data.data(), data.size());
            m_out.push_back(checksum);
            m_out.push_back(card.terminator);
            break;
        }
        case 0x43u: // leer datos de la pagina actual
        {
            const uint8_t length = popIn();
            m_out.push_back(0x00u);
            m_out.push_back(0x2Bu);
            std::vector<uint8_t> data(length);
            card.read(data.data(), data.size());
            uint8_t checksum = 0u;
            for (uint8_t value : data)
            {
                checksum ^= value;
                m_out.push_back(value);
            }
            m_out.push_back(checksum);
            m_out.push_back(card.terminator);
            break;
        }
        case 0x82u: // borrar el bloque (16 paginas) de la pagina fijada
            card.eraseBlock();
            terminator(4u);
            break;
        case 0xBFu:
        case 0xF7u:
            terminator(5u);
            break;
        case 0xF3u: // reinicio de la autenticacion
            card.terminator = 0x55u;
            terminator(5u);
            break;
        case 0xF0u: // autenticacion MagicGate: se acepta sin cifrado (secrman va por HLE)
        {
            const uint8_t step = popIn();
            switch (step)
            {
            case 0x01u:
            case 0x02u:
            case 0x04u:
            case 0x0Fu:
            case 0x11u:
            case 0x13u:
            {
                m_out.push_back(0x00u);
                m_out.push_back(0x2Bu);
                uint8_t checksum = 0u;
                for (int i = 0; i < 8; ++i)
                {
                    checksum ^= popIn();
                    m_out.push_back(0x00u);
                }
                m_out.push_back(checksum);
                m_out.push_back(card.terminator);
                break;
            }
            case 0x06u:
            case 0x07u:
            case 0x0Bu:
                terminator(14u);
                break;
            default:
                terminator(5u);
                break;
            }
            break;
        }
        default:
            std::cerr << "[SIO2] comando de memory card no emulado 0x" << std::hex << static_cast<int>(command)
                      << std::dec << std::endl;
            break;
        }
        m_in.clear();
    }

    void Sio2::dmaIn(const uint8_t *source, size_t blockBytes, size_t blocks)
    {
        m_dmaBlockSize = blockBytes;
        for (size_t i = 0; i < blockBytes * blocks; ++i)
            writeFifo(source[i]);
    }

    void Sio2::dmaOut(uint8_t *destination, size_t bytes)
    {
        for (size_t i = 0; i < bytes; ++i)
            destination[i] = readFifo();
    }
}
