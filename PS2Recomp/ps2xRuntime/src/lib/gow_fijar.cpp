// GOW-Port: fijar el objetivo (lock-on) en God of War (SCUS-97399), como en los God of War modernos.
//
// Alt (izquierdo o derecho, pulsado y soltado solo) fija el enemigo actual y vuelve a pulsarse para soltarlo. Con
// el objetivo fijado, mover el ratón a izquierda o derecha pasa al enemigo siguiente en ese lado de la pantalla.
// Kratos dirige sus ataques al objetivo fijado: el juego ya tiene puntería automática y aquí se le da el objetivo.
// Si el objetivo muere se pasa al enemigo más cercano; sin enemigos se suelta. GOW_FIJAR=0 lo desactiva.
//
// Datos del juego (ver docs/CONTROLES.md, "Fijar objetivo"):
//   *(*0x29CD58)        Kratos (criatura): posición +0xC0 (los pies), vida +0x178, máxima +0x17C, alto +0x124.
//   *0x29E414           reserva de criaturas: cabecera (0x31415927), entradas de 0x20 desde +0x20; una viva lleva la
//                       criatura en +0x00 y 0x2B95E8 en +0x18. Kratos y los enemigos del área.
//   *0x29D2AC           tabla de identificadores: entradas de 12 bytes desde +8 {identificador, clase, objeto};
//                       el índice es identificador >> 23.
//   0x1D90F0 / 0x1D9750 eligen el objetivo de Kratos (alcance "Targeting Range" 0x30290C / "Manual Targeting Range"
//                       0x302910) y devuelven su identificador; 0x1D78B0 lo guarda.
//   *0x35FA98 + 0x40    matriz vista-proyección de la cámara (vector fila: clip = (x, y, z, 1) * M).
//
// Herramientas de investigación (variables de entorno):
//   GOW_FIJAR_STICK="t0:dur:lx:ly;..."  fuerza el stick izquierdo (0..255) durante dur segundos desde t0.
//   GOW_FIJAR_VOLCADO="t1,t2,..."       guarda la RAM del EE en fijar_ram_<t>.bin (solo local; nunca se sube).
//   GOW_FIJAR_DIAG=1                    registra los cambios de objetivo.
//   GOW_FIJAR_PRUEBA="t:alt;t:der;t:izq" simula Alt y el ratón a esos segundos (pruebas sin teclado).
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "raylib.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

bool gowTrucosEntradaBloqueada(); // gow_trucos.cpp

namespace
{
    constexpr uint32_t kPad2Read = 0x0027B9F0u;
    constexpr uint32_t kElegirObjetivo = 0x001D90F0u;
    constexpr uint32_t kElegirObjetivoManual = 0x001D9750u;
    constexpr uint32_t kControlJugador = 0x0029CD58u;
    constexpr uint32_t kReservaCriaturas = 0x0029E414u;
    constexpr uint32_t kTablaIdentificadores = 0x0029D2ACu;
    constexpr uint32_t kCamara = 0x0035FA98u;
    constexpr uint32_t kMagiaReserva = 0x31415927u;
    constexpr uint32_t kClaseCriatura = 0x002B95E8u;
    constexpr float kDistanciaMaxima = 3000.0f; // más lejos se suelta el objetivo
    constexpr float kDistanciaFijar = 1500.0f;  // alcance para elegir al pulsar Alt

    PS2Runtime::RecompiledFunction g_pad2Read = nullptr;
    PS2Runtime::RecompiledFunction g_elegirObjetivo = nullptr;
    PS2Runtime::RecompiledFunction g_elegirObjetivoManual = nullptr;
    bool g_diag = false;

    // ---- Memoria del EE ----
    bool direccionValida(uint32_t a, uint32_t bytes = 4u)
    {
        a &= 0x1FFFFFFFu;
        return a >= 0x00100000u && a + bytes <= PS2_RAM_SIZE && (a & 3u) == 0u;
    }
    uint32_t leer32(const uint8_t *rdram, uint32_t a)
    {
        uint32_t v = 0u;
        std::memcpy(&v, rdram + (a & 0x1FFFFFFu), 4);
        return v;
    }
    float leerF(const uint8_t *rdram, uint32_t a)
    {
        float v = 0.0f;
        std::memcpy(&v, rdram + (a & 0x1FFFFFFu), 4);
        return v;
    }

