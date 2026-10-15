# agent/menuclock — state (2026-10-13, stopped on the user's standby order)

## Measured
- Title, main menu, pause menu, gameplay: game speed 1.000, VBlank 59.99-60.00 Hz, IOP clock 1.000 +- 0.0004, audio
  rate <= 1.002 (zones.py and play.cmd environments; before_title, before_play, before_pause). The 3.7 % of 10-12 is gone.
- Load Game (memory card) menu: game speed 1.08 (frame intervals alternating 0.8 / 1.1 fields).
- Captain movie a01MP02 (new game, GOW_WARP=ATHN01D, standing still), before and after: 990 pictures, wall 33.07 s =
  audio produced 33.07 s = PTS 33.03 s, 0 missing, 0 dropped, resample rate <= 1.009, buffer 3600-5700 frames, IOP
  clock 1.006-1.008. No chopping or pitch shift from the clock: the coordinator's fast-clock hypothesis for the broken
  movie audio is not supported (movie_before2, movie_after).

## Cause found (Load Game menu)
- Every second frame the menu sends 3 memory-card commands before the frame-clock read (0x17D778); each cost a fixed
  520 T0 ticks: libmc2's send (0x27B568) byte-copies 0x2080 bytes in an 8-instruction loop and every back-edge charged a
  flat 32 EE cycles (GOW_FRAMECLOCK_TRACE, trace_load2/3).
- Fix: recompiler charges each back-edge its loop body (<= 32). Commit 027ce16 on agent/menuclock (worktree
  ext/PS2Recomp-kl-clock, build out/build-clock). Load Game menu 1.08 -> 1.019-1.020; other states unchanged.
- Gate passed: port/menuclock/gate/20261013_222345 (zones 0-4 60 fps, speed 1.00-1.01), savetest ok (port/menuclock/savetest).

## To merge (main)
- Merge agent/menuclock; build ps2_recomp; regenerate with port/usa/recomp-clock.toml (= recomp-movies2.toml, own output
  dir) or copy port/output-usa-clock/* (1689 files differ only in eeCheckpointDue(N), + ps2_recompiled_stubs.h without
  the old rand stub) into ps2xRuntime/src/runner/; full rebuild (~40 min).
- git apply port/menuclock/gow_overrides.patch (GOW_FRAMECLOCK_TRACE hooks; port/overrides-usa) and copy to the runner.
- Docs: port/menuclock/docs/{performance,runtime-changes,diagnostics,sound}.md (edited copies of master's files).

## Left
- Remaining +2 % in the Load Game menu is the game's own frame-clock design (any read jitter only adds time); expected on
  console/PCSX2 too, not measured there.
- Load Game menu IOP clock 1.002 and movie IOP clock 1.006-1.008 (small, absorbed by the output); not investigated.
