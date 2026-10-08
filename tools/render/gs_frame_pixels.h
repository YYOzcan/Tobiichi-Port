// GOW-Port: comparar/exportar la imagen visible, con el layout explícito de cada backend.
#pragma once
#include "runtime/gs/gs_types.h"
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

namespace GowRenderTool {
enum class PixelLayout { Packed, HostRows640 };
inline bool normalize(const PresentationFrame& frame, std::vector<uint8_t>& out,
                      PixelLayout layout = PixelLayout::Packed, size_t* rowStride = nullptr)
{
    out.clear();
    if (rowStride) *rowStride = 0;
    if (frame.width == 0 && frame.height == 0 && frame.pixels.empty()) return true;
    if (!frame.width || !frame.height || frame.width > 640 || frame.height > 512) return false;
    const size_t packed = size_t(frame.width) * frame.height * 4;
    size_t stride = 0;
    if (layout == PixelLayout::Packed) {
        if (frame.pixels.size() != packed) return false;
        stride = frame.width;
    } else if (layout == PixelLayout::HostRows640) {
        // Contrato explícito de los backends locales: filas640 y altura visible
        // o reserva completa512. No adivinar si un buffer ambiguo usa filas width.
        if (frame.pixels.size() != size_t(640) * frame.height * 4 &&
            frame.pixels.size() != size_t(640) * 512 * 4) return false;
        stride = 640;
    } else return false;
    if (rowStride) *rowStride = stride;
    out.resize(packed);
    for (unsigned y = 0; y < frame.height; ++y)
        std::memcpy(out.data() + size_t(y) * frame.width * 4,
                    frame.pixels.data() + size_t(y) * stride * 4, size_t(frame.width) * 4);
    return true;
}

inline bool writePpm(const std::filesystem::path& path, const PresentationFrame& frame,
                     PixelLayout layout = PixelLayout::Packed)
{
    std::vector<uint8_t> pixels;
    if (!normalize(frame, pixels, layout) || pixels.empty()) return false;
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;
    out << "P6\n" << frame.width << ' ' << frame.height << "\n255\n";
    for (size_t i = 0; i < pixels.size(); i += 4)
        out.write(reinterpret_cast<const char*>(pixels.data() + i), 3);
    return bool(out);
}
}
