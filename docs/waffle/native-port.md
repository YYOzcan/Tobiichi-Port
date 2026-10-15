# Native port plan: replacing every emulated layer

Goal (user, 2026-10-10): no emulation. 1920x1080 internal, 60 fps minimum, in every zone.
End target (user, 2026-10-11): the same native port running on the Nintendo Switch: every native layer must stay portable
(AArch64, switch-mesa GL, Tegra X1 CPU ~5-8x slower than the dev PC; see README.md and switch.md).
This file is the inventory and the order of work. Status per layer is measured, not hoped.

## What is "emulated" today

| Layer | Today | Size | Native replacement | Status |
|---|---|---|---|---|
| EE CPU (MIPS R5900 game code) | **static recompilation** to x86 (6.4k functions) — already native code, no interpreter | generated | keep; optimise codegen (drop per-insn `ctx->pc`, fast memory paths) | native |
| Kernel/syscalls/threads | HLE in the runtime (Kernel/, ~23k lines) | HLE | keep | native (HLE) |
| VU0 macro mode | recompiled inline COP2 ops | inline | keep | native |
| VU1 microcode | native per-instruction-pair code generated ahead of time (tools/vu1/vu1n_gen.py), A/B verified | generated | later: lower to GPU compute | native |
| VIF1 / GIF / DMA plumbing | no DMA controller: sceDmaSend hands the game's packets (its DMA tag lists walked in place) to the VIF decoder (UNPACK into VU memory) and the GIF paths | ~1k lines | becomes a thinner loader once VU1 outputs vertices directly | native (step 2) |
| GS (graphics synthesizer) | **native render-target renderer** `GSHwBackend`, the only renderer: real render targets and textures at `PS2X_GS_HW_SCALE` (default 2), paletted textures as index + palette textures, reinterpretation passes (channel shuffles, aliased Z, CRTC merge, the shadow passes' Z-buffer inversion) done natively; triangles, sprites and lines | ~2.3k lines | done: textures and CLUTs come from a small native texture/CLUT store (`GSTextureStore`, step 5); no CPU rasteriser left | native |
| IOP (I/O CPU + IRX modules: CDVD, SIO2, 989snd) | the game's 8 IRX modules (sio2man, dbcman, sio2d, mc2_d, ds2u_d, libsd, 989nomid, smpd_iop; 52k instructions) **compiled ahead of time** to C++ (tools/iop/iopn_gen.py -> ps2xIOP/src/native); HLE kernel imports; the R3000 interpreter only runs code without a compiled form | generated | replace the hardware models below (SPU2, SIO2, CDVD) with native services | native code, in progress |
| SPU2 | native SoundEngine driven by LIBSD's exports (docs/sound.md) | in IOP | done | native (step 3) |

## Standing order (user, 2026-10-11): convert everything to native, nothing emulated
Native now: EE game code (recompiled), VU0 macro, VU1 microprograms and the IOP IRX modules (compiled ahead of time), GS
rendering (native renderer, the only one), kernel (HLE). Remaining hardware models, converted in this order, each step
verified on the 4 zones (images, fps, audio) before the next:
1. pad / memory card: SIO2 chip model + sio2man/dbcman/sio2d/ds2u_d/mc2_d -> native pad and memory-card services;
   - DONE (2026-10-11): MC2_D's card I/O routines and SIO2D's port probes are native C++ overrides (docs/memory-card.md);
     the SIO2 chip model and the DualShock model are deleted; the pad is read natively on the EE (gow_overrides.cpp).
     Mechanism for all such cuts: IRX function overrides (IopNativeOverride, tools/iop/native_overrides.txt);
2. VIF1 / GIF / DMA data path -> VU1 and GS fed directly from the game's packets;
   - DONE (2026-10-11): no DMA controller model. sceDmaSend hands the game's packets (flat or its DMA tag list, walked in
     place) straight to the VIF decoder / GIF paths (`PS2Memory::sendDma`, `sendDmaChain`) and runs the DMA-end handlers
     at once; the few CHCR stores in game code (boot VIF0 chain 0x1838D0, scratchpad copies) are served the same way.
     Packets are still the game's own formats (VIFcodes, GIF tags): decoding them is reading the game's data;
