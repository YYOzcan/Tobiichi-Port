"""Compare two GS VRAM images page by page (8 KB pages, 512 per 4 MB).

usage: python -I tools/vramdiff.py OURS.bin PCSX2_GS.bin
PCSX2_GS.bin is GS.bin from a PCSX2 save state; the 4 MB VRAM inside it is located by best match with OURS.
"""
import sys

PAGE = 8192
VRAM = 4 * 1024 * 1024


def main():
    ours = open(sys.argv[1], 'rb').read()
    blob = open(sys.argv[2], 'rb').read()
    if len(blob) == VRAM:
        ref, offset = blob, 0
    else:
        best = None
        for offset in range(0, len(blob) - VRAM + 1, 4):
            score = sum(ours[p:p + 64] == blob[offset + p:offset + p + 64] for p in range(0, VRAM, PAGE * 8))
            if best is None or score > best[0]:
                best = (score, offset)
        offset = best[1]
        ref = blob[offset:offset + VRAM]
    print(f'pcsx2 VRAM offset in blob: {offset}')
    rows = []
    for page in range(VRAM // PAGE):
        a = ours[page * PAGE:(page + 1) * PAGE]
        b = ref[page * PAGE:(page + 1) * PAGE]
        same = sum(x == y for x, y in zip(a, b)) / PAGE
        empty_a = a.count(0) == PAGE
        empty_b = b.count(0) == PAGE
        rows.append((page, same, empty_a, empty_b))
    # Map: one char per page, 32 pages per line (= 256 KB). '=' identical, '~' >90%, '.' both empty,
    # 'o' only ours has data, 'p' only pcsx2 has data, 'x' different.
    for line in range(0, len(rows), 32):
        chars = []
        for page, same, ea, eb in rows[line:line + 32]:
            if ea and eb:
                chars.append('.')
            elif same == 1.0:
                chars.append('=')
            elif same > 0.9:
                chars.append('~')
            elif ea:
                chars.append('p')
            elif eb:
                chars.append('o')
            else:
                chars.append('x')
        print(f'{line * PAGE:06X} {"".join(chars)}')


if __name__ == '__main__':
    main()
