#!/usr/bin/env python3
"""Valida config/funcmap.csv y config/recomp.template.toml sin necesitar el juego.

Uso:  python tools/ci/validar_config.py [--runtime RUTA_A_PS2RECOMP]

Errores (codigo 1), que de otro modo solo aparecen al recompilar en Windows:
  - funcmap.csv: cabecera, direcciones hexadecimales, orden, solapes, Size != End - Start, nombres repetidos.
  - recomp.template.toml: marcadores @ELF@/@MAP@/@OUT@, formato "nombre@0xDIRECCION" en stubs y
    entry_points, direcciones fuera de toda funcion de funcmap.csv.
  - Con --runtime: stubs sin handler en ps2xRuntime/include/ps2_call_list.h (el nombre, o sin "_" inicial).
Avisos (no fallan): stubs que no empiezan en una funcion (p. ej. las que empiezan en un delay slot y se
enlazan desde src/gow_overrides.cpp) y direcciones repetidas entre stubs y entry_points.
"""
from __future__ import annotations

import argparse
import bisect
import csv
import re
import sys
import tomllib
from pathlib import Path

RAIZ = Path(__file__).resolve().parents[2]
FUNCMAP = RAIZ / "config" / "funcmap.csv"
PLANTILLA = RAIZ / "config" / "recomp.template.toml"
LIBM_DOUBLE = {"sin", "cos", "tan", "atan", "atan2", "sqrt", "pow", "exp", "log", "fabs", "floor", "ceil", "fmod"}
SELECTOR = re.compile(r"^(?P<nombre>[A-Za-z_$][\w$.]*)@0x(?P<dir>[0-9A-Fa-f]{1,8})$")

errores: list[str] = []
avisos: list[str] = []


def leer_funcmap() -> list[tuple[str, int, int]]:
    with FUNCMAP.open(newline="", encoding="utf-8") as f:
        lector = csv.reader(f)
        cabecera = next(lector, None)
        if cabecera != ["Name", "Start", "End", "Size"]:
            errores.append(f"funcmap.csv: cabecera {cabecera}, se esperaba Name,Start,End,Size")
            return []
        funciones = []
        for n, fila in enumerate(lector, start=2):
            try:
                nombre, ini, fin, tam = fila
                ini_i, fin_i, tam_i = int(ini, 16), int(fin, 16), int(tam)
            except ValueError:
                errores.append(f"funcmap.csv:{n}: fila mal formada: {fila}")
                continue
            if fin_i - ini_i != tam_i:
                errores.append(f"funcmap.csv:{n}: {nombre}: Size {tam_i} != End - Start ({fin_i - ini_i})")
            if fin_i <= ini_i:
                errores.append(f"funcmap.csv:{n}: {nombre}: End <= Start")
            funciones.append((nombre, ini_i, fin_i))

    vistos: dict[str, int] = {}
    for i, (nombre, ini, fin) in enumerate(funciones):
        if nombre in vistos:
            errores.append(f"funcmap.csv: nombre repetido {nombre}")
        vistos[nombre] = ini
        if i and ini < funciones[i - 1][1]:
            errores.append(f"funcmap.csv: {nombre} (0x{ini:08X}) no esta ordenada por direccion")
        elif i and ini < funciones[i - 1][2]:
            errores.append(f"funcmap.csv: {nombre} (0x{ini:08X}) se solapa con {funciones[i - 1][0]}")
    return funciones


def selectores(config: dict, clave: str) -> list[tuple[str, int]]:
    valores = config.get("general", {}).get(clave, [])
    salida = []
    for v in valores:
        m = SELECTOR.match(v) if isinstance(v, str) else None
        if not m:
            errores.append(f"recomp.template.toml: {clave}: '{v}' no tiene el formato nombre@0xDIRECCION")
            continue
        salida.append((m["nombre"], int(m["dir"], 16)))
    return salida


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--runtime", type=Path, help="checkout de PS2Recomp (con los parches aplicados)")
    args = ap.parse_args()

    funciones = leer_funcmap()
    inicios = [f[1] for f in funciones]

    texto = PLANTILLA.read_text(encoding="utf-8")
    for marca in ("@ELF@", "@MAP@", "@OUT@"):
        if marca not in texto:
            errores.append(f"recomp.template.toml: falta el marcador {marca} que rellena compilar.ps1")
    try:
        config = tomllib.loads(texto)
    except tomllib.TOMLDecodeError as e:
        errores.append(f"recomp.template.toml: TOML no valido: {e}")
        config = {}

    stubs = selectores(config, "stubs")
    entradas = selectores(config, "entry_points")

    for clave, lista in (("stubs", stubs), ("entry_points", entradas)):
        for nombre, direccion in lista:
            i = bisect.bisect_right(inicios, direccion) - 1
            if i < 0 or direccion >= funciones[i][2]:
                errores.append(f"{clave}: {nombre}@0x{direccion:08X} no cae dentro de ninguna funcion de funcmap.csv")
            elif clave == "stubs" and direccion != funciones[i][1]:
                avisos.append(f"stubs: {nombre}@0x{direccion:08X} no empieza una funcion (esta dentro de {funciones[i][0]})")

    # La libm de God of War es double por software ($a0 -> $v0); los handlers del runtime son float
    # ($f12 -> $f0). Reemplazarla devuelve el argumento intacto (la tabla de senos salía con sin(x) = x).
    for nombre, direccion in stubs:
        if nombre in LIBM_DOUBLE:
            errores.append(f"stubs: {nombre}@0x{direccion:08X} es la libm double por software; "
                           "el handler float del runtime no respeta su ABI")

    por_direccion: dict[int, list[str]] = {}
    for nombre, direccion in stubs + entradas:
        por_direccion.setdefault(direccion, []).append(nombre)
    for direccion, nombres in sorted(por_direccion.items()):
        if len(nombres) > 1:
            avisos.append(f"0x{direccion:08X} aparece varias veces: {', '.join(nombres)}")

    if args.runtime:
        lista_llamadas = args.runtime / "ps2xRuntime" / "include" / "ps2_call_list.h"
        handlers = set(re.findall(r"X\((\w+)\)", lista_llamadas.read_text(encoding="utf-8")))
        for nombre, direccion in stubs:
            if nombre not in handlers and nombre.lstrip("_") not in handlers:
                errores.append(f"stubs: {nombre}@0x{direccion:08X} no tiene handler en ps2_call_list.h")

    for a in avisos:
        print(f"::warning::{a}")
    for e in errores:
        print(f"::error::{e}")
    print(f"funcmap.csv: {len(funciones)} funciones; stubs: {len(stubs)}; entry_points: {len(entradas)}; "
          f"errores: {len(errores)}; avisos: {len(avisos)}")
    return 1 if errores else 0


if __name__ == "__main__":
    sys.exit(main())
