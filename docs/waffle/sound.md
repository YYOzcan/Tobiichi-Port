# Sound: the native sound engine

The game's sound engine is its own IOP code: 989snd (`989NOMID.IRX`, sequencer, voice allocation, streaming) with the
SMPD streamer plugin, compiled ahead of time like every IRX (docs/native-port.md). Below it there is no sound hardware
model: the SPU2 register-level model and the IOP's SPU DMA channels were removed on 2026-10-11.

## Boundary: the LIBSD API
- 989snd reaches the sound unit **only** through LIBSD.IRX's exports (it never touches SPU2 registers; only LIBSD did).
- Those exports are native C++ (`ps2xIOP/src/native/iop_native_overrides.cpp`, listed in tools/iop/native_overrides.txt):
  sceSdInit #4 0x456c, SetParam #5 0x3670, GetParam #6 0x36cc, SetSwitch #7 0x372c, GetSwitch #8 0x3764, SetAddr #9
  0x379c, GetAddr #10 0x3800, SetCoreAttr #11 0x3cbc, VoiceTrans #17 0x18a0, BlockTrans #18 0x1c30, VoiceTransStatus
  #19 0x1af0, BlockTransStatus #20 0x1e4c, SetEffectAttr #23 0x0c3c, SetTransIntrHandler #26 0x3e3c,
  SetEffectWorkArea #31 0x0984 (addresses checked against LIBSD's export table). Note2Pitch #13 stays game code (math).
- Entry codes as libsd: `(id << 8) | (voice << 1) | core`, master/effect/stream volumes with bit 7 (LIBSD's register
  table at 0x4930 gives the id order: 0 VOLL, 1 VOLR, 2 PITCH, 3 ADSR1, 4 ADSR2, 5 ENVX, 6/7 VOLX, 8 MMIX, 9/A MVOL,
  B/C EVOL, D/E AVOL, F/10 BVOL, 11/12 MVOLX, 13 PMON, 14 NON, 15 KON, 16 KOFF, 17 ENDX, 18-1B VMIX L/EL/R/ER,
  1C ESA, 1D EEA, 1E TSA, 1F IRQA, 20 SSA, 21 LSA, 22 NAX). Addresses are byte addresses (16-byte aligned).

## SoundEngine (`ps2xIOP/src/emulator/core/sound_engine.{h,cpp}`)
- Typed state: per voice volume L/R, pitch, ADSR1/2, start/loop/next addresses, envelope; per core VMIX/NON/PMON masks,
  MMIX, ATTR, master/effect/aux/stream volumes, ESA/EEA. 2 MB sample RAM (the game's sample data).
- DSP (unchanged from the former model, PCSX2 / psx-spx algorithms): ADPCM decode, pitch with linear interpolation,
  ADSR, dry mix per voice, master volume; NAX reported inside the playing block like PCSX2's NextA (989snd's polled
  streams abort when NAX leaves the ring halves: that was the 2026-10-09 music-restart bug).
- Core input stream (BlockTrans, "ADMA"): 1 KB blocks of 256 left + 256 right 16-bit samples read from the IOP ring at
  48 kHz, mixed at BVOL while MMIX's sound-input bits (0xC0) are set; mode 0x13 loops, mode 2 stops. 989snd clears its
  transfer handler before starting it and polls the position. (Not implemented in the former model.)
  BVOL is a plain 16-bit signed level (0x7FFF = 1.0), unlike voice volumes; `sceSdBlockTransStatus` returns the IOP
  address being read (bits 0-23) and the ring half (bit 24), as libsd does. Used by the movie sound (docs/fmv.md).
- Transfers are copies; VoiceTrans returns `(size + 63) & ~63` and, for mode 0, schedules the driver's completion
  handler `handler(channel, arg)` (989snd 0x78bc: releases its transfer lock and wakes the waiting thread) 512 IOP cycles
  later through `IopNativeServices::callGuestLater`, as the DMA interrupt did. VoiceTransStatus returns 1.
