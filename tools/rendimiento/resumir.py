#!/usr/bin/env python3
"""Resume ventanas del perfil opcional. Los tiempos son transcurridos y exclusivos por hilo."""
from __future__ import annotations
import argparse
from bisect import bisect_left, bisect_right
import json
import re
from pathlib import Path


def select_windows(text: str, desde: float, hasta: float, partida: bool = False) -> list[dict]:
    """Con partida, exige estados cargados que encierren cada ventana del perfil.

    El reloj del mando comienza en su primera lectura y el del perfil en la
    presentación. Se usa el orden de las líneas, nunca se igualan esos relojes.
    """
    if '[gow-perf:invalid]' in text:
        raise ValueError('perfil invalidado durante la ejecución; repetir sin carga externa')
    rows = []
    positions = []
    runs = []
    current = []
    for position, line in enumerate(text.splitlines()):
        if '[gow-perf]' in line:
            row = {key: float(value) for key, value in re.findall(r'(\w+)=([0-9.]+)', line)}
            if 'window' in row and 't' in row:
                rows.append(row)
                positions.append(position)
        elif '[gow-pad2:state]' in line:
            state = {key: int(value) for key, value in re.findall(r'(state|pending|levelReady)=(\d+)', line)}
            if state == {'state': 11, 'pending': 0, 'levelReady': 1}:
                current.append(position)
            else:
                if len(current) >= 2:
                    runs.append(current)
                current = []
    if len(current) >= 2:
        runs.append(current)

    spans = []
    if partida:
        for run in runs:
            # El primer informe posterior al estado inicial limita por arriba
            # el inicio; el último anterior al estado final limita por abajo el
            # fin. Así se excluyen las ventanas que tocan carga o transición.
            first = bisect_right(positions, run[0])
            last = bisect_left(positions, run[-1]) - 1
            if first <= last and first < len(rows):
                spans.append((rows[first]['t'], rows[last]['t']))

    selected = []
    rounding = 0.011 if partida else 0
    for row in rows:
        start, end = row['t'] - row['window'], row['t']
        if start < desde - rounding or end > hasta + rounding:
            continue
        # t y window se imprimen redondeados a centésimas por separado.
        if partida and not any(start >= low - 0.011 and end <= high + 0.011 for low, high in spans):
            continue
        selected.append(row)
    return selected


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('log', type=Path)
    parser.add_argument('--desde', type=float, default=100)
    parser.add_argument('--hasta', type=float, default=145)
    parser.add_argument('--partida', action='store_true',
                        help='exigir state=11, pending=0 y levelReady=1 antes y después de las ventanas')
    parser.add_argument('--json', type=Path, dest='output')
    args = parser.parse_args()
    try:
        rows = select_windows(args.log.read_text(encoding='utf-8', errors='replace'),
                              args.desde, args.hasta, args.partida)
    except ValueError as error:
        parser.error(str(error))
    if not rows:
        qualifier = ' de partida cargada' if args.partida else ''
        parser.error(f'no hay ventanas completas{qualifier} en el intervalo elegido')
    seconds = sum(row['window'] for row in rows)
    keys = ('ee_ms', 'vu_ms', 'gs_ms', 'iop_ms', 'guest_wait_ms', 'upload_ms', 'host_wait_ms')
    totals = {key: sum(row.get(key, 0) for row in rows) for key in keys}
    guest_ms = sum(totals[key] for key in keys[:5])
    result = {
        'ventanas': len(rows), 'segundos': seconds,
        'desde': rows[0]['t']-rows[0]['window'], 'hasta': rows[-1]['t'],
        'guest_flip_hz': sum(row.get('guest_flip_hz', 0)*row['window'] for row in rows)/seconds,
        'host_hz': sum(row.get('host_hz', 0)*row['window'] for row in rows)/seconds,
        'tiempo_ms': totals,
        'porcentaje_hilo_juego': {key: 100*totals[key]/guest_ms if guest_ms else 0 for key in keys[:5]},
    }
    if args.partida:
        result['seleccion'] = 'partida observada: state=11, pending=0, levelReady=1'
    print(json.dumps(result, ensure_ascii=False, indent=2))
    if args.output:
        args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
