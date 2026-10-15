"""Per-texture vertex extents in the first frame of a PCSX2 GS dump (to compare two dumps object by object).

usage: python -I tools/gsdump_objects.py a.gs [b.gs]
"""
import struct
import sys
from collections import defaultdict

sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__)))
from gsdump_stats import transfers  # noqa: E402


def objects(path):
    stats = defaultdict(lambda: [0, 1 << 30, -1, 1 << 30, -1, 0])  # count, xmin, xmax, ymin, ymax, adcSkipped
    tex0 = 0
    for frame, p, data in transfers(path):
        if frame > 0:
            break
        off = 0
        while off + 16 <= len(data):
            lo, hi = struct.unpack_from('<QQ', data, off)
            off += 16
            nloop = lo & 0x7FFF
            flg = (lo >> 58) & 3
            nreg = (lo >> 60) & 0xF or 16
            if flg == 0:
                for _ in range(nloop):
                    for r in range(nreg):
                        if off + 16 > len(data):
                            break
                        reg = (hi >> (4 * r)) & 0xF
                        w = struct.unpack_from('<4I', data, off)
                        if reg == 0xE:  # A+D
                            addr = w[2] & 0xFF
                            if addr == 0x06:
                                tex0 = w[0] | (w[1] << 32)
                        elif reg in (4, 5):
                            s = stats[tex0 & 0x3FFF]
                            if w[3] & 0x8000:
                                s[5] += 1
                            else:
                                x, y = (w[0] & 0xFFFF) / 16.0, (w[1] & 0xFFFF) / 16.0
                                s[0] += 1
                                s[1] = min(s[1], x); s[2] = max(s[2], x)
                                s[3] = min(s[3], y); s[4] = max(s[4], y)
                        off += 16
            elif flg == 1:
                off += ((nloop * nreg + 1) // 2) * 16
            else:
                off += nloop * 16
    return stats


def main():
    a = objects(sys.argv[1])
    b = objects(sys.argv[2]) if len(sys.argv) > 2 else {}
    for tbp in sorted(set(a) | set(b)):
        def fmt(s):
            if not s or s[0] == 0:
                return f'{"-":>34}'
            return f'{s[0]:6d} x[{s[1]:7.0f},{s[2]:7.0f}] y[{s[3]:7.0f},{s[4]:7.0f}]'
        print(f'TBP {tbp:04X}  A:{fmt(a.get(tbp))}   B:{fmt(b.get(tbp))}')


if __name__ == '__main__':
    main()
