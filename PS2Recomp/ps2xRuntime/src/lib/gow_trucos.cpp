// GOW-Port: menú de trucos (entrenador) de God of War (SCUS-97399, NTSC-U). F2 lo abre durante la partida;
// TOBIICHI_TRUCOS="inmortal,un_golpe,..." (lanzador) da el estado inicial y TOBIICHI_IDIOMA (tr/en/es) el idioma.
//
// Direcciones sacadas del ejecutable (no de códigos de terceros):
//   0x302CC0  estado de Kratos (es lo que va a la partida guardada):
//     +0x5C float magia, +0x60 float medidor de la Furia de los Dioses (0..100, AddRage lo limita a 100),
//     +0x68 u16 orbes rojos (SetOrbs, 0x1DB250, los limita a 60000),
//     +0x76 u8 nivel de vida (0..4), +0x77 u8 nivel de magia (0..5) (0x1D8200: ojos de Gorgona / plumas de fénix),
//     +0x78..+0x7C u8 niveles de Furia de Zeus, Mirada de Medusa, Ira de Poseidón, Ejército de Hades y Espada de
//     Artemisa (0..2), +0x7D u8 nivel de las Espadas del Caos (0..4); 0x1D8CB8 da por completas esas cifras,
//     +0x82 u16 objetos (0x04 Zeus, 0x08 Medusa, 0x10 Poseidón, 0x20 Hades, 0x40 Artemisa, 0x100 tridente).
//   0x3028E0  ajustes del jugador: +0x00..+0x10 vida máxima de cada nivel, +0x14..+0x28 magia máxima de cada nivel.
//   0x29CD58  controlador del jugador; su primer campo es Kratos (vida en +0x178, máxima en +0x17C).
//   0x29CB94  variables de la interfaz (Costumes_Unlocked +0x1AC, HardMode_Unlocked +0x1B0).
//   0x2A12C8  partidas terminadas (bits 0-2 fácil/normal/difícil, 3 Modo Dios, 4 Desafío de los Dioses): de ahí
//     salen los extras, los trajes y la dificultad Modo Dios (0x1BA9B8, 0x22F4B0). Se guarda en la tarjeta.
//   0x1E0A80  fija la vida de una criatura (a0, f12; la deja entre 0 y la máxima). 0x1E0A98 le resta daño (a0, f12)
//     y avisa de los umbrales que cruza (fases de los jefes); acaba llamando a 0x1E0A80.
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "raylib.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    enum Truco : int
    {
        Inmortal,
        UnGolpe,
        MagiaInfinita,
        FuriaInfinita,
        OrbesMaximos,
        MejorasMaximas,
        TodosLosPoderes,
        MedidoresMaximos,
        Extras,
        kNumTrucos
    };
    constexpr const char *kIds[kNumTrucos] = {"inmortal", "un_golpe", "magia", "furia", "orbes",
                                              "mejoras", "poderes", "medidores", "extras"};

    constexpr uint32_t kMascara = 0x01FFFFFFu;
    constexpr uint32_t kEstado = 0x00302CC0u;
    constexpr uint32_t kAjustes = 0x003028E0u;
    constexpr uint32_t kControlJugador = 0x0029CD58u;
    constexpr uint32_t kVariablesInterfaz = 0x0029CB94u;
    constexpr uint32_t kPartidasTerminadas = 0x002A12C8u;
    constexpr uint32_t kFijarVida = 0x001E0A80u;
    constexpr uint32_t kRestarVida = 0x001E0A98u;

    std::array<std::atomic<bool>, kNumTrucos> g_activo{};
    std::atomic<bool> g_instalado{false};
    std::atomic<bool> g_menuAbierto{false};
    std::atomic<bool> g_bloqueoTrasCerrar{false};
    PS2Runtime::RecompiledFunction g_fijarVida = nullptr;
    PS2Runtime::RecompiledFunction g_restarVida = nullptr;

    bool activo(Truco truco) { return g_activo[truco].load(std::memory_order_relaxed); }

    bool diagActivo()
    {
        static const bool diag = []
        {
            const char *valor = std::getenv("TOBIICHI_TRUCOS_DIAG");
            return valor && std::strcmp(valor, "1") == 0;
        }();
        return diag;
    }

    // TOBIICHI_TRUCOS_DIAG=1: las primeras llamadas a las funciones de la vida (criatura, antes, pedido, después).
    void diagVida(const char *funcion, uint32_t criatura, uint32_t jugador, float antes, float pedido, float ajustado)
    {
        static std::atomic<unsigned> mensajes{0};
        if (!diagActivo() || mensajes.fetch_add(1, std::memory_order_relaxed) >= 400u)
            return;
        std::fprintf(stderr, "[trucos:vida] %s criatura=%06x%s vida=%.1f pedido=%.1f -> %.1f\n", funcion, criatura,
                     criatura == jugador ? " (Kratos)" : "", antes, pedido, ajustado);
    }

    bool direccionValida(uint32_t direccion, uint32_t bytes = 4u)
    {
        return direccion >= 0x00100000u && direccion + bytes <= PS2_RAM_SIZE && (direccion & 3u) == 0u;
    }

    template <typename T>
    T leer(const uint8_t *rdram, uint32_t direccion)
    {
        T valor{};
        std::memcpy(&valor, rdram + direccion, sizeof(T));
        return valor;
    }

    template <typename T>
    void escribir(uint8_t *rdram, uint32_t direccion, T valor)
    {
        std::memcpy(rdram + direccion, &valor, sizeof(T));
    }

    float vidaMaximaDeNivel(const uint8_t *rdram, unsigned nivel)
    {
        return leer<float>(rdram, kAjustes + 4u * std::min(nivel, 4u));
    }

    // Kratos: primer campo del controlador del jugador. 0 si los punteros no son de la RAM del juego.
    uint32_t kratos(const uint8_t *rdram)
    {
        const uint32_t control = leer<uint32_t>(rdram, kControlJugador) & kMascara;
        if (!direccionValida(control))
            return 0u;
        const uint32_t criatura = leer<uint32_t>(rdram, control) & kMascara;
        return direccionValida(criatura, 0x180u) ? criatura : 0u;
    }

    // Antes de escribir en Kratos (fuera de su propio código), su vida máxima tiene que ser una de las de la tabla
    // de niveles: así no se toca un objeto ya liberado durante una carga.
    bool kratosPlausible(const uint8_t *rdram, uint32_t criatura)
    {
        const float maxima = leer<float>(rdram, criatura + 0x17Cu);
        for (unsigned nivel = 0; nivel <= 4u; ++nivel)
            if (maxima > 0.0f && maxima == vidaMaximaDeNivel(rdram, nivel))
                return true;
        return false;
    }

    // 0x1E0A80 (a0 criatura, f12 vida nueva). Los argumentos solo se tocan al entrar: si el juego reanuda la función
    // tras un checkpoint (ctx->pc distinto de la entrada), se llama al original sin más.
    void fijarVida(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool inmortal = activo(Inmortal), unGolpe = activo(UnGolpe);
        const uint32_t criatura = GPR_U32(ctx, 4) & kMascara;
        if (ctx->pc == kFijarVida && (inmortal || unGolpe || diagActivo()) && direccionValida(criatura, 0x180u))
        {
            const float actual = leer<float>(rdram, criatura + 0x178u), pedido = ctx->f[12];
            const uint32_t jugador = kratos(rdram);
            if (ctx->f[12] < actual && jugador != 0u)
            {
                if (criatura == jugador && inmortal)
                    ctx->f[12] = actual;
                else if (criatura != jugador && unGolpe)
                    ctx->f[12] = 0.0f;
            }
            diagVida("fijar", criatura, jugador, actual, pedido, ctx->f[12]);
        }
        g_fijarVida(rdram, ctx, runtime);
    }

    // 0x1E0A98 (a0 criatura, f12 daño). Con un golpe el daño cubre toda la vida, así el juego avisa de todos los
    // umbrales que cruza (fases de los jefes) igual que si se los quitaran poco a poco.
    void restarVida(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool inmortal = activo(Inmortal), unGolpe = activo(UnGolpe);
        const uint32_t criatura = GPR_U32(ctx, 4) & kMascara;
        if (ctx->pc == kRestarVida && (inmortal || unGolpe || diagActivo()) && ctx->f[12] > 0.0f &&
            direccionValida(criatura, 0x180u))
        {
            const uint32_t jugador = kratos(rdram);
            const float pedido = ctx->f[12];
            if (jugador != 0u && criatura == jugador && inmortal)
                ctx->f[12] = 0.0f;
            else if (jugador != 0u && criatura != jugador && unGolpe)
                ctx->f[12] = std::max(ctx->f[12], leer<float>(rdram, criatura + 0x178u) + 1.0f);
            diagVida("restar", criatura, jugador, leer<float>(rdram, criatura + 0x178u), pedido, ctx->f[12]);
        }
        g_restarVida(rdram, ctx, runtime);
    }

    void diagnostico(const uint8_t *rdram)
    {
        static unsigned vblanks = 0;
        if (!diagActivo() || (++vblanks % 120u) != 0u)
            return;
        const uint32_t control = leer<uint32_t>(rdram, kControlJugador) & kMascara;
        const uint32_t jugador = kratos(rdram);
        std::fprintf(stderr,
                     "[trucos] control=%06x kratos=%06x vida=%.1f/%.1f plausible=%d magia=%.1f furia=%.1f(%.1f) orbes=%u "
                     "niveles vida=%u magia=%u zeus=%u medusa=%u poseidon=%u hades=%u artemisa=%u espadas=%u "
                     "objetos=%04x magia_elegida=%u ojos=%u plumas=%u terminadas=%x tabla vida=%.0f,%.0f,%.0f,%.0f,%.0f magia=%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",
                     control, jugador, jugador ? leer<float>(rdram, jugador + 0x178u) : -1.0f,
                     jugador ? leer<float>(rdram, jugador + 0x17Cu) : -1.0f, jugador ? kratosPlausible(rdram, jugador) : 0,
                     leer<float>(rdram, kEstado + 0x5Cu), leer<float>(rdram, kEstado + 0x60u), leer<float>(rdram, kEstado + 0x64u),
                     leer<uint16_t>(rdram, kEstado + 0x68u), rdram[kEstado + 0x76u], rdram[kEstado + 0x77u],
                     rdram[kEstado + 0x78u], rdram[kEstado + 0x79u], rdram[kEstado + 0x7Au], rdram[kEstado + 0x7Bu],
                     rdram[kEstado + 0x7Cu], rdram[kEstado + 0x7Du], leer<uint16_t>(rdram, kEstado + 0x82u), rdram[kEstado + 0x7Eu],
                     rdram[kEstado + 0x7Fu], rdram[kEstado + 0x80u], leer<uint32_t>(rdram, kPartidasTerminadas),
                     leer<float>(rdram, kAjustes + 0x00u), leer<float>(rdram, kAjustes + 0x04u), leer<float>(rdram, kAjustes + 0x08u),
                     leer<float>(rdram, kAjustes + 0x0Cu), leer<float>(rdram, kAjustes + 0x10u), leer<float>(rdram, kAjustes + 0x14u),
                     leer<float>(rdram, kAjustes + 0x18u), leer<float>(rdram, kAjustes + 0x1Cu), leer<float>(rdram, kAjustes + 0x20u),
                     leer<float>(rdram, kAjustes + 0x24u), leer<float>(rdram, kAjustes + 0x28u));
    }

    // ---- Menú (hilo principal) ----

    struct Textos
    {
        const char *titulo;
        const char *subtitulo;
        const char *ayuda;
        const char *nombre[kNumTrucos];
        const char *descripcion[kNumTrucos];
    };

    const Textos kTurco = {
        "HİLE MENÜSÜ",
        "Menü açıkken oyun girdisi durur",
        "↑↓ seç    Enter aç/kapat    F2 / Esc kapat",
        {"Ölümsüzlük", "Tek vuruşta öldürme", "Sınırsız büyü", "Sınırsız Rage of the Gods", "Maksimum kırmızı küre",
         "Tüm yükseltmeler", "Tüm güçler ve silahlar", "Maksimum can ve büyü barı", "Tüm ekstraları aç"},
        {"Kratos hasar almaz, canı hep dolu kalır.",
         "Düşmanlar ve bosslar tek vuruşta ölür.",
         "Büyü barı hiç azalmaz.",
         "Öfke barı hep dolu; açıkken bitmez.",
         "60000 kırmızı küre (oyunun sınırı).",
         "Blades of Chaos 5. seviye; büyüler ve Blade of Artemis 3. seviye.",
         "Zeus's Fury, Medusa's Gaze, Poseidon's Rage, Army of Hades, Blade of Artemis, Poseidon's Trident.",
         "Bütün Gorgon Eye ve Phoenix Feather yükseltmeleri.",
         "God Mode zorluğu, kostümler, videolar, Challenge of the Gods. Kayıt alınca kalıcı olur."},
    };

    const Textos kIngles = {
        "CHEAT MENU",
        "Game input is paused while the menu is open",
        "↑↓ select    Enter toggle    F2 / Esc close",
        {"God mode", "One-hit kills", "Infinite magic", "Infinite Rage of the Gods", "Max red orbs", "All upgrades",
         "All powers and weapons", "Max health and magic", "Unlock all extras"},
        {"Kratos takes no damage; health stays full.",
         "Enemies and bosses die in a single hit.",
         "The magic meter never drains.",
         "Rage meter always full; never runs out while active.",
         "60000 red orbs (the game's cap).",
         "Blades of Chaos level 5; magic and Blade of Artemis level 3.",
         "Zeus's Fury, Medusa's Gaze, Poseidon's Rage, Army of Hades, Blade of Artemis, Poseidon's Trident.",
         "Every Gorgon Eye and Phoenix Feather upgrade.",
         "God Mode difficulty, costumes, videos, Challenge of the Gods. Permanent once you save."},
    };

    const Textos kEspanol = {
        "MENÚ DE TRUCOS",
        "Con el menú abierto el juego no recibe controles",
        "↑↓ elegir    Enter activar    F2 / Esc cerrar",
        {"Inmortalidad", "Muerte de un golpe", "Magia infinita", "Furia de los Dioses infinita", "Orbes rojos al máximo",
         "Todas las mejoras", "Todos los poderes y armas", "Vida y magia al máximo", "Desbloquear todos los extras"},
        {"Kratos no recibe daño; la vida siempre llena.",
         "Los enemigos y los jefes mueren de un golpe.",
         "La barra de magia nunca baja.",
         "Barra de furia siempre llena; no se acaba mientras está activa.",
         "60000 orbes rojos (el límite del juego).",
         "Espadas del Caos nivel 5; magias y Espada de Artemisa nivel 3.",
         "Furia de Zeus, Mirada de Medusa, Ira de Poseidón, Ejército de Hades, Espada de Artemisa, Tridente de Poseidón.",
         "Todas las mejoras de Ojos de Gorgona y Plumas de Fénix.",
         "Dificultad Modo Dios, trajes, vídeos, Desafío de los Dioses. Al guardar queda para siempre."},
    };

    const Textos &textos()
    {
        static const Textos *elegidos = []
        {
            const char *idioma = std::getenv("TOBIICHI_IDIOMA");
            if (idioma && std::strncmp(idioma, "tr", 2) == 0)
                return &kTurco;
            if (idioma && std::strncmp(idioma, "es", 2) == 0)
                return &kEspanol;
            return &kIngles;
        }();
        return *elegidos;
    }

    struct Fuentes
    {
        Font normal{};
        Font negrita{};
        bool propias = false;
    };

    // Fuente del sistema con los caracteres del turco y del español; si no hay ninguna, la de raylib.
    Font cargarFuente(const std::vector<std::string> &rutas)
    {
        std::vector<int> codigos;
        for (int c = 32; c < 127; ++c)
            codigos.push_back(c);
        for (int c = 160; c < 256; ++c)
            codigos.push_back(c);
        for (int c : {0x011E, 0x011F, 0x0130, 0x0131, 0x015E, 0x015F, 0x2190, 0x2191, 0x2192, 0x2193, 0x2022, 0x2026})
            codigos.push_back(c);
        for (const std::string &ruta : rutas)
        {
            std::error_code error;
            if (ruta.empty() || !std::filesystem::is_regular_file(ruta, error))
                continue;
            Font fuente = LoadFontEx(ruta.c_str(), 64, codigos.data(), static_cast<int>(codigos.size()));
            if (fuente.texture.id != 0 && fuente.glyphCount > 0)
            {
                GenTextureMipmaps(&fuente.texture);
                SetTextureFilter(fuente.texture, TEXTURE_FILTER_TRILINEAR);
                return fuente;
            }
        }
        return Font{};
    }

    Fuentes &fuentes()
    {
        static Fuentes f = []
        {
            Fuentes out;
            const char *propia = std::getenv("TOBIICHI_FUENTE_MENU");
            out.normal = cargarFuente({propia ? propia : "", "/usr/share/fonts/TTF/DejaVuSans.ttf",
                                       "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", "/usr/share/fonts/noto/NotoSans-Regular.ttf",
                                       "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
                                       "/usr/share/fonts/liberation/LiberationSans-Regular.ttf", "C:/Windows/Fonts/segoeui.ttf",
                                       "C:/Windows/Fonts/arial.ttf"});
            out.negrita = cargarFuente({"/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
                                        "/usr/share/fonts/noto/NotoSans-Bold.ttf", "/usr/share/fonts/truetype/noto/NotoSans-Bold.ttf",
                                        "/usr/share/fonts/liberation/LiberationSans-Bold.ttf", "C:/Windows/Fonts/segoeuib.ttf",
                                        "C:/Windows/Fonts/arialbd.ttf"});
            out.propias = out.normal.texture.id != 0;
            if (!out.propias)
                out.normal = GetFontDefault();
            if (out.negrita.texture.id == 0)
                out.negrita = out.normal;
            return out;
        }();
        return f;
    }

    void texto(const Font &fuente, const char *cadena, float x, float y, float tamano, Color color)
    {
        DrawTextEx(fuente, cadena, Vector2{std::round(x), std::round(y)}, tamano, tamano * 0.02f, color);
    }

    float ancho(const Font &fuente, const char *cadena, float tamano)
    {
        return MeasureTextEx(fuente, cadena, tamano, tamano * 0.02f).x;
    }

    // Recorta la descripción con "…" si no cabe.
    std::string ajustar(const Font &fuente, const char *cadena, float tamano, float maximo)
    {
        std::string s(cadena);
        if (ancho(fuente, s.c_str(), tamano) <= maximo)
            return s;
        while (!s.empty())
        {
            do
                s.pop_back();
            while (!s.empty() && (static_cast<unsigned char>(s.back()) & 0xC0u) == 0x80u);
            if (!s.empty())
                s.pop_back();
            const std::string prueba = s + "…";
            if (ancho(fuente, prueba.c_str(), tamano) <= maximo)
                return prueba;
        }
        return s;
    }

    constexpr Color kOro{212, 168, 87, 255};
    constexpr Color kOroClaro{243, 216, 150, 255};
    constexpr Color kTexto{240, 230, 218, 255};
    constexpr Color kTextoSuave{188, 169, 153, 255};
    constexpr Color kTextoTenue{127, 109, 96, 255};
    constexpr Color kBorde{94, 61, 38, 255};

    struct EstadoMenu
    {
        int elegido = 0;
        int teclaCierre = 0;
        bool cursorOculto = false;
    };
    EstadoMenu g_menu;

    struct Geometria
    {
        float escala, x, y, w, cabecera, fila, pie, h;
    };

    Geometria geometria()
    {
        const float sw = static_cast<float>(GetScreenWidth()), sh = static_cast<float>(GetScreenHeight());
        Geometria g{};
        g.escala = std::clamp(sh / 1080.0f, 0.6f, 2.0f);
        g.w = std::min(sw - 32.0f, 820.0f * g.escala);
        g.cabecera = 96.0f * g.escala;
        g.fila = 64.0f * g.escala;
        g.pie = 52.0f * g.escala;
        g.h = std::min(sh - 32.0f, g.cabecera + g.fila * static_cast<float>(kNumTrucos) + g.pie);
        g.x = std::floor((sw - g.w) * 0.5f);
        g.y = std::floor((sh - g.h) * 0.5f);
        return g;
    }

    void alternar(int indice)
    {
        const bool nuevo = !g_activo[indice].load(std::memory_order_relaxed);
        g_activo[indice].store(nuevo, std::memory_order_relaxed);
        std::cerr << "[trucos] " << kIds[indice] << (nuevo ? " activo" : " desactivado") << std::endl;
    }

    void abrir(bool escCierraJuego)
    {
        (void)escCierraJuego;
        g_menuAbierto.store(true, std::memory_order_release);
        SetExitKey(KEY_NULL);
        g_menu.cursorOculto = IsCursorHidden();
        if (g_menu.cursorOculto)
            ShowCursor();
    }

    void cerrar(bool escCierraJuego, int tecla)
    {
        g_menuAbierto.store(false, std::memory_order_release);
        g_menu.teclaCierre = tecla;
        g_bloqueoTrasCerrar.store(tecla != 0, std::memory_order_release);
        if (escCierraJuego)
            SetExitKey(KEY_ESCAPE);
        if (g_menu.cursorOculto)
            HideCursor();
    }
}

