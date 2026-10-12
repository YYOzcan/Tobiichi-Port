# God Of War: Tobiichi Launcher

Lanzador gráfico del port (`launcher/`, C++20 y Qt 6 Quick). Guarda los ajustes y arranca `ps2EntryRunner` con
las variables de entorno que les corresponden. La interfaz está en turco, inglés y español (`qml/Textos.js`).

## Compilar y ejecutar

```sh
cmake -S launcher -B launcher/build -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C launcher/build
launcher/build/tobiichi-launcher             # --jugar: arranca el juego con los ajustes guardados
```

Requiere Qt ≥ 6.5 (Core, Gui, Qml, Quick, QuickControls2; módulos QML Controls, Dialogs, Effects, Shapes y
Particles). En "Otros" crea la entrada del menú de aplicaciones (`~/.local/share/applications/
tobiichi-launcher.desktop`, con la acción "Jugar ya" = `--jugar`) y un acceso directo en el escritorio.

## Dónde guarda cada cosa

| Qué | Dónde (Linux) |
|---|---|
| Ajustes | `~/.config/Tobiichi/Launcher.conf` (`[ajustes]`) |
| Registro de la última partida (stdout + stderr) | `~/.local/share/Tobiichi/Launcher/registros/ultimo.log` (la anterior, `anterior.log`) |
| Icono generado (omega con la fuente Cinzel) | `~/.local/share/Tobiichi/Launcher/icono.png` |
| Imagen de portada elegida por el usuario (copia) | `~/.local/share/Tobiichi/Launcher/portada-<ms>.<ext>` |
| Caché de sombreadores del GS | `~/.cache/Tobiichi/Launcher/sombreadores` (`PS2X_GS_SHADER_CACHE_DIR`) |
| Tarjeta de memoria | `mc0/` junto a `SCUS_973.99` (como siempre) |

El juego se ejecuta con la carpeta de datos del lanzador como directorio de trabajo. Al arrancar crea ahí `mc0/` y
`mc1/` vacías (rutas por defecto antes de cargar el ELF); las partidas van a `mc0/` junto al ELF.

## Imagen de portada

En "Otros" (o arrastrándola a la ventana) se puede poner una imagen propia en la portada (p. ej. Origami Tobiichi,
que da nombre al port). El repositorio no incluye ninguna: el personaje tiene derechos de autor.

- Se copia a la carpeta de datos, así que no depende del archivo original.
- Cubre la portada sin deformarse. "Posición" la sube o la baja hasta un 40 % de la zona, para dejar la cara en el
  hueco central.
- El borde superior se funde con el fondo (máscara de `MultiEffect` con `maskSpreadAtMin`; sin dispersión la
  máscara es un umbral duro).
- Se oscurece arriba (título) y abajo (estado y botón). "Brillo" la oscurece entera.

## Archivos del juego

- **ELF** (`SCUS_973.99`): se comprueba con el CRC de PCSX2 (XOR de las palabras de 32 bits) = `D6385328`.
- **Datos**: la ISO elegida (`GOW_ISO`) o, si no hay, la que buscaría el juego (`../God of War.iso` respecto al ELF
  o la primera `.iso` de su carpeta), o los archivos extraídos (`GODOFWAR.TOC` y `PART1.PAK`).
- **Ejecutor**: `ps2EntryRunner`. `rutasDetectadas()` busca el ELF y `PS2Recomp/build/ps2xRuntime/ps2EntryRunner`
  hacia arriba desde la carpeta del lanzador.

## Variables que pasa al juego

Las de rendimiento son las de `run_gow.sh` (`PS2X_GS_GPU`, `GOW_EE_CICLOS=50`, `PS2X_VU1_HILO`,
`PS2X_GS_PRESENT_BUZON`...). Si una ya está en el entorno del usuario, se respeta.

