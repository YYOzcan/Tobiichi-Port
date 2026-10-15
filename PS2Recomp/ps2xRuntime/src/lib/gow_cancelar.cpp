// GOW-Port: cancelación de animaciones de Kratos en God of War (SCUS-97399), para un combate más ágil.
//
// Cómo decide el juego cuándo empieza el movimiento siguiente (ver docs/CONTROLES.md, "Cancelar animaciones"):
//   *(Kratos+0x324)       controlador de movimientos de Kratos. +0x58 identificador del movimiento actual (0x50 de pie,
//                         0x47-0x4A combo de cuadrado, 0x20 triángulo, 0x30/0x21/0x22 bloqueo, 0x201-0x208 evasión,
//                         0x64-0x68 golpe recibido); +0x1AC estado (0x18 atacando, 0x19 bloqueando).
//   controlador+0x1C0     cola de transiciones pedidas con los botones: {+0 puntero a entradas, +4 u8 tamaño,
//                         +5 u8 lectura (0xFF vacía), +6 u8 escritura}; entradas de 8 bytes {transición, umbral}.
//   0x2048F8              cada cuadro saca la primera transición de la cola cuando el avance normalizado del
//                         movimiento actual llega a su umbral, y la empieza con 0x2088E8(controlador, transición).
// El juego ya corta un ataque con el bloqueo (L1) o la evasión (stick derecho) en el cuadro siguiente: esas transiciones
// llegan con umbral 0. Lo que obliga a esperar es el umbral de las demás: atacar desde una evasión espera al 50 % de la
// voltereta (~0,6 s) y cada golpe del combo de cuadrado al 27-47 % del anterior. Aquí:
//   - Evasión: las transiciones pedidas durante una evasión empiezan, como mucho, al kUmbralEvasion de su avance.
//   - Combo: los umbrales entre ataques se multiplican por el factor GOW_CANCELAR_COMBO (1 = como el original).
//   - Búfer de entrada: una pulsación de cuadrado o triángulo que el juego no aceptó (p. ej. al soltar L1 en el mismo
//     cuadro, o justo antes de acabar un movimiento) se repite unas veces durante kVentanaBufer segundos.
// Solo se cambian umbrales y pulsaciones: las transiciones son las del propio juego. GOW_CANCELAR=0 lo desactiva todo.
//
// Herramientas de investigación (solo local; los volcados contienen RAM del juego y nunca se suben):
//   GOW_CANCELAR_DIAG=1                     registra cada movimiento que empieza ([gow-cancelar] mov) y cada transición
//                                           que entra en la cola de Kratos con su umbral ([gow-cancelar] cola).
//   GOW_CANCELAR_TRAMO="t:dur:ini-fin,..."  guarda esas regiones de RAM (hex) en cada lectura del mando, en
//                                           cancelar_tramo.bin: double t, uint16 botones, 6 bytes de relleno y las
//                                           regiones seguidas. tools/perfil/linea_cancelar.py las muestra.
//   GOW_CANCELAR_EJE="t:dur:byte:valor;..." fuerza un byte del búfer de libpad2 (2/3 stick derecho X/Y, 4/5 izquierdo).
//   GOW_CANCELAR_VOLCADO="t1,t2,..."        guarda la RAM del EE en cancelar_ram_<t>.bin.
//   GOW_CANCELAR_VIGILAR="dir:bytes:t:dur"  (Linux x86-64) protege contra escritura la página de RAM del EE de dir y
//                                           guarda el RIP de cada escritura a [dir, dir+bytes) (fallo de página y un
//                                           paso con TF) en cancelar_escrituras.txt; nm sobre ps2EntryRunner da la
//                                           función recompilada.
// Los tiempos cuentan desde la primera lectura del mando, como GOW_FORCE_PAD.
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
#include <utility>
#include <vector>
#if defined(__linux__) && defined(__x86_64__)
#include <csignal>
#include <link.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>
#define GOW_CANCELAR_VIGILAR 1
#endif

namespace
{
    constexpr uint32_t kPad2Read = 0x0027B9F0u;
    constexpr uint32_t kEmpezarMovimiento = 0x002088E8u;
    constexpr uint32_t kControlJugador = 0x0029CD58u;
    constexpr uint16_t kCuadrado = 0x8000u, kTriangulo = 0x1000u; // bytes 0-1 del búfer de libpad2, activos a 0
    constexpr double kVentanaBufer = 0.35;                        // segundos que se recuerda una pulsación
    constexpr double kEsperaBufer = 0.035;                        // antes de repetirla
    constexpr int kRepeticiones = 3;

