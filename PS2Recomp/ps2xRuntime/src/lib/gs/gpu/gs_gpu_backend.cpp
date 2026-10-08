// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_shared_present.h"
#include "runtime/gs/gs_swizzle.h"
#include "runtime/gs/ps2_gs_memory.h"
#include "../gs_gpu_helpers.h"
#include "../gs_sprite_rules.h"
#include "../gs_triangle_rules.h"
#include "gs_gl.h"
#include "gs_gpu_shaders.h"
#include "ThreadNaming.h"
#include "ThreadPriority.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <condition_variable>
#include <deque>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <thread>
#include <filesystem>
#include <fstream>
#include <xmmintrin.h>

using namespace GSGL;
using namespace GSCpuInternal;

namespace
{
    // GOW-Port: la preparación GS conserva el redondeo del productor EE/VU.
    class GSGpuRoundingScope
    {
        const unsigned rounding = _mm_getcsr() & _MM_ROUND_MASK;
    public:
        GSGpuRoundingScope()
        {
            if (rounding != _MM_ROUND_NEAREST)
                _mm_setcsr(_mm_getcsr() & ~_MM_ROUND_MASK);
        }
        ~GSGpuRoundingScope()
        {
            if (rounding != _MM_ROUND_NEAREST)
                _mm_setcsr((_mm_getcsr() & ~_MM_ROUND_MASK) | rounding);
        }
    };
    // GOW-Port: el frontend existente consume filas de 640 píxeles, incluso con CRTC menor.
    PresentationFrame gowPresentationRows(PresentationFrame frame)
    {
        if (frame.pixels.empty() || frame.width == 640u)
            return frame;
        std::vector<uint8_t> rows(static_cast<size_t>(640u) * frame.height * 4u);
        const size_t bytes = static_cast<size_t>(frame.width) * 4u;
        for (uint32_t y = 0; y < frame.height; ++y)
            std::memcpy(rows.data() + static_cast<size_t>(y) * 640u * 4u,
                        frame.pixels.data() + static_cast<size_t>(y) * bytes, bytes);
        frame.pixels = std::move(rows);
        return frame;
    }
    constexpr uint32_t kPrimWords = 40u;
    constexpr uint32_t kStateWords = 32u;
    constexpr uint32_t kTileSize = 16u;
    constexpr uint32_t kTileGrid = 128u;
    constexpr uint32_t kClutSlots = 1024u;
    constexpr uint32_t kPages = 512u;
    constexpr uint32_t kShadowPages = 512u;
    constexpr uint32_t kMaxEpochs = 256u;
    // GOW-Port: el frontend de GoW usa filas de 640 píxeles.
    constexpr uint32_t kMaxPresentationWidth = 640u;
    constexpr uint32_t kMaxPresentationHeight = 2048u;

    enum PrimType : uint32_t
    {
        PrimPoint = 0u,
        PrimSprite = 1u,
        PrimTriangle = 2u,
    };

    enum StateWord : uint32_t
    {
        SFbp = 0u,
        SFbw,
        SFpsm,
        SFbmsk,
        SZbp,
        SZpsm,
        SZmask,
        SScissorX,
        SScissorY,
        STbp0,
        STbw,
        STpsm,
        STexMode,
        SCsa,
        STexSize,
        SClampLo,
        SClampHi,
        SAlpha,
        SAlphaFix,
        STest,
        SFba,
        SFlags,
        STexa,
        SFogCol,
        SClut,
        SEpoch,
    };

    constexpr uint32_t FIip = 1u;
    constexpr uint32_t FTme = 2u;
    constexpr uint32_t FFge = 4u;
    constexpr uint32_t FAbe = 8u;
    constexpr uint32_t FFst = 16u;
    constexpr uint32_t FPabe = 32u;
    constexpr uint32_t FLinear = 64u;
    constexpr uint32_t FWrap = 128u;

    uint32_t fbits(float value)
    {
        uint32_t bits;
        std::memcpy(&bits, &value, sizeof(bits));
        return bits;
    }

    uint32_t packColor(const GSVertex &v)
    {
        return static_cast<uint32_t>(v.r) | (static_cast<uint32_t>(v.g) << 8u) | (static_cast<uint32_t>(v.b) << 16u) |
               (static_cast<uint32_t>(v.a) << 24u);
    }

    struct ClutOp
    {
        uint32_t target = 0;
        uint32_t source = 0;
        uint32_t psm = 0;
        uint32_t cbp = 0;
        uint32_t packed = 0;
        uint32_t cbw = 0;
        uint32_t cou = 0;
        uint32_t cov = 0;
        uint32_t epoch = 0;
        std::array<uint16_t, 32> writers{};
    };

    std::atomic<bool> s_asyncPresent{false};

    constexpr size_t kRingChunk = 16u * 1024u * 1024u;
    constexpr uint32_t kRingChunks = 4u;
    constexpr size_t kRingAlign = 256u;

    struct Readback
    {
        GLuint buffer = 0;
        const uint8_t *mapped = nullptr;
        size_t capacity = 0;
        GLsync fence = nullptr;
        GLuint query = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t displayFbp = 0;
        // GOW-Port: conservar la procedencia de la imagen en el readback diferido.
        uint32_t sourceFbp = 0;
        bool usedPreferred = false;
        uint64_t sequence = 0u;
    };

    struct Program
    {
        GLuint id = 0;
        GLint loc[4] = {-1, -1, -1, -1};
    };

    struct CrtcCircuit
    {
        bool enabled = false;
        uint32_t fbp = 0u;
        uint32_t fbw = 1u;
        uint8_t psm = 0u;
        uint32_t dbx = 0u;
        uint32_t dby = 0u;
        int32_t dx = 0;
        int32_t dy = 0;
        int32_t dw = 0;
        int32_t dh = 0;
        int32_t hdiv = 1;
        int32_t vdiv = 1;
    };

    CrtcCircuit decodeCircuit(bool enabled, uint64_t dispfb, uint64_t display, bool halfHeightBuffer)
    {
        CrtcCircuit c{};
        c.fbp = static_cast<uint32_t>(dispfb & 0x1FFu);
        c.fbw = std::max<uint32_t>(1u, static_cast<uint32_t>((dispfb >> 9) & 0x3Fu));
        c.psm = static_cast<uint8_t>((dispfb >> 15) & 0x1Fu);
        c.dbx = static_cast<uint32_t>((dispfb >> 32) & 0x7FFu);
        c.dby = static_cast<uint32_t>((dispfb >> 43) & 0x7FFu);
        c.dx = static_cast<int32_t>(display & 0xFFFu);
        c.dy = static_cast<int32_t>((display >> 12) & 0x7FFu);
        c.hdiv = static_cast<int32_t>((display >> 23) & 0xFu) + 1;
        c.vdiv = (static_cast<int32_t>((display >> 27) & 0x3u) + 1) * (halfHeightBuffer ? 2 : 1);
        c.dw = static_cast<int32_t>((display >> 32) & 0xFFFu) + 1;
        c.dh = static_cast<int32_t>((display >> 44) & 0x7FFu) + 1;
        c.enabled = enabled && display != 0u && c.dw >= c.hdiv && c.dh >= c.vdiv;
        return c;
    }

    void markPages(std::bitset<kPages> &pages, uint32_t psm, uint32_t base, uint32_t bw, int x0, int y0, int x1, int y1)
    {
        const GSSwizzle::Format &format = GSSwizzle::GetFormat(psm);
        if (format.kind == GSSwizzle::Kind::Invalid || x1 < x0 || y1 < y0)
            return;
        const uint32_t pagesPerRow = (bw * 64u) >> format.pageShiftX;
        const uint32_t basePage = base >> 5u;
        const bool spill = (base & 31u) != 0u;
        const uint32_t px0 = static_cast<uint32_t>(std::max(x0, 0)) >> format.pageShiftX;
        const uint32_t px1 = static_cast<uint32_t>(std::max(x1, 0)) >> format.pageShiftX;
        const uint32_t py0 = static_cast<uint32_t>(std::max(y0, 0)) >> format.pageShiftY;
        const uint32_t py1 = static_cast<uint32_t>(std::max(y1, 0)) >> format.pageShiftY;
        if ((py1 - py0 + 1u) * (px1 - px0 + 1u) >= kPages)
        {
            pages.set();
            return;
        }
        for (uint32_t py = py0; py <= py1; ++py)
            for (uint32_t px = px0; px <= px1; ++px)
            {
                const uint32_t page = basePage + py * pagesPerRow + px;
                pages.set(page % kPages);
                if (spill)
                    pages.set((page + 1u) % kPages);
            }
    }
}

struct GSGpuBackend::Impl
{
    GSGpuBackend::Stats &stats;
    Context context;
    bool initialized = false;
    bool failed = false;
    uint8_t *hostVram = nullptr;
    uint32_t hostVramSize = 0u;

    GLuint vramBuffer = 0;
    GLuint swizzleBuffer = 0;
    GLuint clutBuffer = 0;
    GLuint primBuffer = 0;
    GLuint stateBuffer = 0;
    GLuint tileBuffer = 0;
    GLuint tileListBuffer = 0;
    GLuint dataBuffer = 0;
    GLuint clutOpBuffer = 0;
    std::vector<uint32_t> clutOpWords;
    std::array<uint16_t, 32> clutWriters{};
    size_t dataCapacity = 0;
    GLuint ringBuffer = 0;
    uint8_t *ring = nullptr;
    uint32_t ringChunk = 0u;
    size_t ringOffset = 0u;
    std::array<GLsync, kRingChunks> ringFences{};

    Program raster;
    Program clutLoad;
    Program upload;
    Program copyRead;
    Program copyWrite;
    Program clear;
    Program poke;
    Program present;
    Program presentHash;
    Program pageCopy;
    Program hwRaster;
    GLuint hwFramebuffer = 0;
    GLuint hwVertexArray = 0;
    bool hwEnabled = false;
    bool hwAllowed = true;
    bool hwConservative = false;
    GLuint hwVertexShader = 0;
    std::string hwFragmentHead;
    std::string hwFragmentBody;
    using HwKey = std::array<uint32_t, 11>;
    std::map<HwKey, Program> hwVariants;
    struct CompileJob
    {
        HwKey key{};
        std::string fragment;
        std::string cacheKey;
        std::filesystem::path cachePath;
    };
    struct CompileResult
    {
        HwKey key{};
        GLuint program = 0;
        bool fromCache = false;
        double ms = 0.0;
    };
    std::set<HwKey> hwRequested;
    std::deque<CompileJob> hwJobs;
    std::vector<CompileResult> hwResults;
    std::mutex hwCompileMutex;
    std::condition_variable hwCompileCv;
    bool hwCompileStop = false;
    std::thread hwCompiler;
    void *hwWorkerContext = nullptr;
    struct HwRun
    {
        const Program *program;
        uint32_t first;
        uint32_t last;
    };
    std::vector<HwRun> hwRuns;
    double hwRingWaitMs = 0.0;
    double hwVariantMs = 0.0;
    std::string hwVertexSource;

    std::vector<uint32_t> prims;
    uint32_t primCount = 0u;
    std::vector<uint32_t> states;
    std::array<uint32_t, kStateWords> lastState{};
    uint32_t stateCount = 0u;
    std::vector<std::vector<uint32_t>> bins;
    std::vector<uint32_t> touched;
    std::vector<uint32_t> tileHeaders;
    std::vector<uint32_t> tileList;
    std::bitset<kPages> writePages;
    // GOW-Port: color y profundidad pueden compartir VRAM con swizzles distintos.
    std::bitset<kPages> colorPages;
    std::bitset<kPages> depthAccessPages;
    std::bitset<kPages> batchClutPages;
    bool deferUploads = true;
    std::vector<uint32_t> pageMaps;
    std::array<uint32_t, kPages> firstLiveEpoch{};
    uint32_t epoch = 0u;
    uint32_t shadowNext = 0u;
    uint32_t batchClutLoads = 0u;
    std::vector<uint32_t> copyPairs;
    std::vector<uint32_t> uploadWords;
    std::vector<uint32_t> uploadGroups;
    std::vector<uint32_t> uploadData_;
    uint32_t uploadCount = 0u;
    std::bitset<kPages> pendingWritePages;
    std::bitset<kPages> transferPages;
    bool transferQueued = false;
    GLuint pageMapBuffer = 0;
    std::bitset<kPages> readPages;
    bool cacheTexturePages = true;
    bool fastTriangleSetup = true;
    bool texturePagesValid = false;
    std::array<uint32_t, 8> texturePagesKey{};
    std::bitset<kPages> texturePages;
    uint64_t targetKey = 0u;
    bool hasTarget = false;
    std::vector<ClutOp> clutOps;
    uint32_t clutSlot = 0u;
    bool clutKeyValid = false;
    std::array<uint32_t, 6> clutKey{};
    std::bitset<kPages> clutSourcePages;
    std::array<uint32_t, 2> clutCbp{};

    std::array<Readback, 3> readbacks{};
    uint32_t readbackNext = 0u;
    uint64_t readbackSequence = 0u;
    uint64_t lastFrameSequence = 0u;
    PresentationFrame lastFrame;
    uint64_t contentRevision = 1u;
    uint64_t presentedRevision = 0u;
    // GOW-Port: incluir la fuente preferida en la clave de presentación compartida.
    std::array<uint64_t, 11> presentedCrtc{};
    uint64_t renderedSequence = 0u;

    struct PresentStats
    {
        bool enabled = false;
        bool queryOpen = false;
        std::array<GLuint, 4> queries{};
        uint32_t queryNext = 0u;
        uint32_t frames = 0u;
        uint64_t gpuNs = 0u;
        uint64_t gpuFrames = 0u;
        std::chrono::steady_clock::duration wait{};
        std::chrono::steady_clock::duration submit{};
        std::chrono::steady_clock::time_point windowStart = std::chrono::steady_clock::now();
        uint64_t batches = 0u;
        uint64_t clutLoads = 0u;
        uint64_t transfers = 0u;
        uint64_t lastPrims = 0u;
        uint32_t drawn = 0u;
        uint32_t readbackSkips = 0u;
        uint32_t sharedSkips = 0u;
        uint32_t composites = 0u;
    } presentStats;

    struct GpuProf
    {
        struct Pending
        {
            uint32_t kind;
            GLuint begin;
            GLuint end;
            std::array<uint32_t, 8> info;
        };
        std::vector<std::pair<uint64_t, std::array<uint32_t, 8>>> rasterTimes;
        std::array<uint32_t, 8> nextInfo{};
        bool enabled = false;
        std::vector<GLuint> freeQueries;
        std::vector<Pending> pending;
        std::array<uint64_t, 8> ns{};
        std::array<uint64_t, 8> count{};
        uint64_t pairs = 0u;
        uint64_t tiles = 0u;
        uint64_t maxBin = 0u;
        uint64_t sumMaxBin = 0u;
        uint64_t prims = 0u;
        uint64_t frames = 0u;
        std::array<uint64_t, 6> reasons{};
        std::array<uint64_t, 3> uploadHazards{};
    } prof;

    void flushFor(uint32_t reason)
    {
        if (prof.enabled && primCount != 0u)
            ++prof.reasons[reason];
        flushBatch();
    }

    GLuint profQuery()
    {
        if (prof.freeQueries.empty())
        {
            prof.freeQueries.resize(256u);
            gl().GenQueries(256, prof.freeQueries.data());
        }
        const GLuint query = prof.freeQueries.back();
        prof.freeQueries.pop_back();
        return query;
    }

    GLuint profBegin()
    {
        if (!prof.enabled)
            return 0u;
        const GLuint query = profQuery();
        gl().QueryCounter(query, kTimestamp);
        return query;
    }

    void profEnd(uint32_t kind, GLuint begin)
    {
        if (!prof.enabled)
            return;
        const GLuint end = profQuery();
        gl().QueryCounter(end, kTimestamp);
        prof.pending.push_back({kind, begin, end, prof.nextInfo});
        prof.nextInfo = {};
        if (prof.pending.size() >= 4096u)
            profResolve();
    }

    void profFrame()
    {
        if (!prof.enabled)
            return;
        profResolve();
        if (++prof.frames < 4u)
            return;
        profReport();
    }

