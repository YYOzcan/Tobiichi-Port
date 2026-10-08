// GOW-Port: preservar el pixel CT24/Z24 que atraviesa dos bloques de IMAGE.
#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

struct GSUpload24State
{
    std::array<uint8_t, 3> bytes{};
    uint32_t size = 0u;

    // El receptor devuelve false cuando termina la transferencia; su padding se descarta.
    // Solo copiar hasta dos bytes pendientes; entregar el resto directamente al backend.
    template <typename Receiver>
    void consume(const uint8_t *data, uint32_t length, Receiver receive)
    {
        uint32_t offset = 0u;
        if (size)
        {
            const uint32_t copy = std::min(3u - size, length);
            std::memcpy(bytes.data() + size, data, copy);
            size += copy;
            offset += copy;
            if (size < 3u) return;
            size = 0u;
            if (!receive(bytes.data(), 3u)) return;
        }
        const uint32_t aligned = ((length - offset) / 3u) * 3u;
        if (aligned && !receive(data + offset, aligned)) return;
        offset += aligned;
        size = length - offset;
        if (size) std::memcpy(bytes.data(), data + offset, size);
    }
};
