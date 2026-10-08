// GOW-Port: enlaces manuales para God of War (SCUS-97399).
#include "game_overrides.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "ps2_host_backend.h"
#include "gow_pad2_packet.h"
#include "gow_gs_replay.h" // GOW-Port: captura opcional y acotada para comparar backends.
#include <ps2_recompiled_functions.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <array>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    uint32_t readGuest32(const uint8_t *rdram, uint32_t addr);
    void gowDiagPrimPoll(uint8_t *rdram, double seconds);
    // libpad2 uses socket handles and an 18-byte payload, unlike libpad's
    // port/slot API and 32-byte status packet. God of War expects state 1 and
    // a button profile beginning with 0xff to identify a DualShock 2.
    struct GowPadSocket { bool open = false; uint32_t port = 0; };
    std::array<GowPadSocket, 2> g_padSockets{};

    void padReturn(R5900Context *ctx, uint32_t result)
    {
        SET_GPR_S32(ctx, 2, static_cast<int32_t>(result));
        ctx->pc = GPR_U32(ctx, 31);
    }

    GowPadSocket *padSocket(R5900Context *ctx)
    {
        const uint32_t handle = GPR_U32(ctx, 4);
        return handle < g_padSockets.size() && g_padSockets[handle].open ? &g_padSockets[handle] : nullptr;
    }

    uint8_t *padBuffer(uint8_t *rdram, uint32_t address, size_t size)
    {
        const uint32_t physical = address & 0x1fffffffu;
        return address && physical < 0x02000000u && size <= 0x02000000u - physical ? rdram + physical : nullptr;
    }

    void gowPad2Init(uint8_t *, R5900Context *ctx, PS2Runtime *)
    {
        g_padSockets = {};
        padReturn(ctx, 1u);
    }

    void gowPad2CreateSocket(uint8_t *rdram, R5900Context *ctx, PS2Runtime *)
    {
        const uint8_t *params = padBuffer(rdram, GPR_U32(ctx, 4), 12);
        uint32_t port = 0, slot = 0;
        if (params) { std::memcpy(&port, params + 4, 4); std::memcpy(&slot, params + 8, 4); }
        if (!params || port >= 2 || slot != 0 || (GPR_U32(ctx, 5) & 63u)) { padReturn(ctx, 0xffffffffu); return; }
        for (uint32_t handle = 0; handle < g_padSockets.size(); ++handle)
        {
            if (g_padSockets[handle].open) continue;
            g_padSockets[handle] = {true, port};
            std::fprintf(stderr, "[gow-pad2] socket=%u port=%u slot=%u\n", handle, port, slot);
            padReturn(ctx, handle);
            return;
        }
        padReturn(ctx, 0xffffffffu);
    }

    void gowPad2DeleteSocket(uint8_t *, R5900Context *ctx, PS2Runtime *)
    {
        auto *socket = padSocket(ctx);
        if (socket) socket->open = false;
        padReturn(ctx, socket ? 1u : 0xffffffffu);
    }

    void gowPad2GetState(uint8_t *, R5900Context *ctx, PS2Runtime *)
    {
        const auto *socket = padSocket(ctx);
        // Only the first port has a host input backend. Keep port 2 disconnected.
        padReturn(ctx, socket && socket->port == 0 ? 1u : 0u);
    }

    void gowPad2GetButtonProfile(uint8_t *rdram, R5900Context *ctx, PS2Runtime *)
    {
        auto *buffer = padBuffer(rdram, GPR_U32(ctx, 5), 4);
        const auto *socket = padSocket(ctx);
        if (!buffer || !socket || socket->port != 0) { padReturn(ctx, 0xffffffffu); return; }
        std::memset(buffer, 0xff, 4);
        padReturn(ctx, 4u);
    }

    void gowPad2Read(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        auto *buffer = padBuffer(rdram, GPR_U32(ctx, 5), 18);
        const auto *socket = padSocket(ctx);
        uint8_t state[32]{};
        if (!buffer || !socket || socket->port != 0 || !runtime ||
            !runtime->padBackend().readState(0, 0, state, sizeof(state))) { padReturn(ctx, 0xffffffffu); return; }
        if (!IsGamepadAvailable(0))
        {
            state[6] = IsKeyDown(KEY_A) ? 0 : IsKeyDown(KEY_D) ? 255 : 128;
            state[7] = IsKeyDown(KEY_W) ? 0 : IsKeyDown(KEY_S) ? 255 : 128;
            state[4] = IsKeyDown(KEY_J) ? 0 : IsKeyDown(KEY_L) ? 255 : 128;
            state[5] = IsKeyDown(KEY_I) ? 0 : IsKeyDown(KEY_K) ? 255 : 128;
        }
        // Opt-in smoke test: advance title/new-game prompts without host UI input.
        // Capture the GS's own presented pixels; normal play never injects input.
        static const bool smokeTest = [] {
            const char *value = std::getenv("GOW_PAD_TEST");
            return value && std::strcmp(value, "1") == 0;
        }();
        static const auto testStart = std::chrono::steady_clock::now();
        if (smokeTest)
        {
            const double seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - testStart).count();
            // GOW-Port: comprobar el estado durante el perfil sin escribir capturas ni volcados.
            static const bool noCapture = [] {
                const char *value = std::getenv("GOW_PAD_TEST_NO_CAPTURE");
                return value && std::strcmp(value, "1") == 0;
            }();
            static double nextStateReport = 0;
            static const bool primDiag = [] { const char *diag=std::getenv("GOW_EE_PRIM_DIAG"); return diag && std::strcmp(diag,"1")==0; }();
            if (primDiag)
                gowDiagPrimPoll(rdram,seconds);
            if (noCapture && seconds >= nextStateReport)
            {
                nextStateReport = seconds + 5;
                std::fprintf(stderr, "[gow-pad2:state] seconds=%.2f state=%u pending=%u stage=%u levelReady=%u flashReady=%u movie=%u\n",
                             seconds, readGuest32(rdram, 0x29E560u), readGuest32(rdram, 0x29E574u),
                             readGuest32(rdram, 0x29E5A0u), readGuest32(rdram, 0x29E584u),
                             readGuest32(rdram, 0x29CAB4u), readGuest32(rdram, 0x29C838u));
            }
            // GOW_PAD_GUION="5:start,12:abajo,16:x": pulsaciones de 0,7 s en esos segundos (en lugar de la
            // secuencia fija). Botones: start, select, arriba, abajo, izquierda, derecha, x, circulo, cuadrado,
            // triangulo, l1, r1, l2, r2.
            struct ScriptedPress { double seconds; uint8_t byte; uint8_t mask; };
            static const std::vector<ScriptedPress> script = [] {
                std::vector<ScriptedPress> presses;
                const char *text = std::getenv("GOW_PAD_GUION");
                if (!text)
                    return presses;
                static const std::pair<const char *, std::pair<uint8_t, uint8_t>> buttons[] = {
                    {"select", {2, 0x01}}, {"start", {2, 0x08}}, {"arriba", {2, 0x10}}, {"derecha", {2, 0x20}},
                    {"abajo", {2, 0x40}}, {"izquierda", {2, 0x80}}, {"l2", {3, 0x01}}, {"r2", {3, 0x02}},
                    {"l1", {3, 0x04}}, {"r1", {3, 0x08}}, {"triangulo", {3, 0x10}}, {"circulo", {3, 0x20}},
                    {"x", {3, 0x40}}, {"cuadrado", {3, 0x80}}};
                std::string item;
                std::istringstream stream(text);
                while (std::getline(stream, item, ','))
                {
                    const size_t colon = item.find(':');
                    if (colon == std::string::npos)
                        continue;
                    const std::string name = item.substr(colon + 1);
                    for (const auto &[button, bit] : buttons)
                        if (name == button)
                            presses.push_back({std::strtod(item.c_str(), nullptr), bit.first, bit.second});
                }
                return presses;
            }();
            if (!script.empty())
            {
                for (const ScriptedPress &press : script)
                    if (seconds >= press.seconds && seconds < press.seconds + 0.7)
                        state[press.byte] &= static_cast<uint8_t>(~press.mask);
            }
            else
            {
                constexpr double presses[] = {5, 12, 20, 28, 36, 52, 60, 68, 76, 84, 100, 116, 132};
                for (size_t i = 0; i < std::size(presses); ++i)
                    if (seconds >= presses[i] && seconds < presses[i] + 0.7)
                    {
                        if (i == 0) state[2] &= ~0x08u; // Start
                        else state[3] &= ~0x40u; // Cross
                    }
            }
            static size_t capture = 0;
            constexpr double captures[] = {4, 10, 18, 26, 34, 44, 56, 70, 90, 110, 130, 160, 190, 240, 360, 480, 580};
            if (!noCapture && capture < std::size(captures) && seconds >= captures[capture])
            {
                std::vector<uint8_t> pixels;
                uint32_t width = 0, height = 0, display = 0, source = 0;
                bool preferred = false;
                if (runtime->gs().copyLatchedHostPresentationFrame(pixels, width, height, &display, &source, &preferred))
                {
                    const std::string name = "gow_pad_test_" + std::to_string(capture) + ".ppm";
                    std::ofstream file(name, std::ios::binary);
                    file << "P6\n" << width << ' ' << height << "\n255\n";
                    for (size_t i = 0; i + 3 < pixels.size(); i += 4)
                        file.write(reinterpret_cast<const char *>(pixels.data() + i), 3);
                    std::fprintf(stderr, "[gow-pad2:test] frame=%s seconds=%.2f\n", name.c_str(), seconds);
                    uint32_t gameState = 0, pending = 0;
                    std::memcpy(&gameState, rdram + 0x0029E560u, sizeof(gameState));
                    std::memcpy(&pending, rdram + 0x0029E574u, sizeof(pending));
                    std::fprintf(stderr, "[gow-pad2:test] state=%u pending=%u stage=%u levelReady=%u flashReady=%u movie=%u\n",
                                 gameState, pending, readGuest32(rdram, 0x29E5A0u), readGuest32(rdram, 0x29E584u),
                                 readGuest32(rdram, 0x29CAB4u), readGuest32(rdram, 0x29C838u));
                    if (std::getenv("GOW_RENDER_DIAG"))
                    {
                        static bool renderDumped = false;
                        // GOW_RENDER_DIAG_DESDE=<segundos>: volcar la primera captura en partida a partir de ese momento.
                        static const double dumpFrom = []
                        {
                            const char *v = std::getenv("GOW_RENDER_DIAG_DESDE");
                            return v ? std::strtod(v, nullptr) : 0.0;
                        }();
                        if (gameState == 11u && !renderDumped && seconds >= dumpFrom)
                        {
                            renderDumped = true;
                            std::ofstream code("gow_vu1_code.bin", std::ios::binary);
                            code.write(reinterpret_cast<const char *>(runtime->memory().getVU1Code()), 0x4000);
                            std::ofstream data("gow_vu1_data.bin", std::ios::binary);
                            data.write(reinterpret_cast<const char *>(runtime->memory().getVU1Data()), 0x4000);
                            std::ofstream ram("gow_render_ram.bin", std::ios::binary);
                            ram.write(reinterpret_cast<const char *>(rdram), 0x02000000u);
                            // Sincronizar la VRAM del backend GPU antes de leer el búfer host.
                            runtime->gs().refreshDisplaySnapshot();
                            const auto gsState = runtime->gs().getDebugSnapshot();
                            std::ofstream vram("gow_render_vram.bin", std::ios::binary);
                            vram.write(reinterpret_cast<const char *>(runtime->memory().getGSVRAM()), PS2_GS_VRAM_SIZE);
                            for (unsigned context = 0; context < 2; ++context)
                            {
                                const auto &frame = gsState.ctx[context].frame;
                                if (!frame.fbw || (frame.psm != 0u && frame.psm != 1u)) continue;
                                const std::string name = "gow_render_context_" + std::to_string(context) + ".ppm";
                                std::ofstream image(name, std::ios::binary);
                                image << "P6\n" << width << ' ' << height << "\n255\n";
                                uint32_t nonBlack = 0u;
                                for (uint32_t y = 0; y < height; ++y)
                                    for (uint32_t x = 0; x < width; ++x)
                                    {
                                        const uint32_t color = runtime->gs().ReadVram(frame.psm, frame.fbp * 32u, frame.fbw, x, y);
                                        const uint8_t rgb[] = {uint8_t(color), uint8_t(color >> 8), uint8_t(color >> 16)};
                                        image.write(reinterpret_cast<const char *>(rgb), 3);
                                        nonBlack += (color & 0xFFFFFFu) != 0u;
                                    }
                                std::fprintf(stderr, "[gow-gs:buffer] context=%u fbp=%u fbw=%u psm=%u nonBlack=%u file=%s\n",
                                             context, frame.fbp, frame.fbw, frame.psm, nonBlack, name.c_str());
                            }
                        }
                        const auto snapshot = runtime->gs().getDebugSnapshot();
                        std::fprintf(stderr, "[gow-gs] ctxFbp=%u,%u display=%u source=%u\n", snapshot.ctx[0].frame.fbp,
                                     snapshot.ctx[1].frame.fbp, display, source);
                        unsigned count = 0;
                        const auto history = runtime->gs().getDebugHistory();
                        for (auto event = history.rbegin(); event != history.rend() && count < 16; ++event)
                            if (event->kind == GSDebugEventKind::Draw)
                            {
                                ++count;
                                std::fprintf(stderr, "[gow-gs:draw] prim=%u tex=%u fbp=%u xy=%g,%g:%g,%g z=%g:%g a=%u:%u test=%llx alpha=%llx\n",
                                             unsigned(event->prim.type), unsigned(event->prim.tme), event->frame.fbp,
                                             event->xMin, event->yMin, event->xMax, event->yMax, event->zMin, event->zMax,
                                             event->aMin, event->aMax, static_cast<unsigned long long>(event->test),
                                             static_cast<unsigned long long>(event->alpha));
                            }
                    }
                }
                ++capture;
            }
        }
        const auto packet = gow_pad2::makePacket(state);
        std::memcpy(buffer, packet.data(), packet.size());
        const uint16_t buttons = static_cast<uint16_t>(state[2] | (state[3] << 8));
        static unsigned reads = 0;
        static uint16_t lastButtons = 0xffff;
        if (++reads <= 3 || buttons != lastButtons)
            std::fprintf(stderr, "[gow-pad2] read buttons=%04x sticks=%u,%u,%u,%u\n", buttons, buffer[2], buffer[3], buffer[4], buffer[5]);
        lastButtons = buttons;
        static const bool anmDiag = std::getenv("GOW_ANM_DIAG") != nullptr;
        if (anmDiag && readGuest32(rdram, 0x29E560u) == 4u && reads % 100 == 0)
        {
            const uint32_t card = readGuest32(rdram, 0x29BE50u);
            std::fprintf(stderr, "[gow-transition] padType=%u cardState=%u pause=%u,%u,%u,%u speed=%x\n",
                         readGuest32(rdram, 0x2FD9C8u), readGuest32(rdram, card + 0x278u),
                         readGuest32(rdram, 0x29E564u), readGuest32(rdram, 0x29E568u),
                         readGuest32(rdram, 0x29E56Cu), readGuest32(rdram, 0x29E570u), readGuest32(rdram, 0x32F1F0u));
        }
        padReturn(ctx, 18u);
    }

    void gowVibGetProfile(uint8_t *, R5900Context *ctx, PS2Runtime *)
    {
        // No rumble capability yet; the game skips actuator updates for count 0.
        padReturn(ctx, 0u);
    }

    // Sectores de la capa 0 del DVD (donde empieza la capa 1). Medido en la ISO del usuario.
    constexpr uint32_t kLayer1StartLbn = 2080544u;

    void writeGuest32(uint8_t *rdram, uint32_t addr, uint32_t value)
    {
        if (addr == 0u) return;
        std::memcpy(rdram + (addr & 0x01FFFFFFu), &value, sizeof(value));
    }

    uint32_t readGuest32(const uint8_t *rdram, uint32_t addr)
    {
        uint32_t v;
        std::memcpy(&v, rdram + (addr & 0x01FFFFFFu), sizeof(v));
        return v;
    }

    void gowDiagPathSelect(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        // GOW-Port: getenv recorre todo el entorno; en funciones llamadas a menudo se lee una vez.
        static const bool pathDiag = std::getenv("GOW_PATH_DIAG") != nullptr;
        if (ctx->pc == 0x00180E50u && pathDiag)
        {
            const uint32_t object = GPR_U32(ctx, 4);
            const uint32_t address = GPR_U32(ctx, 5);
            const auto *text = padBuffer(rdram, address, 256);
            std::fprintf(stderr, "[gow-path] iterator=0x%x parent=0x%x child=%.255s\n", object,
                         readGuest32(rdram, object + 4), text ? reinterpret_cast<const char *>(text) : "<invalid>");
        }
        sub_00180E50_0x180e50(rdram, ctx, runtime);
    }

    void gowDiagAttachNode(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        static const bool pathDiag = std::getenv("GOW_PATH_DIAG") != nullptr;
        if (ctx->pc == 0x00180D08u && GPR_U32(ctx, 5) == 0 && pathDiag)
        {
            std::ofstream file("gow_path_failure.bin", std::ios::binary);
            file.write(reinterpret_cast<const char *>(rdram), 0x02000000u);
            std::fprintf(stderr, "[gow-path] NULL node iterator=0x%x ra=0x%x; RAM saved\n", GPR_U32(ctx, 4), GPR_U32(ctx, 31));
        }
        sub_00180D08_0x180d08(rdram, ctx, runtime);
    }

    // SCUS-97399 sceIpuInit uses SetD4_CHCR at 0x279588 and tables at
    // 0x2a1610/0x2a1660. The generic stub's hard-coded 0x126428 is a
    // FilteredCopyTile continuation in this ELF, so initialize MMIO directly.
    void gowIpuInit(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        auto &memory = runtime->memory();
        memory.write32(0x1000B400u, 1u);
        memory.write32(0x10002010u, 0x40000000u);
        memory.write32(0x10002000u, 0u);
        for (uint32_t offset : {0u, 16u, 32u, 48u, 64u, 64u, 64u, 64u})
            memory.write128(0x10007010u, runtime->Load128(rdram, ctx, 0x002A1610u + offset));
        memory.write32(0x10002000u, 0x50000000u);
        memory.write32(0x10002000u, 0x58000000u);
        for (uint32_t offset : {0u, 16u})
            memory.write128(0x10007010u, runtime->Load128(rdram, ctx, 0x002A1660u + offset));
        memory.write32(0x10002000u, 0x60000000u);
        memory.write32(0x10002000u, 0x90000000u);
        memory.write32(0x10002010u, 0x40000000u);
        memory.write32(0x10002000u, 0u);
        std::fprintf(stderr, "[gow-ipu] initialized using SCUS-97399 tables\n");
        padReturn(ctx, 0u);
    }

    // Optional FMV bypass at the movie API, before buffers/RPCs are allocated.
    // Keep the normal MPEG path available for decoder investigation.
    void gowSkipMovieLoad(uint8_t *rdram, R5900Context *ctx, PS2Runtime *)
    {
        const auto *name = padBuffer(rdram, GPR_U32(ctx, 4), 128);
        std::fprintf(stderr, "[gow-fmv] skipped %.127s\n", name ? reinterpret_cast<const char *>(name) : "<invalid>");
        writeGuest32(rdram, 0x0029C838u, 0u);
        writeGuest32(rdram, 0x0029C870u, 0u);
        writeGuest32(rdram, 0x0029C840u, 0u);
        padReturn(ctx, 0u);
    }

    void gowSkipMovieReady(uint8_t *, R5900Context *ctx, PS2Runtime *) { padReturn(ctx, 1u); }
    void gowSkipMovieNoop(uint8_t *, R5900Context *ctx, PS2Runtime *) { padReturn(ctx, 0u); }

    void gowDiagFlashReady(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        static unsigned calls = 0;
        if (++calls <= 30)
            std::fprintf(stderr, "[gow-flash-ready] a0=%x event=%x ra=%x\n", GPR_U32(ctx, 4), GPR_U32(ctx, 5), GPR_U32(ctx, 31));
        sub_001B2390_0x1b2390(rdram, ctx, runtime);
    }

    void gowDiagAnimationTime(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t ra = GPR_U32(ctx, 31), object = GPR_U32(ctx, 4);
        static const bool fastBoot = [] { const char *value = std::getenv("GOW_FAST_BOOT"); return value && std::strcmp(value, "1") == 0; }();
        if (fastBoot && ra == 0x0021E714u &&
            readGuest32(rdram, 0x29E560u) == 4u && readGuest32(rdram, 0x29E584u) == 1u)
        {
            // Only the intro-completion query is bypassed, after the level load.
            // No animation state or game-state flags are changed.
            sub_00100BF0_0x100bf0(rdram, ctx, runtime);
            return;
        }
        sub_00100C50_0x100c50(rdram, ctx, runtime);
        static unsigned samples = 0;
        if (readGuest32(rdram, 0x29E560u) == 4u && ctx->pc == ra && samples++ % 100 == 0)
        {
            float delta = 0;
            std::memcpy(&delta, rdram + 0x29C64Cu, sizeof(delta));
            std::fprintf(stderr, "[gow-animation] object=%x time=%g delta=%g\n", object, ctx->f[0], delta);
        }
    }

    void gowDiagAnimationDuration(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t ra = GPR_U32(ctx, 31);
        sub_00100BF0_0x100bf0(rdram, ctx, runtime);
        static unsigned samples = 0;
        if (readGuest32(rdram, 0x29E560u) == 4u && ctx->pc == ra && samples++ % 100 == 0)
            std::fprintf(stderr, "[gow-animation] duration=%g\n", ctx->f[0]);
    }

    void gowDiagFilteredCopy(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        static unsigned entries = 0, resumes = 0;
        if (ctx->pc == 0x001262C8u && ++entries <= 30)
            std::fprintf(stderr, "[gow-filter] entry a0=%x a1=%x a2=%x a3=%x t0=%x t1=%x t2=%x t3=%x ra=%x sp=%x\n",
                         GPR_U32(ctx, 4), GPR_U32(ctx, 5), GPR_U32(ctx, 6), GPR_U32(ctx, 7),
                         GPR_U32(ctx, 8), GPR_U32(ctx, 9), GPR_U32(ctx, 10), GPR_U32(ctx, 11),
                         GPR_U32(ctx, 31), GPR_U32(ctx, 29));
        if (ctx->pc == 0x00126528u && ++resumes <= 40)
            std::fprintf(stderr, "[gow-filter] resume index=%x limit=%x rows=%x ra=%x sp=%x\n",
                         GPR_U32(ctx, 10), GPR_U32(ctx, 12), GPR_U32(ctx, 14), GPR_U32(ctx, 31), GPR_U32(ctx, 29));
        sub_001262C8_0x1262c8(rdram, ctx, runtime);
    }

    // GOW-Port: observar el productor de posiciones, sin alterar buffers ni ejecución EE.
    void gowDiagInitUnpack(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00141350u) { sub_00141350_0x141350(rdram, ctx, runtime); return; }
        const uint32_t object=GPR_U32(ctx,4), data=GPR_U32(ctx,5), type=GPR_U32(ctx,6);
        const uint32_t chunk=GPR_U32(ctx,7), buffer=GPR_U32(ctx,8), caller=GPR_U32(ctx,31);
        sub_00141350_0x141350(rdram, ctx, runtime);
        static unsigned samples=0;
        if (samples++ < 64 && ctx->pc == caller)
            std::fprintf(stderr,"[gow-eeprim:init] this=%x caller=%x type=%u chunk=%u buffer=%u command=%x next=%x\n",
                         object,caller,type,chunk,buffer,data,GPR_U32(ctx,2));
    }

    struct GowPrimProbe { uint32_t object=0,caller=0,address=0; };
    std::array<GowPrimProbe,16> g_primProbes{};
    size_t g_nextPrimProbe=0;

    // GOW-Port: observar la lista usada por ProcessServer antes de ejecutar el original.
    // La lista de SCUS-97399 usa nodos en objeto+8 y termina en NULL (MIPS 0x141BF4/0x1421A4).
    void gowDiagPrimContext(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00141B78u) { sub_00141B78_0x141b78(rdram, ctx, runtime); return; }
        static unsigned early = 0u, scene = 0u;
        const uint32_t state = readGuest32(rdram, 0x29E560u);
        auto &sample = state == 11u ? scene : early;
        const uint32_t context = GPR_U32(ctx, 4);
        if (sample < 64u && padBuffer(rdram, context, 0x4Cu))
        {
            ++sample;
            const uint32_t view = readGuest32(rdram, 0x33104Cu);
            const bool validView = padBuffer(rdram, view, 0x3B0u) != nullptr;
            const uint32_t viewId = validView ? readGuest32(rdram, view + 0x3ACu) : 0u;
            const uint32_t contextMask = readGuest32(rdram, context + 0x48u);
            uint32_t camera = 0u;
            if (validView)
            {
                const uint32_t cameraNode = readGuest32(rdram, view + 0x360u);
                if (cameraNode != view + 0x360u && padBuffer(rdram, cameraNode, 12u))
                    camera = readGuest32(rdram, cameraNode + 8u);
            }
            std::array<uint32_t, 256> seen{};
            std::array<bool, 16> members{};
            uint32_t node = readGuest32(rdram, context + 0x24u);
            const uint32_t head = node;
            size_t count = 0u;
            uint32_t candidates = 0u;
            bool invalid = false, cycle = false;
            while (node && count < seen.size())
            {
                const uint32_t physical = node & 0x1FFFFFFFu;
                for (size_t i = 0u; i < count; ++i)
                    cycle |= seen[i] == physical;
                if (cycle) break;
                if (physical < 8u || !padBuffer(rdram, node - 8u, 0x148u)) { invalid = true; break; }
                seen[count++] = physical;
                const uint32_t object = node - 8u;
                const auto *objectData = padBuffer(rdram, object, 0x148u);
                const int8_t updated = static_cast<int8_t>(objectData[0x146u]);
                const uint32_t dma = (updated == 0 || updated == 1) ? readGuest32(rdram, object + 0xF0u + 4u * updated) : 0u;
                const uint32_t objectMask = readGuest32(rdram, object + 0xD8u);
                candidates += camera && (viewId & contextMask) && dma && (viewId & objectMask) ? 1u : 0u;
                for (size_t i = 0u; i < g_primProbes.size(); ++i)
                    members[i] = members[i] || (g_primProbes[i].object &&
                        (g_primProbes[i].object & 0x1FFFFFFFu) == (object & 0x1FFFFFFFu));
                node = readGuest32(rdram, node);
            }
            std::fprintf(stderr, "[gow-eeprim:context] sample=%u state=%u this=%x view=%x validView=%u id=%x mask=%x camera=%x head=%x nodes=%zu candidates=%u invalid=%u cycle=%u truncated=%u\n",
                         sample, state, context, view, validView ? 1u : 0u, viewId, contextMask, camera, head,
                         count, candidates, invalid ? 1u : 0u, cycle ? 1u : 0u, node && !invalid && !cycle ? 1u : 0u);
            for (size_t i = 0u; i < g_primProbes.size(); ++i)
            {
                const auto &p = g_primProbes[i];
                const auto *objectData = padBuffer(rdram, p.object, 0x148u);
                if (!objectData) continue;
                std::fprintf(stderr, "[gow-eeprim:member] sample=%u state=%u context=%x this=%x caller=%x member=%u updated=%u rendered=%u viewMask=%x next=%x dma=%x,%x\n",
                             sample, state, context, p.object, p.caller, members[i] ? 1u : 0u,
                             objectData[0x146u], objectData[0x147u], readGuest32(rdram, p.object + 0xD8u),
                             readGuest32(rdram, p.object + 8u), readGuest32(rdram, p.object + 0xF0u), readGuest32(rdram, p.object + 0xF4u));
            }
        }
        // Nunca escribir índices, posiciones ni registros: el original conserva también sus checkpoints.
        sub_00141B78_0x141b78(rdram, ctx, runtime);
    }

    // GOW-Port: seleccionar el contexto de modelos segun el MIPS retail, sin modificarlo.
    void gowDiagModelServer(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00159C58u) { sub_00159C58_0x159c58(rdram, ctx, runtime); return; }
        const uint32_t state = readGuest32(rdram, 0x29E560u), server = GPR_U32(ctx, 4);
        static unsigned early = 0u, scene = 0u;
        auto &samples = state == 11u ? scene : early;
        if (samples < 64u)
        {
            const unsigned sample = ++samples;
            const bool validServer = padBuffer(rdram, server, 0xD8u) != nullptr;
            const uint32_t table = validServer ? readGuest32(rdram, server + 0x24u) : 0u;
            const uint32_t group = validServer ? readGuest32(rdram, server + 0x44u) : 0u;
            const uint32_t slot = validServer ? readGuest32(rdram, server + 0xD4u) : 0u;
            // Calculos en 64 bits para no envolver indices fuera de RAM.
            const uint64_t row = (table & 0x1FFFFFFFu) + uint64_t(group) * 12u;
            const bool validRow = table && row < 0x02000000u && padBuffer(rdram, uint32_t(row), 12u);
            const uint32_t array = validRow ? readGuest32(rdram, uint32_t(row)) : 0u;
            const uint64_t cell = (array & 0x1FFFFFFFu) + uint64_t(slot) * 4u;
            const bool validCell = array && cell < 0x02000000u && padBuffer(rdram, uint32_t(cell), 4u);
            const uint32_t context = validCell ? readGuest32(rdram, uint32_t(cell)) : 0u;
            const bool validContext = padBuffer(rdram, context, 0x24u) != nullptr;
            const uint32_t vtable = validContext ? readGuest32(rdram, context + 0x20u) : 0u;
            const auto *methods = padBuffer(rdram, vtable, 0x20u);
            int16_t adjustment = 0;
            if (methods) std::memcpy(&adjustment, methods + 0x18u, sizeof(adjustment));
            const uint32_t target = methods ? readGuest32(rdram, vtable + 0x1Cu) : 0u;
            std::fprintf(stderr, "[gow-model:server] sample=%u state=%u this=%x valid=%u table=%x group=%u slot=%u array=%x context=%x validContext=%u vtable=%x validMethods=%u adjustment=%d target=%x\n",
                         sample, state, server, validServer ? 1u : 0u, table, group, slot, array, context,
                         validContext ? 1u : 0u, vtable, methods ? 1u : 0u, int(adjustment), target);
        }
        // La seleccion es una fotografia de entrada; el original conserva sus checkpoints y llamadas.
        sub_00159C58_0x159c58(rdram, ctx, runtime);
    }

    struct GowModelContextSamples { uint32_t physical = 0u; unsigned early = 0u, scene = 0u; };

    // GOW-Port: el maestro es compartido por varios servidores; limitar cada contexto
    // evita que los primeros servidores agoten las muestras del servidor de modelos.
    unsigned gowModelContextSample(std::array<GowModelContextSamples, 8> &probes, uint32_t context, uint32_t state)
    {
        const uint32_t physical = context & 0x1FFFFFFFu;
        if (!physical) return 0u;
        for (auto &probe : probes)
            if (probe.physical == physical || !probe.physical)
            {
                probe.physical = physical;
                auto &samples = state == 11u ? probe.scene : probe.early;
                return samples < 64u ? ++samples : 0u;
            }
        return 0u;
    }

    // GOW-Port: lista del maestro GROB segun el MIPS retail 0x151238-0x151334.
    // Una fotografia de entrada no sustituye la ejecucion ni prueba un envio al GS.
    void gowDiagGrobMaster(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x001511F0u) { sub_001511F0_0x1511f0(rdram, ctx, runtime); return; }
        const uint32_t state = readGuest32(rdram, 0x29E560u), context = GPR_U32(ctx, 4);
        static std::array<GowModelContextSamples, 8> probes{};
        const unsigned sample = gowModelContextSample(probes, context, state);
        if (sample)
        {
            const bool validContext = padBuffer(rdram, context, 0x28u) != nullptr;
            const uint32_t head = validContext ? readGuest32(rdram, context + 0x24u) : 0u;
            uint32_t node = head;
            std::array<uint32_t, 256> seen{};
            size_t count = 0u, active = 0u, invalidRoutes = 0u;
            bool invalid = !validContext, cycle = false;
            while (node && count < seen.size())
            {
                const uint32_t physical = node & 0x1FFFFFFFu;
                for (size_t i = 0u; i < count; ++i) cycle |= seen[i] == physical;
                if (cycle) break;
                const auto *clientData = physical >= 8u ? padBuffer(rdram, node - 8u, 0x48u) : nullptr;
                if (!clientData) { invalid = true; break; }
                seen[count++] = physical;
                const uint32_t client = node - 8u;
                uint16_t id = 0u;
                std::memcpy(&id, clientData, sizeof(id));
                const uint32_t enabled = readGuest32(rdram, client + 0x2Cu);
                const uint32_t view = readGuest32(rdram, client + 0x44u);
                const uint32_t server = readGuest32(rdram, 0x32E848u + uint32_t(id) * 4u);
                const uint32_t vtable = readGuest32(rdram, client + 0x20u);
                const auto *methods = padBuffer(rdram, vtable, 0x20u);
                int16_t adjustment = 0;
                if (methods) std::memcpy(&adjustment, methods + 0x18u, sizeof(adjustment));
                const uint32_t target = methods ? readGuest32(rdram, vtable + 0x1Cu) : 0u;
                const bool validRoute = methods && padBuffer(rdram, server, 0x24u) &&
                    padBuffer(rdram, view, 2u) && padBuffer(rdram, target, 4u);
                active += enabled ? 1u : 0u;
                invalidRoutes += enabled && !validRoute ? 1u : 0u;
                if (sample <= 8u)
                    std::fprintf(stderr, "[gow-model:grob-client] sample=%u state=%u master=%x index=%zu this=%x id=%x enabled=%x clients=%x view=%x server=%x vtable=%x adjustment=%d target=%x validRoute=%u\n",
                                 sample, state, context, count - 1u, client, unsigned(id), enabled,
                                 readGuest32(rdram, client + 0x24u), view, server, vtable, int(adjustment), target,
                                 validRoute ? 1u : 0u);
                node = readGuest32(rdram, node);
            }
            std::fprintf(stderr, "[gow-model:grob-master] sample=%u state=%u this=%x valid=%u head=%x nodes=%zu active=%zu invalidRoutes=%zu invalid=%u cycle=%u truncated=%u\n",
                         sample, state, context, validContext ? 1u : 0u, head, count, active, invalidRoutes,
                         invalid ? 1u : 0u, cycle ? 1u : 0u, node && !invalid && !cycle ? 1u : 0u);
        }
        sub_001511F0_0x1511f0(rdram, ctx, runtime);
    }

    // GOW-Port: filtros de la lista de modelos, comprobados en MIPS 0x1598A0-0x15991C.
    void gowDiagModelContext(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00159878u) { sub_00159878_0x159878(rdram, ctx, runtime); return; }
        const uint32_t state = readGuest32(rdram, 0x29E560u), context = GPR_U32(ctx, 4);
        static std::array<GowModelContextSamples, 8> probes{};
        const unsigned sample = gowModelContextSample(probes, context, state);
        if (sample)
        {
            const bool validContext = padBuffer(rdram, context, 0x60u) != nullptr;
            const uint32_t view = readGuest32(rdram, 0x33104Cu);
            const bool validView = padBuffer(rdram, view, 0x3B0u) != nullptr;
            const uint32_t viewId = validView ? readGuest32(rdram, view + 0x3ACu) : 0u;
            const uint32_t mask = validContext ? readGuest32(rdram, context + 0x48u) : 0u;
            const uint32_t staticCount = validContext ? readGuest32(rdram, context + 0x54u) : 0u;
            const uint32_t sphereTree = validContext ? readGuest32(rdram, context + 0x58u) : 0u;
            const uint32_t sphereValid = validContext ? readGuest32(rdram, context + 0x5Cu) : 0u;
            const bool useStatic = sphereValid && staticCount;
            uint32_t node = validContext ? readGuest32(rdram, context + 0x24u) : 0u;
            const uint32_t head = node;
            std::array<uint32_t, 256> seen{};
            size_t count = 0u, viewRejected = 0u, treeCandidates = 0u, processCandidates = 0u;
            bool invalid = !validContext || !validView, cycle = false;
            while (node && count < seen.size())
            {
                const uint32_t physical = node & 0x1FFFFFFFu;
                for (size_t i = 0u; i < count; ++i) cycle |= seen[i] == physical;
                if (cycle) break;
                const auto *data = physical >= 8u ? padBuffer(rdram, node - 8u, 0x124u) : nullptr;
                if (!data) { invalid = true; break; }
                seen[count++] = physical;
                const uint32_t model = node - 8u, modelMask = readGuest32(rdram, model + 0xD8u);
                int16_t sphereId = 0;
                std::memcpy(&sphereId, data + 0x122u, sizeof(sphereId));
                const bool passesView = (viewId & mask) && (viewId & modelMask);
                viewRejected += !passesView ? 1u : 0u;
                treeCandidates += passesView && useStatic && sphereId >= 0 ? 1u : 0u;
                processCandidates += passesView && (!useStatic || sphereId < 0) ? 1u : 0u;
                if (sample <= 8u)
                    std::fprintf(stderr, "[gow-model:client] sample=%u state=%u context=%x index=%zu this=%x mask=%x sphereId=%d passesView=%u treeCandidate=%u\n",
                                 sample, state, context, count - 1u, model, modelMask, int(sphereId), passesView ? 1u : 0u,
                                 passesView && useStatic && sphereId >= 0 ? 1u : 0u);
                node = readGuest32(rdram, node);
            }
            std::fprintf(stderr, "[gow-model:context] sample=%u state=%u this=%x view=%x validView=%u id=%x mask=%x head=%x nodes=%zu viewRejected=%zu treeCandidates=%zu processCandidates=%zu staticCount=%u sphereTree=%x sphereValid=%u invalid=%u cycle=%u truncated=%u\n",
                         sample, state, context, view, validView ? 1u : 0u, viewId, mask, head, count,
                         viewRejected, treeCandidates, processCandidates, staticCount, sphereTree, sphereValid,
                         invalid ? 1u : 0u, cycle ? 1u : 0u, node && !invalid && !cycle ? 1u : 0u);
        }
        sub_00159878_0x159878(rdram, ctx, runtime);
    }

    // GOW-Port: entrada real de la rutina que procesa un modelo (MIPS 0x157A60).
    // Su estructura coincide con ProcessModel de la referencia GoW 2; el mapa retail no la nombra.
    void gowDiagProcessModel(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00157A60u) { sub_00157A60_0x157a60(rdram, ctx, runtime); return; }
        const uint32_t state = readGuest32(rdram, 0x29E560u);
        static unsigned early = 0u, scene = 0u;
        auto &samples = state == 11u ? scene : early;
        if (samples < 64u)
        {
            const uint32_t context = GPR_U32(ctx, 4), model = GPR_U32(ctx, 5);
            const bool valid = padBuffer(rdram, model, 0xE8u) != nullptr;
            const uint32_t view = readGuest32(rdram, 0x33104Cu);
            const uint32_t object = valid ? readGuest32(rdram, model + 0x18u) : 0u;
            const bool validObject = padBuffer(rdram, object, 0x108u) != nullptr;
            const uint32_t skeleton = validObject ? readGuest32(rdram, object + 0x104u) : 0u;
            const auto *skeletonData = padBuffer(rdram, skeleton, 0x90u);
            uint16_t rootId = 0u;
            if (skeletonData) std::memcpy(&rootId, skeletonData + 0x86u, sizeof(rootId));
            const uint32_t visibility = skeletonData ? readGuest32(rdram, skeleton + 0x54u) : 0u;
            const uint64_t rootAddress = (visibility & 0x1FFFFFFFu) + uint64_t(rootId) * 4u;
            const bool validRoot = skeletonData && (!visibility || (rootAddress < 0x02000000u && padBuffer(rdram, uint32_t(rootAddress), 4u)));
            const uint32_t rootVisible = validRoot ? (!visibility || readGuest32(rdram, uint32_t(rootAddress)) ? 1u : 0u) : 0u;
            std::fprintf(stderr, "[gow-model:process] sample=%u state=%u context=%x this=%x valid=%u caller=%x view=%x groups=%u groupArray=%x disableCulling=%u object=%x skeleton=%x visibility=%x rootId=%u validRoot=%u rootVisible=%u groupBits=%x\n",
                         ++samples, state, context, model, valid ? 1u : 0u, GPR_U32(ctx, 31), view,
                         valid ? readGuest32(rdram, model + 0xE0u) : 0u,
                         valid ? readGuest32(rdram, model + 0xE4u) : 0u, GPR_U32(ctx, 6), object, skeleton,
                         visibility, unsigned(rootId), validRoot ? 1u : 0u, rootVisible,
                         validObject ? readGuest32(rdram, object + 0x100u) : 0u);
        }
        sub_00157A60_0x157a60(rdram, ctx, runtime);
    }

    // GOW-Port: resultado del Clip llamado desde ProcessModel (MIPS 0x157FA8).
    // Solo observar bits de argumentos y resultado; no cambiar la FPU ni el criterio del juego.
    void gowDiagModelClip(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x00169120u) { sub_00169120_0x169120(rdram, ctx, runtime); return; }
        const uint32_t caller = GPR_U32(ctx, 31), state = readGuest32(rdram, 0x29E560u);
        static unsigned early = 0u, scene = 0u;
        auto &samples = state == 11u ? scene : early;
        const unsigned sample = caller == 0x00157FB0u && samples < 64u ? ++samples : 0u;
        const uint32_t view = GPR_U32(ctx, 4), model = GPR_U32(ctx, 17), group = GPR_U32(ctx, 19);
        std::array<uint32_t, 4> sphere{};
        std::array<uint32_t, 10> planes{};
        const bool validView = padBuffer(rdram, view, 0x38Cu) != nullptr;
        if (sample)
        {
            for (size_t i = 0u; i < sphere.size(); ++i) std::memcpy(&sphere[i], &ctx->f[12u + i], 4u);
            const std::array<uint32_t, 10> offsets = {0x384u, 0x388u, 0x2C0u, 0x2C8u, 0x2D4u, 0x2D8u, 0x2E0u, 0x2E8u, 0x2F4u, 0x2F8u};
            if (validView)
                for (size_t i = 0u; i < offsets.size(); ++i) planes[i] = readGuest32(rdram, view + offsets[i]);
        }
        sub_00169120_0x169120(rdram, ctx, runtime);
        if (sample)
            std::fprintf(stderr, "[gow-model:clip] sample=%u state=%u this=%x group=%x view=%x validView=%u sphere=%08x,%08x,%08x,%08x planes=%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x completed=%u result=%x\n",
                         sample, state, model, group, view, validView ? 1u : 0u,
                         sphere[0], sphere[1], sphere[2], sphere[3], planes[0], planes[1], planes[2], planes[3],
                         planes[4], planes[5], planes[6], planes[7], planes[8], planes[9], ctx->pc == caller ? 1u : 0u,
                         ctx->pc == caller ? GPR_U32(ctx, 2) : 0u);
    }

    void gowDiagPrimPoll(uint8_t *rdram, double seconds)
    {
        static double next=0;
        if(seconds<next) return;
        next=seconds+5;
        if(readGuest32(rdram,0x29E560u)!=11u) return;
        for(const auto &p:g_primProbes)
        {
            const auto *data=padBuffer(rdram,p.address,16);
            if(!data) continue;
            uint32_t words[4]{}; std::memcpy(words,data,16);
            std::fprintf(stderr,"[gow-eeprim:later] seconds=%.2f this=%x caller=%x data=%x first=%08x,%08x,%08x,%08x\n",
                         seconds,p.object,p.caller,p.address,words[0],words[1],words[2],words[3]);
        }
    }

    void gowDiagUpdateAddress(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x001417D8u) { sub_001417D8_0x1417d8(rdram, ctx, runtime); return; }
        const uint32_t object=GPR_U32(ctx,4), type=GPR_U32(ctx,5), offset=GPR_U32(ctx,6);
        const uint32_t chunk=GPR_U32(ctx,7), buffer=GPR_U32(ctx,8), caller=GPR_U32(ctx,31);
        sub_001417D8_0x1417d8(rdram, ctx, runtime);
        static unsigned early=0, scene=0;
        auto &samples=readGuest32(rdram,0x29E560u)==11u ? scene : early;
        if (type != 0u || samples >= (readGuest32(rdram,0x29E560u)==11u ? 256u : 64u)) return;
        ++samples;
        // Un checkpoint no es un retorno: no interpretar v0 como dirección en ese caso.
        if (ctx->pc != caller)
        {
            std::fprintf(stderr,"[gow-eeprim:update] caller=%x this=%x checkpoint=%x\n",caller,object,ctx->pc);
            return;
        }
        const uint32_t address=GPR_U32(ctx,2);
        const auto *data=padBuffer(rdram,address,16);
        uint32_t words[4]{}; if(data) std::memcpy(words,data,16);
        if(data)
        {
            bool found=false;
            for(const auto &p:g_primProbes) found |= p.address==address;
            if(!found) g_primProbes[g_nextPrimProbe++ % g_primProbes.size()]={object,caller,address};
        }
        std::fprintf(stderr,"[gow-eeprim:update] this=%x caller=%x type=%u offset=%u chunk=%u buffer=%u data=%x valid=%u first=%08x,%08x,%08x,%08x\n",
                     object,caller,type,offset,chunk,buffer,address,data?1u:0u,words[0],words[1],words[2],words[3]);
    }

    // int sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start)
    void gowCdReadDvdDualInfo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *)
    {
        writeGuest32(rdram, GPR_U32(ctx, 4), 1u);
        writeGuest32(rdram, GPR_U32(ctx, 5), kLayer1StartLbn);
        SET_GPR_U32(ctx, 2, 1u);
        ctx->pc = GPR_U32(ctx, 31);
    }

    // Volcado hex + ASCII de memoria del EE para el registro de comandos.
    void dumpGuestBytes(const uint8_t *rdram, uint32_t addr, uint32_t len)
    {
        for (uint32_t off = 0; off < len; off += 16u)
        {
            char hex[16 * 3 + 1] = {};
            char asc[17] = {};
            const uint32_t n = (len - off < 16u) ? (len - off) : 16u;
            for (uint32_t i = 0; i < n; ++i)
            {
                const uint8_t c = rdram[(addr + off + i) & 0x01FFFFFFu];
                std::snprintf(hex + i * 3, 4, "%02x ", c);
                asc[i] = (c >= 0x20 && c < 0x7F) ? static_cast<char>(c) : '.';
            }
            std::fprintf(stderr, "[gow-snd]     +%03x: %-48s %s\n", off, hex, asc);
        }
    }

    // sub_0026BF28(cmd, tamano, datos): envio de comandos al driver de sonido 989snd (version EE).
    // El original hace sceSifCallRpc(sid 0x123456, rpc = cmd, envio = 0x305640 [tamano bytes],
    // respuesta = 0x305600 [12 bytes]) y devuelve la palabra 1 de la respuesta.
    // cmd 0x68 = mensaje para un plugin de 989snd (smpd, el cargador de datos): 'datos' apunta a
    // {u32 a, u32 b, u32 len, u32 ptr} y se envian los 12 primeros bytes + len bytes copiados de ptr.
    // Desde que el emulador del IOP ejecuta los IRX originales (989NOMID.IRX + SMPD_IOP.IRX, copiados en
    // IOP_MOD/ junto al ELF), el comando se pasa al original; aqui solo registramos lo que pide el juego.
    // Con GOW_SND_STUB=1 se vuelve al comportamiento antiguo (responder 0 sin pasar por el IOP).
    int g_sndCmdCount = 0;
    const bool g_sndStub = []
    {
        const char *v = std::getenv("GOW_SND_STUB");
        return v != nullptr && v[0] == '1';
    }();

    void gowSnd989SendCommand(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != 0x0026BF28u) // reanudacion tras un checkpoint dentro del original
        {
            sub_0026BF28_0x26bf28(rdram, ctx, runtime);
            return;
        }
        const uint32_t cmd = GPR_U32(ctx, 4);
        const uint32_t size = GPR_U32(ctx, 5);
        const uint32_t data = GPR_U32(ctx, 6);
        if (++g_sndCmdCount <= 300)
        {
            if (cmd == 0x68u)
            {
                const uint32_t a = readGuest32(rdram, data);
                const uint32_t b = readGuest32(rdram, data + 4u);
                const uint32_t len = readGuest32(rdram, data + 8u);
                const uint32_t ptr = readGuest32(rdram, data + 12u);
                std::fprintf(stderr, "[gow-snd] #%d cmd=0x68 (plugin) tamano=0x%x a=0x%x b=0x%x len=0x%x ptr=0x%x ra=0x%x\n",
                             g_sndCmdCount, size, a, b, len, ptr, GPR_U32(ctx, 31));
                dumpGuestBytes(rdram, ptr, (len < 0x80u) ? len : 0x80u);
            }
            else
            {
                std::fprintf(stderr, "[gow-snd] #%d cmd=0x%x tamano=0x%x datos=0x%x ra=0x%x\n",
                             g_sndCmdCount, cmd, size, data, GPR_U32(ctx, 31));
                dumpGuestBytes(rdram, data, (size < 0x40u) ? size : 0x40u);
            }
        }
        if (g_sndStub)
        {
            SET_GPR_U32(ctx, 2, 0u);
            ctx->pc = GPR_U32(ctx, 31);
            return;
        }
        const uint32_t ra = GPR_U32(ctx, 31);
        sub_0026BF28_0x26bf28(rdram, ctx, runtime);
        if (g_sndCmdCount <= 300 && ctx->pc == ra)
        {
            std::fprintf(stderr, "[gow-snd]   -> v0=0x%x\n", GPR_U32(ctx, 2));
            // Lectura de smpd (snd_DoExternCall 'SMPD' tipo 6: {.., destino@+0xC, tamano@+0x10, ..}): primeros bytes leidos
            if (cmd == 0x4Cu && readGuest32(rdram, data) == 0x534D5044u && readGuest32(rdram, data + 4u) == 6u)
            {
                const uint32_t dst = readGuest32(rdram, data + 12u);
                std::fprintf(stderr, "[gow-snd]   datos leidos en 0x%x:\n", dst);
                dumpGuestBytes(rdram, dst, 0x30u);
            }
        }
    }

    // sceSifLoadStartModuleBuffer(iopAddr, argLen, args, int *result) usado por el juego para cargar un
    // modulo IOP minimo embebido en el ELF ("ck01"). El runtime aun no puede ejecutar modulos cargados
    // desde memoria del IOP, asi que respondemos como una consola retail: el modulo se carga (id valido)
    // y termina con NO_RESIDENT_END (1), que es el valor con el que el juego continua normalmente.
    void gowLoadStartModuleBuffer(uint8_t *rdram, R5900Context *ctx, PS2Runtime *)
    {
        writeGuest32(rdram, GPR_U32(ctx, 7), 1u);
        SET_GPR_U32(ctx, 2, 0x40001000u);
        ctx->pc = GPR_U32(ctx, 31);
    }

    // smpd (SMPD_IOP.IRX) lee GODOFWAR.TOC / PART*.PAK por numero de sector con sceCdRead. Sin imagen de
    // disco, el IOP monta una ISO virtual con los archivos extraidos; con la ISO original los sectores son
    // exactamente los del DVD. Orden: variable GOW_ISO, "../God of War.iso" respecto al ELF, o el primer
    // .iso de la carpeta del ELF.
    void configureGowCdImage()
    {
        namespace fs = std::filesystem;
        PS2Runtime::IoPaths paths = PS2Runtime::getIoPaths();
        if (!paths.cdImage.empty())
            return;
        std::error_code ec;
        fs::path image;
#ifdef _WIN32
        // Windows environment variables are UTF-16; getenv's ANSI bytes are not UTF-8.
        if (const wchar_t *env = _wgetenv(L"GOW_ISO"); env != nullptr && env[0] != L'\0')
            image = fs::path(env);
#else
        if (const char *env = std::getenv("GOW_ISO"); env != nullptr && env[0] != '\0')
            image = fs::u8path(env);
#endif
        else if (!paths.elfDirectory.empty())
        {
            const fs::path sibling = paths.elfDirectory.parent_path() / "God of War.iso";
            if (fs::is_regular_file(sibling, ec))
                image = sibling;
            else
                for (const auto &entry : fs::directory_iterator(paths.elfDirectory, ec))
                    if (entry.is_regular_file(ec) && entry.path().extension() == ".iso")
                    {
                        image = entry.path();
                        break;
                    }
        }
        if (image.empty() || !fs::is_regular_file(image, ec))
        {
            std::fprintf(stderr, "[gow-cd] sin imagen de disco: el IOP usara la ISO virtual de la carpeta extraida\n");
            return;
        }
        paths.cdImage = image;
        PS2Runtime::setIoPaths(paths);
        const auto imageUtf8 = image.u8string();
        std::fprintf(stderr, "[gow-cd] imagen de disco: %s\n", reinterpret_cast<const char *>(imageUtf8.c_str()));
    }

    void applyGowOverrides(PS2Runtime &runtime)
    {
        configureGowCdImage();
        gow_gs_replay::configure(runtime.memory(),runtime.gs());
        // El heap interno del runtime va bajo el ELF (memoria libre) para no pisar el heap propio del juego,
        // que este crea con SetupHeap al final del .bss (patches/ps2recomp-heap.patch).
        runtime.setPrivateGuestHeap(0x000A0000u, 0x000FF000u);
        runtime.replaceFunction(0x00279600u, gowIpuInit);
        if (std::getenv("GOW_PATH_DIAG") || std::getenv("GOW_ANM_DIAG") || std::getenv("GOW_FAST_BOOT"))
        {
            runtime.replaceFunction(0x001B2390u, gowDiagFlashReady);
            runtime.replaceFunction(0x00100C50u, gowDiagAnimationTime);
            runtime.replaceFunction(0x00100BF0u, gowDiagAnimationDuration);
        }
        if (const char *skip = std::getenv("GOW_SKIP_FMV"); skip && std::strcmp(skip, "1") == 0)
        {
            runtime.replaceFunction(0x00188CA0u, gowSkipMovieLoad);
            runtime.replaceFunction(0x00188E80u, gowSkipMovieNoop);
            runtime.replaceFunction(0x00188ED8u, gowSkipMovieReady);
            runtime.replaceFunction(0x00188EF0u, gowSkipMovieReady);
            runtime.replaceFunction(0x00188F20u, gowSkipMovieNoop);
        }
        if (std::getenv("GOW_RENDER_DIAG"))
            for (const uint32_t address : {0x001262C8u, 0x00126310u, 0x0012633Cu, 0x00126368u,
                                           0x00126428u, 0x00126478u, 0x00126528u})
                runtime.replaceFunction(address, gowDiagFilteredCopy);
        if (const char *diag=std::getenv("GOW_EE_PRIM_DIAG"); diag && std::strcmp(diag,"1")==0)
        {
            runtime.replaceFunction(0x00141350u, gowDiagInitUnpack);
            runtime.replaceFunction(0x001417D8u, gowDiagUpdateAddress);
            runtime.replaceFunction(0x00141B78u, gowDiagPrimContext);
        }
        if (const char *diag = std::getenv("GOW_MODEL_DIAG"); diag && std::strcmp(diag, "1") == 0)
        {
            runtime.replaceFunction(0x00159C58u, gowDiagModelServer);
            runtime.replaceFunction(0x001511F0u, gowDiagGrobMaster);
            runtime.replaceFunction(0x00159878u, gowDiagModelContext);
            runtime.replaceFunction(0x00157A60u, gowDiagProcessModel);
            runtime.replaceFunction(0x00169120u, gowDiagModelClip);
        }
        runtime.replaceFunction(0x00180E50u, gowDiagPathSelect);
        runtime.replaceFunction(0x00180D08u, gowDiagAttachNode);
        runtime.replaceFunction(0x0027B7E8u, gowPad2Init);
        runtime.replaceFunction(0x0027B828u, gowPad2Init);
        runtime.replaceFunction(0x0027B890u, gowPad2CreateSocket);
        runtime.replaceFunction(0x0027B998u, gowPad2DeleteSocket);
        runtime.replaceFunction(0x0027B9F0u, gowPad2Read);
        runtime.replaceFunction(0x0027BAC8u, gowPad2GetButtonProfile);
        runtime.replaceFunction(0x0027BB98u, gowPad2GetState);
        runtime.replaceFunction(0x0027BF90u, gowVibGetProfile);
        // El recompilador descarta estas dos funciones porque empiezan en el delay slot
        // de un "jr ra" suelto de la funcion anterior.
        const bool a = ps2_game_overrides::bindAddressHandler(runtime, 0x00296C48u, "sceSifInitRpc");
        const bool b = ps2_game_overrides::bindAddressHandler(runtime, 0x00294990u, "iWakeupThread");
        // Sin handler en el runtime: la version original espera al CDVD del IOP para siempre.
        const bool c = runtime.replaceFunction(0x0027AB00u, gowCdReadDvdDualInfo);
        const bool d = runtime.replaceFunction(0x0026BF28u, gowSnd989SendCommand);
        const bool e = runtime.replaceFunction(0x00298CE8u, gowLoadStartModuleBuffer);
        std::fprintf(stderr, "[gow-override] sceSifInitRpc=%d iWakeupThread=%d sceCdReadDvdDualInfo=%d snd989=%d modbuf=%d\n",
                     a, b, c, d, e);
    }
}

PS2_REGISTER_GAME_OVERRIDE("God of War (SCUS-97399)", "SCUS_973.99", 0x00100008u, 0u, applyGowOverrides)