    void profResolve()
    {
        for (const GpuProf::Pending &item : prof.pending)
        {
            GLuint64 a = 0u;
            GLuint64 b = 0u;
            gl().GetQueryObjectui64v(item.begin, kQueryResult, &a);
            gl().GetQueryObjectui64v(item.end, kQueryResult, &b);
            prof.ns[item.kind] += b - a;
            if (item.kind == 0u)
                prof.rasterTimes.push_back({b - a, item.info});
            ++prof.count[item.kind];
            prof.freeQueries.push_back(item.begin);
            prof.freeQueries.push_back(item.end);
        }
        prof.pending.clear();
    }

    void profReport()
    {
        prof.frames = std::max<uint64_t>(prof.frames, 1u);
        static const char *kNames[8] = {"raster", "clut", "upload", "copyRead", "copyWrite", "present", "clear", "other"};
        std::fprintf(stderr, "[gs-gpu-prof] per frame:");
        for (uint32_t kind = 0; kind < 8u; ++kind)
            if (prof.count[kind] != 0u)
                std::fprintf(stderr, " %s %.2f ms (%.0f)", kNames[kind], prof.ns[kind] / 1e6 / prof.frames,
                             static_cast<double>(prof.count[kind]) / prof.frames);
        std::fprintf(stderr, " | prims %.0f tiles %.0f pairs %.0f maxBin %llu\n", static_cast<double>(prof.prims) / prof.frames,
                     static_cast<double>(prof.tiles) / prof.frames, static_cast<double>(prof.pairs) / prof.frames,
                     static_cast<unsigned long long>(prof.maxBin));
        std::fprintf(stderr, "[gs-gpu-prof] flushes: target %llu texture %llu clut %llu transfer %llu external %llu sync %llu\n",
                     static_cast<unsigned long long>(prof.reasons[0]), static_cast<unsigned long long>(prof.reasons[1]),
                     static_cast<unsigned long long>(prof.reasons[2]), static_cast<unsigned long long>(prof.reasons[3]),
                     static_cast<unsigned long long>(prof.reasons[4]), static_cast<unsigned long long>(prof.reasons[5]));
        prof.reasons = {};
        std::fprintf(stderr, "[gs-gpu-prof] upload hazards: target %llu clut %llu texture-read %llu\n", static_cast<unsigned long long>(prof.uploadHazards[0]),
                     static_cast<unsigned long long>(prof.uploadHazards[1]), static_cast<unsigned long long>(prof.uploadHazards[2]));
        prof.uploadHazards = {};
        std::fprintf(stderr, "[gs-gpu-prof] sum of per-dispatch longest bins %.0f per frame\n", static_cast<double>(prof.sumMaxBin) / prof.frames);
        std::sort(prof.rasterTimes.begin(), prof.rasterTimes.end(), [](const auto &l, const auto &r) { return l.first > r.first; });
        for (size_t i = 0; i < std::min<size_t>(prof.rasterTimes.size(), 15u); ++i)
        {
            const auto &[ns, info] = prof.rasterTimes[i];
            std::fprintf(stderr, "[gs-gpu-prof]   %.2f ms prims %u tiles %u pairs %u maxBin %u fbp %x fpsm %x zbp %x flags %x\n", ns / 1e6, info[0], info[1],
                         info[2], info[3], info[4], info[5], info[6], info[7]);
        }
        std::map<std::pair<uint32_t, uint32_t>, std::array<uint64_t, 4>> byTarget;
        for (const auto &[ns, info] : prof.rasterTimes)
        {
            auto &entry = byTarget[{info[4], info[7]}];
            entry[0] += ns;
            entry[1] += 1u;
            entry[2] += info[2];
            entry[3] += info[0];
        }
        std::vector<std::pair<uint64_t, std::pair<uint32_t, uint32_t>>> targets;
        for (const auto &[key, entry] : byTarget)
            targets.push_back({entry[0], key});
        std::sort(targets.rbegin(), targets.rend());
        for (size_t i = 0; i < std::min<size_t>(targets.size(), 20u); ++i)
        {
            const auto &entry = byTarget[targets[i].second];
            std::fprintf(stderr, "[gs-gpu-prof]   target fbp %x flags %x: %.2f ms in %llu dispatches, %llu pairs, %llu prims\n", targets[i].second.first,
                         targets[i].second.second, entry[0] / 1e6 / prof.frames, static_cast<unsigned long long>(entry[1]),
                         static_cast<unsigned long long>(entry[2]), static_cast<unsigned long long>(entry[3]));
        }
        prof.rasterTimes.clear();
        std::fflush(stderr);
        prof.ns = {};
        prof.count = {};
        prof.pairs = prof.tiles = prof.prims = prof.maxBin = prof.sumMaxBin = 0u;
        prof.frames = 0u;
    }

    GSTransferCommand transfer{};
    GSTransferSnapshot transferState{};
    GSUpload24State upload24{}; // GOW-Port: pixel de 24 bits pendiente entre bloques IMAGE.
    std::vector<uint8_t> localToHost;
    size_t localToHostReadPos = 0u;
    std::vector<uint32_t> scratch;

    explicit Impl(GSGpuBackend::Stats &s) : stats(s)
    {
        const char *statsValue = std::getenv("PS2X_GS_GPU_STATS");
        presentStats.enabled = statsValue && *statsValue && *statsValue != '0';
        const char *profValue = std::getenv("PS2X_GS_GPU_PROF");
        prof.enabled = profValue && *profValue && *profValue != '0';
        const char *deferValue = std::getenv("PS2X_GS_GPU_DEFER_UPLOADS");
        deferUploads = !(deferValue && *deferValue == '0');
        bins.resize(kTileGrid * kTileGrid);
        transfer.direction = 3u;
        transferState.direction = 3u;
    }

    ~Impl()
    {
        stopCompileWorker();
        if (initialized && prof.enabled)
        {
            profResolve();
            profReport();
        }
        if (initialized)
        {
            const Api &gl = context.gl();
            if (context.Shared())
                DestroyShared(gl);
            for (Readback &slot : readbacks)
            {
                if (slot.fence)
                    gl.DeleteSync(slot.fence);
                if (slot.buffer)
                    gl.DeleteBuffers(1, &slot.buffer);
            }
            for (GLuint query : presentStats.queries)
                if (query)
                    gl.DeleteQueries(1, &query);
            const GLuint buffers[] = {vramBuffer, swizzleBuffer, clutBuffer, primBuffer, stateBuffer, tileBuffer, tileListBuffer, dataBuffer, clutOpBuffer, pageMapBuffer};
            gl.DeleteBuffers(static_cast<GLsizei>(std::size(buffers)), buffers);
            for (Program *program : {&raster, &clutLoad, &upload, &copyRead, &copyWrite, &clear, &poke, &present, &presentHash, &pageCopy, &hwRaster})
                if (program->id)
                    gl.DeleteProgram(program->id);
            if (hwFramebuffer)
                gl.DeleteFramebuffers(1, &hwFramebuffer);
            if (hwVertexArray)
                gl.DeleteVertexArrays(1, &hwVertexArray);
            for (auto &[key, program] : hwVariants)
                if (program.id)
                    gl.DeleteProgram(program.id);
            if (hwVertexShader)
                gl.DeleteShader(hwVertexShader);
        }
    }

    const Api &gl() const
    {
        return context.gl();
    }

