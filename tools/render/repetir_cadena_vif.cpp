// GOW-Port: repite la cadena VIF1 de un cuadro sobre VIF1/VU1/GS del runtime, sin el EE.
// Entrada preparada por tools/render/extraer_cadena_vif.py desde un savestate de PCSX2 o un
// volcado del port (GOW_RENDER_DIAG). Separa los fallos de VIF1/VU1/GS de los datos del EE:
// con los paquetes de PCSX2, una imagen correcta descarta VIF1/VU1/GS como causa.
// Los archivos de entrada y salida contienen datos del juego: nunca se publican.
#include "runtime/ps2_memory.h"
#include "runtime/ps2_vu1.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/ps2_gif_arbiter.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    std::vector<uint8_t> load(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary);
        return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), {});
    }

    void ppm(GS &gs, const std::string &path, uint32_t fbp, uint32_t fbw, uint32_t psm, uint32_t width, uint32_t height)
    {
        std::ofstream out(path, std::ios::binary);
        out << "P6\n" << width << ' ' << height << "\n255\n";
        for (uint32_t y = 0; y < height; ++y)
            for (uint32_t x = 0; x < width; ++x)
            {
                const uint32_t color = gs.ReadVram(psm, fbp * 32u, fbw, x, y);
                const char rgb[3] = {char(color & 0xFFu), char((color >> 8) & 0xFFu), char((color >> 16) & 0xFFu)};
                out.write(rgb, 3);
            }
    }
}

void ps2MuestreoIniciar(); // GOW-Port: ps2_muestreo.cpp (GOW_MUESTREO="inicio:duración")

