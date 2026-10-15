#pragma once

// GOW-Port: native sound engine (replaces the register-level SPU2 model). The game's sound driver (989snd) reaches the
// sound hardware only through the LIBSD API; those calls are native (src/native/iop_native_overrides.cpp) and land here
// as typed voice / core state. No SPU2 registers and no IOP DMA controller exist: transfers are copies into the sample
// RAM. Mixing: 2 cores x 24 ADPCM voices (pitch with linear interpolation, ADSR envelope), dry mix L/R per voice,
// master volume, plus the core input stream (LIBSD block transfer, "ADMA") at the stream volume. 48 kHz stereo output.
// DSP algorithms as in PCSX2 (pcsx2/SPU2) and psx-spx (ADPCM / ADSR are the same as on the PS1). Reverb: parameters
// stored, not mixed yet. docs/native-port.md (step 3), docs/sound.md.

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

namespace ps2x::iop::detail
{
    class SoundEngine
    {
    public:
        static constexpr uint32_t RamHalfwords = 1u << 20u; // 2 MB sample RAM
        static constexpr uint32_t VoicesPerCore = 24u;
        static constexpr uint32_t CyclesPerSample = 768u;  // IOP 36.864 MHz / 48 kHz

        SoundEngine();
        void reset();

        // ---- LIBSD API (entry codes as libsd: (id << 8) | (voice << 1) | core; master volumes have bit 7 set) ----
        void setParam(uint32_t entry, uint16_t value);   // sceSdSetParam
        [[nodiscard]] uint16_t getParam(uint32_t entry) const; // sceSdGetParam
        void setSwitch(uint32_t entry, uint32_t mask);   // sceSdSetSwitch (KON, KOFF, VMIX*, NON, PMON)
        [[nodiscard]] uint32_t getSwitch(uint32_t entry) const; // sceSdGetSwitch
        void setAddr(uint32_t entry, uint32_t byteAddress); // sceSdSetAddr (SSA, LSA, NAX, ESA, EEA, ...)
        [[nodiscard]] uint32_t getAddr(uint32_t entry) const; // sceSdGetAddr (byte address)
        void setCoreAttr(uint32_t entry, uint32_t value);  // sceSdSetCoreAttr
        [[nodiscard]] uint32_t getCoreAttr(uint32_t entry) const;
        void initCore(uint32_t core);                      // sceSdInit state of one core

        // sample RAM transfers (sceSdVoiceTrans): byte address in sample RAM
        void writeSampleRam(uint32_t byteAddress, const uint8_t *source, size_t bytes);
        void readSampleRam(uint32_t byteAddress, uint8_t *destination, size_t bytes) const;
        void clearSampleRam(uint32_t byteAddress, size_t bytes);

        // core input stream (sceSdBlockTrans with SD_BLOCK_LOOP): the engine reads 512-byte L / R blocks from the ring in
        // IOP RAM at 48 kHz; onHalf is called (from advanceTo) each time a half of the ring has been consumed.
        struct StreamRing
        {
            const uint8_t *base = nullptr; // IOP RAM of the ring
            uint32_t size = 0;             // bytes
            uint32_t position = 0;         // next byte to read
            bool active = false;
            bool loop = false;             // false: the buffer plays once
        };
        void startStream(uint32_t core, const uint8_t *ring, uint32_t size, bool loop);
        void stopStream(uint32_t core);
        [[nodiscard]] uint32_t streamPosition(uint32_t core) const { return m_stream[core & 1u].position; }
        [[nodiscard]] bool takeStreamHalf(uint32_t core) noexcept; // a half was consumed since the last call

        // time: one stereo sample every CyclesPerSample IOP cycles
        void advanceTo(uint64_t iopCycle);

        // stereo samples produced so far (producer: IOP thread, consumer: host audio thread)
        [[nodiscard]] size_t pendingFrames() const;
        size_t drainOutput(int16_t *stereo, size_t maxFrames, size_t maxLatencyFrames = SIZE_MAX);

    private:
        struct Voice
        {
            // parameters (as the driver sets them)
            uint16_t volL = 0, volR = 0, pitch = 0, adsr1 = 0, adsr2 = 0;
            uint32_t ssa = 0;                // start, halfwords
            // playback state
            bool active = false;
            uint32_t nax = 0;                // next ADPCM block to decode (halfwords)
            uint32_t playBlock = 0;          // block being played (NAX reads from it, like PCSX2's NextA)
            bool playStarted = false;
            uint32_t lsa = 0;                // loop start
            bool lsaFromDriver = false;      // the driver set LSA: block loop-start flags do not override it
            uint32_t pitchCounter = 0;       // 4.12
            int16_t decoded[28]{};
            uint32_t decodedIndex = 28;      // 28 = decode the next block first
            int32_t hist1 = 0, hist2 = 0;
            int16_t prev[2]{};
            uint8_t blockFlags = 0;
            enum class Phase : uint8_t { Off, Attack, Decay, Sustain, Release } phase = Phase::Off;
            int32_t envelope = 0;
            uint32_t envelopeCounter = 0;
        };
        struct Core
        {
            std::array<Voice, VoicesPerCore> voices{};
            uint32_t vmixL = 0, vmixR = 0, vmixEL = 0, vmixER = 0, non = 0, pmon = 0, endx = 0;
            uint16_t mmix = 0, attr = 0;
            uint16_t mvolL = 0, mvolR = 0, evolL = 0, evolR = 0, avolL = 0, avolR = 0, bvolL = 0, bvolR = 0;
            uint32_t esa = 0, eea = 0, irqa = 0, tsa = 0; // halfwords
        };

        void keyOn(Core &core, uint32_t mask);
        void keyOff(Core &core, uint32_t mask);
        void decodeBlock(Core &core, uint32_t index);
        int32_t stepVoice(Core &core, uint32_t index);
        static void stepEnvelope(Voice &v);
        static uint32_t naxOf(const Voice &v) noexcept;
        void streamSample(uint32_t core, int32_t &left, int32_t &right);
        void step();

        std::vector<uint16_t> m_ram;
        std::array<Core, 2> m_cores{};
        std::array<StreamRing, 2> m_stream{};
        std::array<bool, 2> m_streamHalf{};
        std::vector<int16_t> m_output;
        mutable std::mutex m_outputMutex;
        double m_resamplePhase = 0.0; // drainOutput: fractional read position when playing back faster
        uint64_t m_lastCycle = 0;
    };
}
