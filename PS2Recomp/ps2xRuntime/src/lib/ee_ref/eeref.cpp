#include <cstdlib>
// EE differential tester core: memory model, execute loop, branches (PCSX2 Interpreter.cpp), COP2 moves
// (PCSX2 VU0.cpp) and the comparison. PCSX2-derived parts are GPL-3.0+.
#include "Common.h"
#include "R5900OpcodeTables.h"
#include "eeref.h"

#include <set>

alignas(16) cpuRegistersPack _cpuRegistersPack;
alignas(16) tlbs tlb[48];
cachedTlbs_t cachedTlbs;
s32 EEsCycle;
u64 EEoCycle;

namespace pcsx2vu0
{
    void special(u32 code);
    u32 *vf(int index);
    u32 &vi(int index);
    u32 *acc();
}

namespace
{
    constexpr u32 kRamSize = 32u * 1024u * 1024u;
    constexpr u32 kScratchSize = 16u * 1024u;
    std::vector<u8> s_ram;
    std::vector<u8> s_scratch;
    std::set<u32> s_written; // words written by the reference run (RAM: physical, scratchpad: 0x70000000|offset)
    const char *s_stop = nullptr;

    u8 *resolve(u32 addr, u32 size, bool write)
    {
        if ((addr & 0xF0000000u) == 0x70000000u)
        {
            const u32 off = addr & (kScratchSize - 1);
            if (off + size > kScratchSize)
                return nullptr;
            if (write)
                for (u32 i = 0; i < size; i += 4)
                    s_written.insert(0x70000000u | ((off + i) & ~3u));
            return s_scratch.data() + off;
        }
        const u32 phys = addr & 0x1FFFFFFFu;
        if (phys + size > kRamSize)
            return nullptr;
        if (write)
            for (u32 i = 0; i < size; i += 4)
                s_written.insert((phys + i) & ~3u);
        return s_ram.data() + phys;
    }

    template <typename T>
    T load(u32 addr)
    {
        T value{};
        if (u8 *p = resolve(addr & ~static_cast<u32>(sizeof(T) - 1), sizeof(T), false))
            std::memcpy(&value, p, sizeof(T));
        else
            eeref::stop("read outside RAM/scratchpad");
        return value;
    }

    template <typename T>
    void store(u32 addr, T value)
    {
        if (u8 *p = resolve(addr & ~static_cast<u32>(sizeof(T) - 1), sizeof(T), true))
            std::memcpy(p, &value, sizeof(T));
        else
            eeref::stop("write outside RAM/scratchpad");
    }

    void execI()
    {
        cpuRegs.code = memRead32(cpuRegs.pc);
        cpuRegs.pc += 4;
        R5900::GetCurrentInstruction().interpret();
    }

    // PCSX2 Interpreter.cpp _doBranch_shared: run the delay slot, then jump.
    void doBranch(u32 target)
    {
        cpuRegs.branch = 1;
        execI();
        cpuRegs.pc = target;
        cpuRegs.branch = 0;
    }
}

u8 memRead8(u32 a) { return load<u8>(a); }
u16 memRead16(u32 a) { return load<u16>(a); }
u32 memRead32(u32 a) { return load<u32>(a); }
u64 memRead64(u32 a) { return load<u64>(a); }
void memRead128(u32 a, u128 &out) { out = load<u128>(a); }
void memWrite8(u32 a, u8 v) { store<u8>(a, v); }
void memWrite16(u32 a, u16 v) { store<u16>(a, v); }
void memWrite32(u32 a, u32 v) { store<u32>(a, v); }
void memWrite64(u32 a, u64 v) { store<u64>(a, v); }
void memWrite128(u32 a, const u128 &v) { store<u128>(a, v); }
void cpuException(u32, u32) { eeref::stop("cpu exception"); }
void intUpdateCPUCycles() {}
void intEventTest() {}
void intDoBranch(u32 target) { doBranch(target); }
void intSetBranch() {}

namespace eeref
{
    void stop(const char *reason)
    {
        if (!s_stop)
            s_stop = reason;
    }

