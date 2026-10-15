#!/usr/bin/env bash
# Tobiichi Port — instalador para Linux.
#
#   ./instalar.sh [ruta/a/God of War.iso] [--sin-optimizar] [--optimizar [segundos]] [--jobs N]
#
# Pasos (cada uno se salta si ya está hecho):
#   1. Extrae el disco de la ISO en game/ (con su mapa de sectores, .disc_layout) y prepara game/IOP_MOD.
#   2. Compila el recompilador (ps2_recomp) y traduce SCUS_973.99 a C++ con config/recomp.template.toml.
#   3. Compila el juego (ps2EntryRunner) y el lanzador (Qt 6).
#   4. Optimización: arranca el juego unos minutos con pulsaciones automáticas, guarda el microcódigo de VU1 y los
#      módulos del IOP que usa y recompila con ellos como código nativo (mucho más rápido). Solo la primera vez;
#      --optimizar lo repite (más zonas jugadas = más código nativo), --sin-optimizar lo omite.
#   5. Crea el acceso directo del menú de aplicaciones.
#
# Nada de lo que se genera a partir del juego (disco, código C++, microcódigo) sale de este ordenador.
set -euo pipefail

RAIZ="$(cd "$(dirname "$0")" && pwd)"
REC="$RAIZ/PS2Recomp"
BUILD="$REC/build"
GAME="$RAIZ/game"
GEN="$RAIZ/build-gen"
VU1="$RAIZ/capturas_vu1"
# Procesos de compilación: uno por núcleo, pero como mucho uno por cada 2 GB de memoria (cada unidad de ~8 archivos
# generados con -O3 usa 1-2 GB); el enlace con LTO, uno por cada 3 GB y como mucho 4. --jobs N lo fija.
MEM_GB="$(awk '/MemTotal/ {print int($2 / 1048576)}' /proc/meminfo 2>/dev/null || echo 8)"
JOBS="$(nproc 2>/dev/null || echo 4)"
[ "$JOBS" -gt $(( MEM_GB / 2 > 0 ? MEM_GB / 2 : 1 )) ] && JOBS=$(( MEM_GB / 2 > 0 ? MEM_GB / 2 : 1 ))
ISO=""
OPTIMIZAR="auto"
SEGUNDOS=240

while [ $# -gt 0 ]; do
    case "$1" in
        --sin-optimizar) OPTIMIZAR="no" ;;
        --optimizar) OPTIMIZAR="si"; if [[ "${2:-}" =~ ^[0-9]+$ ]]; then SEGUNDOS="$2"; shift; fi ;;
        --jobs) JOBS="$2"; shift ;;
        -h|--help) sed -n 2,16p "$0"; exit 0 ;;
        *) ISO="$1" ;;
    esac
    shift
done

LTO_JOBS=$(( MEM_GB / 3 )); [ "$LTO_JOBS" -gt 4 ] && LTO_JOBS=4; [ "$LTO_JOBS" -gt "$JOBS" ] && LTO_JOBS=$JOBS
[ "$LTO_JOBS" -lt 1 ] && LTO_JOBS=1

paso() { printf '\n\033[1;31m==>\033[0m \033[1m%s\033[0m\n' "$*"; }
aviso() { printf '\033[1;33m[aviso]\033[0m %s\n' "$*"; }
error() { printf '\033[1;31m[error]\033[0m %s\n' "$*" >&2; exit 1; }

