#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_swizzle.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <vector>
#include <xmmintrin.h>

// GOW-Port: comparación sintética de feedback bilineal, sin datos del juego.
namespace {
constexpr unsigned kWidth = 64, kHeight = 64;
constexpr unsigned kSourceBytes = 16384, kDisjointBase = 2u << 20;
using Frame = std::array<uint32_t, kWidth * kHeight>;

Frame frame(const std::vector<uint8_t>& bytes)
{
    Frame out{}; const auto& fmt = GSSwizzle::GetFormat(GS_PSM_CT32);
    for (unsigned y = 0; y < kHeight; ++y)
        for (unsigned x = 0; x < kWidth; ++x) {
            const auto loc = GSSwizzle::Locate(fmt, 0, 1, x, y);
            out[y * kWidth + x] = GSSwizzle::LoadAt(fmt, bytes.data() + loc.byte, loc.shift);
        }
    return out;
}

unsigned byteDifferences(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b)
{
    if (a.size() != b.size()) return UINT32_MAX;
    unsigned count = 0;
    for (size_t i = 0; i < a.size(); ++i) count += a[i] != b[i];
    return count;
}

void compare(const char* name, const Frame& a, const Frame& b)
{
    unsigned pixels = 0, bytes = 0, rows = 0;
    for (unsigned y = 0; y < kHeight; ++y) {
        unsigned row = 0;
        for (unsigned x = 0; x < kWidth; ++x) {
            const uint32_t difference = a[y * kWidth + x] ^ b[y * kWidth + x];
            if (!difference) continue;
            ++pixels; ++row;
            for (unsigned c = 0; c < 4; ++c) bytes += ((difference >> (c * 8u)) & 255u) != 0;
        }
        if (row) { ++rows; std::printf("%s row=%u pixels=%u\n", name, y, row); }
    }
    std::printf("%s framebufferPixels=%u framebufferBytes=%u rows=%u\n", name, pixels, bytes, rows);
}

GSPrimitiveBatch batch(bool disjoint)
{
    GSPrimitiveBatch b{}; b.vertexCount = 2; b.state.prim.type = GS_PRIM_SPRITE;
    b.state.prim.tme = true; b.state.prim.fst = true;
    b.state.linearFilter = true; b.state.textureWidth = kWidth; b.state.textureHeight = kHeight;
    b.state.colclamp = 1;
    auto& c = b.state.context;
    c.frame.fbw = 1; c.frame.psm = GS_PSM_CT32; c.frame.fbmsk = 0xFF000000u;
    c.scissor = {0, 63, 0, 63}; c.zbuf.zbp = 32; c.zbuf.psm = GS_PSM_Z32; c.zbuf.zmask = true;
    c.test = 1ull << 17; c.clamp = 5;
    c.tex0.psm = GS_PSM_CT32; c.tex0.tbw = 1; c.tex0.tw = 6; c.tex0.th = 6;
    c.tex0.tcc = 1; c.tex0.tfx = 0; c.tex0.tbp0 = disjoint ? kDisjointBase / 256u : 0;
    for (auto& v : b.vertices) { v.r = v.g = v.b = v.a = 128; v.z = 7; }
    b.vertices[1].x = 32; b.vertices[1].y = 64;
    b.vertices[1].u = 32 * 16; b.vertices[1].v = 64 * 16;
    return b;
}
}