    struct Criatura
    {
        uint32_t dir = 0u;
        float x = 0.0f, y = 0.0f, z = 0.0f;
        float vida = 0.0f;
        float alto = 40.0f;
        // Pantalla (coordenadas normalizadas -1..1, y hacia abajo) del pecho.
        float px = 0.0f, py = 0.0f, w = 0.0f;
        bool enPantalla = false;
    };

    bool leerCriatura(const uint8_t *rdram, uint32_t dir, Criatura &c)
    {
        if (!direccionValida(dir, 0x360u))
            return false;
        c.dir = dir & 0x1FFFFFFu;
        c.x = leerF(rdram, c.dir + 0xC0u);
        c.y = leerF(rdram, c.dir + 0xC4u);
        c.z = leerF(rdram, c.dir + 0xC8u);
        const float w = leerF(rdram, c.dir + 0xCCu);
        c.vida = leerF(rdram, c.dir + 0x178u);
        const float maxima = leerF(rdram, c.dir + 0x17Cu);
        const float medio = leerF(rdram, c.dir + 0x124u);
        // +0x124: el alto (35 en los legionarios; en pantalla miden ~41 sobre los pies).
        c.alto = std::isfinite(medio) && medio > 5.0f && medio < 1000.0f ? medio : 40.0f;
        return w == 1.0f && std::isfinite(c.x) && std::isfinite(c.y) && std::isfinite(c.z) && std::isfinite(c.vida) &&
               std::isfinite(maxima) && maxima >= 1.0f && maxima <= 100000.0f && c.vida <= maxima;
    }

    // Kratos: la criatura del controlador del jugador.
    bool kratos(const uint8_t *rdram, Criatura &k)
    {
        const uint32_t control = leer32(rdram, kControlJugador);
        if (!direccionValida(control))
            return false;
        return leerCriatura(rdram, leer32(rdram, control), k) && k.vida > 0.0f;
    }

    std::vector<Criatura> enemigos(const uint8_t *rdram, uint32_t kratosDir)
    {
        std::vector<Criatura> lista;
        const uint32_t reserva = leer32(rdram, kReservaCriaturas);
        if (!direccionValida(reserva, 0x20u) || leer32(rdram, reserva) != kMagiaReserva)
            return lista;
        const uint32_t base = (reserva & 0x1FFFFFFu) + 0x20u;
        for (uint32_t i = 0; i < 128u; ++i)
        {
            const uint32_t e = base + i * 0x20u;
            if (!direccionValida(e, 0x20u))
                break;
            const uint32_t primero = leer32(rdram, e);
            if (leer32(rdram, e + 0x18u) == kClaseCriatura)
            {
                Criatura c;
                if ((primero & 0x1FFFFFFu) != kratosDir && leerCriatura(rdram, primero, c) && c.vida > 0.0f)
                    lista.push_back(c);
                continue;
            }
            // Entrada libre: enlaza con la siguiente o termina la lista. Otra cosa: fin de la reserva.
            if (primero != 0u && (primero & 0x1FFFFFFu) != e + 0x20u)
                break;
        }
        return lista;
    }

    bool matrizCamara(const uint8_t *rdram, float (&m)[16])
    {
        const uint32_t camara = leer32(rdram, kCamara);
        if (!direccionValida(camara, 0x80u))
            return false;
        for (int i = 0; i < 16; ++i)
        {
            m[i] = leerF(rdram, camara + 0x40u + static_cast<uint32_t>(i) * 4u);
            if (!std::isfinite(m[i]))
                return false;
        }
        return true;
    }

