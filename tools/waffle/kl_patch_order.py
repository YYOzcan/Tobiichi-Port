"""Print the PS2Recomp patch order used by the other God of War recomp project (scripts/compilar.ps1).

usage: python -I tools/kl_patch_order.py <project>/scripts/compilar.ps1
"""
import re
import sys

text = open(sys.argv[1], encoding='utf-8').read()
variables = dict(re.findall(r"\$(\w+)\s*=\s*Join-Path \$RepoRoot 'patches[\\/]([^']+)'", text))
for name in re.findall(r"Run \$git @\('apply', '--ignore-whitespace', '--verbose', \$(\w+)\)", text):
    print(variables.get(name, '?' + name))
