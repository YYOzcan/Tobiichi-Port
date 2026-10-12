#!/usr/bin/env bash
# GOW-Port: perfil por muestreo mientras se juega (Linux). Arranca el juego con run_gow.sh; a los 60 s toma 30 s
# de muestras de todos los hilos y las deja en logs/perfil_partida.txt (y .maps). Se puede seguir jugando después.
set -e
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"
mkdir -p logs
[ -x logs/muestrear_linux ] || g++ -O2 -std=c++20 tools/perfil/muestrear_linux.cpp -o logs/muestrear_linux
exec logs/muestrear_linux ps2EntryRunner "${ESPERA:-60}" "${DURACION:-30}" 2000 "$root/logs/perfil_partida.txt" -- ./run_gow.sh "$@"
