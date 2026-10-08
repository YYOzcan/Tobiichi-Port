// GOW-Port: layouts visibles y Present real de CPU, sin datos del juego.
#include "../tools/render/gs_frame_pixels.h"
#include "runtime/gs/gs_cpu_backend.h"
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <string>

namespace {
unsigned failures = 0;
void test(const char* name, bool condition)
{
    std::printf("%s: %s\n", name, condition ? "OK" : "FAIL"); failures += !condition;
}
PresentationFrame synthetic(unsigned stride, unsigned rows)
{
    PresentationFrame frame{}; frame.width = 3; frame.height = 2;
    frame.pixels.assign(size_t(stride) * rows * 4, 0xa5);
    for (unsigned y = 0; y < 2; ++y)
        for (unsigned x = 0; x < 3; ++x) {
            auto* p = frame.pixels.data() + (size_t(y) * stride + x) * 4;
            p[0] = uint8_t(11 + x); p[1] = uint8_t(21 + y); p[2] = uint8_t(31 + x + y); p[3] = 255;
        }
    return frame;
}
}
int main()
{
    namespace frames = GowRenderTool;
    constexpr auto packedLayout = frames::PixelLayout::Packed;
    constexpr auto hostLayout = frames::PixelLayout::HostRows640;
    const auto packed = synthetic(3, 2), gpuPadded = synthetic(640, 2), cpuReserved = synthetic(640, 512);
    std::vector<uint8_t> expected, actual;
    size_t stride = 0;
    test("packed layout", frames::normalize(packed, expected, packedLayout, &stride) && stride == 3 && expected.size() == 24);
    test("GPU640xheight equals packed", frames::normalize(gpuPadded, actual, hostLayout, &stride) && stride == 640 && actual == expected);
    test("CPU640x512 equals packed", frames::normalize(cpuReserved, actual, hostLayout, &stride) && stride == 640 && actual == expected);
    auto changed = gpuPadded;
    changed.pixels[(640 + 1) * 4 + 2] ^= 1;
    test("visible change survives normalization", frames::normalize(changed, actual, hostLayout) && actual != expected && actual[18] != expected[18]);
    unsigned changedBytes = 0;
    for (unsigned i = 0; i < actual.size(); ++i) changedBytes += actual[i] != expected[i];
    test("visible change is exactly one byte", changedBytes == 1);
    auto padding = cpuReserved;
    padding.pixels[3 * 4] ^= 1; padding.pixels[(511 * 640 + 639) * 4] ^= 1;
    test("padding is ignored", frames::normalize(padding, actual, hostLayout) && actual == expected);
    auto bad = gpuPadded; bad.pixels.pop_back();
    test("truncated layout rejected", !frames::normalize(bad, actual, hostLayout) && actual.empty());
    auto ambiguous = gpuPadded; ambiguous.width = 320;
    test("ambiguous untagged padding rejected", !frames::normalize(ambiguous, actual));
    test("explicit host layout resolves ambiguity", frames::normalize(ambiguous, actual, hostLayout) && actual.size() == size_t(320) * 2 * 4);
    test("packed height padding rejected", !frames::normalize(cpuReserved, actual, packedLayout));
    bad = packed; bad.width = 641;
    test("oversized width rejected", !frames::normalize(bad, actual, frames::PixelLayout::HostRows640));
    bad = packed; bad.height = 513;
    test("oversized height rejected", !frames::normalize(bad, actual, frames::PixelLayout::HostRows640));
    bad = {}; bad.width = 3;
    test("partial empty dimensions rejected", !frames::normalize(bad, actual, frames::PixelLayout::HostRows640));
    test("disabled empty frame accepted", frames::normalize({}, actual) && actual.empty());

    const std::filesystem::path ppm("logs/gs_frame_pixels_test.ppm");
    test("CPU-reserved PPM exported", frames::writePpm(ppm, cpuReserved, hostLayout));
    std::ifstream file(ppm, std::ios::binary);
    const std::vector<char> bytes((std::istreambuf_iterator<char>(file)), {});
    const std::string header("P6\n3 2\n255\n");
    std::vector<char> rgb(header.begin(), header.end());
    for (unsigned i = 0; i < expected.size(); i += 4)
        rgb.insert(rgb.end(), expected.begin() + i, expected.begin() + i + 3);
    test("PPM contains visible RGB only", bytes == rgb);
    file.close(); std::filesystem::remove(ppm);

    // Control directo de la API usada por apply(Present), sin GPU ni datos del juego.
    std::vector<uint8_t> vram(4u << 20);
    GSCpuBackend cpu; cpu.Initialize(vram.data(), uint32_t(vram.size()));
    for (unsigned y = 0; y < 2; ++y)
        for (unsigned x = 0; x < 3; ++x) {
            const auto i = (y * 3 + x) * 4;
            const uint32_t color = 0x80000000u | expected[i] | (uint32_t(expected[i + 1]) << 8) | (uint32_t(expected[i + 2]) << 16);
            cpu.WriteVram(GS_PSM_CT32, 0, 1, x, y, color);
        }
    GSPresentationRequest request{}; request.pmode = 1; request.dispfb1 = 1ull << 9;
    // Present acepta displays de al menos 64×64; un display menor activa su fallback NTSC.
    request.display1 = (63ull << 32) | (63ull << 44);
    std::vector<uint8_t> expectedDirect(size_t(64) * 64 * 4);
    for (size_t i = 3; i < expectedDirect.size(); i += 4) expectedDirect[i] = 255;
    for (unsigned y = 0; y < 2; ++y)
        for (unsigned x = 0; x < 3; ++x)
            std::copy_n(expected.data() + (y * 3 + x) * 4, 4,
                        expectedDirect.data() + (y * 64 + x) * 4);
    const auto direct = cpu.Present(request);
    std::printf("directCPU dimensions=%ux%u rawBytes=%zu\n", direct.width, direct.height, direct.pixels.size());
    test("direct CPU Present uses reserved host buffer", direct.width == 64 && direct.height == 64 && direct.pixels.size() == size_t(640) * 512 * 4);
    test("direct CPU Present normalizes expected image", frames::normalize(direct, actual, hostLayout, &stride) && stride == 640 && actual == expectedDirect);
    std::printf("failures=%u\n", failures);
    return failures ? 1 : 0;
}
