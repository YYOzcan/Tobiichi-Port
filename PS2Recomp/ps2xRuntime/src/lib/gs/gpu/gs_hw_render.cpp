// GOW-Port: renderizador por hardware de triángulos (PS2X_GS_HW=1). Ver gs_hw_render.h.
#include "gs_hw_render.h"
#include "gs_gpu_shaders.h"
#include "../gs_sprite_rules.h"
#include "runtime/gs/gs_swizzle.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

using namespace GSGL;

// GOW-Port: triángulos dibujados por hardware en todo el proceso (pruebas).
static std::atomic<uint64_t> g_triangulosHw{0};
uint64_t gowGsHwTriangulos() { return g_triangulosHw.load(std::memory_order_relaxed); }
static std::atomic<uint64_t> g_spritesHw{0};
uint64_t gowGsHwSprites() { return g_spritesHw.load(std::memory_order_relaxed); }

namespace GSHw
{
    namespace
    {
        // Funciones y constantes de OpenGL que gs_gl.h no carga.
        constexpr GLenum kBlend = 0x0BE2, kDepthTest = 0x0B71, kScissorTest = 0x0C11;
        constexpr GLenum kFuncAdd = 0x8006, kFuncSubtract = 0x800A, kFuncReverseSubtract = 0x800B;
        constexpr GLenum kZero = 0u, kOne = 1u, kSrc1Alpha = 0x8589, kOneMinusSrc1Alpha = 0x88FB;
        constexpr GLenum kNever = 0x0200, kGreater = 0x0204, kGequal = 0x0206, kAlways = 0x0207;
        constexpr GLenum kColorAttachment0 = 0x8CE0, kDepthAttachment = 0x8D00, kFramebufferComplete = 0x8CD5;
        constexpr GLenum kDepthComponent32F = 0x8CAC, kDepthComponent = 0x1902, kFloat = 0x1406;
        constexpr GLint kNearest = 0x2600, kRepeat = 0x2901;
        constexpr GLenum kTexture0 = 0x84C0, kLowerLeft = 0x8CA1, kNegativeOneToOne = 0x935E, kZeroToOne = 0x935F;
        constexpr GLenum kStreamDrawUsage = 0x88E0;

        struct ApiHw
        {
            void (*FramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint) = nullptr;
            GLenum (*CheckFramebufferStatus)(GLenum) = nullptr;
            void (*BlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum) = nullptr;
            void (*BlendEquationSeparate)(GLenum, GLenum) = nullptr;
            void (*DepthFunc)(GLenum) = nullptr;
            void (*DepthMask)(GLboolean) = nullptr;
            void (*ColorMask)(GLboolean, GLboolean, GLboolean, GLboolean) = nullptr;
            void (*Scissor)(GLint, GLint, GLsizei, GLsizei) = nullptr;
            void (*ClipControl)(GLenum, GLenum) = nullptr;
            void (*ActiveTexture)(GLenum) = nullptr;
            void (*Uniform1i)(GLint, GLint) = nullptr;
            void (*Uniform4f)(GLint, float, float, float, float) = nullptr;
            void (*CopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei,
                                     GLsizei) = nullptr;
            void (*TextureBarrier)() = nullptr;
        };

        void *procedimiento(const char *nombre)
        {
#if defined(_WIN32)
            void *p = reinterpret_cast<void *>(wglGetProcAddress(nombre));
            const auto v = reinterpret_cast<intptr_t>(p);
            if (v == 0 || v == 1 || v == 2 || v == 3 || v == -1)
            {
                static HMODULE modulo = LoadLibraryA("opengl32.dll");
                p = reinterpret_cast<void *>(GetProcAddress(modulo, nombre));
            }
            return p;
#else
            return reinterpret_cast<void *>(glfwGetProcAddress(nombre));
#endif
        }

        template <typename T>
        bool cargar(T &f, const char *nombre)
        {
            f = reinterpret_cast<T>(procedimiento(nombre));
            return f != nullptr;
        }

        // Carga de un objetivo desde los planos: triángulo a pantalla completa; cada píxel lee su plano.
        const char *const kCargaVs = R"GLSL(
void main()
{
    vec2 p = vec2(gl_VertexID == 1 ? 3.0 : -1.0, gl_VertexID == 2 ? 3.0 : -1.0);
    gl_Position = vec4(p, 0.0, 1.0);
}
)GLSL";

        // Lectura y escritura de un plano cualquiera con el búfer completo en el binding 0.
        const char *const kPlanos = R"GLSL(
uniform uvec4 uPlano; // x = escala, y = palabras por plano
uint leerPlano(uint k, uint psm, uint base, uint bw, uint x, uint y)
{
    uint f = fmtOf(psm);
    if (FMT_KIND[f] == KIND_INVALID)
        return 0u;
    uvec2 loc = locate(f, base, bw, x, y);
    uint word = vram[k * uPlano.y + (loc.x >> 2u)];
    switch (FMT_KIND[f])
    {
    case KIND_32: return word;
    case KIND_24: return word & 0x00FFFFFFu;
    case KIND_16: return (word >> ((loc.x & 2u) * 8u)) & 0xFFFFu;
    }
    return 0u;
}
void escribirPlano(uint k, uint psm, uint base, uint bw, uint x, uint y, uint value)
{
    uint f = fmtOf(psm);
    if (FMT_KIND[f] == KIND_INVALID)
        return;
    uvec2 loc = locate(f, base, bw, x, y);
    uint i = k * uPlano.y + (loc.x >> 2u);
    switch (FMT_KIND[f])
    {
    case KIND_32:
        vram[i] = value;
        break;
    case KIND_24:
        vram[i] = (vram[i] & 0xFF000000u) | (value & 0x00FFFFFFu);
        break;
    case KIND_16:
    {
        uint shift = (loc.x & 2u) * 8u;
        atomicAnd(vram[i], ~(0xFFFFu << shift));
        atomicOr(vram[i], (value & 0xFFFFu) << shift);
        break;
    }
    }
}
uint planoDe(uvec2 p) { return (p.y % uPlano.x) * uPlano.x + (p.x % uPlano.x); }
)GLSL";

        const char *const kCargaFs = R"GLSL(
uniform uvec4 uObj;   // x = base (bloques), y = bw, z = psm, w = 1 profundidad
uniform vec4 uZEsc;   // x = 1 / 2^bits de Z
layout(location = 0) out vec4 oColor;
void main()
{
    uvec2 p = uvec2(gl_FragCoord.xy);
    uint raw = leerPlano(planoDe(p), uObj.z, uObj.x, uObj.y, p.x / uPlano.x, p.y / uPlano.x);
    if (uObj.w != 0u)
    {
        gl_FragDepth = float(raw) * uZEsc.x;
        oColor = vec4(0.0);
        return;
    }
    if (uObj.z == 2u || uObj.z == 10u)
        raw = rgba5551To8888(raw);
    uvec4 c = uvec4(raw & 0xFFu, (raw >> 8u) & 0xFFu, (raw >> 16u) & 0xFFu, raw >> 24u);
    if (uObj.z == 1u)
        c.a = 0x80u;
    oColor = vec4(c) / 255.0;
    gl_FragDepth = 0.0;
}
)GLSL";

        const char *const kVolcado = R"GLSL(
layout(local_size_x = 8, local_size_y = 8) in;
uniform sampler2D uFuente;
uniform uvec4 uObj;   // x = base, y = bw, z = psm, w = 1 profundidad
uniform uvec4 uRect;  // rectángulo en píxeles del objetivo: x0, y0, x1, y1 (exclusivo)
uniform vec4 uZEsc;   // y = 2^bits de Z, z = Z máximo
void main()
{
    uvec2 p = gl_GlobalInvocationID.xy + uRect.xy;
    if (p.x >= uRect.z || p.y >= uRect.w)
        return;
    vec4 v = texelFetch(uFuente, ivec2(p), 0);
    uint value;
    if (uObj.w != 0u)
        value = uint(min(floor(double(v.r) * double(uZEsc.y) + 0.5lf), double(uZEsc.y) - 1.0lf));
    else
    {
        uvec4 c = uvec4(round(clamp(v, 0.0, 1.0) * 255.0));
        value = c.r | (c.g << 8u) | (c.b << 16u) | (c.a << 24u);
        if (uObj.z == 2u || uObj.z == 10u)
            value = rgba8888To5551(value);
    }
    escribirPlano(planoDe(p), uObj.z, uObj.x, uObj.y, p.x / uPlano.x, p.y / uPlano.x, value);
}
)GLSL";

        // Decodificación de una textura del GS (plano 0) a RGBA8, con CLUT y TEXA como la ruta software.
        const char *const kDecodificar = R"GLSL(
layout(local_size_x = 8, local_size_y = 8) in;
layout(std430, binding = 12) writeonly buffer Salida { uint texels[]; };
uniform uvec4 uTex;   // x = tbp0, y = tbw, z = psm, w = ancho | alto << 16
uniform uvec4 uClut;  // x = cpsm, y = csm, z = csa, w = ranura
uniform uvec4 uTexa;  // x = ta0, y = aem, z = ta1
uint texa(uint psm, uint texel)
{
    if (psm == 0u)
        return texel;
    bool rgbZero = (texel & 0x00FFFFFFu) == 0u;
    uint a = texel >> 24u;
    if (psm == 1u)
        a = (uTexa.y != 0u && rgbZero) ? 0u : uTexa.x;
    else if (psm == 2u || psm == 10u)
        a = (a & 0x80u) != 0u ? uTexa.z : ((uTexa.y != 0u && rgbZero) ? 0u : uTexa.x);
    return (texel & 0x00FFFFFFu) | (a << 24u);
}
bool cuatroBits(uint psm) { return psm == 0x14u || psm == 0x24u || psm == 0x2Cu; }
bool ochoBits(uint psm) { return psm == 0x13u || psm == 0x1Bu; }
uint deClut(uint index, uint sourcePsm)
{
    uint cpsm = uClut.x;
    bool sixteenBit = cpsm == 2u || cpsm == 10u;
    uint clutBase = (uClut.z & (sixteenBit ? 0x1Fu : 0x0Fu)) << 4u;
    uint sourceIndex = cuatroBits(sourcePsm) ? (index & 0x0Fu) : index;
    uint clutIndex = (clutBase + sourceIndex) & (sixteenBit ? 0x1FFu : 0x0FFu);
    if (!sixteenBit && uClut.y == 0u && ochoBits(sourcePsm))
        clutIndex = min((sourceIndex & 0xF0u) + clutBase, 240u) + (sourceIndex & 0x0Fu);
    uint version = uClut.w;
    if (cpsm == 0u)
        return texa(0u, clutEntry(version, clutIndex) | (clutEntry(version, clutIndex + 256u) << 16u));
    if (cpsm == 1u)
        return texa(1u, (clutEntry(version, clutIndex) | (clutEntry(version, clutIndex + 256u) << 16u)) & 0x00FFFFFFu);
    if (sixteenBit)
        return texa(cpsm, rgba5551To8888(clutEntry(version, clutIndex)));
    return 0xFFFF00FFu;
}
void main()
{
    uint w = uTex.w & 0xFFFFu, h = uTex.w >> 16u;
    uvec2 p = gl_GlobalInvocationID.xy;
    if (p.x >= w || p.y >= h)
        return;
    uint psm = uTex.z;
    uint raw = readPixel(psm, uTex.x, uTex.y, p.x, p.y);
    uint c = 0xFFFF00FFu;
    switch (psm)
    {
    case 0x00u: case 0x01u: c = texa(psm, raw); break;
    case 0x02u: case 0x0Au: c = texa(psm, rgba5551To8888(raw)); break;
    // GOW-Port: alias de profundidad leídos como textura (sprites): mismas reglas de TEXA que su formato de color.
    case 0x30u: c = raw; break;
    case 0x31u: c = texa(1u, raw); break;
    case 0x32u: case 0x3Au: c = texa(2u, rgba5551To8888(raw)); break;
    case 0x13u: case 0x1Bu: case 0x14u: case 0x24u: case 0x2Cu: c = deClut(raw & 0xFFu, psm); break;
    }
    texels[p.y * w + p.x] = c;
}
)GLSL";

        const char *const kDibujoVs = R"GLSL(
layout(std430, binding = 11) readonly buffer Vertices { uint vtx[]; };
uniform vec4 uDestino; // x = escala, y = 2 / ancho, z = 2 / alto (píxeles del objetivo), w = escala de Z
noperspective out vec4 vColor;
flat out vec4 vColorPlano;
noperspective out vec3 vStq;
noperspective out vec2 vUv;
noperspective out float vNiebla;
void main()
{
    uint b = uint(gl_VertexID) * 12u;
    float x = uintBitsToFloat(vtx[b]) * uDestino.x + 0.5;
    float y = uintBitsToFloat(vtx[b + 1u]) * uDestino.x + 0.5;
    gl_Position = vec4(x * uDestino.y - 1.0, y * uDestino.z - 1.0, float(vtx[b + 2u]) * uDestino.w, 1.0);
    uint c = vtx[b + 3u];
    vec4 color = vec4(float(c & 0xFFu), float((c >> 8u) & 0xFFu), float((c >> 16u) & 0xFFu), float(c >> 24u));
    vColor = color;
    vColorPlano = color;
    vStq = vec3(uintBitsToFloat(vtx[b + 4u]), uintBitsToFloat(vtx[b + 5u]), uintBitsToFloat(vtx[b + 6u]));
    vUv = vec2(uintBitsToFloat(vtx[b + 7u]), uintBitsToFloat(vtx[b + 8u]));
    vNiebla = uintBitsToFloat(vtx[b + 9u]);
}
)GLSL";

        const char *const kDibujoFs = R"GLSL(
uniform sampler2D uTextura;
uniform uvec4 uMezcla; // x = color de la niebla, y = factor C (0 As, 2 FIX), z = FIX
uniform vec4 uTexTam;  // x = ancho, y = alto
noperspective in vec4 vColor;
flat in vec4 vColorPlano;
noperspective in vec3 vStq;
noperspective in vec2 vUv;
noperspective in float vNiebla;
layout(location = 0, index = 0) out vec4 oColor;
layout(location = 0, index = 1) out vec4 oFactor;
const uint M_TME = 1u, M_IIP = 2u, M_FST = 4u, M_FGE = 8u;
uint u8(float v) { return uint(clamp(int(floor(v + 1.0 / 512.0)), 0, 255)); }
void main()
{
    uint flags = uModo.x;
    vec4 vc = (flags & M_IIP) != 0u ? vColor : vColorPlano;
    uvec4 c = uvec4(u8(vc.r), u8(vc.g), u8(vc.b), u8(vc.a));
    if ((flags & M_TME) != 0u)
    {
        vec2 uv;
        if ((flags & M_FST) != 0u)
            uv = floor(vUv + 1.0 / 512.0) / 16.0 / uTexTam.xy;
        else
        {
            float q = abs(vStq.z) > 1.0e-8 ? vStq.z : 1.0;
            uv = vStq.xy / q;
        }
        uvec4 t = uvec4(round(texture(uTextura, uv) * 255.0));
        bool tcc = (uModo.y >> 8u) != 0u;
        int tr = int(t.r), tg = int(t.g), tb = int(t.b), ta = int(t.a);
        int vr = int(c.r), vg = int(c.g), vb = int(c.b), va = int(c.a);
        switch (uModo.y & 0xFFu)
        {
        case 0u:
            c = uvec4(c8((tr * vr) >> 7), c8((tg * vg) >> 7), c8((tb * vb) >> 7), tcc ? c8((ta * va) >> 7) : uint(va));
            break;
        case 1u:
            c = uvec4(uint(tr), uint(tg), uint(tb), tcc ? uint(ta) : uint(va));
            break;
        case 2u:
            c = uvec4(c8(((tr * vr) >> 7) + va), c8(((tg * vg) >> 7) + va), c8(((tb * vb) >> 7) + va), tcc ? c8(ta + va) : uint(va));
            break;
        default:
            c = uvec4(c8(((tr * vr) >> 7) + va), c8(((tg * vg) >> 7) + va), c8(((tb * vb) >> 7) + va), tcc ? uint(ta) : uint(va));
            break;
        }
    }
    if ((flags & M_FGE) != 0u)
    {
        uint f = u8(vNiebla);
        uint inv = 256u - f;
        uint fc = uMezcla.x;
        c.r = ((f * c.r + inv * (fc & 0xFFu)) >> 8u) & 0xFFu;
        c.g = ((f * c.g + inv * ((fc >> 8u) & 0xFFu)) >> 8u) & 0xFFu;
        c.b = ((f * c.b + inv * ((fc >> 16u) & 0xFFu)) >> 8u) & 0xFFu;
    }
    if (MODO == 1u)
    {
        // GOW-Port: modo exacto (mezcla con Ad, DATE, FBMSK por bits): el lote no repite píxeles.
        uint raw = palabraObjetivo(uDestinoTex, ivec2(gl_FragCoord.xy));
        uint fpsm = uExacto.w;
        uint v;
        if (!escribir(c, fpsm, fpsm == 1u ? (raw & 0x00FFFFFFu) : raw, v))
            discard;
        oColor = vec4(uvec4(v & 0xFFu, (v >> 8u) & 0xFFu, (v >> 16u) & 0xFFu, v >> 24u)) / 255.0;
        oFactor = vec4(0.0);
        return;
    }
    bool pasa = pasaAlfa(uModo.z, c.a);
    if ((uModo.w != 2u && !pasa) || (uModo.w == 2u && pasa))
        discard;
    float factor = (uMezcla.y == 0u ? float(c.a) : float(uMezcla.z)) / 128.0;
    uint a = c.a;
    if ((flags & M_FBA) != 0u)
        a |= 0x80u;
    oColor = vec4(vec3(c.rgb) / 255.0, float(a) / 255.0);
    oFactor = vec4(0.0, 0.0, 0.0, factor);
}
)GLSL";

        // GOW-Port: sprites (posprocesado, HUD). Igual que drawSprite de la ruta de cómputo: el rectángulo y la UV se
        // calculan en píxeles nativos y cada muestra lee el mismo texel de su propio plano (los sprites no se
        // desplazan). Registro de 16 palabras por sprite: x0 | x1 << 16, y0 | y1 << 16 (inclusivos, ya recortados),
        // origen x, y, escala x, y, u0, v0, u1, v1 (texels), Z, color, niebla.
        const char *const kSpriteVs = R"GLSL(
