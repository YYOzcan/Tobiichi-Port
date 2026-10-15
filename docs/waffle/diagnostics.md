# Diagnostics

All are opt-in environment variables (added by us; implementations noted).

| Variable | Output | Where implemented |
|---|---|---|
| `PS2X_HEARTBEAT=<s>` | every s seconds: debug PC/RA, EE cycle, **live** context PC + regs (v0 v1 a0-a3 s0-s3 ra), EE threads (status/wait), IOP cycles/modules/threads/RPC servers/services/diagnostics | ps2xRuntime/src/main.cpp — no longer in the runtime (2026-10-13) |
| `PS2X_HEARTBEAT_PEEK=[iop:]addr:len,…` | hex dump of EE RAM (or IOP RAM with `iop:`) each heartbeat | main.cpp — no longer in the runtime (2026-10-13) |
| `PS2X_TRACE_CALLS=hex,…` | wraps listed EE functions: `[call] addr(a0..a3) ra=` / `[ret ] addr -> v0=` | main.cpp (replaceFunction; original found via ctx->pc) — no longer in the runtime (2026-10-13) |
| `PS2X_TRACE_RPC=1` | each RPC served by an IRX: sid, fn, mode, 11 send words, 4 reply words; plus `[sifdma]` IOP→EE DMA (src, dst, size, 4 words) | ps2xIOP iop_rpc.cpp |
| `PS2X_TRACE_IOP_IMPORTS=1` | every IOP import call `lib:ordinal a0 a1 a2 ra` (very verbose, ~400k lines/30 s) | ps2xIOP iop_emulator.cpp dispatchImport |
| `PS2X_TRACE_CDVD=1` | IOP cdvdman calls (`ord=6` = sceCdRead lsn/count/dst) | ps2xIOP iop_cdvd.cpp |
| `PS2X_TRACE_FILEIO=1` | EE fioOpen/fioRead (failed opens always logged) | ps2xRuntime Syscalls/FileIO.cpp |
| `PS2X_TRACE_SIO2=1` | per SEND3 entry: CTRL, FIFO-out fill, port, len, connected, command, fifo/dma, reply, RECV1; DMA ch11/12 setups | ps2xIOP iop_sio2.cpp |
| `PS2X_TRACE_EVF=1` | IOP event flags: set/clear/wait(now/block)/wake with bits and thread id ("thread -1" = no current thread) | ps2xIOP iop_kernel.cpp |
| `PS2X_IOP_WATCH=hex[,hex]` | every IOP guest store to those words: pc, opcode, address, value, ra | ps2xIOP iop_cpu.cpp |
| `GOW_IO_HIST=<s>` / `GOW_IOP_IO_HIST=<s>` | hardware register accesses still made by game code, EE `[io-hist] op addr pc ra n` (slow-path loads/stores, incl. scratchpad) and IOP `[iop-io-hist] op addr n`, counted for `<s>` seconds after the first access and printed once (only if accesses continue past the window); the IOP one also prints `[iop-io-first] op addr` when a register is first touched. Keep `<s>` shorter than the run (zones.py runs ~200 s: use 170). Inventory: docs/native-port.md | ps2xRuntime ps2_runtime.cpp (ioHist), ps2xIOP iop_memory.cpp (iopIoHist) |
| `GOW_GS_HW_DUMPMAX=<n>`, `GOW_GS_HW_FAILTINT=1`, `GOW_GS_HW_SKIPTBP=<hex>` | GS renderer bisecting: raise the batch-dump cap (with GOW_GS_HW_DUMPAT/DUMPALL; each batch also prints a `[gs-hw-dump-bb]` line: screen bbox, TEXA, TFX/TCC, IIP, max vertex colour/alpha, prim type, vertex Z range in buffer units `z=lo-hi`); paint alpha-test-failing RGB_ONLY fragments of textured main-target draws magenta; skip every draw textured from one block address | ps2xRuntime/src/lib/gs/gpu/gs_hw_backend.cpp |
| `GOW_GS_HW_PALDUMP=<tbp hex>` | prints the 256-entry palette (`[gs-hw-pal]`, rgba hex) and the index histogram (`[gs-hw-idx]`) of the first paletted draws textured from that block | ps2xRuntime/src/lib/gs/gpu/gs_hw_backend.cpp |
| PCSX2 single-frame GS dump | ref/pcsx2/inis/PCSX2.ini binds `GSDumpSingleFrame` to Shift+F8 (uncompressed .gs in ref/pcsx2/snaps); `tools/pcsx2_key.ps1 pcsx2-qt 119 66 -shift` triggers it, PINE `struct.pack('<IBB', 6, 10, slot)` loads a save state first (states 07-09 are Desert spots). `tools/gsdump_stats.py` / `gsdump_objects.py` / `gsdump_draws.py` (per-draw state, colour and Z ranges) parse the dump | tools/ |
| `GOW_GS_TEXCHECK=1` | every direct-colour texture decode is re-done per texel with GSSwizzle and compared with the row reader; prints mismatches and a count every 200 textures | ps2xRuntime/src/lib/gs/gpu/gs_hw_backend.cpp (decodeDirect) |
| `GOW_DELTA_DIAG=1` (+ `GOW_PERF_FRAME_PC=0x001837B8`) | game-speed meter: once per wall second `[gow-speed] frames= wall= game= speed= delta_min= delta_max=`; `game` = sum of the game's own frame step (float at 0x29C64C) over the frames (entries to vid::Flip), `speed` = game s / wall s (1.00 = real time, >1 game time runs fast, <1 slow motion). Read it before trusting any fps above 30. Idea taken from KIexster's patches/ps2recomp-game-speed.patch. tools/zones.py turns it on and reports a game-speed column | ps2xRuntime/include/runtime/ps2_perf.h (gameSpeedFrame, from guestEntry) |
| `GOW_MPEG_DIAG=1` | movies: pictures handed to the game, stream-callback registrations and call counts, the game's movie audio state per picture (989snd stream globals 0x304CEC.., audio ring read/fill/full) and audio packets queued/taken/refused; `[MPEG:sync]` every 30 pictures (PTS, wall time, audio device position, decoder stub time) and the first audio packet PTS (A/V check, docs/fmv.md) | ps2xRuntime Kernel/Stubs/MPEG.cpp |
| `GOW_MOVIE_OVERRIDE=<name>[,<name>...]` | debug: each movie load takes the next name instead of the game's (the first replaces the intro or the first menu request); with more than one name the title menu starts the next movie each time the player is idle again (tools/movies.py, docs/fmv.md) | runner gow_overrides.cpp (port/overrides-usa) |
| `GOW_SND_DIAG=1` | LIBSD: every `sceSdBlockTrans` (core input stream) and every MMIX/MVOL/EVOL/AVOL/BVOL write; the stream start also prints the audio device position | ps2xIOP src/native/iop_native_overrides.cpp |
| `GOW_AUDIO_STATS=1`, `GOW_IOP_DRIFT=1`, `GOW_SND_REGLOG=1` | sound output: requested/missing/dropped frames, highest resample rate and buffer level every ~5 s; IOP cycles granted by the EE vs advanced (with wall time) and the top IOP calls made outside `runCycles`; core volume/mix register writes. Details: docs/sound.md | ps2xIOP sound_engine.cpp, iop_emulator.cpp |
| `GOW_AUDIO=0` + `GOW_AUDIO_PCM=<file>`, `GOW_AUDIO_RAW=<file>` | muted recording: the output stream runs at volume 0 (paced and drained as when heard) and the PCM is written; the raw file holds the mix as the sound engine produces it, before the output's rate adaptation (sample-exact comparison with a source, tools/movies.py) | ps2xRuntime ps2_runtime.cpp; ps2xIOP sound_engine.cpp |
| `GOW_SND_VOICEDUMP=1` | while a movie stream plays (first 10 s, once per second) every voice still sounding (pitch, volumes, envelope, SSA/LSA/NAX) and, when a stream starts, 989snd's sound handles (type, group, flags; stream voices) - which sounds a movie's group pause leaves playing | ps2xIOP sound_engine.cpp; ps2xIOP src/native/iop_native_overrides.cpp (sdBlockTrans) |
| `GOW_SND_CALLLOG=1` | voice volume / pitch writes that change a value and KON/KOFF masks (`[snd-call]`), the game's sound-group pause/continue `0x175148(pause, mask)` (`[gow-snd-groups]`) and every direct 989snd command after the first 300 except the status poll 0x40 | ps2xIOP sound_engine.cpp; runner gow_overrides.cpp |
| `GOW_MPEG_DIAG=1` (additions) | `[MPEG:wait]` once per second while no picture is ready (end flags, demuxed bytes, CD EOF); `[gow-fmv] load <name>` for every movie the game loads; `[gow-fmv-read]` the movie's stream reads near the end of the file (0x17AFE0: asked, size, position, returned); `[gow-fmv-poll]` the movie struct words that changed, once per second while the player polls; `[MPEG:skip]` bytes skipped to resync the PSS demuxer, `[MPEG:hold]` pictures held more than 2 s for their presentation tick; `GOW_MPEG_DIAG=2` logs every stream read of a file over 1 MB | Kernel/Stubs/MPEG.cpp; runner gow_overrides.cpp |
| `GOW_GS_HW_PALDUMPMAX=<n>` | with `GOW_GS_HW_PALDUMP`: number of index-texture decodes of that block written as PGM (default 4); the palette is dumped even when it comes from the cache | ps2xRuntime/src/lib/gs/gpu/gs_hw_backend.cpp |
| `GOW_GS_HW_DISPLOG=1` | the display registers (PMODE, SMODE2, DISPFB1/2, DISPLAY1/2) each time they change, with the present number | gs_hw_backend.cpp (Present) |
| `GOW_GS_HW_DISPDUMP=<n>` | the n-th present after the displayed size changed (e.g. a movie starts) writes the whole displayed render target to `gs_hw_disp_<fbp>_<w>x<h>.ppm` | gs_hw_backend.cpp (Present) |
| `GOW_GS_HW_RTDUMPFBP=<n>` | with `GOW_GS_HW_RTDUMP`/`RTDUMPAT`: dump that render target instead of fbp 0 / 208 | gs_hw_backend.cpp |
| `GOW_MPEG_PICDUMP=<n>` | decoded picture n of each movie to `mpeg_pic_<n>.ppm` (decoder output, before the GS) | ps2xRuntime Kernel/Stubs/MPEG.cpp |
| `GOW_GS_HW_RTLOG=1` | each render target created or grown (`[gs-hw-rt] new/grow fbp fbw`) | gs_hw_backend.cpp |
| `GOW_GS_HW_XFERWATCH=<hex block>`, `GOW_GS_HW_XFERRANGE=<lo>-<hi>` | log the image transfers whose block range holds that block / whose destination lies in [lo, hi), with the first bytes of the next upload | gs_hw_backend.cpp |
| `GOW_GS_HW_EDGELOG=1` | every 300 presents: the displayed buffer's first host rows and columns before composition (edge-line artefacts) | gs_hw_backend.cpp (present) |
| `PS2X_GS_TRACE_TBP=<tbp0>` (`-2`, `-3`) | vertices drawn with that texture active; `-2` untextured triangle fans, `-3` textured fans, with the vertex colour | ps2xRuntime/src/lib/gs/gs_frontend.cpp |
| `GOW_BONUS_MOVIE=<NN>` | plays BONUS movie NN through the Treasures-menu path (docs/fmv.md) | runner gow_overrides.cpp |
| `GOW_VIB_LOG=1`, `GOW_PAD_BT_RUMBLE=1` | every rumble command of the game (`[gow-vib] small= large=`); rumble also for DualShock 4 / DualSense pads connected by Bluetooth (off by default: the first output report switches the pad to its extended input report, which DirectInput may not read) | runner gow_overrides.cpp; ps2xRuntime/src/lib/ps2_pad_rumble_win.cpp |
| `GOW_WARP=<zone>[;<zone>...]`, `GOW_WARP_DELAY=<s>` (default 0.5), `GOW_WARP_STAY=<s>` (default 60) | debug level warp: `GOW_WARP_DELAY` seconds after gameplay starts, the game's own script builtins LoadForWarp(zone) + Warp() load the zone and move Kratos to its warp point; after `GOW_WARP_STAY` seconds the next zone. Logs `[gow-warp] request/arrived/timeout/done` and writes two captures per zone (`gow_warp_<n>_<zone>_<k>.ppm`, 5 s after arrival and half way). Zone names = WAD names of GODOFWAR.TOC without ".WAD" (e.g. `PAND04G`). One warp per boot is reliable; chained warps can crash or hang (docs/game-internals.md) | runner gow_overrides.cpp (gowWarpPoll, called after the pad read) |
| `GOW_FLASHQ_WATCH=<hex block>` | Flash UI action-queue trace: every queue append, every drain whose queue holds that block (with the node list), and new/delete of that block. For the heap guard's "second delete ... at=0x1461ac" | runner gow_overrides.cpp |
| `GOW_THREAD_WATCH=<s>` | every <s> seconds a host thread prints the EE threads (status, wait reason, pc, ra) and the movie player struct words `*0x304F20` +0xE8..+0x15C (video/audio rings, flags). Works when the guest is blocked for good (no frames, no pad polls, where `GOW_THREAD_DUMP` never fires). Wait reasons: 1 sleep, 2 semaphore, 3 event flag, 4 VSync, 5 external, 6 MPEG | runner gow_overrides.cpp (applyGowOverrides) |
| `GOW_CD_TRACE=1` | every IOP `sceCdRead`: lsn, sectors, IOP destination, result (`[cd-read]`) | ps2xIOP src/emulator/imports/iop_cdvd.cpp |
| `GOW_MPEG_DIAG=1` (addition) | `[MPEG:refused] callback type len`: a stream callback refused a packet (its ring is full; the demux stops there) | ps2xRuntime Kernel/Stubs/MPEG.cpp |
| `GOW_PLAYER_TRACE=1`, `GOW_GOD_MODE=1` | once per second Kratos's position, game state and movie state (steering scripted runs); test runs only: Kratos's health refilled every poll | runner gow_overrides.cpp |

