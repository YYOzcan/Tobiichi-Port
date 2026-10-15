// GOW-Port: native VU1 backend runtime (included at the end of ps2_vu1_core.cpp). See include/runtime/ps2_vu1_native.h.
#include "runtime/ps2_vu1_native.h"

#include <memory>
#include <unordered_map>

namespace
{
    struct NativeEntry
    {
        VU1NativeFn fn;
        uint32_t pairs;
        const VU1TailDesc *tail;
        bool readsEntryFlags; // reads MAC/clip flags written before the block (vu1n_gen.py: bit 16 of pairs)
        std::vector<uint8_t> cyc; // issue cycle of each pair (block entry = 0), filled on first use
    };
    std::unordered_map<uint64_t, NativeEntry> &nativeRegistry()
    {
        static std::unordered_map<uint64_t, NativeEntry> registry;
        return registry;
    }
    bool isBranchLower(uint32_t lower)
    {
        switch (lower >> 25)
        {
        case 0x20: case 0x21: case 0x24: case 0x25: case 0x28: case 0x29: case 0x2C: case 0x2D: case 0x2E: case 0x2F:
            return true;
        default:
            return false;
        }
    }
    // Same rule as tools/vu1/vu1n_gen.py: pairs from pc up to and including the delay slot of the first branch, the pair
    // after an E bit, or a D/T pair; at most 64 pairs; an all-zero pair is invalid (extent 0).
    uint32_t nativeExtent(const uint8_t *code, uint32_t size, uint32_t pc, uint32_t *words)
    {
        uint32_t n = 0;
        for (uint32_t p = pc; p + 8u <= size && n < 64u; p += 8u)
        {
            uint32_t lower, upper;
            std::memcpy(&lower, code + p, 4);
            std::memcpy(&upper, code + p + 4, 4);
            if (lower == 0u && upper == 0u)
                return n == 0u ? 0u : n;
            words[n * 2u] = lower;
            words[n * 2u + 1u] = upper;
            ++n;
            const bool iBit = (upper >> 31) != 0u;
            if (((upper >> 28) & 1u) || ((upper >> 27) & 1u))
                break;
            if ((!iBit && isBranchLower(lower)) || ((upper >> 30) & 1u))
            {
                uint32_t dl, du;
                if (p + 16u <= size)
                {
                    std::memcpy(&dl, code + p + 8u, 4);
                    std::memcpy(&du, code + p + 12u, 4);
                    if (!(dl == 0u && du == 0u))
                    {
                        words[n * 2u] = dl;
                        words[n * 2u + 1u] = du;
                        ++n;
                    }
                }
                break;
            }
        }
        return n;
    }
}

void vu1nRegisterBlock(uint64_t key, VU1NativeFn fn, uint32_t pairs, const VU1TailDesc *tail)
{
    nativeRegistry()[key] = {fn, pairs & 0xFFFFu, tail, (pairs & 0x10000u) != 0u, {}};
}

// Issue cycles of the pairs of a block as the exact engine would see them (operand/pipeline stalls included), assuming
// every pipeline is idle at block entry. Flag readers use them to decide which earlier FMAC/CLIP result is visible.
void VU1Interpreter::nativeTiming(const uint8_t *code, uint32_t pc, uint32_t count, std::vector<uint8_t> &cyc)
{
    VU1Interpreter t(*this);
    constexpr uint64_t base = 1u << 20;
    t.m_cycle = base;
    for (auto &r : t.m_vfReady)
        r.fill(0u);
    t.m_viReady.fill(0u);
    t.m_accReady.fill(0u);
    t.m_fdiv.valid = false;
    for (auto &e : t.m_efu)
        e.valid = false;
    t.m_efuResourceReady = 0;
    t.m_xgkick.active = false;
    cyc.assign(count, 0);
    for (uint32_t i = 0; i < count; ++i)
    {
        const DecodedInstructionPair d = t.decodeInstructionPair(code, pc + i * 8u);
        const uint64_t ready = t.calculatePairReadyCycle(d);
        if (ready > t.m_cycle)
            t.m_cycle = ready;
        cyc[i] = static_cast<uint8_t>(std::min<uint64_t>(t.m_cycle - base, 255u));
        t.markPairWrites(d);
        if (d.lowerUsage.pipeline == PipelineFdiv && !d.lowerUsage.waitQ)
        {
            t.m_fdiv.valid = true;
            t.m_fdiv.readyCycle = t.m_cycle + d.lowerUsage.latency;
        }
        else if (d.lowerUsage.pipeline == PipelineEfu && !d.lowerUsage.waitP)
        {
            t.m_efu[0].valid = true;
            t.m_efu[0].readyCycle = t.m_cycle + d.lowerUsage.latency;
            t.m_efuResourceReady = t.m_cycle + (d.lowerUsage.latency > 0u ? d.lowerUsage.latency - 1u : 0u);
        }
        ++t.m_cycle;
    }
}

void VU1NativeAccess::callLower(VU1NativeCtx &n, uint32_t pc, uint32_t lower, uint32_t upper)
{
    VU1Interpreter &vu = *n.vu;
    auto &c = *static_cast<VU1Interpreter::StepContext *>(n.context);
    vu.m_state.pc = pc;
    vu.execLower(lower, c.vuData, c.dataSize, *c.gs, c.memory, upper);
    VU1NativeAccess::commitValuesKeepTiming(vu);
    VU1NativeAccess::importFlags(vu); // the callout's flag writes join the native blocks' ones
}

void VU1NativeAccess::callUpper(VU1NativeCtx &n, uint32_t pc, uint32_t upper)
{
    VU1Interpreter &vu = *n.vu;
    vu.m_state.pc = pc;
    vu.execUpper(upper);
    VU1NativeAccess::commitValuesKeepTiming(vu);
    VU1NativeAccess::importFlags(vu); // the callout's flag writes join the native blocks' ones
}

