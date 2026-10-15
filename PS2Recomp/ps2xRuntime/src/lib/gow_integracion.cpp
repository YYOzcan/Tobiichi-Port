// GOW-Port: funciones de Tobiichi Port sobre el runtime de Waffle565 (God-Of-War-Native-Port).
//
// El runtime de Waffle (GS nativo por render targets, IOP y VU1 compilados, vídeos nativos) es la base. Aquí se
// conectan, con el menor número de cambios en sus archivos, las funciones del port de Tobiichi:
//   - Ventana del lanzador: TOBIICHI_ANCHO / TOBIICHI_ALTO (o GOW_WINDOW=<an>x<al>), TOBIICHI_PANTALLA=completa
//     (F11 alterna), TOBIICHI_VSYNC=1, TOBIICHI_TITULO, TOBIICHI_ICONO, TOBIICHI_ESC_SALIR=0, TOBIICHI_VENTANA_FPS.
//   - Proporción de la imagen: TOBIICHI_ASPECTO ("estirar", "4:3", "21:9"...) o el aspecto de TOBIICHI_PANORAMICO;
//     sin ninguna, 16:9 como en Waffle.
//   - Panorámico Hor+ (TOBIICHI_PANORAMICO=A): la proyección lee el factor de 0x7F00 (parche de config/
//     recomp.template.toml) y aquí se escribe en cada VBlank. Sin la variable, F = 0,5625 con el modo 16:9 del juego
//     (el que fuerzan los overrides de Waffle): la imagen es bit a bit la misma que sin el parche.
//   - Teclado configurable (TOBIICHI_TECLAS, ps2_pad.cpp), menú de trucos (F2, gow_trucos.cpp), fijar objetivo
//     (Alt, gow_fijar.cpp), combate ágil (gow_cancelar.cpp), iconos de botones por dispositivo (gow_iconos.cpp),
//     escaneo progresivo (gow_video.cpp) y la sonda de funciones (GOW_SONDEO, gow_sondeo.cpp).
//   - gow_espera.cpp (el EE duerme mientras espera el cuadro) queda opcional con GOW_ESPERA_EE=1: Waffle mide la
//     velocidad del juego con los ciclos de ese bucle y la deja en 1,00.
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "raylib.h"

#include <algorithm>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

bool tobiichiSticksTeclado(uint8_t (&sticks)[4]); // ps2_pad.cpp (teclado configurable)
void gowTrucosInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowVideoInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowFijarInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowCancelarInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowSondeoInstalar(PS2Runtime &runtime);
void gowIconosInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowEsperaInstalar(PS2Runtime &runtime, const std::string &elfPath);
void gowFijarEntrada();
void gowFijarDibujar(float x, float y, float w, float h);
void gowIconosDibujar(float x, float y, float w, float h);
bool gowTrucosEntradaBloqueada();
void gowTrucosMenuEntrada(bool escCierraJuego);
void gowTrucosMenuDibujar();
void gowTrucosVBlank(uint8_t *rdram);
#if !defined(PLATFORM_VITA) && !defined(__ANDROID__)
extern "C" void glfwSetWindowAttrib(void *window, int attrib, int value); // GLFW va enlazado dentro de raylib
#endif

namespace
{
    bool envFlag(const char *name, bool fallback)
    {
        const char *value = std::getenv(name);
        if (!value || !*value)
            return fallback;
        return value[0] == '1';
    }

    long envLong(const char *name, long fallback, long low, long high)
    {
        const char *value = std::getenv(name);
        if (!value || !*value)
            return fallback;
        return std::clamp(std::strtol(value, nullptr, 10), low, high);
    }

    float parseAspect(const char *value)
    {
        float width = 0.0f, height = 0.0f;
        if (std::sscanf(value, "%f:%f", &width, &height) == 2 && width > 0.0f && height > 0.0f)
            return width / height;
        const float aspect = std::strtof(value, nullptr);
        return aspect >= 0.5f && aspect <= 4.0f ? aspect : 0.0f;
    }