int main()
{
    struct Restore { unsigned csr = _mm_getcsr(); ~Restore(){ _mm_setcsr(csr); } } restore;
    _mm_setcsr(_mm_getcsr() & ~_MM_ROUND_MASK);
    std::vector<uint8_t> initial(GSSwizzle::kMemorySize);
    const auto& fmt = GSSwizzle::GetFormat(GS_PSM_CT32);
    for (unsigned y = 0; y < kHeight; ++y)
        for (unsigned x = 0; x < kWidth; ++x) {
            const uint32_t color = 0x80000000u | ((x * 37u + y * 13u + x * y * 3u) & 255u) |
                (((x * 11u + y * 29u) & 255u) << 8u) | (((x * x * 5u + y * 47u) & 255u) << 16u);
            const auto loc = GSSwizzle::Locate(fmt, 0, 1, x, y);
            if (loc.byte + 4 > kSourceBytes) return 2;
            std::memcpy(initial.data() + loc.byte, &color, 4);
        }
    std::array<Frame, 2> cpuFrames{};
    std::array<std::array<Frame, 2>, 2> gpuFrames{};
    for (unsigned variant = 0; variant < 2; ++variant) {
        const bool disjoint = variant != 0;
        auto input = initial; const auto b = batch(disjoint);
        if (disjoint) {
            std::memcpy(input.data() + kDisjointBase, input.data(), kSourceBytes);
            unsigned checked = 0;
            // CLAMP remapea vecinos -1 de las primeras coordenadas a 0.
            for (int rawY = -1; rawY < 64; ++rawY)
                for (int rawX = -1; rawX < 32; ++rawX) {
                    const unsigned x = unsigned(std::clamp(rawX, 0, 63));
                    const unsigned y = unsigned(std::clamp(rawY, 0, 63));
                    const auto from = GSSwizzle::Locate(fmt, 0, 1, x, y);
                    const auto to = GSSwizzle::Locate(fmt, kDisjointBase / 256u, 1, x, y);
                    if (from.byte + 4 > kSourceBytes || to.byte != from.byte + kDisjointBase ||
                        to.byte + 4 > input.size() || to.byte < kSourceBytes ||
                        std::memcmp(initial.data() + from.byte, input.data() + to.byte, 4)) return 2;
                    ++checked;
                }
            std::printf("synthetic disjoint coverage checks=%u firstNeighbor=(-1,-1)->(0,0)\n", checked);
        }
        auto cpuInput = input;
        GSCpuBackend cpu; cpu.Initialize(cpuInput.data(), uint32_t(cpuInput.size())); cpu.Submit(b);
        std::vector<uint8_t> expected; cpu.SnapshotVram(expected); cpuFrames[variant] = frame(expected);
        for (unsigned repeat = 0; repeat < 2; ++repeat) {
            auto gpuInput = input;
            auto candidate = std::make_unique<GSGpuBackend>(); auto* gpu = candidate.get();
            gpu->SetHardwareRasterAllowed(false);
            GSThreadedBackend gl(std::move(candidate)); gl.Initialize(gpuInput.data(), uint32_t(gpuInput.size()));
            // GOW-Port: el fallback puede destruir candidate; comprobar la identidad antes de usar gpu.
            if (dynamic_cast<GSGpuBackend*>(&gl.Inner()) != gpu || !gpu->IsReady()) {
                std::fprintf(stderr, "Se requiere OpenGL compute; el fallback CPU no sirve para esta comparacion.\n");
                return 2;
            }
            gl.Submit(b); gl.Sync(GSSyncReason::DebugReadback);
            std::vector<uint8_t> actual; gl.SnapshotVram(actual);
            gpuFrames[variant][repeat] = frame(actual);
            std::printf("variant=%u repeat=%u CPUvsGPUfullVRAMBytes=%u\n", variant, repeat,
                        byteDifferences(expected, actual));
            char label[64]; std::snprintf(label, sizeof(label), "CPUvsGPU variant=%u repeat=%u", variant, repeat);
            compare(label, cpuFrames[variant], gpuFrames[variant][repeat]);
        }
        compare(disjoint ? "GPU disjoint repeats" : "GPU mutable repeats", gpuFrames[variant][0], gpuFrames[variant][1]);
    }
    compare("CPU mutable vs disjoint", cpuFrames[0], cpuFrames[1]);
    for (unsigned repeat = 0; repeat < 2; ++repeat)
        compare("GPU mutable vs disjoint", gpuFrames[0][repeat], gpuFrames[1][repeat]);
    return 0;
}
