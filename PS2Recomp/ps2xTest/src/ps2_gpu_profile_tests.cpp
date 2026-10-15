// GOW-Port: timestamps simulados para probar el perfil sin juego ni driver.
#include "MiniTest.h"
#include "gs/gs_gpu_profile.h"

#include <set>
#include <vector>

namespace
{
    using GSGpuProfile::Queue;
    using GSGpuProfile::Window;

    void frames(Queue &queue, unsigned count = 4u)
    {
        for (unsigned i = 0u; i < count; ++i)
            queue.endFrame();
    }

    bool sample(Queue &queue, uint32_t kind, uint32_t begin, uint32_t end,
                std::array<uint32_t, 8> info = {})
    {
        if (!queue.sampleAllowed())
            return false;
        queue.pending.push_back({kind, begin, end, info});
        return true;
    }
}

void register_ps2_gpu_profile_tests()
{
    MiniTest::Case("GS GPU perfil diferido", [](TestCase &tc)
    {
        tc.Run("GPU ocupada no lee resultados ni recicla consultas", [](TestCase &t)
        {
            Queue q;
            sample(q, 0u, 1u, 2u);
            frames(q);
            unsigned probes = 0u, reads = 0u, reports = 0u;
            q.collect([&](uint32_t id)
                      {
                          ++probes;
                          t.Equals(id, 2u, "Solo consulta disponibilidad del último timestamp");
                          return false;
                      },
                      [&](uint32_t) { ++reads; t.Fail("Lectura prematura"); return uint64_t{0}; },
                      [&](const Window &) { ++reports; });
            t.Equals(probes, 1u, "Una consulta, sin bucle de espera");
            t.Equals(reads, 0u, "No lee QUERY_RESULT pendiente");
            t.Equals(reports, 0u, "No informa una ventana incompleta");
            t.Equals(q.waitingWindows(), size_t{1}, "Retiene la ventana");
            t.IsTrue(q.freeQueries.empty(), "No reutiliza handles pendientes");
        });

        tc.Run("Recoge ventanas listas en orden y una sola vez", [](TestCase &t)
        {
            Queue q;
            sample(q, 0u, 1u, 2u); q.prims = 11u; frames(q);
            sample(q, 2u, 3u, 4u); q.prims = 29u; frames(q);
            std::vector<Window> reports;
            std::vector<uint32_t> reads;
            bool secondReady = false;
            auto collect = [&]
            {
                q.collect([&](uint32_t id) { return id == 2u || secondReady; },
                          [&](uint32_t id)
                          {
                              t.IsTrue(id <= 2u || secondReady, "No lee la segunda ventana prematuramente");
                              reads.push_back(id);
                              const uint64_t values[] = {0u, 100u, 160u, 200u, 320u};
                              return values[id];
                          },
                          [&](const Window &w) { reports.push_back(w); });
            };
            collect();
            t.Equals(reports.size(), size_t{1}, "Solo recoge la primera ventana");
            t.Equals(q.waitingWindows(), size_t{1}, "Conserva la segunda");
            t.Equals(reads, std::vector<uint32_t>({1u, 2u}), "Lee una vez los timestamps listos");
            secondReady = true;
            collect(); collect();
            t.Equals(reports.size(), size_t{2}, "No duplica informes");
            t.Equals(reads, std::vector<uint32_t>({1u, 2u, 3u, 4u}), "Orden estable");
            if (reports.size() != 2u)
                return;
            t.Equals(reports[0].ns[0], uint64_t{60}, "Tiempo raster original");
            t.Equals(reports[1].ns[2], uint64_t{120}, "Tiempo upload original");
            t.Equals(reports[0].prims, uint64_t{11}, "Contadores de la primera ventana");
            t.Equals(reports[1].prims, uint64_t{29}, "Contadores de la segunda");
            t.Equals(reports[0].frames, uint64_t{4}, "Cuatro cuadros originales");
            t.Equals(reports[1].frames, uint64_t{4}, "Cuatro cuadros siguientes");
            t.Equals(q.freeQueries, std::vector<uint32_t>({1u, 2u, 3u, 4u}), "Recicla tras leer");
        });

        tc.Run("Preserva metadatos y contadores con sus timestamps", [](TestCase &t)
        {
            Queue q;
            const std::array<uint32_t, 8> info = {7u, 8u, 9u, 10u, 0xd0u, 2u, 0x120u, 0x4bu};
            sample(q, 0u, 1u, 2u, info); sample(q, 0u, 3u, 4u, info);
            q.prims = 14u; q.pairs = 18u; q.tiles = 16u;
            q.maxBin = 10u; q.sumMaxBin = 20u;
            q.reasons[3] = 2u; q.uploadHazards[1] = 3u;
            frames(q);
            t.Equals(q.prims, uint64_t{0}, "Reinicia contadores activos");
            t.Equals(q.reasons[3], uint64_t{0}, "Reinicia razones activas");
            q.prims = 999u; q.reasons[3] = 999u; q.uploadHazards[1] = 999u; q.nextInfo.fill(999u);
            unsigned reports = 0u;
            q.collect([](uint32_t) { return true; },
                      [](uint32_t id) { return uint64_t{id} * 50u; },
                      [&](const Window &w)
                      {
                          ++reports;
                          t.Equals(w.ns[0], uint64_t{100}, "Suma las dos muestras");
                          t.Equals(w.count[0], uint64_t{2}, "Cuenta las dos muestras");
                          t.Equals(w.prims, uint64_t{14}, "No mezcla primitivas nuevas");
                          t.Equals(w.pairs, uint64_t{18}, "Conserva pares");
                          t.Equals(w.tiles, uint64_t{16}, "Conserva tiles");
                          t.Equals(w.maxBin, uint64_t{10}, "Conserva máximo");
                          t.Equals(w.sumMaxBin, uint64_t{20}, "Conserva suma");
                          t.Equals(w.reasons[3], uint64_t{2}, "Conserva razones");
                          t.Equals(w.uploadHazards[1], uint64_t{3}, "Conserva hazards");
                          t.Equals(w.rasterTimes.size(), size_t{2}, "Retiene muestras raster");
                          for (const auto &entry : w.rasterTimes)
                          {
                              t.Equals(entry.first, uint64_t{50}, "Duración correcta");
                              t.Equals(entry.second, info, "FBP, PSM, ZBP y flags originales");
                          }
                      });
            t.Equals(reports, 1u, "Informa la ventana congelada");
            t.Equals(q.prims, uint64_t{999}, "No altera contadores nuevos al recoger");
        });

        tc.Run("Cola llena conserva cuadros sin esperar", [](TestCase &t)
        {
            Queue q;
            for (uint32_t i = 1u; i <= 3u; ++i)
            {
                sample(q, 0u, i * 2u - 1u, i * 2u); q.prims = i; frames(q);
            }
            sample(q, 0u, 7u, 8u); q.prims = 4u; frames(q);
            t.Equals(q.waitingWindows(), GSGpuProfile::kMaxWaitingWindows, "Cola limitada");
            t.Equals(q.frames, uint64_t{4}, "Conserva ventana activa");
            t.Equals(q.prims, uint64_t{4}, "Conserva contadores activos");
            std::vector<Window> reports;
            q.collect([](uint32_t) { return false; },
                      [&](uint32_t) { t.Fail("No espera con la cola llena"); return uint64_t{0}; },
                      [&](const Window &) { t.Fail("No informa resultados pendientes"); });
            auto collect = [&]
            {
                q.collect([](uint32_t) { return true; },
                          [](uint32_t id) { return uint64_t{id} * 10u; },
                          [&](const Window &w) { reports.push_back(w); });
            };
            collect(); q.endFrame(); collect();
            t.Equals(q.frames, uint64_t{0}, "Sella al liberarse espacio");
            t.Equals(reports.size(), size_t{4}, "No pierde ventanas");
            uint64_t totalFrames = 0u, totalPrims = 0u;
            for (const auto &w : reports)
            {
                totalFrames += w.frames; totalPrims += w.prims;
                t.Equals(w.ns[0], uint64_t{10}, "Cada ventana conserva su muestra");
            }
            t.Equals(totalFrames, uint64_t{17}, "Cuenta 17 cuadros reales");
            t.Equals(totalPrims, uint64_t{10}, "Cuenta 10 primitivas reales");
            if (reports.size() == 4u)
                t.Equals(reports[3].frames, uint64_t{5}, "Divisor real con contrapresión");
        });

        tc.Run("Limita consultas y marca omisiones sin perder contadores", [](TestCase &t)
        {
            Queue q;
            for (uint32_t i = 0u; i < GSGpuProfile::kMaxSamplesPerWindow + 3u; ++i)
            {
                sample(q, 0u, i * 2u + 1u, i * 2u + 2u); ++q.prims;
            }
            t.Equals(q.pending.size(), GSGpuProfile::kMaxSamplesPerWindow, "Máximo 4096 pares");
            frames(q);
            unsigned reports = 0u;
            q.collect([](uint32_t) { return true; },
                      [](uint32_t id) { return uint64_t{id} * 100u; },
                      [&](const Window &w)
                      {
                          ++reports;
                          t.Equals(w.skippedQueries, uint64_t{3}, "Perfil explícitamente parcial");
                          t.Equals(w.prims, uint64_t{4099}, "Conserva trabajo sin muestra");
                          t.Equals(w.count[0], uint64_t{4096}, "Cuenta muestras aceptadas");
                          t.Equals(w.ns[0], uint64_t{409600}, "Tiempo de muestras aceptadas");
                          t.Equals(w.rasterTimes.size(), size_t{4096}, "Memoria raster limitada");
                      });
            t.Equals(reports, 1u, "Informe parcial único");
            t.Equals(q.freeQueries.size(), size_t{8192}, "Recicla consultas aceptadas");
            const std::set<uint32_t> handles(q.freeQueries.begin(), q.freeQueries.end());
            t.Equals(handles.size(), size_t{8192}, "No recicla handles dos veces");
            t.IsTrue(q.sampleAllowed(), "Siguiente ventana vuelve a medir");
            t.Equals(q.skippedQueries, uint64_t{0}, "No arrastra omisiones");
        });

        tc.Run("Cierre recoge ventana corta y recicla todos los handles", [](TestCase &t)
        {
            Queue q;
            sample(q, 0u, 1u, 2u); frames(q);
            sample(q, 5u, 3u, 4u); frames(q, 2u);
            q.finish(); q.finish();
            unsigned probes = 0u;
            std::vector<Window> reports;
            q.collect([&](uint32_t) { ++probes; return false; },
                      [](uint32_t id) { return uint64_t{id} * 10u; },
                      [&](const Window &w) { reports.push_back(w); }, true);
            t.Equals(probes, 0u, "Solo el cierre permite lectura forzada");
            t.Equals(reports.size(), size_t{2}, "Cerrar dos veces no duplica");
            if (reports.size() == 2u)
            {
                t.Equals(reports[0].frames, uint64_t{4}, "Ventana completa");
                t.Equals(reports[1].frames, uint64_t{2}, "Divisor de ventana corta");
                t.Equals(reports[1].ns[5], uint64_t{10}, "Timestamp de presentación");
            }
            t.Equals(q.waitingWindows(), size_t{0}, "No quedan pendientes");
            t.Equals(q.freeQueries.size(), size_t{4}, "Handles listos para DeleteQueries");
        });

        tc.Run("Cierre vacío no inventa cuadros", [](TestCase &t)
        {
            Queue q;
            q.finish();
            q.collect([](uint32_t) { return true; },
                      [&](uint32_t) { t.Fail("No hay consultas"); return uint64_t{0}; },
                      [&](const Window &) { t.Fail("No hay ventanas"); }, true);
            t.Equals(q.waitingWindows(), size_t{0}, "Cola vacía");
            t.IsTrue(q.freeQueries.empty(), "No crea handles");
        });

        tc.Run("Ventana sin muestras conserva cuadros y contadores", [](TestCase &t)
        {
            Queue q;
            q.reasons[5] = 2u; frames(q);
            unsigned reports = 0u;
            q.collect([&](uint32_t) { t.Fail("No necesita disponibilidad"); return false; },
                      [&](uint32_t) { t.Fail("No hay timestamps"); return uint64_t{0}; },
                      [&](const Window &w)
                      {
                          ++reports;
                          t.Equals(w.frames, uint64_t{4}, "Cuatro cuadros sin consultas");
                          t.Equals(w.reasons[5], uint64_t{2}, "Conserva flushes");
                          t.Equals(w.count[0], uint64_t{0}, "No inventa muestras");
                      });
            t.Equals(reports, 1u, "Informa contadores reales");
        });
    });
}
