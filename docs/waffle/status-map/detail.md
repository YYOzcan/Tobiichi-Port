# Status detail

Generated from `data.toml` by `tools/status_map.py`; do not edit by hand.

## Sony SDK libraries (100.0%, 647 functions)

| Library | Functions | State | Note |
|---|---:|---|---|
| libmpeg | 103 | ✅ ok | Movies play at real speed with sound (native libmpeg2 decoder, native sound engine); audio trails picture ~0.1 s, constant |
| libipu | 5 | ✅ ok | Served by the native decoder |
| libgraph | 7 | ✅ ok | Display setup is a native override (GS display state, no GS register access) |
| libdma | 8 | ✅ ok | sceDmaSend feeds VIF/GIF directly; no DMA controller model |
| libcdvd | 10 | ✅ ok | CD reads served from the extracted game files (disc-usa/); the ISO only with GOW_ISO |
| libdbc | 11 | ✅ ok | dbcman RPC answered by native pad services |
| libpad2 | 13 | ✅ ok | Native pad read on the EE (keyboard / gamepad) |
| libvib | 2 | ✅ ok | DualShock 2 actuators -> host gamepad rumble (Windows: XInput pads, DualShock 4 / DualSense over USB through HID, Bluetooth opt-in; raylib elsewhere); verified by the user on a real DualShock 4 over USB (2026-10-13) |
| libmc2 | 90 | ✅ ok | Native memory-card service; load and save verified (savetest) |
| libscf | 14 | ✅ ok |  |
| libgcc | 32 | ✅ ok |  |
| C++ EH | 34 | ✅ ok |  |
| libm | 14 | ✅ ok |  |
| libc | 150 | ✅ ok |  |
| libkernel | 101 | ✅ ok | Runs natively; DelayThread on the scheduler, no timer register access |
| sif | 24 | ✅ ok | RPC as direct native calls |
| fileio | 15 | ✅ ok |  |
| loadfile | 14 | ✅ ok |  |

## PS2 hardware (100.0%)

| Group | Component | Weight | State |
|---|---|---:|---|
| EE | R5900 CPU: game code statically recompiled to C++ (6.4k functions) | 5 | ✅ ok |
| EE | Kernel: threads, semaphores, alarms, syscalls (native HLE) | 3 | ✅ ok |
| EE | FPU (COP1) and MMI instructions | 2 | ✅ ok |
| EE | INTC: not accessed by game code in gameplay | 2 | ✅ ok |
| EE | DMA controller: no model, packets go straight to VIF/GIF | 2 | ✅ ok |
| EE | Timers: native EE clock (game code calls it, counts computed from guest cycles); T2 users (DelayThread) on the scheduler | 1 | ✅ ok |
| GS / VU | GS: native OpenGL render-target renderer, 2x internal, 16:9; display registers native | 3 | ✅ ok |
| GS / VU | VIF1 decoded directly; VU1 microprograms compiled ahead of time to C++ | 3 | ✅ ok |
| GS / VU | Textures and CLUT: native texture store; palettes from render targets read on the GPU | 2 | ✅ ok |
| GS / VU | GIF (PATH1-3): the game's GIF tags fed to the renderer | 2 | ✅ ok |
| GS / VU | IPU: replaced by the native MPEG-2 decoder (libmpeg2); movies play at real speed with sound | 2 | ✅ ok |
| IOP | R3000A CPU: no interpreter on the hot path | 3 | ✅ ok |
| IOP | SPU2: native sound engine driven by LIBSD's exports | 3 | ✅ ok |
| IOP | The game's 8 IRX modules compiled ahead of time to C++ | 2 | ✅ ok |
| IOP | SIF: RPC and DMA as direct native calls | 2 | ✅ ok |
| IOP | CDVD: the game's reads served from the extracted files (no drive model) | 2 | ✅ ok |
| IOP | Pad: native service (SIO2 chip model deleted) | 2 | ✅ ok |
| IOP | Memory card: native service, load/save verified | 2 | ✅ ok |
