// GOW-Port: diagnósticos del GS instalados desde el runtime (sin las variables no hacen nada).
//
// - GOW_GS_REPLAY_TRACE: captura de comandos del GS (src/gow_gs_replay.h en la raíz del repositorio). En el árbol de
//   PS2Recomp la copia de runner/gow_overrides.cpp no la instala. Solo graba en el estado 11 (partida).
// - GOW_TEXTURAS="inicio:duracion:carpeta": cada textura distinta que se dibuja en ese tramo, en cualquier estado del
//   juego (menús incluidos), decodificada en el momento del dibujo con su CLUT y TEXA: el juego reutiliza la misma
//   zona de VRAM para varias texturas dentro de un cuadro, así que la clave es TEX0 más una huella de 32 x 32 texels,
//   calculada en el primer dibujo de cada TEX0 en cada cuadro. Escribe <carpeta>/tex_NNN.png, tex_NNN_<an>x<al>.idx
//   (índices crudos de las indexadas) e indice.txt (TEX0 y el primer dibujo: rectángulo de pantalla y UV). Necesita
//   el backend CPU sin hilo (PS2X_GS_GPU=0 PS2X_GS_THREAD=0) para leer la VRAM barato. Solo local: las imágenes son
//   datos del juego y nunca se suben.
#include "ps2_runtime.h"
#include "gow_gs_replay.h"
#include "gs/gs_decodificar_textura.h"
#include "raylib.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace
{
    class Texturas final : public GSRasterBackend, public GSBackendStateAccess
    {
    public:
        Texturas(std::unique_ptr<GSRasterBackend> inner, double inicio, double duracion, std::filesystem::path carpeta)
            : m_inner(std::move(inner)), m_inicio(inicio), m_fin(inicio + duracion), m_carpeta(std::move(carpeta))
        {
        }

        void Initialize(uint8_t *p, uint32_t n) override { m_inner->Initialize(p, n); }
        void Reset() override { m_inner->Reset(); }
        void Submit(const GSPrimitiveBatch &b) override
        {
            if (activo())
            {
                ++m_tipos[std::make_tuple(int(b.state.prim.type), int(b.state.prim.tme), int(b.state.context.tex0.psm), int(b.state.prim.fst))];
                if (b.state.prim.tme && !m_soloTipos)
                    anotar(b);
            }
            m_inner->Submit(b);
        }
        void LoadClut(const GSTex0Reg &a, const GSTexClutReg &b) override { m_inner->LoadClut(a, b); }
        void BeginTransfer(const GSTransferCommand &v) override { m_inner->BeginTransfer(v); }
        void UploadImage(const uint8_t *p, uint32_t n) override { m_inner->UploadImage(p, n); }
        void Flush() override { m_inner->Flush(); }
        void TextureFlush() override { m_inner->TextureFlush(); }
        void Sync(GSSyncReason v) override { m_inner->Sync(v); }
        PresentationFrame Present(const GSPresentationRequest &v) override
        {
            ++m_cuadro;
            if (m_estado == 1 && segundos() > m_fin)
                terminar();
            return m_inner->Present(v);
        }
        bool ClearFramebuffer(const GSContext &c, uint32_t rgba) override { return m_inner->ClearFramebuffer(c, rgba); }
        uint32_t ConsumeLocalToHostBytes(uint8_t *p, uint32_t n) override { return m_inner->ConsumeLocalToHostBytes(p, n); }
        uint32_t ReadVram(uint32_t p, uint32_t b, uint32_t w, uint32_t x, uint32_t y) const override { return m_inner->ReadVram(p, b, w, x, y); }
        void WriteVram(uint32_t p, uint32_t b, uint32_t w, uint32_t x, uint32_t y, uint32_t v) override { m_inner->WriteVram(p, b, w, x, y, v); }
        void SnapshotVram(std::vector<uint8_t> &v) const override { m_inner->SnapshotVram(v); }
        GSTransferSnapshot GetTransferSnapshot() const override { return m_inner->GetTransferSnapshot(); }
        bool ExportState(GSBackendState &v) override
        {
            auto *a = dynamic_cast<GSBackendStateAccess *>(m_inner.get());
            return a && a->ExportState(v);
        }
        bool ImportState(const GSBackendState &v) override
        {
            auto *a = dynamic_cast<GSBackendStateAccess *>(m_inner.get());
            return a && a->ImportState(v);
        }

    private:
        struct Vista
        {
            int numero = 0;
            size_t dibujos = 0;
            std::string linea;
        };
        using Clave = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>;

        double segundos() const { return std::chrono::duration<double>(std::chrono::steady_clock::now() - m_arranque).count(); }

        bool activo()
        {
            if (m_estado == 0 && segundos() >= m_inicio)
            {
                m_estado = 1;
                std::filesystem::create_directories(m_carpeta);
                std::fprintf(stderr, "[gow-texturas] registrando texturas durante %.1f s\n", m_fin - m_inicio);
            }
            return m_estado == 1;
        }

        uint64_t huella(const GSTex0Reg &t) const
        {
            const uint32_t w = std::min(1u << t.tw, 1024u), h = std::min(1u << t.th, 1024u);
            uint64_t x = 1469598103934665603ull;
            for (uint32_t j = 0; j < 32u; ++j)
                for (uint32_t i = 0; i < 32u; ++i)
                    x = (x ^ m_inner->ReadVram(t.psm, t.tbp0, t.tbw, i * w / 32u, j * h / 32u)) * 1099511628211ull;
            return x;
        }

        void anotar(const GSPrimitiveBatch &b)
        {
            const GSTex0Reg &t = b.state.context.tex0;
            const Clave clave{t.tbp0, t.tbw, t.psm, t.tw, t.th, t.cbp, t.cpsm, t.csa, t.tcc};
            uint64_t &cuadro = m_cuadroVisto[clave];
            uint64_t &h = m_huellaCuadro[clave];
            if (cuadro != m_cuadro + 1u)
            {
                cuadro = m_cuadro + 1u;
                h = huella(t) ^ (uint64_t(t.cbp) << 32) ^ (uint64_t(t.csa) << 48);
            }
            Vista &v = m_vistas[std::make_pair(clave, h)];
            ++v.dibujos;
            if (v.numero != 0)
                return;
            v.numero = int(m_vistas.size());
            GSBackendState estado;
            ExportState(estado);
            uint32_t w = 0, al = 0;
            std::vector<uint32_t> px = GSDecodificar::imagen(*m_inner, t, estado.clut, b.state.texa, w, al);
            char nombre[64];
            std::snprintf(nombre, sizeof(nombre), "tex_%03d.png", v.numero);
            Image img{px.data(), int(w), int(al), 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
            ExportImage(img, (m_carpeta / nombre).string().c_str());
            if (GSDecodificar::indexado(t.psm))
            {
                std::snprintf(nombre, sizeof(nombre), "tex_%03d_%ux%u.idx", v.numero, w, al);
                std::ofstream f(m_carpeta / nombre, std::ios::binary);
                for (uint32_t y = 0; y < al; ++y)
                    for (uint32_t x = 0; x < w; ++x)
                        f.put(char(m_inner->ReadVram(t.psm, t.tbp0, t.tbw, x, y)));
            }
            const auto &a = b.vertices[0];
            const auto &c = b.vertices[b.vertexCount > 1 ? b.vertexCount - 1 : 0];
            char ej[200];
            if (b.state.prim.fst)
                std::snprintf(ej, sizeof(ej), "tipo=%d xy=%.1f,%.1f-%.1f,%.1f uv=%.1f,%.1f-%.1f,%.1f", int(b.state.prim.type), a.x, a.y, c.x, c.y,
                              a.u / 16.0, a.v / 16.0, c.u / 16.0, c.v / 16.0);
            else
                std::snprintf(ej, sizeof(ej), "tipo=%d xy=%.1f,%.1f-%.1f,%.1f st=%.3f,%.3f-%.3f,%.3f", int(b.state.prim.type), a.x, a.y, c.x, c.y,
                              a.s / a.q, a.t / a.q, c.s / c.q, c.t / c.q);
            char l[420];
            std::snprintf(l, sizeof(l), "tex_%03d t=%.2f tbp0=0x%X tbw=%u psm=0x%X %ux%u cbp=0x%X cpsm=%u csm=%u csa=%u tcc=%u %s", v.numero,
                          segundos(), t.tbp0, t.tbw, t.psm, 1u << t.tw, 1u << t.th, t.cbp, t.cpsm, t.csm, t.csa, t.tcc, ej);
            v.linea = l;
        }

        void terminar()
        {
            m_estado = 2;
            std::ofstream indice(m_carpeta / "indice.txt");
            std::vector<const Vista *> orden;
            for (const auto &[k, v] : m_vistas)
                orden.push_back(&v);
            std::sort(orden.begin(), orden.end(), [](const Vista *a, const Vista *b) { return a->numero < b->numero; });
            for (const Vista *v : orden)
                indice << v->linea << " dibujos=" << v->dibujos << '\n';
            for (const auto &[k, n] : m_tipos)
                indice << "# tipo=" << std::get<0>(k) << " tme=" << std::get<1>(k) << " psm=0x" << std::hex << std::get<2>(k) << std::dec
                       << " fst=" << std::get<3>(k) << " dibujos=" << n << '\n';
            std::fprintf(stderr, "[gow-texturas] %zu texturas en %s\n", m_vistas.size(), m_carpeta.string().c_str());
        }

        std::unique_ptr<GSRasterBackend> m_inner;
        double m_inicio, m_fin;
        std::filesystem::path m_carpeta;
        int m_estado = 0; // 0 esperando, 1 registrando, 2 terminado
        std::map<std::pair<Clave, uint64_t>, Vista> m_vistas;
        std::map<Clave, uint64_t> m_cuadroVisto, m_huellaCuadro;
        uint64_t m_cuadro = 0u;
        std::map<std::tuple<int, int, int, int>, size_t> m_tipos;
        // GOW_TEXTURAS_SOLO_TIPOS=1: solo cuenta los dibujos por tipo (sirve con el backend de GPU).
        const bool m_soloTipos = [] { const char *v = std::getenv("GOW_TEXTURAS_SOLO_TIPOS"); return v && v[0] == '1'; }();
        const std::chrono::steady_clock::time_point m_arranque = std::chrono::steady_clock::now();
    };
}

void gowCapturaGsInstalar(PS2Runtime &runtime)
{
    if (const char *v = std::getenv("GOW_GS_REPLAY_TRACE"); v && *v)
    {
        gow_gs_replay::configure(runtime.memory(), runtime.gs());
        return;
    }
    if (const char *v = std::getenv("GOW_TEXTURAS"))
    {
        double inicio = 0.0, duracion = 0.0;
        char carpeta[512] = {};
        if (std::sscanf(v, "%lf:%lf:%511[^\n]", &inicio, &duracion, carpeta) == 3 && duracion > 0.0)
        {
            runtime.gs().setRasterBackend(std::make_unique<Texturas>(GSThreadedBackend::MakeDefault(), inicio, duracion, carpeta));
            std::fprintf(stderr, "[gow-texturas] desde %.1f s durante %.1f s en %s\n", inicio, duracion, carpeta);
        }
    }
}
