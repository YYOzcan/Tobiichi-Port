// GOW-Port: memoria real y fences simulados, sin driver ni assets del juego.
#include "MiniTest.h"
#include "gs/gs_gpu_upload_ring.h"

#include <algorithm>
#include <array>
#include <limits>
#include <set>
#include <vector>

namespace
{
    using GSGpuUpload::Failure;
    using GSGpuUpload::WaitResult;
    using TestRing = GSGpuUpload::Ring<uint32_t, 64u, 4u, 16u>;

    struct Fixture
    {
        std::array<uint8_t, 256u> bytes{};
        TestRing ring;
        uint32_t nextFence = 1u;
        bool nullFence = false;
        WaitResult outcome = WaitResult::Signaled;
        std::vector<uint32_t> waited, deleted;

        Fixture() { bytes.fill(0xa5u); ring.setStorage(bytes.data()); }
        size_t put(const void *data, size_t size)
        {
            return ring.put(data, size,
                            [&] { return nullFence ? 0u : nextFence++; },
                            [&](uint32_t fence) { waited.push_back(fence); return outcome; },
                            [&](uint32_t fence) { deleted.push_back(fence); });
        }
        void fill(TestCase &t)
        {
            for (uint8_t chunk = 0u; chunk < 4u; ++chunk)
            {
                std::array<uint8_t, 64u> data{};
                data.fill(static_cast<uint8_t>(0x10u + chunk));
                t.Equals(put(data.data(), data.size()), size_t{chunk} * 64u, "Llena cuatro chunks distintos");
            }
        }
        void release()
        {
            ring.releaseFences([&](uint32_t fence) { deleted.push_back(fence); });
        }
    };

    void failedReuse(TestCase &t, WaitResult outcome, Failure expected)
    {
        Fixture f;
        f.fill(t);
        const auto protectedBytes = f.bytes;
        f.outcome = outcome;
        const std::array<uint8_t, 7u> data = {1u, 2u, 3u, 4u, 5u, 6u, 7u};
        std::vector<uint8_t> fallback;
        unsigned fallbacks = 0u;
        auto upload = [&]
        {
            const size_t offset = f.put(data.data(), data.size());
            if (offset == SIZE_MAX)
            {
                ++fallbacks;
                fallback.assign(data.begin(), data.end());
            }
            return offset;
        };
        t.Equals(upload(), SIZE_MAX, "No reutiliza un chunk cuya fence no se señaló");
        t.Equals(f.bytes, protectedBytes, "El primer fallo no altera uploads pendientes");
        t.IsTrue(f.ring.disabled(), "La ruta persistente queda deshabilitada");
        t.IsFalse(f.ring.available(), "available también impide reusar el ring");
        t.Equals(f.ring.failure(), expected, "Conserva el motivo de sincronización");
        t.Equals(upload(), SIZE_MAX, "El segundo upload también usa fallback");
        t.Equals(f.bytes, protectedBytes, "No escribe en el cursor del fallo anterior");
        t.Equals(fallbacks, 2u, "Ambos uploads llegan al fallback");
        t.Equals(fallback, std::vector<uint8_t>(data.begin(), data.end()), "El fallback conserva el payload");
        t.Equals(f.waited, std::vector<uint32_t>({1u}), "No vuelve a esperar tras deshabilitarse");
        t.IsTrue(f.deleted.empty(), "Retiene la fence pendiente y la recién creada");
        t.Equals(f.nextFence, 5u, "No crea una nueva fence en el segundo intento");
        f.release();
        t.Equals(f.deleted, std::vector<uint32_t>({1u, 2u, 3u, 4u}), "El cierre libera todos los handles retenidos");
        f.release();
        t.Equals(f.deleted.size(), size_t{4}, "El segundo cierre no duplica eliminaciones");
    }
}

