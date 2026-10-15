# Tobiichi Ultimate: runtime de Waffle565 + funciones de Tobiichi Port

Rama `ultimate` (15 de octubre de 2026). Une este port con
[Waffle565/God-Of-War-Native-Port](https://github.com/Waffle565/God-Of-War-Native-Port) (rama `runtime` para
PS2Recomp, rama `main` para documentación, herramientas y overrides).

## Por qué el runtime de Waffle es la base

Los dos proyectos salen del mismo PS2Recomp (`c5a9d02`, 30 de septiembre de 2026) y de la pila de parches de
KIexster, pero el GS, el IOP, la VU1 y el DMA se separaron por completo:

| | Tobiichi Port (rama `main`) | Waffle565 (base de `ultimate`) |
|---|---|---|
| GS | rasterizador por software + GPU por cómputo y sprites por hardware sobre una VRAM | renderizador nativo por render targets (sin modelo de VRAM; texturas y CLUT en un almacén propio) |
| IOP | intérprete R3000 | los 8 IRX compilados a C++ por adelantado; el intérprete solo para lo que no está compilado |
| VU1 | microcódigo compilado (generar_vu1) | igual + backend nativo `vu1n_gen.py` con latencia de banderas entre bloques |
| Vídeos | FFmpeg encima de la imagen | libmpeg2 nativo, a velocidad real y con sonido |
| Plataforma | Linux | Windows (MSVC) |

Un merge línea a línea deja 39 archivos y ~8000 líneas en conflicto entre dos motores incompatibles (Waffle borró
`gs_cpu_backend.cpp`, del que depende todo nuestro GS). Por eso `ultimate` toma el runtime de Waffle completo y le
añade lo nuestro encima. El estado anterior queda en el commit «Instantánea del árbol de trabajo…» de esta rama y en
`~/Belgeler/Origami_Tobiichi_yedek_2026-10-15_premerge/` (tar.zst del código y `.git`, diff y HEAD).

## Qué se añadió al runtime de Waffle

- **Linux.**
  - `gs/gpu/gs_gl.cpp`: el contexto del GS, los de los hilos auxiliares y la presentación compartida (texturas sin
    pasar por la RAM) con GLFW. Los huecos, los fences y la carga de las funciones de GL quedan comunes a WGL y GLFW;
    el código de Windows es el de Waffle.
  - `CMakeLists.txt` (raíz): `-march=native -ffp-contract=off` con GCC/Clang (intrínsecos SSE4.1/AVX como en MSVC
    x64; sin fusionar a*b+c en FMA, igual que `/fp:precise`: la FMAC de VU y la FPU del EE redondean por separado).
  - `ps2xRuntime/CMakeLists.txt`: `ee_ref/` como carpeta de inclusión de sus propios fuentes (`common/Pcsx2Defs.h`).
  - `setlocale(LC_CTYPE, "C")` tras abrir la ventana (con tr_TR fallaban las comparaciones ASCII de 'I'/'i').
- **Funciones de Tobiichi Port** (`src/lib/gow_integracion.cpp` las conecta; en los archivos de Waffle solo hay
  llamadas de una línea en `ps2_runtime.cpp`, `gs/gs_host_present.cpp` y `Kernel/EeScheduler.cpp`):
  - ventana del lanzador (`TOBIICHI_ANCHO/ALTO`, `TOBIICHI_PANTALLA=completa` y F11, `TOBIICHI_VSYNC`,
    `TOBIICHI_TITULO`, `TOBIICHI_ICONO`, `TOBIICHI_ESC_SALIR`, `TOBIICHI_VENTANA_FPS`; `GOW_WINDOW` de Waffle
    sigue valiendo);
  - proporción `TOBIICHI_ASPECTO` (`estirar`, `4:3`, `21:9`…; sin ella 16:9 como en Waffle);
  - panorámico Hor+ `TOBIICHI_PANORAMICO=A` (parche de `config/recomp.template.toml` + factor en 0x7F00 en cada
    VBlank). Sin la variable el factor es 0,5625 con el modo 16:9 que fuerzan los overrides de Waffle: la imagen es
    la misma que en Waffle;
  - teclado configurable `TOBIICHI_TECLAS` y esquema DMC5 (`ps2_pad.cpp`, merge a tres bandas con el de Waffle:
    se conservan su vibración y su selección de mando);
  - menú de trucos (F2), fijar objetivo (Alt), combate ágil, iconos de botones según el dispositivo, escaneo
    progresivo, sonda `GOW_SONDEO`;
  - `gow_espera.cpp` (el EE duerme mientras espera el cuadro) solo con `GOW_ESPERA_EE=1`: Waffle ajustó la
    velocidad del juego (1,00) con los ciclos de ese bucle.
