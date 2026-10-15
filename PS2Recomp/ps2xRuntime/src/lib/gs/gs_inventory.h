// GOW-Port: GOW_GS_INVENTORY=1 classifies what the game does with the GS, to size a render-target renderer: which draws sample
// textures that live inside earlier render targets (same or other pixel format), feedback draws (FBP==TBP), depth-as-texture,
// CLUT loads from render targets, uploads/readbacks that touch render targets and CPU VRAM accessors. Printed every 5 s.
#pragma once

#include "runtime/gs/gs_types.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>

class GsInventory
{
public:
    static GsInventory &get()
    {
        static GsInventory inv;
        return inv;
    }
    bool enabled() const { return m_enabled; }

    void draw(const GSPrimitiveBatch &b)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        const GSContext &c = b.state.context;
        ++m_draws;
        ++m_prim[static_cast<int>(b.state.prim.type) & 7];
        const uint32_t fbp = c.frame.fbp, tbp = c.tex0.tbp0;
        if (c.frame.fbmsk != 0u) ++m_fbmsk;
        if (b.state.prim.abe) ++m_abe;
        if (b.state.prim.fge) ++m_fog;
        if (b.state.prim.aa1) ++m_aa;
        if ((c.test & 1u) != 0u) ++m_atest;           // ATE
        if (((c.test >> 14) & 1u) != 0u) ++m_date;    // DATE
        if (((c.test >> 16) & 1u) != 0u) ++m_zte;     // ZTE
        if (b.state.dthe) ++m_dither;
        if (b.state.pabe) ++m_pabe;
        if (b.state.scanmsk) ++m_scanmsk;
        ++m_hist["alpha a|b|c|d lo8=" + hex(c.alpha & 0xFF) + (((c.alpha >> 4) & 3) == 2 ? " fix=" + hex((c.alpha >> 32) & 0xFF) : "") + (b.state.prim.abe ? " ABE" : " noABE")];
        ++m_hist["test ate=" + hex(c.test & 1) + " atst=" + hex((c.test >> 1) & 7) + " aref=" + hex((c.test >> 4) & 0xFF) + " afail=" + hex((c.test >> 12) & 3) + " ztst=" + hex((c.test >> 17) & 3)];
        ++m_hist["frame psm=" + hex(c.frame.psm) + " fbw=" + hex(c.frame.fbw) + " fbp=" + hex(c.frame.fbp) + " zpsm=" + hex(c.zbuf.psm) + " zbp=" + hex(c.zbuf.zbp) + (c.zbuf.zmask ? " ZMSK" : "")];
        if (b.state.prim.tme)
            ++m_hist["tex tfx=" + hex(c.tex0.tfx) + " tcc=" + hex(c.tex0.tcc) + " fst=" + hex(b.state.prim.fst) + " iip=" + hex(b.state.prim.iip) + " lin=" + hex(b.state.linearFilter) + " clamp=" + hex(c.clamp & 0xF) + " size=" + hex(b.state.textureWidth) + "x" + hex(b.state.textureHeight)];
        if (c.frame.fbmsk) ++m_hist["fbmsk=" + hex(c.frame.fbmsk)];
        noteTarget(fbp, c.frame.fbw, c.frame.psm);
        if (!c.zbuf.zmask && ((c.test >> 16) & 1u) != 0u)
            noteTarget(c.zbuf.zbp, c.frame.fbw, static_cast<uint8_t>(c.zbuf.psm | 0x30u)); // depth, flagged
        if (!b.state.prim.tme)
        {
            ++m_untextured;
            return;
        }
        if (fbp == tbp) ++m_feedback;
        if (c.zbuf.zbp == tbp) ++m_depthAsTex;
        {
            const auto up = m_uploads.find(tbp);
            if (up == m_uploads.end())
                ++m_hist["tex psm=" + hex(c.tex0.psm) + " no upload at tbp"];
            else
                ++m_hist["tex psm=" + hex(c.tex0.psm) + " tbw=" + hex(c.tex0.tbw) + " vs upload psm=" + hex(up->second[0]) + " bw=" + hex(up->second[1]) + " " + hex(up->second[2]) + "x" + hex(up->second[3]) + " tex=" + hex(b.state.textureWidth) + "x" + hex(b.state.textureHeight)];
        }
        const Target *t = findTarget(tbp);
        if (!t)
        {
            ++m_plainTex;
            ++m_texPsm[c.tex0.psm & 63];
            return;
        }
        const bool exact = (t->base == tbp);
        const bool sameFamily = family(t->psm) == family(c.tex0.psm);
        if (exact && t->psm == c.tex0.psm) ++m_rtSame;
        else if (exact && sameFamily) ++m_rtSameFamilyOtherPsm;
        else if (exact) ++m_rtReinterpret;
        else if (sameFamily) ++m_rtInsideSame;
        else ++m_rtInsideOther;
        if (!exact || !sameFamily || t->psm != c.tex0.psm)
            ++m_reinterpKinds[(static_cast<uint32_t>(t->psm) << 8) | c.tex0.psm];
    }
    void clut(const GSTex0Reg &t)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        ++m_clutLoads;
        if (findTarget(t.cbp)) ++m_clutFromRt;
    }
    void transfer(const GSTransferCommand &c)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        const uint32_t dir = c.direction;
        if (dir == 0u)
        {
            ++m_hostToLocal;
            m_uploads[c.bitbltbuf.dbp] = {c.bitbltbuf.dpsm, c.bitbltbuf.dbw, c.trxreg.rrw, c.trxreg.rrh};
            ++m_hist["upload dpsm=" + hex(c.bitbltbuf.dpsm) + " dbw=" + hex(c.bitbltbuf.dbw) + " " + hex(c.trxreg.rrw) + "x" + hex(c.trxreg.rrh)];
            if (findTarget(c.bitbltbuf.dbp)) ++m_uploadIntoRt;
            m_uploadPixels += static_cast<uint64_t>(c.trxreg.rrw) * c.trxreg.rrh;
        }
        else if (dir == 1u)
        {
            ++m_localToHost;
            if (findTarget(c.bitbltbuf.sbp)) ++m_readbackFromRt;
            m_readbackPixels += static_cast<uint64_t>(c.trxreg.rrw) * c.trxreg.rrh;
        }
        else
        {
            ++m_localToLocal;
            if (findTarget(c.bitbltbuf.sbp)) ++m_copyFromRt;
            if (findTarget(c.bitbltbuf.dbp)) ++m_copyIntoRt;
        }
    }
    void clear() { std::lock_guard<std::mutex> lock(m_mutex); ++m_clears; }
    void cpuRead() { std::lock_guard<std::mutex> lock(m_mutex); ++m_cpuRead; }
    void cpuWrite() { std::lock_guard<std::mutex> lock(m_mutex); ++m_cpuWrite; }
    void snapshot() { std::lock_guard<std::mutex> lock(m_mutex); ++m_snapshots; }
    void consumeL2H() { std::lock_guard<std::mutex> lock(m_mutex); ++m_consumeL2H; }
    void present()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        ++m_presents;
        const auto now = std::chrono::steady_clock::now();
        if (now - m_last < std::chrono::seconds(5))
            return;
        m_last = now;
        report();
        m_targets.clear();
    }