// Instala los envoltorios de la vida (solo God of War) y lee el estado inicial de TOBIICHI_TRUCOS.
void gowTrucosInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99" || g_instalado.load())
        return;
    if (!runtime.hasFunction(kFijarVida) || !runtime.hasFunction(kRestarVida))
    {
        std::cerr << "[trucos] faltan las funciones de la vida; menú de trucos desactivado" << std::endl;
        return;
    }
    g_fijarVida = runtime.lookupFunction(kFijarVida);
    g_restarVida = runtime.lookupFunction(kRestarVida);
    runtime.replaceFunction(kFijarVida, &fijarVida);
    runtime.replaceFunction(kRestarVida, &restarVida);
    if (const char *lista = std::getenv("TOBIICHI_TRUCOS"))
    {
        std::string valor(lista);
        size_t inicio = 0;
        while (inicio <= valor.size())
        {
            const size_t fin = std::min(valor.find(',', inicio), valor.size());
            const std::string id = valor.substr(inicio, fin - inicio);
            for (int i = 0; i < kNumTrucos; ++i)
                if (id == kIds[i])
                    g_activo[i].store(true, std::memory_order_relaxed);
            inicio = fin + 1;
        }
    }
    g_instalado.store(true);
    std::string activos;
    for (int i = 0; i < kNumTrucos; ++i)
        if (g_activo[i].load())
            activos += std::string(activos.empty() ? "" : ",") + kIds[i];
    std::cerr << "[trucos] menú de trucos listo (F2); activos: " << (activos.empty() ? "ninguno" : activos) << std::endl;
}