Always-on: `[gow-heapguard] <what> object= at= freed-by=` (runner gow_overrides.cpp heap_guard): a double delete or a deleted child of the UI timeline player was dropped instead of crashing; the first three also dump the last guest branches. `freed-by` names the early delete (docs/game-internals.md).

`GOW_PLAYER_TRACE=1` now also prints `zone=<current zone name>`.
`tools/levels.py`: level check. For each zone, one runner boot: new game (as zones.py slot 0), warp
0.5 s after gameplay starts, stay `--stay` seconds (default 30) moving and attacking with GOW_GOD_MODE, then judge:
arrived or timed out, load time, fps and game speed while there, `[guest-branch:missing-target]`,
`[gow-heapguard]`, the zones.py error patterns, two captures. `--zones all` = the 108 zone WADs of the TOC
(~1 min each); `--batch N` chains N warps per boot (faster, but see the limits). `--exe-dir` selects the runner.

Always-on logs we added: `[SIF module] load-failed/load-unhandled` (RPC.cpp), `fioOpen failed:`.

## Notes
- `m_debugPc` (heartbeat "pc=") only updates at dispatch points and can be stale; the `live pc=` line samples the
  running context (generated code writes ctx->pc per instruction) and is reliable. Sample several times.
- IOP `[import]` lines go through the host log (stdout) while EE `[call]` lines go to stderr; their relative
  order in the log file is not reliable. `[rpc]` lines are printed **after** the server function returns, so the
  imports printed just before belong to that request.
