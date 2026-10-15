#include <chrono>
#include <cstdlib>
#include "ee_watch.h"

#include <cstdio>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

namespace
{
    // The host page holding the range is made read-only; a write faults, is logged, the page is unprotected for
    // one single-stepped instruction, then protected again.
    eewatch::GuestPcProvider s_provider;
    uint8_t *s_page = nullptr;
    uintptr_t s_begin = 0, s_end = 0;
    uint32_t s_guest = 0, s_hits = 0;

    // GOW-Port: PS2X_EE_WATCH_FROM=<s>: report writes only after <s> seconds of process time (skips load-time writes).
    bool watchGateOpen()
    {
        static const auto t0 = std::chrono::steady_clock::now();
        static const double from = std::getenv("PS2X_EE_WATCH_FROM") ? std::atof(std::getenv("PS2X_EE_WATCH_FROM")) : 0.0;
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count() >= from;
    }
    LONG CALLBACK handler(EXCEPTION_POINTERS *info)
    {
        const DWORD code = info->ExceptionRecord->ExceptionCode;
        if (code == EXCEPTION_ACCESS_VIOLATION && info->ExceptionRecord->NumberParameters >= 2 &&
            info->ExceptionRecord->ExceptionInformation[0] == 1)
        {
            const uintptr_t address = info->ExceptionRecord->ExceptionInformation[1];
            const uintptr_t page = reinterpret_cast<uintptr_t>(s_page);
            if (address >= page && address < page + 4096)
            {
                if (address + 16 > s_begin && address < s_end && s_hits < 400 && watchGateOpen())
                {
                    ++s_hits;
                    uint32_t pc = 0, ra = 0;
                    if (s_provider)
                        s_provider(pc, ra);
                    std::fprintf(stderr, "[eewatch] write ee 0x%08X pc=0x%08X ra=0x%08X\n",
                                 static_cast<uint32_t>(s_guest + (address - s_begin)), pc, ra);
                }
                DWORD old;
                VirtualProtect(s_page, 4096, PAGE_READWRITE, &old);
                info->ContextRecord->EFlags |= 0x100; // single-step the faulting store
                return EXCEPTION_CONTINUE_EXECUTION;
            }
        }
        if (code == EXCEPTION_SINGLE_STEP && s_page)
        {
            DWORD old;
            VirtualProtect(s_page, 4096, PAGE_READONLY, &old);
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }
}

namespace eewatch
{
    void install(uint8_t *rdram, uint32_t guestAddress, uint32_t length, GuestPcProvider provider)
    {
        s_provider = std::move(provider);
        s_guest = guestAddress;
        s_begin = reinterpret_cast<uintptr_t>(rdram + guestAddress);
        s_end = s_begin + length;
        s_page = reinterpret_cast<uint8_t *>(s_begin & ~static_cast<uintptr_t>(4095));
        AddVectoredExceptionHandler(1, handler);
        DWORD old;
        VirtualProtect(s_page, 4096, PAGE_READONLY, &old);
        std::fprintf(stderr, "[eewatch] watching ee 0x%08X len 0x%X\n", guestAddress, length);
    }
}
#else
namespace eewatch
{
    void install(uint8_t *, uint32_t, uint32_t, GuestPcProvider) {}
}
#endif
