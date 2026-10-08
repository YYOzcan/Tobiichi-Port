#ifndef PS2_PERF_H
#define PS2_PERF_H

// GOW-Port: perfil opcional de tiempo transcurrido exclusivo, separado por hilo.
// Los tiempos incluyen esperas del sistema; no representan muestras de uso de CPU.
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

namespace ps2_perf
{
    enum class Bucket : size_t { Ee, Vu, Gs, Iop, GuestWait, Upload, HostWait, Count, None = Count };
    constexpr size_t bucketCount = static_cast<size_t>(Bucket::Count);

    // Contabilidad con reloj inyectable para comprobar el anidamiento sin sleeps.
    struct Accounting
    {
        Bucket active = Bucket::None;
        uint64_t since = 0;

        struct Charge { Bucket bucket; uint64_t nanos; };
        Charge switchTo(Bucket next, uint64_t now)
        {
            const Charge charge{active, now >= since ? now - since : 0u};
            active = next;
            since = now;
            return charge;
        }
    };

    inline bool enabled()
    {
        static const bool on = [] {
            const char *value = std::getenv("GOW_PERF_DIAG");
            return value && std::strcmp(value, "1") == 0;
        }();
        return on;
    }
    inline bool countFrames()
    {
        static const bool on = [] {
            const char *value = std::getenv("GOW_PERF_DIAG");
            return value && (std::strcmp(value, "1") == 0 || std::strcmp(value, "frames") == 0);
        }();
        return on;
    }
    inline std::array<std::atomic<uint64_t>, bucketCount> nanos{};
    inline std::atomic<uint64_t> guestFlips{0}, hostFrames{0};
    inline thread_local Accounting accounting;
    inline uint64_t nowNanos()
    {
        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
    }
    inline void switchTo(Bucket next)
    {
        const auto charge = accounting.switchTo(next, nowNanos());
        if (charge.bucket != Bucket::None)
            nanos[static_cast<size_t>(charge.bucket)].fetch_add(charge.nanos, std::memory_order_relaxed);
    }
    class Scope
    {
        bool on;
        Bucket previous = Bucket::None;
    public:
        explicit Scope(Bucket bucket) : on(enabled())
        {
            if (on) { previous = accounting.active; switchTo(bucket); }
        }
        ~Scope() { if (on) switchTo(previous); }
        Scope(const Scope &) = delete;
        Scope &operator=(const Scope &) = delete;
    };
    inline void guestEntry(uint32_t pc)
    {
        if (!countFrames()) return;
        static const uint32_t framePc = [] {
            const char *value = std::getenv("GOW_PERF_FRAME_PC");
            return value ? static_cast<uint32_t>(std::strtoul(value, nullptr, 0)) : 0u;
        }();
        // Solo entradas a la funciÃ³n elegida: las reanudaciones no cuentan como cuadros nuevos.
        if (framePc != 0u && pc == framePc) guestFlips.fetch_add(1, std::memory_order_relaxed);
    }
    inline void report()
    {
        if (!countFrames()) return;
        // Se llama Ãºnicamente desde el hilo de presentaciÃ³n. No lee RAM del juego.
        const uint64_t now = nowNanos();
        static uint64_t first = now, last = now;
        static std::array<uint64_t, bucketCount> before{};
        static uint64_t previousFlips = 0, previousFrames = 0;
        if (now - last < 5000000000ull) return;
        const double seconds = static_cast<double>(now - last) * 1e-9;
        std::array<double, bucketCount> ms{};
        for (size_t i = 0; i < bucketCount; ++i)
        {
            const uint64_t total = nanos[i].load(std::memory_order_relaxed);
            ms[i] = static_cast<double>(total - before[i]) * 1e-6;
            before[i] = total;
        }
        const uint64_t flips = guestFlips.load(std::memory_order_relaxed);
        const uint64_t frames = hostFrames.load(std::memory_order_relaxed);
        std::fprintf(stderr, "[gow-perf] t=%.2f window=%.2f ee_ms=%.2f vu_ms=%.2f gs_ms=%.2f iop_ms=%.2f guest_wait_ms=%.2f upload_ms=%.2f host_wait_ms=%.2f guest_flip_hz=%.2f host_hz=%.2f\n",
            (now - first) * 1e-9, seconds, ms[0], ms[1], ms[2], ms[3], ms[4], ms[5], ms[6],
            (flips - previousFlips) / seconds, (frames - previousFrames) / seconds);
        previousFlips = flips; previousFrames = frames; last = now;
    }
}
#endif
