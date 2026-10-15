// GOW-Port: iconos de botones según el dispositivo en God of War (SCUS-97399).
//
// Con un mando de PlayStation los iconos del juego (X, círculo, L1...) no cambian. Con teclado y ratón se dibuja la
// tecla asignada a esa acción (la del lanzador, TOBIICHI_TECLAS), y con cualquier otro mando, el botón del mando Xbox
// que da esa acción con el esquema activo (DMC5 por defecto). GOW_ICONOS=0 lo desactiva; GOW_ICONOS_ESTILO=teclado|
// xbox|original fuerza un estilo.
//
// Cómo dibuja el juego los iconos (ver docs/CONTROLES.md, "Iconos de botones"):
//   - Los menús, los textos con [XButton] y los avisos de los minijuegos son películas de su reproductor de Flash. La
//     película del HUD tiene símbolos con nombre ("XButton", "L1Button", "XButtonGreek", "UpButton"...): sprites con un
//     fondo común y una forma propia (el aspa, el círculo...). Las mismas formas se reutilizan en los menús.
//   - 0x149FA0(forma, ctx, id, matriz, cxform) dibuja una forma: a0 = su entrada (8 bytes) en la tabla de formas de la
//     película, a3 = matriz 4 x 4 (fila: escala x/y en [0]/[5], traslación en [12]/[13], en el espacio del escenario
//     de 640 x 480 a medio píxel: x = 320 + tx / 2, y = 240 - ty / 2).
// Aquí, cuando la forma es la propia de un botón, no se dibuja y se anota su posición; la ventana dibuja encima, en
// ese sitio y a resolución nativa, el icono del dispositivo con la letra de la casa (Cinzel, de la misma familia que
// la de los menús). El fondo común del juego queda debajo, tapado por el icono.
//
// Herramientas (solo locales):
//   GOW_ICONOS_DIAG=1                registra las películas encontradas y cada forma de botón que se sustituye.
//   GOW_ICONOS_OCULTAR="a,b,..."     (hex) no dibuja las formas con esa entrada (a0) o ese id (a2).
//   GOW_ICONOS_VOLCAR="t:carpeta"    a los t segundos guarda en PNG las texturas de Flash de la RAM (nodos
//                                    {0xC, 0x30024}: imagen T8/T4 subida como CT32 y su CLUT en el nodo siguiente).
//   GOW_ICONOS_TAMANO=f              factor del tamaño de los iconos (1 = el del fondo del botón del juego).
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "raylib.h"
#include "runtime/gs/gs_swizzle.h"

#include <algorithm>
#include <atomic>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <vector>

extern const unsigned char gowFuenteIconos[];     // gow_fuente_iconos.cpp (generado por CMake)
extern const size_t gowFuenteIconosTam;
int tobiichiCodigosAccion(const char *accion, int *codigos, int max); // ps2_pad.cpp
int tobiichiBotonMandoAccion(const char *accion);                      // ps2_pad.cpp
extern "C" const char *glfwGetKeyName(int key, int scancode);

namespace
{
    constexpr uint32_t kDibujarForma = 0x00149FA0u;

    PS2Runtime::RecompiledFunction g_dibujarForma = nullptr;
    bool g_diag = false, g_activo = false;
    std::set<uint32_t> g_ocultar;
    const auto g_arranque = std::chrono::steady_clock::now();

    double segundos() { return std::chrono::duration<double>(std::chrono::steady_clock::now() - g_arranque).count(); }

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

    bool valida(uint32_t a, uint32_t n) { return a >= 0x100000u && a + n <= PS2_RAM_SIZE; }

    // ---- Botones ----
    enum Boton : uint8_t
    {
        BCruz, BCirculo, BCuadrado, BTriangulo, BL1, BR1, BL2, BR2, BL3, BR3, BStart, BSelect,
        BArriba, BAbajo, BIzquierda, BDerecha, BCruceta, BStickIzq, NumBotones
    };
    constexpr const char *kAccion[NumBotones] = {"cross", "circle", "square", "triangle", "l1", "r1", "l2", "r2", "l3", "r3",
                                                 "start", "select", "up", "down", "left", "right", "up", "li_arriba"};
    enum Variante : uint8_t
    {
        VNormal, // icono de los menús y del texto
        VGriego, // aviso grande de los minijuegos (borde griego)
    };
    struct Simbolo
    {
        const char *nombre;
        Boton boton;
        Variante variante;
    };
    // GOW-Port: "R2ButtonStatic" (el R2 fijo del medidor de la Furia de los Dioses en el HUD) se deja como en el juego: es
    // decorativo y grande, y con el teclado salía un "CTRL" enorme encima del medidor.
    const Simbolo kSimbolos[] = {
        {"XButton", BCruz, VNormal}, {"CircleButton", BCirculo, VNormal}, {"SquareButton", BCuadrado, VNormal},
        {"TriangleButton", BTriangulo, VNormal}, {"L1Button", BL1, VNormal}, {"R1Button", BR1, VNormal},
        {"L2Button", BL2, VNormal}, {"R2Button", BR2, VNormal}, {"L3", BL3, VNormal},
        {"R3", BR3, VNormal}, {"StartButton", BStart, VNormal}, {"SelectButton", BSelect, VNormal},
        {"Joystick", BStickIzq, VNormal}, {"UpButton", BArriba, VNormal}, {"DownButton", BAbajo, VNormal},
        {"LeftButton", BIzquierda, VNormal}, {"RightButton", BDerecha, VNormal}, {"DpadButton", BCruceta, VNormal},
        {"XButtonGreek", BCruz, VGriego}, {"CircleButtonGreek", BCirculo, VGriego},
        {"SquareButtonGreek", BCuadrado, VGriego}, {"TriangleButtonGreek", BTriangulo, VGriego},
        {"360CW", BStickIzq, VGriego}, {"360CCW", BStickIzq, VGriego}, {"Up180CW", BStickIzq, VGriego},
        {"Up180CCW", BStickIzq, VGriego}, {"Down180CW", BStickIzq, VGriego}, {"Down180CCW", BStickIzq, VGriego},
        {"WiggleBackForth", BStickIzq, VGriego}, {"WiggleStick", BStickIzq, VGriego}, {"R2ButtonPress", BR2, VGriego}};
    constexpr int kNumSimbolos = int(sizeof(kSimbolos) / sizeof(kSimbolos[0]));

    // ---- Películas de Flash ----
    // Cabecera: +0 0x21, +4 0x1E000004, +8 0x25803200 (escenario de 640 x 480 en twips), +0x0C/+0x10 caracteres
    // (u32: índice << 16 | tipo; 1 forma, 7 sprite), +0x14/+0x18 formas (8 bytes: u16 malla, u16 rellenos, puntero),
    // +0x3C/+0x40 sprites (24 bytes: +0x02 número de listas, +0x10 puntero a las listas), +0x58/+0x5C cadenas.
    // Listas de un sprite: {u16 tipo, u16 n, puntero} a n registros de 10 bytes {profundidad, carácter, matriz, ?,
    // cxform}. Los nombres: en las listas de colocación, u16 carácter, matriz, cxform y el nombre (u16 a +6).
    struct Pelicula
    {
        uint32_t cabecera = 0u, caracteres = 0u, numCaracteres = 0u, formas = 0u, numFormas = 0u, sprites = 0u,
                 numSprites = 0u, cadenas = 0u, numCadenas = 0u;
        std::map<uint32_t, std::pair<Boton, Variante>> formasBoton; // entrada de forma -> botón
        // Fuentes (+0x1C/+0x20; 40 bytes): +0x14 formas de los glifos (8 bytes), +0x1C código -> glifo (u16, 256).
        struct Fuente
        {
            uint32_t glifos = 0u, numGlifos = 0u;
            std::vector<char> letra; // glifo -> carácter
        };
        std::vector<Fuente> fuentes;
    };
    std::vector<Pelicula> g_peliculas;
    std::set<uint32_t> g_formasDesconocidas;
    std::chrono::steady_clock::time_point g_ultimoEscaneo{};