| Ajuste | Variable |
|---|---|
| Tarjeta gráfica (Linux) | NVIDIA propietaria: `__NV_PRIME_RENDER_OFFLOAD=1`, `__GLX_VENDOR_LIBRARY_NAME=nvidia`; otra no predeterminada (Mesa): `DRI_PRIME=pci-0000_BB_DD_F`; "Automática": nada |
| Tarjeta gráfica (Windows) | `HKCU\Software\Microsoft\DirectX\UserGpuPreferences`, `GpuPreference=1/2;` para el ejecutor |
| Pantalla completa / ventana | `TOBIICHI_PANTALLA=completa\|ventana`, `TOBIICHI_ANCHO`, `TOBIICHI_ALTO` |
| Relación de aspecto | `TOBIICHI_PANORAMICO=16:9\|16:10\|21:9` (sin variable: 4:3), `TOBIICHI_ASPECTO=auto\|estirar` |
| Escalado | `TOBIICHI_FILTRO=fsr\|bilineal\|pixel`, `TOBIICHI_NITIDEZ` (pasos de RCAS, 0-2), `TOBIICHI_FXAA=1` |
| Límite de FPS / VSync / contador | `TOBIICHI_VENTANA_FPS` (0 = sin límite), `TOBIICHI_VSYNC=1`, `TOBIICHI_FPS_GOSTER=1` |
| Opciones | `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1` (o sin ellas), `TOBIICHI_DMC5_CONTROLS=1\|0`, `TOBIICHI_ESC_SALIR=0\|1` |
| Siempre | `TOBIICHI_TITULO=God of War`, `TOBIICHI_ICONO=<icono.png>`, `TOBIICHI_PANEL=0` (panel de depuración oculto, F1 lo abre) |

## Lado del runtime

### Ventana y presentación (`ps2_runtime.cpp`, espacio `presentacion`)

Sin las variables todo queda como antes (`run_gow.sh` no las usa).

- **Pantalla completa**: `SetWindowSize(monitor)` + `ToggleFullscreen()`, es decir, `glfwSetWindowMonitor` con el
  modo de vídeo actual: no cambia la resolución. `ToggleBorderlessWindowed` de raylib solo quita el marco y KWin
  (XWayland) dejaba la ventana en 922x1074 en una pantalla de 1920x1200. F11 alterna; al volver se recupera el
  tamaño de ventana. En pantalla completa se oculta el cursor.
- **Proporción**: `TOBIICHI_ASPECTO=auto` usa 4:3, el aspecto de `TOBIICHI_PANORAMICO` o 16:9 si el juego tiene
  activado su propio modo panorámico (0x29CC90). Sin la variable se conserva la proporción de píxeles del GS
  (640x448, 1,43), la de antes. El rectángulo de destino va en píxeles enteros.
- **Escalado**: sombreadores GLSL 330 en el hilo principal (raylib).
  - `fsr`: EASU de AMD FSR 1.0 (12 texeles con `texelFetch`, mismo núcleo de Lanczos aproximado) a la resolución
    de destino en una textura, y RCAS 1:1 a la pantalla.
  - `bilineal`: muestreo bilineal limitado a la zona válida (el cuadro mide 640x512 y el GS llena 640x448).
  - `pixel`: el dibujo de antes.
  - `TOBIICHI_FXAA=1` suaviza a 640x448 antes de escalar.
  - Los pasos fuera de pantalla solo se rehacen con un cuadro nuevo o un cambio de tamaño.
  - Si un sombreador no compila se usa el dibujo de antes.
- **Contador** (`TOBIICHI_FPS_GOSTER=1`): cuadros del juego (`g_gowGuestFrames`, entradas a `GOW_PERF_FRAME_PC`) y
  de la ventana (`GetFPS`).
- `TOBIICHI_ESC_SALIR=0`: `SetExitKey(KEY_NULL)`; con el teclado clásico Escape es el círculo del mando.
- Pruebas: `TOBIICHI_CAPTURAS=20,50` guarda `ventana_20.png`... (la ventana tal como se ve) en la carpeta de
  trabajo.

### Pantalla panorámica (Hor+)

Basada en el parche "Widescreen 16:9" de PCSX2 para `SCUS-97399_D6385328` (nemesis2000 y CRASHARKI). El juego tiene
un modo panorámico propio (`sub_001B5A98`: aspecto 16/9 en 0x32F1B0 y en los modos de pantalla 0x2FD930/0x2FD968,
indicador 0x29CC90) que recorta la imagen por arriba y por abajo. El parche reescribe la proyección de la cámara
(`sub_00169238`, 0x169250-0x16944C) para ampliar el campo de visión horizontal por 0,75 × aspecto, y además:

