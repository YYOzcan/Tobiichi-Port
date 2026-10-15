# God of War (PS2) → native port (PC, then Nintendo Switch)

These documents are the **single source of truth** for this project. Every session starts by reading them and
ends by updating them. Do not rely on chat history: if something was discovered, it belongs in one of these files.

Goal: static recompilation of God of War (PS2, PAL, SCES-53133) with PS2Recomp into a native executable, made playable
on PC first (debuggable), then built for Nintendo Switch homebrew (the user's Switch runs Atmosphère).
**Main achievement (user, 2026-10-11): after the PC port, the game must run on the Nintendo Switch.** Everything built
for PC has to stay portable to it: AArch64 (no x86-only intrinsics without a portable/sse2neon path), no Windows-only
APIs outside platform code, GPU features available in switch-mesa (the native GS uses GL 4.3 core shaders, dual-source
blending and texture barriers: to verify there), ~3 GB memory, and a CPU ~5-8x slower than the dev PC, so CPU-side speed
(EE, VU1, IOP) is a requirement. See [switch.md](switch.md).
Order: the Switch build itself (toolchain port to ext/PS2Recomp-kl, NRO, tests in Citron: `ref/citron/citron-cmd.exe`)
starts only after the PC port is complete.
The user wants the game **totally playable**; work continues until then. Game data is read from **extracted files**
(`disc/`), never from the ISO.

## Documents

| File | Contents |
|---|---|
| [status.md](status.md) | Where the port stands right now, the active task, the ordered next steps. **Read first.** |
| [build-and-run.md](build-and-run.md) | Toolchain, recompile pipeline, build configurations and their cost, how to run, tools. |
| [diagnostics.md](diagnostics.md) | Debug env vars, trace tools and the debugging methods that worked. |
| [disc.md](disc.md) | Disc layout, extraction, `.disc_layout`/`.disc_meta`, `DiscSource`. |
| [elf-and-recompilation.md](elf-and-recompilation.md) | ELF facts, function discovery, analyzer pitfalls (the removed NOP patches). |
| [game-internals.md](game-internals.md) | God of War code knowledge: boot flow, addresses, heap, loaders, 989snd/SMPD protocol, waits. |
| [runtime-changes.md](runtime-changes.md) | Every change made to the EE runtime (ps2xRuntime) and recompiler, and why. |
| [iop-changes.md](iop-changes.md) | Every change made to the IOP emulator (ps2xIOP), and why. |
| [native-port.md](native-port.md) | Inventory of every emulated layer, its native replacement, measured cost and the order of work. |
| [vu1-native-flags.md](vu1-native-flags.md) | VU1 native blocks: MAC/clip flag latency across blocks, the character-shadow cull bug, the opt-in exact mode and its cost. |
| [visual-audit.md](visual-audit.md) | Suspected rendering defects found in the zone captures (vs PCSX2), with the likely GS cause. |
| [fmv.md](fmv.md) | Movies: libmpeg2 decoder, how the game plays a movie, what is still open. |
| [sound.md](sound.md) | Native sound engine: the LIBSD API boundary, SoundEngine, what is mixed. |
| [memory-card.md](memory-card.md) | PS2 memory card format and how the game reaches the card (for the native card service). |
| [status-map/](status-map/detail.md) | Status map shown on the GitHub page: edit `data.toml`, run `python tools/status_map.py`. Keep it in step with status.md. |
| [switch.md](switch.md) | Switch toolchain (WSL + devkitPro), Switch build changes, open Switch issues. |
| [gemini-helper.md](gemini-helper.md) | Read-only helper agent (`agy`/Gemini) to offload log/dump analysis: when and how to call it. |

## Project layout

    God Of War/
      docs/                this documentation
      iso/                 the user's redump ISO (kept, not used at runtime)
      disc/                all 16 disc files extracted + .disc_layout/.disc_meta + imgui.ini (runtime cwd)
      port/gow.toml        recompiler config        port/functions.csv  function map (tools/find_functions.py)
      port/output/         generated C++ (regenerated, never edited)
      port/overrides/      game-specific runtime code (god_of_war_overrides.cpp)
      port/*.log, *.png    run logs / screenshots (scratch)
      disc-usa/            USA disc extracted + IOP_MOD/ + Mcd001.ps2 (copy of the user's card)
      ext/PS2Recomp-kl/    PS2Recomp worktree with KIexster's 68 patches (USA primary target)
      ref/                 reference material: proto/ (Hydra Battle demo prototype), pcsx2/ (PCSX2 2.8.2)
      tools/               project scripts (see build-and-run.md)
      ext/PS2Recomp/       PS2Recomp clone with our (uncommitted) changes
      LOG.md               pointer to these docs

## Rules for working on this project

- Update the relevant doc in the same step as a discovery or code change (fact, address, reason, how verified).
- Mark anything unverified as **unverified**. Remove or correct facts that turn out wrong.
- Prefer generic fixes in PS2Recomp (runtime/IOP/recompiler) over game hacks; game-specific code goes only in
  `port/overrides/god_of_war_overrides.cpp` and is documented in game-internals.md.
- Never run two builds of `out/build` at the same time (they corrupt each other; see build-and-run.md).
- performance.md — speed work toward 60 fps: baseline, levers, measurements