3. SPU2 register-level voice mixer -> native mixer;
   - DONE (2026-10-11): LIBSD exports are native, driving SoundEngine; SPU2 model and SPU DMA removed (docs/sound.md);
4. SIF (EE <-> IOP RPC/DMA) -> direct native calls;
   - ALREADY NATIVE (checked 2026-10-11): the EE sceSif* functions are runtime functions (Kernel/Stubs/SIF.cpp) and the
     IOP's sifman/sifcmd imports are native (ps2xIOP services/iop_rpc.cpp): an RPC is a direct call of the IOP server
     function with copies in and out, SIF DMA is a copy. No SIF register or SIF DMA channel is accessed (inventory below);
5. GS register / 4 MB memory image -> native texture and CLUT store;
   - Measured (2026-10-11, `GOW_GS_TEXSRC=1`, Olympus + Cliffs, texture decodes per run): PSMT8 textures are read
     almost only from data the game uploaded as CT32 (Olympus 27k of 27k, Cliffs 35k + 3.8k from CT16S uploads), CT24
     textures from CT32 uploads (~4.4k), CT16S from same-format uploads (exact or a part); no texture comes from a local
     copy or a render-target readback. So the store keeps upload words at their GS block addresses (the game's
     "upload as 32 bit, read as 8 bit" packing needs the address math), but needs no rasteriser, framebuffer or
     transfer-readback model;
   - DONE (2026-10-11, branch agent/texstore): `GSTextureStore` (ps2xRuntime/src/lib/gs/gpu/gs_texture_store.*,
     ~370 lines) owned by `GSHwBackend` replaces the 2.2k-line `GSCpuBackend` (CPU rasteriser, VRAM-as-framebuffer,
     transfers, readback, presentation), which is deleted with its unit tests (ps2xTest/gs_cache) and its rasteriser
     rule headers. The store receives the game's HOST->LOCAL uploads (CT24 pixels split across IMAGE packets kept, as
     before) and LOCAL->LOCAL copies (none measured; a plain copy), writing the words at their GS block addresses with
     the swizzle tables (ps2_gs_memory) because the game reads its uploads in another format; it loads the CLUT by the
     TEX0.CLD rules (CSM1/CSM2, CSA, CBP0/1 compare) and serves BuildPalette / ClutHash / a generic point-sampled
     DecodeTextureRgba (for formats without a direct layout; none seen). LOCAL->HOST is not modelled (the game never
     reads GS memory back): ConsumeLocalToHostBytes returns 0. The one-page texture-cache model (stale reads until
     TEXFLUSH) is gone: CLUT loads read the current bytes, like the renderer's own texture decode always did.
     Nothing but the game's uploads writes the memory image (2026-10-12, branch agent/clutrt): a CLUT load whose
     source memory a render target was drawn into (TEX0.CBP inside a live target, not overwritten by a later
     upload) reads its source words from that target on the GPU - the store computes the CSM1/CSM2 source pixels,
     the renderer's CLUT fetch pass reads them through the reinterpreting fetch (CPSM view of the target, same
     address math as textures read from targets) into a 256x1 target and returns the 1 KB of raw words, cached per
     target version. The former whole-target readback into the memory image (`syncTargetToVram`) is deleted.
     Measured with `GOW_GS_TEXSRC=1` (key `clut-from-rt`): no CLUT of zones 1-4 comes from a render target (the
     2.8k of the 2026-10-10 inventory were span-heuristic false positives), so the pass is a safety path for
     other scenes. The backend interface's ReadVram/WriteVram/SnapshotVram (debug panel, GS recorder) still
     reach the store;
     `GS::setRasterBackend(nullptr)` (host shutdown) now installs a no-op backend instead of the CPU rasteriser;
   - GS privileged registers DONE (2026-10-11, branch agent/gsregs): the game no longer touches them. The three
     functions that did are native overrides (gow_overrides.cpp) on a small native service, `runtime/gs/gs_display.h`
     (`ps2_gs_display::setDisplay/display/finishPending/ackFinish`, src/lib/gs/gs_display.cpp):
     - 0x183360 (per-frame display setup, called by 0x1837B8) computes a typed `GSDisplayState` (PMODE, SMODE2,
       DISPFB1/2, DISPLAY1/2, BGCOLOR in register bit layout) from the game's video globals (width/height 0x2FDD50/54,
       buffer FBP/PSM 0x331074/70, PAL flag 0x331078, interlace bit 0x32F1B4, field mode 0x334F5C) and hands it to
       `setDisplay`, which stores it in the GS state block that `GS::buildPresentationRequestUnlocked` copies into
       every `GSHwBackend::Present` request (same GS-worker barrier as the register stores had). Same output: without
       field mode both circuits are on, ALP 0x80, circuit 1 one line lower (DBY 1, DH-1) = the menu "Soften" merge;
       with field mode circuit 1 is off. `GOW_GSREGS_CHECK=1` also runs the original function and prints
       `[gsregs-check]` comparisons (defined register fields only; the original leaves stack garbage in unused bits);
     - 0x182DD8 (GS interrupt handler, INTC 0): FINISH test/ack via `finishPending/ackFinish` on the native GS status
       (set by the FINISH register in the game's GIF packets, delivered by `EeScheduler::pollGsInterrupt`); sets the
       game's "GS done" flag 0x29C7D0 = 2 and its GPU-time statistic (that part still reads timer 0);
     - 0x182E88 (installs that handler): same kernel calls (AddIntcHandler, EnableIntc, GsGetIMR/GsPutIMR unmasking
       FINISH); its CSR store is the native ack.
     The MMIO decode of 0x12000000-0x12001FFF in PS2Memory stays only as an unused fallback (`GOW_IO_HIST` shows any
     access);
EE timers (no-emulation order, after step 5):
   - Timer 2 DONE (2026-10-12, branch agent/timers): libkernel's timer system (InitTimer/StartTimerSystemTime from
     _InitSys 0x2994A0, SetTimerAlarm, the timer-2 interrupt handler cbTimerHandler 0x299D08) served only DelayThread
     (0x294A30; ~9 calls per 150 s in Olympus). DelayThread is native (`gowDelayThread`: `EeScheduler::delayCurrent`,
     a guest-time wake-up event, same return values) and InitTimer/StartTimerSystemTime return success without
     programming timer 2 or installing its handler, so no game code touches timer 2 (`GOW_IO_HIST`: 0 accesses, before
     ~60 incl. the uncached 0xB0001000/10/20 stores). An unexpected user of the timer system would show up there;
   - Timers 0/1 DONE (2026-10-12, branch agent/t01clock): the game's clock idiom (T0 count + wrap word 0x303628 +
     last value 0x2C7908, T1 the same with 0x303630/0x2C790C) is inlined in 0x179F00 (T0 twice, T1), 0x17A0E0,
     0x17A2A0, 0x17D778 (frame step, twice), 0x14A290, 0x1452F8 and the FINISH handler; most of these call guest
     functions that can block, so C++ overrides could not replace them. Instead the recompiler emits every 32-bit
     access the analysis resolves to a timer register as a call of the native EE clock
     (`PS2Memory::eeTimerLoad/eeTimerStore`, docs/runtime-changes.md): 27 call sites in 13 functions, including the
     boot code 0x138978 that sets T0 = BUSCLK/256 (mode 0x82) and T1 = H-BLNK (0x83). Neither mode raises events, so
     the count is computed when read: count at epoch + guest EE cycles since the epoch x clock / 294.912 MHz (the
     same floor as the former stepping model; timers with compare/overflow events keep that model). The FINISH
     override reads the same clock. `GOW_IO_HIST=150`, slot 1: 0 timer register accesses (before: T0 51051 reads,
     T1 7293, 2 mode writes); game speed 1.00. Regenerating the USA code changes exactly these 13 files;
