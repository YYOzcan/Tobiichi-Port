"""Disassemble an IRX (R3000, relocatable at base 0). usage: irxdis.py IRX [--find STRING] [--at HEX [N]]
--find lists code locations referencing the string (lui/addiu or lui/ori pairs on its address)."""
import capstone, struct, sys
m = open(sys.argv[1], 'rb').read()
shoff = struct.unpack_from('<I', m, 32)[0]; shnum = struct.unpack_from('<H', m, 48)[0]; shstr = struct.unpack_from('<H', m, 50)[0]
so = struct.unpack_from('<10I', m, shoff + shstr * 40)[4]
secs = {}
for i in range(shnum):
    n, t, f, a, o, s = struct.unpack_from('<6I', m, shoff + i * 40)
    secs[m[so + n:m.index(b'\0', so + n)].decode()] = (a, o, s)
ta, to, ts = secs['.text']
img = bytearray(max(a + s for a, o, s in secs.values()))
for name, (a, o, s) in secs.items():
    if name in ('.text', '.data', '.rodata') and s:
        img[a:a + s] = m[o:o + s]
md = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS32 | capstone.CS_MODE_LITTLE_ENDIAN)
md.detail = False
code = list(md.disasm(bytes(img[ta:ta + ts]), ta))
if '--find' in sys.argv:
    target = img.find(sys.argv[sys.argv.index('--find') + 1].encode())
    print('string at', hex(target))
    hi = {}
    for i in code:
        if i.mnemonic == 'lui':
            r, v = i.op_str.split(', '); hi[r] = int(v, 0) << 16
        elif i.mnemonic in ('addiu', 'ori'):
            ops = i.op_str.split(', ')
            if len(ops) == 3 and ops[1] in hi:
                v = int(ops[2], 0)
                if i.mnemonic == 'addiu' and v >= 0x8000: v -= 0x10000
                if v < 0 and i.mnemonic == 'addiu': pass
                if (hi[ops[1]] + v) & 0xffffffff == target:
                    print('ref at', hex(i.address))
if '--at' in sys.argv:
    k = sys.argv.index('--at'); a = int(sys.argv[k + 1], 16); n = int(sys.argv[k + 2]) if len(sys.argv) > k + 2 else 60
    for i in code:
        if a <= i.address < a + 4 * n:
            print('  %05x: %-7s %s' % (i.address, i.mnemonic, i.op_str))
