# Build and run

## Toolchain (Windows)
- Visual Studio Build Tools 2026 (MSVC 14.51), Windows SDK 10.0.26100, CMake 4.3 bundled at
  `C:/Program Files (x86)/Microsoft Visual Studio/18/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe`.
- Generator "Visual Studio 18 2026", x64, build dir `ext/PS2Recomp/out/build`.
- Python 3.11 (+ `capstone` installed with pip) for the tools.
- PS2Recomp: github.com/ran-j/PS2Recomp, cloned at commit 2c5fbb9 (2026-10-05) into `ext/PS2Recomp`.

## Recompile pipeline
1. (once) `ps2_analyzer disc/SCES_531.33 port/gow.toml` — already done; `port/gow.toml` is now hand-maintained.
2. `python -I tools/find_functions.py disc/SCES_531.33 port/output port/functions.csv` — function map
   (`gow.toml` → `ghidra_output = "port/functions.csv"`). Needs an existing `port/output` for the known starts.
3. `rm -rf port/output && ext/PS2Recomp/out/build/ps2xRecomp/Release/ps2_recomp.exe port/gow.toml > port/recomp.log`
   Expect: 6482 functions, 0 errors, ~2240 control-flow warnings (indirect jumps → runtime dispatch, harmless).
4. `tools/sync_runner.sh` — copies changed `port/output/*.cpp` + `port/overrides/*.cpp` into
   `ext/PS2Recomp/ps2xRuntime/src/runner/` and headers into `ps2xRuntime/include/`; deletes stale runner files.
   Copies only changed files so builds stay incremental. Slow-ish on Windows (~2 min, 6500 cmp calls).
5. Build: `cmake --build out/build --config RelWithDebInfo --parallel --target ps2EntryRunner > port/build.log`
   (rebuild the recompiler itself with `--config Release --target ps2_recomp` after changing ps2xRecomp).

## Build cost (important for planning)
- Use **RelWithDebInfo** for iteration. Release uses /GL + /LTCG, making every relink a full link-time codegen.
- Changing any header in the runner's precompiled header (`ps2_runtime.h`, `ps2_call_list.h`, `ee_scheduler.h`,
  `gs_frontend.h`, generated `ps2_recompiled_functions.h`, …) → full rebuild ≈ 20–40 min.
- `.cpp`-only changes in ps2xRuntime/ps2xIOP → seconds to ~1 min.
- Never start a second build while one runs: an overlapped build once ended rc=1 and forced a full recompile.
- `grep " error "` on build.log gives false "Binary file matches"; use `grep -aE 'error C|error LNK'`.
- The link prints `/FORCE` warning LNK4088; that is a configured option, not an error.
- Re-run `cmake -S . -B out/build` after adding source files (globs / CMakeLists edits).

## Run
- Executable: `ext/PS2Recomp/out/build/ps2xRuntime/RelWithDebInfo/ps2EntryRunner.exe <abs path>/disc/SCES_531.33`
  run with cwd = `disc/`. No second argument: the disc comes from `disc/.disc_layout` (see disc.md).
  (argv[2] = path to an .iso is still supported but the user does not want ISO reads.)
- Test runs play sound (user 2026-10-12, "enable the audio"): `tools/zones.py` and `tools/savetest.py` mute only with
  `--silent` (GOW_AUDIO=0).
- `play.cmd` plays the movies (cutscenes; docs/fmv.md). The zone and save tests set `GOW_SKIP_FMV=1` to keep runs
  short; `tools/movies.py` plays every movie of the disc (muted, sound recorded) and judges picture and sound
  (docs/fmv.md; needs numpy).
- Game data comes from the extracted disc in `disc-usa/` (docs/disc.md); `play.cmd` and the test tools never read the
  ISO (`--iso` in zones.py/savetest.py, or `GOW_ISO=<iso>`, for comparisons).
- `tools/run.sh <seconds> <name> [ENV=VALUE ...]` — runs from disc/, waits, screenshots, kills;
  log → `port/<name>.log`, screenshot → `port/<name>.png`.
- `tools/shot.ps1 <process> <out.png>` — PrintWindow capture of the game window (works with overlapping windows).
- The runtime debug panel (F1) is ImGui; its state is saved in `disc/imgui.ini` (set `Collapsed=1` to hide).
- Window 640x448; keyboard/gamepad mapping in ps2xRuntime/src/lib/ps2_pad.cpp:
  arrows/WASD = d-pad, X/Space = ✕, C/Esc = ○, Z = □, V = △, Q/E = L1/R1, LShift/RShift = L2/R2,
  Enter = Start, Tab = Select; gamepad 0 if present.

## Project tools (`tools/`)
| Tool | Purpose |
|---|---|
| iso_extract.py | List/extract ISO (both layers); `--layout` writes .disc_layout/.disc_meta |
| find_functions.py | Build function map CSV (see elf-and-recompilation.md) |
| dis.py ADDR | Print R5900 disassembly of the generated function containing ADDR (from port/output comments) |
| irxdis.py IRX [--find STR] [--at HEX N] | Disassemble an IRX (R3000, base 0) / find string references |
| peek.py LOG | Decode heartbeat peek lines into hex + ASCII |
| run.sh / shot.ps1 | Run + screenshot |
| key.ps1 | Post a held key to a window without focus (WM_KEYDOWN/UP): `key.ps1 proc delay holdMs vk scan [repeat]` |
| pine.py | Read EE memory of a running PCSX2 (PINE) |
| irxfind.py | Locate IRX modules inside an IOP RAM dump (PCSX2 save state) |
| vramdiff.py | Page map of our GS VRAM vs PCSX2's GS.bin |
| ppm2png.py | Convert PS2X_FRAME_DUMP output to PNG |
| sync_runner.sh | Sync generated code + overrides into the runner |
| switch/ | Switch smoke-link helpers (see switch.md) |

Note: `dis.py` reads comments in port/output; a few delay-slot lines are missing there. For exact bytes use capstone
on the ELF (file offset = vaddr − 0xFF000). Capstone mis-decodes R5900 128-bit ops (lq/sq/MMI).
- Pitfall (2026-10-09): editing C++ through a Python heredoc in the Bash tool turned "\n" inside C string
  literals into real newlines (C2001). Use the Edit tool for lines containing escapes.
