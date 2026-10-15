# Work on standby (2026-10-13)

The user put everything on standby for the Nintendo Switch test port. Saved here so nothing is lost:

- `menuclock-STATE.md` + `menuclock-overrides.patch`: the Load Game menu clock fix. The recompiler change is commit
  027ce16 on runtime branch `agent/menuclock` (pushed as `runtime-menuclock`). Merge = regenerate the game code with
  it, full rebuild (~40 min), apply the patch to port/overrides-usa/gow_overrides.cpp, gate.
- `levels-STATE.md`: level check results (ATHN01E fine; ATHN01D 38-40 fps, VU1 worker saturated; rechecks left).
- The captain movie (A01MP02) broken sound: cause located, see docs/fmv.md "Open".
