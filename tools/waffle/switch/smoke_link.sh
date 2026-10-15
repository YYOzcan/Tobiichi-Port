set -e
ln -sfn "/mnt/c/Users/lovas/Claude/God Of War/ext/PS2Recomp" /tmp/ps2r
R=/tmp/ps2r; B="$R/out/switch"; T=/tmp/swlink; SCR="/mnt/c/Users/lovas/Claude/God Of War/tools/switch"
rm -rf $T; mkdir -p $T; cd $T
export DEVKITPRO=/opt/devkitpro; export PATH=/opt/devkitpro/devkitA64/bin:/opt/devkitpro/tools/bin:/opt/devkitpro/portlibs/switch/bin:$PATH
CXX=aarch64-none-elf-g++
FLAGS="-DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP_SDL -DPLATFORM_SWITCH -DPS2X_ENABLE_IOP_RPC_TRACE=1 -DPS2X_HAS_FFMPEG=1 -DPS2_RUNTIME_LOGS=1 -DUSE_SSE2NEON -I$B/_deps/sse2neon-src -I$R/ps2xRuntime/include -I$R/ps2xRuntime/src/lib/Kernel -I$B/_deps/raylib-src/src -I$R/ps2xIOP/include -isystem /opt/devkitpro/portlibs/switch/include/SDL2 -isystem /opt/devkitpro/portlibs/switch/include -isystem /opt/devkitpro/libnx/include -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -ftls-model=local-exec -ffunction-sections -fdata-sections -D__SWITCH__ -O2 -std=gnu++20 -flto=auto"

# Smoke-test copy of main.cpp with the (main-thread) heartbeat compile errors patched.
python3 - "$R/ps2xRuntime/src/main.cpp" main_fixed.cpp <<'PY'
import re, sys
s = open(sys.argv[1]).read()
s = re.sub(r'%d\n", (tick|thread\.id)', lambda m: '%d\\n", ' + m.group(1), s)
s = '#include "runtime/ee_scheduler.h"\n' + s
open(sys.argv[2], 'w').write(s)
PY

$CXX $FLAGS '-DPS2X_DEFAULT_BOOT_ELF="sdmc:/switch/gow/SCES_531.33"' '-DPS2X_DEFAULT_CD_IMAGE="sdmc:/switch/gow/gow.iso"' -c main_fixed.cpp -o main.o
$CXX $FLAGS -c "$R/ps2xRuntime/src/lib/ps2_switch_runtime.cpp" -o sw.o
$CXX $FLAGS -c "$SCR/register_placeholder.cpp" -o reg.o

SDL=$(aarch64-none-elf-pkg-config --static --libs sdl2)
FF=$(aarch64-none-elf-pkg-config --static --libs libavformat libavcodec libswscale libswresample libavutil)
set +e
$CXX -specs=/opt/devkitpro/libnx/switch.specs -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -O2 -flto=auto \
  main.o sw.o reg.o "$B/ps2xRuntime/libps2_runtime.a" "$B/ps2xIOP/libps2_iop.a" "$B/_deps/raylib-build/raylib/libraylib.a" \
  $FF $SDL -L/opt/devkitpro/libnx/lib -lnx -lm -o smoke.elf > link.log 2>&1
echo "link rc=$?"
grep -oE "undefined reference to [^']*'[^']+'" link.log | sort | uniq -c | sort -rn | head -40
grep -E 'error' link.log | grep -v 'undefined reference' | head -10
set -e
ls -la smoke.elf && aarch64-none-elf-size smoke.elf
nacptool --create "PS2 Retro X" "PS2Recomp" "0.1.0" smoke.nacp && elf2nro smoke.elf smoke.nro --nacp=smoke.nacp && ls -la smoke.nro
mkdir -p "$B/smoke" && cp smoke.nro smoke.elf "$B/smoke/" && echo copied
