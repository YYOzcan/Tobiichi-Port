# Tobiichi Port — God of War PS2 PC Port

A work-in-progress PC port of **God of War (SCUS-97399)** using static recompilation (MIPS R5900 → C++20) via the [PS2Recomp](https://github.com/ran-j/PS2Recomp) framework.

> Inspired by [N64Recomp](https://github.com/Mr-Wiseguy/N64Recomp) and [OpenGOAL](https://github.com/open-goal/jak-project).

---

## Project Structure

```
Tobiichi-Port/
├── PS2Recomp/                  # PS2Recomp framework (forked from ran-j/PS2Recomp)
│   └── ps2xRuntime/
│       └── src/lib/
│           └── game_overrides.cpp  ← All God of War-specific hooks live here
├── god_of_war.toml             # Recompiler configuration
├── GODOFWAR.TOC                # Game table of contents
├── *.IRX                       # IOP module binaries (PS2 I/O Processor)
└── SYSTEM.CNF                  # PS2 system configuration
```

---

## How It Works

1. The God of War ELF (`SCUS_973.99`) is statically recompiled: **MIPS → C++**
2. `ps2xRuntime` provides a High-Level Emulation (HLE) layer replacing the PS2 kernel, IOP, SIF, and GS subsystems
3. `game_overrides.cpp` contains targeted hooks that bypass PS2-specific hardware synchronization loops
4. The output runs natively on x86-64 Linux/Windows via Raylib/OpenGL

---

## Build Instructions

### Requirements
- CMake 3.20+
- GCC 12+ or Clang 15+ (C++20)
- Raylib

### Steps
```bash
git clone https://github.com/YYOzcan/Tobiichi-Port.git
cd Tobiichi-Port/PS2Recomp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### Running
```bash
./build/ps2xRuntime/ps2EntryRunner /path/to/SCUS_973.99 --window
```

> **Note:** `SCUS_973.99` and `PART1.PAK` are copyrighted game files and are **not** included in this repository. You must own a legal copy of the game.

---

## Current Status

| Milestone | Status |
|-----------|--------|
| ELF analysis & recompilation | ✅ Done |
| Basic PS2 kernel (threads, semaphores) | ✅ Done |
| GS (Graphics Synthesizer) frame output | ✅ Done |
| IOP synchronization stubs | ✅ Done |
| SCEA logo screen renders | ✅ Done |
| Main game thread activation | 🔄 In Progress |
| Title screen / Main menu | ⏳ Pending |
| Playable level | ⏳ Pending |

---

## Contributing

This project is under active development. Feel free to fork, open issues, or submit pull requests.

**Team / Collaborators:** [@YYOzcan](https://github.com/YYOzcan)

---

## License

This project contains no copyrighted game assets. The tooling and runtime code is provided under the same license as [PS2Recomp](https://github.com/ran-j/PS2Recomp).