    GLuint makeBuffer(size_t size, const void *data, GLuint binding)
    {
        GLuint buffer = 0;
        gl().GenBuffers(1, &buffer);
        gl().BindBuffer(kShaderStorageBuffer, buffer);
        gl().BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(size), data, kDynamicDraw);
        gl().BindBufferBase(kShaderStorageBuffer, binding, buffer);
        return buffer;
    }

    size_t ringPut(const void *data, size_t size)
    {
        const size_t payloadSize = size;
        size = std::max<size_t>(size, 16u);
        if (!ring || size > kRingChunk)
            return SIZE_MAX;
        ringOffset = (ringOffset + kRingAlign - 1u) & ~(kRingAlign - 1u);
        if (ringOffset + size > kRingChunk)
        {
            ringFences[ringChunk] = gl().FenceSync(kSyncGpuCommandsComplete, 0u);
            ringChunk = (ringChunk + 1u) % kRingChunks;
            if (GLsync fence = ringFences[ringChunk])
            {
                const auto waitStart = std::chrono::steady_clock::now();
                gl().ClientWaitSync(fence, kSyncFlushCommandsBit, 5000000000ull);
                hwRingWaitMs += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - waitStart).count();
                gl().DeleteSync(fence);
                ringFences[ringChunk] = nullptr;
            }
            ringOffset = 0u;
        }
        const size_t offset = static_cast<size_t>(ringChunk) * kRingChunk + ringOffset;
        if (data)
        {
            std::memcpy(ring + offset, data, payloadSize);
            if (payloadSize < size)
                std::memset(ring + offset + payloadSize, 0, size - payloadSize);
        }
        ringOffset += size;
        return offset;
    }

    void bindUpload(GLuint binding, GLuint fallbackBuffer, const void *data, size_t size)
    {
        const size_t offset = ringPut(data, size);
        if (offset == SIZE_MAX)
        {
            setBuffer(fallbackBuffer, size, data);
            gl().BindBufferBase(kShaderStorageBuffer, binding, fallbackBuffer);
            return;
        }
        gl().BindBufferRange(kShaderStorageBuffer, binding, ringBuffer, static_cast<GLintptr>(offset),
                             static_cast<GLsizeiptr>(std::max<size_t>(size, 16u)));
    }

    void setBuffer(GLuint buffer, size_t size, const void *data)
    {
        gl().BindBuffer(kShaderStorageBuffer, buffer);
        gl().BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(std::max<size_t>(size, 16u)), nullptr, kStreamDraw);
        if (size != 0u && data)
            gl().BufferSubData(kShaderStorageBuffer, 0, static_cast<GLsizeiptr>(size), data);
    }

    bool compile(Program &program, const std::string &prefix, const char *body, std::initializer_list<const char *> uniforms)
    {
        const std::string source = prefix + GSGpuShaders::kCommon + body;
        const auto fingerprint = [](const void *data, size_t size)
        {
            uint64_t value = 14695981039346656037ull;
            const auto *bytes = static_cast<const uint8_t *>(data);
            for (size_t i = 0; i < size; ++i)
                value = (value ^ bytes[i]) * 1099511628211ull;
            return value;
        };
        const auto bindUniforms = [&]
        {
            size_t index = 0u;
            for (const char *name : uniforms)
                program.loc[index++] = gl().GetUniformLocation(program.id, name);
        };
        const std::string driver = std::string(reinterpret_cast<const char *>(gl().GetString(kVendor))) + "\n" +
            reinterpret_cast<const char *>(gl().GetString(kRenderer)) + "\n" + reinterpret_cast<const char *>(gl().GetString(kVersion));
        std::filesystem::path cachePath;
        const char *cache = std::getenv("PS2X_GS_SHADER_CACHE");
        if (!cache || *cache != '0')
            if (const char *directory = std::getenv("PS2X_GS_SHADER_CACHE_DIR"))
            {
                const std::string key = driver + "\n" + source;
                char name[32];
                std::snprintf(name, sizeof(name), "%016llx.glbin", static_cast<unsigned long long>(fingerprint(key.data(), key.size())));
                cachePath = std::filesystem::path(directory) / name;
            }
        if (!cachePath.empty())
        {
            std::ifstream input(cachePath, std::ios::binary);
            std::array<uint32_t, 5> header{};
            uint64_t checksum = 0u;
            input.read(reinterpret_cast<char *>(header.data()), sizeof(header));
            input.read(reinterpret_cast<char *>(&checksum), sizeof(checksum));
            if (input && header[0] == 0x31425347u && header[2] == driver.size() && header[3] == source.size() &&
                header[4] != 0u && header[4] <= 256u * 1024u * 1024u)
            {
                std::string storedDriver(driver.size(), '\0');
                std::string storedSource(source.size(), '\0');
                std::vector<uint8_t> binary(header[4]);
                input.read(storedDriver.data(), storedDriver.size());
                input.read(storedSource.data(), storedSource.size());
                input.read(reinterpret_cast<char *>(binary.data()), binary.size());
                if (input && storedDriver == driver && storedSource == source && fingerprint(binary.data(), binary.size()) == checksum)
                {
                    program.id = gl().CreateProgram();
                    gl().ProgramBinary(program.id, header[1], binary.data(), static_cast<GLsizei>(binary.size()));
                    GLint linked = 0;
                    gl().GetProgramiv(program.id, kLinkStatus, &linked);
                    if (linked)
                    {
                        bindUniforms();
                        std::fprintf(stderr, "[gs-gpu] shader binary cache hit %s\n", cachePath.filename().string().c_str());
                        return true;
                    }
                    gl().DeleteProgram(program.id);
                    program.id = 0u;
                }
            }
        }
        const char *text = source.c_str();
        const GLuint shader = gl().CreateShader(kComputeShader);
        gl().ShaderSource(shader, 1, &text, nullptr);
        gl().CompileShader(shader);
        GLint ok = 0;
        gl().GetShaderiv(shader, kCompileStatus, &ok);
        if (!ok)
        {
            GLint length = 0;
            gl().GetShaderiv(shader, kInfoLogLength, &length);
            std::string log(static_cast<size_t>(std::max(length, 1)), '\0');
            gl().GetShaderInfoLog(shader, length, nullptr, log.data());
            std::fprintf(stderr, "[gs-gpu] shader compile failed:\n%s\n", log.c_str());
            std::fflush(stderr);
            gl().DeleteShader(shader);
            return false;
        }
        program.id = gl().CreateProgram();
        if (!cachePath.empty())
            gl().ProgramParameteri(program.id, kProgramBinaryRetrievableHint, 1);
        gl().AttachShader(program.id, shader);
        gl().LinkProgram(program.id);
        gl().DeleteShader(shader);
        gl().GetProgramiv(program.id, kLinkStatus, &ok);
        if (!ok)
        {
            GLint length = 0;
            gl().GetProgramiv(program.id, kInfoLogLength, &length);
            std::string log(static_cast<size_t>(std::max(length, 1)), '\0');
            gl().GetProgramInfoLog(program.id, length, nullptr, log.data());
            std::fprintf(stderr, "[gs-gpu] program link failed:\n%s\n", log.c_str());
            std::fflush(stderr);
            return false;
        }
        bindUniforms();
        if (!cachePath.empty())
        {
            GLint length = 0;
            gl().GetProgramiv(program.id, kProgramBinaryLength, &length);
            if (length > 0 && length <= 256 * 1024 * 1024)
            {
                std::vector<uint8_t> binary(static_cast<size_t>(length));
                GLsizei written = 0;
                GLenum format = 0u;
                gl().GetProgramBinary(program.id, length, &written, &format, binary.data());
                if (written > 0)
                {
                    const std::array<uint32_t, 5> header = {0x31425347u, format, static_cast<uint32_t>(driver.size()),
                        static_cast<uint32_t>(source.size()), static_cast<uint32_t>(written)};
                    const uint64_t checksum = fingerprint(binary.data(), static_cast<size_t>(written));
                    std::error_code error;
                    std::filesystem::create_directories(cachePath.parent_path(), error);
                    std::ofstream output(cachePath, std::ios::binary | std::ios::trunc);
                    output.write(reinterpret_cast<const char *>(header.data()), sizeof(header));
                    output.write(reinterpret_cast<const char *>(&checksum), sizeof(checksum));
                    output.write(driver.data(), driver.size());
                    output.write(source.data(), source.size());
                    output.write(reinterpret_cast<const char *>(binary.data()), written);
                }
            }
        }
        return true;
    }

    GLuint compileStage(GLenum kind, const std::string &source)
    {
        const char *text = source.c_str();
        const GLuint shader = gl().CreateShader(kind);
        gl().ShaderSource(shader, 1, &text, nullptr);
        gl().CompileShader(shader);
        GLint ok = 0;
        gl().GetShaderiv(shader, kCompileStatus, &ok);
        if (ok)
            return shader;
        GLint length = 0;
        gl().GetShaderiv(shader, kInfoLogLength, &length);
        std::string log(static_cast<size_t>(std::max(length, 1)), '\0');
        gl().GetShaderInfoLog(shader, length, nullptr, log.data());
        std::fprintf(stderr, "[gs-gpu] hardware raster shader compile failed:\n%s\n", log.c_str());
        std::fflush(stderr);
        gl().DeleteShader(shader);
        return 0u;
    }

    static bool hwLogEnabled()
    {
        static const bool enabled = [] {
            const char *value = std::getenv("PS2X_GS_HW_LOG");
            return value && *value && *value != '0';
        }();
        return enabled;
    }

    static double hwLogSeconds()
    {
        return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    HwKey hardwareKey(uint32_t prim) const
    {
        const uint32_t header = prims[static_cast<size_t>(prim) * kPrimWords];
        const uint32_t *s = states.data() + static_cast<size_t>(header >> 8u) * kStateWords;
        return {header & 0xFFu, s[SFlags], s[SFpsm], s[SZpsm], s[SZmask], s[STpsm], s[STexMode], s[SAlpha], s[STest] & ~0xFF0u,
                s[SClampLo] & 0xFu, s[SFba]};
    }

    std::filesystem::path hardwareCachePath(const std::string &key) const
    {
        const char *cache = std::getenv("PS2X_GS_SHADER_CACHE");
        const char *directory = std::getenv("PS2X_GS_SHADER_CACHE_DIR");
        if ((cache && *cache == '0') || !directory)
            return {};
        uint64_t value = 14695981039346656037ull;
        for (unsigned char c : key)
            value = (value ^ c) * 1099511628211ull;
        char name[40];
        std::snprintf(name, sizeof(name), "hw_%016llx.glbin", static_cast<unsigned long long>(value));
        return std::filesystem::path(directory) / name;
    }

    static uint64_t binaryChecksum(const std::vector<uint8_t> &data)
    {
        uint64_t value = 14695981039346656037ull;
        for (uint8_t c : data)
            value = (value ^ c) * 1099511628211ull;
        return value;
    }

    GLuint loadHardwareBinary(const std::filesystem::path &path, const std::string &key)
    {
        if (path.empty())
            return 0u;
        std::ifstream input(path, std::ios::binary);
        std::array<uint32_t, 4> header{};
        uint64_t checksum = 0u;
        input.read(reinterpret_cast<char *>(header.data()), sizeof(header));
        input.read(reinterpret_cast<char *>(&checksum), sizeof(checksum));
        if (!input || header[0] != 0x31574853u || header[2] != key.size() || header[3] == 0u || header[3] > 64u * 1024u * 1024u)
            return 0u;
        std::string storedKey(key.size(), '\0');
        std::vector<uint8_t> binary(header[3]);
        input.read(storedKey.data(), storedKey.size());
        input.read(reinterpret_cast<char *>(binary.data()), binary.size());
        if (!input || storedKey != key || binaryChecksum(binary) != checksum)
            return 0u;
        const GLuint program = gl().CreateProgram();
        gl().ProgramBinary(program, header[1], binary.data(), static_cast<GLsizei>(binary.size()));
        GLint linked = 0;
        gl().GetProgramiv(program, kLinkStatus, &linked);
        if (linked)
            return program;
        gl().DeleteProgram(program);
        return 0u;
    }

    void storeHardwareBinary(const std::filesystem::path &path, const std::string &key, GLuint program)
    {
        if (path.empty())
            return;
        GLint length = 0;
        gl().GetProgramiv(program, kProgramBinaryLength, &length);
        if (length <= 0 || length > 64 * 1024 * 1024)
            return;
        std::vector<uint8_t> binary(static_cast<size_t>(length));
        GLsizei written = 0;
        GLenum format = 0u;
        gl().GetProgramBinary(program, length, &written, &format, binary.data());
        if (written <= 0)
            return;
        binary.resize(static_cast<size_t>(written));
        const std::array<uint32_t, 4> header = {0x31574853u, format, static_cast<uint32_t>(key.size()), static_cast<uint32_t>(written)};
        const uint64_t checksum = binaryChecksum(binary);
        std::error_code error;
        std::filesystem::create_directories(path.parent_path(), error);
        const std::filesystem::path temporary = path.string() + ".tmp";
        {
            std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
            output.write(reinterpret_cast<const char *>(header.data()), sizeof(header));
            output.write(reinterpret_cast<const char *>(&checksum), sizeof(checksum));
            output.write(key.data(), key.size());
            output.write(reinterpret_cast<const char *>(binary.data()), binary.size());
        }
        std::filesystem::rename(temporary, path, error);
    }

    std::string hardwareFragmentSource(const HwKey &key) const
    {
        static const char *const kNames[] = {"K_TYPE", "K_FLAGS", "K_FPSM", "K_ZPSM", "K_ZMASK", "K_TPSM", "K_TEXMODE", "K_ALPHA",
                                             "K_TEST", "K_CLAMPLO", "K_FBA"};
        std::string defines = "#define HW_SPECIALIZED 1\n#define HW_TYPE(h) K_TYPE\n";
        for (size_t i = 0; i < key.size(); ++i)
            defines += "#define " + std::string(kNames[i]) + " " + std::to_string(key[i]) + "u\n";
        return hwFragmentHead + defines + hwFragmentBody;
    }

    void finishVariant(Program &program, GLuint id)
    {
        program.id = id;
        program.loc[0] = gl().GetUniformLocation(id, "uRaster");
        program.loc[1] = gl().GetUniformLocation(id, "uHw");
    }

    void drainCompiledVariants()
    {
        std::vector<CompileResult> results;
        {
            std::lock_guard<std::mutex> lock(hwCompileMutex);
            results.swap(hwResults);
        }
        for (const CompileResult &result : results)
        {
            Program &program = hwVariants[result.key];
            if (result.program)
                finishVariant(program, result.program);
            if (hwLogEnabled())
                std::fprintf(stderr, "[gs-hw] %.3f variant %s in %.0f ms (%zu known)\n", hwLogSeconds(),
                             !result.program ? "failed" : result.fromCache ? "loaded from cache" : "compiled", result.ms, hwVariants.size());
        }
    }

    std::filesystem::path hardwareManifestPath() const
    {
        const char *cache = std::getenv("PS2X_GS_SHADER_CACHE");
        const char *directory = std::getenv("PS2X_GS_SHADER_CACHE_DIR");
        if ((cache && *cache == '0') || !directory)
            return {};
        return std::filesystem::path(directory) / "hw_keys.txt";
    }

    void prewarmHardwareVariants()
    {
        const std::filesystem::path path = hardwareManifestPath();
        if (path.empty())
            return;
        std::ifstream input(path);
        std::string line;
        size_t queued = 0u;
        while (std::getline(input, line))
        {
            HwKey key{};
            std::istringstream fields(line);
            size_t count = 0u;
            while (count < key.size() && (fields >> std::hex >> key[count]))
                ++count;
            if (count != key.size() || !hwRequested.insert(key).second)
                continue;
            requestVariant(key);
            ++queued;
        }
        if (queued)
            std::fprintf(stderr, "[gs-gpu] preloading %zu hardware raster shaders\n", queued);
    }

    void rememberVariant(const HwKey &key)
    {
        const std::filesystem::path path = hardwareManifestPath();
        if (path.empty())
            return;
        std::error_code error;
        std::filesystem::create_directories(path.parent_path(), error);
        std::ofstream output(path, std::ios::app);
        for (size_t i = 0; i < key.size(); ++i)
            output << std::hex << key[i] << (i + 1u < key.size() ? ' ' : '\n');
    }

    void requestVariant(const HwKey &key)
    {
        CompileJob job;
        job.key = key;
        job.fragment = hardwareFragmentSource(key);
        job.cacheKey = std::string(reinterpret_cast<const char *>(gl().GetString(kRenderer))) + "\n" +
                       reinterpret_cast<const char *>(gl().GetString(kVersion)) + "\n" + hwVertexSource + "\n" + job.fragment;
        job.cachePath = hardwareCachePath(job.cacheKey);
        {
            std::lock_guard<std::mutex> lock(hwCompileMutex);
            hwJobs.push_back(std::move(job));
        }
        hwCompileCv.notify_one();
    }

    const Program *hardwareVariant(const HwKey &key)
    {
        auto found = hwVariants.find(key);
        if (found != hwVariants.end())
            return found->second.id ? &found->second : nullptr;
        if (!hwRequested.insert(key).second)
            return nullptr;
        rememberVariant(key);
        requestVariant(key);
        return nullptr;
    }

    void compileWorker()
    {
        if (!context.MakeWorkerCurrent(hwWorkerContext))
            return;
        ThreadNaming::SetCurrentThreadName("GSShaderCompiler");
#if defined(_WIN32)
        SetThreadPriority(GetCurrentThread(), -1);
#endif
        if (gl().MaxShaderCompilerThreads)
            gl().MaxShaderCompilerThreads(2u);
        const GLuint vertex = compileStage(kVertexShader, hwVertexSource);
        struct InFlight
        {
            CompileJob job;
            GLuint program = 0;
            GLuint fragment = 0;
            std::chrono::steady_clock::time_point started;
        };
        std::vector<InFlight> inFlight;
        for (;;)
        {
            std::deque<CompileJob> jobs;
            {
                std::unique_lock<std::mutex> lock(hwCompileMutex);
                if (inFlight.empty())
                    hwCompileCv.wait(lock, [&] { return hwCompileStop || !hwJobs.empty(); });
                else
                    hwCompileCv.wait_for(lock, std::chrono::milliseconds(4), [&] { return hwCompileStop || !hwJobs.empty(); });
                if (hwCompileStop)
                    break;
                jobs.swap(hwJobs);
            }
            std::vector<CompileResult> done;
            for (CompileJob &job : jobs)
            {
                const auto started = std::chrono::steady_clock::now();
                if (const GLuint cached = loadHardwareBinary(job.cachePath, job.cacheKey))
                {
                    gl().Finish();
                    std::lock_guard<std::mutex> lock(hwCompileMutex);
                    hwResults.push_back({job.key, cached, true, std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count()});
                    continue;
                }
                InFlight item;
                item.started = started;
                const char *text = job.fragment.c_str();
                item.fragment = gl().CreateShader(kFragmentShader);
                gl().ShaderSource(item.fragment, 1, &text, nullptr);
                gl().CompileShader(item.fragment);
                GLint fragOk = 0;
                gl().GetShaderiv(item.fragment, kCompileStatus, &fragOk);
                if (!fragOk)
                {
                    GLint length = 0;
                    gl().GetShaderiv(item.fragment, kInfoLogLength, &length);
                    std::string log(static_cast<size_t>(std::max(length, 1)), '\0');
                    gl().GetShaderInfoLog(item.fragment, length, nullptr, log.data());
                    std::fprintf(stderr, "[gs-gpu] hardware fragment compile failed:\n%s\n", log.c_str());
                    std::fflush(stderr);
                    gl().DeleteShader(item.fragment);
                    continue;
                }
                item.program = gl().CreateProgram();
                gl().ProgramParameteri(item.program, kProgramBinaryRetrievableHint, 1);
                gl().AttachShader(item.program, vertex);
                gl().AttachShader(item.program, item.fragment);
                gl().LinkProgram(item.program);
                item.job = std::move(job);
                inFlight.push_back(std::move(item));
            }
            for (size_t i = 0; i < inFlight.size();)
            {
                InFlight &item = inFlight[i];
                GLint complete = 1;
                if (gl().MaxShaderCompilerThreads)
                    gl().GetProgramiv(item.program, kCompletionStatus, &complete);
                if (!complete)
                {
                    ++i;
                    continue;
                }
                GLint ok = 0;
                gl().GetProgramiv(item.program, kLinkStatus, &ok);
                gl().DeleteShader(item.fragment);
                if (ok)
                    storeHardwareBinary(item.job.cachePath, item.job.cacheKey, item.program);
                else
                {
                    GLint length = 0;
                    gl().GetProgramiv(item.program, kInfoLogLength, &length);
                    std::string log(static_cast<size_t>(std::max(length, 1)), '\0');
                    gl().GetProgramInfoLog(item.program, length, nullptr, log.data());
                    std::fprintf(stderr, "[gs-gpu] hardware raster variant failed; that state keeps the compute renderer:\n%s\n", log.c_str());
                    std::fflush(stderr);
                    gl().DeleteProgram(item.program);
                    item.program = 0;
                }
                done.push_back({item.job.key, item.program, false,
                                std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - item.started).count()});
                inFlight.erase(inFlight.begin() + static_cast<std::ptrdiff_t>(i));
            }
            if (!done.empty())
            {
                gl().Finish();
                std::lock_guard<std::mutex> lock(hwCompileMutex);
                hwResults.insert(hwResults.end(), done.begin(), done.end());
            }
        }
        for (InFlight &item : inFlight)
        {
            gl().DeleteShader(item.fragment);
            gl().DeleteProgram(item.program);
        }
        if (vertex)
            gl().DeleteShader(vertex);
        gl().Finish();
    }

    void stopCompileWorker()
    {
        if (!hwCompiler.joinable())
            return;
        {
            std::lock_guard<std::mutex> lock(hwCompileMutex);
            hwCompileStop = true;
        }
        hwCompileCv.notify_all();
        hwCompiler.join();
        Context::DestroyWorker(hwWorkerContext);
        hwWorkerContext = nullptr;
    }

    static std::string hardwareShadingFunctions(const std::string &body)
    {
        std::string out = "bool shadeOut(out uint oz, out uvec4 oc, out uint ofog, uint z, uvec4 c, uint fog)\n"
                          "{\n    oz = z;\n    oc = c;\n    ofog = fog;\n    return true;\n}\n";
        const char *names[] = {"drawPoint", "drawSprite", "drawTriangle"};
        const char *shaded[] = {"shadePoint", "shadeSprite", "shadeTriangle"};
        for (int i = 0; i < 3; ++i)
        {
            const std::string signature = std::string("void ") + names[i] + "(uint p, uint s, int x, int y)\n{";
            const size_t start = body.find(signature);
            if (start == std::string::npos)
                return {};
            size_t depth = 0u;
            size_t end = body.find('{', start);
            for (; end < body.size(); ++end)
            {
                if (body[end] == '{')
                    ++depth;
                else if (body[end] == '}' && --depth == 0u)
                    break;
            }
            if (end >= body.size())
                return {};
            std::string function = body.substr(start, end - start + 1u);
            function.replace(0, signature.size(), std::string("bool ") + shaded[i] +
                                                      "(uint p, uint s, int x, int y, out uint oz, out uvec4 oc, out uint ofog)\n{");
            for (size_t at = 0; (at = function.find("writePixel(s, x, y, ", at)) != std::string::npos;)
            {
                function.replace(at, std::string("writePixel(s, x, y, ").size(), "return shadeOut(oz, oc, ofog, ");
                at += std::string("return shadeOut(oz, oc, ofog, ").size();
            }
            for (size_t at = 0; (at = function.find("return;", at)) != std::string::npos;)
            {
                function.replace(at, std::string("return;").size(), "return false;");
                at += std::string("return false;").size();
            }
            out += function + "\n";
        }
        out += "bool shadePrim(uint p, int x, int y, out uint s, out uint oz, out uvec4 oc, out uint ofog)\n"
               "{\n"
               "    uint header = pw(p, 0u);\n"
               "    s = header >> 8u;\n"
               "    oz = 0u;\n    oc = uvec4(0u);\n    ofog = 0u;\n"
               "    switch (HW_TYPE(header))\n"
               "    {\n"
               "    case 0u: return shadePoint(p, s, x, y, oz, oc, ofog);\n"
               "    case 1u: return shadeSprite(p, s, x, y, oz, oc, ofog);\n"
               "    case 2u: return shadeTriangle(p, s, x, y, oz, oc, ofog);\n"
               "    }\n"
               "    return false;\n"
               "}\n";
        return out;
    }

    bool setupHardwareRaster(const std::string &prefix)
    {
        const char *setting = std::getenv("PS2X_GS_HW_RASTER");
        if ((setting && *setting == '0') || !gl().graphics || !hwAllowed)
            return false;
        const std::string version = "#version 460 core\n";
        std::string body = GSGpuShaders::kRaster;
        const std::string layout = "layout(local_size_x = 16, local_size_y = 16) in;";
        const std::string stateRead = "uint st(uint s, uint i) { return states[s * STATE_WORDS + i]; }";
        const std::string coverType = "    uint type = header & 0xFFu;";
        const std::string drawType = "    switch (header & 0xFFu)";
        const size_t layoutAt = body.find(layout);
        const size_t mainAt = body.find("void main()");
        if (layoutAt == std::string::npos || mainAt == std::string::npos || body.find(stateRead) == std::string::npos ||
            body.find(coverType) == std::string::npos || body.find(drawType) == std::string::npos)
            return false;
        body = body.substr(0, mainAt);
        body.erase(layoutAt, layout.size());
        body.replace(body.find(stateRead), stateRead.size(),
                     "#ifdef HW_SPECIALIZED\n"
                     "uint st(uint s, uint i)\n"
                     "{\n"
                     "    uint v = states[s * STATE_WORDS + i];\n"
                     "    if (i == S_FLAGS) return K_FLAGS;\n"
                     "    if (i == S_FPSM) return K_FPSM;\n"
                     "    if (i == S_ZPSM) return K_ZPSM;\n"
                     "    if (i == S_ZMASK) return K_ZMASK;\n"
                     "    if (i == S_TPSM) return K_TPSM;\n"
                     "    if (i == S_TEXMODE) return K_TEXMODE;\n"
                     "    if (i == S_ALPHA) return K_ALPHA;\n"
                     "    if (i == S_TEST) return (v & 0xFF0u) | K_TEST;\n"
                     "    if (i == S_CLAMP_LO) return (v & ~0xFu) | K_CLAMPLO;\n"
                     "    if (i == S_FBA) return K_FBA;\n"
                     "    return v;\n"
                     "}\n"
                     "#else\n" +
                         stateRead +
                         "\n#endif\n");
        body.replace(body.find(coverType), coverType.size(), "    uint type = HW_TYPE(header);");
        body.replace(body.find(drawType), drawType.size(), "    switch (HW_TYPE(header))");
        const std::string shading = hardwareShadingFunctions(body);
        if (shading.empty())
            return false;
        body += shading;
        const std::string testInterlock = version + "#extension GL_ARB_fragment_shader_interlock : require\nvoid main() {}\n";
        GLuint testShader = gl().CreateShader(kFragmentShader);
        const char *testSrc = testInterlock.c_str();
        gl().ShaderSource(testShader, 1, &testSrc, nullptr);
        gl().CompileShader(testShader);
        GLint interlockSupported = 0;
        gl().GetShaderiv(testShader, kCompileStatus, &interlockSupported);
        gl().DeleteShader(testShader);
        if (!interlockSupported)
        {
            std::fprintf(stderr, "[gs-gpu] GL_ARB_fragment_shader_interlock not supported by driver, using pure compute rasterizer\n");
            std::fflush(stderr);
            return false;
        }

        hwFragmentHead = version + "#extension GL_ARB_fragment_shader_interlock : require\n";
        std::string common = GSGpuShaders::kCommon;
        const std::string vramDeclaration = "layout(std430, binding = 0) buffer VramBuffer";
        if (common.find(vramDeclaration) == std::string::npos)
            return false;
        common.replace(common.find(vramDeclaration), vramDeclaration.size(), "layout(std430, binding = 0) coherent buffer VramBuffer");
        hwFragmentBody = prefix.substr(version.size()) + common + body + GSGpuShaders::kHwFragmentMain;
        if (gl().MaxShaderCompilerThreads)
            gl().MaxShaderCompilerThreads(0xFFFFFFFFu);
        hwVertexSource = version + GSGpuShaders::kHwVertex;
        hwVertexShader = compileStage(kVertexShader, hwVertexSource);
        if (!hwVertexShader)
            return false;
        hwWorkerContext = context.CreateWorker();
        if (!hwWorkerContext)
            return false;
        hwCompiler = std::thread([this] { compileWorker(); });
        prewarmHardwareVariants();
        const char *expand = std::getenv("PS2X_GS_HW_TRIANGLES");
        hwConservative = !(expand && *expand == '0');
        gl().GenFramebuffers(1, &hwFramebuffer);
        gl().BindFramebuffer(kFramebuffer, hwFramebuffer);
        gl().FramebufferParameteri(kFramebuffer, kFramebufferDefaultWidth, 2048);
        gl().FramebufferParameteri(kFramebuffer, kFramebufferDefaultHeight, 2048);
        gl().GenVertexArrays(1, &hwVertexArray);
        std::fprintf(stderr, "[gs-gpu] hardware rasterization active%s\n", hwConservative ? ", expanded triangles" : "");
        std::fflush(stderr);
        return true;
    }

    bool ensure()
    {
        if (initialized)
            return true;
        if (failed)
            return false;
        std::string error;
        if (!context.Create(error))
        {
            std::fprintf(stderr, "[gs-gpu] %s\n", error.c_str());
            std::fflush(stderr);
            failed = true;
            return false;
        }
        std::fprintf(stderr, "[gs-gpu] %s / %s\n", reinterpret_cast<const char *>(gl().GetString(kRenderer)),
                     reinterpret_cast<const char *>(gl().GetString(kVersion)));
        std::fflush(stderr);

        GSSwizzle::GetFormat(0u);
        using GSMem::PixelStorageMode;
        const std::pair<const char *, PixelStorageMode> tables[] = {
            {"TABLE_C32", PixelStorageMode::C32}, {"TABLE_Z32", PixelStorageMode::Z32}, {"TABLE_C16", PixelStorageMode::C16},
            {"TABLE_C16S", PixelStorageMode::C16S}, {"TABLE_Z16", PixelStorageMode::Z16}, {"TABLE_Z16S", PixelStorageMode::Z16S},
            {"TABLE_P8", PixelStorageMode::P8}, {"TABLE_P4", PixelStorageMode::P4}};
        const uint32_t sizes[] = {65536u, 65536u, 131072u, 131072u, 131072u, 131072u, 262144u, 524288u};
        std::vector<uint16_t> swizzle;
        std::string prefix = "#version 460 core\n";
        for (size_t i = 0; i < std::size(tables); ++i)
        {
            prefix += "#define " + std::string(tables[i].first) + " " + std::to_string(swizzle.size()) + "u\n";
            const uint16_t *data = GSMem::PageTableData(tables[i].second);
            swizzle.insert(swizzle.end(), data, data + sizes[i]);
        }
        std::string common = GSGpuShaders::kCommon;
        (void)common;

        vramBuffer = makeBuffer(GSSwizzle::kMemorySize + static_cast<size_t>(kShadowPages) * 8192u, nullptr, 0u);
        swizzleBuffer = makeBuffer(swizzle.size() * sizeof(uint16_t), swizzle.data(), 1u);
        std::vector<uint32_t> zeros(kClutSlots * 256u, 0u);
        clutBuffer = makeBuffer(zeros.size() * sizeof(uint32_t), zeros.data(), 2u);
        primBuffer = makeBuffer(16u, nullptr, 3u);
        stateBuffer = makeBuffer(16u, nullptr, 4u);
        tileBuffer = makeBuffer(16u, nullptr, 5u);
        tileListBuffer = makeBuffer(16u, nullptr, 6u);
        dataBuffer = makeBuffer(16u, nullptr, 7u);
        clutOpBuffer = makeBuffer(16u, nullptr, 8u);
        pageMapBuffer = makeBuffer(16u, nullptr, 9u);
        dataCapacity = 16u;
        gl().GenBuffers(1, &ringBuffer);
        gl().BindBuffer(kShaderStorageBuffer, ringBuffer);
        gl().BufferStorage(kShaderStorageBuffer, static_cast<GLsizeiptr>(kRingChunk * kRingChunks), nullptr,
                           kMapWriteBit | kMapPersistentBit | kMapCoherentBit);
        ring = static_cast<uint8_t *>(gl().MapBufferRange(kShaderStorageBuffer, 0, static_cast<GLsizeiptr>(kRingChunk * kRingChunks),
                                                          kMapWriteBit | kMapPersistentBit | kMapCoherentBit));

        const bool ok = compile(raster, prefix, GSGpuShaders::kRaster, {"uRaster"}) &&
                        compile(pageCopy, prefix, GSGpuShaders::kPageCopy, {}) &&
                        compile(clutLoad, prefix, GSGpuShaders::kClutLoad, {"uClutA", "uClutB"}) &&
                        compile(upload, prefix, GSGpuShaders::kUpload, {"uUpload"}) &&
                        compile(copyRead, prefix, GSGpuShaders::kCopyRead, {"uSrc", "uSize"}) &&
                        compile(copyWrite, prefix, GSGpuShaders::kCopyWrite, {"uDst", "uSize"}) &&
                        compile(clear, prefix, GSGpuShaders::kClear, {"uFrame", "uRect"}) &&
                        compile(poke, prefix, GSGpuShaders::kPoke, {"uArgs", "uArgs2"}) &&
                        compile(present, prefix, GSGpuShaders::kPresent, {"uOut", "uC1", "uC2", "uMode"});
        if (!ok)
        {
            failed = true;
            return false;
        }
        hwEnabled = setupHardwareRaster(prefix);
        const char *hashValue = std::getenv("PS2X_FRAME_HASH");
        if (context.Shared() && hashValue && *hashValue == '1')
        {
            if (!compile(presentHash, prefix, GSGpuShaders::kPresentHash, {"uPixels"}))
            {
                if (presentHash.id)
                    gl().DeleteProgram(presentHash.id);
                presentHash = {};
                std::fprintf(stderr, "[gs-present] image hashing unavailable\n");
            }
        }
        initialized = true;
        if (hostVram)
            uploadHostVram();
        return true;
    }

    void barrier()
    {
        gl().MemBarrier(kShaderStorageBarrierBit | kBufferUpdateBarrierBit);
    }

    void uploadHostVram()
    {
        clutKeyValid = false;
        if (!hostVram)
            return;
        gl().BindBuffer(kShaderStorageBuffer, vramBuffer);
        gl().BufferSubData(kShaderStorageBuffer, 0, static_cast<GLsizeiptr>(std::min<uint32_t>(hostVramSize, GSSwizzle::kMemorySize)), hostVram);
    }

    void downloadVram(uint8_t *out, size_t size)
    {
        barrier();
        gl().BindBuffer(kShaderStorageBuffer, vramBuffer);
        gl().GetBufferSubData(kShaderStorageBuffer, 0, static_cast<GLsizeiptr>(std::min<size_t>(size, GSSwizzle::kMemorySize)), out);
    }

    void readData(void *out, size_t size)
    {
        barrier();
        gl().BindBuffer(kShaderStorageBuffer, dataBuffer);
        gl().GetBufferSubData(kShaderStorageBuffer, 0, static_cast<GLsizeiptr>(size), out);
    }

    void resetBatch()
    {
        prims.clear();
        primCount = 0u;
        states.clear();
        stateCount = 0u;
        for (uint32_t tile : touched)
            bins[tile].clear();
        touched.clear();
        writePages.reset();
        colorPages.reset();
        depthAccessPages.reset();
        readPages.reset();
        batchClutPages.reset();
        hasTarget = false;
        clutOps.clear();
        epoch = 0u;
        batchClutLoads = 0u;
        copyPairs.clear();
        uploadWords.clear();
        uploadGroups.clear();
        uploadData_.clear();
        uploadCount = 0u;
        pendingWritePages.reset();
        shadowNext = 0u;
        firstLiveEpoch.fill(0u);
        pageMaps.resize(kPages);
        for (uint32_t page = 0; page < kPages; ++page)
            pageMaps[page] = page;
    }

    bool copyOnWrite(const std::bitset<kPages> &pages)
    {
        const uint32_t count = static_cast<uint32_t>(pages.count());
        if (count == 0u)
            return true;
        if (shadowNext + count > kShadowPages || epoch + 1u >= kMaxEpochs)
            return false;
        if ((pages & pendingWritePages).any())
            executeTransfers();
        for (uint32_t page = 0; page < kPages; ++page)
        {
            if (!pages.test(page))
                continue;
            const uint32_t slot = kPages + shadowNext++;
            copyPairs.push_back(page | (slot << 16u));
            for (uint32_t e = firstLiveEpoch[page]; e <= epoch; ++e)
                pageMaps[static_cast<size_t>(e) * kPages + page] = slot;
            firstLiveEpoch[page] = epoch + 1u;
        }
        ++epoch;
        const size_t base = pageMaps.size();
        pageMaps.resize(base + kPages);
        for (uint32_t page = 0; page < kPages; ++page)
            pageMaps[base + page] = page;
        return true;
    }

    void executeTransfers()
    {
        if (!copyPairs.empty())
        {
            uploadData(copyPairs.data(), copyPairs.size() * sizeof(uint32_t));
            gl().UseProgram(pageCopy.id);
            const GLuint profCopy = profBegin();
            gl().DispatchCompute(static_cast<GLuint>(copyPairs.size()), 1u, 1u);
            profEnd(3u, profCopy);
            barrier();
            copyPairs.clear();
        }
        if (!uploadWords.empty())
        {
            const uint32_t descriptors = static_cast<uint32_t>(uploadCount);
            const uint32_t mapOffset = static_cast<uint32_t>(uploadWords.size());
            uploadWords.insert(uploadWords.end(), uploadGroups.begin(), uploadGroups.end());
            const uint32_t dataOffset = static_cast<uint32_t>(uploadWords.size());
            for (uint32_t d = 0; d < descriptors; ++d)
                uploadWords[d * 9u + 8u] += dataOffset;
            uploadWords.insert(uploadWords.end(), uploadData_.begin(), uploadData_.end());
            uploadData(uploadWords.data(), uploadWords.size() * sizeof(uint32_t));
            gl().UseProgram(upload.id);
            gl().Uniform4ui(upload.loc[0], mapOffset, 0u, 0u, 0u);
            const GLuint profUpload = profBegin();
            gl().DispatchCompute(static_cast<GLuint>(uploadGroups.size()), 1u, 1u);
            profEnd(2u, profUpload);
            barrier();
            uploadWords.clear();
            uploadGroups.clear();
            uploadData_.clear();
            uploadCount = 0u;
        }
        pendingWritePages.reset();
    }

    void dispatchClutOps()
    {
        const Api &g = gl();
        if (clutOps.empty())
            return;
        {
            clutOpWords.assign(clutOps.size() * 24u, 0u);
            for (size_t i = 0; i < clutOps.size(); ++i)
            {
                const ClutOp &op = clutOps[i];
                uint32_t *w = clutOpWords.data() + i * 24u;
                w[0] = op.target;
                w[1] = isFourBitIndexedPsm(static_cast<uint8_t>(op.psm)) ? 1u : 0u;
                w[2] = op.cbp;
                w[3] = op.packed;
                w[4] = op.cbw;
                w[5] = op.cou;
                w[6] = op.cov;
                w[7] = op.epoch;
                for (uint32_t b = 0; b < 16u; ++b)
                    w[8u + b] = static_cast<uint32_t>(op.writers[b * 2u]) | (static_cast<uint32_t>(op.writers[b * 2u + 1u]) << 16u);
            }
            bindUpload(8u, clutOpBuffer, clutOpWords.data(), clutOpWords.size() * sizeof(uint32_t));
            g.UseProgram(clutLoad.id);
            g.Uniform4ui(clutLoad.loc[0], clutOps.front().source, epoch, 0u, 0u);
            const GLuint profClut = profBegin();
            g.DispatchCompute(static_cast<GLuint>(clutOps.size()), 1u, 1u);
            profEnd(1u, profClut);
            barrier();
            stats.clutLoads += clutOps.size();
        }
        clutOps.clear();
        batchClutPages.reset();
    }

    void flushBatch()
    {
        const auto flushStart = std::chrono::steady_clock::now();
        const uint32_t flushPrims = primCount;
        bool fallback = false;
        struct FlushLog
        {
            const std::chrono::steady_clock::time_point &start;
            const uint32_t &prims;
            const bool &fallback;
            double &ringWait;
            double &variantMs;
            ~FlushLog()
            {
                if (!hwLogEnabled())
                    return;
                const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
                if (fallback || ms > 8.0)
                    std::fprintf(stderr, "[gs-hw] %.3f flush %u prims %.1f ms ring wait %.1f ms variants %.1f ms%s\n", hwLogSeconds(), prims, ms, ringWait,
                                 variantMs, fallback ? " (compute fallback)" : "");
            }
        } flushLog{flushStart, flushPrims, fallback, hwRingWaitMs, hwVariantMs};
        hwRingWaitMs = 0.0;
        hwVariantMs = 0.0;
        if (initialized)
            executeTransfers();
        if (!initialized || (primCount == 0u && clutOps.empty()))
        {
            resetBatch();
            return;
        }
        const Api &g = gl();
        if (epoch != 0u)
            bindUpload(9u, pageMapBuffer, pageMaps.data(), static_cast<size_t>(epoch) * kPages * sizeof(uint32_t));
        dispatchClutOps();
        bool drawn = false;
        if (primCount != 0u && hwEnabled)
        {
            drainCompiledVariants();
            hwRuns.clear();
            uint32_t runStart = 0u;
            HwKey runKey = hardwareKey(0u);
            bool ready = true;
            for (uint32_t prim = 1u; prim <= primCount; ++prim)
            {
                HwKey key{};
                if (prim < primCount)
                {
                    key = hardwareKey(prim);
                    if (key == runKey)
                        continue;
                }
                const auto variantStart = std::chrono::steady_clock::now();
                const Program *program = hardwareVariant(runKey);
                hwVariantMs += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - variantStart).count();
                ready = ready && program != nullptr;
                hwRuns.push_back({program, runStart, prim});
                runStart = prim;
                runKey = key;
            }
            if (ready)
            {
                bindUpload(3u, primBuffer, prims.data(), prims.size() * sizeof(uint32_t));
                bindUpload(4u, stateBuffer, states.data(), states.size() * sizeof(uint32_t));
                g.BindFramebuffer(kFramebuffer, hwFramebuffer);
                g.Viewport(0, 0, 2048, 2048);
                g.BindVertexArray(hwVertexArray);
                const GLuint profRaster = profBegin();
                for (const HwRun &run : hwRuns)
                {
                    g.UseProgram(run.program->id);
                    g.Uniform4ui(run.program->loc[0], epoch, 0u, 0u, 0u);
                    g.Uniform4ui(run.program->loc[1], hwConservative ? 1u : 0u, 0u, 0u, 0u);
                    g.DrawArrays(kTriangles, static_cast<GLint>(run.first * 6u), static_cast<GLsizei>((run.last - run.first) * 6u));
                }
                profEnd(0u, profRaster);
                if (prof.enabled)
                    prof.prims += primCount;
                barrier();
                stats.batches += 1u;
                stats.prims += primCount;
                drawn = true;
            }
        }
        if (primCount != 0u && !drawn)
        {
            fallback = hwEnabled;
            if (hwEnabled)
                for (uint32_t prim = 0u; prim < primCount; ++prim)
                {
                    const uint32_t *p = prims.data() + static_cast<size_t>(prim) * kPrimWords;
                    if ((p[0] & 0xFFu) == PrimPoint)
                        binBox(prim, static_cast<int>(p[1]), static_cast<int>(p[2]), static_cast<int>(p[1]), static_cast<int>(p[2]));
                    else if ((p[0] & 0xFFu) == PrimTriangle)
                    {
                        GSTriangleRaster tri;
                        for (int v = 0; v < 3; ++v)
                        {
                            tri.x[v] = static_cast<int32_t>(p[3u + v * 2u]);
                            tri.y[v] = static_cast<int32_t>(p[4u + v * 2u]);
                        }
                        const int64_t sign = static_cast<int32_t>(p[9]);
                        for (int e = 0; e < 3; ++e)
                        {
                            const int a = (e + 1) % 3;
                            const int b = (e + 2) % 3;
                            tri.a[e] = -(tri.y[b] - tri.y[a]) * sign;
                            tri.b[e] = (tri.x[b] - tri.x[a]) * sign;
                            tri.c[e] = -(tri.a[e] * tri.x[a] + tri.b[e] * tri.y[a]);
                            tri.bias[e] = (tri.a[e] > 0 || (tri.a[e] == 0 && tri.b[e] > 0)) ? 1 : 0;
                        }
                        hwEnabled = false;
                        binTriangle(prim, tri, static_cast<int>(p[1] & 0xFFFFu), static_cast<int>(p[2] & 0xFFFFu), static_cast<int>(p[1] >> 16u),
                                    static_cast<int>(p[2] >> 16u));
                        hwEnabled = true;
                    }
                    else
                        binBox(prim, static_cast<int>(p[1] & 0xFFFFu), static_cast<int>(p[2] & 0xFFFFu), static_cast<int>(p[1] >> 16u),
                               static_cast<int>(p[2] >> 16u));
                }
            tileHeaders.clear();
            tileHeaders.reserve(touched.size() * 4u);
            tileList.clear();
            size_t totalPairs = 0u;
            for (uint32_t tile : touched)
                totalPairs += bins[tile].size();
            tileList.reserve(totalPairs);
            for (uint32_t tile : touched)
            {
                const std::vector<uint32_t> &bin = bins[tile];
                tileHeaders.push_back(tile % kTileGrid);
                tileHeaders.push_back(tile / kTileGrid);
                tileHeaders.push_back(static_cast<uint32_t>(tileList.size()));
                tileHeaders.push_back(static_cast<uint32_t>(bin.size()));
                tileList.insert(tileList.end(), bin.begin(), bin.end());
            }
            bindUpload(3u, primBuffer, prims.data(), prims.size() * sizeof(uint32_t));
            bindUpload(4u, stateBuffer, states.data(), states.size() * sizeof(uint32_t));
            bindUpload(5u, tileBuffer, tileHeaders.data(), tileHeaders.size() * sizeof(uint32_t));
            bindUpload(6u, tileListBuffer, tileList.data(), tileList.size() * sizeof(uint32_t));
            g.UseProgram(raster.id);
            g.Uniform4ui(raster.loc[0], epoch, 0u, 0u, 0u);
            const GLuint profRaster = profBegin();
            g.DispatchCompute(static_cast<GLuint>(touched.size()), 1u, 1u);
            profEnd(0u, profRaster);
            if (prof.enabled)
            {
                prof.pairs += tileList.size();
                prof.tiles += touched.size();
                prof.prims += primCount;
                uint64_t dispatchMax = 0u;
                for (uint32_t tile : touched)
                    dispatchMax = std::max<uint64_t>(dispatchMax, bins[tile].size());
                prof.maxBin = std::max(prof.maxBin, dispatchMax);
                const uint32_t s0 = prims.empty() ? 0u : (prims[0] >> 8u);
                const uint32_t *st0 = states.data() + static_cast<size_t>(s0) * kStateWords;
                if (!prof.pending.empty())
                    prof.pending.back().info = {primCount, static_cast<uint32_t>(touched.size()), static_cast<uint32_t>(tileList.size()),
                                            static_cast<uint32_t>(dispatchMax), st0[SFbp] >> 5u, st0[SFpsm], st0[SZbp] >> 5u, st0[SFlags]};
                prof.sumMaxBin += dispatchMax;
            }
            barrier();
            stats.batches += 1u;
            stats.tiles += touched.size();
            stats.prims += primCount;
        }
        resetBatch();
    }

    uint32_t addState(const GSDrawState &state)
    {
        const GSContext &ctx = state.context;
        std::array<uint32_t, kStateWords> s{};
        s[SFbp] = ctx.frame.fbp << 5u;
        s[SFbw] = std::max<uint32_t>(ctx.frame.fbw, 1u);
        s[SFpsm] = ctx.frame.psm;
        s[SFbmsk] = ctx.frame.fbmsk;
        s[SZbp] = ctx.zbuf.zbp << 5u;
        s[SZpsm] = ctx.zbuf.psm;
        s[SZmask] = ctx.zbuf.zmask ? 1u : 0u;
        s[SScissorX] = static_cast<uint32_t>(ctx.scissor.x0) | (static_cast<uint32_t>(ctx.scissor.x1) << 16u);
        s[SScissorY] = static_cast<uint32_t>(ctx.scissor.y0) | (static_cast<uint32_t>(ctx.scissor.y1) << 16u);
        const uint32_t flags = (state.prim.iip ? FIip : 0u) | (state.prim.tme ? FTme : 0u) | (state.prim.fge ? FFge : 0u) |
                               (state.prim.abe ? FAbe : 0u) | (state.prim.fst ? FFst : 0u) | (state.pabe ? FPabe : 0u) |
                               (state.linearFilter ? FLinear : 0u) | ((state.colclamp & 1u) == 0u ? FWrap : 0u);
        s[SFlags] = flags;
        if (state.prim.tme)
        {
            s[STbp0] = ctx.tex0.tbp0;
            s[STbw] = ctx.tex0.tbw;
            s[STpsm] = ctx.tex0.psm;
            s[STexMode] = static_cast<uint32_t>(ctx.tex0.tcc) | (static_cast<uint32_t>(ctx.tex0.tfx) << 8u) |
                          (static_cast<uint32_t>(ctx.tex0.cpsm) << 16u) | (static_cast<uint32_t>(ctx.tex0.csm) << 24u);
            s[SCsa] = ctx.tex0.csa;
            s[STexSize] = static_cast<uint32_t>(state.textureWidth) | (static_cast<uint32_t>(state.textureHeight) << 16u);
            s[SClampLo] = static_cast<uint32_t>(ctx.clamp);
            s[SClampHi] = static_cast<uint32_t>(ctx.clamp >> 32u);
            s[STexa] = static_cast<uint32_t>(state.texa.ta0) | (state.texa.aem ? 0x100u : 0u) | (static_cast<uint32_t>(state.texa.ta1) << 16u);
            s[SClut] = clutSlot;
            s[SEpoch] = epoch;
        }
        s[SAlpha] = static_cast<uint32_t>(ctx.alpha);
        s[SAlphaFix] = static_cast<uint32_t>(ctx.alpha >> 32u);
        s[STest] = static_cast<uint32_t>(ctx.test);
        s[SFba] = static_cast<uint32_t>(ctx.fba);
        s[SFogCol] = static_cast<uint32_t>(state.fogR) | (static_cast<uint32_t>(state.fogG) << 8u) | (static_cast<uint32_t>(state.fogB) << 16u);
        if (stateCount != 0u && s == lastState)
            return stateCount - 1u;
        lastState = s;
        states.insert(states.end(), s.begin(), s.end());
        return stateCount++;
    }

    bool prepareTarget(const GSDrawState &state, int x0, int y0, int x1, int y1)
    {
        const GSContext &ctx = state.context;
        const uint64_t key = static_cast<uint64_t>(ctx.frame.fbp) | (static_cast<uint64_t>(ctx.frame.fbw) << 9u) |
                             (static_cast<uint64_t>(ctx.frame.psm) << 16u) | (static_cast<uint64_t>(ctx.zbuf.zbp) << 24u) |
                             (static_cast<uint64_t>(ctx.zbuf.psm) << 33u);
        if (hasTarget && key != targetKey)
        {
            ++stats.flushTarget;
            flushFor(0u);
        }

        std::bitset<kPages> color, depth;
        const uint32_t fbw = std::max<uint32_t>(ctx.frame.fbw, 1u);
        markPages(color, ctx.frame.psm, ctx.frame.fbp << 5u, fbw, x0, y0, x1, y1);
        const uint32_t ztest = static_cast<uint32_t>((ctx.test >> 17) & 3u);
        if (!ctx.zbuf.zmask || ztest >= 2u)
            markPages(depth, ctx.zbuf.psm, ctx.zbuf.zbp << 5u, fbw, x0, y0, x1, y1);
        // GOW-Port: orden entre primitivas cuando color y Z reinterpretan las mismas
        // paginas. El orden por pixel del shader no protege alias entre otros pixels.
        // Es conservador por pagina; no resuelve alias internos de una sola primitiva.
        if ((color & depthAccessPages).any() || (depth & colorPages).any())
        {
            ++stats.flushTarget;
            flushFor(0u);
        }
        const auto write = color | depth;

        std::bitset<kPages> read;
        if (state.prim.tme)
        {
            const uint64_t clamp = ctx.clamp;
            // GOW-Port: REGION_CLAMP lee MIN..MAX; REGION_REPEAT produce MAX..(MIN|MAX).
            // Conservar los huecos dentro del rectangulo y el rango completo si MIN>MAX.
            const auto bounds = [](uint32_t mode, int size, uint32_t minimum, uint32_t maximum)
            {
                if (mode == 2u && minimum <= maximum)
                    return std::array<int, 2>{static_cast<int>(minimum), static_cast<int>(maximum)};
                if (mode == 3u)
                    return std::array<int, 2>{static_cast<int>(maximum), static_cast<int>(minimum | maximum)};
                return std::array<int, 2>{0, mode == 2u ? 1023 : size - 1};
            };
            const auto u = bounds(static_cast<uint32_t>(clamp & 3u), state.textureWidth,
                                  static_cast<uint32_t>((clamp >> 4) & 1023u), static_cast<uint32_t>((clamp >> 14) & 1023u));
            const auto v = bounds(static_cast<uint32_t>((clamp >> 2) & 3u), state.textureHeight,
                                  static_cast<uint32_t>((clamp >> 24) & 1023u), static_cast<uint32_t>((clamp >> 34) & 1023u));
            // GOW-Port: ambos extremos invalidan la clave, tambien cuando solo cambia MIN.
            const std::array<uint32_t, 8> key{ctx.tex0.psm, ctx.tex0.tbp0, ctx.tex0.tbw,
                                             static_cast<uint32_t>(u[0]), static_cast<uint32_t>(u[1]),
                                             static_cast<uint32_t>(v[0]), static_cast<uint32_t>(v[1]), 0u};
            if (cacheTexturePages && texturePagesValid && key == texturePagesKey)
                read = texturePages;
            else
            {
                markPages(read, ctx.tex0.psm, ctx.tex0.tbp0, ctx.tex0.tbw, u[0], v[0], u[1], v[1]);
                texturePages = read;
                texturePagesKey = key;
                texturePagesValid = true;
            }
        }
        if ((read & writePages).any() || (write & readPages).any())
        {
            ++stats.flushTexture;
            flushFor(1u);
        }
        if (clutKeyValid && (write & clutSourcePages).any())
            clutKeyValid = false;
        writePages |= write;
        colorPages |= color;
        depthAccessPages |= depth;
        readPages |= read;
        targetKey = key;
        hasTarget = true;
        return true;
    }

    void binTriangle(uint32_t prim, const GSTriangleRaster &tri, int x0, int y0, int x1, int y1)
    {
        if (hwEnabled)
            return;
        const int tile = static_cast<int>(kTileSize);
        const int tx0 = x0 / tile;
        const int tx1 = x1 / tile;
        const int ty0 = y0 / tile;
        const int ty1 = y1 / tile;
        if ((tx1 - tx0) + (ty1 - ty0) < 2 || x0 < 0 || y0 < 0 || x1 > 2047 || y1 > 2047)
        {
            bin(prim, x0, y0, x1, y1);
            return;
        }
        for (int ty = ty0; ty <= ty1; ++ty)
        {
            const int64_t py0 = static_cast<int64_t>(std::max(y0, ty * tile)) * 16;
            const int64_t py1 = static_cast<int64_t>(std::min(y1, ty * tile + tile - 1)) * 16;
            for (int tx = tx0; tx <= tx1; ++tx)
            {
                const int64_t px0 = static_cast<int64_t>(std::max(x0, tx * tile)) * 16;
                const int64_t px1 = static_cast<int64_t>(std::min(x1, tx * tile + tile - 1)) * 16;
                bool outside = false;
                for (int i = 0; i < 3 && !outside; ++i)
                {
                    const int64_t e = tri.a[i] * (tri.a[i] > 0 ? px1 : px0) + tri.b[i] * (tri.b[i] > 0 ? py1 : py0) + tri.c[i];
                    outside = e + tri.bias[i] <= 0;
                }
                if (outside)
                    continue;
                const uint32_t index = static_cast<uint32_t>(ty) * kTileGrid + static_cast<uint32_t>(tx);
                std::vector<uint32_t> &b = bins[index];
                if (b.empty())
                    touched.push_back(index);
                b.push_back(prim);
            }
        }
    }

    void bin(uint32_t prim, int x0, int y0, int x1, int y1)
    {
        if (hwEnabled)
            return;
        binBox(prim, x0, y0, x1, y1);
    }

    void binBox(uint32_t prim, int x0, int y0, int x1, int y1)
    {
        const uint32_t tx0 = static_cast<uint32_t>(std::clamp(x0, 0, 2047)) / kTileSize;
        const uint32_t tx1 = static_cast<uint32_t>(std::clamp(x1, 0, 2047)) / kTileSize;
        const uint32_t ty0 = static_cast<uint32_t>(std::clamp(y0, 0, 2047)) / kTileSize;
        const uint32_t ty1 = static_cast<uint32_t>(std::clamp(y1, 0, 2047)) / kTileSize;
        for (uint32_t ty = ty0; ty <= ty1; ++ty)
            for (uint32_t tx = tx0; tx <= tx1; ++tx)
            {
                std::vector<uint32_t> &b = bins[ty * kTileGrid + tx];
                if (b.empty())
                    touched.push_back(ty * kTileGrid + tx);
                b.push_back(prim);
            }
    }

    uint32_t *newPrim(uint32_t type, uint32_t stateIndex)
    {
        const size_t offset = prims.size();
        prims.resize(offset + kPrimWords, 0u);
        prims[offset] = type | (stateIndex << 8u);
        ++primCount;
        return prims.data() + offset;
    }

    void addPoint(const GSDrawState &state, int x, int y, uint32_t z, const GSVertex &color, uint8_t fog)
    {
        const GSContext &ctx = state.context;
        if (x < ctx.scissor.x0 || x > ctx.scissor.x1 || y < ctx.scissor.y0 || y > ctx.scissor.y1)
            return;
        prepareTarget(state, x, y, x, y);
        const uint32_t s = addState(state);
        uint32_t *p = newPrim(PrimPoint, s);
        p[1] = static_cast<uint32_t>(x);
        p[2] = static_cast<uint32_t>(y);
        p[3] = z;
        p[4] = packColor(color);
        p[5] = fog;
        bin(primCount - 1u, x, y, x, y);
    }

    void addSprite(const GSPrimitiveBatch &batch)
    {
        const GSDrawState &state = batch.state;
        const GSVertex &v0 = batch.vertices[0];
        const GSVertex &v1 = batch.vertices[1];
        const auto &ctx = state.context;
        const GSSpriteAxis axisX = gsSpriteAxis(v0.x, v1.x, static_cast<float>(ctx.xyoffset.ofx) / 16.0f);
        const GSSpriteAxis axisY = gsSpriteAxis(v0.y, v1.y, static_cast<float>(ctx.xyoffset.ofy) / 16.0f);
        const int unclippedX0 = axisX.first;
        const int unclippedY0 = axisY.first;
        const int unclippedX1 = axisX.last;
        const int unclippedY1 = axisY.last;
        if (unclippedX1 < unclippedX0 || unclippedY1 < unclippedY0)
            return;
        if (unclippedX1 < ctx.scissor.x0 || unclippedX0 > ctx.scissor.x1 || unclippedY1 < ctx.scissor.y0 || unclippedY0 > ctx.scissor.y1)
            return;
        const int drawX0 = clampInt(unclippedX0, ctx.scissor.x0, ctx.scissor.x1);
        const int drawY0 = clampInt(unclippedY0, ctx.scissor.y0, ctx.scissor.y1);
        const int drawX1 = clampInt(unclippedX1, ctx.scissor.x0, ctx.scissor.x1);
        const int drawY1 = clampInt(unclippedY1, ctx.scissor.y0, ctx.scissor.y1);

        prepareTarget(state, drawX0, drawY0, drawX1, drawY1);
        const uint32_t s = addState(state);
        uint32_t *p = newPrim(PrimSprite, s);
        p[1] = static_cast<uint32_t>(drawX0) | (static_cast<uint32_t>(drawX1) << 16u);
        p[2] = static_cast<uint32_t>(drawY0) | (static_cast<uint32_t>(drawY1) << 16u);
        p[3] = fbits(axisX.origin);
        p[4] = fbits(axisY.origin);
        p[5] = fbits(axisX.scale);
        p[6] = fbits(axisY.scale);
        if (state.prim.tme)
        {
            float u0f, v0f, u1f, v1f;
            if (state.prim.fst)
            {
                u0f = static_cast<float>(v0.u) / 16.0f;
                v0f = static_cast<float>(v0.v) / 16.0f;
                u1f = static_cast<float>(v1.u) / 16.0f;
                v1f = static_cast<float>(v1.v) / 16.0f;
            }
            else
            {
                const float q0 = fabsQ(v0.q);
                const float q1 = fabsQ(v1.q);
                u0f = (v0.s / q0) * static_cast<float>(state.textureWidth);
                v0f = (v0.t / q0) * static_cast<float>(state.textureHeight);
                u1f = (v1.s / q1) * static_cast<float>(state.textureWidth);
                v1f = (v1.t / q1) * static_cast<float>(state.textureHeight);
            }
            p[7] = fbits(u0f);
            p[8] = fbits(v0f);
            p[9] = fbits(u1f);
            p[10] = fbits(v1f);
        }
        p[13] = static_cast<uint32_t>(v1.z);
        p[14] = packColor(v1);
        p[15] = v1.fog;
        bin(primCount - 1u, drawX0, drawY0, drawX1, drawY1);
    }

    void addTriangle(const GSPrimitiveBatch &batch)
    {
        const GSDrawState &state = batch.state;
        const GSVertex &v0 = batch.vertices[0];
        const GSVertex &v1 = batch.vertices[1];
        const GSVertex &v2 = batch.vertices[2];
        const auto &ctx = state.context;
        GSTriangleRaster tri;
        if (!gsTriangleSetup(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y, ctx.xyoffset.ofx, ctx.xyoffset.ofy, tri, fastTriangleSetup))
            return;
        const int minX = std::max(tri.minX, static_cast<int>(ctx.scissor.x0));
        const int maxX = std::min(tri.maxX, static_cast<int>(ctx.scissor.x1));
        const int minY = std::max(tri.minY, static_cast<int>(ctx.scissor.y0));
        const int maxY = std::min(tri.maxY, static_cast<int>(ctx.scissor.y1));
        if (minX > maxX || minY > maxY)
            return;

        prepareTarget(state, minX, minY, maxX, maxY);
        const uint32_t s = addState(state);
        uint32_t *p = newPrim(PrimTriangle, s);
        p[1] = static_cast<uint32_t>(minX) | (static_cast<uint32_t>(maxX) << 16u);
        p[2] = static_cast<uint32_t>(minY) | (static_cast<uint32_t>(maxY) << 16u);
        for (uint32_t i = 0; i < 3u; ++i)
        {
            p[3u + i * 2u] = static_cast<uint32_t>(static_cast<int32_t>(tri.x[i]));
            p[4u + i * 2u] = static_cast<uint32_t>(static_cast<int32_t>(tri.y[i]));
        }
        p[9] = static_cast<uint32_t>(tri.winding);
        p[10] = fbits(static_cast<float>(tri.invArea));
        // GOW-Port: conservar el recíproco double; p[33..34] estaban libres.
        std::memcpy(p + 33, &tri.invArea, sizeof(tri.invArea));
        std::memcpy(p + 11, &v0.z, 8u);
        std::memcpy(p + 13, &v1.z, 8u);
        std::memcpy(p + 15, &v2.z, 8u);
        p[17] = packColor(v0);
        p[18] = packColor(v1);
        p[19] = packColor(v2);
        const GSVertex *vs[3] = {&v0, &v1, &v2};
        for (uint32_t i = 0; i < 3u; ++i)
        {
            p[20u + i * 3u] = fbits(vs[i]->s);
            p[21u + i * 3u] = fbits(vs[i]->t);
            p[22u + i * 3u] = fbits(vs[i]->q);
            p[29u + i] = static_cast<uint32_t>(vs[i]->u) | (static_cast<uint32_t>(vs[i]->v) << 16u);
        }
        p[32] = static_cast<uint32_t>(v0.fog) | (static_cast<uint32_t>(v1.fog) << 8u) | (static_cast<uint32_t>(v2.fog) << 16u);
        binTriangle(primCount - 1u, tri, minX, minY, maxX, maxY);
    }

    void addLine(const GSPrimitiveBatch &batch)
    {
        const GSDrawState &state = batch.state;
        const GSVertex &v0 = batch.vertices[0];
        const GSVertex &v1 = batch.vertices[1];
        const auto &ctx = state.context;
        const int ofx = ctx.xyoffset.ofx >> 4;
        const int ofy = ctx.xyoffset.ofy >> 4;
        int x0 = static_cast<int>(v0.x) - ofx;
        int y0 = static_cast<int>(v0.y) - ofy;
        const int x1 = static_cast<int>(v1.x) - ofx;
        const int y1 = static_cast<int>(v1.y) - ofy;
        const int dx = std::abs(x1 - x0);
        const int dy = -std::abs(y1 - y0);
        const int sx = (x0 < x1) ? 1 : -1;
        const int sy = (y0 < y1) ? 1 : -1;
        int err = dx + dy;
        int totalSteps = std::max(std::abs(x1 - x0), std::abs(y1 - y0));
        if (totalSteps == 0)
            totalSteps = 1;
        int step = 0;
        for (;;)
        {
            const float t = static_cast<float>(step) / static_cast<float>(totalSteps);
            GSVertex color = v1;
            if (state.prim.iip)
            {
                color.r = clampU8(static_cast<int>(v0.r + (v1.r - v0.r) * t));
                color.g = clampU8(static_cast<int>(v0.g + (v1.g - v0.g) * t));
                color.b = clampU8(static_cast<int>(v0.b + (v1.b - v0.b) * t));
                color.a = clampU8(static_cast<int>(v0.a + (v1.a - v0.a) * t));
            }
            const double z = (v0.z + (v1.z - v0.z) * t);
            const uint8_t fog = clampU8(static_cast<int>(v0.fog + (v1.fog - v0.fog) * t));
            addPoint(state, x0, y0, static_cast<uint32_t>(z), color, fog);
            if (x0 == x1 && y0 == y1)
                break;
            const int e2 = 2 * err;
            if (e2 >= dy)
            {
                err += dy;
                x0 += sx;
            }
            if (e2 <= dx)
            {
                err += dx;
                y0 += sy;
            }
            ++step;
        }
    }

    void loadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut)
    {
        if (!isFourBitIndexedPsm(tex0.psm) && !isEightBitIndexedPsm(tex0.psm))
            return;
        switch (tex0.cld)
        {
        case 1u:
            break;
        case 2u:
            clutCbp[0] = tex0.cbp;
            break;
        case 3u:
            clutCbp[1] = tex0.cbp;
            break;
        case 4u:
            if (clutCbp[0] == tex0.cbp)
                return;
            clutCbp[0] = tex0.cbp;
            break;
        case 5u:
            if (clutCbp[1] == tex0.cbp)
                return;
            clutCbp[1] = tex0.cbp;
            break;
        default:
            return;
        }
        const bool sixteenBit = tex0.cpsm == GS_PSM_CT16 || tex0.cpsm == GS_PSM_CT16S;
        const bool thirtyTwoBit = tex0.cpsm == GS_PSM_CT32 || tex0.cpsm == GS_PSM_CT24;
        if (!sixteenBit && !thirtyTwoBit)
            return;
        std::bitset<kPages> source;
        if (tex0.csm == 0u)
            markPages(source, tex0.cpsm, tex0.cbp, 1u, 0, 0, 15, 15);
        else
        {
            const uint32_t width = texclut.cbw != 0u ? texclut.cbw : 1u;
            const int x0 = static_cast<int>(texclut.cou) * 16;
            markPages(source, tex0.cpsm, tex0.cbp, width, x0, texclut.cov, x0 + 255, texclut.cov);
        }
        if ((source & writePages).any() || batchClutLoads + 2u >= kClutSlots)
        {
            ++stats.flushTexture;
            flushFor(2u);
        }
        const std::array<uint32_t, 6> key = {isFourBitIndexedPsm(tex0.psm) ? 1u : 0u, tex0.cbp,
                                             static_cast<uint32_t>(tex0.cpsm) | (static_cast<uint32_t>(tex0.csm) << 8u) | (static_cast<uint32_t>(tex0.csa) << 16u),
                                             texclut.cbw, texclut.cou, texclut.cov};
        if (clutKeyValid && key == clutKey)
            return;
        clutKey = key;
        clutKeyValid = true;
        clutSourcePages = source;
        if (clutOps.empty())
            clutWriters.fill(0xFFFFu);
        {
            const uint16_t index = static_cast<uint16_t>(clutOps.size());
            const bool fourBit = isFourBitIndexedPsm(tex0.psm);
            const uint32_t count = fourBit ? 16u : 256u;
            const uint32_t destinationBase = (tex0.csa & (sixteenBit ? 0x1Fu : 0x0Fu)) << 4u;
            const bool suffix = tex0.csm == 0u && !sixteenBit && !fourBit;
            for (uint32_t entry = suffix ? destinationBase : 0u; entry < count; entry += 16u)
            {
                if (sixteenBit)
                    clutWriters[((destinationBase + entry) & 0x1FFu) >> 4u] = index;
                else
                {
                    const uint32_t block = ((suffix ? entry : destinationBase + entry) & 0xFFu) >> 4u;
                    clutWriters[block] = index;
                    clutWriters[block + 16u] = index;
                }
            }
        }
        ClutOp op;
        op.writers = clutWriters;
        op.source = clutSlot;
        clutSlot = (clutSlot + 1u) % kClutSlots;
        op.target = clutSlot;
        op.psm = tex0.psm;
        op.cbp = tex0.cbp;
        op.packed = static_cast<uint32_t>(tex0.cpsm) | (static_cast<uint32_t>(tex0.csm) << 8u) | (static_cast<uint32_t>(tex0.csa) << 16u);
        op.cbw = texclut.cbw;
        op.cou = texclut.cou;
        op.cov = texclut.cov;
        op.epoch = epoch;
        clutOps.push_back(op);
        ++batchClutLoads;
        batchClutPages |= source;
    }

    void uploadData(const void *data, size_t size)
    {
        bindUpload(7u, dataBuffer, data, size);
    }

    void reserveData(size_t size)
    {
        if (size > dataCapacity)
        {
            dataCapacity = std::max(size, dataCapacity * 2u);
            gl().BindBuffer(kShaderStorageBuffer, dataBuffer);
            gl().BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(dataCapacity), nullptr, kDynamicDraw);
        }
        gl().BindBufferBase(kShaderStorageBuffer, 7u, dataBuffer);
    }

    void dispatchLinear(uint32_t count, uint32_t kind)
    {
        const GLuint profLinear = profBegin();
        gl().DispatchCompute((count + 255u) / 256u, 1u, 1u);
        profEnd(kind, profLinear);
        barrier();
    }

    void copyRegion(uint32_t spsm, uint32_t sbp, uint32_t sbw, uint32_t ssax, uint32_t ssay, uint32_t rrw, uint32_t rrh, uint32_t dir)
    {
        reserveData(static_cast<size_t>(rrw) * rrh * 4u);
        gl().UseProgram(copyRead.id);
        gl().Uniform4ui(copyRead.loc[0], sbp, sbw, spsm, ssax | (ssay << 16u));
        gl().Uniform4ui(copyRead.loc[1], rrw, rrh, dir, 0u);
        dispatchLinear(rrw * rrh, 3u);
    }

    void localToLocal()
    {
        const uint32_t rrw = transfer.trxreg.rrw;
        const uint32_t rrh = transfer.trxreg.rrh;
        const uint32_t total = rrw * rrh;
        if (total == 0u)
        {
            transferState.direction = 3u;
            return;
        }
        const GSBitBltBuf &b = transfer.bitbltbuf;
        copyRegion(b.spsm, b.sbp, std::max<uint32_t>(b.sbw, 1u), transfer.trxpos.ssax, transfer.trxpos.ssay, rrw, rrh, transfer.trxpos.dir);
        clutKeyValid = false;
        gl().UseProgram(copyWrite.id);
        gl().Uniform4ui(copyWrite.loc[0], b.dbp, std::max<uint32_t>(b.dbw, 1u), b.dpsm,
                        static_cast<uint32_t>(transfer.trxpos.dsax) | (static_cast<uint32_t>(transfer.trxpos.dsay) << 16u));
        gl().Uniform4ui(copyWrite.loc[1], rrw, rrh, transfer.trxpos.dir, 0u);
        dispatchLinear(total, 4u);
        transferState.copiedPixels = total;
        transferState.direction = 3u;
    }

    void localToHostTransfer()
    {
        localToHost.clear();
        localToHostReadPos = 0u;
        const uint32_t rrw = transfer.trxreg.rrw;
        const uint32_t rrh = transfer.trxreg.rrh;
        const uint32_t total = rrw * rrh;
        const GSBitBltBuf &b = transfer.bitbltbuf;
        const uint32_t bpp = static_cast<uint32_t>(GSMem::BitsPerPixel(static_cast<GSMem::PixelStorageMode>(b.spsm)));
        if (total != 0u)
        {
            copyRegion(b.spsm, b.sbp, std::max<uint32_t>(b.sbw, 1u), transfer.trxpos.ssax, transfer.trxpos.ssay, rrw, rrh, 0u);
            scratch.resize(total);
            readData(scratch.data(), static_cast<size_t>(total) * 4u);
        }
        localToHost.reserve((static_cast<size_t>(total) * bpp + 7u) / 8u);
        for (uint32_t pixel = 0u; pixel < total; ++pixel)
        {
            const uint32_t value = scratch[pixel];
            switch (bpp)
            {
            case 32:
                localToHost.push_back(static_cast<uint8_t>(value));
                localToHost.push_back(static_cast<uint8_t>(value >> 8u));
                localToHost.push_back(static_cast<uint8_t>(value >> 16u));
                localToHost.push_back(static_cast<uint8_t>(value >> 24u));
                break;
            case 24:
                localToHost.push_back(static_cast<uint8_t>(value));
                localToHost.push_back(static_cast<uint8_t>(value >> 8u));
                localToHost.push_back(static_cast<uint8_t>(value >> 16u));
                break;
            case 16:
                localToHost.push_back(static_cast<uint8_t>(value));
                localToHost.push_back(static_cast<uint8_t>(value >> 8u));
                break;
            case 8:
                localToHost.push_back(static_cast<uint8_t>(value));
                break;
            case 4:
                if ((pixel & 1u) == 0u)
                {
                    const uint32_t next = pixel + 1u < total ? scratch[pixel + 1u] : 0u;
                    localToHost.push_back(static_cast<uint8_t>((value & 0x0Fu) | ((next & 0x0Fu) << 4u)));
                }
                break;
            default:
                break;
            }
        }
        transferState.copiedPixels = total;
        transferState.localToHostPendingBytes = localToHost.size();
    }

    void uploadImage(const uint8_t *data, uint32_t sizeBytes)
    {
        if (!data || !sizeBytes || transferState.direction != 0u || !transferState.totalPixels)
            return;
        if (transfer.bitbltbuf.dpsm == GS_PSM_CT24 || transfer.bitbltbuf.dpsm == GS_PSM_Z24)
            upload24.consume(data, sizeBytes, [&](const uint8_t *aligned, uint32_t bytes) {
                uploadImageAligned(aligned, bytes);
                return transferState.direction == 0u;
            });
        else
            uploadImageAligned(data, sizeBytes);
    }

    void uploadImageAligned(const uint8_t *data, uint32_t sizeBytes)
    {
        if (!data || sizeBytes == 0u || transferState.direction != 0u)
            return;
        if (transfer.trxreg.rrw == 0u || transfer.trxreg.rrh == 0u || transferState.totalPixels == 0u)
            return;
        const uint8_t dpsm = transfer.bitbltbuf.dpsm;
        uint32_t bitsPer = 0u;
        switch (dpsm)
        {
        case GS_PSM_CT32:
        case GS_PSM_Z32:
            bitsPer = 32u;
            break;
        case GS_PSM_CT24:
        case GS_PSM_Z24:
            bitsPer = 24u;
            break;
        case GS_PSM_CT16:
        case GS_PSM_CT16S:
        case GS_PSM_Z16:
        case GS_PSM_Z16S:
            bitsPer = 16u;
            break;
        case GS_PSM_T8:
        case GS_PSM_T8H:
            bitsPer = 8u;
            break;
        case GS_PSM_T4:
        case GS_PSM_T4HL:
        case GS_PSM_T4HH:
            bitsPer = 4u;
            break;
        default:
            return;
        }
        const uint32_t remaining = transferState.totalPixels - transferState.copiedPixels;
        const uint32_t available = static_cast<uint32_t>((static_cast<uint64_t>(sizeBytes) * 8u) / bitsPer);
        const uint32_t count = std::min(remaining, available);
        if (count == 0u)
            return;
        const size_t bytes = (static_cast<size_t>(count) * bitsPer + 7u) / 8u;
        const uint32_t dbw = std::max<uint32_t>(transfer.bitbltbuf.dbw, 1u);
        clutKeyValid = false;
        if ((!transferQueued && (transferPages & pendingWritePages).any()) || uploadCount >= 0xFFFFu)
            executeTransfers();
        transferQueued = true;
        const size_t dataStart = uploadData_.size();
        uploadData_.resize(dataStart + (bytes + 3u) / 4u, 0u);
        std::memcpy(uploadData_.data() + dataStart, data, std::min<size_t>(bytes, sizeBytes));
        const uint32_t descriptor = uploadCount++;
        const uint32_t words[9] = {transfer.bitbltbuf.dbp, dbw, dpsm, transfer.trxreg.rrw, transferState.copiedPixels, count,
                                   transfer.trxpos.dsax, transfer.trxpos.dsay, static_cast<uint32_t>(dataStart)};
        uploadWords.insert(uploadWords.end(), words, words + 9);
        for (uint32_t group = 0; group < (count + 255u) / 256u; ++group)
            uploadGroups.push_back(descriptor | (group << 16u));
        pendingWritePages |= transferPages;

        transferState.copiedPixels = std::min<uint32_t>(transferState.totalPixels, transferState.copiedPixels + count);
        if (transferState.copiedPixels >= transferState.totalPixels)
        {
            transferState.direction = 3u;
            transferState.totalPixels = 0u;
            return;
        }
        transferState.x = transfer.trxpos.dsax + (transferState.copiedPixels % transfer.trxreg.rrw);
        transferState.y = transfer.trxpos.dsay + (transferState.copiedPixels / transfer.trxreg.rrw);
    }

    void harvest(Readback &slot)
    {
        if (!slot.fence)
            return;
        const auto waitStart = std::chrono::steady_clock::now();
        const GLenum status = gl().ClientWaitSync(slot.fence, 0u, 0ull);
        presentStats.wait += std::chrono::steady_clock::now() - waitStart;
        if (status != kAlreadySignaled && status != kConditionSatisfied)
            return;
        gl().DeleteSync(slot.fence);
        slot.fence = nullptr;
        if (slot.query)
        {
            GLuint64 ns = 0u;
            gl().GetQueryObjectui64v(slot.query, kQueryResult, &ns);
            presentStats.gpuNs += ns;
            ++presentStats.gpuFrames;
            slot.query = 0u;
        }
        if (slot.sequence <= lastFrameSequence)
            return;
        lastFrameSequence = slot.sequence;
        lastFrame.width = slot.width;
        lastFrame.height = slot.height;
        lastFrame.displayFbp = slot.displayFbp;
        lastFrame.sourceFbp = slot.sourceFbp;
        lastFrame.usedPreferred = slot.usedPreferred;
        lastFrame.pixels.resize(static_cast<size_t>(slot.width) * slot.height * 4u);
        std::memcpy(lastFrame.pixels.data(), slot.mapped, lastFrame.pixels.size());
    }

    PresentationFrame presentAsync(uint32_t width, uint32_t height, uint32_t displayFbp,
                                   uint32_t sourceFbp, bool usedPreferred)
    {
        for (uint32_t i = 0; i < readbacks.size(); ++i)
            harvest(readbacks[(readbackNext + i) % readbacks.size()]);
        Readback &slot = readbacks[readbackNext];
        if (slot.fence)
        {
            ++presentStats.readbackSkips;
            if (presentStats.enabled)
                reportPresentStats();
            return lastFrame;
        }
        const size_t bytes = static_cast<size_t>(width) * height * 4u;
        if (slot.capacity < bytes)
        {
            if (slot.buffer)
            {
                gl().BindBuffer(kCopyWriteBuffer, slot.buffer);
                gl().UnmapBuffer(kCopyWriteBuffer);
                gl().DeleteBuffers(1, &slot.buffer);
            }
            gl().GenBuffers(1, &slot.buffer);
            gl().BindBuffer(kCopyWriteBuffer, slot.buffer);
            const GLbitfield flags = kMapReadBit | kMapPersistentBit | kMapCoherentBit;
            gl().BufferStorage(kCopyWriteBuffer, static_cast<GLsizeiptr>(bytes), nullptr, flags | kClientStorageBit);
            slot.mapped = static_cast<const uint8_t *>(gl().MapBufferRange(kCopyWriteBuffer, 0, static_cast<GLsizeiptr>(bytes), flags));
            slot.capacity = bytes;
        }
        barrier();
        gl().BindBuffer(kCopyReadBuffer, dataBuffer);
        gl().BindBuffer(kCopyWriteBuffer, slot.buffer);
        gl().CopyBufferSubData(kCopyReadBuffer, kCopyWriteBuffer, 0, 0, static_cast<GLsizeiptr>(bytes));
        if (presentStats.enabled && presentStats.queryOpen)
        {
            gl().EndQuery(kTimeElapsed);
            slot.query = presentStats.queries[presentStats.queryNext];
            presentStats.queryNext = (presentStats.queryNext + 1u) % static_cast<uint32_t>(presentStats.queries.size());
        }
        slot.fence = gl().FenceSync(kSyncGpuCommandsComplete, 0u);
        const auto flushStart = std::chrono::steady_clock::now();
        gl().Flush();
        presentStats.submit += std::chrono::steady_clock::now() - flushStart;
        slot.width = width;
        slot.height = height;
        slot.displayFbp = displayFbp;
        slot.sourceFbp = sourceFbp;
        slot.usedPreferred = usedPreferred;
        slot.sequence = ++readbackSequence;
        readbackNext = (readbackNext + 1u) % static_cast<uint32_t>(readbacks.size());
        for (uint32_t i = 0; i < readbacks.size(); ++i)
            harvest(readbacks[(readbackNext + i) % readbacks.size()]);
        if (presentStats.enabled)
        {
            GLuint &query = presentStats.queries[presentStats.queryNext];
            if (!query)
                gl().GenQueries(1, &query);
            gl().BeginQuery(kTimeElapsed, query);
            presentStats.queryOpen = true;
            reportPresentStats();
        }
        return lastFrame;
    }

    void reportPresentStats()
    {
        PresentStats &s = presentStats;
        ++s.frames;
        if (stats.prims != s.lastPrims)
            ++s.drawn;
        s.lastPrims = stats.prims;
        const auto now = std::chrono::steady_clock::now();
        const double window = std::chrono::duration<double>(now - s.windowStart).count();
        if (window < 2.0)
            return;
        const double frames = s.frames;
        std::fprintf(stderr,
                     "[gs-gpu] %.1f presents/s, %.1f drawn/s, GPU interval %.2f ms/frame (%s), wait %.2f ms/frame, flush %.2f ms/frame, "
                     "%.1f batches, %.1f clut loads, %.1f transfers per frame, %u readback skips, %u shared skips, %.1f composites/s\n",
                     frames / window, s.drawn / window, s.gpuFrames ? s.gpuNs / 1e6 / s.gpuFrames : 0.0,
                     s.gpuFrames ? "sampled" : "unavailable",
                     std::chrono::duration<double, std::milli>(s.wait).count() / frames,
                     std::chrono::duration<double, std::milli>(s.submit).count() / frames,
                     (stats.batches - s.batches) / frames, (stats.clutLoads - s.clutLoads) / frames,
                     (stats.flushOther - s.transfers) / frames, s.readbackSkips, s.sharedSkips, s.composites / window);
        std::fflush(stderr);
        s.frames = 0u;
        s.drawn = 0u;
        s.readbackSkips = 0u;
        s.sharedSkips = 0u;
        s.composites = 0u;
        s.gpuNs = 0u;
        s.gpuFrames = 0u;
        s.wait = {};
        s.submit = {};
        s.windowStart = now;
        s.batches = stats.batches;
        s.clutLoads = stats.clutLoads;
        s.transfers = stats.flushOther;
    }

    void writeClut(const std::array<uint16_t, 512> &values)
    {
        clutKeyValid = false;
        std::array<uint32_t, 256> words{};
        for (uint32_t i = 0; i < 256u; ++i)
            words[i] = static_cast<uint32_t>(values[i * 2u]) | (static_cast<uint32_t>(values[i * 2u + 1u]) << 16u);
        gl().BindBuffer(kShaderStorageBuffer, clutBuffer);
        gl().BufferSubData(kShaderStorageBuffer, static_cast<GLintptr>(clutSlot) * 1024, 1024, words.data());
    }

    void readClut(std::array<uint16_t, 512> &values)
    {
        std::array<uint32_t, 256> words{};
        barrier();
        gl().BindBuffer(kShaderStorageBuffer, clutBuffer);
        gl().GetBufferSubData(kShaderStorageBuffer, static_cast<GLintptr>(clutSlot) * 1024, 1024, words.data());
        for (uint32_t i = 0; i < 256u; ++i)
        {
            values[i * 2u] = static_cast<uint16_t>(words[i]);
            values[i * 2u + 1u] = static_cast<uint16_t>(words[i] >> 16u);
        }
    }
};

