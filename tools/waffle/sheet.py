"""Contact sheet of gow_pad_test_<i>.png captures (half size, 4 columns).
usage: python -I tools/sheet.py <capture dir> <first> <last> <out.png>"""
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


folder, first, last, out_path = sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), sys.argv[4]
images = [read_png(f"{folder}/gow_pad_test_{i}.png") for i in range(first, last + 1)]
w, h = images[0][0] // 2, images[0][1] // 2
cols = 4
rows_n = (len(images) + cols - 1) // cols
out = [bytearray(w * cols * 3) for _ in range(h * rows_n)]
for k, (_, _, rows) in enumerate(images):
    cx, cy = (k % cols) * w, (k // cols) * h
    for y in range(h):
        src, line = rows[y * 2], out[cy + y]
        for x in range(w):
            line[(cx + x) * 3:(cx + x) * 3 + 3] = src[x * 6:x * 6 + 3]
raw = b''.join(b'\x00' + bytes(line) for line in out)
png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w * cols, h * rows_n, 8, 2, 0, 0, 0))
png += chunk(b'IDAT', zlib.compress(raw, 6)) + chunk(b'IEND', b'')
open(out_path, 'wb').write(png)
