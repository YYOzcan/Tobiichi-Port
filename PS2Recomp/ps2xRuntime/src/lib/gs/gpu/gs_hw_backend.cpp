// GOW-Port: render-target GS renderer, see include/runtime/gs/gs_hw_backend.h.
#include "runtime/gs/gs_hw_backend.h"
#include "gs_texture_store.h"
#include "runtime/gs/gs_swizzle.h"
#include "gs_gl.h"
#include "../gs_gpu_helpers.h"
#include "runtime/gs/gs_shared_present.h"

#include <map>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
    using namespace GSGL;

    constexpr GLenum kArrayBuffer = 0x8892;
    constexpr GLenum kFloat = 0x1406;
    constexpr GLenum kColorAttachment0 = 0x8CE0;
    constexpr GLenum kDepthAttachment = 0x8D00;
    constexpr GLenum kFramebufferComplete = 0x8CD5;
    constexpr GLenum kDepthComponent32F = 0x8CAC;
    constexpr GLenum kDepthComponent = 0x1902;
    constexpr GLenum kBlend = 0x0BE2;
    constexpr GLenum kDepthTest = 0x0B71;
    constexpr GLenum kScissorTest = 0x0C11;
    constexpr GLenum kCullFace = 0x0B44;
    constexpr GLenum kOne = 1, kZero = 0;
    constexpr GLenum kSrc1Alpha = 0x8589, kOneMinusSrc1Alpha = 0x88FB;
    constexpr GLenum kConstantColor = 0x8001, kOneMinusConstantColor = 0x8002;
    constexpr GLenum kFuncAdd = 0x8006, kFuncReverseSubtract = 0x800B;
    constexpr GLbitfield kColorBufferBit = 0x4000, kDepthBufferBit = 0x100;
    constexpr GLenum kNever = 0x200, kLess = 0x201, kLEqual = 0x203, kGreater = 0x204, kGEqual = 0x206, kAlways = 0x207;
    constexpr GLenum kTexture0 = 0x84C0;
    constexpr GLint kRepeat = 0x2901;
    constexpr GLenum kUnpackAlignment = 0x0CF5, kPackAlignment = 0x0D05;
    constexpr GLenum kFalse = 0, kTrue = 1;

    const char *kVsSource = R"(#version 430 core
layout(location = 0) in vec2 aPos;     // PS2 pixels, centre-adjusted
layout(location = 1) in float aZ;      // 0..1
layout(location = 2) in vec4 aCol;     // 0..255
layout(location = 3) in vec3 aSTQ;
layout(location = 4) in vec2 aUV;      // texels
layout(location = 5) in vec4 aUVClamp; // texels: the range the GS samples (sprites), else unbounded
uniform vec2 uInvSize;
noperspective out vec4 vCol;
flat out vec4 vColFlat;
noperspective out vec3 vSTQ;
noperspective out vec2 vUV;
flat out vec4 vUVClamp;
void main()
{
    gl_Position = vec4(aPos * uInvSize * 2.0 - 1.0, aZ * 2.0 - 1.0, 1.0);
    vCol = aCol;
    vColFlat = aCol;
    vSTQ = aSTQ;
    vUV = aUV;
    vUVClamp = aUVClamp;
}
)";

    const char *kFsSource = R"(#version 430 core
noperspective in vec4 vCol;
flat in vec4 vColFlat;
noperspective in vec3 vSTQ;
noperspective in vec2 vUV;
flat in vec4 vUVClamp;
layout(location = 0, index = 0) out vec4 oColor;
layout(location = 0, index = 1) out vec4 oBlend;
uniform sampler2D uTex;
uniform vec2 uTexSize;   // size the sampled image is normalised by (render targets: their own size)
uniform vec2 uTexDim;    // TEX0 TW/TH: size STQ coordinates are scaled by

// Reinterpreting fetch: the texture lives in the memory a render target was drawn into, but with another format / width /
// layout (16 bit view of a 32 bit target, T8H = alpha plane, other pitch...). The texel's GS memory address is computed
// from the texture format, mapped back to the render-target pixel that owns it and the bits are re-extracted: pure address
// math on the GPU, no memory image.
uniform int uReinterp;
uniform int uDate, uDatm;   // destination alpha test (reads the target itself)
// GS blend done in the shader (reads the target): destination-alpha factor (Ad, 0x80 = 1.0) and COLCLAMP=0 wrap-around,
// which fixed-function blending cannot express. uAbcd = ALPHA A, B, C, D selectors.
uniform int uSwBlend, uColClamp;
uniform ivec4 uAbcd;
uniform float uFix;
// Z buffer in the colour memory of the target itself (ZBP == FBP): the test reads the Z word from the target's colour,
// a passing write stores the Z word there. 0 = off, else 1 + ZTST.
uniform int uZAlias, uZAliasWrite;
uniform float uZAliasMax;
uniform sampler2D uDest;
uniform int uZTex;     // 16/24/32: sampling a depth buffer (Z16/Z24/Z32 texture)
uniform float uZMax;
)";

    // Shared by the draw shader and the CLUT fetch: a texel of a texture format read from a render target's memory.
    const char *kReinterpretSource = R"(
uniform usampler2D uTables;
uniform sampler2D uRtColor;
uniform sampler2D uPalette;
uniform ivec4 uTexFmt;   // pageShiftX, pageShiftY, pixelsPerPageShift, unpackedShift
uniform ivec4 uTexFmt2;  // bitOffset, texelBits, tableOffset, kind (0 CT32, 1 CT24, 2 CT16, 3 indexed)
uniform ivec4 uRtFmt;    // pageShiftX, pageShiftY, pixelsPerPageShift, bits per pixel
uniform ivec4 uRtFmt2;   // inverseTableOffset, fbp (pages), fbw (64 px), 0
uniform ivec4 uTex0;     // tbp, tbw, width, height
uniform vec2 uRtPx;      // render target size in PS2 pixels

uint tab(uint i) { return texelFetch(uTables, ivec2(int(i & 2047u), int(i >> 11)), 0).r; }

vec4 reinterpretTexel(ivec2 p)
{
    uint x = uint(p.x), y = uint(p.y);
    uint psx = uint(uTexFmt.x), psy = uint(uTexFmt.y);
    uint pagesPerRow = (uint(uTex0.y) * 64u) >> psx;
    uint page = (uint(uTex0.x) >> 5) + (y >> psy) * pagesPerRow + (x >> psx);
    uint entry = ((uint(uTex0.x) & 31u) << (psx + psy)) + ((y & ((1u << psy) - 1u)) << psx) + (x & ((1u << psx) - 1u));
    uint pixelIndex = (page << uint(uTexFmt.z)) + tab(uint(uTexFmt2.z) + entry);
    uint bitpos = (pixelIndex << uint(uTexFmt.w)) + uint(uTexFmt2.x);
    uint B = uint(uRtFmt.w);
    uint rtIdx = bitpos / B;
    uint within = bitpos % B;
    uint rtBase = uint(uRtFmt2.y) << uint(uRtFmt.z);
    if (rtIdx < rtBase) return vec4(1.0, 0.0, 1.0, 1.0);
    uint rel = rtIdx - rtBase;
    uint rpage = rel >> uint(uRtFmt.z);
    uint inpage = rel & ((1u << uint(uRtFmt.z)) - 1u);
    uint e = tab(uint(uRtFmt2.x) + inpage);
    uint rpsx = uint(uRtFmt.x), rpsy = uint(uRtFmt.y);
    uint fbw = uint(uRtFmt2.z);
    uint px = (rpage % fbw) * (1u << rpsx) + (e & ((1u << rpsx) - 1u));
    uint py = (rpage / fbw) * (1u << rpsy) + (e >> rpsx);
    vec4 c = texture(uRtColor, (vec2(float(px), float(py)) + 0.5) / uRtPx) * 255.0;
    c = floor(c + 0.5);
    uint word;
    if (B == 32u)
        word = uint(c.r) | (uint(c.g) << 8) | (uint(c.b) << 16) | (uint(c.a) << 24);
    else
        word = (c.a >= 128.0 ? 0x8000u : 0u) | ((uint(c.b) >> 3) << 10) | ((uint(c.g) >> 3) << 5) | (uint(c.r) >> 3);
    uint bits = uint(uTexFmt2.y);
    uint value = (bits >= 32u) ? (word >> within) : ((word >> within) & ((1u << bits) - 1u));
    int kind = uTexFmt2.w;
    if (kind == 0) return vec4(float(value & 255u), float((value >> 8) & 255u), float((value >> 16) & 255u), float((value >> 24) & 255u)) / 255.0;
    if (kind == 1) return vec4(float(value & 255u), float((value >> 8) & 255u), float((value >> 16) & 255u), 128.0) / 255.0; // alpha via uRtTex24 path
    if (kind == 2)
    {
        vec3 rgb = vec3(float(value & 31u), float((value >> 5) & 31u), float((value >> 10) & 31u)) * 8.0;
        return vec4(rgb, ((value & 0x8000u) != 0u) ? 128.0 : 0.0) / 255.0;
    }
    return texelFetch(uPalette, ivec2(int(value & 255u), 0), 0);
}
)";

    const char *kFsTail = R"(
// Paletted textures (T8/T4 and their H variants): uTex holds the indices (R8, cached per VRAM upload), the colour comes
// from uIdxPalette (256x1, cached per CLUT); filtering is done on the looked-up colours like the GS.
uniform int uIndexed, uLinear;
uniform ivec4 uWrap; // per axis (x, y): 0 repeat, 1 clamp
uniform sampler2D uIdxPalette;
vec4 indexedTexel(ivec2 p)
{
    ivec2 size = max(ivec2(uTexDim), ivec2(1));
    p.x = (uWrap.x == 0) ? ((p.x % size.x) + size.x) % size.x : clamp(p.x, 0, size.x - 1);
    p.y = (uWrap.y == 0) ? ((p.y % size.y) + size.y) % size.y : clamp(p.y, 0, size.y - 1);
    int idx = int(texelFetch(uTex, p, 0).r * 255.0 + 0.5);
    return texelFetch(uIdxPalette, ivec2(idx, 0), 0);
}
uniform int uTme, uFst, uTfx, uTcc, uIip;
uniform int uRtTex24; // sampling a render target as PSMCT24 (1) or PSMCT16 (2): alpha comes from TEXA
uniform float uTa0;
uniform float uTa1;
uniform int uAem;
uniform int uAte, uAtst, uAref;
uniform int uFailTint; // debug: GOW_GS_HW_FAILTINT paints alpha-test failing fragments magenta
uniform int uPass; // 0 = no alpha test, 1 = keep passing fragments, 2 = keep failing fragments
uniform float uBlendScale; // 1/128 style: alpha factor = min(a * scale, 1)

float clamp255(float v) { return clamp(floor(v), 0.0, 255.0); }

bool alphaPasses(float a)
{
    int ai = int(a);
    switch (uAtst)
    {
    case 0: return false;
    case 1: return true;
    case 2: return ai < uAref;
    case 3: return ai <= uAref;
    case 4: return ai == uAref;
    case 5: return ai >= uAref;
    case 6: return ai > uAref;
    default: return ai != uAref;
    }
}

vec3 blendSel(int sel, vec3 cs, vec3 cd) { return sel == 0 ? cs : sel == 1 ? cd : vec3(0.0); }

void main()
{
    uint zFrag = uint(clamp(gl_FragCoord.z, 0.0, 1.0) * uZAliasMax + 0.5);
    if (uZAlias != 0)
    {
        vec4 d = floor(texelFetch(uDest, ivec2(gl_FragCoord.xy), 0) * 255.0 + 0.5);
        uint zd = uint(d.r) | (uint(d.g) << 8) | (uint(d.b) << 16);
        int ztst = uZAlias - 1;
        bool pass = ztst == 1 || (ztst == 2 && zFrag >= zd) || (ztst == 3 && zFrag > zd);
        if (!pass) discard;
    }
    if (uDate != 0)
    {
        bool bit = texelFetch(uDest, ivec2(gl_FragCoord.xy), 0).a >= 0.5;
        if (bit != (uDatm != 0)) discard;
    }
    vec4 v = (uIip != 0) ? vCol : vColFlat;
    vec3 rgb = v.rgb;
    float a = v.a;
    if (uTme != 0)
    {
        // U = S/Q with the sign of Q: a negative Q flips both coordinates (the menu Kratos has one)
        float q = (abs(vSTQ.z) < 1e-30) ? 1e-30 : vSTQ.z;
        vec2 uv = (uFst != 0) ? vUV : (vSTQ.xy / q) * uTexDim;
        // at the internal scale a pixel samples between the GS's sample points: keep it inside the range the GS samples
        // (sprites), so filtering never reaches the texel beyond the primitive's last one
        uv = clamp(uv, vUVClamp.xy, vUVClamp.zw);
        // point sampling picks texel floor(u) of the GS's 1/16 texel coordinate: truncate like the GS (the 1/64 step
        // absorbs float interpolation error, a 1:1 copy lands exactly on texel edges)
        if (uLinear == 0)
            uv = floor(uv * 16.0 + 0.015625) / 16.0;
        vec4 t;
        if (uReinterp != 0)
        {
            ivec2 ip = ivec2(floor(uv));
            ip = ivec2(clamp(ip.x, 0, uTex0.z - 1), clamp(ip.y, 0, uTex0.w - 1));
            t = reinterpretTexel(ip) * 255.0;
        }
        else if (uIndexed != 0)
        {
            if (uLinear != 0)
            {
                vec2 f = uv - 0.5;
                ivec2 i0 = ivec2(floor(f));
                vec2 w = f - floor(f);
                t = mix(mix(indexedTexel(i0), indexedTexel(i0 + ivec2(1, 0)), w.x),
                        mix(indexedTexel(i0 + ivec2(0, 1)), indexedTexel(i0 + ivec2(1, 1)), w.x), w.y) * 255.0;
            }
            else
                t = indexedTexel(ivec2(floor(uv))) * 255.0;
        }
        else if (uZTex != 0)
        {
            vec2 zhost = vec2(textureSize(uTex, 0)); // depth is always point sampled: the host texel's centre
            float zf = texture(uTex, (floor(uv * zhost / uTexSize + 0.001) + 0.5) / zhost).r;
            uint zi = uint(clamp(zf, 0.0, 1.0) * uZMax + 0.5);
            if (uZTex == 16)
            {
                vec3 rgb = vec3(float(zi & 31u), float((zi >> 5) & 31u), float((zi >> 10) & 31u)) * 8.0;
                t = vec4(rgb, ((zi & 0x8000u) != 0u) ? 128.0 : 0.0);
            }
            else
                t = vec4(float(zi & 255u), float((zi >> 8) & 255u), float((zi >> 16) & 255u), 128.0);
        }
        else if (uLinear == 0)
        {
            // the centre of the host texel (render targets are scaled) inside texel floor(u): never on a texel edge
            vec2 host = vec2(textureSize(uTex, 0));
            t = texture(uTex, (floor(uv * host / uTexSize + 0.001) + 0.5) / host) * 255.0;
        }
        else
            t = texture(uTex, uv / uTexSize) * 255.0;
        t = floor(t + 0.5);
        if (uRtTex24 == 1)
            t.a = (uAem != 0 && t.r + t.g + t.b == 0.0) ? 0.0 : uTa0;
        else if (uRtTex24 == 2)
            t.a = (uAem != 0 && t.r + t.g + t.b == 0.0) ? 0.0 : ((t.a >= 128.0) ? uTa1 : uTa0);
        float ta = (uTcc != 0) ? t.a : v.a;
        if (uTfx == 0)
        {
            rgb = vec3(clamp255(t.r * v.r / 128.0), clamp255(t.g * v.g / 128.0), clamp255(t.b * v.b / 128.0));
            a = (uTcc != 0) ? clamp255(t.a * v.a / 128.0) : v.a;
        }
        else if (uTfx == 1)
        {
            rgb = t.rgb;
            a = ta;
        }
        else if (uTfx == 2)
        {
            rgb = vec3(clamp255(t.r * v.r / 128.0 + v.a), clamp255(t.g * v.g / 128.0 + v.a), clamp255(t.b * v.b / 128.0 + v.a));
            a = (uTcc != 0) ? clamp255(t.a + v.a) : v.a;
        }
        else
        {
            rgb = vec3(clamp255(t.r * v.r / 128.0 + v.a), clamp255(t.g * v.g / 128.0 + v.a), clamp255(t.b * v.b / 128.0 + v.a));
            a = ta;
        }
    }
    if (uPass != 0)
    {
        bool pass = (uAte == 0) || alphaPasses(a);
        if (uPass == 1 && !pass) discard;
        if (uPass == 2 && pass) discard;
        if (uPass == 2 && uFailTint != 0) { rgb = vec3(255.0, 0.0, 255.0); a = 128.0; }
    }
    if (uSwBlend != 0)
    {
        vec4 d = floor(texelFetch(uDest, ivec2(gl_FragCoord.xy), 0) * 255.0 + 0.5);
        vec3 cs = floor(rgb);
        float c = uAbcd.z == 0 ? a : uAbcd.z == 1 ? d.a : uFix;
        vec3 r = floor((blendSel(uAbcd.x, cs, d.rgb) - blendSel(uAbcd.y, cs, d.rgb)) * c / 128.0) + blendSel(uAbcd.w, cs, d.rgb);
        rgb = (uColClamp != 0) ? clamp(r, 0.0, 255.0) : r - 256.0 * floor(r / 256.0);
    }
    if (uZAlias != 0 && uZAliasWrite != 0)
        rgb = vec3(float(zFrag & 255u), float((zFrag >> 8) & 255u), float((zFrag >> 16) & 255u));
    oColor = vec4(rgb / 255.0, a / 255.0);
    float f = min(a * uBlendScale, 1.0);
    oBlend = vec4(f);
}
)";

    // Channel shuffle: the game moves bytes between the colour channels of a 32 bit target (or out of the Z buffer) by drawing
    // 8 px sprites through a 16 bit view of that memory. In a 16 bit view, the two 8 px halves of each 16 px column group are
    // the low and high halfwords of the same 8 owner pixels, so every such sprite is a halfword move between owner pixels:
    // one quad per 8x8 owner block, source = owner pixel of the texel (+ offset), halfword selected by uHs / uHd. The written
    // bytes are chosen by the colour mask (FBMSK). The alpha bit goes through TEXA (uTexa), the colour bits are copied.
    const char *kShuffleVs = R"(#version 430 core
layout(location = 0) in vec2 aPos;   // destination owner pixel (PS2 px)
layout(location = 1) in vec2 aOff;   // source owner pixel - destination owner pixel
uniform vec2 uInvSize;
flat out vec2 vOff;
void main()
{
    gl_Position = vec4(aPos * uInvSize * 2.0 - 1.0, 0.0, 1.0);
    vOff = aOff;
}
)";
    const char *kShuffleFs = R"(#version 430 core
