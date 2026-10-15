// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_shared_present.h"
#include "ThreadPriority.h"
#include "ThreadNaming.h"

#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <xmmintrin.h>

namespace
{
    constexpr size_t kPublishBytes = 64u * 1024u;
    constexpr size_t kMaxPendingChunks = 256u;
    std::atomic<bool> s_enabledByDefault{false};
    std::atomic<bool> s_gpuByDefault{false};

    bool discardDraws()
    {
        static const bool discard = []
        {
            const char *value = std::getenv("PS2X_GS_DISCARD_DRAWS");
            return value && *value && *value != '0';
        }();
        return discard;
    }

    struct LoadClutArgs
    {
        GSTex0Reg tex0;
        GSTexClutReg texclut;
    };

    struct WriteVramArgs
    {
        uint32_t psm;
        uint32_t base;
        uint32_t bw;
        uint32_t x;
        uint32_t y;
        uint32_t value;
    };

    template <typename T>
    T readAt(const uint8_t *data)
    {
        T value;
        std::memcpy(&value, data, sizeof(T));
        return value;
    }
}

// GOW-Port: presentación por buzón (PS2X_GS_PRESENT_BUZON=1; sin contexto GL compartido, como en Linux).
// Antes, en cada VSync el hilo principal hacía Flush + Sync + Present con RunOnWorker: esperaba a que el hilo
// del GS vaciara toda su cola, y con el juego a 50-60 cuadros/s la cola no se vaciaba nunca (ventana a 6-10
// cuadros/s). Ahora Present se encola en orden con el resto de comandos; el hilo del GS deja el cuadro en el
// buzón y el hilo principal muestra el último que haya, sin esperar. Un solo backend con hilo por proceso.
namespace
{
    std::atomic<bool> g_presentMailbox{false};
    std::mutex g_mailboxMutex;
    PresentationFrame g_mailboxFrame;
    // GOW-Port: número del cuadro del buzón y del último entregado al hilo principal. Si no cambió, Present no copia
    // el cuadro otra vez (con resolución interna son varios MB por VSync).
    uint64_t g_mailboxSequence = 0u;
    uint64_t g_mailboxDelivered = 0u;
}

bool gowGsPresentMailboxActive()
{
    return g_presentMailbox.load(std::memory_order_relaxed);
}

uint64_t gowGsPresentMailboxDelivered()
{
    std::lock_guard<std::mutex> lock(g_mailboxMutex);
    return g_mailboxDelivered;
}

GSThreadedBackend::GSThreadedBackend(std::unique_ptr<GSRasterBackend> inner)
    : m_inner(std::move(inner))
{
    // GOW-Port: el buzón se decide en cada backend (uno por proceso) y empieza vacío.
    {
        const char *mailbox = std::getenv("PS2X_GS_PRESENT_BUZON");
        std::lock_guard<std::mutex> lock(g_mailboxMutex);
        g_presentMailbox.store(mailbox && mailbox[0] == '1' && !GSSharedPresent::Active(), std::memory_order_relaxed);
        g_mailboxFrame = {};
        g_mailboxSequence = g_mailboxDelivered = 0u;
    }
    const char *compact = std::getenv("PS2X_GS_COMPACT_QUEUE");
    m_compactQueue = !compact || *compact != '0';
    if (const char *limit = std::getenv("PS2X_GS_QUEUE_CHUNKS"))
        m_queueChunkLimit = static_cast<size_t>(std::clamp(std::atoi(limit), 1, static_cast<int>(kMaxPendingChunks)));
    m_open.reserve(kPublishBytes + 4096u);
    m_worker = std::thread([this]
                           { WorkerLoop(); });
}

GSThreadedBackend::~GSThreadedBackend()
{
    // GOW-Port: completar incluso el último bloque antes de cerrar el contexto GL.
    Drain();
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_stop = true;
        m_pending.clear();
    }
    m_workCv.notify_all();
    if (m_worker.joinable())
        m_worker.join();
}

