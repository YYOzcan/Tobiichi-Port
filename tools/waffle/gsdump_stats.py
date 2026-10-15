"""Summarise a PCSX2 GS dump (.gs, uncompressed): transfers per path, and per-transfer GIF tag signatures.

usage: python -I tools/gsdump_stats.py dump.gs [--path N] [--list]
"""
import struct
import sys
from collections import Counter


def transfers(path):
    d = open(path, 'rb').read()
    hs = struct.unpack_from('<I', d, 4)[0]
    ss = struct.unpack_from('<I', d, 12)[0]
    pos = 8 + hs + ss + 0x2000
    frame = 0
    while pos < len(d):
        t = d[pos]
        pos += 1
        if t == 0:
            p = d[pos]
            size = struct.unpack_from('<I', d, pos + 1)[0]
            yield frame, p, d[pos + 5:pos + 5 + size]
            pos += 5 + size
        elif t == 1:
            pos += 1
            frame += 1
        elif t == 2:
            pos += 4
        elif t == 3:
            pos += 0x2000
        else:
            break


def tags(data):
    """GIF tags of a transfer: (nloop, flg, nreg, prim, regs-hex)."""
    out = []
    off = 0
    while off + 16 <= len(data):
        lo, hi = struct.unpack_from('<QQ', data, off)
        off += 16
        nloop = lo & 0x7FFF
        flg = (lo >> 58) & 3
        nreg = (lo >> 60) & 0xF or 16
        prim = (lo >> 47) & 0x7FF if (lo >> 46) & 1 else None
        out.append((nloop, flg, nreg, prim, f'{hi & ((1 << (4 * nreg)) - 1):X}'))
        if flg == 0:
            off += nloop * nreg * 16
        elif flg == 1:
            off += ((nloop * nreg + 1) // 2) * 16
        else:
            off += nloop * 16
        if lo & 0x8000:
            break
    return out


def main():
    path = sys.argv[1]
    only = int(sys.argv[sys.argv.index('--path') + 1]) if '--path' in sys.argv else None
    counts = Counter()
    for frame, p, data in transfers(path):
        if frame > 0:
            break
        counts[p] += 1
        if '--list' in sys.argv and (only is None or p == only):
            print(p, len(data), tags(data)[:3])
    print('transfers per path (frame 0):', dict(counts))


if __name__ == '__main__':
    main()
