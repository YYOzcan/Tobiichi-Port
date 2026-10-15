// GOW-Port: contexto host, selección de frames y dibujo raylib usados por el port.
#include "runtime/gs/gs_host_present.h"
#include "rlgl.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/ps2_perf.h"
#include "ps2_log.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

float gowAspectoPresentacion();                                // GOW-Port: gow_integracion.cpp
void gowCuadroDibujar(float x, float y, float w, float h); // GOW-Port: gow_integracion.cpp
namespace
{
    constexpr uint32_t kWidth = 640u;
    constexpr uint32_t kHeight = 512u;
    constexpr uint32_t kDisplayHeight = 448u;
}


namespace
{
    // GOW-Port: output scaler. The GS renders at its native resolution (512x448); this pass maps that image onto the window
    // at the window's resolution with a 5-tap Catmull-Rom bicubic (GOW_SCALER=sharp, default) instead of the plain
    // bilinear stretch (GOW_SCALER=bilinear), then applies a light contrast-adaptive sharpen. It does not add detail
    // (that needs a scaled GS render target); it removes the blur of the stretch.
    const char *kScalerFragment = R"GLSL(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec2 srcSize;
uniform float sharpen;
uniform float plain;
uniform float fxaa;
out vec4 finalColor;

vec4 tex(vec2 uv) { return texture(texture0, uv); }

// GOW-Port: FXAA (TOBIICHI_FXAA=1, lanzador) sobre los texeles del juego, antes del escalado de la ventana.
vec3 fxaaColor(vec2 uv)
{
    vec2 inv = 1.0 / srcSize;
    vec3 rgbNW = tex(uv + vec2(-1.0, -1.0) * inv).rgb, rgbNE = tex(uv + vec2(1.0, -1.0) * inv).rgb;
    vec3 rgbSW = tex(uv + vec2(-1.0, 1.0) * inv).rgb, rgbSE = tex(uv + vec2(1.0, 1.0) * inv).rgb;
    vec3 rgbM = tex(uv).rgb;
    const vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma), lumaNE = dot(rgbNE, luma), lumaSW = dot(rgbSW, luma), lumaSE = dot(rgbSE, luma);
    float lumaM = dot(rgbM, luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
    vec2 dir = vec2(-((lumaNW + lumaNE) - (lumaSW + lumaSE)), (lumaNW + lumaSW) - (lumaNE + lumaSE));
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 / 8.0), 1.0 / 128.0);
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = clamp(dir * rcpDirMin, vec2(-8.0), vec2(8.0)) * inv;
    vec3 rgbA = 0.5 * (tex(uv + dir * (1.0 / 3.0 - 0.5)).rgb + tex(uv + dir * (2.0 / 3.0 - 0.5)).rgb);
    vec3 rgbB = rgbA * 0.5 + 0.25 * (tex(uv - dir * 0.5).rgb + tex(uv + dir * 0.5).rgb);
    float lumaB = dot(rgbB, luma);
    return (lumaB < lumaMin || lumaB > lumaMax) ? rgbA : rgbB;
}

