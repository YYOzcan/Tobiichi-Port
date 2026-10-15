# Disc

## The disc
- User's redump: `iso/God of War (Europe, Australia) (En,Fr,De,Es,It).iso`, 8,018,624,512 bytes, PAL, SCES-53133.
  `SYSTEM.CNF`: `BOOT2 = cdrom0:\SCES_531.33;1`, `VER = 1.00`, `VMODE = PAL`.
- Dual-layer DVD, **UDF bridge** (ISO9660 + UDF). Sector 16 PVD (volume "GODOFWAR", publisher SCEE),
  17 terminator, 18 `BEA01`, 19 `NSR02`, 20 `TEA01`, UDF anchor area further on. Root directory LBA 261.
- Layer 0 volume size 1,902,128 sectors. Layer 1 has its own PVD at sector 1,902,128; its extents are relative to
  **1,902,112** (= layer0 size − 16). The drive exposes both layers as one linear LSN range.

| LSN | Size (bytes) | File |
|---|---|---|
| 281 | 56 | SYSTEM.CNF |
| 282 | 1,919,260 | SCES_531.33 (main ELF) |
| 1220 | 278,305 | IOPRP300.IMG (IOP reboot image) |
| 1356–1507 | | SIO2MAN, DBCMAN, SIO2D, MC2_S1, DS1O_S1, MC2_D, DS2U_D, LIBSD, 989NOMID, SMPD_IOP .IRX |
| 1532 | 51,900 | GODOFWAR.TOC |
| 1558 | 3,892,353,024 | PART1.PAK (layer 0) |
| 1,902,379 | 4,122,523,648 | PART2.PAK (layer 1, its directory only) |

## GODOFWAR.TOC
Entries of 24 bytes: name[12] (e.g. `R_PERMF.WAD`), u32 part/flags, u32 size, u32 sector offset inside the PAK
(e.g. `R_PERMG.WAD` sector 0x707, `R_PERMU.WAD` size 0x37F280 sector 0x1C19). Some entries pack other info in the
part word (e.g. BONUS*.PSS) — **not decoded**. Language variants by last letter: F G I S U (U = English).

## Extraction (user requirement: no ISO reads at runtime)
`python -I tools/iso_extract.py <iso> disc --layout` extracts all 16 files (both layers) and writes:
- `disc/.disc_layout` — text: `sectors 3915344`, `layer1 1902112`, then `file <lsn> <size> <name>` per file.
- `disc/.disc_meta` — 88 records of (u32 LSN + 2048 bytes): every non-zero sector not belonging to a file
  (volume descriptors, UDF structures, directories, path tables), 176 KB.
Extraction verified byte-exact by sampling PAK offsets against the ISO.

## Why the exact layout matters
The game's streaming IRX **SMPD_IOP reads raw sectors** (cdvdman sceCdRead, no sceCdSearchFile): PVD (16),
root directory (261), GODOFWAR.TOC (1532…), then PAK data by absolute LSN. PS2Recomp's original loose-file mode
synthesizes a different virtual ISO, so nothing loaded. The extracted layout reproduces the disc sector for sector.

## DiscSource (ps2xIOP, our component)
`ps2xIOP/include/ps2x/iop/disc_source.h`, `src/disc_source.cpp`:
- `DiscSource::openImage(iso)` and `DiscSource::openExtracted(dir)` (needs `dir/.disc_layout`).
- `readSectors(lsn, count, dst)` (extracted: meta sector → file at original LSN → zeros),
  `findFile("cdrom0:\\NAME;1")` (case-insensitive, `;1` ignored), `layer1Start()`.
- Used by IOP cdvdman (search + reads, image if `IoPaths::cdImage` set, else extracted CD root, else the old virtual
  ISO) and by EE `sceCdReadDvdDualInfo`.

## USA build (no-emulation step 6, 2026-10-12)
- The USA runtime (ext/PS2Recomp-kl) uses the same `DiscSource` (ps2xIOP `disc_source.{h,cpp}`) in its HLE cdvdman
  (`iop_cdvd.cpp`): `sceCdRead` and `sceCdSearchFile` go to the configured image if `GOW_ISO` is set, otherwise to
  the files extracted next to the ELF (`disc-usa/`, cdRoot = ELF directory). A CD read is a host file read at the
  file's offset; there is no drive model. The virtual ISO (PS2Recomp's synthesized layout) is only the fallback for a
  folder without `.disc_layout`.
- `configureGowCdImage` (gow_overrides.cpp) no longer looks for an .iso next to the ELF: only an explicit `GOW_ISO`
  selects the image (comparisons); `play.cmd`, `tools/zones.py` and `tools/savetest.py` run from the extracted files
  (`--iso` in the tools for the image).
- `disc-usa/` holds the full extraction of the USA disc (`iso_extract.py --layout`: 16 files, `.disc_layout` with
  4,161,520 sectors and layer 1 at 2,080,544, `.disc_meta` 88 sectors). Verified 2026-10-12 against the ISO: 100 file
  samples (head, tail, random offsets incl. both PAKs) and all 88 metadata sectors byte-identical.
- The EE side never reads raw sectors in gameplay (no `sceCdRead unresolved` in the zone runs); `cdrom0:` file opens
  are served from the same folder.
- The EE `cdrom0:` VFS (sceOpen/sceRead) still serves loose files from `disc/` (cdRoot = ELF directory).
