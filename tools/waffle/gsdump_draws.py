"""Per-draw summary of frame 0 of a PCSX2 GS dump (.gs, uncompressed): TEX0 tbp/cbp, PRIM, TEST, ALPHA, FRAME, ZMSK, TFX/TCC, max vertex RGB/A, Z/X/Y ranges.

usage: python -I tools/gsdump_draws.py dump.gs [TBP_HEX]
"""
import struct, sys
sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__)))
from gsdump_stats import transfers
path = sys.argv[1]; want = int(sys.argv[2], 16) if len(sys.argv) > 2 else None
st = {'tex0': 0, 'prim': 0, 'test': 0, 'alpha': 0, 'frame': 0, 'zbuf': 0, 'rgba': (0, 0, 0, 0), 'clamp': 0, 'tex1': 0}
groups = []
cur = None
def key():
    return (st['tex0'], st['prim'], st['test'], st['alpha'], st['frame'], st['zbuf'])
def vert(x, y, z):
    global cur
    k = key()
    if cur is None or cur['k'] != k:
        cur = {'k': k, 'n': 0, 'rgba': [], 'z': [], 'x': [], 'y': []}
        groups.append(cur)
    cur['n'] += 1; cur['rgba'].append(st['rgba']); cur['z'].append(z); cur['x'].append(x); cur['y'].append(y)
AD = {0x00: 'prim', 0x06: 'tex0', 0x07: 'tex0', 0x47: 'test', 0x48: 'test', 0x42: 'alpha', 0x43: 'alpha', 0x4c: 'frame', 0x4d: 'frame', 0x4e: 'zbuf', 0x4f: 'zbuf', 0x08: 'clamp', 0x14: 'tex1'}
for frame, p, data in transfers(path):
    if frame > 0: break
    off = 0
    while off + 16 <= len(data):
        lo, hi = struct.unpack_from('<QQ', data, off); off += 16
        nloop = lo & 0x7FFF; flg = (lo >> 58) & 3; nreg = (lo >> 60) & 0xF or 16
        if (lo >> 46) & 1: st['prim'] = (lo >> 47) & 0x7FF
        if flg == 0:
            for _ in range(nloop):
                for r in range(nreg):
                    if off + 16 > len(data): break
                    reg = (hi >> (4 * r)) & 0xF
                    w = struct.unpack_from('<4I', data, off)
                    if reg == 0xE:
                        a = w[2] & 0xFF; v = w[0] | (w[1] << 32)
                        if a in AD: st[AD[a]] = v
                    elif reg == 0:
                        st['prim'] = w[0] & 0x7FF
                    elif reg == 1:
                        st['rgba'] = (w[0] & 0xFF, w[1] & 0xFF, w[2] & 0xFF, w[3] & 0xFF)
                    elif reg == 4:
                        vert((w[0] & 0xFFFF) / 16, (w[1] & 0xFFFF) / 16, (w[2] >> 4) & 0xFFFFFF)
                    elif reg == 5:
                        vert((w[0] & 0xFFFF) / 16, (w[1] & 0xFFFF) / 16, w[2])
                    off += 16
        elif flg == 1:
            regs = [(hi >> (4 * r)) & 0xF for r in range(nreg)]
            for i in range(nloop * nreg):
                if off + 8 > len(data): break
                v = struct.unpack_from('<Q', data, off); v = v[0]; off += 8
                reg = regs[i % nreg]
                if reg == 0: st['prim'] = v & 0x7FF
                elif reg == 1: st['rgba'] = (v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF, (v >> 24) & 0xFF)
                elif reg in (4, 0xC): vert((v & 0xFFFF) / 16, ((v >> 16) & 0xFFFF) / 16, (v >> 32) & 0xFFFFFF)
                elif reg in (5, 0xD): vert((v & 0xFFFF) / 16, ((v >> 16) & 0xFFFF) / 16, v >> 32)
                elif reg == 6: st['tex0'] = v
            if (nloop * nreg) % 2: off += 8
        else:
            off += nloop * 16
for i, g in enumerate(groups):
    tex0, prim, test, alpha, frm, zb = g['k']
    tbp = tex0 & 0x3FFF
    if want is not None and tbp != want and not (want == -1): continue
    rs = g['rgba']; cm = max(max(c[:3]) for c in rs); am = max(c[3] for c in rs)
    tfx = (tex0 >> 35) & 3; tcc = (tex0 >> 34) & 1; cbp = (tex0 >> 37) & 0x3FFF
    print(f"#{i} n={g['n']} tbp={tbp:x} cbp={cbp:x} prim={prim:x} test={test:x} alpha={alpha:x} fbp={frm & 0x1FF:x} zmsk={(zb >> 32) & 1} tfx={tfx} tcc={tcc} cmax={cm} amax={am} z={min(g['z']):x}-{max(g['z']):x} x={min(g['x']):.0f}-{max(g['x']):.0f} y={min(g['y']):.0f}-{max(g['y']):.0f}")
