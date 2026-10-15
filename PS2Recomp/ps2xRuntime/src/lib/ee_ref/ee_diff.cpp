// GOW-Port: EE differential tester hookup (ported from our PAL stack's main.cpp).
// PS2X_EE_DIFF=<hex addr>[,...] or PS2X_EE_DIFF=all: wraps recompiled functions; the first PS2X_EE_DIFF_MAX calls
// (default 3, "all": 1) are re-run on PCSX2's EE interpreter (eeref) from an entry snapshot and every differing
// register / written word is printed. PS2X_EE_DIFF_START=<s>: only calls made at least <s> seconds after start
// are checked (e.g. while a scripted walk runs). PS2X_EE_DIFF_STEPS limits interpreter steps (default 2M).
#include "ps2_runtime.h"
#include "eeref.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace
{
    std::unordered_map<uint32_t, PS2Runtime::RecompiledFunction> g_originals;
    PS2Runtime *g_runtime = nullptr;
    bool g_quiet = false;
    std::chrono::steady_clock::time_point g_startTime;
    double g_startDelay = 0.0;
    std::mutex g_mutex; // one comparison at a time (guest threads may run on several host threads)

    eeref::CpuSnapshot snapshotCpu(const R5900Context *ctx)
    {
        eeref::CpuSnapshot s{};
        for (int i = 0; i < 32; ++i)
        {
            std::memcpy(s.gpr[i], &ctx->r[i], 16);
            std::memcpy(&s.f[i], &ctx->f[i], 4);
            std::memcpy(s.vf[i], &ctx->vu0_vf[i], 16);
        }
        s.hi = ctx->hi;
        s.lo = ctx->lo;
        s.hi1 = ctx->hi1;
        s.lo1 = ctx->lo1;
        s.sa = ctx->sa;
        std::memcpy(&s.facc, &ctx->f_acc, 4);
        s.fcr31 = ctx->fcr31;
        for (int i = 0; i < 16; ++i)
            s.vi[i] = ctx->vi[i];
        std::memcpy(s.acc, &ctx->vu0_acc, 16);
        std::memcpy(&s.q, &ctx->vu0_q, 4);
        std::memcpy(&s.p, &ctx->vu0_p, 4);
        std::memcpy(&s.i, &ctx->vu0_i, 4);
        std::memcpy(&s.r, &ctx->vu0_r, 4);
        s.status = ctx->vu0_status;
        s.mac = ctx->vu0_mac_flags;
        s.clip = ctx->vu0_clip_flags;
        return s;
    }

    void diffCallWrapper(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t address = ctx->pc;
        const PS2Runtime::RecompiledFunction original = g_originals.at(address);
        static std::unordered_map<uint32_t, int> calls;
        static const int maxCalls = std::getenv("PS2X_EE_DIFF_MAX") ? std::atoi(std::getenv("PS2X_EE_DIFF_MAX"))
                                                                    : (g_quiet ? 1 : 3);
        const double elapsed =
            std::chrono::duration<double>(std::chrono::steady_clock::now() - g_startTime).count();
        std::unique_lock<std::mutex> lock(g_mutex, std::try_to_lock);
        // GOW-Port: PS2X_EE_DIFF_EVERY=<n>: compare only every n-th call of a function (spreads the checked calls over
        // many frames / animation phases instead of the first few calls); PS2X_EE_DIFF_MAX then bounds the checked ones.
        static const int every = std::getenv("PS2X_EE_DIFF_EVERY") ? std::max(1, std::atoi(std::getenv("PS2X_EE_DIFF_EVERY"))) : 1;
        static std::unordered_map<uint32_t, int> seenCalls;
        static std::unordered_map<uint32_t, int> checked;
        const int seq = seenCalls[address]++;
        const bool skipThis = elapsed < g_startDelay || !lock.owns_lock() || ((seq + static_cast<int>(address >> 2)) % every) != 0 || checked[address] >= maxCalls;
        if (!skipThis) { ++checked[address]; ++calls[address]; }
        if (skipThis)
        {
            if (lock.owns_lock())
                lock.unlock();
            original(rdram, ctx, runtime);
            return;
        }
        const uint32_t returnPc = getRegU32(ctx, 31);
        const eeref::CpuSnapshot before = snapshotCpu(ctx);
        uint8_t *scratch = g_runtime->memory().getScratchpad();
        std::vector<uint8_t> ramBefore(rdram, rdram + PS2_RAM_SIZE);
        std::vector<uint8_t> scratchBefore(scratch, scratch + PS2_SCRATCHPAD_SIZE);
        lock.unlock(); // the call may block on other guest threads that also enter wrappers
        original(rdram, ctx, runtime);
        lock.lock();
        const eeref::CpuSnapshot after = snapshotCpu(ctx);
        if (after.gpr[29][0] != before.gpr[29][0] || ctx->pc != returnPc)
        {
            static std::unordered_map<uint32_t, bool> skippedOnce;
            if (g_quiet && !skippedOnce[address])
            {
                skippedOnce[address] = true;
                std::fprintf(stderr, "[eediff] %08X (ra %08X) skipped: did not return normally (pc %08X sp %08X->%08X)\n", address, returnPc, ctx->pc, static_cast<uint32_t>(before.gpr[29][0]), static_cast<uint32_t>(after.gpr[29][0]));
            }
            if (!g_quiet)
                std::fprintf(stderr, "[eediff] %08X: call did not return normally, skipped\n", address);
            return;
        }
        static const unsigned long long maxSteps =
            std::getenv("PS2X_EE_DIFF_STEPS") ? std::strtoull(std::getenv("PS2X_EE_DIFF_STEPS"), nullptr, 10) : 2'000'000ull;
        const eeref::Result result = eeref::run(before, ramBefore.data(), scratchBefore.data(), address, returnPc,
                                                after, rdram, scratch, maxSteps);
        static unsigned identical = 0, stopped = 0, differing = 0;
        if (!result.completed)
        {
            ++stopped;
            // Report each not-comparable function once, so unchecked code is visible.
            static std::unordered_map<uint32_t, bool> reported;
            if (!reported[address])
            {
                reported[address] = true;
                std::fprintf(stderr, "[eediff] %08X (ra %08X) not comparable: %s (%llu steps)\n", address, returnPc,
                             result.stopReason.c_str(), (unsigned long long)result.steps);
            }
        }
        else if (result.differences.empty())
            ++identical;
        else
            ++differing;
        // GOW-Port: differences written above the entry stack pointer land in a caller's frame (outputs or the
        // locals of a never-returning loop); report them separately, they are invisible in the caller's own diff.
        if (result.completed)
        {
            const uint32_t entrySp = static_cast<uint32_t>(before.gpr[29][0]) & 0x01FFFFFFu;
            static unsigned callerFrame = 0;
            for (const std::string &line : result.differences)
            {
                unsigned long addr = 0;
                if (line.rfind("mem ", 0) == 0 && std::sscanf(line.c_str() + 4, "%lx", &addr) == 1 &&
                    addr >= entrySp && addr < 0x02000000ul && callerFrame < 200u)
                {
                    ++callerFrame;
                    std::fprintf(stderr, "[eediff-callerframe] %08X (ra %08X) sp=%08X %s\n", address, returnPc, entrySp,
                                 line.c_str());
                }
            }
        }
        if (result.completed && !result.differences.empty())
        {
            std::fprintf(stderr, "[eediff] %08X (ra %08X) call %d: %zu+ differences (%llu steps)\n", address, returnPc,
                         calls[address], result.differences.size(), (unsigned long long)result.steps);
            for (const std::string &line : result.differences)
                std::fprintf(stderr, "[eediff]    %s\n", line.c_str());
        }
        else if (!g_quiet)
            std::fprintf(stderr, "[eediff] %08X call %d: %s (%llu steps)\n", address, calls[address],
                         result.completed ? "identical" : result.stopReason.c_str(), (unsigned long long)result.steps);
        if (((identical + stopped + differing) % 200u) == 0u)
            std::fprintf(stderr, "[eediff] tally: %u identical, %u differing, %u not comparable\n", identical,
                         differing, stopped);
    }
}