void main()
{
    if (fxaa > 0.5)
    {
        finalColor = vec4(fxaaColor(fragTexCoord), 1.0);
        return;
    }
    if (plain > 0.5)
    {
        // frame at least as large as its window rectangle: one bilinear tap, no bicubic / sharpen
        finalColor = vec4(texture(texture0, fragTexCoord).rgb, 1.0);
        return;
    }
    vec2 pos = fragTexCoord * srcSize;
    vec2 center = floor(pos - 0.5) + 0.5;
    vec2 f = pos - center;
    vec2 f2 = f * f, f3 = f2 * f;
    vec2 w0 = -0.5 * f3 + f2 - 0.5 * f;
    vec2 w1 = 1.5 * f3 - 2.5 * f2 + 1.0;
    vec2 w2 = -1.5 * f3 + 2.0 * f2 + 0.5 * f;
    vec2 w3 = 0.5 * f3 - 0.5 * f2;
    vec2 w12 = w1 + w2;
    vec2 offset12 = w2 / w12;
    vec2 tc0 = (center - 1.0) / srcSize;
    vec2 tc3 = (center + 2.0) / srcSize;
    vec2 tc12 = (center + offset12) / srcSize;
    vec4 c = tex(vec2(tc12.x, tc0.y)) * (w12.x * w0.y)
           + tex(vec2(tc0.x, tc12.y)) * (w0.x * w12.y)
           + tex(vec2(tc12.x, tc12.y)) * (w12.x * w12.y)
           + tex(vec2(tc3.x, tc12.y)) * (w3.x * w12.y)
           + tex(vec2(tc12.x, tc3.y)) * (w12.x * w3.y);
    float norm = (w12.x * w0.y) + (w0.x * w12.y) + (w12.x * w12.y) + (w3.x * w12.y) + (w12.x * w3.y);
    c /= norm;
    if (sharpen <= 0.0) // GOW-Port: nitidez 0 = solo el bicúbico
    {
        finalColor = vec4(clamp(c.rgb, 0.0, 1.0), 1.0);
        return;
    }
    // contrast-adaptive sharpen from the four direct neighbours of the nearest source texel
    vec2 px = 1.0 / srcSize;
    vec3 n = tex(fragTexCoord + vec2(0.0, -px.y)).rgb, s = tex(fragTexCoord + vec2(0.0, px.y)).rgb;
    vec3 e = tex(fragTexCoord + vec2(px.x, 0.0)).rgb, w = tex(fragTexCoord + vec2(-px.x, 0.0)).rgb;
    vec3 lo = min(min(n, s), min(e, w)), hi = max(max(n, s), max(e, w));
    vec3 amp = clamp(min(lo, 1.0 - hi) / max(hi, vec3(0.0001)), 0.0, 1.0);
    float peak = -1.0 / mix(8.0, 5.0, sharpen);
    vec3 wgt = sqrt(amp) * peak;
    vec3 sharp = (c.rgb + (n + s + e + w) * wgt) / (1.0 + 4.0 * wgt);
    finalColor = vec4(clamp(sharp, 0.0, 1.0), 1.0);
}
)GLSL";

    Shader g_scaler{};
    int g_scalerSrcSize = -1, g_scalerSharpen = -1, g_scalerPlain = -1;
    int g_scalerFxaa = -1; // GOW-Port: TOBIICHI_FXAA
    bool g_scalerTried = false;

    bool scalerEnabled()
    {
        // GOW-Port: con TOBIICHI_FXAA=1 el sombreador hace falta también con el estirado bilineal.
        static const bool on = [] {
            const char *v = std::getenv("GOW_SCALER"), *fxaa = std::getenv("TOBIICHI_FXAA");
            return !(v && std::strcmp(v, "bilinear") == 0) || (fxaa && fxaa[0] == '1');
        }();
        return on;
    }

    Shader *scalerShader()
    {
        if (!g_scalerTried)
        {
            g_scalerTried = true;
            if (scalerEnabled())
            {
                g_scaler = LoadShaderFromMemory(nullptr, kScalerFragment);
                if (g_scaler.id != 0u && g_scaler.id != rlGetShaderIdDefault())
                {
                    g_scalerSrcSize = GetShaderLocation(g_scaler, "srcSize");
                    g_scalerSharpen = GetShaderLocation(g_scaler, "sharpen");
                    g_scalerPlain = GetShaderLocation(g_scaler, "plain");
                    g_scalerFxaa = GetShaderLocation(g_scaler, "fxaa");
                }
                else
                {
                    std::fprintf(stderr, "[gs-present] scaler shader failed, using bilinear\n");
                    g_scaler = {};
                }
            }
        }
        return g_scaler.id != 0u ? &g_scaler : nullptr;
    }
}

