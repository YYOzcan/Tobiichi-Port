#!/usr/bin/env bash
# GOW-Port: God of War (SCUS-97399) con el runtime de Waffle565 (God-Of-War-Native-Port) y las funciones de Tobiichi
# Port (lanzador, combate ágil, fijar objetivo, trucos, iconos de botones, panorámico Hor+). Ver docs/ULTIMATE.md.
RAIZ="$(cd "$(dirname "$0")" && pwd)"
cd "$RAIZ/PS2Recomp"
# Ajustes de juego de Waffle (tools/waffle/play.cmd): VIF1/VU1/GIF en el hilo del GS y FINISH asíncrono.
export PS2X_GS_WORKER=${PS2X_GS_WORKER:-1}
export GOW_GS_FINISH_ASINCRONO=${GOW_GS_FINISH_ASINCRONO:-1}
# Sonido en la salida por defecto del sistema.
export GOW_AUDIO_DEVICE=${GOW_AUDIO_DEVICE:-default}
# Resolución interna del GS (Waffle: 2 por defecto; 1-4).
export PS2X_GS_HW_SCALE=${PS2X_GS_HW_SCALE:-2}
# Datos del juego: la ISO (sin PART2.PAK extraído). Con el disco extraído por tools/waffle/iso_extract.py --layout
# junto al ELF, GOW_ISO= (vacío) lo lee de la carpeta.
export GOW_ISO=${GOW_ISO-"$RAIZ/God of War.iso"}
[ -z "$GOW_ISO" ] && unset GOW_ISO
# Tarjeta de memoria: copia propia de este árbol (la del juego principal no se toca).
export GOW_MC0=${GOW_MC0:-"$RAIZ/Mcd001.ps2"}
export TOBIICHI_DMC5_CONTROLS=${TOBIICHI_DMC5_CONTROLS:-1}
# Vídeos: Waffle los reproduce de forma nativa con sonido. GOW_SKIP_FMV=1 los salta.
export GOW_SKIP_FMV=${GOW_SKIP_FMV:-0}
# PS2X_RUNNER: otro ejecutable para comparar.
"${PS2X_RUNNER:-./build/ps2xRuntime/ps2EntryRunner}" "$RAIZ/SCUS_973.99" "$@"
