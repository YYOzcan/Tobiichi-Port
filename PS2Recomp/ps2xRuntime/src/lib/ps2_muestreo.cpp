// GOW-Port: perfil por muestreo dentro del proceso (Linux), para cuando no hay perf ni ptrace.
//   GOW_MUESTREO="inicio:duracion"  desde el segundo inicio y durante duracion segundos, SIGPROF cada ~1 ms de CPU
//                                   guarda el contador de programa del hilo que corre. Al terminar escribe
//                                   muestreo.txt: "base <dirección de carga>", "hilo <tid> <nombre>" y "<tid> <pc>".
// tools/perfil/resumir_muestreo.py lo agrupa por función con nm. Sin la variable no hace nada.
#if defined(__linux__)
#include <algorithm>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <link.h>
#include <set>
#include <string>
#include <sys/syscall.h>
#include <sys/time.h>
#include <thread>
#include <ucontext.h>
#include <unistd.h>

namespace
{
    constexpr size_t kMaxMuestras = 1u << 22;
    struct Muestra
    {
        uint32_t tid;
        uint64_t pc;
    };
    Muestra *g_muestras = nullptr;
    std::atomic<size_t> g_cuenta{0};
    std::atomic<bool> g_activo{false};

    void manejador(int, siginfo_t *, void *contexto)
    {
        if (!g_activo.load(std::memory_order_relaxed))
            return;
        const size_t i = g_cuenta.fetch_add(1u, std::memory_order_relaxed);
        if (i >= kMaxMuestras)
            return;
        const auto *uc = static_cast<const ucontext_t *>(contexto);
        g_muestras[i].tid = static_cast<uint32_t>(syscall(SYS_gettid));
        g_muestras[i].pc = static_cast<uint64_t>(uc->uc_mcontext.gregs[REG_RIP]);
    }

    uintptr_t baseEjecutable()
    {
        uintptr_t base = 0u;
        dl_iterate_phdr([](dl_phdr_info *info, size_t, void *dato) {
            if (info->dlpi_name == nullptr || info->dlpi_name[0] == '\0')
            {
                *static_cast<uintptr_t *>(dato) = static_cast<uintptr_t>(info->dlpi_addr);
                return 1;
            }
            return 0;
        }, &base);
        return base;
    }
}

void ps2MuestreoIniciar()
{
    const char *valor = std::getenv("GOW_MUESTREO");
    if (!valor)
        return;
    double inicio = 0.0, duracion = 0.0;
    if (std::sscanf(valor, "%lf:%lf", &inicio, &duracion) != 2 || duracion <= 0.0)
        return;
    g_muestras = new Muestra[kMaxMuestras];
    struct sigaction sa{};
    sa.sa_sigaction = &manejador;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGPROF, &sa, nullptr);
    std::thread([inicio, duracion] {
        std::this_thread::sleep_for(std::chrono::duration<double>(inicio));
        g_activo.store(true);
        itimerval t{};
        t.it_interval.tv_usec = 1000;
        t.it_value.tv_usec = 1000;
        setitimer(ITIMER_PROF, &t, nullptr);
        std::this_thread::sleep_for(std::chrono::duration<double>(duracion));
        itimerval cero{};
        setitimer(ITIMER_PROF, &cero, nullptr);
        g_activo.store(false);
        const size_t n = std::min(g_cuenta.load(), kMaxMuestras);
        std::ofstream salida("muestreo.txt");
        salida << "base " << std::hex << baseEjecutable() << std::dec << "\n";
        {
            // Bibliotecas: "mapa <inicio> <fin> <desplazamiento> <ruta>" de las regiones ejecutables.
            std::ifstream mapas("/proc/self/maps");
            std::string linea;
            while (std::getline(mapas, linea))
            {
                char rango[64] = {}, permisos[8] = {}, desp[32] = {}, dev[16] = {}, ruta[512] = {};
                unsigned long inodo = 0;
                if (std::sscanf(linea.c_str(), "%63s %7s %31s %15s %lu %511s", rango, permisos, desp, dev, &inodo, ruta) >= 6 &&
                    permisos[2] == 'x')
                {
                    std::string r(rango);
                    const size_t g = r.find('-');
                    salida << "mapa " << r.substr(0, g) << " " << r.substr(g + 1) << " " << desp << " " << ruta << "\n";
                }
            }
        }
        std::set<uint32_t> hilos;
        for (size_t i = 0; i < n; ++i)
            hilos.insert(g_muestras[i].tid);
        for (uint32_t tid : hilos)
        {
            std::ifstream nombre("/proc/self/task/" + std::to_string(tid) + "/comm");
            std::string n2;
            std::getline(nombre, n2);
            salida << "hilo " << tid << " " << (n2.empty() ? "?" : n2) << "\n";
        }
        for (size_t i = 0; i < n; ++i)
            salida << g_muestras[i].tid << " " << std::hex << g_muestras[i].pc << std::dec << "\n";
        std::fprintf(stderr, "[muestreo] %zu muestras en muestreo.txt\n", n);
    }).detach();
    std::fprintf(stderr, "[muestreo] desde %.0f s durante %.0f s\n", inicio, duracion);
}
#else
void ps2MuestreoIniciar() {}
#endif