    PS2Runtime::RecompiledFunction g_pad2Read = nullptr;
    PS2Runtime::RecompiledFunction g_empezarMovimiento = nullptr;
    bool g_activo = false, g_bufer = true, g_diag = false;
    float g_umbralEvasion = 0.2f, g_factorCombo = 1.0f;

    double segundos()
    {
        static const auto arranque = std::chrono::steady_clock::now(); // primera lectura del mando
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - arranque).count();
    }

    uint32_t leer32(const uint8_t *rdram, uint32_t a)
    {
        uint32_t v = 0u;
        std::memcpy(&v, rdram + (a & 0x1FFFFFFu), 4);
        return v;
    }

    bool valida(uint32_t a, uint32_t bytes)
    {
        a &= 0x1FFFFFFFu;
        return a >= 0x00100000u && a + bytes <= PS2_RAM_SIZE && (a & 3u) == 0u;
    }

    // Controlador de movimientos de Kratos (*(Kratos+0x324)) o 0.
    uint32_t controladorKratos(const uint8_t *rdram)
    {
        const uint32_t control = leer32(rdram, kControlJugador);
        const uint32_t kratos = valida(control, 4u) ? leer32(rdram, control) : 0u;
        const uint32_t movs = valida(kratos, 0x360u) ? leer32(rdram, kratos + 0x324u) : 0u;
        return valida(movs, 0x200u) ? movs : 0u;
    }

    struct Cola
    {
        uint32_t entradas = 0u;
        uint8_t tam = 0u, lee = 0xFFu, esc = 0u;
        bool vacia() const { return lee == 0xFFu || tam == 0u || lee >= tam; }
        uint32_t cuantas() const
        {
            if (vacia())
                return 0u;
            const uint32_t n = (static_cast<uint32_t>(esc) + tam - lee) % tam;
            return n == 0u ? tam : n;
        }
    };

    Cola leerCola(const uint8_t *rdram, uint32_t c)
    {
        Cola q;
        const uint32_t base = (c + 0x1C0u) & 0x1FFFFFFu;
        q.entradas = leer32(rdram, base);
        q.tam = rdram[base + 4u];
        q.lee = rdram[base + 5u];
        q.esc = rdram[base + 6u];
        if (!valida(q.entradas, 8u * q.tam))
            q.lee = 0xFFu;
        return q;
    }

    bool evasion(uint32_t id) { return id >= 0x200u && id <= 0x20Fu; }
    bool atacando(uint32_t estado) { return (estado & 0x19u) == 0x18u; }

    // ---- Umbrales de la cola ----
    void ajustarCola(uint8_t *rdram, uint32_t c)
    {
        static uint32_t escalados[8] = {};
        const Cola q = leerCola(rdram, c);
        if (q.vacia())
        {
            std::memset(escalados, 0, sizeof(escalados));
            return;
        }
        const uint32_t id = leer32(rdram, c + 0x58u);
        const bool combo = g_factorCombo < 1.0f && atacando(leer32(rdram, c + 0x1ACu));
        for (uint32_t k = 0, i = q.lee; k < q.cuantas(); ++k, i = (i + 1u) % q.tam)
        {
            const uint32_t e = (q.entradas + 8u * i) & 0x1FFFFFFu;
            float umbral = 0.0f;
            std::memcpy(&umbral, rdram + e + 4u, 4);
            float nuevo = umbral;
            if (evasion(id))
                nuevo = std::min(umbral, g_umbralEvasion);
            else if (combo && umbral > 0.0f)
            {
                // Cada entrada se escala una sola vez: la clave es la transición y su hueco en la cola.
                const uint32_t clave = leer32(rdram, e) ^ (i << 28);
                if (escalados[i & 7u] != clave)
                {
                    escalados[i & 7u] = clave;
                    nuevo = umbral * g_factorCombo;
                }
            }
            if (nuevo != umbral)
                std::memcpy(rdram + e + 4u, &nuevo, 4);
        }
    }

    // ---- Búfer de entrada ----
    struct Pendiente
    {
        bool activa = false;
        double desde = 0.0, ultimo = 0.0;
        int repeticiones = 0;
        bool soltando = false; // cuadro en que se fuerza el botón suelto antes de volver a pulsarlo
        uint32_t movimientos = 0u;
    };
    Pendiente g_pendientes[2];
    uint16_t g_anterior = 0u; // botones reales pulsados en la lectura anterior (1 = pulsado)

    // El juego aceptó la pulsación: hay una transición en cola, una pedida en +0x44 o empezó otro movimiento atacando.
    bool aceptada(const uint8_t *rdram, uint32_t c, const Pendiente &p)
    {
        return !leerCola(rdram, c).vacia() || leer32(rdram, c + 0x44u) != 0u ||
               (atacando(leer32(rdram, c + 0x1ACu)) && leer32(rdram, c + 0x50u) != p.movimientos);
    }

    void bufer(uint8_t *rdram, uint32_t buffer, uint32_t c, double t)
    {
        uint16_t botones = 0xFFFFu;
        std::memcpy(&botones, rdram + buffer, 2);
        const uint16_t pulsados = static_cast<uint16_t>(~botones);
        const uint16_t mascaras[2] = {kCuadrado, kTriangulo};
        for (int b = 0; b < 2; ++b)
        {
            const uint16_t m = mascaras[b];
            Pendiente &p = g_pendientes[b];
            if ((pulsados & m) && !(g_anterior & m))
            {
                p = {};
                if (g_diag)
                    std::fprintf(stderr, "[gow-cancelar] búfer t=%.3f pulsación 0x%X (mov 0x%X)\n", t, m, leer32(rdram, c + 0x58u));
                p.activa = true;
                p.desde = p.ultimo = t;
                p.movimientos = leer32(rdram, c + 0x50u);
                continue;
            }
            if (!p.activa)
                continue;
            if (p.soltando)
            {
                botones = static_cast<uint16_t>(botones & ~m); // vuelve a pulsarlo: el juego ve una pulsación nueva
                if (g_diag)
                    std::fprintf(stderr, "[gow-cancelar] búfer t=%.3f repite 0x%X (mov 0x%X)\n", t, m, leer32(rdram, c + 0x58u));
                p.soltando = false;
                p.ultimo = t;
                ++p.repeticiones;
                continue;
            }
            if (aceptada(rdram, c, p) || t - p.desde > kVentanaBufer || p.repeticiones >= kRepeticiones)
            {
                if (g_diag)
                    std::fprintf(stderr, "[gow-cancelar] búfer t=%.3f fin 0x%X (%s, %d repeticiones)\n", t, m,
                                 aceptada(rdram, c, p) ? "aceptada" : "caducada", p.repeticiones);
                p.activa = false;
                continue;
            }
            if (t - p.ultimo >= kEsperaBufer)
            {
                botones = static_cast<uint16_t>(botones | m); // un cuadro suelto
                p.soltando = true;
            }
        }
        g_anterior = pulsados;
        std::memcpy(rdram + buffer, &botones, 2);
    }

    // ---- Herramientas de investigación ----
    std::vector<double> g_volcados;
    struct Eje
    {
        double t, dur;
        unsigned byte, valor;
    };
    std::vector<Eje> g_ejes;
    std::FILE *g_tramo = nullptr;
    double g_tramoInicio = 0.0, g_tramoFin = 0.0;
    std::vector<std::pair<uint32_t, uint32_t>> g_regiones;

    void herramientas(uint8_t *rdram, uint32_t buffer, double t)
    {
        for (double &v : g_volcados)
            if (v > 0.0 && t >= v)
            {
                char nombre[64];
                std::snprintf(nombre, sizeof(nombre), "cancelar_ram_%.2f.bin", v);
                if (std::FILE *f = std::fopen(nombre, "wb"))
                {
                    std::fwrite(rdram, 1, PS2_RAM_SIZE, f);
                    std::fclose(f);
                }
                v = -1.0;
            }
        for (const Eje &e : g_ejes)
            if (t >= e.t && t < e.t + e.dur && e.byte < 18u)
                rdram[buffer + e.byte] = static_cast<uint8_t>(e.valor);
        if (g_tramo && t >= g_tramoInicio)
        {
            if (t > g_tramoFin)
            {
                std::fclose(g_tramo);
                g_tramo = nullptr;
                std::fprintf(stderr, "[gow-cancelar] tramo cerrado\n");
            }
            else
            {
                uint16_t bot = 0xFFFFu;
                const uint8_t relleno[6] = {};
                std::memcpy(&bot, rdram + buffer, 2);
                std::fwrite(&t, sizeof(t), 1, g_tramo);
                std::fwrite(&bot, 2, 1, g_tramo);
                std::fwrite(relleno, 1, sizeof(relleno), g_tramo);
                for (const auto &[a, b] : g_regiones)
                    std::fwrite(rdram + a, 1, b - a, g_tramo);
            }
        }
    }

    void diagCola(const uint8_t *rdram, uint32_t c)
    {
        static uint32_t ultimo = 0u;
        const Cola q = leerCola(rdram, c);
        if (q.vacia())
        {
            ultimo = 0u;
            return;
        }
        const uint32_t e = q.entradas + 8u * q.lee;
        const uint32_t reg = leer32(rdram, e);
        float umbral = 0.0f;
        std::memcpy(&umbral, rdram + ((e + 4u) & 0x1FFFFFFu), 4);
        const uint32_t clave = reg ^ (static_cast<uint32_t>(q.lee) << 24) ^ (static_cast<uint32_t>(q.esc) << 16);
        if (clave == ultimo)
            return;
        ultimo = clave;
        std::fprintf(stderr, "[gow-cancelar] cola t=%.3f mov=0x%X reg=0x%X umbral=%.2f lee=%u esc=%u\n", segundos(),
                     leer32(rdram, c + 0x58u), reg, umbral, q.lee, q.esc);
    }