- IOP printf now formats arguments (before: raw "%d"). Old logs (before 2026-10-09) show raw formats.

## Methods that worked
- **Find a hang**: heartbeat live pc → `tools/dis.py` → identify loop → find who sets the awaited flag
  (`grep -l -- '-0xNNNN(' port/output/*.cpp` on the gp/lui-relative offset).
- **Backtrace**: peek the stack (`PS2X_HEARTBEAT_PEEK=1FFFD00:300`), keep words in .text whose word−8 is a `jal`
  (return addresses).
- **Global value**: peek it; initial value: read the ELF at vaddr − 0xFF000.
- **IOP module internals**: `tools/irxdis.py`, import tables (magic 0x41E00000, name at +12, stubs `jr ra; ordinal`),
  call-site arguments in the import trace.
- **Wrong data?** compare peeked EE buffers against the extracted PAK bytes (TOC gives sector offsets).

## PCSX2 as reference (2026-10-09)
- `ref/pcsx2/` portable (portable.txt, inis/PCSX2.ini: BIOS SCPH-70004 v12 PAL, PINE on slot 28011, file log in
  logs/emulog.txt). Boot: `ref/pcsx2/pcsx2-qt.exe -portable -batch -- "<iso>"`. Retail game runs at full speed.
- `tools/pine.py ADDR LEN …` reads EE memory live (`--status`). PINE cannot read IOP RAM.
- IOP RAM / registers / GS state: save a state (PINE opcode 9, slot 1 → `ref/pcsx2/sstates/*.p2s`, a zip with
  iopMemory.bin, eeMemory.bin, GS.bin, …) and extract with 7-Zip. `tools/irxfind.py iopMemory.bin X.IRX` finds where
  PCSX2 loaded each module, so module-relative offsets can be compared with ours.
