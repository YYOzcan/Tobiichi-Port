#include "runtime/ps2_memory.h"
#include "runtime/gs/gs_stage.h"
#include "runtime/gs/gs_display.h"
#include <chrono>
#include <map>
#include <string>
#include "runtime/ps2_address.h"
#include "runtime/gs/gs_frontend.h"
#include "ps2_log.h"
#include <atomic>
#include <cstdio>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
static const auto g_gowProcStart = std::chrono::steady_clock::now(); // GOW-Port: process start for diagnostics

namespace
{
    inline void inRange(uint32_t offset, size_t bytes, size_t regionSize, const char *op, uint32_t address)
    {
        if (static_cast<uint64_t>(offset) + static_cast<uint64_t>(bytes) > static_cast<uint64_t>(regionSize))
        {
            throw std::runtime_error(std::string(op) + " out-of-bounds at address: 0x" + std::to_string(address));
        }
    }

    template <typename T>
    inline T loadScalar(const uint8_t *base, uint32_t offset, size_t regionSize, const char *op, uint32_t address)
    {
        inRange(offset, sizeof(T), regionSize, op, address);
        T value{};
        std::memcpy(&value, base + offset, sizeof(T));
        return value;
    }

    template <typename T>
    inline void storeScalar(uint8_t *base, uint32_t offset, size_t regionSize, T value, const char *op, uint32_t address)
    {
        inRange(offset, sizeof(T), regionSize, op, address);
        std::memcpy(base + offset, &value, sizeof(T));
    }

    inline bool isGsPrivReg(uint32_t addr)
    {
        return Ps2AddressInRange(addr, PS2_GS_PRIV_REG_BASE, PS2_GS_PRIV_REG_SIZE);
    }

    inline bool isIoRegister(uint32_t addr)
    {
        return Ps2AddressInRange(addr, PS2_IO_BASE, PS2_IO_SIZE);
    }

