# Status (updated 2026-10-09, evening)

## How to resume (saved 2026-10-09 ~13:30)
Everything is committed **locally** (nothing pushed anywhere):
- Project folder `God Of War/` is a git repo: docs, tools, configs, overrides (commit 598a416+). Game data,
  ISOs, archives, ext/, ref/, generated code, logs and dumps are git-ignored on purpose.
- `ext/PS2Recomp` branch **gow-pal-port**, commit f18bbb3: all our runtime/IOP/recompiler work (PAL stack).
  The generated runner file register_functions.cpp is left uncommitted on purpose.
- `ext/PS2Recomp-kl` (worktree) branch **gow-usa-kl**, commit ce69fd7: c5a9d02 + KIexster's 68 patches.
Rebuild the USA build from scratch:
1. `ext/PS2Recomp-kl/out/build-kl/ps2xRecomp/Release/ps2_recomp.exe port/usa/recomp.toml` → port/output-usa
   (port/usa/ = their config/funcmap.csv + recomp.template.toml with @ELF@/@MAP@/@OUT@ filled; recreate from
   ref/other-recomp if missing).
2. Copy port/output-usa/* + ref/other-recomp/.../src/gow_overrides.cpp + src/*.h into
   ext/PS2Recomp-kl/ps2xRuntime/src/runner/ (delete old files there first).
3. `cmake --build out/build-kl --config Release --target ps2EntryRunner` in ext/PS2Recomp-kl (~30-40 min full).
4. Run (cwd = exe dir) as in the "First USA run" line below; captures gow_pad_test_N.ppm → tools/ppm2png.py.
Next steps, in order: (a) review/finish loading the user's save (port/usa3 run was interrupted);
(b) performance plan (section at the end); (c) port DiscSource (read extracted disc-usa/ instead of the ISO);
(d) audio (SPU2 output patches exist in their stack); (e) Switch build.

## Direction change (2026-10-09, afternoon)
The user supplied (1) KIexster's god-of-war-recomp project (ref/other-recomp): 68 PS2Recomp patches + config +
overrides that reach USA gameplay (Kratos, HUD, "Docks of Athens", memory card load/save, FMV, ~2 fps);
(2) all game editions (USA/Japan/Asia/Korea zips); (3) a PCSX2 memory card (ref/saves/Mcd002.ps2) holding a
USA save (BASCUS-97399GodOfWar).
**New primary target: USA (SCUS-97399) on their patch stack**, plus our own fixes where theirs lack them.
- ext/PS2Recomp-kl (built OK 2026-10-09 ~12:40, out/build-kl/ps2xRuntime/Release/ps2EntryRunner.exe): git worktree of PS2Recomp at their pinned commit c5a9d02 with all 68 patches applied in
  their order (tools/kl_patch_order.py prints it); build dir out/build-kl (VS generator, Release).
- disc-usa/: USA disc extracted (+ .disc_layout, layer1=2080544), IOP_MOD/ copies of the IRX, Mcd001.ps2 =
  copy of the user's card. port/usa/: their funcmap.csv + recomp.toml; generated code in port/output-usa.
- They independently found the same recompiler bugs (64-bit branches, SQRT.S ft, RSQRT.S, CVT.W, sin/fabs/floor
  stubs). Their checkpoint patch fixes the null virtual call that crashes our PAL build at 0x180E20.
- Still ours to port onto their stack: extracted-file disc reading (DiscSource; they read the ISO via GOW_ISO —
  used temporarily for the first test), real-SIO2 controller fixes (module start() as IOP thread,
  sceSifSetDmaIntr; they use a libpad2 HLE instead), PCSX2 VU1/EE reference tools.
- Other user-supplied files (2026-10-09 12:1x), checked: GoW II (USA, SCUS_974.81) and GoW II "Colossus Battle"
  demo (SCUS_974.82): ELFs have **no symbol tables** (only .text/.data/.rodata/.bss). Kept in ref/gow2,
  ref/gow2demo for a possible later port. ps2dis.zip (PS2 disassembler) and PS2ClientLoader (loads ELFs on real
  hardware) are not needed now (capstone tools + PCSX2 cover this). Japan/Asia/Korea zips not extracted.
- Memory card ref/saves/Mcd002.ps2: PCSX2 8 MB card, folder BASCUS-97399GodOfWar (data0-4.bin, icon.sys,
  static.ico) = USA save. The PAL ELF does not contain its folder name as a string (built at runtime).
- **First USA run on their stack (2026-10-09 ~12:45, verified by frame captures):** title screen with fire and a
  correctly rendered Kratos face, then (scripted Start/X via GOW_PAD_TEST=1) a new game starts and the opening
  shows Kratos on the cliff, fully 3D and textured (port/usa1/gow_pad_test_3.png, _11.png). Run: cwd = exe dir,
  `GOW_PAD_TEST=1 GOW_SKIP_FMV=1 GOW_ISO=<usa iso> GOW_MC0=disc-usa/Mcd001.ps2 ps2EntryRunner.exe disc-usa\SCUS_973.99`
  (captures gow_pad_test_N.ppm beside the exe; convert with tools/ppm2png.py). 200 s run, no crashes.
- PAL (our original stack in ext/PS2Recomp, docs below) is paused; it now boots to the legal screen with real
  soft-float math and stops at the null JALR (0x180E20) their checkpoint patch addresses.

## What works (PC build, verified by running)
- Recompiled game (6482 functions, 0 recompiler errors) builds with MSVC and runs.
- Boot runs entirely from the extracted files in `disc/` (no ISO argument).
- Full boot: CRT, static constructors, IOP reboot path, all 8 game IRX modules load and run on the IOP interpreter,
  anti-tamper check `sceChk01` passes, "SONY COMPUTER ENTERTAINMENT EUROPE PRESENTS" + legal screen.
- Data loading: `R_PermU` package streams from PART1.PAK through SMPD_IOP (byte-exact), sound banks (GENERAL, …)
  upload through 989snd/LIBSD, 218 sound entries register, loading completes.
- Title screen: red "GOD OF WAR" logo renders, then the message
  "PLEASE INSERT AN ANALOG CONTROLLER (DUALSHOCK 2) INTO CONTROLLER PORT 1 TO CONTINUE" (text partly garbled).

## What does not work yet
1. ~~Controller~~ — working (see below).
2. **Font/2D rendering**: some glyphs missing or garbled, some menu items drawn as grey blocks.
3. **Speed**: ~7 M EE cycles/s on the title screen (~2.4 % of a real PS2's 294.9 MHz). During loading ~60 M/s.
   GS and VU1 are CPU-emulated in the runtime. Must become playable speed, on Switch too.
4. **Audio output**: none (SPU2 DMA only signals completion; no mixing/output).
5. Memory cards: MC2_D gets no SIO2 device (reports "no device" once SIO2 lands); saving untested.
6. Switch: runtime libs build for aarch64; full game NRO never built or run on hardware.

## Controller: WORKING (2026-10-09)
Verified by running: the pad is detected and configured (DualShock 2, mode 0x79), polled with full 21-byte reads
(~3 polls/s at current speed), the data reaches the game's libpad2 socket buffer (EE 0x2FFB00, identical layout to
PCSX2: `04121601 00000001 … FFFF 8080 8080`), and pressing ✕ on the title moves to "CHOOSE DIFFICULTY".
Root causes fixed (details in iop-changes.md):
1. IRX module `start()` ran without an IOP thread → SIO2D/DS2U_D's WaitEventFlag/WaitSema during init fell through
   and left SIO2MAN's worker one transaction out of phase forever (replies read before they arrived, port-1 record
   got port-0 data, DS2U_D polled the empty port). Now `start()` runs as a transient thread.
2. sifman 32 `sceSifSetDmaIntr` was unimplemented → DBCMAN never DMA'd pad data to the EE.
3. dmacman ordinals (28/32), SIO2 RECV1 composition / port bit / DMA padding aligned with PCSX2.
4. Keyboard was ignored whenever any gamepad was attached (ps2_pad.cpp); now both are merged.
Test input without focus: `tools/key.ps1 ps2EntryRunner <delay> <holdMs> <vk> <scan> [repeat]`
(Enter = 13 28, X = 88 45).

## Active task: rendering — 2D correct, 3D geometry still wrong
Method (2026-10-09): `PS2X_GS_RECORD` writes our GIF stream as a PCSX2 .gs dump; PCSX2 replays it. PCSX2 drew the
same garbage → the GS rasterizer is not the main problem, the data fed to it is. Findings/fixes so far:
1. VU1 now runs **PCSX2's VU1 interpreter** (ps2xRuntime/src/lib/vu_pcsx2/, default; `PS2X_VU1_LEGACY=1` = old
   VU1Interpreter). Old VU1 aborted microprograms on GIF tags with FLG=3 (valid: = IMAGE) → title logo, text and
   fire background now correct.
2. GS frontend: FLG=3 treated as IMAGE; PRE/PRIM only in PACKED mode (both per PCSX2).
3. VIF1 UNPACK aligned with PCSX2 Vif_Unpack.cpp: V2 writes x,y,x,y; V3 takes w from the next element; V4-5
   expands RGBA5551 to 8-bit; MODE 3 stores data in ROW. No UNPACK is ever cut by a buffer end (logged if so).
4. Recompiler FPU: `rsqrt.s fd,fs,ft` was translated as 1/sqrt(fs) (ignored ft) → now fs/sqrt(|ft|); `div.s` by
   zero gave ±INF → now sign|FLT_MAX, overflow clamped (PCSX2 FPU.cpp). VU0 VDIV/VSQRT/VRSQRT likewise.
   (Rebuild after regenerating port/output — result not yet checked at the time of writing.)
5. GS verified with known-good input: a PCSX2 GS dump of the real title (Shift+F8 in PCSX2, `ref/pcsx2/snaps/`)
   replayed through OUR GS (`PS2X_GS_PLAY`) draws Kratos' face, text and layout correctly → our GS geometry is fine.
6. Bone/model matrices in EE RAM (e.g. 0x3F3F90, 0x450790; same addresses in PCSX2) differ from PCSX2's (scale ~2
   vs ~0.1, translation ~-1000 vs ~10). Writer found with `PS2X_EE_WATCH`: function 0x159108 (stores at
   0x159734..0x1597AC) normalises rows with `sqrt.s`. **Recompiler bug: R5900 SQRT.S takes its operand from ft,
   the translation used fs** (e.g. 0x46010044 = sqrt.s $f1,$f1 computed sqrt($f0)). Fixed in fpu_translator.cpp.
7. Matrix comparison caveat: PCSX2's snapshot was ~25 s into the title, ours at its start, so the bone matrices
   at 0x3F3F90 are not yet an apples-to-apples comparison (needs the same game frame).
8. ps2_runtime_macros.h: CVT.W.S truncation (was round-to-nearest) + FPU/VU0 clamping (full rebuild).
9. **Main 3D bug found (2026-10-09)**: gow.toml stubbed `sin`, `fabs`, `floor` with the runtime's native versions,
   which take a float in $f12 and return in $f0. This game's libm is **double-precision soft-float**: argument
   is a 64-bit double in $a0, result in $v0 (verified by disassembling 0x287FE8/0x289A00/0x289A38). Every sin()
   returned garbage → wrong rotation/bone/camera matrices. Removed the three stubs so the game's own code runs.
   Found with the EE differential tester (`PS2X_EE_DIFF=all`, see diagnostics.md): 1659 functions identical to
   PCSX2's interpreter, the differing ones traced to stubbed library functions.
10. With sin/fabs/floor un-stubbed the game crashed (null JALR at 0x180E20) because its soft-float double code
    hit a recompiler bug: 32-bit sign test in 64-bit branches (see elf-and-recompilation.md). Fixed.
Evidence for the remaining 3D bug (before fix 6): VU1's XGKICK packets contain vertices with Q < 0 and ±3.4e38 coordinates, i.e.
the EE-side matrices/vertices are wrong (VU1 itself is PCSX2's interpreter now).
Screenshots: window capture (`tools/shot.ps1`) returns white when the host display sleeps — use
`PS2X_FRAME_DUMP=<file.ppm>` + `tools/ppm2png.py` instead.

## New references (2026-10-09, in `ref/`, not used at runtime)
- `ref/proto/`: "God of War — The Hydra Battle" demo disc prototype (Dec 23 2004, SCUS-974.67). Checked: the ELF
  has **no** symbol table / debug sections (sections: .text .data .rodata .bss + DVP overlays); its IRX modules
  have no symbols either (SIO2MAN byte-identical to retail). Only strings like `989snd.c`.
- `ref/pcsx2/`: PCSX2 v2.8.2 (Windows Qt build). No BIOS included — PCSX2 needs a BIOS dumped from a PS2.
  Intended use (user, 2026-10-09): study the game with PCSX2 instead of reverse-engineering by building our own
  emulation.

## Next steps after the controller (in order)
1. Font/2D rendering garbage (GS CPU backend: texture/CLUT/alpha path for 2D text) — compare against expected.
2. Get in-game; fix crashes/hangs as they appear (keep using the trace tools).
3. Performance: profile; GS/VU1 to GPU/faster paths; Release (/GL) build for measurement.
4. Audio: SPU2 output.
5. Switch NRO build + on-device test (see switch.md).

## Uncommitted state
All PS2Recomp changes are uncommitted in `ext/PS2Recomp` (39 modified files + new files: disc_source, iop_format,
iop_sio2, ps2_switch_runtime.cpp, switch/). Nothing was committed or pushed.
- USA menu after Start: vertical list "NEW GAME" with ▼ (port/usa2/gow_pad_test_2.png); Down at 13 s after first pad read was too early (still New Game at 18 s) → new game started again (cliff intro).

## Performance work (started 2026-10-09 ~13:10, user request) — USA on the KIexster stack
Their measurements (ref/other-recomp/.../docs/RENDIMIENTO.md): VU1 interpreter dominated (>80 % of the game
thread after an IOP getenv fix); with OpenGL GS, compiled VU1 microcode (501 captured micro-memories), SSE FMAC,
IOP scheduler and VIF1 fast unpack they reach ~7-14 vid::Flip/s in loaded gameplay (profile: VU1 49 %, GS incl.
waits 31 %, EE 14 %, IOP 6 %).
Plan:
1. Runtime switches, no rebuild: `PS2X_GS_GPU=1` (OpenGL GS; `PS2X_GS_THREAD=1` = CPU GS on a thread),
   optional `GOW_GS_FINISH_ASINCRONO=1`. Measure with `GOW_PERF_DIAG`.
2. Capture VU1 micro-memories with `GOW_VU1_CAPTURA=<dir>` over title/intro/gameplay, then rebuild with
   `-DPS2X_VU1_MICROCODE_DIR=<dir> -DPS2X_VU1_GENERATOR_SOURCE=<their>/tools/vu1/generar_vu1.cpp`
   (`GOW_VU1_SIN_COMPILAR=1` disables it at run time).
3. Profile the rest (their tools/perfil/muestrear.cpp sampling profiler; needs /Zi build).
Measurements must run with no compiler or other game instance active.
- 2026-10-09 ~13:15: stopped by the user while the 2nd load-game test (port/usa3.log, GOW_PAD_GUION start@5,abajo@16,x@24...) was running; its captures were not reviewed. Performance step 1 (OpenGL + VU1 capture) not started yet.
- 2026-10-09 (resumed session): reviewed port/usa3 captures (converted to port/usa3/*.png). Menu → LOAD → X:
  **the user's memory card is read correctly**: "Select Load file from Memory Card Slot 1" lists 4 saves with
  thumbnails (first: OLYMPUS, Sep 27 2021 23:54:43, Hero (Normal) 10:11:50) — visible from ~90 s (state=5) to the
  end (240 s). The scripted X presses ended at ~90 s, so no save was selected yet. Next: rerun with X presses after
  ~100 s (port/usa4).
- 2026-10-09: their configureGowCdImage() (gow_overrides.cpp) uses GOW_ISO, else "<elf dir>/../God of War.iso",
  else the first .iso in the ELF folder, **else an IOP "virtual ISO" built from the extracted folder**. So step
  (c) (DiscSource port) may be unnecessary — to verify with a run without GOW_ISO (port/usa5).
- port/usa4 (running): GOW_PAD_GUION='5:start,16:abajo,24:x,105:x,125:x,145:x,175:x,205:x,250:x', 620 s.
- **2026-10-09: user's USA save loads and plays (port/usa4, verified by captures).** Script above: save list at
  ~90 s, "Load Complete." at 190 s (state=5→6), gameplay at 360 s (state=11, flashReady=1): Kratos in Olympus at
  the save altar, R2 prompt, scene fully textured/lit (port/usa4/gow_pad_test_14.png). Next step (a) done.
  User now asked (2026-10-09): **performance, target ≥ 60 fps**. Starting performance plan step 1–2.
- 2026-10-09 perf1 (port/perf1.log): OpenGL GS (PS2X_GS_GPU=1) + GOW_PERF_DIAG + GOW_VU1_CAPTURA=port/vu1_micro,
  same save-load script. Title ~5-5.8 game frames/s; loaded gameplay (state=11, ~375 s) **4.0 game frames/s**
  (host presents 60/s). Per 5 s window in gameplay: VU 3.07 s, EE 1.58 s, GS 0.20 s, IOP 0.15 s → VU1 is ~61 %.
  (Capture adds overhead.) 351 VU1 micro-memories captured (5.7 MB). Next: reconfigure out/build-kl with
  -DPS2X_VU1_MICROCODE_DIR=port/vu1_micro -DPS2X_VU1_GENERATOR_SOURCE=ref/other-recomp/.../tools/vu1/generar_vu1.cpp,
  rebuild, re-measure. 60 fps needs ~15x: requires a real VU1 recompiler (microVU-style) and EE speedups.
  Stopped here by the user.
- 2026-10-09 perf analysis of perf1 gameplay windows: the game thread is saturated (ee+vu+gs+iop ≈ 4.98 s per 5 s);
  per game frame ≈ 250 ms = VU1 155 + EE 77 + GS 10 + IOP 7. 60 fps = 16.7 ms total. host_wait (~4.95 s) is the
  presentation thread, not a bottleneck.
- Rebuilding out/build-kl with compiled VU1 (PS2X_VU1_MICROCODE_DIR=port/vu1_micro, 351 images) **and /Zi + /DEBUG**
  (still /O2) so their sampling profiler (tools/perfil/muestrear.cpp) can name hot functions. Log port/kl_build_vu1.log.
- agy note: first headless run produced no output — it tried a shell command (denied by settings). Prompt must say
  "Do NOT run shell commands; only read files and search the web".
- 2026-10-09 live play with the user's PS4 controller: it did not work — GLFW lists the user's sim-racing gear
  ("HBP Handbrake", HID 346E:001E/001F) as gamepads and ps2_pad.cpp read only slot 0. Fix (ps2_pad.cpp):
  the gamepad whose button was pressed last becomes active (press edges), else first available slot; logs
  "[pad] gamepad slot N: <name>". gow_overrides.cpp keyboard-stick fallback now only when no slot has a gamepad.
  Verified: "[pad] gamepad slot 0: Wireless Controller" (port/play3.log).
  Play config: PS2X_GS_GPU=1 PS2X_GS_WORKER=1 GOW_GS_FINISH_ASINCRONO=1 GOW_SKIP_FMV=1; title menu 30 fps.

## Bug hunt (2026-10-09 evening; user: pause optimization, fix purple fog, Kratos breaking when walking,
## music restarting; add 16:9)
- Save slots on the user's card: 1 OLYMPUS 10:11:50, **2 DESERT OF LOST SOULS 4:24:25 (purple fog visible)**,
  3 THE CLIFFS OF MADNESS 8:15:53, 4 FINAL BATTLE 10:02:09.
- New test tooling (runner gow_overrides.cpp, copy in port/overrides-usa/): GOW_PAD_GUION accepts stick moves
  (lup/ldown/lleft/lright, rup/...) with hold time "*<s>" (e.g. "170:lup*4"); GOW_PAD_CAPTURAS="t1,t2,..."
  sets capture times. IOP: GOW_SPU2_DIAG=1 (spu2.cpp) prints IRQ/IRQA, sound-RAM writes per 64 KB block and
  active voices every 2 s of SPU2 time.
- Reproduced (port/desert1, worker on): purple/blue-violet haze; Kratos' body mostly missing while walking
  (gow_pad_test_6/7), fine standing (_10).
- Music: gameplay audio repeats every ~6.08 s (port/audio1.pcm autocorrelation). SPU2 IRQ never enabled
  (ATTR bit6=0): the driver streams by polling; music voices v1.00/v1.01 (ssa 0x2820/0x3020) loop while sound
  RAM in that area is rewritten.
- 16:9: PCSX2 patches.zip has SCUS-97399_D6385328.pnach (enhanced widescreen code patch 0x169250-0x16944C +
  native widescreen flag 0x29CC90 and aspect floats).
- Parallel agents (user request) analysing music / fog / Kratos / widescreen; outputs in port/agents/<topic>/.
- 2026-10-09 ~19:55: agents put on standby by the user (token budget). Partial outputs, NOT reviewed yet:
  port/agents/fog/diag.diff, port/agents/widescreen/{runtime.diff,make_ws_variants.py}; music/kratos wrote no
  report. A/B run (gameplay-anchored script, worker on = port/abA, off = port/abB) was running at standby; compare
  Kratos frames there first when resuming (tools/sheet.py). Next: finish A/B, review agent diffs, then fix.
- 2026-10-09 A/B gameplay-anchored (port/abA worker on, port/abB off, *_sheet.png): Kratos intact in both
  (24 frames); breakage is intermittent — needs denser capture. Sand haze correct (sandy) in A's sandstorm area.
- **16:9 done (GOW_WIDESCREEN=1)**: gow_overrides.cpp re-applies every frame the data part of PCSX2's pnach
  (flag 0x29CC90=1, floats 0x2FD930/0x2FD968/0x32F1B0 = 16/9) = the game's native widescreen (vertical crop);
  window opens 1280x720 and gs_host_present.cpp fits the image to 16:9. Also without it the image is now shown at
  4:3 (was square pixels, "1:1" per user). Verified port/ws1. Enhanced (wider FOV) variant needs the pnach code
  rewrite 0x169250-0x16944C + recompile — not done. Agent's widescreen runtime.diff was whole-file → unused.
- **Music restart FIXED (2026-10-09)**: SPU2 NAX read one block ahead → 989snd (polling streamer) aborted the
  music stream (error 0x35) on a ring half's last block. NAX now reported like PCSX2 NextA. Details
  port/agents/music/REPORT.md; verified by port/music2.pcm (no ~6 s repetition). User to confirm by ear.
- Purple fog (2026-10-09): fog agent found GS fog code = PCSX2 (port/agents/fog: diag.diff applied uncommitted in
  ext/PS2Recomp-kl — env PS2X_GS_FOG_DIAG=<s>, PS2X_GS_FOG_FORCE=RRGGBB, PS2X_GS_FOG_OFF=1). Run port/fog1:
  **the game uses no GS fog at all (74808 draws, 0 with FGE)**. The haze comes from full-screen ctx1 sprite
  passes on 16-bit views (psm=0x2) of the 32-bit framebuffer with FBMSK masks 0x00003FFF / 0xFFFF00FF = channel
  shuffle / depth-fog effects (PCSX2 HW special-cases these). Prime suspect: our CT16 reinterpretation/masking
  of the 32-bit target (GPU shaders vs CPU backend). Next: reach the purple canyon (desert1 recipe, absolute
  script) and compare PS2X_GS_GPU=0 (CPU) vs GPU; fogdiag lines identify the shuffle draws.

## How to resume (saved 2026-10-09 ~21:00)
- Build: ext/PS2Recomp-kl branch gow-usa-kl (all committed, author Waffle565; register_functions.cpp generated,
  never committed). Runner's gow_overrides.cpp is git-ignored: tracked copy port/overrides-usa/gow_overrides.cpp
  (copy it back before building if the runner file was replaced). out/build-kl: Release, /Zi, traces OFF,
  compiled VU1 from port/vu1_micro (841 images).
- Play: PS2X_GS_GPU=1 PS2X_GS_WORKER=1 GOW_GS_FINISH_ASINCRONO=1 GOW_SKIP_FMV=1 [GOW_WIDESCREEN=1]
  GOW_ISO=<usa iso> GOW_MC0=<copy of ref/saves/Mcd002.ps2>, cwd = exe dir. Test runs: tools/perf_run.sh
  (GOW_PAD_GUION with g-relative times and sticks, GOW_PAD_CAPTURAS), tools/sheet.py, tools/gsw_trace.py.
- Done this session: save loads; 4 → ~20-25 fps (traces off, compiled VU1, GS worker); PS4 pad selection;
  music restart fixed; 16:9 + 4:3 presentation.
- Open, in order: (1) purple fog = channel-shuffle passes (see above): reach the canyon with the desert1 absolute
  script, compare PS2X_GS_GPU=0 vs 1; (2) Kratos intermittent breakage while walking: dense captures; (3) enhanced
  widescreen (pnach code rewrite + recompile); (4) performance (VU1 block compiler, split GS frontend thread).
- Agents: max 1 in parallel, always with Gemini support (user, 2026-10-09).

## Session 2026-10-09 (late) — purple fog, continued
- The "desert1" script (`60:derecha`) actually loads save slot 3 **THE CLIFFS OF MADNESS**; its lavender/purple
  haze is in the canyon background there (port/desert1 captures). fog1/abA reached the desert (sandy haze, OK).
- Bug found (PCSX2 GSRendererSW.cpp:1476-1480): for 16-bit frame PSMs the 32-bit FBMSK must be compressed to 5551
  (0x00003FFF → 0x00FF, 0xFFFF00FF → 0xFC1F). Our general draw path is equivalent (masks in 8888 before packing),
  but both fast-clear paths (gs_cpu_backend.cpp clear sprite, gs_gpu_backend.cpp clear dispatch) used the raw low
  16 bits. Fixed with `GSInternal::frameMask16` (ps2_gs_common.h); not yet rebuilt/verified.
- Save list: cursor starts on slot 1 (Olympus); one `derecha` = slot 2 Desert, two = slot 3 Cliffs (port/cpu2).
  port/cpu1, cpu2 (CPU GS) landed in the desert interior (no purple there). Running port/cpu3: Cliffs with CPU GS.
- **Kratos breakage (user screenshots 2026-10-09 21:32, desert interior, slot 2)**: upper back/head missing while
  walking. Repro: save slot 2 (`85:derecha*0.3`), walk `g8:lup*4`, capture g9 (port/kr*; compare crops with
  tools/crop.py). Results: compiled VU1 broken (kr1 20.7 fps, kr4); VU1 interpreter OK (kr2, 8.6 fps);
  compiled pairs without blocks `GOW_VU1C_SIN_BLOQUES=1` OK (kr3, 14 fps); blocks with dead-flag elimination
  disabled (new diag `GOW_VU1C_FLAGS_VIVOS=1`) still broken (kr4); blocks + GS worker off still broken in some
  frames (kr5, 14 fps) → not a GS-worker race, the bug is in compiled VU1 **blocks**. RANGO bisect visual
  results were ambiguous. New diag `GOW_VU1C_VERIFICAR=1`: each compiled block (without XGKICK) is also run on
  the interpreter from the same state; mismatches print `[vu1c-verify] block <pc> ... <first difference>`.
- KIexster update (19acde6, 2026-10-09 evening): applied patches/ps2recomp-gs-discard-uncovered.patch (GPU HW
  raster discards fragments outside the triangle; PS2X_GS_HW_DISCARD_UNCOVERED=0 = old). Rest of the update is
  his tests/tools/docs (camera probe, GS replay/feedback tooling) — not taken.
- FPS: kr1 (play config + 1 capture/s) 20.7 game fps in the desert; kr4 37 fps at the run's end. User order:
  ≥ 25 fps after every fix.
- Verifier notes: copying the whole VU1Interpreter per block made the game crawl (0.4 fps, never left the title:
  port/ver1-3); now `GOW_VU1C_VERIFICAR=<N>` checks one block in N. MAC/status are not compared (lazy flag
  commit makes m_state.mac differ at block end without any reader — title blocks 0x2840/0x2898/0x2B90 had only
  MAC "differences" and contain no FMAND/FMEQ/FMOR). Blocks containing XGKICK are not verified.
- KIexster ESTADO.md (via Gemini, checked): his VU1 fixes sticky-preserve and FTZ underflow (247a9b3) are already
  in our tree; he reports 7-11 fps, so nothing to take for performance; intro camera torso/head misframing is
  an open bug on his side too (GOW_CAMERA_DIAG).
- **Kratos: narrowed to compiled VU1 blocks that contain XGKICK.** Sampled verifier (`GOW_VU1C_VERIFICAR=500`,
  port/ver4, ~230 s of gameplay, 28 fps): zero register/VU-memory/cycle differences in blocks without XGKICK.
  New diag `GOW_VU1C_EXCLUIR=xgkick` (blocks containing XGKICK run as single compiled pairs; `=flags` does the
  same for MAC/status readers): port/ex1 Kratos intact at g9-g11 (every other compiled run broke there) and
  **29.5 fps**. Next: verifier extended to XGKICK blocks (GIF submit silenced in the shadow run, in-flight XGKICK
  packet bytes compared) to find the exact difference.
- **Correction (2026-10-10)**: verifier with counters (port/ver6): >125 000 gameplay blocks checked (~75 000 with an
  XGKICK packet in flight), **0 differences** in registers, VU memory, cycles and XGKICK packet bytes → compiled
  VU1 blocks behave like the interpreter. Repeat of the exclusion run (port/ex2, 25-31 fps) still had one broken
  frame (g10): `GOW_VU1C_EXCLUIR=xgkick` only made it rarer; earlier "fixed" runs (kr2, kr3, ex1) were likely luck
  of an intermittent bug. In the broken frame a whole torso batch is missing (we see the inside of the model).
  Next: GS capture of a broken frame (PS2X_GS_RECORD) replayed in PCSX2 — tells whether the GIF stream lacks the
  torso (EE/VIF/VU side) or our GS drops it.
- FPS with the current build (play config, desert room, captures on): 28-31 game fps (port/ver4, ex1, ex2) ≥ 25.
- tools/crop.py: side-by-side 2x crops of the same region across captures.

## Priority (user, 2026-10-10)
Kratos bug, user's description: while walking his torso twists to the right progressively until it loops all
the way around and clips into the legs; arms end behind the back; idle sway, attacks, other animations are fine.
→ an EE-side skeletal/animation math bug (bone rotation accumulates/wraps), not missing geometry (consistent with
the VU1 verifier finding no difference). Only after this is fixed and no other apparent bugs remain: aim for
16:9 at 60 fps.

## Session 2026-10-10 — Kratos walk twist: EE differential testing
- **EE differential tester ported to the USA build** (ext/PS2Recomp-kl: src/lib/ee_ref/ee_diff.cpp + ee_ref/ +
  vu_pcsx2/ from the PAL stack, CMakeLists, main.cpp calls ps2InstallEeDiff after loadELF). Env:
  `PS2X_EE_DIFF=all|<hex,...>`, `PS2X_EE_DIFF_MAX=<n>` (calls per function), `PS2X_EE_DIFF_START=<s>` (only calls
  after s seconds, e.g. during a scripted walk), `PS2X_EE_DIFF_STEPS`.
- tools/eediff_filter.py (drops upper-64-bit-only GPR diffs, sorts by steps), tools/callgraph.py (jal call graph
  from the runner sources: does function X reach Y).
- **rand fix (gowRand in gow_overrides.cpp)**: rand@0x28C0C8 is stubbed in recomp.toml and the generic stub returned
  the host's 15-bit rand(). Game's newlib rand (ELF 0x28C0C8 + PCSX2 reference): seed at *(0x2A4294)+0x58,
  seed = seed*0x41C64E6D+0x3039, returns seed & 0x7FFFFFFF. Callers scaling by 2^31 got ~0 (0x23F350: 2.245 vs
  4.5e-05). Now exact.
- ed1 (all functions, first call after 118 s, before the fix): 279/2400 differing; real ones = rand callers
  (0x21B330 reaches rand via 0x184398→0x184348) + 1-3 ULP float noise from div.s/sqrt.s (PCSX2's interpreter
  computes via double; PCSX2 itself is not bit-exact to the PS2 and runs GoW fine → not the cause).
- ed2 (all, 3 calls each, after the rand fix): 5743 identical, 673 differing, none with a significant (>0.1 %)
  non-stack memory difference.
- ed3 (skeleton: CalcWorldMatrix 0x1303D0 + callees 136870,136990,138108,13DC78,13E090,13E158,13E180,185270 and
  CalcSkinHierarchy 0x137558, 300 calls each during the walk): 800 identical, 0 differing (0x137558 not called).
  Names/offsets from KIexster's gow_model_probe.h (skeleton +0x8C = 64-byte joint matrices, +0x86 root id).
- KIexster update c5c4ad9: perf patches dma-iop-timers-cache / vif1-ee-timers-fast do not apply on our tree
  (ps2_memory.cpp, ps2_vif1_interpreter.cpp context) — deferred.
- **Next step**: the twist is not in CalcWorldMatrix/its callees nor in first-call EE code. (1) Verify visually
  whether the rand fix changed the walk (play: walk ~30 s in open space, front camera). (2) Find the animation
  sampler: run `PS2X_EE_DIFF=all PS2X_EE_DIFF_MAX=50 PS2X_EE_DIFF_START=<walk start>` on a short run and look for
  non-ULP differences; also log Kratos' joint matrices (skeleton+0x8C) per frame while walking to see which joint
  rotates progressively, then find its writer with PS2X_EE_WATCH (not yet ported to the USA build).
- ed4 (all functions, 50 calls each during the walk): 7153 identical, 773 differing, 74 not comparable; no
  significant non-stack memory difference (large gaps only in dead scratch FPRs, e.g. 0x10FC88 chain f5..f10;
  0x20D420 = ULP). Open: which calls were "not comparable" (quiet mode does not print the stop reason).
- **Window 1920x1080 (2026-10-10)**: `GOW_WINDOW=<w>x<h>`; default 1920x1080 with GOW_WIDESCREEN=1 (was 1280x720),
  shrunk to the monitor if needed; image letterboxed at 4:3/16:9 (gs_host_present.cpp). port/hd1: 26-30 fps.
  This is only the window: the GS still renders at native PS2 resolution (~512x448). **Full-HD internal
  rendering** (user, next after the Kratos fix) needs an upscaled render-target path in the GPU backend
  (PCSX2 HW renderer / texture cache style) — a large feature, planned, not started.
- **Twist repro (port/tw1)**: save slot 2, `g8:ldown*16` (walk toward the camera): legs run forward, torso turned
  ~180° with blades raised behind — clearly visible in gow_pad_test_1.
- Eliminated (2026-10-10, all match PCSX2 / sane): EE code during the walk (ed6: ~16 000 calls after gameplay start,
  no significant difference; ed4/ed5 never reached gameplay — all-function hooks slow loading, start the diff after
  gameplay), libc stubs (__divdi3/memcmp/rand differ only in scratch regs), SPR DMA (no interleave mode used, no
  aborted chains; `[dma] SPR ... not handled` diag added), animation dt (0.033 s, GOW_FAST_BOOT diag now also in
  state 11), EE timers (T0 mode 0x082 = BUSCLK/256, read ~660/s; `PS2X_TIMER_DIAG=1`), no VU0 micro-programs
  (no VCALLMS in the ELF). Not comparable = kernel/syscalls/COP0 + DMA register code (ed7, now printed).
- Remaining suspects: data coming from the IOP side (disc-loaded animation data, pad bytes).
- **Next step**: ground truth from PCSX2. Our dump: port/ram_desert_g5.bin (`GOW_RAM_DUMP=g5:<file>`, standing in
  the desert room 5 s after load). Needed: PCSX2 save state (ref/pcsx2, USA ISO, card ref/saves/Mcd002.ps2, slot 2)
  standing in the same room → extract eeMemory.bin (7-Zip) → compare level/animation data regions (static data
  loaded from disc must be identical; differences = IOP/disc path bug).
- **PCSX2 ground truth obtained (automated, see diagnostics.md)**: port/pcsx2state_desert/eeMemory.bin (desert room,
  ~5 s after load) vs ours port/ram_desert_g5.bin. Code/static data identical; level heap identical except an
  allocation-order drift: ours has two extra 16-byte heap entries at 0x19A78C4 (hashes A757E542→01EEFF00,
  A183E323→019A3090), after which data is shifted by +0x1480 (up to ~0x1EF0000); 0x1200000-0x13A0000 is per-frame
  data. Next: check whether the shifted/extra allocations are timing-only (dump both at the same frame) or a real
  difference; then compare Kratos' skeleton/animation data (object+0x104 → skeleton, +0x8C joint matrices).
- PCSX2 visual ground truth (port/pcsx2_walk1.png): running toward the camera Kratos faces it, arms swing, blades on
  his back. Ours (port/tw1/gow_pad_test_1.png): torso turned 180°, blades raised behind → confirmed port bug.
- div.s/sqrt.s ULP gaps explained: our runtime divides/sqrts with round-to-nearest (ps2FpuDivideNearest) while other
  FPU ops run with the EE's chop mode = PCSX2 2.x defaults (separate division rounding). eeref lacks that split →
  its 1-ULP "differences" are reference artifacts, not port bugs.
- SPR normal-mode DMA advances MADR/SADR and zeroes QWC (checked), pad bytes centered (128) — fine.
- Hypothesis for next session: 180° twist that "loops around" = yaw interpolation taking the long way (angle at the
  ±π wrap). Next: locate Kratos' object/skeleton (KIexster probe: hook 0x159878, object+0x104 skeleton) and log the
  spine joint's local yaw per frame in ours vs PCSX2 (PINE reads while walking), then find the variable that feeds
  it and compare that variable between both.
- GOW_SKEL_DIAG=1 / GOW_SKEL_OBJECT=<hex> (gow_overrides, wraps CalcWorldMatrix 0x1303D0): port/sk1 lists only 6
  objects and KIexster's offsets (object+0x104 skeleton, +0x60 definition count) give garbage counts for this a0 →
  the CalcWorldMatrix argument is not his "object" struct. Candidate near the player: 0x739FC0 (skeleton 0x73BB50,
  joints 0x7910F0, pos 2414.7,514,6744.9). Next: confirm the struct (read his gow_model_probe callers / hook
  0x159878 model context) before logging per-joint yaw.
- Skeleton diag now hooks ProcessModel 0x157A60 (object = *(a1+0x18), as in KIexster's probe). port/sk2: object
  0x1112470 has 125 joints (skeleton 0x11143B0, joints 0x11297E0) — likely Kratos. port/sk3 (GOW_SKEL_OBJECT=
  1112470, walking): the matrices at skeleton+0x8C never change → bind pose, not the animated pose. Next: find the
  per-frame animated joint matrices (output of CalcWorldMatrix 0x1303D0 / CalcSkinHierarchy 0x137558, or the
  matrices DMA'd to VU1 for skinning) and log the spine yaw there; then read the same in PCSX2 via PINE.
- **Kratos twist — strongest lead so far (2026-10-10)**:
  - Write watchpoint ported: `PS2X_EE_WATCH=<hex>[:len]` (page guard, logs guest pc/ra; src/lib/ee_watch.cpp) and
    `PS2X_EE_WATCH_WORD=<hex>` (function-level). `GOW_RAM_DUMP=<t>;<t>...:<file>` (multiple dumps, folder must
    exist), `GOW_PAD_LOG=1` (pad packet: clean, no buttons while walking).
  - RAM dumps while walking (port/rdump/ram.0-6): float at 0x11BF5F4 runs 0→4.3 and loops = an animation
    PLAYBACK TIME (writer 0x116EF0: time = min(time + dt*rate, length)), in an anim controller (type ptr
    0x2C2D20, struct base 0x11BF5A4) created by 0x2520C8 with parameters copied from its parent (type 0x2BF1A0,
    built by 0x106328 from 0x100EA8: +0x1C = layer index s5, +0x24 = data byte (lookup 0x239228)+2).
  - PCSX2 ground truth (walking save states port/pcsx2walk2/3): objects of type 0x2BF1A0: PCSX2 43, ours 45;
    (index 1, flag 0x81): PCSX2 1, ours 3 → **our game creates two extra animation layers** (likely the
    raised-blades upper-body overlay). Heap layouts differ per session, match objects by type pointer, not address.
  - Next: find what makes 0x100EA8 create the extra layers (its loop/table input; watch the creation path and
    compare the table entries / owner objects with PCSX2).
  - Refinement: the extra layer owners in ours (0x11BE09C, 0x11BE168, header word 0x00020024 = small 2-joint
    animators, probably props) are not Kratos. The winding time at 0x11BF5F4 belongs to 0x11BE168 → not the
    twist. Kratos' animator = header 0x001E0024 (ours 0x7AE808, PCSX2 0x7A69A0): same layers (0, 1*) in both.
    Next: compare Kratos' animator layers' state (time/rate/weight fields of its two controllers, type 0x2C2D20,
    reached via owner → layer parent (type 0x2BF1A0, +0x10 = owner) → controller (+0x18/+0x1C pointers)) between
    PCSX2 walking states and ours.
- Kratos' own animator layers/controllers are identical to PCSX2 while walking (port/pcsx2walk3 vs rdump/ram.3).
- `GOW_VU1_PCSX2=1` (ps2_runtime.cpp: MSCAL/MSCNT on PCSX2's VU1 interpreter via vu_pcsx2/pcsx2_vu1_bridge, as in
  the PAL stack): port/pv1 still shows the twisted pose → **VU1 semantics ruled out** (both ours and PCSX2's VU1 give
  the same broken pose). Still open: where the bone matrices that reach VU1 get the wrong rotation. Next: dump the
  skinning matrix palette Kratos sends to VU1 (VIF1 UNPACK source in EE RAM) in ours vs PCSX2 while walking.
- Kratos animator object (ours 0x7AE808 / PCSX2 0x7A69A0, ±0x400 bytes): no differing float fields, only pointers.
  No math functions among the recompiler stubs (file/SIF/kernel only). So far everything upstream of the pose
  matches PCSX2; remaining unexplored: the per-joint pose evaluation output (joint matrix palette per frame) and the
  palette's transfer to VU1 (VIF1 UNPACK). Plan: find the palette address via VIF1 UNPACK sources while walking
  (PS2X VIF trace) and compare those matrices with PCSX2's at the same animation phase.

## Session end 2026-10-10 (morning) — state of the Kratos animation bug
- User screenshots 065930/065937: the same raised-arm/blade pose also appears for ONE frame in idle and during
  the Q/E (L1/R1) animation → likely one bug: a wrong pose sampled/blended occasionally (continuously while walking).
- Tried, no visual change (kept, they match PCSX2): VIF1 UNPACK STMOD 3 now stores data in ROW (PCSX2
  Vif_Unpack.cpp setVifRow); EE FPU mode on the GameThread = PCSX2 default (round toward zero + FTZ + DAZ;
  GOW_EE_FPU_NEAREST=1 = old). port/m3, port/chop1 look identical to before (pose deterministic).
- Checked OK: no VIF1 UNPACK cut by buffer ends (`[vif1] UNPACK cut` diag, port/vc1), only 2 EE threads (main +
  waiting sound/stream; `GOW_THREAD_DUMP=<t>`), caller-frame diffs are ULP only (`[eediff-callerframe]`), skipped
  "did not return normally" calls are wrapper artifacts (0x116EF0/0x117A50/0x1064F0 compared OK individually).
- KIexster cbb58c3 (pulled into ref/other-recomp-git): he works on the same thing — full model palette and
  skinning-buffer diagnostics, native joint/camera comparison against a paused PCSX2 EE reference
  (tools/render/pcsx2_ee_reference.py), optional VIF1/VU1 thread patch (PS2X_VU1_HILO=1). His ESTADO.md summary
  was not obtained (Gemini run stopped). **Next: read his palette/joint findings first**, then compare Kratos'
  joint palette (skinning buffer) with PCSX2 at the same animation frame.
- Remaining stage not yet verified against PCSX2: the per-frame joint palette itself (EE output just before VIF1).

## Session 2026-10-10 (midday) — invasive tests of the Kratos twist
- KIexster's ESTADO.md (cbb58c3) read: he has NOT found the cause either (only input palettes at ProcessModel, matches
  PCSX2 within ULP-level noise; skinning output/VIF still unverified). Nothing to borrow for the twist.
- Animation-state object (ours 0x8629C0 / PCSX2 0x862900, referenced from Kratos' animator) carries stale heap garbage
  in ours ('Mark' string at +8, a float rotation at +0xA4) where PCSX2 has zeros → hypothesis "uninitialised heap data".
- **Test: `GOW_HEAP_ZERO=1`** (gow_overrides.cpp, wraps USA heap alloc 0x13DC78, zero-fills every returned block;
  note tools/dis.py reads the PAL port/output, use port/output-usa for USA addresses). port/hz1: pose IDENTICAL to
  port/tw1 (torso twisted, blades raised) → **stale/uninitialised heap data ruled out**.
- Repro command used: `tools/perf_run.sh hz1 230 GOW_HEAP_ZERO=1 GOW_PAD_GUION='5:start,16:abajo,24:x,85:derecha*0.3,92:x,g8:ldown*16' GOW_PAD_CAPTURAS='g12,g16,g20'`
  (gameplay starts ~110 s; captures hz1/gow_pad_test_1.png).
- Next invasive step: dump the joint palette Kratos sends to VU1 (VIF1 UNPACK V4-32 blocks) and compare with the
  bind-pose/hierarchy; or bisect by forcing individual animation layers/controllers off to see which one carries the
  twisted torso.
- New diagnostics (all env-gated, off by default): `GOW_VIF_MATDUMP=<file>:<start>:<len>` (+[vifhist] histogram of UNPACK
  shapes), `GOW_SKEL_ANIM=1` (per model-palette object: joints moved/nonfinite every 90 calls), `GOW_SKEL_DUMP=<file>`
  with `GOW_SKEL_OBJECT=<hex>` (raw 125x64-byte palette per call). Heap addresses are stable between identical scripted
  runs. In the desert Kratos candidate = object 0x1AC38B0 (125 joints, pos 2433,512,6738) but skeleton+0x8C is not a flat
  matrix array for it (only joints 0-5 look like matrices) → the pointer layout differs per object; palette dump unfinished.
- VIF1 UNPACK reviewed against PCSX2 Vif_Unpack.cpp (mask/row/col, STMOD 1/2/3, V2/V4-5, cycle/fill): equivalent except
  V3 W lane (PCSX2 = next source word; ours = stale VU memory, harmless) and CL/WL==0 remap. Histogram shows the walk's
  UNPACKs are V4-16/V4-8 (vertex data) and V4-32 num=1 (headers); no big V4-32 matrix blocks.
- DMA chain walker reviewed: tag ids 0-7 match hardware. No tag with the SPR flag (bit 63) occurs on any channel
  (`[dma] chain tag with SPR flag` diag, port/spr1) → ruled out.
- Dense capture (port/sq1_sheet.png, 16 frames over 1.5 s of the walk toward the camera): the raised-arm/blade pose is
  CONSTANT while the legs animate → the upper body is frozen in one pose (not a periodic glitch): upper-body layer
  not advancing, or blended at the wrong weight with a static "ready" pose.
- Checked, no difference: pad packet (pressures, order), DMA tag semantics, VIF OFFSET/BASE/ITOP/MSCAL double buffer logic,
  UNPACK mask/mode. Animator node lists differ in ours vs PCSX2 (3 contiguous 0x1E0024 nodes vs 2 nodes 0xB0024 in
  PCSX2) — header meaning unknown; may just be heap layout.
- **Next (decisive, not yet done)**: log Kratos' layer controllers' time/weight EVERY frame in ours during the walk
  (controller type 0x2C2D20 via layer parent 0x2BF1A0 +0x18/+0x1C; parent for owner 0x8629C0 at 0x6FC4F0 in ours rdump)
  to see whether layer 1 (flag 0x81, upper body) advances and what weight the blend uses; compare with PCSX2 states over a
  few frames (PINE reads). If time advances and weight is ok, the sampled clip data (disc-loaded) is the suspect.
- **GPU translation cleared (2026-10-10)**: PS2X_GS_GPU=0 (CPU software GS, port/cg2, gameplay at 207 s) shows the SAME
  frozen raised-blade pose as the OpenGL backend → the bug is upstream of the GS (GIF data), not in the GPU translation.
- `GOW_CTRL_DIAG=1` (gow_overrides.cpp, wraps controller update 0x116EF0): every ~4000 calls prints per controller
  (heap 0x600000-0x900000) calls/time/rate. port/ct1: Kratos-area controllers in the static pool (0x6FAF64, 0x6FAFD4,
  0x6FB834/8A4/914/984, 0x7481E8) advance normally (rate 1.0); the same pool addresses exist in PCSX2 with identical layout,
  clip pointers (0x600680, 0x607E00, 0x608200 … static region, equal in both) and advancing times → controllers/clips
  match PCSX2. No "No exact recompiled function" errors in the run. So: inputs (controllers, clips, EE code, VU1, VIF,
  DMA, both GS backends) all match; the frozen pose must come from something not yet compared — candidates: VU0
  state across thread switches/interrupts (vf regs, Q/flags are not saved by our thread switch?), or blend weights
  computed from a game-state variable (speed/stick) that differs between runs.

## Session 2026-10-10 (afternoon) — long invasive hunt, state at end
Ruled out (all verified, see earlier bullets for method): GPU backend (CPU GS shows the same pose), stale heap, pad, DMA tag
semantics/SPR flag, VIF1 UNPACK/MPG/STROW (no cut data, no unhandled VIFcodes, CL=4 WL=1 stride writes OK), VU0 flag registers
(game never uses CFC2/CTC2/VCLIP), sine table (matches PCSX2 to 1 ULP), animation clips (byte-identical to PCSX2), controller
set/weights (same 43 controllers of the player animator 0x74ED74 at identical addresses, weights equal), sampler 0x10FC88
(803 calls diffed against PCSX2's interpreter: only stack garbage/ULP), recompiled-function coverage (no missing functions).
- **Player model = object 0x753E20 (103 joints)**, skeleton 0x755EF0 (+0x88 animator 0x74ED74, +0x8C world palette 0xD53910,
  def +0x60 = 0xD4A960, local matrices array 0xD4FE40). Same addresses in PCSX2 → direct comparison possible.
- **Palette finding**: walking in ours the arm/blade-chain joints (12-30 and 31-51) are 3-18 units from spine joint 3 (mean ~10),
  PCSX2 coherent snapshots (6 walking frames, port/pcx_S.npy) stay 7-11. Local joint translations are constant in both
  (rigid), so the extra excursion comes from the chain joints' ROTATIONS: in ours snapshots 1-2 the 19 chain joints each rotate
  ~100-150 deg (curled) vs <90 in PCSX2. The pose is wrong in the WORLD PALETTE (upstream of VU1).
- Tools: `GOW_SKEL_OBJECT=753e20 GOW_SKEL_DUMP=<file>` (per-call palette), `GOW_DMA_BLOCKDUMP`, `GOW_CTRL_DIAG`,
  `PS2X_EE_WATCH_FROM=<s>` (write watch after s s), `PS2X_EE_DIFF_EVERY=<n>`, VU0 ctl state compared in eediff.
  PCSX2 coherent snapshots: PINE save slot (`python snap.py <slot> <dir>` pattern in this session) + 7z extract; live PINE
  reads are NOT coherent (mixed frames). PCSX2 slot-1 save = Olympus (walk with stick keys W/A/S/D; ~3 s holds).
- Next: sample the chain clip (type 0x3221 clips edd800..ee3d40 at 0xED....) offline with the game's own decoder and compare
  with the palette in both; or diff the blend (0x10A530/0x10B0C8 callers of the sampler) with PS2X_EE_DIFF_EVERY over a long walk.

## ★ Kratos twist FIXED (2026-10-10) — miscompiled PMULTH (MMI)
- **Root cause**: the recompiler's `translatePMULTH` (ps2xRecomp/src/lib/mmi_translation_helpers.cpp) was a wrong template
  (`_mm_madd_epi16` + sum of all products into one scalar). PMULTH (parallel multiply halfword) stores EIGHT separate 32-bit
  products: LO={p0,p1,p4,p5}, HI={p2,p3,p6,p7}, Rd={LO0,HI0,LO2,HI2} (PCSX2 MMI.cpp). The animation clip decoders
  0x115978 / 0x115D00 / 0x116280 (called from the sampler 0x10FC88 via 0x10B0C8) use it to unpack the compressed joint
  angles → wrong local joint matrices for ~46 joints (arms, blade chains, spine incl. joint 9) → torso twist / raised blades.
- **How it was found**: PCSX2-ground-truth palette comparison (same desert scene, coherent PCSX2 save-state snapshots via PINE
  save + 7z) showed PCSX2 keeps joint 9 constant while ours animates it; then the EE differential tester with
  `PS2X_EE_DIFF_LINES=3000` (the old 24-line cap had hidden the real, large mem diffs in the local-matrix array 0xD4FE40)
  showed the recompiled 0x10FC88 produced different local matrices than the interpreter; bisecting callees led to
  0x115978 and its `pmulth`. (Earlier "ULP only" verdicts were wrong because of that cap and my significance filter.)
- **Fix**: `ps2PmulthExec(ctx, rs, rt, rd)` in ps2xRuntime/src/lib/ps2_runtime.cpp (exact PCSX2 semantics); generator
  template now emits the call; the 4 generated PMULTH sites (port/output-usa + runner copies of sub_00115978, sub_00115D00 x2,
  sub_00116280) were patched in place (no full regeneration needed). After the fix the 0x10FC88 diff vs PCSX2's interpreter
  is ULP-only and the walk is visually correct (port/fix1_sheet.png, fix1_crop.png).
- Other approximated MMI templates exist (PMADDH/PHMADH/PMSUBH/PHMSBH/PMULTW/PMADDW/…) but the game does not use them
  (pmulth is the only MMI multiply in the ELF: 4 sites, 3 functions). Verify any other MMI op the same way if new symptoms appear.
- Tools added this session (all env-gated): GOW_SKEL_DUMP/GOW_SKEL_OBJECT, GOW_DMA_BLOCKDUMP, GOW_VIF_MATDUMP, GOW_CTRL_DIAG,
  GOW_BLEND_DIAG, GOW_HEAP_ZERO, PS2X_EE_DIFF_EVERY, PS2X_EE_DIFF_LINES, PS2X_EE_WATCH_FROM, VU0 control-state compare in eediff.

## Checks 2026-10-10 (after the PMULTH fix): MMI, fps, 16:9, internal resolution
- **MMI audit**: all 41 distinct MMI/HI1/LO1 ops present in the USA ELF (pcpyld 1124, ppacw 566, por 380, prot3w 268, pexew 150,
  pextlw 104, paddh, plzcw, pand, psrlh, pceqw, ppach, qfsrv, pextlb, pnor, madd, padduw, psraw, pcpyud, mult1, pextub, pminh,
  pmaxh, psubw, psubb, paddw, ppacb, pcgth, psrah, psllh, mthi1/mtlo1/mfhi1/mflo1, pextuw, pcpyh, pxor, pextlh, psllw, div1,
  multu1, pmulth) were reviewed against PCSX2 MMI.cpp (macros + generated lines): all correct except PMULTH (fixed).
  Full `PS2X_EE_DIFF=all` run during the walk (7269 compared calls, uncapped lines): no non-ULP memory difference outside
  stack garbage, rand-dependent functions (rand stubbed) and VU0 Q-precision noise. qfsrv uses SA in bits consistently
  (MTSAB/MTSAH/MTSA store bits). Unused but still approximate in the generator: PMADDH/PHMADH/PMSUBH/PHMSBH/PMULTW/PMADDW/PMSUBW
  (not in this ELF; fix before porting another title).
- **FPS** (play config PS2X_GS_GPU=1 PS2X_GS_WORKER=1 GOW_GS_FINISH_ASINCRONO=1 GOW_WIDESCREEN=1, desert walk, port/fps1.log):
  guest_flip_hz 42.6-43.0 game fps, host 60 Hz; floor of 25 OK.
- **16:9**: GOW_WIDESCREEN=1 → 1920x1080 window, picture fills the whole window with the pnach's widened projection, no bars,
  Kratos correct (port/win1_window.png).
- **Internal resolution does NOT match the window**: GS framebuffer/VRAM emulation is native 512x448 (captures
  gow_pad_test_*.png are 512x448); the host upscales to 1920x1080 with a bilinear filter → soft image. True internal
  upscaling needs a PCSX2-style HW renderer (render targets + texture cache, because the GS emulation is VRAM-faithful,
  incl. framebuffer feedback/channel-shuffle passes); not a flag. Cheap interim option: sharper present filter
  (sharp-bilinear/Lanczos/CAS) in gs_host_present.cpp.

## 2026-10-10 (evening): release build, output scaler, zone checker
- **Overhead removed**: runner rebuilt with `-DPS2X_ENABLE_DEBUG_UI=OFF` (no ImGui "Runtime Debugger" panel, no per-frame UI work;
  previous cache saved as out/CMakeCache.dbg.bak), per-STCYCL `getenv` (my diag) made static. Same desert walk: guest 42.6 →
  **47.8 fps** (GS worker + FINISH async + widescreen). `play.cmd` = release launcher (no diagnostics; `play.cmd 43` for 4:3;
  makes disc-usa/play.mcd from the user's card on first run).
- **Output scaler** (gs_host_present.cpp, GOW_SCALER=sharp default | bilinear, GOW_SHARPEN=0..1): Catmull-Rom bicubic + CAS
  sharpen at the window resolution instead of the bilinear stretch; costs ~0.7 fps. NOT internal resolution: the GS still
  renders 512x448 (VRAM-faithful compute/hardware raster in gs_gpu_backend.cpp). Real scaling = scaled render targets +
  texture cache + readback/downscale for feedback passes (PCSX2 GSRendererHW style) — separate multi-week project, not started.
- **tools/zones.py** (zone regression check): per save slot loads the game, walks 4 directions, captures frames, and judges
  gameplay reached / fps floor / runtime errors / blank captures / change vs `--baseline`; `--diff` adds the EE differential
  tester; `--card` takes any memory card (more saves = more zones). First run (port/zones/20261010_123435/report.md):
  slot 1 Olympus 21.8 fps FAIL, slot 2 Desert 28 ok, slot 3 Cliffs 21.2 FAIL, slot 4 Final battle 25.2 ok. All zones render
  correctly (Kratos pose fine). Open per the fps floor order: Olympus and Cliffs sit below 25 fps → profile those zones next.

## 2026-10-10 (night): native VU1 backend (no VU emulation left on the hot path)
- **What it is**: `tools/vu1/vu1n_gen.py` turns the 3400 captured micro-memories (+ `port/vu1n_heads.txt`, learned entry pcs) into
  1704 straight-line SSE basic blocks (`vu1n_generado/vu1n_part*.cpp`, built by CMake, keyed FNV(pc, words)); runtime in
  `ps2_vu1_native.{h,inl}` (hooked in `VU1Interpreter::run`). No cycle model, no pipeline queues: immediate semantics, MXCSR
  RZ|FTZ|DAZ. The exact engine only steps a pair when no block matches (now: never, `missBlocks=0`) and is the A/B oracle.
- **What had to be modelled to match the exact engine bit for bit** (found by `GOW_VU1N_VERIFY=N` A/B + bisection to the first bad
  block): MAC/CLIP visibility latency (writer at pair j visible from pair j+4, shifted by the *stall model* of the exact engine:
  `nativeTiming()` replays decode/readiness per block with all pipelines idle at entry → `n.cyc[]`); Inf/NaN operands act as ±FLT_MAX
  (`nrm`, registers keep raw bits because integer data travels through VF); MADD/MSUB overflow evaluated wide (RZ saturates the
  product to FLT_MAX); `big` result = overflow flag; header compiled with strict FP (runtime is /fp:fast).
- **Verification**: 40,000 VU1 program runs (Olympus + slot 1) compared with the cycle-exact interpreter (state, VU memory, GIF
  packets): 0 mismatches. Debug env: GOW_VU1N_VERIFY=N, GOW_VU1N_DIAG=1 (hot misses → add to port/vu1n_heads.txt),
  GOW_VU1N_DUMP=1, GOW_VU1_NATIVE_OFF=1 (back to the old path).
- **Perf** (perf_run, Olympus, same build): guest 13.8 → 17.6 fps with native on; VU bucket 1870 → 1070 ms per 5 s. Other zone: 28 fps.
  Remaining VU cost ~7 ns/pair (XGKICK/GIF handling + dispatch, to profile). Olympus/Cliffs still < 25 fps: EE (~25 ms) and IOP now dominate.
- **Next** (docs/native-port.md order): profile VU leftovers, IOP (R3000 interpreter → native sound/CDVD), EE codegen, true 1080p
  renderer; extracted-files loading stays last.

## 2026-10-10 (late): native GS renderer started (`PS2X_GS_HW=1`, opt-in; default backends unchanged)
- **New backend** `GSHwBackend` (ext: `gs_hw_backend.{h,cpp}`): draws are rasterised by the GPU into scaled RGBA render targets
  (one per frame-buffer base, depth per target), textures are decoded once from a shadow VRAM (`GSCpuBackend` still models VRAM,
  transfers, CLUT; `DecodeTextureRgba`) and cached with block-range invalidation, a render target used as a texture of the same
  format is sampled directly, alpha test (incl. AFAIL via a second pass), FBMSK as colour mask, ZTST/ZMSK as GL depth state, the
  dominant ABE modes via dual-source blending. CRTC output is read from the target at `PS2X_GS_HW_SCALE` (default 2) x PS2 size.
- **Verified**: main scene geometry/textures/lighting render correctly (see `GOW_GS_HW_ONLY` bisect frames, depth off); gameplay
  runs ~40 fps at scale 1 (old backend 39-42). Debug env: GOW_GS_HW_STATS, _DUMP/_DUMPAT (per-batch state), _TEXDUMP, _DEPTHDUMP,
  _DEPTHTRACE, _RTDUMP, _ONLY=a-b, _NODEPTH, _NOATEST, _NOFAIL.
- **Not working yet (why the final image is still wrong)**: the game builds the picture in several passes into RT 0 (clear → world →
  clear → ...) and then post-processes through *layout reinterpretation*: 16-bit views (tpsm=2) of narrow targets (fbp 320, fbw 1),
  1024x1024 reads with tbw=1, 32-px column sprites. A plain render-target cache cannot express those; the fallback (write the target
  back to shadow VRAM, `syncTargetToVram`) is implemented but slow (12 fps) and still produces striped output. Z-clear value of the
  game is not 0 (0x900000 seen), so world draws only pass because the game's own clear sequence is replayed faithfully — do not
  add a "clear depth per frame".
- **Next**: (1) resolve those reinterpretation passes explicitly (identify each pass in the inventory: which RT, which psm/tbw view,
  which op — column shuffle / channel merge — and implement it as a dedicated shader on the RT instead of the generic readback),
  (2) GPU-side RT→texture conversion instead of CPU WriteVram, (3) then raise scale and drop the bicubic upscale, (4) host
  presentation currently assumes 640-wide rows (frontend `kHostFrameWidth`) — needs to carry the scaled frame.

## 2026-10-10 (night 2): native GS renderer renders Olympus correctly (`PS2X_GS_HW=1`)
- Full world, lighting, reflective floor, characters verified (port/zones_hw32 sheet) at ~40 fps (scale 1; old backend 39-42).
- Needed beyond the first version: STQ scaled by TEX0 size not by target size; real drawn extents per target; Z wrapped to Z24;
  DATE/DATM destination-alpha test (reads the target); reverse-subtract blend (Cd - Cs*C, fog darkening); depth buffer sampled as
  Z16/Z24 texture; CT16 targets; **reinterpreting texel fetch** (GPU address math with the GS page tables in a texture: texture
  format address -> owning render-target pixel -> bits re-extracted, incl. T8H = alpha plane, CT16 view of CT32) and the same for
  CLUT/palette; draws through a different-format view of an existing target and single-plane FBMSK mask builders are skipped (their
  readback pass is not reproduced yet).
- No VRAM image anywhere in the draw path; the CPU backend is only the payload store for uploaded texture bytes / CLUT.
- Still open: the mask passes (G-plane / CT16-view effects: shadows/fog masks), scale > 1 in the host presenter, slot 3 (Cliffs) 11 fps.

## 2026-10-10 (night 3): internal resolution 3x through the render-target renderer
- `PS2X_GS_HW=1 PS2X_GS_HW_SCALE=3`: Olympus renders at 1536x1341 internal (port/zones_hw33), ~36 fps; host presentation carries frames
  larger than 640x512 (texture sized to the frame, frontend row stride = frame width).
- Remaining visual defect: dark blotches on stone (missing mask passes). Cause: the game builds lighting masks through CT16 views of
  CT32 targets (frame psm=2 on fbp 0, FBMSK 3fff/ffffff/ffff00ff) and single-plane G fills; those draws are currently skipped. Plan:
  a view round trip — proxy target in the view's format filled from the owner by the reinterpreting fetch, draw, resolve back by the
  inverse address mapping (needs texelBits > source bits support in the shader: two source pixels per word).

## 2026-10-10 (night 4): GS mask passes, HUD, menu depth of field (ext 2509d00)
- **Channel shuffles** (`tryShuffle`/`flushShuffle`): the game moves bytes between channels with 8 px sprites through a CT16 view
  of a CT32 target (FBMSK 3FFF = high byte of each halfword), textured from a CT16/Z16 view of a CT32 target or of the Z buffer.
  In a 16 bit view the two 8 px halves of each 16 px column group are the low/high halfwords of the same 8 owner pixels, so each
  sprite becomes owner-block quads (exact addresses: GSSwizzle + inverse page tables) and a halfword copy in a small GL program;
  TEXA is applied to the alpha bit. Olympus per frame: A <- Z[15:8] (fog), A <- G, G-plane shadow mask (now drawn normally with a
  G-only colour mask), swap through the 64 px temp at fbp 320, then `Cd - Cs*As` gated by DATE. Fixed the stone blotches.
- **Removed the colour->depth resolve** (7664544): the colour draws into the Z memory (CT24 at fbp 104 = zbp) are full-screen
  `Cs - Cd` inversions; mirroring them into the GL depth buffer wiped the depth and hid Kratos and the torch flames.
- **High-byte textures** (T8H/T4HL/T4HH) stored in the top byte of the Z memory are read from the uploaded bytes, not from the
  CT24 alias (which never writes bits 24-31): HUD prompts ("R2") and the save point light shaft/glow now match PCSX2.
- **Z buffer in a target's own colour memory** (ZBP == FBP, menu DOF strips at fbp 320): Z test/write in the shader against the
  colour words. **GS blending in the shader** for C = Ad (0x80 = 1.0) and COLCLAMP=0 wrap. Menu background blur now matches.
- Verified: Olympus 40 fps (scale 1), 0 skipped batches, Kratos/flames/HUD/light shaft present (port/ui5).
- PCSX2 reference driving: docs/diagnostics.md "PCSX2 driven automatically"; the old CPU GS backend (no PS2X_GS_HW) is also a
  correct oracle for the menu.
- Menu fixed (ext 99afa2d): STQ texturing divided by |Q| (the menu Kratos has negative Q -> face texture rotated 180 degrees);
  Present now merges both CRTC read circuits like the hardware (menu "Soften": two circuits 1 px apart, ALP 0x80).
- Open: Kratos sometimes yellow/green tinted in gameplay
  (also in the 19:44 baseline); fps of the zone run varied 21-40 between runs (CPU-bound EE/VU windows, re-measure).

## 2026-10-10 (night 5): IOP code native, IOP cost removed (ext 98bc59f)
- The 8 game IRX modules run as ahead-of-time compiled C++ (details: docs/native-port.md "IOP: ahead-of-time compiled IRX
  modules"); 0 interpreted IOP instructions in Olympus.
- IOP time was the EE's per-call accounting (3.4 M runCycles/s), now batched: IOP 2.8 s -> 0.2 s per 5 s, boot to gameplay
  95 s -> 20 s. Olympus renders correctly (port/iopn4).
- Native GS on all zones (port/zones_hw5): Olympus 39, slot 2 55, slot 4 37, **Cliffs 10 fps** (blocks GS_HW default).
- fps measurements: close other emulators/the game first (a forgotten PCSX2 instance halved several runs).

## 2026-10-11: native GS is the only renderer (ext c122cad)
- The VRAM-emulating GPU rasteriser is deleted; `PS2X_GS_HW` / `PS2X_GS_GPU` no longer exist. Internal scale `PS2X_GS_HW_SCALE`
  (default 2).
- Paletted textures: index texture (R8, per upload) + palette texture (per CLUT), lookup/filter in the shader; replaces the
  per-texel CPU decode per texture x palette (cause of the hitches when enemies load: Cliffs had 1500 live textures, now ~180).
- Present: the two read circuits are composed on the GPU (was 2 full readbacks + CPU blend per frame).
- Zones at scale 2 (port/native2): Olympus 37 fps, Cliffs 30-39 fps.

## 2026-10-11: 16:9 only
- User: 16:9 is the standard, never 4:3 again. `GOW_WIDESCREEN` is removed: the game's widescreen data patch is always
  applied (gow_overrides.cpp), the host fits the image at 16:9, the window defaults to 1920x1080; `play.cmd 43` is gone.
  Zone captures (tools/zones.py) are the anamorphic 16:9 frames as the GS draws them (ext 026045a).
- Main achievement set by the user: after the PC port the game must run on the Nintendo Switch (docs/README.md). Citron
  (Switch emulator, nightly 0237a9b88, MSVC build) is unpacked in ref/citron (citron-cmd.exe) for testing the Switch build.

## 2026-10-11: no-emulation order steps 1 and 3 done (ext 875661a, fcc1697)
- Step 1: pad and memory card are native services; the SIO2 chip model is deleted (docs/memory-card.md).
- Step 3: the SPU2 register model and the SPU DMA channels are deleted; LIBSD's exports are native and drive a typed
  SoundEngine (docs/sound.md). Desert audio matches the former model; save test ok.
- EE and VU1 speed agents merged (ext 39379ea, 492db8f): Olympus steady 30 fps (VBlank lock; docs/performance.md).

## 2026-10-11: steps 2 and 4 (ext 293d133)
- Step 2: no DMA controller model; sceDmaSend feeds VIF/GIF directly (docs/native-port.md). 4 zones ok, save test ok.
- Step 4: SIF was already native (direct RPC calls and copies on both sides); no SIF hardware is accessed.
- `GOW_IO_HIST=<s>` lists the hardware registers game code still touches (inventory in docs/native-port.md).
- tools/savetest.py default keys now confirm the overwrite prompt (it defaults to No); tools/dis.py reads the USA build.

## RESUME POINT (2026-10-11)
State: native EE (recompiled), VU1 (compiled), IOP IRX code (compiled), GS (native renderer, only one), pad/card and sound
native services. Order left (docs/native-port.md): (5) GS memory image -> native
texture store, (6) LAST: extracted game files instead of the ISO. Port KIexster's game-speed meter
(ps2recomp-game-speed.patch, GOW_DELTA_DIAG=1) before quoting fps again.
Debug env for the GS renderer: see the "night 2" section (GOW_GS_HW_STATS/_DUMP/_DUMPAT/_RTDUMPAT/_ONLY/_NODEPTH...).
Run: `python -I tools/zones.py --slots 1,2,3,4` (scale: `PS2X_GS_HW_SCALE`); save test: `python -I tools/savetest.py`.

## 2026-10-11 (evening): step 5 started, 3 agents in parallel
- Measured where texture data comes from (`GOW_GS_TEXSRC=1`, ext c522a80; docs/native-port.md step 5): PSMT8/CT24 textures
  are read from CT32 uploads, nothing from render-target readbacks or local copies.
- Agents (each in its own ext worktree, branched from c522a80, merge into gow-usa-kl after checking):
  agent/texstore (PS2Recomp-kl-present): native texture/CLUT store replacing GSCpuBackend in the renderer;
  agent/gsregs (PS2Recomp-kl-vu): GS privileged registers (CSR/PMODE/DISPFB/DISPLAY) as native display state;
  agent/speedmeter (PS2Recomp-kl-ee): KIexster's game-speed meter (GOW_DELTA_DIAG) + zones.py column.
- Zones on main (port/texsrc/20261011_203828): slot 1 60 fps, slot 3 30 fps, both ok.
- Merged (ext a60ce1c, 9290b52, 567dbfa): game-speed meter, native texture/CLUT store (GSCpuBackend deleted), GS
  privileged registers as native display state (0 GS register accesses from game code, boot + Olympus).
  Merged build (port/merged5/20261012_001103, silent): slots 1-4 ok, 60/60/30/60 fps, game speed 1.03/1.02/1.00/1.02;
  savetest ok. A/B texstore vs old main on slots 1,4 (idle machine): equal fps, GS time within 3 %.
- Test runs are silent by default (`--audio` for audio tests).
- Left in step 5: palette loads from a render target still go through a readback into the GS memory image
  (syncTargetToVram, ~2.8k of 8.9k CLUT loads in Olympus). Timers: proposal in docs/native-port.md (T0 game clock,
  T2 kernel alarms). Game speed at 60 fps is 2-3 % fast (step clamped at 1/60 s? unverified).

## 2026-10-12: second round merged (ext 7f31fe8, 9d9b312, 7a9a96b)
- CLUT from a render target is read on the GPU; no render target is ever read back into GS memory (the case does not
  occur in zones 1-4: the earlier "2.8k loads" was a false count). GS memory holds only the game's uploads.
- Game speed exact: the guest clock is paced to wall time within each field (15 pacing points per field in
  EeScheduler); the 2-3 % excess at 60 fps came from the GS-wait spin running guest time ~10x fast (docs/performance.md).
- Timer 2 native (DelayThread on the scheduler). T0/T1 still read through the timer model: needs the recompiler to turn
  constant-address timer COUNT loads into native clock calls (docs/native-port.md "EE timers").
- Merged main (port/merged6/20261012_021137): 60/60/33/60 fps, game speed 1.00 in all zones, no image warnings vs
  merged5, savetest ok.
- GitHub: github.com/Waffle565/God-Of-War-Native-Port (main = this repo, runtime = ext gow-usa-kl); README status map
  from docs/status-map/data.toml (tools/status_map.py). Push only when the user asks.
- Next: T0/T1 via the recompiler (USA regeneration + full rebuild), then step 6 (extracted files instead of the ISO).

## 2026-10-12 (night): autonomous mode (user asleep)
- User order: work without questions; decisions and blockers are written here. Task order: T0/T1 timers via the
  recompiler -> step 6 extracted disc files -> Cliffs 60 fps -> FMV/IPU native -> visual bugs from zone captures ->
  anything else still emulated. Merge gate: zones 1-4 ok vs latest merged baseline, fps not lower, game speed 1.00,
  savetest ok. Push main + runtime to "native" every 2 h and before finishing.
- Running (forks, branched from ext 7a9a96b): agent/t01clock (PS2Recomp-kl-vu), agent/discfiles (-present),
  agent/cliffs60 (-ee). Baseline: port/merged6/20261012_021137 (60/60/33/60, speed 1.00).
- 03:5x: agent/cliffs60 done (Cliffs 33 -> 60 fps, row-run GS uploads); merged into main as 34d35ff, gate running
  (with --iso, because the disc-files tool change is not on main yet). agent/discfiles done (extracted files, ISO
  only with GOW_ISO; disc-usa already complete, nothing extracted); merge gate after cliffs60's.
  New forks: agent/fmv (FMV/IPU native, -ee), agent/visual (visual bugs from captures, -present).
- Visual defects from the zone captures (fork agent/visual, 2026-10-12; reference: PCSX2 Desert frame port/pcsx2_walk1.png):
  1. **Character shadows missing** (Kratos has a ground shadow in PCSX2, none in port/merged6/20261012_021137/zone_slot2):
     the shadow passes invert the Z memory (full-screen CT24 colour draw at FBP == ZBP, Cs - Cd with white), draw the
     G-plane shadow mask with ZTST GEQUAL and invert back; our GL depth never saw the inversion, so the mask failed
     everywhere. FIXED (inversion tracked per Z buffer; port/visual_shadow/20261012_044040 shows the shadows).
  2. **Line primitives skipped** (~10/frame in the Desert: sand streaks, GOW_GS_HW_STATS skippedPrim): FIXED (drawn as
     one-pixel quads, skippedPrim=0).
  3. Top row of every capture is darker grey: the CRTC merge of the two read circuits (circuit 1 one line lower) blends
     row 0 with the black background, as the hardware does (hidden by TV overscan). Not a defect, left as is.
  4. Kratos looks washed-out/orange near light shafts (slot 2 capture 2): seen in some runs only, changes with timing;
     confirmed against a matched PCSX2 frame (port/kt_match.png: PCSX2 port/kt_pc_c2.png vs ours, Desert, 2.2 s into the walk):
   ours draws the ground dust far too bright/orange over Kratos and the light-shaft area. Bisected (fork agent/kratostint,
   ext 5a372d5, GOW_GS_HW_SKIPTBP): skipping the draws textured from tbp 0x39D0 (two ~690-vertex flat-shaded tristrips,
   T8 + CLUT 0x3C90 CT32, TFX modulate TCC=1, ALPHA Cs*As+Cd, ZTST GEQUAL, ZMSK, vertex rgb <= 82, a <= 39) removes the
   orange entirely; skipping the haze sprite (tbp 0x3980, (Cd-Cs)*Ad+Cs) does not. Depth is consistent (dust z 0x806D18 >
   Kratos 0x8054xx, so the dust is legitimately in front); Kratos passes its alpha test (GOW_GS_HW_FAILTINT). So the
   brightness of these additive draws is wrong: next suspects are the CLUT 0x3C90 alpha / colours (GOW_GS_HW_TEXDUMP)
   and the flat-shaded per-triangle colour (kick vertex).
   **Narrowed (fork B4, ext agent/kratostint): not the GS renderer.** PCSX2 single-frame GS dumps of the Desert (save
   states 07/08/09, standing and walking: ref/pcsx2/snaps/*SCUS-97399_20261012{100034,100055,100115,103129,103151}.gs,
   parsed by a per-draw summary script) give, for the same draws: identical dust state (prim 0x154, TFX 0, TCC 1,
   ALPHA 0x8000000048, TEST 0x5360B, vertex rgb max 82, a max 39) and a grey-noise CLUT with alpha 0x80 like ours
   (GOW_GS_HW_PALDUMP). The difference is geometry: on the PS2 the dust is ONE ~1060-1100-vertex strip at Z
   0x8010xx-0x8024xx, always behind Kratos (Z 0x802C00-0x803036 in all five dumps: the camera keeps a fixed distance),
   so ZTST GEQUAL hides it on Kratos. Ours draws TWO ~690-vertex strips spanning huge screen extents (-847..2211 px)
   with Z 0x80F2C8-0x84FF06 (at the camera), and our Kratos Z is 0x8056xx (walking) / 0x80C2xx (zone start); our
   world Z range is also much wider (0x803D-0x831B vs PS2 0x8008-0x8026), and Kratos looks larger in our captures.
   => the camera/projection (or the dust emitter placement) computed by game code differs from the PS2 in the Desert.
   Not the 16:9 patch (Kratos Z identical with the widescreen data patch off). Next: compare the camera/projection
   inputs (VU1 microprogram constants: the matrix + Z scale/offset the EE uploads per frame) between PCSX2 (PINE reads
   or an EE RAM dump from a save state) and ours at a matched state; suspects: EE camera code (frame-delta or rand
   driven), VU0 macro ops in the camera path. Open.
   Side finding: the game's `rand` (0x28C0C8: 32-bit LCG x*1103515245+12345 on the reent struct at *(0x2A4294)+0x58,
   returns 31 bits) is replaced by a runtime stub returning `std::rand() & 0x7FFF` (15 bits): every caller that
   scales by 2^31 gets almost no randomness (noise palettes, particles). Fix tested in agent/kratostint: drop the
   `rand@0x0028C0C8` stub from port/usa/recomp*.toml so the game's own rand runs (one regenerated file,
   port/output-usa-rand/sub_0028C0C8_0x28c0c8.cpp; ps2_recompiled_stubs.h keeps a harmless duplicate declaration).
   It does not fix the dust.
   **Camera hypothesis refuted (fork B5, matched states):** the PCSX2 states 07-09 are at a different Desert spot.
   At the same zone start (same card, PCSX2 loaded via PINE) the camera object 0x75CD70 matches ours: projection
   0x100/0x280 identical except the 16:9 y scale, camera parameter +0x3A8 = 37000 and +0x1B8 = 370370 in both, and
   it switches to 16500 when walking out in both (0x125BE0 copies it from the active region object, +0x39C = changed
   flag). A PCSX2 GS dump at that zone start (ref/pcsx2/snaps/*20261012113302.gs) has the same per-texture Z ranges as
   ours (38e0 80ac16-80ba2c vs 80aad7-80b8cd, 39e0 808588-808ac9 vs 80859b-8089b7) and the dust (39d0) at the
   camera too (80ff3e-85d4d4, rgb 9, a 16; ours rgb 7, a 13). Only near differs slightly (+0x384: -10.0049 vs -10.0).
   A PCSX2 burst during the walk out of the save room (port/b5/pcsx2_walk_burst.png, 0.4-3.9 s) shows the dust over
   Kratos's lower body on the PS2 too at ~1.8 s, gone by ~2.5 s, when the dust becomes the far 1080-vertex strip
   (*20261012120341.gs: Z 8019a3-8023fb). So the orange in our 2.2 s capture is mostly this transition caught at a
   different instant; what may remain is a brightness/timing difference, not measured frame-exactly. Lower priority.
- 05:2x merged and verified (ext 34d35ff cliffs60, then discfiles + t01clock as 52630c6): port/merged8/20261012_050655:
  60/60/60/60 fps, game speed 1.00 all zones, extracted files (no ISO), savetest ok. Timers: 0 accesses from game code.
  Decision: discfiles and t01clock were gated together (one full 35-min rebuild instead of two); both had passed
  their own 4-zone runs. Push to "native" was held ~45 min past the 2 h mark to push a verified state.
- 06:5x: agent/visual merged (ff3cf11: character shadows via Z-inversion tracking, line primitives). Its gate
  (port/merged9) had slot 2 at 55.5-60 fps while other forks ran; GS time slot 2 +13 % (shadows now drawn).
  agent/residual merged (8820bd0: EE DMA registers -> native DMA service via the recompiler; 27 regenerated files).
  Decision: one gate for both (full rebuild needed anyway); slot 2 at 60 fps in that gate decides visual.
  agent/fmv hit its turn limit; resumed to commit and verify.
- 07:5x: main's link failed (exe locked): a test runner orphaned at 06:50 when I stopped the slot-2 re-run shell
  (TaskStop kills the shell, not the game it started). It also kept every "wait for an idle machine" loop waiting for
  an hour. Killed it; gate re-run. Lesson: after stopping a test shell, check `Get-Process ps2EntryRunner` and close
  the runner it started.
- 08:0x: agent/fmv partial (c9870e2): libmpeg2 0.5.1 vendored (GPL-2+, portable) instead of FFmpeg, mbcount bound
  (fixes the heap overwrite that showed as garbage), RT-sampling fix; intro still black (blocker in docs/fmv.md:
  how .m2 pictures reach TBP 0x2800). Not merged yet (feature incomplete); a new fork continues on the same branch.
- 08:4x VERIFIED (port/merged10/20261012_081448, main ext 8820bd0 = visual + residual): 60/60/60/60 fps (single windows
  59.4-59.8 while forks ran), game speed 1.00/1.00/1.01/1.00, savetest ok. Desert holds 60 with shadows drawn.
  Remaining EE hardware access: one VIF1 CHCR read/write at boot (dynamic address, served by the DMA service).
- 09:4x: agent/fmv (1a7b5fe): the intro movie plays to the end and the game continues (stream callbacks run nested
  as libmpeg expects -> real picture size; GS: TEST.ZTE=0 means no depth test; sceMpegIsEnd flag). Movie audio still
  silent: a fork continues on the same branch. Plan: merge 1a7b5fe after the scratchpad gate (merged11), own gate.
  Scratchpad A/B slot 4 (main vs fast path, 2 runs each): EE 2750/2774 vs 2739/2702, 60 fps, speed 1.00 -> merged
  (61497cb), full rebuild + gate running.
- New-game test (fork agent/newgame, tools/zones.py --slots 0): title -> New Game -> Hero -> Aegean Sea ship works;
  fights, blade trails, HUD, death screen render correctly (port/newgame/ng1, ng2 sheets); no missing functions,
  no errors. Open: ship start ~43 fps (worker job VU1+GS serial, docs/performance.md "Aegean Sea").
- 10:4x VERIFIED scratchpad fast path (port/merged11/20261012_101724, ext 61497cb): 60/60/60/60, speed 1.00 x4,
  savetest ok. Merged FMV video (e21f2f2 = agent/fmv 1a7b5fe; libmpeg2 vendored, FFmpeg off by default); gate running.
- ~10:50-11:00: the account's usage limit stopped all three forks (movie audio, Kratos tint, new-game test) mid-task;
  resumed at 11:00 after the reset. Movie audio finding so far: the audio data is noise-like (wrong format/layout).
- 11:1x: Kratos tint is not a GS bug: vs PCSX2 GS dumps the draw state and palette match, but our depth/geometry
  differ (world Z 0x803D-0x831B vs PS2 0x8008-0x8026; the dust lands in front of Kratos) -> camera/projection
  upstream of the GS. New fork on it. Side bug found: `rand` (0x28C0C8) is stubbed with std::rand() & 0x7FFF
  (15 bits) instead of the game's own 31-bit rand; fix = drop the stub, regenerate that function
  (port/output-usa-rand); to be merged with the camera fix or alone after its gate.
- 12:0x VERIFIED FMV video (port/merged12/20261012_114149, ext e21f2f2): 60 x4, speed 1.00 x4, savetest ok.
- 12:1x: Kratos tint (defect 4) is mostly timing, not a bug: at a matched state camera, projection and depth match
  PCSX2 (PINE + GS dump); the PS2 also shows the save-room exit dust over Kratos for ~0.7 s. Low priority now.
  rand fix (31-bit game rand instead of the 15-bit stub) to be merged after the current gate.
- 12:3x VERIFIED new-game texture row decode (port/merged13/20261012_115916, ext 9de5084): slots 0-4 all 60 fps,
  speed 1.00, savetest ok. zones.py slot 0 = new game (ship start). Merged GS debug tools (611993b) and the rand
  fix (runner sub_0028C0C8 regenerated as the game's own function; port/usa/recomp*.toml: rand stub commented out);
  gate running. New fork: agent/pipeline (ship start 43 fps: VU1 + GS frontend serial in one worker job).
- 12:4x VERIFIED rand fix + GS debug tools (port/merged14/20261012_122017, ext 611993b + runner sub_0028C0C8):
  slots 0-4 60 fps, speed 1.00, savetest ok. Slot 0's last capture differs (43 > 40) only because the fight plays
  out differently with the game's own rand (both frames render correctly). docs: runtime-changes/elf: rand no
  longer stubbed.
- 13:5x VERIFIED movie audio (port/merged15/20261012_131851, ext 0ad6d2a): zones 0-4 60 fps, speed 1.00 (slot 3
  1.01 mean), savetest ok; Desert audio A/B before/after (BVOL change touches all sound): 195 s each, mean RMS
  4971 vs 4980, correlation 1.0, no silent windows. The intro movie plays to the end with sound.
- 15:0x: agent/pipeline (ee6ed82): GS frontend on its own stage thread, pipelined with VU1; ship start (new game)
  36-42 -> 60 fps; PS2X_GS_PIPELINE=0 = old path. Merged as 832a7b4, full rebuild + gate running. Movies with the
  pipeline are checked by the movies fork. tools/run.sh and port/newgame/run.sh killed every runner by image name
  (taskkill /IM), which killed other tests' runs; now they end only their own process.
- 15:2x VERIFIED VU1/GS pipeline (port/merged16/20261012_150523, ext 832a7b4): zones 0-4 60 fps, speed 1.00,
  savetest ok. User back ~15:15 ("enable the audio"): test runs play sound again; autonomous loop ended.
- 16:2x VERIFIED movies at real speed (port/merged17/20261012_161100, ext 1fc7911): zones 0-4 60 fps, speed 1.00,
  savetest ok (sound on). Intro, Semo02, Semo05 play at real speed with sound (A/V: audio ~0.1 s behind, constant).
  play.cmd now plays the movies (GOW_SKIP_FMV removed); tests still skip them. Unchecked: a01mp05 (ship trigger
  not reached by the script), BONUS movies.
- 16:4x: user order "do all except the Switch build, the PC port must be perfect". Three forks from ext 1fc7911:
  agent/newgame2 (new game past the ship start, a01mp05 trigger), agent/movies2 (BONUS movies, IPU/DMA ch3/4
  register stores in the movie path, Kratos tint frame-exact), agent/vibration (DualShock actuators -> native
  gamepad rumble, the 9 IOP startup register stores). Each merges after the usual gate (zones 0-4, savetest).
- 21:3x VERIFIED particle fix + vibration (port/merged18/20261012_212017, ext c25562c + merge of agent/vibration
  e8aa85d): zones 0-4 60 fps (slot 3 59.0-59.8 / speed 1.02 while 3 forks built; re-run pending), savetest ok.
  User report "shadows and particles broken": the torch embers drew as 4-petal stars and the ship's water splash as
  star sprites. Cause: PACKED ST wrote its Q word straight into the vertex; on the GS it only latches Q until the
  next PACKED RGBAQ (GIF tags reset it). The heat-haze fans (tbp 0, prim 0x5d) send ST,XYZF2 vertices with junk Q
  (8.4e6, 0.0067, 1e-38...), so every triangle sampled the frame buffer far off. Torches now match PCSX2.
  Vibration: gowVibGetProfile reports actuators, gowVibSetActParam -> PSPadBackend::setActuators (XInput on
  Windows); 92 updates logged in a new-game fight; no real pad tested yet. IOP: 0 hardware accesses.
  Open: shadows (fork agent/shadows: Olympus floor rectangle, black blobs in slot 4/3), souls unchecked (no orb
  pickup in the scripted runs), audio clipping (user report; present since the native sound engine, intro movie
  62 clipped samples/s), visual audit list in docs/visual-audit.md.
- 22:3x audio crackle fixed (ext 2342429, user report "the audio is clipping"): the output dropped ~30 % of the
  samples on the title screen and menus. The sound engine's sample clock followed the IOP's own cycle count, which
  runs ahead of the EE (a dbcman RPC at 0x12BCC costs ~10 M IOP cycles/s on the menus); it now follows the cycles the
  EE granted. The menus' guest clock is still ~3.7 % ahead of the wall clock (open: EE cycles per field above the
  VBlank period there); the output absorbs that with up to 5 % faster interpolated playback instead of cutting
  sample blocks. Desert: 0 drops, 0 saturated samples, 0 jumps. docs/sound.md. Merged agent/movies2 (all 14 BONUS
  movies at real speed with sound; movie path without hardware registers); combined gate pending.
- 2026-10-12 late / 10-13: Cliffs freeze in combat fixed (ext 60669d6: the shadow-volume COLCLAMP=0 counting is one
  fixed-function reverse-subtract/add draw instead of per-triangle draws); edge line along the top and left fixed in
  the present pass (ext acdb310, clamp to source row/column 2 at 2x; the upstream pass leaving row/column 0 unpainted
  is still open); agent/newgame2 merged (ghost overlay after a01mp05: a target overwritten by a depth write is no
  longer a texture source); scripted tests ignore a connected gamepad (stick drift loaded wrong slots). Gate
  port/merged20: Cliffs, Olympus, slot 4 60 fps, speed 1.00. Chest glow colour confirmed normal by the user.
- 10-13: character shadows, root cause found (agent/shadows2, merged into gow-usa-kl): the native VU1 blocks made
  MAC/clip flags visible too early at block boundaries, so the culling loop gave both shadow-volume halves the same
  ADC bits and every count netted to zero. The exact fix (flag latency and pipeline state across blocks) is merged but
  opt-in (`GOW_VU1N_FLAG_LATENCY=1`): it draws the shadows (gate port/shadows2/gate_latency, zones 0-4 60 fps, savetest
  ok) but costs 2x VU1 time (heavy Olympus spot ~39 fps vs 56). Default unchanged. Fork agent/shadows3 profiles and
  makes it cheap enough to be the default. docs/vu1-native-flags.md.
- 10-13 ~09:00: character shadows ON by default (agent/shadows3 merged): flag latency across native VU1 blocks is the
  only model, cost ~+23 % VU1 time vs the old model (block history ring, flags computed only when read). Gate
  port/merged22/20261013_085616: zones 0-4 60 fps, speed 1.00, savetest ok; soft shadows under Kratos in Desert and
  slot 4, no wedges. Switch GOW_VU1N_FLAG_LATENCY removed. Profiler: tools/sample_prof.py (link with /MAP).
- 10-13 ~13:00: user playthrough with a DualShock 4: rumble verified (USB; direct HID output reports, ext cb896df).
  User found a combat freeze (ship after the Hydra fights, Cliffs within a minute of a fight): use-after-free in
  the UI timeline player of the enemy-meter HUD movie (docs/game-internals.md). Contained by a heap guard in
  gow_overrides.cpp (double deletes ignored, deleted children dropped, `[gow-heapguard]` log names the early delete);
  root cause open until a user log with the guard lines. Merged agent/visual3 (intro movie fills the picture,
  sprite sampling clamped: no RGB lines at the movie edges). Gate port/merged24/20261013_125553: zones 0-4 60 fps,
  speed 1.00, savetest ok. Hydra-grab fog not reproduced (needs a save before the fight).
- 10-13 ~13:30: merged agent/edge2 (vertices shifted by half a host pixel: no stale edge rows/columns, the bright
  bar along the top/left/top-right is gone). Gate port/merged25/20261013_131639: zones 0-4 60 fps, speed 1.00, savetest
  ok; first 6 rows/columns of every capture follow the scene.
- 10-13 ~15:30: vertical bars / notched text (user) fixed: merged agent/text (sprite UV clamp open on sides shared with
  the previous strip). Merged tree identical to the tested branch; gate port/text/gate/20261013_152149 (zones 0-4 60 fps,
  savetest ok). Running: agent/warp (level warp, Hydra fog, heap-guard root cause), agent/movies4 (every movie, broken audio).
- 10-13 user decisions on the remaining list: SKIPPED Bluetooth rumble, Kratos tint, Cliffs camera clipping (likely
  original), the intro movie's darker last row; LATER: top edge row 0. Ask the user before starting the Switch build.
  Remaining: archers-movie audio (agent/movies4), combat freeze root cause (needs a meter fight log with the fixed
  guard), full levels.py run (108 zones, ATHN01E), new game past the trap door, menu guest clock 3.7 % fast.
- 10-13 ~18:45: gate port/merged26/20261013_182214 (level warp overrides, fixed heap guard, audio device selection; sound
  on the Oculus test device): zones 0-4 ok 58.8-60 fps, speed 1.00-1.02, savetest ok, 0 heap-guard reports.
- 10-13 ~19:30 user test (port/usertest1/play6.log): Cliffs combat no longer freezes, and the heap guard logged 0
  reports in the whole session, so the original use-after-free did not recur at all (not just caught). Archers/captain
  movie audio still broken: loopback recording port/usertest1/live_audio.wav shows the movie at full scale (hard
  clipping) with hundreds of sample jumps per second, gameplay before/after clean; sent to agent/movies4.
- 10-13 ~20:00: merged agent/movies4 (movie ends at the video sequence end: A01MP01 froze after the second Hydra
  fight with its last sound buffer looping; tools/movies.py, 45/53 story movies ok; P04MP05 stops after ~180
  pictures (open, also on main); SEMO08 drift to recheck). A01MP02 (captain) still clips: a loud group-8 sound plays
  under it on the real path (mask 0x7EFF leaves group 8 on); next: voice dump at its real start. User: SKIP the
  scripted new game past the trap door (the user plays those parts).
- 10-13 ~23:00: user ordered the Nintendo Switch test port now, everything else on standby (agent/menuclock, agent/levels
  told to commit WIP and stop). A01MP02 cause located (docs/fmv.md Open): L/R swap + 123-sample misalignment of the
  movie PCM on the real path. Merged agent/movies5 (P04MP05 720/743 pictures); its gate not yet re-run on main.
- agent/levels on standby (port/levels/STATE.md): ATHN01E 4/4 single-warp boots ok (the old crash was a chained warp,
  a test-tool limit); ATHN01D (ship deck, save altar) 37.6-40.4 fps alone, VU1 worker saturated (open, needs a VU1
  profile); ATHN03A / PAND04G low fps measured with another runner (recheck alone); movie rechecks (SEMO08,
  P06MP01, SATINTRO, SEMO01-04) not run.
- agent/menuclock on standby, fix READY to merge (port/menuclock/STATE.md): title, main and pause menus and gameplay
  already run at 1.000 (the 3.7 % of 10-12 is gone); only Load Game ran at 1.08: recompiled loops were charged a flat
  32 cycles per iteration, so the card-command byte copies cost 0.9 ms of guest time per frame. Recompiler fix
  027ce16 (loops charged their real size, max 32): Load Game 1.02, gate port/menuclock/gate/20261013_222345 ok. Merge
  = regenerate (port/usa/recomp-clock.toml or port/output-usa-clock, 1689 files) + full rebuild ~40 min + overrides
  patch + docs; after the Switch test port. The captain movie runs at exact speed (33.07 s in 33.07 s): its broken
  sound is not a clock problem.