    // COP2 (VU0 macro mode). Moves follow PCSX2 VU0.cpp; arithmetic runs PCSX2's VUops via pcsx2vu0::special.
    void cop2(u32 code)
    {
        const u32 rs = (code >> 21) & 0x1F, rt = (code >> 16) & 0x1F, rd = (code >> 11) & 0x1F;
        switch (rs)
        {
        case 1: // QMFC2
            if (rt)
                std::memcpy(&cpuRegs.GPR.r[rt].UD[0], pcsx2vu0::vf(rd), 16);
            break;
        case 2: // CFC2
            if (rt)
            {
                if (rd == 20)
                    cpuRegs.GPR.r[rt].UD[0] = pcsx2vu0::vi(20) & 0x7FFFFF;
                else
                    cpuRegs.GPR.r[rt].SD[0] = static_cast<s32>(pcsx2vu0::vi(rd));
            }
            break;
        case 5: // QMTC2
            if (rd)
                std::memcpy(pcsx2vu0::vf(rd), &cpuRegs.GPR.r[rt].UD[0], 16);
            break;
        case 6: // CTC2 (VI registers, R, I, Q)
            if (rd && rd < 16)
                pcsx2vu0::vi(rd) = cpuRegs.GPR.r[rt].UL[0] & 0xFFFF;
            else if (rd == 20)
                pcsx2vu0::vi(20) = (cpuRegs.GPR.r[rt].UL[0] & 0x7FFFFF) | 0x3F800000;
            else if (rd == 21 || rd == 22)
                pcsx2vu0::vi(rd) = cpuRegs.GPR.r[rt].UL[0];
            else if (rd)
                stop("CTC2 to a VU control register");
            break;
        case 8: // BC2F/BC2T/BC2FL/BC2TL: VU0 is never busy in macro-only code
        {
            const bool taken = (rt & 1) == 0; // BC2F taken, BC2T not taken
            const u32 target = cpuRegs.pc + static_cast<u32>(static_cast<s32>(static_cast<s16>(code)) * 4);
            if (taken)
                doBranch(target);
            else if (rt & 2)
                cpuRegs.pc += 4; // branch likely, not taken: skip the delay slot
            break;
        }
        default:
            if (rs >= 16)
                pcsx2vu0::special(code);
            else
                stop("unknown COP2 instruction");
            break;
        }
    }

    Result run(const CpuSnapshot &before, const uint8_t *ram, const uint8_t *scratch, uint32_t entryPc,
               uint32_t returnPc, const CpuSnapshot &after, const uint8_t *ramAfter, const uint8_t *scratchAfter,
               uint64_t maxSteps)
    {
        Result result;
        s_ram.assign(ram, ram + kRamSize);
        s_scratch.assign(scratch, scratch + kScratchSize);
        s_written.clear();
        s_stop = nullptr;

        std::memset(&cpuRegs, 0, sizeof(cpuRegs));
        std::memset(&fpuRegs, 0, sizeof(fpuRegs));
        for (int i = 0; i < 32; ++i)
        {
            cpuRegs.GPR.r[i].UD[0] = before.gpr[i][0];
            cpuRegs.GPR.r[i].UD[1] = before.gpr[i][1];
            fpuRegs.fpr[i].UL = before.f[i];
            std::memcpy(pcsx2vu0::vf(i), before.vf[i], 16);
        }
        cpuRegs.HI.UD[0] = before.hi;
        cpuRegs.HI.UD[1] = before.hi1;
        cpuRegs.LO.UD[0] = before.lo;
        cpuRegs.LO.UD[1] = before.lo1;
        cpuRegs.sa = before.sa;
        fpuRegs.ACC.UL = before.facc;
        fpuRegs.fprc[31] = before.fcr31;
        for (int i = 0; i < 16; ++i)
            pcsx2vu0::vi(i) = before.vi[i];
        std::memcpy(pcsx2vu0::acc(), before.acc, 16);
        pcsx2vu0::vi(22) = before.q;
        pcsx2vu0::vi(23) = before.p;
        pcsx2vu0::vi(21) = before.i;
        pcsx2vu0::vi(20) = before.r;
        pcsx2vu0::vi(16) = before.status;
        pcsx2vu0::vi(17) = before.mac;
        pcsx2vu0::vi(18) = before.clip;
        pcsx2vu0::vf(0)[0] = pcsx2vu0::vf(0)[1] = pcsx2vu0::vf(0)[2] = 0;
        pcsx2vu0::vf(0)[3] = 0x3F800000u;

        const u64 entrySp = cpuRegs.GPR.r[29].UD[0];
        cpuRegs.pc = entryPc;
        while (result.steps < maxSteps && !s_stop)
        {
            if (cpuRegs.pc == returnPc && cpuRegs.GPR.r[29].UD[0] == entrySp)
            {
                result.completed = true;
                break;
            }
            execI();
            ++result.steps;
        }
        if (!result.completed)
        {
            result.stopReason = s_stop ? s_stop : "step limit";
            return result;
        }

        char line[220];
        const auto note = [&](const char *text)
        {
            if (result.differences.size() < (std::getenv("PS2X_EE_DIFF_LINES") ? static_cast<size_t>(std::atoi(std::getenv("PS2X_EE_DIFF_LINES"))) : 24u))
                result.differences.emplace_back(text);
        };
        for (int i = 1; i < 32; ++i)
        {
            if (i == 26 || i == 27)
                continue; // k0/k1
            if (cpuRegs.GPR.r[i].UD[0] != after.gpr[i][0] || cpuRegs.GPR.r[i].UD[1] != after.gpr[i][1])
            {
                std::snprintf(line, sizeof(line), "gpr%-2d ref %016llX_%016llX ours %016llX_%016llX", i,
                              (unsigned long long)cpuRegs.GPR.r[i].UD[1], (unsigned long long)cpuRegs.GPR.r[i].UD[0],
                              (unsigned long long)after.gpr[i][1], (unsigned long long)after.gpr[i][0]);
                note(line);
            }
        }
        for (int i = 0; i < 32; ++i)
            if (fpuRegs.fpr[i].UL != after.f[i])
            {
                std::snprintf(line, sizeof(line), "f%-2d ref %08X (%g) ours %08X (%g)", i, fpuRegs.fpr[i].UL,
                              fpuRegs.fpr[i].f, after.f[i], std::bit_cast<float>(after.f[i]));
                note(line);
            }
        for (int i = 1; i < 32; ++i)
            if (std::memcmp(pcsx2vu0::vf(i), after.vf[i], 16) != 0)
            {
                const u32 *r = pcsx2vu0::vf(i);
                std::snprintf(line, sizeof(line), "vf%-2d ref %g %g %g %g ours %g %g %g %g", i,
                              std::bit_cast<float>(r[0]), std::bit_cast<float>(r[1]), std::bit_cast<float>(r[2]),
                              std::bit_cast<float>(r[3]), std::bit_cast<float>(after.vf[i][0]),
                              std::bit_cast<float>(after.vf[i][1]), std::bit_cast<float>(after.vf[i][2]),
                              std::bit_cast<float>(after.vf[i][3]));
                note(line);
            }
        {
            struct Ctl { const char *name; int idx; u32 ours; u32 mask; };
            const Ctl ctls[] = {{"vuQ", 22, after.q, 0xFFFFFFFFu}, {"vuP", 23, after.p, 0xFFFFFFFFu}, {"vuI", 21, after.i, 0xFFFFFFFFu},
                                {"vuStatus", 16, after.status, 0xFFFu}, {"vuMAC", 17, after.mac, 0xFFFFu}, {"vuClip", 18, after.clip, 0xFFFFFFu}};
            for (const Ctl &c : ctls)
            {
                const u32 ref = pcsx2vu0::vi(c.idx);
                if ((ref & c.mask) != (c.ours & c.mask))
                {
                    std::snprintf(line, sizeof(line), "%s ref %08X ours %08X", c.name, ref & c.mask, c.ours & c.mask);
                    note(line);
                }
            }
        }
        for (const u32 word : s_written)
        {
            u32 ref, ours;
            if ((word & 0xF0000000u) == 0x70000000u)
            {
                std::memcpy(&ref, s_scratch.data() + (word & (kScratchSize - 1)), 4);
                std::memcpy(&ours, scratchAfter + (word & (kScratchSize - 1)), 4);
            }
            else
            {
                std::memcpy(&ref, s_ram.data() + word, 4);
                std::memcpy(&ours, ramAfter + word, 4);
            }
            if (ref != ours)
            {
                std::snprintf(line, sizeof(line), "mem %08X ref %08X (%g) ours %08X (%g)", word, ref,
                              std::bit_cast<float>(ref), ours, std::bit_cast<float>(ours));
                note(line);
            }
        }
        return result;
    }
}


