"""Find where an IRX module was loaded in an IOP RAM dump (e.g. iopMemory.bin from a PCSX2 save state).

usage: python -I tools/irxfind.py IOPRAM.bin MODULE.irx [MODULE.irx ...]
Matches the module's text with relocated instruction words (j/jal/lui and their partner immediates) masked out.
"""
import struct
import sys


def load_segment(path):
    d = open(path, 'rb').read()
    phoff = struct.unpack_from('<I', d, 0x1C)[0]
    phnum = struct.unpack_from('<H', d, 0x2C)[0]
    for i in range(phnum):
        t, off, va, pa, fs = struct.unpack_from('<5I', d, phoff + i * 32)
        if t == 1:
            return d[off:off + fs]
    raise ValueError('no PT_LOAD')


def stable_words(seg, start, count):
    out = []
    for k in range(count):
        w = struct.unpack_from('<I', seg, start + 4 * k)[0]
        op = w >> 26
        out.append(None if op in (2, 3, 0x0F, 0x09, 0x23, 0x2B, 0x21, 0x25, 0x20, 0x24, 0x29, 0x28) else w)
    return out


def main():
    ram = open(sys.argv[1], 'rb').read()
    for path in sys.argv[2:]:
        seg = load_segment(path)
        hits = {}
        for probe in range(0x40, min(len(seg) - 128, 0x1000), 0x40):
            pattern = stable_words(seg, probe, 32)
            anchor = next(i for i, w in enumerate(pattern) if w is not None)
            needle = struct.pack('<I', pattern[anchor])
            pos = ram.find(needle)
            while pos != -1:
                base = pos - 4 * anchor - probe
                if base >= 0 and base % 4 == 0 and base + probe + 128 <= len(ram) and all(w is None or struct.unpack_from('<I', ram, base + probe + 4 * i)[0] == w
                                     for i, w in enumerate(pattern)):
                    hits[base] = hits.get(base, 0) + 1
                pos = ram.find(needle, pos + 4)
        best = sorted(hits.items(), key=lambda kv: -kv[1])[:3]
        print(path.replace(chr(92), '/').split('/')[-1],' '.join(f'0x{b:X}({n})' for b, n in best))


if __name__ == '__main__':
    main()
