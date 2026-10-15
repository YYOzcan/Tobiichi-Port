// GOW-Port: native texture / CLUT store, see gs_texture_store.h.
#include "gs_texture_store.h"
#include "../gs_gpu_helpers.h"
#include "runtime/gs/ps2_gs_memory.h"

#include <algorithm>
#include <cstring>
#include <mutex>
#include <stdexcept>

using namespace GSCpuInternal;

namespace
{
    // GS memory layout per PSM (swizzle tables of ps2_gs_memory): the game's own data layout.
    uint32_t readPixel(uint8_t *vram, uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
    {
        using namespace GSMem;
        switch (psm & 0x3Fu)
        {
        case GS_PSM_CT32: return ReadCT32(vram, base, bw, x, y);
        case GS_PSM_CT24: return ReadCT24(vram, base, bw, x, y);
        case GS_PSM_CT16: return ReadCT16(vram, base, bw, x, y);
        case GS_PSM_CT16S: return ReadCT16S(vram, base, bw, x, y);
        case GS_PSM_T8: return ReadP8(vram, base, bw, x, y);
        case GS_PSM_T8H: return ReadP8H(vram, base, bw, x, y);
        case GS_PSM_T4: return ReadP4(vram, base, bw, x, y);
        case GS_PSM_T4HH: return ReadP4HH(vram, base, bw, x, y);
        case GS_PSM_T4HL: return ReadP4HL(vram, base, bw, x, y);
        case GS_PSM_Z32: return ReadZ32(vram, base, bw, x, y);
        case GS_PSM_Z24: return ReadZ24(vram, base, bw, x, y);
        case GS_PSM_Z16: return ReadZ16(vram, base, bw, x, y);
        case GS_PSM_Z16S: return ReadZ16S(vram, base, bw, x, y);
        default: return 0u;
        }
    }

    void writePixel(uint8_t *vram, uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value)
    {
        using namespace GSMem;
        switch (psm & 0x3Fu)
        {
        case GS_PSM_CT32: WriteCT32(vram, base, bw, x, y, value); break;
        case GS_PSM_CT24: WriteCT24(vram, base, bw, x, y, value); break;
        case GS_PSM_CT16: WriteCT16(vram, base, bw, x, y, value); break;
        case GS_PSM_CT16S: WriteCT16S(vram, base, bw, x, y, value); break;
        case GS_PSM_T8: WriteP8(vram, base, bw, x, y, value); break;
        case GS_PSM_T8H: WriteP8H(vram, base, bw, x, y, value); break;
        case GS_PSM_T4: WriteP4(vram, base, bw, x, y, value); break;
        case GS_PSM_T4HH: WriteP4HH(vram, base, bw, x, y, value); break;
        case GS_PSM_T4HL: WriteP4HL(vram, base, bw, x, y, value); break;
        case GS_PSM_Z32: WriteZ32(vram, base, bw, x, y, value); break;
        case GS_PSM_Z24: WriteZ24(vram, base, bw, x, y, value); break;
        case GS_PSM_Z16: WriteZ16(vram, base, bw, x, y, value); break;
        case GS_PSM_Z16S: WriteZ16S(vram, base, bw, x, y, value); break;
        default: break;
        }
    }
}

void GSTextureStore::Initialize(uint8_t *vram, uint32_t vramSize)
{
    if (vram && vramSize < GSMem::MEMORY_SIZE)
        throw std::invalid_argument("GS texture store requires the 4 MiB GS memory image");
    static std::once_flag tablesOnce;
    std::call_once(tablesOnce, [] { GSMem::InitLookupTables(); });
    m_vram = vram;
    m_vramSize = vramSize;
    Reset();
}

void GSTextureStore::Reset()
{
    m_clut.fill(0u);
    m_clutCbp.fill(0u);
    m_transfer = {};
    m_transfer.direction = 3u;
    m_state = {};
    m_state.direction = 3u;
    m_upload24 = {};
}

// ---- CLUT ------------------------------------------------------------------------------------------------------------

void GSTextureStore::LoadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut, const ClutSource &source)
{
    const bool fourBit = isFourBitIndexedPsm(tex0.psm);
    if (!m_vram || (!fourBit && !isEightBitIndexedPsm(tex0.psm)))
        return;
    switch (tex0.cld) // CLD: 1 always, 2/3 always + set CBP0/1, 4/5 only when CBP differs from CBP0/1
    {
    case 1u: break;
    case 2u: m_clutCbp[0] = tex0.cbp; break;
    case 3u: m_clutCbp[1] = tex0.cbp; break;
    case 4u: if (m_clutCbp[0] == tex0.cbp) return; m_clutCbp[0] = tex0.cbp; break;
    case 5u: if (m_clutCbp[1] == tex0.cbp) return; m_clutCbp[1] = tex0.cbp; break;
    default: return;
    }

    const bool sixteenBit = tex0.cpsm == GS_PSM_CT16 || tex0.cpsm == GS_PSM_CT16S;
    const bool thirtyTwoBit = tex0.cpsm == GS_PSM_CT32 || tex0.cpsm == GS_PSM_CT24;
    if (!sixteenBit && !thirtyTwoBit)
        return;
    const uint32_t entryCount = fourBit ? 16u : 256u;
    const uint32_t destinationBase = (static_cast<uint32_t>(tex0.csa) & (sixteenBit ? 0x1Fu : 0x0Fu)) << 4u;
    // CSM1 with a 32-bit 256-colour CLUT: entries below CSA*16 keep their previous values.
    const bool loadCsm1Suffix = tex0.csm == 0u && thirtyTwoBit && !fourBit;
    const uint32_t first = loadCsm1Suffix ? destinationBase : 0u;
    // CSM1: 16x16 (8x2 for 16 colours) block with bits 3 and 4 of the index swapped, in a 64 px wide buffer;
    // CSM2: one line at (COU*16, COV) of a CBW-wide buffer
    const uint32_t sourceWidth = tex0.csm == 0u ? 1u : (texclut.cbw != 0u ? static_cast<uint32_t>(texclut.cbw) : 1u);
    std::array<uint16_t, 512> xy{};
    const uint32_t count = entryCount - first;
    for (uint32_t i = 0; i < count; ++i)
    {
        const uint32_t entry = first + i;
        if (tex0.csm == 0u)
        {
            const uint32_t sourceIndex = swizzleClutIndexCSM1(entry);
            xy[i * 2u] = static_cast<uint16_t>(sourceIndex & 0x0Fu);
            xy[i * 2u + 1u] = static_cast<uint16_t>(sourceIndex >> 4u);
        }
        else
        {
            xy[i * 2u] = static_cast<uint16_t>((static_cast<uint32_t>(texclut.cou) << 4u) + entry);
            xy[i * 2u + 1u] = static_cast<uint16_t>(texclut.cov);
        }
    }
    std::array<uint32_t, 256> words{};
    if (!source || !source(tex0, sourceWidth, xy.data(), count, words.data()))
        for (uint32_t i = 0; i < count; ++i)
            words[i] = readPixel(m_vram, tex0.cpsm, tex0.cbp, sourceWidth, xy[i * 2u], xy[i * 2u + 1u]);
    for (uint32_t i = 0; i < count; ++i)
    {
        const uint32_t entry = first + i, raw = words[i];
        const uint32_t destination = (loadCsm1Suffix ? entry : destinationBase + entry) & (sixteenBit ? 0x1FFu : 0x0FFu);
        if (sixteenBit)
            m_clut[destination] = static_cast<uint16_t>(raw);
        else
        {
            m_clut[destination] = static_cast<uint16_t>(raw & 0xFFFFu);
            m_clut[destination + 256u] = static_cast<uint16_t>(raw >> 16u);
        }
    }
}

