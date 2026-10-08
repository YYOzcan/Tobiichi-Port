// GOW-Port: pruebas de la emulacion del SPU2 (ps2xIOP/src/emulator/core/spu2.*).
#include "MiniTest.h"
#include "../../ps2xIOP/src/emulator/core/iop_memory.h"
#include "../../ps2xIOP/src/emulator/core/spu2.h"
#include "../../ps2xIOP/tests/iop_compat_test_support.h"
#include "ps2x/iop/iop_subsystem.h"

#include <cstdint>
#include <vector>

using ps2x::iop::detail::IopMemory;
using ps2x::iop::detail::Spu2;

namespace
{
    constexpr uint32_t kBase = Spu2::RegBase;

    void setAddr(Spu2 &spu, uint32_t offset, uint32_t halfwords)
    {
        spu.write16(kBase + offset, static_cast<uint16_t>(halfwords >> 16u));
        spu.write16(kBase + offset + 2u, static_cast<uint16_t>(halfwords));
    }

    // Bloque ADPCM de 16 bytes: cabecera (desplazamiento, filtro, flags) y 28 nibbles.
    void writeBlock(Spu2 &spu, uint32_t address, uint8_t shift, uint8_t filter, uint8_t flags,
                    const std::vector<uint8_t> &nibbles)
    {
        spu.writeRam(address, static_cast<uint16_t>(shift | (filter << 4u) | (flags << 8u)));
        for (uint32_t word = 0; word < 7u; ++word)
        {
            uint16_t packed = 0;
            for (uint32_t n = 0; n < 4u; ++n)
            {
                const size_t i = word * 4u + n;
                packed |= static_cast<uint16_t>((i < nibbles.size() ? nibbles[i] : 0u) & 0xFu) << (n * 4u);
            }
            spu.writeRam(address + 1u + word, packed);
        }
    }

    // Voz 0 del nucleo 0: SSA, tono 48 kHz, ataque instantaneo y sostenido al maximo, mezclada a ambos lados.
    void setupVoice0(Spu2 &spu, uint32_t ssa)
    {
        setAddr(spu, Spu2::RegVoiceAddr + 0u, ssa); // SSA
        spu.write16(kBase + 0x4u, 0x1000u);          // PITCH
        spu.write16(kBase + 0x6u, 0x000Fu);          // ADSR1: ataque 0 (el mas rapido), sostenido 0x8000
        spu.write16(kBase + 0x8u, 0x0000u);          // ADSR2
        spu.write16(kBase + 0x0u, 0x3FFFu);          // VOLL
        spu.write16(kBase + 0x2u, 0x3FFFu);          // VOLR
        spu.write16(kBase + Spu2::RegVmixL, 0x0001u);
        spu.write16(kBase + Spu2::RegVmixR, 0x0001u);
        for (uint32_t core = 0; core < 2u; ++core)
        {
            spu.write16(kBase + Spu2::RegMvolBase + core * Spu2::RegMvolStride, 0x3FFFu);
            spu.write16(kBase + Spu2::RegMvolBase + core * Spu2::RegMvolStride + 2u, 0x3FFFu);
        }
    }
}

