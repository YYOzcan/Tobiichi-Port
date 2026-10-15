// GOW-Port: vídeos (FMV) de God of War (SCUS-97399). Reproductor del juego (0x189BD0 abre, 0x18AC20 lee y separa el
// vídeo del PSS, 0x188848 es su lectura asíncrona de archivo, 0x18A170 pide cada cuadro). GOW_FMV_DIAG=1 registra
// lo que devuelven, para depurar la reproducción.
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "Kernel/Stubs/MPEG.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <deque>
#include <iostream>
#include <mutex>
#include <string>

namespace
{
    constexpr uint32_t kAbrir = 0x00189BD0u;
    constexpr uint32_t kLeer = 0x0018AC20u;
    constexpr uint32_t kLeerArchivo = 0x00188848u;
    constexpr uint32_t kPelicula = 0x00304F20u; // puntero al objeto del vídeo
    // sceMpegIsEnd de la libmpeg del juego: devuelve *(mp->sys + 0), que solo escribe el decodificador original. Con
    // el decodificador HLE quedaba siempre a 0 y el juego (0x189B00 / 0x18A298) esperaba cuadros para siempre al
    // terminar el vídeo: pantalla negra con el EE ocupado.
    constexpr uint32_t kMpegIsEnd = 0x0026FF70u;
    constexpr uint32_t kCbAudio = 0x0018A8F8u; // callback de flujo de audio (sceMpegAddStrCallback, 0x18A6A8)
    constexpr uint32_t kConsumirAudio = 0x00189A88u; // anillo de audio del vídeo -> IOP (0x188380)

    constexpr uint32_t kPeliculaActiva = 0x0029C838u; // distinto de 0 mientras se reproduce un vídeo (ver gowSkipMovieLoad)
    std::atomic<bool> g_esGow{false};

    // Cola en el host delante del anillo de audio del vídeo (ver cbAudio).
    struct ColaAudio
    {
        std::deque<uint8_t> bytes;
        uint64_t recibidos = 0, maximo = 0;
    };
    ColaAudio g_colaAudio;
    std::mutex g_colaAudioMutex; // el EE es el único que la usa; el mutex solo protege de reentradas raras

    PS2Runtime::RecompiledFunction g_abrir = nullptr;
    PS2Runtime::RecompiledFunction g_leer = nullptr;
    PS2Runtime::RecompiledFunction g_leerArchivo = nullptr;
    PS2Runtime::RecompiledFunction g_cbAudio = nullptr;
    PS2Runtime::RecompiledFunction g_consumirAudio = nullptr;

    uint32_t leer32(const uint8_t *rdram, uint32_t direccion)
    {
        uint32_t valor = 0u;
        direccion &= 0x01FFFFFFu;
        if (direccion + 4u <= PS2_RAM_SIZE)
            std::memcpy(&valor, rdram + direccion, 4u);
        return valor;
    }

    bool diag()
    {
        static const bool activo = []
        {
            const char *v = std::getenv("GOW_FMV_DIAG");
            return v && v[0] == '1';
        }();
        return activo;
    }

    void estado(const char *donde, uint8_t *rdram, R5900Context *ctx)
    {
        static std::atomic<unsigned> mensajes{0};
        if (mensajes.fetch_add(1) >= 300u)
            return;
        const uint32_t obj = leer32(rdram, kPelicula);
        std::fprintf(stderr, "[fmv] %s v0=%d pc=0x%x obj=0x%x 4c=%d 58=%u 5c=%u 140=%u 154=%u f8=0x%x\n", donde,
                     static_cast<int32_t>(GPR_U32(ctx, 2)), ctx->pc, obj, static_cast<int32_t>(leer32(rdram, obj + 0x4Cu)),
                     leer32(rdram, obj + 0x58u), leer32(rdram, obj + 0x5Cu), leer32(rdram, obj + 0x140u),
                     leer32(rdram, obj + 0x154u), leer32(rdram, obj + 0xF8u));
    }

    void abrir(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool entrada = ctx->pc == kAbrir;
        if (entrada)
        {
            std::lock_guard<std::mutex> lock(g_colaAudioMutex);
            g_colaAudio = ColaAudio{}; // vídeo nuevo: nada pendiente del anterior
        }
        g_abrir(rdram, ctx, runtime);
        if (entrada && diag())
            estado("abrir", rdram, ctx);
    }