void ps2InstallEeDiff(PS2Runtime &runtime)
{
    const char *list = std::getenv("PS2X_EE_DIFF");
    if (!list || !*list)
        return;
    g_runtime = &runtime;
    g_startTime = std::chrono::steady_clock::now();
    if (const char *start = std::getenv("PS2X_EE_DIFF_START"))
        g_startDelay = std::atof(start);
    unsigned hooked = 0;
    auto hook = [&](uint32_t address)
    {
        if (g_originals.count(address) != 0u)
            return;
        if (const PS2Runtime::RecompiledFunction original = runtime.lookupFunction(address))
        {
            g_originals[address] = original;
            runtime.replaceFunction(address, diffCallWrapper);
            ++hooked;
        }
    };
    if (std::strcmp(list, "all") == 0)
    {
        g_quiet = true;
        for (uint32_t address = 0x00100000u; address < 0x002C0000u; address += 4u)
            hook(address);
    }
    else
        for (const char *cursor = list; cursor && *cursor;)
        {
            char *end = nullptr;
            hook(static_cast<uint32_t>(std::strtoul(cursor, &end, 16)));
            cursor = (end && *end == ',') ? end + 1 : nullptr;
        }
    std::fprintf(stderr, "[eediff] hooked %u functions (start after %.1f s)\n", hooked, g_startDelay);
}

