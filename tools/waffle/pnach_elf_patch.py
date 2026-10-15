#!/usr/bin/env python3
"""Apply the code-word ("word") patches of a PCSX2 .pnach section to a COPY of a PS2 ELF.

The game code is statically recompiled, so PCSX2 code rewrites (patch=N,EE,<addr>,word,<value>) must be
baked into the ELF that is fed to the recompiler. Data / "extended" codes are applied by the runtime and are
only listed here (with a warning for 32-bit extended writes that target code: those need recompiled-code
support, see port/agents/widescreen/REPORT.md).

EE virtual addresses are mapped to file offsets through the ELF program headers (PT_LOAD, file-backed part
only); addresses outside every loadable segment (or in .bss-like memsz-only space) are refused.

Usage:
  python -I tools/pnach_elf_patch.py IN.elf OUT.elf PNACH [--section NAME] [--set ADDR=VALUE ...] [--dry-run]
  PNACH may be a .pnach file or ZIP:MEMBER, e.g.
    ref/pcsx2/resources/patches.zip:SCUS-97399_D6385328.pnach
"""
import argparse
import re
import struct
import sys
import zipfile
from pathlib import Path

PT_LOAD = 1
PF_X = 1

PATCH_RE = re.compile(r"^patch\s*=\s*(\d+)\s*,\s*(EE|IOP)\s*,\s*([0-9A-Fa-f]+)\s*,\s*(\w+)\s*,\s*([0-9A-Fa-f]+)", re.I)


def read_pnach(spec):
    p = Path(spec)
    if p.is_file():
        return p.read_text(encoding="utf-8", errors="replace")
    # ZIP:MEMBER (the zip path itself may contain ':' as in C:/..., so split on the last one)
    if ":" in spec:
        zpath, member = spec.rsplit(":", 1)
        with zipfile.ZipFile(zpath) as z:
            return z.read(member).decode("utf-8", errors="replace")
    sys.exit(f"error: cannot read pnach {spec!r}")