void VU1NativeAccess::xgkick(VU1NativeCtx &n, uint32_t qwordAddress)
{
    VU1Interpreter &vu = *n.vu;
    if (vu.m_unit != VU1Interpreter::Unit::VU1 || !vu.m_activeVuData || vu.m_activeVuDataSize < 16u)
        return;
    vu.m_xgkick.reset();
    vu.m_xgkick.active = true;
    vu.m_xgkick.sourceAddress = (qwordAddress * 16u) % vu.m_activeVuDataSize;
    vu.m_xgkick.cycleCredit = 0x40000000u; // the whole packet is read at once (PCSX2 does the same)
    vu.m_xgkick.issueCycle = vu.m_cycle;
    // Fast path: walk the GIFtags in VU memory, then copy the whole packet with at most two memcpy (wrap). Same bytes and
    // end state as progressXgkick's qword loop; anything unusual (bad format, oversize, xgkick trace on) takes that loop.
    const uint32_t size = vu.m_activeVuDataSize;
    if (!g_xgkickTrace && (size & (size - 1u)) == 0u)
    {
        constexpr uint32_t kMax = VU1Interpreter::XgkickPipeline::kBufferSize;
        const uint32_t src = vu.m_xgkick.sourceAddress;
        uint32_t total = 0u;
        bool ok = false;
        for (;;)
        {
            const uint32_t at = (src + total) & (size - 1u);
            if (total > kMax - 16u || at + 8u > size)
                break;
            uint64_t tagLo;
            std::memcpy(&tagLo, vu.m_activeVuData + at, 8);
            const uint32_t nloop = static_cast<uint32_t>(tagLo & 0x7FFFu);
            const uint32_t format = static_cast<uint32_t>((tagLo >> 58) & 0x3u);
            uint32_t nreg = static_cast<uint32_t>((tagLo >> 60) & 0xFu);
            if (nreg == 0u)
                nreg = 16u;
            uint64_t tagBytes = 16u;
            if (format == 0u)
                tagBytes += static_cast<uint64_t>(nloop) * nreg * 16u;
            else if (format == 1u)
                tagBytes += ((static_cast<uint64_t>(nloop) * nreg + 1u) & ~1ull) * 8u;
            else if (format == 2u)
                tagBytes += static_cast<uint64_t>(nloop) * 16u;
            else
                break;
            if (tagBytes > kMax - total)
                break;
            total += static_cast<uint32_t>(tagBytes);
            if ((tagLo >> 15) & 1u)
            {
                ok = true;
                break;
            }
        }
        if (ok)
        {
            uint8_t *dst = vu.m_xgkick.packet.data();
            const uint32_t first = src & (size - 1u);
            const uint32_t head = std::min(total, size - first);
            std::memcpy(dst, vu.m_activeVuData + first, head);
            for (uint32_t done = head; done < total;)
            {
                const uint32_t chunk = std::min(total - done, size);
                std::memcpy(dst + done, vu.m_activeVuData, chunk);
                done += chunk;
            }
            vu.m_xgkick.copiedBytes = total;
            vu.m_xgkick.totalBytes = total;
            vu.m_xgkick.currentTagEnd = total;
            vu.m_xgkick.currentTagEop = true;
            vu.m_xgkick.cycleCredit = 0x40000000u - (total / 16u) * 2u + 1u;
            vu.finishXgkick();
            return;
        }
    }
    vu.progressXgkick();
}

// Native entry (and after an exact callout inside a block): the exact engine's flag pipeline moves into the rings
// (status / sticky updates, not modelled by the native blocks, are applied at once like before).
void VU1NativeAccess::importFlags(VU1Interpreter &vu)
{
    VU1Interpreter::NativeState &ns = *vu.m_native;
    if (!ns.flagsInRings)
    {
        ns.macRing.reset(vu.m_state.mac);
        ns.clipRing.reset(vu.m_state.clip);
        ns.clipRing.clip = true;
        ns.flagsInRings = true;
    }
    while (vu.m_flagCount != 0u)
    {
        auto &e = vu.m_flagPipeline[vu.m_flagHead];
        vu.m_flagHead = (vu.m_flagHead + 1u) % VU1Interpreter::kMaxFlagEntries;
        --vu.m_flagCount;
        if (e.writesMac)
            ringPush(ns.macRing, e.issueCycle, e.mac);
        if (e.writesClip)
            ringPush(ns.clipRing, e.issueCycle, e.clip);
        if (e.writesStatus)
        {
            const uint32_t current = e.status & 0xFu;
            vu.m_state.status = (vu.m_state.status & 0xFF0u) | current | ((current | e.extraSticky) << 6);
        }
        if (e.writesSticky)
            vu.m_state.status = (vu.m_state.status & 0x03Fu) | (e.status & 0xFC0u);
        e.valid = false;
    }
}

// The exact engine continues: visible flags become its committed values, writers still in flight its flag pipeline.
void VU1NativeAccess::exportFlags(VU1Interpreter &vu)
{
    VU1Interpreter::NativeState &ns = *vu.m_native;
    if (!ns.flagsInRings)
        return;
    ns.flagsInRings = false;
    vu.m_state.mac = ringAt(ns.macRing, vu.m_cycle);
    vu.m_state.clip = ringAt(ns.clipRing, vu.m_cycle);
    // pending writers of both rings (tail records included), oldest first
    struct P { uint64_t issue; uint32_t value; bool clip; };
    P pending[32];
    uint32_t count = 0;
    for (const auto *r : {&ns.macRing, &ns.clipRing})
        for (uint32_t k = 4u; k >= 1u; --k)
        {
            const uint32_t i = (r->next + 4u - k) & 3u;
            if (r->issue[i] + VU1Interpreter::kFmacLatency > vu.m_cycle)
            {
                pending[count++] = {r->issue[i], r->valueOf(i), r == &ns.clipRing};
                if (const VU1FlagTail *t = r->tail[i])
                {
                    const uint32_t n = r->clip ? t->desc->clipCount : t->desc->macCount;
                    for (uint32_t j = 0; j < n; ++j)
                    {
                        const uint8_t pair = r->clip ? t->desc->clipPair[j] : t->desc->macPair[j];
                        const uint64_t issue = t->start + t->cyc[pair];
                        if (issue + VU1Interpreter::kFmacLatency > vu.m_cycle)
                            pending[count++] = {issue, r->clip ? t->c[j] : vu1n::macValRt(t->q[j], t->desc->macMask[j]), r->clip};
                    }
                }
            }
        }
    std::sort(pending, pending + count, [](const P &a, const P &b) { return a.issue < b.issue; });
    for (uint32_t k = 0; k < count; ++k)
    {
        if (vu.m_flagCount >= VU1Interpreter::kMaxFlagEntries)
            break;
        auto &e = vu.m_flagPipeline[(vu.m_flagHead + vu.m_flagCount) % VU1Interpreter::kMaxFlagEntries];
        ++vu.m_flagCount;
        e.mac = pending[k].clip ? 0u : pending[k].value;
        e.clip = pending[k].clip ? pending[k].value : 0u;
        e.status = e.extraSticky = 0u;
        e.writesMac = !pending[k].clip;
        e.writesClip = pending[k].clip;
        e.writesStatus = e.writesSticky = false;
        e.valid = true;
        e.issueCycle = pending[k].issue;
        e.readyCycle = pending[k].issue + VU1Interpreter::kFmacLatency;
    }
}