6. CDVD -> extracted game files (last).
   - DONE (2026-10-12): the game reads `disc-usa/` (files extracted with their original LSNs, docs/disc.md); the
     ISO is only opened when `GOW_ISO` is set explicitly. smpd's raw sector reads are host file reads (DiscSource).

## Hardware access inventory (2026-10-12, `GOW_IO_HIST=170 GOW_IOP_IO_HIST=170`, boot + each of the 4 zones)
Measured on agent/residual (main + disc files + native clock + native DMA requests), port/residual_ver/20261012_063312:
- **EE game code: one access left per boot.** 0x13F6B8 (after sceDmaReset/sceDmaGetChan) sets VIF1's tag-transfer
  bit with `lw/sw 0($a0)` on CHCR 0x10009000: the address arrives in a register, so it goes through the generic
  path, which dispatches to the same native DMA request service. Nothing else in 170 s of any zone.
- **DMA registers: no hardware path since agent/residual.** Before: in 170 s per zone ~35k D_STAT clears and
  ~13-18k register stores per scratchpad channel (8 fromSPR at 0x1590F0/0x159C58, 9 toSPR at 0x101888/0x117D10/
  0x1188F0, QWC/MADR/SADR/CHCR each), plus the boot VIF0 chain (0x1838D0) and D_PCR. The recompiler now emits every
  32-bit access to 0x10008000-0x1000EFFF as a call of `PS2Memory::eeDmaStore/eeDmaLoad` (87 stores, 16 loads in 27
  functions, most of them libdma/libipu); a CHCR store with STR runs the copy or VIF/GIF transfer at once. No DMA
  controller state exists (registers are latched values).
