#include "pcsx2_vu1_bridge.h"

#include "Common.h"
#include "Gif_Unit.h"
#include "MTVU.h"
#include "VUmicro.h"

#include <cfenv>
#include <cstdlib>
#include <vector>

// Globals the borrowed PCSX2 sources expect.
VURegs vuRegs[2];
VIFregisters vif0Regs{};
VIFregisters vif1Regs{};
Pcsx2CpuRegsShim cpuRegs{};
Pcsx2Vu1ThreadShim vu1Thread{};
Pcsx2GifUnitShim gifUnit{};

namespace
{
    std::vector<u8> s_kickPacket;

    // PS2X_VU1_TRACE_BAD=<file>: when a kicked packet holds a float beyond 1e30, write the VU1 state captured at
    // the start of that microprogram (data mem 16 KB, VF 32x16, VI 16x4, start pc, top, itop) once.
    struct BadKickTrace
    {
        const char *path = std::getenv("PS2X_VU1_TRACE_BAD");
        bool written = false;
        std::vector<u8> mem;
        VECTOR vf[32];
        u32 vi[16];
        u32 pc = 0, top = 0, itop = 0;
    };
    BadKickTrace &badTrace()
    {
        static BadKickTrace t;
        return t;
    }

    // A drawn vertex (PACKED XYZ2/XYZF2 with ADC clear) with saturated X or Y.
    bool packetLooksBad(const u8 *packet, u32 size)
    {
        u32 offset = 0;
        while (offset + 16 <= size)
        {
            u64 lo, hi;
            std::memcpy(&lo, packet + offset, 8);
            std::memcpy(&hi, packet + offset + 8, 8);
            offset += 16;
            const u32 nloop = static_cast<u32>(lo & 0x7FFFu);
            const u32 flg = static_cast<u32>((lo >> 58) & 3u);
            u32 nreg = static_cast<u32>((lo >> 60) & 0xFu);
            if (nreg == 0)
                nreg = 16;
            if (flg != 0)
            {
                offset += (flg == 1) ? ((nreg * nloop + 1) / 2) * 16 : nloop * 16;
                continue;
            }
            for (u32 loop = 0; loop < nloop; ++loop)
                for (u32 r = 0; r < nreg && offset + 16 <= size; ++r, offset += 16)
                {
                    const u32 reg = static_cast<u32>((hi >> (r * 4)) & 0xFu);
                    if (reg != 4u && reg != 5u)
                        continue;
                    u32 w[4];
                    std::memcpy(w, packet + offset, 16);
                    const bool adc = (w[3] & 0x8000u) != 0u;
                    const u32 x = w[0] & 0xFFFFu, y = w[1] & 0xFFFFu;
                    // Saturated coordinates (FTOI of a huge/invalid value): the "shard" vertices.
                    if (!adc && (x == 0u || x >= 0xFFF0u || y == 0u || y >= 0xFFF0u))
                        return true;
                }
            if (lo & 0x8000u)
                break; // EOP
        }
        return false;
    }

    void resetVu1Once()
    {
        static bool done = false;
        if (done)
            return;
        done = true;
        VURegs &vu = vuRegs[1];
        std::memset(static_cast<void *>(vu.VF), 0, sizeof(vu.VF));
        std::memset(static_cast<void *>(vu.VI), 0, sizeof(vu.VI));
        vu.VF[0].f.w = 1.0f;
        vu.idx = 1;
        vu.cycle = 0;
        vu.branch = 0;
        vu.ebit = 0;
        vu.xgkickenable = false;
        vu.fmacreadpos = vu.fmacwritepos = vu.fmaccount = 0;
        vu.ialureadpos = vu.ialuwritepos = vu.ialucount = 0;
        vu.fdiv.enable = 0;
        vu.efu.enable = 0;
        vu.VIBackupCycles = 0;
        vuRegs[0].idx = 0;
    }
}

u32 Pcsx2GifUnitShim::GetGSPacketSize(GIF_PATH, u8 *mem, u32 offset, u32, bool)
{
    u64 lo;
    std::memcpy(&lo, mem + (offset & 0x3FF0u), sizeof(lo));
    const u32 nloop = static_cast<u32>(lo & 0x7FFFu);
    const u32 flg = static_cast<u32>((lo >> 58) & 3u);
    u32 nreg = static_cast<u32>((lo >> 60) & 0xFu);
    if (nreg == 0u)
        nreg = 16u;
    u32 len = 0;
    if (flg == 0u)
        len = nreg * nloop * 16u;
    else if (flg == 1u)
        len = ((nreg * nloop + 1u) >> 1) * 16u;
    else
        len = nloop * 16u;
    const u32 size = 16u + len;
    if (size >= 0x4000u)
        return 0; // PCSX2: "GS packet size exceeded VU memory size"
    return size | (static_cast<u32>((lo >> 15) & 1u) << 31);
}

u32 Pcsx2GifUnitShim::TransferGSPacketData(GIF_TRANSFER_TYPE, u8 *mem, u32 size, bool)
{
    s_kickPacket.insert(s_kickPacket.end(), mem, mem + size);
    return size;
}

namespace pcsx2vu1
{
    bool enabled()
    {
        // Default since 2026-10-09; PS2X_VU1_LEGACY=1 selects the old VU1Interpreter.
        static const bool on = std::getenv("PS2X_VU1_LEGACY") == nullptr;
        return on;
    }