uint64_t GSTextureStore::ClutHash() const
{
    uint64_t hash = 1469598103934665603ull;
    for (uint16_t v : m_clut)
        hash = (hash ^ v) * 1099511628211ull;
    return hash;
}

uint32_t GSTextureStore::ClutColor(const GSDrawState &state, uint32_t index) const
{
    const GSTex0Reg &t = state.context.tex0;
    const bool sixteenBit = t.cpsm == GS_PSM_CT16 || t.cpsm == GS_PSM_CT16S;
    const uint32_t clutBase = (static_cast<uint32_t>(t.csa) & (sixteenBit ? 0x1Fu : 0x0Fu)) << 4u;
    const uint32_t sourceIndex = isFourBitIndexedPsm(t.psm) ? (index & 0x0Fu) : (index & 0xFFu);
    uint32_t clutIndex = (clutBase + sourceIndex) & (sixteenBit ? 0x1FFu : 0x0FFu);
    if (!sixteenBit && t.csm == 0u && isEightBitIndexedPsm(t.psm))
        clutIndex = std::min((sourceIndex & 0xF0u) + clutBase, 240u) + (sourceIndex & 0x0Fu);
    switch (t.cpsm)
    {
    case GS_PSM_CT32:
        return applyTexa(state.texa, t.cpsm, static_cast<uint32_t>(m_clut[clutIndex]) | (static_cast<uint32_t>(m_clut[clutIndex + 256u]) << 16u));
    case GS_PSM_CT24:
        return applyTexa(state.texa, t.cpsm, (static_cast<uint32_t>(m_clut[clutIndex]) | (static_cast<uint32_t>(m_clut[clutIndex + 256u]) << 16u)) & 0x00FFFFFFu);
    case GS_PSM_CT16:
    case GS_PSM_CT16S:
        return applyTexa(state.texa, t.cpsm, Rgba5551ToRgba8888(m_clut[clutIndex]));
    default:
        return 0xFFFF00FFu;
    }
}