// Values of results in flight are written at once (a reader would stall until they are ready anyway, so it sees the
// same value), but their timing state stays: the flag queue, and FDIV/EFU marked busy until their ready cycle.
void VU1NativeAccess::commitValuesKeepTiming(VU1Interpreter &vu)
{
    const uint32_t flagHead = vu.m_flagHead, flagCount = vu.m_flagCount;
    const VU1Interpreter::ScalarPipelineEntry fdiv = vu.m_fdiv;
    const auto efu = vu.m_efu;
    vu.m_flagCount = 0u;
    vu.commitEverythingNow();
    vu.m_flagHead = flagHead;
    vu.m_flagCount = flagCount;
    vu.m_fdiv = fdiv;
    vu.m_efu = efu;
    if (vu.m_fdiv.valid)
        vu.m_nextCommitCycle = std::min(vu.m_nextCommitCycle, vu.m_fdiv.readyCycle);
    for (const VU1Interpreter::ScalarPipelineEntry &e : vu.m_efu)
        if (e.valid)
            vu.m_nextCommitCycle = std::min(vu.m_nextCommitCycle, e.readyCycle);
}

// First use of a block: decoded pairs, the lanes it reads before writing them (with the idle-schedule cycle of that
// first read) and the last write of every lane it writes.
void VU1NativeAccess::prepareBlockTiming(VU1Interpreter &vu, VU1Interpreter::NativeState::BlockTiming &bt, const uint8_t *code, uint32_t pc, uint32_t count,
                                        const uint8_t *idle)
{
    using NS = VU1Interpreter::NativeState;
    bt.idle = idle;
    bt.dec.clear();
    bt.scalarPairs.clear();
    bool read[NS::kLanes] = {}, written[NS::kLanes] = {};
    bool scalarWritten[3] = {};
    uint32_t &maxLat = vu.m_native->maxLat;
    const auto onRead = [&](uint32_t lane, uint8_t at) {
        if (read[lane] || written[lane])
            return;
        read[lane] = true;
        bt.readMask[lane >> 6] |= 1ull << (lane & 63u);
        bt.readAt[lane] = at;
    };
    const auto onWrite = [&](uint32_t lane, uint32_t pair, uint32_t lat) {
        written[lane] = true;
        bt.writeMask[lane >> 6] |= 1ull << (lane & 63u);
        bt.lastPair[lane] = static_cast<uint8_t>(pair);
        bt.lastLat[lane] = static_cast<uint8_t>(lat);
        maxLat = std::max(maxLat, lat);
    };
    const auto onScalarRead = [&](uint32_t k, uint8_t at) {
        if (scalarWritten[k] || (bt.scalarRead & (1u << k)))
            return;
        bt.scalarRead = static_cast<uint8_t>(bt.scalarRead | (1u << k));
        bt.scalarAt[k] = at;
    };
    for (uint32_t i = 0; i < count; ++i)
    {
        const VU1Interpreter::DecodedInstructionPair d = vu.decodeInstructionPair(code, pc + i * 8u);
        bt.dec.push_back(d);
        const uint8_t at = idle[i];
        for (const VU1Interpreter::InstructionUsage *u : {&d.upperUsage, &d.lowerUsage})
        {
            for (uint32_t k = 0; k < u->vfReadCount; ++k)
                for (uint32_t c = 0; c < 4u; ++c)
                    if (u->vfRead[k].lanes & (1u << (3u - c)))
                        onRead(u->vfRead[k].reg * 4u + c, at);
            for (uint32_t r = 1; r < 16u; ++r)
                if (u->viRead & (1u << r))
                    onRead(128u + r, at);
            for (uint32_t c = 0; c < 4u; ++c)
                if (u->accRead & (1u << (3u - c)))
                    onRead(144u + c, at);
        }
        if (d.lowerUsage.pipeline == VU1Interpreter::PipelineFdiv || d.lowerUsage.waitQ)
            onScalarRead(0, at);
        if (d.lowerUsage.pipeline == VU1Interpreter::PipelineEfu)
            onScalarRead(1, at);
        if (d.lowerUsage.waitP)
            onScalarRead(2, at);
        // writes, in markPairWrites' order (lower VF, upper VF, VI, ACC)
        const auto vfWrite = [&](const VU1Interpreter::InstructionUsage &u, bool lower) {
            const VU1Interpreter::VfAccess w = u.vfWrite;
            if (w.reg == 0u || (lower && d.suppressedLowerVf == w.reg))
                return;
            const uint32_t lat = u.vfLatency != 0u ? u.vfLatency : u.latency;
            for (uint32_t c = 0; c < 4u; ++c)
                if (w.lanes & (1u << (3u - c)))
                    onWrite(w.reg * 4u + c, i, lat);
        };
        vfWrite(d.lowerUsage, true);
        vfWrite(d.upperUsage, false);
        for (uint32_t r = 1; r < 16u; ++r)
            if (d.lowerUsage.viWrite & (1u << r))
                onWrite(128u + r, i, d.lowerUsage.viLatency != 0u ? d.lowerUsage.viLatency : d.lowerUsage.latency);
        for (uint32_t c = 0; c < 4u; ++c)
            if (d.upperUsage.accWrite & (1u << (3u - c)))
                onWrite(144u + c, i, VU1Interpreter::kAccForwardLatency);
        const bool fdivOp = d.lowerUsage.pipeline == VU1Interpreter::PipelineFdiv && !d.lowerUsage.waitQ;
        const bool efuOp = d.lowerUsage.pipeline == VU1Interpreter::PipelineEfu && !d.lowerUsage.waitP;
        if (fdivOp || efuOp)
        {
            bt.scalarPairs.push_back(static_cast<uint8_t>(i));
            scalarWritten[fdivOp ? 0 : 1] = true;
            if (efuOp)
                scalarWritten[2] = true;
        }
    }
}