flat in vec2 vOff;
out vec4 oColor;
uniform sampler2D uSrc;
uniform int uSrcZ;     // source is a depth buffer (Z words)
uniform float uZMax;
uniform int uHs, uHd;  // source / destination halfword (0 low = R,G; 1 high = B,A)
uniform float uScale;
uniform ivec4 uTexa;   // TA0 >> 7, TA1 >> 7, AEM: what the 16 bit texel's alpha bit becomes after expansion and re-packing
void main()
{
    ivec2 p = ivec2(gl_FragCoord.xy) + ivec2(round(vOff * uScale));
    vec4 c;
    if (uSrcZ != 0)
    {
        uint z = uint(clamp(texelFetch(uSrc, p, 0).r, 0.0, 1.0) * uZMax + 0.5);
        c = vec4(float(z & 255u), float((z >> 8) & 255u), float((z >> 16) & 255u), float(z >> 24)) / 255.0;
    }
    else
        c = texelFetch(uSrc, p, 0);
    vec2 h = (uHs == 0) ? c.rg : c.ba;
    uint v = uint(h.x * 255.0 + 0.5) | (uint(h.y * 255.0 + 0.5) << 8);
    uint rgb = v & 0x7FFFu;
    uint a = (uTexa.z != 0 && rgb == 0u) ? 0u : uint((v & 0x8000u) != 0u ? uTexa.y : uTexa.x);
    v = rgb | (a << 15);
    h = vec2(float(v & 255u), float(v >> 8)) / 255.0;
    oColor = (uHd == 0) ? vec4(h, 0.0, 0.0) : vec4(0.0, 0.0, h);
}
)";

    struct ShuffleVertex
    {
        float x, y, ox, oy;
    };

    // Display output: copies one read circuit (offset DBX/DBY) into the presentation framebuffer; circuit 1 is blended over
    // circuit 2 by fixed-function blending (ALP or its own alpha x2).
    const char *kPresentVs = R"(#version 430 core
void main()
{
    vec2 p = vec2(float((gl_VertexID << 1) & 2), float(gl_VertexID & 2));
    gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);
}
)";
    const char *kPresentFs = R"(#version 430 core
out vec4 oColor;
uniform sampler2D uSrc;
uniform ivec4 uSrcOffset; // x, y: source pixel of output pixel 0; z: 1 = CT24 (alpha 0x80); w: 1 = alpha x2 as blend factor
uniform int uSrcEdge; // first source row/column shown; the ones before it repeat it
void main()
{
    ivec2 p = max(ivec2(gl_FragCoord.xy) + uSrcOffset.xy, ivec2(uSrcEdge));
    ivec2 size = textureSize(uSrc, 0);
    vec4 c = (p.x < size.x && p.y < size.y) ? texelFetch(uSrc, p, 0) : vec4(0.0);
    float a = (uSrcOffset.z != 0) ? 128.0 / 255.0 : c.a;
    oColor = vec4(c.rgb, (uSrcOffset.w != 0) ? min(1.0, a * 2.0) : a);
}
)";

    // CLUT fetch: output pixel i is the raw word of CLUT source pixel i (its x, y in uCoords) as the game's GS memory holds
    // it, read from the render target that owns that memory through the reinterpreting fetch (kind 0: the word's bytes).
    const char *kClutFsHead = R"(#version 430 core
out vec4 oColor;
)";
    const char *kClutFsMain = R"(
uniform usampler2D uCoords;
void main()
{
    uvec2 c = texelFetch(uCoords, ivec2(int(gl_FragCoord.x), 0), 0).rg;
    oColor = reinterpretTexel(ivec2(c));
}
)";

    // GS vertex as sent to the GPU.
    struct HwVertex
    {
        float x, y, z;
        float r, g, b, a;
        float s, t, q;
        float u, v;
        float cu0 = -1e30f, cv0 = -1e30f, cu1 = 1e30f, cv1 = 1e30f; // texel range the GS samples (sprites)
    };

    struct Texture
    {
        GLuint id = 0;
        uint32_t width = 0, height = 0;
        uint32_t blockLo = 0, blockHi = 0;
        bool valid = false;
        uint64_t lastUse = 0;
    };

    struct RenderTarget
    {
        GLuint color = 0, depth = 0, fbo = 0;
        uint32_t fbp = 0, fbw = 1; // PS2 page base and width in 64 px units
        uint8_t psm = 0;
        uint32_t zbp = ~0u;
        uint32_t pxW = 0, pxH = 0; // size in PS2 pixels
        uint32_t glW = 0, glH = 0;
        bool depthCleared = false;
        uint64_t version = 1, lastDrawSeq = 0;
        uint64_t lastDepthSeq = 0; // writeSeq of the last draw that wrote this target's depth (memory at zbp)
        uint32_t usedW = 0, usedH = 0; // PS2 pixels touched by draws (scissor extents)
    };

    uint32_t pageRowsFor(uint32_t psm)
    {
        switch (psm & 0x3F)
        {
        case 0x13: case 0x1B: case 0x24: case 0x2C: return 64u;  // T8 / T8H
        case 0x14: case 0x2C + 1: return 128u;                    // T4
        case 0x02: case 0x0A: case 0x32: case 0x3A: return 64u;  // 16 bit
        default: return 32u;
        }
    }

    // conservative block (256 B) span of `rows` rows of a buffer `bw` (64 px units) wide
    uint32_t spanBlocks(uint32_t psm, uint32_t bw, uint32_t rows)
    {
        const uint32_t pagesDown = (rows + pageRowsFor(psm) - 1u) / pageRowsFor(psm);
        return std::max<uint32_t>(1u, pagesDown) * std::max<uint32_t>(1u, bw) * 32u;
    }
}

struct GSHwBackend::Impl
{
    bool xferWatchHit = false; // GOW_GS_HW_XFERWATCH: log the next upload's first bytes
    GSTextureStore store; // uploaded texture bytes + CLUT (no rasteriser, no framebuffer)
    GSGL::Context context;
    bool initialized = false, failed = false;
    uint8_t *vram = nullptr;
    uint32_t vramSize = 0;

    float scale = 2.0f;
    GLuint program = 0, vao = 0, vbo = 0;
    GLint locInvSize = -1, locTex = -1, locTexSize = -1, locTexDim = -1, locTme = -1, locFst = -1, locTfx = -1, locTcc = -1, locIip = -1,
          locAte = -1, locFailTint = -1, locAtst = -1, locAref = -1, locPass = -1, locBlendScale = -1, locRtTex24 = -1, locTa0 = -1, locTa1 = -1, locReinterp = -1, locDate = -1, locDatm = -1, locDest = -1, locZTex = -1, locZMax = -1, locTables = -1, locRtColor = -1, locPalette = -1, locTexFmt = -1, locTexFmt2 = -1,
          locRtFmt = -1, locRtFmt2 = -1, locTex0 = -1, locRtPx = -1, locAem = -1;
    GLint locIndexed = -1, locLinear = -1, locWrap = -1, locIdxPalette = -1;
    GLint locSwBlend = -1, locColClamp = -1, locAbcd = -1, locFix = -1, locZAlias = -1, locZAliasWrite = -1, locZAliasMax = -1;

    GLuint tableTex = 0, paletteTex = 0;
    GLuint presentProgram = 0, presentVao = 0, presentFbo = 0, presentTex = 0;
    GLint locPresentSrc = -1, locPresentOffset = -1, locPresentEdge = -1;
    uint32_t presentW = 0, presentH = 0;
    GLuint shuffleProgram = 0, shuffleVao = 0, shuffleVbo = 0;
    GLint locShTexa = -1;
    GLint locShInvSize = -1, locShSrc = -1, locShSrcZ = -1, locShZMax = -1, locShHs = -1, locShHd = -1, locShScale = -1;
    // queued shuffle sprites of one state, as owner-space quads per (source half, destination half)
    std::vector<ShuffleVertex> shuffleQuads[4];
    GSDrawState shuffleState{};
    bool haveShuffle = false;
    int shuffleWhy = 0; // debug: which tryShuffle check rejected the last sprite
    RenderTarget *shuffleDst = nullptr, *shuffleSrc = nullptr;
    bool shuffleSrcZ = false;
    std::unordered_map<uint32_t, std::vector<uint16_t>> ownerInverse; // psm -> in-page word index -> y * 64 + x
    std::unordered_map<const uint16_t *, uint32_t> tableOffset;
    std::unordered_map<uint32_t, uint32_t> inverseOffset; // psm -> offset of the inverse page table
    std::vector<HwVertex> pending;
    // the previous sprite of the pending batch (strip seams: see the sprite path in draw)
    struct SpriteEdges
    {
        float xs[2], ys[2], us[2], vs[2]; // corners: texel coordinates us/vs at screen edges xs/ys
    };
    struct LastSprite
    {
        SpriteEdges edges{};
        size_t end = 0;           // pending.size() right after it
        uint64_t batch = ~0ull;   // batchSerial when it was added
    } lastSprite;
    uint64_t batchSerial = 0; // counts flushes of the pending batch

    // Opens the clamp on the side two consecutive sprites share when the texture continues across it: same extent and
    // texel range along the seam, touching screen edges, equal texel coordinate at the seam.
    static void openSharedSide(const SpriteEdges &prev, const SpriteEdges &cur, HwVertex *prevVertices, float &cu0, float &cu1,
                               float &cv0, float &cv1)
    {
        const auto same = [](const float a[2], const float b[2], float tol)
        {
            return std::fabs(std::min(a[0], a[1]) - std::min(b[0], b[1])) <= tol &&
                   std::fabs(std::max(a[0], a[1]) - std::max(b[0], b[1])) <= tol;
        };
        constexpr float kXyTol = 1.0f / 64.0f, kUvTol = 1.0f / 32.0f;
        // along one axis: p/c = screen edges, pt/ct = texel coordinates at them; returns the edge index of each sprite
        const auto seam = [&](const float p[2], const float pt[2], const float c[2], const float ct[2], int &ip, int &ic)
        {
            for (ip = 0; ip < 2; ++ip)
                for (ic = 0; ic < 2; ++ic)
                    if (std::fabs(p[ip] - c[ic]) <= kXyTol && std::fabs(pt[ip] - ct[ic]) <= kUvTol &&
                        // the two sprites lie on opposite sides of the seam
                        (p[1 - ip] - p[ip]) * (c[1 - ic] - c[ic]) < 0.0f)
                        return true;
            return false;
        };
        int ip = 0, ic = 0;
        if (same(prev.ys, cur.ys, kXyTol) && same(prev.vs, cur.vs, kUvTol) && seam(prev.xs, prev.us, cur.xs, cur.us, ip, ic))
        {
            const bool prevHigh = prev.us[ip] > prev.us[1 - ip], curHigh = cur.us[ic] > cur.us[1 - ic];
            for (int i = 0; i < 6; ++i)
                (prevHigh ? prevVertices[i].cu1 : prevVertices[i].cu0) = prevHigh ? 1e30f : -1e30f;
            (curHigh ? cu1 : cu0) = curHigh ? 1e30f : -1e30f;
        }
        else if (same(prev.xs, cur.xs, kXyTol) && same(prev.us, cur.us, kUvTol) && seam(prev.ys, prev.vs, cur.ys, cur.vs, ip, ic))
        {
            const bool prevHigh = prev.vs[ip] > prev.vs[1 - ip], curHigh = cur.vs[ic] > cur.vs[1 - ic];
            for (int i = 0; i < 6; ++i)
                (prevHigh ? prevVertices[i].cv1 : prevVertices[i].cv0) = prevHigh ? 1e30f : -1e30f;
            (curHigh ? cv1 : cv0) = curHigh ? 1e30f : -1e30f;
        }
    }
    GSDrawState pendingState{};
    bool havePending = false;
    double firstRawZ = 0.0;

    std::unordered_map<uint64_t, Texture> textures;
    std::vector<RenderTarget> targets;
    uint64_t useCounter = 0, writeSeq = 0;
    struct UploadRecord { uint32_t lo, hi; uint64_t seq; };
    std::vector<UploadRecord> uploadLog;
    uint64_t clutHash = 0;

    struct Stats
    {
        uint64_t shuffles = 0;
        uint64_t draws = 0, batches = 0, skippedPsm = 0, unsupportedBlend = 0, texDecodes = 0, texHits = 0, skippedPrim = 0;
        std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
    } stats;
    bool statsEnabled = std::getenv("GOW_GS_HW_STATS") != nullptr;

    const Api &gl() const { return context.gl(); }

    GLuint compile(GLenum type, const char *src) { return compile(type, {src}); }
    GLuint compile(GLenum type, std::initializer_list<const char *> parts)
    {
        const Api &g = gl();
        const GLuint sh = g.CreateShader(type);
        g.ShaderSource(sh, static_cast<GLsizei>(parts.size()), parts.begin(), nullptr);
        g.CompileShader(sh);
        GLint ok = 0;
        g.GetShaderiv(sh, kCompileStatus, &ok);
        if (!ok)
        {
            char log[2048];
            GLsizei n = 0;
            g.GetShaderInfoLog(sh, sizeof(log), &n, log);
            std::fprintf(stderr, "[gs-hw] shader error: %s\n", log);
            return 0;
        }
        return sh;
    }