std::unique_ptr<GSRasterBackend> GSThreadedBackend::MakeDefault()
{
    const char *value = std::getenv("PS2X_GS_THREAD");
    const bool enabled = (value && *value) ? *value != '0' : s_enabledByDefault.load();
    const char *gpu = std::getenv("PS2X_GS_GPU");
    const bool useGpu = (gpu && *gpu) ? *gpu != '0' : s_gpuByDefault.load();
    if (useGpu)
    {
        // GOW-Port: PS2X_GS_ASYNC_PRESENT=1 lee el cuadro presentado con un PBO y una fence en vez de
        // glGetBufferSubData: el hilo del GS ya no espera a que la GPU termine en cada presentación (en Linux no
        // hay presentación compartida; en partida el hilo del GS pasaba ~82 % del tiempo en el driver). Se
        // muestra el último cuadro ya leído (un cuadro de retraso como mucho).
        const char *async = std::getenv("PS2X_GS_ASYNC_PRESENT");
        if (async && async[0] == '1')
            GSGpuBackend::SetAsyncPresentDefault(true);
        return std::make_unique<GSThreadedBackend>(std::make_unique<GSGpuBackend>());
    }
    if (!enabled)
        return std::make_unique<GSCpuBackend>();
    return std::make_unique<GSThreadedBackend>(std::make_unique<GSCpuBackend>());
}

void GSThreadedBackend::SetEnabledByDefault(bool enabled)
{
    s_enabledByDefault.store(enabled);
}

void GSThreadedBackend::SetGpuByDefault(bool enabled)
{
    s_gpuByDefault.store(enabled);
}

void GSThreadedBackend::Enqueue(Op op, const void *payload, uint32_t size)
{
    std::lock_guard<std::mutex> lock(m_producerMutex);
    const uint32_t csr = _mm_getcsr();
    if (csr != m_lastMxcsr)
    {
        m_lastMxcsr = csr;
        const uint8_t header = static_cast<uint8_t>(Op::Mxcsr);
        const uint32_t csrSize = sizeof(csr);
        m_open.push_back(header);
        m_open.insert(m_open.end(), reinterpret_cast<const uint8_t *>(&csrSize), reinterpret_cast<const uint8_t *>(&csrSize) + 4);
        m_open.insert(m_open.end(), reinterpret_cast<const uint8_t *>(&csr), reinterpret_cast<const uint8_t *>(&csr) + 4);
    }
    const auto append = [&](Op kind, const void *bytes, uint32_t length)
    {
        uint8_t header[5];
        header[0] = static_cast<uint8_t>(kind);
        std::memcpy(header + 1u, &length, sizeof(length));
        m_open.insert(m_open.end(), header, header + sizeof(header));
        if (length)
            m_open.insert(m_open.end(), static_cast<const uint8_t *>(bytes), static_cast<const uint8_t *>(bytes) + length);
    };
    if (op == Op::Submit && m_compactQueue)
    {
        const auto &draw = *static_cast<const GSPrimitiveBatch *>(payload);
        if (!m_drawStateValid || std::memcmp(&m_lastDrawState, &draw.state, sizeof(draw.state)) != 0)
        {
            std::memcpy(&m_lastDrawState, &draw.state, sizeof(draw.state));
            m_drawStateValid = true;
            append(Op::DrawState, &draw.state, sizeof(draw.state));
        }
        append(Op::Vertices, &draw, static_cast<uint32_t>(offsetof(GSPrimitiveBatch, state)));
    }
    else
        append(op, payload, size);
    if (m_open.size() >= kPublishBytes)
        PublishLocked();
}

void GSThreadedBackend::PublishLocked()
{
    if (m_open.empty())
        return;
    std::vector<uint8_t> next;
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_doneCv.wait(lock, [&]
                      { return m_stop || m_pending.size() < m_queueChunkLimit; });
        m_pending.push_back(std::move(m_open));
        ++m_published;
        if (!m_spare.empty())
        {
            next = std::move(m_spare.back());
            m_spare.pop_back();
        }
    }
    m_workCv.notify_one();
    next.clear();
    m_open = std::move(next);
    if (m_open.capacity() < kPublishBytes)
        m_open.reserve(kPublishBytes + 4096u);
}