- One stereo sample per 768 IOP cycles (`advanceTo`), drained by the host audio thread (`drainOutput`).
- Sample clock = the IOP cycles the EE granted (`IopEmulator::runCycles`), each call clamped to its grant: IOP work
  outside runCycles (EE-side RPC calls into IOP servers; a dbcman RPC at 0x12BCC costs ~10 M IOP cycles/s on the
  title screen and menus) and overshoot inside it move the IOP clock ahead of the EE but produce no samples.
- Output rate adaptation (`drainOutput`): the latency target is 100 ms (`kSpu2MaxLatencyFrames`). Above it the
  buffer is played up to 5 % faster with linear interpolation; at or below it the samples are copied unchanged. A
  buffer more than 4 targets above (after a stall) is cut back once. On the menus the guest clock runs ~3.7 % ahead
  of the wall clock (EE cycles per field above the VBlank period; open), so the menus play at ~1.038; gameplay ~1.001.
- Former behaviour (until 2026-10-12): the output cut blocks of samples whenever the buffer exceeded the target.
  Combined with the clock above it dropped ~30 % of the samples on the menus: the audible crackle ("clipping").
  `GOW_AUDIO_STATS=1` prints requested/missing/dropped frames, the highest rate and the buffer level every ~5 s;
  `GOW_IOP_DRIFT=1` prints granted vs advanced IOP cycles and the top outside calls; `GOW_SND_REGLOG=1` logs the
  core register writes (MMIX, MVOL, EVOL, AVOL, BVOL).
- Not mixed yet: reverb (parameters stored), volume sweeps (target applied at once), gaussian interpolation.

## Verified (2026-10-11)
Desert zone with `GOW_AUDIO_PCM`: 158.9 s of audio in a 160 s run (former model 156.5 s), same level profile, same 2
short silences (port/audio_native1 vs audio_native2); zone ok at 60 fps; save test ok.

## Verified (2026-10-12, crackle fix)
Desert run (port/aud9): 0 dropped frames, 0 underruns, 0 saturated samples (was 2.5/s), 0 sample jumps > 12000 (was
1.6/s); per-10 s RMS matches the former recording where both cover the same part (2791/3160/3621 vs 2808/3163/3597).

## Output device
The sound engine plays on the system default output (raylib audio) unless a device is named: `GOW_AUDIO_DEVICE=<part of
its name>` or the first line of `%LOCALAPPDATA%\GodOfWarNativeudio_device.txt` (per user, so every instance and
worktree build follows it; e.g. `Oculus` for "Cuffie (Oculus Virtual Audio Device)"). The stream is then played on
that device through miniaudio directly (ps2xRuntime/src/lib/ps2_audio_device.cpp, raylib's miniaudio build: its
configuration macros must match raudio.c). No match: the log lists the devices and the default output is used.
`play.cmd` sets `GOW_AUDIO_DEVICE=default` (the system default output), so the per-user file only routes test runs
(user 2026-10-13: tests on the Oculus output, playing on the main output). `GOW_AUDIO=0` (zones.py --silent) still mutes;
a muted recording (`GOW_AUDIO_PCM`) never uses the chosen device.

## Sound groups and movies (2026-10-13)
- 989snd keeps every sound handle in a group (handle +0x17). The game pauses and continues groups through SMPD fn 0x10
  (`0x175148(pause, mask)` on the EE -> 989snd plugin call -> SMPD 0x66F4 -> 989snd export #67 pause / #68 continue),
  e.g. all groups while loading (mask 0x7FFF) and, when a movie starts, a per-movie mask (docs/fmv.md). 989snd pauses a
  sound by setting its voices' pitch and volume to 0 and a stream (type 4, 0x12398) by zeroing the voices of its
  channels, all through the LIBSD calls the engine serves.
- Checked with `GOW_SND_CALLLOG`, `GOW_SND_VOICEDUMP` and `GOW_AUDIO_RAW` (port/movies4): the movie stream is mixed
  sample-exact (gain 1.001 against the PSS track); under A01MP05 the voices of the group-1 stream keep playing, as the
  movie's mask asks.
- Recording without hearing it: `GOW_AUDIO=0` with `GOW_AUDIO_PCM` runs the output at volume 0; `GOW_AUDIO_RAW` writes
  the mix before the output's rate adaptation (the PCM file is after it, so it drifts up to 5 % against a source).
