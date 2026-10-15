"""Print heartbeat peek lines from a run log as hex words + ASCII. usage: peek.py LOG [max_lines]"""
import re, struct, sys
n = int(sys.argv[2]) if len(sys.argv) > 2 else 64
for line in open(sys.argv[1], 'rb').read().decode('latin1').splitlines():
    m = re.match(r'\s*peek ((?:iop:)?[0-9A-F]{8}):((?: [0-9A-F]{8})+)', line)
    if m:
        data = b''.join(struct.pack('<I', int(w, 16)) for w in m.group(2).split())
        print(m.group(1), m.group(2).strip(), ''.join(chr(b) if 32 <= b < 127 else '.' for b in data))
        n -= 1
        if n == 0:
            break