void GSTextureStore::BuildPalette(const GSDrawState &state, uint32_t out[256]) const
{
    for (uint32_t i = 0; i < 256u; ++i)
        out[i] = ClutColor(state, i);
}

void GSTextureStore::DecodeTextureRgba(const GSDrawState &state, std::vector<uint32_t> &out) const
{
    const GSTex0Reg &t = state.context.tex0;
    const uint32_t w = std::max<uint32_t>(1u, state.textureWidth), h = std::max<uint32_t>(1u, state.textureHeight);
    const uint64_t clamp = state.context.clamp;
    const uint8_t wrapU = static_cast<uint8_t>(clamp & 0x3u), wrapV = static_cast<uint8_t>((clamp >> 2) & 0x3u);
    const uint16_t minU = static_cast<uint16_t>((clamp >> 4) & 0x3FFu), maxU = static_cast<uint16_t>((clamp >> 14) & 0x3FFu);
    const uint16_t minV = static_cast<uint16_t>((clamp >> 24) & 0x3FFu), maxV = static_cast<uint16_t>((clamp >> 34) & 0x3FFu);
    out.resize(static_cast<size_t>(w) * h);
    for (uint32_t y = 0; y < h; ++y)
        for (uint32_t x = 0; x < w; ++x)
        {
            const int u = wrapTextureCoordinate(static_cast<int>(std::min<uint32_t>(x, 4095u)), static_cast<int>(w), wrapU, minU, maxU);
            const int v = wrapTextureCoordinate(static_cast<int>(std::min<uint32_t>(y, 4095u)), static_cast<int>(h), wrapV, minV, maxV);
            const uint32_t raw = m_vram ? readPixel(m_vram, t.psm, t.tbp0, t.tbw, static_cast<uint32_t>(u), static_cast<uint32_t>(v)) : 0u;
            uint32_t texel = 0xFFFF00FFu;
            switch (t.psm)
            {
            case GS_PSM_CT32: case GS_PSM_Z32: case GS_PSM_CT24: case GS_PSM_Z24:
                texel = applyTexa(state.texa, t.psm, raw);
                break;
            case GS_PSM_CT16: case GS_PSM_CT16S: case GS_PSM_Z16: case GS_PSM_Z16S:
                texel = applyTexa(state.texa, t.psm, Rgba5551ToRgba8888(static_cast<uint16_t>(raw)));
                break;
            case GS_PSM_T8: case GS_PSM_T8H: case GS_PSM_T4: case GS_PSM_T4HL: case GS_PSM_T4HH:
                texel = ClutColor(state, raw & 0xFFu);
                break;
            default:
                break;
            }
            out[static_cast<size_t>(y) * w + x] = texel;
        }
}

// ---- transfers -------------------------------------------------------------------------------------------------------

void GSTextureStore::BeginTransfer(const GSTransferCommand &command)
{
    m_transfer = command;
    m_upload24 = {};
    m_state.x = command.trxpos.dsax;
    m_state.y = command.trxpos.dsay;
    m_state.totalPixels = static_cast<uint32_t>(command.trxreg.rrw) * static_cast<uint32_t>(command.trxreg.rrh);
    m_state.copiedPixels = 0u;
    m_state.direction = command.direction;
    m_state.localToHostPendingBytes = 0u;
    if (command.direction == 2u)
        CopyLocalToLocal();
    else if (command.direction == 1u)
        m_state.copiedPixels = m_state.totalPixels; // nothing is read back (never used by the game)
}

void GSTextureStore::Upload(const uint8_t *data, uint32_t sizeBytes)
{
    if (!data || !sizeBytes || !m_vram || m_state.direction != 0u || !m_state.totalPixels)
        return;
    if (m_transfer.bitbltbuf.dpsm == GS_PSM_CT24 || m_transfer.bitbltbuf.dpsm == GS_PSM_Z24)
        m_upload24.consume(data, sizeBytes, [&](const uint8_t *aligned, uint32_t bytes) {
            UploadAligned(aligned, bytes);
            return m_state.direction == 0u;
        });
    else
        UploadAligned(data, sizeBytes);
}