    // Formas (entradas) que cuelgan de un carácter, recorriendo sprites anidados.
    void formasDe(const uint8_t *rdram, const Pelicula &p, uint32_t c, std::set<uint32_t> &salida, std::set<uint32_t> &vistos, int prof)
    {
        if (c >= p.numCaracteres || prof > 8 || !vistos.insert(c).second)
            return;
        const uint32_t t = leer32(rdram, p.caracteres + 4u * c), tipo = t & 0xFFFFu, ix = t >> 16;
        if (tipo == 1u && ix < p.numFormas)
        {
            salida.insert(p.formas + 8u * ix);
            return;
        }
        if (tipo != 7u || ix >= p.numSprites)
            return;
        const uint32_t e = p.sprites + 24u * ix;
        const uint32_t listas = leer32(rdram, e) >> 16, ptr = leer32(rdram, e + 16u);
        for (uint32_t k = 0; k < std::min(listas, 512u) && valida(ptr + 8u * k, 8u); ++k)
        {
            const uint32_t n = leer32(rdram, ptr + 8u * k) >> 16, regs = leer32(rdram, ptr + 8u * k + 4u);
            for (uint32_t r = 0; r < std::min(n, 256u) && valida(regs + 10u * r, 10u); ++r)
            {
                uint16_t hijo = 0;
                std::memcpy(&hijo, rdram + regs + 10u * r + 2u, 2);
                formasDe(rdram, p, hijo, salida, vistos, prof + 1);
            }
        }
    }