// Hilo del EE, al empezar cada VBlank: valores que se mantienen mientras el truco está activo.
void gowTrucosVBlank(uint8_t *rdram)
{
    if (!rdram || !g_instalado.load(std::memory_order_relaxed))
        return;
    diagnostico(rdram);

    if (activo(MagiaInfinita))
    {
        const unsigned nivel = std::min<unsigned>(rdram[kEstado + 0x77u], 5u);
        const float maxima = leer<float>(rdram, kAjustes + 0x14u + 4u * nivel);
        if (std::isfinite(maxima) && maxima > 0.0f && leer<float>(rdram, kEstado + 0x5Cu) < maxima)
            escribir<float>(rdram, kEstado + 0x5Cu, maxima);
    }
    if (activo(FuriaInfinita) && leer<float>(rdram, kEstado + 0x60u) < 100.0f)
        escribir<float>(rdram, kEstado + 0x60u, 100.0f);
    if (activo(OrbesMaximos) && leer<uint16_t>(rdram, kEstado + 0x68u) != 60000u)
        escribir<uint16_t>(rdram, kEstado + 0x68u, 60000u);
    if (activo(MejorasMaximas))
    {
        for (uint32_t i = 0x78u; i <= 0x7Cu; ++i)
            rdram[kEstado + i] = std::max<uint8_t>(rdram[kEstado + i], 2u);
        rdram[kEstado + 0x7Du] = std::max<uint8_t>(rdram[kEstado + 0x7Du], 4u);
    }
    if (activo(TodosLosPoderes))
        escribir<uint16_t>(rdram, kEstado + 0x82u, static_cast<uint16_t>(leer<uint16_t>(rdram, kEstado + 0x82u) | 0x017Cu));

    const uint32_t jugador = kratos(rdram);
    const bool jugadorSeguro = jugador != 0u && kratosPlausible(rdram, jugador);
    if (activo(MedidoresMaximos))
    {
        rdram[kEstado + 0x76u] = std::max<uint8_t>(rdram[kEstado + 0x76u], 4u);
        rdram[kEstado + 0x77u] = std::max<uint8_t>(rdram[kEstado + 0x77u], 5u);
        if (jugadorSeguro)
        {
            const float maxima = vidaMaximaDeNivel(rdram, 4u);
            if (leer<float>(rdram, jugador + 0x17Cu) < maxima)
                escribir<float>(rdram, jugador + 0x17Cu, maxima);
        }
    }
    if (activo(Inmortal) && jugadorSeguro)
    {
        // Solo rellena si sigue vivo: no resucita a mitad de una muerte.
        const float vida = leer<float>(rdram, jugador + 0x178u), maxima = leer<float>(rdram, jugador + 0x17Cu);
        if (vida > 0.0f && vida < maxima)
            escribir<float>(rdram, jugador + 0x178u, maxima);
    }
    if (activo(Extras))
    {
        const uint32_t terminadas = leer<uint32_t>(rdram, kPartidasTerminadas);
        if ((terminadas & 0x1Fu) != 0x1Fu)
            escribir<uint32_t>(rdram, kPartidasTerminadas, terminadas | 0x1Fu);
        const uint32_t variables = leer<uint32_t>(rdram, kVariablesInterfaz) & kMascara;
        if (direccionValida(variables, 0x1B4u))
        {
            escribir<uint32_t>(rdram, variables + 0x1ACu, 3u);
            escribir<uint32_t>(rdram, variables + 0x1B0u, 1u);
        }
    }
}

