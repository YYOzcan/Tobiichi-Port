#!/usr/bin/env bash
# Sync generated code (port/output) and game overrides (port/overrides) into the PS2Recomp runner.
# Copies only files whose content changed, so MSBuild rebuilds only the affected unity batches.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
RUNNER="$ROOT/ext/PS2Recomp/ps2xRuntime/src/runner"
INCLUDE="$ROOT/ext/PS2Recomp/ps2xRuntime/include"
copy_if_changed() { cmp -s "$1" "$2" || cp "$1" "$2"; }
declare -A keep
for f in "$ROOT"/port/output/*.cpp "$ROOT"/port/overrides/*.cpp; do
    keep["$(basename "$f")"]=1
    copy_if_changed "$f" "$RUNNER/$(basename "$f")"
done
for f in "$ROOT"/port/output/*.h; do copy_if_changed "$f" "$INCLUDE/$(basename "$f")"; done
for f in "$RUNNER"/*.cpp; do [ -n "${keep[$(basename "$f")]:-}" ] || rm "$f"; done
echo "runner: $(ls "$RUNNER" | wc -l) sources"
