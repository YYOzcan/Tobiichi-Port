// GOW-Port: sonda de funciones recompiladas (diagnóstico, solo con GOW_SONDEO).
//
// GOW_SONDEO="codigo_ini-codigo_fin:datos_ini-datos_fin:t:dur" envuelve cada función recompilada cuyo inicio está en
// [codigo_ini, codigo_fin) (hex). Durante [t, t+dur) segundos cuenta, por función, las llamadas en las que algún
// argumento ($a0-$a3, $t0-$t3) cae en [datos_ini, datos_fin) y guarda las primeras con sus argumentos. Al terminar
// escribe sondeo.txt. Sirve para encontrar qué funciones reciben un objeto concreto (p. ej. un símbolo de Flash).
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace
{
    constexpr size_t kMax = 2048u;
    struct Sonda
    {
        uint32_t inicio = 0u;
        PS2Runtime::RecompiledFunction original = nullptr;
        uint64_t llamadas = 0u, coincidencias = 0u;
        std::vector<std::string> ejemplos;
    };
    std::array<Sonda, kMax> g_sondas;
    size_t g_numSondas = 0u;
    uint32_t g_datosIni = 0u, g_datosFin = 0u;
    double g_t0 = 0.0, g_t1 = 0.0;
    bool g_escrito = false;
    const auto g_arranque = std::chrono::steady_clock::now();

    double segundos() { return std::chrono::duration<double>(std::chrono::steady_clock::now() - g_arranque).count(); }

    void escribir()
    {
        g_escrito = true;
        std::vector<const Sonda *> v;
        for (size_t i = 0; i < g_numSondas; ++i)
            if (g_sondas[i].coincidencias)
                v.push_back(&g_sondas[i]);
        std::sort(v.begin(), v.end(), [](const Sonda *a, const Sonda *b) { return a->coincidencias > b->coincidencias; });
        if (std::FILE *f = std::fopen("sondeo.txt", "w"))
        {
            for (const Sonda *s : v)
            {
                std::fprintf(f, "0x%06X llamadas=%llu coincidencias=%llu\n", s->inicio, static_cast<unsigned long long>(s->llamadas),
                             static_cast<unsigned long long>(s->coincidencias));
                for (const std::string &e : s->ejemplos)
                    std::fprintf(f, "    %s\n", e.c_str());
            }
            std::fclose(f);
        }
        std::fprintf(stderr, "[gow-sondeo] %zu funciones con coincidencias en sondeo.txt\n", v.size());
    }

    template <size_t I>
    void envoltorio(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        Sonda &s = g_sondas[I];
        if (ctx->pc == s.inicio && !g_escrito)
        {
            const double t = segundos();
            if (t >= g_t0 && t < g_t1)
            {
                ++s.llamadas;
                const uint32_t regs[8] = {GPR_U32(ctx, 4), GPR_U32(ctx, 5), GPR_U32(ctx, 6), GPR_U32(ctx, 7),
                                          GPR_U32(ctx, 8), GPR_U32(ctx, 9), GPR_U32(ctx, 10), GPR_U32(ctx, 11)};
                bool hay = false;
                for (uint32_t r : regs)
                    hay |= (r & 0x1FFFFFFFu) >= g_datosIni && (r & 0x1FFFFFFFu) < g_datosFin;
                if (hay)
                {
                    ++s.coincidencias;
                    if (s.ejemplos.size() < 6u)
                    {
                        char b[200];
                        std::snprintf(b, sizeof(b), "t=%.2f ra=%06X a0=%08X a1=%08X a2=%08X a3=%08X t0=%08X t1=%08X t2=%08X t3=%08X", t,
                                      GPR_U32(ctx, 31), regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]);
                        s.ejemplos.emplace_back(b);
                    }
                }
            }
            else if (t >= g_t1)
                escribir();
        }
        s.original(rdram, ctx, runtime);
    }

    template <size_t... I>
    constexpr std::array<PS2Runtime::RecompiledFunction, sizeof...(I)> tabla(std::index_sequence<I...>)
    {
        return {&envoltorio<I>...};
    }
    const auto g_envoltorios = tabla(std::make_index_sequence<kMax>{});
}

void gowSondeoInstalar(PS2Runtime &runtime)
{
    const char *v = std::getenv("GOW_SONDEO");
    if (!v)
        return;
    unsigned ci = 0, cf = 0, di = 0, df = 0;
    double t = 0.0, dur = 0.0;
    if (std::sscanf(v, "%x-%x:%x-%x:%lf:%lf", &ci, &cf, &di, &df, &t, &dur) != 6)
        return;
    g_datosIni = di;
    g_datosFin = df;
    g_t0 = t;
    g_t1 = t + dur;
    // Inicio de cada función: la primera dirección del rango que la tabla resuelve a un puntero nuevo (las entradas de
    // reanudación de la misma función devuelven el mismo puntero).
    std::map<PS2Runtime::RecompiledFunction, uint32_t> vistas;
    for (uint32_t a = ci; a < cf && g_numSondas < kMax; a += 4u)
    {
        if (!runtime.hasFunction(a))
            continue;
        PS2Runtime::RecompiledFunction f = runtime.lookupFunction(a);
        if (!f || vistas.count(f))
            continue;
        vistas[f] = a;
        Sonda &s = g_sondas[g_numSondas];
        s.inicio = a;
        s.original = f;
        runtime.replaceFunction(a, g_envoltorios[g_numSondas]);
        ++g_numSondas;
    }
    std::fprintf(stderr, "[gow-sondeo] %zu funciones en 0x%X-0x%X; datos 0x%X-0x%X; t=%.1f+%.1f\n", g_numSondas, ci, cf, di, df, t, dur);
}