void GSThreadedBackend::Drain() const
{
    auto *self = const_cast<GSThreadedBackend *>(this);
    uint64_t target = 0u;
    {
        std::lock_guard<std::mutex> lock(m_producerMutex);
        self->PublishLocked();
        std::lock_guard<std::mutex> queueLock(m_queueMutex);
        target = m_published;
    }
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_doneCv.wait(lock, [&]
                  { return m_completed >= target || m_stop; });
}

void GSThreadedBackend::WorkerLoop()
{
    ThreadNaming::SetCurrentThreadName("GSThread");
    ThreadPriority::RaiseCurrentThread(ThreadPriority::Level::AboveNormal);
    GSPrimitiveBatch draw;
    for (;;)
    {
        std::vector<uint8_t> chunk;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_workCv.wait(lock, [&]
                          { return m_stop || !m_pending.empty(); });
            if (m_stop)
            {
                m_inner.reset();
                return;
            }
            chunk = std::move(m_pending.front());
            m_pending.pop_front();
        }
        {
            std::lock_guard<std::mutex> exec(m_execMutex);
            Execute(chunk, draw);
        }
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            ++m_completed;
            if (m_spare.size() < 64u)
                m_spare.push_back(std::move(chunk));
        }
        m_doneCv.notify_all();
    }
}

void GSThreadedBackend::Execute(const std::vector<uint8_t> &chunk, GSPrimitiveBatch &draw)
{
    const uint8_t *data = chunk.data();
    const size_t size = chunk.size();
    size_t offset = 0u;
    // GOW-Port: PS2X_GS_OP_PROF=1: tiempo del hilo del GS por tipo de comando (cada 5 s).
    static const bool opProf = [] { const char *v = std::getenv("PS2X_GS_OP_PROF"); return v && v[0] == '1'; }();
    static std::array<double, 12> opMs{};
    static std::array<uint64_t, 12> opCount{};
    static auto opReport = std::chrono::steady_clock::now();
    while (offset + 5u <= size)
    {
        const Op op = static_cast<Op>(data[offset]);
        const uint32_t length = readAt<uint32_t>(data + offset + 1u);
        const uint8_t *payload = data + offset + 5u;
        offset += 5u + length;
        const auto opStart = opProf ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
        struct OpTimer
        {
            bool on; Op op; std::chrono::steady_clock::time_point start;
            ~OpTimer()
            {
                if (!on || static_cast<size_t>(op) >= opMs.size())
                    return;
                const auto now = std::chrono::steady_clock::now();
                opMs[static_cast<size_t>(op)] += std::chrono::duration<double, std::milli>(now - start).count();
                ++opCount[static_cast<size_t>(op)];
                if (now - opReport < std::chrono::seconds(5))
                    return;
                static const char *kNames[12] = {"mxcsr", "submit", "clut", "transfer", "upload", "texflush",
                                                 "writevram", "sync", "present", "drawstate", "vertices", "call"};
                std::fprintf(stderr, "[gs-op-prof]");
                for (size_t i = 0; i < opMs.size(); ++i)
                    if (opCount[i])
                        std::fprintf(stderr, " %s %.0fms/%llu", kNames[i], opMs[i], static_cast<unsigned long long>(opCount[i]));
                std::fprintf(stderr, "\n");
                opMs.fill(0.0);
                opCount.fill(0u);
                opReport = now;
            }
        } opTimer{opProf, op, opStart};
        switch (op)
        {
        case Op::Mxcsr:
            _mm_setcsr(readAt<uint32_t>(payload));
            break;
        case Op::Submit:
            if (!discardDraws())
                m_inner->Submit(readAt<GSPrimitiveBatch>(payload));
            break;
        case Op::LoadClut:
        {
            const LoadClutArgs args = readAt<LoadClutArgs>(payload);
            m_inner->LoadClut(args.tex0, args.texclut);
            break;
        }
        case Op::BeginTransfer:
            m_inner->BeginTransfer(readAt<GSTransferCommand>(payload));
            break;
        case Op::Upload:
            m_inner->UploadImage(payload, length);
            break;
        case Op::TextureFlush:
            m_inner->TextureFlush();
            break;
        case Op::WriteVram:
        {
            const WriteVramArgs a = readAt<WriteVramArgs>(payload);
            m_inner->WriteVram(a.psm, a.base, a.bw, a.x, a.y, a.value);
            break;
        }
        case Op::Sync:
            m_inner->Sync(readAt<GSSyncReason>(payload));
            break;
        case Op::DrawState:
            std::memcpy(&draw.state, payload, sizeof(draw.state));
            break;
        case Op::Vertices:
            std::memcpy(&draw, payload, offsetof(GSPrimitiveBatch, state));
            if (!discardDraws())
                m_inner->Submit(draw);
            break;
        case Op::Present:
            if (gowGsPresentMailboxActive())
            {
                PresentationFrame frame = m_inner->Present(readAt<GSPresentationRequest>(payload));
                if (frame)
                {
                    std::lock_guard<std::mutex> lock(g_mailboxMutex);
                    g_mailboxFrame = std::move(frame);
                    ++g_mailboxSequence;
                }
            }
            else
                m_inner->Present(readAt<GSPresentationRequest>(payload));
            break;
        case Op::Call:
            (*readAt<const std::function<void()> *>(payload))();
            break;
        }
    }
}

