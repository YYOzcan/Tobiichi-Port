"""Side-by-side crops of capture PNGs, scaled 2x (to compare a detail across runs).
usage: python -I tools/crop.py <x> <y> <w> <h> <out.png> <in.png>..."""
import struct
import sys
import zlib



def read_png(path):
    data = open(path, 'rb').read()
    i, width, height, idat = 8, 0, 0, b''
    while i < len(data):
        n = struct.unpack('>I', data[i:i + 4])[0]
        kind, body = data[i + 4:i + 8], data[i + 8:i + 8 + n]
        if kind == b'IHDR':
            width, height = struct.unpack('>II', body[:8])
        elif kind == b'IDAT':
            idat += body
        i += 12 + n
    raw = zlib.decompress(idat)  # filter type 0 rows, as written by tools/ppm2png.py
    stride = width * 3
    return width, height, [raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)] for y in range(height)]


def chunk(kind, body):
    return struct.pack('>I', len(body)) + kind + body + struct.pack('>I', zlib.crc32(kind + body) & 0xFFFFFFFF)


x, y, w, h = (int(v) for v in sys.argv[1:5])
out, inputs = sys.argv[5], sys.argv[6:]
rows = [bytearray() for _ in range(h * 2)]
for path in inputs:
    _, _, pixels = read_png(path)
    for r in range(h):
        line = pixels[y + r][x * 3:(x + w) * 3]
        wide = b''.join(line[i:i + 3] * 2 for i in range(0, len(line), 3)) + b'\0\0\0' * 4
        rows[r * 2] += wide
        rows[r * 2 + 1] += wide
total = len(rows[0]) // 3
raw = b''.join(b'\0' + bytes(r) for r in rows)
png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', total, h * 2, 8, 2, 0, 0, 0))
png += chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b'')
open(out, 'wb').write(png)
