#!/usr/bin/env python3
"""Prepara la entrada de tools/render/repetir_cadena_vif.cpp.

Extrae la cadena DMA de VIF1 de un cuadro (etiquetas, VIFcodes TTE y datos) junto con la
memoria de VU1 y la VRAM del GS. Funciona con dos orígenes:

  --pcsx2 <savestate.p2s>   savestate de PCSX2 (zip con eeMemory.bin, GS.bin, vu1*.bin...)
  --volcado <carpeta>       volcado del port con GOW_RENDER_DIAG (gow_render_ram.bin, ...)

La salida contiene datos del juego: se guarda en logs/ y nunca se publica.
"""
import argparse
import os
import struct
import sys
import zipfile

# Cabeceras de cuadro de God of War (DIRECT con la configuración del GS y NEXT a la lista):
# el juego alterna entre dos búferes.
INICIOS_CUADRO = (0x450C00, 0x450A00)
RAM = 0x2000000


def recorrer(ee, inicio, fin=None, limite=500000):
    """Recorre una cadena DMA desde `inicio`. Devuelve (dirección de END, número de etiquetas)."""
    a, pila, n = inicio, [], 0
    while n < limite:
        if a < 0 or a + 16 > min(RAM, len(ee)) or a & 15:
            return None, n
        t = struct.unpack_from('<Q', ee, a)[0]
        qwc, tid, addr = t & 0xFFFF, (t >> 28) & 7, (t >> 32) & 0x7FFFFFFF
        n += 1
        if tid not in (1, 2, 3, 4, 5, 6, 7):
            return None, n
        datos = a + 16 if tid in (1, 2, 5, 6, 7) else addr & (RAM - 1)
        if datos + qwc * 16 > min(RAM, len(ee)):
            return None, n
        if tid == 1:
            a = a + 16 + qwc * 16
        elif tid == 2:
            a = addr
        elif tid in (3, 4):
            a += 16
        elif tid == 5:
            if len(pila) >= 2:
                return None, n
            pila.append(a + 16 + qwc * 16)
            a = addr
        elif tid == 6:
            if not pila:
                return None, n
            a = pila.pop()
        elif tid == 7:
            return (a, n) if fin is None or a == fin else (None, n)
        else:
            return None, n
    return None, n


def seleccionar_cadena(ee, inicio=None, fin=None):
    """Exige una sola cabecera válida; una elección explícita no identifica el cuadro actual."""
    # GOW-Port: ambos búferes pueden conservar cadenas válidas; su orden no identifica el cuadro.
    candidatos = [inicio] if inicio is not None else dict.fromkeys(INICIOS_CUADRO)
    validos = []
    for candidato in candidatos:
        final, etiquetas = recorrer(ee, candidato, fin)
        if final is not None:
            validos.append((candidato, final, etiquetas))
    destino = '' if fin is None else ' 0x%X' % fin
    if not validos:
        if inicio is not None:
            raise ValueError('La cadena elegida con --inicio 0x%X no termina en END%s' % (inicio, destino))
        raise ValueError('Ninguna cabecera de cuadro termina en END%s' % destino)
    if len(validos) > 1:
        detalle = ', '.join('0x%X -> END 0x%X' % (candidato, final)
                            for candidato, final, _ in validos)
        raise ValueError('Selección ambigua: %s. Indica --inicio; elegir una cabecera no demuestra '
                         'que sea el cuadro actual.' % detalle)
    return validos[0]


def aplanar(ee, inicio):
    """Flujo que recibe VIF1 con CHCR.TTE: los 64 bits altos de cada etiqueta y su carga."""
    final, etiquetas = recorrer(ee, inicio)
    if final is None:
        raise ValueError('Cadena DMA inválida o sin END')
    out, a, pila = bytearray(), inicio, []
    for _ in range(etiquetas):
        t = struct.unpack_from('<Q', ee, a)[0]
        qwc, tid, addr = t & 0xFFFF, (t >> 28) & 7, (t >> 32) & 0x7FFFFFFF
        out += ee[a + 8:a + 16]
        if tid in (1, 2, 5, 6, 7):
            datos = a + 16
        else:
            datos = addr & (RAM - 1)
        if tid == 1:
            a = a + 16 + qwc * 16
        elif tid == 2:
            a = addr
        elif tid in (3, 4):
            a += 16
        elif tid == 5:
            pila.append(a + 16 + qwc * 16)
            a = addr
        elif tid == 6:
            a = pila.pop() if pila else None
        else:
            a = None
        out += ee[datos:datos + qwc * 16]
    return bytes(out)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = p.add_mutually_exclusive_group(required=True)
    g.add_argument('--pcsx2', help='savestate .p2s de PCSX2')
    g.add_argument('--volcado', help='carpeta con gow_render_ram.bin, gow_render_vram.bin, gow_vu1_*.bin')
    p.add_argument('--inicio', type=lambda v: int(v, 0), default=None,
                   help='cabecera elegida explícitamente; por defecto exige una única cadena válida '
                        'entre 0x450C00 y 0x450A00')
    p.add_argument('salida', help='carpeta de salida (en logs/)')
    a = p.parse_args()

    os.makedirs(a.salida, exist_ok=True)
    if a.pcsx2:
        z = zipfile.ZipFile(a.pcsx2)
        ee = z.read('eeMemory.bin')
        gs = z.read('GS.bin')
        # GSState::Freeze: registros, 4 MB de VRAM y, al final, 4 GIFPath (etiqueta 16 B + reg 4 B) y Q.
        vram = gs[len(gs) - 0x54 - 0x400000:len(gs) - 0x54]
        archivos = {'vu1MicroMem.bin': z.read('vu1MicroMem.bin'), 'vu1Memory.bin': z.read('vu1Memory.bin'),
                    'eeHwRegs.bin': z.read('eeHwRegs.bin'), 'Screenshot.png': z.read('Screenshot.png')}
        hw = archivos['eeHwRegs.bin']
        fin = struct.unpack_from('<I', hw, 0x9030)[0]  # D1_TADR: END de la última cadena
    else:
        leer = lambda n: open(os.path.join(a.volcado, n), 'rb').read()
        ee, vram = leer('gow_render_ram.bin'), leer('gow_render_vram.bin')
        archivos = {'vu1MicroMem.bin': leer('gow_vu1_code.bin'), 'vu1Memory.bin': leer('gow_vu1_data.bin')}
        fin = None
    if len(vram) != 0x400000 or len(ee) != RAM:
        sys.exit('Tamaños inesperados de RAM o VRAM')

    try:
        a.inicio, final, etiquetas = seleccionar_cadena(ee, a.inicio, fin)
    except ValueError as error:
        sys.exit(str(error))
    flujo = aplanar(ee, a.inicio)
    for nombre, datos in archivos.items():
        open(os.path.join(a.salida, nombre), 'wb').write(datos)
    open(os.path.join(a.salida, 'vram.bin'), 'wb').write(vram)
    open(os.path.join(a.salida, 'eeMemory.bin'), 'wb').write(ee)
    open(os.path.join(a.salida, 'vif1_stream.bin'), 'wb').write(flujo)
    print('cadena 0x%X -> END 0x%X: %d etiquetas, %d bytes para VIF1' % (a.inicio, final, etiquetas, len(flujo)))


if __name__ == '__main__':
    main()
