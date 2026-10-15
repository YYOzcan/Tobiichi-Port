# FMV (movies)

Status: **movies play natively, at real speed, with their sound, and end; the game then continues.** Checked: the
intro (Semo01), Semo02 and Semo05 (through `GOW_MOVIE_OVERRIDE`), the new-game path (the intro, then the ship level
preloads a01mp05 and waits for its trigger while gameplay runs at 60 fps), and all 14 BONUS movies through the
Treasures-menu path (below). No hardware register is touched while a movie plays (`GOW_IO_HIST`). `play.cmd` plays the movies; zone and save
tests still set `GOW_SKIP_FMV=1` (it replaces the movie API: 0x188CA0 load, 0x188E80/ED8/EF0/F20, so the game
continues at once) to keep the runs short.

## What exists
- **Decoder**: the game's libmpeg entry points (`sceMpeg*`, stubbed in the recompiler config) are served by the runtime
  (`ps2xRuntime/src/lib/Kernel/Stubs/MPEG.cpp`). MPEG-2 video is decoded by the vendored **libmpeg2 0.5.1**
  (`ps2xRuntime/third_party/libmpeg2`, GPL-2-or-later, plain C, no CPU-specific code, also builds for the Switch).
  FFmpeg is no longer used (`PS2X_ENABLE_FFMPEG`, default OFF, keeps it as an opt-in backend).
- `sceMpegGetPicture` writes at most `mbcount` macroblocks (16x16 RGB32 = 1024 bytes each), like the original library.
- **Stream callbacks run inside `sceMpegDemuxPss`**, nested on the demuxing thread (`dispatchGuestStreamCallback`), as
  libmpeg does. They were queued for later before; the game's player depends on the synchronous call (below).
  A callback that does not return (thread switch) falls back to the queued invocation and logs `[mpeg] stream callback
  ... did not return`.
- **End of stream**: libmpeg's `sceMpegIsEnd` is the game's own code (0x26FF70: returns the first word of `mp->sys`).
  The stub sets that word when the video is over and every decoded picture was handed out, and clears it in
  `sceMpegCreate`. Without it the player stayed in its playing state forever after the last picture. The video is over
  at its **sequence end code** (`000001B7`, where libmpeg reports the end; the decoder is flushed there) or at the PSS
  program end (`000001B9`), whichever is first; the demuxer still hands the audio packets after it to the game.
  Until 2026-10-13 only the program end counted. Every movie file ends with a 4-byte tail holding that code (files are
  16 KB blocks + 4 bytes); when the player's block reader (0x188848, 4 x 16 KB ring, reads through 0x17AFE0 = SMPD fn 6)
  asked for one more block before the tail was demuxed, it spun on end-of-file reads (0 bytes) forever: A01MP01 (the
  ship movie after the second Hydra fight) froze after its last picture while 989snd kept looping the last 16 KB of
  its IOP sound ring (user report "audio totally broken"). Reproduced and fixed with tools/movies.py.
- The game plays the widescreen files (`.PSW`, e.g. A01MP01.PSW) where they exist; the names it asks for have no
  extension. 67 movies are on the disc (`*.PSS`), 53 of them also as `.PSW`.
- GS renderer: `TEST.ZTE = 0` means no depth test (the GS ignores ZTST then). The movie draws its picture sprite with
  `TEST = 0`; it was treated as ZTST NEVER and rejected after the first frame, which froze the picture.
- **Real-time playback**: the movie thread never blocks; it polls its stream service (0x188B80, called only by the
  movie player 0x188848) as fast as it can. Guest time advances only by executed cycles, and the recompiled poll costs
  more host time per guest cycle than a real EE, so guest time, the IOP and with it the movie sound fell to 0.72x real
  time (pictures at ~22 fps instead of 30; measured with the sync line below). The override `gowMovieStreamService`
  calls `EeScheduler::catchUpToHost` before each poll: guest cycles of scheduled events whose host deadline has already
  passed are accounted (EE timers and IOP included), at most one field per call. Gameplay is not affected (there the
  guest is never behind the host clock).
- `GOW_MPEG_DIAG=1`: pictures handed to the game, `AddStrCallback` registrations, stream-callback call counts, and a
  `[MPEG:sync]` line every 30 pictures (PTS, wall time, audio device position played/produced, time spent in the
  decoder stubs) plus each stream's first audio packet PTS. `GOW_SND_DIAG=1` adds the device position to the LIBSD
  stream start (`BlockTrans ... mode=13`).