- Method that found the controller bug: compare the same EE buffer (PINE) and the same IRX-relative IOP structures
  (save state) between PCSX2 and our port, then watchpoint (`PS2X_IOP_WATCH`) the field that differs.

## Graphics diagnostics (2026-10-09)
- `PS2X_GS_RECORD=<out.gs> PS2X_GS_RECORD_TEMPLATE=port/pcsx2state/GS.bin PS2X_GS_RECORD_START=<vsync>
  PS2X_GS_RECORD_FRAMES=<n>` → PCSX2 dump; open with `ref/pcsx2/pcsx2-qt.exe -portable -batch -- <out.gs>`.
  The template is GS.bin from a PCSX2 save state (VRAM at offset 428 is replaced by ours). VSync rate here is
  ~4.5/s at boot; the title is around vsync 190 (~80 s). Colours in the replay are off (CLUT state), geometry is
  faithful.
- `PS2X_FRAME_DUMP=<file.ppm>` (+ `python -I tools/ppm2png.py in.ppm out.png`): the runtime's own frame; use this
  instead of window screenshots when the display may be asleep.
- `PS2X_VU1_DUMP`, `PS2X_GS_DUMP` + `tools/vramdiff.py` for VRAM page maps against PCSX2's GS.bin.
- `PS2X_EE_WATCH=<hex addr>[:<hex len>]` (Windows): logs `[eewatch] write ee <addr> pc=<guest pc> ra=<ra>` for every
  store into that EE RAM range (page guard + single step; ee_watch.cpp). Found the bone-matrix writer this way.
