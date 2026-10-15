"""Decode a PSMCT32/PSMCT24 framebuffer from a 4 MB GS VRAM image to PNG.

usage: python -I tools/gsfb.py VRAM.bin FBP(hex, 2048-word units) FBW(64-px units) WIDTH HEIGHT out.png
"""
import struct
import sys
import zlib

BLOCK32 = [[0, 1, 4, 5, 16, 17, 20, 21], [2, 3, 6, 7, 18, 19, 22, 23],
           [8, 9, 12, 13, 24, 25, 28, 29], [10, 11, 14, 15, 26, 27, 30, 31]]
COLUMN32 = [[0, 1, 4, 5, 8, 9, 12, 13], [2, 3, 6, 7, 10, 11, 14, 15],
            [16, 17, 20, 21, 24, 25, 28, 29], [18, 19, 22, 23, 26, 27, 30, 31],
            [32, 33, 36, 37, 40, 41, 44, 45], [34, 35, 38, 39, 42, 43, 46, 47],
            [48, 49, 52, 53, 56, 57, 60, 61], [50, 51, 54, 55, 58, 59, 62, 63]]


def main():
    vram = open(sys.argv[1], 'rb').read()
    fbp, fbw = int(sys.argv[2], 16), int(sys.argv[3])
    width, height = int(sys.argv[4]), int(sys.argv[5])
    rows = bytearray()
    for y in range(height):
        rows.append(0)
        for x in range(width):
            page = fbp + (y // 32) * fbw + (x // 64)
            word = page * 2048 + BLOCK32[(y % 32) // 8][(x % 64) // 8] * 64 + COLUMN32[y % 8][x % 8]
            off = (word * 4) & 0x3FFFFF
            rows += vram[off:off + 3]
    def chunk(kind, body):
        return struct.pack('>I', len(body)) + kind + body + struct.pack('>I', zlib.crc32(kind + body) & 0xFFFFFFFF)
    png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', width, height, 8, 2, 0, 0, 0))
    png += chunk(b'IDAT', zlib.compress(bytes(rows), 6)) + chunk(b'IEND', b'')
    open(sys.argv[6], 'wb').write(png)


if __name__ == '__main__':
    main()