- `GOW_MOVIE_OVERRIDE=<name>` (debug): the first movie the game loads is replaced by that one (e.g. `Semo05`,
  `BONUS03`); the name is put on the guest stack and passed to the load function 0x188CA0 (which copies it into the
  movie struct), so any length up to 31 characters works.
- `GOW_BONUS_MOVIE=<NN>` (debug): plays bonus movie NN from the title menu exactly as the Treasures menu does, without
  unlocking it (`GOW_BONUS_MOVIE_DELAY`, default 10 s after the menu update first runs; give a pad script, e.g.
  `GOW_PAD_GUION=900:select`, so the default test presses do not start a new game). The menu's command handler
  0x1BA2C8 writes the two digits into the game's "BonusXX" buffer (0x29CC00) and sets the menu object's movie name
  (+0x1518) and +0x1520; the menu update 0x1BA4F8 then calls 0x1B2D20(name, 3, 1) (the scripted movie request,
  played by 0x1B2958 -> 0x188CA0) and returns to the menu when it ends. Logs `[gow-fmv] menu sees movie state a -> b`
  (0x29C838) for the test scripts.

## How the game plays a movie (USA build)
- Movie thread 0x189020, state in 0x29C838: 3..9 load, **10** = loaded, waiting; **11** = playing. 0x188E80 (start
  request, also sends SMPD command 0x1C) is called by the level script 0x21ED08 when the scene is ready. The Kratos
  frames before state 11 are the in-engine intro, not the movie.
- Open (0x189BD0, movie struct = `sceMpeg` at +0, game fields after it): file extension picks the mode (0x2B2F50
  ".m2" -> mode 2 at +0x140). It reads the first 0x4000 bytes through its read callback (+0x60) and demuxes them
  (`sceMpegDemuxPss`, 0x2740D0 -> 0x273CF0); its video stream callback 0x18A788 copies the elementary stream into the
  ring at +0xE8 (+0xF0 write position). It then reads the picture size from the sequence header at the ring start
  (+0x58 width, +0x5C height), allocates the picture buffers (+0x94[], (w/16)*(h/16)*1024 bytes) and calls
  `sceMpegCreate`. Stream callbacks: type 0 (M2V) 0x18A788, type 2 (PCM, channel 0) 0x18A8F8.
- Per frame (0x18A170): `sceMpegIsEnd`, then `sceMpegGetPicture(mp, +0x94[i], mbcount)`; the picture is uploaded as
  40 strips of 16x480 to TBP 0x2800 (TBW 12) and drawn as a sprite into fbp 104 (TEST = 0, ZTE off).
- The movie's VBlank handler 0x26CF20 calls 0x26E798 (PMODE/SMODE2/DISPLAY1/2/DISPFB1/2 stores) and kicks the upload
  and draw packets.

## Movie audio (how it reaches the speakers)
- The PSS audio is private stream 1, sub-stream header `FF A0 00 00` (0xAn = PCM channel n), then the stream header
  `SShd` (type 1 = PCM16 little endian, 48000 Hz, 2 channels, interleave 0x200) + `SSbd`, then PCM in blocks of
  512 bytes left / 512 bytes right. Packets are 4096 bytes on disc; the PCM runs on across packets of odd lengths.
- The stub hands each audio packet (type PCM = 2, ADPCM = 3, libmpeg's constants) to the game's callback 0x18A8F8
  from its own copy of the demuxed bytes, through a guest buffer (the game reuses its 16 KB read buffer). The callback
  keeps the first 0x28 bytes (+0x10C) and appends the rest to the 100 KB audio ring (+0xFC base, +0x100 size,
  +0x104 read, +0x108 fill); when the ring is full it returns 0 and sets +0x134. libmpeg stops demuxing there; the
  stub keeps refused packets, in order, and hands them over first on the next demux call.
- The movie thread (0x189020) sets up a 989snd PCM stream (0x1882E8: SNDRPC 0x3B, IOP ring 0x4000 bytes at 0x77640;
  0x188408: 0x3E start) and on every pass drains the EE ring into the IOP ring (0x189A88 -> 0x188380 -> 0x188688:
  989snd command 0x40 = `sceSdBlockTransStatus`, minus the IOP ring address = where the sound unit reads; then SIF
  DMA in 1 KB units). 989snd plays the IOP ring with `sceSdBlockTrans(core 1, mode 0x13 loop)` = the core input
  stream of the native SoundEngine, mixed at BVOL 0x7FFE with MMIX 0x0FCF.
- Fixed for this (2026-10-12): `sceMpegCreate` resets the sceMpeg's callbacks (the game registers its stream callbacks
  before Create for the first demux and again after it: both stayed active and every audio packet went into the ring
  twice); `sceSdBlockTransStatus` returns the IOP address read (+ ring half in bit 24) like libsd, not an offset
  (the game's free-space count went negative and nothing was sent); BVOL is a plain 16-bit level (it was converted
  like a voice volume: 0x7FFE became -2, the stream was mixed at about -80 dB).