# --- 0. Herramientas ---------------------------------------------------------------------------------------------
paso "Comprobando herramientas"
faltan=()
for c in cmake ninja g++ python3 git; do command -v "$c" >/dev/null 2>&1 || faltan+=("$c"); done
if [ ${#faltan[@]} -gt 0 ]; then
    echo "Faltan: ${faltan[*]}"
    echo "  Arch / CachyOS:  sudo pacman -S --needed base-devel cmake ninja python git qt6-base qt6-declarative qt6-svg"
    echo "  Ubuntu / Debian: sudo apt install build-essential cmake ninja-build python3 git libgl-dev libx11-dev \\"
    echo "                   libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxkbcommon-dev libwayland-dev libasound2-dev qt6-base-dev qt6-declarative-dev"
    echo "  Fedora:          sudo dnf install gcc-c++ cmake ninja-build python3 git mesa-libGL-devel libX11-devel \\"
    echo "                   libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libxkbcommon-devel wayland-devel alsa-lib-devel qt6-qtbase-devel qt6-qtdeclarative-devel"
    exit 1
fi

# --- 1. Datos del juego -------------------------------------------------------------------------------------------
paso "Datos del juego (game/)"
mkdir -p "$GAME"
if [ ! -f "$GAME/SCUS_973.99" ] || [ ! -f "$GAME/.disc_layout" ]; then
    if [ -z "$ISO" ]; then
        for c in "$GAME"/*.iso "$GAME"/*.ISO "$RAIZ"/*.iso "$RAIZ"/*.ISO; do [ -f "$c" ] && { ISO="$c"; break; }; done
    fi
    [ -n "$ISO" ] && [ -f "$ISO" ] || error "No encuentro la ISO de God of War (USA, SCUS-97399). Pásala como argumento: ./instalar.sh \"/ruta/God of War.iso\""
    echo "Extrayendo $ISO (unos 8 GB; el juego no necesita la ISO después)..."
    python3 -I "$RAIZ/tools/waffle/iso_extract.py" "$ISO" "$GAME" --layout
fi
grep -q "SCUS_973.99" "$GAME/SYSTEM.CNF" 2>/dev/null || error "game/ no es God of War USA (SCUS-97399): SYSTEM.CNF no arranca SCUS_973.99."
mkdir -p "$GAME/IOP_MOD"
for f in "$GAME"/*.IRX; do
    n="$(basename "$f")"
    [ -f "$GAME/IOP_MOD/$n" ] || cp "$f" "$GAME/IOP_MOD/$n"
    l="$(echo "$n" | tr 'A-Z' 'a-z')"
    [ -e "$GAME/IOP_MOD/$l" ] || ln -s "$n" "$GAME/IOP_MOD/$l"
done
echo "Listo: $(ls "$GAME" | wc -l) archivos, módulos del IOP en game/IOP_MOD."

# --- 2. Recompilador y código del juego ---------------------------------------------------------------------------
configurar() {
    local extra=()
    if compgen -G "$VU1/*.bin" >/dev/null; then
        extra+=("-DPS2X_VU1_MICROCODE_DIR=$VU1" "-DPS2X_VU1_GENERATOR_SOURCE=$RAIZ/tools/vu1/generar_vu1.cpp"
                "-DPS2X_VU1N_GEN_OVERRIDE=$RAIZ/tools/vu1/vu1n_gen.py")
    fi
    cmake -S "$REC" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
        -DPS2X_ENABLE_RUNTIME_LOGS=OFF -DPS2X_ENABLE_AGRESSIVE_LOGS=OFF -DPS2X_ENABLE_IOP_RPC_TRACE=OFF \
        -DPS2X_BUILD_STUDIO=OFF -DPS2X_BUILD_ANALYZER=OFF -DPS2X_BUILD_TEST=OFF -DPS2X_RUNNER_UNITY_BUILD_BATCH_SIZE=8 \
        -DPS2X_LTO_JOBS="$LTO_JOBS" \
        "${extra[@]}" >/dev/null
}

paso "Configurando la compilación (la primera vez descarga raylib, imgui y toml11)"
configurar
paso "Compilando el recompilador"
ninja -C "$BUILD" -j"$JOBS" ps2_recomp

paso "Traduciendo SCUS_973.99 a C++"
mkdir -p "$GEN/out"
cp "$GAME/SCUS_973.99" "$GEN/SCUS_973.99"
cp "$RAIZ/config/funcmap.csv" "$GEN/funcmap.csv"
sed -e "s|@ELF@|$GEN/SCUS_973.99|" -e "s|@MAP@|$GEN/funcmap.csv|" -e "s|@OUT@|$GEN/out/|" \
    "$RAIZ/config/recomp.template.toml" > "$GEN/recomp.toml"
"$BUILD/ps2xRecomp/ps2_recomp" "$GEN/recomp.toml" > "$GEN/recomp.log" 2>&1 || { tail -20 "$GEN/recomp.log"; error "ps2_recomp falló (ver build-gen/recomp.log)"; }
RUNNER="$REC/ps2xRuntime/src/runner"
mkdir -p "$RUNNER"
copiar() { cmp -s "$1" "$2" || cp "$1" "$2"; }   # solo lo que cambió: la recompilación sigue siendo incremental
for f in "$GEN"/out/*.cpp; do copiar "$f" "$RUNNER/$(basename "$f")"; done
for f in "$GEN"/out/*.h; do copiar "$f" "$REC/ps2xRuntime/include/$(basename "$f")"; done
for f in gow_overrides.cpp gow_pad2_packet.h gow_gs_replay.h; do copiar "$RAIZ/src/$f" "$RUNNER/$f"; done
echo "$(ls "$GEN"/out/*.cpp | wc -l) archivos C++ en PS2Recomp/ps2xRuntime/src/runner."

# --- 3. Juego y lanzador -------------------------------------------------------------------------------------------
compilar_juego() {
    paso "Compilando el juego (la primera vez tarda: ~6.400 archivos y enlace con LTO)"
    ninja -C "$BUILD" -j"$JOBS" ps2EntryRunner
}
configurar
compilar_juego

paso "Compilando el lanzador (Qt 6)"
if cmake -S "$RAIZ/launcher" -B "$RAIZ/launcher/build" -G Ninja -DCMAKE_BUILD_TYPE=Release >/dev/null 2>&1 \
    && ninja -C "$RAIZ/launcher/build" -j"$JOBS"; then
    LANZADOR="$RAIZ/launcher/build/tobiichi-launcher"
else
    LANZADOR=""
    aviso "No se pudo compilar el lanzador (¿falta Qt 6 con Qt Quick?). El juego se puede abrir con ./run_gow.sh."
fi

# --- 4. Optimización (VU1 e IOP nativos) -----------------------------------------------------------------------------
if [ "$OPTIMIZAR" = "si" ] || { [ "$OPTIMIZAR" = "auto" ] && ! compgen -G "$VU1/*.bin" >/dev/null; }; then
    paso "Optimización: el juego se abre ${SEGUNDOS} s solo (no toques el teclado); se guarda el código de VU1 y del IOP"
    mkdir -p "$VU1" "$GEN/iop_mods"
    (cd "$REC" && env GOW_VU1_CAPTURA="$VU1" PS2X_IOP_DUMP_MODULES="$GEN/iop_mods" GOW_SKIP_FMV=1 \
        GOW_PAD_TEST=1 GOW_PAD_TEST_NO_CAPTURE=1 GOW_MC0="$GEN/optimizar.ps2" PS2X_GS_WORKER=1 GOW_GS_FINISH_ASINCRONO=1 \
        GOW_PAD_GUION="5:start,12:x,20:x,28:x,40:cuadrado,41:cuadrado,42:cuadrado,44:triangulo,48:lup*3,52:x,55:cuadrado,56:triangulo,60:circulo,64:r1,70:lleft*2,74:cuadrado,76:cuadrado,80:triangulo,90:lup*4,96:x,100:cuadrado,104:l1,110:lright*2,120:cuadrado,125:triangulo,140:lup*5,150:cuadrado,160:triangulo,180:lup*5,200:cuadrado" \
        timeout "$SEGUNDOS" ./build/ps2xRuntime/ps2EntryRunner "$GAME/SCUS_973.99" > "$GEN/optimizar.log" 2>&1) || true
    echo "VU1: $(ls "$VU1"/*.bin 2>/dev/null | wc -l) micromemorias; IOP: $(ls "$GEN"/iop_mods/*.bin 2>/dev/null | wc -l) módulos."
    if compgen -G "$GEN/iop_mods/*.bin" >/dev/null; then
        python3 -I "$RAIZ/tools/iop/iopn_gen.py" "$GEN/iop_mods" "$REC/ps2xIOP/src/native"
    fi
    configurar
    compilar_juego
fi

# --- 5. Acceso directo --------------------------------------------------------------------------------------------
if [ -n "$LANZADOR" ]; then
    paso "Acceso directo"
    APPS="${XDG_DATA_HOME:-$HOME/.local/share}/applications"
    mkdir -p "$APPS"
    # Mismo archivo que escribe el propio lanzador ("Crear acceso directo"); el icono lo genera al abrirse.
    cat > "$APPS/tobiichi-launcher.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=God Of War: Tobiichi Port
GenericName=Game Launcher
Comment=God of War (PS2) PC port
Exec="$LANZADOR"
Icon=${XDG_DATA_HOME:-$HOME/.local/share}/Tobiichi/LauncherUltimate/icono.png
Terminal=false
Categories=Game;
StartupWMClass=tobiichi-launcher
EOF
    echo "Menú de aplicaciones: \"God Of War: Tobiichi Port\"."
fi

paso "Listo"
echo "  Lanzador: ${LANZADOR:-(sin compilar)}"
echo "  Sin lanzador: ./run_gow.sh"
echo "  Más código nativo tras jugar zonas nuevas: ./instalar.sh --optimizar"
