# Performance (USA build on the KIexster stack)

Target (user, 2026-10-09): ≥ 60 fps, "see this game fly".

## Baseline (2026-10-09, port/perf1.log, OpenGL GS, interpreter VU1, VU1 capture on)
Loaded gameplay (state=11): 4.0 game frames/s. Game thread saturated; per game frame ≈ 250 ms:
VU1 155 ms, EE 77 ms, GS 10 ms, IOP 7 ms. 60 fps needs ≤ 16.7 ms → ~15x.

## Where the time goes / levers (verified in source unless marked)
1. **VU1 (61 %)**. The interpreter models the pipeline per instruction pair. Their per-block C++ generator
   (tools/vu1/generar_vu1.cpp, enabled with -DPS2X_VU1_MICROCODE_DIR) measured 2-3x on a bench frame.
   PCSX2's microVU (ref/pcsx2-src/pcsx2/x86/microVU_*.inl) resolves stalls at compile time: per-block static
   simulation with regCycleInfo (4-bit stall counter per VF component, microVU_IR.h:8), 4 flag instances
   (statFlag/macFlag/clipFlag[4], microVU.h:84-86), Q/P ping-pong instances, dead-flag elimination. The emitted
   code has no runtime pipeline bookkeeping. → model for a real VU1 block compiler.
2. **VU1 on its own thread (PCSX2 MTVU, ref/pcsx2-src/pcsx2/MTVU.{h,cpp})**: EE posts commands to a lock-free
   ring (MTVU_VU_EXECUTE, MTVU_VU_WRITE_MICRO/DATA/VIREGS/VFREGS, VIF unpack...); EE waits (VU_Thread::WaitVU,
   MTVU.cpp:435) only when it must read VU1 state or on VIF FLUSH*. Would overlap EE (77 ms) and VU1 (155 ms).
3. **EE recompiled code overheads** (seen in port/output-usa/sub_0017A0E0_0x17a0e0.cpp + ps2_runtime_macros.h):
   - `ctx->pc = …` stored before every instruction;
   - every JAL goes through PS2Runtime::dispatchGuestBranch (ps2_runtime.cpp:1463): atomic branch-trace ring
     (GOW-Port debug), eeCheckpointDue, hasFunction/lookupFunction, indirect call, ps2_perf::guestEntry;
   - every load/store checks isSpecialAddress + a contiguity check;
   - GPRs live as __m128i; 32-bit writes go through _mm_move_sd-style merges.
   (ps2TraceGuestWrite is an empty inline — no cost.)
Gains per lever above are estimates from the Gemini review (gemini-work/results/perf-research.md) — **unverified**.

## Log
- 2026-10-09: build with compiled VU1 (351 captured images) + /Zi (profiling) started (port/kl_build_vu1.log).
  Pitfall: in Git Bash, `-DCMAKE_CXX_FLAGS=/Zi …` gets rewritten to "C:/Program Files/Git/Zi" — set
  MSYS_NO_PATHCONV=1 MSYS2_ARG_CONV_EXCL="*" when passing MSVC flags.