    bool ensure()
    {
        if (initialized)
            return true;
        if (failed)
            return false;
        std::string error;
        if (!context.Create(error) || !gl().hwRaster)
        {
            std::fprintf(stderr, "[gs-hw] GL unavailable: %s\n", error.c_str());
            failed = true;
            return false;
        }
        const Api &g = gl();
        const GLuint v = compile(GSGL::kVertexShader, kVsSource);
        const GLuint f = compile(GSGL::kFragmentShader, {kFsSource, kReinterpretSource, kFsTail});
        if (!v || !f)
        {
            failed = true;
            return false;
        }
        program = g.CreateProgram();
        g.AttachShader(program, v);
        g.AttachShader(program, f);
        g.LinkProgram(program);
        GLint ok = 0;
        g.GetProgramiv(program, kLinkStatus, &ok);
        if (!ok)
        {
            char log[2048];
            GLsizei n = 0;
            g.GetProgramInfoLog(program, sizeof(log), &n, log);
            std::fprintf(stderr, "[gs-hw] link error: %s\n", log);
            failed = true;
            return false;
        }
        const auto loc = [&](const char *name) { return g.GetUniformLocation(program, name); };
        locInvSize = loc("uInvSize"); locTex = loc("uTex"); locTexSize = loc("uTexSize"); locTexDim = loc("uTexDim"); locTme = loc("uTme");
        locFst = loc("uFst"); locTfx = loc("uTfx"); locTcc = loc("uTcc"); locIip = loc("uIip"); locAte = loc("uAte");
        locAtst = loc("uAtst"); locFailTint = loc("uFailTint"); locAref = loc("uAref"); locPass = loc("uPass"); locBlendScale = loc("uBlendScale");
        locReinterp = loc("uReinterp"); locDate = loc("uDate"); locDatm = loc("uDatm"); locDest = loc("uDest"); locZTex = loc("uZTex"); locZMax = loc("uZMax"); locTables = loc("uTables"); locRtColor = loc("uRtColor"); locPalette = loc("uPalette");
        locTexFmt = loc("uTexFmt"); locTexFmt2 = loc("uTexFmt2"); locRtFmt = loc("uRtFmt"); locRtFmt2 = loc("uRtFmt2");
        locTex0 = loc("uTex0"); locRtPx = loc("uRtPx");
        locIndexed = loc("uIndexed"); locLinear = loc("uLinear"); locWrap = loc("uWrap"); locIdxPalette = loc("uIdxPalette");
        locSwBlend = loc("uSwBlend"); locColClamp = loc("uColClamp"); locAbcd = loc("uAbcd"); locFix = loc("uFix");
        locZAlias = loc("uZAlias"); locZAliasWrite = loc("uZAliasWrite"); locZAliasMax = loc("uZAliasMax");
        locRtTex24 = loc("uRtTex24"); locTa0 = loc("uTa0"); locTa1 = loc("uTa1"); locAem = loc("uAem");

        g.GenVertexArrays(1, &vao);
        g.BindVertexArray(vao);
        g.GenBuffers(1, &vbo);
        g.BindBuffer(kArrayBuffer, vbo);
        const GLsizei stride = sizeof(HwVertex);
        g.VertexAttribPointer(0, 2, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, x)));
        g.VertexAttribPointer(1, 1, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, z)));
        g.VertexAttribPointer(2, 4, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, r)));
        g.VertexAttribPointer(3, 3, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, s)));
        g.VertexAttribPointer(4, 2, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, u)));
        g.VertexAttribPointer(5, 4, kFloat, kFalse, stride, reinterpret_cast<const void *>(offsetof(HwVertex, cu0)));
        for (GLuint i = 0; i < 6; ++i)
            g.EnableVertexAttribArray(i);
        buildTables();
        {
            const GLuint sv = compile(GSGL::kVertexShader, kShuffleVs), sfs = compile(GSGL::kFragmentShader, kShuffleFs);
            if (sv && sfs)
            {
                shuffleProgram = g.CreateProgram();
                g.AttachShader(shuffleProgram, sv);
                g.AttachShader(shuffleProgram, sfs);
                g.LinkProgram(shuffleProgram);
                const auto sloc = [&](const char *name) { return g.GetUniformLocation(shuffleProgram, name); };
                locShInvSize = sloc("uInvSize"); locShSrc = sloc("uSrc"); locShSrcZ = sloc("uSrcZ"); locShZMax = sloc("uZMax");
                locShHs = sloc("uHs"); locShHd = sloc("uHd"); locShScale = sloc("uScale"); locShTexa = sloc("uTexa");
                g.GenVertexArrays(1, &shuffleVao);
                g.BindVertexArray(shuffleVao);
                g.GenBuffers(1, &shuffleVbo);
                g.BindBuffer(kArrayBuffer, shuffleVbo);
                g.VertexAttribPointer(0, 2, kFloat, kFalse, sizeof(ShuffleVertex), reinterpret_cast<const void *>(offsetof(ShuffleVertex, x)));
                g.VertexAttribPointer(1, 2, kFloat, kFalse, sizeof(ShuffleVertex), reinterpret_cast<const void *>(offsetof(ShuffleVertex, ox)));
                g.EnableVertexAttribArray(0);
                g.EnableVertexAttribArray(1);
                g.BindVertexArray(vao);
                g.BindBuffer(kArrayBuffer, vbo);
            }
        }
        {
            const GLuint pv = compile(GSGL::kVertexShader, kPresentVs), pf = compile(GSGL::kFragmentShader, kPresentFs);
            if (pv && pf)
            {
                presentProgram = g.CreateProgram();
                g.AttachShader(presentProgram, pv);
                g.AttachShader(presentProgram, pf);
                g.LinkProgram(presentProgram);
                locPresentSrc = g.GetUniformLocation(presentProgram, "uSrc");
                locPresentOffset = g.GetUniformLocation(presentProgram, "uSrcOffset");
                locPresentEdge = g.GetUniformLocation(presentProgram, "uSrcEdge");
                g.GenVertexArrays(1, &presentVao);
                g.BindVertexArray(vao);
            }
        }
        if (const char *s = std::getenv("PS2X_GS_HW_SCALE"))
            scale = std::max(1.0f, static_cast<float>(std::atof(s)));
        std::fprintf(stderr, "[gs-hw] render-target renderer ready, scale %.2f (%s)\n", scale,
                     reinterpret_cast<const char *>(g.GetString(kRenderer)));
        initialized = true;
        return true;
    }

    // forward page tables of every texture format + inverse tables (in-page pixel index -> in-page x/y) of the render-target
    // formats, in one R16UI texture (2048 entries per row)
    void buildTables()
    {
        const Api &g = gl();
        std::vector<uint16_t> data;
        const uint32_t psms[] = {0x00, 0x01, 0x02, 0x0A, 0x13, 0x14, 0x1B, 0x24, 0x2C};
        for (const uint32_t psm : psms)
        {
            const GSSwizzle::Format &f = GSSwizzle::GetFormat(psm);
            if (!f.table || tableOffset.count(f.table))
                continue;
            const uint32_t size = 32u << (f.pageShiftX + f.pageShiftY);
            tableOffset[f.table] = static_cast<uint32_t>(data.size());
            data.insert(data.end(), f.table, f.table + size);
        }
        for (const uint32_t psm : {0x00u, 0x01u, 0x02u, 0x0Au})
        {
            const GSSwizzle::Format &f = GSSwizzle::GetFormat(psm);
            const uint32_t pageSize = 1u << (f.pageShiftX + f.pageShiftY);
            inverseOffset[psm] = static_cast<uint32_t>(data.size());
            data.resize(data.size() + pageSize, 0);
            uint16_t *inv = &data[inverseOffset[psm]];
            for (uint32_t e = 0; e < pageSize; ++e)
                inv[f.table[e]] = static_cast<uint16_t>(e);
        }
        const uint32_t rows = static_cast<uint32_t>((data.size() + 2047u) / 2048u);
        data.resize(static_cast<size_t>(rows) * 2048u, 0);
        g.GenTextures(1, &tableTex);
        g.BindTexture(kTexture2D, tableTex);
        g.PixelStorei(kUnpackAlignment, 1);
        g.TexImage2D(kTexture2D, 0, 0x8234 /*R16UI*/, 2048, rows, 0, 0x8D94 /*RED_INTEGER*/, 0x1403 /*UNSIGNED_SHORT*/, data.data());
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        g.GenTextures(1, &paletteTex);
        g.BindTexture(kTexture2D, paletteTex);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), 256, 1, 0, kRgba, kUnsignedByte, nullptr);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
    }

    // ---- render targets -------------------------------------------------------------------------------------------
    RenderTarget &target(uint32_t fbp, uint32_t fbw)
    {
        for (RenderTarget &t : targets)
            if (t.fbp == fbp && t.fbw >= fbw)
                return t;
        static const bool rtLog = std::getenv("GOW_GS_HW_RTLOG") != nullptr;
        if (rtLog)
            std::fprintf(stderr, "[gs-hw-rt] new/grow fbp=%u fbw=%u\n", fbp, fbw);
        for (RenderTarget &t : targets) // grow an existing one
            if (t.fbp == fbp)
            {
                destroy(t);
                createTarget(t, fbp, fbw);
                return t;
            }
        targets.emplace_back();
        createTarget(targets.back(), fbp, fbw);
        return targets.back();
    }

    void destroy(RenderTarget &t)
    {
        const Api &g = gl();
        if (t.fbo) g.DeleteFramebuffers(1, &t.fbo);
        if (t.color) g.DeleteTextures(1, &t.color);
        if (t.depth) g.DeleteTextures(1, &t.depth);
        t = {};
    }

    void createTarget(RenderTarget &t, uint32_t fbp, uint32_t fbw)
    {
        const Api &g = gl();
        t.fbp = fbp;
        t.psm = 0;
        t.fbw = std::max<uint32_t>(fbw, 1u);
        t.pxW = t.fbw * 64u;
        t.pxH = 512u;
        t.glW = static_cast<uint32_t>(std::ceil(t.pxW * scale));
        t.glH = static_cast<uint32_t>(std::ceil(t.pxH * scale));
        g.GenTextures(1, &t.color);
        g.BindTexture(kTexture2D, t.color);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), t.glW, t.glH, 0, kRgba, kUnsignedByte, nullptr);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kLinear);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kLinear);
        g.GenFramebuffers(1, &t.fbo);
        g.BindFramebuffer(kFramebuffer, t.fbo);
        g.FramebufferTexture2D(kFramebuffer, kColorAttachment0, kTexture2D, t.color, 0);
        g.ClearColor(0.f, 0.f, 0.f, 0.f);
        g.Clear(kColorBufferBit);
        std::fprintf(stderr, "[gs-hw] render target fbp=%u fbw=%u -> %ux%u\n", fbp, t.fbw, t.glW, t.glH);
    }

    void attachDepth(RenderTarget &t, uint32_t zbp)
    {
        const Api &g = gl();
        if (!t.depth)
        {
            g.GenTextures(1, &t.depth);
            g.BindTexture(kTexture2D, t.depth);
            g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kDepthComponent32F), t.glW, t.glH, 0, kDepthComponent, kFloat, nullptr);
            g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
            g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
            g.BindFramebuffer(kFramebuffer, t.fbo);
            g.FramebufferTexture2D(kFramebuffer, kDepthAttachment, kTexture2D, t.depth, 0);
            g.ClearDepth(0.0);
            g.Clear(kDepthBufferBit);
        }
        t.zbp = zbp;
    }

    // ---- textures -------------------------------------------------------------------------------------------------
    static bool isIndexed(uint8_t psm)
    {
        return psm == GS_PSM_T8 || psm == GS_PSM_T8H || psm == GS_PSM_T4 || psm == GS_PSM_T4HL || psm == GS_PSM_T4HH;
    }

    Texture &textureFor(const GSDrawState &s)
    {
        const GSTex0Reg &t = s.context.tex0;
        uint64_t key = t.tbp0 | (static_cast<uint64_t>(t.tbw) << 14) | (static_cast<uint64_t>(t.psm & 63) << 20) |
                       (static_cast<uint64_t>(s.textureWidth) << 26) | (static_cast<uint64_t>(s.textureHeight) << 38);
        key = key * 1099511628211ull ^ (static_cast<uint64_t>(s.texa.ta0) | (static_cast<uint64_t>(s.texa.ta1) << 8) | (static_cast<uint64_t>(s.texa.aem) << 16));
        if (isIndexed(t.psm))
        {
            key = key * 1099511628211ull ^ clutHash;
            key = key * 1099511628211ull ^ (t.cpsm | (t.csm << 8) | (t.csa << 16));
        }
        Texture &tex = textures[key];
        tex.lastUse = ++useCounter;
        if (tex.valid)
        {
            ++stats.texHits;
            return tex;
        }
        ++stats.texDecodes;
        classifyTexture(s);
        const Api &g = gl();
        std::vector<uint32_t> pixels;
        decodeDirect(s, pixels);
        static const int texDumpLimit = std::getenv("GOW_GS_HW_TEXDUMP") ? std::atoi(std::getenv("GOW_GS_HW_TEXDUMP")) : 0;
        static int texDumped = 0;
        if (texDumped < texDumpLimit && s.textureWidth > 16)
        {
            char name[96];
            std::snprintf(name, sizeof(name), "gs_hw_tex_%02d_tbp%x_psm%u_%ux%u.ppm", texDumped++, t.tbp0, t.psm, s.textureWidth, s.textureHeight);
            if (FILE *f = std::fopen(name, "wb"))
            {
                std::fprintf(f, "P6 %u %u 255 ", s.textureWidth, s.textureHeight);
                for (uint32_t px : pixels)
                {
                    const uint8_t rgb[3] = {static_cast<uint8_t>(px), static_cast<uint8_t>(px >> 8), static_cast<uint8_t>(px >> 16)};
                    std::fwrite(rgb, 1, 3, f);
                }
                std::fclose(f);
            }
        }
        tex.width = std::max<uint32_t>(1u, s.textureWidth);
        tex.height = std::max<uint32_t>(1u, s.textureHeight);
        tex.blockLo = t.tbp0;
        tex.blockHi = t.tbp0 + spanBlocks(t.psm, t.tbw, tex.height);
        if (!tex.id)
            g.GenTextures(1, &tex.id);
        g.BindTexture(kTexture2D, tex.id);
        g.PixelStorei(kUnpackAlignment, 4);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), tex.width, tex.height, 0, kRgba, kUnsignedByte, pixels.data());
        tex.valid = true;
        if (textures.size() > 6000u)
            evictOld();
        return tex;
    }

    // Texels of a direct-colour texture read from GS memory with the swizzle tables, alpha expanded by TEXA like the GS
    // texture unit (CT24: TA0 / AEM, CT16: TA0/TA1 by the alpha bit).
    void decodeDirect(const GSDrawState &s, std::vector<uint32_t> &out)
    {
        const GSTex0Reg &t = s.context.tex0;
        const GSSwizzle::Format &f = GSSwizzle::GetFormat(t.psm);
        const uint32_t w = std::max<uint32_t>(1u, s.textureWidth), h = std::max<uint32_t>(1u, s.textureHeight);
        const bool sixteen = f.kind == GSSwizzle::Kind::Bits16;
        if (!vram || !f.table || !(sixteen || f.kind == GSSwizzle::Kind::Bits32 || f.kind == GSSwizzle::Kind::Bits24))
        {
            store.DecodeTextureRgba(s, out); // formats without a direct layout (none seen in this game)
            return;
        }
        out.resize(static_cast<size_t>(w) * h);
        for (uint32_t y = 0; y < h; ++y)
        {
            uint32_t *line = out.data() + static_cast<size_t>(y) * w;
            // One row at a time with the format resolved once (GSMem::ReadColorRun, same page tables as GSSwizzle):
            // big direct-colour textures (CT24 views of CT32 uploads in the Aegean Sea) were decoded per texel.
            if (!GSMem::ReadColorRun(vram, t.psm, t.tbp0, t.tbw, 0u, y, w, line))
            {
                const GSSwizzle::AxisPart row = GSSwizzle::RowPart(f, t.tbp0, t.tbw, y);
                for (uint32_t x = 0; x < w; ++x)
                {
                    const GSSwizzle::Location at = GSSwizzle::Combine(f, row, GSSwizzle::ColumnPart(f, x));
                    line[x] = GSSwizzle::LoadAt(f, vram + at.byte, at.shift);
                }
            }
            for (uint32_t x = 0; x < w; ++x)
                line[x] = GSCpuInternal::applyTexa(s.texa, t.psm, sixteen ? GSCpuInternal::Rgba5551ToRgba8888(static_cast<uint16_t>(line[x])) : line[x]);
        }
        static const bool check = std::getenv("GOW_GS_TEXCHECK") != nullptr;
        if (check)
        {
            static int mismatches = 0, checked = 0;
            for (uint32_t y = 0; y < h; ++y)
            {
                const GSSwizzle::AxisPart row = GSSwizzle::RowPart(f, t.tbp0, t.tbw, y);
                for (uint32_t x = 0; x < w; ++x)
                {
                    const GSSwizzle::Location at = GSSwizzle::Combine(f, row, GSSwizzle::ColumnPart(f, x));
                    const uint32_t raw = GSSwizzle::LoadAt(f, vram + at.byte, at.shift);
                    const uint32_t ref = GSCpuInternal::applyTexa(s.texa, t.psm, sixteen ? GSCpuInternal::Rgba5551ToRgba8888(static_cast<uint16_t>(raw)) : raw);
                    if (ref != out[static_cast<size_t>(y) * w + x] && mismatches++ < 20)
                        std::fprintf(stderr, "[gs-texcheck] psm=%u tbp=%x tbw=%u %ux%u at %u,%u ref=%08x run=%08x\n", t.psm, t.tbp0, t.tbw, w, h, x, y, ref, out[static_cast<size_t>(y) * w + x]);
                }
            }
            if (++checked % 200 == 0)
                std::fprintf(stderr, "[gs-texcheck] %d textures checked, %d mismatching texels\n", checked, mismatches);
        }
    }

    // Index texture of a paletted format: the raw indices, read from GS memory with the swizzle tables. Independent of
    // the CLUT, so palette changes (animated CLUTs, the same image with several palettes) cost nothing.
    Texture &indexTextureFor(const GSDrawState &s)
    {
        const GSTex0Reg &t = s.context.tex0;
        const uint64_t key = (1ull << 63) | t.tbp0 | (static_cast<uint64_t>(t.tbw) << 14) | (static_cast<uint64_t>(t.psm & 63) << 20) |
                             (static_cast<uint64_t>(s.textureWidth) << 26) | (static_cast<uint64_t>(s.textureHeight) << 38);
        Texture &tex = textures[key];
        tex.lastUse = ++useCounter;
        if (tex.valid)
        {
            ++stats.texHits;
            return tex;
        }
        ++stats.texDecodes;
        classifyTexture(s);
        tex.width = std::max<uint32_t>(1u, s.textureWidth);
        tex.height = std::max<uint32_t>(1u, s.textureHeight);
        std::vector<uint8_t> indices(static_cast<size_t>(tex.width) * tex.height);
        for (uint32_t y = 0; y < tex.height; ++y)
            GSMem::ReadIndexRun(vram, t.psm, t.tbp0, t.tbw, 0u, y, tex.width,
                                indices.data() + static_cast<size_t>(y) * tex.width);
        static const long idxDumpTbp = std::getenv("GOW_GS_HW_PALDUMP") ? std::strtol(std::getenv("GOW_GS_HW_PALDUMP"), nullptr, 16) : -1;
        static int idxDumped = 0;
        // GOW_GS_HW_PALDUMPMAX=<n>: dump the first n decodes of that block's index texture (default 4)
        static const int idxDumpMax = std::getenv("GOW_GS_HW_PALDUMPMAX") ? std::atoi(std::getenv("GOW_GS_HW_PALDUMPMAX")) : 4;
        if (idxDumpTbp >= 0 && static_cast<long>(t.tbp0) == idxDumpTbp && idxDumped < idxDumpMax)
        {
            ++idxDumped;
            uint32_t hist[256] = {};
            for (uint8_t i : indices)
                ++hist[i];
            uint32_t pageHash = 2166136261u;
            for (uint32_t i = 0; i < 8192u; ++i)
                pageHash = (pageHash ^ vram[static_cast<size_t>(t.tbp0) * 256u + i]) * 16777619u;
            std::fprintf(stderr, "[gs-hw-idx] tbp=%x page hash %08x %ux%u psm=%u tbw=%u (index:count)", t.tbp0, pageHash, tex.width, tex.height, t.psm, t.tbw);
            for (int i = 0; i < 256; ++i)
                if (hist[i])
                    std::fprintf(stderr, " %d:%u", i, hist[i]);
            std::fprintf(stderr, "\n");
            char name[64];
            std::snprintf(name, sizeof(name), "gs_hw_idx_%d_tbp%x_%ux%u.pgm", idxDumped, t.tbp0, tex.width, tex.height);
            if (FILE *f = std::fopen(name, "wb"))
            {
                std::fprintf(f, "P5 %u %u 255 ", tex.width, tex.height);
                std::fwrite(indices.data(), 1, indices.size(), f);
                std::fclose(f);
            }
        }
        tex.blockLo = t.tbp0;
        tex.blockHi = t.tbp0 + spanBlocks(t.psm, t.tbw, tex.height);
        const Api &g = gl();
        if (!tex.id)
            g.GenTextures(1, &tex.id);
        g.BindTexture(kTexture2D, tex.id);
        g.PixelStorei(kUnpackAlignment, 1);
        g.TexImage2D(kTexture2D, 0, 0x8229 /*R8*/, tex.width, tex.height, 0, 0x1903 /*RED*/, kUnsignedByte, indices.data());
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        tex.valid = true;
        if (textures.size() > 6000u)
            evictOld();
        return tex;
    }

    // 256x1 RGBA palette of the current CLUT as the draw reads it (format, offset, TEXA alpha)
    std::unordered_map<uint64_t, GLuint> palettes;
    GLuint paletteFor(const GSDrawState &s)
    {
        const GSTex0Reg &t = s.context.tex0;
        uint64_t key = clutHash;
        key = key * 1099511628211ull ^ (t.cpsm | (t.csm << 8) | (t.csa << 16) | (static_cast<uint64_t>(t.psm & 63) << 24));
        key = key * 1099511628211ull ^ (static_cast<uint64_t>(s.texa.ta0) | (static_cast<uint64_t>(s.texa.ta1) << 8) | (static_cast<uint64_t>(s.texa.aem) << 16));
        // GOW_GS_HW_PALDUMP=<tbp hex>: debug, print the palette of each CLUT (cbp) the draws textured from that block use (rgba per entry)
        static const long palDumpTbp = std::getenv("GOW_GS_HW_PALDUMP") ? std::strtol(std::getenv("GOW_GS_HW_PALDUMP"), nullptr, 16) : -1;
        static std::vector<uint32_t> palDumpedCbp; // one dump per CLUT address
        if (palDumpTbp >= 0 && static_cast<long>(t.tbp0) == palDumpTbp && palDumpedCbp.size() < 8 &&
            std::find(palDumpedCbp.begin(), palDumpedCbp.end(), t.cbp) == palDumpedCbp.end())
        {
            palDumpedCbp.push_back(t.cbp);
            uint32_t colors[256];
            store.BuildPalette(s, colors);
            std::fprintf(stderr, "[gs-hw-pal] tbp=%x cbp=%x cpsm=%u csm=%u csa=%u:", t.tbp0, t.cbp, t.cpsm, t.csm, t.csa);
            for (int i = 0; i < 256; ++i)
                std::fprintf(stderr, "%s%08x", (i % 16) ? " " : "\n  ", colors[i]);
            std::fprintf(stderr, "\n");
        }
        const auto it = palettes.find(key);
        if (it != palettes.end())
            return it->second;
        const Api &g = gl();
        if (palettes.size() > 4096u)
        {
            for (auto &kv : palettes)
                g.DeleteTextures(1, &kv.second);
            palettes.clear();
        }
        uint32_t colors[256];
        store.BuildPalette(s, colors);
        GLuint id = 0;
        g.GenTextures(1, &id);
        g.BindTexture(kTexture2D, id);
        g.PixelStorei(kUnpackAlignment, 4);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), 256, 1, 0, kRgba, kUnsignedByte, colors);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        palettes[key] = id;
        return id;
    }

    void evictOld()
    {
        const Api &g = gl();
        for (auto it = textures.begin(); it != textures.end();)
        {
            if (it->second.lastUse + 3000u < useCounter)
            {
                if (it->second.id)
                    g.DeleteTextures(1, &it->second.id);
                it = textures.erase(it);
            }
            else
                ++it;
        }
    }

    void invalidateBlocks(uint32_t lo, uint32_t hi)
    {
        for (auto &kv : textures)
        {
            Texture &t = kv.second;
            if (t.valid && t.blockLo < hi && lo < t.blockHi)
                t.valid = false;
        }
    }

    // The render target whose memory range holds the texture's first block (and was not overwritten by an upload since).
    // Formats that live only in bits 24-31 (T8H, T4HL, T4HH) are never written by a 24 bit target (CT24 colour, Z24): the
    // game keeps uploaded textures there, so such a target is not their source.
    RenderTarget *findReinterpretSource(uint32_t tbp, uint8_t tpsm)
    {
        const bool highByte = tpsm == GS_PSM_T8H || tpsm == GS_PSM_T4HL || tpsm == GS_PSM_T4HH;
        for (RenderTarget &t : targets)
        {
            if (t.usedW == 0u || (highByte && t.psm == GS_PSM_CT24) || overwrittenByDepth(t))
                continue;
            const uint32_t tlo = t.fbp * 32u, thi = tlo + spanBlocks(t.psm, t.fbw, t.usedH);
            if (tbp < tlo || tbp >= thi)
                continue;
            if (!uploadedSinceDraw(t, tbp))
                return &t;
        }
        return nullptr;
    }

    // True when the game uploaded new pixels at `tbp` after the target's last draw: the memory then holds the upload,
    // not the target's picture (e.g. FMV frames uploaded where a temporary target lived), so the texture comes from
    // the store.
    // True when another target's depth buffer lives in this target's memory (ZBP == its FBP) and was written after this
    // target's last colour draw: the memory then holds Z, not the colour picture. Example: the movie player draws its
    // pictures into fbp 104, which is the gameplay Z buffer; after the movie the depth writes replace them, and the
    // game's passes that read the Z memory as PSMCT24 (fog/DOF strips into fbp 320) must not see the old movie frame.
    bool overwrittenByDepth(const RenderTarget &t) const
    {
        for (const RenderTarget &o : targets)
            if (&o != &t && o.depth && o.zbp == t.fbp && o.lastDepthSeq > t.lastDrawSeq)
                return true;
        return false;
    }

    bool uploadedSinceDraw(const RenderTarget &t, uint32_t tbp) const
    {
        for (const UploadRecord &u : uploadLog)
            if (u.seq > t.lastDrawSeq && u.lo <= tbp && tbp < u.hi)
                return true;
        return false;
    }

    void setupReinterpret(const GSDrawState &s, RenderTarget &rt)
    {
        const Api &g = gl();
        const GSContext &c = s.context;
        const GSSwizzle::Format &tf = GSSwizzle::GetFormat(c.tex0.psm);
        const GSSwizzle::Format &rf = GSSwizzle::GetFormat(rt.psm);
        const auto offsetOf = [&](const uint16_t *table) { const auto it = tableOffset.find(table); return it == tableOffset.end() ? 0u : it->second; };
        int kind = 3, texelBits = 8;
        switch (tf.kind)
        {
        case GSSwizzle::Kind::Bits32: kind = 0; texelBits = 32; break;
        case GSSwizzle::Kind::Bits24: kind = 1; texelBits = 24; break;
        case GSSwizzle::Kind::Bits16: kind = 2; texelBits = 16; break;
        case GSSwizzle::Kind::Bits8: kind = 3; texelBits = 8; break;
        default: kind = 3; texelBits = 4; break;
        }
        if (kind == 3)
        {
            uint32_t palette[256];
            store.BuildPalette(s, palette);
            g.ActiveTexture(kTexture0 + 3);
            g.BindTexture(kTexture2D, paletteTex);
            g.PixelStorei(kUnpackAlignment, 4);
            g.TexSubImage2D(kTexture2D, 0, 0, 0, 256, 1, kRgba, kUnsignedByte, palette);
        }
        g.ActiveTexture(kTexture0 + 1);
        g.BindTexture(kTexture2D, rt.color);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        g.ActiveTexture(kTexture0 + 2);
        g.BindTexture(kTexture2D, tableTex);
        g.ActiveTexture(kTexture0);
        g.Uniform1i(locRtColor, 1);
        g.Uniform1i(locTables, 2);
        g.Uniform1i(locPalette, 3);
        g.Uniform4i(locTexFmt, tf.pageShiftX, tf.pageShiftY, tf.pixelsPerPageShift, tf.unpackedShift);
        g.Uniform4i(locTexFmt2, tf.bitOffset, texelBits, static_cast<GLint>(offsetOf(tf.table)), kind);
        const auto inv = inverseOffset.find(rt.psm);
        g.Uniform4i(locRtFmt, rf.pageShiftX, rf.pageShiftY, rf.pixelsPerPageShift, 1 << rf.unpackedShift);
        g.Uniform4i(locRtFmt2, inv == inverseOffset.end() ? 0 : static_cast<GLint>(inv->second), static_cast<GLint>(rt.fbp), static_cast<GLint>(rt.fbw), 0);
        g.Uniform4i(locTex0, static_cast<GLint>(c.tex0.tbp0), c.tex0.tbw, s.textureWidth, s.textureHeight);
        g.Uniform2f(locRtPx, static_cast<float>(rt.pxW), static_cast<float>(rt.pxH));
    }

    // ---- CLUT from a render target --------------------------------------------------------------------------------
    // A CLUT whose source memory a render target was drawn into is read from that target on the GPU: one pass writes the
    // raw source words (reinterpreting fetch, CPSM view of the target) into a 256x1 target, the 1 KB result goes to the
    // CLUT store. Results are cached per target version, so a target read many times per frame costs one pass.
    GLuint clutProgram = 0, clutFbo = 0, clutTex = 0, clutCoordTex = 0;
    GLint locClTables = -1, locClRtColor = -1, locClCoords = -1, locClTexFmt = -1, locClTexFmt2 = -1, locClRtFmt = -1, locClRtFmt2 = -1,
          locClTex0 = -1, locClRtPx = -1;
    std::unordered_map<uint64_t, std::vector<uint32_t>> clutCache;

    bool ensureClutProgram()
    {
        if (clutProgram)
            return true;
        const Api &g = gl();
        const GLuint v = compile(GSGL::kVertexShader, kPresentVs), f = compile(GSGL::kFragmentShader, {kClutFsHead, kReinterpretSource, kClutFsMain});
        if (!v || !f)
            return false;
        clutProgram = g.CreateProgram();
        g.AttachShader(clutProgram, v);
        g.AttachShader(clutProgram, f);
        g.LinkProgram(clutProgram);
        const auto loc = [&](const char *name) { return g.GetUniformLocation(clutProgram, name); };
        locClTables = loc("uTables"); locClRtColor = loc("uRtColor"); locClCoords = loc("uCoords"); locClTexFmt = loc("uTexFmt");
        locClTexFmt2 = loc("uTexFmt2"); locClRtFmt = loc("uRtFmt"); locClRtFmt2 = loc("uRtFmt2"); locClTex0 = loc("uTex0"); locClRtPx = loc("uRtPx");
        g.GenTextures(1, &clutTex);
        g.BindTexture(kTexture2D, clutTex);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), 256, 1, 0, kRgba, kUnsignedByte, nullptr);
        g.GenTextures(1, &clutCoordTex);
        g.BindTexture(kTexture2D, clutCoordTex);
        g.TexImage2D(kTexture2D, 0, 0x823A /*RG16UI*/, 256, 1, 0, 0x8228 /*RG_INTEGER*/, 0x1403 /*UNSIGNED_SHORT*/, nullptr);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        g.GenFramebuffers(1, &clutFbo);
        g.BindFramebuffer(kFramebuffer, clutFbo);
        g.FramebufferTexture2D(kFramebuffer, kColorAttachment0, kTexture2D, clutTex, 0);
        return true;
    }

    bool clutFromTarget(const GSTex0Reg &tex0, uint32_t width, const uint16_t *xy, uint32_t count, uint32_t *words)
    {
        RenderTarget *rt = findReinterpretSource(tex0.cbp, tex0.cpsm);
        if (!rt || count == 0u || count > 256u || !ensureClutProgram())
            return false;
        uint64_t key = 1469598103934665603ull;
        const auto mix = [&key](uint64_t v) { key = (key ^ v) * 1099511628211ull; };
        mix(rt->fbp); mix(rt->version); mix(tex0.cbp); mix(tex0.cpsm); mix(width); mix(count);
        for (uint32_t i = 0; i < count * 2u; ++i)
            mix(xy[i]);
        if (texSrcDiag)
            ++texSources["clut-from-rt psm=" + std::to_string(rt->psm)];
        if (const auto it = clutCache.find(key); it != clutCache.end())
        {
            std::memcpy(words, it->second.data(), count * sizeof(uint32_t));
            return true;
        }
        const Api &g = gl();
        const GSSwizzle::Format &tf = GSSwizzle::GetFormat(tex0.cpsm);
        const GSSwizzle::Format &rf = GSSwizzle::GetFormat(rt->psm);
        const auto table = tableOffset.find(tf.table);
        const auto inv = inverseOffset.find(rt->psm);
        if (table == tableOffset.end() || inv == inverseOffset.end())
            return false;
        const int texelBits = tf.kind == GSSwizzle::Kind::Bits32 ? 32 : tf.kind == GSSwizzle::Kind::Bits24 ? 24 : 16;
        g.UseProgram(clutProgram);
        g.ActiveTexture(kTexture0 + 1);
        g.BindTexture(kTexture2D, rt->color);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        g.ActiveTexture(kTexture0 + 2);
        g.BindTexture(kTexture2D, tableTex);
        g.ActiveTexture(kTexture0 + 3);
        g.BindTexture(kTexture2D, clutCoordTex);
        g.PixelStorei(kUnpackAlignment, 2);
        g.TexSubImage2D(kTexture2D, 0, 0, 0, static_cast<GLsizei>(count), 1, 0x8228 /*RG_INTEGER*/, 0x1403 /*UNSIGNED_SHORT*/, xy);
        g.ActiveTexture(kTexture0);
        g.Uniform1i(locClRtColor, 1);
        g.Uniform1i(locClTables, 2);
        g.Uniform1i(locClCoords, 3);
        g.Uniform4i(locClTexFmt, tf.pageShiftX, tf.pageShiftY, tf.pixelsPerPageShift, tf.unpackedShift);
        g.Uniform4i(locClTexFmt2, tf.bitOffset, texelBits, static_cast<GLint>(table->second), 0);
        g.Uniform4i(locClRtFmt, rf.pageShiftX, rf.pageShiftY, rf.pixelsPerPageShift, 1 << rf.unpackedShift);
        g.Uniform4i(locClRtFmt2, static_cast<GLint>(inv->second), static_cast<GLint>(rt->fbp), static_cast<GLint>(rt->fbw), 0);
        g.Uniform4i(locClTex0, static_cast<GLint>(tex0.cbp), static_cast<GLint>(width), 256, 256);
        g.Uniform2f(locClRtPx, static_cast<float>(rt->pxW), static_cast<float>(rt->pxH));
        g.BindFramebuffer(kFramebuffer, clutFbo);
        g.Disable(kBlend);
        g.Disable(kDepthTest);
        g.Disable(kScissorTest);
        g.ColorMask(kTrue, kTrue, kTrue, kTrue);
        g.Viewport(0, 0, static_cast<GLsizei>(count), 1);
        g.BindVertexArray(presentVao);
        g.DrawArrays(kTriangles, 0, 3);
        g.PixelStorei(kPackAlignment, 4);
        g.ReadPixels(0, 0, static_cast<GLsizei>(count), 1, kRgba, kUnsignedByte, words);
        g.BindVertexArray(vao);
        g.UseProgram(program);
        g.BindBuffer(kArrayBuffer, vbo);
        if (clutCache.size() > 4096u)
            clutCache.clear();
        clutCache.emplace(key, std::vector<uint32_t>(words, words + count));
        return true;
    }

    // ---- drawing --------------------------------------------------------------------------------------------------
    static bool sameState(const GSDrawState &a, const GSDrawState &b)
    {
        return std::memcmp(&a, &b, sizeof(GSDrawState)) == 0;
    }

    void addVertex(const GSDrawState &s, const GSVertex &v, float u, float tv, float zmax)
    {
        const GSContext &c = s.context;
        if (pending.empty())
            firstRawZ = v.z;
        // The GS samples pixel (x, y) at the integer point (x, y); GL samples host pixel h at its centre h + 0.5. Shifting
        // by half a HOST pixel maps the PS2 sample of pixel x onto the centre of host pixel scale * x, so a primitive
        // covering PS2 pixels [x0, x1) covers host pixels [scale * x0, scale * x1) and its texture coordinates at host
        // pixel scale * x equal the PS2's at x. (Half a PS2 pixel moved every primitive one host pixel down and right at
        // 2x: host row/column 0 of every target stayed unpainted and each copy pass shifted the picture by a host pixel;
        // the filtered passes smeared that stale edge into the picture, the bright bar along the top and left.)
        const float half = 0.5f / scale;
        HwVertex h;
        h.x = v.x - static_cast<float>(c.xyoffset.ofx) / 16.0f + half;
        h.y = v.y - static_cast<float>(c.xyoffset.ofy) / 16.0f + half;
        // the Z buffer keeps only its low bits (Z24: 24, Z16: 16): a vertex Z of 1<<24 is stored as 0
        double zq = std::max(v.z, 0.0);
        if (zmax < 4294967295.0f)
            zq = static_cast<double>(static_cast<uint64_t>(zq) & (zmax < 70000.0f ? 0xFFFFull : 0xFFFFFFull));
        h.z = static_cast<float>(std::min(zq / zmax, 1.0));
        h.r = v.r; h.g = v.g; h.b = v.b; h.a = v.a;
        h.s = v.s; h.t = v.t; h.q = v.q;
        h.u = u; h.v = tv;
        pending.push_back(h);
    }

    static bool family16(uint8_t psm) { return psm == GS_PSM_CT16 || psm == GS_PSM_CT16S; }

    static float zMaxFor(uint8_t zpsm)
    {
        switch (zpsm)
        {
        case 0x30: return 4294967295.0f;
        case 0x32: case 0x3A: return 65535.0f;
        default: return 16777215.0f;
        }
    }

    // ---- channel shuffles (see kShuffleFs) -------------------------------------------------------------------------
    const std::vector<uint16_t> &inverseFor(uint32_t ownerPsm)
    {
        std::vector<uint16_t> &inv = ownerInverse[ownerPsm];
        if (inv.empty())
        {
            const GSSwizzle::Format &f = GSSwizzle::GetFormat(ownerPsm);
            inv.assign(2048u, 0);
            for (uint32_t e = 0; e < 2048u; ++e)
                inv[f.table[e]] = static_cast<uint16_t>(e);
        }
        return inv;
    }

    // pixel (x, y) of a 16 bit view (psm/base/bw) -> pixel and halfword of the 32 bit owner laid out as ownerPsm at fbp/fbw
    bool viewToOwner(uint32_t viewPsm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t ownerPsm, uint32_t fbp, uint32_t fbw,
                     uint32_t &ox, uint32_t &oy, uint32_t &half)
    {
        const uint32_t byte = GSSwizzle::Locate(GSSwizzle::GetFormat(viewPsm), base, bw, x, y).byte;
        const uint32_t word = byte >> 2, first = fbp * 2048u;
        if (word < first)
            return false;
        const uint32_t rel = word - first, page = rel >> 11u, e = inverseFor(ownerPsm)[rel & 2047u];
        half = (byte >> 1) & 1u;
        ox = (page % fbw) * 64u + (e & 63u);
        oy = (page / fbw) * 32u + (e >> 6u);
        return true;
    }

    // an 8x8 unit of the view at (x, y) -> an 8x8 owner block at (ox, oy), one halfword (checked at the far corner)
    bool unitToOwner(uint32_t viewPsm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t ownerPsm, uint32_t fbp, uint32_t fbw,
                     uint32_t &ox, uint32_t &oy, uint32_t &half)
    {
        uint32_t ex, ey, eh;
        return viewToOwner(viewPsm, base, bw, x, y, ownerPsm, fbp, fbw, ox, oy, half) &&
               viewToOwner(viewPsm, base, bw, x + 7u, y + 7u, ownerPsm, fbp, fbw, ex, ey, eh) && eh == half && ex == ox + 7u && ey == oy + 7u;
    }

    static uint32_t fbmsk16(uint32_t m)
    {
        return ((m >> 3) & 0x1Fu) | ((m >> 6) & 0x3E0u) | ((m >> 9) & 0x7C00u) | ((m >> 16) & 0x8000u);
    }

    // a sprite drawn through a 16 bit view of a 32 bit target, textured from a 16 bit view of a 32 bit target or a Z buffer,
    // 8 px aligned, copying texels 1:1: queued as a channel shuffle. False = not that shape (the caller decides).
    bool tryShuffle(const GSDrawState &s, const GSPrimitiveBatch &b)
    {
        const GSContext &c = s.context;
        const uint8_t tpsm = c.tex0.psm;
        const bool zTex = tpsm == 0x32 || tpsm == 0x3A;
        if (s.prim.type != GS_PRIM_SPRITE || !s.prim.tme || !s.prim.fst || s.prim.abe || !(family16(tpsm) || zTex))
            { shuffleWhy = 1; return false; }
        if ((c.test & 1u) != 0u && ((c.test >> 1) & 7u) != 1u) // alpha test other than ALWAYS
            { shuffleWhy = 2; return false; }
        if (((c.test >> 14) & 1u) != 0u) // DATE
            { shuffleWhy = 3; return false; }
        {
            // the texture function must pass the texel through: decal, or modulate by 128
            const GSVertex &v = b.vertices[1];
            const bool identity = c.tex0.tfx == 1 || (c.tex0.tfx == 0 && v.r == 128 && v.g == 128 && v.b == 128 && (!c.tex0.tcc || v.a == 128));
            if (!identity)
                { shuffleWhy = 4; return false; }
        }
        // each byte of the halfword must be fully written or fully kept
        const uint32_t m16 = fbmsk16(c.frame.fbmsk);
        const uint32_t lowByte = m16 & 0xFFu, highByte = m16 & 0xFF00u;
        if ((lowByte != 0u && lowByte != 0xFFu) || (highByte != 0u && highByte != 0xFF00u) || m16 == 0xFFFFu)
            { shuffleWhy = 5; return false; }
        // destination owner: an existing 32 bit target at FBP, or a new one
        RenderTarget *dst = findTarget(c.frame.fbp);
        if (dst && family16(dst->psm) && dst->usedW != 0u)
            { shuffleWhy = 6; return false; }
        // source owner
        if ((c.tex0.tbp0 % 32u) != 0u)
            { shuffleWhy = 7; return false; }
        // a Z16 view reads a Z buffer, or a colour target laid out as Z (the address mapping covers both)
        RenderTarget *src = nullptr;
        bool srcDepth = false;
        if (zTex)
            for (RenderTarget &t : targets)
                if (t.depth && t.zbp == c.tex0.tbp0 / 32u && t.fbp != t.zbp)
                {
                    src = &t;
                    srcDepth = true;
                }
        if (!src)
            if (RenderTarget *t = findTarget(c.tex0.tbp0 / 32u))
                if (!family16(t->psm) && t->usedW != 0u)
                    src = t;
        if (!src)
            { shuffleWhy = 8; return false; }
        // geometry: integer, 8 px aligned rectangle, texels 1:1 at an 8 px aligned offset
        const GSVertex &a = b.vertices[0], &e = b.vertices[1];
        const float ofx = c.xyoffset.ofx / 16.0f, ofy = c.xyoffset.ofy / 16.0f;
        const float fx0 = std::min(a.x, e.x) - ofx, fx1 = std::max(a.x, e.x) - ofx, fy0 = std::min(a.y, e.y) - ofy, fy1 = std::max(a.y, e.y) - ofy;
        const auto whole = [](float v) { return std::fabs(v - std::round(v)) < 1e-3f && v >= 0.0f; };
        if (!whole(fx0) || !whole(fx1) || !whole(fy0) || !whole(fy1))
            { shuffleWhy = 9; return false; }
        const int x0 = static_cast<int>(std::lround(fx0)), x1 = static_cast<int>(std::lround(fx1));
        const int y0 = static_cast<int>(std::lround(fy0)), y1 = static_cast<int>(std::lround(fy1));
        const GSVertex &left = (a.x <= e.x) ? a : e;
        const GSVertex &top = (a.y <= e.y) ? a : e;
        const int du = static_cast<int>(std::floor(left.u / 16.0f)) - x0, dv = static_cast<int>(std::floor(top.v / 16.0f)) - y0;
        const int uSpan = static_cast<int>(std::lround(std::fabs(static_cast<float>(a.u) - static_cast<float>(e.u)) / 16.0f));
        const int vSpan = static_cast<int>(std::lround(std::fabs(static_cast<float>(a.v) - static_cast<float>(e.v)) / 16.0f));
        if (((x0 | x1 | y0 | y1 | du | dv) & 7) != 0 || x1 <= x0 || y1 <= y0 || uSpan != x1 - x0 || vSpan != y1 - y0)
            { shuffleWhy = 10; return false; }
        if (x0 + du < 0 || y0 + dv < 0 || x0 < static_cast<int>(c.scissor.x0) || y0 < static_cast<int>(c.scissor.y0) ||
            x1 - 1 > static_cast<int>(c.scissor.x1) || y1 - 1 > static_cast<int>(c.scissor.y1))
            { shuffleWhy = 11; return false; }
        if (!dst)
        {
            // creating a target may move the others: nothing queued may point at them, src is found again
            flushShuffle();
            const size_t srcIndex = static_cast<size_t>(src - targets.data());
            dst = &target(c.frame.fbp, c.frame.fbw);
            src = &targets[srcIndex];
        }
        // map every 8x8 unit; the whole sprite is rejected if any unit does not land on one owner block
        const uint32_t srcOwnerPsm = srcDepth ? 0x30u : 0x00u, srcFbp = srcDepth ? src->zbp : src->fbp;
        std::vector<ShuffleVertex> quads[4];
        uint32_t maxX = 0, maxY = 0;
        for (int y = y0; y < y1; y += 8)
            for (int x = x0; x < x1; x += 8)
            {
                uint32_t dx, dy, hd, sx, sy, hs;
                if (!unitToOwner(c.frame.psm, c.frame.fbp * 32u, c.frame.fbw, x, y, 0x00u, dst->fbp, dst->fbw, dx, dy, hd) ||
                    !unitToOwner(tpsm, c.tex0.tbp0, c.tex0.tbw, x + du, y + dv, srcOwnerPsm, srcFbp, src->fbw, sx, sy, hs))
                    { shuffleWhy = 12; return false; }
                if (dx + 8u > dst->pxW || dy + 8u > dst->pxH || sx + 8u > src->pxW || sy + 8u > src->pxH)
                    { shuffleWhy = 13; return false; }
                if (src == dst && !srcDepth && (sx != dx || sy != dy))
                    { shuffleWhy = 14; return false; } // would read texels that other quads of the pass write
                const float ox = static_cast<float>(sx) - static_cast<float>(dx), oy = static_cast<float>(sy) - static_cast<float>(dy);
                const float X0 = static_cast<float>(dx), Y0 = static_cast<float>(dy), X1 = X0 + 8.0f, Y1 = Y0 + 8.0f;
                std::vector<ShuffleVertex> &q = quads[hs * 2u + hd];
                q.insert(q.end(), {{X0, Y0, ox, oy}, {X1, Y0, ox, oy}, {X0, Y1, ox, oy}, {X1, Y0, ox, oy}, {X1, Y1, ox, oy}, {X0, Y1, ox, oy}});
                maxX = std::max(maxX, dx + 8u);
                maxY = std::max(maxY, dy + 8u);
            }
        // queue: one GL pass per state run
        if (havePending)
            flushPending();
        if (haveShuffle && (!sameState(shuffleState, s) || shuffleDst != dst || shuffleSrc != src || shuffleSrcZ != srcDepth))
            flushShuffle();
        if (!haveShuffle)
        {
            haveShuffle = true;
            shuffleState = s;
            shuffleDst = dst;
            shuffleSrc = src;
            shuffleSrcZ = srcDepth;
        }
        for (int i = 0; i < 4; ++i)
            shuffleQuads[i].insert(shuffleQuads[i].end(), quads[i].begin(), quads[i].end());
        dst->usedW = std::max(dst->usedW, std::min(maxX, dst->pxW));
        dst->usedH = std::max(dst->usedH, std::min(maxY, dst->pxH));
        ++stats.shuffles;
        return true;
    }

    void flushShuffle()
    {
        if (!haveShuffle)
            return;
        haveShuffle = false;
        if (!shuffleProgram)
        {
            for (auto &q : shuffleQuads)
                q.clear();
            return;
        }
        RenderTarget &dst = *shuffleDst, &src = *shuffleSrc;
        const GSContext &c = shuffleState.context;
        const Api &g = gl();
        ++dst.version;
        dst.lastDrawSeq = ++writeSeq;
        const uint32_t m16 = fbmsk16(c.frame.fbmsk);
        const GLboolean lo = (m16 & 0xFFu) == 0u ? kTrue : kFalse, hi = (m16 & 0xFF00u) == 0u ? kTrue : kFalse;
        g.BindFramebuffer(kFramebuffer, dst.fbo);
        g.Viewport(0, 0, dst.glW, dst.glH);
        g.Disable(kScissorTest);
        g.Disable(kBlend);
        g.Disable(kDepthTest);
        g.DepthMask(kFalse);
        g.UseProgram(shuffleProgram);
        g.ActiveTexture(kTexture0);
        g.BindTexture(kTexture2D, shuffleSrcZ ? src.depth : src.color);
        g.Uniform1i(locShSrc, 0);
        g.Uniform1i(locShSrcZ, shuffleSrcZ ? 1 : 0);
        g.Uniform1f(locShZMax, zMaxFor(c.zbuf.psm));
        g.Uniform1f(locShScale, scale);
        g.Uniform4i(locShTexa, shuffleState.texa.ta0 >> 7, shuffleState.texa.ta1 >> 7, shuffleState.texa.aem ? 1 : 0, 0);
        g.Uniform2f(locShInvSize, 1.0f / dst.pxW, 1.0f / dst.pxH);
        if (&src == &dst)
            g.TextureBarrier();
        g.BindVertexArray(shuffleVao);
        g.BindBuffer(kArrayBuffer, shuffleVbo);
        for (uint32_t i = 0; i < 4; ++i)
        {
            std::vector<ShuffleVertex> &q = shuffleQuads[i];
            if (q.empty())
                continue;
            const uint32_t hs = i >> 1, hd = i & 1u;
            g.Uniform1i(locShHs, static_cast<GLint>(hs));
            g.Uniform1i(locShHd, static_cast<GLint>(hd));
            g.ColorMask(hd == 0u ? lo : kFalse, hd == 0u ? hi : kFalse, hd == 1u ? lo : kFalse, hd == 1u ? hi : kFalse);
            g.BufferData(kArrayBuffer, static_cast<GLsizeiptr>(q.size() * sizeof(ShuffleVertex)), q.data(), kStreamDraw);
            g.DrawArrays(kTriangles, 0, static_cast<GLsizei>(q.size()));
            q.clear();
        }
        g.ColorMask(kTrue, kTrue, kTrue, kTrue);
        g.BindVertexArray(vao);
        g.BindBuffer(kArrayBuffer, vbo);
        ++stats.batches;
    }

    // GOW_GS_HW_DUMP window: skipped batches are listed in order with the drawn ones
    void dumpSkipped(const GSDrawState &s, const GSPrimitiveBatch &b, const char *why)
    {
        if (dumpPresents < 0 || presentCount < dumpPresents || presentCount >= dumpPresents + 3 || dumped >= dumpMax)
            return;
        flushPending();
        ++dumped;
        dumpAfterSkip = true;
        const GSContext &c = s.context;
        const GSVertex &v0 = b.vertices[0], &v1 = b.vertices[1];
        std::fprintf(stderr,
                     "[gs-hw-skip] #%d %s why=%d prim=%d fbp=%u fbw=%u fpsm=%u fbmsk=%x zbp=%x zmsk=%d tme=%d tbp=%x tbw=%u tpsm=%u %ux%u cbp=%x test=%llx alpha=%llx abe=%d v0=(%.1f,%.1f uv=%u,%u col=%u,%u,%u,%u) v1=(%.1f,%.1f uv=%u,%u) scis=%u-%u,%u-%u\n",
                     dumped, why, shuffleWhy, static_cast<int>(s.prim.type), c.frame.fbp, c.frame.fbw, c.frame.psm, c.frame.fbmsk, c.zbuf.zbp, c.zbuf.zmask ? 1 : 0,
                     s.prim.tme ? 1 : 0, c.tex0.tbp0, c.tex0.tbw, c.tex0.psm, s.textureWidth, s.textureHeight, c.tex0.cbp,
                     (unsigned long long)c.test, (unsigned long long)c.alpha, s.prim.abe ? 1 : 0,
                     v0.x, v0.y, v0.u, v0.v, (unsigned)v0.r, (unsigned)v0.g, (unsigned)v0.b, (unsigned)v0.a, v1.x, v1.y, v1.u, v1.v,
                     c.scissor.x0, c.scissor.x1, c.scissor.y0, c.scissor.y1);
    }

    void submit(const GSPrimitiveBatch &b)
    {
        const GSDrawState &s = b.state;
        const GSPrimType type = s.prim.type;
        const bool tri = type == GS_PRIM_TRIANGLE || type == GS_PRIM_TRISTRIP || type == GS_PRIM_TRIFAN;
        const bool sprite = type == GS_PRIM_SPRITE;
        const bool line = type == GS_PRIM_LINE || type == GS_PRIM_LINESTRIP;
        if (!tri && !sprite && !line)
        {
            ++stats.skippedPrim;
            dumpSkipped(s, b, "prim");
            return;
        }
        const uint8_t fpsm = s.context.frame.psm;
        if (family16(fpsm) && tryShuffle(s, b))
            return;
        flushShuffle();
        if (fpsm != GS_PSM_CT32 && fpsm != GS_PSM_CT24 && fpsm != GS_PSM_CT16 && fpsm != GS_PSM_CT16S)
        {
            ++stats.skippedPsm;
            return;
        }
        // a draw through a different-format view (CT16) of memory that a CT32/CT24 target already owns writes bit fields of its
        // pixels; it cannot be rasterised into the RGBA target at the same coordinates
        for (const RenderTarget &t : targets)
            if (t.fbp == s.context.frame.fbp && t.usedW != 0u && family16(t.psm) != family16(fpsm))
            {
                ++stats.skippedPsm;
                dumpSkipped(s, b, "view");
                return;
            }
        if (havePending && !sameState(pendingState, s))
            flushPending();
        if (!havePending)
        {
            pendingState = s;
            havePending = true;
        }
        const float zmax = zMaxFor(s.context.zbuf.psm);
        const float texW = static_cast<float>(std::max<uint16_t>(s.textureWidth, 1)), texH = static_cast<float>(std::max<uint16_t>(s.textureHeight, 1));
        const auto texelUV = [&](const GSVertex &v, float &u, float &t)
        {
            if (s.prim.fst)
            {
                u = static_cast<float>(v.u) / 16.0f;
                t = static_cast<float>(v.v) / 16.0f;
            }
            else
            {
                u = 0.0f;
                t = 0.0f;
            }
        };
        if (line)
        {
            // a GS line covers about one pixel across its length: drawn as a quad one PS2 pixel wide around the segment
            // (at least one pixel long), colour/Z/texture coordinates taken from the nearer end point. The game uses
            // them for the sand streaks and for the per-frame black line that clears row 0 of the frame buffer.
            const GSVertex &a = b.vertices[0], &c = b.vertices[1];
            float dx = c.x - a.x, dy = c.y - a.y;
            const float len = std::sqrt(dx * dx + dy * dy);
            if (len < 1e-4f)
                dx = 1.0f, dy = 0.0f;
            else
                dx /= len, dy /= len;
            const float ext = len < 1.0f ? (1.0f - len) * 0.5f : 0.0f; // short lines still cover one pixel
            const float nx = -dy * 0.5f, ny = dx * 0.5f;
            GSVertex e[2] = {a, c};
            e[0].x -= dx * ext; e[0].y -= dy * ext;
            e[1].x += dx * ext; e[1].y += dy * ext;
            const int order[6][2] = {{0, 1}, {1, 1}, {0, -1}, {1, 1}, {1, -1}, {0, -1}};
            // across the line the quad is centred on the PS2 pixel centre (sample + 0.5), so it covers every host pixel of
            // the pixels it crosses; along the line it covers [start, end) like a sprite edge
            const float centre = 0.5f - 0.5f / scale;
            for (const auto &o : order)
            {
                GSVertex v = e[o[0]];
                v.x += nx * static_cast<float>(o[1]) + centre * std::fabs(dy);
                v.y += ny * static_cast<float>(o[1]) + centre * std::fabs(dx);
                float u, t;
                texelUV(v, u, t);
                addVertex(s, v, u, t, zmax);
            }
        }
        else if (tri)
        {
            for (int i = 0; i < 3; ++i)
            {
                float u, t;
                texelUV(b.vertices[i], u, t);
                addVertex(s, b.vertices[i], u, t, zmax);
            }
        }
        else
        {
            const GSVertex &a = b.vertices[0];
            const GSVertex &c = b.vertices[1];
            float u0, v0, u1, v1;
            if (s.prim.fst)
            {
                u0 = a.u / 16.0f; v0 = a.v / 16.0f; u1 = c.u / 16.0f; v1 = c.v / 16.0f;
            }
            else
            {
                const float q0 = std::fabs(a.q) < 1e-20f ? 1e-20f : a.q, q1 = std::fabs(c.q) < 1e-20f ? 1e-20f : c.q;
                u0 = a.s / q0 * texW; v0 = a.t / q0 * texH; u1 = c.s / q1 * texW; v1 = c.t / q1 * texH;
            }
            GSDrawState sp = s; // sprites carry texel UVs, never STQ
            (void)sp;
            GSVertex corner[4] = {a, a, a, a};
            const float xs[2] = {a.x, c.x}, ys[2] = {a.y, c.y};
            const float us[2] = {u0, u1}, vs[2] = {v0, v1};
            // the texel coordinates of the first and last pixel the GS covers (pixel n is covered when lo <= n < hi);
            // a sprite covering no pixel on the GS keeps its whole range
            const auto sampled = [](float p0, float p1, float t0, float t1, float &lo, float &hi)
            {
                lo = std::min(t0, t1);
                hi = std::max(t0, t1);
                const float first = std::ceil(std::min(p0, p1)), last = std::ceil(std::max(p0, p1)) - 1.0f;
                if (last < first || p1 == p0)
                    return;
                const float ta = t0 + (first - p0) * (t1 - t0) / (p1 - p0), tb = t0 + (last - p0) * (t1 - t0) / (p1 - p0);
                lo = std::min(ta, tb);
                hi = std::max(ta, tb);
            };
            float cu0, cu1, cv0, cv1;
            sampled(a.x - s.context.xyoffset.ofx / 16.0f, c.x - s.context.xyoffset.ofx / 16.0f, u0, u1, cu0, cu1);
            sampled(a.y - s.context.xyoffset.ofy / 16.0f, c.y - s.context.xyoffset.ofy / 16.0f, v0, v1, cv0, cv1);
            // A picture drawn as strips (full-screen passes, logos, fonts) continues across each strip seam: there the clamp
            // would repeat the last sampled texel for the host pixels between the two strips' GS sample points (a step at
            // every seam). The side a sprite shares with the previous sprite of the batch, with the texture continuing
            // across it, is left open on both sprites; outer edges stay clamped.
            SpriteEdges cur{{xs[0], xs[1]}, {ys[0], ys[1]}, {us[0], us[1]}, {vs[0], vs[1]}};
            if (lastSprite.batch == batchSerial && lastSprite.end == pending.size() && lastSprite.end >= 6)
                openSharedSide(lastSprite.edges, cur, &pending[lastSprite.end - 6], cu0, cu1, cv0, cv1);
            const int order[6][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 1}};
            for (const auto &o : order)
            {
                GSVertex v = c; // colour, z, fog come from the second vertex
                v.x = xs[o[0]];
                v.y = ys[o[1]];
                addVertex(s, v, us[o[0]], vs[o[1]], zmax);
                pending.back().s = us[o[0]] / texW;
                pending.back().t = vs[o[1]] / texH;
                pending.back().q = 1.0f;
                pending.back().cu0 = cu0;
                pending.back().cv0 = cv0;
                pending.back().cu1 = cu1;
                pending.back().cv1 = cv1;
            }
            lastSprite = {cur, pending.size(), batchSerial};
            (void)corner;
        }
        ++stats.draws;
    }

    void flushPending()
    {
        ++batchSerial; // the next sprite starts a new batch: no seam with the previous one
        flushShuffle();
        if (!havePending || pending.empty())
        {
            havePending = false;
            pending.clear();
            return;
        }
        havePending = false;
        if (!ensure())
        {
            pending.clear();
            return;
        }
        draw(pendingState, pending);
        pending.clear();
    }

    void blendState(const GSDrawState &s, bool &enabled, GLenum &sf, GLenum &df, float &fixScale, float &constant, GLenum &equation, bool &soft)
    {
        enabled = false;
        soft = false;
        equation = kFuncAdd;
        sf = kOne; df = kZero;
        fixScale = 1.0f / 128.0f;
        constant = 0.0f;
        if (!s.prim.abe)
            return;
        const uint64_t alpha = s.context.alpha;
        const uint32_t a = alpha & 3, b = (alpha >> 2) & 3, c = (alpha >> 4) & 3, d = (alpha >> 6) & 3;
        const uint32_t fix = static_cast<uint32_t>((alpha >> 32) & 0xFF);
        GLenum cs, cd; // factor C and 1-C
        if (c == 0) { cs = kSrc1Alpha; cd = kOneMinusSrc1Alpha; }
        else if (c == 2) { cs = kConstantColor; cd = kOneMinusConstantColor; constant = std::min(fix / 128.0f, 1.0f); }
        else { soft = true; cs = kSrc1Alpha; cd = kOneMinusSrc1Alpha; } // C = Ad
        // COLCLAMP=0: results wrap around instead of saturating, below 0 (B != 0) and above 255 (Cs*C + Cd). The character
        // shadow-volume pass counts in the G channel this way (Cs*FIX + Cd, G cleared to 127): it draws its triangles once
        // adding 255 (= -1) and once adding 1. Clamping saturated the first half at 255, the second could not undo it, and
        // everything the volume covered was darkened (black wedges on walls, rectangles under Kratos).
        if ((s.colclamp & 1u) == 0u && a != b)
            soft = true;
        if (a == b)
        {
            // (A-A)*C + D = D
            if (d == 0) return;            // Cs: plain write
            enabled = true; sf = kZero; df = kOne; return; // Cd: destination unchanged
        }
        enabled = true;
        if (a == 0 && b == 1 && d == 1) { sf = cs; df = cd; }            // Cs*C + Cd*(1-C)
        else if (a == 0 && b == 2 && d == 1) { sf = cs; df = kOne; }     // Cs*C + Cd
        else if (a == 2 && b == 1 && d == 1) { sf = kZero; df = cd; }    // Cd*(1-C)
        else if (a == 0 && b == 2 && d == 2) { sf = cs; df = kZero; }    // Cs*C
        else if (a == 2 && b == 0 && d == 2) { sf = kZero; df = kZero; } // 0
        else if (a == 2 && b == 0 && d == 1) { sf = cs; df = kOne; equation = kFuncReverseSubtract; } // Cd - Cs*C
        else { soft = true; sf = cs; df = cd; }
        if (soft)
            ++stats.unsupportedBlend;
    }

    int dumpPresents = std::getenv("GOW_GS_HW_DUMP") ? std::atoi(std::getenv("GOW_GS_HW_DUMP")) : -1;
    int presentCount = 0, dumped = 0, dumpedAt = 0;
    const int dumpMax = std::getenv("GOW_GS_HW_DUMPMAX") ? std::atoi(std::getenv("GOW_GS_HW_DUMPMAX")) : 4000;
    bool dumpAfterSkip = false;
    const bool dumpAll = std::getenv("GOW_GS_HW_DUMPALL") != nullptr;

    int onlyLo = std::getenv("GOW_GS_HW_ONLY") ? std::atoi(std::getenv("GOW_GS_HW_ONLY")) : -1;
    int onlyHi = std::getenv("GOW_GS_HW_ONLY") && std::strchr(std::getenv("GOW_GS_HW_ONLY"), '-') ? std::atoi(std::strchr(std::getenv("GOW_GS_HW_ONLY"), '-') + 1) : 1 << 30;
    int frameBatch = 0;

    // Z buffers whose memory the game has inverted (Z' = 0xFFFFFF - Z) with a full-screen colour draw into the Z memory
    // (CT24 at FBP == ZBP, Cs - Cd with Cs = 255): the shadow passes invert the Z buffer, draw the shadow mask with ZTST GEQUAL
    // (= LEQUAL against the real depth) and invert it back. The GL depth buffer keeps the real depth; while the flag is set,
    // depth tests use 1 - z and the reversed comparison, which is the same test on the inverted memory.
    std::vector<uint32_t> invertedZ;
    bool zInverted(uint32_t zbp) const { return std::find(invertedZ.begin(), invertedZ.end(), zbp) != invertedZ.end(); }
    static bool isZInversion(const GSDrawState &s, const std::vector<HwVertex> &verts)
    {
        const GSContext &c = s.context;
        const uint64_t al = c.alpha;
        if (c.frame.fbp != c.zbuf.zbp || c.frame.psm != GS_PSM_CT24 || s.prim.tme || !s.prim.abe || c.frame.fbmsk != 0u ||
            (al & 0xFFu) != 0xA4u || ((al >> 32) & 0xFFu) != 0x80u || verts.empty())
            return false;
        float x0 = 1e9f, y0 = 1e9f, x1 = -1e9f, y1 = -1e9f;
        for (const HwVertex &v : verts)
        {
            if (v.r < 254.5f || v.g < 254.5f || v.b < 254.5f)
                return false;
            x0 = std::min(x0, v.x), y0 = std::min(y0, v.y), x1 = std::max(x1, v.x), y1 = std::max(y1, v.y);
        }
        return x0 <= c.scissor.x0 + 1.0f && y0 <= c.scissor.y0 + 1.0f && x1 >= c.scissor.x1 && y1 >= c.scissor.y1;
    }

    void draw(const GSDrawState &s, const std::vector<HwVertex> &verts)
    {
        const Api &g = gl();
        ++frameBatch;
        if (onlyLo >= 0 && (frameBatch < onlyLo || frameBatch > onlyHi) && s.context.frame.fbp == 0 && s.context.frame.fbw == 8 && !(s.prim.tme && s.context.tex0.tbp0 == 0))
            return;
        const GSContext &c = s.context;
        // GOW_GS_HW_SKIPTBP=<hex>: debug, skip draws textured from that block (bisecting post passes)
        static const long skipTbp = std::getenv("GOW_GS_HW_SKIPTBP") ? std::strtol(std::getenv("GOW_GS_HW_SKIPTBP"), nullptr, 16) : -1;
        if (skipTbp >= 0 && s.prim.tme && static_cast<long>(c.tex0.tbp0) == skipTbp)
            return;
        static const double dumpAtSec = std::getenv("GOW_GS_HW_DUMPAT") ? std::atof(std::getenv("GOW_GS_HW_DUMPAT")) : -1.0;
        static const auto t0 = std::chrono::steady_clock::now();
        const double nowSec = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        if (dumpAtSec >= 0.0 && nowSec >= dumpAtSec && dumpedAt == 0 && frameBatch == 1)
            dumpedAt = 1;
        if (dumpedAt == 1 && dumped < dumpMax && dumpPresents < 0)
            dumpPresents = 0, presentCount = 0;
        if (dumpPresents >= 0 && presentCount >= dumpPresents && presentCount < dumpPresents + 3 && dumped < dumpMax && (dumpAll || c.frame.fbp == 208 || c.frame.fbp == 320 || dumped < 40 || dumpAfterSkip))
        {
            ++dumped;
            const HwVertex &v0 = verts[0];
            float bx0 = 1e9f, by0 = 1e9f, bx1 = -1e9f, by1 = -1e9f, cmax = 0.0f, amax = 0.0f, zlo = 2.0f, zhi = -1.0f;
            for (const HwVertex &v : verts)
            {
                bx0 = std::min(bx0, v.x), by0 = std::min(by0, v.y), bx1 = std::max(bx1, v.x), by1 = std::max(by1, v.y);
                cmax = std::max({cmax, v.r, v.g, v.b}), amax = std::max(amax, v.a), zlo = std::min(zlo, v.z), zhi = std::max(zhi, v.z);
            }
            const float zscale = zMaxFor(c.zbuf.psm) < 4294967295.0f ? zMaxFor(c.zbuf.psm) : 16777215.0f;
            std::fprintf(stderr, "[gs-hw-dump-bb] #%d %.0f-%.0f,%.0f-%.0f ta0=%x ta1=%x aem=%d fge=%d tfx=%u tcc=%u iip=%d cmax=%.0f amax=%.0f prim=%u z=%x-%x\n",
                         dumped, bx0, bx1, by0, by1, s.texa.ta0, s.texa.ta1, s.texa.aem ? 1 : 0, s.prim.fge ? 1 : 0,
                         c.tex0.tfx, c.tex0.tcc, s.prim.iip ? 1 : 0, cmax, amax, static_cast<unsigned>(s.prim.type),
                         static_cast<unsigned>(zlo * zscale + 0.5f), static_cast<unsigned>(zhi * zscale + 0.5f));
            std::fprintf(stderr,
                         "[gs-hw-dump] #%d fb=%d verts=%zu fbp=%u fbw=%u fpsm=%u zbp=%x zpsm=%x zmsk=%d tme=%d tbp=%x tbw=%u tpsm=%u %ux%u cbp=%x test=%llx alpha=%llx abe=%d fbmsk=%x rawz=%.0f v0=(%.1f,%.1f z=%.3f col=%.0f,%.0f,%.0f,%.0f uv=%.1f,%.1f) scis=%u-%u,%u-%u\n",
                         dumped, frameBatch, verts.size(), c.frame.fbp, c.frame.fbw, c.frame.psm, c.zbuf.zbp, c.zbuf.psm, c.zbuf.zmask ? 1 : 0, s.prim.tme ? 1 : 0,
                         c.tex0.tbp0, c.tex0.tbw, c.tex0.psm, s.textureWidth, s.textureHeight, c.tex0.cbp, (unsigned long long)c.test,
                         (unsigned long long)c.alpha, s.prim.abe ? 1 : 0, c.frame.fbmsk, firstRawZ, v0.x, v0.y, v0.z, v0.r, v0.g, v0.b, v0.a, v0.u, v0.v,
                         c.scissor.x0, c.scissor.x1, c.scissor.y0, c.scissor.y1);
        }
        RenderTarget &rt = target(c.frame.fbp, c.frame.fbw);
        attachDepth(rt, c.zbuf.zbp);
        rt.psm = c.frame.psm;
        ++rt.version;
        rt.lastDrawSeq = ++writeSeq;
        {
            // real extent of what was drawn (vertices clipped to the scissor), not the scissor itself
            float maxX = 0.0f, maxY = 0.0f;
            for (const HwVertex &v : verts)
            {
                maxX = std::max(maxX, v.x);
                maxY = std::max(maxY, v.y);
            }
            const uint32_t bx = static_cast<uint32_t>(std::min<float>(std::max(maxX, 0.0f), static_cast<float>(c.scissor.x1 + 1u)));
            const uint32_t by = static_cast<uint32_t>(std::min<float>(std::max(maxY, 0.0f), static_cast<float>(c.scissor.y1 + 1u)));
            rt.usedW = std::max<uint32_t>(rt.usedW, std::min<uint32_t>(bx, rt.pxW));
            rt.usedH = std::max<uint32_t>(rt.usedH, std::min<uint32_t>(by, rt.pxH));
        }
        g.BindFramebuffer(kFramebuffer, rt.fbo);
        g.Viewport(0, 0, rt.glW, rt.glH);
        g.Enable(kScissorTest);
        const int sx0 = c.scissor.x0, sy0 = c.scissor.y0;
        const int sw = std::max(0, static_cast<int>(c.scissor.x1) - sx0 + 1), sh = std::max(0, static_cast<int>(c.scissor.y1) - sy0 + 1);
        g.Scissor(static_cast<GLint>(std::floor(sx0 * scale)), static_cast<GLint>(std::floor(sy0 * scale)),
                  static_cast<GLsizei>(std::ceil(sw * scale)), static_cast<GLsizei>(std::ceil(sh * scale)));
        g.Disable(kCullFace);

        // depth
        // ZTE = 0 means no depth test on the GS (the movie player draws its picture sprite with TEST = 0): ALWAYS
        const uint32_t ztst = ((c.test >> 16) & 1u) ? static_cast<uint32_t>((c.test >> 17) & 3u) : 1u;
        static const bool noDepth = std::getenv("GOW_GS_HW_NODEPTH") != nullptr;
        // Z buffer in this target's own colour memory: tested and written in the shader against the colour words
        const bool zAlias = c.zbuf.zbp == c.frame.fbp && ((c.test >> 16) & 1u) != 0u &&
                            (c.frame.psm == GS_PSM_CT32 || c.frame.psm == GS_PSM_CT24);
        if (noDepth || zAlias) g.Disable(kDepthTest); else g.Enable(kDepthTest);
        const bool zInv = !zAlias && ((c.test >> 16) & 1u) != 0u && zInverted(c.zbuf.zbp);
        if (zInv)
            g.DepthFunc(ztst == 0 ? kNever : ztst == 1 ? kAlways : ztst == 2 ? kLEqual : kLess);
        else
            g.DepthFunc(ztst == 0 ? kNever : ztst == 1 ? kAlways : ztst == 2 ? kGEqual : kGreater);
        std::vector<HwVertex> flippedZ;
        if (zInv)
        {
            flippedZ = verts;
            for (HwVertex &v : flippedZ)
                v.z = 1.0f - v.z;
        }
        const std::vector<HwVertex> &dverts = zInv ? flippedZ : verts;
        if (isZInversion(s, verts))
        {
            if (zInverted(c.zbuf.zbp))
                invertedZ.erase(std::find(invertedZ.begin(), invertedZ.end(), c.zbuf.zbp));
            else
                invertedZ.push_back(c.zbuf.zbp);
        }
        const bool zwrite = !c.zbuf.zmask && !zAlias;
        if (zwrite && ((c.test >> 16) & 1u) != 0u)
            rt.lastDepthSeq = rt.lastDrawSeq;
        const bool zAliasWrite = zAlias && !c.zbuf.zmask;

        // colour mask
        const uint32_t fbmsk = c.frame.fbmsk;
        const GLboolean mr = (fbmsk & 0xFF) == 0xFF ? kFalse : kTrue, mg = (fbmsk & 0xFF00) == 0xFF00 ? kFalse : kTrue,
                        mb = (fbmsk & 0xFF0000) == 0xFF0000 ? kFalse : kTrue, ma = (fbmsk & 0xFF000000u) == 0xFF000000u ? kFalse : kTrue;

        bool blend = false, softBlend = false;
        GLenum sf, df, equation;
        float fixScale, constant;
        blendState(s, blend, sf, df, fixScale, constant, equation, softBlend);
        // COLCLAMP=0 with Cs*FIX + Cd and one flat untextured colour (the shadow-volume counting passes: G += 255, then
        // G += 1, modulo 256): every fragment adds the same constant modulo 256, and additions commute, so the fixed-function
        // blend does it in one draw: adding v < 128 is an add, adding v >= 128 is subtracting 256 - v. Exact while the
        // count stays inside 0..255 (it starts at 127). Drawing such passes per triangle through the shader blend stalled
        // the renderer for seconds in fights with many shadow casters.
        float wrapAmount[3] = {0.0f, 0.0f, 0.0f};
        bool wrapCount = false;
        if (softBlend && !zAliasWrite && (s.colclamp & 1u) == 0u && !s.prim.tme && !verts.empty())
        {
            const uint64_t al = c.alpha;
            const uint32_t a = al & 3u, b = (al >> 2) & 3u, cc = (al >> 4) & 3u, d = (al >> 6) & 3u, fix = static_cast<uint32_t>((al >> 32) & 0xFFu);
            if (a == 0u && b == 2u && cc == 2u && d == 1u)
            {
                const float col[3] = {verts[0].r, verts[0].g, verts[0].b};
                const GLboolean written[3] = {mr, mg, mb};
                bool flat = true;
                for (const HwVertex &v : verts)
                    flat = flat && v.r == col[0] && v.g == col[1] && v.b == col[2];
                int direction = 0; // +1 add, -1 subtract, 2 mixed
                for (int ch = 0; ch < 3 && flat; ++ch)
                {
                    if (!written[ch])
                        continue;
                    const uint32_t v = std::min<uint32_t>(255u, (static_cast<uint32_t>(col[ch]) * fix) >> 7);
                    const int dir = v >= 128u ? -1 : 1;
                    direction = direction == 0 || direction == dir ? dir : 2;
                    // the blend multiplies the constant by the source colour (Cs / 255): factor = amount / source
                    wrapAmount[ch] = col[ch] > 0.0f ? static_cast<float>(dir < 0 ? 256u - v : v) / col[ch] : 0.0f;
                }
                if (flat && (direction == 1 || direction == -1))
                {
                    wrapCount = true;
                    softBlend = false;
                    blend = true;
                    sf = kConstantColor;
                    df = kOne;
                    equation = direction < 0 ? kFuncReverseSubtract : kFuncAdd;
                }
            }
        }
        if (softBlend || zAliasWrite) // the shader produces the final colour (a Z write replaces the colour word)
            blend = false;
        if (blend)
        {
            g.Enable(kBlend);
            g.BlendEquationSeparate(equation, kFuncAdd);
            g.BlendFuncSeparate(sf, df, kOne, kZero);
            if (wrapCount)
                g.BlendColor(wrapAmount[0], wrapAmount[1], wrapAmount[2], 0.0f);
            else
                g.BlendColor(constant, constant, constant, constant);
        }
        else
            g.Disable(kBlend);

        g.UseProgram(program);
        {
            const bool date = ((c.test >> 14) & 1u) != 0u && c.frame.psm != GS_PSM_CT24;
            g.Uniform1i(locDate, date ? 1 : 0);
            g.Uniform1i(locDatm, ((c.test >> 15) & 1u) != 0u ? 1 : 0);
            const uint64_t al = c.alpha;
            g.Uniform1i(locSwBlend, softBlend && !zAliasWrite ? 1 : 0);
            g.Uniform1i(locColClamp, (s.colclamp & 1u) != 0u ? 1 : 0);
            g.Uniform4i(locAbcd, static_cast<GLint>(al & 3u), static_cast<GLint>((al >> 2) & 3u), static_cast<GLint>((al >> 4) & 3u), static_cast<GLint>((al >> 6) & 3u));
            g.Uniform1f(locFix, static_cast<float>((al >> 32) & 0xFFu));
            g.Uniform1i(locZAlias, zAlias ? 1 + static_cast<GLint>(ztst) : 0);
            g.Uniform1i(locZAliasWrite, zAliasWrite ? 1 : 0);
            g.Uniform1f(locZAliasMax, zMaxFor(c.zbuf.psm));
            if (date || softBlend || zAlias)
            {
                g.ActiveTexture(kTexture0 + 4);
                g.BindTexture(kTexture2D, rt.color);
                g.Uniform1i(locDest, 4);
                g.ActiveTexture(kTexture0);
                g.TextureBarrier();
            }
        }
        g.Uniform2f(locInvSize, 1.0f / rt.pxW, 1.0f / rt.pxH);
        g.Uniform1i(locTme, s.prim.tme ? 1 : 0);
        g.Uniform1i(locFst, s.prim.fst ? 1 : 0);
        g.Uniform1i(locIip, s.prim.iip ? 1 : 0);
        g.Uniform1i(locTfx, c.tex0.tfx);
        g.Uniform1i(locTcc, c.tex0.tcc);
        g.Uniform1f(locBlendScale, 1.0f / 128.0f);
        if (s.prim.tme)
        {
            // a texture that lives in a render target of the same format is sampled straight from it
            RenderTarget *src = nullptr;
            const auto family = [](uint8_t psm) { return (psm == GS_PSM_CT16 || psm == GS_PSM_CT16S) ? 16 : (psm == GS_PSM_CT32 || psm == GS_PSM_CT24) ? 32 : 0; };
            if (family(c.tex0.psm) != 0 && (c.tex0.tbp0 % 32u) == 0u)
                if (RenderTarget *candidate = findTarget(c.tex0.tbp0 / 32u))
                    if (family(candidate->psm) == family(c.tex0.psm) && !uploadedSinceDraw(*candidate, c.tex0.tbp0) &&
                        !overwrittenByDepth(*candidate))
                        src = candidate;
            if (src == &rt)
                g.TextureBarrier();
            Texture dummy;
            RenderTarget *zsrc = nullptr;
            const bool zFormat = c.tex0.psm == 0x30 || c.tex0.psm == 0x31 || c.tex0.psm == 0x32 || c.tex0.psm == 0x3A;
            if (zFormat && (c.tex0.tbp0 % 32u) == 0u)
                for (RenderTarget &t : targets)
                    if (t.depth && t.zbp == c.tex0.tbp0 / 32u && t.fbp != t.zbp)
                        zsrc = &t;
            if (zsrc)
                src = nullptr;
            RenderTarget *rsrc = nullptr;
            if (!src && !zsrc)
                rsrc = findReinterpretSource(c.tex0.tbp0, c.tex0.psm);
            if (rsrc == &rt)
                g.TextureBarrier();
            const bool indexed = !(src || rsrc || zsrc) && isIndexed(c.tex0.psm) && vram != nullptr;
            Texture &tex = (src || rsrc || zsrc) ? dummy : indexed ? indexTextureFor(s) : textureFor(s);
            g.Uniform1i(locIndexed, indexed ? 1 : 0);
            g.Uniform1i(locLinear, s.linearFilter ? 1 : 0);
            if (indexed)
            {
                g.ActiveTexture(kTexture0 + 5);
                g.BindTexture(kTexture2D, paletteFor(s));
                g.Uniform1i(locIdxPalette, 5);
                g.Uniform4i(locWrap, (c.clamp & 3u) == 0u ? 0 : 1, ((c.clamp >> 2) & 3u) == 0u ? 0 : 1, 0, 0);
            }
            g.ActiveTexture(kTexture0);
            g.BindTexture(kTexture2D, zsrc ? zsrc->depth : src ? src->color : rsrc ? rsrc->color : tex.id);
            g.Uniform1i(locZTex, !zsrc ? 0 : c.tex0.psm == 0x32 || c.tex0.psm == 0x3A ? 16 : c.tex0.psm == 0x31 ? 24 : 32);
            g.Uniform1f(locZMax, zsrc ? zMaxFor(static_cast<uint8_t>(c.tex0.psm)) : 1.0f);
            g.Uniform1i(locRtTex24, !(src || rsrc) ? 0 : c.tex0.psm == GS_PSM_CT24 ? 1 : family16(c.tex0.psm) ? 2 : 0);
            g.Uniform1i(locReinterp, rsrc ? 1 : 0);
            if (rsrc)
                setupReinterpret(s, *rsrc);
            g.Uniform1f(locTa0, static_cast<float>(s.texa.ta0));
            g.Uniform1f(locTa1, static_cast<float>(s.texa.ta1));
            g.Uniform1i(locAem, s.texa.aem ? 1 : 0);
            const GLint filter = s.linearFilter ? kLinear : kNearest;
            g.TexParameteri(kTexture2D, kTextureMinFilter, filter);
            g.TexParameteri(kTexture2D, kTextureMagFilter, filter);
            const uint64_t clamp = c.clamp;
            const GLint wu = (clamp & 3u) == 0u ? kRepeat : kClampToEdge, wv = ((clamp >> 2) & 3u) == 0u ? kRepeat : kClampToEdge;
            g.TexParameteri(kTexture2D, kTextureWrapS, wu);
            g.TexParameteri(kTexture2D, kTextureWrapT, wv);
            if (indexed)
            {
                g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
                g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
            }
            g.Uniform1i(locTex, 0);
            g.Uniform2f(locTexDim, static_cast<float>(std::max<uint16_t>(s.textureWidth, 1)), static_cast<float>(std::max<uint16_t>(s.textureHeight, 1)));
            if (zsrc)
            {
                g.Uniform2f(locTexSize, static_cast<float>(zsrc->pxW), static_cast<float>(zsrc->pxH));
                g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
                g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
            }
            else if (src)
                g.Uniform2f(locTexSize, static_cast<float>(src->pxW), static_cast<float>(src->pxH));
            else
                g.Uniform2f(locTexSize, static_cast<float>(tex.width), static_cast<float>(tex.height));
        }
        g.BindVertexArray(vao);
        g.BindBuffer(kArrayBuffer, vbo);
        g.BufferData(kArrayBuffer, static_cast<GLsizeiptr>(dverts.size() * sizeof(HwVertex)), dverts.data(), kStreamDraw);

        const bool ate = (c.test & 1u) != 0u;
        const uint32_t atst = static_cast<uint32_t>((c.test >> 1) & 7u), aref = static_cast<uint32_t>((c.test >> 4) & 0xFFu);
        const uint32_t afail = static_cast<uint32_t>((c.test >> 12) & 3u);
        g.Uniform1i(locAte, ate ? 1 : 0);
        g.Uniform1i(locAtst, static_cast<GLint>(atst));
        g.Uniform1i(locAref, static_cast<GLint>(aref));
        static const bool forceNoTest = std::getenv("GOW_GS_HW_NOATEST") != nullptr;
        g.Uniform1i(locPass, (ate && !forceNoTest) ? 1 : 0);
        g.Uniform1i(locFailTint, 0);
        static const int traceAt = std::getenv("GOW_GS_HW_DEPTHTRACE") ? std::atoi(std::getenv("GOW_GS_HW_DEPTHTRACE")) : -1;
        const bool tracing = traceAt >= 0 && presentCount >= traceAt && presentCount < traceAt + 1 && rt.depth && rt.fbp == 0;
        const auto depthStats = [&](const char *when)
        {
            std::vector<float> dz(static_cast<size_t>(rt.glW) * rt.glH);
            g.BindFramebuffer(kFramebuffer, rt.fbo);
            g.ReadPixels(0, 0, rt.glW, rt.glH, kDepthComponent, kFloat, dz.data());
            double mx = 0.0;
            size_t nz = 0;
            for (float v : dz) { mx = std::max<double>(mx, v); nz += v > 0.0f; }
            std::fprintf(stderr, "[gs-hw-depth] batch %d %s: max=%.3f nonzero=%zu/%zu (this batch z=%.3f zmsk=%d ztst=%u verts=%zu tbp=%x)\n", frameBatch, when, mx, nz, dz.size(),
                         verts[0].z, c.zbuf.zmask ? 1 : 0, ztst, verts.size(), c.tex0.tbp0);
        };
        if (tracing) depthStats("before");
        // GOW_GS_HW_VOLTRACE=<n>: the first n COLCLAMP=0 draws (shadow volumes): vertex depth sent (after the Z-inversion
        // flip), the depth buffer under the volume's bounding box, the depth test and the blend path
        static const int volTrace = std::getenv("GOW_GS_HW_VOLTRACE") ? std::atoi(std::getenv("GOW_GS_HW_VOLTRACE")) : 0;
        static int volTraced = 0;
        int volBox[4] = {0, -1, 0, -1};
        if ((s.colclamp & 1u) == 0u && zInv && volTraced < volTrace && rt.depth)
        {
            ++volTraced;
            float x0 = 1e9f, x1 = -1e9f, y0 = 1e9f, y1 = -1e9f, z0 = 2.0f, z1 = -1.0f;
            for (const HwVertex &v : dverts)
                x0 = std::min(x0, v.x), x1 = std::max(x1, v.x), y0 = std::min(y0, v.y), y1 = std::max(y1, v.y), z0 = std::min(z0, v.z), z1 = std::max(z1, v.z);
            const int bx0 = std::max(0, static_cast<int>(x0 * scale)), bx1 = std::min(static_cast<int>(rt.glW) - 1, static_cast<int>(x1 * scale));
            const int by0 = std::max(0, static_cast<int>(y0 * scale)), by1 = std::min(static_cast<int>(rt.glH) - 1, static_cast<int>(y1 * scale));
            volBox[0] = bx0, volBox[1] = bx1, volBox[2] = by0, volBox[3] = by1;
            size_t trisDown = 0, trisUp = 0;
            for (size_t i = 2; i < dverts.size(); i += 3)
                (dverts[i].g >= 128.0f ? trisDown : trisUp) += 1;
            std::fprintf(stderr, "[gs-hw-vol]   triangles G>=128 %zu, G<128 %zu\n", trisDown, trisUp);
            float d0 = 2.0f, d1 = -1.0f;
            if (bx1 >= bx0 && by1 >= by0)
            {
                std::vector<float> dz(static_cast<size_t>(bx1 - bx0 + 1) * (by1 - by0 + 1));
                g.BindFramebuffer(kFramebuffer, rt.fbo);
                g.ReadPixels(bx0, by0, bx1 - bx0 + 1, by1 - by0 + 1, kDepthComponent, kFloat, dz.data());
                for (float v : dz)
                    d0 = std::min(d0, v), d1 = std::max(d1, v);
            }
            std::fprintf(stderr, "[gs-hw-vol] batch %d verts=%zu zInv=%d ztst=%u vertex z %.6f-%.6f (x %.0f-%.0f y %.0f-%.0f) depth under it %.6f-%.6f softBlend=%d wrapCount=%d zbp=%x attached=%x\n",
                         frameBatch, dverts.size(), zInv ? 1 : 0, ztst, z0, z1, x0, x1, y0, y1, d0, d1, softBlend ? 1 : 0, wrapCount ? 1 : 0,
                         c.zbuf.zbp, rt.zbp);
        }
        g.ColorMask(mr, mg, mb, ma);
        g.DepthMask(zwrite ? kTrue : kFalse);
        if (softBlend && !zAliasWrite && (s.colclamp & 1u) == 0u)
        {
            // wrapping blend (COLCLAMP=0, only the shadow-volume passes): the shader reads the destination, so draw one
            // triangle at a time with a barrier in between; overlapping triangles of one draw then see each other's results
            // like on the GS (the volumes count overlaps this way)
            for (size_t i = 0; i + 3 <= verts.size(); i += 3)
            {
                if (i != 0)
                    g.TextureBarrier();
                g.DrawArrays(kTriangles, static_cast<GLint>(i), 3);
            }
        }
        else
            g.DrawArrays(kTriangles, 0, static_cast<GLsizei>(verts.size()));
        if (volBox[1] >= volBox[0] && volBox[3] >= volBox[2])
        {
            const int w = volBox[1] - volBox[0] + 1, h = volBox[3] - volBox[2] + 1;
            std::vector<uint8_t> px(static_cast<size_t>(w) * h * 4u);
            g.PixelStorei(kPackAlignment, 1);
            g.ReadPixels(volBox[0], volBox[2], w, h, kRgba, kUnsignedByte, px.data());
            size_t below = 0, above = 0, equal = 0;
            for (size_t i = 1; i < px.size(); i += 4)
                (px[i] < 127 ? below : px[i] > 127 ? above : equal) += 1;
            std::fprintf(stderr, "[gs-hw-vol]   after: G<127 %zu, G>127 %zu, G=127 %zu\n", below, above, equal);
        }
        static const bool noFailPass = std::getenv("GOW_GS_HW_NOFAIL") != nullptr;
        if (ate && afail != 0u && !noFailPass)
        {
            // failing fragments: 1 FB_ONLY (colour+alpha, no Z), 2 ZB_ONLY (Z only), 3 RGB_ONLY (colour, no alpha, no Z)
            g.Uniform1i(locPass, 2);
            static const bool failTint = std::getenv("GOW_GS_HW_FAILTINT") != nullptr;
            g.Uniform1i(locFailTint, (failTint && afail == 3u && s.prim.tme && c.frame.fbp == 0u) ? 1 : 0);
            if (afail == 1u) { g.DepthMask(kFalse); }
            else if (afail == 2u) { g.ColorMask(kFalse, kFalse, kFalse, kFalse); }
            else { g.DepthMask(kFalse); g.ColorMask(mr, mg, mb, kFalse); }
            g.DrawArrays(kTriangles, 0, static_cast<GLsizei>(verts.size()));
        }
        ++stats.batches;
        g.Disable(kScissorTest);
        static const int rtDumpAt = std::getenv("GOW_GS_HW_RTDUMP") ? std::atoi(std::getenv("GOW_GS_HW_RTDUMP")) : -1;
        static const double rtDumpSec = std::getenv("GOW_GS_HW_RTDUMPAT") ? std::atof(std::getenv("GOW_GS_HW_RTDUMPAT")) : -1.0;
        static const auto rtT0 = std::chrono::steady_clock::now();
        static int rtDumpPresent = -1;
        // GOW_GS_HW_RTDUMPRANGE=a-b: batches of that frame to dump (default 26-46)
        static const char *rtRange = std::getenv("GOW_GS_HW_RTDUMPRANGE");
        static const int rtDumpLo = rtRange ? std::atoi(rtRange) : 26;
        static const int rtDumpHi = rtRange && std::strchr(rtRange, '-') ? std::atoi(std::strchr(rtRange, '-') + 1) : 46;
        // GOW_GS_HW_RTDUMPFBP=<n>: dump that render target instead of fbp 0 / 208
        static const long rtDumpFbp = std::getenv("GOW_GS_HW_RTDUMPFBP") ? std::strtol(std::getenv("GOW_GS_HW_RTDUMPFBP"), nullptr, 0) : -1;
        static std::vector<bool> rtDumped(1024, false); // with the GOW_GS_HW_DUMP window: the first frame that reaches a batch wins
        if (rtDumpSec >= 0.0 && rtDumpPresent < 0 && frameBatch == 1 && std::chrono::duration<double>(std::chrono::steady_clock::now() - rtT0).count() >= rtDumpSec)
            rtDumpPresent = presentCount;
        if (((rtDumpAt >= 0 && presentCount == rtDumpAt) || (rtDumpPresent >= 0 && presentCount >= rtDumpPresent && presentCount <= rtDumpPresent + 1) || (rtRange && dumpPresents >= 0 && presentCount >= dumpPresents && presentCount < dumpPresents + 3 && !rtDumped[frameBatch & 1023])) && (rtDumpFbp >= 0 ? static_cast<long>(rt.fbp) == rtDumpFbp : (rt.fbp == 0 || rt.fbp == 208)) && frameBatch >= rtDumpLo && frameBatch <= rtDumpHi)
        {
            std::vector<uint8_t> px(static_cast<size_t>(rt.glW) * rt.glH * 4u);
            g.BindFramebuffer(kFramebuffer, rt.fbo);
            g.PixelStorei(kPackAlignment, 1);
            g.ReadPixels(0, 0, rt.glW, rt.glH, kRgba, kUnsignedByte, px.data());
            char name[64];
            std::snprintf(name, sizeof(name), "gs_hw_rt%u_p%d_b%03d.ppm", rt.fbp, presentCount, frameBatch);
            rtDumped[frameBatch & 1023] = true;
            if (FILE *f = std::fopen(name, "wb"))
            {
                std::fprintf(f, "P6 %u %u 255 ", rt.glW, rt.glH);
                for (size_t i = 0; i + 3 < px.size(); i += 4)
                    std::fwrite(&px[i], 1, 3, f);
                std::fclose(f);
            }
            std::snprintf(name, sizeof(name), "gs_hw_rt%u_p%d_b%03d_a.pgm", rt.fbp, presentCount, frameBatch);
            if (FILE *f = std::fopen(name, "wb")) // alpha (the shadow mask reaches the darken pass through it)
            {
                std::fprintf(f, "P5 %u %u 255 ", rt.glW, rt.glH);
                for (size_t i = 3; i < px.size(); i += 4)
                    std::fwrite(&px[i], 1, 1, f);
                std::fclose(f);
            }
        }

        static int errorsShown = 0;
        if (errorsShown < 8)
            if (const GLenum err = g.GetError())
                std::fprintf(stderr, "[gs-hw] GL error 0x%x after batch %llu\n", err, (unsigned long long)stats.batches), ++errorsShown;
    }

    // GOW-Port: GOW_GS_TEXSRC=1 classifies every texture decode (and target readback) by where its data came from, every
    // 5 s: one upload of the same format and buffer, parts / other formats of uploads, local copies, render targets.
    // Measures what a texture store without the GS memory image must handle (docs/native-port.md, step 5).
    struct UploadRect { uint32_t dbp, dbw, dpsm, x, y, w, h, dir; };
    std::vector<UploadRect> uploadRects;
    std::map<std::string, uint64_t> texSources;
    const bool texSrcDiag = std::getenv("GOW_GS_TEXSRC") != nullptr;
    void noteTransfer(const GSTransferCommand &c)
    {
        if (!texSrcDiag)
            return;
        if (uploadRects.size() > 8192u)
            uploadRects.erase(uploadRects.begin(), uploadRects.begin() + 4096);
        uploadRects.push_back({c.bitbltbuf.dbp, c.bitbltbuf.dbw, c.bitbltbuf.dpsm, c.trxpos.dsax, c.trxpos.dsay,
                               c.trxreg.rrw, c.trxreg.rrh, c.direction});
    }
    void classifyTexture(const GSDrawState &s)
    {
        if (!texSrcDiag)
            return;
        const GSTex0Reg &t = s.context.tex0;
        const uint32_t lo = t.tbp0, hi = lo + spanBlocks(t.psm, t.tbw, std::max<uint32_t>(1u, s.textureHeight));
        const char *what = "none";
        uint32_t otherPsm = 0;
        for (auto it = uploadRects.rbegin(); it != uploadRects.rend(); ++it)
        {
            const UploadRect &u = *it;
            const uint32_t ulo = u.dbp, uhi = ulo + spanBlocks(u.dpsm, u.dbw, u.y + u.h);
            if (!(ulo < hi && lo < uhi))
                continue;
            if (u.dir == 2u)
                what = "local-copy";
            else if (u.dpsm != t.psm)
                what = "upload-other-psm", otherPsm = u.dpsm;
            else if (u.dbp == t.tbp0 && u.dbw == t.tbw && u.x == 0u && u.y == 0u && u.w >= s.textureWidth && u.h >= s.textureHeight)
                what = "upload-exact";
            else
                what = "upload-same-psm-part";
            break;
        }
        char key[96];
        std::snprintf(key, sizeof(key), "%s psm=%02x%s", what, t.psm, otherPsm ? (std::string(" from ") + std::to_string(otherPsm)).c_str() : "");
        ++texSources[key];
    }

    void reportStats()
    {
        if (texSrcDiag)
        {
            static auto last = std::chrono::steady_clock::now();
            const auto now = std::chrono::steady_clock::now();
            if (now - last >= std::chrono::seconds(5))
            {
                last = now;
                for (const auto &kv : texSources)
                    std::fprintf(stderr, "[gs-texsrc] %s x%llu\n", kv.first.c_str(), static_cast<unsigned long long>(kv.second));
                texSources.clear();
            }
        }
        if (!statsEnabled)
            return;
        const auto now = std::chrono::steady_clock::now();
        if (now - stats.last < std::chrono::seconds(5))
            return;
        stats.last = now;
        std::fprintf(stderr, "[gs-hw] shuffles=%llu draws=%llu batches=%llu texDecodes=%llu texHits=%llu skippedPsm=%llu skippedPrim=%llu unsupportedBlend=%llu textures=%zu\n",
                     (unsigned long long)stats.shuffles, (unsigned long long)stats.draws, (unsigned long long)stats.batches, (unsigned long long)stats.texDecodes,
                     (unsigned long long)stats.texHits, (unsigned long long)stats.skippedPsm, (unsigned long long)stats.skippedPrim,
                     (unsigned long long)stats.unsupportedBlend, textures.size());
        stats.shuffles = stats.draws = stats.batches = stats.texDecodes = stats.texHits = stats.skippedPsm = stats.skippedPrim = stats.unsupportedBlend = 0;
    }

    RenderTarget *findTarget(uint32_t fbp)
    {
        for (RenderTarget &t : targets)
            if (t.fbp == fbp)
                return &t;
        return nullptr;
    }
};

