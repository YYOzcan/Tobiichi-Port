#!/usr/bin/env python3
"""GOW-Port: línea de tiempo del controlador de movimientos de Kratos (cancelar_tramo.bin con la región 79f300-79f500).
Uso: linea_cancelar.py <tramo.bin> [t0 t1]"""
import struct, sys
F = 16 + 0x200
d = open(sys.argv[1], "rb").read()
t0, t1 = (float(sys.argv[2]), float(sys.argv[3])) if len(sys.argv) > 3 else (0, 1e9)
offs = [0x44, 0x54, 0x58, 0x60, 0x70, 0x78, 0x1ac]
print("t      bot  " + " ".join(f"{o:>9x}" for o in offs))
prev = None
for i in range(len(d) // F):
    t, bot = struct.unpack_from("<dH", d, i * F)
    if not t0 <= t <= t1:
        continue
    row = [struct.unpack_from("<I", d, i * F + 16 + o)[0] for o in offs]
    b = (~bot) & 0xFFFF
    s = ("SQ" if b & 0x8000 else "") + ("L1" if b & 0x400 else "") + ("TR" if b & 0x1000 else "")
    if row != prev or s:
        print(f"{t:.2f} {s:4} " + " ".join(f"{v:9x}" for v in row))
        prev = row