void GSGpuBackend::SetAsyncPresentDefault(bool enabled)
{
    s_asyncPresent.store(enabled, std::memory_order_relaxed);
}

GSGpuBackend::GSGpuBackend()
    : m_impl(std::make_unique<Impl>(m_stats))
{
    const char *setting = std::getenv("PS2X_GS_TEXTURE_PAGE_CACHE");
    m_impl->cacheTexturePages = !setting || std::string_view(setting) != "0";
    setting = std::getenv("PS2X_GS_FAST_TRIANGLE_SETUP");
    m_impl->fastTriangleSetup = !setting || std::string_view(setting) != "0";
}

GSGpuBackend::~GSGpuBackend() = default;

void GSGpuBackend::SetTexturePageCacheEnabled(bool enabled)
{
    m_impl->cacheTexturePages = enabled;
}

void GSGpuBackend::SetFastTriangleSetupEnabled(bool enabled)
{
    m_impl->fastTriangleSetup = enabled;
}

void GSGpuBackend::SetHardwareRasterAllowed(bool allowed)
{
    m_impl->hwAllowed = allowed;
}

void GSGpuBackend::Initialize(uint8_t *vram, uint32_t vramSize)
{
    Impl &d = *m_impl;
    d.hostVram = vram;
    d.hostVramSize = vramSize;
    d.resetBatch();
    Reset();
    if (d.ensure())
        d.uploadHostVram();
}

