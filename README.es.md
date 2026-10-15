<div align="center">

# God of War — Tobiichi Port

[English](README.md) · [Türkçe](README.tr.md) · **Español**

**Port nativo para PC de *God of War* (PS2, NTSC-U `SCUS-97399`), hecho recompilando estáticamente código MIPS R5900 a C++, con su propio lanzador.**

![Plataforma](https://img.shields.io/badge/plataforma-Linux%20%7C%20Windows%20x64-0078D6?logo=linux&logoColor=white)
![Lenguaje](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![Lanzador](https://img.shields.io/badge/lanzador-Qt%206-41CD52?logo=qt&logoColor=white)
![Basado en](https://img.shields.io/badge/basado%20en-PS2Recomp-8A2BE2)
![Estado](https://img.shields.io/badge/estado-jugable%20%C2%B7%20experimental-orange)

</div>

---

> [!IMPORTANT]
> Este repositorio **no contiene ningún archivo del juego** (ISO, ejecutable, módulos IRX ni datos `.PAK`) ni el
> código C++ generado a partir de ellos. Necesitas **tu propia copia legal** de God of War para PS2.

## Índice

- [Qué es](#qué-es)
- [Lo más destacado](#lo-más-destacado)
- [Estado actual](#estado-actual)
- [Inicio rápido](#inicio-rápido)
- [God Of War: Tobiichi Launcher](#god-of-war-tobiichi-launcher)
- [Estructura del repositorio](#estructura-del-repositorio)
- [Cómo funciona](#cómo-funciona)
- [Documentación](#documentación)
- [Créditos y licencia](#créditos-y-licencia)

## Qué es

En lugar de emular la PlayStation 2 instrucción a instrucción, este proyecto **traduce el ejecutable original del
juego (`SCUS_973.99`) a C++** con [PS2Recomp](https://github.com/ran-j/PS2Recomp) y lo compila como un programa
nativo de PC, enlazado con un runtime que reimplementa el hardware y el sistema operativo de la PS2 (núcleo del EE,
GS, VU1, DMA, SPU2, CD/DVD…). El procesador de E/S (IOP) ejecuta los **módulos IRX originales** del juego (driver de
sonido, lector de datos…) en un intérprete R3000A.

El objetivo es un port con sensación nativa: velocidad de juego en tiempo real, presentación fluida, gráficos y
sonido correctos.

## Lo más destacado

| | |
|---|---|
| **Lanzador** | Tarjeta gráfica, resolución, panorámica, escalado FSR, límite de FPS y rutas de archivos en un solo sitio |
| **Panorámica** | Cámara Hor+ real (16:9, 16:10, 21:9), basada en el parche de PCSX2; desactivada = idéntica bit a bit al original |
| **Resolución interna** | El GS dibuja a 1×–8× (supermuestreo); 2× por defecto, con resolución dinámica que baja un paso si la GPU no llega a 60 FPS. "Imagen nítida" quita el doblado de líneas y el antiparpadeo de la PS2 |
| **Escalado** | AMD FSR 1.0 (EASU + RCAS) y FXAA en la capa de presentación; reducción por área si la imagen es mayor que la pantalla |
| **Ventana fluida** | La ventana presenta hasta 120+ FPS con independencia de la lógica del juego a 60 Hz |
| **Audio** | Estirado temporal con zona muerta y reloj del IOP ligado al tiempo del EE: el tempo se queda en 1,00, sin bucles |
| **VU1 recompilada** | El microcódigo VU1 del juego se compila a código nativo; modo rápido con la precisión de PCSX2 (1,5 veces más rápido) o modo exacto bit a bit |
| **Velocidad real** | El VBlank sigue al reloj real: el juego pierde cuadros en lugar de ir a cámara lenta |
| **Fijar objetivo** | **Alt** fija el enemigo más cercano y Kratos dirige sus ataques a él; mueve el ratón a izquierda o derecha para cambiar de objetivo |
| **Combate ágil** | Desde una voltereta se ataca o se bloquea al 20 % en lugar del 50 %, y una pulsación de ataque perdida se repite un momento (por ejemplo, soltar L1 y atacar en el mismo cuadro); cortar ataques con el bloqueo o la evasión ya estaba en el juego |
| **Iconos de botones** | Los iconos de botones del juego siguen al dispositivo: la tecla o el botón del ratón asignados, los botones Xbox con otros mandos (A/B/X/Y, LB/RB/LT/RT) y los originales con uno de PlayStation; dibujados a la resolución de la ventana con el estilo de los menús del juego |
| **Menú de trucos** | **F2** en el juego: inmortalidad, muerte de un golpe, magia y Furia de los Dioses infinitas, orbes al máximo, todas las mejoras y poderes, todos los extras |

## Estado actual

<a href="docs/estado/detalle.es.md"><img src="docs/estado/mapa.es.svg" alt="Mapa de estado del port: funciones de las bibliotecas del SDK de Sony y componentes de hardware de la PS2, coloreados por estado" width="100%"></a>

Desglose por biblioteca y componente: [`docs/estado/detalle.es.md`](docs/estado/detalle.es.md).

| Hito | Estado |
|---|:---:|
| Recompilar `SCUS_973.99` a C++ (6 418 archivos) y compilar de forma nativa | ✅ |
| Módulos IRX originales en el emulador del IOP; lectura desde la ISO original | ✅ |
| Menús, selección de dificultad, juego, mando y teclado/ratón | ✅ |
| Imagen (OpenGL; rasterizador por hardware con `fragment_shader_interlock` o de cómputo) | ✅ |
| Audio a tempo de tiempo real | ✅ |
| Panorámica (Hor+) y escalado FSR | ✅ |
| Resolución interna 2×–8× e imagen nítida | ✅ |
| FMV: la intro se reproduce entera con imagen y sonido y pasa al juego; los demás vídeos usan el mismo camino, sin comprobar uno a uno | 🔧 |
| Tarjeta de memoria: guardar/cargar verificado; formatear sin verificar | 🔧 |
| Rendimiento: 60 FPS en partida con el modo rápido de VU1 (la escena de prueba del barco pasó de 30 a 60 en una RTX 4050) | ✅ |

### Sobre los cuadros por segundo

La lógica del juego está ligada al VBlank de 60 Hz de la PS2, así que **el juego en sí no puede pasar de 60 FPS**;
subir el VBlank solo hace que se juegue más rápido. La ventana sí puede presentar a 120 Hz o más, lo que muestra cada
cuadro nuevo antes y reduce la latencia. El límite es el hilo de VU1 (CPU). El **modo rápido de VU1**
(`PS2X_VU1_RAPIDO=ON`, la compilación por defecto aquí) usa la precisión de PCSX2 (SSE con redondeo hacia cero, DAZ/FTZ,
flags Z/S perezosos) en lugar del modelo exacto: VU1 por cuadro 22 → 13 ms y la escena de prueba más pesada de 30 a
60 FPS, con la imagen del cuadro de prueba idéntica píxel a píxel. `PS2X_VU1_RAPIDO=OFF` compila el modo exacto. Una
GPU dedicada importa para el rasterizador del GS (4–7 ms por cuadro en una RTX 4050 frente a 20–26 ms en una Radeon
680M).

**Resolución interna:** cada posición de muestra tiene su propia copia de la VRAM del GS (el esquema de
paraLLEl-GS); las lecturas y las paletas usan la copia nativa, así que el juego ve la misma memoria que en una PS2.
El coste de GPU crece con el cuadrado de la escala. En una RTX 4050 Laptop: 1× 60 FPS, 2× 40–60 FPS, 3× 18–24 FPS.
4× o más necesitan una GPU mucho más rápida. La resolución dinámica (activada por defecto)
mantiene los 60 FPS bajando hasta 1×; por debajo de eso el límite es la GPU. "Imagen nítida" ya quita por sí sola casi
todo el desenfoque de la PS2.

## Inicio rápido

Necesitas tu propio `SCUS_973.99`, los módulos del disco (`*.IRX`) a su lado y la ISO original (llamada
`God of War.iso`, en la carpeta superior a la del ELF, o indica su ruta con `GOW_ISO`). Lista completa:
[`docs/ARQUITECTURA.md`](docs/ARQUITECTURA.md).

### Linux

```bash
cd PS2Recomp
cmake --build build --target ps2EntryRunner -j$(nproc)    # compila el ejecutor del juego
cd .. && cmake -S launcher -B launcher/build -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C launcher/build                                    # compila el lanzador
launcher/build/tobiichi-launcher                           # ábrelo, revisa "Archivos" y pulsa JUGAR
```

Sin el lanzador: `./run_gow.sh`. Usa la GPU por defecto del sistema; `TOBIICHI_GPU=nvidia ./run_gow.sh` fuerza la
NVIDIA dedicada (PRIME offload).

### Windows

```bat
scripts\1_instalar_herramientas.cmd   :: solo la primera vez (Git y Build Tools con winget)
scripts\2_compilar.cmd                :: 20–40 min la primera vez
scripts\3_ejecutar.cmd
```

## God Of War: Tobiichi Launcher

`launcher/` (Qt 6 Quick, en **turco / inglés / español**) guarda tus ajustes y arranca `ps2EntryRunner` con las
variables `TOBIICHI_*` correspondientes. Detalle: [`docs/LANZADOR.md`](docs/LANZADOR.md).

| Pestaña | Qué se puede ajustar |
|---|---|
| **Gráficos** | Tarjeta gráfica, pantalla completa/ventana y resolución, relación de aspecto (4:3, 16:9, 16:10, 21:9 Hor+), estirar, escalado FSR / bilineal / píxel, nitidez, FXAA, resolución de dibujo (automática, 1×–8×), imagen nítida |
| **Rendimiento** | Límite de FPS (30 … sin límite), VSync, contador de FPS en pantalla |
| **Archivos** | Ejecutable del juego (verificado por CRC), ISO, ejecutor del port, carpeta de la tarjeta de memoria, detección automática |
| **Controles** | Esquema de teclado, comportamiento de ESC, tabla de teclas |
| **Trucos** | Trucos activos al arrancar (el menú **F2** del juego los cambia al momento) |
| **Otros** | Idioma, omitir vídeos, arranque rápido, accesos directos, registro de la última partida, restablecer, imagen de portada opcional |

`tobiichi-launcher --jugar` arranca el juego directamente con los ajustes guardados (la acción "Jugar ya" de la
entrada del menú). En el juego: **F11** alterna la pantalla completa, **F2** abre el menú de trucos y **F1** el panel de desarrollo.

## Estructura del repositorio

```
.
├── config/                       # Mapa de funciones y configuración del recompilador (incl. parche panorámico)
├── docs/                         # Documentación técnica y mapa de estado
├── launcher/                     # God Of War: Tobiichi Launcher (Qt 6)
├── patches/                      # Cambios sobre PS2Recomp, aplicados en orden
├── scripts/                      # Scripts de compilación, prueba y ejecución
├── src/                          # Reemplazos específicos del juego
├── tests/                        # Pruebas independientes del juego
├── tools/                        # Generador de VU1, mapa de estado, diagnóstico
├── PS2Recomp/                    # Runtime y recompilador (árbol de trabajo)
└── run_gow.sh                    # Script de arranque en Linux sin el lanzador
```

## Cómo funciona

```mermaid
flowchart LR
    A[SCUS_973.99<br/>ELF MIPS R5900] --> B[ps2_recomp]
    M[funcmap.csv] --> B
    C[recomp.template.toml] --> B
    B --> D[~6 400 archivos C++]
    D --> E[CMake + Ninja]
    O[gow_overrides.cpp] --> E
    P[Runtime de PS2Recomp + parches] --> E
    V[Microcódigo VU1 compilado a C++] --> E
    E --> F[ps2EntryRunner]
    I[Módulos IRX originales] --> G[Emulador del IOP R3000A]
    G --> F
    L[Lanzador] -->|variables TOBIICHI_*| F
```

## Documentación

- [`docs/ESTADO.md`](docs/ESTADO.md) — registro de la investigación: qué se probó y con qué resultado.
- [`docs/LANZADOR.md`](docs/LANZADOR.md) — lanzador, capa de presentación y panorámica.
- [`docs/RENDIMIENTO.md`](docs/RENDIMIENTO.md), [`docs/RENDERIZADO.md`](docs/RENDERIZADO.md), [`docs/CONTROLES.md`](docs/CONTROLES.md), [`docs/FMV_Y_AUDIO.md`](docs/FMV_Y_AUDIO.md), [`docs/MEMORY_CARD.md`](docs/MEMORY_CARD.md), [`docs/ARQUITECTURA.md`](docs/ARQUITECTURA.md).

Convenciones para colaborar: [`AGENTS.md`](AGENTS.md).

## Créditos y licencia

- [**PS2Recomp**](https://github.com/ran-j/PS2Recomp) de ran-j y colaboradores — recompilador y runtime (GPL-3.0).
- [**Fork del runtime de SotC**](https://github.com/LightVelox/PS2Recomp/tree/ac9efa070638ad3b3accd284de6f898d5ab271d1) de Taylor N. Albarnaz / LightVelox — backend GS OpenGL, cola de comandos y arreglos del EE (GPL-3.0).
- [**god-of-war-recomp de KIexster**](https://github.com/KIexster/god-of-war-recomp) — la tubería de recompilación de God of War y los parches de VU1/VIF sobre los que se construye este port.
- Panorámica: basada en el parche "Widescreen 16:9" de PCSX2 para SCUS-97399, de nemesis2000 y CRASHARKI.
- Lanzador: fuente [Cinzel](https://github.com/NDISCOVER/Cinzel) (SIL OFL 1.1, `launcher/recursos/fuentes/OFL.txt`); escalado adaptado de AMD FidelityFX Super Resolution 1.0 (MIT).
- *God of War* © Sony Interactive Entertainment / Santa Monica Studio. Este proyecto no está afiliado ni respaldado por Sony. No se distribuye ningún contenido del juego.

El código de este repositorio se publica bajo la licencia **GPL-3.0**, en coherencia con PS2Recomp. Ver [`LICENSE`](LICENSE).