// Host->local pixels in transfer order (left to right, top to bottom inside the TRXPOS/TRXREG rectangle).
void GSTextureStore::UploadAligned(const uint8_t *data, uint32_t sizeBytes)
{
    if (!data || sizeBytes == 0u || !m_vram || m_state.direction != 0u)
        return;
    if (m_transfer.trxreg.rrw == 0u || m_transfer.trxreg.rrh == 0u || m_state.totalPixels == 0u)
        return;
    const uint32_t dbp = m_transfer.bitbltbuf.dbp;
    const uint32_t dbw = std::max<uint32_t>(m_transfer.bitbltbuf.dbw, 1u);
    const uint8_t dpsm = m_transfer.bitbltbuf.dpsm;
    const uint32_t rrw = m_transfer.trxreg.rrw;
    const uint32_t dsax = m_transfer.trxpos.dsax, dsay = m_transfer.trxpos.dsay;
    auto advance = [&](uint32_t count)
    {
        m_state.copiedPixels = std::min<uint32_t>(m_state.totalPixels, m_state.copiedPixels + count);
        if (m_state.copiedPixels >= m_state.totalPixels)
        {
            m_state.direction = 3u;
            m_state.totalPixels = 0u;
            return;
        }
        m_state.x = dsax + (m_state.copiedPixels % rrw);
        m_state.y = dsay + (m_state.copiedPixels / rrw);
    };
    uint32_t bits;
    switch (dpsm)
    {
    case GS_PSM_CT32: case GS_PSM_Z32: bits = 32u; break;
    case GS_PSM_CT24: case GS_PSM_Z24: bits = 24u; break;
    case GS_PSM_CT16: case GS_PSM_CT16S: case GS_PSM_Z16: case GS_PSM_Z16S: bits = 16u; break;
    case GS_PSM_T8: case GS_PSM_T8H: bits = 8u; break;
    case GS_PSM_T4: case GS_PSM_T4HL: case GS_PSM_T4HH: bits = 4u; break;
    default: return;
    }
    // Whole pixels in this chunk (a 24 bit pixel split across chunks is joined by Upload), written one row run at a time.
    const uint32_t avail = static_cast<uint32_t>((static_cast<uint64_t>(sizeBytes) * 8u) / bits);
    uint32_t done = 0u;
    while (done < avail && m_state.direction == 0u)
    {
        const uint32_t n = std::min({dsax + rrw - m_state.x, avail - done, m_state.totalPixels - m_state.copiedPixels});
        GSMem::WriteRun(m_vram, dpsm, dbp, dbw, m_state.x, m_state.y, data, done, n);
        done += n;
        advance(n);
    }
}

void GSTextureStore::CopyLocalToLocal()
{
    const uint32_t rrw = m_transfer.trxreg.rrw, rrh = m_transfer.trxreg.rrh, total = rrw * rrh;
    if (m_vram && total != 0u)
    {
        const GSBitBltBuf &b = m_transfer.bitbltbuf;
        const GSTrxPos &p = m_transfer.trxpos;
        for (uint32_t pixel = 0; pixel < total; ++pixel)
        {
            uint32_t x = pixel % rrw, y = pixel / rrw;
            if ((p.dir & 0x2u) != 0u)
                x = rrw - x - 1u;
            if ((p.dir & 0x1u) != 0u)
                y = rrh - y - 1u;
            const uint32_t value = readPixel(m_vram, b.spsm, b.sbp, std::max<uint32_t>(b.sbw, 1u), x + p.ssax, y + p.ssay);
            writePixel(m_vram, b.dpsm, b.dbp, std::max<uint32_t>(b.dbw, 1u), x + p.dsax, y + p.dsay, value);
        }
    }
    m_state.copiedPixels = total;
    m_state.direction = 3u;
}

// ---- raw access ------------------------------------------------------------------------------------------------------

uint32_t GSTextureStore::Read(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
{
    return m_vram ? readPixel(m_vram, psm, base, bw, x, y) : 0u;
}

void GSTextureStore::Write(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value)
{
    if (m_vram)
        writePixel(m_vram, psm, base, bw, x, y, value);
}

void GSTextureStore::Snapshot(std::vector<uint8_t> &out) const
{
    if (!m_vram || m_vramSize == 0u)
    {
        out.clear();
        return;
    }
    out.assign(m_vram, m_vram + m_vramSize);
}
