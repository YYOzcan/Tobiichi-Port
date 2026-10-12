// GOW-Port: perfilador por muestreo para Linux (equivalente a muestrear.cpp). Lanza el juego como hijo (con
// ptrace_scope=1 solo se puede rastrear a descendientes) y lee el RIP de cada hilo cada <intervalo> us.
// Sampling profiler: launches a command, finds a descendant process by name, and samples every
// thread's RIP via ptrace (works with yama ptrace_scope=1 because the target is a descendant).
// Usage: sampler <procname> <warmup_s> <duration_s> <interval_us> <out.txt> -- cmd args...
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <thread>
#include <vector>

static int ppidOf(int pid) {
    std::ifstream f("/proc/" + std::to_string(pid) + "/stat");
    std::string s; std::getline(f, s);
    auto p = s.rfind(')'); if (p == std::string::npos) return -1;
    char st; int ppid; std::sscanf(s.c_str() + p + 2, "%c %d", &st, &ppid); return ppid;
}
static std::string comm(const std::string &path) {
    std::ifstream f(path); std::string s; std::getline(f, s); return s;
}
static int findDescendant(int root, const char *name) {
    DIR *d = opendir("/proc"); if (!d) return -1; int found = -1;
    while (dirent *e = readdir(d)) {
        int pid = std::atoi(e->d_name); if (pid <= 0) continue;
        if (comm("/proc/" + std::to_string(pid) + "/comm").rfind(name, 0) != 0) continue;
        for (int p = pid; p > 1; p = ppidOf(p)) if (p == root) { found = pid; break; }
        if (found > 0) break;
    }
    closedir(d); return found;
}
static std::vector<int> tasks(int pid) {
    std::vector<int> out; std::string dir = "/proc/" + std::to_string(pid) + "/task";
    DIR *d = opendir(dir.c_str()); if (!d) return out;
    while (dirent *e = readdir(d)) { int t = std::atoi(e->d_name); if (t > 0) out.push_back(t); }
    closedir(d); return out;
}
// Interrupt tid, wait for the stop, read RIP, resume. Returns false if the thread is gone.
static bool sample(int tid, unsigned long long &rip) {
    if (ptrace(PTRACE_INTERRUPT, tid, 0, 0) != 0) return false;
    for (;;) {
        int st = 0;
        if (waitpid(tid, &st, __WALL) != tid) return false;
        if (WIFEXITED(st) || WIFSIGNALED(st)) return false;
        if (!WIFSTOPPED(st)) continue;
        const int event = st >> 16;
        if (event == PTRACE_EVENT_STOP) {
            user_regs_struct regs{};
            if (ptrace(PTRACE_GETREGS, tid, 0, &regs) == 0) rip = regs.rip;
            ptrace(PTRACE_CONT, tid, 0, 0);
            return true;
        }
        // Signal-delivery stop: reinject and keep waiting for our interrupt stop.
        ptrace(PTRACE_CONT, tid, 0, (void *)(long)WSTOPSIG(st));
    }
}
int main(int argc, char **argv) {
    if (argc < 8 || std::strcmp(argv[6], "--") != 0) {
        std::fprintf(stderr, "usage: sampler <procname> <warmup_s> <duration_s> <interval_us> <out> -- cmd...\n");
        return 2;
    }
    const char *name = argv[1];
    const double warmup = std::atof(argv[2]), duration = std::atof(argv[3]);
    const int interval = std::atoi(argv[4]);
    const char *outPath = argv[5];
    const int child = fork();
    if (child == 0) { execvp(argv[7], argv + 7); _exit(127); }
    std::this_thread::sleep_for(std::chrono::duration<double>(warmup));
    const int target = findDescendant(child, name);
    if (target <= 0) { std::fprintf(stderr, "target not found\n"); kill(child, SIGINT); return 1; }
    std::map<std::pair<std::string, unsigned long long>, unsigned> hist; // (thread name, rip) -> count
    std::set<int> seized;
    const auto end = std::chrono::steady_clock::now() + std::chrono::duration<double>(duration);
    unsigned long long samples = 0;
    while (std::chrono::steady_clock::now() < end) {
        for (int tid : tasks(target)) {
            if (!seized.count(tid)) {
                if (ptrace(PTRACE_SEIZE, tid, 0, 0) != 0) continue;
                seized.insert(tid);
            }
            unsigned long long rip = 0;
            if (!sample(tid, rip)) { seized.erase(tid); continue; }
            const std::string tname = comm("/proc/" + std::to_string(target) + "/task/" + std::to_string(tid) + "/comm");
            ++hist[{tname + "#" + std::to_string(tid), rip}];
            ++samples;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(interval));
    }
    // Save memory maps before detaching (for symbolization).
    {
        std::ifstream m("/proc/" + std::to_string(target) + "/maps");
        std::ofstream o(std::string(outPath) + ".maps"); o << m.rdbuf();
    }
    for (int tid : seized) {
        // PTRACE_DETACH needs a ptrace-stop: interrupt, wait for it (reinjecting signals), then detach.
        if (ptrace(PTRACE_INTERRUPT, tid, 0, 0) != 0) continue;
        for (;;) {
            int st = 0;
            if (waitpid(tid, &st, __WALL) != tid || !WIFSTOPPED(st)) break;
            if ((st >> 16) == PTRACE_EVENT_STOP) { ptrace(PTRACE_DETACH, tid, 0, 0); break; }
            ptrace(PTRACE_CONT, tid, 0, (void *)(long)WSTOPSIG(st));
        }
    }
    std::FILE *out = std::fopen(outPath, "w");
    for (auto &[k, v] : hist) std::fprintf(out, "%s %llx %u\n", k.first.c_str(), k.second, v);
    std::fclose(out);
    std::fprintf(stderr, "samples=%llu threads=%zu\n", samples, seized.size());
    // Por defecto el juego sigue abierto (se puede seguir jugando); MUESTREAR_CERRAR=1 lo cierra al terminar.
    if (const char *close = std::getenv("MUESTREAR_CERRAR"); close && close[0] == '1')
        kill(target, SIGINT);
    int st; waitpid(child, &st, 0);
    return 0;
}