bool GSGpuBackend::IsReady() const
{
    return m_impl->initialized && !m_impl->failed;
}

void GSGpuBackend::Reset()
{
    Impl &d = *m_impl;
    ++d.contentRevision;
    d.flushBatch();
    d.clutCbp.fill(0u);
    d.transfer = {};
    d.transfer.direction = 3u;
    d.transferState = {};
    d.transferState.direction = 3u;
    d.upload24 = {}; // GOW-Port: reset descarta el pixel incompleto.
    d.localToHost.clear();
    d.localToHostReadPos = 0u;
    if (d.hostVram && d.hostVramSize && d.ensure())
    {
        std::array<uint16_t, 512> zeros{};
        d.writeClut(zeros);
    }
}

void GSGpuBackend::Submit(const GSPrimitiveBatch &batch)
{
    Impl &d = *m_impl;
    if (batch.vertexCount == 0u || !d.ensure())
        return;
    const GSGpuRoundingScope rounding;
    ++d.contentRevision;
    switch (batch.state.prim.type)
    {
    case GS_PRIM_SPRITE:
        d.addSprite(batch);
        break;
    case GS_PRIM_TRIANGLE:
    case GS_PRIM_TRISTRIP:
    case GS_PRIM_TRIFAN:
        d.addTriangle(batch);
        break;
    case GS_PRIM_LINE:
    case GS_PRIM_LINESTRIP:
        d.addLine(batch);
        break;
    case GS_PRIM_POINT:
    {
        const GSVertex &v = batch.vertices[0];
        const auto &ctx = batch.state.context;
        d.addPoint(batch.state, static_cast<int>(v.x) - (ctx.xyoffset.ofx >> 4), static_cast<int>(v.y) - (ctx.xyoffset.ofy >> 4),
                   static_cast<uint32_t>(v.z), v, v.fog);
        break;
    }
    default:
        break;
    }
}