- `PS2X_EE_DUMP=<file>`: 32 MB EE RAM at every heartbeat; compare with eeMemory.bin from a PCSX2 save state
  (PINE opcode 9 saves to a slot) — same ELF, so static/heap addresses usually line up.
- `PS2X_GS_PLAY=<pcsx2 dump.gs>` (+ `PS2X_GS_PLAY_OUT`, `PS2X_GS_PLAY_VRAM`): replay a real-game PCSX2 GS dump
  through our GS; `tools/gsfb.py VRAM FBP FBW W H out.png` decodes a framebuffer from VRAM;
  `tools/gsdump_objects.py a.gs b.gs` compares per-texture vertex extents of two dumps.
- `PS2X_VU1_TRACE_BAD=<file>`: VU1 state at the start of the first microprogram whose kicked packet has saturated
  (0 / 0xFFFx) drawn vertices.

## EE differential tester (2026-10-09) — the most useful tool so far
- PCSX2's R5900 interpreter (R5900OpcodeImpl.cpp, MMI.cpp, FPU.cpp, R5900OpcodeTables.cpp, branch code from
  Interpreter.cpp; GPL-3.0+) lives in ps2xRuntime/src/lib/ee_ref with shims; VU0 macro ops use the embedded PCSX2
  VUops (vu_pcsx2/pcsx2_vu0_cop2.cpp). Syscalls, COP0 and I/O stop a reference run ("not comparable").
- `PS2X_EE_DIFF=<hex>[,...]` (first PS2X_EE_DIFF_MAX calls, default 3) or `PS2X_EE_DIFF=all` (every function's
  first call; only mismatches + a tally are printed). Each call: snapshot CPU + 32 MB RAM + scratchpad, run our
  recompiled function, re-run from the snapshot on the interpreter until it returns to $ra with the entry $sp,
  compare GPRs (128-bit), FPRs, VF regs and every word the reference wrote. `PS2X_EE_DIFF_STEPS` limits steps.
- Expected mismatches: functions replaced by runtime stubs (gow.toml `stubs`: rand, printf/fs/sif/mpeg …) and
  their callers; upper 64 bits of GPRs in a few places. Anything else is a recompiler bug.

## PCSX2 driven automatically (2026-10-10) — ground truth for the USA build
- ref/pcsx2/inis/PCSX2.ini now has `[MemoryCards]` (slot 1 = memcards/Mcd001.ps2 = copy of ref/saves/Mcd002.ps2;
  old card kept as Mcd001.ps2.bak; ini backup PCSX2.ini.bak) and `[Pad1]` keyboard bindings: Cross=K, Circle=L,
  Square=J, Triangle=I, Start=Return, Select=Backspace, left stick W/A/S/D, D-pad = arrows (arrows do NOT work with
  posted messages — extended keys; use the stick keys in menus).
- Boot from PowerShell (bash paths fail): `Start-Process ref\pcsx2\pcsx2-qt.exe -ArgumentList '-portable','-batch',
  '--','"<...>\iso-usa\God of War (USA).iso"'`. Drive it with `tools/key.ps1 pcsx2-qt 0 <holdMs> <vk> <scan>`
  (K = 75 37, I = 73 23, S = 83 31, Return = 13 28), screenshots with `tools/shot.ps1 pcsx2-qt <png>`, game state via
  `tools/pine.py 29E560 4` (11 = gameplay). Load desert save: Return, I (back if New Game), S, K, then K until state 11.
- Save state via PINE: send `struct.pack('<IBB', 6, 9, <slot>)` to 127.0.0.1:28011 → ref/pcsx2/sstates/
  SCUS-97399 (D6385328).0<slot>.p2s; extract with `7z e -o<dir> <p2s> eeMemory.bin Scratchpad.bin`.