void GoemonPreloadTlb() {}
void GoemonUnloadTlb(u32) {}

namespace R5900::Interpreter::OpcodeImpl
{
    // LQC2/SQC2 (PCSX2 VU0.cpp).
    void LQC2()
    {
        const u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + static_cast<s16>(cpuRegs.code);
        u128 value;
        memRead128(addr, value);
        if (_Rt_)
            std::memcpy(pcsx2vu0::vf(_Rt_), &value, 16);
    }
    void SQC2()
    {
        const u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + static_cast<s16>(cpuRegs.code);
        u128 value;
        std::memcpy(&value, pcsx2vu0::vf(_Rt_), 16);
        memWrite128(addr, value);
    }
    void CACHE() {}

    // COP0 (system control) is outside what the differential tester compares: stop the reference run.
    namespace COP0
    {
        void MFC0() { eeref::stop("COP0"); }
        void MTC0() { eeref::stop("COP0"); }
        void BC0F() { eeref::stop("COP0"); }
        void BC0T() { eeref::stop("COP0"); }
        void BC0FL() { eeref::stop("COP0"); }
        void BC0TL() { eeref::stop("COP0"); }
        void TLBR() { eeref::stop("COP0"); }
        void TLBWI() { eeref::stop("COP0"); }
        void TLBWR() { eeref::stop("COP0"); }
        void TLBP() { eeref::stop("COP0"); }
        void ERET() { eeref::stop("COP0"); }
        void EI() { eeref::stop("COP0"); }
        void DI() { eeref::stop("COP0"); }
    }
}

// Branch and jump instructions (PCSX2 Interpreter.cpp).
#include "branches.inc"
