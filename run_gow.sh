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
export GOW_UNLOCKED_FPS=1
export GOW_TARGET_FPS=${GOW_TARGET_FPS:-120}
./build/ps2xRuntime/ps2EntryRunner "/home/yigit/Belgeler/Origami Tobiichi/SCUS_973.99" "$@"