    void escanearPeliculas(const uint8_t *rdram)
    {
        const auto inicio = std::chrono::steady_clock::now();
        g_peliculas.clear();
        for (uint32_t h = 0x100000u; h + 0x60u < PS2_RAM_SIZE; h += 4u)
        {
            if (leer32(rdram, h + 8u) != 0x25803200u || leer32(rdram, h + 4u) != 0x1E000004u || leer32(rdram, h) != 0x21u)
                continue;
            Pelicula p;
            p.cabecera = h;
            p.numCaracteres = leer32(rdram, h + 0x0Cu);
            p.caracteres = leer32(rdram, h + 0x10u);
            p.numFormas = leer32(rdram, h + 0x14u);
            p.formas = leer32(rdram, h + 0x18u);
            p.numSprites = leer32(rdram, h + 0x3Cu);
            p.sprites = leer32(rdram, h + 0x40u);
            p.numCadenas = leer32(rdram, h + 0x58u);
            p.cadenas = leer32(rdram, h + 0x5Cu);
            if (p.numCaracteres == 0u || p.numCaracteres > 8192u || !valida(p.caracteres, p.numCaracteres * 4u) ||
                !valida(p.formas, p.numFormas * 8u) || !valida(p.sprites, p.numSprites * 24u) || !valida(p.cadenas, p.numCadenas))
                continue;
            // Sprites con nombre de botón y sus formas.
            std::map<uint32_t, std::vector<std::pair<size_t, int>>> candidatos; // forma -> (formas del sprite, símbolo)
            // Registros de colocación con nombre de botón: {u16 carácter, matriz, cxform, nombre, profundidad}. Los
            // buenos van seguidos (la línea de tiempo principal pone todos los botones juntos); un acierto suelto, sin
            // otro nombre de botón a menos de 64 bytes, es una coincidencia de bytes y se descarta.
            struct Acierto
            {
                uint32_t direccion, caracter;
                int simbolo;
            };
            std::vector<Acierto> aciertos;
            const uint32_t numMatrices = leer32(rdram, h + 0x48u);
            const uint32_t desde = std::min({p.caracteres, p.formas, p.sprites});
            for (uint32_t a = desde; a + 10u <= p.cadenas; a += 2u)
            {
                uint16_t reg[5];
                std::memcpy(reg, rdram + a, 10);
                const uint32_t c = reg[0], nombre = reg[3];
                if (c >= p.numCaracteres || reg[1] >= numMatrices || reg[4] >= 0x1000u || nombre >= p.numCadenas ||
                    (nombre && rdram[p.cadenas + nombre - 1u] != 0))
                    continue;
                if ((leer32(rdram, p.caracteres + 4u * c) & 0xFFFFu) != 7u)
                    continue;
                const char *n = reinterpret_cast<const char *>(rdram + p.cadenas + nombre);
                for (int s = 0; s < kNumSimbolos; ++s)
                    if (std::strncmp(n, kSimbolos[s].nombre, 24) == 0 && n[std::strlen(kSimbolos[s].nombre)] == 0)
                        aciertos.push_back({a, c, s});
            }
            std::set<std::pair<int, uint32_t>> hechos;
            for (const Acierto &x : aciertos)
            {
                bool vecino = false;
                for (const Acierto &y : aciertos)
                    vecino |= y.simbolo != x.simbolo && (y.direccion > x.direccion ? y.direccion - x.direccion : x.direccion - y.direccion) < 64u;
                if (!vecino || !hechos.insert({x.simbolo, x.caracter}).second)
                    continue;
                std::set<uint32_t> formas, vistos;
                formasDe(rdram, p, x.caracter, formas, vistos, 0);
                for (uint32_t f : formas)
                    candidatos[f].push_back({formas.size(), x.simbolo});
            }
            // Cada forma es del botón del sprite más pequeño que la usa; si dos botones distintos empatan (el fondo
            // común), no es de ninguno.
            for (auto &[f, lista] : candidatos)
            {
                std::sort(lista.begin(), lista.end());
                bool unico = true;
                for (const auto &[tam, s] : lista)
                    if (tam == lista[0].first && (kSimbolos[s].boton != kSimbolos[lista[0].second].boton ||
                                                  kSimbolos[s].variante != kSimbolos[lista[0].second].variante))
                        unico = false;
                if (unico)
                    p.formasBoton[f] = {kSimbolos[lista[0].second].boton, kSimbolos[lista[0].second].variante};
            }
            const uint32_t numFuentes = leer32(rdram, h + 0x1Cu), fuentes = leer32(rdram, h + 0x20u);
            for (uint32_t k = 0; k < std::min(numFuentes, 16u) && valida(fuentes + 40u * k, 40u); ++k)
            {
                const uint32_t e = fuentes + 40u * k;
                Pelicula::Fuente fu;
                fu.numGlifos = leer32(rdram, e) & 0xFFFFu;
                fu.glifos = leer32(rdram, e + 0x14u);
                const uint32_t mapa = leer32(rdram, e + 0x1Cu);
                if (fu.numGlifos == 0u || fu.numGlifos > 512u || !valida(fu.glifos, 8u * fu.numGlifos) || !valida(mapa, 512u))
                    continue;
                fu.letra.assign(fu.numGlifos, 0);
                for (uint32_t c = 32; c < 128; ++c)
                {
                    uint16_t g = 0;
                    std::memcpy(&g, rdram + mapa + 2u * c, 2);
                    if (g < fu.numGlifos)
                        fu.letra[g] = char(std::toupper(int(c)));
                }
                p.fuentes.push_back(std::move(fu));
            }
            if (g_diag)
                std::fprintf(stderr, "[gow-iconos] película %08X: %u caracteres, %u formas, %zu formas de botón\n", h,
                             p.numCaracteres, p.numFormas, p.formasBoton.size());
            g_peliculas.push_back(std::move(p));
        }
        if (g_diag)
            std::fprintf(stderr, "[gow-iconos] búsqueda de películas: %zu en %.1f ms\n", g_peliculas.size(),
                         std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - inicio).count());
    }

    // Botón de una forma, o falso. Si la forma no es de ninguna película conocida vuelve a buscarlas (como mucho una
    // vez cada 2 s y solo por una forma que no se había visto: el juego carga y descarga películas; las formas que
    // siguen sin película después de buscar no vuelven a provocar búsquedas).
    bool botonDeForma(const uint8_t *rdram, uint32_t entrada, Boton &b, Variante &v)
    {
        for (int intento = 0; intento < 2; ++intento)
        {
            for (const Pelicula &p : g_peliculas)
                if (entrada >= p.formas && entrada < p.formas + 8u * p.numFormas)
                {
                    if (leer32(rdram, p.cabecera + 8u) != 0x25803200u)
                        break;
                    const auto it = p.formasBoton.find(entrada);
                    if (it == p.formasBoton.end())
                        return false;
                    b = it->second.first;
                    v = it->second.second;
                    return true;
                }
            const auto ahora = std::chrono::steady_clock::now();
            if (intento == 0 && g_formasDesconocidas.insert(entrada).second && ahora - g_ultimoEscaneo > std::chrono::seconds(2))
            {
                g_ultimoEscaneo = ahora;
                escanearPeliculas(rdram);
            }
            else
                break;
        }
        return false;
    }

    // ---- Botones de cara por su color ----
    // Los botones de cara (aspa, círculo, cuadrado, triángulo) son un fondo y encima, en el mismo sitio, la forma del
    // símbolo, de un solo color. El color es el mismo en todas las películas (también en las copias sin nombre de los
    // menús, como el "X = Select" del título): eso los reconoce. El fondo dice la variante: el disco oscuro de los
    // menús (dos rellenos, el primero 0x191919) o el marco claro de los minijuegos (un relleno blanco).
    struct Forma
    {
        uint32_t malla = 0u, rellenos = 0u, color0 = 0u, color1 = 0u;
    };

    Forma leerForma(const uint8_t *rdram, uint32_t entrada)
    {
        Forma f;
        if (!valida(entrada, 8u))
            return f;
        const uint32_t w = leer32(rdram, entrada), p = leer32(rdram, entrada + 4u);
        f.malla = w & 0xFFFFu;
        f.rellenos = w >> 16;
        if (f.rellenos >= 1u && valida(p, 16u))
        {
            f.color0 = leer32(rdram, p);
            f.color1 = f.rellenos >= 2u ? leer32(rdram, p + 8u) : 0u;
        }
        return f;
    }

    bool colorDeBoton(uint32_t color, Boton &b)
    {
        switch (color)
        {
        case 0xFF9999FFu: b = BCruz; return true;
        case 0xFFCC6400u: case 0xFFCC4B00u: b = BCirculo; return true;
        case 0xFFCC3C28u: case 0xFFFF6699u: b = BCuadrado; return true;
        case 0xFF009955u: b = BTriangulo; return true;
        default: return false;
        }
    }

    // Caja de la malla de una forma, en unidades locales. La malla es una cadena DMA para VU1: desde ctx (a1 de
    // 0x149FA0), *(*(ctx + 0xCE4) + 0xE4) es la base de las mallas, base + 0x50 una tabla de desplazamientos por número
    // de malla; en la malla, etiquetas DMA "ref" (id 3: qwc y dirección) hasta "ret" (id 6), y en sus datos, UNPACK
    // V4-16 (comando 0x6D) con los vértices: x, y en 16 bits con signo (cada vértice ocupa 8 bytes).
    struct Caja
    {
        bool valida = false;
        float x0 = 0.0f, y0 = 0.0f, x1 = 0.0f, y1 = 0.0f;
    };
    std::map<std::pair<uint32_t, uint32_t>, Caja> g_cajas;

    Caja cajaMalla(const uint8_t *rdram, uint32_t ctx, uint32_t malla)
    {
        const auto clave = std::make_pair(ctx, malla);
        if (const auto it = g_cajas.find(clave); it != g_cajas.end())
            return it->second;
        Caja c;
        const uint32_t p1 = valida(ctx + 0xCE4u, 4u) ? leer32(rdram, ctx + 0xCE4u) : 0u;
        const uint32_t p2 = valida(p1 + 0xE4u, 4u) ? leer32(rdram, p1 + 0xE4u) : 0u;
        const uint32_t base = valida(p2, 4u) ? leer32(rdram, p2) : 0u;
        if (valida(base + 0x50u + 4u * malla, 4u))
        {
            const uint32_t m = base + leer32(rdram, base + 0x50u + 4u * malla);
            float x0 = 1e9f, y0 = 1e9f, x1 = -1e9f, y1 = -1e9f;
            for (uint32_t q = (m + 15u) & ~15u; q < m + 0x400u && valida(q, 16u); q += 16u)
            {
                const uint32_t etiqueta = leer32(rdram, q), id = (etiqueta >> 28) & 7u;
                if (id == 6u || id == 7u)
                    break;
                if (id != 3u)
                    continue;
                const uint32_t qwc = etiqueta & 0xFFFFu, datos = leer32(rdram, q + 4u);
                if (!valida(datos, qwc * 16u) || qwc > 4096u)
                    continue;
                for (uint32_t w = 0; w < qwc * 4u;)
                {
                    const uint32_t vif = leer32(rdram, datos + 4u * w);
                    const uint32_t cmd = (vif >> 24) & 0x7Fu, num = (vif >> 16) & 0xFFu;
                    ++w;
                    if ((cmd & 0x60u) == 0x60u)
                    {
                        const uint32_t vn = (cmd >> 2) & 3u, vl = cmd & 3u;
                        const uint32_t bytes = ((32u >> vl) * (vn + 1u) * (num ? num : 256u) + 31u) / 32u;
                        if (cmd == 0x6Du)
                            for (uint32_t k = 0; k < (num ? num : 256u) && w + 2u * k < qwc * 4u; ++k)
                            {
                                const uint32_t xy = leer32(rdram, datos + 4u * (w + 2u * k));
                                const float x = float(int16_t(xy & 0xFFFFu)), y = float(int16_t(xy >> 16));
                                x0 = std::min(x0, x);
                                x1 = std::max(x1, x);
                                y0 = std::min(y0, y);
                                y1 = std::max(y1, y);
                            }
                        w += bytes;
                    }
                }
            }
            if (x1 >= x0 && y1 >= y0)
                c = {true, x0, y0, x1, y1};
        }
        g_cajas[clave] = c;
        return c;
    }

    struct Anterior
    {
        uint32_t entrada = 0u;
        float tx = 0.0f, ty = 0.0f, m0 = 0.0f, m1 = 0.0f, m4 = 0.0f, m5 = 0.0f;
        Caja caja;
        bool fondoMenu = false, fondoGriego = false;
    } g_anterior;

    // Botones con rótulo (L1, R2, START...): un fondo propio (rellenos 0x232323 y blanco) y encima el rótulo con los
    // glifos de la fuente. Se juntan las letras que caen dentro del fondo y, al llegar otra forma, se resuelve el botón.
    struct Rotulo
    {
        bool abierto = false;
        Anterior fondo;
        float cx = 0.0f, cy = 0.0f, radio = 0.0f; // centro y radio del fondo en el espacio de la matriz
        std::vector<std::pair<float, char>> letras;
        float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
    } g_rotulo;

    // Formas con un botón pintado dentro de un dibujo del menú (las pestañas L1/R1 de la pausa de la película del HUD:
    // 936 caracteres, 220 formas). Centro y radio del botón en fracciones del radio de la caja de la forma.
    struct Especial
    {
        uint32_t numCaracteres, numFormas, indice;
        Boton boton;
        float dx, dy, radio;
    };
    constexpr Especial kEspeciales[] = {
        {936u, 220u, 110u, BL1, 0.40f, 0.12f, 0.42f},
        {936u, 220u, 109u, BR1, -0.33f, 0.12f, 0.42f},
    };

    const Especial *especial(uint32_t entrada)
    {
        for (const Pelicula &p : g_peliculas)
            if (entrada >= p.formas && entrada < p.formas + 8u * p.numFormas)
                for (const Especial &e : kEspeciales)
                    if (p.numCaracteres == e.numCaracteres && p.numFormas == e.numFormas && entrada == p.formas + 8u * e.indice)
                        return &e;
        return nullptr;
    }

    // Carácter de una forma si es el glifo de una fuente de alguna película (0 si no).
    char letraDeGlifo(uint32_t entrada)
    {
        for (const Pelicula &p : g_peliculas)
            for (const Pelicula::Fuente &f : p.fuentes)
                if (entrada >= f.glifos && entrada < f.glifos + 8u * f.numGlifos && (entrada - f.glifos) % 8u == 0u)
                    return f.letra[(entrada - f.glifos) / 8u];
        return 0;
    }

    bool rotuloDeBoton(const std::string &t, Boton &b)
    {
        static const std::pair<const char *, Boton> kRotulos[] = {
            {"L1", BL1}, {"R1", BR1}, {"L2", BL2}, {"R2", BR2}, {"L3", BL3}, {"R3", BR3}, {"START", BStart}, {"SELECT", BSelect}};
        for (const auto &[r, x] : kRotulos)
            if (t == r)
            {
                b = x;
                return true;
            }
        return false;
    }

    // ---- Iconos anotados (hilo del EE) y publicados (hilo principal) ----
    struct Icono
    {
        Boton boton;
        Variante variante;
        float x, y;   // centro, en píxeles del escenario de 640 x 480
        float escala; // radio en unidades del escenario a medio píxel (radio local * escala de la matriz)
        float r, g, b, a; // multiplicadores del cxform (oscurecido y transparencia de los menús)
    };
    std::mutex g_mutex;
    // GOW-Port: modo panorámico del propio juego (0x29CC90 = 1; los overrides de Waffle y TOBIICHI_PANORAMICO lo
    // activan). En ese modo el reproductor de Flash estira el escenario en vertical, alrededor del centro, por el aspecto
    // del juego / (4/3): 4/3 con 16:9, medido en los menús de pausa y de título (error < 4 píxeles a 922 x 518).
    std::atomic<float> g_estiramientoVertical{1.0f};
    std::vector<Icono> g_construyendo, g_publicados;
    std::chrono::steady_clock::time_point g_ultimoAnotado{}, g_publicadoEn{};

    // Con g_mutex: los iconos de un cuadro del EE llegan seguidos; más de 8 ms después de uno empieza otro cuadro.
    void cerrarCuadro(std::chrono::steady_clock::time_point ahora)
    {
        if (ahora - g_ultimoAnotado > std::chrono::milliseconds(8) && !g_construyendo.empty())
        {
            g_publicados.swap(g_construyendo);
            g_construyendo.clear();
            g_publicadoEn = g_ultimoAnotado;
        }
    }

    void anotar(const Icono &icono)
    {
        const auto ahora = std::chrono::steady_clock::now();
        std::lock_guard<std::mutex> lock(g_mutex);
        cerrarCuadro(ahora);
        g_ultimoAnotado = ahora;
        for (const Icono &o : g_construyendo) // mismo botón en el mismo sitio (las dos formas del cuadrado...)
            if (o.boton == icono.boton && std::fabs(o.x - icono.x) < 4.0f && std::fabs(o.y - icono.y) < 4.0f)
                return;
        g_construyendo.push_back(icono);
    }

    // Multiplicadores del cxform (8.8): u16 r, g, b, a en las dos primeras palabras.
    void leerCxform(const uint8_t *rdram, uint32_t cx, float &r, float &g, float &b, float &a)
    {
        r = g = b = a = 1.0f;
        if (!valida(cx, 8u))
            return;
        const uint32_t w0 = leer32(rdram, cx), w1 = leer32(rdram, cx + 4u);
        r = std::clamp(float(w0 & 0xFFFFu) / 256.0f, 0.0f, 1.0f);
        g = std::clamp(float(w0 >> 16) / 256.0f, 0.0f, 1.0f);
        b = std::clamp(float(w1 & 0xFFFFu) / 256.0f, 0.0f, 1.0f);
        a = std::clamp(float(w1 >> 16) / 256.0f, 0.0f, 1.0f);
    }

    // Centro (espacio de la matriz) y radio de la caja de una forma colocada.
    void centroYRadio(const Anterior &f, float &cx, float &cy, float &radio)
    {
        const float ox = f.caja.valida ? (f.caja.x0 + f.caja.x1) * 0.5f : 0.0f, oy = f.caja.valida ? (f.caja.y0 + f.caja.y1) * 0.5f : 0.0f;
        cx = f.m0 * ox + f.m4 * oy + f.tx;
        cy = f.m1 * ox + f.m5 * oy + f.ty;
        radio = (f.caja.valida ? std::max(f.caja.x1 - f.caja.x0, f.caja.y1 - f.caja.y0) * 0.5f : 540.0f) * std::hypot(f.m0, f.m1);
    }

    void cerrarRotulo()
    {
        if (!g_rotulo.abierto)
            return;
        g_rotulo.abierto = false;
        std::sort(g_rotulo.letras.begin(), g_rotulo.letras.end());
        // Cada glifo puede dibujarse dos veces (contorno y relleno) en el mismo sitio: se cuenta una.
        std::string t;
        float ultimaX = -1e9f;
        for (const auto &[x, c] : g_rotulo.letras)
        {
            if (c != ' ' && !(std::fabs(x - ultimaX) < 1.0f && !t.empty() && t.back() == c))
                t += c;
            ultimaX = x;
        }
        Boton b;
        if (g_diag && !t.empty())
        {
            static std::set<std::string> vistos;
            if (vistos.insert(t).second)
                std::fprintf(stderr, "[gow-iconos] rótulo '%s'\n", t.c_str());
        }
        if (rotuloDeBoton(t, b))
            anotar(Icono{b, VNormal, 320.0f + g_rotulo.cx * 0.5f, 240.0f - g_rotulo.cy * 0.5f, g_rotulo.radio, g_rotulo.r, g_rotulo.g,
                         g_rotulo.b, g_rotulo.a});
    }

    void dibujarForma(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != kDibujarForma)
        {
            g_dibujarForma(rdram, ctx, runtime);
            return;
        }
        {
            // Estiramiento vertical del escenario: aspecto del juego (0x32F1B0) / (4/3); 1 sin el modo panorámico.
            float aspecto = 4.0f / 3.0f;
            std::memcpy(&aspecto, rdram + 0x32F1B0u, sizeof(aspecto));
            const bool ancho = rdram[0x29CC90u] == 1u && aspecto > 1.0f && aspecto < 4.0f;
            g_estiramientoVertical.store(ancho ? aspecto * 0.75f : 1.0f, std::memory_order_relaxed);
        }
        const uint32_t entrada = GPR_U32(ctx, 4), m = GPR_U32(ctx, 7);
        if (!g_ocultar.empty() && (g_ocultar.count(entrada) || g_ocultar.count(GPR_U32(ctx, 6))))
        {
            ctx->pc = GPR_U32(ctx, 31);
            return;
        }
        if (!g_activo || !valida(m, 64u) || !valida(entrada, 8u))
        {
            g_dibujarForma(rdram, ctx, runtime);
            return;
        }
        Anterior actual;
        actual.entrada = entrada;
        actual.m0 = leerF(rdram, m);
        actual.m1 = leerF(rdram, m + 4u);
        actual.m4 = leerF(rdram, m + 16u);
        actual.m5 = leerF(rdram, m + 20u);
        actual.tx = leerF(rdram, m + 48u);
        actual.ty = leerF(rdram, m + 52u);
        const Forma f = leerForma(rdram, entrada);
        actual.caja = cajaMalla(rdram, GPR_U32(ctx, 5), f.malla);
        float cx = 0.0f, cy = 0.0f, radio = 0.0f;
        centroYRadio(actual, cx, cy, radio);
        if (g_diag)
        {
            static std::set<uint32_t> vistas; // cada forma, la primera vez
            if (vistas.insert(entrada).second && vistas.size() < 3000)
                std::fprintf(stderr, "[gow-iconos] forma %08X malla=%u n=%u color=%08X,%08X centro %.1f,%.1f radio %.1f ra=%06X\n", entrada,
                             f.malla, f.rellenos, f.color0, f.color1, 320.0f + cx * 0.5f, 240.0f - cy * 0.5f, radio * 0.5f, GPR_U32(ctx, 31));
        }

        // Rótulo abierto: las letras dentro del fondo se juntan (se dibujan: el icono las tapa); otra forma lo cierra.
        if (g_rotulo.abierto)
        {
            const char letra = letraDeGlifo(entrada);
            if (letra && std::hypot(cx - g_rotulo.cx, cy - g_rotulo.cy) < g_rotulo.radio * 1.2f && g_rotulo.letras.size() < 8u)
            {
                g_rotulo.letras.push_back({cx, letra});
                g_dibujarForma(rdram, ctx, runtime);
                return;
            }
            cerrarRotulo();
        }

        // Pestañas L1/R1 de la pausa: el dibujo se queda y el icono tapa el botón pintado.
        if (const Especial *e = especial(entrada))
        {
            Icono i{e->boton, VNormal, 320.0f + (cx + e->dx * radio) * 0.5f, 240.0f - (cy + e->dy * radio) * 0.5f, radio * e->radio * 1.0f,
                    1.0f, 1.0f, 1.0f, 1.0f};
            leerCxform(rdram, GPR_U32(ctx, 8), i.r, i.g, i.b, i.a);
            anotar(i);
        }

        // Botón de cara: un solo relleno con el color de un símbolo, dentro del fondo dibujado justo antes.
        Boton b = BCruz;
        Variante v = VNormal;
        bool esBoton = false;
        Anterior fondo = g_anterior;
        float fx = 0.0f, fy = 0.0f, fr = 0.0f;
        centroYRadio(fondo, fx, fy, fr);
        const bool dentro = std::hypot(cx - fx, cy - fy) < std::max(6.0f, fr);
        if (f.rellenos == 1u && dentro && (fondo.fondoMenu || fondo.fondoGriego) && colorDeBoton(f.color0, b))
        {
            v = fondo.fondoGriego ? VGriego : VNormal;
            esBoton = true;
        }
        else if (botonDeForma(rdram, entrada, b, v) && b != BCruz && b != BCirculo && b != BCuadrado && b != BTriangulo)
        {
            esBoton = true;
            if (!dentro)
                fondo = actual; // botón por nombre sin fondo justo antes: su propia caja
        }
        actual.fondoMenu = f.rellenos == 2u && (f.color0 & 0x00FFFFFFu) == 0x191919u && f.color1 == 0xFFFFFFFFu;
        actual.fondoGriego = f.rellenos == 1u && f.color0 == 0xFFFFFFFFu;
        g_anterior = actual;

        // Fondo de un botón con rótulo (L1, R2, START...): abre el rótulo.
        if (f.rellenos >= 2u && (f.color0 & 0x00FFFFFFu) == 0x232323u && f.color1 == 0xFFFFFFFFu)
        {
            g_rotulo = Rotulo{};
            g_rotulo.abierto = true;
            g_rotulo.cx = cx;
            g_rotulo.cy = cy;
            g_rotulo.radio = radio;
            leerCxform(rdram, GPR_U32(ctx, 8), g_rotulo.r, g_rotulo.g, g_rotulo.b, g_rotulo.a);
        }

        if (!esBoton)
        {
            g_dibujarForma(rdram, ctx, runtime);
            return;
        }
        // Centro y tamaño del icono: los de la caja del fondo.
        centroYRadio(fondo, fx, fy, fr);
        Icono i{b, v, 320.0f + fx * 0.5f, 240.0f - fy * 0.5f, fr, 1.0f, 1.0f, 1.0f, 1.0f};
        leerCxform(rdram, GPR_U32(ctx, 8), i.r, i.g, i.b, i.a);
        if (g_diag)
        {
            static std::map<uint32_t, int> vistos;
            if (vistos[entrada]++ % 60 == 0)
                std::fprintf(stderr, "[gow-iconos] t=%.2f %s (%d) en %.1f,%.1f radio %.1f forma %08X alfa %.2f\n", segundos(), kAccion[b], int(v),
                             i.x, i.y, i.escala * 0.5f, entrada, i.a);
        }
        anotar(i);
        ctx->pc = GPR_U32(ctx, 31); // la forma del juego no se dibuja
    }

    // ---- Texturas de Flash (herramienta GOW_ICONOS_VOLCAR) ----
    struct TexturaFlash
    {
        uint32_t psm = 0u, tw = 0u, th = 0u, bw = 1u, subidaAncho = 0u, datos = 0u, datosClut = 0u, qwords = 0u;
    };

    bool leerTextura(const uint8_t *rdram, uint32_t nodo, TexturaFlash &t)
    {
        t.psm = leer32(rdram, nodo + 0x20u);
        if (t.psm != 0x13u && t.psm != 0x14u)
            return false;
        t.subidaAncho = leer32(rdram, nodo + 0x10u) & 0xFFFFu;
        const uint32_t formato = leer32(rdram, nodo + 0x28u);
        t.tw = formato & 0xFFu;
        t.th = (formato >> 8) & 0xFFu;
        t.bw = std::max<uint32_t>(1u, leer32(rdram, nodo + 0x2Cu) & 0xFFFFu);
        t.datos = leer32(rdram, nodo + 0x38u);
        const uint32_t sig = leer32(rdram, nodo + 8u), clut = sig >= 8u ? sig - 8u : 0u;
        if (t.tw > 10u || t.th > 10u || !valida(clut, 0x58u) || leer32(rdram, clut) != 0xCu || leer32(rdram, clut + 0x20u) != 0u)
            return false;
        t.datosClut = leer32(rdram, clut + 0x38u);
        if (!valida(t.datos, 16u) || !valida(t.datosClut, 16u + 1024u) || ((leer32(rdram, t.datos + 4u) >> 26) & 3u) != 2u)
            return false;
        t.qwords = leer32(rdram, t.datos) & 0x7FFFu;
        return t.qwords != 0u && valida(t.datos + 16u, t.qwords * 16u);
    }

    void volcarTexturas(const uint8_t *rdram, const std::string &carpeta)
    {
        std::filesystem::create_directories(carpeta);
        static std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
        size_t n = 0;
        for (uint32_t a = 0x100000u; a + 0x58u < PS2_RAM_SIZE; a += 8u)
        {
            TexturaFlash t;
            if (leer32(rdram, a) != 0xCu || leer32(rdram, a + 4u) != 0x30024u || !leerTextura(rdram, a, t))
                continue;
            // La subida es CT32 (subidaAncho de ancho, DBW = bw) y la textura se lee como T8/T4 (TBW = bw).
            std::fill(vram.begin(), vram.end(), 0u);
            const GSSwizzle::Format &ct32 = GSSwizzle::GetFormat(0x00u), &f = GSSwizzle::GetFormat(t.psm);
            const uint32_t sw = std::max<uint32_t>(1u, t.subidaAncho);
            for (uint32_t k = 0; k < t.qwords * 4u; ++k)
            {
                const auto loc = GSSwizzle::Locate(ct32, 0u, t.bw, k % sw, k / sw);
                GSSwizzle::StoreAt(ct32, vram.data() + loc.byte, loc.shift, leer32(rdram, t.datos + 16u + 4u * k));
            }
            const uint32_t w = 1u << t.tw, h = 1u << t.th;
            std::vector<uint32_t> px(size_t(w) * h);
            for (uint32_t y = 0; y < h; ++y)
                for (uint32_t x = 0; x < w; ++x)
                {
                    const auto loc = GSSwizzle::Locate(f, 0u, t.bw, x, y);
                    uint32_t i = GSSwizzle::LoadAt(f, vram.data() + loc.byte, loc.shift);
                    if (t.psm == 0x13u)
                        i = (i & 0xE7u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1); // CSM1
                    const uint32_t c = leer32(rdram, t.datosClut + 16u + 4u * i);
                    px[size_t(y) * w + x] = (c & 0x00FFFFFFu) | (std::min<uint32_t>(((c >> 24) & 0xFFu) * 2u, 255u) << 24);
                }
            char nombre[64];
            std::snprintf(nombre, sizeof(nombre), "/%08X.png", a);
            Image img{px.data(), int(w), int(h), 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
            ExportImage(img, (carpeta + nombre).c_str());
            ++n;
        }
        std::fprintf(stderr, "[gow-iconos] %zu texturas de Flash en %s\n", n, carpeta.c_str());
    }

    double g_volcarT = -1.0;
    std::string g_volcarCarpeta;

    void dibujarFormaHerramientas(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (g_volcarT >= 0.0 && segundos() >= g_volcarT)
        {
            g_volcarT = -1.0;
            volcarTexturas(rdram, g_volcarCarpeta);
        }
        dibujarForma(rdram, ctx, runtime);
    }

    // ---- Dibujo de los iconos (hilo principal, con el contexto de la ventana) ----
    enum Estilo
    {
        EOriginal,
        ETeclado,
        EXbox
    };

    Font g_fuente{};
    bool g_fuenteCargada = false;

    void cargarFuente()
    {
        if (g_fuenteCargada)
            return;
        g_fuenteCargada = true;
        // ASCII y las letras del turco y del español que pueden salir en el nombre de una tecla.
        std::vector<int> puntos;
        for (int c = 32; c < 127; ++c)
            puntos.push_back(c);
        for (int c : {0xC7, 0xD6, 0xDC, 0xD1, 0x11E, 0x130, 0x15E, 0xE7, 0xF6, 0xFC, 0xF1, 0x11F, 0x131, 0x15F})
            puntos.push_back(c);
        if (gowFuenteIconosTam > 0u)
            g_fuente = LoadFontFromMemory(".ttf", gowFuenteIconos, int(gowFuenteIconosTam), 96, puntos.data(), int(puntos.size()));
        if (g_fuente.texture.id == 0)
            g_fuente = GetFontDefault();
        else
            SetTextureFilter(g_fuente.texture, TEXTURE_FILTER_BILINEAR);
    }

    Estilo estiloActual()
    {
        static const int forzado = [] {
            const char *v = std::getenv("GOW_ICONOS_ESTILO");
            if (!v)
                return -1;
            const std::string s(v);
            return s == "teclado" ? int(ETeclado) : s == "xbox" ? int(EXbox) : s == "original" ? int(EOriginal) : -1;
        }();
        if (forzado >= 0)
            return Estilo(forzado);
        // Como ps2_pad.cpp: con un mando conectado se juega con el mando y el teclado no cuenta.
        if (!IsGamepadAvailable(0))
            return ETeclado;
        std::string nombre = GetGamepadName(0) ? GetGamepadName(0) : "";
        std::transform(nombre.begin(), nombre.end(), nombre.begin(), [](unsigned char c) { return char(std::tolower(c)); });
        for (const char *ps : {"playstation", "dualshock", "dualsense", "sony", "ps3", "ps4", "ps5", "wireless controller"})
            if (nombre.find(ps) != std::string::npos)
                return EOriginal;
        return EXbox;
    }

    std::string nombreTecla(int codigo)
    {
        if (codigo >= 1000)
            return codigo <= 1002 ? "#RAT" + std::to_string(codigo - 1000) : "M" + std::to_string(codigo - 999);
        switch (codigo)
        {
        case KEY_SPACE: return "#ESP";
        case KEY_LEFT_SHIFT: case KEY_RIGHT_SHIFT: return "#MAY";
        case KEY_LEFT_CONTROL: case KEY_RIGHT_CONTROL: return "CTRL";
        case KEY_LEFT_ALT: case KEY_RIGHT_ALT: return "ALT";
        case KEY_ENTER: case KEY_KP_ENTER: return "#ENT";
        case KEY_TAB: return "#TAB";
        case KEY_ESCAPE: return "ESC";
        case KEY_BACKSPACE: return "BKSP";
        case KEY_CAPS_LOCK: return "CAPS";
        case KEY_UP: return "#ARR";
        case KEY_DOWN: return "#ABA";
        case KEY_LEFT: return "#IZQ";
        case KEY_RIGHT: return "#DER";
        default: break;
        }
        if (codigo >= KEY_F1 && codigo <= KEY_F12)
            return "F" + std::to_string(codigo - KEY_F1 + 1);
        if (codigo >= KEY_KP_0 && codigo <= KEY_KP_9)
            return "NUM" + std::to_string(codigo - KEY_KP_0);
        // Letras y signos: el nombre en la distribución activa (GLFW), en mayúsculas (también ı ş ğ ü ö ç).
        if (const char *n = glfwGetKeyName(codigo, 0); n && *n)
        {
            std::string s(n);
            static const std::pair<const char *, const char *> kMayus[] = {
                {"\xC4\xB1", "I"}, {"i", "\xC4\xB0"}, {"\xC5\x9F", "\xC5\x9E"}, {"\xC4\x9F", "\xC4\x9E"},
                {"\xC3\xBC", "\xC3\x9C"}, {"\xC3\xB6", "\xC3\x96"}, {"\xC3\xA7", "\xC3\x87"}, {"\xC3\xB1", "\xC3\x91"}};
            for (const auto &[min, may] : kMayus)
                if (s == min)
                    return may;
            if (s.size() == 1)
                s[0] = char(std::toupper(static_cast<unsigned char>(s[0])));
            return s;
        }
        if (codigo >= 32 && codigo < 127)
            return std::string(1, char(codigo));
        return "?";
    }

    // Rótulo del icono: texto, o "#..." para lo que se dibuja (flechas, ratón, cruceta, menú).
    std::string rotulo(Estilo e, Boton b)
    {
        if (e == ETeclado)
        {
            if (b == BStickIzq)
            {
                int c[4] = {};
                int k = 0;
                for (const char *a : {"li_arriba", "li_izq", "li_abajo", "li_der"})
                    tobiichiCodigosAccion(a, &c[k++], 1);
                if (c[0] == KEY_W && c[1] == KEY_A && c[2] == KEY_S && c[3] == KEY_D)
                    return "WASD";
                std::string s;
                for (int x : c)
                    s += nombreTecla(x).substr(0, 1);
                return s;
            }
            if (b == BCruceta)
                return "#CRU";
            int codigos[4];
            if (tobiichiCodigosAccion(kAccion[b], codigos, 4) <= 0)
                return "";
            return nombreTecla(codigos[0]);
        }
        switch (tobiichiBotonMandoAccion(kAccion[b]))
        {
        case GAMEPAD_BUTTON_RIGHT_FACE_DOWN: return "A";
        case GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: return "B";
        case GAMEPAD_BUTTON_RIGHT_FACE_LEFT: return "X";
        case GAMEPAD_BUTTON_RIGHT_FACE_UP: return "Y";
        case GAMEPAD_BUTTON_LEFT_TRIGGER_1: return "LB";
        case GAMEPAD_BUTTON_RIGHT_TRIGGER_1: return "RB";
        case GAMEPAD_BUTTON_LEFT_TRIGGER_2: return "LT";
        case GAMEPAD_BUTTON_RIGHT_TRIGGER_2: return "RT";
        case GAMEPAD_BUTTON_LEFT_THUMB: return "LS";
        case GAMEPAD_BUTTON_RIGHT_THUMB: return "RS";
        case GAMEPAD_BUTTON_MIDDLE_RIGHT: return "#MENU";
        case GAMEPAD_BUTTON_MIDDLE_LEFT: return "#VISTA";
        case GAMEPAD_BUTTON_LEFT_FACE_UP: return "#ARR";
        case GAMEPAD_BUTTON_LEFT_FACE_DOWN: return "#ABA";
        case GAMEPAD_BUTTON_LEFT_FACE_LEFT: return "#IZQ";
        case GAMEPAD_BUTTON_LEFT_FACE_RIGHT: return "#DER";
        default: break;
        }
        return b == BStickIzq ? "LS" : b == BCruceta ? "#CRU" : "";
    }

    Color colorXbox(const std::string &r)
    {
        if (r == "A") return Color{96, 190, 60, 255};
        if (r == "B") return Color{224, 64, 52, 255};
        if (r == "X") return Color{52, 132, 228, 255};
        if (r == "Y") return Color{236, 190, 40, 255};
        return Color{232, 222, 200, 255};
    }

    constexpr int kRadio = 64; // los iconos se dibujan a 128 píxeles de alto y se escalan

    void textoCentrado(const std::string &s, Vector2 c, float alto, Color color, float anchoMax)
    {
        float tam = alto;
        Vector2 m = MeasureTextEx(g_fuente, s.c_str(), tam, 0.0f);
        if (m.x > anchoMax)
        {
            tam *= anchoMax / m.x;
            m = MeasureTextEx(g_fuente, s.c_str(), tam, 0.0f);
        }
        const Vector2 p{c.x - m.x * 0.5f, c.y - m.y * 0.5f};
        // Contorno oscuro, como el trazo de los rótulos del juego, y la letra encima con algo más de peso.
        const Color sombra{10, 8, 6, 230};
        for (int dx = -3; dx <= 3; ++dx)
            for (int dy = -3; dy <= 3; ++dy)
                if (dx * dx + dy * dy <= 10 && (dx || dy))
                    DrawTextEx(g_fuente, s.c_str(), Vector2{p.x + dx, p.y + dy}, tam, 0.0f, sombra);
        // Peso de letra de los rótulos del juego: varias pasadas desplazadas medio píxel.
        for (float d : {0.0f, 0.8f, 1.6f})
        {
            DrawTextEx(g_fuente, s.c_str(), Vector2{p.x + d, p.y}, tam, 0.0f, color);
            DrawTextEx(g_fuente, s.c_str(), Vector2{p.x + d, p.y + 0.8f}, tam, 0.0f, color);
        }
    }

    void flecha(Vector2 c, float r, int dir, Color color)
    {
        // dir: 0 arriba, 1 abajo, 2 izquierda, 3 derecha
        const float a = (dir == 0 ? -90.0f : dir == 1 ? 90.0f : dir == 2 ? 180.0f : 0.0f) * DEG2RAD;
        const Vector2 punta{c.x + std::cos(a) * r, c.y + std::sin(a) * r};
        const Vector2 b1{c.x + std::cos(a + 2.4f) * r * 0.85f, c.y + std::sin(a + 2.4f) * r * 0.85f};
        const Vector2 b2{c.x + std::cos(a - 2.4f) * r * 0.85f, c.y + std::sin(a - 2.4f) * r * 0.85f};
        DrawTriangle(punta, b2, b1, color);
        DrawTriangle(punta, b1, b2, color);
    }

    void dibujarRaton(Vector2 c, float r, int boton, Color color)
    {
        const Rectangle cuerpo{c.x - r * 0.42f, c.y - r * 0.62f, r * 0.84f, r * 1.24f};
        DrawRectangleRounded(cuerpo, 0.9f, 12, Color{20, 18, 16, 255});
        DrawRectangleRoundedLinesEx(cuerpo, 0.9f, 12, 5.0f, color);
        const float corte = c.y - r * 0.08f;
        DrawLineEx(Vector2{c.x, cuerpo.y + 2.0f}, Vector2{c.x, corte}, 4.5f, color);
        DrawLineEx(Vector2{cuerpo.x + 2.0f, corte}, Vector2{cuerpo.x + cuerpo.width - 2.0f, corte}, 4.5f, color);
        const Color rojo{200, 48, 36, 255};
        const float alto = corte - cuerpo.y - 7.0f;
        if (boton == 0)
            DrawRectangleRounded(Rectangle{cuerpo.x + 5.0f, cuerpo.y + 5.0f, r * 0.42f - 8.0f, alto}, 0.7f, 8, rojo);
        else if (boton == 1)
            DrawRectangleRounded(Rectangle{c.x + 3.0f, cuerpo.y + 5.0f, r * 0.42f - 8.0f, alto}, 0.7f, 8, rojo);
        else
            DrawRectangleRounded(Rectangle{c.x - r * 0.07f, cuerpo.y + r * 0.12f, r * 0.14f, r * 0.3f}, 0.9f, 8, rojo);
    }

    struct Textura
    {
        RenderTexture2D rt{};
        float aspecto = 1.0f; // ancho / alto
    };
    std::map<std::string, Textura> g_texturas;

    const Textura &textura(Estilo e, Boton b, Variante v)
    {
        const std::string r = rotulo(e, b);
        const std::string clave = std::to_string(int(e)) + ":" + std::to_string(int(v)) + ":" + r;
        if (const auto it = g_texturas.find(clave); it != g_texturas.end())
            return it->second;
        cargarFuente();
        // El juego reserva en el texto el ancho de un botón: la tecla es cuadrada, como mucho algo más ancha para
        // rótulos de 3-4 letras (CTRL, ESC, F10...); Espacio, Mayúsculas, Intro y Tab llevan su símbolo.
        const bool largo = r.size() > 2 && r[0] != '#';
        const int alto = 2 * kRadio;
        const int ancho = e == ETeclado && largo ? int(alto * 1.25f) : alto;
        Textura t;
        t.aspecto = float(ancho) / float(alto);
        t.rt = LoadRenderTexture(ancho, alto);
        SetTextureFilter(t.rt.texture, TEXTURE_FILTER_BILINEAR);
        BeginTextureMode(t.rt);
        ClearBackground(Color{0, 0, 0, 0});
        const Vector2 c{ancho * 0.5f, alto * 0.5f};
        const float R = kRadio - 3.0f;
        const Color borde{150, 138, 112, 255}, piedra{34, 30, 26, 255}, piedraBaja{14, 12, 10, 255};
        const Color letra{236, 226, 202, 255}, oro{214, 176, 92, 255};
        const bool griego = v == VGriego;
        const bool hombro = e == EXbox && (r == "LB" || r == "RB" || r == "LT" || r == "RT");
        if (e == ETeclado || hombro)
        {
            // Tecla: rectángulo redondeado con bisel.
            const Rectangle k{4.0f, 6.0f, ancho - 8.0f, alto - 12.0f};
            DrawRectangleRounded(Rectangle{k.x, k.y + 4.0f, k.width, k.height}, 0.35f, 12, piedraBaja);
            DrawRectangleRounded(k, 0.35f, 12, piedra);
            DrawRectangleGradientV(int(k.x + 8), int(k.y + 6), int(k.width - 16), int(k.height * 0.5f), Color{62, 56, 48, 255}, piedra);
            DrawRectangleRoundedLinesEx(k, 0.35f, 12, griego ? 5.0f : 3.5f, griego ? oro : borde);
            DrawRectangleRoundedLinesEx(Rectangle{k.x + 7.0f, k.y + 7.0f, k.width - 14.0f, k.height - 16.0f}, 0.3f, 12, 1.5f,
                                        Color{90, 82, 68, 160});
        }
        else
        {
            // Disco de los botones del juego.
            DrawCircleGradient(int(c.x), int(c.y), R, Color{64, 58, 50, 255}, piedraBaja);
            DrawRing(c, R - (griego ? 6.0f : 4.0f), R, 0.0f, 360.0f, 64, griego ? oro : borde);
            DrawRing(c, R - 10.0f, R - 8.5f, 0.0f, 360.0f, 64, Color{90, 82, 68, 140});
        }
        const Color tinta = e == EXbox ? colorXbox(r) : (griego ? oro : letra);
        const float g = 7.0f; // grosor de trazo de los símbolos
        if (r.rfind("#RAT", 0) == 0)
            dibujarRaton(c, R * 0.95f, r[4] - '0', letra);
        else if (r == "#ESP") // ⎵
        {
            const float x0 = c.x - R * 0.5f, x1 = c.x + R * 0.5f, y0 = c.y - R * 0.02f, y1 = c.y + R * 0.26f;
            DrawLineEx(Vector2{x0, y0}, Vector2{x0, y1}, g, tinta);
            DrawLineEx(Vector2{x0 - g * 0.5f, y1}, Vector2{x1 + g * 0.5f, y1}, g, tinta);
            DrawLineEx(Vector2{x1, y1}, Vector2{x1, y0}, g, tinta);
        }
        else if (r == "#MAY") // ⇧
        {
            const Vector2 punta{c.x, c.y - R * 0.5f}, i{c.x - R * 0.42f, c.y - R * 0.02f}, d{c.x + R * 0.42f, c.y - R * 0.02f};
            const float t0 = c.x - R * 0.2f, t1 = c.x + R * 0.2f, base = c.y + R * 0.42f;
            DrawLineEx(punta, i, g, tinta);
            DrawLineEx(punta, d, g, tinta);
            DrawLineEx(i, Vector2{t0, i.y}, g, tinta);
            DrawLineEx(d, Vector2{t1, d.y}, g, tinta);
            DrawLineEx(Vector2{t0, i.y - g * 0.5f}, Vector2{t0, base}, g, tinta);
            DrawLineEx(Vector2{t1, d.y - g * 0.5f}, Vector2{t1, base}, g, tinta);
            DrawLineEx(Vector2{t0 - g * 0.5f, base}, Vector2{t1 + g * 0.5f, base}, g, tinta);
        }
        else if (r == "#ENT") // ↵
        {
            const float x1 = c.x + R * 0.38f, y0 = c.y - R * 0.4f, y1 = c.y + R * 0.18f, x0 = c.x - R * 0.2f;
            DrawLineEx(Vector2{x1, y0}, Vector2{x1, y1}, g, tinta);
            DrawLineEx(Vector2{x1 + g * 0.5f, y1}, Vector2{x0, y1}, g, tinta);
            flecha(Vector2{x0 - R * 0.06f, y1}, R * 0.24f, 2, tinta);
        }
        else if (r == "#TAB") // ⇥
        {
            const float y = c.y, x0 = c.x - R * 0.42f, x1 = c.x + R * 0.26f;
            DrawLineEx(Vector2{x0, y}, Vector2{x1 - R * 0.1f, y}, g, tinta);
            flecha(Vector2{x1 - R * 0.04f, y}, R * 0.22f, 3, tinta);
            DrawLineEx(Vector2{c.x + R * 0.42f, y - R * 0.3f}, Vector2{c.x + R * 0.42f, y + R * 0.3f}, g, tinta);
        }
        else if (r == "#ARR" || r == "#ABA" || r == "#IZQ" || r == "#DER")
            flecha(c, R * 0.5f, r == "#ARR" ? 0 : r == "#ABA" ? 1 : r == "#IZQ" ? 2 : 3, tinta);
        else if (r == "#CRU")
        {
            for (int d = 0; d < 4; ++d)
                flecha(Vector2{c.x + (d == 2 ? -R * 0.42f : d == 3 ? R * 0.42f : 0.0f), c.y + (d == 0 ? -R * 0.42f : d == 1 ? R * 0.42f : 0.0f)},
                       R * 0.26f, d, tinta);
        }
        else if (r == "#MENU")
        {
            for (int k = -1; k <= 1; ++k)
                DrawRectangleRounded(Rectangle{c.x - R * 0.38f, c.y + k * R * 0.26f - 4.0f, R * 0.76f, 8.0f}, 1.0f, 6, tinta);
        }
        else if (r == "#VISTA")
        {
            DrawRectangleRoundedLinesEx(Rectangle{c.x - R * 0.42f, c.y - R * 0.36f, R * 0.5f, R * 0.44f}, 0.3f, 6, 4.0f, tinta);
            DrawRectangleRounded(Rectangle{c.x - R * 0.1f, c.y - R * 0.1f, R * 0.5f, R * 0.44f}, 0.3f, 6, tinta);
        }
        else if (!r.empty())
            textoCentrado(r, Vector2{c.x, c.y + 2.0f}, r.size() <= 1 ? alto * 0.74f : r.size() == 2 ? alto * 0.48f : alto * 0.44f, tinta,
                          ancho - 26.0f);
        EndTextureMode();
        return g_texturas.emplace(clave, t).first->second;
    }
}