- Check: port/fmvc4v (`GOW_AUDIO_PCM`): the movie section (35-80 s) has sound with the smoothness of real audio
  (first-difference / RMS 0.06-0.28, the menu music measures 0.1-0.2; it was 1.3-1.4 = noise before).

## A/V sync (intro, port/c5/sync5)
- Picture PTS follows wall time (6.01 s of PTS per 6.00 s of wall; drift = the 29.97/30 rate), and the device plays
  exactly what the engine produces (no underruns). Semo02: 113.1 s PTS in 113.0 s wall, Semo05: 110.1 in 110.0.
- Audio and video start at the same PTS (8329). When a picture is handed to the game, the audio produced so far is
  ~90 ms behind its PTS (picture 30: 1.094 s vs 1.0225 s; picture 600: 20.113 s vs 20.0225 s), constant over the
  movie; the device buffer adds ~20 ms and the picture is shown 1-2 VBlanks after it is handed over, so what is heard
  trails what is seen by roughly 0.1 s.

## BONUS movies (Treasures menu, port/movies2)
The disc has 14: BONUS01, 03, 06, 10, 12, 14, 16, 17, 18, 19, 20 (the credits), 21, 24, 25 (01/19/20/21 on layer 1).
Each was played with `GOW_BONUS_MOVIE` from the title menu, with sound and a `GOW_AUDIO_PCM` dump
(`port/movies2/run_bonus_all.sh`, results in `bonus_all.txt`, contact sheet `bonus_sheet.png`):
- pictures at 30.00 per wall second in every movie (14 s for BONUS19 up to 812 s for BONUS03);
- sound for the whole movie: produced audio = picture time, RMS 3.6k-13k, smooth (first difference / RMS 0.01-0.83,
  noise measures 1.3-1.4), at most 5 silent one-second windows (fades);
- every movie ends (movie thread 11 -> 0) and the game is back at the title menu; no runtime errors.

## Hardware registers (none while a movie plays)
The player's own display/DMA layer (0x26CF20 VBlank handler -> 0x26D048, 0x26E798 display setup, 0x26ED68 / 0x26EDE0
normal / chain DMA sends, 0x26ED20 D_SQWC, 0x26CB90) and the open/close code (0x189BD0, 0x18A170: D_ENABLEW and the
IPU channels) used to go through the generic hardware path: per picture ~3 GS display stores (SMODE2, DISPLAY1/2,
PMODE, DISPFB1/2), a CSR read and 3 DMA sends (VIF1, GIF x2) with their D_STAT clears. Now (docs/runtime-changes.md
"Movie path without hardware registers"): display stores are `gsDisplayStore` calls on the native display service,
the CSR read is `gsStatusLoad`, the DMA stores go to the native DMA request service (VIF1/GIF packets sent at once;
D_ENABLEW dropped; fromIPU/toIPU starts have nothing to move). `GOW_IO_HIST` during BONUS17: 0 accesses (before, during
BONUS03: ~11k each of SMODE2/DISPLAY1/DISPLAY2 per 400 s, plus the DMA registers).

## Picture size and edges (2026-10-13, agent/visual3)
- Every movie stream is 640x480 (`GetPicture size=640x480`), but the picture is the top 448 lines; the last 32 lines
  are black in the stream itself (`GOW_MPEG_PICDUMP`). The movie sets a 480-line display (DISPLAY2 DH 479, MAGH 3) at
  the same DY (50) as gameplay (448 lines), so a TV shows the movie picture where the game picture is and the black
  band in its bottom border. The host present cuts displays to the 448-line TV area (`kTvLines`, gs_hw_backend.cpp
  Present): the movie fills the window like the game does (before: a black band under the movie, user report).
