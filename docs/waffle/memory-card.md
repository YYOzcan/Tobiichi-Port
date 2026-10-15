# PS2 memory card: format facts for the native memory-card service

Goal (docs/native-port.md, standing order step 1): replace the hardware path EE libmc2 -> DBCMAN RPC -> MC2_D.IRX ->
SIO2MAN -> SIO2 chip model -> raw card image with a native service that implements the card file system directly on
the same image file (`GOW_MC0`, PCSX2 `.ps2` format).

## How the game reaches the card today
- MC2_D.IRX registers **no RPC server** (no `sifcmd` import). Imports: sysmem, sysclib, thbase, thsemap, vblank, sio2man,
  secrman, cdvdman, dbcman, sio2d. It is a driver under DBCMAN, like the pad driver DS2U_D: the EE talks to both pad and
  card through DBCMAN's RPC (`0x80001300` family).
- So pad + card become native together (the EE pad calls are already native: gow_overrides.cpp scePad2*).

## Card image (`.ps2`), verified in ref/pcsx2-src/pcsx2/SIO/Memcard/MemoryCardFolder.h / MemoryCardFile.cpp
- Page = 512 data bytes + 16 spare (ECC) bytes = 528 raw bytes; cluster = 2 pages (1024 data bytes); erase block =
  16 pages (8 clusters). 8 MB card: 16384 pages, file size 8,650,752 bytes (0x840000). Raw offset of data byte b of
  page p: p * 528 + b.
- ECC: 12 bytes per page (3 per 128-byte quarter, Hamming; `CalculateECC` in MemoryCardFile.cpp / MemoryCardFolder.cpp),
  rest of the spare area padding. Readers may ignore it; writers must keep it valid for the real hardware path and
  for PCSX2 (compute it like `CalculateECC`).
- Superblock (page 0): magic "Sony PS2 Memory Card Format " (0x00, 28), version (0x1C, 12), page_len u16 (0x28),
  pages_per_cluster u16 (0x2A), pages_per_block u16 (0x2C), clusters_per_card u32 (0x30), alloc_offset u32 (0x34),
  alloc_end u32 (0x38), rootdir_cluster u32 (0x3C, relative to alloc_offset), backup_block1/2 u32 (0x40/0x44),
  ifc_list[32] u32 (0x50), bad_block_list[32] u32 (0xD0), card_type u8 (0x150, 2 = PS2), card_flags u8 (0x151).
- FAT: superblock ifc_list -> indirect FAT clusters (256 u32 each) -> FAT clusters (256 u32 entries, one per allocatable
  cluster). Entry: bit 31 = in use, bits 0-30 = next cluster (relative to alloc_offset); 0x7FFFFFFF = end of chain
  (stored 0xFFFFFFFF). Free cluster: bit 31 clear. Data cluster c is physical cluster alloc_offset + c.
- Directory entry, 512 bytes (2 per cluster): mode u32 (0x00; 0x10 file, 0x20 dir, 0x8000 exists, 0x0400 PS2 save,
  rwx bits 0x1/0x2/0x4; defaults dir 0x8427, file 0x8497), length u32 (0x04; bytes for a file, entry count incl. "." and
  ".." for a directory), created time (0x08, 8 bytes: unused, sec, min, hour, day, month, year u16), cluster u32 (0x10;
  first cluster, 0xFFFFFFFF for an empty file), dirEntry u32 (0x14; in a subdir's "." = its index in the parent),
  modified time (0x18), attr u32 (0x20), name[32] (0x40). Entry 0 = ".", entry 1 = "..".

## The game's card protocol (captured 2026-10-11, PS2X_TRACE_RPC=800013, boot + save load, port/rpc2)
- **The card file system runs on the EE** (libmc2); the IOP side (DBCMAN + MC2_D) only moves raw pages. A native service
  therefore only has to answer raw page commands from the card image; the game keeps doing its own file system.
- DBCMAN main server 0x80001300 (0x90-byte buffers, synchronous): fn 0x80001363 version check; fn 0x80001304
  (words 0x310, 0x30CF40 = an EE buffer); fn 0x80001301 twice = socket creation, buffer `3 2 {2|3} 0 0 "MC2SOCKET"`
  (memory-card sockets on ports 2 and 3).
- MC2 socket server **0x8000131C** (fn 0x8000131C, mode 1 = asynchronous, send/receive 0x2090 bytes, ~270 calls/s).
  Send words: `0, cmd, 0x2080, page, count, 0x200 (page size), 0x10 (spare size), 0x4000`. Counts seen:
  cmd 1 x31354 (read `count` pages from `page`; pages advance by 2 = one cluster), cmd 4 x975 (about once per frame:
  status poll), cmd 6 x8 and cmd 0xC x8 (around the save load), cmd 0xD x1, cmd 3 x1 (all other words 0: probe/identify).
- Still to find: the reply layout of each command (receive buffer after completion: data + spare, status words) and the
  meaning of cmds 3/4/6/0xC/0xD (MC2_D dispatch), plus the write/erase commands (only seen when saving).

## Native card I/O (2026-10-11, ext 6ef7583)
- MC2_D (cmd dispatch 0x1f74; status block 0x4418 / status word 0x4420 / data buffer 0x4498, sent to the EE by DBCMAN
  signal-data) stays the game's own compiled code. Its six routines that talked to the card over SIO2 are replaced by
  native C++ on the card image (ps2xIOP/src/native/iop_native_overrides.cpp, tools/iop/native_overrides.txt):
  read_page 0x0c8c (port, slot, page, size, stack+0x10 = IOP dst) -> 1/0; write_page 0x0fdc (port, slot, page, IOP src,
  stack+0x10 = size); erase_block 0x0a98 (port, slot, first page); get_specs 0x13a8 (port, slot, u32 out[2] =
  0x00100200, 0x4000); init_card 0x0650 and probe 0x164c (port, slot) -> 1 when a card is present (a real card echoes
  the 0x55 terminator the driver sets, which gives 1). Ports 2/3 = card slots 1/2.
- Verified with tools/savetest.py (load slot 1, R2 at the save point, Yes / slot / overwrite Yes): "Save Complete",
  129 pages written, root directory intact, the saved card loads into gameplay (port/savetest3, port/saveload1).

## Still to find (next)
- Done: SIO2D's probes are native too (pad probe 0x0978 -> none, card probe 0x0a1c -> card image present on port 2/3),
  MC2_D's F3 check 0x08d8 native; no SIO2 transfer exists, the SIO2 model is deleted (ext 2026-10-11).