- **No se trajo** (lo cubre Waffle o depende de nuestro GS): el GS por hardware de Tobiichi (`gs_hw_render.cpp`), la
  imagen de los vídeos por FFmpeg (`gow_peliculas.cpp`), FSR/FXAA de la presentación (Waffle tiene su escalado
  bicúbico con nitidez, `GOW_SHARPEN`), las capturas de texturas del GS (`gow_captura_gs.cpp`).

## Código del juego

- `config/recomp.template.toml` (con el parche Hor+) y `config/funcmap.csv`, recompilados con el `ps2_recomp` de
  Waffle (6418 archivos, 0 errores; 49 archivos cambian respecto a `generated2`). El stub de `rand` (0x28C0C8) va
  comentado como en Waffle: corre el `rand` del propio juego (31 bits).
- Overrides: `src/gow_overrides.cpp` = `port/overrides-usa/gow_overrides.cpp` de Waffle (superconjunto de los de
  KIexster: heap guard, warp, vídeos, 16:9...).
- VU1: `tools/vu1/generar_vu1.cpp` es la versión de KIexster del 9 de octubre (`c73f6e3`), la que corresponde al
  `ps2_vu1_compiled.inl` de Waffle, y `tools/vu1/vu1n_gen.py` el backend nativo de Waffle (con `vu1n_heads.txt`).

## Compilar y jugar (Linux)

```sh
cd PS2Recomp
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DPS2X_ENABLE_RUNTIME_LOGS=OFF \
  -DPS2X_ENABLE_AGRESSIVE_LOGS=OFF -DPS2X_ENABLE_IOP_RPC_TRACE=OFF -DPS2X_BUILD_STUDIO=OFF \
  -DPS2X_BUILD_ANALYZER=OFF -DPS2X_RUNNER_UNITY_BUILD_BATCH_SIZE=8 \
  -DPS2X_VU1_MICROCODE_DIR="$PWD/../capturas_vu1" -DPS2X_VU1_GENERATOR_SOURCE="$PWD/../tools/vu1/generar_vu1.cpp" \
  -DPS2X_VU1N_GEN_OVERRIDE="$PWD/../tools/vu1/vu1n_gen.py"
nice -n 19 ninja -C build -j3 ps2EntryRunner
cd .. && ./run_gow.sh
```

El código generado va en `PS2Recomp/ps2xRuntime/src/runner/` (`.cpp` + `src/gow_overrides.cpp`,
`gow_pad2_packet.h`, `gow_gs_replay.h`) y sus cabeceras en `ps2xRuntime/include/`.

`run_gow.sh` usa los ajustes de `tools/waffle/play.cmd` (`PS2X_GS_WORKER=1`, `GOW_GS_FINISH_ASINCRONO=1`,
`GOW_AUDIO_DEVICE=default`), escala interna `PS2X_GS_HW_SCALE=2`, la ISO (`GOW_ISO`; este árbol no tiene PART2.PAK
extraído) y la tarjeta `Mcd001.ps2` propia del árbol. El lanzador pasa los mismos valores y la escala elegida también
como `PS2X_GS_HW_SCALE`.

## Documentación de Waffle

`docs/waffle/` (inglés): estado, diagnóstico, puerto nativo, rendimiento, sonido, vídeos, tarjeta de memoria,
detalles internos del juego. Sus herramientas están en `tools/waffle/` (zonas, partidas guardadas, vídeos,
desensambladores) y `tools/iop/` (generador del IOP nativo).