GSHwBackend::GSHwBackend() : m_impl(std::make_unique<Impl>()) {}
GSHwBackend::~GSHwBackend() = default;

void GSHwBackend::Initialize(uint8_t *vram, uint32_t vramSize)
{
    m_impl->vram = vram;
    m_impl->vramSize = vramSize;
    m_impl->store.Initialize(vram, vramSize);
    // GOW-Port: create the GL context now (on the GS worker, while the host context is released) so that it can share
    // objects with the host window and UsesSharedPresentation() is known right after Initialize.
    m_impl->ensure();
}

bool GSHwBackend::UsesSharedPresentation() const
{
    return m_impl->context.Shared() && GSSharedPresent::Active();
}

void GSHwBackend::Reset()
{
    Impl &d = *m_impl;
    d.flushPending();
    d.store.Reset();
    d.invertedZ.clear();
    for (auto &kv : d.textures)
        kv.second.valid = false;
}

void GSHwBackend::Submit(const GSPrimitiveBatch &batch)
{
    if (batch.vertexCount == 0u)
        return;
    Impl &d = *m_impl;
    if (!d.ensure())
        return;
    d.submit(batch);
}

void GSHwBackend::LoadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut)
{
    Impl &d = *m_impl;
    d.flushPending();
    if (d.initialized)
        d.store.LoadClut(tex0, texclut, [&d](const GSTex0Reg &t, uint32_t width, const uint16_t *xy, uint32_t count, uint32_t *words)
                         { return d.clutFromTarget(t, width, xy, count, words); });
    else
        d.store.LoadClut(tex0, texclut);
    d.clutHash = d.store.ClutHash();
}