static inline uint64_t &vu1nLaneWord(VU1Interpreter &vu, uint32_t lane)
{
    return VU1NativeAccess::laneWord(vu, lane);
}

uint64_t &VU1NativeAccess::laneWord(VU1Interpreter &vu, uint32_t lane)
{
    if (lane < 128u)
        return vu.m_vfReady[lane >> 2][lane & 3u];
    if (lane < 144u)
        return vu.m_viReady[lane - 128u];
    return vu.m_accReady[lane - 144u];
}

// Ready cycles of lanes from the blocks in `hist`, newest first: calls ready(lane, cycle) for every lane of `want` whose
// newest writer is one of them and can still be in flight at `now` (cycle 0: surely ready), and removes those lanes from
// `want`. Lanes left in `want` are ready by `now` unless arraysReadyBy > now: then they hold the exact engine's values.
// Blocks that ended maxLat or more cycles before `now` (and all older ones) hold nothing in flight any more.
template <typename F>
void VU1NativeAccess::walkHistory(VU1Interpreter::NativeState &ns, uint64_t now, uint64_t want[3], F &&ready)
{
    using NS = VU1Interpreter::NativeState;
    const uint32_t n = std::min(ns.histCount, NS::kHist);
    uint32_t k = 0;
    for (; k < n; ++k)
    {
        const NS::Hist &h = ns.hist[(ns.histNext + NS::kHist - 1u - k) % NS::kHist];
        if (h.end + ns.maxLat <= now)
            break;
        for (uint32_t w = 0; w < 3u; ++w)
        {
            const uint64_t lanes = want[w] & h.bt->writeMask[w];
            want[w] &= ~lanes;
            for (uint64_t bits = lanes; bits != 0u; bits &= bits - 1u)
            {
                const uint32_t lane = w * 64u + static_cast<uint32_t>(std::countr_zero(bits));
                ready(lane, h.start + h.cyc[h.bt->lastPair[lane]] + h.bt->lastLat[lane]);
            }
        }
    }
    if (ns.arraysReadyBy <= now)
        return;
    // Shortly after native entry: lanes written by the older blocks are ready, the others keep the exact engine's values.
    // All blocks since entry are still in the ring here (they span less than the exact engine's latencies, far below kHist).
    for (; k < n; ++k)
    {
        const NS::Hist &h = ns.hist[(ns.histNext + NS::kHist - 1u - k) % NS::kHist];
        for (uint32_t w = 0; w < 3u; ++w)
        {
            const uint64_t lanes = want[w] & h.bt->writeMask[w];
            want[w] &= ~lanes;
            for (uint64_t bits = lanes; bits != 0u; bits &= bits - 1u)
                ready(w * 64u + static_cast<uint32_t>(std::countr_zero(bits)), 0u);
        }
    }
}

// Before the exact engine looks at its readiness arrays: lanes the native blocks wrote that may still be in flight get
// their real ready cycle (the others are ready by now, as every stale value is); the history starts over.
void VU1NativeAccess::syncInflight(VU1Interpreter &vu)
{
    VU1Interpreter::NativeState &ns = *vu.m_native;
    uint64_t want[3] = {~0ull, ~0ull, (1ull << (VU1Interpreter::NativeState::kLanes - 128u)) - 1u};
    uint64_t readyBy = ns.arraysReadyBy;
    walkHistory(ns, vu.m_cycle, want, [&](uint32_t lane, uint64_t ready) {
        vu1nLaneWord(vu, lane) = ready;
        readyBy = std::max(readyBy, ready);
    });
    ns.arraysReadyBy = readyBy;
    ns.histCount = 0u;
}

