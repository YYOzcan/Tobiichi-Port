// GOW-Port: renderizador por hardware de triángulos (PS2X_GS_HW=1). Ver docs/RENDERIZADO.md, "Renderizador por
// hardware".
//
// La ruta software del backend OpenGL emula el GS píxel a píxel sobre la VRAM (un plano por muestra con resolución
// interna). Aquí los triángulos que se pueden expresar con el pipeline de la GPU se dibujan en texturas de color y
// profundidad a la resolución interna, con la mezcla, el Z y el muestreo de la GPU. Los planos de VRAM siguen siendo la
// referencia: un objetivo se carga desde ellos antes de dibujar y se vuelca a ellos antes de cualquier operación de la
// ruta software que lea o escriba sus páginas.
#pragma once

#include "gs_gl.h"
#include "runtime/gs/gs_types.h"

#include <bitset>
#include <cstdint>
#include <memory>
#include <string>

namespace GSHw
{
    constexpr size_t kPaginas = 512u;
    using Paginas = std::bitset<kPaginas>;

    // VRAM del backend: un búfer con S×S planos de planoBytes cada uno (el plano 0 es el GS nativo).
    struct Vram
    {
        GSGL::GLuint buffer = 0u;
        size_t planoBytes = 0u;
        uint32_t escala = 1u;
    };

    struct Estadisticas
    {
        uint64_t aceptados = 0u;
        uint64_t rechazados = 0u;
        uint64_t dibujos = 0u;
        uint64_t cargas = 0u;
        uint64_t volcados = 0u;
        uint64_t texturas = 0u;
        uint64_t aciertos = 0u;
        uint64_t motivo[16] = {};
    };

    // Páginas de VRAM (8 KB) que ocupa un rectángulo en un formato (base en bloques de 256 bytes, bw en 64 píxeles).
    void marcarPaginas(Paginas &paginas, uint32_t psm, uint32_t base, uint32_t bw, int x0, int y0, int x1, int y1);

    class Renderizador
    {
    public:
        Renderizador();
        ~Renderizador();
        Renderizador(const Renderizador &) = delete;
        Renderizador &operator=(const Renderizador &) = delete;

        // prefijo: "#version" y las definiciones de las tablas de swizzle (con el contexto GL actual).
        bool iniciar(const GSGL::Api &gl, const std::string &prefijo);
        // Sin tocar la GPU: 0 si el triángulo se puede dibujar aquí; si no, el motivo (estadísticas).
        uint32_t admite(const GSPrimitiveBatch &batch) const;
        // Dibuja (o acumula) un triángulo admitido. clutSlot: la CLUT del backend, ya cargada en la GPU.
        void dibujar(const GSPrimitiveBatch &batch, const Vram &vram, uint32_t clutSlot);
        // Antes de una operación de la ruta software que lee o escribe estas páginas: emite los dibujos acumulados y
        // vuelca los objetivos con cambios en ellas.
        // origen: quién lo pide, para el diagnóstico (1 dibujo, 2 CLUT, 3 transferencia, 4 borrado, 5 píxel...).
        void antesDeSoftware(const Paginas &toca, const Vram &vram, uint32_t origen = 0u);
        // La ruta software escribió estas páginas: los objetivos y texturas que las usan se recargan.
        void escrito(const Paginas &paginas);
        // Carga de CLUT en el backend (clave de la carga, páginas de origen, si conserva parte de la anterior).
        void cargaClut(uint64_t clave, const Paginas &fuente, bool parcial);
        // Emite y vuelca todo (presentación, lecturas, sincronización).
        void volcarTodo(const Vram &vram, uint32_t origen = 0u);
        // Tras volcarTodo: olvida los objetivos (cambio de escala, reinicio de la VRAM).
        void descartarTodo();
        void rechazado(uint32_t motivo);
        void rechazadoDetalle(uint32_t motivo, const GSPrimitiveBatch &batch);
        void informe();

    private:
        struct Impl;
        std::unique_ptr<Impl> m;
    };
}