    inline uint64_t *gsRegPtr(GSRegisters &gs, uint32_t addr)
    {
        // Support both 64-bit base offsets and +4 dword aliases.
        uint32_t off = (addr - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        switch (off)
        {
        case 0x0000:
            return &gs.pmode;
        case 0x0010:
            return &gs.smode1;
        case 0x0020:
            return &gs.smode2;
        case 0x0030:
            return &gs.srfsh;
        case 0x0040:
            return &gs.synch1;
        case 0x0050:
            return &gs.synch2;
        case 0x0060:
            return &gs.syncv;
        case 0x0070:
            return &gs.dispfb1;
        case 0x0080:
            return &gs.display1;
        case 0x0090:
            return &gs.dispfb2;
        case 0x00A0:
            return &gs.display2;
        case 0x00B0:
            return &gs.extbuf;
        case 0x00C0:
            return &gs.extdata;
        case 0x00D0:
            return &gs.extwrite;
        case 0x00E0:
            return &gs.bgcolor;
        // CSR (offset 0x1000) is intentionally not handled here: it is
        // std::atomic<uint64_t> and no longer converts to uint64_t*. Callers must
        // check for offset 0x1000 themselves and go through writeCsrHalf/
        // writeCsrFull/gs.csr.load() instead of gsRegPtr().
        case 0x1010:
            return &gs.imr;
        case 0x1040:
            return &gs.busdir;
        case 0x1080:
            return &gs.siglblid;
        default:
            return nullptr;
        }
    }

    constexpr uint32_t kGsCsrRegOffset = 0x1000u;

    // Atomically apply a 32-bit write to one half (off=0 low dword, off=4 high
    // dword) of the GS CSR register. Bits 0..1 of the low dword (SIGNAL/FINISH) are
    // write-one-to-clear; everything else is a plain merge. Uses compare_exchange
    // so the whole read-modify-write is a single atomic step -- this register is
    // also touched by the vsync worker (FIELD bit) and the GIF (SIGNAL/FINISH) on
    // other threads, so a load-then-store here would race with them.
    inline void writeCsrHalf(std::atomic<uint64_t> &csr, uint32_t off, uint32_t value)
    {
        constexpr uint32_t kW1cMask = 0x3u;
        uint64_t expected = csr.load();
        uint64_t desired;
        do
        {
            if (off == 0u)
            {
                uint32_t oldLow = static_cast<uint32_t>(expected & 0xFFFFFFFFull);
                uint32_t mergedLow = (oldLow & kW1cMask) | (value & ~kW1cMask);
                desired = (expected & 0xFFFFFFFF00000000ull) | static_cast<uint64_t>(mergedLow);
                desired &= ~static_cast<uint64_t>(value & kW1cMask);
            }
            else
            {
                uint64_t mask = 0xFFFFFFFFull << (off * 8u);
                desired = (expected & ~mask) | (static_cast<uint64_t>(value) << (off * 8u));
            }
        } while (!csr.compare_exchange_weak(expected, desired));
    }

    // Same as writeCsrHalf but for a full 64-bit CSR write (bits 0..1 are still
    // write-one-to-clear against the current value).
    inline void writeCsrFull(std::atomic<uint64_t> &csr, uint64_t value)
    {
        constexpr uint64_t kW1cMask = 0x3ull;
        uint64_t expected = csr.load();
        uint64_t desired;
        do
        {
            desired = (expected & kW1cMask) | (value & ~kW1cMask);
            desired &= ~(value & kW1cMask);
        } while (!csr.compare_exchange_weak(expected, desired));
    }

    constexpr std::array<uint32_t, 4> kEeTimerBases = {
        0x10000000u,
        0x10000800u,
        0x10001000u,
        0x10001800u,
    };
    constexpr uint32_t kEeTimerCountOffset = 0x00u;
    constexpr uint32_t kEeTimerModeOffset = 0x10u;
    constexpr uint32_t kEeTimerCompareOffset = 0x20u;
    constexpr uint32_t kEeTimerHoldOffset = 0x30u;
    constexpr uint32_t kEeTimerModeClksMask = 0x3u;
    constexpr uint32_t kEeTimerModeConfigMask = 0x3FFu;
    constexpr uint32_t kEeTimerModeStatusMask = 0xC00u;
    constexpr uint32_t kEeTimerModeZret = 1u << 6;
    constexpr uint32_t kEeTimerModeCue = 1u << 7;
    constexpr uint32_t kEeTimerModeCmpe = 1u << 8;
    constexpr uint32_t kEeTimerModeOvfe = 1u << 9;
    constexpr uint32_t kEeTimerModeEquf = 1u << 10;
    constexpr uint32_t kEeTimerModeOvff = 1u << 11;
    constexpr uint64_t kEeClockHz = 294912000ull;
    constexpr std::array<uint64_t, 4> kEeTimerClockHz = {
        147456000ull,
        9216000ull,
        576000ull,
        15734ull,
    };

    inline bool decodeEeTimerRegister(uint32_t address, size_t &timerIndex, uint32_t &offset)
    {
        for (size_t index = 0; index < kEeTimerBases.size(); ++index)
        {
            const uint32_t candidateOffset = address - kEeTimerBases[index];
            if (candidateOffset == kEeTimerCountOffset ||
                candidateOffset == kEeTimerModeOffset ||
                candidateOffset == kEeTimerCompareOffset ||
                (index < 2u && candidateOffset == kEeTimerHoldOffset))
            {
                timerIndex = index;
                offset = candidateOffset;
                return true;
            }
        }
        return false;
    }

    // No compare/overflow events and no zero-return: the count is a pure function of elapsed guest cycles.
    constexpr bool isClockOnlyEeTimer(uint32_t mode)
    {
        return (mode & (kEeTimerModeCmpe | kEeTimerModeOvfe | kEeTimerModeZret)) == 0u;
    }

    // Whole timer ticks in `cycles` guest EE cycles at `clockHz` (exact, no 64-bit overflow).
    constexpr uint64_t eeTimerTicks(uint64_t cycles, uint64_t clockHz)
    {
        return (cycles / kEeClockHz) * clockHz + (cycles % kEeClockHz) * clockHz / kEeClockHz;
    }

    // Fraction of a tick left over after eeTimerTicks, in the stepping model's clockRemainder units.
    constexpr uint64_t eeTimerRemainder(uint64_t cycles, uint64_t clockHz)
    {
        return (cycles % kEeClockHz) * clockHz % kEeClockHz;
    }

    constexpr uint64_t ticksUntilMatch(uint32_t count, uint32_t target)
    {
        const uint32_t distance = (target - count) & 0xFFFFu;
        return distance == 0u ? 0x10000ull : static_cast<uint64_t>(distance);
    }
}

// Helpers for GS VRAM addressing (PSMCT32 path).
static inline uint32_t gs_vram_offset(uint32_t basePage, uint32_t x, uint32_t y, uint32_t fbw)
{
    // basePage is in 2048-byte units; fbw is in blocks of 64 pixels.
    uint32_t strideBytes = fbw * 64 * 4;
    return basePage * 2048 + y * strideBytes + x * 4;
}

PS2Memory::PS2Memory()
    : m_rdram(nullptr), m_scratchpad(nullptr), iop_ram(nullptr), m_seenGifCopy(false), m_gsVRAM(nullptr)
{
    ps2SetScratchpadHostPtr(nullptr);
    const char *worker = std::getenv("PS2X_GS_WORKER");
    m_gsWorkerEnabled = worker != nullptr && worker[0] == '1';
    if (m_gsWorkerEnabled)
    {
        m_gsWorker = std::thread([this] { gsWorkerLoop(); });
        m_gsWorkerId = m_gsWorker.get_id();
        std::fprintf(stderr, "[gs-worker] VIF1/GIF processing on a worker thread (PS2X_GS_WORKER=1)\n");
    }
}

PS2Memory::~PS2Memory()
{
    stopGsWorker();
    if (m_rdram)
    {
        delete[] m_rdram;
        m_rdram = nullptr;
    }

    if (m_scratchpad)
    {
        ps2SetScratchpadHostPtr(nullptr);
        delete[] m_scratchpad;
        m_scratchpad = nullptr;
    }

    if (m_gsVRAM)
    {
        delete[] m_gsVRAM;
        m_gsVRAM = nullptr;
    }

    if (m_vu1Code)
    {
        delete[] m_vu1Code;
        m_vu1Code = nullptr;
    }
    if (m_vu1Data)
    {
        delete[] m_vu1Data;
        m_vu1Data = nullptr;
    }
    if (m_vu0Code)
    {
        delete[] m_vu0Code;
        m_vu0Code = nullptr;
    }
    if (m_vu0Data)
    {
        delete[] m_vu0Data;
        m_vu0Data = nullptr;
    }

    if (iop_ram)
    {
        delete[] iop_ram;
        iop_ram = nullptr;
    }
}

bool PS2Memory::initialize(size_t ramSize)
{
    auto cleanup = [this]()
    {
        delete[] m_rdram;
        delete[] m_scratchpad;
        delete[] iop_ram;
        delete[] m_gsVRAM;
        delete[] m_vu0Code;
        delete[] m_vu0Data;
        delete[] m_vu1Code;
        delete[] m_vu1Data;
        m_rdram = nullptr;
        m_scratchpad = nullptr;
        ps2SetScratchpadHostPtr(nullptr);
        iop_ram = nullptr;
        m_gsVRAM = nullptr;
        m_vu0Code = nullptr;
        m_vu0Data = nullptr;
        m_vu1Code = nullptr;
        m_vu1Data = nullptr;
    };

    cleanup();
    m_seenGifCopy = false;
    m_dmaStartCount.store(0, std::memory_order_relaxed);
    m_gifCopyCount.store(0, std::memory_order_relaxed);
    m_gsWriteCount.store(0, std::memory_order_relaxed);
    m_vifWriteCount.store(0, std::memory_order_relaxed);
    {
        std::lock_guard<std::mutex> lock(m_completedDmacMutex);
        m_completedDmacCauses.clear();
    }
    m_codeRegions.clear();
    m_path3Masked = false;
    m_path3MaskedFifo.clear();
    // GOW-Port: descartar cualquier DIRECT incompleto al inicializar VIF1.
    m_vif1DirectBytesRemaining = 0u;
    m_vif1DirectHl = false;
    m_vif1DirectPayload.clear();
    resetEeTimers();

    try
    {
        // Allocate main RAM
        m_rdram = new uint8_t[ramSize];
        std::memset(m_rdram, 0, ramSize);

        // Allocate scratchpad
        m_scratchpad = new uint8_t[PS2_SCRATCHPAD_SIZE];
        std::memset(m_scratchpad, 0, PS2_SCRATCHPAD_SIZE);
        ps2SetScratchpadHostPtr(m_scratchpad);

        // Initialize EE TLB entries (R5900 has 48 entries).
        m_tlbEntries.assign(48, TLBEntry{0, 0, 0, false});

        // Allocate IOP RAM
        iop_ram = new uint8_t[2 * 1024 * 1024]; // 2MB

        // Initialize IOP RAM with zeros
        std::memset(iop_ram, 0, 2 * 1024 * 1024);

        // Initialize I/O registers
        m_ioRegisters.clear();

        // Initialize GS registers
        memset(&gs_regs, 0, sizeof(gs_regs));
        // memset zero-fills std::atomic<uint64_t>::csr's bytes, which is not itself
        // a guaranteed-valid atomic store; make the zero-initialization explicit.
        gs_regs.csr.store(0);
        gs_regs.dispfb1 = (0ULL << 0) | (10ULL << 9) | (0ULL << 15) | (0ULL << 32) | (0ULL << 43);
        gs_regs.display1 = (0ULL << 0) | (0ULL << 12) | (0ULL << 23) | (0ULL << 27) | (639ULL << 32) | (447ULL << 44);
        gs_regs.dispfb2 = gs_regs.dispfb1;
        gs_regs.display2 = gs_regs.display1;

        // Allocate GS VRAM (4MB)
        m_gsVRAM = new uint8_t[PS2_GS_VRAM_SIZE];
        std::memset(m_gsVRAM, 0, PS2_GS_VRAM_SIZE);

        m_vu0Code = new uint8_t[PS2_VU0_CODE_SIZE];
        m_vu0Data = new uint8_t[PS2_VU0_DATA_SIZE];
        std::memset(m_vu0Code, 0, PS2_VU0_CODE_SIZE);
        std::memset(m_vu0Data, 0, PS2_VU0_DATA_SIZE);

        m_vu1Code = new uint8_t[PS2_VU1_CODE_SIZE];
        m_vu1Data = new uint8_t[PS2_VU1_DATA_SIZE];
        std::memset(m_vu1Code, 0, PS2_VU1_CODE_SIZE);
        std::memset(m_vu1Data, 0, PS2_VU1_DATA_SIZE);
        markVU0CodeModified();
        markVU1CodeModified();

        // Initialize VIF registers
        memset(&vif0_regs, 0, sizeof(vif0_regs));
        memset(&vif1_regs, 0, sizeof(vif1_regs));

        // Initialize DMA registers
        memset(dma_regs, 0, sizeof(dma_regs));

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error initializing PS2 memory: " << e.what() << std::endl;
        cleanup();
        return false;
    }
}

void PS2Memory::resetEeTimers() noexcept
{
    m_eeTimers = {};
    m_eeTimerPendingCycles = 0;
    m_eeTimerBudget = 0;
    m_eeCycleTotal = 0;
}

void PS2Memory::flushEeTimers() noexcept
{
    // pending < budget always holds, so this never crosses a timer event (no interrupt to raise here).
    if (m_eeTimerPendingCycles != 0u)
    {
        const uint64_t cycles = m_eeTimerPendingCycles;
        m_eeTimerPendingCycles = 0;
        (void)stepEeTimers(cycles);
    }
}

uint32_t PS2Memory::eeTimerCount(const EeTimer &timer) const noexcept
{
    if (!isClockOnlyEeTimer(timer.mode) || (timer.mode & kEeTimerModeCue) == 0u)
        return timer.count & 0xFFFFu; // stepping model (flushed by the caller) or stopped
    const uint64_t clockHz = kEeTimerClockHz[timer.mode & kEeTimerModeClksMask];
    return static_cast<uint32_t>(timer.count + eeTimerTicks(m_eeCycleTotal - timer.epoch, clockHz)) & 0xFFFFu;
}

namespace
{
    inline uint32_t eeTimerPhysical(uint32_t address)
    {
        return (address >= 0x80000000u && address < 0xC0000000u) ? (address & 0x1FFFFFFFu) : address;
    }
}

bool PS2Memory::isEeTimerRegister(uint32_t address) noexcept
{
    size_t index = 0u;
    uint32_t offset = 0u;
    return decodeEeTimerRegister(eeTimerPhysical(address), index, offset);
}

uint32_t PS2Memory::eeTimerLoad(uint32_t address) noexcept
{
    size_t index = 0u;
    uint32_t offset = 0u;
    if (!decodeEeTimerRegister(eeTimerPhysical(address), index, offset))
        return 0u;
    flushEeTimers();
    const EeTimer &timer = m_eeTimers[index];
    switch (offset)
    {
    case kEeTimerCountOffset:
    {
        const uint32_t count = eeTimerCount(timer);
        // GOW-Port: PS2X_TIMER_DIAG=1 prints the first count reads of each timer with its mode (clock source).
        static const bool diag = std::getenv("PS2X_TIMER_DIAG") != nullptr;
        static unsigned reads[4] = {};
        if (diag && (++reads[index] <= 3u || reads[index] % 20000u == 0u))
            std::fprintf(stderr, "[timer] T%zu read #%u count=%04x mode=%03x\n", index, reads[index], count,
                         timer.mode & 0x3FFu);
        return count;
    }
    case kEeTimerModeOffset:
        return timer.mode & (kEeTimerModeConfigMask | kEeTimerModeStatusMask);
    case kEeTimerCompareOffset:
        return timer.compare & 0xFFFFu;
    case kEeTimerHoldOffset:
        return timer.hold & 0xFFFFu;
    default:
        return 0u;
    }
}

bool PS2Memory::eeTimerStore(uint32_t address, uint32_t value) noexcept
{
    size_t index = 0u;
    uint32_t offset = 0u;
    if (!decodeEeTimerRegister(eeTimerPhysical(address), index, offset))
        return false;
    flushEeTimers();
    m_eeTimerBudget = 0; // recompute the distance to the next interrupt at the next advance
    EeTimer &timer = m_eeTimers[index];
    switch (offset)
    {
    case kEeTimerCountOffset:
        timer.count = value & 0xFFFFu;
        timer.clockRemainder = 0u;
        timer.epoch = m_eeCycleTotal;
        break;
    case kEeTimerModeOffset:
    {
        const uint32_t previousMode = timer.mode;
        const uint32_t status = (previousMode & kEeTimerModeStatusMask) & ~(value & kEeTimerModeStatusMask);
        const uint32_t mode = (value & kEeTimerModeConfigMask) | status;
        const bool clockChanged = ((previousMode ^ mode) & (kEeTimerModeClksMask | kEeTimerModeCue)) != 0u;
        const bool wasClockOnly = isClockOnlyEeTimer(previousMode) && (previousMode & kEeTimerModeCue) != 0u;
        if (wasClockOnly && (clockChanged || !isClockOnlyEeTimer(mode)))
        {
            // Leave the computed form: materialise the count; the stepping model continues with the exact
            // fraction of a tick when the clock is unchanged (what it would hold had it stepped all along).
            const uint64_t clockHz = kEeTimerClockHz[previousMode & kEeTimerModeClksMask];
            const uint64_t elapsed = m_eeCycleTotal - timer.epoch;
            timer.count = eeTimerCount(timer);
            timer.clockRemainder = clockChanged ? 0u : eeTimerRemainder(elapsed, clockHz);
            timer.epoch = m_eeCycleTotal;
        }
        else if (!wasClockOnly && isClockOnlyEeTimer(mode))
        {
            // Enter the computed form at the current count; a fraction of a tick of a running clock is dropped.
            timer.clockRemainder = 0u;
            timer.epoch = m_eeCycleTotal;
        }
        else if (clockChanged)
        {
            timer.clockRemainder = 0u;
        }
        timer.mode = mode;
        break;
    }
    case kEeTimerCompareOffset:
        timer.compare = value & 0xFFFFu;
        break;
    case kEeTimerHoldOffset:
        timer.hold = value & 0xFFFFu;
        break;
    default:
        return false;
    }
    return true;
}

uint32_t PS2Memory::advanceEeTimers(uint64_t eeCycles) noexcept
{
    if (eeCycles == 0u)
    {
        return 0u;
    }

    m_eeCycleTotal += eeCycles;
    m_eeTimerPendingCycles += eeCycles;
    if (m_eeTimerPendingCycles < m_eeTimerBudget)
    {
        return 0u;
    }
    const uint64_t cycles = m_eeTimerPendingCycles;
    m_eeTimerPendingCycles = 0;
    const uint32_t interruptMask = stepEeTimers(cycles);
    const uint64_t next = cyclesUntilNextEeTimerInterrupt();
    m_eeTimerBudget = next;
    return interruptMask;
}

uint32_t PS2Memory::stepEeTimers(uint64_t eeCycles) noexcept
{
    uint32_t interruptMask = 0u;
    for (size_t index = 0; index < m_eeTimers.size(); ++index)
    {
        EeTimer &timer = m_eeTimers[index];
        if ((timer.mode & kEeTimerModeCue) == 0u || isClockOnlyEeTimer(timer.mode))
        {
            continue; // stopped, or a clock-only timer whose count is computed when read (eeTimerCount)
        }

        const uint64_t clockHz = kEeTimerClockHz[timer.mode & kEeTimerModeClksMask];
        const uint64_t wholeSeconds = eeCycles / kEeClockHz;
        const uint64_t remainingCycles = eeCycles % kEeClockHz;
        const uint64_t scaled = remainingCycles * clockHz + timer.clockRemainder;
        const uint64_t ticks = wholeSeconds * clockHz + scaled / kEeClockHz;
        timer.clockRemainder = scaled % kEeClockHz;
        if (ticks == 0u)
        {
            continue;
        }

        const uint32_t oldCount = timer.count & 0xFFFFu;
        const uint32_t compare = timer.compare & 0xFFFFu;
        const uint64_t compareDistance = ticksUntilMatch(oldCount, compare);
        const uint64_t overflowDistance = 0x10000ull - oldCount;
        const bool zeroReturn = (timer.mode & kEeTimerModeZret) != 0u;
        const bool compareReached = ticks >= compareDistance;
        bool overflowReached = false;

        if (zeroReturn)
        {
            overflowReached = ticks >= overflowDistance && overflowDistance <= compareDistance;
            if (compareReached)
            {
                const uint64_t remaining = ticks - compareDistance;
                timer.count = compare == 0u
                                  ? static_cast<uint32_t>(remaining & 0xFFFFu)
                                  : static_cast<uint32_t>(remaining % compare);
            }
            else
            {
                timer.count = static_cast<uint32_t>((oldCount + ticks) & 0xFFFFu);
            }
        }
        else
        {
            overflowReached = ticks >= overflowDistance;
            timer.count = static_cast<uint32_t>((oldCount + ticks) & 0xFFFFu);
        }

        if (compareReached && (timer.mode & kEeTimerModeCmpe) != 0u && (timer.mode & kEeTimerModeEquf) == 0u)
        {
            timer.mode |= kEeTimerModeEquf;
            interruptMask |= 1u << index;
        }
        if (overflowReached && (timer.mode & kEeTimerModeOvfe) != 0u && (timer.mode & kEeTimerModeOvff) == 0u)
        {
            timer.mode |= kEeTimerModeOvff;
            interruptMask |= 1u << index;
        }
    }
    return interruptMask;
}

uint64_t PS2Memory::cyclesUntilNextEeTimerInterrupt() const noexcept
{
    uint64_t nearest = std::numeric_limits<uint64_t>::max();
    for (const EeTimer &timer : m_eeTimers)
    {
        if ((timer.mode & kEeTimerModeCue) == 0u)
        {
            continue;
        }

        const uint32_t count = timer.count & 0xFFFFu;
        const uint32_t compare = timer.compare & 0xFFFFu;
        const uint64_t compareDistance = ticksUntilMatch(count, compare);
        const uint64_t overflowDistance = 0x10000ull - count;
        uint64_t eventTicks = std::numeric_limits<uint64_t>::max();

        if ((timer.mode & kEeTimerModeCmpe) != 0u &&
            (timer.mode & kEeTimerModeEquf) == 0u)
        {
            eventTicks = compareDistance;
        }
        const bool overflowCanOccur = (timer.mode & kEeTimerModeZret) == 0u ||
                                      overflowDistance <= compareDistance;
        if (overflowCanOccur &&
            (timer.mode & kEeTimerModeOvfe) != 0u &&
            (timer.mode & kEeTimerModeOvff) == 0u)
        {
            eventTicks = std::min(eventTicks, overflowDistance);
        }
        if (eventTicks == std::numeric_limits<uint64_t>::max())
        {
            continue;
        }

        const uint64_t clockHz = kEeTimerClockHz[timer.mode & kEeTimerModeClksMask];
        const uint64_t numerator = eventTicks * kEeClockHz - timer.clockRemainder;
        const uint64_t cycles = (numerator + clockHz - 1u) / clockHz;
        nearest = std::min(nearest, std::max<uint64_t>(1u, cycles));
    }
    // The timer state is as of the last advance; m_eeTimerPendingCycles (< nearest) have elapsed since.
    if (nearest == std::numeric_limits<uint64_t>::max())
    {
        return nearest;
    }
    return std::max<uint64_t>(1u, nearest - m_eeTimerPendingCycles);
}

bool PS2Memory::isScratchpad(uint32_t address) const
{
    return ps2IsScratchpadAddress(address);
}

uint8_t *PS2Memory::mapVuMemory(uint32_t physAddr, uint32_t size, uint32_t &offset, uint32_t &limit)
{
    return const_cast<uint8_t *>(static_cast<const PS2Memory *>(this)->mapVuMemory(physAddr, size, offset, limit));
}

const uint8_t *PS2Memory::mapVuMemory(uint32_t physAddr, uint32_t size, uint32_t &offset, uint32_t &limit) const
{
    auto mapRange = [&](uint32_t base, uint32_t rangeSize, const uint8_t *ptr) -> const uint8_t *
    {
        if (!ptr || physAddr < base)
        {
            return nullptr;
        }
        const uint32_t local = physAddr - base;
        if (local >= rangeSize || size > (rangeSize - local))
        {
            return nullptr;
        }
        offset = local;
        limit = rangeSize;
        return ptr;
    };

    if (const uint8_t *ptr = mapRange(PS2_VU0_CODE_BASE, PS2_VU0_CODE_SIZE, m_vu0Code))
    {
        return ptr;
    }
    if (const uint8_t *ptr = mapRange(PS2_VU0_DATA_BASE, PS2_VU0_DATA_SIZE, m_vu0Data))
    {
        return ptr;
    }
    if (const uint8_t *ptr = mapRange(PS2_VU1_CODE_BASE, PS2_VU1_CODE_SIZE, m_vu1Code))
    {
        return ptr;
    }
    return mapRange(PS2_VU1_DATA_BASE, PS2_VU1_DATA_SIZE, m_vu1Data);
}

uint32_t PS2Memory::translateAddress(uint32_t virtualAddress)
{
    if (isScratchpad(virtualAddress))
    {
        return ps2ScratchpadOffset(virtualAddress);
    }

    // EE uncached aliases of main RAM (per PS2 memory map):
    //   0x20000000-0x3FFFFFFF -> 32MB mirror of RDRAM
    // This includes the accelerated window rooted at 0x30100000.
    if (Ps2IsUncachedRamMirrorAddress(virtualAddress))
    {
        return virtualAddress & PS2_RAM_MASK;
    }

    // KSEG0/KSEG1 direct-mapped window.
    if (Ps2IsKseg01Address(virtualAddress))
    {
        return Ps2DirectMappedPhysicalAddress(virtualAddress);
    }

    // In this runtime, low segments are treated as physical-style addresses already.
    if (virtualAddress < 0x80000000)
    {
        return virtualAddress;
    }

    // KSEG2/KSEG3 are TLB mapped.
    if (Ps2IsKseg23Address(virtualAddress))
    {
        for (const auto &entry : m_tlbEntries)
        {
            if (entry.valid)
            {
                // PageMask uses bits [24:13]. Build an address-level mask (plus 4KB base page bits).
                const uint32_t mask = entry.mask & 0x01FFE000u;
                const uint32_t compareMask = ~(mask | 0xFFFu);
                if ((virtualAddress & compareMask) == (entry.vpn & compareMask))
                {
                    // TLB hit
                    const uint32_t pageOffsetMask = mask | 0xFFFu;
                    const uint32_t physBase = entry.pfn << 12;
                    return physBase | (virtualAddress & pageOffsetMask);
                }
            }
        }
        throw std::runtime_error("TLB miss for address: 0x" + std::to_string(virtualAddress));
    }

    return virtualAddress;
}

bool PS2Memory::tlbRead(uint32_t index, uint32_t &vpn, uint32_t &pfn, uint32_t &mask, bool &valid) const
{
    if (index >= m_tlbEntries.size())
    {
        return false;
    }

    const TLBEntry &entry = m_tlbEntries[index];
    vpn = entry.vpn;
    pfn = entry.pfn;
    mask = entry.mask;
    valid = entry.valid;
    return true;
}

bool PS2Memory::tlbWrite(uint32_t index, uint32_t vpn, uint32_t pfn, uint32_t mask, bool valid)
{
    if (index >= m_tlbEntries.size())
    {
        return false;
    }

    TLBEntry &entry = m_tlbEntries[index];
    entry.vpn = vpn & 0xFFFFF000u;
    entry.pfn = pfn & 0x000FFFFFu;
    entry.mask = mask & 0x01FFE000u;
    entry.valid = valid;
    return true;
}

int32_t PS2Memory::tlbProbe(uint32_t vpn) const
{
    const uint32_t normalizedVpn = vpn & 0xFFFFF000u;
    for (uint32_t i = 0; i < static_cast<uint32_t>(m_tlbEntries.size()); ++i)
    {
        const TLBEntry &entry = m_tlbEntries[i];
        if (!entry.valid)
        {
            continue;
        }

        const uint32_t mask = entry.mask & 0x01FFE000u;
        const uint32_t compareMask = ~(mask | 0xFFFu);
        if ((normalizedVpn & compareMask) == (entry.vpn & compareMask))
        {
            return static_cast<int32_t>(i);
        }
    }

    return -1;
}

uint8_t PS2Memory::read8(uint32_t address)
{
    syncGsWorkerFor(address);
    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        return m_scratchpad[physAddr];
    }
    if (physAddr < PS2_RAM_SIZE)
    {
        return m_rdram[physAddr];
    }
    uint32_t vuOffset = 0;
    uint32_t vuLimit = 0;
    if (const uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint8_t), vuOffset, vuLimit))
    {
        (void)vuLimit;
        return vuMem[vuOffset];
    }
    else if (isIoRegister(physAddr))
    {
        uint32_t regAddr = physAddr & ~0x3;
        uint32_t value = readIORegister(regAddr);
        uint32_t shift = (physAddr & 3) * 8;
        return static_cast<uint8_t>((value >> shift) & 0xFF);
    }

    return 0;
}