// Issue cycles (relative to vu.m_cycle) of the block's pairs: the idle table unless a lane it reads is still in flight
// past that read; then the exact engine's stall model, run once per distinct (lane, slack) set and cached.
const uint8_t *VU1NativeAccess::blockTiming(VU1Interpreter &vu, VU1Interpreter::NativeState::Slot &sl, uint32_t &cycId)
{
    using NS = VU1Interpreter::NativeState;
    NS &ns = *vu.m_native;
    NS::BlockTiming &bt = *sl.bt;
    const uint64_t start = vu.m_cycle;
    const NS::Hist *pred = ns.histCount ? &ns.hist[(ns.histNext + NS::kHist - 1u) % NS::kHist] : nullptr;
    const bool memoOk = pred && sl.memoable && pred->end == start && pred->end - pred->start >= ns.maxLat &&
                        ns.arraysReadyBy <= start;
    if (memoOk && sl.memoPred == pred->bt && sl.memoPredId == pred->cycId && sl.memoCyc)
    {
        cycId = sl.memoId;
        return sl.memoCyc;
    }
    const NS::BlockTiming *predBt = memoOk ? pred->bt : nullptr;
    const uint32_t predId = memoOk ? pred->cycId : 0u;
    const auto remember = [&](const uint8_t *cyc, uint32_t id) {
        if (predBt)
            sl.memoPred = predBt, sl.memoPredId = predId, sl.memoCyc = cyc, sl.memoId = id;
        cycId = id;
        return cyc;
    };
    uint64_t hot[3] = {};
    uint8_t slack[NS::kLanes];
    const auto note = [&](uint32_t lane, uint64_t ready) {
        const uint64_t readAt = start + bt.readAt[lane];
        if (ready > readAt)
        {
            hot[lane >> 6] |= 1ull << (lane & 63u);
            slack[lane] = static_cast<uint8_t>(std::min<uint64_t>(ready - readAt, 255u));
        }
    };
    uint64_t want[3] = {bt.readMask[0], bt.readMask[1], bt.readMask[2]};
    walkHistory(ns, start, want, note);
    if (ns.arraysReadyBy > start) // not written by native blocks since the exact engine ran: its readiness arrays
        for (uint32_t w = 0; w < 3u; ++w)
            for (uint64_t bits = want[w]; bits != 0u; bits &= bits - 1u)
            {
                const uint32_t lane = w * 64u + static_cast<uint32_t>(std::countr_zero(bits));
                note(lane, vu1nLaneWord(vu, lane));
            }
    ns.sig.clear();
    for (uint32_t w = 0; w < 3u; ++w)
        for (uint64_t bits = hot[w]; bits != 0u; bits &= bits - 1u)
        {
            const uint32_t lane = w * 64u + static_cast<uint32_t>(std::countr_zero(bits));
            ns.sig.push_back(static_cast<uint16_t>((lane << 8) | slack[lane]));
        }
    if (bt.scalarRead)
    {
        uint64_t ready[3] = {vu.m_fdiv.valid ? vu.m_fdiv.readyCycle : 0u, vu.m_efuResourceReady, 0u};
        for (const VU1Interpreter::ScalarPipelineEntry &e : vu.m_efu)
            if (e.valid)
                ready[2] = std::max(ready[2], e.readyCycle);
        for (uint32_t k = 0; k < 3u; ++k)
            if ((bt.scalarRead & (1u << k)) && ready[k] > start + bt.scalarAt[k])
                ns.sig.push_back(static_cast<uint16_t>(((200u + k) << 8) | std::min<uint64_t>(ready[k] - start - bt.scalarAt[k], 255u)));
    }
    if (ns.sig.empty())
        return remember(bt.idle, 0u);
    for (const auto &c : bt.cache)
        if (c.sig == ns.sig)
            return remember(c.cyc.data(), c.id);
    // simulate on the exact engine's pipeline state (synced; this also drops the history, whose timing tables may be
    // cache slots replaced below), then restore it
    syncInflight(vu);
    const uint64_t keepCycle = vu.m_cycle;
    const auto vfReady = vu.m_vfReady;
    const auto viReady = vu.m_viReady;
    const auto accReady = vu.m_accReady;
    const VU1Interpreter::ScalarPipelineEntry fdiv = vu.m_fdiv;
    const auto efu = vu.m_efu;
    const uint64_t efuResource = vu.m_efuResourceReady;
    const bool xgkick = vu.m_xgkick.active;
    vu.m_xgkick.active = false;
    std::vector<uint8_t> cyc(bt.dec.size());
    for (size_t i = 0; i < bt.dec.size(); ++i)
    {
        const VU1Interpreter::DecodedInstructionPair &d = bt.dec[i];
        const uint64_t ready = vu.calculatePairReadyCycle(d);
        if (ready > vu.m_cycle)
            vu.m_cycle = ready;
        cyc[i] = static_cast<uint8_t>(std::min<uint64_t>(vu.m_cycle - keepCycle, 255u));
        vu.markPairWrites(d);
        if (d.lowerUsage.pipeline == VU1Interpreter::PipelineFdiv && !d.lowerUsage.waitQ)
        {
            vu.m_fdiv.valid = true;
            vu.m_fdiv.readyCycle = vu.m_cycle + d.lowerUsage.latency;
        }
        else if (d.lowerUsage.pipeline == VU1Interpreter::PipelineEfu && !d.lowerUsage.waitP)
        {
            vu.m_efu[0].valid = true;
            vu.m_efu[0].readyCycle = vu.m_cycle + d.lowerUsage.latency;
            vu.m_efuResourceReady = vu.m_cycle + (d.lowerUsage.latency > 0u ? d.lowerUsage.latency - 1u : 0u);
        }
        ++vu.m_cycle;
    }
    vu.m_cycle = keepCycle;
    vu.m_vfReady = vfReady;
    vu.m_viReady = viReady;
    vu.m_accReady = accReady;
    vu.m_fdiv = fdiv;
    vu.m_efu = efu;
    vu.m_efuResourceReady = efuResource;
    vu.m_xgkick.active = xgkick;
    NS::BlockTiming::Cached &slot = bt.cache.size() < 16u ? bt.cache.emplace_back() : bt.cache[bt.next++ % 16u];
    slot.sig = ns.sig;
    slot.cyc = std::move(cyc);
    slot.id = ns.nextCycId++;
    for (NS::Slot &other : ns.slots) // may point into the cache slot replaced here
        if (other.bt == &bt)
            other.memoCyc = nullptr;
    return remember(slot.cyc.data(), slot.id);
}

// After a native block: it joins the history (its results that outlive it are found there when needed); FDIV/EFU stay
// busy until their ready cycle.
// An FDIV / EFU operation a native block started at `issue`: busy until its ready cycle.
void VU1NativeAccess::scalarStart(VU1Interpreter &vu, uint64_t issue, uint32_t latency, bool fdiv)
{
    if (fdiv)
    {
        vu.m_fdiv.valid = true;
        vu.m_fdiv.readyCycle = issue + latency;
        vu.m_fdiv.value = vu.m_state.q;
        vu.m_fdiv.statusDi = vu.m_state.status & 0x30u;
        vu.m_nextCommitCycle = std::min(vu.m_nextCommitCycle, vu.m_fdiv.readyCycle);
        return;
    }
    // EFU instructions run through callLower, which queued their result at the block's start cycle: move the newest
    // entry to the pair's real issue cycle
    VU1Interpreter::ScalarPipelineEntry *newest = nullptr;
    for (VU1Interpreter::ScalarPipelineEntry &e : vu.m_efu)
        if (e.valid && (!newest || e.readyCycle >= newest->readyCycle))
            newest = &e;
    if (newest)
    {
        newest->readyCycle = issue + latency;
        vu.m_nextCommitCycle = std::min(vu.m_nextCommitCycle, newest->readyCycle);
    }
    vu.m_efuResourceReady = issue + (latency > 0u ? latency - 1u : 0u);
}

