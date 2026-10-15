# Changes to the IOP emulator (ps2xIOP)

ps2xIOP runs the game's real IRX modules on an R3000 interpreter with an HLE kernel. All changes below are generic,
in `ext/PS2Recomp/ps2xIOP`, uncommitted.

## Memory: one sysmem pool
- Before: bump allocator 0x120000–0x1F0000 (832 KB) that never reused freed blocks; IRX images used a separate
  cursor from 0x10000; QueryMaxFreeMemSize = space above the cursor. 989snd: "failed to allocate memory".
- Now (`core/iop_memory.{h,cpp}`): single pool **0x10000–0x1F0000**, first-fit over gaps, allocations kept sorted,
  `maxFreeMemory` = largest gap; relocatable IRX images are allocated from it (`IopModuleLoader::load(image, memory)`,
  `moduleCursor`/`kModuleLoadBase` plumbing removed). Call stacks remain at 0x1F0000–0x1FFF00.

## Module start arguments
- loadcore calls `start(argc, argv)`. Before: start(byteLength, rawBuffer). Now argv[0] = module path, then one
  pointer per NUL-separated argument string, NULL-terminated, allocated in IOP RAM (`iop_emulator.cpp` loadImage).

## Module buffers from IOP RAM
- `sceSifLoadModuleBuffer`'s address is IOP RAM (image DMA'd into an sceSifAllocIopHeap block). The loader read EE
  RAM. Now `IopModuleLoader::readElf(reader, addr)` tries IOP RAM first, EE RAM as fallback
  (`services/iop_module_loader.*`, `iop_emulator.cpp` loadModuleBuffer).

## RPC server functions run as IOP threads
- Before: `IopRpcBridge::handleRpc` ran the IRX server function with `callFunction` (no thread). A WaitSema there
  (no current thread) neither blocked nor set v0 → the server replied before its worker thread finished.
- Now: `IopGuestExecutor::executeGuestFunctionAsThread` (iop_rpc.h) — `IopKernel::createTransientThread` (priority 10,
  8 KB stack), the scheduler (`scheduleOnce`, factored out of `runCycles`) runs until the thread returns
  (budget 150M IOP cycles, warning if exceeded), then `removeThread`. The EE call stays synchronous.

## sysclib/stdio formatting
- New `imports/iop_format.{h,cpp}`: printf formatter (d i u x X o c s p %, flags, width/precision incl. `*`,
  h/l/ll) with O32 varargs (`iopRegisterVarargs`: remaining a-registers then caller stack sp+16) or va_list
  (`iopVaListVarargs`). Used by sysclib 19 sprintf, 42 vsprintf, stdio 4 printf, 9 fdprintf, 14 vfdprintf.
  Before, the format was copied verbatim → SMPD built names like "%s…" and resource opens failed.

## sifcmd / sifman
- sifcmd 23 `sceSifGetOtherData(rdata, eeSrc, iopDst, size, mode)`: was a stub returning 0 without copying; now
  copies EE RAM → IOP RAM (iop_rpc.cpp).
- sifman 7 sceSifSetDma (IOP→EE) already worked; added `[sifdma]` trace under PS2X_TRACE_RPC.
- sifman 8 sceSifDmaStat returns −1 (complete) always.

## cdvdman / disc
- Reads and sceCdSearchFile go through `DiscSource` (see disc.md); image if configured, else extracted layout in
  the CD root, else upstream's virtual ISO. Opt-in `PS2X_TRACE_CDVD`.
- sceCdSC(−9) returns kCdvdmanVersion 0x226 (ck01 passes). sceCdSC(−23) LSN translation is identity (linear LSN).

## Diagnostics added
`PS2X_TRACE_IOP_IMPORTS` (iop_emulator.cpp), `PS2X_TRACE_RPC` (iop_rpc.cpp), `PS2X_TRACE_CDVD`, `PS2X_TRACE_SIO2`.

## SIO2 + DualShock 2 (2026-10-09, working end to end: input reaches the game)
- `core/iop_sio2.{h,cpp}`: `IopSio2` serves 0x1F808200–0x1F808283: SEND3[16] 0x200+4i, SEND1/2 0x240+8i,
  FIFO in 0x260 (byte write), FIFO out 0x264 (byte read, pops), CTRL 0x268 (bit0 start → transfer; 0xC bits = reset
  FIFOs), RECV1 0x26C (0x1100 connected / 0x1D100 none — matches game traffic), RECV2 0x270 = 0xF, RECV3 = 0,
  ISTAT 0x280 (bit0 set after transfer, W1C).
- Transfer: for each non-zero SEND3: port = bits 0-1, length = bits 8-16 (verified: e.g. 0x00140540 = port 0, 5 bytes); input from DMA ch 11
  block i (if requested) else FIFO; device chosen by first byte (0x01 = pad, ports 0/1); response to DMA ch 12
  block i or FIFO out. Non-pad / unplugged → 0xFF bytes, disconnected.