- **IOP (compiled IRX code): 0 hardware accesses.** The 9 configuration stores at module start (sio2man SIO2_CTRL
  0x1F808268; libsd's SSBUS/SPU delay registers 0x1F801014/1404/140C/1414 and DPCR/DPCR2 0x1F8010F0/0x1F801570) are
  native overrides (tools/iop/native_overrides.txt: sio2man_irx 0000/0014 keep the control value, libsd_irx 1560
  bus setup is a no-op); `GOW_IOP_IO_HIST=170` logs no `iop-io` line.
- **Scratchpad memory** (not hardware): ~40 M accesses per 170 s (Desert ~37 M, slot 4 ~156 M) used to go through
  `runtime->Load/Store`; since ext agent/scratchpad the access macros read and write it directly (aligned
  accesses), see docs/performance.md "Scratchpad fast path".

Earlier state (2026-10-11, `GOW_IO_HIST=150`, boot + Olympus) and what was converted since. What the game's own code
read or wrote as hardware registers (the generated code also marks every constant-address access with `// MMIO:`;
`tools/dis.py ADDR` disassembles the USA build):
- GS privileged registers: none since agent/gsregs (step 5 above). Before: CSR read+write per FINISH interrupt
  (handler 0x182DD8, ~2 per frame) plus one write at install (0x182E88), and SMODE2/PMODE/DISPFB1/DISPLAY1/
  DISPFB2/DISPLAY2/BGCOLOR stored once per frame by 0x183360.
- EE timers: none since agent/t01clock (game code calls the native EE clock; before: T0 count ~51k reads in 150 s at
  0x179F18/54, 0x17A168, 0x17A2C8, 0x17D780/7BC and in the FINISH handler, T1 count once per frame at 0x179F94, T0/T1
  mode once at boot at 0x138984/94). T2: none since agent/timers (before: libkernel's timer system 0x2998xx-0x299Fxx,
  ~60 accesses).
- Scratchpad DMA (channels 8/9) in 0x117D10, 0x1188F0, 0x1590F0, 0x159C58, 0x101888 and D_STAT clears: served as copies;
  since agent/residual direct calls of the native DMA request service (above).
- Movies: none since agent/movies2. The player's display/DMA layer (0x26CB90..0x26EDE0) and open/close code
  (0x189BD0, 0x18A170) stored per picture SMODE2/DISPLAY1/DISPLAY2 (+ PMODE, DISPFB1/2, a CSR read) and kicked VIF1/GIF
  sends with D_STAT clears, plus D_ENABLEW and the IPU channels at open/close, through the generic path. The
  recompiler now emits them as calls of the native display service (`gsDisplayStore/gsStatusLoad`) and the native DMA
  request service (D_ENABLE never suspends; IPU starts have nothing to move: the libmpeg2 decoder reads the demuxed
  PSS). `GOW_IO_HIST` during a 148 s bonus movie: 0 accesses (docs/fmv.md, docs/runtime-changes.md).
- INTC mask (libkernel 0x2940B0/0x294140), once per DI/EI (not seen in the slot-1 runs of 2026-10-11 evening).
- Not accessed: VIF/GIF registers, SIF registers, SIF DMA, VIF1/GIF channel registers (except the boot TTE setting).

## What a no-emulation port really requires

The EE side is done the way static recompilation ports are done. The remaining emulation is *hardware*, and the only way to
remove hardware emulation is to replace the hardware interface with native code that produces the same result from the
game's own data. For each layer:

1. **VU1 -> GPU vertex processing.** The ~500 microprograms (skinning, transform, lighting, particles) are compiled
   mechanically, not hand-written: lower the compiled VU1 programs (already analysed per instruction pair by
   `generar_vu1`) to GLSL compute, one invocation per draw batch (MSCAL), input = the batch's 16 KB data memory snapshot,
   output = vertex records. This removes the VU1 bucket (the largest cost: 14-33 ms/frame) from the CPU entirely.
2. **GS -> native renderer.** Consume the vertex records and the game's render state (alpha, Z, fog, texture, CLUT,
   render-target switches) and draw with real GPU textures/targets at 1920x1080. The hard part is the game's framebuffer
   feedback passes (channel-shuffle fog, bloom, depth tricks): each must be recognised and replaced by an equivalent pass.
   This is the PCSX2 "hardware renderer" problem, solved per game instead of per console.
