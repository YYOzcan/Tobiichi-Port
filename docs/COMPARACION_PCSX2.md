# Comparación con PCSX2: cadena VIF1 de un cuadro

_6 de octubre de 2026_

## Objetivo

Separar los fallos de VIF1/VU1/GS de los datos que prepara el EE. La herramienta toma la cadena DMA
de VIF1 de un cuadro ya construido por el juego y la ejecuta sobre el VIF1, VU1 y GS del runtime,
sin ejecutar el EE:

- con una cadena de **PCSX2** (savestate), una imagen correcta indica que VIF1/VU1/GS dibujan bien
  esos paquetes;
- con una cadena **del port** (volcado de `GOW_RENDER_DIAG`), la repetición debe reproducir la imagen
  del juego, siempre que se haya identificado la cadena del cuadro correspondiente. Una semejanza
  visual con una cabecera elegida entre dos cuadros no certifica esa correspondencia.

## Uso

```powershell
scripts\compilar_repetir_vif.cmd            # requiere scripts\2_compilar.cmd
python tools\render\extraer_cadena_vif.py --pcsx2 "<sstates>\SCUS-97399 (XXXXXXXX).01.p2s" logs\vif_pcsx2
logs\repetir_cadena_vif.exe logs\vif_pcsx2 logs\vif_pcsx2\imagen
```

Para un volcado del port: ejecutar el juego con `GOW_RENDER_DIAG=1` y, opcionalmente,
`GOW_RENDER_DIAG_DESDE=<segundos>` (vuelca la primera captura del mando en estado 11 a partir de ese
momento; sin la variable, la primera en estado 11). Los volcados quedan junto al ejecutable:

```powershell
python tools\render\extraer_cadena_vif.py --volcado E:\gowport\PS2Recomp\out\build\ps2xRuntime logs\vif_port
logs\repetir_cadena_vif.exe logs\vif_port logs\vif_port\imagen
```

El extractor examina las dos cabeceras. Si ambas terminan en END, se detiene e indica los candidatos
para elegir mediante `--inicio 0x450C00` o `--inicio 0x450A00`. En un savestate también rechaza la
selección si varias cadenas terminan en el mismo `D1_TADR`. `--inicio` permite repetir una cadena
conocida, pero no demuestra que sea la del cuadro actual. El volcado del port todavía no guarda
`D1_TADR`: si ambas son válidas, hay que comparar las dos y mantener esa limitación en el resultado.

`repetir_cadena_vif` escribe `imagen_antes.ppm` e `imagen_despues.ppm` del framebuffer indicado
(por defecto `FBP=0`, `FBW=8`, PSMCT32, 512×448, el que usa la partida). Todo lo extraído contiene
datos del juego y queda en `logs/`.

### Detalles del formato

- El juego alterna las cabeceras `0x450C00` y `0x450A00` (un DIRECT de 15 QW con la configuración
  del GS y un NEXT a la lista). En un savestate se exige el END que apunta `D1_TADR`.
  Se reproduce lo que recibe VIF1 con `CHCR.TTE`: los 64 bits altos de cada etiqueta seguidos
  de su carga, siguiendo CALL/RET.
- En `GS.bin` del savestate (PCSX2 v2.x), la VRAM son los 4 MB anteriores a los últimos `0x54` bytes
  (cuatro `GIFPath` de 20 bytes y `Q`).
- Los registros de VIF1 se toman de `eeHwRegs.bin` (`0x3C00`). VU1 empieza con registros a cero; la
  cadena del cuadro sube el microcódigo y las constantes que usa.
- No se restaura la paleta interna CLUT del GS ni el conjunto completo de registros de VU1.
- No se repite la cadena del canal GIF (PATH3): las texturas que el juego sube durante el cuadro no
  se actualizan. Las diferencias de colores y texturas pueden proceder tanto de esas subidas como
  del estado interno no restaurado; no se atribuyen exclusivamente a PATH3.

## Resultados

| Entrada | Resultado |
|---|---|
| PCSX2, Egeo (Kratos en el mástil, savestate `6C2355D5`) | Geometría correcta: barco, mástil, rocas, agua y Kratos en su sitio. Difieren colores (Kratos y el agua); no se separó el efecto de PATH3 del estado interno no restaurado. |
| PCSX2, Desierto de las Almas Perdidas (`C1CFCB84`) | Escena reconocible y en su sitio, con una neblina más intensa y partículas de fuego con otra textura. |
| PCSX2, Hades (`CBE116C1`) | Kratos y el HUD correctos; faltan las paredes. Sin investigar. |
| Port, partida a los 190 s | La repetición produjo una imagen semejante (fondo de tablas oscuro y una silueta negra). Control ambiguo: las dos cabeceras terminan en END y el extractor anterior escogió la primera sin identificar el cuadro actual. |

El microcódigo de VU1 que sube el port coincide con el de los savestates en los primeros `0x24D8`
bytes; el resto es una zona que el juego reemplaza durante la partida.

**Conclusión:** con los paquetes de PCSX2 probados, VIF1, VU1 y el GS del runtime dibujan la
geometría del Egeo correctamente. Esto no certifica otras entradas ni descarta diferencias GS en
colores o texturas. El control del port a los 190 s queda inconcluso como comparación del mismo
cuadro por la selección ambigua. La causa EE de la cámara deformada se comprobó después siguiendo
la tabla de senos y verificando su arreglo en el juego, como se describe abajo.

