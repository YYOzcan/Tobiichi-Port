// GOW-Port: extrae las texturas que usa un tramo capturado del GS (GOW_GS_REPLAY_TRACE) a PNG.
//
// Uso: texturas_gs <captura.bin> <carpeta> [--sprites]
// Repite la captura en el backend CPU y, antes de cada primitiva texturizada, decodifica la textura (con su CLUT y TEXA
// del momento) la primera vez que aparece cada combinación TEX0. Escribe <carpeta>/tex_NNN.png y <carpeta>/indice.txt
// (una línea por textura: TEX0, tamaño, número de dibujos y el rectángulo de pantalla y UV del primero de cada tipo).
// Las indexadas también dejan tex_NNN_<an>x<al>.idx con un byte de índice por texel.
// Con --sprites solo cuenta los sprites (los iconos y el texto de la interfaz son sprites).
// Solo para uso local: las imágenes salen de los datos del juego y nunca se suben.
#include "gow_gs_replay.h"
#include "gs_decodificar_textura.h"
#include "raylib.h"
#include "runtime/gs/gs_cpu_backend.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <tuple>

namespace replay = gow_gs_replay;
namespace
{
    bool aplicar(GSRasterBackend &b, const replay::Record &r)
    {
        using replay::Op;
        GSPrimitiveBatch batch{};
        replay::Clut clut{};
        GSTransferCommand transfer{};
        replay::Clear clear{};
        replay::Pixel pixel{};
        GSPresentationRequest present{};
        GSSyncReason sync{};
        uint32_t csr = 0;
        switch (r.op)
        {
        case Op::Submit: if (!replay::pod(r, batch) || batch.vertexCount > 3) return false; b.Submit(batch); break;
        case Op::Clut: if (!replay::pod(r, clut)) return false; b.LoadClut(clut.tex0, clut.texclut); break;
        case Op::Transfer: if (!replay::pod(r, transfer)) return false; b.BeginTransfer(transfer); break;
        case Op::Upload: b.UploadImage(r.data.data(), uint32_t(r.data.size())); break;
        case Op::TextureFlush: b.TextureFlush(); break;
        case Op::Flush: b.Flush(); break;
        case Op::Reset: b.Reset(); break;
        case Op::Sync: if (!replay::pod(r, sync)) return false; b.Sync(sync); break;
        case Op::Present: if (!replay::pod(r, present)) return false; (void)b.Present(present); break;
        case Op::Clear: if (!replay::pod(r, clear)) return false; b.ClearFramebuffer(clear.context, clear.rgba); break;
        case Op::Write: if (!replay::pod(r, pixel)) return false; b.WriteVram(pixel.psm, pixel.base, pixel.bw, pixel.x, pixel.y, pixel.value); break;
        case Op::Read: break;
        case Op::Mxcsr: if (!replay::pod(r, csr)) return false; break;
        case Op::Consume: break;
        default: return false;
        }
        return true;
    }