void GSHwBackend::BeginTransfer(const GSTransferCommand &command)
{
    Impl &d = *m_impl;
    d.flushPending();
    d.store.BeginTransfer(command);
    d.noteTransfer(command);
    if (command.direction == 0u || command.direction == 2u)
    {
        const uint32_t rows = static_cast<uint32_t>(command.trxpos.dsay) + command.trxreg.rrh;
        const uint32_t lo = command.bitbltbuf.dbp, hi = lo + spanBlocks(command.bitbltbuf.dpsm, command.bitbltbuf.dbw, rows);
        d.invalidateBlocks(lo, hi);
        // GOW_GS_HW_XFERWATCH=<hex block>: debug, log the transfers whose block range holds that block
        static const long xferWatch = std::getenv("GOW_GS_HW_XFERWATCH") ? std::strtol(std::getenv("GOW_GS_HW_XFERWATCH"), nullptr, 16) : -1;
        // GOW_GS_HW_XFERRANGE=<lo hex>-<hi hex>: also log every transfer whose destination block lies in [lo, hi)
        static const char *xferRange = std::getenv("GOW_GS_HW_XFERRANGE");
        static const long rangeLo = xferRange ? std::strtol(xferRange, nullptr, 16) : -1;
        static const long rangeHi = xferRange && std::strchr(xferRange, '-') ? std::strtol(std::strchr(xferRange, '-') + 1, nullptr, 16) : -1;
        if (rangeLo >= 0 && static_cast<long>(lo) >= rangeLo && static_cast<long>(lo) < rangeHi && command.bitbltbuf.dbp != 0x2800u)
            std::fprintf(stderr, "[gs-hw-xfer-range] dir=%u dbp=%x dbw=%u dpsm=%u rr=%ux%u\n", command.direction, command.bitbltbuf.dbp,
                         command.bitbltbuf.dbw, command.bitbltbuf.dpsm, command.trxreg.rrw, command.trxreg.rrh);
        if (xferWatch >= 0 && lo <= static_cast<uint32_t>(xferWatch) && static_cast<uint32_t>(xferWatch) < hi)
            d.xferWatchHit = true, std::fprintf(stderr, "[gs-hw-xfer] dir=%u dbp=%x dbw=%u dpsm=%u dsa=%u,%u rr=%ux%u\n", command.direction,
                         command.bitbltbuf.dbp, command.bitbltbuf.dbw, command.bitbltbuf.dpsm, command.trxpos.dsax,
                         command.trxpos.dsay, command.trxreg.rrw, command.trxreg.rrh);
        if (d.uploadLog.size() > 4096u)
            d.uploadLog.erase(d.uploadLog.begin(), d.uploadLog.begin() + 2048);
        d.uploadLog.push_back({lo, hi, ++d.writeSeq});
    }
}