void register_ps2_spu2_tests()
{
    MiniTest::Case("PS2Spu2", [](TestCase &tc)
    {
        tc.Run("manual transfer writes SPU RAM at TSA and advances it", [](TestCase &t)
        {
            Spu2 spu;
            setAddr(spu, Spu2::RegTsa, 0x1234u);
            spu.write16(kBase + Spu2::RegData, 0xAAAAu);
            spu.write16(kBase + Spu2::RegData, 0xBBBBu);
            t.Equals(spu.ram(0x1234u), static_cast<uint16_t>(0xAAAAu), "first halfword at TSA");
            t.Equals(spu.ram(0x1235u), static_cast<uint16_t>(0xBBBBu), "second halfword after TSA advanced");
            t.Equals(spu.read16(kBase + Spu2::RegTsa + 2u), static_cast<uint16_t>(0x1236u), "TSA should advance by two");
        });

        tc.Run("IOP 16-bit writes reach the SPU2 data port exactly once", [](TestCase &t)
        {
            IopMemory memory;
            memory.write16(kBase + Spu2::RegTsa, 0u);
            memory.write16(kBase + Spu2::RegTsa + 2u, 0x100u);
            memory.write16(kBase + Spu2::RegData, 0x1111u);
            memory.write16(kBase + Spu2::RegData, 0x2222u);
            t.Equals(memory.spu2().ram(0x100u), static_cast<uint16_t>(0x1111u), "first data port write");
            t.Equals(memory.spu2().ram(0x101u), static_cast<uint16_t>(0x2222u), "second data port write");
            t.Equals(memory.read16(kBase + Spu2::RegTsa + 2u), static_cast<uint16_t>(0x102u),
                     "each 16-bit write should advance TSA once, not once per byte");
        });

        tc.Run("SPU DMA copies IOP RAM into SPU RAM and keeps STATX and IRQ timing", [](TestCase &t)
        {
            IopMemory memory;
            const uint8_t payload[16] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE,
                                         0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
            t.IsTrue(memory.writeRam(0x80000u, payload, sizeof(payload)), "payload should be written to IOP RAM");
            memory.write16(kBase + 0x400u + Spu2::RegTsa, 0u);       // nucleo 1
            memory.write16(kBase + 0x400u + Spu2::RegTsa + 2u, 0x2000u);
            memory.write32(0x1F801500u, 0x80000u);                    // MADR canal 7
            memory.write32(0x1F801504u, (1u << 16u) | 4u);            // BCR: 1 bloque de 4 palabras
            memory.write32(0x1F801508u, 0x01000201u);                 // CHCR: inicio, de memoria al SPU2
            t.Equals(memory.spu2().ram(0x2000u), static_cast<uint16_t>(0x3210u), "first halfword copied");
            t.Equals(memory.spu2().ram(0x2007u), static_cast<uint16_t>(0xEFCDu), "last halfword copied");
            t.Equals(memory.read16(kBase + 0x400u + Spu2::RegTsa + 2u), static_cast<uint16_t>(0x2008u),
                     "DMA should advance the core TSA");
            t.IsTrue((memory.read16(kBase + 0x400u + Spu2::RegStatx) & Spu2::StatxDmaReady) != 0u,
                     "STATX should report the transfer as done, as before");
            const auto start = memory.takeDmaStart();
            t.IsTrue(start.has_value() && start->irq == 0x28, "the core 1 DMA interrupt should still be scheduled");
        });

        tc.Run("ADPCM decodes shift and prediction filters", [](TestCase &t)
        {
            Spu2 spu;
            writeBlock(spu, 0x1000u, 12u, 0u, 0u, {1u, 2u, 3u, 0xFu});
            writeBlock(spu, 0x1008u, 0u, 1u, 0u, {1u, 0u});
            setupVoice0(spu, 0x1000u);
            spu.write16(kBase + Spu2::RegKon, 0x0001u);
            spu.step();
            const auto &v = spu.voice(0u, 0u);
            t.Equals(v.decoded[0], static_cast<int16_t>(1), "shift 12 keeps the nibble value");
            t.Equals(v.decoded[2], static_cast<int16_t>(3), "third nibble");
            t.Equals(v.decoded[3], static_cast<int16_t>(-1), "nibbles are signed");
            for (int i = 0; i < 28; ++i)
                spu.step();
            t.Equals(spu.voice(0u, 0u).decoded[0], static_cast<int16_t>(4096), "shift 0 scales the nibble by 4096");
            t.Equals(spu.voice(0u, 0u).decoded[1], static_cast<int16_t>(3840),
                     "filter 1 adds 60/64 of the previous sample");
        });

        tc.Run("loop end flags stop or repeat the voice and set ENDX", [](TestCase &t)
        {
            Spu2 spu;
            writeBlock(spu, 0x2000u, 0u, 0u, 0x01u, {1u}); // fin sin repetir
            writeBlock(spu, 0x3000u, 0u, 0u, 0x07u, {1u}); // inicio de bucle + fin + repetir
            setupVoice0(spu, 0x2000u);
            setAddr(spu, Spu2::RegVoiceAddr + 0xCu, 0x3000u); // SSA de la voz 1
            spu.write16(kBase + 0x10u + 0x4u, 0x1000u);
            spu.write16(kBase + Spu2::RegKon, 0x0003u);
            for (int i = 0; i < 40; ++i)
                spu.step();
            t.IsFalse(spu.voice(0u, 0u).active, "a block ending without repeat should silence the voice");
            t.IsTrue(spu.voice(0u, 1u).active, "a repeating block should keep the voice playing");
            t.Equals(spu.voice(0u, 1u).nax, 0x3008u, "the repeating voice should have jumped back to its loop start");
            t.Equals(spu.read16(kBase + Spu2::RegEndx), static_cast<uint16_t>(0x0003u),
                     "both voices should report the end flag in ENDX");
            spu.write16(kBase + Spu2::RegEndx, 0u);
            t.Equals(spu.read16(kBase + Spu2::RegEndx), static_cast<uint16_t>(0u), "writing ENDX should clear it");
        });

        tc.Run("ADSR attacks to full level and releases to silence after KOFF", [](TestCase &t)
        {
            Spu2 spu;
            writeBlock(spu, 0x4000u, 0u, 0u, 0x03u, {7u, 7u, 7u, 7u});
            setupVoice0(spu, 0x4000u);
            spu.write16(kBase + 0x8u, 0x0000u); // liberacion con tasa 0 (la mas rapida)
            spu.write16(kBase + Spu2::RegKon, 0x0001u);
            for (int i = 0; i < 3; ++i) // ataque 0: +0x3800 por muestra, maximo en la tercera
                spu.step();
            t.Equals(spu.read16(kBase + 0xAu), static_cast<uint16_t>(0x7FFFu), "ENVX should reach the maximum quickly");
            spu.write16(kBase + Spu2::RegKoff, 0x0001u);
            for (int i = 0; i < 16; ++i)
                spu.step();
            t.Equals(spu.read16(kBase + 0xAu), static_cast<uint16_t>(0u), "ENVX should reach zero after release");
            t.IsFalse(spu.voice(0u, 0u).active, "the voice should be off after its release");
        });

        tc.Run("an active voice is mixed into the stereo output", [](TestCase &t)
        {
            Spu2 spu;
            writeBlock(spu, 0x5000u, 0u, 0u, 0x03u, std::vector<uint8_t>(28u, 3u));
            setupVoice0(spu, 0x5000u);
            spu.write16(kBase + 0x2u, 0x4000u); // VOLR = -1.0
            spu.write16(kBase + Spu2::RegKon, 0x0001u);
            spu.advanceTo(Spu2::CyclesPerSample * 64u);
            t.Equals(spu.pendingFrames(), static_cast<size_t>(64u), "one frame per 768 IOP cycles");
            std::vector<int16_t> out(128u);
            t.Equals(spu.drainOutput(out.data(), 64u), static_cast<size_t>(64u), "all frames should drain");
            t.IsTrue(out[126] > 0, "left output should follow the positive samples");
            t.IsTrue(out[127] < 0, "right output should follow the negative voice volume");
            t.Equals(spu.pendingFrames(), static_cast<size_t>(0u), "drained frames should be removed");
        });

        tc.Run("draining with a latency limit drops the oldest frames", [](TestCase &t)
        {
            Spu2 spu;
            for (int i = 0; i < 100; ++i)
                spu.step();
            std::vector<int16_t> out(20u);
            t.Equals(spu.drainOutput(out.data(), 10u, 30u), static_cast<size_t>(10u), "ten frames should be returned");
            t.Equals(spu.pendingFrames(), static_cast<size_t>(30u),
                     "frames beyond the latency limit should be discarded, keeping the newest");
        });

        tc.Run("the IOP subsystem exposes one SPU2 frame per 768 IOP cycles", [](TestCase &t)
        {
            iop_test::Host host;
            ps2x::iop::IopSubsystem subsystem(host);
            subsystem.runEeCycles(8u * Spu2::CyclesPerSample * 100u); // 8 ciclos del EE por ciclo del IOP
            std::vector<int16_t> out(400u);
            t.Equals(subsystem.drainAudio(out.data(), 200u), static_cast<size_t>(100u),
                     "an idle IOP should still produce audio frames up to the last cycle run");
        });

        tc.Run("reaching IRQA with IRQs enabled raises the SPU2 interrupt", [](TestCase &t)
        {
            Spu2 spu;
            setAddr(spu, Spu2::RegIrqa, 0x6002u);
            spu.write16(kBase + Spu2::RegAttr, 0x8040u);
            setAddr(spu, Spu2::RegTsa, 0x6000u);
            spu.write16(kBase + Spu2::RegData, 1u);
            t.IsFalse(spu.takeInterrupt(), "no IRQ before IRQA");
            spu.write16(kBase + Spu2::RegData, 2u);
            spu.write16(kBase + Spu2::RegData, 3u);
            t.IsTrue(spu.takeInterrupt(), "writing IRQA should raise the IRQ");
            t.IsTrue((spu.read16(kBase + 0x7C2u) & 0x4u) != 0u, "SPDIF_IRQINFO should flag core 0");
            t.IsFalse(spu.takeInterrupt(), "the IRQ should be consumed once");
        });
    });
}