void GSHostPresentation::captureHostContext()
{
    if (started)
        return;
    started = true;
    const char *setting = std::getenv("PS2X_GS_DIRECT_PRESENT");
    // GOW-Port: shared GL textures (no readback/upload) by default; PS2X_GS_DIRECT_PRESENT=0 forces RAM frames.
    captureRequested = !(setting && *setting == '0');
    if (captureRequested)
        GSSharedPresent::CaptureHostContext();
}

void GSHostPresentation::restoreHostContext()
{
    if (captureRequested)
        GSSharedPresent::RestoreHostContext();
}

void GSHostPresentation::createFallback()
{
    if (fallback.id != 0u)
        return;
    Image blank = GenImageColor(kWidth, kHeight, BLANK);
    fallback = LoadTextureFromImage(blank);
    UnloadImage(blank);
    SetTextureFilter(fallback, TEXTURE_FILTER_POINT); // Coincide con la ruta RAM original.
    upload.resize(static_cast<size_t>(kWidth) * kHeight * 4u, 0u);
}

void GSHostPresentation::blankFallback()
{
    if (!uploadedBlank)
    {
        for (size_t offset = 0u; offset < upload.size(); offset += 4u)
        {
            upload[offset] = MAGENTA.r;
            upload[offset + 1u] = MAGENTA.g;
            upload[offset + 2u] = MAGENTA.b;
            upload[offset + 3u] = MAGENTA.a;
        }
        UpdateTexture(fallback, upload.data());
        uploadedBlank = true;
    }
    current.texture = fallback;
    current.width = kWidth;
    current.height = kDisplayHeight;
    current.borrowed = false;
    current.blank = true;
    uploaded = true;
}