#ifdef GOW_CANCELAR_VIGILAR
    struct Escritura
    {
        double t;
        uint64_t rip;
        uint32_t dir;
        uint32_t valor;
    };
    constexpr size_t kMaxEscrituras = 4096u;
    Escritura g_escrituras[kMaxEscrituras];
    std::atomic<size_t> g_numEscrituras{0};
    uint8_t *g_rdram = nullptr;
    uint32_t g_vigDir = 0u, g_vigBytes = 0u;
    double g_vigInicio = 0.0, g_vigFin = 0.0;
    uintptr_t g_pagina = 0u;
    size_t g_tamPagina = 4096u;
    std::atomic<int> g_vigEstado{0}; // 0 sin empezar, 1 protegiendo, 2 terminado
    struct sigaction g_segvAnterior{}, g_trapAnterior{};
    thread_local bool t_pasoPendiente = false;
    thread_local uint64_t t_rip = 0u;
    thread_local uint32_t t_dir = 0u;

    void segv(int sig, siginfo_t *info, void *contexto)
    {
        const uintptr_t a = reinterpret_cast<uintptr_t>(info->si_addr);
        if (g_pagina != 0u && a >= g_pagina && a < g_pagina + g_tamPagina)
        {
            auto *uc = static_cast<ucontext_t *>(contexto);
            mprotect(reinterpret_cast<void *>(g_pagina), g_tamPagina, PROT_READ | PROT_WRITE);
            t_pasoPendiente = true;
            t_rip = static_cast<uint64_t>(uc->uc_mcontext.gregs[REG_RIP]);
            t_dir = static_cast<uint32_t>(a - reinterpret_cast<uintptr_t>(g_rdram));
            uc->uc_mcontext.gregs[REG_EFL] |= 0x100; // TF: un paso y SIGTRAP
            return;
        }
        if (g_segvAnterior.sa_flags & SA_SIGINFO)
        {
            if (g_segvAnterior.sa_sigaction)
                g_segvAnterior.sa_sigaction(sig, info, contexto);
            return;
        }
        if (g_segvAnterior.sa_handler == SIG_DFL || g_segvAnterior.sa_handler == SIG_IGN)
        {
            signal(SIGSEGV, SIG_DFL); // la instrucción se repite y el proceso termina como siempre
            return;
        }
        g_segvAnterior.sa_handler(sig);
    }

    void trap(int sig, siginfo_t *info, void *contexto)
    {
        if (!t_pasoPendiente)
        {
            if ((g_trapAnterior.sa_flags & SA_SIGINFO) && g_trapAnterior.sa_sigaction)
                g_trapAnterior.sa_sigaction(sig, info, contexto);
            return;
        }
        auto *uc = static_cast<ucontext_t *>(contexto);
        uc->uc_mcontext.gregs[REG_EFL] &= ~0x100;
        t_pasoPendiente = false;
        const uint32_t d = t_dir & ~3u;
        if (d + 4u > g_vigDir && d < g_vigDir + g_vigBytes)
        {
            const size_t i = g_numEscrituras.fetch_add(1u);
            if (i < kMaxEscrituras)
            {
                uint32_t v = 0u;
                std::memcpy(&v, g_rdram + d, 4);
                g_escrituras[i] = {segundos(), t_rip, t_dir, v};
            }
        }
        if (g_vigEstado.load() == 1)
            mprotect(reinterpret_cast<void *>(g_pagina), g_tamPagina, PROT_READ);
    }

    uintptr_t baseEjecutable()
    {
        uintptr_t base = 0u;
        dl_iterate_phdr([](dl_phdr_info *i, size_t, void *dato) {
            if (i->dlpi_name == nullptr || i->dlpi_name[0] == '\0')
            {
                *static_cast<uintptr_t *>(dato) = static_cast<uintptr_t>(i->dlpi_addr);
                return 1;
            }
            return 0;
        }, &base);
        return base;
    }

    // Desde la lectura del mando (hilo del EE): empieza y termina la vigilancia.
    void vigilar(uint8_t *rdram, double t)
    {
        const int estado = g_vigEstado.load();
        if (g_vigBytes == 0u || estado == 2)
            return;
        if (estado == 0 && t >= g_vigInicio)
        {
            g_rdram = rdram;
            g_tamPagina = static_cast<size_t>(sysconf(_SC_PAGESIZE));
            g_pagina = reinterpret_cast<uintptr_t>(rdram + g_vigDir) & ~(g_tamPagina - 1u);
            struct sigaction sa{};
            sa.sa_sigaction = &segv;
            sa.sa_flags = SA_SIGINFO | SA_NODEFER;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGSEGV, &sa, &g_segvAnterior);
            sa.sa_sigaction = &trap;
            sigaction(SIGTRAP, &sa, &g_trapAnterior);
            g_vigEstado.store(1);
            mprotect(reinterpret_cast<void *>(g_pagina), g_tamPagina, PROT_READ);
            std::fprintf(stderr, "[gow-cancelar] vigilando 0x%X (%u bytes)\n", g_vigDir, g_vigBytes);
        }
        else if (estado == 1 && t > g_vigFin)
        {
            g_vigEstado.store(2);
            mprotect(reinterpret_cast<void *>(g_pagina), g_tamPagina, PROT_READ | PROT_WRITE);
            const size_t n = std::min(g_numEscrituras.load(), kMaxEscrituras);
            if (std::FILE *f = std::fopen("cancelar_escrituras.txt", "w"))
            {
                std::fprintf(f, "base %llx\n", static_cast<unsigned long long>(baseEjecutable()));
                for (size_t i = 0; i < n; ++i)
                    std::fprintf(f, "%.3f %llx %x %x\n", g_escrituras[i].t, static_cast<unsigned long long>(g_escrituras[i].rip),
                                 g_escrituras[i].dir, g_escrituras[i].valor);
                std::fclose(f);
            }
            std::fprintf(stderr, "[gow-cancelar] %zu escrituras en cancelar_escrituras.txt\n", n);
        }
    }
