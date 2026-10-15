"""Print the R5900 disassembly of a recompiled function (from the comments in the recompiler output).
usage: dis.py ADDR [DIR]   (ADDR = any address inside the function, hex; DIR = output folder, default port/output-usa,
the USA build the runner runs; port/output is the European build, other addresses)"""
import os, re, sys
a = int(sys.argv[1], 16)
out = sys.argv[2] if len(sys.argv) > 2 else 'port/output-usa'
best = None
for name in os.listdir(out):
    m = re.match(r'(?:sub|entry)_([0-9A-F]{8})_', name)
    if m and int(m.group(1), 16) <= a and (best is None or int(m.group(1), 16) > best[0]):
        best = (int(m.group(1), 16), name)
for line in open(os.path.join(out, best[1])):
    m = re.match(r'\s*// (0x[0-9a-f]+): 0x[0-9a-f]+\s+(.*)', line)
    if m:
        print(('=> ' if int(m.group(1), 16) == a else '   ') + m.group(1) + ': ' + m.group(2))
print('function', best[1])