// Envoltorio del mando (hilo del EE): con el menú abierto el juego no recibe nada. Al cerrarlo sigue sin recibir
// hasta que se suelta la tecla que lo cerró (Esc es el círculo con el teclado clásico).
bool gowTrucosEntradaBloqueada()
{
    if (g_menuAbierto.load(std::memory_order_acquire))
        return true;
    return g_bloqueoTrasCerrar.load(std::memory_order_acquire);
}

// Hilo principal, antes de dibujar: F2 abre y cierra; con el menú abierto, teclado, ratón y mando lo manejan.
void gowTrucosMenuEntrada(bool escCierraJuego)
{
    if (!g_instalado.load(std::memory_order_relaxed))
        return;
    if (g_bloqueoTrasCerrar.load(std::memory_order_relaxed) && (g_menu.teclaCierre == 0 || !IsKeyDown(g_menu.teclaCierre)) &&
        !IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        g_bloqueoTrasCerrar.store(false, std::memory_order_release);

    // Pruebas (capturas sin teclado): TOBIICHI_TRUCOS_ABRIR_EN=<segundos> abre el menú a esa hora.
    static double abrirEn = []
    {
        const char *valor = std::getenv("TOBIICHI_TRUCOS_ABRIR_EN");
        return valor ? std::atof(valor) : -1.0;
    }();
    const bool abierto = g_menuAbierto.load(std::memory_order_relaxed);
    if (!abierto)
    {
        const bool prueba = abrirEn >= 0.0 && GetTime() >= abrirEn;
        if (prueba)
            abrirEn = -1.0;
        if (IsKeyPressed(KEY_F2) || prueba)
            abrir(escCierraJuego);
        return;
    }
    if (IsKeyPressed(KEY_F2) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
    {
        cerrar(escCierraJuego, IsKeyPressed(KEY_F2) ? KEY_F2 : IsKeyPressed(KEY_ESCAPE) ? KEY_ESCAPE : KEY_BACKSPACE);
        return;
    }
    if (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    {
        cerrar(escCierraJuego, 0);
        g_bloqueoTrasCerrar.store(true, std::memory_order_release);
        return;
    }

    int &elegido = g_menu.elegido;
    const bool mando = IsGamepadAvailable(0);
    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP) || IsKeyPressed(KEY_W) ||
        (mando && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)))
        elegido = (elegido + kNumTrucos - 1) % kNumTrucos;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN) || IsKeyPressed(KEY_S) ||
        (mando && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)))
        elegido = (elegido + 1) % kNumTrucos;
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_LEFT) ||
        IsKeyPressed(KEY_RIGHT) || (mando && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)))
        alternar(elegido);

    const Geometria g = geometria();
    const Vector2 raton = GetMousePosition();
    const float filasY = g.y + g.cabecera;
    if (raton.x >= g.x && raton.x < g.x + g.w && raton.y >= filasY && raton.y < filasY + g.fila * static_cast<float>(kNumTrucos))
    {
        const int sobre = std::clamp(static_cast<int>((raton.y - filasY) / g.fila), 0, kNumTrucos - 1);
        const Vector2 delta = GetMouseDelta();
        if (delta.x != 0.0f || delta.y != 0.0f)
            elegido = sobre;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            elegido = sobre;
            alternar(sobre);
        }
    }
}