uint16_t PS2Memory::read16(uint32_t address)
{
    syncGsWorkerFor(address);
    if (address & 1)
    {
        throw std::runtime_error("Unaligned 16-bit read at address: 0x" + std::to_string(address));
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        return loadScalar<uint16_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, "read16 scratchpad", address);
    }
    if (physAddr < PS2_RAM_SIZE)
    {
        return loadScalar<uint16_t>(m_rdram, physAddr, PS2_RAM_SIZE, "read16 rdram", address);
    }
    uint32_t vuOffset = 0;
    uint32_t vuLimit = 0;
    if (const uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint16_t), vuOffset, vuLimit))
    {
        return loadScalar<uint16_t>(vuMem, vuOffset, vuLimit, "read16 vu", address);
    }
    else if (isIoRegister(physAddr))
    {
        uint32_t regAddr = physAddr & ~0x3;
        uint32_t value = readIORegister(regAddr);
        uint32_t shift = (physAddr & 2) * 8;
        return static_cast<uint16_t>((value >> shift) & 0xFFFF);
    }

    return 0;
}

uint32_t PS2Memory::read32(uint32_t address)
{
    syncGsWorkerFor(address);
    if (address & 3)
    {
        throw std::runtime_error("Unaligned 32-bit read at address: 0x" + std::to_string(address));
    }

    if (isGsPrivReg(address))
    {
        uint32_t off = address & 7;
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            uint64_t val = gs_regs.csr.load();
            return (uint32_t)(val >> (off * 8));
        }
        uint64_t *reg = gsRegPtr(gs_regs, address);
        if (!reg)
            return 0;
        uint64_t val = *reg;
        return (uint32_t)(val >> (off * 8));
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        return loadScalar<uint32_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, "read32 scratchpad", address);
    }
    if (physAddr < PS2_RAM_SIZE)
    {
        return loadScalar<uint32_t>(m_rdram, physAddr, PS2_RAM_SIZE, "read32 rdram", address);
    }
    uint32_t vuOffset = 0;
    uint32_t vuLimit = 0;
    if (const uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint32_t), vuOffset, vuLimit))
    {
        return loadScalar<uint32_t>(vuMem, vuOffset, vuLimit, "read32 vu", address);
    }
    else if (isIoRegister(physAddr))
    {
        return readIORegister(physAddr);
    }

    return 0;
}

uint64_t PS2Memory::read64(uint32_t address)
{
    syncGsWorkerFor(address);
    if (address & 7)
    {
        throw std::runtime_error("Unaligned 64-bit read at address: 0x" + std::to_string(address));
    }

    if (isGsPrivReg(address))
    {
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            return gs_regs.csr.load();
        }
        uint64_t *reg = gsRegPtr(gs_regs, address);
        return reg ? *reg : 0;
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        return loadScalar<uint64_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, "read64 scratchpad", address);
    }
    if (physAddr < PS2_RAM_SIZE)
    {
        return loadScalar<uint64_t>(m_rdram, physAddr, PS2_RAM_SIZE, "read64 rdram", address);
    }
    uint32_t vuOffset = 0;
    uint32_t vuLimit = 0;
    if (const uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint64_t), vuOffset, vuLimit))
    {
        return loadScalar<uint64_t>(vuMem, vuOffset, vuLimit, "read64 vu", address);
    }

    // 64-bit IO read: compose from the two adjacent 32-bit IO register slots
    // to avoid any side-effects from read32 handlers.
    if (isIoRegister(address))
    {
        uint32_t lo = m_ioRegisters.count(address) ? m_ioRegisters[address] : 0u;
        uint32_t hi = m_ioRegisters.count(address + 4) ? m_ioRegisters[address + 4] : 0u;
        return static_cast<uint64_t>(lo) | (static_cast<uint64_t>(hi) << 32);
    }
    return (uint64_t)read32(address) | ((uint64_t)read32(address + 4) << 32);
}

