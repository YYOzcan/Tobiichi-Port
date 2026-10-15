#!/usr/bin/env python3
# GOW-Port: resume muestreo.txt (GOW_MUESTREO, ps2_muestreo.cpp) por hilo y función con los símbolos de nm.
# Uso: resumir_muestreo.py <muestreo.txt> <ejecutable> [funciones por hilo]
import bisect, collections, subprocess, sys

def main():
    archivo, exe = sys.argv[1], sys.argv[2]
    tope = int(sys.argv[3]) if len(sys.argv) > 3 else 25
    sim = []
    for linea in subprocess.run(["nm", "-C", "--defined-only", exe], capture_output=True, text=True).stdout.splitlines():
        partes = linea.split(" ", 2)
        if len(partes) == 3 and partes[1].lower() in ("t", "w"):
            sim.append((int(partes[0], 16), partes[2]))
    sim.sort()
    dirs = [s[0] for s in sim]
    base, nombres, cuentas, mapas = 0, {}, collections.defaultdict(collections.Counter), []
    for linea in open(archivo):
        p = linea.split()
        if p[0] == "base":
            base = int(p[1], 16)
        elif p[0] == "mapa":
            mapas.append((int(p[1], 16), int(p[2], 16), int(p[3], 16), p[4]))
        elif p[0] == "hilo":
            nombres[int(p[1])] = " ".join(p[2:])
        else:
            tid, pc = int(p[0]), int(p[1], 16) - base
            i = bisect.bisect_right(dirs, pc) - 1
            f = sim[i][1] if i >= 0 and pc - dirs[i] < 0x100000 else None
            if f is None:
                pa = pc + base
                f = next((f"[{m[3].split('/')[-1]}+{pa - m[0] + m[2]:x}]" for m in mapas if m[0] <= pa < m[1]), "(fuera del ejecutable)")
                f = f.split("+")[0] + "]" if f.startswith("[") else f
            cuentas[tid][f] += 1
    total = sum(sum(c.values()) for c in cuentas.values())
    for tid, c in sorted(cuentas.items(), key=lambda x: -sum(x[1].values())):
        n = sum(c.values())
        print(f"== hilo {tid} {nombres.get(tid, '?')}: {n} muestras ({100 * n / total:.1f} %)")
        for f, k in c.most_common(tope):
            print(f"  {100 * k / n:5.1f} %  {f[:150]}")

main()
