"""GOW-Port: el control debe ejecutar pares compilados reales, además de dar paridad."""
import os
import re
import subprocess
import sys

env = dict(os.environ, GOW_VU1C_DIAG="1")
for name in ("GOW_VU1C_RANGO", "GOW_VU1C_SIN_BLOQUES", "GOW_VU1_SIN_COMPILAR"):
    env.pop(name, None)
result = subprocess.run([sys.argv[1]], env=env, capture_output=True, text=True, timeout=120)
match = re.search(r"\[vu1c\] compilados=(\d+) interpretados=(\d+)", result.stderr)
if result.returncode or not match or int(match[1]) == 0 or int(match[2]) == 0:
    raise AssertionError((result.returncode, result.stdout, result.stderr))
div = re.search(r"VU1 DIV: (\d+) casos exactos", result.stdout)
if not div or int(div[1]) < 19072:
    raise AssertionError(("Falta el control DIV completo", result.stdout, result.stderr))
print(result.stdout.strip())
print(f"Ruta real: {match[1]} pares compilados y {match[2]} interpretados")
