#!/usr/bin/env python3
"""Compara la salida de ps2x_tests con la lista de fallos conocidos.

Uso:  ps2x_tests | python tools/ci/comprobar_pruebas.py tests/fallos_conocidos.txt

Falla (codigo 1) si alguna prueba que no esta en la lista falla, o si la suite no llega a imprimir
su resumen (se colgo o se cerro antes de tiempo). Avisa, sin fallar, cuando una prueba de la lista
ya pasa, para que se pueda quitar de ella.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

ANSI = re.compile(r"\x1b\[[0-9;]*m")
ESTADO = re.compile(r"\[(Passed|Failed|Error)\]")


def resultados(salida: str) -> dict[str, str]:
    """{"suite :: prueba": "Passed" | "Failed" | "Error"} a partir de la salida de MiniTest.

    MiniTest escribe "  [Run]: <prueba> " sin salto de linea, luego lo que imprima la prueba y despues
    "[Passed]", "[Failed]" o "[Error]"; el nombre termina en el primer salto de linea o codigo ANSI.
    """
    res: dict[str, str] = {}
    texto = ANSI.sub("\x00", salida)  # marca donde habia codigos de color, que delimitan el nombre
    suites = [(m.start(), m.group(1).replace("\x00", "").strip())
                    for m in re.finditer(r"^\[Suite\]: (.*)$", texto, re.M)]
    trozos = texto.split("  [Run]: ")
    pos = len(trozos[0])
    for trozo in trozos[1:]:
        inicio = pos
        pos += len("  [Run]: ") + len(trozo)
        suite = next((n for p, n in reversed(suites) if p < inicio), "?")
        nombre = re.split(r"[\n\x00]", trozo.lstrip("\x00"), maxsplit=1)[0].strip()
        m = ESTADO.search(trozo.replace("\x00", ""))
        res[f"{suite} :: {nombre}"] = m.group(1) if m else "Error"
    return res


def main() -> int:
    if len(sys.argv) != 2:
        print(__doc__, file=sys.stderr)
        return 2
    conocidos = {
        linea.strip() for linea in Path(sys.argv[1]).read_text(encoding="utf-8").splitlines()
        if linea.strip() and not linea.lstrip().startswith("#")
    }

    salida = sys.stdin.read()
    sys.stdout.write(salida)
    sys.stdout.flush()
    res = resultados(salida)
    pasan = {n for n, e in res.items() if e == "Passed"}
    fallan = {n for n, e in res.items() if e != "Passed"}
    resumen = "Total Tests:" in salida

    nuevos = sorted(fallan - conocidos)
    arreglados = sorted(conocidos & pasan)
    print("\n==== Comprobacion de la suite ====")
    print(f"Pasan: {len(pasan)}  Fallan: {len(fallan)}  Fallos conocidos: {len(fallan & conocidos)}")
    for nombre in arreglados:
        print(f"::notice::Ya pasa (se puede quitar de la lista de fallos conocidos): {nombre}")
    for nombre in nuevos:
        print(f"::error::Fallo nuevo: {nombre}")
    if not resumen:
        print("::error::La suite no imprimio su resumen: se colgo o termino antes de tiempo")
    if not pasan and not fallan:
        print("::error::No se encontro ningun resultado de prueba en la salida")
        return 1
    return 1 if nuevos or not resumen else 0


if __name__ == "__main__":
    sys.exit(main())