__m128i PS2Memory::read128(uint32_t address)
{
    syncGsWorkerFor(address);
    if (address & 15)
    {
        throw std::runtime_error("Unaligned 128-bit read at address: 0x" + std::to_string(address));
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        inRange(physAddr, sizeof(__m128i), PS2_SCRATCHPAD_SIZE, "read128 scratchpad", address);
        return _mm_loadu_si128(reinterpret_cast<__m128i *>(&m_scratchpad[physAddr]));
    }
    if (physAddr < PS2_RAM_SIZE)
    {
        inRange(physAddr, sizeof(__m128i), PS2_RAM_SIZE, "read128 rdram", address);
        return _mm_loadu_si128(reinterpret_cast<__m128i *>(&m_rdram[physAddr]));
    }
    uint32_t vuOffset = 0;
    uint32_t vuLimit = 0;
    if (const uint8_t *vuMem = mapVuMemory(physAddr, sizeof(__m128i), vuOffset, vuLimit))
    {
        inRange(vuOffset, sizeof(__m128i), vuLimit, "read128 vu", address);
        return _mm_loadu_si128(reinterpret_cast<const __m128i *>(vuMem + vuOffset));
    }

    // 128-bit reads are primarily for quad-word loads in the EE, which are only valid for RAM areas
    // Return zeroes for unsupported areas
    return _mm_setzero_si128();
}

void PS2Memory::write8(uint32_t address, uint8_t value)
{
    syncGsWorkerFor(address);
    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        m_scratchpad[physAddr] = value;
    }
    else if (physAddr < PS2_RAM_SIZE)
    {
        m_rdram[physAddr] = value;
    }
    else
    {
        uint32_t vuOffset = 0;
        uint32_t vuLimit = 0;
        if (uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint8_t), vuOffset, vuLimit))
        {
            (void)vuLimit;
            vuMem[vuOffset] = value;
            if (vuMem == m_vu0Code)
                markVU0CodeModified();
            else if (vuMem == m_vu1Code)
                markVU1CodeModified();
            return;
        }
    }
    if (isIoRegister(physAddr))
    {
        // IO registers - handle byte writes by modifying the appropriate byte in the word
        uint32_t regAddr = physAddr & ~0x3;
        uint32_t shift = (physAddr & 3) * 8;
        uint32_t mask = ~(0xFF << shift);
        uint32_t newValue = (m_ioRegisters[regAddr] & mask) | ((uint32_t)value << shift);
        writeIORegister(regAddr, newValue);
    }
}

void PS2Memory::write16(uint32_t address, uint16_t value)
{
    syncGsWorkerFor(address);
    if (address & 1)
    {
        throw std::runtime_error("Unaligned 16-bit write at address: 0x" + std::to_string(address));
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        storeScalar<uint16_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, value, "write16 scratchpad", address);
    }
    else if (physAddr < PS2_RAM_SIZE)
    {
        storeScalar<uint16_t>(m_rdram, physAddr, PS2_RAM_SIZE, value, "write16 rdram", address);
    }
    else
    {
        uint32_t vuOffset = 0;
        uint32_t vuLimit = 0;
        if (uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint16_t), vuOffset, vuLimit))
        {
            storeScalar<uint16_t>(vuMem, vuOffset, vuLimit, value, "write16 vu", address);
            if (vuMem == m_vu0Code)
                markVU0CodeModified();
            else if (vuMem == m_vu1Code)
                markVU1CodeModified();
            return;
        }
    }
    if (isIoRegister(physAddr))
    {
        uint32_t regAddr = physAddr & ~0x3;
        uint32_t shift = (physAddr & 2) * 8;
        uint32_t mask = ~(0xFFFF << shift);
        uint32_t newValue = (m_ioRegisters[regAddr] & mask) | ((uint32_t)value << shift);
        writeIORegister(regAddr, newValue);
    }
}

void PS2Memory::write32(uint32_t address, uint32_t value)
{
    syncGsWorkerFor(address);
    if (address & 3)
    {
        throw std::runtime_error("Unaligned 32-bit write at address: 0x" + std::to_string(address));
    }

    if (isGsPrivReg(address))
    {
        uint32_t off = address & 7;
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            // CSR: bits 0..1 of the low dword are write-one-to-clear status bits.
            // Done as a single atomic RMW -- see writeCsrHalf's comment.
            writeCsrHalf(gs_regs.csr, off, value);
        }
        else if (uint64_t *reg = gsRegPtr(gs_regs, address))
        {
            uint64_t mask = 0xFFFFFFFFULL << (off * 8);
            uint64_t newVal = (*reg & ~mask) | ((uint64_t)value << (off * 8));
            *reg = newVal;
        }
        return;
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        storeScalar<uint32_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, value, "write32 scratchpad", address);
    }
    else if (physAddr < PS2_RAM_SIZE)
    {
        // Check if this might be code modification
        markModified(address, 4);

        storeScalar<uint32_t>(m_rdram, physAddr, PS2_RAM_SIZE, value, "write32 rdram", address);
    }
    else
    {
        uint32_t vuOffset = 0;
        uint32_t vuLimit = 0;
        if (uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint32_t), vuOffset, vuLimit))
        {
            storeScalar<uint32_t>(vuMem, vuOffset, vuLimit, value, "write32 vu", address);
            if (vuMem == m_vu0Code)
                markVU0CodeModified();
            else if (vuMem == m_vu1Code)
                markVU1CodeModified();
            return;
        }
    }
    if (isIoRegister(physAddr))
    {
        writeIORegister(physAddr, value);
    }
}

void PS2Memory::write64(uint32_t address, uint64_t value)
{
    syncGsWorkerFor(address);
    if (address & 7)
    {
        throw std::runtime_error("Unaligned 64-bit write at address: 0x" + std::to_string(address));
    }

    if (isGsPrivReg(address))
    {
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            // CSR: bits 0..1 are write-one-to-clear status bits. Done as a single
            // atomic RMW -- see writeCsrFull's comment.
            writeCsrFull(gs_regs.csr, value);
        }
        else if (uint64_t *reg = gsRegPtr(gs_regs, address))
        {
            *reg = value;
        }
        return;
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (scratch)
    {
        storeScalar<uint64_t>(m_scratchpad, physAddr, PS2_SCRATCHPAD_SIZE, value, "write64 scratchpad", address);
    }
    else if (physAddr < PS2_RAM_SIZE)
    {
        markModified(address, 8);
        storeScalar<uint64_t>(m_rdram, physAddr, PS2_RAM_SIZE, value, "write64 rdram", address);
    }
    else
    {
        uint32_t vuOffset = 0;
        uint32_t vuLimit = 0;
        if (uint8_t *vuMem = mapVuMemory(physAddr, sizeof(uint64_t), vuOffset, vuLimit))
        {
            storeScalar<uint64_t>(vuMem, vuOffset, vuLimit, value, "write64 vu", address);
            if (vuMem == m_vu0Code)
                markVU0CodeModified();
            else if (vuMem == m_vu1Code)
                markVU1CodeModified();
            return;
        }
    }
    if (isIoRegister(physAddr))
    {
        write32(address, (uint32_t)value);
        write32(address + 4, (uint32_t)(value >> 32));
    }
}

void PS2Memory::write128(uint32_t address, __m128i value)
{
    syncGsWorkerFor(address);
    if (address & 15)
    {
        throw std::runtime_error("Unaligned 128-bit write at address: 0x" + std::to_string(address));
    }

    const bool scratch = isScratchpad(address);
    uint32_t physAddr = translateAddress(address);

    if (!scratch && physAddr == 0x10004000u) // VIF0_FIFO
    {
        alignas(16) uint8_t fifoData[16];
        _mm_storeu_si128(reinterpret_cast<__m128i *>(fifoData), value);
        processVIF0Data(fifoData, sizeof(fifoData));
        return;
    }
    if (!scratch && physAddr == 0x10005000u) // VIF1_FIFO
    {
        alignas(16) uint8_t fifoData[16];
        _mm_storeu_si128(reinterpret_cast<__m128i *>(fifoData), value);
        processVIF1Data(fifoData, sizeof(fifoData));
        return;
    }

    if (scratch)
    {
        inRange(physAddr, sizeof(__m128i), PS2_SCRATCHPAD_SIZE, "write128 scratchpad", address);
        _mm_storeu_si128(reinterpret_cast<__m128i *>(&m_scratchpad[physAddr]), value);
    }
    else if (physAddr < PS2_RAM_SIZE)
    {
        markModified(address, 16);
        inRange(physAddr, sizeof(__m128i), PS2_RAM_SIZE, "write128 rdram", address);
        _mm_storeu_si128(reinterpret_cast<__m128i *>(&m_rdram[physAddr]), value);
    }
    else
    {
        uint32_t vuOffset = 0;
        uint32_t vuLimit = 0;
        if (uint8_t *vuMem = mapVuMemory(physAddr, sizeof(__m128i), vuOffset, vuLimit))
        {
            inRange(vuOffset, sizeof(__m128i), vuLimit, "write128 vu", address);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(vuMem + vuOffset), value);
            if (vuMem == m_vu0Code)
                markVU0CodeModified();
            else if (vuMem == m_vu1Code)
                markVU1CodeModified();
            return;
        }
    }
    if (isIoRegister(physAddr))
    {
        // Non-RAM 128-bit stores are modeled as two 64-bit stores.
        uint64_t lo = _mm_extract_epi64(value, 0);
        uint64_t hi = _mm_extract_epi64(value, 1);

        write64(address, lo);
        write64(address + 8, hi);
    }
}