## Colores de vértice (descartado)

En un savestate del Egeo más avanzado (`6C2355D5`), varias mallas tienen en PCSX2 colores de vértice
reescritos (`0x80606060`), mientras el port conserva los del disco. Con el savestate del inicio de la
partida (`D6385328`), PCSX2 también conserva los colores del disco: es un recálculo posterior del
nivel, no un fallo del port. Se descarta como causa de la escena oscura.

## Matriz de la cámara: causa y arreglo (2026-10-06)

En la partida del port, la matriz de la cámara que llega a VU1 tenía ejes ortogonales de longitud
1,27, 1,52 y 1,93; en PCSX2 miden 1. Esto estiraba toda la escena, también en la intro sin
`GOW_FAST_BOOT`. Siguiendo las escrituras (una vigilancia temporal en `ps2TraceGuestWrite`, ya
retirada) se llegó a la articulación 1 del esqueleto que anima la cámara de la intro, calculada por
`makeAnimMatricesRot` (`0x10B9C0`). Esa función toma seno y coseno de una tabla de 4096 floats que se
copia al scratchpad (`0x70000000`) desde `*(0x304638)` = `0x52C600`.

En el port la tabla contenía el ángulo y no su seno (`0,1963 / 0,3927 / 0,7854 / 1,5704` frente a
`0,1951 / 0,3827 / 0,7071 / 1,0` en PCSX2). La rellena `0x118798` con
`dptofp(sin(fptodp(x)))`: la libm del juego es **double por software** (argumento en `$a0`,
resultado en `$v0`), pero `config/recomp.template.toml` reemplazaba `sin@0x00287378` por el handler
float del runtime (`$f12 -> $f0`). `$v0` conservaba el argumento, así que `sin(x)` devolvía `x`.
`fabs` y `floor` tenían el mismo problema; solo los usa esa libm (`__ieee754_rem_pio2`,
`__kernel_rem_pio2`).

**Arreglo:** `sin`, `fabs` y `floor` dejan de ser stubs y se ejecuta la libm original recompilada.
`tools/ci/validar_config.py` rechaza ahora reemplazar funciones de la libm double.

Comprobación con la compilación completa y `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1`: la tabla del port
coincide con PCSX2 (`0 / 0,1951 / 0,3827 / 0,7071 / 1,0`), la matriz de la cámara a los 190 s mide
1 en los tres ejes y las capturas de 160 y 190 s muestran la cubierta del barco, los acantilados, el
cielo y la lluvia sin polígonos estirados. Las animaciones de Kratos y los enemigos usan la misma
tabla; queda por verificar su aspecto en partida.

## Inicio de la partida sin `GOW_FAST_BOOT` (2026-10-07)

Con el arreglo de `sin` y las mejoras de rendimiento, la intro termina sola: a los ~480 s (OpenGL,
`GOW_SKIP_FMV=1`) aparece el HUD. La matriz de la cámara coincide con la del savestate de PCSX2 del
inicio (`D6385328`): misma posición `(1530,2; 49,8; 1973,8)` y mismos ejes. Al repetir la cadena
VIF1 de ese cuadro, la imagen del port reproduce la del juego: Kratos aparece como polígonos rojos
gigantes delante de la cámara, mientras la cadena de PCSX2 lo dibuja bien. El fallo vuelve a estar
en los datos del EE.

Entre las matrices V4-32 de 4×4 que sube cada cadena, el port tiene muchas con escala uniforme
0,1–0,2 en las direcciones VU `0x106`–`0x12E` que PCSX2 no tiene (allí son 1,0, 0,3 o 0,5). Sigue
abierto: identificar el esqueleto de Kratos y comparar su paleta de huesos con la de PCSX2 en el
mismo cuadro. Las salidas de `makeAnimMatrices*` del port tienen rotaciones unitarias; la escala
0,1/0,3/0,5 aparece en la articulación raíz de las variantes `NonUnitScale`.

### Causa: DMA del scratchpad en modo cadena (2026-10-07)

En el cuadro de partida, la paleta de huesos de Kratos que sube a VU1 (`UNPACK V4-32`, 36 QW en
VU `0x106`) llegaba entera a cero en el port; en la cadena de PCSX2 son matrices válidas.
`CalcSkinHierarchy` (`0x137508`) deja los huesos en el scratchpad (`0x70000010`) y el juego los
copia a los paquetes con el canal fromSPR en **cadena de destino** (`CHCR=0x104`; también usa toSPR
en cadena de origen, `CHCR=0x105`). El runtime solo implementaba el modo normal de los canales 8 y 9
y no copiaba nada en modo cadena.

`patches/ps2recomp-spr-chain.patch` implementa ambos modos: fromSPR lee etiquetas
`{QWC, ID, IRQ, ADDR}` del scratchpad y escribe cada bloque en su dirección de RAM (`cnts`, `cnt`,
`end`); toSPR recorre etiquetas en RAM (`refe/cnt/next/ref/refs/call/ret/end`, con TTE) y escribe
los datos seguidos en el scratchpad. Dos regresiones fallan sin el parche; la suite pasa **547/547**.

Con la compilación completa, OpenGL y `GOW_SKIP_FMV=1` (sin `GOW_FAST_BOOT`), las capturas de 240,
360, 480 y 580 s muestran la intro, a Kratos en la cubierta, a los no muertos y la partida con el
HUD, todos con su forma correcta.