layout(std430, binding = 11) readonly buffer Sprites { uint spr[]; };
uniform vec4 uDestino; // x = escala, y = 2 / ancho, z = 2 / alto (píxeles del objetivo), w = escala de Z
flat out uint vSprite;
void main()
{
    uint i = uint(gl_VertexID) / 6u, c = uint(gl_VertexID) % 6u;
    uint b = i * 16u;
    bool dx = c == 1u || c == 3u || c == 4u;
    bool dy = c == 2u || c == 4u || c == 5u;
    float x = float(dx ? (spr[b] >> 16u) + 1u : (spr[b] & 0xFFFFu)) * uDestino.x;
    float y = float(dy ? (spr[b + 1u] >> 16u) + 1u : (spr[b + 1u] & 0xFFFFu)) * uDestino.x;
    gl_Position = vec4(x * uDestino.y - 1.0, y * uDestino.z - 1.0, float(spr[b + 10u]) * uDestino.w, 1.0);
    vSprite = i;
}
)GLSL";

        // GOW-Port: escritura de un píxel como writePixel de la ruta de cómputo (sin Z), leyendo el destino: la usan los
        // modos exactos de sprites y triángulos. Necesita rgba5551To8888 y rgba8888To5551 (kCommon).
        const char *const kEscritura = R"GLSL(
uniform uvec4 uModo;   // x = banderas, y = tfx | tcc << 8, z = TEST, w = pasada (0 normal, 1 pasan, 2 fallan)
uniform uvec4 uExacto; // x = modo, y = FBMSK, z = ALPHA (a | b << 2 | c << 4 | d << 6 | FIX << 8 | PABE << 16 | WRAP << 17 | ABE << 18), w = psm del dibujo
uniform sampler2D uDestinoTex;
const uint M_FBA = 16u;
uint c8(int v) { return uint(clamp(v, 0, 255)); }
bool pasaAlfa(uint test, uint alpha)
{
    if ((test & 1u) == 0u)
        return true;
    uint aref = (test >> 4u) & 0xFFu;
    switch ((test >> 1u) & 7u)
    {
    case 0u: return false;
    case 1u: return true;
    case 2u: return alpha < aref;
    case 3u: return alpha <= aref;
    case 4u: return alpha == aref;
    case 5u: return alpha >= aref;
    case 6u: return alpha > aref;
    }
    return alpha != aref;
}
uint palabraObjetivo(sampler2D t, ivec2 p)
{
    uvec4 c = uvec4(round(texelFetch(t, p, 0) * 255.0));
    return c.r | (c.g << 8u) | (c.b << 16u) | (c.a << 24u);
}
int elegir(uint sel, int cs, int cd) { return sel == 0u ? cs : (sel == 1u ? cd : 0); }
// writePixel de la ruta de cómputo sin Z: el valor nuevo del píxel (crudo, en el formato fpsm) o false si no se escribe.
bool escribir(uvec4 c, uint fpsm, uint raw, out uint salida)
{
    uint test = uModo.z;
    int r = int(c.r), g = int(c.g), b = int(c.b), a = int(c.a);
    bool pasa = pasaAlfa(test, uint(a));
    bool escribeRgb = true, escribeA = true;
    if (!pasa)
    {
        uint fallo = (test >> 12u) & 3u;
        escribeRgb = fallo == 1u || fallo == 3u;
        escribeA = fallo == 1u || (fallo == 3u && fpsm != 0u);
    }
    if (!escribeRgb && !escribeA)
        return false;
    bool dieciseis = fpsm == 2u || fpsm == 0x0Au;
    uint fbrgba = dieciseis ? rgba5551To8888(raw) : (fpsm == 1u ? (raw | 0x80000000u) : raw);
    if (((test >> 14u) & 1u) != 0u && (fpsm == 0u || dieciseis))
    {
        bool datm = ((test >> 15u) & 1u) != 0u;
        bool bit = dieciseis ? ((raw >> 15u) & 1u) != 0u : ((raw >> 31u) & 1u) != 0u;
        if (bit != datm)
            return false;
    }
    uint alfa = uExacto.z;
    if ((alfa & (1u << 18u)) != 0u && !((alfa & (1u << 16u)) != 0u && (a & 0x80) == 0))
    {
        int dr = int(fbrgba & 0xFFu), dg = int((fbrgba >> 8u) & 0xFFu), db = int((fbrgba >> 16u) & 0xFFu), da = int(fbrgba >> 24u);
        uint asel = alfa & 3u, bsel = (alfa >> 2u) & 3u, csel = (alfa >> 4u) & 3u, dsel = (alfa >> 6u) & 3u;
        int fix = int((alfa >> 8u) & 0xFFu);
        int ca = csel == 0u ? a : (csel == 1u ? da : fix);
        int br = ((elegir(asel, r, dr) - elegir(bsel, r, dr)) * ca >> 7) + elegir(dsel, r, dr);
        int bg = ((elegir(asel, g, dg) - elegir(bsel, g, dg)) * ca >> 7) + elegir(dsel, g, dg);
        int bb = ((elegir(asel, b, db) - elegir(bsel, b, db)) * ca >> 7) + elegir(dsel, b, db);
        if ((alfa & (1u << 17u)) != 0u)
        {
            r = br & 0xFF; g = bg & 0xFF; b = bb & 0xFF;
        }
        else
        {
            r = int(c8(br)); g = int(c8(bg)); b = int(c8(bb));
        }
    }
    if (escribeA && (uModo.x & M_FBA) != 0u && fpsm != 1u)
        a |= 0x80;
    uint pixel = uint(r) | (uint(g) << 8u) | (uint(b) << 16u) | (uint(a & 0xFF) << 24u);
    uint fbmsk = uExacto.y;
    if (fbmsk != 0u)
        pixel = (pixel & ~fbmsk) | (fbrgba & fbmsk);
    if (escribeRgb && !escribeA && fpsm == 0u)
        pixel = (pixel & 0x00FFFFFFu) | (fbrgba & 0xFF000000u);
    salida = dieciseis ? rgba8888To5551(pixel) : pixel;
    return true;
}
)GLSL";

        // Fuentes: 0 textura decodificada (plano 0), 1 objetivo en su formato, 2 objetivo CT32 visto como CT16, 3 los
        // planos de la VRAM (cualquier formato no indexado). Modos: 0 mezcla de la GPU, 1 exacto (lee el destino y aplica
        // la mezcla, DATE, FBMSK y FBA del GS como la ruta de cómputo), 2 dibujo CT16 sobre un objetivo CT32 (cada píxel
        // del objetivo son dos píxeles CT16: x y x + 8 de un bloque). Necesita kCommon y kPlanos delante.
        const char *const kSpriteFs = R"GLSL(