// Hilo principal, cada cuadro, sobre la imagen del juego (rectángulo de destino en la ventana).
void gowIconosDibujar(float dx, float dy, float dw, float dh)
{
    if (!g_activo)
        return;
    std::vector<Icono> iconos;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        const auto ahora = std::chrono::steady_clock::now();
        cerrarCuadro(ahora);
        if (ahora - g_publicadoEn > std::chrono::milliseconds(70)) // hace rato que el juego no dibuja iconos
            g_publicados.clear();
        iconos = g_publicados;
    }
    const Estilo e = estiloActual();
    if (e == EOriginal || iconos.empty())
        return;
    static const float ajuste = [] {
        const char *v = std::getenv("GOW_ICONOS_TAMANO");
        return v ? std::strtof(v, nullptr) : 1.0f;
    }();
    for (const Icono &i : iconos)
    {
        const Textura &t = textura(e, i.boton, i.variante);
        // Radio en píxeles del escenario (el espacio de la matriz va a medio píxel).
        const float r = i.escala * 0.5f * ajuste;
        const float alto = 2.0f * r / 480.0f * dh, ancho = alto * t.aspecto;
        const float y = 240.0f + (i.y - 240.0f) * g_estiramientoVertical.load(std::memory_order_relaxed);
        const float cx = dx + i.x / 640.0f * dw, cy = dy + y / 480.0f * dh;
        const Rectangle origen{0.0f, 0.0f, float(t.rt.texture.width), -float(t.rt.texture.height)};
        const Color tinte{static_cast<unsigned char>(255.0f * i.r), static_cast<unsigned char>(255.0f * i.g),
                          static_cast<unsigned char>(255.0f * i.b), static_cast<unsigned char>(255.0f * i.a)};
        DrawTexturePro(t.rt.texture, origen, Rectangle{cx - ancho * 0.5f, cy - alto * 0.5f, ancho, alto}, Vector2{0.0f, 0.0f}, 0.0f, tinte);
    }
}

void gowIconosInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99" || !runtime.hasFunction(kDibujarForma))
        return;
    const char *activo = std::getenv("GOW_ICONOS");
    g_activo = !(activo && activo[0] == '0');
    const char *d = std::getenv("GOW_ICONOS_DIAG");
    g_diag = d && d[0] == '1';
    if (const char *o = std::getenv("GOW_ICONOS_OCULTAR"))
        for (const char *p = o; *p;)
        {
            char *fin = nullptr;
            const unsigned long v = std::strtoul(p, &fin, 16);
            if (fin == p)
                break;
            g_ocultar.insert(static_cast<uint32_t>(v));
            p = *fin == ',' ? fin + 1 : fin;
        }
    if (const char *v = std::getenv("GOW_ICONOS_VOLCAR"))
    {
        char carpeta[512] = {};
        if (std::sscanf(v, "%lf:%511[^\n]", &g_volcarT, carpeta) == 2)
            g_volcarCarpeta = carpeta;
        else
            g_volcarT = -1.0;
    }
    if (!g_activo && g_ocultar.empty() && g_volcarT < 0.0)
        return;
    g_dibujarForma = runtime.lookupFunction(kDibujarForma);
    runtime.replaceFunction(kDibujarForma, g_volcarT >= 0.0 ? &dibujarFormaHerramientas : &dibujarForma);
    if (g_activo)
        std::cerr << "[gow-iconos] iconos de botones según el dispositivo" << std::endl;
}