GSHostPresentation::View GSHostPresentation::prepare(GS &gs, uint64_t vsyncTick)
{
    createFallback();
    const bool shared = gs.usesSharedPresentation() && GSSharedPresent::Active();
    if (!modeKnown || shared != sharedMode)
    {
        std::fprintf(stderr, "[gs-present] host mode: %s\n", shared ? "shared texture" : "RAM frames");
        std::fflush(stderr);
        modeKnown = true;
        sharedMode = shared;
        hasLatched = uploaded = uploadedBlank = false;
        lastSharedSequence = 0u;
        current = {};
    }
    const bool needsLatch = !hasLatched || vsyncTick != lastTick;
    if (needsLatch)
    {
        gs.latchHostPresentationFrame();
        lastTick = vsyncTick;
        hasLatched = true;
    }
    current.shared = shared;
    if (shared)
    {
        // GOW-Port: la llamada anterior ya terminó EndDrawing, incluido el batch.
        // Acquire puede conservar el slot previo; nunca descargar píxeles aquí.
        GSSharedPresent::Frame frame;
        if (GSSharedPresent::Acquire(frame))
        {
            current.frame = frame;
            if (frame.sequence != lastSharedSequence)
            {
                gs.recordAcquiredSharedFrame(frame);
                lastSharedSequence = frame.sequence;
            }
            if (!frame.blank && frame.texture != 0u && frame.width != 0u && frame.height != 0u)
            {
                current.texture = Texture2D{frame.texture, static_cast<int>(frame.width), static_cast<int>(frame.height),
                                            1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
                current.width = frame.width;
                current.height = frame.height;
                current.borrowed = true;
                current.blank = false;
                return current;
            }
        }
        blankFallback(); // PMODE apagado conserva el placeholder magenta de RAM.
        return current;
    }
    if (!needsLatch && uploaded)
        return current;

    scratch.clear();
    uint32_t width = 0u, height = 0u, displayFbp = 0u, sourceFbp = 0u;
    bool preferred = false;
    if (!gs.copyLatchedHostPresentationFrame(scratch, width, height, &displayFbp, &sourceFbp, &preferred))
    {
        blankFallback();
        lastWidth = current.width;
        lastHeight = current.height;
        return current;
    }
    PS2_IF_AGRESSIVE_LOGS({
        if (uploadDebugCount < 128u || displayFbp != lastDisplayFbp || sourceFbp != lastSourceFbp ||
            preferred != lastPreferred || width != lastWidth || height != lastHeight)
            std::cout << "[frame:upload] idx=" << uploadDebugCount << " tick=" << vsyncTick
                      << " displayFbp=" << displayFbp << " sourceFbp=" << sourceFbp
                      << " size=" << width << "x" << height
                      << " preferred=" << static_cast<uint32_t>(preferred ? 1u : 0u) << std::endl;
        ++uploadDebugCount;
    });
    lastDisplayFbp = displayFbp;
    lastSourceFbp = sourceFbp;
    lastPreferred = preferred;
    lastWidth = width;
    lastHeight = height;
    if (width > kWidth || height > kHeight)
    {
        // GOW-Port: render-target renderer frames (internal resolution) are uploaded as they are, in a texture of their size.
        if (width > fallbackWidth || height > fallbackHeight)
        {
            UnloadTexture(fallback);
            fallbackWidth = std::max(fallbackWidth, width);
            fallbackHeight = std::max(fallbackHeight, height);
            Image bigBlank = GenImageColor(static_cast<int>(fallbackWidth), static_cast<int>(fallbackHeight), BLANK);
            fallback = LoadTextureFromImage(bigBlank);
            UnloadImage(bigBlank);
            SetTextureFilter(fallback, TEXTURE_FILTER_POINT);
        }
        UpdateTextureRec(fallback, Rectangle{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)}, scratch.data());
        uploaded = true;
        uploadedBlank = false;
        current.texture = fallback;
        current.width = width;
        current.height = height;
        current.borrowed = current.blank = false;
        current.frame = {};
        return current;
    }
    std::fill(upload.begin(), upload.end(), 0u);
    const uint32_t copyWidth = std::min(width, kWidth);
    const uint32_t copyHeight = std::min(height, kHeight);
    const size_t sourceRow = static_cast<size_t>(width) * 4u;
    const size_t destinationRow = static_cast<size_t>(kWidth) * 4u;
    const size_t copyRow = static_cast<size_t>(copyWidth) * 4u;
    for (uint32_t y = 0u; y < copyHeight; ++y)
    {
        const size_t sourceOffset = static_cast<size_t>(y) * sourceRow;
        const size_t destinationOffset = static_cast<size_t>(y) * destinationRow;
        if (sourceOffset + copyRow > scratch.size() || destinationOffset + copyRow > upload.size())
            break;
        std::memcpy(upload.data() + destinationOffset, scratch.data() + sourceOffset, copyRow);
    }
    UpdateTexture(fallback, upload.data());
    uploaded = true;
    uploadedBlank = false;
    current.texture = fallback;
    current.width = width;
    current.height = height;
    current.borrowed = current.blank = false;
    current.frame = {};
    return current;
}

