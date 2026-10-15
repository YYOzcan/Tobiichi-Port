// GOW-Port: frontend y cola reales; backend procedural detenido sin sleeps ni assets.
#include "MiniTest.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_shared_present.h"
#include "runtime/gs/gs_swizzle.h"
#include "runtime/ps2_memory.h"

#include <chrono>
#include <condition_variable>
#include <cstring>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace
{
    enum Event { Draw = 1, Present = 2, Read = 3, Finish = 4, Capture = 5, Flush = 6 };
    struct Recording
    {
        std::mutex mutex;
        std::condition_variable cv;
        bool holdDraw = false;
        bool drawEntered = false;
        bool drawReleased = false;
        bool hostReturned = false;
        std::vector<int> events;
        std::vector<GSPresentationRequest> requests;
        uint32_t drawCount = 0u;
        uint32_t finishCount = 0u;
        uint32_t captures = 0u;
        std::thread::id owner;
        std::thread::id captureOwner;

        template<class Predicate>
        bool wait(Predicate predicate)
        {
            std::unique_lock<std::mutex> lock(mutex);
            // GOW-Port: limite anti-deadlock del control negativo, no una espera para medir asincronia.
            return cv.wait_for(lock, std::chrono::seconds(5), predicate);
        }
        void release()
        {
            { std::lock_guard<std::mutex> lock(mutex); drawReleased = true; }
            cv.notify_all();
        }
    };

    class ProceduralBackend final : public GSRasterBackend
    {
        Recording &r;
        bool shared;
    public:
        ProceduralBackend(Recording &recording, bool isShared) : r(recording), shared(isShared) {}
        bool UsesSharedPresentation() const override { return shared; }
        void Initialize(uint8_t *, uint32_t) override { r.owner = std::this_thread::get_id(); }
        void Reset() override {}
        void Submit(const GSPrimitiveBatch &) override
        {
            std::unique_lock<std::mutex> lock(r.mutex);
            if (r.holdDraw)
            {
                r.drawEntered = true;
                r.cv.notify_all();
                r.cv.wait(lock, [&] { return r.drawReleased; });
            }
            ++r.drawCount;
            r.events.push_back(Draw);
        }
        void LoadClut(const GSTex0Reg &, const GSTexClutReg &) override {}
        void BeginTransfer(const GSTransferCommand &) override {}
        void UploadImage(const uint8_t *, uint32_t) override {}
        void Flush() override { std::lock_guard<std::mutex> lock(r.mutex); r.events.push_back(::Flush); }
        void TextureFlush() override {}
        void Sync(GSSyncReason reason) override
        {
            if (reason == GSSyncReason::Finish)
            {
                std::lock_guard<std::mutex> lock(r.mutex);
                ++r.finishCount;
                r.events.push_back(Finish);
            }
        }
        PresentationFrame Present(const GSPresentationRequest &request) override
        {
            std::lock_guard<std::mutex> lock(r.mutex);
            r.requests.push_back(request);
            if (request.forceReadback)
            {
                r.events.push_back(Capture);
                ++r.captures;
                r.captureOwner = std::this_thread::get_id();
            }
            else r.events.push_back(::Present);
            if ((shared && !request.forceReadback) || (request.pmode & 3u) == 0u)
                return {};
            PresentationFrame frame;
            frame.width = 64u;
            frame.height = 2u;
            frame.displayFbp = static_cast<uint32_t>(request.dispfb1 & 0x1ffu);
            frame.usedPreferred = request.hasPreferredSource;
            frame.sourceFbp = request.hasPreferredSource ? request.preferredSource.fbp : frame.displayFbp;
            frame.pixels.resize(640u * frame.height * 4u, 0xeeu);
            const uint32_t color = 0x80302000u | (frame.displayFbp & 0xffu);
            for (uint32_t y = 0u; y < frame.height; ++y)
                for (uint32_t x = 0u; x < frame.width; ++x)
                {
                    const uint32_t value = color + (y << 8u) + x;
                    std::memcpy(frame.pixels.data() + (y * 640u + x) * 4u, &value, 4u);
                }
            return frame;
        }
        bool ClearFramebuffer(const GSContext &, uint32_t) override { return false; }
        uint32_t ConsumeLocalToHostBytes(uint8_t *, uint32_t) override { return 0u; }
        uint32_t ReadVram(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) const override
        {
            std::lock_guard<std::mutex> lock(r.mutex);
            r.events.push_back(Read);
            return (r.finishCount << 16u) | r.drawCount;
        }
        void WriteVram(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) override {}
        void SnapshotVram(std::vector<uint8_t> &out) const override { out.clear(); }
        GSTransferSnapshot GetTransferSnapshot() const override { return {}; }
    };

    struct Fixture
    {
        Recording recording;
        std::vector<uint8_t> vram = std::vector<uint8_t>(GSSwizzle::kMemorySize);
        GSRegisters registers{};
        GS gs;
        GSThreadedBackend *threaded = nullptr;
        explicit Fixture(bool shared = true)
        {
            registers.pmode = 1u;
            registers.dispfb1 = 12u;
            registers.vsyncTick.store(31u);
            gs.init(vram.data(), static_cast<uint32_t>(vram.size()), &registers);
            auto backend = std::make_unique<GSThreadedBackend>(std::make_unique<ProceduralBackend>(recording, shared));
            threaded = backend.get();
            gs.setRasterBackend(std::move(backend));
            recording.events.clear();
        }
        ~Fixture() { recording.release(); }
        void point()
        {
            gs.writeRegister(GS_REG_PRIM, GS_PRIM_POINT);
            gs.writeRegister(GS_REG_RGBAQ, 0x3f80000080403020ull);
            gs.writeRegister(GS_REG_XYZ2, 0x00100010u);
        }
    };
}

