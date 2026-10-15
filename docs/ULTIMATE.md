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

## Medidas en este portátil (Radeon 680M, perfil de rendimiento, 15 de octubre de 2026)

Barco, partida nueva, 40-95 s, `GOW_PAD_GUION="5:start,12:x,20:x,28:x"`, IOP nativo (los 8 módulos):

| `PS2X_GS_HW_SCALE` | cuadros del juego/s | ventana | GPU |
|---|---|---|---|
| 1 | 50-56 | 60 Hz | 48-60 % |
| 2 | 46-47 | 60 Hz | 86 % |
| 3 | 35 | 13 Hz | 100 % |

- A 1x y 2x el límite no es la GPU sino el hilo de VU1 (~3 s de cada 5: 159 M ciclos de VU1 por segundo, todo
  nativo, 3,7 ns por ciclo) y la espera del EE (`guest_wait_ms` ~2,6 s de cada 5).
- A 3x la GPU está llena y la ventana (`EndDrawing`) espera detrás del trabajo del GS: el juego va a 35 cuadros/s
  pero se ven 13. Por eso `run_gow.sh` usa 2.
- Comparado con la rama `main` (mismo recorrido): 1x 60, 2x 56-60, 3x 31-32. El GS de Waffle es más ligero a 3x,
  pero aquí su VU1 en un solo hilo limita a 1x y 2x.

## Iconos de botones con el modo 16:9 del juego

Los overrides de Waffle activan siempre el modo 16:9 del propio juego (0x29CC90 = 1). En ese modo el reproductor de
Flash estira el escenario en vertical 4/3 alrededor del centro; `gow_iconos.cpp` aplica `y' = 240 + (y - 240) * 4/3`
mientras el indicador está activo (medido con seis iconos del menú de pausa y del de título: error < 4 píxeles).

## Pendiente

- La ventana a 3x (prioridad de la presentación frente al GS en la GPU, o escala dinámica en el renderizador de
  Waffle).
- Probar en partida: menú de trucos (F2), fijar objetivo (Alt) con el 16:9 del juego (la marca usa la proyección
  4:3), combate ágil, avisos de QTE.
- El lanzador (Qt) no se ha recompilado en esta rama.
- Windows: el código de WGL es el de Waffle, sin cambios de comportamiento, pero no se ha compilado en esta rama.

## Correcciones tras la primera prueba con el lanzador (15 de octubre, noche)

- **El acceso directo abría la rama main.** `~/.local/share/applications/tobiichi-launcher.desktop` apuntaba al
  lanzador de `Origami Tobiichi/`, que guardaba el ejecutable de main en sus ajustes. Ahora el lanzador de esta rama
  usa sus propios ajustes (`Tobiichi/LauncherUltimate`) y el acceso directo "Tobiichi Ultimate" lo abre; el de main
  queda como "Tobiichi Launcher (main)".
- **Panorámico Hor+ con los overrides de Waffle:** ellos escriben el aspecto 16/9 en cada lectura del mando;
  `gow_integracion.cpp` vuelve a poner el elegido justo después.
- **Vídeos a pantalla completa:** con Hor+ el juego dibujaba el vídeo en una caja 4:3 por 0x304D94 = 2 (del parche de
  PCSX2), que ya no se escribe (`TOBIICHI_PANORAMICO_304D94=1` lo recupera). Además, mientras un
  vídeo carga o se reproduce (estados 3-9 y 11 en 0x29C838) se deja el modo 16:9 de Waffle (vídeos `.PSW`).
- **"CTRL" enorme en el medidor de la Furia:** el símbolo `R2ButtonStatic` del HUD es decorativo; ya no se sustituye
  (con el mapa de teclas por defecto R2 = Ctrl).
- **Imagen demasiado nítida:** el escalado de Waffle siempre realzaba. El lanzador pasa ahora `GOW_SCALER=bilinear`
  con los filtros "bilineal" y "pixel", y con "fsr" el bicúbico con `GOW_SHARPEN` = 0,5 × nitidez (0 = sin realce).
  `TOBIICHI_FXAA=1` aplica FXAA en el mismo sombreador.
- **Contador de cuadros** (`TOBIICHI_FPS_GOSTER=1`): cuadros del juego (entradas a 0x1837B8) y de la ventana.
- **Rendimiento:** la caída a 20-35 cuadros/s fue con el perfil `power-saver` (a 1x; con `performance`, 50-56).
  El límite es la VU1 (~19 ms por cuadro con ese perfil, frente a ~9 ms del generador de VU1 de la rama main con
  `gow_espera`). Siguiente paso: el generador de VU1 de main (rondas 2 y 3 de KIexster, SIMD, modo rápido) en este
  runtime.

## Versión de salida (15 de octubre de 2026)

- **Iconos de botones originales.** Se quitó la sustitución de iconos por dispositivo (`gow_iconos.cpp`, la fuente
  incrustada, los rótulos de `ps2_pad.cpp` y la opción "Iconos de botones" del lanzador): el juego muestra sus propios
  iconos de PlayStation, como en la PS2.
- **Lanzador:** filtro "bilineal" (imagen suave) por defecto en instalaciones nuevas; el filtro "fsr" se llama ahora
  "Bicúbico (nítido)", que es lo que hace con este runtime.
- **README** (los tres idiomas) al día con esta versión.