bool PS2Memory::writeIORegister(uint32_t address, uint32_t value)
{
    syncGsWorkerFor(address);
    size_t timerIndex = 0u;
    uint32_t timerOffset = 0u;
    if (decodeEeTimerRegister(address, timerIndex, timerOffset))
    {
        return eeTimerStore(address, value);
    }
    if (isEeDmaRegister(address))
    {
        return eeDmaStore(address, value);
    }

    if (isGsPrivReg(address))
    {
        // NB: unreachable from write8/16/32/64 today since those all funnel IO
        // register writes through addresses in PS2_IO_BASE's range, which is
        // disjoint from PS2_GS_PRIV_REG_BASE; kept correct for direct callers.
        m_ioRegisters[address] = value;
        const uint32_t off = address & 7u;
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            writeCsrHalf(gs_regs.csr, off, value);
        }
        else if (uint64_t *reg = gsRegPtr(gs_regs, address))
        {
            const uint64_t mask = 0xFFFFFFFFull << (off * 8u);
            *reg = (*reg & ~mask) | (static_cast<uint64_t>(value) << (off * 8u));
        }
        m_gsWriteCount.fetch_add(1, std::memory_order_relaxed);
        return true;
    }

    if (address >= 0x10002000 && address <= 0x10002030)
    {
        if (address == 0x10002010)
        {
            m_ioRegisters[address] = value & ~(1u << 31);
            if (value & (1u << 30))
            {
                m_ioRegisters[0x10002000] = 0;
                m_ioRegisters[0x10002020] = 0;
                m_ioRegisters[0x10002030] = 0;
            }
        }
        else
        {
            m_ioRegisters[address] = value;
        }
        return true;
    }

    m_ioRegisters[address] = value;

    if (address >= 0x10003C00u && address < 0x10003E00u)
    {
        m_vifWriteCount.fetch_add(1, std::memory_order_relaxed);

        switch (address)
        {
        case 0x10003C10u:     // VIF1_FBRST
            if (value & 0x1u) // RST
            {
                const bool wasPath3Masked = m_path3Masked;
                std::memset(&vif1_regs, 0, sizeof(vif1_regs));
                // GOW-Port: FBRST también descarta la carga DIRECT pendiente y su prioridad.
                m_vif1DirectBytesRemaining = 0u;
                m_vif1DirectHl = false;
                m_vif1DirectPayload.clear();
                m_path3Masked = false;
                if (wasPath3Masked)
                    flushMaskedPath3Packets();
            }
            if (value & 0x8u) // STC
            {
                vif1_regs.stat &= ~((1u << 8) | (1u << 9) | (1u << 10) | (1u << 11) | (1u << 12) | (1u << 13));
            }
            break;
        case 0x10003C30u:
            vif1_regs.mark = value & 0xFFFFu;
            vif1_regs.stat &= ~(1u << 6); // clear MRK flag on CPU write
            break;
        case 0x10003C40u:
            vif1_regs.cycle = value & 0xFFFFu;
            break;
        case 0x10003C50u:
            vif1_regs.mode = value & 0x3u;
            break;
        case 0x10003C60u:
            vif1_regs.num = value & 0xFFu;
            break;
        case 0x10003C70u:
            vif1_regs.mask = value;
            break;
        case 0x10003C80u:
            vif1_regs.code = value;
            break;
        case 0x10003C90u:
            vif1_regs.itops = value & 0x3FFu;
            break;
        case 0x10003CA0u:
            vif1_regs.base = value & 0x3FFu;
            break;
        case 0x10003CB0u:
            vif1_regs.ofst = value & 0x3FFu;
            break;
        case 0x10003CC0u:
            vif1_regs.tops = value & 0x3FFu;
            break;
        case 0x10003CD0u:
            vif1_regs.itop = value & 0x3FFu;
            break;
        case 0x10003CE0u:
            vif1_regs.top = value & 0x3FFu;
            break;
        default:
            break;
        }

        return true;
    }

    if (address >= 0x10003800u && address < 0x10003A00u)
    {
        m_vifWriteCount.fetch_add(1, std::memory_order_relaxed);
        return true;
    }

    if (address >= 0x10000000 && address < 0x10010000)
    {
        if (address >= 0x10000200 && address < 0x10000300)
        {
            return true;
        }
        if (address >= 0x10000000 && address < 0x10000100)
        {
            return true;
        }
    }

    return false;
}

// GOW-Port: native DMA request service (see ps2_memory.h).
bool PS2Memory::isEeDmaRegister(uint32_t address) noexcept
{
    if (address >= 0xC0000000u || (address >= 0x20000000u && address < 0x80000000u))
        return false; // KSEG2/3, scratchpad and the uncached RAM mirror are never DMA registers
    const uint32_t phys = address & 0x1FFFFFFFu;
    return (phys >= 0x10008000u && phys < 0x1000F000u) || phys == 0x1000F520u || phys == 0x1000F590u;
}

uint32_t PS2Memory::eeDmaLoad(uint32_t address) noexcept
{
    if ((address & 0x1FFFFFFFu) == 0x1000F520u)
        return 0u; // D_ENABLER: DMA is never suspended (see eeDmaStore)
    const auto it = m_ioRegisters.find(address & 0x1FFFFFFFu);
    return it != m_ioRegisters.end() ? it->second : 0u;
}

bool PS2Memory::eeDmaStore(uint32_t address, uint32_t value)
{
    address &= 0x1FFFFFFFu;
    // D_STAT: the game clears its DMA-end bits after its scratchpad copies; no DMA status is kept, transfers are
    // complete when the store that starts them returns (docs/native-port.md, step 2).
    if (address == 0x1000E010u)
        return true;
    // D_ENABLEW: libdma and the movie player suspend DMA (CPND) around channel setup. No transfer runs in the
    // background, so there is nothing to suspend: the store is dropped and D_ENABLER reads 0 (never suspended).
    if (address == 0x1000F590u || address == 0x1000F520u)
        return true;
    m_ioRegisters[address] = value;
    // DMA channel registers written by game code (the boot VIF0 chain 0x1838D0, the scratchpad copies, VIF1's
    // tag-transfer bit set by 0x13F700) are latched; a CHCR store with STR runs that transfer natively now and its
    // DMA-end handlers after the store. VIF1 / GIF packets are normally sent through sceDmaSend (Stubs/DMA.cpp).
    {
        if ((address & 0xFFu) != 0u || (value & 0x100u) == 0u)
            return true;
        const uint32_t channelBase = address & 0xFFFFFF00u;
        m_ioRegisters[address] = value & ~0x100u;
        m_dmaStartCount.fetch_add(1, std::memory_order_relaxed);

        // GOW-Port: PS2X_EE_WATCH_WORD also reports scratchpad DMAs that change the watched RAM word.
        static const uint32_t watchWord = [] {
            const char *v = std::getenv("PS2X_EE_WATCH_WORD");
            return v ? static_cast<uint32_t>(std::strtoul(v, nullptr, 16)) & 0x01FFFFFCu : 0u;
        }();
        uint32_t watchBefore = 0u;
        if (watchWord)
            std::memcpy(&watchBefore, m_rdram + watchWord, 4);
        if (tryProcessScratchpadDma(channelBase, value))
        {
            if (watchWord)
            {
                uint32_t watchAfter;
                std::memcpy(&watchAfter, m_rdram + watchWord, 4);
                static unsigned reports = 0u;
                if (watchAfter != watchBefore && ++reports <= 40u)
                    std::fprintf(stderr, "[eewatch] SPR DMA %08x chcr=%08x: %08x -> %08x\n", channelBase, value,
                                 watchBefore, watchAfter);
            }
            return true;
        }

        DmaPath path;
        uint32_t cause;
        switch (channelBase)
        {
        case 0x10008000u: path = DmaPath::Vif0; cause = 0u; break;
        case 0x10009000u: path = DmaPath::Vif1; cause = 1u; break;
        case 0x1000A000u: path = DmaPath::Gif; cause = 2u; break;
        case 0x1000B000u:
        case 0x1000B400u:
            // fromIPU / toIPU: the movie player feeds its bitstream to the IPU this way; the native MPEG decoder
            // (Stubs/MPEG.cpp) takes the video from the PSS data the game demuxes (sceMpegDemuxPss): nothing to move.
            return true;
        default:
        {
            static unsigned reports = 0u;
            if (++reports <= 20u)
                std::fprintf(stderr, "[dma] channel %08x started by game code is not handled (chcr=%08x)\n", channelBase, value);
            return true;
        }
        }
        if (((value >> 2u) & 0x3u) == 1u)
            sendDmaChain(path, m_ioRegisters[channelBase + 0x30u]);
        else
            sendDma(path, m_ioRegisters[channelBase + 0x10u], m_ioRegisters[channelBase + 0x20u] & 0xFFFFu);
        queueCompletedDmacCause(cause);
        return true;
    }
}

// GOW-Port: native display service entry (see ps2_memory.h, runtime/gs/gs_display.h).
bool PS2Memory::isGsDisplayRegister(uint32_t address) noexcept
{
    if (address >= 0xC0000000u || (address >= 0x20000000u && address < 0x80000000u))
        return false;
    switch (address & 0x1FFFFFFFu)
    {
    case 0x12000000u: case 0x12000020u: case 0x12000070u: case 0x12000080u:
    case 0x12000090u: case 0x120000A0u: case 0x120000E0u:
        return true;
    default:
        return false;
    }
}

bool PS2Memory::isGsStatusRegister(uint32_t address) noexcept
{
    return address < 0xC0000000u && !(address >= 0x20000000u && address < 0x80000000u) &&
           (address & 0x1FFFFFFFu) == 0x12001000u;
}

void PS2Memory::gsDisplayStore(uint32_t address, uint64_t value)
{
    GSDisplayState state = ps2_gs_display::display(*this);
    switch (address & 0x1FFFFFFFu)
    {
    case 0x12000000u: state.pmode = value; break;
    case 0x12000020u: state.smode2 = value; break;
    case 0x12000070u: state.dispfb1 = value; break;
    case 0x12000080u: state.display1 = value; break;
    case 0x12000090u: state.dispfb2 = value; break;
    case 0x120000A0u: state.display2 = value; break;
    case 0x120000E0u: state.bgcolor = value; break;
    default: return;
    }
    ps2_gs_display::setDisplay(*this, state);
}

uint64_t PS2Memory::gsStatusLoad()
{
    return ps2_gs_display::status(*this);
}

bool PS2Memory::tryProcessScratchpadDma(uint32_t channelBase, uint32_t chcr)
{
    static constexpr uint32_t kSprFromChannel = 0x1000D000u;
    static constexpr uint32_t kSprToChannel = 0x1000D400u;
    if (channelBase != kSprFromChannel && channelBase != kSprToChannel)
        return false;

    const uint32_t mode = (chcr >> 2u) & 0x3u;
    // GOW-Port: modo cadena. fromSPR usa cadena de destino (etiquetas en el scratchpad que indican
    // la dirección de RAM) y toSPR cadena de origen (etiquetas en RAM, datos seguidos en el scratchpad).
    // God of War copia así la paleta de huesos que CalcSkinHierarchy deja en el scratchpad; sin esto
    // los paquetes de VU1 quedaban a cero y los personajes se dibujaban como polígonos gigantes.
    if (mode == 1u)
        return processScratchpadChain(channelBase, chcr);
    if (mode != 0u)
    {
        // GOW-Port: interleave (MOD=2) is not implemented; report it so a missing transfer is visible.
        static unsigned reports = 0u;
        if (++reports <= 20u)
            std::fprintf(stderr, "[dma] SPR %s mode %u not handled (chcr=%08x qwc=%u madr=%08x sadr=%04x)\n",
                         channelBase == 0x1000D000u ? "fromSPR" : "toSPR", mode, chcr,
                         m_ioRegisters[channelBase + 0x20u] & 0xFFFFu, m_ioRegisters[channelBase + 0x10u],
                         m_ioRegisters[channelBase + 0x80u] & 0x3FF0u);
        return false;
    }

    const uint32_t qwc = m_ioRegisters[channelBase + 0x20u] & 0xFFFFu;
    const uint32_t byteCount = qwc * 16u;
    const uint32_t originalMadr = m_ioRegisters[channelBase + 0x10u] & 0x7FFFFFF0u;
    const uint32_t originalSadr = m_ioRegisters[channelBase + 0x80u] & 0x3FF0u;

    uint32_t mainOffset = 0u;
    try
    {
        mainOffset = translateAddress(originalMadr);
    }
    catch (const std::exception &)
    {
        return false;
    }

    if (mainOffset > PS2_RAM_SIZE || byteCount > PS2_RAM_SIZE - mainOffset)
        return false;

    const bool fromScratchpad = channelBase == kSprFromChannel;
    uint32_t scratchOffset = originalSadr;
    uint32_t bytesLeft = byteCount;
    uint32_t copied = 0u;
    while (bytesLeft != 0u)
    {
        const uint32_t scratchChunk = PS2_SCRATCHPAD_SIZE - scratchOffset;
        const uint32_t chunk = std::min(bytesLeft, scratchChunk);
        if (fromScratchpad)
        {
            std::memcpy(m_rdram + mainOffset + copied, m_scratchpad + scratchOffset, chunk);
            markModified(mainOffset + copied, chunk);
        }
        else
        {
            std::memcpy(m_scratchpad + scratchOffset, m_rdram + mainOffset + copied, chunk);
        }

        copied += chunk;
        bytesLeft -= chunk;
        scratchOffset = (scratchOffset + chunk) & (PS2_SCRATCHPAD_SIZE - 1u);
    }

    m_ioRegisters[channelBase + 0x10u] = (originalMadr + byteCount) & 0x7FFFFFF0u;
    m_ioRegisters[channelBase + 0x20u] = 0u;
    m_ioRegisters[channelBase + 0x80u] = (originalSadr + byteCount) & 0x3FF0u;
    queueCompletedDmacCause(fromScratchpad ? 8u : 9u);
    return true;
}