- DualShock 2 model per port: modes 0x41/0x73/0x79, config mode 0xF3; commands 0x40 0x41 0x42 0x43 0x44 0x45 0x46
  0x47 0x4C 0x4D 0x4F with standard replies (pressure bytes 0xFF when pressed). Default mode digital (0x41).
- `IopMemory::attachSio2` routes the range; on transfer completion IRQ 0x11 is queued (400 cycles) through the
  interrupt queue `m_dmaStarts` (was a single optional; now a deque drained in `schedulePendingDma`).
- `dmacman`: ordinal 28 (dmac_request) → `IopSio2::dmaRequest(ch, addr, blockWords, blockCount)` (channels 11/12),
  28/32 (dmac_transfer) return 1, others 0 (all were stubbed to 0 before). 33/34 was wrong (seen in the import trace).
- CTRL: reset bits (0xC) clear the FIFOs only on a write without the start bit (SIO2MAN writes 0x3BC|1).
- Driver chain (from the IRX code): SIO2D probes each port (len-5 `01 42`), calls the driver table registered with
  sio2d:6 — DS2U_D table at module+0x2260: +0xC probe (0x1A8C, claims mode 0x41/0x73/0x79 via sio2d:9(dev,0)),
  +0x10 connect (0x1B24, StartThread of the poll thread). DS2U_D polls once per WaitVblankStart (vblank:4).
  sio2d:9(dev, n) returns dev+8 (mode id) for n=0, dev+0 for 1, dev+4 for 2.
- `IopHost::readPad(port, state)` (iop_host.h, default false) supplies controller state; runtime implements it.
- SIO2 DMA completion IRQs (0x2B/0x2C) are not raised (SIO2MAN appears to wait on IRQ 0x11 only — **unverified**).

## IOP facts learned
- Interrupts are HLE: intrman RegisterIntrHandler/EnableIntr; `IopIntrman::dispatchInterrupt(irq)` calls the handler
  with a 100k-instruction budget. DMA irq numbers: SPU 0x24/0x28; SIO2 = 0x11.
- Hardware registers are a map in IopMemory; SPU2 DMA (CHCR 0x1F8010C8 / 0x1F801548) only signals completion
  (no data, no audio).
- Physical IRX RPC servers are authoritative for their SID; HLE services (MCSERV, LIBSD, DBCMAN) only answer when no
  IRX serves that SID. The HLE DBCMAN only answers a version query.
- `dmacman` was stubbed to 0 entirely before our change.

## Module start() runs as an IOP thread (2026-10-09)
- `loadImage` used `callFunction(entry, …)` (no current thread). SIO2D/DS2U_D call SIO2MAN (WaitSema + event-flag
  handshake with SIO2MAN's worker thread) from their start code; with no thread, WaitEventFlag returned at once,
  leaving bits (e.g. 0x1409) set, so every later caller wait was satisfied by the previous transaction's bits.
  Found with `PS2X_TRACE_EVF` ("thread -1" waits). Now `executeGuestFunctionAsThread(entry, …)` (same as RPC servers).
- SIO2MAN protocol (event flag bits): client lock 1→ack 2 (sio2man:61, 0x874) or 4→8 (63, 0x8A4); transfer
  0x400→done 0x800 (51, 0xA94); unlock 0x1000 (62); worker waits 0x4155 / 0x1400, IRQ handler sets 0x2000.

## sifman 32 sceSifSetDmaIntr (2026-10-09)
- Was unimplemented (default case returned 0, no copy). DBCMAN sends controller data to the EE socket buffers
  with it (callback DBCMAN+0x2F4). Now handled like sceSifSetDma (7) plus the completion callback, run by the
  emulator right after the import returns (`IopRpcBridge::takeDmaCallbacks`).

## SIO2 aligned with PCSX2 (pcsx2/SIO/Sio2.cpp, GPL-3.0+)
- SEND3: port = bit 0 (bit 1 is not a port), length mask 0x3FF. RECV1 rebuilt per packet: +0x100 one port /
  0x200 two ports, |0x1000, missing pad on port 0 |0x1D000, port 1 |0x2D000; memory card/other → 0x1D100.
- DMA out: each reply padded with zeros to its DMA block. Pad protocol replies were already byte-identical to
  PCSX2's PadDualshock2 for the commands this game uses.
- Drivers' view (from disassembly): SIO2D +0x1518 treats a port as missing if RECV1 bit 13 or bit 16 is set.
  DS2U_D builds SEND3 as (old & ~3) | port | 0x40 and treats (RECV1 >> 14) & 3 == 0 as connected.