// GOW-Port: PS2X_EE_WATCH_WORD=<hex addr>: every recompiled function is wrapped; after a call returns, if the
// watched 32-bit word changed, "[eewatch] <func> (ra) old -> new" is printed (first 40 changes). Nested calls
// report first, so the first line of a change names the innermost function that wrote it.
namespace
{
    uint32_t g_watchAddress = 0;
    std::unordered_map<uint32_t, PS2Runtime::RecompiledFunction> g_watchOriginals;
    void watchWrapper(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t address = ctx->pc, ra = getRegU32(ctx, 31);
        uint32_t before;
        std::memcpy(&before, rdram + g_watchAddress, 4);
        g_watchOriginals.at(address)(rdram, ctx, runtime);
        uint32_t after;
        std::memcpy(&after, rdram + g_watchAddress, 4);
        static unsigned reports = 0;
        if (after != before && reports < 40u)
        {
            ++reports;
            float fb, fa;
            std::memcpy(&fb, &before, 4);
            std::memcpy(&fa, &after, 4);
            std::fprintf(stderr, "[eewatch] %08X (ra %08X) %08X (%g) -> %08X (%g)\n", address, ra, before, fb, after, fa);
        }
    }
}

void ps2InstallEeWatch(PS2Runtime &runtime)
{
    const char *value = std::getenv("PS2X_EE_WATCH_WORD");
    if (!value || !*value)
        return;
    g_watchAddress = static_cast<uint32_t>(std::strtoul(value, nullptr, 16)) & 0x01FFFFFCu;
    unsigned hooked = 0;
    for (uint32_t address = 0x00100000u; address < 0x002C0000u; address += 4u)
        if (const PS2Runtime::RecompiledFunction original = runtime.lookupFunction(address))
        {
            g_watchOriginals[address] = original;
            runtime.replaceFunction(address, watchWrapper);
            ++hooked;
        }
    std::fprintf(stderr, "[eewatch] watching %08X in %u functions\n", g_watchAddress, hooked);
}

#include "../ee_watch.h"
#include "runtime/ee_scheduler.h"

// GOW-Port: PS2X_EE_WATCH=<hex addr>[:<hex len>]: page-guard write watchpoint (ported from the PAL stack); logs the
// guest pc/ra of every store into the range, also from code that never returns (thread main loops).
void ps2InstallEePageWatch(PS2Runtime &runtime)
{
    const char *spec = std::getenv("PS2X_EE_WATCH");
    if (!spec)
        return;
    char *end = nullptr;
    const uint32_t guest = static_cast<uint32_t>(std::strtoul(spec, &end, 16)) & 0x1FFFFFFu;
    uint32_t length = 16;
    if (end && *end == ':')
        length = static_cast<uint32_t>(std::strtoul(end + 1, nullptr, 16));
    eewatch::install(runtime.memory().getRDRAM(), guest, length, [&runtime](uint32_t &pc, uint32_t &ra)
                     {
                         R5900Context *ctx = runtime.eeScheduler().currentContext();
                         pc = ctx ? ctx->pc : 0u;
                         ra = ctx ? getRegU32(ctx, 31) : 0u; });
}