void GSGpuBackend::LoadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut)
{
    Impl &d = *m_impl;
    if (d.ensure())
        d.loadClut(tex0, texclut);
}

void GSGpuBackend::BeginTransfer(const GSTransferCommand &command)
{
    Impl &d = *m_impl;
    if (command.direction == 2u)
        ++d.contentRevision;
    if (!d.ensure())
        return;
    bool flush = true;
    d.transferPages.reset();
    d.transferQueued = false;
    if (command.direction == 0u)
    {
        const GSBitBltBuf &b = command.bitbltbuf;
        const int x0 = static_cast<int>(command.trxpos.dsax);
        const int y0 = static_cast<int>(command.trxpos.dsay);
        markPages(d.transferPages, b.dpsm, b.dbp, std::max<uint32_t>(b.dbw, 1u), x0, y0, x0 + static_cast<int>(command.trxreg.rrw) - 1,
                  y0 + static_cast<int>(command.trxreg.rrh) - 1);
    }
    if (command.direction == 0u && d.deferUploads)
    {
        const std::bitset<kPages> &destination = d.transferPages;
        flush = (destination & d.writePages).any();
        if (!flush && !d.copyOnWrite(destination & (d.readPages | d.batchClutPages)))
            flush = true;
        if (d.prof.enabled && flush && d.primCount != 0u)
        {
            if ((destination & d.writePages).any())
                ++d.prof.uploadHazards[0];
            else
                ++d.prof.uploadHazards[2];
        }
    }
    if (flush)
    {
        ++m_stats.flushOther;
        d.flushFor(3u);
    }
    d.transfer = command;
    d.upload24 = {}; // GOW-Port: no heredar datos de otra transferencia.
    d.transferState.x = command.trxpos.dsax;
    d.transferState.y = command.trxpos.dsay;
    d.transferState.totalPixels = static_cast<uint32_t>(command.trxreg.rrw) * static_cast<uint32_t>(command.trxreg.rrh);
    d.transferState.copiedPixels = 0u;
    d.transferState.direction = command.direction;
    d.transferState.localToHostPendingBytes = 0u;
    if (command.direction == 2u)
        d.localToLocal();
    else if (command.direction == 1u)
        d.localToHostTransfer();
}