void GSHwBackend::UploadImage(const uint8_t *data, uint32_t sizeBytes)
{
    Impl &d = *m_impl;
    if (d.xferWatchHit && sizeBytes >= 32u)
    {
        std::fprintf(stderr, "[gs-hw-xfer] data %u bytes:", sizeBytes);
        for (uint32_t i = 0; i < 32u; ++i)
            std::fprintf(stderr, " %02x", data[i]);
        std::fprintf(stderr, "\n");
    }
    const bool watched = d.xferWatchHit;
    d.xferWatchHit = false;
    d.store.Upload(data, sizeBytes);
    if (watched && d.vram)
    {
        static const long block = std::strtol(std::getenv("GOW_GS_HW_XFERWATCH"), nullptr, 16);
        uint32_t h = 2166136261u;
        for (uint32_t i = 0; i < 8192u; ++i)
            h = (h ^ d.vram[static_cast<size_t>(block) * 256u + i]) * 16777619u;
        std::fprintf(stderr, "[gs-hw-xfer] page hash after upload %08x\n", h);
    }
}

void GSHwBackend::Flush()
{
    m_impl->flushPending();
}

void GSHwBackend::TextureFlush()
{
    m_impl->flushPending(); // textures are re-read from the store when an upload overlaps them, not on TEXFLUSH
}

