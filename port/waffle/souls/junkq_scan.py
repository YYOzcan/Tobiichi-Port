"""Which draws of a PCSX2 GS dump send ST-only vertices whose ST word-2 (Q) differs from the RGBAQ.Q in effect.
Those draws rendered with junk Q before ext c25562c (PACKED ST latch). usage: python port/souls/junkq_scan.py dump.gs"""
import struct, sys
sys.path.insert(0, 'tools')
from gsdump_stats import transfers
from collections import defaultdict
st = {'tex0': 0, 'prim': 0}
q_vert = 1.0; q_latch = 1.0; bad = defaultdict(lambda: [0, 0])
for frame, p, data in transfers(sys.argv[1]):
    if frame > 0: break
    off = 0
    while off + 16 <= len(data):
        lo, hi = struct.unpack_from('<QQ', data, off); off += 16
        nloop = lo & 0x7FFF; flg = (lo >> 58) & 3; nreg = (lo >> 60) & 0xF or 16
        if (lo >> 46) & 1: st['prim'] = (lo >> 47) & 0x7FF
        q_latch = 1.0
        if flg == 0:
            regs = [(hi >> (4 * r)) & 0xF for r in range(nreg)]
            for i in range(nloop * nreg):
                if off + 16 > len(data): break
                reg = regs[i % nreg]; w = struct.unpack_from('<4I', data, off); f = struct.unpack_from('<4f', data, off); off += 16
                if reg == 0xE:
                    a = w[2] & 0xFF; v = w[0] | (w[1] << 32)
                    if a in (6, 7): st['tex0'] = v
                    elif a == 0: st['prim'] = v & 0x7FF
                    elif a == 1: q_vert = struct.unpack('<f', struct.pack('<I', w[1]))[0]
                elif reg == 0: st['prim'] = w[0] & 0x7FF
                elif reg == 2: q_latch = f[2]
                elif reg == 1: q_vert = q_latch
                elif reg in (4, 5, 0xC, 0xD):
                    k = (st['tex0'] & 0x3FFF, st['prim'])
                    bad[k][1] += 1
                    # old code: vertex Q = ST word 2 of the last ST write
                    if (st['prim'] >> 4) & 1 and not (st['prim'] >> 8) & 1 and q_latch != q_vert: bad[k][0] += 1
        elif flg == 1:
            n = nloop * nreg; off += n * 8 + (8 if n % 2 else 0)
        else:
            off += nloop * 16
for (tbp, prim), (b, n) in sorted(bad.items(), key=lambda x: -x[1][0]):
    if b: print(f'tbp={tbp:x} prim={prim:x} junk-Q vertices {b}/{n}')