3. **IOP -> native services.** CDVD: map the game's file requests to the extracted disc files. Pad: already native.
   989snd: replace the IOP module with a native sound engine (SMPD/SDBK formats are documented in game-internals.md).
4. **Plumbing last.** Once VU1 and GS are native, DMA/VIF/GIF become a loader that hands buffers to those two.

## Order and what unblocks what

1. VU1 interpreter fallback -> 0 (coverage). *Prerequisite for everything below; in progress.*
2. VU1 -> GPU compute (frees ~60 % of the frame time; gets 60 fps in the heavy zones).
3. Native renderer at 1080p (replaces GS; the biggest piece of work).
4. Native sound + CDVD (removes the IOP interpreter; ~19 ms/frame of CPU in Olympus today).
5. EE codegen optimisation (24 ms/frame in Olympus; needs ~2x for 60 fps with margin).

## Honest scale

Steps 2-4 are each a project of weeks, not a session. Nothing here is hypothetical: every layer has a measured cost
and a defined native replacement; none can be skipped to reach "no emulation".

## GS inventory (2026-10-10, `GOW_GS_INVENTORY=1`, Olympus walk, per 5 s)
~1.5 M draws/5 s (≈ 5 k/frame, almost all triangle strips with ABE+ATEST+ZTE), 98 % sample plain uploaded textures (PSMT8/PSMT4 with CLUT);
~860 host→local uploads (8.4 M px); **zero** CPU VRAM reads/writes/snapshots, zero local→host / local→local transfers, no uploads into render
targets, no fog/DATE/dither/PABE/SCANMSK/depth-as-texture. Special cases are rare: RT used as texture (same format) ≈ 6.9 k, feedback
(FBP==TBP) ≈ 4.6 k, CLUT loaded from an RT ≈ 2.8 k of 8.9 k loads, FBMSK≠0 ≈ 18 k, RT reinterpretation (CT16/CT32 → CT24) ≈ 2.3 k (may
include false positives of the span heuristic). => A render-target renderer is feasible with: scaled RT + depth per (FBP,FBW,PSM), texture
cache decoded from a shadow VRAM, CLUT-aware palettised textures, shader alpha test + blend, FBMSK via write mask, and a conservative
downscale-readback for the rare RT-as-CLUT/reinterpret cases.
Plan (seam = new `GSRasterBackend`, old backend stays default/oracle): (a) scale-1 RT renderer vs old backend frames, (b) RT-as-texture,
(c) conservative readback, (d) raise scale to window size (non-uniform 3.75 x 2.41 per axis is fine: vertex scale only), then drop the
bicubic upscale.