    RunResult run(uint8_t *microMem, uint8_t *dataMem, int64_t startPc, uint32_t top, uint32_t itop,
                  bool dBitEnabled, bool tBitEnabled, uint64_t maxCycles, const SubmitPath1 &submit)
    {
        resetVu1Once();
        VURegs &vu = vuRegs[1];
        vu.Micro = microMem;
        vu.Mem = dataMem;
        vif1Regs.top = top & 0x3FFu;
        vif1Regs.itop = itop & 0x3FFu;
        vu1Thread.vifRegs = vif1Regs;
        u32 &fbrst = vuRegs[0].VI[REG_FBRST].UL;
        fbrst = (fbrst & ~0xC00u) | (dBitEnabled ? 0x400u : 0u) | (tBitEnabled ? 0x800u : 0u);
        u32 &vpuStat = vuRegs[0].VI[REG_VPU_STAT].UL;
        vpuStat &= ~0x600u;
        if (startPc >= 0)
        {
            vu.VI[REG_TPC].UL = static_cast<u32>(startPc) & 0x3FF8u;
            vu.branch = 0;
            vu.ebit = 0;
        }
        // GOW-Port: GOW_VU1_STARTMAC=1: debug, the MAC and clip flags a startPc 0 program starts with (A/B with VU1Interpreter)
        static const bool startMacLog = std::getenv("GOW_VU1_STARTMAC") != nullptr;
        static unsigned startMacShown = 0;
        if (startMacLog && startPc == 0 && startMacShown < 4000u && (startMacShown++ % 50u) == 0u)
            std::fprintf(stderr, "[vu1-startmac] pcsx2 mac=%x clip=%x\n", vu.VI[REG_MAC_FLAG].UL & 0xFFFFu, vu.VI[REG_CLIP_FLAG].UL & 0xFFFFFFu);
        vpuStat |= 0x100u; // VU1 running

        BadKickTrace &trace = badTrace();
        if (trace.path && !trace.written)
        {
            trace.mem.assign(dataMem, dataMem + 16384);
            std::memcpy(trace.vf, vu.VF, sizeof(trace.vf));
            for (int i = 0; i < 16; ++i)
                trace.vi[i] = vu.VI[i].UL;
            trace.pc = vu.VI[REG_TPC].UL;
            trace.top = top;
            trace.itop = itop;
        }
        const SubmitPath1 checkedSubmit = [&](const uint8_t *packet, uint32_t size)
        {
            if (trace.path && !trace.written && packetLooksBad(packet, size))
            {
                trace.written = true;
                if (std::FILE *f = std::fopen(trace.path, "wb"))
                {
                    std::fwrite(trace.mem.data(), 1, trace.mem.size(), f);
                    std::fwrite(trace.vf, 1, sizeof(trace.vf), f);
                    std::fwrite(trace.vi, 1, sizeof(trace.vi), f);
                    const u32 meta[4] = {trace.pc, trace.top, trace.itop, size};
                    std::fwrite(meta, 1, sizeof(meta), f);
                    std::fwrite(packet, 1, size, f);
                    std::fclose(f);
                }
                std::fprintf(stderr, "[vu1] bad packet from program at pc=0x%X top=0x%X: state written\n", trace.pc, top);
            }
            submit(packet, size);
        };

        const int previousRounding = std::fegetround();
        std::fesetround(FE_TOWARDZERO); // VU float rounding (PCSX2 sets the FPU control word the same way)
        const u64 budgetEnd = vu.cycle + maxCycles;
        while ((vpuStat & 0x100u) != 0u && vu.cycle < budgetEnd)
        {
            vu1Exec(&vu);
            if (!vu.xgkickenable && !s_kickPacket.empty())
            {
                checkedSubmit(s_kickPacket.data(), static_cast<uint32_t>(s_kickPacket.size()));
                s_kickPacket.clear();
            }
        }
        std::fesetround(previousRounding);

        RunResult result;
        result.finished = (vpuStat & 0x100u) == 0u;
        result.stoppedByD = (vpuStat & 0x200u) != 0u;
        result.stoppedByT = (vpuStat & 0x400u) != 0u;
        if (result.finished && !s_kickPacket.empty())
        {
            checkedSubmit(s_kickPacket.data(), static_cast<uint32_t>(s_kickPacket.size()));
            s_kickPacket.clear();
        }
        // GOW-Port: GOW_VU1_STARTMAC=1 also counts the MAC flag a startPc 0 program ends with
        static const bool endMacLog = std::getenv("GOW_VU1_STARTMAC") != nullptr;
        static unsigned endMacCount[3] = {}, endMacRuns = 0;
        if (endMacLog && startPc == 0)
        {
            const u32 mac = vu.VI[REG_MAC_FLAG].UL & 0xFFFFu;
            ++endMacCount[mac == 0x12u ? 0 : mac == 0u ? 1 : 2];
            if (++endMacRuns % 20000u == 0u)
                std::fprintf(stderr, "[vu1-endmac] pcsx2 runs=%u mac12=%u mac0=%u other=%u\n", endMacRuns, endMacCount[0], endMacCount[1], endMacCount[2]);
        }
        return result;
    }
}
