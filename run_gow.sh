#!/usr/bin/env bash
cd "/home/yigit/Belgeler/Origami Tobiichi/PS2Recomp"
# GOW_FAST_BOOT=1 da por terminada la animación de entrada en cuanto carga el nivel (acorta la apertura): no se usa.
export GOW_FAST_BOOT=${GOW_FAST_BOOT:-0}
export GOW_SKIP_FMV=${GOW_SKIP_FMV:-1} # GOW-Port: vídeos desactivados por ahora (se retomarán tras optimizar la partida)
export TOBIICHI_DMC5_CONTROLS=1
export PS2X_GS_GPU=${PS2X_GS_GPU:-1}
# GOW-Port: GPU. Por defecto la del sistema (en el portátil híbrido, la integrada AMD): radeonsi no tiene
# GL_ARB_fragment_shader_interlock y el GS usa el rasterizador de cómputo puro. TOBIICHI_GPU=nvidia fuerza la
# dedicada (PRIME offload) si `nvidia-smi` responde: rasterizado por hardware y mucha más potencia.
if [ "${TOBIICHI_GPU:-integrada}" = "nvidia" ] && command -v nvidia-smi >/dev/null 2>&1 && nvidia-smi -L >/dev/null 2>&1; then
    export __NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia
fi
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
# El código recompilado cobra 32 ciclos por vuelta de bucle y 8 por llamada; en partida eso daba ~10 M ciclos por
# cuadro (2 VBlanks) aunque el host lo hacía en un VBlank, y el juego iba a 30. Al 50 % (medido) la velocidad del
# juego sigue al 100 % (VBlank al reloj real) y los cuadros suben. GOW_EE_CICLOS=100 vuelve al valor anterior.
export GOW_EE_CICLOS=${GOW_EE_CICLOS:-50}
# VIF1/VU1 en su propio hilo y los paquetes GIF de VU1 en otro (como MTVU en PCSX2). Probado en partida: más
# cuadros/s e imagen correcta. PS2X_VU1_HILO=0 / PS2X_GS_FRENTE=0 vuelven al hilo único.
export PS2X_VU1_HILO=${PS2X_VU1_HILO:-1}
export PS2X_GS_FRENTE=${PS2X_GS_FRENTE:-1}
# Presentación asíncrona (PBO + fence): el hilo del GS no espera a la GPU en cada cuadro. En Linux no hay
# presentación compartida y la lectura síncrona dejaba el hilo del GS ~82 % en el driver. Probado: ~30 cuadros/s.
export PS2X_GS_ASYNC_PRESENT=${PS2X_GS_ASYNC_PRESENT:-1}
# Presentación por buzón: el hilo principal muestra el último cuadro listo sin esperar a que el hilo del GS vacíe
# su cola. Sin esto, con el juego a 50-60 cuadros/s la ventana caía a 6-10 cuadros/s.
export PS2X_GS_PRESENT_BUZON=${PS2X_GS_PRESENT_BUZON:-1}
# Presentación compartida: el contexto del GS comparte texturas con el de la ventana y entrega el cuadro en la GPU, sin
# leerlo a la RAM ni volver a subirlo (2048x1792 a 4x). PS2X_GS_DIRECT_PRESENT=0 vuelve a la lectura.
export PS2X_GS_DIRECT_PRESENT=${PS2X_GS_DIRECT_PRESENT:-1}
# PS2X_RUNNER: otro ejecutable (p. ej. uno guardado) para comparar.
"${PS2X_RUNNER:-./build/ps2xRuntime/ps2EntryRunner}" "/home/yigit/Belgeler/Origami Tobiichi/SCUS_973.99" "$@"
