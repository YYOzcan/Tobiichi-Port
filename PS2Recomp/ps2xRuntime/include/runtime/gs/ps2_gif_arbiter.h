#ifndef PS2_GIF_ARBITER_H
#define PS2_GIF_ARBITER_H

#include <array>
#include <cstdint>
#include <functional>
#include <vector>

enum class GifPathId : uint8_t
{
    Path1 = 1,
    Path2 = 2,
    Path3 = 3,
};

struct GifArbiterPacket
{
    GifPathId pathId;
    bool path2DirectHl = false;
    bool path3Image = false;
    std::vector<uint8_t> data;
};

class GifArbiter
{
public:
    using ProcessPacketFn = std::function<void(const uint8_t *, uint32_t)>;
    // GOW-Port: identificar el flujo sin romper los callbacks existentes de dos argumentos.
    using ProcessPathPacketFn = std::function<void(GifPathId, const uint8_t *, uint32_t)>;

    GifArbiter() = default;
    explicit GifArbiter(ProcessPacketFn processFn);

    void setProcessPacketFn(ProcessPacketFn fn);
    void setProcessPathPacketFn(ProcessPathPacketFn fn) { m_processFn = std::move(fn); }
    void reset() { m_queue.clear(); m_path3Input = {}; }

    void submit(GifPathId pathId, const uint8_t *data, uint32_t sizeBytes, bool path2DirectHl = false);

    void drain();
    bool empty() const { return m_queue.empty(); }

private:
    ProcessPathPacketFn m_processFn;
    std::vector<GifArbiterPacket> m_queue;

    // GOW-Port: el primer quadword de un bloque DMA puede ser payload, no una GIFtag.
    struct Path3InputState
    {
        std::array<uint8_t, 16> tag{};
        uint32_t tagBytes = 0u;
        uint32_t payloadBytes = 0u;
        uint8_t format = 0u;
    } m_path3Input;

    bool trackPath3Packet(const uint8_t *data, uint32_t sizeBytes);
    static uint8_t pathPriority(GifPathId id);
};

#endif
