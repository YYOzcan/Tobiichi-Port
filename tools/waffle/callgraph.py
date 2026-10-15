"""Call graph of the recompiled functions (from the disassembly comments in the runner sources).
usage: python -I tools/callgraph.py <dir with sub_*.cpp> <target hex> <func hex>...
prints, for each function, whether it can reach the target via jal (and one path)."""
import os
import re
import sys

src = sys.argv[1]
graph = {}
for name in os.listdir(src):
    m = re.match(r'sub_([0-9A-F]{8})_', name)
    if not m:
        continue
    calls = set()
    for line in open(os.path.join(src, name), encoding='utf-8', errors='replace'):
        c = re.search(r'//\s*0x[0-9a-f]+:\s+0x[0-9a-f]+\s+jal\s+(?:0x|func_)([0-9A-Fa-f]+)', line)
        if c:
            calls.add(int(c.group(1), 16))
    graph[int(m.group(1), 16)] = calls

target = int(sys.argv[2], 16)
for f in sys.argv[3:]:
    start = int(f, 16)
    prev, todo = {start: None}, [start]
    while todo:
        n = todo.pop()
        if n == target:
            break
        for c in graph.get(n, ()):
            if c not in prev:
                prev[c] = n
                todo.append(c)
    if target in prev:
        path, n = [], target
        while n is not None:
            path.append(f'{n:06X}')
            n = prev[n]
        print(f'{start:06X}: reaches {target:06X} via ' + ' <- '.join(path))
    else:
        print(f'{start:06X}: does not reach {target:06X} ({len(prev)} functions reachable)')