void GSHwBackend::Sync(GSSyncReason)
{
    m_impl->flushPending();
}

bool GSHwBackend::ClearFramebuffer(const GSContext &context, uint32_t rgba)
{
    Impl &d = *m_impl;
    if (!d.ensure() || context.frame.fbw == 0u)
        return false;
    d.flushPending();
    const Api &g = d.gl();
    RenderTarget &rt = d.target(context.frame.fbp, context.frame.fbw);
    g.BindFramebuffer(kFramebuffer, rt.fbo);
    g.Enable(kScissorTest);
    const int sx0 = context.scissor.x0, sy0 = context.scissor.y0;
    g.Scissor(static_cast<GLint>(std::floor(sx0 * d.scale)), static_cast<GLint>(std::floor(sy0 * d.scale)),
              static_cast<GLsizei>(std::ceil((context.scissor.x1 - sx0 + 1) * d.scale)),
              static_cast<GLsizei>(std::ceil((context.scissor.y1 - sy0 + 1) * d.scale)));
    g.ColorMask(kTrue, kTrue, kTrue, kTrue);
    g.ClearColor((rgba & 0xFF) / 255.0f, ((rgba >> 8) & 0xFF) / 255.0f, ((rgba >> 16) & 0xFF) / 255.0f, ((rgba >> 24) & 0xFF) / 255.0f);
    g.Clear(kColorBufferBit);
    g.Disable(kScissorTest);
    return true;
}