    bool escCierraJuego()
    {
        static const bool value = envFlag("TOBIICHI_ESC_SALIR", true);
        return value;
    }

    void applyCursor()
    {
        if (IsWindowFullscreen())
            HideCursor();
        else
            ShowCursor();
    }

    // Pantalla completa con el modo de vídeo actual del monitor (no cambia la resolución). En X11/XWayland el gestor
    // de ventanas la trata como pantalla completa de verdad; ToggleBorderlessWindowed solo quita el marco.
    void alternarPantallaCompleta()
    {
        static int previousWidth = 0, previousHeight = 0;
        if (!IsWindowFullscreen())
        {
            previousWidth = GetScreenWidth();
            previousHeight = GetScreenHeight();
            const int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
#if !defined(PLATFORM_VITA) && !defined(__ANDROID__)
            // Sin minimizar al perder el foco (GLFW_AUTO_ICONIFY): con la ventana minimizada el framebuffer mide 0.
            glfwSetWindowAttrib(GetWindowHandle(), 0x00020006 /* GLFW_AUTO_ICONIFY */, 0 /* GLFW_FALSE */);
#endif
            ToggleFullscreen();
        }
        else
        {
            ToggleFullscreen();
            if (previousWidth > 0 && previousHeight > 0)
                SetWindowSize(previousWidth, previousHeight);
        }
        applyCursor();
    }

    // GOW-Port: lectura del mando de God of War (scePad2Read, 0x27B9F0; gowPad2Read en los overrides de Waffle). Con
    // TOBIICHI_TECLAS los sticks del teclado salen del mapa configurable; con el menú de trucos abierto el paquete
    // queda en reposo (botones sueltos, sticks centrados, sin presión).
    constexpr uint32_t kGowPad2Read = 0x0027B9F0u;
    PS2Runtime::RecompiledFunction g_gowPad2Read = nullptr;

    void tobiichiPad2Read(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t buffer = GPR_U32(ctx, 5) & 0x01FFFFFFu;
        g_gowPad2Read(rdram, ctx, runtime);
        if (GPR_U32(ctx, 2) != 18u || buffer + 18u > PS2_RAM_SIZE)
            return;
        if (gowTrucosEntradaBloqueada())
        {
            uint8_t *paquete = rdram + buffer;
            paquete[0] = paquete[1] = 0xFFu;
            std::memset(paquete + 2u, 0x80, 4u);
            std::memset(paquete + 6u, 0, 12u);
            return;
        }
        uint8_t sticks[4];
        if (tobiichiSticksTeclado(sticks))
            std::memcpy(rdram + buffer + 2u, sticks, sizeof(sticks));
    }

    // Panorámico Hor+ (ver docs/LANZADOR.md, "Panorámico"): F en 0x7F00 y el indicador de vídeo en 0x7F04, en cada
    // VBlank y como el parche de PCSX2: aspecto A en 0x32F1B0 y en los dos modos de pantalla (0x2FD930/0x2FD968),
    // indicador del juego 0x29CC90 = 1, 0x304D94 = 2 y vídeos sin modo panorámico; F = 0,75 (se ve más a los lados)
    // salvo con el fondo del menú (0x29CC50 = 1), donde F = 1/A (recorte vertical).
    void gowPanoramicoVBlank(uint8_t *rdram);
}

float gowAspectoPanoramico()
{
    static const float aspect = []
    {
        const char *value = std::getenv("TOBIICHI_PANORAMICO");
        if (!value || !*value)
            return 0.0f;
        const float result = parseAspect(value);
        return result >= 1.0f && result <= 4.0f ? result : 0.0f;
    }();
    return aspect;
}