    void leer(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool entrada = ctx->pc == kLeer;
        const uint32_t bloqueante = GPR_U32(ctx, 4);
        g_leer(rdram, ctx, runtime);
        if (entrada && diag() && bloqueante)
        {
            estado("leer(bloqueante)", rdram, ctx);
            const uint32_t obj = leer32(rdram, kPelicula);
            for (uint32_t campo : {0xF8u, 0x48u})
            {
                const uint32_t a = leer32(rdram, obj + campo) & 0x01FFFFFFu;
                if (a + 16u > PS2_RAM_SIZE)
                    continue;
                std::fprintf(stderr, "[fmv]   +0x%x -> 0x%x:", campo, a);
                for (uint32_t i = 0; i < 16u; ++i)
                    std::fprintf(stderr, " %02x", rdram[a + i]);
                std::fprintf(stderr, "\n");
            }
        }
    }

    void leerArchivo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const bool entrada = ctx->pc == kLeerArchivo;
        g_leerArchivo(rdram, ctx, runtime);
        static std::atomic<unsigned> mensajes{0};
        if (entrada && diag() && mensajes.fetch_add(1) < 60u)
            std::fprintf(stderr, "[fmv] leerArchivo v0=%d\n", static_cast<int32_t>(GPR_U32(ctx, 2)));
    }

    // GOW-Port: audio de los vídeos sin pérdidas. El callback de flujo de audio del juego (0x18A8F8) copia la cabecera
    // SShd/SSbd (40 bytes) a obj+0x10C y el resto al anillo obj+0xFC (tamaño +0x100, lectura +0x104, ocupado +0x108); si
    // no cabe, marca obj+0x134 y devuelve 0. libmpeg para entonces el demux y vuelve a entregar el paquete más tarde,
    // pero el demux HLE ya lo ha consumido: el paquete se perdía. Aquí se reimplementa ese callback con una cola en el
    // host delante del anillo: lo que no cabe espera y entra cuando el juego consume (0x189A88, cada cuadro). Así el
    // vídeo puede ir decodificado por delante sin dejar el audio sin datos ni perderlo.

    void escribir32(uint8_t *rdram, uint32_t direccion, uint32_t valor)
    {
        direccion &= 0x01FFFFFFu;
        if (direccion + 4u <= PS2_RAM_SIZE)
            std::memcpy(rdram + direccion, &valor, 4u);
    }

    // Pasa al anillo del juego todo lo que quepa de la cola.
    void rellenarAnillo(uint8_t *rdram)
    {
        const uint32_t obj = leer32(rdram, kPelicula) & 0x01FFFFFFu;
        if (obj == 0u || obj + 0x150u > PS2_RAM_SIZE)
            return;
        const uint32_t anillo = leer32(rdram, obj + 0xFCu) & 0x01FFFFFFu;
        const uint32_t tam = leer32(rdram, obj + 0x100u);
        const uint32_t lectura = leer32(rdram, obj + 0x104u);
        uint32_t ocupado = leer32(rdram, obj + 0x108u);
        if (anillo == 0u || tam == 0u || ocupado > tam || anillo + tam > PS2_RAM_SIZE)
            return;
        std::lock_guard<std::mutex> lock(g_colaAudioMutex);
        uint32_t n = static_cast<uint32_t>(std::min<size_t>(tam - ocupado, g_colaAudio.bytes.size()));
        uint32_t pos = (lectura + ocupado) % tam;
        while (n > 0u)
        {
            const uint32_t tramo = std::min(n, tam - pos);
            std::copy_n(g_colaAudio.bytes.begin(), tramo, rdram + anillo + pos);
            g_colaAudio.bytes.erase(g_colaAudio.bytes.begin(), g_colaAudio.bytes.begin() + tramo);
            ocupado += tramo;
            pos = (pos + tramo) % tam;
            n -= tramo;
        }
        escribir32(rdram, obj + 0x108u, ocupado);
        escribir32(rdram, obj + 0x134u, 0u);
    }

    void cbAudio(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc != kCbAudio) // reanudación tras un checkpoint: el original
        {
            g_cbAudio(rdram, ctx, runtime);
            return;
        }
        const uint32_t obj = leer32(rdram, kPelicula) & 0x01FFFFFFu;
        const uint32_t datos = GPR_U32(ctx, 5) & 0x01FFFFFFu;
        uint32_t ptr = leer32(rdram, datos + 0x8u) & 0x01FFFFFFu;
        uint32_t largo = leer32(rdram, datos + 0xCu);
        if (obj == 0u || largo < 4u || ptr + largo > PS2_RAM_SIZE || obj + 0x150u > PS2_RAM_SIZE)
        {
            g_cbAudio(rdram, ctx, runtime);
            return;
        }
        // Como el original: se saltan los 4 bytes de subflujo y, salvo en el tipo 3, los 40 primeros van a la cabecera.
        ptr += 4u;
        largo -= 4u;
        escribir32(rdram, datos + 0x8u, ptr);
        escribir32(rdram, datos + 0xCu, largo);
        if (leer32(rdram, obj + 0x144u) != 3u)
        {
            uint32_t cabecera = leer32(rdram, obj + 0x138u);
            if (cabecera < 0x28u)
            {
                const uint32_t n = std::min(0x28u - cabecera, largo);
                std::memcpy(rdram + obj + 0x10Cu + cabecera, rdram + ptr, n);
                cabecera += n;
                ptr += n;
                largo -= n;
                escribir32(rdram, obj + 0x138u, cabecera);
            }
        }
        static std::FILE *referencia = [] // GOW_FMV_AUDIO_REF=<archivo>: el audio que recibe el juego
        {
            const char *v = std::getenv("GOW_FMV_AUDIO_REF");
            return v && v[0] ? std::fopen(v, "wb") : nullptr;
        }();
        if (referencia)
            std::fwrite(rdram + ptr, 1, largo, referencia);
        {
            std::lock_guard<std::mutex> lock(g_colaAudioMutex);
            g_colaAudio.bytes.insert(g_colaAudio.bytes.end(), rdram + ptr, rdram + ptr + largo);
            g_colaAudio.recibidos += largo;
            g_colaAudio.maximo = std::max<uint64_t>(g_colaAudio.maximo, g_colaAudio.bytes.size());
        }
        rellenarAnillo(rdram);
        static std::atomic<unsigned> llamadas{0};
        const unsigned n = llamadas.fetch_add(1);
        if (diag() && (n < 4u || n % 500u == 499u))
        {
            std::lock_guard<std::mutex> lock(g_colaAudioMutex);
            std::fprintf(stderr, "[fmv-audio] paquete %u: recibidos=%llu en cola=%zu (máx %llu) anillo %u/%u\n", n,
                         static_cast<unsigned long long>(g_colaAudio.recibidos), g_colaAudio.bytes.size(),
                         static_cast<unsigned long long>(g_colaAudio.maximo), leer32(rdram, obj + 0x108u),
                         leer32(rdram, obj + 0x100u));
        }
        SET_GPR_U32(ctx, 2, 1u); // aceptado, como el original cuando cabe
        ctx->pc = GPR_U32(ctx, 31);
    }

    // 0x189A88: el reproductor pasa audio del anillo al IOP (una vez por cuadro). Antes se rellena desde la cola.
    void consumirAudio(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (ctx->pc == kConsumirAudio)
            rellenarAnillo(rdram);
        g_consumirAudio(rdram, ctx, runtime);
    }

    void finVideo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        ps2_stubs::sceMpegIsEnd(rdram, ctx, runtime);
        if (diag())
        {
            static int32_t anterior = -1;
            const int32_t fin = static_cast<int32_t>(GPR_U32(ctx, 2));
            if (fin != anterior)
                std::fprintf(stderr, "[fmv] sceMpegIsEnd=%d ra=0x%x\n", fin, GPR_U32(ctx, 31));
            anterior = fin;
        }
    }

    void envolver(PS2Runtime &runtime, uint32_t direccion, PS2Runtime::RecompiledFunction &original,
                  PS2Runtime::RecompiledFunction nueva)
    {
        if (!runtime.hasFunction(direccion))
            return;
        original = runtime.lookupFunction(direccion);
        runtime.replaceFunction(direccion, nueva);
    }
}

// Hilo principal: ¿hay un vídeo del juego en curso? (la ventana muestra entonces el cuadro decodificado).
bool gowPeliculaEnPantalla(const uint8_t *rdram)
{
    return g_esGow.load(std::memory_order_relaxed) && rdram && leer32(rdram, kPeliculaActiva) != 0u;
}

void gowPeliculasInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99")
        return;
    g_esGow.store(true);
    if (runtime.hasFunction(kMpegIsEnd))
        runtime.replaceFunction(kMpegIsEnd, &finVideo);
    envolver(runtime, kAbrir, g_abrir, &abrir);
    envolver(runtime, kCbAudio, g_cbAudio, &cbAudio);
    envolver(runtime, kConsumirAudio, g_consumirAudio, &consumirAudio);
    if (!diag())
        return;
    envolver(runtime, kLeer, g_leer, &leer);
    envolver(runtime, kLeerArchivo, g_leerArchivo, &leerArchivo);
    std::cerr << "[fmv] diagnóstico del reproductor activo" << std::endl;
}