// GOW-Port: cadenas DMA del scratchpad (canales 8 y 9), según la especificación del DMAC del EE.
bool PS2Memory::processScratchpadChain(uint32_t channelBase, uint32_t chcr)
{
    static constexpr uint32_t kSprFromChannel = 0x1000D000u;
    static constexpr int kMaxTags = 1 << 16;
    const bool fromScratchpad = channelBase == kSprFromChannel;
    const bool tieEnabled = (chcr & (1u << 7)) != 0u;
    uint32_t sadr = m_ioRegisters[channelBase + 0x80u] & 0x3FF0u;
    uint32_t madr = m_ioRegisters[channelBase + 0x10u] & 0x7FFFFFF0u;
    uint32_t lastTagUpper = (chcr >> 16u) & 0xFFFFu;
    auto copyToSpr = [&](const uint8_t *src, uint32_t bytes)
    {
        for (uint32_t done = 0u; done < bytes;)
        {
            const uint32_t chunk = std::min(bytes - done, PS2_SCRATCHPAD_SIZE - sadr);
            std::memcpy(m_scratchpad + sadr, src + done, chunk);
            done += chunk;
            sadr = (sadr + chunk) & (PS2_SCRATCHPAD_SIZE - 1u);
        }
    };
    // Origen en RAM o en el propio scratchpad (bit 31 de la dirección de la etiqueta).
    auto sourcePointer = [&](uint32_t address, uint32_t bytes) -> const uint8_t *
    {
        if ((address & 0x80000000u) != 0u || isScratchpad(address))
        {
            const uint32_t offset = address & (PS2_SCRATCHPAD_SIZE - 1u);
            return offset + bytes <= PS2_SCRATCHPAD_SIZE ? m_scratchpad + offset : nullptr;
        }
        uint32_t offset = 0u;
        try { offset = translateAddress(address); } catch (const std::exception &) { return nullptr; }
        return offset < PS2_RAM_SIZE && bytes <= PS2_RAM_SIZE - offset ? m_rdram + offset : nullptr;
    };

    if (fromScratchpad)
    {
        // Cadena de destino: etiqueta {QWC, ID, IRQ, ADDR} en el scratchpad; ID 0 = cnts, 1 = cnt, 7 = end.
        for (int tags = 0; tags < kMaxTags; ++tags)
        {
            uint64_t tag = 0u;
            std::memcpy(&tag, m_scratchpad + sadr, sizeof(tag));
            sadr = (sadr + 16u) & (PS2_SCRATCHPAD_SIZE - 1u);
            const uint32_t qwc = static_cast<uint32_t>(tag & 0xFFFFu);
            const uint32_t id = static_cast<uint32_t>((tag >> 28u) & 0x7u);
            const bool irq = ((tag >> 31u) & 1u) != 0u;
            lastTagUpper = static_cast<uint32_t>((tag >> 16u) & 0xFFFFu);
            madr = static_cast<uint32_t>(tag >> 32u) & 0x7FFFFFF0u;
            uint32_t offset = 0u;
            bool valid = true;
            try { offset = translateAddress(madr); } catch (const std::exception &) { valid = false; }
            const uint32_t bytes = qwc * 16u;
            if (valid && offset < PS2_RAM_SIZE && bytes <= PS2_RAM_SIZE - offset)
            {
                for (uint32_t done = 0u; done < bytes;)
                {
                    const uint32_t chunk = std::min(bytes - done, PS2_SCRATCHPAD_SIZE - sadr);
                    std::memcpy(m_rdram + offset + done, m_scratchpad + sadr, chunk);
                    done += chunk;
                    sadr = (sadr + chunk) & (PS2_SCRATCHPAD_SIZE - 1u);
                }
                markModified(offset, bytes);
            }
            else
            {
                sadr = (sadr + bytes) & (PS2_SCRATCHPAD_SIZE - 1u);
            }
            madr += bytes;
            if (id == 7u || (id != 0u && id != 1u) || (irq && tieEnabled))
                break;
        }
    }
    else
    {
        // Cadena de origen: etiquetas en RAM (como VIF/GIF); los datos se escriben seguidos en el scratchpad.
        uint32_t tadr = m_ioRegisters[channelBase + 0x30u];
        uint32_t asp = (chcr >> 4u) & 0x3u;
        uint32_t asr[2] = {m_ioRegisters[channelBase + 0x40u], m_ioRegisters[channelBase + 0x50u]};
        const bool transferTag = (chcr & 0x40u) != 0u;
        for (int tags = 0; tags < kMaxTags; ++tags)
        {
            const uint8_t *tagPointer = sourcePointer(tadr, 16u);
            if (!tagPointer)
                break;
            uint64_t tag = 0u;
            std::memcpy(&tag, tagPointer, sizeof(tag));
            const uint32_t qwc = static_cast<uint32_t>(tag & 0xFFFFu);
            const uint32_t id = static_cast<uint32_t>((tag >> 28u) & 0x7u);
            const bool irq = ((tag >> 31u) & 1u) != 0u;
            const uint32_t addr = static_cast<uint32_t>(tag >> 32u) & 0xFFFFFFF0u;
            lastTagUpper = static_cast<uint32_t>((tag >> 16u) & 0xFFFFu);
            uint32_t data = tadr + 16u;
            bool end = false;
            switch (id)
            {
            case 0u: data = addr; tadr += 16u; end = true; break; // refe
            case 1u: tadr = data + qwc * 16u; break;              // cnt
            case 2u: tadr = addr; break;                          // next
            case 3u: case 4u: data = addr; tadr += 16u; break;    // ref, refs
            case 5u:                                              // call
                if (asp < 2u) asr[asp++] = data + qwc * 16u;
                tadr = addr;
                break;
            case 6u:                                              // ret
                if (asp > 0u) tadr = asr[--asp];
                else end = true;
                break;
            default: end = true; break;                           // end
            }
            if (transferTag)
                copyToSpr(tagPointer, 16u);
            if (qwc != 0u)
            {
                if (const uint8_t *source = sourcePointer(data, qwc * 16u))
                    copyToSpr(source, qwc * 16u);
                else
                    sadr = (sadr + qwc * 16u) & (PS2_SCRATCHPAD_SIZE - 1u);
            }
            madr = data + qwc * 16u;
            if (end || (irq && tieEnabled))
                break;
        }
        m_ioRegisters[channelBase + 0x30u] = tadr;
        m_ioRegisters[channelBase + 0x40u] = asr[0];
        m_ioRegisters[channelBase + 0x50u] = asr[1];
        chcr = (chcr & ~(0x3u << 4u)) | ((asp & 0x3u) << 4u);
    }

    m_ioRegisters[channelBase + 0x00u] = (chcr & 0x0000FFFFu) | (lastTagUpper << 16u);
    m_ioRegisters[channelBase + 0x10u] = madr & 0x7FFFFFF0u;
    m_ioRegisters[channelBase + 0x20u] = 0u;
    m_ioRegisters[channelBase + 0x80u] = sadr & 0x3FF0u;
    queueCompletedDmacCause(fromScratchpad ? 8u : 9u);
    return true;
}

static void gsWorkerTrace(const char *what, size_t bytes);

// GOW-Port: native DMA data path (docs/native-port.md, step 2). Bytes of guest memory (RAM or scratchpad) in order, with
// the RAM wrap of the former transfer loops.
void PS2Memory::appendGuestBytes(uint32_t address, uint32_t bytes, std::vector<uint8_t> &out)
{
    const bool scratch = isScratchpad(address);
    uint32_t offset = 0u;
    try
    {
        offset = translateAddress(address);
    }
    catch (const std::exception &)
    {
        return;
    }
    const uint8_t *base = scratch ? m_scratchpad : m_rdram;
    const uint32_t size = scratch ? PS2_SCRATCHPAD_SIZE : PS2_RAM_SIZE;
    while (bytes != 0u)
    {
        if (offset >= size)
            offset = 0u;
        const uint32_t chunk = std::min(bytes, size - offset);
        out.insert(out.end(), base + offset, base + offset + chunk);
        bytes -= chunk;
        offset += chunk;
    }
}

void PS2Memory::sendDma(DmaPath path, uint32_t address, uint32_t qwc)
{
    std::vector<uint8_t> bytes;
    appendGuestBytes(address, qwc * 16u, bytes);
    deliverDma(path, std::move(bytes));
}

