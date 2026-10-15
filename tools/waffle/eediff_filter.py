"""Filter [eediff] output: drop GPR differences confined to the upper 64 bits and functions whose reference run
called a known stub/override; print the remaining differing functions, fewest steps first.
usage: python -I tools/eediff_filter.py <log> [max]"""
import re
import sys

blocks, current = [], None
for line in open(sys.argv[1], encoding='utf-8', errors='replace'):
    m = re.search(r'\[eediff\] ([0-9A-F]{8}) \(ra ([0-9A-F]{8})\) call \d+: .*\((\d+) steps\)', line)
    if m:
        current = [m.group(1), m.group(2), int(m.group(3)), []]
        blocks.append(current)
        continue
    m = re.search(r'\[eediff\]    (.*)', line)
    if m and current:
        current[3].append(m.group(1).strip())
    elif '[eediff]' in line:
        current = None

def real(diff):
    m = re.match(r'gpr\d+\s+ref ([0-9A-F]{16})_([0-9A-F]{16}) ours ([0-9A-F]{16})_([0-9A-F]{16})', diff)
    return not (m and m.group(2) == m.group(4))

limit = int(sys.argv[2]) if len(sys.argv) > 2 else 40
shown = 0
for addr, ra, steps, diffs in sorted(blocks, key=lambda b: b[2]):
    kept = [d for d in diffs if real(d)]
    if not kept:
        continue
    print(f'{addr} ra={ra} steps={steps}: ' + ' | '.join(kept[:4])[:230])
    shown += 1
    if shown >= limit:
        break