GSHostPresentation::View GSHostPresentation::renderFrame(GS &gs, uint64_t vsyncTick, const std::function<void()> &overlay)
{
    View selected;
    {
        ps2_perf::Scope perf(ps2_perf::Bucket::Upload);
        selected = prepare(gs, vsyncTick);
    }
    BeginDrawing();
    ClearBackground(BLACK);
    const float sourceWidth = static_cast<float>(std::max<uint32_t>(1u, selected.width));
    const float sourceHeight = static_cast<float>(std::max<uint32_t>(1u, selected.height));
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());
    // GOW-Port: a PS2 frame (e.g. 512x448) is shown at the TV's aspect, not with square pixels:
    // always 16:9 (the game renders widescreen, see gow_overrides.cpp; 4:3 is not supported any more).
    // GOW-Port: TOBIICHI_ASPECTO / TOBIICHI_PANORAMICO (gow_integracion.cpp); 0 = estirar a toda la ventana.
    const float displayAspect = gowAspectoPresentacion();
    const float destinationWidth = displayAspect > 0.0f ? std::min(screenWidth, screenHeight * displayAspect) : screenWidth;
    const float destinationHeight = displayAspect > 0.0f ? destinationWidth / displayAspect : screenHeight;
    const Rectangle source{0.0f, 0.0f, sourceWidth, sourceHeight};
    const Rectangle destination{(screenWidth - destinationWidth) * 0.5f,
                                (screenHeight - destinationHeight) * 0.5f,
                                destinationWidth, destinationHeight};
    // GOW-Port: textura del PBO con filas en orden; no invertir source.height.
    // The bicubic + sharpen pass only helps when the frame is magnified; a frame at least as large as its window
    // rectangle (PS2X_GS_HW_SCALE high enough, or a small window) is drawn with one linear tap (same shader, "plain").
    const bool magnified = sourceWidth < destinationWidth || sourceHeight < destinationHeight;
    Shader *scaler = scalerShader();
    if (!scaler)
        SetTextureFilter(selected.texture, TEXTURE_FILTER_BILINEAR);
    if (scaler)
    {
        const float size[2] = {sourceWidth, sourceHeight};
        static const float sharpen = [] { const char *v = std::getenv("GOW_SHARPEN"); return v ? static_cast<float>(std::atof(v)) : 0.5f; }();
        SetShaderValue(*scaler, g_scalerSrcSize, size, SHADER_UNIFORM_VEC2);
        SetShaderValue(*scaler, g_scalerSharpen, &sharpen, SHADER_UNIFORM_FLOAT);
        const float plain = magnified ? 0.0f : 1.0f;
        SetShaderValue(*scaler, g_scalerPlain, &plain, SHADER_UNIFORM_FLOAT);
        static const float fxaa = [] { const char *v = std::getenv("TOBIICHI_FXAA"); return v && v[0] == '1' ? 1.0f : 0.0f; }();
        SetShaderValue(*scaler, g_scalerFxaa, &fxaa, SHADER_UNIFORM_FLOAT);
        SetTextureFilter(selected.texture, TEXTURE_FILTER_BILINEAR);
        BeginShaderMode(*scaler);
    }
    DrawTexturePro(selected.texture, source, destination, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    if (scaler)
        EndShaderMode();
    gowCuadroDibujar(destination.x, destination.y, destination.width, destination.height); // GOW-Port
    if (overlay)
        overlay();
    // GOW-Port: GOW_HOST_SHOT=<n>: at host frame n write the window's back buffer (what is about to be shown) to
    // host_shot.png in the working directory, plus the frame / window sizes, to check presentation without a desktop grab.
    static const long hostShotAt = [] { const char *v = std::getenv("GOW_HOST_SHOT"); return v ? std::atol(v) : -1L; }();
    static long hostFrame = 0;
    if (hostShotAt >= 0 && hostFrame++ == hostShotAt)
    {
        rlDrawRenderBatchActive();
        Image screen = LoadImageFromScreen();
        ExportImage(screen, "host_shot.png");
        UnloadImage(screen);
        std::fprintf(stderr, "[gs-present] host_shot frame=%ux%u tex=%u window=%dx%d shared=%d scaler=%d\n", selected.width, selected.height,
                     selected.texture.id, GetScreenWidth(), GetScreenHeight(), selected.shared ? 1 : 0, scaler ? 1 : 0);
    }
    {
        ps2_perf::Scope perf(ps2_perf::Bucket::HostWait);
        EndDrawing();
    }
    return selected;
}

void GSHostPresentation::shutdown(GS &gs)
{
    if (!started && fallback.id == 0u)
        return;
    // GOW-Port: nullptr instala un backend nulo; drena y destruye el worker/contexto compartido.
    gs.setRasterBackend(nullptr);
    restoreHostContext();
    if (fallback.id != 0u)
        UnloadTexture(fallback); // Nunca descargar la Texture2D prestada del productor.
    fallback = {};
    if (captureRequested)
        GSSharedPresent::ShutdownHost();
    started = captureRequested = hasLatched = uploaded = uploadedBlank = modeKnown = sharedMode = false;
    lastTick = lastSharedSequence = 0u;
    current = {};
    scratch.clear();
    upload.clear();
}