void runGsSharedQueueTests()
{
    MiniTest::Case("GS shared presentation queue", [](TestCase &t)
    {
        t.Run("shared frontend returns before held draw and preserves FIFO requests", [](TestCase &t)
        {
            Fixture f;
            f.recording.holdDraw = true;
            f.point();
            std::thread host([&]
            {
                f.gs.latchHostPresentationFrame();
                { std::lock_guard<std::mutex> lock(f.recording.mutex); f.recording.hostReturned = true; }
                f.recording.cv.notify_all();
            });
            const bool entered = f.recording.wait([&] { return f.recording.drawEntered; });
            const bool returnedWhileHeld = f.recording.wait([&] { return f.recording.hostReturned; });
            if (returnedWhileHeld)
            {
                f.registers.dispfb1 = 19u;
                f.registers.vsyncTick.store(32u);
                f.gs.latchHostPresentationFrame();
            }
            f.recording.release();
            host.join();
            f.threaded->ReadVram(0u, 0u, 1u, 0u, 0u);
            t.IsTrue(entered, "El worker se detuvo dentro del dibujo real encolado por GS");
            t.IsTrue(returnedWhileHeld, "El latch retorna sin liberar al worker");
            t.IsTrue(f.recording.events == std::vector<int>({Draw, Present, Present, Read}),
                     "Draw y requests anteriores conservan FIFO sin Flush del host");
            t.Equals(f.recording.captures, 0u, "Presentacion normal no descarga pixeles");
            t.Equals(f.recording.requests.size(), size_t(2u), "Ambas presentaciones llegaron al worker");
            if (f.recording.requests.size() == 2u)
            {
                t.Equals(f.recording.requests[0].dispfb1, 12ull, "Primer request copiado al encolar");
                t.Equals(f.recording.requests[0].vsyncTick, 31ull, "Primer tick no recibe el posterior");
                t.Equals(f.recording.requests[1].dispfb1, 19ull, "Segundo CRTC mantiene su orden");
                t.Equals(f.recording.requests[1].vsyncTick, 32ull, "Segundo tick pertenece a su request");
            }
        });

        t.Run("shared diagnostics read on worker with latched CRTC and cache generation", [](TestCase &t)
        {
            Fixture f;
            std::vector<uint8_t> pixels;
            uint32_t width = 0u, height = 0u, display = 0u, source = 0u;
            bool preferred = true;
            t.IsFalse(f.gs.copyLatchedHostPresentationFrame(pixels, width, height),
                      "Sin latch anterior no se inventa un request para capturar");
            t.Equals(f.recording.captures, 0u, "Sin latch no se consulta al worker");
            f.gs.latchHostPresentationFrame();
            f.registers.dispfb1 = 25u;
            f.registers.vsyncTick.store(41u);
            t.IsTrue(f.gs.copyLatchedHostPresentationFrame(pixels, width, height, &display, &source, &preferred),
                     "La captura explicita conserva la API de copia en modo shared");
            t.Equals(width, 64u, "Ancho del compositor capturado");
            t.Equals(height, 2u, "Alto del compositor capturado");
            t.Equals(display, 12u, "La captura usa el CRTC latched, no los registros posteriores");
            t.Equals(source, 12u, "Fuente devuelta por el compositor");
            t.IsFalse(preferred, "No se inventa preferredSource");
            t.Equals(pixels.size(), size_t(64u * 2u * 4u), "Filas de 640 compactadas sin padding");
            if (pixels.size() == 64u * 2u * 4u)
            {
                uint32_t first = 0u, secondRow = 0u;
                std::memcpy(&first, pixels.data(), 4u);
                std::memcpy(&secondRow, pixels.data() + 64u * 4u, 4u);
                t.Equals(first, 0x8030200cu, "Contenido real de la captura");
                t.Equals(secondRow, 0x8030210cu, "La segunda fila no toma el padding");
            }
            t.IsTrue(f.recording.captureOwner == f.recording.owner, "Lectura en el mismo hilo propietario");
            t.IsFalse(f.recording.captureOwner == std::this_thread::get_id(), "Nunca descarga desde EE/host");
            t.Equals(f.recording.captures, 1u, "Una descarga explicita");
            f.gs.copyLatchedHostPresentationFrame(pixels, width, height);
            t.Equals(f.recording.captures, 1u, "Repetir la copia no repite el readback del mismo latch");
            f.gs.latchHostPresentationFrame();
            f.gs.copyLatchedHostPresentationFrame(pixels, width, height, &display);
            t.Equals(f.recording.captures, 2u, "Un nuevo latch invalida la captura anterior");
            t.Equals(display, 25u, "La nueva captura incorpora el CRTC del nuevo latch");
            f.registers.pmode = 0u;
            f.gs.latchHostPresentationFrame();
            t.IsFalse(f.gs.copyLatchedHostPresentationFrame(pixels, width, height, &display, &source, &preferred),
                      "PMODE deshabilitado no conserva una captura vieja");
            t.IsTrue(pixels.empty() && width == 0u && height == 0u && display == 0u && source == 0u && !preferred,
                     "La captura vacia limpia todos sus outputs");
        });

        t.Run("shared FINISH and reads retain barriers after held draws", [](TestCase &t)
        {
            Fixture f;
            f.recording.holdDraw = true;
            f.point();
            // GOW-Port: también el control negativo de Flush debe cerrar sin deadlock.
            std::thread presenter([&]
            {
                f.gs.latchHostPresentationFrame();
                { std::lock_guard<std::mutex> lock(f.recording.mutex); f.recording.hostReturned = true; }
                f.recording.cv.notify_all();
            });
            const bool latched = f.recording.wait([&] { return f.recording.hostReturned; });
            if (!latched)
            {
                f.recording.release();
                presenter.join();
                t.Fail("El latch bloqueó antes del control de FINISH");
                return;
            }
            presenter.join();
            { std::lock_guard<std::mutex> lock(f.recording.mutex); f.recording.hostReturned = false; }
            const bool entered = f.recording.wait([&] { return f.recording.drawEntered; });
            uint32_t result = 0u;
            uint32_t observedAfterFinish = 0u;
            std::thread reader([&]
            {
                f.threaded->Sync(GSSyncReason::Finish);
                {
                    std::lock_guard<std::mutex> lock(f.recording.mutex);
                    observedAfterFinish = (f.recording.finishCount << 16u) | f.recording.drawCount;
                    f.recording.hostReturned = true;
                }
                f.recording.cv.notify_all();
                result = f.gs.ReadVram(0u, 0u, 1u, 0u, 0u);
            });
            // GOW-Port: si FINISH retorna antes de soltar el draw, el estado observado sera cero.
            // En la ruta correcta el limite del control libera el worker para que la prueba cierre.
            const bool returnedWhileHeld = f.recording.wait([&] { return f.recording.hostReturned; });
            f.recording.release();
            reader.join();
            t.IsTrue(entered, "El dibujo anterior estaba detenido");
            t.IsFalse(returnedWhileHeld, "FINISH no retorna con el dibujo anterior detenido");
            t.Equals(observedAfterFinish, 0x00010001u, "Al retornar FINISH sus efectos ya son visibles");
            t.Equals(result, 0x00010001u, "Lectura solo retorna despues del dibujo y FINISH");
            t.IsTrue(f.recording.events == std::vector<int>({Draw, Present, Finish, Read}),
                     "FINISH conserva la barrera y orden en la misma cola compartida");
        });

        t.Run("nonshared frontend retains synchronous pixel path", [](TestCase &t)
        {
            Fixture f(false);
            f.point();
            f.gs.latchHostPresentationFrame();
            std::vector<uint8_t> pixels;
            uint32_t width = 0u, height = 0u, display = 0u;
            t.IsFalse(f.gs.usesSharedPresentation(), "La instancia CPU no toma sharing de otro backend");
            t.IsTrue(f.gs.copyLatchedHostPresentationFrame(pixels, width, height, &display),
                     "El latch sin sharing conserva pixeles disponibles al retornar");
            t.Equals(display, 12u, "Metadata normal del backend");
            t.Equals(f.recording.captures, 0u, "No fuerza otra presentacion para copiar pixeles CPU");
            t.IsTrue(f.recording.events == std::vector<int>({Draw, Flush, Present}),
                     "CPU conserva Flush y composicion sincrona");
        });

        t.Run("shared acquired metadata belongs to displayed frame not next request", [](TestCase &t)
        {
            Fixture f;
            f.gs.setDebugHistoryPaused(false);
            f.gs.latchHostPresentationFrame();
            GSSharedPresent::Frame shared;
            shared.sequence = 8u;
            shared.vsyncTick = 28u;
            shared.width = 64u;
            shared.height = 96u;
            shared.displayFbp = 17u;
            shared.sourceFbp = 29u;
            shared.usedPreferred = true;
            f.gs.recordAcquiredSharedFrame(shared);
            f.registers.dispfb1 = 31u;
            f.gs.latchHostPresentationFrame();
            f.gs.recordAcquiredSharedFrame(shared);
            const auto snapshot = f.gs.getDebugSnapshot();
            t.Equals(snapshot.hostPresentationDisplayFbp, 17u, "Se muestran metadatos del frame retenido");
            t.Equals(snapshot.hostPresentationSourceFbp, 29u, "Fuente correcta del compositor adquirido");
            t.IsTrue(snapshot.hostPresentationUsedPreferred, "Preferred del frame adquirido");
            t.IsTrue(snapshot.hasHostPresentationFrame, "Shared tiene frame aunque no haya pixeles RAM");
            const auto history = f.gs.getDebugHistory();
            uint32_t presents = 0u;
            for (const auto &event : history)
                if (event.kind == GSDebugEventKind::Present)
                {
                    ++presents;
                    t.Equals(event.displayFbp, 17u, "Evento del frame adquirido");
                    t.Equals(event.sourceFbp, 29u, "Evento conserva fuente adquirida");
                    t.Equals(event.vsyncTick, 28ull, "Tick del frame adquirido, no del request posterior");
                }
            t.Equals(presents, 1u, "Repetir slot no duplica eventos de presentacion");
            shared.sequence = 9u;
            shared.blank = true;
            f.gs.recordAcquiredSharedFrame(shared);
            const auto blank = f.gs.getDebugSnapshot();
            t.IsFalse(blank.hasHostPresentationFrame, "Blank invalida estado de display previo");
            t.Equals(blank.hostPresentationWidth, 0u, "Blank equivale a frame RAM vacio");
            t.Equals(blank.hostPresentationDisplayFbp, 0u, "Blank limpia metadata previa");
        });
    });
}