// After a native block: it joins the history (its results that outlive it are found there when needed); FDIV/EFU stay
// busy until their ready cycle.
VU1N_INLINE void VU1NativeAccess::finishBlockTiming(VU1Interpreter &vu, const VU1Interpreter::NativeState::Slot &sl, const uint8_t *cyc,
                                                     uint32_t cycId, uint64_t start)
{
    using NS = VU1Interpreter::NativeState;
    NS &ns = *vu.m_native;
    const uint64_t end = start + cyc[sl.pairs - 1u] + 1u;
    NS::Hist &h = ns.hist[ns.histNext];
    h.bt = sl.bt;
    h.cyc = cyc;
    h.start = start;
    h.end = end;
    h.cycId = cycId;
    ns.histNext = (ns.histNext + 1u) % NS::kHist;
    ++ns.histCount;
    vu.m_cycle = end;
    if (sl.scalarCount == 0u)
        return;
    if (sl.scalarCount != NS::kScalarMany)
    {
        for (uint32_t k = 0; k < sl.scalarCount; ++k)
            scalarStart(vu, start + cyc[sl.scalar[k].pair], sl.scalar[k].latency, sl.scalar[k].fdiv);
        return;
    }
    const NS::BlockTiming &bt = *sl.bt;
    for (const uint8_t i : bt.scalarPairs)
    {
        const VU1Interpreter::DecodedInstructionPair &d = bt.dec[i];
        scalarStart(vu, start + cyc[i], d.lowerUsage.latency, d.lowerUsage.pipeline == VU1Interpreter::PipelineFdiv);
    }
}

// The dispatch slot of pc, set up on first use (native block lookup, timing tables).
VU1Interpreter::NativeState::Slot &VU1NativeAccess::slotFor(VU1Interpreter &vu, const uint8_t *code, uint32_t codeSize, uint32_t pc)
{
    VU1Interpreter::NativeState &ns = *vu.m_native;
    VU1Interpreter::NativeState::Slot &sl = ns.slots[pc >> 3];
    if (!sl.known)
    {
        uint32_t words[128];
        const uint32_t count = nativeExtent(code, codeSize, pc, words);
        sl = {};
        sl.known = true;
        sl.pairs = static_cast<uint16_t>(count);
        if (count != 0u)
        {
            const auto it = nativeRegistry().find(vu1n::blockKey(pc, words, count * 2u));
            if (it != nativeRegistry().end())
            {
                if (it->second.cyc.empty())
                    vu.nativeTiming(code, pc, count, it->second.cyc);
                VU1Interpreter::NativeState::BlockTiming &bt = ns.timings[it->first];
                if (bt.dec.empty())
                    prepareBlockTiming(vu, bt, code, pc, count, it->second.cyc.data());
                bt.readsEntryFlags = it->second.readsEntryFlags;
                sl.fn = it->second.fn;
                sl.idle = it->second.cyc.data();
                sl.bt = &bt;
                sl.readsEntryFlags = bt.readsEntryFlags;
                sl.memoable = bt.scalarRead == 0u;
                sl.tail = it->second.tail;
                if (bt.scalarPairs.size() > std::size(sl.scalar))
                    sl.scalarCount = VU1Interpreter::NativeState::kScalarMany;
                else
                    for (const uint8_t i : bt.scalarPairs)
                        sl.scalar[sl.scalarCount++] = {i, static_cast<uint8_t>(bt.dec[i].lowerUsage.latency),
                                                       bt.dec[i].lowerUsage.pipeline == VU1Interpreter::PipelineFdiv};
            }
            else if (ns.diag)
                ++ns.missPcs[pc];
        }
    }
    return sl;
}

void VU1Interpreter::commitEverythingNow()
{
    const uint64_t keep = m_cycle;
    m_cycle = ~0ull >> 1;
    m_nextCommitCycle = 0u;
    commitReadyPipelines();
    commitReadyFlags();
    m_cycle = keep;
    m_nextCommitCycle = ~0ull;
}