- 2026-10-09 14:20: build OK (compiled VU1: 13 generated programa*.cpp from 351 images; exe 154 MB + PDB).
  New tools: tools/perf_run.sh (save-load script + GOW_PERF_DIAG + optional muestrear profile, fresh copy of the
  user's card each run), port/prof/muestrear.exe (built from their tools/perfil/muestrear.cpp).
  Pitfall: `cmd //c x.cmd` with MSYS_NO_PATHCONV=1 leaves cmd interactive (hangs) — call cmd from PowerShell.
- Scheduler facts (EeScheduler.cpp): VBlank fires when counted EE cycles reach kVBlankPeriodCycles AND the host
  deadline passed (processDueDeadlines); checkpoints charge 32 cycles per backward branch and per guest call,
  each running advanceEeTimers + advanceIopEeCycles. VU1 runs synchronously in the VIF1 MSCAL callback on the
  game thread (ps2_runtime.cpp syncCoreSubsystems); VIF1/GIF DMA chains are snapshotted at kick (chainData) and
  processed immediately, completion flagged at once (ps2_memory.cpp processPendingTransfers).
- 2026-10-09 perf2 (compiled VU1, still with traces): gameplay ~7 game frames/s (was 4.0). Per frame: EE 77 ms,
  VU1 47 ms, GS 10, IOP 7.5. Profile (port/perf2.prof): **44 % of the game thread in WriteFile** —
  ps2_log.txt grew to 2.7 GB: per-function enter/exit trace (ps2_log.h, AGRESSIVE_LOGS, flush per line).
  Cause: our out/build-kl used CMake defaults PS2X_ENABLE_AGRESSIVE_LOGS / RUNTIME_LOGS / IOP_RPC_TRACE = ON;
  their compilar.ps1 sets them OFF unless tracing. **All earlier numbers (perf1, perf2) include this cost.**
- 2026-10-09 14:40: user supplied KIexster update (god-of-war-recomp-main(1).zip = GitHub main 8441486, extracted
  to ref/other-recomp-new; git clone in ref/other-recomp-git). 8 new patches applied cleanly to ext/PS2Recomp-kl
  (uncommitted — user declined the commit): gs-upload-ring, vu1-zero-factor, vu1-direct-store, vu1-cold-scalar,
  vu1-simd-zero, vu1-xgkick-flush, gs-shared-host, vu1-generator-dir (generator now takes the capture folder).
  Repo monitored for new commits (git ls-remote every 5 min).
- KIexster update content (Gemini summary gemini-work/results/kl-update-perf.md; env var + FPS figures verified):
  VU1 patches measured on their VIF1/VU1 replay bench (compiled VU1, ms/frame): zero-factor 103→99,
  direct-store 100→93, cold-scalar 93→91, simd-zero 90→83, xgkick-flush 82→78 (all automatic, no switch).
  gs-upload-ring = robustness only. gs-shared-host = opt-in `PS2X_GS_DIRECT_PRESENT=1` (WGL shared texture,
  no readback; log says "[gs-present] host mode: shared texture"), +0.9 % = noise. generator-dir = generator
  takes the capture folder (they now have 2302 micromemories incl. the final battle).
  Their latest loaded-gameplay figure (RENDIMIENTO_PRESENTACION.md): **6.85-6.91 game fps** on Ryzen 7 5800XT +
  RX 5700 XT, OpenGL, compiled VU1 (501 images), traces OFF. Their next bottleneck: GPU raster of FBP 0 flags
  0x4b (textured+blended+bilinear) ≈ 50-56 ms per frame in the fragment-shader-interlock path.
- **2026-10-09 perf3 (traces OFF + 8 new patches + compiled VU1 351 images): gameplay 13.6-14.6 game fps**
  (was ~7 with traces; KIexster's own figure 6.9 on a slower PC). Per frame ≈ 71 ms: VU1 36, GS 15, EE 13
  (was 77 — the trace was most of it), IOP 7. Profile port/perf3.prof (game thread): VU1 *interpreter*
  functions dominate the VU share (commitReadyPipelines, decodeInstructionPair, commitReadyFlags) → most
  Olympus microprograms are not in our 351 captures; 12.6 % GSThreadedBackend::Drain (waiting for the GS
  thread); ~10 % is GOW_PERF_DIAG itself (QueryPerformanceCounter, ps2_perf::switchTo).
  Next: capture VU1 micro-memories in gameplay with this build, merge, rebuild.
- 2026-10-09 VU1 capture round 2: 841 micro-memories (port/vu1_micro, +490 from 7 min of Olympus gameplay).
  perf4: 14.2-14.6 fps — no change. The profile's top-40 interpreter functions sum to only 6.6 % of the thread;
  the VU bucket (~48 %) is mostly compiled blocks spread over thousands of functions → compiled VU1 is simply
  expensive (consistent with KIexster's 78 ms/frame replay bench). GOW_VU1C_DIAG prints only from a static
  destructor, which this runtime's exit path skips (no output even with WM_CLOSE).
- **GS worker thread (PS2X_GS_WORKER=1, implemented 2026-10-09, building)** — PCSX2-MTVU-like:
  PS2Memory::processPendingTransfers copies GIF/VIF1 bytes at the kick (chains already were) into a job; a worker
  thread runs VIF1 → VU1 → PATH1/2/3 → GS frontend in order. DMA completion (CHCR.STR, D_STAT, handlers) stays
  at the kick on the EE thread, as before. Every EE entry into worker-owned state syncs first:
  MMIO read*/write*/read/writeIORegister for GS privileged regs, 0x10003000-0x10003FFF, VIF1/GIF FIFOs,
  VU1 memory; submitGifPacket / processVIF1Data / native GIF chains / flushMaskedPath3Packets when called off the
  worker; GS stubs (Support.h applyGsRegPairs, GS.cpp clear/store-image). VU1 MSCAL/MSCNT on the worker use the
  FBRST captured at the kick and do not write VPU_STAT (game has no CFC2/CTC2 — verified by grepping the
  recompiled code). Worker stopped before GS teardown. Shared-state map: gemini-work/results/vif1-shared-state.md
  (spot-checked).
- 2026-10-09 worker1 (PS2X_GS_WORKER=1): boots, loads the save, gameplay renders correctly
  (port/worker1/gow_pad_test_13.png identical scene to non-worker runs). 15.0-15.6 fps vs 14.2-14.6 without.
  ee_ms rose to ~4.4 s/5 s = the EE thread mostly waits in the worker sync → some sync point fires very often.
  Added PS2X_GS_WORKER_DIAG=1 (per-site sync/wait report every 5 s; sync helpers moved to the .cpp so future
  changes there avoid a PCH rebuild). Gemini review of the worker timed out (20 min, no output) — task too broad.
- worker2 (PS2X_GS_WORKER_DIAG): almost all waits at "mmio 0x70003F30" = **scratchpad** — needsGsWorkerSync
  masked 0x70003F30 to 0x10003F30 (VIF register range). Fixed (scratchpad excluded).
- worker3/4: no false waits any more (CSR 0x12001000 syncs wait ~0.2 ms/5 s), but 12.6-13.4 fps (< 14.5 serial).
  Profile: EE thread idle-spinning (34 % QueryPerformanceCounter + timers/IOP), worker 47 % waiting. Cause: the
  game waits for each DMA chain via the GS FINISH interrupt (vid::WaitForDMAComplete 0x183878 polls *0x29C7D0,
  set to 2 by the GS IRQ handler 0x182DD8 — KIexster ESTADO.md §7); EeScheduler::waitForEvent sleeps until the
  next timer/VBlank deadline and nothing woke it when the worker set FINISH. Fix (building): PS2Memory
  setGsWorkerWake → worker posts EeEvent ExternalWake (type 0xFFFFFFFF, matches no waiter) after a job that left
  CSR SIGNAL/FINISH set, so pollGsInterrupt runs at once.
- **2026-10-09 worker5 (worker + wake fix): 20.0 game fps** (was 14.5 serial), picture correct
  (port/worker5/gow_pad_test_13.png). Locked at 60/3: frames snap to VBlanks.
- Timeline (PS2X_GS_WORKER_TRACE=<s>, tools/gsw_trace.py): each frame the game kicks ONE ~1.95 MB DMA chain
  (0x13F730) right after vid::Flip; the worker needs **46.6 ms** for it (VU1 + GS frontend); the EE reaches
  vid::WaitForDMAComplete ~48 ms later and waits ~1.4 ms. Critical path = that one worker job.
  With GOW_GS_FINISH_ASINCRONO=1 the job drops to 42.7 ms (still 20 fps). 30 fps needs the job < ~33 ms.
  Next options: split GS frontend onto its own thread (pipeline VU1 → GS, ~11 ms), faster VU1 (microVU-style
  block compiler; VU1 ≈ 34 ms/frame).
- Stopped here by the user (2026-10-09). All runtime changes uncommitted in ext/PS2Recomp-kl.
- 2026-10-09 first real play session by the user (PS4 controller, port/play3.log, ~5 min): no errors or crashes.
  After the first 2 min (menus/loading): avg 24.5 game fps, min 15.6, max 52.1 per 5 s window. Title menu 30.
  The controller disconnected once near the end (Bluetooth); input fell back to keyboard as designed.

## EE checkpoint cost and the meaning of ee_ms (2026-10-11, ext branch agent/ee-speed 62dee0e, e96ee58)
- Profile (port/agent_ee/base2, muestrear, Olympus): the EE thread was ~55 % busy, and **~40 % of that was
  QueryPerformanceCounter**: `PS2Runtime::advanceIopEeCycles` opened a `ps2_perf::Scope` (two clock reads with
  GOW_PERF_DIAG=1) at *every* EE checkpoint (each backward branch and guest call, millions/s). iop_ms 1.3 s/5 s was
  mostly that scope. Fix: `IopSubsystem::accrueEeCycles` / `runPendingEeCycles`; the scope wraps only the batched IOP
  run (same IOP behaviour). iop_ms 1.3 s -> 0.15 s.
- EE timers (`PS2Memory::advanceEeTimers`) advance in batches up to the next timer interrupt
  (`cyclesUntilNextEeTimerInterrupt`); timer register reads/writes flush first, so counts/interrupts are exact
  (tick math carries its remainder; Gemini review gemini-work/results/ee-timer-batch-review.md agreed).
  Branch-trace ring: relaxed load/store instead of a locked fetch_add.
- `SET_GPR_*` write the low 64 bits with one scalar store (was 128-bit load + merge + store per GPR write).
- What the EE does in Olympus: after kicking the frame's DMA chain it **spins** in 0x17A2A0 (20000-iteration delay
  loop polling *0x29C7D0 == 1, the vid DMA-busy flag), each iteration an EE checkpoint. So the old ee_ms (~3.5 s/5 s)
  was mostly spin + the sleep until the host VBlank deadline (processDueDeadlines), not game logic.
  processDueDeadlines' sleep now counts as guest_wait: **ee_ms is EE work + spin (~1.4 s/5 s)**; thread busy ~31 %.
- Frame pacing: with cheap checkpoints the guest VBlank runs at exactly 60 Hz host-paced (GOW_VBLANK_DIAG=1:
  59.99 Hz, host lag < 2 ms) and Olympus locks at **30.0 fps** (2 VBlanks). The base build showed 31-35 fps
  (port/agent_ee/base2): unverified explanation — its slow checkpoints let guest time drift and VBlanks catch up
  faster than 60 Hz. Use the game-speed meter before reading fps above 30 as a win.
- Bottleneck now: the GS worker (VU1 + GS frontend) job, ~23-26 ms per frame (port/agent_ee/gap.py on
  PS2X_GS_WORKER_TRACE output); 60 fps needs < 16.7 ms. EE is no longer on the critical path on PC.
- Tools: port/agent_ee/prof_run.sh <bin_dir> <name> (zone slot 1 + muestrear profile + worker trace summary).

## 2026-10-11: native VU1 speed-up (ext branch agent/vu1-speed: 0055349, 994a514)
- **Cause found**: `vu1n::madd<>` (every MADD/MSUB of the generated blocks) was not inlined - its double-precision overflow
  fallback made it too big - and as a real call MSVC x64 passes its three `__m128` through memory: 12 % of all VU-thread
  samples, more than all blocks together. Fast path now `VU1N_INLINE` (MSVC `__forceinline`, GCC/Clang `always_inline`),
  fallback `maddWide` noinline. All other `vu1n::` helpers (divOp, clipVal, ...) forced inline too.
- XGKICK from native blocks walks the GIFtags in VU memory and copies the packet with at most two memcpy instead of
  `progressXgkick`'s per-qword loop (fallback to the loop for odd packets / `GOW_XGKICK` trace).
- Olympus, logs-off build, same session (port/agent_vu/base2 -> xgk1): vu_ms 2.58-2.70 s -> 1.27-1.39 s per 5 s while
  doing ~1.8x more VU work; VU cost per VU cycle 8.0 -> 2.2 ns; guest_flip_hz 31-36 -> 52-64.
- **Bit-exact proof**: `GOW_VU1N_RECORD=<file>` (`_N`, `_STRIDE`) stores VU1 run inputs + hash of the native output (state,
  data memory, GIF packets); `GOW_VU1N_REPLAY=<file>` reruns them with the current build at the first VU1 run and prints
  `[vu1n-replay] N records, M differ` (`GOW_VU1N_REPLAY_REPS=n` adds warm timing). 6000 records (menu + Olympus) from the
  original code: 0 differ after every change.
- Tried and dropped: keeping VF/VI/ACC/Q/I in C++ locals inside each generated block (bit-exact, but no measurable gain:
  MSVC already forwards the stores; draft at port/agent_vu/vu1n_gen_v2.py).
- Remaining worker-thread cost around VU1 (profile port/agent_vu/xgk1.prof): blocks ~20 %, runNative dispatch ~5 %,
  resetScheduler ~2.5 % per MSCAL, GifArbiter per-packet vector alloc/copy ~3-5 % (a Path1 direct path needs a change in
  ps2_gif_arbiter.h = full rebuild), VIF1 unpack ~13 %.
- Build note: a fresh configure defaults PS2X_ENABLE_RUNTIME_LOGS / AGRESSIVE_LOGS / IOP_RPC_TRACE / DEBUG_UI to ON, which
  writes a GB-sized ps2_log.txt (function enter/exit) and caps the game at ~10 fps; pass them OFF like build-kl.

## Game-speed meter (2026-10-11, ext branch agent/speedmeter 17488d4)
- What: `GOW_DELTA_DIAG=1` (with `GOW_PERF_FRAME_PC=0x001837B8`) sums the game's own per-frame time step (float at
  0x29C64C, seconds) at every vid::Flip entry and prints `[gow-speed] ... speed=` once per wall second: game seconds per
  wall second. 1.00 = real time; fps can be judged only together with it (fps above 30 with speed 1.00 is real; fps
  above 30 with speed > 1 means game time runs fast). Idea and the 0x29C64C address taken from KIexster's
  patches/ps2recomp-game-speed.patch, folded into `ps2_perf::guestEntry` (ps2_perf.h); zero cost when off.
- tools/zones.py sets it and reports "game speed (mean, min-max)" over the last 20 windows (warning outside 0.9-1.1).
- Measured, zones slots 1-4 (port/zones/20261011_232420, Release, all ok, windows after gameplay start):

  | slot | fps | speed in 60 fps windows | speed in 30 fps windows | overall |
  |---|---|---|---|---|
  | 1 Olympus | 60 (30 for ~11 s after load) | 1.031 | 0.999 | 1.027 |
  | 2 Desert | 60 | 1.024 | - | 1.024 |
  | 3 Cliffs | 30 (60 for ~20 s) | 1.026 | 0.999 | 1.004 |
  | 4 Final battle | 60 | 1.018 | - | 1.018 |
- Reading: the 60 fps is real: the game takes ~1/60 s steps (delta_min 0.0166); it is not a 30 fps game whose clock
  runs double. The 2-3 % excess at 60 fps was a runtime timing error, fixed (below).
- How the game measures a frame (0x17D778, also inlined in vid::WaitForDMAComplete 0x17A2A0): T0 (BUSCLK/256 =
  576 kHz) extended to 64 bit (wraps at 0x303628, last value 0x2C7908); ticks since its previous frame read -> 0x29C670;
  fields = ticks / 96.1 / 100 (115.2 in PAL), clamped to [1, 4], then max(fields, 60 / target fps); step = fields / 60.
  So a frame shorter than one field counts as one field and a longer one counts in full: any jitter of the read point
  only adds game time.
- Cause (2026-10-12): per-frame ticks alternated ~9000 / ~10200 in our build (`[gow-speed-hist]`: half the frames in
  bin 9, half in bin 10 at 1.06 fields), while PCSX2 reads 9572-9640 every frame (PINE, desert, speed 1.000). Trace:
  vid::WaitForDMAComplete spins on the GS-done flag 0x29C7D0 and the recompiled spin burns guest cycles ~10x faster
  than wall time (a FINISH 1 ms of wall time after a VBlank arrived 5800 ticks = 10 ms of guest time after it), so where
  the FINISH and the next frame-clock read land in guest time depended on how long the host GS worker took.
- Fix (EeScheduler::processDueDeadlines, ext agent/gamespeed): 15 no-op pacing deadlines per field on the VBlank grid
  (cycle deadline and host deadline in lockstep, like VBlank itself). The guest clock can no longer run ahead of the
  wall clock by more than 1/16 field inside a frame; real work runs at about wall rate already, so only spins are held.
  `[gow-speed-hist]` (same switch) prints the per-frame tick histogram in tenths of a field.
- Note: runs that never log `[memory card]` (stale git-ignored iopn_*/gow_overrides.cpp in a worktree) stay in the
  menu at 60 fps, speed 1.00; their numbers say nothing about gameplay.

## Presentation without readback (zero-copy, branch agent/present in ext/PS2Recomp-kl-present)
- **Before**: GSHwBackend::Present composed the CRTC circuits into presentTex, then glReadPixels into
  PresentationFrame::pixels; the host uploaded them again (UpdateTextureRec) and ran the bicubic scaler. The host
  waited for the GS worker on every latch: `upload_ms` ~0.7-1.1 s per 5 s window.
- **Now**: the GS GL context is created in GSHwBackend::Initialize (GS worker, while the host context is released)
  and shares objects with the raylib window (wglCreateContextAttribsARB with the host HGLRC, gs_gl.cpp).
  Present composes as before, forces alpha 1 on the GPU and copies presentTex into one of 8 shared slot textures
  with glCopyImageSubData (`GSGL::PublishSharedTexture`, fenced). The host draws the slot texture directly
  (`GSSharedPresent::Acquire`, gs_host_present.cpp). Present is queued (asynchronous) on the GS worker.
  On by default; `PS2X_GS_DIRECT_PRESENT=0` restores RAM frames.
- Zone captures (GOW_PAD_CAPTURAS) still get pixels: `copyLatchedHostPresentationFrame` sends a forceReadback
  request, which reads back once.
- Host scaler: the bicubic+sharpen pass only runs when the frame is magnified; a frame at least as large as its
  4:3/16:9 rectangle (e.g. `PS2X_GS_HW_SCALE=3` at 1920x1080, or a small window) gets one bilinear tap.
- Measured (Olympus slot 1, 1920x1080, scale 2, same build back to back, port/agent_present/r3_ram vs r3_shared):
  upload_ms 970-1100 → 23 ms per 5 s; game fps 36-38 in both (the game thread is the limit; the host
  thread is now idle in vsync, host_wait_ms 3.9 → 4.95 s). Captures identical (r2_ram vs r2_shared sheet.png).
- Check the window content with `GOW_HOST_SHOT=<host frame>` (writes host_shot.png = back buffer, next to the exe).
  Desktop grabs (tools/shot.ps1 PrintWindow, CopyFromScreen) of DEBUG_UI=OFF builds came back all white in
  both RAM and shared modes while host_shot.png is correct; cause **not found** (DEBUG_UI=ON builds grab fine).
- Switch: the mechanism is GL-generic (shared context + texture copy + fence sync); only context creation /
  host-context capture is WGL (gs_gl.cpp, `_WIN32` block). The non-Windows build has no GS GL context yet;
  an EGL/SDL version would capture eglGetCurrentContext in CaptureHostContext and pass it as share_context.
  glCopyImageSubData needs GL 4.3 / ARB_copy_image (or a glBlitFramebuffer fallback on GL 3.3).
- Worktree build pitfall: a fresh configure defaults to PS2X_ENABLE_AGRESSIVE_LOGS / RUNTIME_LOGS / DEBUG_UI /
  IOP_RPC_TRACE = ON and no PS2X_VU1_MICROCODE_DIR (interpreted VU1): ~3 fps and a GB-size ps2_log.txt.
  Copy those cache values from out/build-kl (logs/UI/trace OFF, VU1 dir port/vu1_micro + generator source).

## Cliffs of Madness 30 -> 60 fps: texture uploads (2026-10-12, ext branch agent/cliffs60)
- Cliffs (save slot 3) was GS-bound at ~32 fps: gs_ms 3330 per 5 s (~20 ms per frame) against 1150 in Olympus at 60 fps.
  The zone streams 4 bit (PSMT4) textures every frame. Sampling the GS worker (port/agent_ee/prof_run3.sh: zone slot 3 +
  muestrear) showed the time on the CPU, not the GPU: `GSMem::WriteP4` 25 %, `GSTextureStore::UploadAligned` ~20 %,
  `indexTextureFor` 16 % of the worker thread.
- Cause: host->local uploads were written one pixel at a time through a format switch and a non-inlined write call,
  with two integer divisions (pixel index -> x,y) per pixel; the index textures were decoded per texel through the
  generic `GSSwizzle` path.
- Fix: `GSMem::WriteRun` writes one row run of a transfer with the format resolved once and the page-table address
  math inlined (`PixelStorageTraits<psm>::Write`); `UploadAligned` splits the stream into row runs (no per-pixel
  division). `GSMem::ReadIndexRun` decodes a row of a paletted texture the same way for `indexTextureFor`. Same
  addresses as before (same page tables), so the GS memory contents and the textures are unchanged. Portable C++.
- Result: Cliffs 60 fps (gs_ms ~1640 per 5 s, GS worker busy 63 % instead of 85 %); the other zones stay at 60.


## Scratchpad fast path (2026-10-12, ext branch agent/scratchpad 96f61ab)
- The scratchpad (16 KB at 0x70000000, alias 0xF0000000) is plain memory, but `Ps2IsSpecialAddress` includes it, so
  every access in recompiled code took `runtime->Load/Store` (a call, the GOW_IO_HIST check, `syncGsWorkerFor`, a
  bounds-checked copy): ~40 M accesses per 170 s per zone, ~156 M in slot 4 (docs/native-port.md inventory).
- Now the READ*/WRITE* macros (include/ps2_runtime_macros.h) test for the scratchpad inside their special-address branch
  and access it directly (`Ps2ScratchpadFastPtr`); unaligned accesses and every other special address keep the runtime
  path (address error unchanged). RAM accesses are unchanged. No regeneration: the generated code already uses the
  macros (~150k access sites); only a full rebuild.
- Verified (port/spr/20261012_081449, baseline merged9): 4 zones ok, 60 fps everywhere, game speed 1.00-1.02, no image
  warnings; savetest ok. With `GOW_IO_HIST=60` in slot 4 the histogram window never closed: no access reached the
  runtime path after the first one for the whole run (before: ~156 M scratchpad accesses per 170 s).
- ee_ms did not drop in that run (slot 1 2088 vs 1920, slot 4 2989 vs 2683): ee_ms includes the GS-wait spin (see
  "EE checkpoint cost" above) and other forks were building at the same time, so it is not a cost measure here. The
  gain matters where the EE is the bottleneck (Switch); measure it there or with a profiler on an idle machine.

## Aegean Sea (new game) ship start: 43 fps, worker job bound (2026-10-12, ext branch agent/newgame)
- New-game test (`tools/zones.py --slots 0`): the first ship deck runs at ~43 fps while the camera looks over the rain
  and the sea (from gameplay +15 s until Kratos moves on); the rest of the fight holds 60 fps.
- Per frame there: VU1 ~6.7 ms + GS frontend ~8.2 ms (Olympus: ~4 + ~4), ~16 M primitives per 5 s. Worker trace
  (`PS2X_GS_WORKER_TRACE`, port/agent_ee/gap.py): job 17.9 ms + EE gap 4.5 ms = ~22 ms per frame.
- Not the GPU and not the GL queue: `PS2X_GS_HW_SCALE=1` and `PS2X_GS_QUEUE_CHUNKS=48` leave it at 43-45 fps.
  Sampling (muestrear) shows no thread saturated (EE 34 %, VIF/VU1/GS-frontend thread 28 %, GL thread 26 %): the
  stages run one after another. `decodeDirect` was 12 % of the GL thread; it now reads rows (`GSMem::ReadColorRun`,
  bit-identical, `GOW_GS_TEXCHECK=1` verifies) but fps did not change.
- Fix needed: run VU1 and the GS frontend as a pipeline (the GIF arbiter's path-packet callback is the boundary:
  VU1/XGKICK output queued to a GS-frontend thread), so the job costs max(VU1, GS) instead of the sum. Not done yet:
  it changes which thread owns `GS` state (EE-side syncs `syncGsWorkerIfOtherThread`, FINISH, transfers).

## VU1 / GS frontend pipeline (2026-10-12, ext branch agent/pipeline)
- With the GS worker (`PS2X_GS_WORKER=1`) the worker ran VIF1 + VU1 and, after every XGKICK, the GS frontend
  (`GS::processGIFPacket`) on the same thread, so a frame cost VU1 + GS frontend (ship start: ~6.7 + ~8.2 ms).
- Now the GIF arbiter's packet callback hands each packet (copied, in arbiter order) to a GS frontend stage thread
  (`ps2xRuntime/src/lib/gs/gs_stage.cpp`); VU1 of packet N+1 overlaps the GS frontend of packet N. The queue is bounded
  (4 MB) so the worker cannot run a frame ahead.
- Synchronisation is unchanged for everyone else: `PS2Memory::waitGsWorkerIdle` waits for the worker *and* the stage,
  so every EE access that synced with the worker (GS register stores, readbacks, display state, FINISH handshake)
  still sees all queued GS work done. The stage never waits for itself (`onStageThread`), and it wakes the EE after a
  batch when the GS raised an interrupt (FINISH/SIGNAL), as the worker did after a job.
- `PS2X_GS_PIPELINE=0` keeps the GS frontend on the worker thread (A/B and fallback). Portable C++ (std::thread).
- Measured (idle new-game run, port/newgame/b6idle_*: the ship start with the camera over the rain and sea):
  pipeline on 59.2-60.2 fps through the whole scene, `PS2X_GS_PIPELINE=0` 36-42 fps; game speed 1.00 both.
  Zones 0-4 (port/b6_zones/20261012_143318 + port/b6_zones2/20261012_145143 for slots 2 and 4, whose first runs
  were killed from outside by another test's `taskkill /IM`): 60 fps everywhere, speed 1.00, no image warnings;
  savetest ok.