int main(int argc, char **argv)
{
    ps2MuestreoIniciar();
    if (argc < 3)
    {
        std::cerr << "Uso: repetir_cadena_vif <carpeta> <prefijo de salida> [fbp=0 fbw=8 psm=0 ancho=512 alto=448]\n";
        return 2;
    }
    const std::string dir = argv[1], prefix = argv[2];
    auto arg = [&](int i, uint32_t fallback) { return argc > i ? uint32_t(std::strtoul(argv[i], nullptr, 0)) : fallback; };
    const uint32_t fbp = arg(3, 0u), fbw = arg(4, 8u), psm = arg(5, 0u), width = arg(6, 512u), height = arg(7, 448u);

    const auto vram = load(dir + "/vram.bin");
    const auto code = load(dir + "/vu1MicroMem.bin");
    const auto data = load(dir + "/vu1Memory.bin");
    const auto stream = load(dir + "/vif1_stream.bin");
    const auto hw = load(dir + "/eeHwRegs.bin"); // opcional: registros VIF1 de PCSX2
    if (vram.size() != PS2_GS_VRAM_SIZE || code.size() != PS2_VU1_CODE_SIZE || data.size() != PS2_VU1_DATA_SIZE || stream.empty())
    {
        std::cerr << "Faltan vram.bin, vu1MicroMem.bin, vu1Memory.bin o vif1_stream.bin\n";
        return 1;
    }

    PS2Memory mem;
    if (!mem.initialize())
        return 1;
    std::memcpy(mem.getGSVRAM(), vram.data(), vram.size());
    std::memcpy(mem.getVU1Code(), code.data(), code.size());
    std::memcpy(mem.getVU1Data(), data.data(), data.size());
    if (hw.size() >= 0x4000u)
    {
        // VIF1 en 0x10003C00: STAT, CYCLE +0x40, MODE +0x50, MASK +0x70, ITOPS +0x90, BASE +0xA0,
        // OFST +0xB0, TOPS +0xC0, ITOP +0xD0, TOP +0xE0, R0-R3 +0x100 y C0-C3 +0x140.
        auto reg = [&](uint32_t offset) { uint32_t v; std::memcpy(&v, hw.data() + offset, 4); return v; };
        auto &vif = mem.vif1_regs;
        vif.stat = reg(0x3C00); vif.cycle = reg(0x3C40); vif.mode = reg(0x3C50); vif.mask = reg(0x3C70);
        vif.itops = reg(0x3C90); vif.base = reg(0x3CA0); vif.ofst = reg(0x3CB0); vif.tops = reg(0x3CC0);
        vif.itop = reg(0x3CD0); vif.top = reg(0x3CE0);
        for (uint32_t i = 0; i < 4u; ++i)
        {
            vif.row[i] = reg(0x3D00 + i * 16u);
            vif.col[i] = reg(0x3D40 + i * 16u);
        }
    }

    GS gs;
    gs.init(mem.getGSVRAM(), static_cast<uint32_t>(PS2_GS_VRAM_SIZE), &mem.gs());
    GifArbiter arbiter;
    // GOW-Port: GOW_REPETIR_SIN_GS=1 descarta los paquetes GIF: mide solo VIF1/VU1 (en el juego el GS va en otro hilo).
    const bool sinGs = std::getenv("GOW_REPETIR_SIN_GS") != nullptr;
    // GOW-Port: huella de todo lo que sale hacia el GS (para comparar dos ejecuciones sin dibujar).
    uint64_t salidaHash = 1469598103934665603ull, salidaBytes = 0u;
    arbiter.setProcessPathPacketFn([&](GifPathId path, const uint8_t *packet, uint32_t size)
                                   {
        salidaHash = (salidaHash ^ static_cast<uint8_t>(path)) * 1099511628211ull;
        for (uint32_t i = 0; i < size; ++i)
            salidaHash = (salidaHash ^ packet[i]) * 1099511628211ull;
        salidaBytes += size;
        if (!sinGs) gs.processGIFPacket(packet, size, path); });
    mem.setGifArbiter(&arbiter);

    // Igual que PS2Runtime::syncCoreSubsystems, sin los bits D/T del EE.
    VU1Interpreter vu1;
    {
        // Como PS2Runtime: escrituras directas salvo con GOW_VU1_COLAS=1.
        const char *queues = std::getenv("GOW_VU1_COLAS");
        vu1.setDirectRegisterWrites(!(queues && std::strcmp(queues, "1") == 0));
    }
    uint64_t launches = 0;
    if (std::getenv("GOW_VU1_SIN_COMPILAR"))
        vu1.setCompiledProgramsEnabled(false);
    // GOW_REPETIR_HUELLAS=<archivo>: tras cada lanzamiento escribe una huella del estado de VU1 (registros,
    // flags, ciclos y memoria de datos). Comparar las de dos ejecuciones da el primer lanzamiento distinto.
    std::FILE *prints = nullptr;
    if (const char *path = std::getenv("GOW_REPETIR_HUELLAS"))
        prints = std::fopen(path, "w");
    const auto fingerprint = [&](uint32_t pc)
    {
        if (!prints)
            return;
        const VU1State &st = vu1.state();
        uint64_t hash = 1469598103934665603ull;
        const auto mix = [&](const void *data, size_t size)
        {
            const uint8_t *bytes = static_cast<const uint8_t *>(data);
            for (size_t i = 0; i < size; ++i)
                hash = (hash ^ bytes[i]) * 1099511628211ull;
        };
        // Una huella por grupo para saber qué parte diverge.
        uint64_t parts[6]{};
        const auto part = [&](int index)
        {
            parts[index] = hash;
            hash = 1469598103934665603ull;
        };
        mix(st.vf, sizeof(st.vf));
        part(0);
        mix(st.vi, sizeof(st.vi));
        mix(st.acc, sizeof(st.acc));
        mix(&st.q, sizeof(st.q));
        mix(&st.p, sizeof(st.p));
        mix(&st.i, sizeof(st.i));
        part(1);
        mix(&st.mac, sizeof(st.mac));
        mix(&st.status, sizeof(st.status));
        mix(&st.clip, sizeof(st.clip));
        part(2);
        mix(&st.cycles, sizeof(st.cycles));
        mix(&st.pc, sizeof(st.pc));
        part(3);
        mix(mem.getVU1Data(), PS2_VU1_DATA_SIZE);
        part(4);
        std::fprintf(prints, "%llu pc=%04x vf=%016llx vi=%016llx flags=%016llx ciclos=%016llx datos=%016llx\n",
                     static_cast<unsigned long long>(launches), pc, static_cast<unsigned long long>(parts[0]),
                     static_cast<unsigned long long>(parts[1]), static_cast<unsigned long long>(parts[2]),
                     static_cast<unsigned long long>(parts[3]), static_cast<unsigned long long>(parts[4]));
    };
    // GOW-Port: GOW_REPETIR_PERTURBAR=<clases> llena con basura, antes de cada MSCAL, los registros de esas clases:
    // "vf", "vi", "acc", "qpi" (Q, P, I), "flags" (MAC, status, clip), "todo", o uno solo ("vf5", "vi3"). Si la
    // salida hacia el GS no cambia, ningún programa depende de lo que dejó el anterior en esos registros.
    const char *perturbarTexto = std::getenv("GOW_REPETIR_PERTURBAR");
    const std::string clases = perturbarTexto ? perturbarTexto : "";
    const auto tiene = [&](const char *c) { return clases == "todo" || clases.find(c) != std::string::npos; };
    int soloVf = -1, soloVi = -1;
    if (clases.rfind("vf", 0) == 0 && clases.size() > 2 && std::isdigit(static_cast<unsigned char>(clases[2])))
        soloVf = std::atoi(clases.c_str() + 2);
    if (clases.rfind("vi", 0) == 0 && clases.size() > 2 && std::isdigit(static_cast<unsigned char>(clases[2])))
        soloVi = std::atoi(clases.c_str() + 2);
    const bool perturbar = !clases.empty();
    uint64_t mscal = 0u, mscnt = 0u, semilla = 0x9E3779B97F4A7C15ull;
    const auto basura = [&] { semilla ^= semilla << 13; semilla ^= semilla >> 7; semilla ^= semilla << 17; return semilla; };
    const auto basuraF = [&] { return static_cast<float>(static_cast<int32_t>(basura() & 0xFFFFu) - 32768) * 0.37f; };
    // GOW-Port: GOW_REPETIR_TRAZA_VI=<archivo>: por lanzamiento, pc y VI11/VI13 antes y después.
    // GOW_REPETIR_BORRAR_ESCRITO=1: tras cada lanzamiento, basura en todo lo que escribió el programa en la memoria de
    // datos; si la salida no cambia, ningún lanzamiento lee lo que escribió el programa de otro.
    std::FILE *trazaVi = nullptr;
    if (const char *t = std::getenv("GOW_REPETIR_TRAZA_VI"))
        trazaVi = std::fopen(t, "w");
    const bool borrarEscrito = std::getenv("GOW_REPETIR_BORRAR_ESCRITO") != nullptr;
    std::vector<uint8_t> antesDatos(PS2_VU1_DATA_SIZE);
    mem.setVu1MscalCallback([&](uint32_t pc, uint32_t top, uint32_t itop)
                            {
        ++launches;
        ++mscal;
        const int32_t vi11 = vu1.state().vi[11], vi13 = vu1.state().vi[13];
        if (borrarEscrito)
            std::memcpy(antesDatos.data(), mem.getVU1Data(), PS2_VU1_DATA_SIZE);
        if (perturbar)
        {
            VU1State &st = vu1.state();
            if (soloVf > 0)
                for (int l = 0; l < 4; ++l) st.vf[soloVf][l] = basuraF();
            else if (soloVi > 0)
                st.vi[soloVi] = static_cast<int16_t>(basura());
            else
            {
                if (tiene("vf")) for (int r = 1; r < 32; ++r) for (int l = 0; l < 4; ++l) st.vf[r][l] = basuraF();
                if (tiene("vi")) for (int r = 1; r < 16; ++r) st.vi[r] = static_cast<int16_t>(basura());
                if (tiene("acc")) for (int l = 0; l < 4; ++l) st.acc[l] = basuraF();
                if (tiene("qpi")) { st.q = basuraF(); st.p = basuraF(); st.i = basuraF(); }
                if (tiene("flags")) { st.mac = static_cast<uint32_t>(basura()) & 0xFFFFu; st.status = static_cast<uint32_t>(basura()) & 0xFFFu; st.clip = static_cast<uint32_t>(basura()) & 0xFFFFFFu; }
            }
        }
        vu1.execute(mem.getVU1Code(), PS2_VU1_CODE_SIZE, mem.getVU1Data(), PS2_VU1_DATA_SIZE, gs, &mem, pc, top, itop, 65536);
        if (trazaVi)
            std::fprintf(trazaVi, "%llu pc=%04x top=%04x itop=%04x vi11 %d->%d vi13 %d->%d\n", static_cast<unsigned long long>(launches), pc, top,
                         itop, vi11, vu1.state().vi[11], vi13, vu1.state().vi[13]);
        if (borrarEscrito)
        {
            uint8_t *d = mem.getVU1Data();
            for (uint32_t b = 0; b < PS2_VU1_DATA_SIZE; ++b)
                if (d[b] != antesDatos[b])
                    d[b] = static_cast<uint8_t>(basura());
        }
        fingerprint(pc); });
    mem.setVu1MscntCallback([&](uint32_t top, uint32_t itop)
                            {
        ++launches;
        ++mscnt;
        vu1.resume(mem.getVU1Code(), PS2_VU1_CODE_SIZE, mem.getVU1Data(), PS2_VU1_DATA_SIZE, gs, &mem, top, itop, 65536);
        fingerprint(0xFFFF); });

    if (!sinGs) // sin GS no hay imagen que comparar (y leerla píxel a píxel ensuciaría el perfil)
        ppm(gs, prefix + "_antes.ppm", fbp, fbw, psm, width, height);
    // GOW_REPETIR_VECES=N repite la cadena N veces y mide el tiempo (banco de pruebas de VIF1/VU1).
    const char *timesText = std::getenv("GOW_REPETIR_VECES");
    const uint32_t times = timesText ? std::max<uint32_t>(1u, uint32_t(std::strtoul(timesText, nullptr, 10))) : 1u;
    const auto begin = std::chrono::steady_clock::now();
    for (uint32_t pass = 0; pass < times; ++pass)
    {
        mem.processVIF1Data(stream.data(), static_cast<uint32_t>(stream.size()));
        arbiter.drain();
    }
    const double elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - begin).count();
    if (times > 1u)
        std::printf("[repetir-vif] %u pasadas en %.3f s (%.1f ms por cuadro)\n", times, elapsed, 1000.0 * elapsed / times);
    if (!sinGs)
        ppm(gs, prefix + "_despues.ppm", fbp, fbw, psm, width, height);
    std::printf("[repetir-vif] bytes=%zu lanzamientos_vu1=%llu fbp=%u fbw=%u psm=%u\n", stream.size(),
                static_cast<unsigned long long>(launches), fbp, fbw, psm);
    std::printf("[repetir-vif] MSCAL=%llu MSCNT=%llu salida al GS: %llu bytes, huella %016llx\n",
                static_cast<unsigned long long>(mscal), static_cast<unsigned long long>(mscnt),
                static_cast<unsigned long long>(salidaBytes), static_cast<unsigned long long>(salidaHash));
    return 0;
}