- fija los tres aspectos;
- pone el indicador del juego a 1;
- escribe 0x304D94 = 2;
- hace que el reproductor de vídeo reciba 0 (0x21E4F0);
- en el fondo del menú (0x29CC50 = 1) usa 0,5625 en vez de 0,75 (recorte vertical).

En un port recompilado el código no se puede parchear en memoria, así que:

1. **Al recompilar**, `config/recomp.template.toml` aplica las 128 palabras del parche a `sub_00169238`. En
   0x1692B8/0x1692BC, `lwc1 $f1, 0x7F00($zero)` + `nop` sustituyen a `lui $at, 0x3F40` + `mtc1`: el factor F
   se lee de memoria. 0x21E4F0 pasa a `lw $a3, 0x7F04($zero)`. 0x7F00-0x7F07 es memoria del núcleo que el juego no
   usa; el runtime solo usa 0x2F0/0x2F8 y la tabla de syscalls en 0x11F80.
2. **En el runtime**, `gowPanoramicoVBlank` (`Kernel/EeScheduler.cpp`) escribe F y el indicador de vídeo al
   arrancar el planificador y en cada VBlank.
   - **Sin `TOBIICHI_PANORAMICO`**: F = 0,75 (o 0,5625 si el juego está en su modo 16:9; si no, 1/aspecto), y el
     indicador de vídeo = 0x29CC90. F × aspecto da exactamente 1,0 (`0x3F800000`, comprobado en el host), así que
     la proyección da lo mismo bit a bit que el código original.
   - **Con `TOBIICHI_PANORAMICO=A`**: hace lo mismo que el parche, con A en lugar de 16/9 y F = 1/A en el fondo
     del menú.

El HUD y las pantallas 2D se estiran en horizontal (el parche tampoco los corrige). Con un ejecutor generado sin
estos parches, el runtime escribe en 0x7F00/0x7F04 sin efecto (el código original no lee ahí) y solo queda el modo
panorámico del juego, con recorte.

### Lo que no hay: resolución interna 2×-4×

El GS se emula sobre su VRAM de 4 MB con direcciones entrelazadas por formato (rasterizador de cómputo o por
hardware con `fragment_shader_interlock`). Dibujar a 2×-4× exigiría una copia supermuestreada de la VRAM,
resolverla en las transferencias local→local y al leer render targets como texturas, y presentar desde ella. Es
el esquema de paraLLEl-GS y supone un trabajo grande.

Además, el coste de rasterizado crece con el cuadrado de la escala. Hoy cuesta 4-7 ms por cuadro en la RTX 4050
y 20-26 ms en la 680M; a 2× serían 16-28 ms en la 4050. El lanzador lo indica ("Resolución de dibujo: 1×") y
ofrece FSR 1.0 para ganar nitidez a la resolución de la pantalla.

## Verificado (12 de octubre de 2026, Radeon 680M, pantalla 1920x1200)

- `logs/perf_lanzador2`: 150 s con `GOW_PAD_TEST` y las variables del lanzador (pantalla completa, 16:10, FSR + FXAA,
  contador).
  - Guarda de imagen: OK.
  - Velocidad del juego 1,00.
  - Ventana 105-120 FPS.
  - Juego 60 en el menú y 30 en la partida, con la GPU integrada al 90-100 % (limita el rasterizado del GS).
  - Sonido: tempo 1,00 y sin vaciados.
- Capturas de la ventana: 1920x1200, imagen 16:10 sin bandas; los personajes y la cara de Kratos del menú con
  proporciones correctas (Hor+), el HUD estirado.
- Lanzador de punta a punta (`--jugar`):
  - encontró el ELF (CRC correcto), la ISO y el ejecutor;
  - el juego arrancó a pantalla completa 1920x1200;
  - el registro quedó en `registros/ultimo.log`.
- Recompilación: con `config/recomp.template.toml` el recompilador genera exactamente los 6418 archivos de
  `generated2` (0 diferencias). Sin las palabras nuevas también: el `generated2` de antes salía igual.