void GSThreadedBackend::RunOnWorker(const std::function<void()> &function) const
{
    auto *self = const_cast<GSThreadedBackend *>(this);
    const std::function<void()> *pointer = &function;
    self->Enqueue(Op::Call, &pointer, sizeof(pointer));
    Drain();
}

void GSThreadedBackend::Initialize(uint8_t *vram, uint32_t vramSize)
{
    RunOnWorker([&] {
        m_inner->Initialize(vram, vramSize);
        // GOW-Port: un error GL debe conservar la salida CPU, no descartar los dibujos.
        if (auto *gpu = dynamic_cast<GSGpuBackend *>(m_inner.get()); gpu && !gpu->IsReady())
        {
            std::fprintf(stderr, "[gow-gs] OpenGL no disponible; usando CPU en el hilo GS.\n");
            m_inner = std::make_unique<GSCpuBackend>();
            m_inner->Initialize(vram, vramSize);
        }
    });
}

void GSThreadedBackend::Reset()
{
    RunOnWorker([&] { m_inner->Reset(); });
}

void GSThreadedBackend::Submit(const GSPrimitiveBatch &batch)
{
    Enqueue(Op::Submit, &batch, sizeof(batch));
}

void GSThreadedBackend::LoadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut)
{
    const LoadClutArgs args{tex0, texclut};
    Enqueue(Op::LoadClut, &args, sizeof(args));
}

void GSThreadedBackend::BeginTransfer(const GSTransferCommand &command)
{
    Enqueue(Op::BeginTransfer, &command, sizeof(command));
}

void GSThreadedBackend::UploadImage(const uint8_t *data, uint32_t sizeBytes)
{
    Enqueue(Op::Upload, data, data ? sizeBytes : 0u);
}

void GSThreadedBackend::Flush()
{
    // GOW-Port: barrera para lectura/presentación y llamadas del frontend existente.
    RunOnWorker([&] { m_inner->Flush(); });
}

void GSThreadedBackend::TextureFlush()
{
    Enqueue(Op::TextureFlush, nullptr, 0u);
}

