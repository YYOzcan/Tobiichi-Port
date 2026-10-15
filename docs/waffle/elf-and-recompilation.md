# ELF and recompilation

## SCES_531.33
- Entry 0x100008. One PT_LOAD, RWX, vaddr 0x100000, filesz 0x1C9078, memsz 0x25F080. File offset = vaddr − 0xFF000.
- No symbols. Sections: `.text` 0x100000–0x29C7E4 (~1.6 MB, flags AX), `.data` 0x29C800 size 0x16900 (flags **WAX**:
  marked executable!), `.rodata` 0x2B3100, `.bss` 0x2C9080 size 0x95328 (ends 0x35E3A8).
- 24 `.DVP.overlay.*` sections = VU microcode (VU1 rendering), named overlays; not EE code.
- SDK 3.0 libraries: libkernl, libcdvd (only init/sync/mmode/dualinfo/poweroff), libdma, libipu+libmpeg (FMV),
  libpad2 + libdbc (controller), libmc2, libscf, libgraph; Sony 989snd (EE side) talks to IOP 989snd.
- `.data` contains kernel patch blobs that run at 0x8007xxxx (TLB handlers, from libkernl) — not game code.
- `.data` 0x2A5410 (857 bytes) is an embedded IRX "ck01" (see game-internals.md, sceChk01).

## Config: port/gow.toml
- Generated once by ps2_analyzer (82 SDK functions bound to runtime handlers by signature), then edited:
  - `ghidra_output = "port/functions.csv"` (our function map).
  - `skip = [...]` 6 kernel blobs in .data (no longer needed with the map, kept harmless).
  - **`patches.instructions` emptied.** The analyzer had added 73 "Potential self-modifying code" patches that
    turn instructions into NOPs. All 73 were ordinary `sw` stores into `.data` (flagged because `.data` is WAX).
    One of them (0x26C808, sets 989snd's pending-batch pointer 0x2A30C8) broke loading. Never re-add such patches.
  - `patch_cop0 = true`, `patch_cache = true` left as generated.

## Function discovery (tools/find_functions.py → port/functions.csv)
The stripped analyzer misses functions reached only indirectly. The map = union of:
1. starts already known to the recompiler (port/output file names),
2. all JAL targets,
3. J targets, data words in .data/.rodata pointing into .text, and code-built addresses (`lui`+`addiu`/`ori`
   within 8 instructions) — each only if it sits on a function boundary (right after `jr $ra` or a tail-call `j`
   plus its delay slot, optionally followed by nop padding),
4. minus pointer runs that look like switch jump tables (≥3 adjacent text pointers spanning < 4 KB).
Ends = next start (clamped to .text end). Current count **6482**.
Missing functions show at runtime as `[guest-branch:missing-target] … target=0x…`. Found so far: 0x29C7B8/0x29C7D0
(static ctor/dtor stubs from the ctor table at 0x2A7F2C), 0x1D4EA8 (indirect call target, address built in code).
Fix = improve find_functions.py, regenerate, full rebuild.

## Recompiler facts
- Generated calls go through `runtime->dispatchGuestBranch` / the function table, so
  `PS2Runtime::replaceFunction`/`bindAddressHandler` reliably intercept them.
- Entry points inside a function get `case` labels in a `switch(ctx->pc)` at the top of the generated function.
- MFC0/MTC0 Count now emit `runtime->readCop0Count()`/`writeCop0Count()` (our change; see runtime-changes.md).
- Game has only 2 `mfc0 Count`, 18 `mfc0 Status`, a few mtc0 (Status/EPC/ErrorEPC/Wired); no performance counters.

## Recompiler translation bugs fixed (2026-10-09; verified against PCSX2 FPU.cpp / VUops.cpp)
- COP1 `SQRT.S fd, ft`: operand is ft (fs unused on the R5900); was translated with fs. Now fd = sqrt(|ft|).
- COP1 `RSQRT.S fd, fs, ft`: fd = fs / sqrt(|ft|); was 1/sqrt(fs). Zero/denormal ft → sign(ft)|FLT_MAX.
- COP1 `DIV.S`: zero/denormal divisor → sign(fs^ft)|FLT_MAX (was ±INF); overflow clamps to ±FLT_MAX.
- VU0 macro `VDIV`/`VSQRT`/`VRSQRT`: |ft|, fs used by VRSQRT, divide-by-zero → ±FLT_MAX.
- Runtime macros (ps2xRuntime/include/ps2_runtime_macros.h, PCH → full rebuild): `FPU_CVT_W_S` used nearbyintf
  (round to nearest) — R5900 CVT.W.S truncates and saturates (ps2_fcvt_w). FPU add/sub/mul and VU0 PS2_VADD/VSUB/VMUL
  now clamp to ±FLT_MAX (no Inf/NaN on PS2). Host rounding is still round-to-nearest (PS2: toward zero) — **open**.
- **BLEZ/BGTZ/BLTZ/BGEZ (+L, +AL, +ALL) tested only the low 32 bits** (GPR_S32) — the R5900 tests the full
  64-bit register. Broke 64-bit code, e.g. the soft-float double library (`dsubu` then `bltz` in 0x285328 negated
  results). Fixed in control_flow_emitter.cpp (GPR_S64). Found with the EE differential tester.
- Disassembly comments show unnamed COP1 ops as `c1 0x4` (sqrt.s) — the generated C++ is what counts.
