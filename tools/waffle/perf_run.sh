#!/bin/sh
# Perf run of the USA build: loads the user's save (first slot) with the scripted pad, measures with
# GOW_PERF_DIAG and optionally samples the process with muestrear (needs a /Zi build).
# usage: tools/perf_run.sh <name> <seconds> [profile_at_s profile_len_s] [ENV=VALUE ...]
# log -> port/<name>.log, profile -> port/<name>.prof, captures -> port/<name>/*.png
set -e
ROOT="C:/Users/lovas/Claude/God Of War"
EXE_DIR="$ROOT/ext/PS2Recomp-kl/out/build-kl/ps2xRuntime/Release"
name=$1; secs=$2; shift 2
prof_at=""; prof_len=""
case "$1" in [0-9]*) prof_at=$1; prof_len=$2; shift 2;; esac

cd "$EXE_DIR"
rm -f gow_pad_test_*.ppm
cp "$ROOT/ref/saves/Mcd002.ps2" "$ROOT/disc-usa/Mcd001.ps2"  # fresh copy of the user's card each run
env GOW_PERF_DIAG=1 GOW_PERF_FRAME_PC=0x001837B8 GOW_FAST_BOOT=1 GOW_PAD_TEST=1 GOW_SKIP_FMV=1 \
    GOW_ISO="$ROOT/iso-usa/God of War (USA).iso" GOW_MC0="$ROOT/disc-usa/Mcd001.ps2" \
    GOW_PAD_GUION="${GOW_PAD_GUION:-5:start,16:abajo,24:x,105:x,125:x,145:x,175:x,205:x}" "$@" \
    ./ps2EntryRunner.exe "$ROOT/disc-usa/SCUS_973.99" > "$ROOT/port/$name.log" 2>&1 &
sleep 3
pid=$(tasklist //FI "IMAGENAME eq ps2EntryRunner.exe" //FO CSV //NH | head -1 | cut -d, -f2 | tr -d '"')
if [ -n "$prof_at" ]; then
    sleep "$prof_at"
    "$ROOT/port/prof/muestrear.exe" "$pid" "$prof_len" 6 ${PROF_FUNCS:-40} > "$ROOT/port/$name.prof" 2>&1
    sleep $((secs - prof_at - prof_len - 3))
else
    sleep $((secs - 3))
fi
taskkill //PID "$pid" > /dev/null 2>&1 || true  # WM_CLOSE first: lets exit-time stats (GOW_VU1C_DIAG) print
sleep 15
taskkill //F //PID "$pid" > /dev/null 2>&1 || true
wait 2>/dev/null || true
mkdir -p "$ROOT/port/$name"
for f in gow_pad_test_*.ppm; do
    [ -f "$f" ] && python -I "$ROOT/tools/ppm2png.py" "$f" "$ROOT/port/$name/${f%.ppm}.png"
done
grep -a "gow-pad2:test\] state" "$ROOT/port/$name.log" | tail -3
grep -a "^\[gow-perf\] t=" "$ROOT/port/$name.log" | tail -6 | awk '{print $2,$4,$5,$6,$7,$12}'
