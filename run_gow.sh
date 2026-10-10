#!/usr/bin/env bash
cd "/home/yigit/Belgeler/Origami Tobiichi/PS2Recomp"
export GOW_FAST_BOOT=1
export GOW_SKIP_FMV=1
export TOBIICHI_DMC5_CONTROLS=1
export PS2X_GS_GPU=1
export PS2X_GS_THREAD=1
export GOW_XGKICK_IMMEDIATE=1
export GOW_PERF_FRAME_PC=0x001837B8
export GOW_GS_FINISH_ASINCRONO=1
export PS2X_GS_QUEUE_CHUNKS=128
export PS2X_GS_GPU_DEFER_UPLOADS=1
export PS2X_GS_COMPACT_QUEUE=1
# VBlank a 60 Hz (NTSC). El juego cuenta VBlanks y alterna el bit de campo en cada uno; 120 Hz rompe esa
# temporización. GOW_UNLOCKED_FPS además adelanta ciclos del EE/IOP sin esperar al reloj (SPU2 fuera de ritmo).
export GOW_UNLOCKED_FPS=${GOW_UNLOCKED_FPS:-0}
export GOW_TARGET_FPS=${GOW_TARGET_FPS:-60}
# El IOP avanza en tandas de 1024 ciclos del EE (como mucho ~3,4 µs de retraso): 9,2 → 1,7 ms por cuadro.
export GOW_IOP_BATCH=${GOW_IOP_BATCH:-1024}
# VBlank al reloj real: si el EE va por detrás, se adelanta su tiempo. El juego pierde cuadros en vez de ir a
# cámara lenta (velocidad del juego 38-43 % → 90-100 % del tiempo real con 10-15 cuadros/s).
export GOW_VBLANK_REALTIME=${GOW_VBLANK_REALTIME:-1}
./build/ps2xRuntime/ps2EntryRunner "/home/yigit/Belgeler/Origami Tobiichi/SCUS_973.99" "$@"
