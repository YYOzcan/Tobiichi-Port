# Nintendo Switch target

The user's Switch runs Atmosphère (custom firmware). Target: homebrew NRO (devkitPro/libnx); an NSP would need the
user's own `prod.keys` (Lockpick_RCM) and is not planned until the game runs well.

## Toolchain (in WSL Ubuntu, as root)
- devkitPro's installer/apt host is blocked for scripted downloads (Cloudflare), so Ubuntu's
  `pacman-package-manager` is configured for devkitPro repos: `/opt/devkitpro/pacman.conf`, wrapper
  `/usr/local/bin/dkp-pacman`, mirror pkg.devkitpro.org over HTTPS.
- **Security caveat:** `SigLevel = Never` (keyring host also blocked) → packages are not signature-verified.
  Restore signature checking when the keyring can be fetched.
- Installed: switch-dev (devkitA64 GCC 16.1.0, libnx 4.12.0), switch-sdl2 2.28.5, switch-glfw 3.3.4,
  switch-mesa 20.1.0, switch-glad, switch-ffmpeg 7.1, switch-zlib. No raylib package: raylib 5.5 is fetched by
  CMake and built with PLATFORM=SDL (Mesa GL 3.3).
- Root git: `safe.directory '*'` (repo lives on /mnt/c).

## Repo changes for Switch (ext/PS2Recomp, uncommitted)
- `CMakeLists.txt`: Switch toolchain → runtime-only build (like Android). SSE → NEON via the repo's sse2neon path.
- `ps2xRuntime/CMakeLists.txt`: PS2X_IS_SWITCH; raylib PLATFORM=SDL, CUSTOMIZE_BUILD, SUPPORT_MODULE_RAUDIO=OFF
  (miniaudio has no Switch backend); debug UI and sccache off; `PLATFORM_SWITCH` define; NACP + `nx_create_nro`;
  cache var `PS2X_DEFAULT_CD_IMAGE`.
- `ps2xRuntime/src/lib/ps2_switch_runtime.cpp` (new): userAppInit/Exit → sockets + nxlink stdio.
- `ps2_runtime.cpp`: 1280x720 window on Switch, no raylib audio, `sdmc:` paths kept as-is.
- `ps2_audio.cpp`: Switch uses the Vita no-audio paths.
- `src/main.cpp` (`__SWITCH__` only): default boot path verbatim; default disc image when no argv[2].
  **Needs updating** to the extracted-disc model (DiscSource::openExtracted) instead of an ISO image.
- `switch/build.sh`: configure + build into `out/switch`.
- `tools/switch/smoke_link.sh`, `register_placeholder.cpp`: smoke NRO with an empty function table.

## Verified
- `libps2_runtime.a` (46 objects), `libps2_iop.a` (23 objects), `libraylib.a` build for AArch64.
- Smoke NRO `out/switch/smoke/smoke.nro` (40 MB) links with no undefined symbols (no game code).
- Sample generated game files (MMI/VU0-heavy) and register_functions.cpp compile for AArch64 unchanged.
- (All before the IOP/runtime changes of 2026-10-09; rebuild needed.)

## Commands (from Git Bash)
    MSYS_NO_PATHCONV=1 wsl.exe -d Ubuntu -u root -- bash -c 'cd "/mnt/c/Users/lovas/Claude/God Of War/ext/PS2Recomp" && ./switch/build.sh sdmc:/switch/gow/SCES_531.33 sdmc:/switch/gow/gow.iso ps2_iop ps2_runtime'
    MSYS_NO_PATHCONV=1 wsl.exe -d Ubuntu -u root -- bash "/mnt/c/Users/lovas/Claude/God Of War/tools/switch/smoke_link.sh"
Dropping the targets builds the full NRO (~6500 generated files, GCC + LTO, slow on /mnt/c; never done).

## Open issues
- No audio backend on Switch (needs SDL2 or audren for PS2AudioBackend).
- Performance: GS and VU1 run on the CPU; already only ~2.4 % of real speed on a desktop CPU at the title screen.
  This is the main risk for 4× ~1 GHz A57.
- FMV via switch-ffmpeg software decode (CPU cost).
- Memory: 32 MB guest RAM + 32 MB function table + GS; fine in title-takeover mode (~3 GB, launch a game holding R),
  tight in applet mode (~440 MB).
- Game data on SD: 8 GB of PAKs → exFAT card (FAT32 has a 4 GB file limit). Use the extracted `disc/` folder.
- Testing: copy NRO + disc folder to SD, launch via hbmenu over a game (hold R), logs via `nxlink -s`.
