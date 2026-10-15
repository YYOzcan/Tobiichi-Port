"""Build a function-map CSV (PS2Recomp ghidra_output format) for the stripped GoW ELF.
Starts = functions already known to the recompiler (port/output file names)
       + JAL targets
       + J targets and data pointers (minus jump tables) that sit on a function boundary (right after `jr $ra`/`j` + delay slot,
         optionally followed by nop padding). Ends = next start (clamped to .text end).
usage: find_functions.py ELF OUTPUT_DIR CSV"""
import os, re, struct, sys

elf, outdir, csv = sys.argv[1:4]
d = open(elf, 'rb').read()
FILE_BASE = 0x100000 - 0x1000          # vaddr - file offset of the single PT_LOAD
TEXT_START, TEXT_END = 0x100000, 0x29C7E4
DATA_RANGES = [(0x29C800, 0x2B3100), (0x2B3100, 0x2C9078)]   # .data, .rodata
JR_RA, NOP = 0x03E00008, 0

def ends_function(w):
    return w == JR_RA or (w >> 26) == 2      # `jr $ra` or tail-call `j`

def word(addr):
    return struct.unpack_from('<I', d, addr - FILE_BASE)[0]

def on_boundary(addr):
    a = addr - 4
    while a >= TEXT_START and word(a) == NOP and a >= addr - 64:
        if a - 4 >= TEXT_START and ends_function(word(a - 4)):   # the nop was the delay slot
            return True
        a -= 4
    return a - 4 >= TEXT_START and ends_function(word(a - 4))     # `a` is a non-nop delay slot

starts = set()
for name in os.listdir(outdir):
    m = re.match(r'(?:sub|entry)_([0-9A-Fa-f]{8})', name)
    if m:
        starts.add(int(m.group(1), 16))
known = len(starts)

jal, jmp = set(), set()
for a in range(TEXT_START, TEXT_END, 4):
    w = word(a)
    op = w >> 26
    if op in (2, 3):
        t = ((a + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
        if TEXT_START <= t < TEXT_END:
            (jal if op == 3 else jmp).add(t)
def is_text_ptr(w):
    return TEXT_START <= w < TEXT_END and w % 4 == 0

# Runs of >=3 adjacent text pointers spanning <4 KB are switch jump tables: their targets are case
# labels inside one function, not function starts.
ptrs = set()
for lo, hi in DATA_RANGES:
    run = []
    for a in range(lo, hi + 4, 4):
        w = word(a) if a < hi else 0
        if is_text_ptr(w):
            run.append(w)
            continue
        if not (len(run) >= 3 and max(run) - min(run) < 0x1000):
            ptrs.update(run)
        run = []

# Addresses materialized in code (lui rX, hi ; addiu/ori rY, rX, lo within a few instructions), e.g. function
# pointers stored into tables at runtime.
built = set()
for a in range(TEXT_START, TEXT_END, 4):
    w = word(a)
    if w >> 26 != 0x0F:  # lui
        continue
    rt, hi = (w >> 16) & 31, (w & 0xFFFF) << 16
    for b in range(a + 4, min(a + 32, TEXT_END), 4):
        x = word(b)
        op, rs = x >> 26, (x >> 21) & 31
        if rs == rt and op in (0x09, 0x0D):  # addiu / ori
            lo = x & 0xFFFF
            value = (hi + (lo - 0x10000 if op == 0x09 and lo & 0x8000 else lo)) & 0xFFFFFFFF
            if TEXT_START <= value < TEXT_END and value % 4 == 0:
                built.add(value)
            break

starts |= jal
starts |= {t for t in jmp | ptrs | built if on_boundary(t)}
starts = sorted(s for s in starts if TEXT_START <= s < TEXT_END)

with open(csv, 'w') as f:
    f.write('name,start,end,size\n')
    for i, s in enumerate(starts):
        e = starts[i + 1] if i + 1 < len(starts) else TEXT_END
        f.write(f'sub_{s:08X},0x{s:08X},0x{e:08X},{e - s}\n')
print(f'known {known}, jal {len(jal)}, ptr-candidates {len(ptrs)}, code-built {len(built)}, total starts {len(starts)}')