    void proyectar(const float (&m)[16], Criatura &c)
    {
        const float x = c.x, y = c.y + c.alto * 0.55f, z = c.z; // el pecho, como la marca de los juegos modernos
        const float cx = x * m[0] + y * m[4] + z * m[8] + m[12];
        const float cy = x * m[1] + y * m[5] + z * m[9] + m[13];
        const float cw = x * m[3] + y * m[7] + z * m[11] + m[15];
        c.w = cw;
        if (cw <= 1.0f)
        {
            c.enPantalla = false;
            return;
        }
        c.px = cx / cw;
        c.py = cy / cw;
        c.enPantalla = std::fabs(c.px) < 1.1f && std::fabs(c.py) < 1.1f;
    }

    float distancia(const Criatura &a, const Criatura &b)
    {
        const float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    // ---- Estado (hilo del juego) ----
    uint32_t g_fijado = 0u;     // dirección de la criatura fijada (0: ninguna)
    uint64_t g_sobrescritos = 0u;

    // Peticiones del hilo principal y lo que necesita para dibujar.
    std::atomic<uint32_t> g_pulsaciones{0u};
    std::atomic<int32_t> g_cambios{0};
    std::atomic<bool> g_activoPublicado{false};
    std::mutex g_dibujoMutex;
    struct Dibujo
    {
        bool visible = false;
        float x = 0.0f, y = 0.0f;
    } g_dibujo;

    const Criatura *buscar(const std::vector<Criatura> &lista, uint32_t dir)
    {
        for (const Criatura &c : lista)
            if (c.dir == dir)
                return &c;
        return nullptr;
    }

    // El enemigo "actual": el más cercano a Kratos entre los visibles, favoreciendo el centro de la pantalla.
    uint32_t elegirInicial(const std::vector<Criatura> &lista, const Criatura &k, float alcance)
    {
        uint32_t mejor = 0u;
        float puntos = 1e30f;
        for (const Criatura &c : lista)
        {
            const float d = distancia(c, k);
            if (d > alcance)
                continue;
            const float p = d * (c.enPantalla ? 1.0f + std::fabs(c.px) : 3.0f);
            if (p < puntos)
            {
                puntos = p;
                mejor = c.dir;
            }
        }
        return mejor;
    }

    // El siguiente visible a la izquierda (lado < 0) o a la derecha del actual.
    uint32_t elegirLado(const std::vector<Criatura> &lista, const Criatura &actual, int lado)
    {
        uint32_t mejor = 0u;
        float mejorDx = 1e30f;
        for (const Criatura &c : lista)
        {
            if (c.dir == actual.dir || !c.enPantalla)
                continue;
            const float dx = (c.px - actual.px) * static_cast<float>(lado);
            if (dx > 0.01f && dx < mejorDx)
            {
                mejorDx = dx;
                mejor = c.dir;
            }
        }
        return mejor;
    }

    void cambiarFijado(uint32_t nuevo, const char *motivo)
    {
        if (nuevo == g_fijado)
            return;
        if (g_diag)
            std::fprintf(stderr, "[gow-fijar] objetivo 0x%x -> 0x%x (%s)\n", g_fijado, nuevo, motivo);
        g_fijado = nuevo;
    }

    // Una vez por lectura del mando (cada cuadro del juego).
    void actualizar(const uint8_t *rdram)
    {
        const uint32_t pulsaciones = g_pulsaciones.exchange(0u);
        const int32_t cambios = g_cambios.exchange(0);
        Criatura k;
        float m[16];
        const bool hayKratos = kratos(rdram, k);
        const bool hayCamara = matrizCamara(rdram, m);
        std::vector<Criatura> lista;
        if (hayKratos)
        {
            lista = enemigos(rdram, k.dir);
            if (hayCamara)
                for (Criatura &c : lista)
                    proyectar(m, c);
        }
        if (!hayKratos)
            cambiarFijado(0u, "sin Kratos");
        if (hayKratos && (pulsaciones & 1u))
            cambiarFijado(g_fijado ? 0u : elegirInicial(lista, k, kDistanciaFijar), g_fijado ? "Alt: soltar" : "Alt: fijar");
        if (g_fijado)
        {
            const Criatura *actual = buscar(lista, g_fijado);
            if (!actual || distancia(*actual, k) > kDistanciaMaxima)
                cambiarFijado(elegirInicial(lista, k, kDistanciaFijar), actual ? "demasiado lejos" : "objetivo muerto");
            else if (cambios != 0)
            {
                const uint32_t lado = elegirLado(lista, *actual, cambios > 0 ? 1 : -1);
                if (lado)
                    cambiarFijado(lado, cambios > 0 ? "ratón: derecha" : "ratón: izquierda");
            }
        }
        if (g_diag)
        {
            static auto ultimo = std::chrono::steady_clock::now();
            const auto ahora = std::chrono::steady_clock::now();
            if (ahora - ultimo > std::chrono::seconds(2))
            {
                ultimo = ahora;
                std::fprintf(stderr, "[gow-fijar] kratos=%d camara=%d (0x%x) enemigos=%zu fijado=0x%x", hayKratos ? 1 : 0, hayCamara ? 1 : 0,
                             leer32(rdram, kCamara), lista.size(), g_fijado);
                for (const Criatura &c : lista)
                    std::fprintf(stderr, " [0x%x %.2f,%.2f w=%.0f%s]", c.dir, c.px, c.py, c.w, c.enPantalla ? "" : " fuera");
                std::fprintf(stderr, "\n");
            }
        }
        Dibujo d;
        if (const Criatura *c = g_fijado ? buscar(lista, g_fijado) : nullptr; c && c->enPantalla && hayCamara)
        {
            d.visible = true;
            d.x = c->px;
            d.y = c->py;
        }
        {
            std::lock_guard<std::mutex> lock(g_dibujoMutex);
            g_dibujo = d;
        }
        g_activoPublicado.store(g_fijado != 0u, std::memory_order_relaxed);
    }

    // Identificador del juego para un objeto (tabla de 0x29D2AC); 0 si no está.
    uint32_t identificador(const uint8_t *rdram, uint32_t objeto)
    {
        const uint32_t tabla = leer32(rdram, kTablaIdentificadores);
        if (!direccionValida(tabla))
            return 0u;
        const uint32_t base = (tabla & 0x1FFFFFFu) + 8u;
        for (uint32_t i = 0; i < 2048u; ++i)
        {
            const uint32_t e = base + i * 12u;
            if (e + 12u > PS2_RAM_SIZE)
                break;
            const uint32_t id = leer32(rdram, e);
            if ((id & 7u) != 0u || (id >> 23u) != i)
                continue;
            if ((leer32(rdram, e + 8u) & 0x1FFFFFFu) == objeto)
                return id;
        }
        return 0u;
    }

    // 0x1D90F0 y 0x1D9750: tras la elección del juego, el objetivo fijado.
    void sobrescribirObjetivo(uint8_t *rdram, R5900Context *ctx)
    {
        if (!g_fijado)
            return;
        const uint32_t id = identificador(rdram, g_fijado);
        if (!id)
            return;
        SET_GPR_U32(ctx, 2, id);
        ++g_sobrescritos;
    }

    void elegirObjetivo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool entrada = ctx->pc == kElegirObjetivo;
        g_elegirObjetivo(rdram, ctx, runtime);
        if (entrada)
            sobrescribirObjetivo(rdram, ctx);
    }

