// GOW-Port: IRX functions replaced by native C++ (see iop_native.h). Each entry must also be listed in
// tools/iop/native_overrides.txt so the generated code hands control to the dispatcher at that address.
#include "native/iop_native.h"

#include "emulator/core/iop_cpu.h"
#include "emulator/core/iop_memory.h"
#include "emulator/core/memory_card.h"
#include "emulator/core/sound_engine.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

// Audio device position (ps2xRuntime ps2_runtime.cpp), printed at the stream start for the movie A/V check.
extern std::atomic<uint64_t> g_gowAudioFramesProduced;

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr uint32_t kA0 = 4, kV0 = 2, kSp = 29, kGp = 28;

        uint32_t arg(IopNativeCall &c, uint32_t index) // arguments from index 4 on come from the caller's stack
        {
            return index < 4u ? c.cpu.gpr[kA0 + index] : c.memory.load32(c.cpu.gpr[kSp] + 16u + (index - 4u) * 4u);
        }
        void ret(IopNativeCall &c, uint32_t value) { c.cpu.gpr[kV0] = value; }

        // ---- MC2_D.IRX: the memory-card driver's card I/O (docs/memory-card.md) ----------------------------------
        // MC2_D keeps its command dispatch, buffers and replies to the EE (the card file system runs on the EE in
        // libmc2); only the routines that talked to the card through SIO2 transfers are native: they read and write
        // the card image directly. Ports 2/3 are memory-card slots 1/2.

        MemoryCard *cardFor(IopNativeCall &c, uint32_t port)
        {
            return c.memory.cards().card(port & 1u); // ports 2/3 -> slots 0/1
        }

        // 0x0c8c: int read_page(port, slot, page, size, void *iopDst /* stack +0x10 */); 1 = ok, 0 = error
        void mcReadPage(IopNativeCall &c)
        {
            MemoryCard *card = cardFor(c, arg(c, 0));
            const uint32_t page = arg(c, 2), size = arg(c, 3), destination = arg(c, 4);
            if (!card || size == 0u || size > MemoryCard::RawPageSize * MemoryCard::PagesPerBlock)
                return ret(c, 0u);
            std::vector<uint8_t> data(size);
            card->setAddress(page);
            card->read(data.data(), size);
            ret(c, c.memory.writeRam(destination, data.data(), size) ? 1u : 0u);
        }

        // 0x0fdc: int write_page(port, slot, page, const void *iopSrc, size /* stack +0x10 */)
        void mcWritePage(IopNativeCall &c)
        {
            MemoryCard *card = cardFor(c, arg(c, 0));
            const uint32_t page = arg(c, 2), source = arg(c, 3), size = arg(c, 4);
            std::vector<uint8_t> data(size);
            if (!card || size == 0u || size > MemoryCard::RawPageSize * MemoryCard::PagesPerBlock ||
                !c.memory.readRam(source, data.data(), size))
                return ret(c, 0u);
            card->setAddress(page);
            card->write(data.data(), size); // NAND: bits only go from 1 to 0, the driver erases first
            ret(c, 1u);
        }

        // 0x0a98: int erase_block(port, slot, firstPageOfBlock)
        void mcEraseBlock(IopNativeCall &c)
        {
            MemoryCard *card = cardFor(c, arg(c, 0));
            if (!card)
                return ret(c, 0u);
            card->setAddress(arg(c, 2) & ~(MemoryCard::PagesPerBlock - 1u));
            card->eraseBlock();
            ret(c, 1u);
        }

        // 0x13a8: int get_specs(port, slot, u32 out[2]): page size / pages per block / page count
        void mcGetSpecs(IopNativeCall &c)
        {
            if (!cardFor(c, arg(c, 0)))
                return ret(c, 0u);
            const uint32_t specs[2] = {(MemoryCard::PagesPerBlock << 16) | MemoryCard::PageSize, MemoryCard::PageCount};
            ret(c, c.memory.writeRam(arg(c, 2), specs, sizeof(specs)) ? 1u : 0u);
        }

        // 0x0650 init_card, 0x164c probe, 0x08d8 probe_f3: (port, slot) -> 1 when a card image is present
        // (a real card echoes the 0x55 terminator the driver sets, which gives 1)
        void mcPresent(IopNativeCall &c)
        {
            ret(c, cardFor(c, arg(c, 0)) ? 1u : 0u);
        }

        // ---- SIO2MAN.IRX: SIO2_CTRL accessors -------------------------------------------------------------------------
        // No SIO2 chip exists (pad and cards are native services), so the control register is a latched value.
        uint32_t g_sio2Ctrl = 0u;

        // 0x0000: void sio2_ctrl_set(u32) (module start writes 0x3bc)
        void sio2CtrlSet(IopNativeCall &c)
        {
            g_sio2Ctrl = arg(c, 0);
        }

        // 0x0014: u32 sio2_ctrl_get()
        void sio2CtrlGet(IopNativeCall &c)
        {
            ret(c, g_sio2Ctrl);
        }

        // ---- SIO2D.IRX: device detection (docs/memory-card.md) -----------------------------------------------------
        // The game reads the controller on the EE natively (scePad2* in gow_overrides.cpp) and opens no pad socket on
        // the IOP, so no pad is reported: DS2U_D never connects and never polls. Memory cards are reported from the
        // card images, which runs MC2_D's own connect path. No SIO2 transfer exists.

        // 0x0978: int probe_pad(port, slot, u8 *reply) -> > 0 = connected
        void sio2dProbePad(IopNativeCall &c)
        {
            ret(c, 0u);
        }

        // 0x0a1c: int probe_card(port, slot) -> non-zero = memory card present (ports 2/3)
        void sio2dProbeCard(IopNativeCall &c)
        {
            const uint32_t port = arg(c, 0);
            ret(c, (port == 2u || port == 3u) && arg(c, 1) == 0u && cardFor(c, port) ? 1u : 0u);
        }

        // ---- LIBSD.IRX: the sound library (docs/sound.md) ----------------------------------------------------------
        // The game's sound driver (989snd) reaches the sound hardware only through these calls; they drive the native
        // sound engine directly (no SPU2 registers, no IOP DMA). Transfers are copies that complete at once; the
        // driver's completion handler is still called after the call returns, as the DMA interrupt did.

        struct LibsdState
        {
            std::array<uint32_t, 2> handler{}, handlerGp{}, handlerArg{}; // sceSdSetTransIntrHandler per channel
            std::array<bool, 2> blockActive{};
            std::array<uint32_t, 2> blockBuffer{}, blockSize{}; // sceSdBlockTrans's IOP ring per channel
        };
        LibsdState g_libsd;

        constexpr uint64_t kTransferCompletionCycles = 512u; // the completion handler runs shortly after the call

        // 0x1560: SPU2 bus setup, called by the module start: SSBUS delay/address registers (0x1F801014/1404/140C/
        // 1414) and the SPU2 DMA enable bits in DPCR/DPCR2. No bus, DMA controller or SPU2 exists behind them.
        void sdBusSetup(IopNativeCall &)
        {
        }

        // #4 sceSdInit(flag): the state LIBSD's own init leaves the sound unit in (LIBSD.IRX 0x456c)
        void sdInit(IopNativeCall &c)
        {
            SoundEngine &sound = c.services.sound();
            g_libsd = {};
            for (uint32_t core = 0; core < 2u; ++core)
            {
                sound.initCore(core);
                sound.setSwitch((0x16u << 8) | core, 0xFFFFFFu); // KOFF all voices
                for (uint32_t id : {0x18u, 0x19u, 0x1Au, 0x1Bu})  // VMIXL, VMIXEL, VMIXR, VMIXER: all voices
                    sound.setSwitch((id << 8) | core, 0xFFFFFFu);
                sound.setParam((0x08u << 8) | core, core == 0u ? 0x0FF0u : 0x0FFCu); // MMIX
                for (uint32_t id = 0x09u; id <= 0x10u; ++id)                         // MVOL, EVOL, AVOL, BVOL
                    sound.setParam((id << 8) | 0x80u | core, (core == 1u && (id == 0x0Du || id == 0x0Eu)) ? 0x7FFFu : 0u);
                for (uint32_t voice = 0; voice < SoundEngine::VoicesPerCore; ++voice)
                {
                    const uint32_t v = (voice << 1) | core;
                    sound.setParam((0x02u << 8) | v, 0x3FFFu); // PITCH
                    sound.setAddr((0x20u << 8) | v, 0u);       // SSA
                }
            }
            const uint8_t silentLoop[16] = {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
                                            0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07};
            sound.writeSampleRam(0x5000u, silentLoop, sizeof(silentLoop)); // the default loop block
            ret(c, 0u);
        }

        // GOW_SND_DIAG=1: logs the core-input stream calls and MMIX/BVOL/MVOL writes (movie audio investigation)
        const bool g_sndDiag = std::getenv("GOW_SND_DIAG") != nullptr;

        void sdSetParam(IopNativeCall &c)
        {
            const uint32_t entry = arg(c, 0), id = (entry >> 8) & 0xFFu;
            if (g_sndDiag && (id == 0x08u || (id >= 0x09u && id <= 0x10u)))
                std::fprintf(stderr, "[snd-diag] SetParam id=%02x core=%u value=%04x\n", id, entry & 1u, arg(c, 1) & 0xFFFFu);
            c.services.sound().setParam(entry, static_cast<uint16_t>(arg(c, 1)));
        }
        void sdGetParam(IopNativeCall &c) { ret(c, c.services.sound().getParam(arg(c, 0))); }
        void sdSetSwitch(IopNativeCall &c) { c.services.sound().setSwitch(arg(c, 0), arg(c, 1)); }
        void sdGetSwitch(IopNativeCall &c) { ret(c, c.services.sound().getSwitch(arg(c, 0))); }
        void sdSetAddr(IopNativeCall &c) { c.services.sound().setAddr(arg(c, 0), arg(c, 1)); }
        void sdGetAddr(IopNativeCall &c) { ret(c, c.services.sound().getAddr(arg(c, 0))); }
        void sdSetCoreAttr(IopNativeCall &c) { c.services.sound().setCoreAttr(arg(c, 0), arg(c, 1)); }

        // #17 sceSdVoiceTrans(channel, mode, iopAddr, spuAddr, size) -> size rounded up to 64 bytes
        void sdVoiceTrans(IopNativeCall &c)
        {
            const uint32_t channel = arg(c, 0) & 1u, mode = arg(c, 1), iopAddr = arg(c, 2), spuAddr = arg(c, 3), size = arg(c, 4);
            SoundEngine &sound = c.services.sound();
            std::vector<uint8_t> data(size);
            if ((mode & 3u) == 0u) // write
            {
                (void)c.memory.readRam(iopAddr, data.data(), size);
                sound.writeSampleRam(spuAddr, data.data(), size);
            }
            else // read
            {
                sound.readSampleRam(spuAddr, data.data(), size);
                (void)c.memory.writeRam(iopAddr, data.data(), size);
            }
            // mode 0 is a DMA transfer: the driver's handler runs on completion (989snd 0x78bc releases its transfer lock
            // and signals the waiting thread); mode 8 is synchronous and has no completion interrupt
            if ((mode & 8u) == 0u && g_libsd.handler[channel] != 0u)
                c.services.callGuestLater(g_libsd.handler[channel], g_libsd.handlerGp[channel], channel,
                                          g_libsd.handlerArg[channel], kTransferCompletionCycles);
            ret(c, (size + 63u) & ~63u);
        }

        // #19 sceSdVoiceTransStatus(channel, flag): copies complete at once
        void sdVoiceTransStatus(IopNativeCall &c) { ret(c, 1u); }

        // #20 sceSdBlockTransStatus(channel, flag): like libsd, the IOP address the input stream is reading (bits 0-23)
        // and the ring half being played (bit 24); 0 when stopped. 989snd hands it to the EE (command 0x40), where the
        // movie player subtracts its ring address to get the offset it may refill up to (0x188688).
        void sdBlockTransStatus(IopNativeCall &c)
        {
            const uint32_t channel = arg(c, 0) & 1u;
            if (!g_libsd.blockActive[channel])
                return ret(c, 0u);
            const uint32_t position = c.services.sound().streamPosition(channel);
            const uint32_t side = position >= g_libsd.blockSize[channel] / 2u ? 1u : 0u;
            ret(c, (side << 24) | ((g_libsd.blockBuffer[channel] + position) & 0xFFFFFFu));
        }

        // #18 sceSdBlockTrans(channel, mode, iopBuffer, size, startAddr): the core input stream. Mode 2 stops it;
        // SD_BLOCK_LOOP (0x10) plays the IOP ring continuously (989snd polls the position and has no handler set);
        // otherwise the buffer is played once.
        void sdBlockTrans(IopNativeCall &c)
        {
            const uint32_t channel = arg(c, 0) & 1u, mode = arg(c, 1), iopBuffer = arg(c, 2), size = arg(c, 3);
            SoundEngine &sound = c.services.sound();
            if (g_sndDiag)
                std::fprintf(stderr, "[snd-diag] BlockTrans core=%u mode=%x buf=%x size=%x audio_produced=%llu\n", channel, mode, iopBuffer,
                             size, static_cast<unsigned long long>(g_gowAudioFramesProduced.load()));
            if ((mode & 3u) == 2u)
            {
                sound.stopStream(channel);
                g_libsd.blockActive[channel] = false;
                return ret(c, 0u);
            }
            const uint32_t physical = IopMemory::physicalAddress(iopBuffer);
            if (physical + size > IopMemory::RamSize)
                return ret(c, static_cast<uint32_t>(-100));
            // GOW_SND_VOICEDUMP=1 (debug): 989snd's sound handles when a stream starts (module base 0x25E00, list head
            // at +0x1EE34, next at +0x24; +0x00 bits 24-28 type, +0x16 flags, +0x17 group) - which sounds a movie's
            // group pause (989snd export #67) leaves playing
            static const bool voiceDump = std::getenv("GOW_SND_VOICEDUMP") != nullptr;
            if (voiceDump)
                for (uint32_t handle = c.memory.read32(0x25E00u + 0x1EE34u), n = 0; handle != 0u && n < 256u; handle = c.memory.read32(handle + 0x24u), ++n)
                {
                    const uint32_t word0 = c.memory.read32(handle), flagsGroup = c.memory.read32(handle + 0x14u);
                    // streams (type 4): the voices of their channels (+4 list, next +0xC8, voice +0x7C) and +0x38,
                    // as 989snd's stream pause (0x12398) silences them; voice n = core n / 24, voice n % 24
                    std::string voices;
                    if (((word0 >> 24) & 0x1Fu) == 4u)
                    {
                        for (uint32_t channel = c.memory.read32(handle + 4u), k = 0; channel != 0u && k < 8u; channel = c.memory.read32(channel + 0xC8u), ++k)
                            voices += " " + std::to_string(c.memory.read32(channel + 0x7Cu));
                        voices += " extra=" + std::to_string(static_cast<int32_t>(c.memory.read32(handle + 0x38u)));
                    }
                    std::fprintf(stderr, "[snd-handles] handle=%x type=%u group=%u flags=%02x word0=%08x%s\n", handle, (word0 >> 24) & 0x1Fu,
                                 (flagsGroup >> 24) & 0xFFu, (flagsGroup >> 16) & 0xFFu, word0, voices.c_str());
                }
            sound.startStream(channel, c.memory.ram().data() + physical, size, (mode & 0x10u) != 0u);
            g_libsd.blockActive[channel] = true;
            g_libsd.blockBuffer[channel] = iopBuffer;
            g_libsd.blockSize[channel] = size;
            ret(c, 0u);
        }

        // #26 sceSdSetTransIntrHandler(channel, handler, arg)
        void sdSetTransIntrHandler(IopNativeCall &c)
        {
            const uint32_t channel = arg(c, 0) & 1u;
            g_libsd.handler[channel] = arg(c, 1);
            g_libsd.handlerArg[channel] = arg(c, 2);
            g_libsd.handlerGp[channel] = c.cpu.gpr[kGp];
            ret(c, 0u);
        }

        // #23 sceSdSetEffectAttr(core, attr *): reverb mode and depths (stored; reverb is not mixed yet)
        void sdSetEffectAttr(IopNativeCall &c)
        {
            const uint32_t core = arg(c, 0) & 1u, attr = arg(c, 1);
            SoundEngine &sound = c.services.sound();
            const uint32_t mode = c.memory.load32(attr + 4u);
            sound.setParam((0x0Bu << 8) | 0x80u | core, static_cast<uint16_t>(c.memory.load32(attr + 8u)));  // EVOLL
            sound.setParam((0x0Cu << 8) | 0x80u | core, static_cast<uint16_t>(c.memory.load32(attr + 12u))); // EVOLR
            sound.setCoreAttr(2u | core, mode != 0u ? 1u : 0u);
            ret(c, 0u);
        }

        // #31 sceSdSetEffectWorkArea(core, channel, mode): reserves the reverb work area at the end of sample RAM
        void sdSetEffectWorkArea(IopNativeCall &c)
        {
            static constexpr uint32_t kWorkHalfwords[10] = {0x02, 0x4D8, 0x3E8, 0x908, 0xDFC, 0x15BC, 0x1ED8, 0x3008, 0x3008, 0x780};
            const uint32_t core = arg(c, 0) & 1u, mode = arg(c, 2);
            SoundEngine &sound = c.services.sound();
            const uint32_t end = 0x1FFFFFu;
            const uint32_t start = end - kWorkHalfwords[mode < 10u ? mode : 0u] * 8u + 1u;
            sound.setAddr((0x1Du << 8) | core, end);   // EEA
            sound.setAddr((0x1Cu << 8) | core, start); // ESA
            sound.clearSampleRam(start, 64u);
            ret(c, 0u);
        }

        const IopNativeOverride kOverrides[] = {
            {"mc2_d_irx", 0x0c8cu, "mc2_d read_page", &mcReadPage},
            {"mc2_d_irx", 0x0fdcu, "mc2_d write_page", &mcWritePage},
            {"mc2_d_irx", 0x0a98u, "mc2_d erase_block", &mcEraseBlock},
            {"mc2_d_irx", 0x13a8u, "mc2_d get_specs", &mcGetSpecs},
            {"mc2_d_irx", 0x0650u, "mc2_d init_card", &mcPresent},
            {"mc2_d_irx", 0x164cu, "mc2_d probe", &mcPresent},
            {"mc2_d_irx", 0x08d8u, "mc2_d probe_f3", &mcPresent},
            {"sio2man_irx", 0x0000u, "sio2man ctrl_set", &sio2CtrlSet},
            {"sio2man_irx", 0x0014u, "sio2man ctrl_get", &sio2CtrlGet},
            {"sio2d_irx", 0x0978u, "sio2d probe_pad", &sio2dProbePad},
            {"sio2d_irx", 0x0a1cu, "sio2d probe_card", &sio2dProbeCard},
            {"libsd_irx", 0x1560u, "libsd bus setup", &sdBusSetup},
            {"libsd_irx", 0x456cu, "sceSdInit", &sdInit},
            {"libsd_irx", 0x3670u, "sceSdSetParam", &sdSetParam},
            {"libsd_irx", 0x36ccu, "sceSdGetParam", &sdGetParam},
            {"libsd_irx", 0x372cu, "sceSdSetSwitch", &sdSetSwitch},
            {"libsd_irx", 0x3764u, "sceSdGetSwitch", &sdGetSwitch},
            {"libsd_irx", 0x379cu, "sceSdSetAddr", &sdSetAddr},
            {"libsd_irx", 0x3800u, "sceSdGetAddr", &sdGetAddr},
            {"libsd_irx", 0x3cbcu, "sceSdSetCoreAttr", &sdSetCoreAttr},
            {"libsd_irx", 0x18a0u, "sceSdVoiceTrans", &sdVoiceTrans},
            {"libsd_irx", 0x1c30u, "sceSdBlockTrans", &sdBlockTrans},
            {"libsd_irx", 0x1af0u, "sceSdVoiceTransStatus", &sdVoiceTransStatus},
            {"libsd_irx", 0x1e4cu, "sceSdBlockTransStatus", &sdBlockTransStatus},
            {"libsd_irx", 0x0c3cu, "sceSdSetEffectAttr", &sdSetEffectAttr},
            {"libsd_irx", 0x3e3cu, "sceSdSetTransIntrHandler", &sdSetTransIntrHandler},
            {"libsd_irx", 0x0984u, "sceSdSetEffectWorkArea", &sdSetEffectWorkArea},
        };
    }

    const IopNativeOverride *iopNativeOverrides(size_t &count)
    {
        count = sizeof(kOverrides) / sizeof(kOverrides[0]);
        return kOverrides;
    }
}