// Hilo principal, dentro de BeginDrawing.
void gowTrucosMenuDibujar()
{
    if (!g_menuAbierto.load(std::memory_order_relaxed))
        return;
    const Fuentes &f = fuentes();
    const Textos &t = textos();
    const Geometria g = geometria();
    const float s = g.escala;

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{6, 3, 2, 150});
    const Rectangle panel{g.x, g.y, g.w, g.h};
    DrawRectangleRec(panel, Color{20, 12, 9, 238});
    DrawRectangleGradientV(static_cast<int>(g.x), static_cast<int>(g.y), static_cast<int>(g.w), static_cast<int>(g.cabecera),
                           Color{90, 13, 9, 200}, Color{20, 12, 9, 0});
    DrawRectangleLinesEx(panel, std::max(1.0f, 1.5f * s), kBorde);
    DrawRectangle(static_cast<int>(g.x), static_cast<int>(g.y), static_cast<int>(g.w), std::max(2, static_cast<int>(3.0f * s)), kOro);

    const float margen = 28.0f * s;
    const float tamTitulo = 30.0f * s, tamSub = 15.0f * s;
    texto(f.negrita, t.titulo, g.x + margen, g.y + 22.0f * s, tamTitulo, kOroClaro);
    texto(f.normal, t.subtitulo, g.x + margen, g.y + 22.0f * s + tamTitulo + 6.0f * s, tamSub, kTextoTenue);
    const char *marca = "TOBIICHI";
    texto(f.negrita, marca, g.x + g.w - margen - ancho(f.negrita, marca, 14.0f * s), g.y + 30.0f * s, 14.0f * s, kOro);
    DrawLineEx(Vector2{g.x + margen, g.y + g.cabecera - 1.0f}, Vector2{g.x + g.w - margen, g.y + g.cabecera - 1.0f},
               std::max(1.0f, s), kBorde);

    const float tamNombre = 21.0f * s, tamDesc = 15.0f * s;
    const float interruptorW = 52.0f * s, interruptorH = 26.0f * s;
    for (int i = 0; i < kNumTrucos; ++i)
    {
        const float fy = g.y + g.cabecera + g.fila * static_cast<float>(i);
        if (fy + g.fila > g.y + g.h - g.pie + 1.0f)
            break;
        const bool encendido = g_activo[i].load(std::memory_order_relaxed);
        const bool sel = i == g_menu.elegido;
        if (sel)
        {
            DrawRectangleRec(Rectangle{g.x + 1.0f, fy, g.w - 2.0f, g.fila}, Color{58, 30, 18, 200});
            DrawRectangleRec(Rectangle{g.x + 1.0f, fy, std::max(3.0f, 4.0f * s), g.fila}, kOro);
        }
        const float textoX = g.x + margen;
        const float textoMax = g.w - margen * 2.0f - interruptorW - 20.0f * s;
        const float bloque = tamNombre + 6.0f * s + tamDesc;
        const float ty = fy + (g.fila - bloque) * 0.5f;
        texto(f.negrita, t.nombre[i], textoX, ty, tamNombre, encendido ? kOroClaro : (sel ? kTexto : kTextoSuave));
        const std::string desc = ajustar(f.normal, t.descripcion[i], tamDesc, textoMax);
        texto(f.normal, desc.c_str(), textoX, ty + tamNombre + 6.0f * s, tamDesc, kTextoTenue);

        const Rectangle pista{g.x + g.w - margen - interruptorW, fy + (g.fila - interruptorH) * 0.5f, interruptorW, interruptorH};
        DrawRectangleRounded(pista, 1.0f, 12, encendido ? Color{212, 168, 87, 255} : Color{45, 30, 22, 255});
        DrawRectangleRoundedLinesEx(pista, 1.0f, 12, std::max(1.0f, s), encendido ? kOroClaro : kBorde);
        const float radio = interruptorH * 0.5f - 3.0f * s;
        const float cx = encendido ? pista.x + pista.width - interruptorH * 0.5f : pista.x + interruptorH * 0.5f;
        DrawCircleV(Vector2{cx, pista.y + interruptorH * 0.5f}, radio, encendido ? Color{29, 15, 7, 255} : kTextoSuave);

        if (i + 1 < kNumTrucos)
            DrawLineEx(Vector2{g.x + margen, fy + g.fila}, Vector2{g.x + g.w - margen, fy + g.fila}, 1.0f, Color{61, 38, 25, 160});
    }

    const float pieY = g.y + g.h - g.pie;
    DrawLineEx(Vector2{g.x + margen, pieY}, Vector2{g.x + g.w - margen, pieY}, std::max(1.0f, s), kBorde);
    texto(f.normal, t.ayuda, g.x + margen, pieY + (g.pie - tamDesc) * 0.5f, tamDesc, kTextoSuave);
}