namespace
{
    void gowPanoramicoVBlank(uint8_t *rdram)
    {
        if (!rdram)
            return;
        const auto read32 = [rdram](uint32_t address)
        {
            uint32_t value = 0u;
            std::memcpy(&value, rdram + address, sizeof(value));
            return value;
        };
        const auto write32 = [rdram](uint32_t address, uint32_t value) { std::memcpy(rdram + address, &value, sizeof(value)); };
        const auto floatBits = [](float value)
        {
            uint32_t bits = 0u;
            std::memcpy(&bits, &value, sizeof(bits));
            return bits;
        };
        const float target = gowAspectoPanoramico();
        float factor = 0.75f;
        if (target > 0.0f)
        {
            const uint32_t bits = floatBits(target);
            write32(0x32F1B0u, bits);
            write32(0x2FD930u, bits);
            write32(0x2FD968u, bits);
            rdram[0x29CC90u] = 1u;
            write32(0x304D94u, 2u);
            write32(0x7F04u, 0u);
            uint16_t menuBackground = 0u;
            std::memcpy(&menuBackground, rdram + 0x29CC50u, sizeof(menuBackground));
            if (menuBackground == 1u)
                factor = 1.0f / target;
        }
        else
        {
            const uint32_t bits = read32(0x32F1B0u);
            float aspect = 0.0f;
            std::memcpy(&aspect, &bits, sizeof(aspect));
            if (bits == 0x3FE38E39u) // 16/9: modo panorámico del propio juego
                factor = 0.5625f;
            else if (bits != 0x3FAAAAABu && aspect > 0.5f && aspect < 4.0f) // 4/3 o aún sin escribir: 0,75
                factor = 1.0f / aspect;
            write32(0x7F04u, read32(0x29CC90u));
        }
        write32(0x7F00u, floatBits(factor));
    }
}

// GOW-Port: Kernel/EeScheduler.cpp, al empezar cada VBlank y al reiniciar el planificador.
void gowIntegracionVBlank(uint8_t *rdram)
{
    gowPanoramicoVBlank(rdram);
    gowTrucosVBlank(rdram);
}

// GOW-Port: proporción de la imagen en la ventana (gs_host_present.cpp). 0 = estirar a toda la ventana.
float gowAspectoPresentacion()
{
    static const float aspect = []
    {
        if (const char *value = std::getenv("TOBIICHI_ASPECTO"); value && *value && std::strcmp(value, "auto") != 0)
        {
            if (std::strcmp(value, "estirar") == 0)
                return 0.0f;
            if (const float fixed = parseAspect(value); fixed > 0.0f)
                return fixed;
        }
        if (const float wide = gowAspectoPanoramico(); wide > 0.0f)
            return wide;
        return 16.0f / 9.0f;
    }();
    return aspect;
}