def parse_sections(text):
    """Return {section_name: [(lineno, place, cpu, addr, kind, value, raw)]}; '' = before any section."""
    sections = {"": []}
    current = ""
    for no, raw in enumerate(text.splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith("//") or line.startswith(";"):
            continue  # fully commented lines are ignored, exactly like PCSX2
        m = re.match(r"^\[(.+)\]$", line)
        if m:
            current = m.group(1).strip()
            sections.setdefault(current, [])
            continue
        m = PATCH_RE.match(line)
        if m:
            place, cpu, addr, kind, value = m.groups()
            sections[current].append((no, int(place), cpu.upper(), int(addr, 16), kind.lower(), int(value, 16), raw))
    return sections


class Elf:
    def __init__(self, data):
        if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
            sys.exit("error: not a 32-bit little-endian ELF")
        self.data = data
        phoff, = struct.unpack_from("<I", data, 0x1C)
        shoff, = struct.unpack_from("<I", data, 0x20)
        phentsize, phnum, shentsize, shnum, shstrndx = struct.unpack_from("<HHHHH", data, 0x2A)
        self.loads = []
        for i in range(phnum):
            p_type, p_offset, p_vaddr, _paddr, p_filesz, p_memsz, p_flags, _align = struct.unpack_from(
                "<8I", data, phoff + i * phentsize)
            if p_type == PT_LOAD:
                self.loads.append((p_vaddr, p_offset, p_filesz, p_memsz, p_flags))
        self.sections = []
        if shoff and shnum and shstrndx < shnum:
            def sh(i):
                return struct.unpack_from("<10I", data, shoff + i * shentsize)
            stroff = sh(shstrndx)[4]
            for i in range(shnum):
                name, _t, _f, addr, _o, size = sh(i)[:6]
                end = data.index(b"\0", stroff + name)
                self.sections.append((data[stroff + name:end].decode(errors="replace"), addr, size))

    def offset(self, vaddr, size=4):
        """File offset of [vaddr, vaddr+size) or None if not entirely in one file-backed PT_LOAD."""
        for p_vaddr, p_offset, p_filesz, _memsz, flags in self.loads:
            if p_vaddr <= vaddr and vaddr + size <= p_vaddr + p_filesz:
                return p_offset + (vaddr - p_vaddr), flags
        return None

    def section_of(self, vaddr):
        for name, addr, size in self.sections:
            if addr and addr <= vaddr < addr + size:
                return name
        return "?"


def disasm(word, addr):
    try:
        import capstone  # optional; capstone mis-decodes some R5900-only ops (MMI, lq/sq, VU0 macro)
        md = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS64 | capstone.CS_MODE_LITTLE_ENDIAN)
        for ins in md.disasm(struct.pack("<I", word), addr):
            return f"{ins.mnemonic} {ins.op_str}".strip()
    except Exception:
        pass
    return "?"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf_in")
    ap.add_argument("elf_out")
    ap.add_argument("pnach", help=".pnach file or ZIP:MEMBER")
    ap.add_argument("--section", help="pnach section name, e.g. 'Widescreen 16:9' (default: the only section "
                                      "that has word patches)")
    ap.add_argument("--set", action="append", default=[], metavar="ADDR=VALUE",
                    help="extra code word to write (hex), applied after the pnach words")
    ap.add_argument("--dry-run", action="store_true", help="only print what would change")
    args = ap.parse_args()

    if Path(args.elf_in).resolve() == Path(args.elf_out).resolve():
        sys.exit("error: refusing to patch the input ELF in place; give a different output path")

    sections = parse_sections(read_pnach(args.pnach))
    with_words = [name for name, items in sections.items() if any(i[4] == "word" for i in items)]
    if args.section is None:
        if len(with_words) != 1:
            sys.exit(f"error: choose --section; sections with word patches: {with_words}")
        args.section = with_words[0]
    if args.section not in sections:
        sys.exit(f"error: section {args.section!r} not found; sections: {[s for s in sections if s]}")
    items = sections[args.section]

    data = bytearray(Path(args.elf_in).read_bytes())
    elf = Elf(bytes(data))

    words = []
    for no, place, cpu, addr, kind, value, raw in items:
        if kind == "word" and cpu == "EE":
            words.append((addr, value & 0xFFFFFFFF, f"pnach line {no}"))
        elif kind == "word":
            print(f"skip   line {no}: {cpu} word patch (only EE is supported)")
    for item in args.set:
        try:
            a, v = item.split("=", 1)
            words.append((int(a, 16), int(v, 16) & 0xFFFFFFFF, "--set"))
        except ValueError:
            sys.exit(f"error: bad --set {item!r} (expected HEXADDR=HEXVALUE)")

    errors = 0
    changed = 0
    print(f"section [{args.section}]: {len(words)} code words; PT_LOAD segments: " +
          ", ".join(f"vaddr 0x{v:X} off 0x{o:X} filesz 0x{f:X} memsz 0x{m:X} flags {fl}"
                    for v, o, f, m, fl in elf.loads))
    for addr, value, origin in words:
        if addr & 3:
            print(f"ERROR  0x{addr:08X}: unaligned word address ({origin})")
            errors += 1
            continue
        hit = elf.offset(addr)
        if hit is None:
            print(f"ERROR  0x{addr:08X}: outside every file-backed loadable segment ({origin})")
            errors += 1
            continue
        off, flags = hit
        old, = struct.unpack_from("<I", data, off)
        note = "" if flags & PF_X else "  [WARNING: segment not executable]"
        state = "same " if old == value else "patch"
        print(f"{state}  0x{addr:08X} off 0x{off:06X} [{elf.section_of(addr)}] {old:08X} -> {value:08X}  "
              f"{disasm(old, addr):<28} -> {disasm(value, addr)}  ({origin}){note}")
        if old != value:
            struct.pack_into("<I", data, off, value)
            changed += 1

    # Extended codes stay runtime-side; flag 32-bit writes into code, they need recompiled-code support.
    for no, place, cpu, addr, kind, value, raw in items:
        if kind != "extended":
            continue
        if (addr >> 28) == 0x2:
            target = addr & 0x0FFFFFFF
            sec = elf.section_of(target)
            if sec == ".text":
                hit = elf.offset(target)
                old = struct.unpack_from("<I", data, hit[0])[0] if hit else None
                print(f"NOTE   line {no}: extended 32-bit write to CODE 0x{target:08X} = {value:08X} "
                      f"({disasm(value, target)}; ELF now {old:08X}) -> runtime code word, needs special handling")

    if errors:
        sys.exit(f"{errors} error(s); nothing written")
    if args.dry_run:
        print(f"dry run: {changed} word(s) would change")
        return
    Path(args.elf_out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.elf_out).write_bytes(bytes(data))
    print(f"wrote {args.elf_out}: {changed} word(s) changed")


if __name__ == "__main__":
    main()