#endif

    // 0x2088E8(controlador, transición): empieza un movimiento (solo con GOW_CANCELAR_DIAG).
    void empezarMovimiento(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc == kEmpezarMovimiento)
        {
            const uint32_t control = GPR_U32(ctx, 4);
            std::fprintf(stderr, "[gow-cancelar] mov t=%.3f ra=0x%X ctl=0x%X reg=0x%X (antes 0x%X)\n", segundos(),
                         GPR_U32(ctx, 31), control, GPR_U32(ctx, 5),
                         valida(control, 0x60u) ? leer32(rdram, control + 0x58u) : 0u);
        }
        g_empezarMovimiento(rdram, ctx, runtime);
    }

    void pad2Read(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t buffer = GPR_U32(ctx, 5) & 0x01FFFFFFu;
        g_pad2Read(rdram, ctx, runtime);
        const double t = segundos();
#ifdef GOW_CANCELAR_VIGILAR
        vigilar(rdram, t);
#endif
        if (GPR_U32(ctx, 2) != 18u || buffer + 18u > PS2_RAM_SIZE)
            return;
        herramientas(rdram, buffer, t);
        const uint32_t c = controladorKratos(rdram);
        if (!c)
            return;
        if (g_activo)
        {
            ajustarCola(rdram, c);
            if (g_bufer)
                bufer(rdram, buffer, c, t);
        }
        if (g_diag)
            diagCola(rdram, c);
    }

    float leerFactor(const char *nombre, float defecto)
    {
        const char *v = std::getenv(nombre);
        if (!v || !*v)
            return defecto;
        const float f = std::strtof(v, nullptr);
        return f >= 0.0f && f <= 1.0f ? f : defecto;
    }
}

void gowCancelarInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99" || !runtime.hasFunction(kPad2Read))
        return;
    const char *activo = std::getenv("GOW_CANCELAR");
    g_activo = !(activo && activo[0] == '0');
    g_umbralEvasion = leerFactor("GOW_CANCELAR_EVASION", g_umbralEvasion);
    g_factorCombo = leerFactor("GOW_CANCELAR_COMBO", g_factorCombo);
    if (const char *v = std::getenv("GOW_CANCELAR_BUFER"); v && v[0] == '0')
        g_bufer = false;

    if (const char *v = std::getenv("GOW_CANCELAR_VOLCADO"))
        for (const char *p = v; *p;)
        {
            char *fin = nullptr;
            const double t = std::strtod(p, &fin);
            if (fin == p)
                break;
            g_volcados.push_back(t);
            p = *fin == ',' ? fin + 1 : fin;
        }
    if (const char *v = std::getenv("GOW_CANCELAR_EJE"))
    {
        const std::string lista(v);
        size_t pos = 0u;
        while (pos < lista.size())
        {
            size_t fin = lista.find(';', pos);
            if (fin == std::string::npos)
                fin = lista.size();
            Eje e{};
            if (std::sscanf(lista.substr(pos, fin - pos).c_str(), "%lf:%lf:%u:%u", &e.t, &e.dur, &e.byte, &e.valor) == 4)
                g_ejes.push_back(e);
            pos = fin + 1u;
        }
    }
    if (const char *v = std::getenv("GOW_CANCELAR_TRAMO"))
    {
        char lista[512] = {};
        if (std::sscanf(v, "%lf:%lf:%511s", &g_tramoInicio, &g_tramoFin, lista) == 3)
        {
            g_tramoFin += g_tramoInicio;
            for (char *tok = std::strtok(lista, ","); tok; tok = std::strtok(nullptr, ","))
            {
                unsigned a = 0u, b = 0u;
                if (std::sscanf(tok, "%x-%x", &a, &b) == 2 && a < b && b <= PS2_RAM_SIZE)
                    g_regiones.emplace_back(a & ~3u, b & ~3u);
            }
            if (!g_regiones.empty())
                g_tramo = std::fopen("cancelar_tramo.bin", "wb");
        }
    }
