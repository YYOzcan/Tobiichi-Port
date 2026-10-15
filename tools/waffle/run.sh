#!/usr/bin/env bash
# Run the PC build from disc/ for N seconds, screenshot, and save the log.
# usage: tools/run.sh <seconds> <name> [env assignments...]
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
secs=$1; name=$2; shift 2
cd "$ROOT/disc"
R="$ROOT/ext/PS2Recomp/out/build/ps2xRuntime/RelWithDebInfo/ps2EntryRunner.exe"
env "$@" "$R" "$(cygpath -w "$PWD/SCES_531.33")" > "$ROOT/port/$name.log" 2>&1 &
pid=$!
sleep "$secs"
powershell -NoProfile -ExecutionPolicy Bypass -File "$(cygpath -w "$ROOT/tools/shot.ps1")" ps2EntryRunner "$(cygpath -w "$ROOT/port/$name.png")" >/dev/null 2>&1
kill -9 "$pid" 2>/dev/null  # only this runner: never kill by image name (other tests may be running)
echo "log: port/$name.log  shot: port/$name.png"