    void elegirObjetivoManual(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool entrada = ctx->pc == kElegirObjetivoManual;
        g_elegirObjetivoManual(rdram, ctx, runtime);
        if (entrada)
            sobrescribirObjetivo(rdram, ctx);
    }

    // ---- Herramientas de investigación ----
    struct Forzado
    {
        double inicio = 0.0, duracion = 0.0;
        uint8_t lx = 128u, ly = 128u;
    };
    std::vector<Forzado> g_forzados;
    std::vector<double> g_volcados;
    std::vector<std::pair<double, int>> g_pruebas; // (segundo, 0 Alt / +1 derecha / -1 izquierda)
    std::chrono::steady_clock::time_point g_t0;

    double segundos()
    {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - g_t0).count();
    }

    void leerHerramientas()
    {
        if (const char *v = std::getenv("GOW_FIJAR_STICK"))
        {
            std::string s(v);
            size_t pos = 0u;
            while (pos < s.size())
            {
                size_t fin = s.find(';', pos);
                if (fin == std::string::npos)
                    fin = s.size();
                Forzado f;
                unsigned lx = 128u, ly = 128u;
                if (std::sscanf(s.substr(pos, fin - pos).c_str(), "%lf:%lf:%u:%u", &f.inicio, &f.duracion, &lx, &ly) == 4)
                {
                    f.lx = static_cast<uint8_t>(lx);
                    f.ly = static_cast<uint8_t>(ly);
                    g_forzados.push_back(f);
                }
                pos = fin + 1u;
            }
        }
        if (const char *v = std::getenv("GOW_FIJAR_PRUEBA"))
        {
            std::string s(v);
            size_t pos = 0u;
            while (pos < s.size())
            {
                size_t fin = s.find(';', pos);
                if (fin == std::string::npos)
                    fin = s.size();
                const std::string tok = s.substr(pos, fin - pos);
                const size_t dos = tok.find(':');
                if (dos != std::string::npos)
                {
                    const std::string que = tok.substr(dos + 1);
                    g_pruebas.push_back({std::atof(tok.substr(0, dos).c_str()), que == "der" ? 1 : (que == "izq" ? -1 : 0)});
                }
                pos = fin + 1u;
            }
        }
        if (const char *v = std::getenv("GOW_FIJAR_VOLCADO"))
        {
            std::string s(v);
            size_t pos = 0u;
            while (pos < s.size())
            {
                size_t fin = s.find(',', pos);
                if (fin == std::string::npos)
                    fin = s.size();
                g_volcados.push_back(std::atof(s.substr(pos, fin - pos).c_str()));
                pos = fin + 1u;
            }
        }
    }

    void herramientas(uint8_t *rdram, uint32_t buffer)
    {
        if (g_forzados.empty() && g_volcados.empty() && g_pruebas.empty())
            return;
        const double t = segundos();
        for (auto &[cuando, que] : g_pruebas)
            if (cuando > 0.0 && t >= cuando)
            {
                if (que == 0)
                    g_pulsaciones.fetch_or(1u);
                else
                    g_cambios.fetch_add(que);
                cuando = -1.0;
            }
        for (const Forzado &f : g_forzados)
            if (t >= f.inicio && t < f.inicio + f.duracion)
            {
                rdram[buffer + 4u] = f.lx;
                rdram[buffer + 5u] = f.ly;
            }
        for (double &v : g_volcados)
            if (v > 0.0 && t >= v)
            {
                char nombre[64];
                std::snprintf(nombre, sizeof(nombre), "fijar_ram_%.0f.bin", v);
                if (FILE *f = std::fopen(nombre, "wb"))
                {
                    std::fwrite(rdram, 1, PS2_RAM_SIZE, f);
                    std::fclose(f);
                }
                std::fprintf(stderr, "[gow-fijar] volcado %s (t=%.2f, objetivo 0x%x, %llu sobrescritos)\n", nombre, t, g_fijado,
                             static_cast<unsigned long long>(g_sobrescritos));
                v = -1.0;
            }
    }

    void pad2Read(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t buffer = GPR_U32(ctx, 5) & 0x01FFFFFFu;
        g_pad2Read(rdram, ctx, runtime);
        if (GPR_U32(ctx, 2) != 18u || buffer + 18u > PS2_RAM_SIZE)
            return;
        actualizar(rdram);
        herramientas(rdram, buffer);
    }

    bool g_instalado = false;
}

