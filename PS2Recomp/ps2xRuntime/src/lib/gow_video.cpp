// GOW-Port: modo de vídeo de God of War (SCUS-97399).
//
// La opción "Progressive Scan" del menú de pausa (480p) quita el doblado de líneas y el antiparpadeo del modo
// entrelazado: la imagen es mucho más nítida. Aquí queda siempre activada (GOW_PROGRESIVO=0 vuelve al ajuste del
// juego).
//
// - Ajustes: func_1B5D70 los registra por nombre ("WideScreen" +0x29C, "ProgressiveScan" +0x2A0, "DeFlicker" +0x2A4
//   sobre el objeto 0x29C9F4). El valor de "ProgressiveScan" vive en 0x29CC94; el menú lo cambia con
//   func_1B5870 -> func_1B5B20.
// - func_21FDA0 (cada cuadro, desde 0x17A2A0) compara 0x29CC94 con el modo aplicado (0x29E610) y, si cambió, elige
//   el descriptor 0x2FD938 (progresivo) o 0x2FD900 (entrelazado) y llama a func_1830D8, que reprograma el GS
//   (sceGsResetGraph y registros de pantalla).
// Escribir 1 en 0x29CC94 antes de esa comprobación hace que el juego cambie de modo por su propio camino. Si el
// jugador desactiva la opción en el menú, en el cuadro siguiente vuelve a quedar activada.
#include "ps2_runtime.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

namespace
{
    constexpr uint32_t kComprobarModo = 0x21FDA0u; // aplica el modo de vídeo elegido si cambió
    constexpr uint32_t kProgresivo = 0x29CC94u;    // ajuste "ProgressiveScan"

    PS2Runtime::RecompiledFunction g_comprobarModo = nullptr;

    void comprobarModo(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        // Solo en la entrada; una reanudación tras un punto de control sigue el original sin más.
        if (ctx->pc == kComprobarModo)
        {
            const uint32_t uno = 1u;
            std::memcpy(rdram + kProgresivo, &uno, sizeof(uno));
        }
        g_comprobarModo(rdram, ctx, runtime);
    }
}

void gowVideoInstalar(PS2Runtime &runtime, const std::string &elfPath)
{
    if (std::filesystem::path(elfPath).filename() != "SCUS_973.99")
        return;
    const char *valor = std::getenv("GOW_PROGRESIVO");
    if (valor && valor[0] == '0')
        return;
    if (!runtime.hasFunction(kComprobarModo))
        return;
    g_comprobarModo = runtime.lookupFunction(kComprobarModo);
    runtime.replaceFunction(kComprobarModo, &comprobarModo);
    std::cerr << "[gow-video] escaneo progresivo (480p) siempre activado" << std::endl;
}
