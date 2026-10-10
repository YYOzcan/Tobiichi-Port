#!/usr/bin/env bash
# GOW-Port: control de rendimiento con guarda de imagen (Linux). Ejecuta run_gow.sh con GOW_PAD_TEST
# (avanza el menú y entra en la partida, guardando gow_pad_test_N.ppm) y GOW_PERF_DIAG, y comprueba:
#   - menú (captura 0): fuego visible (fracción de píxeles cálidos > 0,25);
#   - partida (capturas 6, 8, 10): sin personajes blancos (fracción de píxeles casi blancos < 0,02).
# Los umbrales salen de pasadas buenas (≤ 0,001 blancos) y rotas por VF0/VI0 (0,076-0,186 blancos).
# Una captura que pasa no prueba que la imagen sea correcta; un fallo sí prueba que está rota.
# Uso: scripts/linux_perf_guard.sh <etiqueta> [segundos] [VAR=valor ...]
set -u
tag=${1:?etiqueta}; secs=${2:-150}; shift; [ $# -gt 0 ] && shift
root="$(cd "$(dirname "$0")/.." && pwd)"
out="$root/logs/perf_$tag"; mkdir -p "$out"
rm -f "$root"/PS2Recomp/gow_pad_test_*.ppm
env "$@" GOW_PERF_DIAG=1 GOW_PAD_TEST=1 timeout -s INT "$secs" "$root/run_gow.sh" >"$out/out.log" 2>"$out/err.log"
for f in "$root"/PS2Recomp/gow_pad_test_*.ppm; do
    [ -e "$f" ] || continue
    n=$(basename "$f" .ppm); n=${n#gow_pad_test_}
    magick "$f" "$out/$n.png"
done
python3 -W ignore - "$out" <<'EOF'
import sys, os, re
from PIL import Image
out = sys.argv[1]
def frac(path, pred):
    im = Image.open(path).convert('RGB').resize((160, 112))
    px = list(im.getdata())
    return sum(1 for p in px if pred(*p)) / len(px)
ok = True
menu = os.path.join(out, '0.png')
if os.path.exists(menu):
    warm = frac(menu, lambda r, g, b: r > 150 and r > g + 40 and g > b)
    print(f"menu warm={warm:.3f}")
    ok &= warm > 0.25
else:
    print("menu: sin captura"); ok = False
for n in (6, 8, 10):
    p = os.path.join(out, f'{n}.png')
    if not os.path.exists(p):
        print(f"captura {n}: no existe"); ok = False; continue
    white = frac(p, lambda r, g, b: r > 215 and g > 215 and b > 215)
    print(f"captura {n} white={white:.3f}")
    ok &= white < 0.02
# Ventanas de 5 s desde t >= 60 s (partida). Mediana: las cargas/escenas sin VU dan picos de ~50 cuadros/s.
def field(line, key):
    return float(re.search(key + r'=([0-9.]+)', line).group(1))
rows = [l for l in open(os.path.join(out, 'err.log'), errors='replace')
        if l.startswith('[gow-perf]') and field(l, 't') >= 60.0]
def median(key):
    vals = sorted(field(l, key) for l in rows)
    return vals[len(vals) // 2] if vals else 0.0
flip = median('guest_flip_hz')
last = field(rows[-1], 't') if rows else 0.0
print(f"ventanas={len(rows)} hasta t={last:.0f}s")
if flip:
    print(f"flip(mediana)={flip:.2f} vu/frame={median('vu_ms')/5/flip:.0f}ms ee/frame={median('ee_ms')/5/flip:.0f}ms "
          f"iop/frame={median('iop_ms')/5/flip:.1f}ms gs={median('gs_ms'):.0f}ms/5s")
print("IMAGEN OK" if ok else "IMAGEN ROTA")
sys.exit(0 if ok else 1)
EOF