// Hilo principal, cada cuadro de la ventana: Alt fija o suelta; el ratón cambia de objetivo.
void gowFijarEntrada()
{
    if (!g_instalado || gowTrucosEntradaBloqueada())
        return;
    // Alt cuenta al soltarse, con la ventana activa, si se pulsó solo y poco tiempo: así no cuentan Alt+Tab, otras
    // combinaciones ni las pulsaciones fantasma que llegan al cambiar el foco sin la suelta correspondiente.
    static bool altAbajo = false, otraTecla = false;
    static double altDesde = 0.0;
    const bool alt = IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
    if (alt && !altAbajo)
    {
        altAbajo = true;
        otraTecla = false;
        altDesde = GetTime();
    }
    if (altAbajo)
        for (int tecla = GetKeyPressed(); tecla != 0; tecla = GetKeyPressed())
            if (tecla != KEY_LEFT_ALT && tecla != KEY_RIGHT_ALT)
                otraTecla = true;
    if (!alt && altAbajo)
    {
        altAbajo = false;
        if (!otraTecla && IsWindowFocused() && GetTime() - altDesde < 0.6)
            g_pulsaciones.fetch_or(1u);
    }
    if (!IsWindowFocused())
        altAbajo = false;
    static float acumulado = 0.0f;
    static double ultimoCambio = 0.0;
    if (!g_activoPublicado.load(std::memory_order_relaxed))
    {
        acumulado = 0.0f;
        return;
    }
    acumulado += GetMouseDelta().x;
    const double ahora = GetTime();
    constexpr float kUmbral = 60.0f; // píxeles de ratón para cambiar de objetivo
    if (std::fabs(acumulado) >= kUmbral && ahora - ultimoCambio > 0.25)
    {
        g_cambios.fetch_add(acumulado > 0.0f ? 1 : -1);
        acumulado = 0.0f;
        ultimoCambio = ahora;
    }
    // Sin movimiento sostenido el acumulado se olvida poco a poco.
    acumulado *= 0.9f;
}