// GOW-Port: the game never reads GS memory back (LOCAL->HOST), so there is nothing to hand out.
uint32_t GSHwBackend::ConsumeLocalToHostBytes(uint8_t *, uint32_t)
{
    return 0u;
}

uint32_t GSHwBackend::ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
{
    return m_impl->store.Read(psm, base, bw, x, y);
}

void GSHwBackend::WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value)
{
    m_impl->store.Write(psm, base, bw, x, y, value);
}

void GSHwBackend::SnapshotVram(std::vector<uint8_t> &out) const
{
    m_impl->store.Snapshot(out);
}

GSTransferSnapshot GSHwBackend::GetTransferSnapshot() const
{
    return m_impl->store.TransferState();
}

PresentationFrame GSHwBackend::Present(const GSPresentationRequest &request)
{
    Impl &d = *m_impl;
    PresentationFrame frame;
    if (!d.ensure())
        return frame;
    d.flushPending();
    ++d.presentCount;
    d.dumpAfterSkip = false;
    d.frameBatch = 0;
    d.reportStats();
    const bool enable1 = (request.pmode & 1ull) != 0ull, enable2 = (request.pmode & 2ull) != 0ull;
    const auto decode = [&](bool enabled, uint64_t dispfb, uint64_t display, uint32_t &fbp, uint32_t &fbw, uint32_t &dbx, uint32_t &dby,
                            uint32_t &w, uint32_t &h)
    {
        fbp = static_cast<uint32_t>(dispfb & 0x1FFu);
        fbw = std::max<uint32_t>(1u, static_cast<uint32_t>((dispfb >> 9) & 0x3Fu));
        dbx = static_cast<uint32_t>((dispfb >> 32) & 0x7FFu);
        dby = static_cast<uint32_t>((dispfb >> 43) & 0x7FFu);
        const uint32_t hdiv = static_cast<uint32_t>((display >> 23) & 0xFu) + 1u;
        const uint32_t vdiv = static_cast<uint32_t>((display >> 27) & 0x3u) + 1u;
        w = (static_cast<uint32_t>((display >> 32) & 0xFFFu) + 1u) / hdiv;
        h = (static_cast<uint32_t>((display >> 44) & 0x7FFu) + 1u) / vdiv;
        return enabled && display != 0u && w != 0u && h != 0u;
    };
    // GOW_GS_HW_DISPLOG=1: the display registers each time they change (picture size and placement per mode)
    static const bool dispLog = std::getenv("GOW_GS_HW_DISPLOG") != nullptr;
    static uint64_t lastDisp[6] = {};
    if (dispLog && (request.pmode != lastDisp[0] || request.dispfb1 != lastDisp[1] || request.display1 != lastDisp[2] ||
                    request.dispfb2 != lastDisp[3] || request.display2 != lastDisp[4] || request.smode2 != lastDisp[5]))
    {
        lastDisp[0] = request.pmode; lastDisp[1] = request.dispfb1; lastDisp[2] = request.display1;
        lastDisp[3] = request.dispfb2; lastDisp[4] = request.display2; lastDisp[5] = request.smode2;
        std::fprintf(stderr, "[gs-hw-disp] present=%d pmode=%llx smode2=%llx dispfb1=%llx display1=%llx dispfb2=%llx display2=%llx\n",
                     d.presentCount, (unsigned long long)request.pmode, (unsigned long long)request.smode2, (unsigned long long)request.dispfb1,
                     (unsigned long long)request.display1, (unsigned long long)request.dispfb2, (unsigned long long)request.display2);
    }
    if (d.statsEnabled)
    {
        static int shown = 0;
        if (shown++ < 6)
            std::fprintf(stderr, "[gs-hw] present pmode=%llx smode2=%llx dispfb1=%llx display1=%llx dispfb2=%llx display2=%llx\n",
                         (unsigned long long)request.pmode, (unsigned long long)request.smode2, (unsigned long long)request.dispfb1,
                         (unsigned long long)request.display1, (unsigned long long)request.dispfb2, (unsigned long long)request.display2);
    }
    // the two read circuits; circuit 1 is shown over circuit 2 (or BGCOLOR), blended by ALP (MMOD) or its own alpha x2
    uint32_t fbp1, fbw1, dbx1, dby1, w1, h1, fbp2, fbw2, dbx2, dby2, w2, h2;
    const bool ok1 = enable1 && decode(true, request.dispfb1, request.display1, fbp1, fbw1, dbx1, dby1, w1, h1);
    const bool ok2 = enable2 && decode(true, request.dispfb2, request.display2, fbp2, fbw2, dbx2, dby2, w2, h2);
    const bool shared = !request.forceReadback && d.context.Shared() && GSSharedPresent::Active();
    if (!ok1 && !ok2)
    {
        if (shared)
            GSGL::PublishSharedTexture(d.gl(), 0u, 0u, 0u, d.presentCount, 0u, 0u, request.vsyncTick);
        return frame;
    }
    // The host window shows the TV area of the game's own picture: 448 lines from DY 50 (gameplay, menus). The movies set
    // a 480-line display at the same DY; their streams are 640x480 with the picture in the top 448 lines and 32 black
    // lines below, which a TV shows in its bottom border. Taller displays are cut to 448 lines, so a movie fills the
    // window like the game does instead of leaving a black band under it.
    constexpr uint32_t kTvLines = 448u;
    const uint32_t fbp = ok1 ? fbp1 : fbp2, w = ok1 ? w1 : w2, h = std::min(ok1 ? h1 : h2, kTvLines);
    frame.displayFbp = fbp;
    frame.sourceFbp = fbp;
    // GOW_GS_HW_DISPDUMP=<n>: the n-th present after the displayed buffer's size changed (e.g. a movie starts) writes that
    // whole render target to gs_hw_disp_<fbp>_<w>x<h>.ppm (what the read circuit can reach, beyond the displayed area)
    static const int dispDumpAt = std::getenv("GOW_GS_HW_DISPDUMP") ? std::atoi(std::getenv("GOW_GS_HW_DISPDUMP")) : -1;
    static uint32_t dispDumpSize = 0;
    static int dispDumpCount = 0;
    if (dispDumpAt >= 0)
    {
        if ((w << 16 | h) != dispDumpSize)
            dispDumpSize = w << 16 | h, dispDumpCount = 0;
        if (dispDumpCount++ == dispDumpAt)
            if (RenderTarget *rt = d.findTarget(fbp))
            {
                std::vector<uint8_t> px(static_cast<size_t>(rt->glW) * rt->glH * 4u);
                d.gl().BindFramebuffer(kFramebuffer, rt->fbo);
                d.gl().PixelStorei(kPackAlignment, 1);
                d.gl().ReadPixels(0, 0, rt->glW, rt->glH, kRgba, kUnsignedByte, px.data());
                char name[64];
                std::snprintf(name, sizeof(name), "gs_hw_disp_%u_%ux%u.ppm", fbp, w, h);
                if (FILE *f = std::fopen(name, "wb"))
                {
                    std::fprintf(f, "P6 %u %u 255 ", rt->glW, rt->glH);
                    for (size_t i = 0; i + 3 < px.size(); i += 4)
                        std::fwrite(&px[i], 1, 3, f);
                    std::fclose(f);
                }
            }
    }
    const uint32_t outW = static_cast<uint32_t>(std::ceil(w * d.scale)), outH = static_cast<uint32_t>(std::ceil(h * d.scale));
    frame.width = outW;
    frame.height = outH;
    if (!shared)
        frame.pixels.assign(static_cast<size_t>(outW) * outH * 4u, 0u);
    const Api &g = d.gl();
    g.PixelStorei(kPackAlignment, 1);
    static const int depthDumpAt = std::getenv("GOW_GS_HW_DEPTHDUMP") ? std::atoi(std::getenv("GOW_GS_HW_DEPTHDUMP")) : -1;
    if (depthDumpAt >= 0 && d.presentCount == depthDumpAt)
    {
        RenderTarget *main = d.findTarget(0);
        if (main && main->depth)
        {
            std::vector<float> depth(static_cast<size_t>(main->glW) * main->glH);
            g.BindFramebuffer(kFramebuffer, main->fbo);
            g.ReadPixels(0, 0, main->glW, main->glH, kDepthComponent, kFloat, depth.data());
            if (FILE *f = std::fopen("gs_hw_depth.pgm", "wb"))
            {
                std::fprintf(f, "P5 %u %u 255 ", main->glW, main->glH);
                for (float v : depth)
                {
                    const uint8_t b = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, v * 255.0f)));
                    std::fwrite(&b, 1, 1, f);
                }
                std::fclose(f);
            }
        }
    }

    // GOW_GS_HW_EDGELOG=1: every 300 presents, the displayed buffer's first host rows (at x = width/2) and columns
    // (at y = height/2) before composition (edge artefacts: what the frame buffer holds there)
    static const bool edgeLog = std::getenv("GOW_GS_HW_EDGELOG") != nullptr;
    if (edgeLog && d.presentCount % 300 == 0)
        if (RenderTarget *rt = d.findTarget(fbp))
        {
            uint8_t px[4 * 8];
            g.BindFramebuffer(kFramebuffer, rt->fbo);
            std::fprintf(stderr, "[gs-hw-edge] fbp=%x gl=%ux%u rows:", fbp, rt->glW, rt->glH);
            for (uint32_t y = 0; y < 8; ++y)
            {
                g.ReadPixels(static_cast<GLint>(rt->glW / 2u), static_cast<GLint>(y), 1, 1, kRgba, kUnsignedByte, px);
                std::fprintf(stderr, " %02x%02x%02x", px[0], px[1], px[2]);
            }
            std::fprintf(stderr, " cols:");
            for (uint32_t x = 0; x < 8; ++x)
            {
                g.ReadPixels(static_cast<GLint>(x), static_cast<GLint>(rt->glH / 4u), 1, 1, kRgba, kUnsignedByte, px);
                std::fprintf(stderr, " %02x%02x%02x", px[0], px[1], px[2]);
            }
            std::fprintf(stderr, " usedW=%u pxW=%u\n", rt->usedW, rt->pxW);
        }

    // compose the read circuits on the GPU, then read the result back once
    if (!d.presentProgram)
        return frame;
    if (!d.presentFbo || d.presentW != outW || d.presentH != outH)
    {
        if (d.presentTex)
            g.DeleteTextures(1, &d.presentTex);
        if (!d.presentFbo)
            g.GenFramebuffers(1, &d.presentFbo);
        g.GenTextures(1, &d.presentTex);
        g.BindTexture(kTexture2D, d.presentTex);
        g.TexImage2D(kTexture2D, 0, static_cast<GLint>(kRgba8), outW, outH, 0, kRgba, kUnsignedByte, nullptr);
        // complete without mipmaps (glCopyImageSubData refuses incomplete textures)
        g.TexParameteri(kTexture2D, kTextureMinFilter, kLinear);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kLinear);
        g.BindFramebuffer(kFramebuffer, d.presentFbo);
        g.FramebufferTexture2D(kFramebuffer, kColorAttachment0, kTexture2D, d.presentTex, 0);
        d.presentW = outW;
        d.presentH = outH;
    }
    g.BindFramebuffer(kFramebuffer, d.presentFbo);
    g.Viewport(0, 0, outW, outH);
    g.Disable(kScissorTest);
    g.Disable(kDepthTest);
    g.ColorMask(kTrue, kTrue, kTrue, kTrue);
    g.ClearColor(0.f, 0.f, 0.f, 1.f);
    g.Clear(kColorBufferBit);
    g.UseProgram(d.presentProgram);
    g.BindVertexArray(d.presentVao);
    g.ActiveTexture(kTexture0);
    g.Uniform1i(d.locPresentSrc, 0);
    // Row 0 of the displayed buffer is the game's black line (the 416 -> 448 stretch starts at y 0.5 and a line
    // primitive clears row 0), which a TV's overscan hides on the console: the first two PS2 rows and columns repeat
    // the next one so no dark line shows along the top and left edge.
    g.Uniform1i(d.locPresentEdge, static_cast<GLint>(std::lround(2.0f * d.scale)));
    const bool mmod = ((request.pmode >> 5) & 1u) != 0u, slbg = ((request.pmode >> 7) & 1u) != 0u;
    const uint32_t alp = static_cast<uint32_t>((request.pmode >> 8) & 0xFFu);
    const auto drawCircuit = [&](uint32_t cfbp, uint64_t dispfb, uint32_t cdbx, uint32_t cdby, bool alphaFactor)
    {
        RenderTarget *rt = d.findTarget(cfbp);
        if (!rt)
            return;
        g.BindTexture(kTexture2D, rt->color);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kNearest);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kNearest);
        g.Uniform4i(d.locPresentOffset, static_cast<GLint>(cdbx * d.scale), static_cast<GLint>(cdby * d.scale),
                    ((dispfb >> 15) & 0x1Fu) == GS_PSM_CT24 ? 1 : 0, alphaFactor ? 1 : 0);
        g.DrawArrays(kTriangles, 0, 3);
        g.TexParameteri(kTexture2D, kTextureMinFilter, kLinear);
        g.TexParameteri(kTexture2D, kTextureMagFilter, kLinear);
    };
    g.Disable(kBlend);
    if (ok1 && ok2)
    {
        if (slbg)
        {
            g.ClearColor(static_cast<float>(request.bgcolor & 0xFFu) / 255.f, static_cast<float>((request.bgcolor >> 8) & 0xFFu) / 255.f,
                         static_cast<float>((request.bgcolor >> 16) & 0xFFu) / 255.f, 1.f);
            g.Clear(kColorBufferBit);
        }
        else
            drawCircuit(fbp2, request.dispfb2, dbx2, dby2, false);
        g.Enable(kBlend);
        g.BlendEquationSeparate(kFuncAdd, kFuncAdd);
        if (mmod)
        {
            const float f = static_cast<float>(alp) / 255.f;
            g.BlendColor(f, f, f, f);
            g.BlendFuncSeparate(kConstantColor, kOneMinusConstantColor, kZero, kOne);
        }
        else
            g.BlendFuncSeparate(0x0302 /*SRC_ALPHA*/, 0x0303 /*ONE_MINUS_SRC_ALPHA*/, kZero, kOne);
        drawCircuit(fbp1, request.dispfb1, dbx1, dby1, true);
        g.Disable(kBlend);
    }
    else
        drawCircuit(fbp, ok1 ? request.dispfb1 : request.dispfb2, ok1 ? dbx1 : dbx2, ok1 ? dby1 : dby2, false);
    g.BindVertexArray(d.vao);
    // the displayed image is opaque: force alpha to 1 on the GPU (the host draws it with blending)
    g.ColorMask(kFalse, kFalse, kFalse, kTrue);
    g.ClearColor(0.f, 0.f, 0.f, 1.f);
    g.Clear(kColorBufferBit);
    g.ColorMask(kTrue, kTrue, kTrue, kTrue);
    if (shared)
    {
        // GOW-Port: zero-copy presentation: GPU copy into a texture shared with the host window, no pixels returned.
        GSGL::PublishSharedTexture(g, d.presentTex, outW, outH, d.presentCount, fbp, fbp, request.vsyncTick);
        return PresentationFrame{};
    }
    g.ReadPixels(0, 0, outW, outH, kRgba, kUnsignedByte, frame.pixels.data());
    // the frontend packs presentation rows with a fixed 640 pixel stride
    if (frame.width < 640u)
    {
        std::vector<uint8_t> rows(static_cast<size_t>(640u) * frame.height * 4u, 0u);
        for (uint32_t y = 0; y < frame.height; ++y)
            std::memcpy(rows.data() + static_cast<size_t>(y) * 640u * 4u, frame.pixels.data() + static_cast<size_t>(y) * frame.width * 4u,
                        static_cast<size_t>(frame.width) * 4u);
        frame.pixels = std::move(rows);
    }
    return frame;
}
