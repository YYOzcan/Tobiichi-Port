#!/usr/bin/env python3
"""Resume posiciones y ADC de capturas GIF locales, sin necesitar el juego."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct


def inspeccionar(datos: bytes) -> dict:
    """Valida los límites y cuenta vértices; un kick no garantiza una primitiva."""
    posicion = 0
    vertices = []
    etiquetas = []
    tipos = Counter()

    def exigir(tamano: int) -> None:
        if tamano > len(datos) - posicion:
            raise ValueError(f"payload incompleto en 0x{posicion:x}: faltan {tamano - (len(datos) - posicion)} bytes")

    def xyz(registro: int, bajo: int, alto: int, packed: bool) -> None:
        if registro not in (4, 5, 12, 13):
            return
        x = bajo & 0xffff
        y = (bajo >> (32 if packed else 16)) & 0xffff
        z = ((alto >> 4) & 0xffffff if registro in (4, 12) else alto & 0xffffffff) if packed else (
            (bajo >> 32) & (0xffffff if registro in (4, 12) else 0xffffffff))
        sin_kick = registro in (12, 13) or (packed and bool((alto >> 47) & 1))
        vertices.append((x, y, z, sin_kick))

    while posicion < len(datos):
        exigir(16)
        bajo, alto = struct.unpack_from('<QQ', datos, posicion)
        posicion += 16
        nloop = bajo & 0x7fff
        formato = (bajo >> 58) & 3
        nreg = (bajo >> 60) & 15 or 16
        registros = [(alto >> (4 * i)) & 15 for i in range(nreg)]
        etiquetas.append({'nloop': nloop, 'formato': formato, 'nreg': nreg})
        if formato == 0 and (bajo >> 46) & 1:
            tipos[(bajo >> 47) & 7] += 1
        if formato == 0:
            exigir(nloop * nreg * 16)
            for i in range(nloop * nreg):
                v0, v1 = struct.unpack_from('<QQ', datos, posicion)
                posicion += 16
                registro = registros[i % nreg]
                xyz(registro, v0, v1, True)
                if registro == 14:  # A+D usa la disposición de un registro GS de 64 bits.
                    xyz(v1 & 255, v0, 0, False)
        elif formato == 1:
            exigir(((nloop * nreg * 8 + 15) // 16) * 16)
            for i in range(nloop * nreg):
                v0, = struct.unpack_from('<Q', datos, posicion)
                posicion += 8
                xyz(registros[i % nreg], v0, 0, False)
            if (nloop * nreg) & 1:
                posicion += 8
        elif formato == 2:
            exigir(nloop * 16)
            posicion += nloop * 16
        else:
            raise ValueError(f"formato GIF 3 no soportado en 0x{posicion - 16:x}")

    resultado = {'bytes': len(datos), 'sha256': hashlib.sha256(datos).hexdigest(),
                 'etiquetas': etiquetas, 'tipos_prim_con_pre': dict(tipos),
                 'vertices': len(vertices), 'vertices_con_kick': sum(not v[3] for v in vertices),
                 'vertices_sin_kick': sum(v[3] for v in vertices),
                 'xyz_distintos': len({v[:3] for v in vertices})}
    if vertices:
        resultado['limites_xyz'] = [[min(v[i] for v in vertices), max(v[i] for v in vertices)] for i in range(3)]
    return resultado


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('captura', type=Path, help='archivo GIF o carpeta con gow_geo_gif_*.bin')
    parser.add_argument('--json', type=Path, help='guardar el informe, preferentemente bajo logs/')
    args = parser.parse_args()
    archivos = [args.captura] if args.captura.is_file() else sorted(
        args.captura.glob('gow_geo_gif_*.bin'), key=lambda p: int(re.search(r'_(\d+)$', p.stem)[1]))
    if not archivos:
        parser.error('no se encontraron capturas GIF')
    filas = []
    for archivo in archivos:
        try:
            filas.append({'archivo': archivo.name, **inspeccionar(archivo.read_bytes())})
        except ValueError as error:
            parser.error(f'{archivo.name}: {error}')
    informe = {'paquetes': len(filas), 'vertices': sum(f['vertices'] for f in filas),
               'vertices_con_kick': sum(f['vertices_con_kick'] for f in filas),
               'vertices_sin_kick': sum(f['vertices_sin_kick'] for f in filas),
               'paquetes_sin_vertices': sum(f['vertices'] == 0 for f in filas), 'detalle': filas}
    if args.json:
        args.json.write_text(json.dumps(informe, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: v for k, v in informe.items() if k != 'detalle'}, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