## IOP: ahead-of-time compiled IRX modules (2026-10-10)
- Same idea as the EE: the game's own IOP code runs as native code, not interpreted.
- `core/iop_cpu_exec.h`: the R3000A instruction semantics (`iopExecute`), shared by the interpreter and the generated code.
  The generated code calls it with the instruction word and address as constants, so the compiler removes the decoding and the
  behaviour (load and branch delay slots, exceptions) is identical to the interpreter's.
- Capture: `PS2X_IOP_DUMP_MODULES=<dir>` writes each module's relocated code (`<name>.bin`) and `modules.txt` (name, base,
  text size, FNV-1a hash). The 8 modules load at stable addresses (sio2man 0x10000 ... smpd_iop 0x4C900).
- `tools/iop/iopn_gen.py <dump> ps2xIOP/src/native`: one function per module with a label per instruction; straight-line code
  falls through, after a delay slot it jumps to the static target / fall-through, dynamic jumps go through a switch. It returns
  to the IOP dispatcher at import stubs (`jr ra; addiu $0,$0,n`, served by the HLE kernel), on exceptions, outside the module
  and when the budget (scheduler slice, <= 256 instructions) is used. Threads, interrupts and DMA keep working at those points.
- Runtime (`iop_emulator.cpp`): a module loaded at the generated base with the same hash runs natively, before its start();
  otherwise the log says "no native code for ..." (`PS2X_IOP_NATIVE=0` disables for A/B comparison).
- Generated files are not in git (compiled from the game): regenerate after a module or loader change with
  `PS2X_IOP_DUMP_MODULES=port/iop_mods` + one run to the menu, then `python -I tools/iop/iopn_gen.py port/iop_mods
  ext/PS2Recomp-kl/ps2xIOP/src/native` and a CMake re-configure. Without them the empty registry is linked.
- Specialised C++ per instruction, 512 instructions per function (one function per module, or force-inlining the generic
  semantics, takes MSVC > 30 min and > 12 GB); full build of the 8 modules ~4 min.
- Measured (Olympus, `PS2X_IOP_NATIVE_STATS=1`): 100 % of IOP instructions native, 0 interpreted; the IRX code itself costs
  ~30-70 ms per 5 s.
- The IOP's real cost was the EE calling `runEeCycles` ~3.4 M times/s for ~10 IOP cycles each (full SPU2/timer/scheduler
  service per call): now batched (512 IOP cycles). IOP total 2.8 s -> ~0.2 s per 5 s; boot to Olympus gameplay 95 s -> 20 s.
- Next: SPU2 / SIO2 / CDVD hardware models -> native services (audio output, pad, file reads); then GS default (Cliffs 10 fps).
