#include "sound_engine.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr int32_t kAdpcmFilters[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};
        constexpr size_t kMaxBufferedFrames = 48000u * 2u; // 2 s; without a consumer the oldest samples are dropped

        // libsd ids (entry >> 8), in the order of LIBSD's register table (LIBSD.IRX 0x4930, docs/sound.md)
        enum : uint32_t
        {
            IdVolL = 0x00, IdVolR = 0x01, IdPitch = 0x02, IdAdsr1 = 0x03, IdAdsr2 = 0x04, IdEnvx = 0x05, IdVolXL = 0x06,
            IdVolXR = 0x07, IdMmix = 0x08, IdMvolL = 0x09, IdMvolR = 0x0A, IdEvolL = 0x0B, IdEvolR = 0x0C, IdAvolL = 0x0D,
            IdAvolR = 0x0E, IdBvolL = 0x0F, IdBvolR = 0x10, IdMvolXL = 0x11, IdMvolXR = 0x12,
            IdPmon = 0x13, IdNon = 0x14, IdKon = 0x15, IdKoff = 0x16, IdEndx = 0x17, IdVmixL = 0x18, IdVmixEL = 0x19,
            IdVmixR = 0x1A, IdVmixER = 0x1B,
            IdEsa = 0x1C, IdEea = 0x1D, IdTsa = 0x1E, IdIrqa = 0x1F, IdSsa = 0x20, IdLsa = 0x21, IdNax = 0x22,
        };

        int16_t clamp16(int32_t value) noexcept
        {
            return static_cast<int16_t>(std::clamp(value, -32768, 32767));
        }

        // voice / core volume: fixed mode (bit 15 = 0) = 15-bit signed; sweep mode applies its target at once
        int32_t volumeOf(uint16_t value) noexcept
        {
            if ((value & 0x8000u) == 0u)
                return static_cast<int16_t>(value << 1u) >> 1; // -0x4000..0x3FFF
            return (value & 0x2000u) != 0u ? 0 : 0x3FFF;
        }

        uint32_t idOf(uint32_t entry) noexcept { return (entry >> 8u) & 0xFFu; }
        uint32_t coreOf(uint32_t entry) noexcept { return entry & 1u; }
        uint32_t voiceOf(uint32_t entry) noexcept { return (entry >> 1u) & 0x1Fu; }
    }

    SoundEngine::SoundEngine() : m_ram(RamHalfwords)
    {
        reset();
    }

    void SoundEngine::reset()
    {
        std::fill(m_ram.begin(), m_ram.end(), uint16_t{0});
        m_cores = {};
        m_stream = {};
        m_streamHalf = {};
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            m_output.clear();
        }
        m_lastCycle = 0;
    }

    void SoundEngine::initCore(uint32_t core)
    {
        Core &c = m_cores[core & 1u];
        const std::array<Voice, VoicesPerCore> voices{};
        c = Core{};
        c.voices = voices;
        m_stream[core & 1u] = {};
    }

    // ---- parameters ----------------------------------------------------------------------------------------------

    void SoundEngine::setParam(uint32_t entry, uint16_t value)
    {
        Core &c = m_cores[coreOf(entry)];
        const uint32_t voice = voiceOf(entry);
        // GOW_SND_REGLOG=1: core-level writes (MMIX, master/effect/input volumes) as the driver sets them
        static const bool regLog = std::getenv("GOW_SND_REGLOG") != nullptr;
        if (regLog && idOf(entry) >= IdMmix && idOf(entry) <= IdBvolR)
            std::fprintf(stderr, "[snd-reg] core=%u id=%02x value=%04x\n", coreOf(entry), idOf(entry), value);
        // GOW_SND_CALLLOG=1: voice volume / pitch writes that change the value
        static const bool callLog = std::getenv("GOW_SND_CALLLOG") != nullptr;
        if (callLog && voice < VoicesPerCore && idOf(entry) <= IdPitch)
        {
            const Voice &v = c.voices[voice];
            const uint16_t old = idOf(entry) == IdVolL ? v.volL : idOf(entry) == IdVolR ? v.volR : v.pitch;
            if (old != value)
                std::fprintf(stderr, "[snd-call] core=%u voice=%u id=%02x %04x -> %04x\n", coreOf(entry), voice, idOf(entry), old, value);
        }
        switch (idOf(entry))
        {
        case IdVolL: if (voice < VoicesPerCore) c.voices[voice].volL = value; break;
        case IdVolR: if (voice < VoicesPerCore) c.voices[voice].volR = value; break;
        case IdPitch: if (voice < VoicesPerCore) c.voices[voice].pitch = value; break;
        case IdAdsr1: if (voice < VoicesPerCore) c.voices[voice].adsr1 = value; break;
        case IdAdsr2: if (voice < VoicesPerCore) c.voices[voice].adsr2 = value; break;
        case IdMmix: c.mmix = value; break;
        case IdMvolL: c.mvolL = value; break;
        case IdMvolR: c.mvolR = value; break;
        case IdEvolL: c.evolL = value; break;
        case IdEvolR: c.evolR = value; break;
        case IdAvolL: c.avolL = value; break;
        case IdAvolR: c.avolR = value; break;
        case IdBvolL: c.bvolL = value; break;
        case IdBvolR: c.bvolR = value; break;
        default: break; // ENVX / VOLX / MVOLX are read-only
        }
    }

    uint16_t SoundEngine::getParam(uint32_t entry) const
    {
        const Core &c = m_cores[coreOf(entry)];
        const uint32_t voice = std::min(voiceOf(entry), VoicesPerCore - 1u);
        const Voice &v = c.voices[voice];
        switch (idOf(entry))
        {
        case IdVolL: return v.volL;
        case IdVolR: return v.volR;
        case IdPitch: return v.pitch;
        case IdAdsr1: return v.adsr1;
        case IdAdsr2: return v.adsr2;
        case IdEnvx: return static_cast<uint16_t>(v.envelope);
        case IdVolXL: return static_cast<uint16_t>(volumeOf(v.volL) << 1);
        case IdVolXR: return static_cast<uint16_t>(volumeOf(v.volR) << 1);
        case IdMmix: return c.mmix;
        case IdMvolL: return c.mvolL;
        case IdMvolR: return c.mvolR;
        case IdEvolL: return c.evolL;
        case IdEvolR: return c.evolR;
        case IdAvolL: return c.avolL;
        case IdAvolR: return c.avolR;
        case IdBvolL: return c.bvolL;
        case IdBvolR: return c.bvolR;
        case IdMvolXL: return static_cast<uint16_t>(volumeOf(c.mvolL) << 1);
        case IdMvolXR: return static_cast<uint16_t>(volumeOf(c.mvolR) << 1);
        default: return 0;
        }
    }

    // ---- switches (24-bit voice masks) ---------------------------------------------------------------------------

    void SoundEngine::setSwitch(uint32_t entry, uint32_t mask)
    {
        Core &c = m_cores[coreOf(entry)];
        mask &= 0xFFFFFFu;
        static const bool callLog = std::getenv("GOW_SND_CALLLOG") != nullptr;
        if (callLog && (idOf(entry) == IdKon || idOf(entry) == IdKoff) && mask != 0u)
            std::fprintf(stderr, "[snd-call] core=%u %s %06x\n", coreOf(entry), idOf(entry) == IdKon ? "KON" : "KOFF", mask);
        switch (idOf(entry))
        {
        case IdPmon: c.pmon = mask; break;
        case IdNon: c.non = mask; break;
        case IdKon: keyOn(c, mask); break;
        case IdKoff: keyOff(c, mask); break;
        case IdEndx: c.endx = 0; break; // writing ENDX clears it
        case IdVmixL: c.vmixL = mask; break;
        case IdVmixEL: c.vmixEL = mask; break;
        case IdVmixR: c.vmixR = mask; break;
        case IdVmixER: c.vmixER = mask; break;
        default: break;
        }
    }

    uint32_t SoundEngine::getSwitch(uint32_t entry) const
    {
        const Core &c = m_cores[coreOf(entry)];
        switch (idOf(entry))
        {
        case IdPmon: return c.pmon;
        case IdNon: return c.non;
        case IdEndx: return c.endx;
        case IdVmixL: return c.vmixL;
        case IdVmixEL: return c.vmixEL;
        case IdVmixR: return c.vmixR;
        case IdVmixER: return c.vmixER;
        default: return 0; // KON / KOFF read back as 0
        }
    }

    // ---- addresses (libsd: byte addresses, 16-byte aligned; stored as halfwords) ---------------------------------

    void SoundEngine::setAddr(uint32_t entry, uint32_t byteAddress)
    {
        Core &c = m_cores[coreOf(entry)];
        const uint32_t halfwords = (byteAddress >> 1u) & (RamHalfwords - 1u) & ~7u;
        const uint32_t voice = voiceOf(entry);
        switch (idOf(entry))
        {
        case IdEsa: c.esa = halfwords; break;
        case IdEea: c.eea = halfwords; break;
        case IdTsa: c.tsa = halfwords; break;
        case IdIrqa: c.irqa = halfwords; break;
        case IdSsa:
            if (voice < VoicesPerCore)
                c.voices[voice].ssa = halfwords;
            break;
        case IdLsa:
            if (voice < VoicesPerCore)
            {
                c.voices[voice].lsa = halfwords;
                c.voices[voice].lsaFromDriver = true; // the driver's loop start wins over block flags
            }
            break;
        case IdNax:
            if (voice < VoicesPerCore)
            {
                Voice &v = c.voices[voice];
                v.nax = halfwords;
                v.playBlock = halfwords; // reads back as written until the next block is decoded
                v.playStarted = false;
            }
            break;
        default: break;
        }
    }

    uint32_t SoundEngine::getAddr(uint32_t entry) const
    {
        const Core &c = m_cores[coreOf(entry)];
        const Voice &v = c.voices[std::min(voiceOf(entry), VoicesPerCore - 1u)];
        uint32_t halfwords = 0;
        switch (idOf(entry))
        {
        case IdEsa: halfwords = c.esa; break;
        case IdEea: halfwords = c.eea; break;
        case IdTsa: halfwords = c.tsa; break;
        case IdIrqa: halfwords = c.irqa; break;
        case IdSsa: halfwords = v.ssa; break;
        case IdLsa: halfwords = v.lsa; break;
        case IdNax: halfwords = naxOf(v); break;
        default: break;
        }
        return halfwords << 1u;
    }

    // NAX as PCSX2 reports NextA: always inside the block being played (block + 1 .. block + 7). 'nax' is the next block
    // to decode; during the last block of a streaming half it already lies past the half, and 989snd (989NOMID.IRX
    // 0x13258) then aborts the stream (error 0x35): the music restarted every few seconds.
    uint32_t SoundEngine::naxOf(const Voice &v) noexcept
    {
        if (!v.playStarted)
            return (v.playBlock | 1u) & (RamHalfwords - 1u);
        const uint32_t played = std::min<uint32_t>(v.decodedIndex, 27u) / 4u; // 0..6 (4 samples per halfword)
        return (v.playBlock + 1u + played) & (RamHalfwords - 1u);
    }

    // sceSdSetCoreAttr ids (entry & ~1): 2 effect enable, 4 IRQ enable, 6 mute, 8 noise clock, 0xA SPDIF mode
    void SoundEngine::setCoreAttr(uint32_t entry, uint32_t value)
    {
        Core &c = m_cores[coreOf(entry)];
        switch (entry & ~1u)
        {
        case 2: c.attr = static_cast<uint16_t>((c.attr & ~0x0080u) | (value ? 0x0080u : 0u)); break;
        case 4: c.attr = static_cast<uint16_t>((c.attr & ~0x0040u) | (value ? 0x0040u : 0u)); break;
        case 6: c.attr = static_cast<uint16_t>((c.attr & ~0x4000u) | (value ? 0x4000u : 0u)); break;
        case 8: c.attr = static_cast<uint16_t>((c.attr & ~0x3F00u) | ((value & 0x3Fu) << 8u)); break;
        default: break;
        }
    }

    uint32_t SoundEngine::getCoreAttr(uint32_t entry) const
    {
        const Core &c = m_cores[coreOf(entry)];
        switch (entry & ~1u)
        {
        case 2: return (c.attr >> 7u) & 1u;
        case 4: return (c.attr >> 6u) & 1u;
        case 6: return (c.attr >> 14u) & 1u;
        case 8: return (c.attr >> 8u) & 0x3Fu;
        default: return 0u;
        }
    }

    // ---- sample RAM --------------------------------------------------------------------------------------------------

    void SoundEngine::writeSampleRam(uint32_t byteAddress, const uint8_t *source, size_t bytes)
    {
        uint32_t halfword = byteAddress >> 1u;
        for (size_t i = 0; i + 1u < bytes; i += 2u)
            m_ram[halfword++ & (RamHalfwords - 1u)] = static_cast<uint16_t>(source[i] | (source[i + 1u] << 8u));
    }

    void SoundEngine::readSampleRam(uint32_t byteAddress, uint8_t *destination, size_t bytes) const
    {
        uint32_t halfword = byteAddress >> 1u;
        for (size_t i = 0; i + 1u < bytes; i += 2u)
        {
            const uint16_t value = m_ram[halfword++ & (RamHalfwords - 1u)];
            destination[i] = static_cast<uint8_t>(value);
            destination[i + 1u] = static_cast<uint8_t>(value >> 8u);
        }
    }

    void SoundEngine::clearSampleRam(uint32_t byteAddress, size_t bytes)
    {
        uint32_t halfword = byteAddress >> 1u;
        for (size_t i = 0; i + 1u < bytes; i += 2u)
            m_ram[halfword++ & (RamHalfwords - 1u)] = 0u;
    }

    // ---- core input stream -------------------------------------------------------------------------------------------

    void SoundEngine::startStream(uint32_t core, const uint8_t *ring, uint32_t size, bool loop)
    {
        StreamRing &s = m_stream[core & 1u];
        s.loop = loop;
        s.base = ring;
        s.size = size & ~0x3FFu; // whole 1 KB L/R block pairs
        s.position = 0;
        s.active = ring != nullptr && s.size != 0u;
        m_streamHalf[core & 1u] = false;
    }

    void SoundEngine::stopStream(uint32_t core)
    {
        m_stream[core & 1u].active = false;
    }

    bool SoundEngine::takeStreamHalf(uint32_t core) noexcept
    {
        const bool half = m_streamHalf[core & 1u];
        m_streamHalf[core & 1u] = false;
        return half;
    }

    // One sample per channel from the ring: blocks of 256 left samples (512 bytes) then 256 right samples.
    void SoundEngine::streamSample(uint32_t core, int32_t &left, int32_t &right)
    {
        StreamRing &s = m_stream[core];
        if (!s.active)
            return;
        const uint32_t block = s.position & ~0x3FFu, index = (s.position & 0x3FFu) >> 1u; // sample 0..255 in the block
        int16_t l, r;
        std::memcpy(&l, s.base + block + index * 2u, 2u);
        std::memcpy(&r, s.base + block + 0x200u + index * 2u, 2u);
        const Core &c = m_cores[core];
        // BVOL (sound-data input volume) is a plain 16-bit signed level (0x7FFF = 1.0), not the voice volume format
        // with fixed/sweep modes; 989snd sets 0x7FFE for the movie stream.
        const auto inputVolume = [](uint16_t v) { return static_cast<int32_t>(static_cast<int16_t>(v)) >> 1; };
        if ((c.mmix & 0x0080u) != 0u) // MMIX sound-input bits: the driver enables them while its stream runs
            left += (l * inputVolume(c.bvolL)) >> 14;
        if ((c.mmix & 0x0040u) != 0u)
            right += (r * inputVolume(c.bvolR)) >> 14;
        const uint32_t before = s.position;
        s.position = block + ((index + 1u) * 2u);
        if (index + 1u == 256u)
            s.position = block + 0x400u;
        if (s.position >= s.size)
        {
            s.position = 0;
            if (!s.loop)
                s.active = false;
        }
        const uint32_t half = s.size / 2u;
        if ((before < half && s.position >= half) || s.position == 0)
            m_streamHalf[core] = true;
    }

    // ---- voices ------------------------------------------------------------------------------------------------------

    void SoundEngine::keyOn(Core &c, uint32_t mask)
    {
        for (uint32_t index = 0; index < VoicesPerCore; ++index)
        {
            if ((mask & (1u << index)) == 0u)
                continue;
            Voice &v = c.voices[index];
            Voice fresh{};
            fresh.volL = v.volL;
            fresh.volR = v.volR;
            fresh.pitch = v.pitch;
            fresh.adsr1 = v.adsr1;
            fresh.adsr2 = v.adsr2;
            fresh.ssa = v.ssa;
            fresh.active = true;
            fresh.nax = v.ssa & ~7u;
            fresh.lsa = v.ssa & ~7u;
            fresh.playBlock = v.ssa & ~7u; // NAX reads SSA | 1 until the first block is decoded (PCSX2 Start())
            fresh.phase = Voice::Phase::Attack;
            v = fresh;
            c.endx &= ~(1u << index);
        }
    }

    void SoundEngine::keyOff(Core &c, uint32_t mask)
    {
        for (uint32_t index = 0; index < VoicesPerCore; ++index)
        {
            Voice &v = c.voices[index];
            if ((mask & (1u << index)) != 0u && v.active)
            {
                v.phase = Voice::Phase::Release;
                v.envelopeCounter = 0;
            }
        }
    }

    void SoundEngine::decodeBlock(Core &c, uint32_t index)
    {
        Voice &v = c.voices[index];
        // end of the previous block: with the end flag jump to LSA; without "repeat" the voice stops
        if ((v.blockFlags & 1u) != 0u)
        {
            c.endx |= 1u << index;
            v.nax = v.lsa;
            if ((v.blockFlags & 2u) == 0u)
            {
                v.active = false;
                v.phase = Voice::Phase::Off;
                v.envelope = 0;
            }
        }
        v.blockFlags = 0;
        if (!v.active)
            return;

        const uint32_t block = v.nax & (RamHalfwords - 1u);
        const uint16_t header = m_ram[block];
        uint32_t shift = header & 0xFu;
        if (shift > 12u)
            shift = 9u;
        const uint32_t filter = std::min<uint32_t>((header >> 4u) & 7u, 4u);
        v.blockFlags = static_cast<uint8_t>(header >> 8u);
        if ((v.blockFlags & 4u) != 0u && !v.lsaFromDriver)
            v.lsa = block;

        for (uint32_t word = 1; word < 8u; ++word)
        {
            const uint16_t packed = m_ram[(block + word) & (RamHalfwords - 1u)];
            for (uint32_t nibble = 0; nibble < 4u; ++nibble)
            {
                const int32_t raw = static_cast<int16_t>(((packed >> (nibble * 4u)) & 0xFu) << 12u) >> shift;
                const int32_t predicted = (v.hist1 * kAdpcmFilters[filter][0] + v.hist2 * kAdpcmFilters[filter][1] + 32) >> 6;
                const int16_t sample = clamp16(raw + predicted);
                v.hist2 = v.hist1;
                v.hist1 = sample;
                v.decoded[(word - 1u) * 4u + nibble] = sample;
            }
        }
        v.decodedIndex = 0;
        v.nax = (block + 8u) & (RamHalfwords - 1u);
        v.playBlock = block;
        v.playStarted = true;
    }

    void SoundEngine::stepEnvelope(Voice &v)
    {
        uint32_t rate = 0;
        bool exponential = false;
        bool increase = false;
        switch (v.phase)
        {
        case Voice::Phase::Attack:
            rate = (v.adsr1 >> 8u) & 0x7Fu;
            exponential = (v.adsr1 & 0x8000u) != 0u;
            increase = true;
            break;
        case Voice::Phase::Decay:
            rate = ((v.adsr1 >> 4u) & 0xFu) * 4u;
            exponential = true;
            break;
        case Voice::Phase::Sustain:
            rate = (v.adsr2 >> 6u) & 0x7Fu;
            exponential = (v.adsr2 & 0x8000u) != 0u;
            increase = (v.adsr2 & 0x4000u) == 0u;
            break;
        case Voice::Phase::Release:
            rate = (v.adsr2 & 0x1Fu) * 4u;
            exponential = (v.adsr2 & 0x20u) != 0u;
            break;
        case Voice::Phase::Off:
            return;
        }

        // psx-spx "SPU ADSR": cycles = 1 << max(0, shift - 11); step = value << max(0, 11 - shift)
        const int32_t shiftValue = static_cast<int32_t>(rate >> 2u);
        const int32_t stepValue = static_cast<int32_t>(rate & 3u);
        int32_t step = increase ? 7 - stepValue : -8 + stepValue;
        uint32_t cycles = 1u << static_cast<uint32_t>(std::max(0, shiftValue - 11));
        step <<= std::max(0, 11 - shiftValue);
        if (exponential && increase && v.envelope > 0x6000)
            cycles *= 4u;
        if (exponential && !increase)
            step = step * v.envelope / 0x8000;

        if (++v.envelopeCounter >= cycles)
        {
            v.envelopeCounter = 0;
            v.envelope = std::clamp(v.envelope + step, 0, 0x7FFF);
        }

        switch (v.phase)
        {
        case Voice::Phase::Attack:
            if (v.envelope >= 0x7FFF)
            {
                v.phase = Voice::Phase::Decay;
                v.envelopeCounter = 0;
            }
            break;
        case Voice::Phase::Decay:
            if (v.envelope <= static_cast<int32_t>(((v.adsr1 & 0xFu) + 1u) * 0x800u))
            {
                v.phase = Voice::Phase::Sustain;
                v.envelopeCounter = 0;
            }
            break;
        case Voice::Phase::Release:
            if (v.envelope <= 0)
            {
                v.envelope = 0;
                v.phase = Voice::Phase::Off;
                v.active = false;
            }
            break;
        default:
            break;
        }
    }

    int32_t SoundEngine::stepVoice(Core &c, uint32_t index)
    {
        Voice &v = c.voices[index];
        if (!v.active)
            return 0;
        // pitch 4.12 (0x1000 = 48 kHz), linear interpolation between the last two samples (the hardware uses a
        // 4-point gaussian)
        v.pitchCounter += std::min<uint32_t>(v.pitch, 0x3FFFu);
        while (v.pitchCounter >= 0x1000u && v.active)
        {
            v.pitchCounter -= 0x1000u;
            if (v.decodedIndex >= 28u)
                decodeBlock(c, index);
            if (!v.active)
                break;
            v.prev[1] = v.prev[0];
            v.prev[0] = v.decoded[v.decodedIndex++];
        }
        if (!v.active)
            return 0;
        const int32_t fraction = static_cast<int32_t>(v.pitchCounter & 0xFFFu);
        const int32_t sample = v.prev[1] + (((v.prev[0] - v.prev[1]) * fraction) >> 12);
        stepEnvelope(v);
        return clamp16((sample * v.envelope) >> 15);
    }

    void SoundEngine::step()
    {
        int32_t coreOut[2][2] = {};
        for (uint32_t core = 0; core < 2u; ++core)
        {
            Core &c = m_cores[core];
            int32_t left = 0, right = 0;
            for (uint32_t index = 0; index < VoicesPerCore; ++index)
            {
                const int32_t sample = stepVoice(c, index);
                if (sample == 0)
                    continue;
                if ((c.vmixL & (1u << index)) != 0u)
                    left += (sample * volumeOf(c.voices[index].volL)) >> 14;
                if ((c.vmixR & (1u << index)) != 0u)
                    right += (sample * volumeOf(c.voices[index].volR)) >> 14;
            }
            streamSample(core, left, right);
            coreOut[core][0] = left;
            coreOut[core][1] = right;
        }
        // core 0 through its master volume, added to core 1's dry output, all through core 1's master volume
        // (simplified MMIX routing)
        std::lock_guard<std::mutex> lock(m_outputMutex);
        const int32_t master[2][2] = {{volumeOf(m_cores[0].mvolL), volumeOf(m_cores[0].mvolR)},
                                      {volumeOf(m_cores[1].mvolL), volumeOf(m_cores[1].mvolR)}};
        for (uint32_t side = 0; side < 2u; ++side)
        {
            const int32_t core0 = (coreOut[0][side] * master[0][side]) >> 14;
            m_output.push_back(clamp16(((core0 + coreOut[1][side]) * master[1][side]) >> 14));
        }
        // GOW_SND_VOICEDUMP=1: while a core input stream (a movie) plays, once per second for its first 10 seconds, every
        // voice that is still sounding (active, pitch and envelope non-zero) with its volumes and sample addresses
        static const bool voiceDump = std::getenv("GOW_SND_VOICEDUMP") != nullptr;
        if (voiceDump)
        {
            static uint64_t streamSamples = 0;
            const bool streaming = m_stream[0].active || m_stream[1].active;
            streamSamples = streaming ? streamSamples + 1u : 0u;
            if (streaming && streamSamples % 48000u == 1u && streamSamples < 48000u * 10u)
            {
                std::fprintf(stderr, "[snd-voices] t=%llus mvol0=%04x/%04x mvol1=%04x/%04x\n",
                             static_cast<unsigned long long>(streamSamples / 48000u), m_cores[0].mvolL, m_cores[0].mvolR,
                             m_cores[1].mvolL, m_cores[1].mvolR);
                for (uint32_t core = 0; core < 2u; ++core)
                    for (uint32_t index = 0; index < VoicesPerCore; ++index)
                    {
                        const Voice &v = m_cores[core].voices[index];
                        if (v.active && v.pitch != 0u && v.envelope != 0)
                            std::fprintf(stderr, "[snd-voices]   core=%u voice=%u pitch=%04x vol=%04x/%04x env=%d ssa=%x lsa=%x nax=%x\n",
                                         core, index, v.pitch, v.volL, v.volR, v.envelope, v.ssa * 2u, v.lsa * 2u, v.nax * 2u);
                    }
            }
        }
        // GOW_AUDIO_RAW=<file>: the mixed samples as produced (s16le stereo 48 kHz), before the output's rate adaptation,
        // so a recording can be compared sample by sample with its source (tools/movies.py)
        static std::FILE *raw = [] { const char *path = std::getenv("GOW_AUDIO_RAW"); return path ? std::fopen(path, "wb") : nullptr; }();
        if (raw)
        {
            static std::vector<int16_t> pending;
            pending.insert(pending.end(), m_output.end() - 2, m_output.end());
            if (pending.size() >= 8192u)
            {
                std::fwrite(pending.data(), sizeof(int16_t), pending.size(), raw);
                std::fflush(raw);
                pending.clear();
            }
        }
        if (m_output.size() > kMaxBufferedFrames * 2u)
            m_output.erase(m_output.begin(), m_output.begin() + static_cast<std::ptrdiff_t>(m_output.size() / 2u & ~size_t{1}));
    }

    void SoundEngine::advanceTo(uint64_t iopCycle)
    {
        if (iopCycle <= m_lastCycle)
            return;
        const uint64_t samples = (iopCycle - m_lastCycle) / CyclesPerSample;
        for (uint64_t i = 0; i < samples; ++i)
            step();
        m_lastCycle += samples * CyclesPerSample;
    }

    size_t SoundEngine::pendingFrames() const
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        return m_output.size() / 2u;
    }

    // The device asks for maxFrames; the engine produces at the guest's IOP clock, which can run slightly faster than the
    // device (the title screen and menus run the guest clock ~3.7 % ahead of the wall clock). Above the latency target the
    // buffer is played back up to 5 % faster with linear interpolation instead of dropping blocks of samples (an audible
    // crackle); at or below the target the samples are copied as they are. Only a buffer far above the target (after a
    // stall) is cut back.
    size_t SoundEngine::drainOutput(int16_t *stereo, size_t maxFrames, size_t maxLatencyFrames)
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        size_t available = m_output.size() / 2u;
        size_t dropped = 0;
        double rate = 1.0;
        if (maxLatencyFrames != SIZE_MAX)
        {
            if (available > maxFrames + 4u * maxLatencyFrames)
            {
                dropped = available - maxFrames - maxLatencyFrames;
                m_output.erase(m_output.begin(), m_output.begin() + static_cast<std::ptrdiff_t>(dropped * 2u));
                available -= dropped;
                m_resamplePhase = 0.0;
            }
            const double over = (static_cast<double>(available) - static_cast<double>(maxFrames + maxLatencyFrames)) /
                                static_cast<double>(maxLatencyFrames);
            rate = 1.0 + std::clamp(over * 0.1, 0.0, 0.05);
        }
        size_t frames = 0;
        double position = m_resamplePhase;
        if (rate == 1.0 && position == 0.0)
        {
            frames = std::min(maxFrames, available);
            std::copy_n(m_output.begin(), frames * 2u, stereo);
            position = static_cast<double>(frames);
        }
        else
        {
            for (; frames < maxFrames; ++frames, position += rate)
            {
                const size_t index = static_cast<size_t>(position);
                if (index + 1u >= available)
                    break;
                const double fraction = position - static_cast<double>(index);
                for (size_t side = 0; side < 2u; ++side)
                {
                    const double a = m_output[index * 2u + side], b = m_output[(index + 1u) * 2u + side];
                    stereo[frames * 2u + side] = static_cast<int16_t>(std::lround(a + (b - a) * fraction));
                }
            }
        }
        const size_t consumed = std::min(available, static_cast<size_t>(position));
        m_resamplePhase = position - static_cast<double>(consumed);
        m_output.erase(m_output.begin(), m_output.begin() + static_cast<std::ptrdiff_t>(consumed * 2u));
        // GOW_AUDIO_STATS=1: every ~5 s, frames requested by the device, frames missing (underrun -> silence), frames
        // dropped after a stall, the highest playback rate and the buffered level
        static const bool stats = std::getenv("GOW_AUDIO_STATS") != nullptr;
        if (stats)
        {
            static size_t requested = 0, missing = 0, droppedSum = 0, calls = 0, minLevel = SIZE_MAX, maxLevel = 0;
            static double maxRate = 1.0;
            requested += maxFrames;
            missing += maxFrames - frames;
            droppedSum += dropped;
            maxRate = std::max(maxRate, rate);
            minLevel = std::min(minLevel, available);
            maxLevel = std::max(maxLevel, available);
            ++calls;
            if (requested >= 240000u)
            {
                std::fprintf(stderr, "[audio-stats] requested=%zu missing=%zu dropped=%zu calls=%zu rate<=%.4f level=%zu-%zu\n",
                             requested, missing, droppedSum, calls, maxRate, minLevel, maxLevel);
                requested = missing = droppedSum = calls = maxLevel = 0;
                minLevel = SIZE_MAX;
                maxRate = 1.0;
            }
        }
        return frames;
    }
}
