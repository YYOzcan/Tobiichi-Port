// GOW-Port: un núcleo físico para el hilo de VU1 (Linux), con GOW_AFINIDAD=1 (desactivado por defecto: en el portátil de
// pruebas, con ahorro de energía, VU1 pasa de 20,1 a 19,7 ms por cuadro, dentro del ruido).
//
// El cuadro de God of War lo limita el hilo de VU1 (ver docs/RENDIMIENTO.md, "Portátil en ahorro de energía"). Con
// el perfil de ahorro de energía los demás hilos del juego (EE, GS, IOP) le quitaban rendimiento compartiendo su
// núcleo físico (SMT) y el presupuesto de potencia. Aquí el hilo de VU1 se fija al núcleo con mejor clasificación de
// amd-pstate (prefcore; si no la hay, el último) y el resto de hilos del proceso, presentes y futuros, se mantienen
// fuera de ese núcleo y de su hermano SMT. Solo cambia la afinidad de los hilos del propio proceso; con menos de 4
// CPU no hace nada.
#if defined(__linux__)
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <sched.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>

namespace
{
    int g_nucleo = -1;
    cpu_set_t g_resto;

    int leerEntero(const std::string &ruta, int defecto)
    {
        std::ifstream f(ruta);
        int v = defecto;
        return (f >> v) ? v : defecto;
    }

    bool activo()
    {
        const char *v = std::getenv("GOW_AFINIDAD");
        return v && v[0] == '1';
    }
}

// Hilo principal, antes de crear los hilos del juego.
void ps2AfinidadReservar()
{
    if (!activo() || g_nucleo >= 0)
        return;
    const long cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpus < 4 || cpus > CPU_SETSIZE)
        return;
    int mejor = static_cast<int>(cpus) - 1, rango = -1;
    for (int c = 0; c < cpus; ++c)
    {
        const int r = leerEntero("/sys/devices/system/cpu/cpu" + std::to_string(c) + "/cpufreq/amd_pstate_prefcore_ranking", -1);
        if (r > rango)
        {
            rango = r;
            mejor = c;
        }
    }
    // Hermanos SMT del núcleo elegido ("0-1" o "0,8").
    cpu_set_t reservado;
    CPU_ZERO(&reservado);
    CPU_SET(mejor, &reservado);
    {
        std::ifstream f("/sys/devices/system/cpu/cpu" + std::to_string(mejor) + "/topology/thread_siblings_list");
        std::string lista;
        std::getline(f, lista);
        size_t i = 0u;
        while (i < lista.size())
        {
            size_t fin = lista.find(',', i);
            if (fin == std::string::npos)
                fin = lista.size();
            const std::string parte = lista.substr(i, fin - i);
            const size_t guion = parte.find('-');
            const int a = std::atoi(parte.c_str());
            const int b = guion == std::string::npos ? a : std::atoi(parte.c_str() + guion + 1);
            for (int c = a; c <= b && c < CPU_SETSIZE; ++c)
                CPU_SET(c, &reservado);
            i = fin + 1u;
        }
    }
    CPU_ZERO(&g_resto);
    for (int c = 0; c < cpus; ++c)
        if (!CPU_ISSET(c, &reservado))
            CPU_SET(c, &g_resto);
    if (CPU_COUNT(&g_resto) < 2)
        return;
    g_nucleo = mejor;
    // Todos los hilos que ya existen (y los que creen después, que heredan la máscara) fuera del núcleo reservado.
    if (DIR *dir = opendir("/proc/self/task"))
    {
        while (dirent *e = readdir(dir))
        {
            const int tid = std::atoi(e->d_name);
            if (tid > 0)
                sched_setaffinity(tid, sizeof(g_resto), &g_resto);
        }
        closedir(dir);
    }
    std::fprintf(stderr, "[afinidad] VU1 en la CPU %d; el resto de hilos fuera de ese núcleo físico\n", mejor);
}

// Desde el hilo de VU1, al arrancar.
void ps2AfinidadVu1()
{
    if (g_nucleo < 0)
        return;
    cpu_set_t uno;
    CPU_ZERO(&uno);
    CPU_SET(g_nucleo, &uno);
    sched_setaffinity(0, sizeof(uno), &uno);
}
#else
void ps2AfinidadReservar() {}
void ps2AfinidadVu1() {}
#endif
