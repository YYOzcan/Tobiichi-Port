#!/usr/bin/env python3
"""Imprime, en orden, los parches que scripts/compilar.ps1 aplica sobre PS2Recomp.

La CI los aplica en el mismo orden que la compilacion de Windows, sin una lista duplicada que se
pueda quedar desfasada. Falla si un parche de patches/ no se aplica o si falta un archivo.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

RAIZ = Path(__file__).resolve().parents[2]
COMPILAR = RAIZ / "scripts" / "compilar.ps1"


def main() -> int:
    texto = COMPILAR.read_text(encoding="utf-8-sig")
    # $variable = Join-Path $RepoRoot 'patches\archivo.patch'
    rutas = {m[1].lower(): m[2] for m in re.finditer(
        r"^\s*\$(\w+)\s*=\s*Join-Path\s+\$RepoRoot\s+'(patches[\\/][^']+\.patch)'", texto, re.M | re.I)}
    # Run $git @('apply', ..., $variable)
    orden = [m[1].lower() for m in re.finditer(
        r"^\s*Run\s+\$git\s+@\(\s*'apply'[^)]*\$(\w+)\s*\)", texto, re.M | re.I)]

    errores = []
    parches = []
    for var in orden:
        if var not in rutas:
            errores.append(f"compilar.ps1 aplica ${var}, pero no se encontro su ruta")
            continue
        ruta = RAIZ / rutas[var].replace("\\", "/")
        if not ruta.is_file():
            errores.append(f"no existe {ruta.relative_to(RAIZ).as_posix()}")
        parches.append(ruta)
    sin_aplicar = sorted(set((RAIZ / "patches").glob("*.patch")) - set(parches))
    for ruta in sin_aplicar:
        errores.append(f"{ruta.relative_to(RAIZ).as_posix()} no se aplica en compilar.ps1")
    if not parches:
        errores.append("no se encontro ningun parche en compilar.ps1")

    for e in errores:
        print(f"::error::{e}", file=sys.stderr)
    if errores:
        return 1
    for ruta in parches:
        print(ruta.as_posix())
    return 0


if __name__ == "__main__":
    sys.exit(main())
