// GOW-Port: espera del cuadro de God of War (SCUS-97399) sin girar.
//
// func_17A2A0 (el bucle del cuadro) espera a que una interrupción baje la bandera 0x29C7D0 así:
//     while (*(u32 *)0x29C7D0 == 1)
//         for (v0 = 20000; v0; --v0) ;      // 0x17A328..0x17A35C
// En el código recompilado cada vuelta del bucle interior pasa por eeCheckpointDue: el hilo del EE ocupaba un
// núcleo entero (EeScheduler::accountCycles era el 31 % de sus muestras) solo para esperar. En un portátil con el
// perfil de ahorro de energía ese núcleo quita potencia y el núcleo hermano (SMT) al hilo de VU1, que es el que
// limita el cuadro.
//
// Aquí, cuando el EE vuelve a entrar en ese bucle (al reanudarse tras un punto de control) y la bandera sigue a 1,
// duerme en pasos de ~100 µs. El tiempo dormido se cobra como ciclos del EE (294,912 MHz) con eeCheckpointDue, así
// que el VBlank, los temporizadores y el IOP avanzan con el reloj real igual que antes. En cuanto hay un punto de
// control (una interrupción pendiente, el VBlank) se vuelve al planificador en 0x17A328 con $v0 = 1: el bucle de
// retardo termina en una vuelta y vuelve a leer la bandera (0x17A350). El planificador entrega antes la interrupción.
// La tabla de funciones tiene una entrada por punto de reanudación (0x17A328 y 0x17A32C dentro del bucle), así que el
// envoltorio se instala en las tres. GOW_ESPERA_EE=0 lo desactiva.
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

namespace
{
    constexpr uint32_t kBucleCuadro = 0x17A2A0u;
    constexpr uint32_t kEsperaInicio = 0x17A328u;  // bucle de retardo
    constexpr uint32_t kEsperaFin = 0x17A35Cu;     // ranura de retardo del salto que vuelve a él
    constexpr uint32_t kReanudar = 0x17A328u;      // punto de reanudación registrado del bucle de retardo
    constexpr uint32_t kBandera = 0x29C7D0u;
    constexpr double kRelojEe = 294912000.0;

    PS2Runtime::RecompiledFunction g_bucleCuadro = nullptr;
    std::atomic<uint64_t> g_dormidoNs{0};
    bool g_diag = false;
}

// GOW-Port: GOW_ESPERA_DIAG: instante (ns de steady_clock) en que el EE dejó de esperar el cuadro; ps2_memory.cpp
// mide respecto a él cuándo empieza y acaba de trabajar el hilo de VU1.
std::atomic<int64_t> g_gowFinCuadroNs{0};

namespace
{

    // GOW_ESPERA_DIAG=1: cada 5 s, cuadros y tiempo medio por cuadro que el EE espera la bandera y que trabaja.
    void diagnostico(bool esperando)
    {
        static bool enEspera = false;
        static auto marca = std::chrono::steady_clock::now(), ventana = marca;
        static double esperaMs = 0.0, trabajoMs = 0.0;
        static unsigned cuadros = 0;
        const auto ahora = std::chrono::steady_clock::now();
        const double ms = std::chrono::duration<double, std::milli>(ahora - marca).count();
        if (esperando == enEspera)
            return;
        (enEspera ? esperaMs : trabajoMs) += ms;
        if (!esperando)
            g_gowFinCuadroNs.store(std::chrono::duration_cast<std::chrono::nanoseconds>(ahora.time_since_epoch()).count(),
                                   std::memory_order_relaxed);
        if (esperando)
            ++cuadros;
        enEspera = esperando;
        marca = ahora;
        if (ahora - ventana >= std::chrono::seconds(5) && cuadros)
        {
            std::fprintf(stderr, "[gow-espera] %u esperas: EE espera %.2f ms y trabaja %.2f ms por cuadro\n", cuadros,
                         esperaMs / cuadros, trabajoMs / cuadros);
            esperaMs = trabajoMs = 0.0;
            cuadros = 0;
            ventana = ahora;
        }
    }

    uint32_t bandera(const uint8_t *rdram)
    {
        uint32_t v = 0u;
        std::memcpy(&v, rdram + kBandera, 4);
        return v;
    }

    void bucleCuadro(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t pc = ctx->pc;
        if (pc < kEsperaInicio || pc > kEsperaFin || ctx->in_delay_slot || bandera(rdram) != 1u)
        {
            if (g_diag)
                diagnostico(false);
            g_bucleCuadro(rdram, ctx, runtime);
            return;
        }
        if (g_diag)
            diagnostico(true);
        // El EE espera la bandera: dormir en lugar de girar, cobrando el tiempo real como ciclos.
        auto ultimo = std::chrono::steady_clock::now();
        const auto inicio = ultimo;
        for (;;)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            const auto ahora = std::chrono::steady_clock::now();
            const double segundos = std::chrono::duration<double>(ahora - ultimo).count();
            ultimo = ahora;
            const uint32_t ciclos = static_cast<uint32_t>(std::clamp(segundos * kRelojEe, 32.0, 4.0e6));
            const bool punto = runtime->eeCheckpointDue(ciclos);
            if (punto || bandera(rdram) != 1u || ahora - inicio > std::chrono::milliseconds(50))
                break;
        }
        g_dormidoNs.fetch_add(static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                  std::chrono::steady_clock::now() - inicio).count()),
                              std::memory_order_relaxed);
        // Vuelve al planificador: entrega lo pendiente y reanuda en el bucle de retardo con $v0 = 1, que acaba en una
        // vuelta y vuelve a leer la bandera ($a2 ya vale 0x2A0000 desde 0x17A300).
        SET_GPR_U32(ctx, 2, 1u);
        ctx->pc = kReanudar;
    }
}

uint64_t gowEsperaDormidoNs() { return g_dormidoNs.load(std::memory_order_relaxed); }

void gowEsperaInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99")
        return;
    const char *valor = std::getenv("GOW_ESPERA_EE");
    if (valor && valor[0] == '0')
        return;
    if (!runtime.hasFunction(kBucleCuadro))
        return;
    const char *diag = std::getenv("GOW_ESPERA_DIAG");
    g_diag = diag && diag[0] == '1';
    g_bucleCuadro = runtime.lookupFunction(kBucleCuadro);
    for (const uint32_t pc : {kBucleCuadro, 0x17A328u, 0x17A32Cu})
        if (runtime.hasFunction(pc) && runtime.lookupFunction(pc) == g_bucleCuadro)
            runtime.replaceFunction(pc, &bucleCuadro);
    std::cerr << "[gow-espera] el EE duerme mientras espera el cuadro" << std::endl;
}
