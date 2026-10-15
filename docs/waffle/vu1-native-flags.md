# VU1 native blocks: flag latency across blocks (character shadows)

Character shadows are drawn by a shadow-volume pass:
- the game clears G to 127 and inverts Z;
- it draws the volume twice (front faces G += 255 = -1, back faces G += 1, COLCLAMP=0 wraps);
- it copies G's top bits to alpha (8 px CT16 strips);
- it darkens wherever the count is not zero (DATE).

The two halves of the volume differ only by the ADC bits that the VU1 culling loop writes. For example, at 0x3C38
`FMEQ vi8` tests the sign of the `MSUBy.x` issued exactly 4 pairs earlier, across the loop branch, and `ISW.w` stores
the ADC word. So the culling is only right if MAC/clip flags become visible exactly 4 cycles (`kFmacLatency`) after
their writer, across block boundaries too.

## Why the former model had no shadows
The former model committed, at a block's exit, the newest flag writer of that block. The loop above then read the
flags of its own last pair, so both halves of the volume were culled the same way:
- Desert: 332 / 332 triangles;
- PCSX2: 311 / 381;
- PCSX2's interpreter in our build: 282 / 370.

Every pixel netted to zero. The exact engine (`GOW_VU1_SIN_COMPILAR=1 GOW_VU1_NATIVE_OFF=1`) draws the shadows.

## The model (the only one; ps2_vu1_native.h / .inl, tools/vu1/vu1n_gen.py)
**Flags inside a block.** A reader at pair i sees the newest writer of the block issued at least 4 cycles before it,
on the block's issue cycles `n.cyc`. Flags older than the block come from the flag rings.

**Flag rings** (`VU1FlagRing`, MAC and clip):
- They hold the last 4 writers. The VU issues at most one FMAC / CLIP per cycle, so 4 writers cover the latency
  window.
- A native block pushes only its newest writer. MAC writers are pushed with their unclamped FMAC result and DEST
  mask, and the flags are computed only when something reads them (`vu1n::macValRt`).
- The older writers that can still be the visible one after the exit are those whose successor lies in the block's
  last three pairs. Their values go unconditionally into the block's tail record (`VU1FlagTail` in its history
  entry), and a static `VU1TailDesc` from the generator says which pairs and masks they are.
- A reader that meets an invisible ring entry checks that entry's tail record (`tailVisible`).
- Entry and exit go through the exact engine's flag pipeline (`importFlags / exportFlags`, tail records expanded).

**Entry timing.** A block that reads flags written before it gets its exact issue cycles from the pipeline state at
entry. Every other block uses its idle-pipeline table.
- Lane readiness (VF/VI/ACC) is not tracked per block. The last 64 native blocks are kept in `NativeState::hist`, and
  a lane's ready cycle is derived from its newest writer (`walkHistory`).
- Only blocks that ended less than `maxLat` cycles ago can still hold a lane in flight.
- Lanes not written since native entry come from the exact engine's readiness arrays. These are only read while
  `arraysReadyBy` (cleared at every program start) is in the future.
- The stall model runs once per distinct in-flight state (cached per block, 16 entries).
- When the previous block ran for `maxLat` cycles or more and nothing from the exact engine is in flight, the
  predecessor (block + timing table) alone decides the entry state. Its result is memoized in the dispatch slot; the
  shadow loop at 0x0d00 hits this every iteration.

**Exit.** When the exact engine takes over, the readiness arrays get the lanes still in flight (`syncInflight`).

**Dispatch.** Everything the loop touches per block is in one 64-byte `Slot` per pc: function, idle table, memo,
FDIV/EFU starts.

## Cost
Replay benchmark: 4000 recorded VU1 runs at the end of the Olympus zone walk, 5 warm passes.

| Build | Time | Notes |
|---|---|---|
| Former model | 62.7 ms | |
| First latency version (opt-in, shadows2) | 122 ms | |
| This model | 77-79 ms | |

In game (`GOW_VU1_STATS`, zone gate port/shadows3/gate): 3.3-3.6 ns per VU1 cycle in slots 1-4 (former model 2.7,
shadows2 opt-in 4.8); all zones 60 fps, game speed 1.00.

What the remaining cost is: the newest-writer ring push and tail stores per block (≈ 1/3), the history entry per
block, and the entry-timing walk for flag-reading blocks that miss the memo.

How it was measured:
- `GOW_VU1N_RECORD=<file> GOW_VU1N_RECORD_SKIP=8000000` records runs from the heavy part of a zone run.
- `GOW_VU1N_REPLAY=<file> GOW_VU1N_REPLAY_REPS=6` replays them and prints the time (port/shadows3/bench.sh).
- `tools/sample_prof.py` samples the runner's threads by function, with a /MAP link.

## Verification
`GOW_VU1N_VERIFY` compares native with the exact engine per run. Integer-like words (GIF data, the ADC bit) are
compared exactly, and bisection targets ADC mismatches.

Mismatches with this model:

| Zone | Mismatches | Runs | Rate | Shadows2 opt-in |
|---|---|---|---|---|
| Olympus | 8527 | 890k | 0.96 % | 0.95 % |
| Cliffs | 133 | 852k | 0.016 % | 0.016 % |
| Desert | 3135 | 750k | 0.42 % | 0.34 % |

In Desert almost all mismatches come from one scene late in the walk (5 in the first 400k runs, then ~9 per 1000), so
the rate depends on how much of it a slow verify run reaches.

The mismatch kinds are the same as before: 1-unit rounding (`0000822e/0000822f`) and the few `ffff/0000` and
`0400/0000` words on near-degenerate triangles. No reserved instructions.

Diagnostics:
- `GOW_GS_HW_VOLTRACE=<n>`: triangles per half, and G after the volume.
- `GOW_VU1_KICKPRIM=<prim>`.
- `GOW_VU1_FMANDPC=<pc>`: ours and PCSX2's interpreter.
- `GOW_VU1_STARTMAC=1`.
- `GOW_VU1N_VERIFY` (`GOW_VU1N_DUMP=1` writes the run's micro memory).
- `GOW_VU1N_DIAG=1`: native pairs, misses and native entries per 5 s.
- RT dumps also write alpha (`_a.pgm`).