private:
    struct Target
    {
        uint32_t base, fbw;
        uint8_t psm;
    };
    GsInventory() : m_enabled(std::getenv("GOW_GS_INVENTORY") != nullptr), m_last(std::chrono::steady_clock::now()) {}
    static int family(uint8_t psm)
    {
        switch (psm & 0x0F)
        {
        case 0: case 1: return 32; // PSMCT32/24
        case 2: case 10: return 16; // PSMCT16 / 16S
        case 11: return 8;
        default: return psm & 0x0F;
        }
    }
    void noteTarget(uint32_t base, uint32_t fbw, uint8_t psm)
    {
        for (Target &t : m_targets)
            if (t.base == base)
            {
                t.fbw = fbw;
                t.psm = psm;
                return;
            }
        m_targets.push_back({base, fbw, psm});
    }
    // a target spans fbw*64 pixels x up to 448 rows = fbw * 14 pages * 32 blocks
    const Target *findTarget(uint32_t block) const
    {
        for (const Target &t : m_targets)
        {
            const uint32_t span = (t.fbw ? t.fbw : 10u) * 14u * 32u;
            if (block >= t.base && block < t.base + span)
                return &t;
        }
        return nullptr;
    }
    static std::string hex(uint64_t v)
    {
        char buf[24];
        std::snprintf(buf, sizeof(buf), "%llx", (unsigned long long)v);
        return buf;
    }
    void report()
    {
        {
            std::vector<std::pair<uint64_t, std::string>> top;
            for (const auto &kv : m_hist)
                top.emplace_back(kv.second, kv.first);
            std::sort(top.rbegin(), top.rend());
            for (size_t i = 0; i < top.size() && i < 70u; ++i)
                std::fprintf(stderr, "[gs-inv-h] %8llu  %s\n", (unsigned long long)top[i].first, top[i].second.c_str());
            m_hist.clear();
        }
        std::fprintf(stderr,
                     "[gs-inv] 5s: presents=%llu draws=%llu untextured=%llu plainTex=%llu | RT-as-texture: same=%llu samePageOtherPsm=%llu reinterpret=%llu insideSame=%llu insideOther=%llu"
                     " | feedback(fbp==tbp)=%llu depthAsTex=%llu clutFromRt=%llu/%llu\n",
                     (unsigned long long)m_presents, (unsigned long long)m_draws, (unsigned long long)m_untextured, (unsigned long long)m_plainTex,
                     (unsigned long long)m_rtSame, (unsigned long long)m_rtSameFamilyOtherPsm, (unsigned long long)m_rtReinterpret,
                     (unsigned long long)m_rtInsideSame, (unsigned long long)m_rtInsideOther, (unsigned long long)m_feedback,
                     (unsigned long long)m_depthAsTex, (unsigned long long)m_clutFromRt, (unsigned long long)m_clutLoads);
        std::fprintf(stderr,
                     "[gs-inv]     state: fbmsk!=0=%llu abe=%llu fog=%llu aa=%llu atest=%llu date=%llu zte=%llu dither=%llu pabe=%llu scanmsk=%llu prims(pt,ln,ls,tr,ts,tf,sp)=%llu,%llu,%llu,%llu,%llu,%llu,%llu\n",
                     (unsigned long long)m_fbmsk, (unsigned long long)m_abe, (unsigned long long)m_fog, (unsigned long long)m_aa,
                     (unsigned long long)m_atest, (unsigned long long)m_date, (unsigned long long)m_zte, (unsigned long long)m_dither,
                     (unsigned long long)m_pabe, (unsigned long long)m_scanmsk, (unsigned long long)m_prim[0], (unsigned long long)m_prim[1],
                     (unsigned long long)m_prim[2], (unsigned long long)m_prim[3], (unsigned long long)m_prim[4], (unsigned long long)m_prim[5],
                     (unsigned long long)m_prim[6]);
        std::fprintf(stderr,
                     "[gs-inv]     transfers: host->local=%llu (into RT %llu, %llu px) local->host=%llu (from RT %llu, %llu px) local->local=%llu (from RT %llu, into RT %llu) clears=%llu cpuRead=%llu cpuWrite=%llu snapshot=%llu consumeL2H=%llu\n",
                     (unsigned long long)m_hostToLocal, (unsigned long long)m_uploadIntoRt, (unsigned long long)m_uploadPixels,
                     (unsigned long long)m_localToHost, (unsigned long long)m_readbackFromRt, (unsigned long long)m_readbackPixels,
                     (unsigned long long)m_localToLocal, (unsigned long long)m_copyFromRt, (unsigned long long)m_copyIntoRt,
                     (unsigned long long)m_clears, (unsigned long long)m_cpuRead, (unsigned long long)m_cpuWrite,
                     (unsigned long long)m_snapshots, (unsigned long long)m_consumeL2H);
        for (const auto &kv : m_reinterpKinds)
            std::fprintf(stderr, "[gs-inv]     reinterpret rtPsm=%02x -> texPsm=%02x : %llu draws\n", kv.first >> 8, kv.first & 0xFF, (unsigned long long)kv.second);
        for (const auto &kv : m_texPsm)
            std::fprintf(stderr, "[gs-inv]     plain texture psm=%02x : %llu draws\n", kv.first, (unsigned long long)kv.second);
        m_draws = m_untextured = m_plainTex = m_rtSame = m_rtSameFamilyOtherPsm = m_rtReinterpret = m_rtInsideSame = m_rtInsideOther = 0;
        m_feedback = m_depthAsTex = m_clutFromRt = m_clutLoads = m_fbmsk = m_abe = m_fog = m_aa = m_atest = m_date = m_zte = m_dither = 0;
        m_pabe = m_scanmsk = m_hostToLocal = m_uploadIntoRt = m_uploadPixels = m_localToHost = m_readbackFromRt = m_readbackPixels = 0;
        m_localToLocal = m_copyFromRt = m_copyIntoRt = m_clears = m_cpuRead = m_cpuWrite = m_snapshots = m_consumeL2H = m_presents = 0;
        for (auto &p : m_prim) p = 0;
        m_reinterpKinds.clear();
        m_texPsm.clear();
    }

    bool m_enabled;
    std::mutex m_mutex;
    std::chrono::steady_clock::time_point m_last;
    std::vector<Target> m_targets;
    std::map<uint32_t, uint64_t> m_reinterpKinds, m_texPsm;
    std::map<std::string, uint64_t> m_hist;
    std::map<uint32_t, std::array<uint32_t, 4>> m_uploads;
    uint64_t m_prim[8]{};
    uint64_t m_draws = 0, m_untextured = 0, m_plainTex = 0, m_rtSame = 0, m_rtSameFamilyOtherPsm = 0, m_rtReinterpret = 0;
    uint64_t m_rtInsideSame = 0, m_rtInsideOther = 0, m_feedback = 0, m_depthAsTex = 0, m_clutFromRt = 0, m_clutLoads = 0;
    uint64_t m_fbmsk = 0, m_abe = 0, m_fog = 0, m_aa = 0, m_atest = 0, m_date = 0, m_zte = 0, m_dither = 0, m_pabe = 0, m_scanmsk = 0;
    uint64_t m_hostToLocal = 0, m_uploadIntoRt = 0, m_uploadPixels = 0, m_localToHost = 0, m_readbackFromRt = 0, m_readbackPixels = 0;
    uint64_t m_localToLocal = 0, m_copyFromRt = 0, m_copyIntoRt = 0, m_clears = 0, m_cpuRead = 0, m_cpuWrite = 0, m_snapshots = 0;
    uint64_t m_consumeL2H = 0, m_presents = 0;
};