- The picture is uploaded to TBP 0x2800 (TBW 12) and drawn as one sprite, UV 0.5-640.5 x 0.5-480.5 over 640x480,
  bilinear. At the 2x internal scale the last host column and row sampled 25 % of the texel beyond the picture (the
  memory after it in the 768-wide buffer): a thin coloured line on the right edge and under the picture (user
  report). Every sprite now clamps its sampling to the texel range of the first and last pixel the GS covers (per
  vertex `aUVClamp`), so filtering stays inside what the GS samples. Fixed for all sprites, not only movies.

## Every movie: tools/movies.py (2026-10-13)
`python -I tools/movies.py [--only A,B] [--batch 12]` plays every movie of the disc through the game's own player and
judges picture and sound (needs numpy). `GOW_MOVIE_OVERRIDE=<name>,<name>,...` replaces one movie load per entry; the
title-menu hook (`gowDiagBonusMovie`) requests the next one each time the player is idle again, so the movies of a batch
play one after another in one session. Sound is recorded with the output muted (`GOW_AUDIO=0` + `GOW_AUDIO_PCM`: the
stream runs at volume 0, paced as when heard). Per movie: pictures and pictures/s (30), audio seconds vs picture
seconds, A/V drift, silent seconds, clipped samples (bad above 0.5 %: A01MP05 clips ~0.1 % by design, below), smoothness (first difference / RMS; noise
>= 1.2), repeated 512-frame blocks, dropped/missing output frames, runtime errors and movies that never end.
`--reanalyse <run dir>` judges a finished run again; `GOW_AUDIO_RAW=<file>` records the mix before the output's rate
adaptation, so a movie can be compared with its source track sample by sample.
- Movie sound is exact: A01MP05 recorded raw matches its PCM track at gain 1.001, sample-aligned.
- When a movie starts, the game pauses its sound groups with a per-movie mask (`0x175148(1, mask)` -> SMPD fn 0x10 ->
  989snd export #67, which pauses every sound handle of those groups; table at 0x29C858: A01MP05 0x7CFD, A01MP02 and
  A01MP03 0x7EFF, others the caller's value). A01MP05 leaves groups 1, 8 and 9 playing on purpose: the level music goes
  on under that scene (in the menu test it is the title music, which is why A01MP05 measures some clipping).

- `--new-game <seconds>`: the in-game path. A new game (title, New Game, Hero, the ship) fights around the deck with
  god mode; the game plays the new-game intro (Semo01) and preloads A01MP05 when the ship loads, then plays it from
  its level trigger (about 90 gameplay seconds in). The movies are found by `[gow-fmv] load <name>` (the load hook logs
  every load under `GOW_MPEG_DIAG`); output statistics count only from a movie's first to its last picture (a
  preloaded movie's log segment also holds gameplay).
- In game, A01MP05's track is mixed sample-exact; under it plays the level's group-1 stream (a 4-voice music stream,
  989snd handle group 1: core 1 voices 0/4/7/8), which the movie's mask 0x7CFD leaves running by design; every voice of
  the paused groups is silenced by 989snd (pitch 0, volume 0). Mix: movie RMS ~6400 + music ~7000, 0.2 % clipped.
- Story movies through the menu path (port/movies4/all, story, story2): 45 of 53 ok (A01MP05 clips ~0.1 % against the
  title music, below the threshold); bad: P04MP05 (stops, below), SEMO08 (drift, below); not reached (behind P04MP05 in
  their batch): P06MP01, SATINTRO, SEMO01-04 (SEMO01 is ok in the new-game runs). BONUS movies were verified by
  agent/movies2.

## Open
- **A01MP02 broken sound, cause located (2026-10-13 user session port/usertest1/play8.log, raw mix
  `user_movie_raw2.pcm` in the runner dir):** reached by playing the ship normally from a new game (via the warp it is
  clean). The engine mix during the movie has exactly the track's energy per second but is the track with L/R swapped
  and shifted by +123 samples (best local lag constant over the whole movie, corr 0.8-0.9, never 1.0): the PCM reached
  the core input misaligned against the 0x200-byte L/R interleave, so every 256-sample block mixes the two channels
  (a 187 Hz channel flip = the buzz). Output stage clean (rate <= 1.009, nothing dropped). 40 `[MPEG:refused]` audio
  packets in that session (the EE audio ring full): suspect the refused-packet re-delivery or a partial accept moving
  the byte position by a non-block amount. Next: log bytes accepted per packet vs re-sent, fix so the stream stays
  block-aligned. ON STANDBY (user: Switch test port first).
- **A01MP02 in game (the captain movie): our mix is exact; the breakage is not reproduced in the engine.**
  - Reached on the real path with the level warp: `GOW_WARP=ATHN01D` lands next to the captain, and the level
    script (`CoweringGuy` group in ATHN01D.WAD) loads `a01MP02` about 27 s later.
  - With the user's order (new game, A01MP05 from its ship trigger, then the warp): the run shows the same 20
    `[dma] chain tag with SPR flag` lines at the movie start as the user's logs, so the state matches.
  - In both runs the engine's raw mix (`GOW_AUDIO_RAW`) during the movie equals the movie's own PSS track at gain
    1.000, with a residual of 1-2 RMS. Nothing else plays under it; the music event `MusicGrpAthC4Start`
    (`SND_M_ATH1C4_2`) does not sound during the movie.
  - The output path (`drainOutput`, rate adaptation, recorded with `GOW_AUDIO_PCM`) adds no damage: fewer large
    jumps than the mix, rate <= 1.018, nothing dropped.
  - The track itself is mastered hot: peaks at its limiter ceiling (32015-32030) and ~140 jumps > 8000 per second.
    PCSX2 mixes the core input the same way (`ApplyVolume(ReadInput(), InpVol)`, `>> 15`, BVOL 0x7FFE ~ 1.0), so the
    PS2 plays it at this level too.
  - The user's loopback recording matches the track only at correlation ~0.6 after fitting its 0.7-1.2 % faster
    playback (rate adaptation). It holds more than our mix; a loopback recording also includes every other program
    on that output.
  - 989snd never writes sweep-mode volumes (0 of 71k voice volume writes in a new-game run), and the movie's MMIX is
    0x0FCF (voices, input and core 0 all on): the unmixed volume sweeps and the ignored MMIX voice/external gates are
    not involved.
  - Next: capture the engine's own mix in the user's session (`GOW_AUDIO_RAW=<file>` and `GOW_AUDIO_STATS=1` in
    play.cmd). It tells whether the breakage is in the engine (then visible in that file) or after it.
- **P04MP05 stopped after 180-210 pictures: FIXED (game ring logic), it now plays 720 of 743.**
  - The movie player's video ring (player struct `*0x304F20`: +0xE8 base, +0xEC size 0x40000, +0xF0 write pointer,
    +0xF4/+0xF8 the block sent to the IPU) treats a write pointer at the ring's end as data. The demuxed video of
    P04MP05 filled the ring exactly to its end. When the IPU block pointer then wrapped to the base,
    `available = write - block end` was the whole ring.
  - The no-data callback (0x18AAA8) then kept sending the old ring and never asked for more data. The reader stopped,
    the IOP stopped reading (`GOW_CD_TRACE`: 190 reads, then none), and the main thread looped in VSync waits
    (`GOW_THREAD_WATCH`) while the sound played on.
  - The end and the base are the same position. gow_overrides.cpp (`gowNormaliseVideoRing`) moves the write
    pointer to the base at the start of the no-data callback and of the writer (stream callback 0x18A788).
  - Only code before a guest call is reliable in a wrapper: the writer can return early at an EE checkpoint and be
    finished through the original's own slots, so a post-call fix missed the write.