// Hilo principal, tras dibujar el cuadro del juego en destino: la marca sobre el objetivo fijado.
void gowFijarDibujar(float dx, float dy, float dw, float dh)
{
    if (!g_instalado)
        return;
    Dibujo d;
    {
        std::lock_guard<std::mutex> lock(g_dibujoMutex);
        d = g_dibujo;
    }
    if (!d.visible)
        return;
    const float x = dx + (d.x * 0.5f + 0.5f) * dw;
    const float y = dy + (d.y * 0.5f + 0.5f) * dh;
    const float r = std::max(6.0f, dh * 0.018f);
    const float pulso = 0.75f + 0.25f * std::sin(static_cast<float>(GetTime()) * 6.0f);
    const Color rojo{230, 40, 30, static_cast<unsigned char>(255.0f * pulso)};
    const Color borde{20, 0, 0, 200};
    // Rombo con borde oscuro, como la marca de objetivo de los juegos modernos.
    const Vector2 arriba{x, y - r}, derecha{x + r * 0.75f, y}, abajo{x, y + r}, izquierda{x - r * 0.75f, y};
    DrawTriangle(arriba, izquierda, abajo, rojo);
    DrawTriangle(arriba, abajo, derecha, rojo);
    DrawLineEx(arriba, derecha, 2.0f, borde);
    DrawLineEx(derecha, abajo, 2.0f, borde);
    DrawLineEx(abajo, izquierda, 2.0f, borde);
    DrawLineEx(izquierda, arriba, 2.0f, borde);
}

void gowFijarInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99")
        return;
    g_t0 = std::chrono::steady_clock::now();
    leerHerramientas();
    const char *activo = std::getenv("GOW_FIJAR");
    if (activo && activo[0] == '0')
        return;
    const char *diag = std::getenv("GOW_FIJAR_DIAG");
    g_diag = diag && diag[0] == '1';
    if (!runtime.hasFunction(kPad2Read) || !runtime.hasFunction(kElegirObjetivo) || !runtime.hasFunction(kElegirObjetivoManual))
        return;
    g_pad2Read = runtime.lookupFunction(kPad2Read);
    runtime.replaceFunction(kPad2Read, &pad2Read);
    g_elegirObjetivo = runtime.lookupFunction(kElegirObjetivo);
    runtime.replaceFunction(kElegirObjetivo, &elegirObjetivo);
    g_elegirObjetivoManual = runtime.lookupFunction(kElegirObjetivoManual);
    runtime.replaceFunction(kElegirObjetivoManual, &elegirObjetivoManual);
    g_instalado = true;
    std::cerr << "[gow-fijar] fijar objetivo: Alt; el ratón cambia de objetivo" << std::endl;
}
