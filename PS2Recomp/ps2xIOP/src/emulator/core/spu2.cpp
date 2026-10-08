#include "spu2.h"

#include <algorithm>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr int32_t kAdpcmFilters[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};
        constexpr size_t kMaxBufferedFrames = 48000u * 2u; // 2 s; si nadie consume, se descarta lo mas antiguo

        int16_t clamp16(int32_t value) noexcept
        {
            return static_cast<int16_t>(std::clamp(value, -32768, 32767));
        }

        // Volumen de voz o de nucleo. Modo fijo (bit 15 = 0): 15 bits con signo. El barrido (bit 15 = 1) aun no se
        // emula: se aplica de inmediato su destino (maximo si sube, 0 si baja).
        int32_t volumeFromRegister(uint16_t value) noexcept
        {
            if ((value & 0x8000u) == 0u)
                return static_cast<int16_t>(value << 1u) >> 1; // -0x4000..0x3FFF
            return (value & 0x2000u) != 0u ? 0 : 0x3FFF;
        }
        static size_t s_outputRead = 0;
    }

    Spu2::Spu2() : m_ram(RamHalfwords)
    {
        reset();
    }

    void Spu2::reset()
    {
        std::fill(m_ram.begin(), m_ram.end(), uint16_t{0});
        m_regs.fill(0);
        for (auto &core : m_voices)
            for (auto &voice : core)
                voice = VoiceState{};
        m_endx.fill(0);
        m_activeVoiceCount = 0;
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            m_output.clear();
            s_outputRead = 0;
        }
        m_lastCycle = 0;
        m_interrupt = false;
        reg(RegStatx) = StatxDmaReady;
        reg(0x400u + RegStatx) = StatxDmaReady;
    }

    uint32_t Spu2::reg32(uint32_t offset) const noexcept
    {
        return ((static_cast<uint32_t>(reg(offset)) & 0xFu) << 16u) | reg(offset + 2u);
    }

    void Spu2::setReg32(uint32_t offset, uint32_t value) noexcept
    {
        value &= RamHalfwords - 1u;
        reg(offset) = static_cast<uint16_t>(value >> 16u);
        reg(offset + 2u) = static_cast<uint16_t>(value);
    }

    void Spu2::writeRam(uint32_t halfwordAddress, uint16_t value) noexcept
    {
        halfwordAddress &= RamHalfwords - 1u;
        m_ram[halfwordAddress] = value;
        checkIrqAddress(halfwordAddress);
    }

    void Spu2::checkIrqAddress(uint32_t halfwordAddress) noexcept
    {
        for (uint32_t core = 0; core < 2u; ++core)
        {
            const uint32_t base = core * 0x400u;
            if ((reg(base + RegAttr) & 0x40u) != 0u && reg32(base + RegIrqa) == halfwordAddress)
            {
                m_interrupt = true;
                reg(0x7C2u) |= static_cast<uint16_t>(4u << core); // SPDIF_IRQINFO
            }
        }
    }

    bool Spu2::takeInterrupt() noexcept
    {
        const bool pending = m_interrupt;
        m_interrupt = false;
        return pending;
    }

    uint16_t Spu2::read16(uint32_t physical) const
    {
        const uint32_t offset = (physical - RegBase) & 0x7FEu;
        if (offset < 0x760u)
        {
            const uint32_t core = offset >= 0x400u ? 1u : 0u;
            const uint32_t local = offset & 0x3FFu;
            if (local < 0x180u)
            {
                const uint32_t index = local >> 4u;
                const uint32_t field = local & 0xFu;
                if (index < VoicesPerCore)
                {
                    const VoiceState &v = m_voices[core][index];
                    if (field == 0xAu)
                        return static_cast<uint16_t>(v.envelope);
                    if (field == 0xCu || field == 0xEu)
                        return static_cast<uint16_t>(volumeFromRegister(reg(voiceReg(core, index, field - 0xCu))) << 1u);
                }
            }
            else if (local >= RegVoiceAddr && local < RegVoiceAddr + VoicesPerCore * 0xCu)
            {
                const uint32_t index = (local - RegVoiceAddr) / 0xCu;
                const uint32_t field = (local - RegVoiceAddr) % 0xCu;
                if (field == 8u)
                    return static_cast<uint16_t>(m_voices[core][index].nax >> 16u);
                if (field == 10u)
                    return static_cast<uint16_t>(m_voices[core][index].nax);
            }
            else if (local == RegEndx)
                return static_cast<uint16_t>(m_endx[core]);
            else if (local == RegEndx + 2u)
                return static_cast<uint16_t>(m_endx[core] >> 16u);
        }
        return reg(offset);
    }

    void Spu2::write16(uint32_t physical, uint16_t value)
    {
        const uint32_t offset = (physical - RegBase) & 0x7FEu;
        reg(offset) = value;
        if (offset >= 0x760u)
            return;

        const uint32_t core = offset >= 0x400u ? 1u : 0u;
        const uint32_t base = core * 0x400u;
        const uint32_t local = offset & 0x3FFu;
        switch (local)
        {
        case RegKon:
            keyOn(core, value, 0u);
            return;
        case RegKon + 2u:
            keyOn(core, value & 0xFFu, 16u);
            return;
        case RegKoff:
            keyOff(core, value, 0u);
            return;
        case RegKoff + 2u:
            keyOff(core, value & 0xFFu, 16u);
            return;
        case RegData:
        {
            uint32_t tsa = reg32(base + RegTsa);
            writeRam(tsa, value);
            setReg32(base + RegTsa, tsa + 1u);
            return;
        }
        case RegEndx:
            m_endx[core] &= 0xFF0000u;
            return;
        case RegEndx + 2u:
            m_endx[core] &= 0x00FFFFu;
            return;
        default:
            break;
        }

        if (local >= RegVoiceAddr && local < RegVoiceAddr + VoicesPerCore * 0xCu)
        {
            const uint32_t index = (local - RegVoiceAddr) / 0xCu;
            const uint32_t field = (local - RegVoiceAddr) % 0xCu;
            VoiceState &v = m_voices[core][index];
            if (field == 4u || field == 6u) // LSAX escrito por el driver: manda sobre la marca del bloque
            {
                v.lsa = reg32(voiceAddrReg(core, index, 4u));
                v.lsaFromRegister = true;
            }
            else if (field == 8u || field == 10u)
            {
                v.nax = reg32(voiceAddrReg(core, index, 8u)) & ~7u;
            }
        }
    }

    bool Spu2::dmaWrite(uint32_t core, const uint8_t *source, size_t bytes)
    {
        const uint32_t base = core * 0x400u;
        if ((reg(base + RegAdmas) & (core + 1u)) != 0u)
            return false;
        uint32_t tsa = reg32(base + RegTsa);
        for (size_t i = 0; i + 1u < bytes; i += 2u)
            writeRam(tsa++, static_cast<uint16_t>(source[i] | (source[i + 1u] << 8u)));
        setReg32(base + RegTsa, tsa);
        return true;
    }

    bool Spu2::dmaRead(uint32_t core, uint8_t *destination, size_t bytes)
    {
        const uint32_t base = core * 0x400u;
        if ((reg(base + RegAdmas) & (core + 1u)) != 0u)
            return false;
        uint32_t tsa = reg32(base + RegTsa);
        for (size_t i = 0; i + 1u < bytes; i += 2u)
        {
            const uint16_t value = ram(tsa++);
            destination[i] = static_cast<uint8_t>(value);
            destination[i + 1u] = static_cast<uint8_t>(value >> 8u);
        }
        setReg32(base + RegTsa, tsa);
        return true;
    }

    void Spu2::markDmaReady(uint32_t core) noexcept
    {
        reg(core * 0x400u + RegStatx) |= StatxDmaReady;
    }

    void Spu2::keyOn(uint32_t core, uint32_t mask, uint32_t firstVoice)
    {
        for (uint32_t bit = 0; bit < 16u; ++bit)
        {
            if ((mask & (1u << bit)) == 0u || firstVoice + bit >= VoicesPerCore)
                continue;
            const uint32_t index = firstVoice + bit;
            VoiceState &v = m_voices[core][index];
            const uint32_t ssa = reg32(voiceAddrReg(core, index, 0u)) & ~7u;
            v = VoiceState{};
            v.active = true;
            v.nax = ssa;
            v.lsa = ssa;
            v.phase = VoiceState::Phase::Attack;
            m_endx[core] &= ~(1u << index);
            ++m_activeVoiceCount;
        }
    }

    void Spu2::keyOff(uint32_t core, uint32_t mask, uint32_t firstVoice)
    {
        for (uint32_t bit = 0; bit < 16u; ++bit)
        {
            if ((mask & (1u << bit)) == 0u || firstVoice + bit >= VoicesPerCore)
                continue;
            VoiceState &v = m_voices[core][firstVoice + bit];
            if (v.active)
            {
                v.phase = VoiceState::Phase::Release;
                v.envelopeCounter = 0;
            }
        }
    }

    void Spu2::decodeBlock(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];

        // Fin del bloque anterior: con la marca de fin se salta a LSA; sin "repetir", la voz se apaga.
        if ((v.blockFlags & 1u) != 0u)
        {
            m_endx[core] |= 1u << index;
            v.nax = v.lsa;
            if ((v.blockFlags & 2u) == 0u)
            {
                v.active = false;
                v.phase = VoiceState::Phase::Off;
                v.envelope = 0;
            }
        }
        v.blockFlags = 0;
        if (!v.active)
            return;

        const uint32_t block = v.nax & (RamHalfwords - 1u);
        const uint16_t header = ram(block);
        uint32_t shift = header & 0xFu;
        if (shift > 12u)
            shift = 9u;
        const uint32_t filter = std::min<uint32_t>((header >> 4u) & 7u, 4u);
        v.blockFlags = static_cast<uint8_t>(header >> 8u);
        if ((v.blockFlags & 4u) != 0u && !v.lsaFromRegister)
            v.lsa = block;

        for (uint32_t word = 1; word < 8u; ++word)
        {
            const uint16_t packed = ram(block + word);
            checkIrqAddress((block + word) & (RamHalfwords - 1u));
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
        checkIrqAddress(block);
        v.decodedIndex = 0;
        v.nax = (block + 8u) & (RamHalfwords - 1u);
    }

    void Spu2::stepEnvelope(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];
        const uint16_t adsr1 = reg(voiceReg(core, index, 6u));
        const uint16_t adsr2 = reg(voiceReg(core, index, 8u));

        uint32_t rate = 0;
        bool exponential = false;
        bool increase = false;
        switch (v.phase)
        {
        case VoiceState::Phase::Attack:
            rate = (adsr1 >> 8u) & 0x7Fu;
            exponential = (adsr1 & 0x8000u) != 0u;
            increase = true;
            break;
        case VoiceState::Phase::Decay:
            rate = ((adsr1 >> 4u) & 0xFu) * 4u;
            exponential = true;
            break;
        case VoiceState::Phase::Sustain:
            rate = (adsr2 >> 6u) & 0x7Fu;
            exponential = (adsr2 & 0x8000u) != 0u;
            increase = (adsr2 & 0x4000u) == 0u;
            break;
        case VoiceState::Phase::Release:
            rate = (adsr2 & 0x1Fu) * 4u;
            exponential = (adsr2 & 0x20u) != 0u;
            break;
        case VoiceState::Phase::Off:
            return;
        }

        // psx-spx "SPU ADSR": ciclos = 1 << max(0, shift - 11); paso = valor << max(0, 11 - shift).
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
        case VoiceState::Phase::Attack:
            if (v.envelope >= 0x7FFF)
            {
                v.phase = VoiceState::Phase::Decay;
                v.envelopeCounter = 0;
            }
            break;
        case VoiceState::Phase::Decay:
            if (v.envelope <= static_cast<int32_t>(((adsr1 & 0xFu) + 1u) * 0x800u))
            {
                v.phase = VoiceState::Phase::Sustain;
                v.envelopeCounter = 0;
            }
            break;
        case VoiceState::Phase::Release:
            if (v.envelope <= 0)
            {
                v.envelope = 0;
                v.phase = VoiceState::Phase::Off;
                v.active = false;
                if (m_activeVoiceCount > 0)
                    --m_activeVoiceCount;
            }
            break;
        default:
            break;
        }
    }

    int32_t Spu2::stepVoice(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];
        if (!v.active)
            return 0;

        // Tono 4.12 (0x1000 = 48 kHz). Interpolacion lineal entre las dos ultimas muestras (el hardware usa una
        // gaussiana de 4 puntos).
        v.pitchCounter += std::min<uint32_t>(reg(voiceReg(core, index, 4u)), 0x3FFFu);
        while (v.pitchCounter >= 0x1000u && v.active)
        {
            v.pitchCounter -= 0x1000u;
            if (v.decodedIndex >= 28u)
                decodeBlock(core, index);
            if (!v.active)
                break;
            v.prev[1] = v.prev[0];
            v.prev[0] = v.decoded[v.decodedIndex++];
        }
        if (!v.active)
            return 0;

        const int32_t fraction = static_cast<int32_t>(v.pitchCounter & 0xFFFu);
        const int32_t sample = v.prev[1] + (((v.prev[0] - v.prev[1]) * fraction) >> 12);
        stepEnvelope(core, index);
        v.lastOutput = clamp16((sample * v.envelope) >> 15);
        return v.lastOutput;
    }

    void Spu2::step()
    {
        int32_t coreOut[2][2] = {};
        if (m_activeVoiceCount > 0)
        {
            for (uint32_t core = 0; core < 2u; ++core)
            {
                const uint32_t base = core * 0x400u;
                const uint32_t mixLeft = reg(base + RegVmixL) | (static_cast<uint32_t>(reg(base + RegVmixL + 2u)) << 16u);
                const uint32_t mixRight = reg(base + RegVmixR) | (static_cast<uint32_t>(reg(base + RegVmixR + 2u)) << 16u);
                int32_t left = 0;
                int32_t right = 0;
                for (uint32_t index = 0; index < VoicesPerCore; ++index)
                {
                    if (!m_voices[core][index].active)
                        continue;
                    const int32_t sample = stepVoice(core, index);
                    if (sample == 0)
                        continue;
                    const int32_t volLeft = volumeFromRegister(reg(voiceReg(core, index, 0u)));
                    const int32_t volRight = volumeFromRegister(reg(voiceReg(core, index, 2u)));
                    if ((mixLeft & (1u << index)) != 0u)
                        left += (sample * volLeft) >> 14;
                    if ((mixRight & (1u << index)) != 0u)
                        right += (sample * volRight) >> 14;
                }
                coreOut[core][0] = left;
                coreOut[core][1] = right;
            }
        }

        const auto master = [this](uint32_t core, uint32_t side)
        {
            return volumeFromRegister(reg(RegMvolBase + core * RegMvolStride + side * 2u));
        };
        const int32_t core0L = (coreOut[0][0] * master(0u, 0u)) >> 14;
        const int32_t left = ((core0L + coreOut[1][0]) * master(1u, 0u)) >> 14;
        const int32_t core0R = (coreOut[0][1] * master(0u, 1u)) >> 14;
        const int32_t right = ((core0R + coreOut[1][1]) * master(1u, 1u)) >> 14;

        std::lock_guard<std::mutex> lock(m_outputMutex);
        m_output.push_back(clamp16(left));
        m_output.push_back(clamp16(right));
        const size_t available = m_output.size() - s_outputRead;
        if (available > kMaxBufferedFrames * 2u)
            s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
    }

    void Spu2::advanceTo(uint64_t iopCycle)
    {
        if (iopCycle <= m_lastCycle)
            return;
        const uint64_t samples = (iopCycle - m_lastCycle) / CyclesPerSample;
        if (samples == 0)
            return;

        if (m_activeVoiceCount == 0)
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            const size_t needed = static_cast<size_t>(samples * 2u);
            m_output.insert(m_output.end(), needed, int16_t{0});
            const size_t available = m_output.size() - s_outputRead;
            if (available > kMaxBufferedFrames * 2u)
                s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
        }
        else
        {
            std::vector<int16_t> batch;
            batch.reserve(static_cast<size_t>(samples * 2u));
            for (uint64_t s = 0; s < samples; ++s)
            {
                int32_t coreOut[2][2] = {};
                for (uint32_t core = 0; core < 2u; ++core)
                {
                    const uint32_t base = core * 0x400u;
                    const uint32_t mixLeft = reg(base + RegVmixL) | (static_cast<uint32_t>(reg(base + RegVmixL + 2u)) << 16u);
                    const uint32_t mixRight = reg(base + RegVmixR) | (static_cast<uint32_t>(reg(base + RegVmixR + 2u)) << 16u);
                    int32_t left = 0;
                    int32_t right = 0;
                    for (uint32_t index = 0; index < VoicesPerCore; ++index)
                    {
                        if (!m_voices[core][index].active)
                            continue;
                        const int32_t sample = stepVoice(core, index);
                        if (sample == 0)
                            continue;
                        const int32_t volLeft = volumeFromRegister(reg(voiceReg(core, index, 0u)));
                        const int32_t volRight = volumeFromRegister(reg(voiceReg(core, index, 2u)));
                        if ((mixLeft & (1u << index)) != 0u)
                            left += (sample * volLeft) >> 14;
                        if ((mixRight & (1u << index)) != 0u)
                            right += (sample * volRight) >> 14;
                    }
                    coreOut[core][0] = left;
                    coreOut[core][1] = right;
                }
                const auto master = [this](uint32_t core, uint32_t side)
                {
                    return volumeFromRegister(reg(RegMvolBase + core * RegMvolStride + side * 2u));
                };
                const int32_t core0L = (coreOut[0][0] * master(0u, 0u)) >> 14;
                const int32_t left = ((core0L + coreOut[1][0]) * master(1u, 0u)) >> 14;
                const int32_t core0R = (coreOut[0][1] * master(0u, 1u)) >> 14;
                const int32_t right = ((core0R + coreOut[1][1]) * master(1u, 1u)) >> 14;
                batch.push_back(clamp16(left));
                batch.push_back(clamp16(right));
            }
            std::lock_guard<std::mutex> lock(m_outputMutex);
            m_output.insert(m_output.end(), batch.begin(), batch.end());
            const size_t available = m_output.size() - s_outputRead;
            if (available > kMaxBufferedFrames * 2u)
                s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
        }
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            if (s_outputRead >= 8192u)
            {
                m_output.erase(m_output.begin(), m_output.begin() + static_cast<std::ptrdiff_t>(s_outputRead));
                s_outputRead = 0;
            }
        }
        m_lastCycle += samples * CyclesPerSample;
    }

    size_t Spu2::pendingFrames() const
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        return m_output.size() > s_outputRead ? (m_output.size() - s_outputRead) / 2u : 0u;
    }

    size_t Spu2::drainOutput(int16_t *stereo, size_t maxFrames, size_t maxLatencyFrames)
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        if (s_outputRead >= m_output.size())
        {
            m_output.clear();
            s_outputRead = 0;
            return 0;
        }
        size_t available = (m_output.size() - s_outputRead) / 2u;
        if (maxLatencyFrames != SIZE_MAX && available > maxFrames + maxLatencyFrames)
        {
            const size_t drop = available - maxFrames - maxLatencyFrames;
            s_outputRead += drop * 2u;
            available -= drop;
        }
        const size_t frames = std::min(maxFrames, available);
        if (frames > 0)
        {
            std::copy_n(m_output.data() + s_outputRead, frames * 2u, stereo);
            s_outputRead += frames * 2u;
        }
        if (s_outputRead >= m_output.size())
        {
            m_output.clear();
            s_outputRead = 0;
        }
        return frames;
    }
}