void runGpuUploadRingTests()
{
    MiniTest::Case("GS uploads persistentes protegidos", [](TestCase &tc)
    {
        tc.Run("Timeout conserva memoria pendiente y usa fallback para uploads posteriores", [](TestCase &t)
        {
            failedReuse(t, WaitResult::Timeout, Failure::Timeout);
        });
        tc.Run("WaitFailed conserva memoria pendiente y usa fallback para uploads posteriores", [](TestCase &t)
        {
            failedReuse(t, WaitResult::Failed, Failure::WaitFailed);
        });
        tc.Run("Fence señalada permite reciclar solo el chunk confirmado", [](TestCase &t)
        {
            Fixture f;
            f.fill(t);
            const auto before = f.bytes;
            std::array<uint8_t, 64u> data{};
            data.fill(0x7bu);
            t.Equals(f.put(data.data(), data.size()), size_t{0}, "Vuelve al primer chunk");
            t.IsTrue(std::equal(data.begin(), data.end(), f.bytes.begin()), "Copia el payload tras la confirmación");
            t.IsTrue(std::equal(before.begin() + 64u, before.end(), f.bytes.begin() + 64u), "Los otros tres chunks no cambian");
            t.Equals(f.waited, std::vector<uint32_t>({1u}), "Espera la fence del destino");
            t.Equals(f.deleted, std::vector<uint32_t>({1u}), "Libera solo la fence señalada");
            t.IsTrue(f.ring.available(), "El éxito conserva el ring disponible");
            t.Equals(f.ring.failure(), Failure::None, "No registra un fallo");
        });
        tc.Run("Fence señalada después de esperar protege memoria hasta el callback", [](TestCase &t)
        {
            Fixture f;
            f.fill(t);
            const auto before = f.bytes;
            std::array<uint8_t, 64u> data{};
            data.fill(0xebu);
            unsigned simulatedPolls = 0u;
            bool completed = false;
            const size_t offset = f.ring.put(data.data(), data.size(),
                [&] { return f.nextFence++; },
                [&](uint32_t fence)
                {
                    t.Equals(fence, 1u, "Espera el chunk correcto");
                    // GOW-Port: modelar la espera acotada del driver sin dormir la suite.
                    for (; simulatedPolls < 3u; ++simulatedPolls)
                        t.Equals(f.bytes, before, "No copia mientras la fence sigue pendiente");
                    completed = true;
                    return WaitResult::Signaled;
                },
                [&](uint32_t fence)
                {
                    t.IsTrue(completed, "Solo elimina la fence después de la señal");
                    t.Equals(f.bytes, before, "La copia tampoco precede a la eliminación");
                    f.deleted.push_back(fence);
                });
            t.Equals(simulatedPolls, 3u, "Se modeló la señal tardía");
            t.Equals(offset, size_t{0}, "Acepta la confirmación después de esperar");
            t.IsTrue(std::equal(data.begin(), data.end(), f.bytes.begin()), "Finalmente escribe el payload");
            t.IsTrue(f.ring.available(), "La espera correcta no deshabilita el ring");
        });
        tc.Run("Fence nula deshabilita sin copiar ni tocar uploads previos", [](TestCase &t)
        {
            Fixture f;
            std::array<uint8_t, 64u> data{};
            data.fill(0x27u);
            t.Equals(f.put(data.data(), data.size()), size_t{0}, "Primer chunk sin fence");
            const auto before = f.bytes;
            f.nullFence = true;
            t.Equals(f.put(data.data(), 1u), SIZE_MAX, "No avanza sin fence de protección");
            t.Equals(f.ring.failure(), Failure::NullFence, "Registra la creación fallida");
            t.IsTrue(f.ring.disabled(), "Queda deshabilitado");
            t.Equals(f.bytes, before, "No copia tras la creación fallida");
            t.Equals(f.put(data.data(), 1u), SIZE_MAX, "El siguiente upload también falla");
            t.Equals(f.bytes, before, "El segundo intento conserva todos los bytes");
            t.IsTrue(f.waited.empty(), "No espera una fence inexistente");
            f.release(); f.release();
            t.IsTrue(f.deleted.empty(), "No intenta eliminar handles nulos");
        });
        tc.Run("Cierre elimina una sola vez los handles que quedan", [](TestCase &t)
        {
            Fixture f;
            f.fill(t);
            std::array<uint8_t, 64u> data{};
            t.Equals(f.put(data.data(), data.size()), size_t{0}, "Recicla un chunk antes del cierre");
            f.release(); f.release();
            t.Equals(f.deleted, std::vector<uint32_t>({1u, 2u, 3u, 4u}), "Una eliminación por fence creada");
            t.Equals(std::set<uint32_t>(f.deleted.begin(), f.deleted.end()).size(), size_t{4}, "No elimina dos veces un handle reciclado");
        });
        tc.Run("Padding mínimo y alineación no escriben en huecos ni fuera del ring", [](TestCase &t)
        {
            std::array<uint8_t, 272u> guarded{};
            guarded.fill(0xa5u);
            GSGpuUpload::Ring<uint32_t, 64u, 4u, 32u> ring;
            ring.setStorage(guarded.data() + 8u);
            const std::array<uint8_t, 17u> first = {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u};
            const uint8_t one = 0x7du;
            uint32_t nextFence = 0u;
            auto put = [&](const void *data, size_t size)
            {
                return ring.put(data, size, [&] { return ++nextFence; },
                                [](uint32_t) { return WaitResult::Signaled; }, [](uint32_t) {});
            };
            t.Equals(put(first.data(), first.size()), size_t{0}, "Primer payload en offset cero");
            t.Equals(put(&one, 1u), size_t{32}, "Alinea la siguiente reserva a 32 bytes");
            t.Equals(put(first.data(), first.size()), size_t{64}, "Mueve el payload que no cabe al chunk siguiente");
            t.IsTrue(std::equal(first.begin(), first.end(), guarded.begin() + 8u), "Payload inicial intacto");
            for (size_t i = 17u; i < 32u; ++i)
                t.Equals(guarded[8u + i], uint8_t{0xa5u}, "No rellena el hueco de alineación");
            t.Equals(guarded[8u + 32u], one, "Copia el byte útil");
            for (size_t i = 33u; i < 48u; ++i)
                t.Equals(guarded[8u + i], uint8_t{0u}, "Completa la reserva mínima de 16 bytes con ceros");
            for (size_t i = 48u; i < 64u; ++i)
                t.Equals(guarded[8u + i], uint8_t{0xa5u}, "No sobrescribe el final del chunk previo");
            for (size_t i = 0u; i < 8u; ++i)
            {
                t.Equals(guarded[i], uint8_t{0xa5u}, "Guardia inicial intacta");
                t.Equals(guarded[264u + i], uint8_t{0xa5u}, "Guardia final intacta");
            }
        });
        tc.Run("Sin storage y payload sobredimensionado no copian ni crean fences", [](TestCase &t)
        {
            TestRing ring;
            std::array<uint8_t, 256u> storage{};
            storage.fill(0xa5u);
            const auto before = storage;
            const uint8_t data = 1u;
            unsigned callbacks = 0u;
            auto put = [&](size_t size)
            {
                return ring.put(&data, size, [&] { ++callbacks; return 1u; },
                                [&](uint32_t) { ++callbacks; return WaitResult::Signaled; },
                                [&](uint32_t) { ++callbacks; });
            };
            t.IsFalse(ring.available(), "Sin mapping no hay ring disponible");
            t.Equals(put(1u), SIZE_MAX, "Usa fallback antes de mapear");
            ring.setStorage(storage.data());
            t.Equals(put(65u), SIZE_MAX, "No acepta un upload mayor que un chunk");
            t.Equals(put((std::numeric_limits<size_t>::max)()), SIZE_MAX, "No desborda al calcular el tamaño");
            t.Equals(storage, before, "Los rechazos conservan toda la memoria");
            t.Equals(callbacks, 0u, "Los rechazos no consultan sincronización");
            t.IsTrue(ring.available(), "Un payload grande no deshabilita el ring");
            t.Equals(put(1u), size_t{0}, "Los rechazos no avanzaron el cursor");
        });
        tc.Run("Fuente nula reserva sin escribir y tamaño cero usa el mínimo", [](TestCase &t)
        {
            Fixture f;
            const auto before = f.bytes;
            t.Equals(f.put(nullptr, 0u), size_t{0}, "Reserva vacía de 16 bytes");
            t.Equals(f.bytes, before, "La fuente nula conserva los bytes reservados");
            const uint8_t data = 0x55u;
            t.Equals(f.put(&data, 0u), size_t{16}, "La siguiente reserva empieza tras el mínimo");
            for (size_t i = 16u; i < 32u; ++i)
                t.Equals(f.bytes[i], uint8_t{0u}, "Fuente válida y payload cero inicializan el padding");
        });
        tc.Run("Un payload que termina justo en el chunk no crea fence antes de tiempo", [](TestCase &t)
        {
            Fixture f;
            std::array<uint8_t, 48u> data{};
            t.Equals(f.put(data.data(), 15u), size_t{0}, "Mínimo de 16 bytes");
            t.Equals(f.put(data.data(), data.size()), size_t{16}, "Termina exactamente en el límite");
            t.Equals(f.nextFence, 1u, "No crea fence mientras el upload cabe");
            t.Equals(f.put(data.data(), 1u), size_t{64}, "El siguiente upload abre otro chunk");
            t.Equals(f.nextFence, 2u, "Protege el chunk cerrado con una fence");
            t.IsTrue(f.waited.empty(), "No espera un chunk todavía no usado");
        });
        tc.Run("Cambiar storage no rearma el ring tras un fallo", [](TestCase &t)
        {
            Fixture f;
            f.fill(t);
            f.outcome = WaitResult::Timeout;
            const uint8_t data = 0x66u;
            t.Equals(f.put(&data, 1u), SIZE_MAX, "Provoca el fallo de sincronización");
            std::array<uint8_t, 256u> replacement{};
            replacement.fill(0x37u);
            const auto before = replacement;
            f.ring.setStorage(nullptr); f.ring.setStorage(replacement.data());
            t.Equals(f.put(&data, 1u), SIZE_MAX, "El fallo permanece al reasignar storage");
            t.Equals(replacement, before, "No escribe en un mapping reasignado");
            t.Equals(f.ring.failure(), Failure::Timeout, "Mantiene el motivo original");
        });
        tc.Run("Handles de tipo puntero siguen el mismo ciclo de propiedad", [](TestCase &t)
        {
            std::array<uint8_t, 128u> storage{};
            std::array<uint8_t, 64u> data{};
            std::array<uint8_t, 2u> handles{};
            GSGpuUpload::Ring<const uint8_t *, 64u, 2u, 16u> ring;
            ring.setStorage(storage.data());
            size_t created = 0u;
            std::vector<const uint8_t *> waited, deleted;
            auto put = [&]
            {
                return ring.put(data.data(), data.size(),
                                [&]() -> const uint8_t * { return &handles[created++]; },
                                [&](const uint8_t *fence) { waited.push_back(fence); return WaitResult::Signaled; },
                                [&](const uint8_t *fence) { deleted.push_back(fence); });
            };
            t.Equals(put(), size_t{0}, "Primer upload con handles puntero");
            t.Equals(put(), size_t{64}, "Segundo chunk con fence puntero");
            t.Equals(put(), size_t{0}, "Espera antes de volver al primer chunk");
            t.Equals(waited, std::vector<const uint8_t *>({&handles[0]}), "Consulta la fence correcta");
            ring.releaseFences([&](const uint8_t *fence) { deleted.push_back(fence); });
            ring.releaseFences([&](const uint8_t *fence) { deleted.push_back(fence); });
            t.Equals(deleted, std::vector<const uint8_t *>({&handles[0], &handles[1]}), "Libera cada puntero una vez");
        });
    });
}
