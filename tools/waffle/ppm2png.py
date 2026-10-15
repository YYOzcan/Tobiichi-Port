"""Convert a binary PPM (P6) to PNG. usage: python -I tools/ppm2png.py in.ppm out.png"""
import struct
import sys
import zlib

data = open(sys.argv[1], 'rb').read()
parts = data.split(b'\n', 3)
width, height = map(int, parts[1].split())
pixels = parts[3]
rows = b''.join(b'\x00' + pixels[y * width * 3:(y + 1) * width * 3] for y in range(height))


def chunk(kind, body):
    return struct.pack('>I', len(body)) + kind + body + struct.pack('>I', zlib.crc32(kind + body) & 0xFFFFFFFF)


png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', width, height, 8, 2, 0, 0, 0))
png += chunk(b'IDAT', zlib.compress(rows, 6)) + chunk(b'IEND', b'')
open(sys.argv[2], 'wb').write(png)
