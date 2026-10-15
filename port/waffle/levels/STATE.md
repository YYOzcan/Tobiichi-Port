# agent/levels state (stopped on user STANDBY, 2026-10-13 ~21:40)

Build: worktree ext/PS2Recomp-kl-levels (branch agent/levels = gow-usa-kl, no code changes), build dir
out/build-levels (configured like build-kl: verbose logs off, VU1 dirs set, FFmpeg on).

## ATHN01E (crashed once while loading)
- 4 single-warp boots: 4 of 4 ok, load 1.5 s, fps 51-59, speed 1.01-1.02, no missing-target, no heap guard
  (port/levels/athn01e/20261013_210735).
- The old crash (port/warp/ship1, JALR 0x130cac -> 1 in the render-list dispatcher 0x1309c0) was in a chained-warp batch:
  the known test-tool limit (docs/game-internals.md), not a game bug. The other "failure" (port/warp/single) was the
  window closed from outside before the zone. Nothing to fix.

## Low-fps rechecks
- ATHN01D (ship deck, save altar): alone 37.6 / 40.4 fps min/mean, speed 1.00 (port/levels/athn01d_alone/20261013_213119).
  Real: VU1 ~3.08 s and GS ~2.3 s per 5 s window; the VIF1/VU1 worker is saturated (guest_wait ~3.1 s). Normal scene
  (rain, deck, altar). Not fixed: needs a profile (tools/sample_prof.py, /MAP) of VU1 there; the flag-latency model
  (agent/shadows3, +23 % VU1 time) is a suspect for part of it.
- ATHN03A 42.6 / 47.8, PAND04G 44.6 / 59.3 (with another fork's runner active; port/levels/lowfps/20261013_211250);
  not rechecked alone yet.

## Movies (BONUS skipped)
- Not run yet: SEMO08 alone (A/V drift 4.4 s in a shared run), and P06MP01, SATINTRO, SEMO01-04. The run was waiting
  for an idle machine when stopped. Command:
  python -I tools/movies.py --only SEMO08 --exe ext/PS2Recomp-kl-levels/out/build-levels/ps2xRuntime/Release/ps2EntryRunner.exe
  then --only P06MP01,SATINTRO,SEMO01,SEMO02,SEMO03,SEMO04 --batch 6 with the same --exe.

## Left
1. Movie rechecks above.
2. ATHN03A alone; ATHN01D VU1 profile and fix (performance, not a crash).