bool VU1Interpreter::runNative(StepContext &context)
{
    if (m_unit != Unit::VU1 || context.vuData == nullptr || context.codeSize != PS2_VU1_CODE_SIZE)
        return false;
    if (!m_native)
        m_native = new NativeState();
    NativeState &ns = *m_native;
    if (!ns.enabled)
        return false;
    if (m_state.branchPending || m_state.ebit || m_state.haltAfterDelaySlot || m_stopRequested)
        return false;

    const uint64_t generation = context.memory ? context.memory->getVU1CodeGeneration() : 0u;
    if (generation != ns.generation)
    {
        ns.generation = generation;
        for (NativeState::Slot &sl : ns.slots)
            sl.known = false;
    }

    const unsigned savedCsr = _mm_getcsr();
    bool armed = false; // pending exact-engine pipelines are committed only when a native block really runs
    VU1NativeCtx ctx;
    ctx.s = &m_state;
    ctx.data = context.vuData;
    ctx.mask = context.dataSize - 1u;
    ctx.vu = this;
    ctx.context = &context;
    ctx.macRing = &ns.macRing;
    ctx.clipRing = &ns.clipRing;

    bool handled = false;
    for (;;)
    {
        if (m_stopRequested || m_cycle >= context.budgetEnd)
        {
            handled = true;
            break;
        }
        const uint32_t pc = m_state.pc & 0x3FF8u;
        if (pc + 8u > context.codeSize)
            break;
        NativeState::Slot &sl = ns.slots[pc >> 3];
        if (!sl.known)
            VU1NativeAccess::slotFor(*this, context.vuCode, context.codeSize, pc);
        VU1NativeFn fn = sl.fn;
        if (!fn)
        {
            ++ns.missBlocks;
            if (ns.diag)
                ++ns.missHits[pc];
            break;
        }
        if (!armed)
        {
            // Results in flight from the exact engine: values now, timing kept (blockTiming / the flag queue), so the
            // blocks stall on them and see their flags at the same cycles as the exact engine.
            commitReadyPipelines();
            commitReadyFlags();
            VU1NativeAccess::commitValuesKeepTiming(*this);
            VU1NativeAccess::importFlags(*this);
            ns.histCount = 0u; // the exact engine's readiness arrays hold the state in flight
            if (m_cycle != ns.exitCycle) // the exact engine ran since the last native exit
            {
                uint64_t readyBy = 0u;
                for (const auto &r : m_vfReady)
                    for (const uint64_t c : r)
                        readyBy = std::max(readyBy, c);
                for (const uint64_t c : m_viReady)
                    readyBy = std::max(readyBy, c);
                for (const uint64_t c : m_accReady)
                    readyBy = std::max(readyBy, c);
                ns.arraysReadyBy = readyBy;
            }
            ++ns.nativeRuns;
            _mm_setcsr((savedCsr & ~0x6000u) | 0x6000u | 0x8000u | 0x0040u); // round toward zero, FTZ, DAZ
            armed = true;
        }
        if (ns.limit != ~0u)
        {
            if (ns.count >= ns.limit)
                break;
            if (ns.count + 1u == ns.limit)
                ns.snap = m_state;
            ++ns.count;
            ns.trace.push_back(pc);
        }
        const uint64_t start = m_cycle;
        // Values never depend on timing, only flag reads do. A block that reads flags written before it gets its exact
        // issue cycles from the pipeline state at entry (the stalls decide which of those flags it sees); the others use
        // their idle-pipeline table and only hand their results and flags in flight on.
        uint32_t cycId = 0u;
        const uint8_t *cyc = sl.readsEntryFlags ? VU1NativeAccess::blockTiming(*this, sl, cycId) : sl.idle;
        ctx.cyc = cyc;
        ctx.start = start;
        if (sl.tail)
        {
            VU1FlagTail &t = ns.hist[ns.histNext].tail;
            t.desc = sl.tail;
            t.cyc = cyc;
            t.start = start;
            ctx.tail = &t;
        }
        const uint32_t result = fn(ctx);
        VU1NativeAccess::finishBlockTiming(*this, sl, cyc, cycId, start);
        m_state.cycles = m_cycle;
        if (m_cycle >= m_nextCommitCycle)
            commitReadyPipelines(); // FDIV/EFU entries kept for timing retire when ready (values are written already)
        ns.nativePairs += sl.pairs;
        m_state.pc = result & 0x3FFFu;
        if (result & kVu1nEnded)
        {
            context.programEnded = true;
            handled = true;
            break;
        }
        if (result & kVu1nBail)
            break;
    }
    if (armed)
    {
        VU1NativeAccess::syncInflight(*this); // the exact engine continues: its readiness arrays become current
        VU1NativeAccess::exportFlags(*this);
        ns.exitCycle = m_cycle;
    }
    _mm_setcsr(savedCsr);
    if (ns.diag)
    {
        static auto last = std::chrono::steady_clock::now();
        if (std::chrono::steady_clock::now() - last > std::chrono::seconds(5))
        {
            last = std::chrono::steady_clock::now();
            std::fprintf(stderr, "[vu1n] nativePairs=%llu missBlocks=%llu nativeEntries=%llu distinctMissPcs=%zu\n", ns.nativePairs,
                         ns.missBlocks, ns.nativeRuns, ns.missPcs.size());
            ns.nativePairs = ns.missBlocks = ns.nativeRuns = 0;
            std::vector<std::pair<unsigned, uint32_t>> top;
            for (const auto &kv : ns.missHits)
                top.emplace_back(kv.second, kv.first);
            std::sort(top.rbegin(), top.rend());
            for (size_t i = 0; i < top.size() && i < 40u; ++i)
                std::fprintf(stderr, "[vu1n-miss] pc=%x hits=%u\n", top[i].second, top[i].first);
            ns.missHits.clear();
        }
    }
    return handled;
}

// GOW_VU1N_RECORD=<file> [GOW_VU1N_RECORD_N=4000, GOW_VU1N_RECORD_STRIDE=7, GOW_VU1N_RECORD_SKIP=0 (runs skipped first, to
// record a later part of a zone run; ~76k runs per second in gameplay)]: every STRIDE-th VU1 program run, the input
// (VU1State, micro memory, data memory) and a bit-exact hash of the native result (state, data memory, GIF packets) are
// appended to <file>. GOW_VU1N_REPLAY=<file>: on the first VU1 run, every record is executed by this build's native
// blocks and its hash compared with the recorded one -> "[vu1n-replay] N records, M differ". Proves that a change of the
// generator / runtime keeps the output bit-identical.
namespace
{
    struct Vu1nRecord
    {
        uint32_t magic;
        uint32_t maxCycles;
        uint64_t hash;
        VU1State state;
        uint8_t code[PS2_VU1_CODE_SIZE];
        uint8_t data[16384];
    };
    uint64_t g_vu1nReplayNs = 0; // time spent in the native runs of the replay (GOW_VU1N_REPLAY_REPS timing)
    inline uint64_t fnvBytes(uint64_t h, const void *p, size_t n)
    {
        const uint8_t *b = static_cast<const uint8_t *>(p);
        for (size_t i = 0; i < n; ++i)
            h = (h ^ b[i]) * 1099511628211ull;
        return h;
    }
}