// GOW-Port: GOW_GS_FINISH_ASINCRONO=1 (opcional, desactivado por defecto) encola FINISH en el hilo del GS
// sin esperar ni glFinish: el EE ve el bit FINISH enseguida. Las lecturas de VRAM desde el EE ya sincronizan
// por su cuenta (RunOnWorker) y el hilo del GS conserva el orden de los comandos.
static bool gowFinishAsync()
{
    static const bool on = [] { const char *v = std::getenv("GOW_GS_FINISH_ASINCRONO"); return v && v[0] == '1'; }();
    return on;
}

void GSThreadedBackend::Sync(GSSyncReason reason)
{
    if (reason == GSSyncReason::Finish && gowFinishAsync())
    {
        Enqueue(Op::Sync, &reason, sizeof(reason));
        return;
    }
    if (reason == GSSyncReason::Presentation && GSSharedPresent::Active())
        return;
    if (reason == GSSyncReason::Presentation && gowGsPresentMailboxActive())
    {
        Enqueue(Op::Sync, &reason, sizeof(reason)); // en orden antes del Present encolado, sin esperar
        return;
    }
    // GOW-Port: FINISH solo se publica cuando terminaron los comandos anteriores.
    RunOnWorker([&] { m_inner->Sync(reason); });
}

PresentationFrame GSThreadedBackend::Present(const GSPresentationRequest &request)
{
    if (GSSharedPresent::Active())
    {
        Enqueue(Op::Present, &request, sizeof(request));
        std::lock_guard<std::mutex> lock(m_producerMutex);
        PublishLocked();
        return {};
    }
    if (gowGsPresentMailboxActive())
    {
        Enqueue(Op::Present, &request, sizeof(request));
        {
            std::lock_guard<std::mutex> lock(m_producerMutex);
            PublishLocked();
        }
        std::lock_guard<std::mutex> lock(g_mailboxMutex);
        if (g_mailboxDelivered != 0u && g_mailboxDelivered == g_mailboxSequence)
            return {}; // el mismo cuadro: el frontend conserva el que ya tiene (gowGsPresentMailboxDelivered)
        g_mailboxDelivered = g_mailboxSequence;
        return g_mailboxFrame; // copia: el último cuadro sigue disponible para el siguiente VSync
    }
    PresentationFrame frame;
    RunOnWorker([&] { frame = m_inner->Present(request); });
    return frame;
}

bool GSThreadedBackend::ClearFramebuffer(const GSContext &context, uint32_t rgba)
{
    bool result = false;
    RunOnWorker([&] { result = m_inner->ClearFramebuffer(context, rgba); });
    return result;
}

uint32_t GSThreadedBackend::ConsumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes)
{
    uint32_t result = 0u;
    RunOnWorker([&] { result = m_inner->ConsumeLocalToHostBytes(dst, maxBytes); });
    return result;
}

uint32_t GSThreadedBackend::ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
{
    uint32_t result = 0u;
    RunOnWorker([&] { result = m_inner->ReadVram(psm, base, bw, x, y); });
    return result;
}

void GSThreadedBackend::WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value)
{
    const WriteVramArgs args{psm, base, bw, x, y, value};
    Enqueue(Op::WriteVram, &args, sizeof(args));
}

void GSThreadedBackend::SnapshotVram(std::vector<uint8_t> &out) const
{
    RunOnWorker([&] { m_inner->SnapshotVram(out); });
}

GSTransferSnapshot GSThreadedBackend::GetTransferSnapshot() const
{
    GSTransferSnapshot result;
    RunOnWorker([&] { result = m_inner->GetTransferSnapshot(); });
    return result;
}

bool GSThreadedBackend::ExportState(GSBackendState &out)
{
    bool result = false;
    RunOnWorker([&]
                {
        auto *access = dynamic_cast<GSBackendStateAccess *>(m_inner.get());
        result = access && access->ExportState(out); });
    return result;
}

bool GSThreadedBackend::ImportState(const GSBackendState &state)
{
    bool result = false;
    RunOnWorker([&]
                {
        auto *access = dynamic_cast<GSBackendStateAccess *>(m_inner.get());
        result = access && access->ImportState(state); });
    return result;
}