- **P04MP05 still does not end (stops at picture 720 of 743): end-of-file, open.**
  - The player's reader (0x188848, struct at 0x302B20: +0x18 block, +0x1C blocks left, +0x28 state) reads 16 KB
    blocks through 0x17AFE0 and is demuxed one block behind.
  - The file is 1457 blocks plus a 4-byte tail (the program end code); its sequence end code lies in the last full
    block (1456). In A01MP01, which ends, it lies two blocks before the tail.
  - At the end the reads return 0x4000, then 4 bytes, then 0 at position 0x16C4004. The read loop in 0x18AC20 retries
    a 0-byte result forever when blocking, and sets the end flag (+0x154) only for a negative one. So block 1456 is
    never demuxed: the stub never sees the sequence end, and 5.3 KB stay in the video ring (below the no-data
    callback's 8 KB threshold).
  - Next: what the PS2's SMPD stream returns for the short tail read / the read past the end (negative, or a full
    block), compared with our native SMPD service.
- SEMO08 measured 4.4 s A/V drift (214.6 s of audio for 210.2 s of pictures) in a batch that shared the machine with
  other runs; to recheck alone.
- In some in-game runs (port/movies4/newgame/20261013_171528) the GS stalled for seconds while A01MP05 waited
  preloaded (host 11 fps): the sound starved (up to 3.8 s) and the backlog was then cut. Not reproduced in a run without
  other runners on the machine (port/movies4/gsstats); the same fight with movies skipped did not stall.
