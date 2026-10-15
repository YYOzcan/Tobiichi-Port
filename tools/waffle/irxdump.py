"""Full disassembly of an IRX with import names: python -I tools/irxdump.py IRX > out.txt
jal targets that are import stubs are shown as <library>#<ordinal>; data words of .data/.rodata follow the code."""
import struct
import sys

import capstone

m = open(sys.argv[1], 'rb').read()
shoff = struct.unpack_from('<I', m, 32)[0]
shnum = struct.unpack_from('<H', m, 48)[0]
shstr = struct.unpack_from('<H', m, 50)[0]
so = struct.unpack_from('<10I', m, shoff + shstr * 40)[4]
secs = {}
for i in range(shnum):
    n, t, f, a, o, s = struct.unpack_from('<6I', m, shoff + i * 40)
    secs[m[so + n:m.index(b'\0', so + n)].decode()] = (a, o, s)
img = bytearray(max(a + s for a, o, s in secs.values()))
for name, (a, o, s) in secs.items():
    if name in ('.text', '.data', '.rodata') and s:
        img[a:a + s] = m[o:o + s]
stubs = {}
i = 0
while i < len(img) - 4:
    if struct.unpack_from('<I', img, i)[0] == 0x41E00000:
        lib = img[i + 12:i + 20].split(b'\0')[0].decode(errors='replace')
        j = i + 20
        while j + 8 <= len(img):
            w0, w1 = struct.unpack_from('<II', img, j)
            if w0 == 0x03E00008 and (w1 & 0xFFFF0000) == 0x24000000:
                stubs[j] = f'{lib}#{w1 & 0xFFFF}'
                j += 8
            else:
                break
        i = j
    else:
        i += 4
ta, to, ts = secs['.text']
md = capstone.Cs(capstone.CS_ARCH_MIPS, capstone.CS_MODE_MIPS32 | capstone.CS_MODE_LITTLE_ENDIAN)
md.skipdata = True  # keep going over words capstone cannot decode
print(f'; {sys.argv[1]}: .text 0x{ta:x}+0x{ts:x}; imports: ' + ', '.join(sorted(set(v.split("#")[0] for v in stubs.values()))))
for ins in md.disasm(bytes(img[ta:ta + ts]), ta):
    extra = ''
    if ins.mnemonic in ('jal', 'j'):
        t = int(ins.op_str, 16)
        if t in stubs:
            extra = f'   ; -> {stubs[t]}'
    if ins.address in stubs:
        extra = f'   ; import stub {stubs[ins.address]}'
    print(f'{ins.address:05x}: {ins.mnemonic:7s} {ins.op_str}{extra}')
for name in ('.rodata', '.data'):
    if name in secs and secs[name][2]:
        a, o, s = secs[name]
        print(f'; {name} 0x{a:x}+0x{s:x}')
        for k in range(a, a + s, 16):
            words = struct.unpack_from('<4I', img, k) if k + 16 <= len(img) else ()
            text = ''.join(chr(c) if 32 <= c < 127 else '.' for c in img[k:k + 16])
            print(f'{k:05x}: ' + ' '.join(f'{w:08x}' for w in words) + f'  {text}')
