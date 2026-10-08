// GOW-Port: perfilador por muestreo externo para Windows.
// Uso: muestrear <pid> <segundos> [hilos=6] [funciones=30]
// Suspende cada hilo del proceso cada ~1 ms, lee su RIP y, al terminar, agrupa las muestras por
// función con DbgHelp. Para ver nombres el ejecutable necesita su PDB (/Zi y /DEBUG); sin él solo
// aparecen módulos. Las esperas del sistema (ntdll/KERNELBASE) indican hilos ociosos.
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <tlhelp32.h>
#include <dbghelp.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#pragma comment(lib, "dbghelp.lib")

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::fprintf(stderr, "Uso: muestrear <pid> <segundos> [hilos] [funciones]\n");
        return 2;
    }
    const DWORD pid = static_cast<DWORD>(std::strtoul(argv[1], nullptr, 10));
    const double seconds = std::strtod(argv[2], nullptr);
    const size_t maxThreads = argc > 3 ? std::strtoul(argv[3], nullptr, 10) : 6u;
    const size_t maxFunctions = argc > 4 ? std::strtoul(argv[4], nullptr, 10) : 30u;

    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!process)
    {
        std::fprintf(stderr, "No se pudo abrir el proceso %lu\n", pid);
        return 1;
    }

    std::unordered_map<DWORD, std::unordered_map<DWORD64, uint32_t>> samples;
    // Muestras atribuidas al primer marco del ejecutable (útil cuando el PC está en una DLL del sistema).
    std::unordered_map<DWORD, std::unordered_map<DWORD64, uint32_t>> callers;
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    // GOW-Port: una sola sesion DbgHelp por proceso; repetirla produce ERROR_INVALID_PARAMETER.
    if (!SymInitialize(process, nullptr, TRUE))
    {
        std::fprintf(stderr, "SymInitialize falló (%lu)\n", GetLastError());
        CloseHandle(process);
        return 1;
    }
    DWORD64 exeBase = 0;
    {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        MODULEENTRY32 module{};
        module.dwSize = sizeof(module);
        if (Module32First(snap, &module))
            exeBase = reinterpret_cast<DWORD64>(module.modBaseAddr);
        CloseHandle(snap);
    }
    std::vector<std::pair<DWORD, HANDLE>> threads;
    const ULONGLONG begin = GetTickCount64();
    ULONGLONG lastRefresh = 0;
    while (GetTickCount64() - begin < static_cast<ULONGLONG>(seconds * 1000.0))
    {
        if (GetTickCount64() - lastRefresh > 1000)
        {
            for (auto &[tid, handle] : threads)
                CloseHandle(handle);
            threads.clear();
            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
            THREADENTRY32 entry{};
            entry.dwSize = sizeof(entry);
            for (BOOL ok = Thread32First(snap, &entry); ok; ok = Thread32Next(snap, &entry))
                if (entry.th32OwnerProcessID == pid)
                    if (HANDLE h = OpenThread(THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT, FALSE, entry.th32ThreadID))
                        threads.push_back({entry.th32ThreadID, h});
            CloseHandle(snap);
            lastRefresh = GetTickCount64();
            if (threads.empty())
                break;
        }
        for (auto &[tid, handle] : threads)
        {
            if (SuspendThread(handle) == static_cast<DWORD>(-1))
                continue;
            CONTEXT context{};
            context.ContextFlags = CONTEXT_FULL;
            if (GetThreadContext(handle, &context))
            {
                ++samples[tid][context.Rip];
                if (exeBase && SymGetModuleBase64(process, context.Rip) != exeBase)
                {
                    STACKFRAME64 frame{};
                    frame.AddrPC.Offset = context.Rip; frame.AddrPC.Mode = AddrModeFlat;
                    frame.AddrStack.Offset = context.Rsp; frame.AddrStack.Mode = AddrModeFlat;
                    frame.AddrFrame.Offset = context.Rbp; frame.AddrFrame.Mode = AddrModeFlat;
                    for (int depth = 0; depth < 12; ++depth)
                    {
                        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, handle, &frame, &context, nullptr,
                                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr) || frame.AddrPC.Offset == 0)
                            break;
                        if (SymGetModuleBase64(process, frame.AddrPC.Offset) == exeBase)
                        {
                            ++callers[tid][frame.AddrPC.Offset];
                            break;
                        }
                    }
                }
            }
            ResumeThread(handle);
        }
        Sleep(1);
    }

    // Ordenar los hilos por muestras fuera de esperas del sistema (los más ocupados primero).
    alignas(SYMBOL_INFO) char buffer[sizeof(SYMBOL_INFO) + 512];
    auto resolve = [&](DWORD64 pc)
    {
        auto *symbol = reinterpret_cast<SYMBOL_INFO *>(buffer);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = 511;
        DWORD64 displacement = 0;
        IMAGEHLP_MODULE64 module{};
        module.SizeOfStruct = sizeof(module);
        const std::string mod = SymGetModuleInfo64(process, pc, &module) ? module.ModuleName : "?";
        if (SymFromAddr(process, pc, &displacement, symbol))
            return mod + "!" + symbol->Name + (displacement > 0x400 ? "+0x" + [&]{ char t[24]; std::snprintf(t, sizeof(t), "%llx", static_cast<unsigned long long>(displacement)); return std::string(t); }() : std::string());
        return mod;
    };
    struct ThreadReport { uint64_t busy = 0, total = 0; DWORD tid = 0; std::map<std::string, uint64_t> functions; };
    std::vector<ThreadReport> reports;
    for (const auto &[tid, map] : samples)
    {
        ThreadReport report;
        report.tid = tid;
        for (const auto &[pc, n] : map)
        {
            const std::string name = resolve(pc);
            report.functions[name] += n;
            report.total += n;
            if (name.rfind("ntdll", 0) != 0 && name.rfind("KERNELBASE", 0) != 0 && name.rfind("win32u", 0) != 0)
                report.busy += n;
        }
        reports.push_back(std::move(report));
    }
    std::sort(reports.begin(), reports.end(), [](const auto &a, const auto &b) { return a.busy > b.busy; });
    for (size_t t = 0; t < reports.size() && t < maxThreads; ++t)
    {
        const auto &report = reports[t];
        std::printf("hilo %lu: %llu muestras, %.1f%% fuera de esperas del sistema\n", report.tid,
                    static_cast<unsigned long long>(report.total), 100.0 * report.busy / std::max<uint64_t>(1, report.total));
        std::vector<std::pair<uint64_t, std::string>> sorted;
        for (const auto &[name, n] : report.functions)
            sorted.push_back({n, name});
        std::sort(sorted.rbegin(), sorted.rend());
        for (size_t i = 0; i < sorted.size() && i < maxFunctions; ++i)
            std::printf("  %5.1f%%  %s\n", 100.0 * sorted[i].first / report.total, sorted[i].second.c_str());
        // GOW-Port: atribuir las muestras en DLLs al primer marco recuperado del ejecutable.
        // Son una segunda vista de esas mismas muestras, no tiempo adicional ni CPU exclusiva.
        const auto recovered = callers.find(report.tid);
        if (recovered != callers.end() && !recovered->second.empty())
        {
            std::map<std::string, uint64_t> names;
            uint64_t recoveredCount = 0u;
            for (const auto &[pc, n] : recovered->second)
            {
                names[resolve(pc)] += n;
                recoveredCount += n;
            }
            std::vector<std::pair<uint64_t, std::string>> ranked;
            for (const auto &[name, n] : names)
                ranked.push_back({n, name});
            std::sort(ranked.rbegin(), ranked.rend());
            std::printf("  marcos del ejecutable desde DLL: %llu/%llu muestras (porcentaje del hilo)\n",
                        static_cast<unsigned long long>(recoveredCount), static_cast<unsigned long long>(report.total));
            for (size_t i = 0; i < ranked.size() && i < maxFunctions; ++i)
                std::printf("    %5.1f%%  %s\n", 100.0 * ranked[i].first / report.total, ranked[i].second.c_str());
        }
    }
    for (auto &[tid, handle] : threads)
        CloseHandle(handle);
    SymCleanup(process);
    CloseHandle(process);
    return 0;
}