#ifdef GOW_CANCELAR_VIGILAR
    if (const char *v = std::getenv("GOW_CANCELAR_VIGILAR"))
    {
        unsigned dir = 0u, bytes = 0u;
        if (std::sscanf(v, "%x:%u:%lf:%lf", &dir, &bytes, &g_vigInicio, &g_vigFin) == 4 && dir + bytes <= PS2_RAM_SIZE)
        {
            g_vigDir = dir;
            g_vigBytes = bytes;
            g_vigFin += g_vigInicio;
        }
    }
#endif
    if (const char *v = std::getenv("GOW_CANCELAR_DIAG"); v && v[0] == '1' && runtime.hasFunction(kEmpezarMovimiento))
    {
        g_diag = true;
        g_empezarMovimiento = runtime.lookupFunction(kEmpezarMovimiento);
        runtime.replaceFunction(kEmpezarMovimiento, &empezarMovimiento);
    }
    // Encadena con el envoltorio que ya hubiera (gow_fijar.cpp).
    g_pad2Read = runtime.lookupFunction(kPad2Read);
    runtime.replaceFunction(kPad2Read, &pad2Read);
    if (g_activo)
        std::cerr << "[gow-cancelar] cancelación ágil: evasión al " << g_umbralEvasion << ", combo x" << g_factorCombo
                  << (g_bufer ? ", búfer de entrada" : "") << std::endl;
}