uint64_t VU1NativeAccess::silentNativeHash(VU1Interpreter &vu, void *contextPtr)
{
    auto &context = *static_cast<VU1Interpreter::StepContext *>(contextPtr);
    const bool silentBefore = vu.m_verifySilent;
    vu.m_verifySilent = true;
    g_vuVerifyCapture = true;
    g_vuVerifyPackets.clear();
    VU1Interpreter::StepContext c = context;
    const auto t0 = std::chrono::steady_clock::now();
    for (;;)
    {
        if (vu.runNative(c))
            break;
        if (!vu.stepInterpreted(c))
            break;
    }
    g_vu1nReplayNs += static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count());
    vu.flushPipelines();
    g_vuVerifyCapture = false;
    vu.m_verifySilent = silentBefore;
    const VU1State &s = vu.m_state;
    uint64_t h = 1469598103934665603ull;
    h = fnvBytes(h, s.vf, sizeof(s.vf));
    h = fnvBytes(h, s.vi, sizeof(s.vi));
    h = fnvBytes(h, s.acc, sizeof(s.acc));
    h = fnvBytes(h, &s.q, 4);
    h = fnvBytes(h, &s.p, 4);
    h = fnvBytes(h, &s.i, 4);
    h = fnvBytes(h, &s.mac, 4);
    h = fnvBytes(h, &s.clip, 4);
    h = fnvBytes(h, &s.pc, sizeof(s.pc));
    const uint8_t ended = c.programEnded ? 1u : 0u;
    h = fnvBytes(h, &ended, 1);
    h = fnvBytes(h, c.vuData, c.dataSize);
    h = fnvBytes(h, g_vuVerifyPackets.data(), g_vuVerifyPackets.size());
    return h;
}

void VU1NativeAccess::recordReplay(VU1Interpreter &vu, void *contextPtr, uint32_t maxCycles)
{
    auto &context = *static_cast<VU1Interpreter::StepContext *>(contextPtr);
    static const char *recPath = std::getenv("GOW_VU1N_RECORD");
    static const char *repPath = std::getenv("GOW_VU1N_REPLAY");
    if ((!recPath && !repPath) || context.dataSize != 16384u || context.codeSize != PS2_VU1_CODE_SIZE)
        return;
    if (repPath)
    {
        static bool done = false;
        if (done)
            return;
        done = true;
        FILE *f = std::fopen(repPath, "rb");
        if (!f)
        {
            std::fprintf(stderr, "[vu1n-replay] cannot open %s\n", repPath);
            return;
        }
        auto rec = std::make_unique<Vu1nRecord>();
        VU1Interpreter saved(vu);
        unsigned total = 0, differ = 0;
        static const unsigned reps = std::getenv("GOW_VU1N_REPLAY_REPS") ? static_cast<unsigned>(std::atoi(std::getenv("GOW_VU1N_REPLAY_REPS"))) : 1u;
        auto scratch = std::make_unique<Vu1nRecord>();
        uint64_t timedNs = 0;
        while (std::fread(rec.get(), sizeof(Vu1nRecord), 1, f) == 1)
        {
            ++total;
            for (unsigned rep = 0; rep < std::max(reps, 1u); ++rep)
            {
                vu = saved;
                vu.m_state = rec->state;
                if (rep == 0u)
                    vu.m_native->generation = ~0ull - 1u; // micro memory is not the game's: forget the block cache
                std::memcpy(scratch->data, rec->data, sizeof(rec->data));
                VU1Interpreter::StepContext c = context;
                c.vuCode = rec->code;
                c.vuData = scratch->data;
                c.budgetEnd = vu.m_cycle + rec->maxCycles;
                c.programEnded = false;
                vu.m_activeVuData = scratch->data;
                vu.m_activeVuDataSize = 16384u;
                g_vu1nReplayNs = 0;
                const uint64_t h = silentNativeHash(vu, &c);
                if (rep != 0u)
                    timedNs += g_vu1nReplayNs; // warm block cache only
                else if (h != rec->hash && differ++ < 20u)
                    std::fprintf(stderr, "[vu1n-replay] record %u startPc=%x differs\n", total, rec->state.pc);
            }
        }
        if (reps > 1u)
            std::fprintf(stderr, "[vu1n-replay] timing: %.3f ms for %u warm runs\n", timedNs / 1e6, total * (reps - 1u));
        std::fclose(f);
        vu = saved;
        vu.m_native->generation = ~0ull - 1u;
        std::fprintf(stderr, "[vu1n-replay] %u records, %u differ\n", total, differ);
        return;
    }
    static const unsigned limit = std::getenv("GOW_VU1N_RECORD_N") ? static_cast<unsigned>(std::atoi(std::getenv("GOW_VU1N_RECORD_N"))) : 4000u;
    static const unsigned stride = std::getenv("GOW_VU1N_RECORD_STRIDE") ? static_cast<unsigned>(std::atoi(std::getenv("GOW_VU1N_RECORD_STRIDE"))) : 7u;
    static const unsigned long long skip = std::getenv("GOW_VU1N_RECORD_SKIP") ? std::strtoull(std::getenv("GOW_VU1N_RECORD_SKIP"), nullptr, 10) : 0ull;
    static unsigned long long seen = 0;
    static unsigned written = 0;
    if (written >= limit || seen++ < skip || ((seen - skip) % stride) != 0u)
        return;
    static FILE *f = std::fopen(recPath, "wb");
    if (!f)
        return;
    auto rec = std::make_unique<Vu1nRecord>();
    rec->magic = 0x4E315556u;
    rec->maxCycles = maxCycles;
    rec->state = vu.m_state;
    std::memcpy(rec->code, context.vuCode, PS2_VU1_CODE_SIZE);
    std::memcpy(rec->data, context.vuData, 16384u);
    VU1Interpreter saved(vu);
    // same input as the replay: copies of code/data
    VU1Interpreter::StepContext c = context;
    auto code = std::make_unique<Vu1nRecord>();
    std::memcpy(code->code, rec->code, PS2_VU1_CODE_SIZE);
    std::memcpy(code->data, rec->data, 16384u);
    c.vuCode = code->code;
    c.vuData = code->data;
    c.budgetEnd = vu.m_cycle + maxCycles;
    vu.m_native->generation = ~0ull - 1u;
    vu.m_activeVuData = code->data;
    rec->hash = silentNativeHash(vu, &c);
    vu = saved;
    vu.m_native->generation = ~0ull - 1u;
    std::fwrite(rec.get(), sizeof(Vu1nRecord), 1, f);
    if (++written == limit)
        std::fclose(f), std::fprintf(stderr, "[vu1n-record] %u records written\n", written);
    else if (written % 500u == 0u)
        std::fflush(f);
}