void GSGpuBackend::UploadImage(const uint8_t *data, uint32_t sizeBytes)
{
    Impl &d = *m_impl;
    if (data && sizeBytes)
        ++d.contentRevision;
    if (!d.ensure())
        return;
    d.uploadImage(data, sizeBytes);
}

void GSGpuBackend::Flush()
{
    m_impl->flushFor(4u);
}

void GSGpuBackend::TextureFlush()
{
}

void GSGpuBackend::Sync(GSSyncReason reason)
{
    Impl &d = *m_impl;
    if (!d.hostVram || !d.hostVramSize || !d.ensure())
        return;
    d.flushFor(5u);
    // GOW-Port: FINISH informa al EE solo tras completar el rasterizado en GL.
    static const bool finishAsync = [] { const char *v = std::getenv("GOW_GS_FINISH_ASINCRONO"); return v && v[0] == '1'; }();
    if (reason == GSSyncReason::Finish && !finishAsync)
        d.gl().Finish();
    if (reason == GSSyncReason::DebugReadback && d.hostVram)
        d.downloadVram(d.hostVram, d.hostVramSize);
}

PresentationFrame GSGpuBackend::Present(const GSPresentationRequest &request)
{
    Impl &d = *m_impl;
    PresentationFrame result{};
    if (!d.ensure())
        return result;
    d.flushBatch();
    const bool shared = d.context.Shared() && GSSharedPresent::Active();
    // GOW-Port: paridad real del GS en modo de campos; el modo progresivo no alterna.
    const uint32_t fieldFlags = (request.smode2 & 3u) == 1u
        ? 1u | (static_cast<uint32_t>(request.vsyncTick & 1u) << 1u) : 0u;
    const std::array<uint64_t, 11> crtc = {request.pmode, request.smode2, request.dispfb1, request.display1,
        request.dispfb2, request.display2, request.bgcolor,
        static_cast<uint64_t>(request.preferredSource.fbp) |
            (static_cast<uint64_t>(request.preferredSource.fbw) << 32u) |
            (static_cast<uint64_t>(request.preferredSource.psm) << 48u),
        request.preferredDestFbp, request.hasPreferredSource ? 1u : 0u, fieldFlags};
    if (shared && d.presentedRevision == d.contentRevision && d.presentedCrtc == crtc)
    {
        if (d.presentStats.enabled)
            d.reportPresentStats();
        return result;
    }
    if (shared && !SharedAvailable(d.gl()))
    {
        ++d.presentStats.sharedSkips;
        if (d.presentStats.enabled)
            d.reportPresentStats();
        return result;
    }
    const bool enable1 = (request.pmode & 0x1ull) != 0ull;
    const bool enable2 = (request.pmode & 0x2ull) != 0ull;
    const bool mmod = ((request.pmode >> 5) & 0x1ull) != 0ull;
    const bool slbg = ((request.pmode >> 7) & 0x1ull) != 0ull;
    const uint32_t alp = static_cast<uint32_t>((request.pmode >> 8) & 0xFFull);
    const bool halfHeightBuffer = (request.smode2 & 0x3ull) == 0x3ull;
    const CrtcCircuit circuits[2] = {decodeCircuit(enable1, request.dispfb1, request.display1, halfHeightBuffer),
                                     decodeCircuit(enable2, request.dispfb2, request.display2, halfHeightBuffer)};
    if (!circuits[0].enabled && !circuits[1].enabled && !shared)
        return result;
    int32_t x0 = INT32_MAX, y0 = INT32_MAX, x1 = INT32_MIN, y1 = INT32_MIN;
    int32_t hstep = INT32_MAX, vstep = INT32_MAX;
    for (const CrtcCircuit &c : circuits)
    {
        if (!c.enabled)
            continue;
        x0 = std::min(x0, c.dx);
        y0 = std::min(y0, c.dy);
        x1 = std::max(x1, c.dx + c.dw);
        y1 = std::max(y1, c.dy + c.dh);
        hstep = std::min(hstep, c.hdiv);
        vstep = std::min(vstep, c.vdiv);
    }
    const bool blank = !circuits[0].enabled && !circuits[1].enabled;
    if (blank)
    {
        x0 = y0 = 0;
        x1 = y1 = hstep = vstep = 1;
    }
    const uint32_t width = std::min<uint32_t>(kMaxPresentationWidth, static_cast<uint32_t>((x1 - x0 + hstep - 1) / hstep));
    const uint32_t height = std::min<uint32_t>(kMaxPresentationHeight, static_cast<uint32_t>((y1 - y0 + vstep - 1) / vstep));
    result.width = width;
    result.height = height;
    auto pack = [](const CrtcCircuit &c, std::array<uint32_t, 12> &out)
    {
        // GOW-Port: convertir las páginas DISPFB una sola vez; el shader recibe bloques.
        out = {c.enabled ? 1u : 0u, c.fbp * 32u, c.fbw, c.psm, c.dbx, c.dby, static_cast<uint32_t>(c.dx), static_cast<uint32_t>(c.dy),
               static_cast<uint32_t>(c.dw), static_cast<uint32_t>(c.dh), static_cast<uint32_t>(c.hdiv), static_cast<uint32_t>(c.vdiv)};
    };
    std::array<uint32_t, 12> c1{}, c2{};
    pack(circuits[0], c1);
    pack(circuits[1], c2);
    result.displayFbp = circuits[0].enabled ? circuits[0].fbp : circuits[1].fbp;
    result.sourceFbp = result.displayFbp;
    // GOW-Port: igualar la selección del CPU sin cambiar el renderer de referencia.
    // TEX0/preferredSource usa bloques de 256 B; DISPFB usa páginas de 8 KB.
    const auto &source = request.preferredSource;
    const bool sourceFormat = source.psm == GS_PSM_CT32 || source.psm == GS_PSM_CT24 ||
                              source.psm == GS_PSM_CT16 || source.psm == GS_PSM_CT16S;
    if (circuits[0].enabled != circuits[1].enabled && request.hasPreferredSource && sourceFormat &&
        request.preferredDestFbp == result.displayFbp &&
        (source.fbw != 0u || source.fbp != result.displayFbp))
    {
        auto &c = circuits[0].enabled ? c1 : c2;
        c[1] = source.fbp;
        c[2] = source.fbw ? source.fbw : 10u;
        c[3] = source.psm;
        c[4] = c[5] = 0u;
        result.sourceFbp = source.fbp;
        result.usedPreferred = true;
    }
    d.reserveData(static_cast<size_t>(width) * height * 4u);
    const Api &gl = d.gl();
    gl.UseProgram(d.present.id);
    gl.Uniform4ui(d.present.loc[0], width, height, static_cast<uint32_t>(x0 & 0xFFFF) | (static_cast<uint32_t>(y0) << 16u),
                  static_cast<uint32_t>(hstep) | (static_cast<uint32_t>(vstep) << 16u));
    gl.Uniform1uiv(d.present.loc[1], 12, c1.data());
    gl.Uniform1uiv(d.present.loc[2], 12, c2.data());
    gl.Uniform4ui(d.present.loc[3], static_cast<uint32_t>(request.bgcolor & 0xFFFFFFu), (slbg ? 1u : 0u) | (mmod ? 2u : 0u), alp, fieldFlags);
    const GLuint profPresent = d.profBegin();
    gl.DispatchCompute((width + 15u) / 16u, (height + 15u) / 16u, 1u);
    ++d.presentStats.composites;
    d.profEnd(5u, profPresent);
    d.profFrame();
    if (shared)
    {
        if (PublishShared(gl, d.dataBuffer, width, height, d.renderedSequence + 1u, d.presentHash.id, d.presentHash.loc[0]))
        {
            ++d.renderedSequence;
            d.presentedRevision = d.contentRevision;
            d.presentedCrtc = crtc;
        }
        else
            ++d.presentStats.sharedSkips;
        if (d.presentStats.enabled)
            d.reportPresentStats();
        return {};
    }
    if (s_asyncPresent.load(std::memory_order_relaxed))
        return gowPresentationRows(d.presentAsync(width, height, result.displayFbp, result.sourceFbp, result.usedPreferred));
    result.pixels.resize(static_cast<size_t>(width) * height * 4u);
    d.readData(result.pixels.data(), result.pixels.size());
    return gowPresentationRows(std::move(result));
}

