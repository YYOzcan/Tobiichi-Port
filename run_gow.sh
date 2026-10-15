#!/usr/bin/env bash
# Tobiichi Port: abre el juego sin el lanzador (Linux). Los ajustes son los de la ventana del lanzador por defecto.
#   ./run_gow.sh            con el disco extraído por ./instalar.sh en game/
#   PS2X_GS_HW_SCALE=1 ./run_gow.sh, GOW_SKIP_FMV=1 ./run_gow.sh, ...   (ver docs/ULTIMATE.md)
RAIZ="$(cd "$(dirname "$0")" && pwd)"
cd "$RAIZ/PS2Recomp"
# Ajustes de juego del runtime de Waffle565: VIF1/VU1/GIF en el hilo del GS y FINISH asíncrono.
export PS2X_GS_WORKER=${PS2X_GS_WORKER:-1}
export GOW_GS_FINISH_ASINCRONO=${GOW_GS_FINISH_ASINCRONO:-1}
export GOW_AUDIO_DEVICE=${GOW_AUDIO_DEVICE:-default}
export PS2X_GS_HW_SCALE=${PS2X_GS_HW_SCALE:-2}
export TOBIICHI_DMC5_CONTROLS=${TOBIICHI_DMC5_CONTROLS:-1}
export GOW_SKIP_FMV=${GOW_SKIP_FMV:-0}
# Juego: game/ (instalar.sh) o, en un árbol de desarrollo, el ELF de la raíz con la ISO al lado.
if [ -f "$RAIZ/game/SCUS_973.99" ]; then
    ELF="$RAIZ/game/SCUS_973.99"
else
    ELF="$RAIZ/SCUS_973.99"
fi
if [ ! -f "$(dirname "$ELF")/.disc_layout" ] && [ -z "${GOW_ISO:-}" ]; then
    for c in "$(dirname "$ELF")"/*.iso; do [ -f "$c" ] && export GOW_ISO="$c" && break; done
fi
"${PS2X_RUNNER:-./build/ps2xRuntime/ps2EntryRunner}" "$ELF" "$@"