// GOW-Port: ps2_runtime.cpp (initialize), en lugar del InitWindow de Waffle.
void gowVentanaAbrir(const char *title)
{
    int width = static_cast<int>(envLong("TOBIICHI_ANCHO", 1920, 320, 7680));
    int height = static_cast<int>(envLong("TOBIICHI_ALTO", 1080, 224, 4320));
    if (!std::getenv("TOBIICHI_ANCHO") && !std::getenv("TOBIICHI_ALTO"))
        if (const char *size = std::getenv("GOW_WINDOW"))
        {
            int w = 0, h = 0;
            if (std::sscanf(size, "%dx%d", &w, &h) == 2 && w >= 320 && h >= 240)
                width = w, height = h;
        }
    const char *mode = std::getenv("TOBIICHI_PANTALLA");
    const bool fullscreen = mode && std::strcmp(mode, "completa") == 0;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | (envFlag("TOBIICHI_VSYNC", false) ? FLAG_VSYNC_HINT : 0u));
    const char *customTitle = std::getenv("TOBIICHI_TITULO");
    InitWindow(width, height, customTitle && *customTitle ? customTitle : title);
    // GOW-Port: GLFW pone LC_CTYPE del sistema. Con tr_TR, tolower('I') es 'I' y toupper('i') es 'i': fallaban las
    // comparaciones ASCII de nombres (módulos IRX, archivos del disco). El juego no usa entrada de texto.
    std::setlocale(LC_CTYPE, "C");
    if (!IsWindowReady())
        return;
    const int monitor = GetCurrentMonitor();
    const int maxWidth = GetMonitorWidth(monitor), maxHeight = GetMonitorHeight(monitor);
    if (!fullscreen && maxWidth > 0 && maxHeight > 0 && (width > maxWidth || height > maxHeight))
    {
        const float scale = std::min(static_cast<float>(maxWidth) / width, static_cast<float>(maxHeight) / height);
        SetWindowSize(static_cast<int>(width * scale), static_cast<int>(height * scale));
        SetWindowPosition(0, 0);
    }
    SetWindowMinSize(320, 224);
    if (const char *icon = std::getenv("TOBIICHI_ICONO"); icon && *icon)
    {
        Image image = LoadImage(icon);
        if (image.data)
        {
            SetWindowIcon(image);
            UnloadImage(image);
        }
    }
    if (fullscreen)
        alternarPantallaCompleta();
    if (!escCierraJuego())
        SetExitKey(KEY_NULL);
}

// GOW-Port: cuadros por segundo de la ventana (Waffle: 60). TOBIICHI_VENTANA_FPS=0 los deja sin límite.
int gowVentanaFps()
{
    const char *value = std::getenv("TOBIICHI_VENTANA_FPS");
    if (!value || !*value)
        return 60;
    const long fps = std::strtol(value, nullptr, 10);
    return fps == 0 ? 0 : static_cast<int>(std::clamp<long>(fps, 30, 360));
}

// GOW-Port: ps2_runtime.cpp (loadELF), después de los overrides de Waffle (applyMatching): cada envoltorio llama al
// anterior.
void gowIntegracionInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (runtime.hasFunction(kGowPad2Read))
    {
        if (PS2Runtime::RecompiledFunction actual = runtime.lookupFunction(kGowPad2Read))
        {
            g_gowPad2Read = actual;
            runtime.replaceFunction(kGowPad2Read, &tobiichiPad2Read);
            if (std::getenv("TOBIICHI_TECLAS"))
                std::cerr << "[teclado] mapa configurable activo (TOBIICHI_TECLAS); sticks del teclado desde el mapa" << std::endl;
        }
    }
    gowTrucosInstalar(runtime, elfPath);
    gowVideoInstalar(runtime, elfPath);    // escaneo progresivo siempre activado
    gowFijarInstalar(runtime, elfPath);    // fijar objetivo (envuelve la lectura del mando)
    gowCancelarInstalar(runtime, elfPath); // cancelar ataques (después de fijar: encadena su envoltorio)
    gowSondeoInstalar(runtime);            // GOW_SONDEO (diagnóstico)
    gowIconosInstalar(runtime, elfPath);   // iconos de botones según el dispositivo
    if (envFlag("GOW_ESPERA_EE", false))
        gowEsperaInstalar(runtime, elfPath);
}

// GOW-Port: ps2_runtime.cpp (bucle de la ventana), antes de dibujar cada cuadro.
void gowCuadroEntrada()
{
    if (IsKeyPressed(KEY_F11))
        alternarPantallaCompleta();
    gowTrucosMenuEntrada(escCierraJuego()); // F2, menú de trucos
    gowFijarEntrada();                      // Alt fija el objetivo, el ratón lo cambia
}

// GOW-Port: gs_host_present.cpp (renderFrame), encima de la imagen del juego (destino = rectángulo de la imagen).
void gowCuadroDibujar(float x, float y, float w, float h)
{
    gowFijarDibujar(x, y, w, h);
    gowIconosDibujar(x, y, w, h);
    gowTrucosMenuDibujar();
}