    struct Entrada
    {
        int numero = 0;
        size_t dibujos = 0;
        std::string ejemplo;
    };
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Uso: texturas_gs <captura.bin> <carpeta> [--sprites]\n";
        return 1;
    }
    const std::filesystem::path salida = argv[2];
    const bool soloSprites = argc > 3 && std::strcmp(argv[3], "--sprites") == 0;
    std::filesystem::create_directories(salida);
    SetTraceLogLevel(LOG_WARNING);

    replay::Reader lector(argv[1]);
    replay::Record registro;
    replay::Snapshot inicial;
    if (!lector.next(registro) || registro.op != replay::Op::Initial || !replay::decodeSnapshot(registro, inicial))
    {
        std::cerr << "Captura sin estado inicial\n";
        return 2;
    }
    std::vector<uint8_t> vram = inicial.vram;
    GSCpuBackend cpu;
    cpu.Initialize(vram.data(), uint32_t(vram.size()));
    if (!cpu.ImportState(inicial.state))
    {
        std::cerr << "No se pudo importar el estado inicial\n";
        return 2;
    }

    std::map<std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>, Entrada> vistas;
    size_t indice = 0;
    while (lector.next(registro))
    {
        ++indice;
        if (registro.op == replay::Op::End)
            break;
        GSPrimitiveBatch b{};
        if (registro.op == replay::Op::Submit && replay::pod(registro, b) && b.state.prim.tme &&
            (!soloSprites || b.state.prim.type == GS_PRIM_SPRITE))
        {
            const GSTex0Reg &t = b.state.context.tex0;
            const auto clave = std::make_tuple(t.tbp0, uint32_t(t.tbw), uint32_t(t.psm), uint32_t(t.tw), uint32_t(t.th),
                                               t.cbp, uint32_t(t.cpsm), uint32_t(t.csa), uint32_t(t.tcc));
            Entrada &e = vistas[clave];
            ++e.dibujos;
            if (e.numero == 0)
            {
                e.numero = int(vistas.size());
                cpu.Sync(GSSyncReason::DebugReadback);
                GSBackendState estado;
                cpu.ExportState(estado);
                uint32_t w = 0, h = 0;
                std::vector<uint32_t> px = GSDecodificar::imagen(cpu, t, estado.clut, b.state.texa, w, h);
                if (GSDecodificar::indexado(t.psm))
                {
                    // Índices crudos (un byte por texel) para buscar el origen de la textura en la RAM del EE.
                    char crudo[64];
                    std::snprintf(crudo, sizeof(crudo), "tex_%03d_%ux%u.idx", e.numero, w, h);
                    std::ofstream f(salida / crudo, std::ios::binary);
                    for (uint32_t y = 0; y < h; ++y)
                        for (uint32_t x = 0; x < w; ++x)
                            f.put(char(cpu.ReadVram(t.psm, t.tbp0, t.tbw, x, y)));
                }
                Image img{px.data(), int(w), int(h), 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
                char nombre[64];
                std::snprintf(nombre, sizeof(nombre), "tex_%03d.png", e.numero);
                ExportImage(img, (salida / nombre).string().c_str());
                char ej[256];
                const auto &v0 = b.vertices[0];
                const auto &v1 = b.vertices[b.vertexCount > 1 ? 1 : 0];
                if (b.state.prim.fst)
                    std::snprintf(ej, sizeof(ej), "tipo=%d xy=%.1f,%.1f-%.1f,%.1f uv=%.1f,%.1f-%.1f,%.1f rgba=%u,%u,%u,%u", int(b.state.prim.type),
                                  v0.x, v0.y, v1.x, v1.y, v0.u / 16.0, v0.v / 16.0, v1.u / 16.0, v1.v / 16.0, v0.r, v0.g, v0.b, v0.a);
                else
                    std::snprintf(ej, sizeof(ej), "tipo=%d xy=%.1f,%.1f-%.1f,%.1f st=%.3f,%.3f-%.3f,%.3f", int(b.state.prim.type), v0.x,
                                  v0.y, v1.x, v1.y, v0.s / v0.q, v0.t / v0.q, v1.s / v1.q, v1.t / v1.q);
                e.ejemplo = ej;
            }
        }
        if (!aplicar(cpu, registro))
        {
            std::cerr << "Registro " << indice << " inválido\n";
            return 3;
        }
    }
    std::ofstream idx(salida / "indice.txt");
    std::vector<std::pair<int, std::string>> lineas;
    for (const auto &[k, e] : vistas)
    {
        char l[512];
        std::snprintf(l, sizeof(l), "tex_%03d tbp0=0x%X tbw=%u psm=0x%X %ux%u cbp=0x%X cpsm=%u csa=%u tcc=%u dibujos=%zu %s", e.numero,
                      std::get<0>(k), std::get<1>(k), std::get<2>(k), 1u << std::get<3>(k), 1u << std::get<4>(k), std::get<5>(k),
                      std::get<6>(k), std::get<7>(k), std::get<8>(k), e.dibujos, e.ejemplo.c_str());
        lineas.emplace_back(e.numero, l);
    }
    std::sort(lineas.begin(), lineas.end());
    for (const auto &[n, l] : lineas)
        idx << l << '\n';
    std::cout << vistas.size() << " texturas en " << salida.string() << '\n';
    return 0;
}