// The game's DMA tag list (source chain): {QWC, ID, IRQ, ADDR} tags; refe/cnt/next/ref/refs/call/ret/end, a call stack
// of two. VIF tag lists with the tag-transfer bit (VIF1 CHCR bit 6, set by the game at boot) carry two VIFcodes in each
// tag's upper half, which go to the VIF before the tag's data. An IRQ tag ends the list (sceDmaSend sets TIE).
void PS2Memory::sendDmaChain(DmaPath path, uint32_t tagAddress)
{
    static constexpr int kMaxTags = 1 << 20;
    const uint32_t chcr = path == DmaPath::Vif0 ? 0x10008000u : path == DmaPath::Vif1 ? 0x10009000u : 0x1000A000u;
    const auto config = m_ioRegisters.find(chcr);
    const bool transferTags = path != DmaPath::Gif && config != m_ioRegisters.end() && (config->second & 0x40u) != 0u;
    uint32_t returnStack[2] = {};
    uint32_t depth = 0u;
    std::vector<uint8_t> bytes;
    int tags = 0;
    for (; tags < kMaxTags; ++tags)
    {
        const bool scratch = isScratchpad(tagAddress);
        uint32_t offset = 0u;
        try
        {
            offset = translateAddress(tagAddress);
        }
        catch (const std::exception &)
        {
            break;
        }
        const uint8_t *base = scratch ? m_scratchpad : m_rdram;
        if (offset + 16u > (scratch ? PS2_SCRATCHPAD_SIZE : PS2_RAM_SIZE))
            break;
        uint64_t tag = 0u;
        std::memcpy(&tag, base + offset, sizeof(tag));
        const uint32_t qwc = static_cast<uint32_t>(tag & 0xFFFFu);
        const uint32_t id = static_cast<uint32_t>((tag >> 28u) & 0x7u);
        const bool irq = ((tag >> 31u) & 1u) != 0u;
        const uint32_t addr = static_cast<uint32_t>((tag >> 32u) & 0x7FFFFFFFu);
        if ((tag >> 63u) != 0u)
        {
            static unsigned sprTags = 0;
            if (++sprTags <= 20u || sprTags % 100000u == 0u)
                std::fprintf(stderr, "[dma] chain tag with SPR flag #%u path=%u id=%u addr=%08x qwc=%u\n", sprTags,
                             static_cast<unsigned>(path), id, addr, qwc);
        }

        uint32_t data = tagAddress + 16u;
        bool end = false;
        switch (id)
        {
        case 0u: data = addr; tagAddress += 16u; end = true; break; // refe
        case 1u: tagAddress = data + qwc * 16u; break;              // cnt
        case 2u: tagAddress = addr; break;                          // next
        case 3u: case 4u: data = addr; tagAddress += 16u; break;    // ref, refs
        case 5u:                                                    // call
            if (depth < 2u)
                returnStack[depth++] = data + qwc * 16u;
            tagAddress = addr;
            break;
        case 6u:                                                    // ret
            if (depth > 0u)
                tagAddress = returnStack[--depth];
            else
                end = true;
            break;
        default: end = true; break;                                 // end
        }

        {
            static const double bigFrom = std::getenv("GOW_DMA_BIGTAGS") ? std::atof(std::getenv("GOW_DMA_BIGTAGS")) : -1.0;
            static const auto bigT0 = std::chrono::steady_clock::now();
            const bool bigTags = bigFrom >= 0.0 && std::chrono::duration<double>(std::chrono::steady_clock::now() - bigT0).count() >= bigFrom;
            static unsigned bigCount = 0;
            if (bigTags && path != DmaPath::Gif && qwc >= 200u && ++bigCount <= 400u)
                std::fprintf(stderr, "[dma-big] path=%u id=%u data=%08x qwc=%u\n", static_cast<unsigned>(path), id, data, qwc);
        }
        {
            // GOW_DMA_BLOCKDUMP=<file>:<from s>:<len s>: append [u32 addr][u32 qwc][data] of every VIF chain block.
            static const char *spec = std::getenv("GOW_DMA_BLOCKDUMP");
            if (spec && path != DmaPath::Gif && qwc >= 4u && qwc <= 2000u)
            {
                static std::string dumpPath; static double from = 0, len = 1;
                static const auto t0 = g_gowProcStart;
                static bool init = [&] { dumpPath = spec; size_t c2 = dumpPath.rfind(':'); size_t c1 = (c2 == std::string::npos || c2 == 0) ? std::string::npos : dumpPath.rfind(':', c2 - 1); if (c1 != std::string::npos && c1 > 1) { from = std::atof(dumpPath.c_str() + c1 + 1); len = std::atof(dumpPath.c_str() + c2 + 1); dumpPath.resize(c1); } return true; }();
                (void)init;
                const double now = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
                if (now >= from && now < from + len && !isScratchpad(data) && (data & 0x01FFFFFFu) + qwc * 16u <= PS2_RAM_SIZE)
                    if (FILE *df = std::fopen(dumpPath.c_str(), "ab"))
                    {
                        const uint32_t hdr[2] = {data, qwc};
                        std::fwrite(hdr, 4, 2, df); std::fwrite(m_rdram + (data & 0x01FFFFFFu), 16, qwc, df); std::fclose(df);
                    }
            }
        }

        if (transferTags)
            bytes.insert(bytes.end(), base + offset + 8u, base + offset + 16u);
        if (qwc != 0u)
            appendGuestBytes(data, qwc * 16u, bytes);
        if (end || irq)
            break;
    }
    if (tags >= kMaxTags)
        std::fprintf(stderr, "[dma] chain on path %u stopped after %d tags at 0x%08x\n", static_cast<unsigned>(path), tags,
                     tagAddress);
    deliverDma(path, std::move(bytes));
}

// VIF0 packets are decoded now (VU0). VIF1 and GIF packets go to the GS worker in order (PS2X_GS_WORKER=1, the play
// configuration), or are decoded now and the GIF paths drained.
void PS2Memory::deliverDma(DmaPath path, std::vector<uint8_t> &&bytes)
{
    if (bytes.empty())
        return;
    m_dmaStartCount.fetch_add(1, std::memory_order_relaxed);
    const uint32_t size = static_cast<uint32_t>(bytes.size());
    if (path == DmaPath::Vif0)
    {
        processVIF0Data(bytes.data(), size);
        return;
    }
    if (m_gsWorkerEnabled)
    {
        GsWorkerJob job;
        job.fbrst = m_fbrstProvider ? m_fbrstProvider() : 0u;
        job.items.push_back(GsWorkerItem{path == DmaPath::Vif1, std::move(bytes)});
        gsWorkerTrace("kick", size);
        {
            std::lock_guard<std::mutex> lock(m_gsWorkerMutex);
            m_gsWorkerJobs.push_back(std::move(job));
        }
        m_gsWorkerCv.notify_one();
        return;
    }
    if (path == DmaPath::Vif1)
    {
        processVIF1Data(bytes.data(), size);
    }
    else
    {
        m_seenGifCopy = true;
        m_gifCopyCount.fetch_add(1, std::memory_order_relaxed);
        submitGifPacket(GifPathId::Path3, bytes.data(), size, false);
    }
    if (m_gifArbiter)
        m_gifArbiter->drain();
}

// GOW-Port: PS2X_GS_WORKER_TRACE (see PS2Runtime::dispatchGuestBranch): worker kick/start/done times.
static void gsWorkerTrace(const char *what, size_t bytes)
{
    static const double traceFrom = [] { const char *v = std::getenv("PS2X_GS_WORKER_TRACE"); return v ? std::atof(v) : -1.0; }();
    if (traceFrom < 0.0)
        return;
    static const auto traceStart = std::chrono::steady_clock::now();
    const auto now = std::chrono::steady_clock::now();
    const double s = std::chrono::duration<double>(now - traceStart).count();
    if (s >= traceFrom && s < traceFrom + 2.0)
        std::fprintf(stderr, "[gsw-trace] %.0f %s %zu\n",
                     std::chrono::duration<double, std::micro>(now.time_since_epoch()).count(), what, bytes);
}

void PS2Memory::runGsWorkerJob(GsWorkerJob &job)
{
    size_t traceBytes = 0;
    for (const GsWorkerItem &item : job.items)
        traceBytes += item.data.size();
    gsWorkerTrace("job-start", traceBytes);
    struct TraceDone { size_t bytes; ~TraceDone() { gsWorkerTrace("job-done", bytes); } } traceDone{traceBytes};
    m_gsWorkerJobFbrst = job.fbrst;
    for (GsWorkerItem &item : job.items)
    {
        const uint32_t size = static_cast<uint32_t>(item.data.size());
        if (item.vif1)
        {
            processVIF1Data(item.data.data(), size);
        }
        else
        {
            m_seenGifCopy = true;
            m_gifCopyCount.fetch_add(1, std::memory_order_relaxed);
            submitGifPacket(GifPathId::Path3, item.data.data(), size, false);
        }
    }
    if (m_gifArbiter)
        m_gifArbiter->drain();
}

void PS2Memory::gsWorkerLoop()
{
    for (;;)
    {
        GsWorkerJob job;
        {
            std::unique_lock<std::mutex> lock(m_gsWorkerMutex);
            m_gsWorkerBusy = false;
            if (m_gsWorkerJobs.empty())
                m_gsWorkerIdleCv.notify_all();
            m_gsWorkerCv.wait(lock, [this] { return m_gsWorkerStop || !m_gsWorkerJobs.empty(); });
            if (m_gsWorkerJobs.empty())
                return; // stop requested and nothing left
            job = std::move(m_gsWorkerJobs.front());
            m_gsWorkerJobs.pop_front();
            m_gsWorkerBusy = true;
        }
        try
        {
            runGsWorkerJob(job);
        }
        catch (const std::exception &e)
        {
            std::fprintf(stderr, "[gs-worker] job failed: %s\n", e.what());
        }
        if (m_gsWorkerWake && (gs_regs.csr.load(std::memory_order_acquire) & 0x3u) != 0u)
            m_gsWorkerWake();
    }
}

void PS2Memory::syncGsWorker(const char *site)
{
    if (ps2_gs_stage::onStageThread())
        return; // GOW-Port: the stage runs queued worker output; it must not wait for itself
    if (m_gsWorkerEnabled && !onGsWorkerThread())
        waitGsWorkerIdle(site, 0u);
}

void PS2Memory::syncGsWorkerFor(uint32_t address)
{
    if (ps2_gs_stage::onStageThread())
        return; // GOW-Port: the stage runs queued worker output; it must not wait for itself
    if (m_gsWorkerEnabled && needsGsWorkerSync(address) && !onGsWorkerThread())
        waitGsWorkerIdle(nullptr, address);
}

void PS2Memory::syncGsWorkerIfOtherThread(const char *site)
{
    if (ps2_gs_stage::onStageThread())
        return; // GOW-Port: the stage runs queued worker output; it must not wait for itself
    if (m_gsWorkerEnabled && !onGsWorkerThread())
        waitGsWorkerIdle(site, 0u);
}

namespace
{
    // PS2X_GS_WORKER_DIAG=1: every 5 s, the sync sites that made the EE wait for the worker.
    struct GsWorkerSyncDiag
    {
        struct Entry { uint64_t syncs = 0, waits = 0, waitUs = 0; };
        std::mutex mutex;
        std::map<std::string, Entry> sites;
        std::chrono::steady_clock::time_point next = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    };
    bool gsWorkerSyncDiagEnabled()
    {
        static const bool on = [] { const char *v = std::getenv("PS2X_GS_WORKER_DIAG"); return v && v[0] == '1'; }();
        return on;
    }
}

void PS2Memory::waitGsWorkerIdle(const char *site, uint32_t address)
{
    std::unique_lock<std::mutex> lock(m_gsWorkerMutex);
    const bool busy = !m_gsWorkerJobs.empty() || m_gsWorkerBusy;
    const auto start = std::chrono::steady_clock::now();
    if (busy)
        m_gsWorkerIdleCv.wait(lock, [this] { return m_gsWorkerJobs.empty() && !m_gsWorkerBusy; });
    lock.unlock();
    ps2_gs_stage::waitIdle(); // GOW-Port: the GS frontend stage is part of the worker (gs_stage.h)
    if (!gsWorkerSyncDiagEnabled())
        return;
    static GsWorkerSyncDiag diag;
    const auto now = std::chrono::steady_clock::now();
    char key[48];
    if (site)
        std::snprintf(key, sizeof(key), "%s", site);
    else
        std::snprintf(key, sizeof(key), "mmio 0x%08X", address & ~0xFu);
    std::lock_guard<std::mutex> diagLock(diag.mutex);
    auto &entry = diag.sites[key];
    ++entry.syncs;
    if (busy)
    {
        ++entry.waits;
        entry.waitUs += static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now - start).count());
    }
    if (now >= diag.next)
    {
        diag.next = now + std::chrono::seconds(5);
        for (const auto &[name, e] : diag.sites)
            if (e.waits)
                std::fprintf(stderr, "[gs-worker:sync] %s syncs=%llu waits=%llu wait_ms=%.1f\n", name.c_str(),
                             static_cast<unsigned long long>(e.syncs), static_cast<unsigned long long>(e.waits),
                             e.waitUs / 1000.0);
        diag.sites.clear();
    }
}

void PS2Memory::stopGsWorker()
{
    if (!m_gsWorker.joinable())
        return;
    {
        std::lock_guard<std::mutex> lock(m_gsWorkerMutex);
        m_gsWorkerStop = true;
    }
    m_gsWorkerCv.notify_all();
    m_gsWorker.join();
    m_gsWorkerEnabled = false;
    ps2_gs_stage::stop();
}