layout(std430, binding = 11) readonly buffer Sprites { uint spr[]; };
layout(std430, binding = 13) readonly buffer Inversas { uint inv[]; }; // 0..4095: media palabra -> CT16; 4096..: palabra -> CT32
uniform sampler2D uTextura;
uniform uvec4 uMezcla; // x = color de la niebla, y = factor C (0 As, 2 FIX), z = FIX
uniform uvec4 uFuente; // x = tipo de fuente, y = escala, z = ancho | alto << 16, w = wrapU | wrapV << 2 | 16 TEXA de CT24
uniform uvec4 uTexa;   // x = ta0, y = aem, z = ta1
uniform uvec4 uFuenteObj; // x = tbp0, y = tbw, z = psm (fuentes 2 y 3)
uniform uvec4 uObjetivo;  // x = base, y = bw (objetivo del modo 2)
flat in uint vSprite;
layout(location = 0, index = 0) out vec4 oColor;
layout(location = 0, index = 1) out vec4 oFactor;
const uint M_TME = 1u, M_FST = 4u, M_FGE = 8u, M_LINEAL = 32u;
uint texaDe(uint psm, uint texel)
{
    if (psm == 0u || psm == 0x30u)
        return texel;
    bool cero = (texel & 0x00FFFFFFu) == 0u;
    uint a = texel >> 24u;
    if (psm == 1u || psm == 0x31u)
        a = (uTexa.y != 0u && cero) ? 0u : uTexa.x;
    else
        a = (a & 0x80u) != 0u ? uTexa.z : ((uTexa.y != 0u && cero) ? 0u : uTexa.x);
    return (texel & 0x00FFFFFFu) | (a << 24u);
}
uint leer(int u, int v, ivec2 k)
{
    int w = int(uFuente.z & 0xFFFFu), h = int(uFuente.z >> 16u);
    u = (uFuente.w & 3u) == 0u ? (u & (w - 1)) : clamp(u, 0, w - 1);
    v = ((uFuente.w >> 2u) & 3u) == 0u ? (v & (h - 1)) : clamp(v, 0, h - 1);
    int S = int(uFuente.y);
    if (TIPO == 0u)
        return palabraObjetivo(uTextura, ivec2(u, v));
    if (TIPO == 1u)
    {
        // Más allá del ancho del búfer: la fila de páginas siguiente (dirección lineal de página del GS).
        uint bw = uFuenteObj.y;
        if (uint(u) >= bw * 64u)
        {
            uint lineal = (uint(v) >> 5u) * bw + (uint(u) >> 6u);
            u = int((lineal % bw) * 64u + (uint(u) & 63u));
            v = int((lineal / bw) * 32u + (uint(v) & 31u));
        }
        uint r = palabraObjetivo(uTextura, ivec2(u, v) * S + k);
        return (uFuente.w & 16u) != 0u ? texaDe(1u, r) : r;
    }
    if (TIPO == 2u)
    {
        // Texel CT16 de un objetivo CT32: su palabra y la mitad.
        uint byte = locate(fmtOf(2u), uFuenteObj.x, uFuenteObj.y, uint(u), uint(v)).x;
        uint pagina = (byte >> 13u) - (uFuenteObj.x >> 5u);
        uint l = inv[4096u + ((byte & 8191u) >> 2u)];
        ivec2 q = ivec2(int((pagina % uFuenteObj.y) * 64u + (l & 0xFFu)), int((pagina / uFuenteObj.y) * 32u + (l >> 8u)));
        uint r = (palabraObjetivo(uTextura, q * S + k) >> ((byte & 2u) * 8u)) & 0xFFFFu;
        return texaDe(2u, rgba5551To8888(r));
    }
    uint plano = uint(k.y * S + k.x);
    uint psm = uFuenteObj.z;
    uint r = leerPlano(plano, psm, uFuenteObj.x, uFuenteObj.y, uint(u), uint(v));
    if (psm == 2u || psm == 0x0Au || psm == 0x32u || psm == 0x3Au)
        r = rgba5551To8888(r);
    return texaDe(psm, r);
}
uint lerpCanal(uint c00, uint c10, uint c01, uint c11, uint wx, uint wy)
{
    uint arriba = ((16u - wx) * c00 + wx * c10) >> 4u;
    uint abajo = ((16u - wx) * c01 + wx * c11) >> 4u;
    return ((16u - wy) * arriba + wy * abajo) >> 4u;
}
// Color del sprite en el píxel p (coordenadas del dibujo), con textura y niebla.
uvec4 colorSprite(uint b, ivec2 p, ivec2 k)
{
    uint flags = uModo.x;
    uint col = spr[b + 11u];
    uvec4 c = uvec4(col & 0xFFu, (col >> 8u) & 0xFFu, (col >> 16u) & 0xFFu, col >> 24u);
    if ((flags & M_TME) != 0u)
    {
        float ox = uintBitsToFloat(spr[b + 2u]), oy = uintBitsToFloat(spr[b + 3u]);
        float sx = uintBitsToFloat(spr[b + 4u]), sy = uintBitsToFloat(spr[b + 5u]);
        float u0 = uintBitsToFloat(spr[b + 6u]), v0 = uintBitsToFloat(spr[b + 7u]);
        float u1 = uintBitsToFloat(spr[b + 8u]), v1 = uintBitsToFloat(spr[b + 9u]);
        precise float ty = (float(p.y) - oy) * sy;
        precise float texVf = v0 + (v1 - v0) * ty;
        precise float tx = (float(p.x) - ox) * sx;
        precise float texUf = u0 + (u1 - u0) * tx;
        precise float U;
        precise float V;
        if ((flags & M_FST) != 0u)
        {
            U = float(uint(clamp(int(texUf * 16.0 + 0.5), 0, 0xFFFF))) / 16.0;
            V = float(uint(clamp(int(texVf * 16.0 + 0.5), 0, 0xFFFF))) / 16.0;
        }
        else
        {
            float W = float(uFuente.z & 0xFFFFu), H = float(uFuente.z >> 16u);
            precise float ss = texUf / W;
            precise float tt = texVf / H;
            U = ss * W;
            V = tt * H;
        }
        precise float fu = trunc(U * 65536.0);
        precise float fv = trunc(V * 65536.0);
        uint texel;
        if ((flags & M_LINEAL) == 0u)
            texel = leer(int(floor(fu / 65536.0)), int(floor(fv / 65536.0)), k);
        else
        {
            precise float su = fu / 65536.0 - 0.5;
            precise float sv = fv / 65536.0 - 0.5;
            int iu = int(floor(su)), iv = int(floor(sv));
            uint wx = min(uint((su - float(iu)) * 16.0), 15u), wy = min(uint((sv - float(iv)) * 16.0), 15u);
            uint c00 = leer(iu, iv, k), c10 = leer(iu + 1, iv, k), c01 = leer(iu, iv + 1, k), c11 = leer(iu + 1, iv + 1, k);
            texel = 0u;
            for (uint s = 0u; s < 32u; s += 8u)
                texel |= lerpCanal((c00 >> s) & 0xFFu, (c10 >> s) & 0xFFu, (c01 >> s) & 0xFFu, (c11 >> s) & 0xFFu, wx, wy) << s;
        }
        bool tcc = (uModo.y >> 8u) != 0u;
        int tr = int(texel & 0xFFu), tg = int((texel >> 8u) & 0xFFu), tb = int((texel >> 16u) & 0xFFu), ta = int(texel >> 24u);
        int vr = int(c.r), vg = int(c.g), vb = int(c.b), va = int(c.a);
        switch (uModo.y & 0xFFu)
        {
        case 0u:
            c = uvec4(c8((tr * vr) >> 7), c8((tg * vg) >> 7), c8((tb * vb) >> 7), tcc ? c8((ta * va) >> 7) : uint(va));
            break;
        case 1u:
            c = uvec4(uint(tr), uint(tg), uint(tb), tcc ? uint(ta) : uint(va));
            break;
        case 2u:
            c = uvec4(c8(((tr * vr) >> 7) + va), c8(((tg * vg) >> 7) + va), c8(((tb * vb) >> 7) + va), tcc ? c8(ta + va) : uint(va));
            break;
        default:
            c = uvec4(c8(((tr * vr) >> 7) + va), c8(((tg * vg) >> 7) + va), c8(((tb * vb) >> 7) + va), tcc ? uint(ta) : uint(va));
            break;
        }
    }
    if ((flags & M_FGE) != 0u)
    {
        uint fo = spr[b + 12u] & 0xFFu;
        uint inv2 = 256u - fo;
        uint fc = uMezcla.x;
        c.r = ((fo * c.r + inv2 * (fc & 0xFFu)) >> 8u) & 0xFFu;
        c.g = ((fo * c.g + inv2 * ((fc >> 8u) & 0xFFu)) >> 8u) & 0xFFu;
        c.b = ((fo * c.b + inv2 * ((fc >> 16u) & 0xFFu)) >> 8u) & 0xFFu;
    }
    return c;
}
void main()
{
    uint b = vSprite * 16u;
    int S = int(uFuente.y);
    ivec2 f = ivec2(gl_FragCoord.xy);
    ivec2 p = f / S;
    ivec2 k = f - p * S;
    const uint modo = MODO;
    if (modo == 2u)
    {
        // CT16 sobre CT32: las dos medias palabras del píxel del objetivo.
        uint raw = palabraObjetivo(uDestinoTex, f);
        uint byte = locate(fmtOf(0u), uObjetivo.x, uObjetivo.y, uint(p.x), uint(p.y)).x;
        uint pagina = (byte >> 13u) - (uObjetivo.x >> 5u);
        uint base16 = (byte & 8191u) >> 1u;
        uint rx = spr[b + 13u], ry = spr[b + 14u];
        uint nuevo = raw;
        bool cambia = false;
        for (uint h = 0u; h < 2u; ++h)
        {
            uint l = inv[base16 + h];
            ivec2 q = ivec2(int((pagina % uObjetivo.y) * 64u + (l & 0xFFu)), int((pagina / uObjetivo.y) * 64u + (l >> 8u)));
            if (q.x < int(rx & 0xFFFFu) || q.x > int(rx >> 16u) || q.y < int(ry & 0xFFFFu) || q.y > int(ry >> 16u))
                continue;
            uint v16;
            if (escribir(colorSprite(b, q, k), 2u, (raw >> (h * 16u)) & 0xFFFFu, v16))
            {
                nuevo = (nuevo & ~(0xFFFFu << (h * 16u))) | (v16 << (h * 16u));
                cambia = true;
            }
        }
        if (!cambia)
            discard;
        oColor = vec4(uvec4(nuevo & 0xFFu, (nuevo >> 8u) & 0xFFu, (nuevo >> 16u) & 0xFFu, nuevo >> 24u)) / 255.0;
        oFactor = vec4(0.0);
        return;
    }
    uvec4 c = colorSprite(b, p, k);
    if (modo == 1u)
    {
        uint raw = palabraObjetivo(uDestinoTex, f);
        uint fpsm = uExacto.w;
        uint v;
        if (!escribir(c, fpsm, fpsm == 1u ? (raw & 0x00FFFFFFu) : raw, v))
            discard;
        oColor = vec4(uvec4(v & 0xFFu, (v >> 8u) & 0xFFu, (v >> 16u) & 0xFFu, v >> 24u)) / 255.0;
        oFactor = vec4(0.0);
        return;
    }
    bool pasa = pasaAlfa(uModo.z, c.a);
    if ((uModo.w != 2u && !pasa) || (uModo.w == 2u && pasa))
        discard;
    float factor = (uMezcla.y == 0u ? float(c.a) : float(uMezcla.z)) / 128.0;
    uint a = c.a;
    if ((uModo.x & M_FBA) != 0u)
        a |= 0x80u;
    oColor = vec4(vec3(c.rgb) / 255.0, float(a) / 255.0);
    oFactor = vec4(0.0, 0.0, 0.0, factor);
}
)GLSL";

        struct Programa
        {
            GLuint id = 0u;
            std::array<GLint, 12> loc{};
        };

        uint32_t bitsZ(uint32_t zpsm) { return (zpsm & 0x0Fu) >= 2u ? 16u : ((zpsm & 0x0Fu) == 1u ? 24u : 32u); }
        bool formatoZ(uint32_t zpsm) { return zpsm == 0x30u || zpsm == 0x31u || zpsm == 0x32u || zpsm == 0x3Au; }
        bool formatoColor(uint32_t psm) { return psm == 0x00u || psm == 0x01u; }
        bool formatoTextura(uint32_t psm)
        {
            switch (psm)
            {
            case 0x00u: case 0x01u: case 0x02u: case 0x0Au:
            case 0x13u: case 0x1Bu: case 0x14u: case 0x24u: case 0x2Cu:
                return true;
            }
            return false;
        }
        bool indexado(uint32_t psm) { return psm == 0x13u || psm == 0x1Bu || psm == 0x14u || psm == 0x24u || psm == 0x2Cu; }

        uint64_t mezclar(uint64_t h, uint64_t v)
        {
            h ^= v + 0x9E3779B97F4A7C15ull + (h << 6) + (h >> 2);
            return h;
        }

        // Factores de la mezcla del GS (A - B) * C + D en la GPU. Devuelve false si no tiene equivalente.
        struct Mezcla
        {
            GLenum ecuacion = kFuncAdd, fuente = kOne, destino = kZero;
        };
        bool traducirMezcla(uint32_t a, uint32_t b, uint32_t d, Mezcla &m)
        {
            // Coeficiente de Cs y de Cd: k = s * C + t con s en {-1, 0, 1} y t en {0, 1}.
            const int sS = (a == 0u ? 1 : 0) - (b == 0u ? 1 : 0), tS = d == 0u ? 1 : 0;
            const int sD = (a == 1u ? 1 : 0) - (b == 1u ? 1 : 0), tD = d == 1u ? 1 : 0;
            const auto factor = [](int s, int t, GLenum &f) {
                if (s == 0) { f = t ? kOne : kZero; return true; }
                if (s == 1 && t == 0) { f = kSrc1Alpha; return true; }
                if (s == -1 && t == 1) { f = kOneMinusSrc1Alpha; return true; }
                return false; // 1 + C
            };
            if (sS == -1 && tS == 0)
            {
                // Cd * kd - Cs * C
                if (!(sD == -1 && tD == 0) && factor(sD, tD, m.destino))
                {
                    m.ecuacion = kFuncReverseSubtract;
                    m.fuente = kSrc1Alpha;
                    return true;
                }
                return false;
            }
            if (sD == -1 && tD == 0)
            {
                // Cs * ks - Cd * C
                if (factor(sS, tS, m.fuente))
                {
                    m.ecuacion = kFuncSubtract;
                    m.destino = kSrc1Alpha;
                    return true;
                }
                return false;
            }
            m.ecuacion = kFuncAdd;
            return factor(sS, tS, m.fuente) && factor(sD, tD, m.destino);
        }
    }

    void marcarPaginas(Paginas &paginas, uint32_t psm, uint32_t base, uint32_t bw, int x0, int y0, int x1, int y1)
    {
        const GSSwizzle::Format &format = GSSwizzle::GetFormat(psm);
        if (format.kind == GSSwizzle::Kind::Invalid || x1 < x0 || y1 < y0)
            return;
        const uint32_t porFila = std::max<uint32_t>((bw * 64u) >> format.pageShiftX, 1u);
        const uint32_t primera = base >> 5u;
        const bool desborda = (base & 31u) != 0u;
        const uint32_t px0 = static_cast<uint32_t>(std::max(x0, 0)) >> format.pageShiftX;
        const uint32_t px1 = static_cast<uint32_t>(std::max(x1, 0)) >> format.pageShiftX;
        const uint32_t py0 = static_cast<uint32_t>(std::max(y0, 0)) >> format.pageShiftY;
        const uint32_t py1 = static_cast<uint32_t>(std::max(y1, 0)) >> format.pageShiftY;
        if ((py1 - py0 + 1u) * (px1 - px0 + 1u) >= kPaginas)
        {
            paginas.set();
            return;
        }
        for (uint32_t py = py0; py <= py1; ++py)
            for (uint32_t px = px0; px <= px1; ++px)
            {
                const uint32_t pagina = primera + py * porFila + px;
                paginas.set(pagina % kPaginas);
                if (desborda)
                    paginas.set((pagina + 1u) % kPaginas);
            }
    }

    struct Renderizador::Impl
    {
        const Api *gl = nullptr;
        ApiHw hw;
        Programa carga, volcado, decodificar;
        // GOW-Port: variantes de los sombreadores de dibujo según el modo y la fuente (constantes MODO y TIPO): un único
        // sombreador con todas las ramas reserva registros para la peor y la GPU tiene menos ondas en vuelo.
        std::string fuenteDibujoVs, fuenteDibujoFs, fuenteSpriteVs, fuenteSpriteFs;
        std::unordered_map<uint32_t, Programa> variantes;
        const Programa &variante(bool esSprite, uint32_t modo, uint32_t tipo)
        {
            const uint32_t clave = (esSprite ? 0x100u : 0u) | (modo << 4u) | tipo;
            auto it = variantes.find(clave);
            if (it != variantes.end())
                return it->second;
            Programa &prog = variantes[clave];
            const std::string defs = "#define MODO " + std::to_string(modo) + "u\n#define TIPO " + std::to_string(tipo) + "u\n";
            bool ok;
            if (esSprite)
                ok = compilar(prog, {{kVertexShader, fuenteSpriteVs}, {kFragmentShader, insertarDefs(fuenteSpriteFs, defs)}},
                              {"uDestino", "uModo", "uMezcla", "uFuente", "uTextura", "uTexa", "uFuenteObj", "uExacto", "uObjetivo",
                               "uDestinoTex", "uPlano"});
            else
                ok = compilar(prog, {{kVertexShader, fuenteDibujoVs}, {kFragmentShader, insertarDefs(fuenteDibujoFs, defs)}},
                              {"uDestino", "uModo", "uMezcla", "uTexTam", "uTextura", "uExacto", "uDestinoTex"});
            if (!ok)
                std::fprintf(stderr, "[gs-hw-render] variante %x sin compilar\n", clave);
            return prog;
        }
        // Las definiciones van tras la línea #version.
        static std::string insertarDefs(const std::string &fuente, const std::string &defs)
        {
            const size_t fin = fuente.find('\n');
            return fin == std::string::npos ? defs + fuente : fuente.substr(0, fin + 1) + defs + fuente.substr(fin + 1);
        }
        GLuint vao = 0u, fboCarga = 0u, fboDibujo = 0u, vertices = 0u, salida = 0u;
        // GOW-Port: un FBO por pareja de texturas (color, Z). Cambiar los adjuntos de un FBO en cada lote obliga al
        // controlador a revalidarlo y, en AMD, a vaciar las cachés de color y profundidad.
        std::unordered_map<uint64_t, GLuint> fbos;
        GLuint fboPara(GLuint color, GLuint z)
        {
            const uint64_t clave = static_cast<uint64_t>(color) | (static_cast<uint64_t>(z) << 32u);
            auto it = fbos.find(clave);
            if (it != fbos.end())
                return it->second;
            GLuint fbo = 0u;
            gl->GenFramebuffers(1, &fbo);
            gl->BindFramebuffer(kFramebuffer, fbo);
            hw.FramebufferTexture2D(kFramebuffer, kColorAttachment0, kTexture2D, color, 0);
            hw.FramebufferTexture2D(kFramebuffer, kDepthAttachment, kTexture2D, z, 0);
            fbos.emplace(clave, fbo);
            return fbo;
        }
        // Las texturas se borran al cambiar de escala o de tamaño: sus FBO también.
        void olvidarFbos(GLuint tex)
        {
            for (auto it = fbos.begin(); it != fbos.end();)
                if (static_cast<GLuint>(it->first) == tex || static_cast<GLuint>(it->first >> 32u) == tex)
                {
                    gl->DeleteFramebuffers(1, &it->second);
                    it = fbos.erase(it);
                }
                else
                    ++it;
        }
        size_t salidaCapacidad = 0u;
        // GOW-Port: CT16 sobre CT32. Dentro de una página, inversas de la posición de cada media palabra (CT16) y de cada
        // palabra (CT32), para el sombreador; y el bloque CT32 (8x8) que ocupa cada bloque CT16 (16x8): los dos son los
        // mismos 256 bytes.
        GLuint inversas = 0u;
        std::array<uint8_t, 32> bloque16a32{}; // (by * 4 + bx) CT16 -> (by << 3 | bx) CT32
        void crearTablas()
        {
            const GSSwizzle::Format &f16 = GSSwizzle::GetFormat(0x02u), &f32 = GSSwizzle::GetFormat(0x00u);
            std::vector<uint32_t> t(4096u + 2048u, 0u);
            for (uint32_t y = 0; y < 64u; ++y)
                for (uint32_t x = 0; x < 64u; ++x)
                    t[GSSwizzle::Locate(f16, 0u, 1u, x, y).byte >> 1u] = x | (y << 8u);
            std::array<uint8_t, 32> bloque32{};
            for (uint32_t y = 0; y < 32u; ++y)
                for (uint32_t x = 0; x < 64u; ++x)
                {
                    const uint32_t byte = GSSwizzle::Locate(f32, 0u, 1u, x, y).byte;
                    t[4096u + (byte >> 2u)] = x | (y << 8u);
                    bloque32[byte >> 8u] = static_cast<uint8_t>(((y >> 3u) << 3u) | (x >> 3u));
                }
            for (uint32_t by = 0; by < 8u; ++by)
                for (uint32_t bx = 0; bx < 4u; ++bx)
                    bloque16a32[by * 4u + bx] = bloque32[GSSwizzle::Locate(f16, 0u, 1u, bx * 16u, by * 8u).byte >> 8u];
            gl->GenBuffers(1, &inversas);
            gl->BindBuffer(kShaderStorageBuffer, inversas);
            gl->BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(t.size() * 4u), t.data(), kDynamicDraw);
        }
        // Bloque CT32 (en bloques de 8x8 del objetivo de ancho bw) del bloque CT16 (x16 / 16, y16 / 8) con la misma base.
        std::pair<int, int> bloqueCt32(uint32_t bw, int bx16, int by16) const
        {
            const int pagina = (by16 >> 3) * static_cast<int>(bw) + (bx16 >> 2);
            const uint8_t b = bloque16a32[static_cast<size_t>((by16 & 7) * 4 + (bx16 & 3))];
            return {(pagina % static_cast<int>(bw)) * 8 + (b & 7), (pagina / static_cast<int>(bw)) * 4 + (b >> 3)};
        }
        // Bloques del objetivo que escribe el lote abierto (modos exactos) y los que lee de él (copia).
        std::vector<uint8_t> bloquesEscritos;
        bool marcarBloques(std::vector<uint8_t> &mapa, const std::vector<std::pair<int, int>> &bloques, bool comprobar)
        {
            if (mapa.empty())
                mapa.assign(64u * 64u, 0u);
            for (const auto &[bx, by] : bloques)
                if (bx >= 0 && by >= 0 && bx < 64 && by < 64 && comprobar && mapa[static_cast<size_t>(by * 64 + bx)])
                    return true;
            if (!comprobar)
                for (const auto &[bx, by] : bloques)
                    if (bx >= 0 && by >= 0 && bx < 64 && by < 64)
                        mapa[static_cast<size_t>(by * 64 + bx)] = 1u;
            return false;
        }

        // GOW-Port: copia de la zona que lee un sprite de su propio objetivo.
        GLuint copia = 0u;
        GLsizei copiaAncho = 0, copiaAlto = 0;
        // Páginas con contenido dibujado a la resolución interna (cada plano distinto): un sprite no puede leerlas
        // como textura decodificada del plano 0. Las subidas las vuelven a dejar iguales en todos los planos.
        Paginas dibujadas;
        uint32_t ultimoOrigen = 0u;
        Paginas ultimoToca;
        uint32_t escalaActual = 1u;
        uint64_t spritesHw = 0u;
        Estadisticas stats;
        bool diag = false;
        std::unordered_map<uint64_t, uint64_t> detalleRechazo; // (motivo, registro) -> cuenta
        std::unordered_map<std::string, std::pair<uint64_t, double>> censoSprites; // GOW-Port: clase -> (cuenta, área)
        std::unordered_map<std::string, std::pair<uint64_t, double>> censoCopias;  // GOW-Port: cargas y volcados por objetivo
        template <typename O>
        void anotarCopia(const char *tipo, const O &o, int w, int h)
        {
            if (!diag)
                return;
            char k[96];
            std::snprintf(k, sizeof(k), "%s %x/%u/%x%s origen %u", tipo, o.base, o.bw, o.psm, o.profundidad ? "z" : "", origen);
            auto &e = censoCopias[k];
            ++e.first;
            e.second += static_cast<double>(w) * h;
        }
        uint32_t origen = 0u;                                  // quién pide el volcado (diagnóstico)
        std::array<uint64_t, 16> volcadosPor{};

        // GOW-Port: tiempo de GPU por operación (PS2X_GS_HW_DIAG=1 con PS2X_GS_GPU_PROF=1). Espera a las consultas al
        // informar: altera el ritmo, solo para atribuir el coste.
        bool cronometrar = false;
        struct Medida
        {
            uint32_t tipo;
            GLuint a, b;
            uint64_t clave = 0u;
            uint32_t prims = 0u;
        };
        std::unordered_map<uint64_t, std::array<uint64_t, 3>> porClave; // (ns, lotes, primitivas)
        std::vector<Medida> medidas;
        std::vector<GLuint> consultasLibres;
        std::array<uint64_t, 9> nsPor{}; // carga, volcado, decodificar, triángulos, triángulos exactos, sprites GPU, sprites exactos, CT16, subida
        std::array<uint64_t, 9> cuentaPor{};
        GLuint consulta()
        {
            if (consultasLibres.empty())
            {
                consultasLibres.resize(256u);
                gl->GenQueries(256, consultasLibres.data());
            }
            const GLuint q = consultasLibres.back();
            consultasLibres.pop_back();
            return q;
        }
        GLuint cronoInicio()
        {
            if (!cronometrar)
                return 0u;
            const GLuint q = consulta();
            gl->QueryCounter(q, kTimestamp);
            return q;
        }
        void cronoFin(uint32_t tipo, GLuint a)
        {
            if (!cronometrar)
                return;
            const GLuint b = consulta();
            gl->QueryCounter(b, kTimestamp);
            medidas.push_back({tipo, a, b});
        }
        void cronoResolver()
        {
            for (const Medida &m : medidas)
            {
                GLuint64 a = 0u, b = 0u;
                gl->GetQueryObjectui64v(m.a, kQueryResult, &a);
                gl->GetQueryObjectui64v(m.b, kQueryResult, &b);
                nsPor[m.tipo] += b - a;
                ++cuentaPor[m.tipo];
                if (m.clave)
                {
                    auto &e = porClave[m.clave];
                    e[0] += b - a;
                    ++e[1];
                    e[2] += m.prims;
                }
                consultasLibres.push_back(m.a);
                consultasLibres.push_back(m.b);
            }
            medidas.clear();
        }

        // Generación de cada página: sube cuando la ruta software la escribe o se vuelca un objetivo en ella.
        std::array<uint32_t, kPaginas> gen{};
        uint64_t genGlobal = 1u; // sube con cualquier página: si no cambió, nada caducó
        Paginas pendiente;

        struct Objetivo
        {
            uint32_t base = 0u, bw = 0u, psm = 0u;
            bool profundidad = false;
            GLuint tex = 0u;
            uint32_t escala = 0u, ancho = 0u, alto = 0u; // alto válido (líneas nativas cargadas)
            bool valido = false;
            uint64_t firma = 0u, visto = 0u;
            Paginas paginas;
            bool sucio = false;
            int x0 = 0, y0 = 0, x1 = 0, y1 = 0; // rectángulo sucio en píxeles nativos (x1, y1 exclusivos)
            // GOW-Port: generación de cada página cuando se cargó: si cambian unas pocas, solo se cargan esas.
            std::vector<uint32_t> genVisto;
            // Páginas del rectángulo sucio: los volcados se deciden y se anuncian con ellas, no con todo el ancho del
            // objetivo (en GoW el búfer de 1024 de ancho solo usa 640 y su resto es otro búfer).
            Paginas paginasSucias;
        };
        std::unordered_map<uint64_t, Objetivo> objetivos;

        struct Textura
        {
            GLuint tex = 0u;
            uint64_t firma = 0u, visto = 0u;
            Paginas paginas;
            uint32_t ancho = 0u, alto = 0u;
        };
        std::unordered_map<uint64_t, Textura> texturas;

        uint64_t clutId = 0u;

        // Lote abierto.
        struct Lote
        {
            bool abierto = false;
            bool sprite = false;
            Objetivo *fuente = nullptr; // sprite que lee un objetivo (a la resolución interna)
            bool desdeCopia = false;
            bool texaCt24 = false;
            uint32_t tipoFuente = 0u; // ver kSpriteFs
            uint32_t modo = 0u;       // 0 mezcla de la GPU, 1 exacto, 2 CT16 sobre CT32
            std::array<uint64_t, 12> clave{};
            Objetivo *color = nullptr;
            Objetivo *z = nullptr;
            Textura *textura = nullptr;
            bool lineal = false;
            uint32_t wrapS = 0u, wrapT = 0u;
            Mezcla mezcla;
            bool mezclar = false;
            GSDrawState estado{};
            std::vector<uint32_t> datos;
            int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
        } lote;

        void confirmarPendiente()
        {
            if (!pendiente.any())
                return;
            for (size_t p = 0; p < kPaginas; ++p)
                if (pendiente.test(p))
                    ++gen[p];
            pendiente.reset();
            ++genGlobal;
        }

        // Si las páginas no cambiaron desde que se tomó la firma.
        bool vigente(uint64_t &firma, uint64_t &visto, const Paginas &paginas)
        {
            if (visto == genGlobal)
                return true;
            visto = genGlobal;
            return firmaDe(paginas) == firma;
        }

        uint64_t firmaDe(const Paginas &paginas) const
        {
            uint64_t h = 0u;
            for (size_t p = 0; p < kPaginas; ++p)
                if (paginas.test(p))
                    h = mezclar(h, (static_cast<uint64_t>(p) << 32u) | gen[p]);
            return h;
        }

        bool compilar(Programa &prog, std::initializer_list<std::pair<GLenum, std::string>> etapas,
                      std::initializer_list<const char *> uniformes)
        {
            prog.id = gl->CreateProgram();
            std::vector<GLuint> shaders;
            bool ok = true;
            for (const auto &[tipo, cuerpo] : etapas)
            {
                const GLchar *texto = cuerpo.c_str();
                const GLuint s = gl->CreateShader(tipo);
                gl->ShaderSource(s, 1, &texto, nullptr);
                gl->CompileShader(s);
                GLint compilado = 0;
                gl->GetShaderiv(s, kCompileStatus, &compilado);
                if (!compilado)
                {
                    GLint largo = 0;
                    gl->GetShaderiv(s, kInfoLogLength, &largo);
                    std::string log(static_cast<size_t>(std::max(largo, 1)), '\0');
                    gl->GetShaderInfoLog(s, largo, nullptr, log.data());
                    std::fprintf(stderr, "[gs-hw-render] error al compilar: %s\n", log.c_str());
                    ok = false;
                }
                gl->AttachShader(prog.id, s);
                shaders.push_back(s);
            }
            if (ok)
            {
                gl->LinkProgram(prog.id);
                GLint enlazado = 0;
                gl->GetProgramiv(prog.id, kLinkStatus, &enlazado);
                if (!enlazado)
                {
                    GLint largo = 0;
                    gl->GetProgramiv(prog.id, kInfoLogLength, &largo);
                    std::string log(static_cast<size_t>(std::max(largo, 1)), '\0');
                    gl->GetProgramInfoLog(prog.id, largo, nullptr, log.data());
                    std::fprintf(stderr, "[gs-hw-render] error al enlazar: %s\n", log.c_str());
                    ok = false;
                }
            }
            for (GLuint s : shaders)
                gl->DeleteShader(s);
            size_t i = 0u;
            for (const char *nombre : uniformes)
                prog.loc[i++] = gl->GetUniformLocation(prog.id, nombre);
            return ok;
        }

        void vramCompleta(const Vram &v)
        {
            gl->BindBufferRange(kShaderStorageBuffer, 0u, v.buffer, 0, static_cast<GLsizeiptr>(v.planoBytes * v.escala * v.escala));
        }
        void vramPlano0(const Vram &v)
        {
            gl->BindBufferRange(kShaderStorageBuffer, 0u, v.buffer, 0, static_cast<GLsizeiptr>(v.planoBytes));
        }

        bool estadoDibujo = false; // el estado de la GPU es el de un lote (ver emitir)
        void restaurarSiDibujo()
        {
            if (estadoDibujo)
                restaurarEstado();
        }
        void restaurarEstado()
        {
            estadoDibujo = false;
            gl->Disable(kBlend);
            gl->Disable(kDepthTest);
            gl->Disable(kScissorTest);
            hw.DepthMask(1u);
            hw.ColorMask(1u, 1u, 1u, 1u);
            hw.ClipControl(kLowerLeft, kNegativeOneToOne);
            gl->BindFramebuffer(kFramebuffer, 0u);
            hw.ActiveTexture(kTexture0);
            gl->BindTexture(kTexture2D, 0u);
        }

        static uint64_t claveObjetivo(uint32_t base, uint32_t bw, uint32_t psm, bool z)
        {
            return static_cast<uint64_t>(base) | (static_cast<uint64_t>(bw) << 20u) | (static_cast<uint64_t>(psm) << 28u) |
                   (z ? (1ull << 40u) : 0ull);
        }

        Objetivo &objetivo(uint32_t base, uint32_t bw, uint32_t psm, bool z)
        {
            Objetivo &o = objetivos[claveObjetivo(base, bw, psm, z)];
            o.base = base;
            o.bw = bw;
            o.psm = psm;
            o.profundidad = z;
            return o;
        }

        void crearTextura(Objetivo &o, uint32_t escala)
        {
            if (o.tex)
            {
                olvidarFbos(o.tex);
                gl->DeleteTextures(1, &o.tex);
            }
            gl->GenTextures(1, &o.tex);
            gl->BindTexture(kTexture2D, o.tex);
            const GLsizei w = static_cast<GLsizei>(o.bw * 64u * escala), h = static_cast<GLsizei>(512u * escala);
            if (o.profundidad)
                gl->TexImage2D(kTexture2D, 0, static_cast<GLint>(kDepthComponent32F), w, h, 0, kDepthComponent, kFloat, nullptr);
            else
                gl->TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), w, h, 0, kRgba, kUnsignedByte, nullptr);
            gl->TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
            gl->TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
            gl->BindTexture(kTexture2D, 0u);
            o.escala = escala;
            o.ancho = o.bw * 64u;
            o.alto = 0u;
            o.valido = false;
        }

        // Deja el objetivo con las líneas [0, alto) iguales a los planos.
        void validar(Objetivo &o, uint32_t alto, const Vram &v)
        {
            alto = std::min<uint32_t>(alto, 512u);
            if (!o.tex || o.escala != v.escala)
                crearTextura(o, v.escala);
            if (o.valido && o.alto >= alto && vigente(o.firma, o.visto, o.paginas))
                return;
            // Un objetivo con cambios no queda inválido (se vuelca antes de las escrituras de la ruta software); si hay
            // que cargar más líneas, primero se vuelcan sus cambios.
            if (o.sucio)
                volcar(o, v);
            // GOW-Port: carga parcial. Con las mismas líneas y la base alineada a una página, solo cambian las páginas que
            // otro escribió (en GoW, la fila de páginas que el cuadro comparte con el búfer siguiente).
            int cx0 = 0, cy0 = 0, cx1 = static_cast<int>(o.ancho), cy1 = 0;
            const bool parcial = o.valido && o.alto >= alto && (o.base & 31u) == 0u && o.genVisto.size() == kPaginas;
            if (parcial)
            {
                const uint32_t altoPagina = (o.psm & 0x0Fu) >= 2u ? 64u : 32u;
                cx0 = 1 << 30; cy0 = 1 << 30; cx1 = -1; cy1 = -1;
                for (size_t q = 0; q < kPaginas; ++q)
                    if (o.paginas.test(q) && gen[q] != o.genVisto[q])
                    {
                        const uint32_t rel = (static_cast<uint32_t>(q) - (o.base >> 5u)) & (kPaginas - 1u);
                        const int col = static_cast<int>(rel % o.bw), fila = static_cast<int>(rel / o.bw);
                        cx0 = std::min(cx0, col * 64); cx1 = std::max(cx1, col * 64 + 64);
                        cy0 = std::min(cy0, fila * static_cast<int>(altoPagina)); cy1 = std::max(cy1, (fila + 1) * static_cast<int>(altoPagina));
                    }
                cy1 = std::min(cy1, static_cast<int>(o.alto));
                if (cx1 <= cx0 || cy1 <= cy0)
                {
                    // Cambió otra página de la firma (por ejemplo, volcados propios): nada que cargar.
                    o.firma = firmaDe(o.paginas);
                    o.visto = genGlobal;
                    for (size_t q = 0; q < kPaginas; ++q)
                        o.genVisto[q] = gen[q];
                    return;
                }
            }
            else
            {
                o.alto = std::max(alto, o.valido ? o.alto : 0u);
                o.paginas.reset();
                marcarPaginas(o.paginas, o.psm, o.base, o.bw, 0, 0, static_cast<int>(o.ancho) - 1, static_cast<int>(o.alto) - 1);
                cy1 = static_cast<int>(o.alto);
            }
            const uint32_t S = v.escala;
            gl->BindFramebuffer(kFramebuffer, fboCarga);
            hw.FramebufferTexture2D(kFramebuffer, kColorAttachment0, kTexture2D, o.profundidad ? 0u : o.tex, 0);
            hw.FramebufferTexture2D(kFramebuffer, kDepthAttachment, kTexture2D, o.profundidad ? o.tex : 0u, 0);
            gl->Viewport(0, 0, static_cast<GLsizei>(o.ancho * S), static_cast<GLsizei>(o.alto * S));
            gl->Disable(kBlend);
            gl->Enable(kScissorTest);
            hw.Scissor(cx0 * static_cast<GLint>(S), cy0 * static_cast<GLint>(S), (cx1 - cx0) * static_cast<GLsizei>(S), (cy1 - cy0) * static_cast<GLsizei>(S));
            if (o.profundidad)
            {
                gl->Enable(kDepthTest);
                hw.DepthFunc(kAlways);
                hw.DepthMask(1u);
            }
            else
                gl->Disable(kDepthTest);
            hw.ColorMask(1u, 1u, 1u, 1u);
            hw.ClipControl(kLowerLeft, kNegativeOneToOne);
            const GLuint crono = cronoInicio();
            gl->MemBarrier(kAllBarrierBits);
            vramCompleta(v);
            gl->UseProgram(carga.id);
            gl->Uniform4ui(carga.loc[0], S, static_cast<GLuint>(v.planoBytes / 4u), 0u, 0u);
            // GOW-Port: CT24 se carga y se vuelca como CT32: el byte alto del objetivo es el de la VRAM (los dibujos CT24 no lo
            // escriben) y los dibujos CT16 sobre él (los canales de GoW) pueden cambiarlo.
            gl->Uniform4ui(carga.loc[1], o.base, o.bw, o.psm == 0x01u ? 0x00u : o.psm, o.profundidad ? 1u : 0u);
            hw.Uniform4f(carga.loc[2], 1.0f / static_cast<float>(1ull << bitsZ(o.psm)), 0.0f, 0.0f, 0.0f);
            gl->BindVertexArray(vao);
            gl->DrawArrays(kTriangles, 0, 3);
            cronoFin(0u, crono);
            anotarCopia(parcial ? "carga-parcial" : "carga", o, cx1 - cx0, cy1 - cy0);
            vramPlano0(v);
            restaurarEstado();
            o.firma = firmaDe(o.paginas);
            o.visto = genGlobal;
            o.genVisto.assign(gen.begin(), gen.end());
            o.valido = true;
            o.sucio = false;
            ++stats.cargas;
        }

        void volcar(Objetivo &o, const Vram &v)
        {
            if (!o.sucio)
                return;
            const uint32_t S = o.escala;
            const int x0 = std::max(o.x0, 0), y0 = std::max(o.y0, 0);
            const int x1 = std::min<int>(o.x1, static_cast<int>(o.ancho)), y1 = std::min<int>(o.y1, static_cast<int>(o.alto));
            o.sucio = false;
            const bool vuelca = x1 > x0 && y1 > y0 && S == v.escala;
            if (vuelca)
            {
                const GLuint crono = cronoInicio();
                gl->MemBarrier(kAllBarrierBits);
                vramCompleta(v);
                gl->UseProgram(volcado.id);
                gl->Uniform4ui(volcado.loc[0], S, static_cast<GLuint>(v.planoBytes / 4u), 0u, 0u);
                gl->Uniform4ui(volcado.loc[1], o.base, o.bw, o.psm == 0x01u ? 0x00u : o.psm, o.profundidad ? 1u : 0u);
                gl->Uniform4ui(volcado.loc[2], static_cast<GLuint>(x0) * S, static_cast<GLuint>(y0) * S, static_cast<GLuint>(x1) * S,
                               static_cast<GLuint>(y1) * S);
                const uint32_t bits = bitsZ(o.psm);
                hw.Uniform4f(volcado.loc[3], 0.0f, static_cast<float>(1ull << bits), static_cast<float>((1ull << bits) - 1ull), 0.0f);
                hw.ActiveTexture(kTexture0);
                gl->BindTexture(kTexture2D, o.tex);
                hw.Uniform1i(volcado.loc[4], 0);
                const GLuint w = static_cast<GLuint>(x1 - x0) * S, h = static_cast<GLuint>(y1 - y0) * S;
                gl->DispatchCompute((w + 7u) / 8u, (h + 7u) / 8u, 1u);
                gl->MemBarrier(kAllBarrierBits);
                cronoFin(1u, crono);
                anotarCopia("volcado", o, x1 - x0, y1 - y0);
                gl->BindTexture(kTexture2D, 0u);
                vramPlano0(v);
                ++stats.volcados;
                ++volcadosPor[origen & 15u];
            }
            // El volcado cambia la VRAM: las texturas de esas páginas caducan; el objetivo sigue válido.
            const Paginas &cambiadas = vuelca ? o.paginasSucias : o.paginas;
            for (size_t p = 0; p < kPaginas; ++p)
                if (cambiadas.test(p))
                {
                    ++gen[p];
                    if (o.genVisto.size() == kPaginas)
                        o.genVisto[p] = gen[p];
                }
            ++genGlobal;
            o.firma = firmaDe(o.paginas);
            o.visto = genGlobal;
        }

        Textura *textura(const GSDrawState &st, uint32_t clutSlot, const Vram &v)
        {
            const GSTex0Reg &t = st.context.tex0;
            const uint32_t w = std::clamp<uint32_t>(st.textureWidth, 1u, 1024u), h = std::clamp<uint32_t>(st.textureHeight, 1u, 1024u);
            uint64_t clave = mezclar(0u, t.tbp0);
            clave = mezclar(clave, static_cast<uint64_t>(t.tbw) | (static_cast<uint64_t>(t.psm) << 8u) | (static_cast<uint64_t>(w) << 16u) |
                                       (static_cast<uint64_t>(h) << 32u));
            if (indexado(t.psm))
                clave = mezclar(mezclar(clave, static_cast<uint64_t>(t.cpsm) | (static_cast<uint64_t>(t.csm) << 8u) |
                                                   (static_cast<uint64_t>(t.csa) << 16u)),
                                clutId);
            const bool usaTexa = t.psm == 0x01u || t.psm == 0x02u || t.psm == 0x0Au || t.psm == 0x31u || t.psm == 0x32u || t.psm == 0x3Au ||
                                 (indexado(t.psm) && (t.cpsm == 0x01u || t.cpsm == 0x02u || t.cpsm == 0x0Au));
            if (usaTexa)
                clave = mezclar(clave, static_cast<uint64_t>(st.texa.ta0) | (st.texa.aem ? 0x100ull : 0ull) |
                                           (static_cast<uint64_t>(st.texa.ta1) << 16u));
            Textura &e = texturas[clave];
            if (e.tex && vigente(e.firma, e.visto, e.paginas))
            {
                ++stats.aciertos;
                return &e;
            }
            if (texturas.size() > 4096u)
            {
                for (auto &[k, x] : texturas)
                    if (x.tex && &x != &e)
                        gl->DeleteTextures(1, &x.tex);
                Textura conservada = e;
                texturas.clear();
                texturas[clave] = conservada;
            }
            Textura &n = texturas[clave];
            n.paginas.reset();
            marcarPaginas(n.paginas, t.psm, t.tbp0, std::max<uint32_t>(t.tbw, 1u), 0, 0, static_cast<int>(w) - 1, static_cast<int>(h) - 1);
            const size_t bytes = static_cast<size_t>(w) * h * 4u;
            if (bytes > salidaCapacidad)
            {
                gl->BindBuffer(kShaderStorageBuffer, salida);
                gl->BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(bytes), nullptr, kDynamicDraw);
                salidaCapacidad = bytes;
            }
            const GLuint crono = cronoInicio();
            gl->BindBufferBase(kShaderStorageBuffer, 12u, salida);
            gl->MemBarrier(kAllBarrierBits);
            gl->UseProgram(decodificar.id);
            gl->Uniform4ui(decodificar.loc[0], t.tbp0, std::max<uint32_t>(t.tbw, 1u), t.psm, w | (h << 16u));
            gl->Uniform4ui(decodificar.loc[1], t.cpsm, t.csm, t.csa, clutSlot);
            gl->Uniform4ui(decodificar.loc[2], st.texa.ta0, st.texa.aem ? 1u : 0u, st.texa.ta1, 0u);
            gl->DispatchCompute((w + 7u) / 8u, (h + 7u) / 8u, 1u);
            gl->MemBarrier(kAllBarrierBits);
            if (!n.tex || n.ancho != w || n.alto != h)
            {
                if (n.tex)
                    gl->DeleteTextures(1, &n.tex);
                gl->GenTextures(1, &n.tex);
                gl->BindTexture(kTexture2D, n.tex);
                gl->TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, kRgba,
                               kUnsignedByte, nullptr);
                // Sin mipmaps: con el filtro por defecto la textura estaría incompleta (los sprites la leen con texelFetch).
                gl->TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
                gl->TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
                n.ancho = w;
                n.alto = h;
            }
            else
                gl->BindTexture(kTexture2D, n.tex);
            gl->BindBuffer(kPixelUnpackBuffer, salida);
            gl->TexSubImage2D(kTexture2D, 0, 0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h), kRgba, kUnsignedByte, nullptr);
            gl->BindBuffer(kPixelUnpackBuffer, 0u);
            cronoFin(2u, crono);
            gl->BindTexture(kTexture2D, 0u);
            n.firma = firmaDe(n.paginas);
            n.visto = genGlobal;
            ++stats.texturas;
            (void)v;
            return &n;
        }

        void emitir(const Vram &v)
        {
            Lote &l = lote;
            if (!l.abierto)
                return;
            l.abierto = false;
            if (l.datos.empty())
                return;
            const GSDrawState &st = l.estado;
            const GSContext &c = st.context;
            Objetivo *color = l.color;
            Objetivo *z = l.z;
            const uint32_t S = v.escala;
            if (l.sprite)
                dibujadas |= color->paginas;
            const GLuint cronoSubida = cronoInicio();
            gl->BindBuffer(kShaderStorageBuffer, vertices);
            gl->BufferData(kShaderStorageBuffer, static_cast<GLsizeiptr>(l.datos.size() * 4u), l.datos.data(), kStreamDrawUsage);
            gl->BindBufferBase(kShaderStorageBuffer, 11u, vertices);
            // GOW-Port: sin glMemoryBarrier: BufferData ya está ordenado con los dibujos, y los dispatch que escriben lo
            // que se lee aquí (decodificación, volcados, ruta de cómputo) ponen su propia barrera. Una barrera completa
            // por lote vaciaba la GPU unas cien veces por cuadro.
            cronoFin(8u, cronoSubida);
            const GLuint crono = cronoInicio();
            gl->BindFramebuffer(kFramebuffer, fboPara(color->tex, z ? z->tex : 0u));
            gl->Viewport(0, 0, static_cast<GLsizei>(color->ancho * S), static_cast<GLsizei>(512u * S));
            // En el modo 2 el scissor es de coordenadas CT16: ya está aplicado al rectángulo de cada sprite.
            if (l.sprite && l.modo == 2u)
                gl->Disable(kScissorTest);
            else
            {
                gl->Enable(kScissorTest);
                const int sx0 = c.scissor.x0, sy0 = c.scissor.y0;
                const int sx1 = std::min<int>(c.scissor.x1 + 1, static_cast<int>(color->ancho));
                const int sy1 = std::min<int>(c.scissor.y1 + 1, 512);
                hw.Scissor(sx0 * static_cast<GLint>(S), sy0 * static_cast<GLint>(S), std::max(sx1 - sx0, 0) * static_cast<GLsizei>(S),
                           std::max(sy1 - sy0, 0) * static_cast<GLsizei>(S));
            }
            hw.ClipControl(kLowerLeft, kZeroToOne);
            const uint32_t test = static_cast<uint32_t>(c.test);
            const uint32_t ztst = (test >> 17u) & 3u;
            if (z)
            {
                gl->Enable(kDepthTest);
                hw.DepthFunc(ztst == 2u ? kGequal : (ztst == 3u ? kGreater : (ztst == 0u ? kNever : kAlways)));
            }
            else
                gl->Disable(kDepthTest);
            const bool escribeZ = z && !c.zbuf.zmask;
            if (!l.sprite)
                dibujadas |= color->paginas;
            if (l.mezclar)
            {
                gl->Enable(kBlend);
                hw.BlendEquationSeparate(l.mezcla.ecuacion, kFuncAdd);
                hw.BlendFuncSeparate(l.mezcla.fuente, l.mezcla.destino, kOne, kZero);
            }
            else
                gl->Disable(kBlend);
            const uint32_t fbmsk = c.frame.fbmsk;
            const GLboolean mr = (fbmsk & 0xFFu) == 0u, mg = (fbmsk & 0xFF00u) == 0u, mb = (fbmsk & 0xFF0000u) == 0u;
            const GLboolean ma = (fbmsk & 0xFF000000u) == 0u && c.frame.psm != 0x01u;
            const Programa &prog = variante(l.sprite, l.modo, l.sprite ? l.tipoFuente : 0u);
            gl->UseProgram(prog.id);
            const float zEsc = z ? 1.0f / static_cast<float>(1ull << bitsZ(c.zbuf.psm)) : 0.0f;
            hw.Uniform4f(prog.loc[0], static_cast<float>(S), 2.0f / static_cast<float>(color->ancho * S), 2.0f / static_cast<float>(512u * S), zEsc);
            uint32_t banderas = (st.prim.tme ? 1u : 0u) | (st.prim.iip ? 2u : 0u) | (st.prim.fst ? 4u : 0u) | (st.prim.fge ? 8u : 0u) |
                                ((c.fba & 1u) != 0u ? 16u : 0u) | (l.sprite && st.linearFilter ? 32u : 0u);
            const uint32_t fogCol = static_cast<uint32_t>(st.fogR) | (static_cast<uint32_t>(st.fogG) << 8u) | (static_cast<uint32_t>(st.fogB) << 16u);
            const uint32_t csel = static_cast<uint32_t>((c.alpha >> 4u) & 3u);
            gl->Uniform4ui(prog.loc[2], fogCol, csel, static_cast<uint32_t>((c.alpha >> 32u) & 0xFFu), 0u);
            bool vramEntera = false;
            if (l.sprite)
            {
                const uint32_t tw = std::clamp<uint32_t>(st.textureWidth, 1u, 1024u), th = std::clamp<uint32_t>(st.textureHeight, 1u, 1024u);
                GLuint tex = l.textura ? l.textura->tex : 0u;
                if (l.fuente)
                    tex = l.desdeCopia ? copia : l.fuente->tex;
                hw.ActiveTexture(kTexture0);
                gl->BindTexture(kTexture2D, tex);
                hw.Uniform1i(prog.loc[4], 0);
                gl->Uniform4ui(prog.loc[3], l.tipoFuente, S, tw | (th << 16u), l.wrapS | (l.wrapT << 2u) | (l.texaCt24 ? 16u : 0u));
                gl->Uniform4ui(prog.loc[5], st.texa.ta0, st.texa.aem ? 1u : 0u, st.texa.ta1, 0u);
                gl->Uniform4ui(prog.loc[6], c.tex0.tbp0, std::max<uint32_t>(c.tex0.tbw, 1u), c.tex0.psm, 0u);
                const uint32_t alfa = static_cast<uint32_t>(c.alpha & 0xFFu) | (static_cast<uint32_t>((c.alpha >> 32u) & 0xFFu) << 8u) |
                                      (st.pabe ? 1u << 16u : 0u) | ((st.colclamp & 1u) == 0u ? 1u << 17u : 0u) | (st.prim.abe ? 1u << 18u : 0u);
                gl->Uniform4ui(prog.loc[7], l.modo, c.frame.fbmsk, alfa, c.frame.psm);
                gl->Uniform4ui(prog.loc[8], color->base, color->bw, 0u, 0u);
                gl->Uniform4ui(prog.loc[10], S, static_cast<GLuint>(v.planoBytes / 4u), 0u, 0u);
                gl->BindBufferBase(kShaderStorageBuffer, 13u, inversas);
                if (l.modo != 0u)
                {
                    // El sombreador lee el píxel que escribe: lo dibujado antes tiene que estar visible.
                    hw.ActiveTexture(kTexture0 + 1u);
                    gl->BindTexture(kTexture2D, color->tex);
                    hw.Uniform1i(prog.loc[9], 1);
                    hw.ActiveTexture(kTexture0);
                    hw.TextureBarrier();
                }
                if (l.tipoFuente == 3u)
                {
                    gl->MemBarrier(kAllBarrierBits);
                    vramCompleta(v);
                    vramEntera = true;
                }
            }
            if (!l.sprite)
            {
                // GOW-Port: modo exacto de los triángulos (uExacto.x = 0: mezcla de la GPU).
                const uint32_t alfa = static_cast<uint32_t>(c.alpha & 0xFFu) | (static_cast<uint32_t>((c.alpha >> 32u) & 0xFFu) << 8u) |
                                      (st.pabe ? 1u << 16u : 0u) | ((st.colclamp & 1u) == 0u ? 1u << 17u : 0u) | (st.prim.abe ? 1u << 18u : 0u);
                gl->Uniform4ui(prog.loc[5], l.modo, c.frame.fbmsk, alfa, c.frame.psm);
                if (l.modo != 0u)
                {
                    hw.ActiveTexture(kTexture0 + 1u);
                    gl->BindTexture(kTexture2D, color->tex);
                    hw.Uniform1i(prog.loc[6], 1);
                    hw.ActiveTexture(kTexture0);
                    hw.TextureBarrier();
                }
            }
            if (!l.sprite && l.textura)
            {
                hw.ActiveTexture(kTexture0);
                gl->BindTexture(kTexture2D, l.textura->tex);
                gl->TexParameteri(kTexture2D, kTextureMinFilter, l.lineal ? kLinear : kNearest);
                gl->TexParameteri(kTexture2D, kTextureMagFilter, l.lineal ? kLinear : kNearest);
                gl->TexParameteri(kTexture2D, kTextureWrapS, l.wrapS == 0u ? kRepeat : kClampToEdge);
                gl->TexParameteri(kTexture2D, kTextureWrapT, l.wrapT == 0u ? kRepeat : kClampToEdge);
                hw.Uniform1i(prog.loc[4], 0);
                hw.Uniform4f(prog.loc[3], static_cast<float>(l.textura->ancho), static_cast<float>(l.textura->alto), 0.0f, 0.0f);
            }
            gl->BindVertexArray(vao);
            const GLsizei cuenta = static_cast<GLsizei>(l.sprite ? l.datos.size() / 16u * 6u : l.datos.size() / 12u);
            const uint32_t modoTex = static_cast<uint32_t>(c.tex0.tfx) | (static_cast<uint32_t>(c.tex0.tcc) << 8u);
            const uint32_t afail = (test >> 12u) & 3u;
            const bool exacto = l.modo != 0u;
            const bool dosPasadas = !exacto && (test & 1u) != 0u && afail != 0u;
            // Primera pasada: los píxeles que pasan la prueba de alfa (todos si no hay prueba). En los modos exactos el
            // sombreador aplica la máscara y la prueba de alfa; el CT24 conserva el byte alto.
            if (exacto)
                hw.ColorMask(1u, 1u, 1u, l.modo == 2u || c.frame.psm != 0x01u);
            else
                hw.ColorMask(mr, mg, mb, ma);
            hw.DepthMask(escribeZ ? 1u : 0u);
            gl->Uniform4ui(prog.loc[1], banderas, modoTex, test, dosPasadas ? 1u : 0u);
            gl->DrawArrays(kTriangles, 0, cuenta);
            if (dosPasadas)
            {
                // Los que fallan: FB_ONLY escribe color, ZB_ONLY solo Z, RGB_ONLY solo RGB (en CT24 como FB_ONLY).
                const bool rgbSolo = afail == 3u && c.frame.psm == 0x00u;
                if (afail == 2u)
                    hw.ColorMask(0u, 0u, 0u, 0u);
                else
                    hw.ColorMask(mr, mg, mb, rgbSolo ? 0u : ma);
                hw.DepthMask(afail == 2u && escribeZ ? 1u : 0u);
                gl->Uniform4ui(prog.loc[1], banderas, modoTex, test, 2u);
                gl->DrawArrays(kTriangles, 0, cuenta);
            }
            cronoFin(l.sprite ? 5u + l.modo : 3u + l.modo, crono);
            if (cronometrar && !medidas.empty())
            {
                // Clave: objetivo, Z, formato de textura, mezcla, prueba de alfa, sprite.
                Medida &md = medidas.back();
                md.clave = static_cast<uint64_t>(color->base) | (static_cast<uint64_t>(z ? 1u : 0u) << 20u) |
                           (static_cast<uint64_t>(st.prim.tme ? c.tex0.psm : 0xFFu) << 24u) | (static_cast<uint64_t>(st.prim.abe ? (c.alpha & 0xFFu) : 0xFFu) << 32u) |
                           (static_cast<uint64_t>(test & 0xFFFu) << 40u) | (static_cast<uint64_t>(l.sprite) << 56u) | (1ull << 63u);
                md.prims = static_cast<uint32_t>(cuenta / 3);
            }
            if (vramEntera)
                vramPlano0(v);
            if (exacto)
            {
                hw.ActiveTexture(kTexture0 + 1u);
                gl->BindTexture(kTexture2D, 0u);
                hw.ActiveTexture(kTexture0);
            }
            // GOW-Port: el estado de la GPU (FBO, mezcla, Z, scissor) se queda: cada lote pone el suyo y se restaura al
            // pasar a la ruta software. Volver al FBO 0 tras cada lote obligaba a vaciar las cachés de color y Z.
            estadoDibujo = true;
            const auto ensuciar = [&](Objetivo *o) {
                if (!o)
                    return;
                if (!o->sucio)
                {
                    o->x0 = l.x0; o->y0 = l.y0; o->x1 = l.x1; o->y1 = l.y1;
                    o->sucio = true;
                }
                else
                {
                    o->x0 = std::min(o->x0, l.x0); o->y0 = std::min(o->y0, l.y0);
                    o->x1 = std::max(o->x1, l.x1); o->y1 = std::max(o->y1, l.y1);
                }
                o->paginasSucias.reset();
                marcarPaginas(o->paginasSucias, o->psm, o->base, o->bw, std::max(o->x0, 0), std::max(o->y0, 0),
                              std::min<int>(o->x1, static_cast<int>(o->ancho)) - 1, std::min<int>(o->y1, static_cast<int>(o->alto)) - 1);
            };
            ensuciar(color);
            if (escribeZ)
                ensuciar(z);
            ++stats.dibujos;
            l.datos.clear();
        }

        // GOW-Port: de dónde lee un sprite texturizado. motivo 0: se puede dibujar; objetivo: el objetivo que lee a la
        // resolución interna (nullptr: textura decodificada del plano 0); u0..v1: texels que puede leer (inclusivos).
        struct FuenteSprite
        {
            uint32_t motivo = 0u;
            uint32_t tipo = 0u; // 0 decodificada, 1 objetivo, 2 objetivo CT32 como CT16, 3 planos
            Objetivo *objetivo = nullptr;
            bool texaCt24 = false;
            int u0 = 0, v0 = 0, u1 = -1, v1 = -1;
        };
        static bool sinPaleta(uint32_t psm)
        {
            switch (psm)
            {
            case 0x00u: case 0x01u: case 0x02u: case 0x0Au: case 0x30u: case 0x31u: case 0x32u: case 0x3Au:
                return true;
            }
            return false;
        }
        Objetivo *objetivoColor(uint32_t base, uint32_t bw, uint32_t psm)
        {
            auto it = objetivos.find(claveObjetivo(base, bw, psm, false));
            return it != objetivos.end() && it->second.tex ? &it->second : nullptr;
        }
        // Objetivo de 32 bits por píxel (CT32 o, si no hay, CT24) en el que cae un dibujo o una lectura CT16.
        Objetivo *objetivoPalabras(uint32_t base, uint32_t bw)
        {
            if ((base & 31u) != 0u)
                return nullptr;
            Objetivo *o = objetivoColor(base, bw, 0x00u);
            return o ? o : objetivoColor(base, bw, 0x01u);
        }
        FuenteSprite fuenteSprite(const GSPrimitiveBatch &batch)
        {
            FuenteSprite r;
            const GSDrawState &st = batch.state;
            const GSContext &c = st.context;
            const GSTex0Reg &t = c.tex0;
            const GSVertex &a = batch.vertices[0], &b = batch.vertices[1];
            const int W = static_cast<int>(std::clamp<uint32_t>(st.textureWidth, 1u, 1024u));
            const int H = static_cast<int>(std::clamp<uint32_t>(st.textureHeight, 1u, 1024u));
            float ua, ub, va, vb;
            if (st.prim.fst)
            {
                ua = static_cast<float>(a.u) / 16.0f; ub = static_cast<float>(b.u) / 16.0f;
                va = static_cast<float>(a.v) / 16.0f; vb = static_cast<float>(b.v) / 16.0f;
            }
            else
            {
                const auto q = [](float x) { return std::abs(x) > 1.0e-8f ? x : 1.0f; };
                ua = a.s / q(a.q) * W; ub = b.s / q(b.q) * W;
                va = a.t / q(a.q) * H; vb = b.t / q(b.q) * H;
            }
            // Texels posibles con el filtro (bilineal: uno más a cada lado) y el modo de repetición.
            // Texels del primer y del último píxel dibujados, con la misma cuenta (precise) que kSpriteFs. El bilineal lee
            // el siguiente.
            {
                const GSSpriteAxis ax = gsSpriteAxis(a.x, b.x, static_cast<float>(c.xyoffset.ofx) / 16.0f);
                const GSSpriteAxis ay = gsSpriteAxis(a.y, b.y, static_cast<float>(c.xyoffset.ofy) / 16.0f);
                const int px0 = std::clamp<int>(ax.first, c.scissor.x0, c.scissor.x1), px1 = std::clamp<int>(ax.last, c.scissor.x0, c.scissor.x1);
                const int py0 = std::clamp<int>(ay.first, c.scissor.y0, c.scissor.y1), py1 = std::clamp<int>(ay.last, c.scissor.y0, c.scissor.y1);
                const auto texel = [&](const GSSpriteAxis &e, int pixel, float t0, float t1) {
                    float t = t0 + (t1 - t0) * ((static_cast<float>(pixel) - e.origin) * e.scale);
                    if (st.prim.fst)
                        t = static_cast<float>(std::clamp(static_cast<int>(t * 16.0f + 0.5f), 0, 0xFFFF)) / 16.0f;
                    return st.linearFilter ? t - 0.5f : t;
                };
                const float tu0 = texel(ax, px0, ua, ub), tu1 = texel(ax, px1, ua, ub);
                const float tv0 = texel(ay, py0, va, vb), tv1 = texel(ay, py1, va, vb);
                const int extra = st.linearFilter ? 1 : 0;
                r.u0 = static_cast<int>(std::floor(std::min(tu0, tu1)));
                r.u1 = static_cast<int>(std::floor(std::max(tu0, tu1))) + extra;
                r.v0 = static_cast<int>(std::floor(std::min(tv0, tv1)));
                r.v1 = static_cast<int>(std::floor(std::max(tv0, tv1))) + extra;
                // El margen no sale de lo que el sprite puede leer.
                r.u0 = std::max(r.u0, static_cast<int>(std::floor(std::min(ua, ub))) - extra);
                r.v0 = std::max(r.v0, static_cast<int>(std::floor(std::min(va, vb))) - extra);
                r.u1 = std::min(r.u1, static_cast<int>(std::ceil(std::max(ua, ub))) + extra);
                r.v1 = std::min(r.v1, static_cast<int>(std::ceil(std::max(va, vb))) + extra);
                if (r.u0 >= 0 && r.u0 > r.u1) r.u0 = r.u1;
                if (r.v0 >= 0 && r.v0 > r.v1) r.v0 = r.v1;
            }
            const uint32_t wms = static_cast<uint32_t>(c.clamp & 3u), wmt = static_cast<uint32_t>((c.clamp >> 2u) & 3u);
            if (wms == 1u) { r.u0 = std::clamp(r.u0, 0, W - 1); r.u1 = std::clamp(r.u1, 0, W - 1); }
            if (wmt == 1u) { r.v0 = std::clamp(r.v0, 0, H - 1); r.v1 = std::clamp(r.v1, 0, H - 1); }
            const bool dentro = r.u0 >= 0 && r.v0 >= 0 && r.u1 < W && r.v1 < H;
            // Objetivo con la misma dirección y ancho: CT32 o CT24 leídos en su formato (o CT32 como CT24 con TEXA).
            Objetivo *o = (t.psm == 0x00u || t.psm == 0x01u) ? objetivoColor(t.tbp0, t.tbw, t.psm) : nullptr;
            if (!o && t.psm == 0x01u)
            {
                o = objetivoColor(t.tbp0, t.tbw, 0x00u);
                r.texaCt24 = o != nullptr;
            }
            else if (o && t.psm == 0x01u)
                r.texaCt24 = true;
            // Pasado el ancho del búfer, el GS sigue en la fila de páginas siguiente (misma dirección lineal de página);
            // kSpriteFs hace la misma cuenta. Hace falta que esas filas estén en el objetivo.
            const auto filasPorPaginas = [](int u1, int v1, uint32_t bw, int altoPaginaFuente, int altoPaginaObjetivo) {
                const int lineal = (v1 / altoPaginaFuente) * static_cast<int>(bw) + u1 / 64;
                return (lineal / static_cast<int>(bw) + 1) * altoPaginaObjetivo;
            };
            if (o)
            {
                if (!dentro || filasPorPaginas(r.u1, r.v1, o->bw, 32, 32) > 512 || (o->base & 31u) != 0u)
                    r.motivo = 11u;
                r.objetivo = o;
                r.tipo = 1u;
                return r;
            }
            // Un objetivo CT32 leído como CT16 (los canales de GoW): dos píxeles CT16 por píxel del objetivo.
            if (t.psm == 0x02u)
                if (Objetivo *o32 = objetivoPalabras(t.tbp0, t.tbw))
                {
                    if (!dentro || filasPorPaginas(r.u1, r.v1, o32->bw, 64, 32) > 512)
                        r.motivo = 11u;
                    r.objetivo = o32;
                    r.tipo = 2u;
                    return r;
                }
            // Textura corriente: si sale de páginas dibujadas a la resolución interna (sus planos difieren del 0), se lee
            // de los planos; las indexadas no se pueden.
            if (escalaActual > 1u)
            {
                // Solo los texels que lee (con la repetición, toda la textura).
                Paginas tex;
                if (dentro)
                    marcarPaginas(tex, t.psm, t.tbp0, std::max<uint32_t>(t.tbw, 1u), r.u0, r.v0, r.u1, r.v1);
                else
                    marcarPaginas(tex, t.psm, t.tbp0, std::max<uint32_t>(t.tbw, 1u), 0, 0, W - 1, H - 1);
                Paginas ocupadas = dibujadas;
                for (const auto &[k, x] : objetivos)
                    ocupadas |= x.paginas;
                if ((tex & ocupadas).any())
                {
                    r.tipo = 3u;
                    if (!sinPaleta(t.psm))
                        r.motivo = 10u;
                    // No puede leer las páginas del objetivo en el que dibuja (estarían en la textura, no en los planos).
                    Paginas destino;
                    marcarPaginas(destino, c.frame.psm, c.frame.fbp << 5u, std::max<uint32_t>(c.frame.fbw, 1u), 0, 0,
                                  static_cast<int>(c.frame.fbw) * 64 - 1, static_cast<int>(c.scissor.y1));
                    if ((tex & destino).any())
                        r.motivo = 10u;
                }
            }
            return r;
        }

        // GOW-Port: modo de un triángulo: 1 (exacto, lee el destino) si la mezcla no tiene equivalente en la GPU (C = Ad,
        // PABE), con DATE o con FBMSK por bits; COLCLAMP=0 solo con PS2X_GS_HW_EXACTO=1. PS2X_GS_HW_TRI_EXACTO=0 los deja
        // en la ruta software.
        uint32_t modoTriangulo(const GSDrawState &st) const
        {
            const GSContext &c = st.context;
            const uint32_t test = static_cast<uint32_t>(c.test);
            if (((test >> 14u) & 1u) != 0u)
                return 1u;
            for (uint32_t b = 0; b < 4u; ++b)
            {
                const uint32_t byte = (c.frame.fbmsk >> (b * 8u)) & 0xFFu;
                if (byte != 0u && byte != 0xFFu)
                    return 1u;
            }
            if (st.prim.abe)
            {
                const uint32_t a = static_cast<uint32_t>(c.alpha & 3u), b = static_cast<uint32_t>((c.alpha >> 2u) & 3u);
                const uint32_t cs = static_cast<uint32_t>((c.alpha >> 4u) & 3u), d = static_cast<uint32_t>((c.alpha >> 6u) & 3u);
                static const bool exactoColclamp = [] { const char *v = std::getenv("PS2X_GS_HW_EXACTO"); return v && v[0] == '1'; }();
                Mezcla mz;
                if (cs == 1u || cs == 3u || a == 3u || b == 3u || d == 3u || !traducirMezcla(a, b, d, mz) || st.pabe ||
                    ((st.colclamp & 1u) == 0u && exactoColclamp))
                    return 1u;
            }
            return 0u;
        }

        // Modo de un sprite admitido: 2 si es CT16 sobre un objetivo CT32, 1 si necesita leer el destino (DATE, FBMSK
        // por bits, mezcla con Ad o PABE, COLCLAMP=0), 0 si basta la mezcla de la GPU.
        uint32_t modoSprite(const GSDrawState &st) const
        {
            const GSContext &c = st.context;
            if (c.frame.psm == 0x02u)
                return 2u;
            const uint32_t test = static_cast<uint32_t>(c.test);
            if (((test >> 14u) & 1u) != 0u)
                return 1u;
            for (uint32_t b = 0; b < 4u; ++b)
            {
                const uint32_t byte = (c.frame.fbmsk >> (b * 8u)) & 0xFFu;
                if (byte != 0u && byte != 0xFFu)
                    return 1u;
            }
            if (st.prim.abe)
            {
                const uint32_t a = static_cast<uint32_t>(c.alpha & 3u), b = static_cast<uint32_t>((c.alpha >> 2u) & 3u);
                const uint32_t cs = static_cast<uint32_t>((c.alpha >> 4u) & 3u), d = static_cast<uint32_t>((c.alpha >> 6u) & 3u);
                Mezcla mz;
                if (cs == 1u || cs == 3u || a == 3u || b == 3u || d == 3u || !traducirMezcla(a, b, d, mz) || st.pabe ||
                    (st.colclamp & 1u) == 0u)
                    return 1u;
            }
            return 0u;
        }

        // Copia la zona [x0, x1) x [y0, y1) (píxeles nativos) del objetivo para leerla mientras se dibuja en él.
        void copiar(const Objetivo &o, int x0, int y0, int x1, int y1)
        {
            const GLsizei w = static_cast<GLsizei>(o.bw * 64u * o.escala), h = static_cast<GLsizei>(512u * o.escala);
            if (!copia || copiaAncho != w || copiaAlto != h)
            {
                if (copia)
                    gl->DeleteTextures(1, &copia);
                gl->GenTextures(1, &copia);
                gl->BindTexture(kTexture2D, copia);
                gl->TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), w, h, 0, kRgba, kUnsignedByte, nullptr);
                gl->TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
                gl->TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
                gl->BindTexture(kTexture2D, 0u);
                copiaAncho = w;
                copiaAlto = h;
            }
            const int S = static_cast<int>(o.escala);
            x0 = std::max(x0, 0); y0 = std::max(y0, 0);
            x1 = std::min<int>(x1, static_cast<int>(o.ancho)); y1 = std::min(y1, 512);
            if (x1 <= x0 || y1 <= y0)
                return;
            hw.CopyImageSubData(o.tex, kTexture2D, 0, x0 * S, y0 * S, 0, copia, kTexture2D, 0, x0 * S, y0 * S, 0, (x1 - x0) * S, (y1 - y0) * S, 1);
        }

        void dibujarSprite(const GSPrimitiveBatch &batch, const Vram &v, uint32_t clutSlot)
        {
            const GSDrawState &st = batch.state;
            const GSContext &c = st.context;
            const GSVertex &v0 = batch.vertices[0], &v1 = batch.vertices[1];
            const GSSpriteAxis ax = gsSpriteAxis(v0.x, v1.x, static_cast<float>(c.xyoffset.ofx) / 16.0f);
            const GSSpriteAxis ay = gsSpriteAxis(v0.y, v1.y, static_cast<float>(c.xyoffset.ofy) / 16.0f);
            if (ax.last < ax.first || ay.last < ay.first || ax.last < c.scissor.x0 || ax.first > c.scissor.x1 || ay.last < c.scissor.y0 ||
                ay.first > c.scissor.y1)
                return;
            const int x0 = std::clamp<int>(ax.first, c.scissor.x0, c.scissor.x1), x1 = std::clamp<int>(ax.last, c.scissor.x0, c.scissor.x1);
            const int y0 = std::clamp<int>(ay.first, c.scissor.y0, c.scissor.y1), y1 = std::clamp<int>(ay.last, c.scissor.y0, c.scissor.y1);
            const uint32_t test = static_cast<uint32_t>(c.test);
            const bool zte = (test & 0x10000u) != 0u;
            const uint32_t ztst = zte ? (test >> 17u) & 3u : 1u;
            if (ztst == 0u)
                return;
            const bool usaZ = zte && (ztst >= 2u || !c.zbuf.zmask);
            const uint32_t fbw = c.frame.fbw;
            const uint32_t modo = modoSprite(st);
            // En el modo 2 el objetivo es el CT32 de la misma dirección; las coordenadas del sprite son CT16.
            Objetivo *palabras = modo == 2u ? objetivoPalabras(c.frame.fbp << 5u, fbw) : nullptr;
            const uint32_t psmObjetivo = palabras ? palabras->psm : c.frame.psm;
            FuenteSprite fuente;
            if (st.prim.tme)
                fuente = fuenteSprite(batch);
            Lote &l = lote;
            const bool propio = fuente.objetivo && fuente.objetivo->base == (c.frame.fbp << 5u) && fuente.objetivo->bw == fbw &&
                                fuente.objetivo->psm == psmObjetivo;
            // Bloques CT32 (8x8 nativos) que escribe y, si lee su propio objetivo, los que lee.
            std::vector<std::pair<int, int>> escritos, leidos;
            const auto bloquesRect = [&](std::vector<std::pair<int, int>> &out, int rx0, int ry0, int rx1, int ry1, bool ct16) {
                if (ct16)
                {
                    for (int by = ry0 >> 3; by <= (ry1 >> 3); ++by)
                        for (int bx = rx0 >> 4; bx <= (rx1 >> 4); ++bx)
                            out.push_back(bloqueCt32(fbw, bx, by));
                }
                else
                    for (int by = ry0 >> 3; by <= (ry1 >> 3); ++by)
                        for (int bx = rx0 >> 3; bx <= (rx1 >> 3); ++bx)
                        {
                            // Pasado el ancho, la fila de páginas siguiente (como en kSpriteFs).
                            const int ancho = static_cast<int>(fbw) * 8;
                            if (bx < ancho)
                                out.push_back({bx, by});
                            else
                            {
                                const int lineal = (by >> 2) * static_cast<int>(fbw) + (bx >> 3);
                                out.push_back({(lineal % static_cast<int>(fbw)) * 8 + (bx & 7), (lineal / static_cast<int>(fbw)) * 4 + (by & 3)});
                            }
                        }
            };
            if (modo != 0u)
                bloquesRect(escritos, x0, y0, x1, y1, modo == 2u);
            if (propio)
                bloquesRect(leidos, std::max(fuente.u0, 0), std::max(fuente.v0, 0), fuente.u1, fuente.v1, fuente.tipo == 2u);
            std::array<uint64_t, 12> clave{};
            clave[0] = claveObjetivo(c.frame.fbp << 5u, fbw, psmObjetivo, false);
            clave[1] = usaZ ? claveObjetivo(c.zbuf.zbp << 5u, fbw, c.zbuf.psm, true) : 0u;
            clave[2] = static_cast<uint64_t>(c.scissor.x0) | (static_cast<uint64_t>(c.scissor.x1) << 16u) |
                       (static_cast<uint64_t>(c.scissor.y0) << 32u) | (static_cast<uint64_t>(c.scissor.y1) << 48u);
            clave[3] = c.test | (static_cast<uint64_t>(c.zbuf.zmask) << 40u) | (static_cast<uint64_t>(c.frame.fbmsk) << 32u);
            clave[4] = (st.prim.abe ? c.alpha : 0u) ^ (static_cast<uint64_t>(modo) << 56u) ^ (static_cast<uint64_t>(c.frame.psm) << 48u) ^
                       (static_cast<uint64_t>(st.pabe) << 60u) ^ (static_cast<uint64_t>(st.colclamp & 1u) << 61u);
            clave[5] = (st.prim.tme ? 1u : 0u) | (st.prim.fst ? 4u : 0u) | (st.prim.fge ? 8u : 0u) | ((c.fba & 1u) << 4u) |
                       (static_cast<uint64_t>(st.fogR) << 8u) | (static_cast<uint64_t>(st.fogG) << 16u) | (static_cast<uint64_t>(st.fogB) << 24u) |
                       (static_cast<uint64_t>(st.linearFilter) << 32u) | (1ull << 40u) | (static_cast<uint64_t>(fuente.tipo) << 41u);
            if (st.prim.tme)
            {
                const GSTex0Reg &t = c.tex0;
                clave[6] = static_cast<uint64_t>(t.tbp0) | (static_cast<uint64_t>(t.tbw) << 16u) | (static_cast<uint64_t>(t.psm) << 24u) |
                           (static_cast<uint64_t>(t.tw) << 32u) | (static_cast<uint64_t>(t.th) << 36u) | (static_cast<uint64_t>(t.tcc) << 40u) |
                           (static_cast<uint64_t>(t.tfx) << 41u) | (static_cast<uint64_t>(t.cpsm) << 44u) | (static_cast<uint64_t>(t.csm) << 50u) |
                           (static_cast<uint64_t>(t.csa) << 51u);
                clave[7] = c.clamp & 0xFu;
                clave[8] = indexado(t.psm) ? clutId : 0u;
                clave[9] = static_cast<uint64_t>(st.texa.ta0) | (static_cast<uint64_t>(st.texa.aem) << 8u) | (static_cast<uint64_t>(st.texa.ta1) << 16u) |
                           (static_cast<uint64_t>(st.textureWidth) << 24u) | (static_cast<uint64_t>(st.textureHeight) << 40u);
                clave[11] = reinterpret_cast<uintptr_t>(fuente.objetivo);
            }
            clave[10] = v.escala;
            // Un mismo dibujo no puede escribir dos veces un píxel del objetivo si lee el destino (modos 1 y 2), ni leer
            // de la copia lo que ya escribió este lote: en esos casos se emite antes.
            bool solapa = false;
            if (l.abierto && clave == l.clave)
            {
                if (modo != 0u)
                    solapa = marcarBloques(bloquesEscritos, escritos, true);
                if (!solapa && propio)
                {
                    if (modo != 0u)
                        solapa = marcarBloques(bloquesEscritos, leidos, true);
                    else
                        solapa = l.x1 > l.x0 && fuente.u0 < l.x1 && fuente.u1 >= l.x0 && fuente.v0 < l.y1 && fuente.v1 >= l.y0;
                }
            }
            if (!l.abierto || clave != l.clave || solapa)
            {
                emitir(v);
                confirmarPendiente();
                if (st.prim.tme && !fuente.objetivo)
                {
                    Paginas tex;
                    const bool dentro = fuente.u0 >= 0 && fuente.v0 >= 0 && fuente.u1 < static_cast<int>(st.textureWidth) &&
                                        fuente.v1 < static_cast<int>(st.textureHeight);
                    if (dentro)
                        marcarPaginas(tex, c.tex0.psm, c.tex0.tbp0, std::max<uint32_t>(c.tex0.tbw, 1u), fuente.u0, fuente.v0, fuente.u1, fuente.v1);
                    else
                        marcarPaginas(tex, c.tex0.psm, c.tex0.tbp0, std::max<uint32_t>(c.tex0.tbw, 1u), 0, 0, st.textureWidth - 1, st.textureHeight - 1);
                    volcarSi(tex, v);
                }
                const uint32_t alto = modo == 2u ? std::min<uint32_t>((static_cast<uint32_t>(c.scissor.y1) >> 6u) * 32u + 32u, 512u)
                                                 : std::min<uint32_t>(static_cast<uint32_t>(c.scissor.y1) + 1u, 512u);
                Objetivo &color = objetivo(c.frame.fbp << 5u, fbw, psmObjetivo, false);
                Objetivo *z = usaZ ? &objetivo(c.zbuf.zbp << 5u, fbw, c.zbuf.psm, true) : nullptr;
                validar(color, alto, v);
                if (z)
                    validar(*z, alto, v);
                if (fuente.objetivo && fuente.objetivo != &color)
                {
                    const uint32_t bwf = fuente.objetivo->bw;
                    const uint32_t lineal = fuente.tipo == 2u ? (static_cast<uint32_t>(fuente.v1) >> 6u) * bwf + (static_cast<uint32_t>(fuente.u1) >> 6u)
                                                              : (static_cast<uint32_t>(fuente.v1) >> 5u) * bwf + (static_cast<uint32_t>(fuente.u1) >> 6u);
                    const uint32_t lineas = (lineal / bwf + 1u) * 32u;
                    validar(*fuente.objetivo, lineas, v);
                }
                l.sprite = true;
                l.modo = modo;
                l.tipoFuente = fuente.tipo;
                l.fuente = fuente.objetivo;
                l.texaCt24 = fuente.texaCt24;
                l.desdeCopia = propio;
                l.color = &color;
                l.z = z;
                l.textura = st.prim.tme && fuente.tipo == 0u ? textura(st, clutSlot, v) : nullptr;
                l.lineal = st.linearFilter;
                l.wrapS = static_cast<uint32_t>(c.clamp & 3u);
                l.wrapT = static_cast<uint32_t>((c.clamp >> 2u) & 3u);
                l.mezclar = st.prim.abe && modo == 0u;
                if (l.mezclar)
                    traducirMezcla(static_cast<uint32_t>(c.alpha & 3u), static_cast<uint32_t>((c.alpha >> 2u) & 3u),
                                   static_cast<uint32_t>((c.alpha >> 6u) & 3u), l.mezcla);
                l.estado = st;
                l.clave = clave;
                l.abierto = true;
                l.x0 = l.y0 = 1 << 30;
                l.x1 = l.y1 = -(1 << 30);
                bloquesEscritos.assign(64u * 64u, 0u);
            }
            if (propio)
            {
                // Copia de lo que lee este sprite (en píxeles del objetivo; en CT16, la caja de sus bloques CT32). Cada
                // sprite del lote copia su zona: la copia se ejecuta antes que el dibujo del lote y no se solapa con lo que
                // el lote escribe (comprobado arriba).
                int cx0 = 1 << 30, cy0 = 1 << 30, cx1 = -1, cy1 = -1;
                for (const auto &[bx, by] : leidos)
                {
                    cx0 = std::min(cx0, bx * 8); cy0 = std::min(cy0, by * 8);
                    cx1 = std::max(cx1, bx * 8 + 8); cy1 = std::max(cy1, by * 8 + 8);
                }
                if (leidos.empty())
                {
                    cx0 = std::max(fuente.u0, 0); cy0 = std::max(fuente.v0, 0); cx1 = fuente.u1 + 1; cy1 = fuente.v1 + 1;
                }
                copiar(*l.color, cx0, cy0, cx1, cy1);
            }
            if (modo != 0u)
                marcarBloques(bloquesEscritos, escritos, false);
            const uint32_t zMax = static_cast<uint32_t>((1ull << bitsZ(c.zbuf.psm)) - 1ull);
            const double zd = std::clamp(v1.z, 0.0, 4294967295.0);
            uint32_t w[16] = {};
            w[0] = static_cast<uint32_t>(x0) | (static_cast<uint32_t>(x1) << 16u);
            w[1] = static_cast<uint32_t>(y0) | (static_cast<uint32_t>(y1) << 16u);
            std::memcpy(&w[2], &ax.origin, 4);
            std::memcpy(&w[3], &ay.origin, 4);
            std::memcpy(&w[4], &ax.scale, 4);
            std::memcpy(&w[5], &ay.scale, 4);
            if (st.prim.tme)
            {
                float u0f, v0f, u1f, v1f;
                if (st.prim.fst)
                {
                    u0f = static_cast<float>(v0.u) / 16.0f; v0f = static_cast<float>(v0.v) / 16.0f;
                    u1f = static_cast<float>(v1.u) / 16.0f; v1f = static_cast<float>(v1.v) / 16.0f;
                }
                else
                {
                    const auto q = [](float x) { return std::abs(x) > 1.0e-8f ? x : 1.0f; };
                    u0f = (v0.s / q(v0.q)) * static_cast<float>(st.textureWidth);
                    v0f = (v0.t / q(v0.q)) * static_cast<float>(st.textureHeight);
                    u1f = (v1.s / q(v1.q)) * static_cast<float>(st.textureWidth);
                    v1f = (v1.t / q(v1.q)) * static_cast<float>(st.textureHeight);
                }
                std::memcpy(&w[6], &u0f, 4);
                std::memcpy(&w[7], &v0f, 4);
                std::memcpy(&w[8], &u1f, 4);
                std::memcpy(&w[9], &v1f, 4);
            }
            w[10] = std::min<uint32_t>(static_cast<uint32_t>(zd), zMax);
            w[11] = static_cast<uint32_t>(v1.r) | (static_cast<uint32_t>(v1.g) << 8u) | (static_cast<uint32_t>(v1.b) << 16u) |
                    (static_cast<uint32_t>(v1.a) << 24u);
            w[12] = v1.fog;
            if (modo == 2u)
            {
                // Un rectángulo por tramo de bloques CT32 contiguos en una fila; el sombreador decide qué medias palabras
                // caen dentro del sprite (palabras 13 y 14: su rectángulo CT16).
                w[13] = w[0];
                w[14] = w[1];
                std::sort(escritos.begin(), escritos.end(), [](const auto &a, const auto &b) { return a.second != b.second ? a.second < b.second : a.first < b.first; });
                escritos.erase(std::unique(escritos.begin(), escritos.end()), escritos.end());
                for (size_t k = 0; k < escritos.size();)
                {
                    size_t e = k + 1u;
                    while (e < escritos.size() && escritos[e].second == escritos[k].second && escritos[e].first == escritos[e - 1u].first + 1)
                        ++e;
                    const int qx0 = escritos[k].first * 8, qx1 = escritos[e - 1u].first * 8 + 7, qy0 = escritos[k].second * 8, qy1 = qy0 + 7;
                    w[0] = static_cast<uint32_t>(qx0) | (static_cast<uint32_t>(qx1) << 16u);
                    w[1] = static_cast<uint32_t>(qy0) | (static_cast<uint32_t>(qy1) << 16u);
                    l.datos.insert(l.datos.end(), w, w + 16);
                    l.x0 = std::min(l.x0, qx0);
                    l.y0 = std::min(l.y0, qy0);
                    l.x1 = std::max(l.x1, qx1 + 1);
                    l.y1 = std::max(l.y1, qy1 + 1);
                    k = e;
                }
            }
            else
            {
                l.datos.insert(l.datos.end(), w, w + 16);
                l.x0 = std::min(l.x0, x0);
                l.y0 = std::min(l.y0, y0);
                l.x1 = std::max(l.x1, x1 + 1);
                l.y1 = std::max(l.y1, y1 + 1);
            }
            ++spritesHw;
            g_spritesHw.fetch_add(1u, std::memory_order_relaxed);
            if (l.datos.size() >= 16u * 16384u)
                emitir(v);
        }

        void volcarSi(const Paginas &toca, const Vram &v)
        {
            for (auto &[k, o] : objetivos)
                if (o.sucio && (o.paginasSucias & toca).any())
                    volcar(o, v);
        }
    };

    Renderizador::Renderizador() : m(std::make_unique<Impl>()) {}

    Renderizador::~Renderizador()
    {
        if (!m->gl)
            return;
        // El contexto GL se destruye con el backend; los nombres se liberan con él.
    }

    bool Renderizador::iniciar(const Api &gl, const std::string &prefijo)
    {
        Impl &d = *m;
        d.gl = &gl;
        ApiHw &h = d.hw;
        const bool funciones = cargar(h.FramebufferTexture2D, "glFramebufferTexture2D") &&
                               cargar(h.CheckFramebufferStatus, "glCheckFramebufferStatus") &&
                               cargar(h.BlendFuncSeparate, "glBlendFuncSeparate") &&
                               cargar(h.BlendEquationSeparate, "glBlendEquationSeparate") && cargar(h.DepthFunc, "glDepthFunc") &&
                               cargar(h.DepthMask, "glDepthMask") && cargar(h.ColorMask, "glColorMask") && cargar(h.Scissor, "glScissor") &&
                               cargar(h.ClipControl, "glClipControl") && cargar(h.ActiveTexture, "glActiveTexture") &&
                               cargar(h.Uniform1i, "glUniform1i") && cargar(h.Uniform4f, "glUniform4f") &&
                               cargar(h.CopyImageSubData, "glCopyImageSubData") && cargar(h.TextureBarrier, "glTextureBarrier");
        if (!funciones || !gl.graphics)
        {
            std::fprintf(stderr, "[gs-hw-render] faltan funciones de OpenGL: se usa la ruta software\n");
            d.gl = nullptr;
            return false;
        }
        const std::string version = "#version 460 core\n";
        const std::string comun = prefijo + GSGpuShaders::kCommon;
        const std::string planos = comun + kPlanos;
        d.fuenteDibujoVs = version + kDibujoVs;
        d.fuenteDibujoFs = comun + kEscritura + kDibujoFs;
        d.fuenteSpriteVs = version + kSpriteVs;
        d.fuenteSpriteFs = planos + kEscritura + kSpriteFs;
        const bool ok = d.compilar(d.carga, {{kVertexShader, version + kCargaVs}, {kFragmentShader, planos + kCargaFs}}, {"uPlano", "uObj", "uZEsc"}) &&
                        d.compilar(d.volcado, {{kComputeShader, planos + kVolcado}}, {"uPlano", "uObj", "uRect", "uZEsc", "uFuente"}) &&
                        d.compilar(d.decodificar, {{kComputeShader, comun + kDecodificar}}, {"uTex", "uClut", "uTexa"}) &&
                        d.variante(false, 0u, 0u).id != 0u && d.variante(true, 0u, 1u).id != 0u;
        if (!ok)
        {
            d.gl = nullptr;
            return false;
        }
        gl.GenVertexArrays(1, &d.vao);
        gl.GenFramebuffers(1, &d.fboCarga);
        gl.GenFramebuffers(1, &d.fboDibujo);
        gl.GenBuffers(1, &d.vertices);
        gl.GenBuffers(1, &d.salida);
        d.crearTablas();
        const char *diag = std::getenv("PS2X_GS_HW_DIAG");
        d.diag = diag && diag[0] == '1';
        const char *prof = std::getenv("PS2X_GS_GPU_PROF");
        d.cronometrar = d.diag && prof && prof[0] == '1';
        std::fprintf(stderr, "[gs-hw-render] renderizador por hardware de triángulos activo\n");
        std::fflush(stderr);
        return true;
    }

    uint32_t Renderizador::admite(const GSPrimitiveBatch &batch) const
    {
        const GSDrawState &st = batch.state;
        const GSContext &c = st.context;
        const GSPrimType t = st.prim.type;
        if (!m->gl)
            return 15u;
        const bool sprite = t == GS_PRIM_SPRITE && batch.vertexCount == 2u;
        static const bool sprites = [] { const char *v = std::getenv("PS2X_GS_HW_SPRITES"); return !(v && v[0] == '0'); }();
        if (sprite && !sprites)
            return 1u;
        if (!sprite && (batch.vertexCount != 3u || (t != GS_PRIM_TRIANGLE && t != GS_PRIM_TRISTRIP && t != GS_PRIM_TRIFAN)))
            return 1u;
        if (c.frame.fbw == 0u || c.frame.fbw > 32u)
            return 2u;
        const uint32_t test = static_cast<uint32_t>(c.test);
        if (sprite)
        {
            // GOW-Port: CT16 solo sobre un objetivo CT32 de la misma dirección y ancho (sin Z: el GS los usa para mover
            // canales).
            if (c.frame.psm == 0x02u)
            {
                if (!m->objetivoPalabras(c.frame.fbp << 5u, c.frame.fbw) || ((test >> 16u) & 1u) != 0u &&
                                                                                    (((test >> 17u) & 3u) >= 2u || !c.zbuf.zmask))
                    return 2u;
            }
            else if (!formatoColor(c.frame.psm))
                return 2u;
            // Exactos con prueba de alfa que no escribe Z en los que fallan: no se puede por píxel con la Z de la GPU.
            const bool zEscribe = ((test >> 16u) & 1u) != 0u && !c.zbuf.zmask;
            if (m->modoSprite(st) != 0u && zEscribe && (test & 1u) != 0u && ((test >> 12u) & 3u) != 0u && ((test >> 12u) & 3u) != 2u)
                return 13u;
        }
        else
        {
            if (!formatoColor(c.frame.psm))
                return 2u;
            static const bool triExacto = [] { const char *v = std::getenv("PS2X_GS_HW_TRI_EXACTO"); return !(v && v[0] == '0'); }();
            const uint32_t modo = m->modoTriangulo(st);
            if (modo != 0u && !triExacto)
            {
                for (uint32_t b = 0; b < 4u; ++b)
                {
                    const uint32_t byte = (c.frame.fbmsk >> (b * 8u)) & 0xFFu;
                    if (byte != 0u && byte != 0xFFu)
                        return 3u;
                }
                return ((test >> 14u) & 1u) != 0u ? 7u : 6u;
            }
            const bool zEscribe = ((test >> 16u) & 1u) != 0u && !c.zbuf.zmask;
            if (modo != 0u && zEscribe && (test & 1u) != 0u && ((test >> 12u) & 3u) != 0u && ((test >> 12u) & 3u) != 2u)
                return 13u;
        }
        // GOW-Port: ZTE=0 dibuja sin prueba ni escritura de Z (KIexster ps2recomp-gs-zte, como la ruta software).
        const bool zte = (test & 0x10000u) != 0u;
        const uint32_t ztst = zte ? (test >> 17u) & 3u : 1u;
        const bool usaZ = zte && (ztst >= 2u || !c.zbuf.zmask);
        if (usaZ && !formatoZ(c.zbuf.psm))
            return 4u;
        if (usaZ)
        {
            // GOW-Port: color y Z en las mismas páginas (GoW calcula un máximo en Z sobre un búfer de color): aquí serían
            // dos texturas distintas y el orden de sus volcados no es el del GS. Va a la ruta software.
            const auto paginas = [](uint32_t pagina, uint32_t fbw, uint32_t psm, uint32_t y1) {
                const uint32_t alto = (psm & 0x0Fu) >= 2u ? 64u : 32u; // 16 bits: páginas de 64 filas
                return std::pair<uint32_t, uint32_t>{pagina, pagina + std::max<uint32_t>(fbw, 1u) * (y1 / alto + 1u)};
            };
            const auto f = paginas(c.frame.fbp, c.frame.fbw, c.frame.psm, c.scissor.y1);
            const auto z = paginas(c.zbuf.zbp, c.frame.fbw, c.zbuf.psm, c.scissor.y1);
            if (f.first < z.second && z.first < f.second)
                return 12u;
        }
        // AA1 se ignora como en la ruta software. DATE: solo los sprites (modo exacto).
        if (st.scanmsk != 0u)
            return 7u;
        if (st.prim.tme)
        {
            if (!formatoTextura(c.tex0.psm) && !(sprite && Impl::sinPaleta(c.tex0.psm)))
                return 5u;
            if (indexado(c.tex0.psm) && !(c.tex0.cpsm == 0x00u || c.tex0.cpsm == 0x01u || c.tex0.cpsm == 0x02u || c.tex0.cpsm == 0x0Au))
                return 5u;
            const uint32_t wms = static_cast<uint32_t>(c.clamp & 3u), wmt = static_cast<uint32_t>((c.clamp >> 2u) & 3u);
            if (wms > 1u || wmt > 1u)
                return 8u;
            // Mipmaps: la ruta software también muestrea solo el nivel 0 (con el filtro de linearFilter).
            if (st.textureWidth > 1024u || st.textureHeight > 1024u)
                return 5u;
        }
        // COLCLAMP=0 (desbordar en vez de saturar) solo cambia algo si la mezcla pasa de 255 o baja de 0; la GPU satura.
        // Las mezclas sin equivalente, PABE y (con PS2X_GS_HW_EXACTO=1) COLCLAMP=0 van al modo exacto (modoTriangulo).
        if (sprite && st.prim.tme)
            return m->fuenteSprite(batch).motivo;
        return 0u;
    }

    void Renderizador::dibujar(const GSPrimitiveBatch &batch, const Vram &v, uint32_t clutSlot)
    {
        Impl &d = *m;
        d.escalaActual = v.escala;
        if (batch.state.prim.type == GS_PRIM_SPRITE)
        {
            ++d.stats.aceptados;
            d.dibujarSprite(batch, v, clutSlot);
            return;
        }
        const GSDrawState &st = batch.state;
        const GSContext &c = st.context;
        const uint32_t test = static_cast<uint32_t>(c.test);
        const bool zte = (test & 0x10000u) != 0u; // GOW-Port: ZTE=0 = sin Z (ver admite)
        const uint32_t ztst = zte ? (test >> 17u) & 3u : 1u;
        ++d.stats.aceptados;
        g_triangulosHw.fetch_add(1u, std::memory_order_relaxed);
        if (ztst == 0u)
            return; // ZTST NEVER: el GS no dibuja nada
        const bool usaZ = zte && (ztst >= 2u || !c.zbuf.zmask);
        const uint32_t fbw = c.frame.fbw;
        Impl::Lote &l = d.lote;
        std::array<uint64_t, 12> clave{};
        clave[0] = Impl::claveObjetivo(c.frame.fbp << 5u, fbw, c.frame.psm, false);
        clave[1] = usaZ ? Impl::claveObjetivo(c.zbuf.zbp << 5u, fbw, c.zbuf.psm, true) : 0u;
        clave[2] = static_cast<uint64_t>(c.scissor.x0) | (static_cast<uint64_t>(c.scissor.x1) << 16u) |
                   (static_cast<uint64_t>(c.scissor.y0) << 32u) | (static_cast<uint64_t>(c.scissor.y1) << 48u);
        clave[3] = c.test | (static_cast<uint64_t>(c.zbuf.zmask) << 40u) | (static_cast<uint64_t>(c.frame.fbmsk) << 32u);
        clave[4] = st.prim.abe ? c.alpha : 0u;
        clave[5] = (st.prim.tme ? 1u : 0u) | (st.prim.iip ? 2u : 0u) | (st.prim.fst ? 4u : 0u) | (st.prim.fge ? 8u : 0u) |
                   ((c.fba & 1u) << 4u) | (static_cast<uint64_t>(st.fogR) << 8u) | (static_cast<uint64_t>(st.fogG) << 16u) |
                   (static_cast<uint64_t>(st.fogB) << 24u) | (static_cast<uint64_t>(st.linearFilter) << 32u);
        if (st.prim.tme)
        {
            const GSTex0Reg &t = c.tex0;
            clave[6] = static_cast<uint64_t>(t.tbp0) | (static_cast<uint64_t>(t.tbw) << 16u) | (static_cast<uint64_t>(t.psm) << 24u) |
                       (static_cast<uint64_t>(t.tw) << 32u) | (static_cast<uint64_t>(t.th) << 36u) | (static_cast<uint64_t>(t.tcc) << 40u) |
                       (static_cast<uint64_t>(t.tfx) << 41u) | (static_cast<uint64_t>(t.cpsm) << 44u) | (static_cast<uint64_t>(t.csm) << 50u) |
                       (static_cast<uint64_t>(t.csa) << 51u);
            clave[7] = c.clamp & 0xFu;
            clave[8] = indexado(t.psm) ? d.clutId : 0u;
            clave[9] = static_cast<uint64_t>(st.texa.ta0) | (static_cast<uint64_t>(st.texa.aem) << 8u) | (static_cast<uint64_t>(st.texa.ta1) << 16u) |
                       (static_cast<uint64_t>(st.textureWidth) << 24u) | (static_cast<uint64_t>(st.textureHeight) << 40u);
        }
        clave[10] = v.escala;
        // GOW-Port: modo exacto: el lote no puede pasar dos veces por un píxel (lee el destino); si este triángulo cae en
        // bloques ya escritos por el lote, se emite antes.
        const uint32_t modo = d.modoTriangulo(st);
        clave[11] = modo;
        std::vector<std::pair<int, int>> bloques;
        if (modo != 0u)
        {
            const float ox = c.xyoffset.ofx / 16.0f, oy = c.xyoffset.ofy / 16.0f;
            float bx0 = 1e30f, by0 = 1e30f, bx1 = -1e30f, by1 = -1e30f;
            for (uint32_t i = 0; i < 3u; ++i)
            {
                bx0 = std::min(bx0, batch.vertices[i].x - ox); bx1 = std::max(bx1, batch.vertices[i].x - ox);
                by0 = std::min(by0, batch.vertices[i].y - oy); by1 = std::max(by1, batch.vertices[i].y - oy);
            }
            const int qx0 = std::max(static_cast<int>(std::floor(bx0)) - 1, static_cast<int>(c.scissor.x0));
            const int qy0 = std::max(static_cast<int>(std::floor(by0)) - 1, static_cast<int>(c.scissor.y0));
            const int qx1 = std::min(static_cast<int>(std::ceil(bx1)) + 1, static_cast<int>(c.scissor.x1));
            const int qy1 = std::min(static_cast<int>(std::ceil(by1)) + 1, static_cast<int>(c.scissor.y1));
            for (int by = qy0 >> 3; by <= (qy1 >> 3); ++by)
                for (int bx = qx0 >> 3; bx <= (qx1 >> 3); ++bx)
                    bloques.push_back({bx, by});
        }
        const bool solapa = modo != 0u && l.abierto && clave == l.clave && d.marcarBloques(d.bloquesEscritos, bloques, true);
        if (!l.abierto || clave != l.clave || solapa)
        {
            d.emitir(v);
            d.confirmarPendiente();
            // Texturas que salen de un objetivo con cambios: primero se vuelca.
            if (st.prim.tme)
            {
                Paginas tex;
                marcarPaginas(tex, c.tex0.psm, c.tex0.tbp0, std::max<uint32_t>(c.tex0.tbw, 1u), 0, 0, st.textureWidth - 1, st.textureHeight - 1);
                d.volcarSi(tex, v);
            }
            const uint32_t alto = std::min<uint32_t>(static_cast<uint32_t>(c.scissor.y1) + 1u, 512u);
            Impl::Objetivo &color = d.objetivo(c.frame.fbp << 5u, fbw, c.frame.psm, false);
            Impl::Objetivo *z = usaZ ? &d.objetivo(c.zbuf.zbp << 5u, fbw, c.zbuf.psm, true) : nullptr;
            d.validar(color, alto, v);
            if (z)
                d.validar(*z, alto, v);
            l.sprite = false;
            l.modo = modo;
            l.fuente = nullptr;
            l.desdeCopia = false;
            l.texaCt24 = false;
            d.bloquesEscritos.assign(64u * 64u, 0u);
            l.color = &color;
            l.z = z;
            l.textura = st.prim.tme ? d.textura(st, clutSlot, v) : nullptr;
            l.lineal = st.linearFilter;
            l.wrapS = static_cast<uint32_t>(c.clamp & 3u);
            l.wrapT = static_cast<uint32_t>((c.clamp >> 2u) & 3u);
            l.mezclar = st.prim.abe && modo == 0u;
            if (l.mezclar)
                traducirMezcla(static_cast<uint32_t>(c.alpha & 3u), static_cast<uint32_t>((c.alpha >> 2u) & 3u),
                               static_cast<uint32_t>((c.alpha >> 6u) & 3u), l.mezcla);
            l.estado = st;
            l.clave = clave;
            l.abierto = true;
            l.x0 = l.y0 = 1 << 30;
            l.x1 = l.y1 = -(1 << 30);
        }
        if (modo != 0u)
            d.marcarBloques(d.bloquesEscritos, bloques, false);
        const float ox = c.xyoffset.ofx / 16.0f, oy = c.xyoffset.ofy / 16.0f;
        const uint32_t zMax = static_cast<uint32_t>((1ull << bitsZ(c.zbuf.psm)) - 1ull);
        float minX = 1e30f, minY = 1e30f, maxX = -1e30f, maxY = -1e30f;
        for (uint32_t i = 0; i < 3u; ++i)
        {
            const GSVertex &vx = batch.vertices[i];
            const float x = vx.x - ox, y = vx.y - oy;
            minX = std::min(minX, x); maxX = std::max(maxX, x);
            minY = std::min(minY, y); maxY = std::max(maxY, y);
            const double zd = std::clamp(vx.z, 0.0, 4294967295.0);
            const uint32_t z = std::min<uint32_t>(static_cast<uint32_t>(zd), zMax);
            const uint32_t color = static_cast<uint32_t>(vx.r) | (static_cast<uint32_t>(vx.g) << 8u) | (static_cast<uint32_t>(vx.b) << 16u) |
                                   (static_cast<uint32_t>(vx.a) << 24u);
            uint32_t w[12];
            std::memcpy(&w[0], &x, 4);
            std::memcpy(&w[1], &y, 4);
            w[2] = z;
            w[3] = color;
            std::memcpy(&w[4], &vx.s, 4);
            std::memcpy(&w[5], &vx.t, 4);
            std::memcpy(&w[6], &vx.q, 4);
            const float u = vx.u, vv = vx.v, f = vx.fog;
            std::memcpy(&w[7], &u, 4);
            std::memcpy(&w[8], &vv, 4);
            std::memcpy(&w[9], &f, 4);
            w[10] = w[11] = 0u;
            l.datos.insert(l.datos.end(), w, w + 12);
        }
        l.x0 = std::min(l.x0, std::max(static_cast<int>(std::floor(minX)) - 1, static_cast<int>(c.scissor.x0)));
        l.y0 = std::min(l.y0, std::max(static_cast<int>(std::floor(minY)) - 1, static_cast<int>(c.scissor.y0)));
        l.x1 = std::max(l.x1, std::min(static_cast<int>(std::ceil(maxX)) + 2, static_cast<int>(c.scissor.x1) + 1));
        l.y1 = std::max(l.y1, std::min(static_cast<int>(std::ceil(maxY)) + 2, static_cast<int>(c.scissor.y1) + 1));
        if (l.datos.size() >= 12u * 3u * 16384u)
            d.emitir(v);
    }

    void Renderizador::antesDeSoftware(const Paginas &toca, const Vram &v, uint32_t origen)
    {
        Impl &d = *m;
        if (!d.gl)
            return;
        d.emitir(v);
        d.restaurarSiDibujo();
        d.origen = origen;
        d.ultimoOrigen = origen;
        d.ultimoToca = toca;
        d.volcarSi(toca, v);
        d.origen = 0u;
    }

    void Renderizador::escrito(const Paginas &paginas)
    {
        m->pendiente |= paginas;
        // GOW-Port: un dibujo de la ruta software escribe cada plano por separado; una subida, igual en todos.
        // Una copia local→local copia plano a plano: el destino queda dibujado si el origen lo estaba.
        Impl &d = *m;
        const bool origenDibujado = (d.ultimoToca & ~paginas & d.dibujadas).any();
        if (d.ultimoOrigen == 1u || (d.ultimoOrigen == 3u && origenDibujado))
            d.dibujadas |= paginas;
        else if (d.ultimoOrigen == 3u || d.ultimoOrigen == 4u)
            d.dibujadas &= ~paginas;
    }

    void Renderizador::cargaClut(uint64_t clave, const Paginas &fuente, bool parcial)
    {
        Impl &d = *m;
        d.confirmarPendiente();
        const uint64_t nueva = mezclar(mezclar(parcial ? d.clutId : 0x51u, clave), d.firmaDe(fuente));
        d.clutId = nueva;
    }

    void Renderizador::volcarTodo(const Vram &v, uint32_t origen)
    {
        Impl &d = *m;
        if (!d.gl)
            return;
        d.emitir(v);
        d.restaurarSiDibujo();
        d.origen = origen;
        for (auto &[k, o] : d.objetivos)
            d.volcar(o, v);
        d.origen = 0u;
    }

    void Renderizador::descartarTodo()
    {
        Impl &d = *m;
        d.lote.abierto = false;
        d.lote.datos.clear();
        d.dibujadas.reset();
        for (auto &[k, o] : d.objetivos)
        {
            o.valido = false;
            o.sucio = false;
        }
    }

    void Renderizador::rechazado(uint32_t motivo)
    {
        ++m->stats.rechazados;
        ++m->stats.motivo[motivo & 15u];
    }

    void Renderizador::rechazadoDetalle(uint32_t motivo, const GSPrimitiveBatch &batch)
    {
        rechazado(motivo);
        if (!m->diag)
            return;
        const GSDrawState &st = batch.state;
        const GSContext &c = st.context;
        uint64_t dato = 0u;
        switch (motivo)
        {
        case 1u:
        {
            dato = static_cast<uint64_t>(st.prim.type);
            if (st.prim.type == GS_PRIM_SPRITE)
            {
                const GSVertex &a = batch.vertices[0], &b = batch.vertices[1];
                const float w = std::abs(b.x - a.x), h = std::abs(b.y - a.y);
                const float tw = st.prim.fst ? std::abs(b.u - a.u) / 16.0f : std::abs(b.s / b.q - a.s / a.q) * st.textureWidth;
                const float th = st.prim.fst ? std::abs(b.v - a.v) / 16.0f : std::abs(b.t / b.q - a.t / a.q) * st.textureHeight;
                char k[256];
                std::snprintf(k, sizeof(k), "fb %x/%u/%x msk %08x | %s %x/%u/%x c%x %ux%u | %.0fx%.0f <- %.0fx%.0f | abe %d alpha %llx test %llx tfx %u tcc %u lin %d",
                              c.frame.fbp << 5u, c.frame.fbw, c.frame.psm, c.frame.fbmsk, st.prim.tme ? "tex" : "sin", c.tex0.tbp0, c.tex0.tbw,
                              c.tex0.psm, c.tex0.cpsm, st.textureWidth, st.textureHeight, w, h, tw, th, int(st.prim.abe),
                              static_cast<unsigned long long>(st.prim.abe ? c.alpha : 0u), static_cast<unsigned long long>(c.test),
                              unsigned(c.tex0.tfx), unsigned(c.tex0.tcc), int(st.linearFilter));
                auto &e = m->censoSprites[k];
                ++e.first;
                e.second += static_cast<double>(w) * h;
            }
            break;
        }
        case 6u: dato = (c.alpha & 0xFFu) | ((c.alpha >> 32u) << 8u) | (static_cast<uint64_t>(st.pabe) << 16u) | ((st.colclamp & 1u) << 17u) |
                        (static_cast<uint64_t>(c.frame.fbp) << 24u) | (static_cast<uint64_t>(st.prim.tme) << 40u) | (static_cast<uint64_t>(c.tex0.tbp0) << 41u); break;
        case 7u: dato = (c.test >> 14u) | (st.scanmsk << 8u) | (static_cast<uint64_t>(st.prim.aa1) << 12u); break;
        case 9u: dato = c.tex1 & 0x3FFu; break;
        default: dato = 0u; break;
        }
        ++m->detalleRechazo[(static_cast<uint64_t>(motivo) << 56u) | dato];
    }

    void Renderizador::informe()
    {
        Impl &d = *m;
        if (!d.diag)
            return;
        static auto inicio = std::chrono::steady_clock::now();
        const auto ahora = std::chrono::steady_clock::now();
        const double seg = std::chrono::duration<double>(ahora - inicio).count();
        if (seg < 5.0)
            return;
        Estadisticas &s = d.stats;
        std::fprintf(stderr,
                     "[gs-hw-render] %.0f tri/s por hardware, %.0f por software; %.0f lotes/s, %.1f cargas/s, %.1f volcados/s, "
                     "%.1f texturas/s (%.0f aciertos/s); rechazos:",
                     s.aceptados / seg, s.rechazados / seg, s.dibujos / seg, s.cargas / seg, s.volcados / seg, s.texturas / seg,
                     s.aciertos / seg);
        for (uint32_t i = 0; i < 16u; ++i)
            if (s.motivo[i])
                std::fprintf(stderr, " %u:%.0f", i, s.motivo[i] / seg);
        std::fprintf(stderr, "\n");
        std::vector<std::pair<uint64_t, uint64_t>> lista(d.detalleRechazo.begin(), d.detalleRechazo.end());
        std::sort(lista.begin(), lista.end(), [](const auto &a, const auto &b) { return a.second > b.second; });
        for (size_t i = 0; i < std::min<size_t>(lista.size(), 8u); ++i)
            std::fprintf(stderr, "[gs-hw-render]   rechazo %llu dato %llx: %.0f/s\n", static_cast<unsigned long long>(lista[i].first >> 56u),
                         static_cast<unsigned long long>(lista[i].first & 0x00FFFFFFFFFFFFFFull), lista[i].second / seg);
        d.detalleRechazo.clear();
        if (!d.censoCopias.empty())
        {
            std::vector<std::pair<std::string, std::pair<uint64_t, double>>> v(d.censoCopias.begin(), d.censoCopias.end());
            std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) { return a.second.second > b.second.second; });
            for (size_t i = 0; i < std::min<size_t>(v.size(), 16u); ++i)
                std::fprintf(stderr, "[gs-hw-copia] %.0f/s %.0f px/s %s\n", v[i].second.first / seg, v[i].second.second / seg, v[i].first.c_str());
            d.censoCopias.clear();
        }
        if (!d.censoSprites.empty())
        {
            std::vector<std::pair<std::string, std::pair<uint64_t, double>>> v(d.censoSprites.begin(), d.censoSprites.end());
            std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) { return a.second.second > b.second.second; });
            for (size_t i = 0; i < std::min<size_t>(v.size(), 40u); ++i)
                std::fprintf(stderr, "[gs-hw-sprite] %.0f/s %.0f px/s %s\n", v[i].second.first / seg, v[i].second.second / seg, v[i].first.c_str());
            d.censoSprites.clear();
        }
        std::fprintf(stderr, "[gs-hw-render]   volcados por origen:");
        static const char *kOrigen[16] = {"textura", "dibujo", "clut", "transferencia", "borrado", "pixel", "lectura", "sync",
                                          "presentar", "copia", "escala", "?", "?", "?", "?", "?"};
        for (size_t i = 0; i < d.volcadosPor.size(); ++i)
            if (d.volcadosPor[i])
                std::fprintf(stderr, " %s %.1f/s", kOrigen[i], d.volcadosPor[i] / seg);
        std::fprintf(stderr, "\n");
        d.volcadosPor.fill(0u);
        if (d.cronometrar)
        {
            d.cronoResolver();
            static const char *kTipo[9] = {"carga", "volcado", "decodificar", "tri", "tri-exacto", "sprite", "sprite-exacto", "sprite-ct16", "subida"};
            std::fprintf(stderr, "[gs-hw-render]   GPU ms/s:");
            for (size_t i = 0; i < 9u; ++i)
                std::fprintf(stderr, " %s %.1f (%.0f/s)", kTipo[i], d.nsPor[i] / 1e6 / seg, d.cuentaPor[i] / seg);
            std::fprintf(stderr, "\n");
            d.nsPor.fill(0u);
            d.cuentaPor.fill(0u);
            std::vector<std::pair<uint64_t, std::array<uint64_t, 3>>> v(d.porClave.begin(), d.porClave.end());
            std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) { return a.second[0] > b.second[0]; });
            for (size_t i = 0; i < std::min<size_t>(v.size(), 12u); ++i)
            {
                const uint64_t k = v[i].first;
                std::fprintf(stderr, "[gs-hw-lote] %.1f ms/s %.0f lotes/s %.0f prims/s | %s fb %llx z%llu tex %llx alpha %llx test %llx\n",
                             v[i].second[0] / 1e6 / seg, v[i].second[1] / seg, v[i].second[2] / seg, ((k >> 56u) & 1u) ? "sprite" : "tri",
                             static_cast<unsigned long long>(k & 0xFFFFFu), static_cast<unsigned long long>((k >> 20u) & 1u),
                             static_cast<unsigned long long>((k >> 24u) & 0xFFu), static_cast<unsigned long long>((k >> 32u) & 0xFFu),
                             static_cast<unsigned long long>((k >> 40u) & 0xFFFu));
            }
            d.porClave.clear();
        }
        std::fflush(stderr);
        s = {};
        inicio = ahora;
    }
}