bool GSGpuBackend::ClearFramebuffer(const GSContext &context, uint32_t rgba)
{
    Impl &d = *m_impl;
    ++d.contentRevision;
    if (!d.ensure() || context.frame.fbw == 0u)
        return false;
    const uint8_t psm = context.frame.psm;
    const bool full = psm == GS_PSM_CT32 || psm == GS_PSM_CT24;
    const bool half = psm == GS_PSM_CT16 || psm == GS_PSM_CT16S;
    if (!full && !half)
        return false;
    d.flushBatch();
    uint8_t r = static_cast<uint8_t>(rgba);
    uint8_t g = static_cast<uint8_t>(rgba >> 8u);
    uint8_t b = static_cast<uint8_t>(rgba >> 16u);
    uint8_t a = static_cast<uint8_t>(rgba >> 24u);
    if ((context.fba & 1ull) != 0ull && psm != GS_PSM_CT24)
        a |= 0x80u;
    uint32_t source;
    uint32_t mask = context.frame.fbmsk;
    if (full)
        source = static_cast<uint32_t>(r) | (static_cast<uint32_t>(g) << 8u) | (static_cast<uint32_t>(b) << 16u) | (static_cast<uint32_t>(a) << 24u);
    else
    {
        source = ((r >> 3) & 0x1Fu) | (((g >> 3) & 0x1Fu) << 5) | (((b >> 3) & 0x1Fu) << 10) | ((a >= 0x40u) ? 0x8000u : 0u);
        mask &= 0xFFFFu;
    }
    const uint32_t x0 = context.scissor.x0;
    const uint32_t x1 = std::max<uint32_t>(x0, context.scissor.x1);
    const uint32_t y0 = context.scissor.y0;
    const uint32_t y1 = std::max<uint32_t>(y0, context.scissor.y1);
    const Api &gl = d.gl();
    d.clutKeyValid = false;
    gl.UseProgram(d.clear.id);
    gl.Uniform4ui(d.clear.loc[0], context.frame.fbp << 5u, std::max<uint32_t>(context.frame.fbw, 1u) | (static_cast<uint32_t>(psm) << 16u), mask, source);
    gl.Uniform4ui(d.clear.loc[1], x0, y0, x1, y1);
    gl.DispatchCompute((x1 - x0 + 16u) / 16u, (y1 - y0 + 16u) / 16u, 1u);
    d.barrier();
    return true;
}

uint32_t GSGpuBackend::ConsumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes)
{
    Impl &d = *m_impl;
    if (!dst || maxBytes == 0u || d.localToHostReadPos >= d.localToHost.size())
        return 0u;
    const size_t count = std::min<size_t>(maxBytes, d.localToHost.size() - d.localToHostReadPos);
    std::memcpy(dst, d.localToHost.data() + d.localToHostReadPos, count);
    d.localToHostReadPos += count;
    d.transferState.localToHostPendingBytes = d.localToHost.size() - d.localToHostReadPos;
    return static_cast<uint32_t>(count);
}

uint32_t GSGpuBackend::ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
{
    Impl &d = *m_impl;
    if (!d.ensure())
        return 0u;
    d.flushBatch();
    d.reserveData(16u);
    const Api &gl = d.gl();
    d.clutKeyValid = false;
    gl.UseProgram(d.poke.id);
    gl.Uniform4ui(d.poke.loc[0], psm, base, bw, (x & 0xFFFFu) | (y << 16u));
    gl.Uniform4ui(d.poke.loc[1], 0u, 0u, 0u, 0u);
    gl.DispatchCompute(1u, 1u, 1u);
    uint32_t value = 0u;
    d.readData(&value, sizeof(value));
    return value;
}

void GSGpuBackend::WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value)
{
    Impl &d = *m_impl;
    ++d.contentRevision;
    if (!d.ensure())
        return;
    d.flushBatch();
    const Api &gl = d.gl();
    d.clutKeyValid = false;
    gl.UseProgram(d.poke.id);
    gl.Uniform4ui(d.poke.loc[0], psm, base, bw, (x & 0xFFFFu) | (y << 16u));
    gl.Uniform4ui(d.poke.loc[1], value, 1u, 0u, 0u);
    gl.DispatchCompute(1u, 1u, 1u);
    d.barrier();
}

void GSGpuBackend::SnapshotVram(std::vector<uint8_t> &out) const
{
    Impl &d = *m_impl;
    if (!d.ensure())
    {
        out.clear();
        return;
    }
    d.flushBatch();
    out.resize(GSSwizzle::kMemorySize);
    d.downloadVram(out.data(), out.size());
}

GSTransferSnapshot GSGpuBackend::GetTransferSnapshot() const
{
    const Impl &d = *m_impl;
    GSTransferSnapshot result = d.transferState;
    result.localToHostPendingBytes = d.localToHostReadPos < d.localToHost.size() ? d.localToHost.size() - d.localToHostReadPos : 0u;
    return result;
}

bool GSGpuBackend::ExportState(GSBackendState &out)
{
    Impl &d = *m_impl;
    if (!d.ensure())
        return false;
    d.flushBatch();
    d.readClut(out.clut);
    out.clutCbp = d.clutCbp;
    out.cachePageBase = UINT32_MAX;
    out.cacheBytes.fill(0u);
    out.transfer = d.transfer;
    out.transferState = d.transferState;
    out.upload24 = d.upload24;
    out.localToHost = d.localToHost;
    out.localToHostReadPos = d.localToHostReadPos;
    return true;
}

bool GSGpuBackend::ImportState(const GSBackendState &state)
{
    Impl &d = *m_impl;
    if (state.upload24.size >= 3u) return false; // GOW-Port: solo hay uno o dos bytes pendientes.
    if (!d.ensure())
        return false;
    d.flushBatch();
    d.writeClut(state.clut);
    d.clutCbp = state.clutCbp;
    d.transfer = state.transfer;
    d.transferState = state.transferState;
    d.upload24 = state.upload24;
    d.localToHost = state.localToHost;
    d.localToHostReadPos = static_cast<size_t>(state.localToHostReadPos);
    return true;
}