// EE accesses that observe or change state owned by the worker while it runs.
bool PS2Memory::needsGsWorkerSync(uint32_t address) const
{
    // 0x70000000 (scratchpad) would alias 0x10003xxx once masked.
    if (isScratchpad(address))
        return false;
    const uint32_t phys = address & 0x1FFFFFFFu;
    return isGsPrivReg(address) || isGsPrivReg(phys) ||
           (phys >= 0x10003000u && phys < 0x10004000u) || // GIF and VIF0/VIF1 registers
           (phys >= 0x10005000u && phys < 0x10007000u) || // VIF1 / GIF FIFOs
           (phys >= 0x11008000u && phys < 0x11010000u);   // VU1 micro and data memory
}

void PS2Memory::queueCompletedDmacCause(uint32_t cause)
{
    std::lock_guard<std::mutex> lock(m_completedDmacMutex);
    m_completedDmacCauses.push_back(cause);
}

std::vector<uint32_t> PS2Memory::consumeCompletedDmacCauses()
{
    std::lock_guard<std::mutex> lock(m_completedDmacMutex);
    std::vector<uint32_t> causes;
    causes.swap(m_completedDmacCauses);
    return causes;
}

void PS2Memory::flushMaskedPath3Packets(bool drainImmediately)
{
    syncGsWorkerIfOtherThread("flushMaskedPath3");
    if (m_path3Masked || m_path3MaskedFifo.empty())
        return;

    auto emit = [&](const uint8_t *packetData, uint32_t packetSize)
    {
        if (m_gifArbiter)
            m_gifArbiter->submit(GifPathId::Path3, packetData, packetSize, false);
        else if (m_gifPacketCallback)
            m_gifPacketCallback(packetData, packetSize);
    };

    for (const auto &packet : m_path3MaskedFifo)
    {
        if (packet.size() >= 16u)
            emit(packet.data(), static_cast<uint32_t>(packet.size()));
    }
    m_path3MaskedFifo.clear();

    if (m_gifArbiter && drainImmediately)
        m_gifArbiter->drain();
}

void PS2Memory::submitGifPacket(GifPathId pathId, const uint8_t *data, uint32_t sizeBytes, bool drainImmediately, bool path2DirectHl)
{
    syncGsWorkerIfOtherThread("submitGifPacket");
    if (!data || sizeBytes < 16)
        return;

    if (pathId == GifPathId::Path3)
    {
        if (m_path3Masked)
        {
            m_path3MaskedFifo.emplace_back(data, data + sizeBytes);
            return;
        }
        flushMaskedPath3Packets(false);
    }

    if (m_gifArbiter)
        m_gifArbiter->submit(pathId, data, sizeBytes, path2DirectHl);
    else if (m_gifPacketCallback)
        m_gifPacketCallback(data, sizeBytes);

    if (m_gifArbiter && drainImmediately)
        m_gifArbiter->drain();
}

void PS2Memory::processGIFPacket(uint32_t srcPhysAddr, uint32_t qwCount)
{
    syncGsWorkerIfOtherThread("processGIFPacket");
    if (!m_rdram || qwCount == 0)
        return;
    const uint64_t bytes64 = static_cast<uint64_t>(qwCount) * 16ull;
    uint32_t sizeBytes = (bytes64 > 0xFFFFFFFFull) ? 0xFFFFFFFFu : static_cast<uint32_t>(bytes64);
    uint32_t bytesLeft = sizeBytes;
    while (bytesLeft >= 16)
    {
        if (srcPhysAddr >= PS2_RAM_SIZE)
            srcPhysAddr = 0;
        uint32_t chunk = bytesLeft;
        if (srcPhysAddr + chunk > PS2_RAM_SIZE)
            chunk = PS2_RAM_SIZE - srcPhysAddr;
        if (chunk == 0)
            break;

        m_seenGifCopy = true;
        m_gifCopyCount.fetch_add(1, std::memory_order_relaxed);
        submitGifPacket(GifPathId::Path3, m_rdram + srcPhysAddr, chunk);

        bytesLeft -= chunk;
        srcPhysAddr += chunk;
    }
}

void PS2Memory::processGIFPacket(const uint8_t *data, uint32_t sizeBytes)
{
    if (m_gifArbiter)
        submitGifPacket(GifPathId::Path3, data, sizeBytes);
    else if (m_gifPacketCallback && data && sizeBytes >= 16)
        m_gifPacketCallback(data, sizeBytes);
}

uint32_t PS2Memory::readIORegister(uint32_t address)
{
    syncGsWorkerFor(address);
    size_t timerIndex = 0u;
    uint32_t timerOffset = 0u;
    if (decodeEeTimerRegister(address, timerIndex, timerOffset))
    {
        return eeTimerLoad(address);
    }
    if (isEeDmaRegister(address))
    {
        return eeDmaLoad(address);
    }

    if (isGsPrivReg(address))
    {
        // NB: unreachable from read8/16/32/64 today, same reasoning as the write
        // path above; kept correct for direct callers.
        const uint32_t off = address & 7u;
        const uint32_t regOff = (address - PS2_GS_PRIV_REG_BASE) & ~0x7u;
        if (regOff == kGsCsrRegOffset)
        {
            return static_cast<uint32_t>((gs_regs.csr.load() >> (off * 8u)) & 0xFFFFFFFFull);
        }
        if (uint64_t *reg = gsRegPtr(gs_regs, address))
        {
            return static_cast<uint32_t>((*reg >> (off * 8u)) & 0xFFFFFFFFull);
        }
        return 0u;
    }

    if (address >= 0x10002000 && address <= 0x10002030)
    {
        uint32_t val = 0;
        switch (address)
        {
        case 0x10002000:
            val = m_ioRegisters[address];
            break;
        case 0x10002010:
            val = m_ioRegisters[address] & ~(1u << 31);
            break;
        case 0x10002020:
        case 0x10002030:
            val = m_ioRegisters[address];
            break;
        default:
            val = 0;
            break;
        }
        return val;
    }

    if (address == 0x10003020u) // GIF_STAT
    {
        uint32_t stat = m_ioRegisters.count(address) ? m_ioRegisters[address] : 0u;
        const uint32_t mode = m_ioRegisters.count(0x10003010u) ? m_ioRegisters[0x10003010u] : 0u;
        const uint32_t ctrl = m_ioRegisters.count(0x10003000u) ? m_ioRegisters[0x10003000u] : 0u;

        // M3R and IMT mirror GIF_MODE, PSE mirrors GIF_CTRL, and M3P is the
        // effective PATH3 mask controlled by the VIF1 MSKPATH3 command.
        stat = (stat & ~0xFu) |
               (mode & 0x1u) |
               (m_path3Masked ? 0x2u : 0u) |
               (mode & 0x4u) |
               (ctrl & 0x8u);
        return stat;
    }

    if (address >= 0x10000000 && address < 0x10010000)
    {
        if (address >= 0x10000200 && address < 0x10000300)
        {
            return 0;
        }

        if (address >= 0x1000F200 && address <= 0x1000F260)
        {
            if (address == 0x1000F230)
            {
                return 0x60000;
            }
            if (address == 0x1000F240)
            {
                return 0xF0000002;
            }
            return 0;
        }
    }

    auto it = m_ioRegisters.find(address);
    if (it != m_ioRegisters.end())
    {
        return it->second;
    }

    return 0;
}

void PS2Memory::registerCodeRegion(uint32_t start, uint32_t end)
{
    if (end <= start)
    {
        std::cerr << "Ignoring invalid code region: start=0x" << std::hex << start
                  << " end=0x" << end << std::dec << std::endl;
        return;
    }

    if ((end - start) > PS2_RAM_SIZE)
    {
        std::cerr << "Ignoring oversized code region: start=0x" << std::hex << start
                  << " end=0x" << end << std::dec << std::endl;
        return;
    }

    for (const auto &existing : m_codeRegions)
    {
        if (existing.start == start && existing.end == end)
        {
            return;
        }
    }

    CodeRegion region;
    region.start = start;
    region.end = end;

    size_t sizeInWords = (end - start + 3u) / 4u;
    region.modified.resize(sizeInWords, false);

    m_codeRegions.push_back(region);
    RUNTIME_LOG("Registered code region: " << std::hex << start << " - " << end << std::dec);
}

bool PS2Memory::isAddressInRegion(uint32_t address, const CodeRegion &region)
{
    return (address >= region.start && address < region.end);
}

bool PS2Memory::isCodeAddress(uint32_t address) const
{
    for (const auto &region : m_codeRegions)
    {
        if (address >= region.start && address < region.end)
        {
            return true;
        }
    }
    return false;
}

void PS2Memory::markModified(uint32_t address, uint32_t size)
{
    if (size == 0)
    {
        return;
    }

    const uint64_t writeEnd = static_cast<uint64_t>(address) + static_cast<uint64_t>(size);
    for (auto &region : m_codeRegions)
    {
        const uint64_t regionStart = region.start;
        const uint64_t regionEnd = region.end;
        if (writeEnd <= regionStart || static_cast<uint64_t>(address) >= regionEnd)
        {
            continue;
        }

        uint32_t overlapStart = static_cast<uint32_t>(std::max<uint64_t>(address, regionStart));
        uint32_t overlapEnd = static_cast<uint32_t>(std::min<uint64_t>(writeEnd, regionEnd));

        for (uint32_t addr = overlapStart; addr < overlapEnd; addr += 4)
        {
            size_t bitIndex = (addr - region.start) / 4;
            if (bitIndex < region.modified.size())
            {
                region.modified[bitIndex] = true;
                RUNTIME_LOG("Marked code at " << std::hex << addr << std::dec << " as modified");
            }
        }
    }
}

bool PS2Memory::isCodeModified(uint32_t address, uint32_t size)
{
    if (size == 0)
    {
        return false;
    }

    const uint64_t writeEnd = static_cast<uint64_t>(address) + static_cast<uint64_t>(size);
    for (const auto &region : m_codeRegions)
    {
        const uint64_t regionStart = region.start;
        const uint64_t regionEnd = region.end;
        if (writeEnd <= regionStart || static_cast<uint64_t>(address) >= regionEnd)
        {
            continue;
        }

        uint32_t overlapStart = static_cast<uint32_t>(std::max<uint64_t>(address, regionStart));
        uint32_t overlapEnd = static_cast<uint32_t>(std::min<uint64_t>(writeEnd, regionEnd));

        for (uint32_t addr = overlapStart; addr < overlapEnd; addr += 4)
        {
            size_t bitIndex = (addr - region.start) / 4;
            if (bitIndex < region.modified.size() && region.modified[bitIndex])
            {
                return true; // Found modified code
            }
        }
    }

    return false; // No modifications found
}

void PS2Memory::clearModifiedFlag(uint32_t address, uint32_t size)
{
    if (size == 0)
    {
        return;
    }

    const uint64_t writeEnd = static_cast<uint64_t>(address) + static_cast<uint64_t>(size);
    for (auto &region : m_codeRegions)
    {
        const uint64_t regionStart = region.start;
        const uint64_t regionEnd = region.end;
        if (writeEnd <= regionStart || static_cast<uint64_t>(address) >= regionEnd)
        {
            continue;
        }

        uint32_t overlapStart = static_cast<uint32_t>(std::max<uint64_t>(address, regionStart));
        uint32_t overlapEnd = static_cast<uint32_t>(std::min<uint64_t>(writeEnd, regionEnd));

        for (uint32_t addr = overlapStart; addr < overlapEnd; addr += 4)
        {
            size_t bitIndex = (addr - region.start) / 4;
            if (bitIndex < region.modified.size())
            {
                region.modified[bitIndex] = false;
            }
        }
    }
}
