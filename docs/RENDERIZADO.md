# Renderer CPU y OpenGL

`patches/ps2recomp-gs-opengl.patch` adapta `GSGpuBackend` y `GSThreadedBackend` del fork
de [Taylor N. Albarnaz / LightVelox](https://github.com/LightVelox/PS2Recomp/tree/ac9efa070638ad3b3accd284de6f898d5ab271d1),
rama `sotc-port`, commit `ac9efa070638ad3b3accd284de6f898d5ab271d1`, bajo **GPL-3.0**.
Gracias a sus autores por el backend y el trabajo del port
[sotc-vibe-pc](https://github.com/LightVelox/sotc-vibe-pc). Los archivos importados llevan
`// GOW-Port:` y el commit completo de origen. Los helpers del GPU quedan separados de los
del renderer CPU existente para conservar la comparación.

El CPU sigue siendo la opción predeterminada. El parche solo modifica el GS, su integración
CMake y sus pruebas. No modifica EE, FPU, IOP, VIF, VU1 ni `ps2recomp-fpu-roots.patch`.

## Selección

Después de `scripts\2_compilar.cmd`, en PowerShell:

```powershell
# CPU directo: referencia conservada.
$env:PS2X_GS_GPU = '0'; $env:PS2X_GS_THREAD = '0'

# CPU en el hilo GS: permite separar el efecto de la cola del rasterizado GPU.
$env:PS2X_GS_GPU = '0'; $env:PS2X_GS_THREAD = '1'

# OpenGL en el hilo GS.
$env:PS2X_GS_GPU = '1'; $env:PS2X_GS_THREAD = '0'
scripts\ejecutar.ps1 -Segundos 150
```

Esta adaptación crea un contexto **WGL en Windows con shaders OpenGL 4.6**. Usa rasterizado
gráfico cuando están disponibles las funciones necesarias, con camino compute para los otros
casos. Si falla el contexto o la compilación inicial de shaders, el wrapper cambia al CPU y
emite `[gow-gs] OpenGL no disponible; usando CPU en el hilo GS.`. Ese fallback no cuenta como
validación de GPU. En Linux se compila el backend, pero su contexto es un stub y usa el fallback.

Las lecturas, FINISH y Flush respetan los comandos anteriores. La cola copia los datos enviados
por el EE, conserva cambios de estado y drena sus últimos comandos antes de destruir el contexto
en el hilo propietario. Las tablas de VRAM se inicializan una vez. La presentación se adapta a
las filas de 640 píxeles del frontend existente; aún no se integra la presentación compartida
entre contextos GL del fork. La salida pasa por la copia de píxeles habitual del port.

`ps2recomp-gs-presentation.patch`, aplicado después del backend, incorpora la selección
`preferredSource` del frontend con las mismas condiciones que el CPU para un solo circuito
activo. Esa fuente es una textura con base en **bloques de 256 B**; `DISPFB` usa **páginas de
8 KB**. El shader recibe bases en bloques: convierte la base CRTC una vez y conserva todos
los bits de la fuente preferida. Usa su stride/formato y origen cero, sin alterar el destino
CRTC. Los formatos admitidos son CT32, CT24, CT16 y CT16S. Dos circuitos activos conservan
la composición CRTC. Se mantiene la procedencia de la imagen en el readback diferido y
se incluye la selección en la clave de la presentación compartida, aunque esta última
continúa desactivada en la integración del port.

Con `SMODE2 & 3 == 1`, el compositor duplica las filas del campo seleccionado por
`vsyncTick & 1`: par e impar se alternan usando la paridad real del GS. La clave de
presentación compartida también incluye el campo. El modo progresivo conserva sus filas
y no depende de esa paridad. Con un solo circuito activo se muestra su RGB directamente,
sin mezclarlo contra el fondo por el alfa del píxel; con dos se conserva la mezcla PMODE.

En la **prueba inicial anterior a esta corrección** se ve el menú con defectos y, en estado 11, agua oscura sin
Kratos ni el entorno completo. Las capturas tardías OpenGL de `56–130 s` son idénticas;
las del CPU de `70–130 s` cambian. La mejora de `vid::Flip` no equivale a más imágenes distintas.

Las regresiones de presentación se ejecutan con GPU real, tanto compute como rasterizado
gráfico. Comparan los cuatro formatos con el CPU, una fuente no alineada a páginas, un stride
distinto, origen CRTC no nulo y actualizaciones posteriores. También comprueban destino
incompatible, ausencia de fuente, formato no admitido y composición de dos circuitos. Comparan
campos par/impar, modo progresivo y píxeles sin alfa. Otra muestra usa la temporización
completa de GoW con un patrón sintético de 512×448, sin assets del juego. Antes del arreglo
fallan ambas pruebas GPU (**472/474**); con el arreglo pasan **474/474**.

La observación temporal del juego encontró dos circuitos activos, sin fuente preferida,
con `PMODE=0x8023` y modo de campos. Se compararon ambos compositores sobre la **misma VRAM
obtenida del GPU**: las imágenes diferían porque el CPU seleccionaba el campo y OpenGL
omitía esa paridad. Esto acota
esa diferencia al compositor, sin atribuirla a VU1 ni a un fallo general de escritura de
vértices. Los diagnósticos temporales se retiraron tras localizar la causa. La alternancia
de campos por sí sola no acredita animación ni una partida jugable.

Una ejecución de 155 s con el arreglo, antes de integrar EE/FPU, inicializa la GPU real
sin fallback y alcanza el estado 11. Las cuatro capturas de `70–130 s` son distintas,
frente a las capturas tardías idénticas anteriores. Sigue apareciendo agua oscura, sin
Kratos ni el entorno completo. Esta comprobación verifica la salida del compositor;
la geometría y una partida jugable siguen pendientes.

Tras integrar el parche EE/FPU de Opus y reconstruir las 6418 unidades, la suite nativa
con GPU real pasa **481/481**, y las pruebas separadas de caché GS **45/45**. Las cifras
anteriores de 474 corresponden al runtime previo a esa integración.

La prueba combinada del juego también llega al estado 11 sin fallback. Con los
diagnósticos activados guarda tres capturas distintas a `94,85 / 95,19 / 110,10 s`,
con agua y artefactos; todavía sin Kratos ni el escenario completo. No es un perfil
de rendimiento. Las posiciones observadas mantienen la plantilla deliberada del
loader y los dos buffers no nulos cambiantes; ver el registro en `docs/ESTADO.md`.

## Comparación reproducible

```powershell
scripts\probar_rendimiento.ps1 -Renderer cpu -SoloCuadros -Etiqueta gs_cpu
scripts\probar_rendimiento.ps1 -Renderer cpu-hilo -SoloCuadros -Etiqueta gs_cpu_hilo
scripts\probar_rendimiento.ps1 -Renderer opengl -SoloCuadros -Etiqueta gs_opengl
```

Las ejecuciones deben ser consecutivas, con el mismo ELF, ISO, binario, mandos y escena, sin
capturas ni diagnósticos pesados durante el perfil. El script restaura las variables al terminar.
Comparar `vid::Flip` en estado 11 y presentación del host por separado. El reparto exclusivo
EE/IOP/GS/VU del perfil original describe el hilo del juego; al mover el GS a otro hilo ya no
contabiliza todo su trabajo y no sirve para comparar porcentajes de coste entre renderers.

Prueba local del 2026-10-05, AMD Radeon RX 5700 XT, mismo binario y tres ejecuciones
consecutivas. En cada una se toman tres ventanas completas de 5 s dentro de `120–136 s`,
con el juego en estado 11. Se omiten capturas y diagnósticos de geometría:

| Renderer | `vid::Flip`/s del juego | Presentaciones/s del host |
|---|---:|---:|
| CPU directo | 2,40 | 56,33 |
| CPU con hilo | 2,39 | 55,68 |
| OpenGL con hilo | 3,26 | 59,12 |

En esta muestra, OpenGL mejora aproximadamente un 36 % frente al CPU directo. Son llamadas
a `vid::Flip`, no imágenes distintas ni una medida de jugabilidad. Una ejecución por modo
y unos 15 s de observación son una comparación inicial, sin estimar variabilidad. El hilo GS
con CPU no aporta una mejora en esta muestra. Las capturas se revisan en ejecuciones separadas.

La suite normal comprueba propiedad de payloads, orden de transferencias, estados compactos,
barreras, destrucción de la cola y equivalencia CPU directo/CPU con hilo. Contrasta el
direccionamiento y máscaras de los 13 formatos de VRAM con la implementación existente.

Con una GPU local, habilitar las dos pruebas adicionales antes de ejecutar `ps2x_tests` desde
la raíz de PS2Recomp:

```powershell
$env:GOW_GS_GPU_TEST = '1'
out\build\ps2xTest\ps2x_tests.exe
Remove-Item Env:GOW_GS_GPU_TEST
```

Estas pruebas exigen que se inicialice el GPU real. Comparan clear, sprites, transferencias y
VRAM completa; comprueban el interior/exterior de un triángulo plano, textura CT32 y los píxeles
de presentación. Corren tanto con compute forzado como con rasterizado gráfico permitido.
Cubren esos casos sintéticos; no certifican toda la precisión GS ni una partida jugable.

## Productor de posiciones

`GOW_EE_PRIM_DIAG=1` añade observación limitada de `renEEPrim::InitUNPACKData` (`0x141350`) y
`GetUpdateAddress` (`0x1417D8`). Registra objeto, caller, tipo, chunk, buffer y dirección devuelta;
para posiciones, muestra el primer vector **antes de que el caller lo rellene**. Un checkpoint
se etiqueta como tal y no se trata como retorno. No cambia los datos del juego.

Las muestras se limitan a 64 inicializaciones, 64 direcciones antes del estado 11 y 256 en ese
estado. Con el mando automático se releen cada 5 s hasta 16 direcciones observadas para ver
cambios posteriores. Esos buffers pueden reutilizarse; la lectura tardía no garantiza que el
objeto original siga siendo su propietario. El perfil elimina esta variable para evitar mezclar
la investigación con la medición.
Los ceros previos a la escritura pueden ser una reserva válida: hay que contrastar el buffer
después del productor y el payload DMA/VIF antes de atribuir un fallo. Repetir la prueba cuando
Opus integre sus arreglos de semántica EE/FPU.

La primera ejecución de este diagnóstico registra 64 inicializaciones, 298 retornos de
posiciones y 192 lecturas posteriores. El caller `0x12E258`, dentro de `LoadClient`
(`0x12DE70`), obtiene 40 buffers. En las 14 direcciones de ese caller que conserva la
sonda, todas las lecturas posteriores muestran `(0,0,0,0x8000)`. La inspección del MIPS
original confirma que el bucle `0x12E270–0x12E288` escribe precisamente esa plantilla:
es una inicialización explícita del juego, no una posición calculada que el diagnóstico
haya visto perderse. La primera reserva incluye los chunks observados anteriormente en
el payload VIF con XYZ cero.

El caller `0x1FB800`, dentro de la función `0x1FB4B8`, devuelve dos buffers con XYZ no
nulo y cambiante, también en sus lecturas posteriores. No se observa en esta muestra un
retorno de `GetUpdateAddress` desde `goWater::InitEEPrim` o `UpdateEEPrim`. Estos resultados
acotan la investigación: seguir la transformación de esas plantillas, su selección de
datos y el resultado que VU1 entrega a GIF; no sustituirlas arbitrariamente por posiciones.

La traza posterior, con EE/FPU integrados, vincula mediante las direcciones DMA dos de
esas plantillas (`0x812390` y `0x7F3220`) con sus buffers de `LoadClient`. Llegan en cero
al UNPACK y se observan así en memoria VU1 antes de transformarse. Los dos buffers
actualizados por `0x1FB800` no aparecen como origen de payload en las ocho cadenas
muestreadas; su envío sigue pendiente de identificar. En los primeros 256 paquetes
PATH1 hay 2.654 vértices, 337 con kick y 2.317 sin kick (ADC/XYZ3), con casos de XYZ
repetidos y otros de posiciones distintas. Estos resultados localizan datos y descartes
anteriores al backend GS; no demuestran por sí solos un fallo de VIF/VU1 ni corrigen
la escena ausente. Direcciones, replay y límites: [`ESTADO.md`](ESTADO.md).

La misma variable también observa la entrada de `renEEPrimContext::ProcessServer`
(`0x141B78`). Guarda hasta 64 muestras antes del estado 11 y otras 64 dentro de él.
Por muestra recorre hasta 256 nodos, comprueba límites y ciclos, y registra cámara,
ID/máscara de vista y pertenencia de los objetos observados por `GetUpdateAddress`.
`candidates` solo cuenta los que pasan los primeros filtros de cámara, vista e índice
de DMA en esa fotografía; no acredita visitas posteriores, rasterizado ni dibujos.
Con `invalid`, `cycle` o `truncated` activos, una ausencia en la muestra no permite
afirmar que el objeto no pertenece al resto de la lista. Los registros usan las etiquetas
`[gow-eeprim:context]` y `[gow-eeprim:member]`; no modifican memoria ni índices y las
reanudaciones tras checkpoints llaman directamente al original. Tampoco se usan para medir FPS.

## Inspección offline de GIF

El inspector usa solo la biblioteca estándar de Python y recibe un paquete binario
o una carpeta de capturas locales `gow_geo_gif_*.bin`:

```powershell
python tools/gs/inspeccionar_paquetes.py logs/gs_geometry_probe --json logs/gif_summary.json
python -m unittest discover -s tests -p test_gif_inspector.py
```

Valida tamaños de PACKED, REGLIST (incluido su padding) e IMAGE; el formato 3 no está
soportado. Cuenta escrituras XYZF2/XYZ2/XYZF3/XYZ3 y A+D, distinguiendo kick de ADC/XYZ3.
El JSON contiene métricas, rangos XYZ, etiquetas y SHA-256 por archivo; no copia los
payloads. Los tipos PRIM solo cuentan etiquetas PACKED con PRE: no reconstruyen todo
el estado GS ni las primitivas que efectivamente rasteriza. Los valores X/Y conservan
sus unidades GS, antes de aplicar XYOFFSET. Un kick no garantiza un triángulo visible.

La captura de esta investigación usó sondas temporales VIF/VU1 y un replay local, ya
retirados. `GOW_GEOMETRY_DIAG` y `GOW_REPLAY_STEM` no son opciones del runtime publicado.
Conservar capturas e informes bajo `logs/`; no subir RAM, microcódigo ni datos del juego.

## Transferencias DIRECT de PATH2

`ps2recomp-vif-direct.patch` adapta la corrección de Claude en
[`540defd`](https://github.com/KIexster/god-of-war-recomp/commit/540defd): una IMAGE pendiente
solo consume el payload de los siguientes DIRECT/DIRECTHL. Los comandos VIF entre ellos
siguen ejecutándose. La prioridad corresponde al comando actual, incluso si cambia entre
DIRECT y DIRECTHL al continuar la misma imagen.

`ps2recomp-vif-direct-fragments.patch` conserva por separado el tamaño pendiente de un
DIRECT que llega dividido entre bloques DMA o escrituras FIFO. Su acumulador está limitado
a 65.536 QW (1 MiB, también para IMMEDIATE=0). Solo copia las cargas incompletas; la ruta
que recibe un DIRECT completo sigue enviando sus bytes directamente. Inicializar la memoria
o escribir VIF1_FBRST.RST descarta esa continuación y su prioridad.

Estos dos parches completan el DIRECT antes de entregarlo al parser GS. La continuación
PACKED/REGLIST entre distintos comandos DIRECT se añade después con `ps2recomp-gif-stream.patch`,
descrito abajo. No se reproducen todos los stalls ni los ciclos del hardware ni se añade
continuación de otros comandos VIF. La referencia de comportamiento
es [`_vifCode_Direct` de PCSX2](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/Vif_Codes.cpp),
que conserva el tamaño pendiente y distingue DIRECT de DIRECTHL; no se ha copiado su código.
Se mantiene el crédito del port GS a Taylor N. Albarnaz / LightVelox indicado al inicio.

Las regresiones comprueban píxeles IMAGE, comandos MARK/STCYCL/ITOP intermedios, nuevos
GIFtags después de una imagen, prioridad DIRECTHL, PACKED/REGLIST con todos los cortes
de byte en un payload de 32 B, escrituras FIFO, el tamaño máximo y reset. No contienen
datos del juego. `GOW_VIF_DIAG=1` añade hasta 16 mensajes `[gow-vif-direct]` de inicio y
otros 16 de finalización de transferencias fragmentadas. No habilitarlo para medir FPS.

## Orden de los paquetes GIF

`ps2recomp-gif-order.patch` conserva el orden FIFO dentro de PATH1, PATH2 y PATH3. La cola
agrupa por path con una comparación estricta y elige después entre sus cabeceras: PATH1
tiene prioridad; un DIRECTHL de PATH2 espera a una IMAGE que esté en la cabecera de PATH3.
Un DIRECT normal conserva su prioridad sobre PATH3. No se adelanta una IMAGE a su setup ni
un DIRECT posterior a un DIRECTHL previo del mismo canal.

La excepción DIRECTHL/IMAGE usada antes dentro de `std::stable_sort` no cumplía el
[orden débil estricto exigido por C++](https://eel.is/c++draft/alg.sorting.general#3).
Dos regresiones cubren todas las permutaciones de esos grupos y la prioridad PATH1.
Este arreglo ordena paquetes completos en la abstracción actual; no reproduce todos los
stalls, preempciones ni ciclos del GIF real. Las pruebas son sintéticas y no acreditan
por sí solas una mejora en la imagen o los FPS del juego.

## Etiquetas GIF vacías y PRE

`ps2recomp-gif-tag-semantics.patch` corrige el frontend que comparten los backends CPU y
OpenGL. Una etiqueta con `NLOOP=0` no emite registros: conserva PRIM, los vértices pendientes
y Q. `PRE/PRIM` de la etiqueta solo se aplica en PACKED con datos, y se ignora en REGLIST
e IMAGE. Se corrigen tanto `processGIFPacket` como la ruta PACKED nativa validada. El
atajo de subida IMAGE también respeta PRE del setup PACKED y el reinicio de Q de las
etiquetas no vacías, conservando los bytes subidos e ignorando PRE de IMAGE.

La regla coincide con `GSState::Transfer` de
[PCSX2, commit 32ac6e2](https://github.com/PCSX2/pcsx2/blob/32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e/pcsx2/GS/GSState.cpp#L3371),
que referencia la sección 7.2.2 del manual EE. El arreglo y las pruebas son propios;
no se incorpora código de PCSX2. Cuatro regresiones comprueban el estado, la conservación
de un triángulo entre etiquetas vacías y Q, los controles con PACKED no vacío y PRE,
y los efectos del setup en la subida IMAGE nativa.
Este parche no modifica VIF; la continuación entre DIRECT distintos se añade en el
siguiente parche.

## Continuidad del flujo GIF por PATH

`ps2recomp-gif-stream.patch` conserva por separado el cursor de PATH1, PATH2 y PATH3:
etiqueta incompleta, formato, registro actual, registros pendientes, padding REGLIST y
bytes IMAGE. Cada cursor retiene como máximo 15 bytes de una unidad incompleta. Las
subidas IMAGE contiguas siguen llegando al backend en bloques grandes; no se almacena
otra copia del payload completo en el frontend.

Un nuevo bloque continúa la etiqueta pendiente de su PATH, en lugar de leer sus datos
como otra GIFtag. Q y PRE se aplican al completar una etiqueta, conservando las reglas
de etiquetas vacías. El estado del GS y los registros siguen siendo compartidos; solo
el cursor de lectura es independiente. Reset elimina esos cursores. Los atajos PACKED
y DMA IMAGE se rechazan cuando PATH3 tiene un flujo incompleto, para que lo complete el
parser general.

El callback del árbitro conserva el identificador del PATH; los clientes anteriores de
dos argumentos mantienen su interfaz. VIF entrega los bytes originales de cada DIRECT:
se retiran las etiquetas IMAGE sintéticas que antes envolvían las continuaciones, pues
el frontend conserva ahora su tamaño pendiente. La prueba existente de continuación
comprueba por eso el payload original junto a la etiqueta siguiente, en vez del wrapper.
MARK, STCYCL e ITOP entre comandos VIF siguen ejecutándose.

Nueve regresiones sintéticas comprueban todos los cortes de byte de PACKED, ST/Q y
vértices, REGLIST impar y su relleno, IMAGE y la etiqueta siguiente, NREG=0 (16 registros),
reset, tres PATH intercalados, los atajos nativos y un PACKED repartido entre tres DIRECT.
El frontend es común a CPU y OpenGL; estas pruebas no incluyen archivos del juego.

## Prioridad de las continuaciones IMAGE

`ps2recomp-gif-image-order.patch` clasifica el flujo PATH3 mediante sus etiquetas y
tamaños pendientes. Un bloque de pixels IMAGE conserva su clasificación aunque no
empiece por una etiqueta. Los registros PACKED/REGLIST y el relleno no se interpretan
como etiquetas, aunque sus bits coincidan con IMAGE. También se reconoce IMAGE tras un
setup dentro del mismo bloque. NLOOP=0 no inicia una imagen ni bloquea DIRECTHL.

Se conserva el arbitraje FIFO entre cabeceras del parche anterior. La clasificación
abarca el bloque completo; sigue siendo la abstracción de paquetes del runtime, sin
reproducir la preempción o los ciclos del GIF real. Reset descarta el cursor PATH3 junto
a la cola. Seis regresiones cubren continuaciones entre drains, setup seguido de IMAGE,
datos que parecen etiquetas, IMAGE vacía, padding/etiqueta parcial y reset. Cuatro fixtures
anteriores de prioridad pasan a usar NLOOP=1 con pixels: sus expectativas de orden se
conservan y se elimina la suposición de que una IMAGE vacía transmite datos.

## Compatibilidad IMAGE2

`ps2recomp-gif-image2.patch` trata FLG=3 como IMAGE2, siguiendo la compatibilidad de
[`GSState::Transfer` de PCSX2, commit 32ac6e2](https://github.com/PCSX2/pcsx2/blob/32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e/pcsx2/GS/GSState.cpp#L3489).
Se consume su payload como IMAGE, sin aplicar PRE, en el frontend y el atajo de subida
completa. El árbitro conserva esa clasificación en sus continuaciones. El nombre
anterior `GIF_FMT_DISABLED` se mantiene como alias de API. El arreglo es propio; no se
copia código de PCSX2 ni se presenta FLG=3 como un modo documentado de uso normal del juego.

Tres regresiones verifican todos los cortes de byte y la etiqueta siguiente, los pixels
de la subida nativa en CPU y en un backend de observación, PRE del setup y el arbitraje
de la etiqueta y su continuación. No se ha demostrado que GoW emita IMAGE2 en la escena
observada; el cambio evita desincronizar el parser si recibe este formato.

## Estado de las etiquetas en el atajo DMA de texturas

`ps2recomp-gif-native-tag.patch` completa los efectos de las etiquetas en el atajo
`tryProcessNativeGifImageUploadChain`. Tras validar la cadena entera, pasa la etiqueta
PACKED del setup a `uploadImageNative`: reinicia Q y aplica PRE bajo el mismo lock que
la subida. PRE de la imagen se ignora. También admite IMAGE2, como el frontend general.
Un argumento opcional conserva la API anterior de subida directa sin etiqueta.

Una regresión reproduce antes del arreglo la pérdida de PRE y el Q antiguo en el
siguiente punto, además del rechazo de IMAGE2. Cubre IMAGE/IMAGE2 con PRE activado y
desactivado, pixels y conservación del color. Otra prueba rechaza una cadena con terminal
inválido y comprueba que no cambie PRE/Q, no suba pixels ni incremente el contador nativo.
El atajo sigue validando todos los datos antes de aplicar sus efectos.

## Pixels de 24 bits entre bloques IMAGE

`ps2recomp-gs-image-fragments.patch` conserva uno o dos bytes de un pixel CT24/Z24
cuando termina una carga `UploadImage`. El backend completa ese pixel con la carga
siguiente y entrega el resto en bloques alineados a tres bytes. CPU y OpenGL comparten
este pequeño acumulador; no se copia el payload completo ni se altera la ruta de otros
formatos. Terminar la transferencia descarta su padding. Reset y una nueva transferencia
descartan los bytes pendientes; exportar/importar OpenGL conserva el pixel parcial.

La reproducción inicial sube 48 bytes: en una carga produce 16 pixels, pero en tres
cargas de 16 B produce 15 y deja dirección 0 activa, tanto en CPU como en OpenGL real.
Cuatro regresiones cubren CT24/Z24 en todos los cortes de los 48 bytes, cargas repetidas
de un byte y de un quadword, preservación del byte alto de VRAM, reset/nueva transferencia
y exportación de uno o dos bytes pendientes. Dos pruebas requieren OpenGL real y dos
se ejecutan siempre en CPU. Antes del arreglo fallan tres; después pasan las 519 pruebas
nativas, también después de la compilación completa de 6.418 unidades. La auditoría
reproduce 26 parches y 73 fuentes sin diferencias. El control de partida de 175 s llega
al estado 11 sin fallback CPU; las capturas de 90,15 y 110,13 s siguen mostrando agua
sin Kratos ni el escenario completo. Las 64 llamadas observadas a Clip en esa fase
siguen descartando con `0x80000000` y Y/Z idénticas. No se acredita una mejora de FPS.

## Triángulos CPU como referencia para OpenGL

`ps2recomp-gs-triangle-sampling.patch` elimina el desplazamiento de medio pixel del CPU,
conserva los cuatro bits fraccionales de XYOFFSET y aplica la inclusión de bordes
superiores/izquierdos. Reutiliza `gs_triangle_rules.h`, adaptado de Taylor N. Albarnaz /
LightVelox, commit `ac9efa070638ad3b3accd284de6f898d5ab271d1`, igual que OpenGL.
Las aristas se calculan en entero y avanzan por sumas dentro de cada fila; la Z se
interpola por diferencias para conservar los valores planos de 32 bits.

La convención está descrita en las secciones 2.4.4 y 3.2.9 del
[GS User's Manual](https://www.scribd.com/document/784545197/GS-Users-Manual):
el centro del pixel de pantalla tiene coordenadas enteras y un borde compartido
pertenece a un solo triángulo. La conversión y el recorrido del renderer software de
[PCSX2](https://github.com/PCSX2/pcsx2/blob/32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e/pcsx2/GS/Renderers/SW/GSRasterizer.cpp)
sirven como comprobación independiente; no se copia su código.

Tres regresiones fallan en CPU antes del cambio y pasan ya en las dos rutas OpenGL:
color interpolado en un centro conocido, XYOFFSET fraccional y dos triángulos con
alpha que deben cubrir el borde compartido una sola vez, en ambos sentidos de giro.
Dos fixtures antiguos de STQ/filtro lineal se recalculan para el centro entero, conservando
su capacidad de distinguir interpolación homogénea y filtrado. El fixture de fan ahora
lee CT32 con su distribución swizzled de referencia y exige exactamente el rectángulo
interior de centros enteros; la lectura lineal anterior inventaba huecos.

La comparación sintética de VRAM completa pasa de 12 diferencias a **48/48 casos iguales**
entre CPU y OpenGL compute/hardware, con IIP, cuatro pruebas Z y valores Z32 altos.
Las pruebas del parche y la compilación completa se registran en `ESTADO.md`.

## Sprites CPU como referencia para OpenGL

`ps2recomp-gs-sprite-sampling.patch` reutiliza los ejes firmados de `gs_sprite_rules.h`,
adaptados del mismo commit `ac9efa070638ad3b3accd284de6f898d5ab271d1` de Taylor N.
Albarnaz / LightVelox. El CPU conserva XYOFFSET y UV fraccionales, muestrea en el
centro entero y calcula la textura desde los extremos originales incluso cuando se
invierten los ejes o se recorta con scissor. Un ancho o alto cero deja de dibujar.
Las reglas de cobertura y el recorrido se contrastan con el manual GS 3.2.9 y el
renderer software de PCSX2 enlazados en la sección anterior; OpenGL ya usaba esos ejes.

Cuatro pruebas CPU reproducen los fallos antes del cambio: cobertura fraccional,
área cero, UV con filtro lineal y textura invertida/recortada. Otra prueba exige
OpenGL real en compute y hardware para los mismos casos. La muestra constante
UV=0,75 da `0x80000707` en OpenGL y `0x80006666` en el CPU anterior; también se
contrasta la ruta STQ. La sonda separada de VRAM completa pasa de **14 diferencias
a cero en 16 casos**. Los datos son sintéticos.

Ocho fixtures antiguos de alias CT32, CLUT, alpha y scissor usaban sprites con dos
vértices iguales y dependían del ancho/alto mínimo de un pixel que inventaba el CPU.
Ahora especifican rectángulos de 1×1 sin cambiar las aserciones de esas propiedades.
La regresión nueva exige que una primitiva vacía no cambie la VRAM. No se alteran
el frontend, VIF, VU1, los shaders ni los parches de EE/IOP.

## Color, alpha y niebla constantes en triángulos

`ps2recomp-gs-triangle-constants.patch` interpola RGBA Gouraud y el coeficiente F
por diferencias entre vértices, en CPU y en el código común de los shaders compute/
hardware. Es un ajuste propio sobre el renderer adaptado de SotC. La suma de tres
pesos float redondeados podía quedar por debajo de uno: incluso con atributos iguales
en todos los vértices perdía una unidad de color, alpha o F.

Se reproduce con un triángulo de 17×19 pixels: en CPU se alteran 17 centros con color
constante y 8 con F constante; en cada ruta OpenGL, 151 y 110 respectivamente.
La referencia para color es RGBA exacto; para niebla se compara con un punto de los
mismos atributos, que usa la aplicación de niebla existente sin interpolar F.
El problema incluye alpha 128 convertido en 127, que puede fallar GEQUAL 128 y dejar
huecos aun cuando los vértices tengan alpha suficiente.

Dos regresiones CPU y una OpenGL fallan antes del cambio. Verifican ambos sentidos
de giro, todos los centros interiores, RGBA constante con alpha-test GEQUAL 128 y
F constante frente al control sin interpolación. El shader convierte a float antes
de restar atributos para admitir diferencias negativas sin underflow de enteros.
La suite nativa pasa **531/531**, incluidas siete pruebas con OpenGL real. La sonda
separada y la comparación de gradientes se registran en `ESTADO.md`.

## Coordenadas de textura constantes en triángulos

`ps2recomp-gs-triangle-texcoords.patch` conserva UV 12.4 y S/T/Q constantes mediante
interpolación por diferencias en CPU y OpenGL compute/hardware. Las restas mantienen
el signo para admitir UV descendentes. S, T y Q siguen siendo valores homogéneos:
la división por Q se hace después de interpolar, al muestrear la textura.

La regresión de Q constante de 1,5 detectó además un recíproco inferior en la GPU:
el primer centro ya seleccionaba el texel anterior. El shader refina `1/Q` con el
residuo de una operación `fma` consumida por `precise`; conserva el camino de recíproco
cero. Es un ajuste GS propio, separado de la FPU del EE. GLSL permite un error de
hasta 2,5 ULP en la división y especifica el uso de `precise` con `fma` en las
secciones 4.7.1 y 8.3 de la [especificación de Khronos](https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.4.60.pdf).

Dos pruebas CPU y una OpenGL fallan antes del cambio. Comparan todos los centros
interiores con un sprite texturizado de 1×1 y valores de referencia explícitos,
en ambos sentidos de giro, con nearest y filtrado lineal. Comprueban también un
gradiente descendente y Q variable en un centro lejos de fronteras de texel.
La suite integrada con el parche IOP de Opus pasa **535/535**, incluidas ocho
pruebas con OpenGL real. La precisión en fronteras exactas con Q variable se sigue
investigando por separado; conservar atributos constantes no resuelve todos esos casos.
La sonda independiente confirma la ruta hardware usando los contadores de batches,
primitivas y tiles compute, después de esperar de forma acotada sus variantes asíncronas.

## Integración con MMI y VU0

La integración posterior con MMI y VU0 de Opus pasa **545/545** pruebas nativas con
OpenGL. En estado 11 desaparece la duplicación Y/Z de las esferas: 30 de las primeras
64 llamadas observadas pasan Clip, frente a cero antes. Las capturas ya muestran
polígonos y texturas distintos, pero siguen deformados y sin Kratos reconocible.
Se investigan las paradas de VU1 en EEXP; ver el control integrado en `ESTADO.md`.

`ps2recomp-vu1-efu-opcodes.patch` corrige esa selección de instrucciones y sus
latencias en la decodificación cacheada y en la ejecución. ERSQRT/ESIN/EATAN/EEXP se
contrastan con la tabla LowerOP de PCSX2 en `32ac6e2`, conservando las fórmulas EFU.
Las pruebas usan palabras binarias explícitas y comprueban también WAITP y el
rechazo de instrucciones reservadas. La validación con el juego se registra aparte
para distinguirla de la integración MMI anterior.

La compilación completa posterior pasa **548/548** con OpenGL. En el control de
cinco minutos desaparecen las instrucciones VU1 reservadas y se capturan imágenes
distintas hasta 240 s del reloj PAD. La escena conserva deformaciones graves y
Kratos no es reconocible; esta corrección no completa el renderizado 3D.

Un segundo control de cinco minutos con CPU también muestra deformaciones graves,
sin errores de instrucciones VU1 reservadas. No se puede atribuir todo el fallo a
OpenGL ni comparar pixels entre estas ejecuciones independientes. Se prepara una
repetición con comandos y estado inicial idénticos para acotar la divergencia.

## Repetición local de comandos GS

`ps2recomp-gs-cpu-state.patch` adapta la exportación/importación CPU del fork SotC
`ac9efa070638ad3b3accd284de6f898d5ab271d1`, con crédito a Taylor N. Albarnaz /
LightVelox (GPL-3.0). Conserva la paleta y sus CBP, la página de textura cacheada,
la transferencia, los bytes CT24 pendientes y el buffer/cursor de readback. Los
snapshots inválidos se rechazan antes de modificar el estado del destino.

El diagnóstico opcional `GOW_GS_REPLAY_TRACE` instala un wrapper en los overrides,
conservando la selección CPU/hilo/OpenGL. Comienza después de 150 s del reloj del
host y solo en estado 11; captura tres segundos con límite de 64 MiB. Los plazos
se pueden elegir con `GOW_GS_REPLAY_AFTER` (0..3600 s) y `GOW_GS_REPLAY_SECONDS`
(0,1..60 s), usando punto decimal. El reloj comienza al instalar el backend;
es distinto del reloj de las pulsaciones PAD. Guarda el
estado inicial y final y los comandos, incluidos presentación y modo MXCSR.
Serializa las llamadas al backend durante esta prueba: no se usa para medir FPS.
Sin la variable no instala el wrapper. El perfil elimina todas estas opciones.

`GOW_GS_REPLAY_TEXFLUSH=1` espera además al primer TEXFLUSH que envíe el juego
después del plazo, en estado 11. El estado inicial se guarda **después** de ese
comando y de sincronizar la cola; el TEXFLUSH inicial queda representado por ese
estado. No añade un TEXFLUSH ni invalida antes la caché del renderer. La opción
vale `0` por defecto y permite capturar una entrada con la página CPU invalidada
para importar el mismo estado en GPU. Si el juego no envía esa frontera, la
captura no comienza. Las opciones inválidas desactivan el diagnóstico con un
mensaje, antes de abrir o reemplazar el archivo de salida.

```powershell
# Primero compilar el port con todos los parches y después la herramienta.
.\scripts\compilar_replay_gs.cmd
$env:GOW_GS_REPLAY_TRACE = "$PWD\logs\tramo_gs.bin"
$env:GOW_GS_REPLAY_AFTER = '470'
$env:GOW_GS_REPLAY_SECONDS = '3'
$env:GOW_GS_REPLAY_TEXFLUSH = '1'
# Ejecutar el control del juego con CPU; mantenerlo abierto después del plazo
# hasta que el registro confirme inicio en estado 11 y fin completo=1.
# Al terminar, quitar la variable antes de otros controles.
Remove-Item Env:GOW_GS_REPLAY_TRACE, Env:GOW_GS_REPLAY_AFTER, Env:GOW_GS_REPLAY_SECONDS, Env:GOW_GS_REPLAY_TEXFLUSH
.\logs\repetir_gs.exe .\logs\tramo_gs.bin cpu --lockstep logs
.\logs\repetir_gs.exe .\logs\tramo_gs.bin compute --lockstep logs
.\logs\repetir_gs.exe .\logs\tramo_gs.bin hardware --lockstep logs
```

La herramienta verifica primero que el CPU reproduzca la VRAM final original.
Comprueba también la paleta, la transferencia y el readback finales. El importador
GPU actual no restaura la página CPU: si sus bytes iniciales difieren de la VRAM,
rechaza esa comparación y requiere capturar desde una frontera TEXFLUSH.
Compara después la VRAM y las presentaciones de ambos backends. `--lockstep`
localiza el primer comando que cambia la VRAM de forma distinta; los códigos de
salida son 0 (coincidencia), 1 (divergencia), 2 (archivo/contexto inválido) y 3
(la repetición no reproduce la captura o una lectura esperada). El informe del
primer dibujo incluye TBP/TBW, dimensiones/filtro, TEX0/TEX1/TEXA, CLAMP,
FBP/FBW/PSM, máscara, profundidad y scissor, para identificar lecturas y escrituras
en la misma región de VRAM. Comprueba que
OpenGL esté activo; un fallback CPU no certifica paridad GPU. Las variantes de
hardware pueden usar compute mientras compilan: los contadores se muestran para
comprobar qué trabajo ejecutaron. El formato binario es local y requiere el
mismo ABI y versión de estructuras; no es un formato portátil.

Los binarios, VRAM, comandos y capturas resultantes permanecen en `logs/`, ignorado
por Git. Nunca adjuntarlos a commits ni subirlos a GitHub. La prueba sintética del
script no contiene datos del juego y comprueba el parser y el rechazo de archivos
truncados antes de repetir los comandos en CPU.

La primera captura real verificada (estado 11, 47.207 primitivas y dos presentaciones)
reproduce el estado y la VRAM final CPU exactamente. Compute y el recorrido mixto
con hardware habilitado divergen en el mismo dibujo 561 (registro 577), inicialmente
en tres bytes; se trata de un triángulo STQ con textura PSMT8. El final difiere en
166.763 y 164.227 bytes respectivamente, y en ambas presentaciones. Se confirma
OpenGL real en la RX 5700 XT; el recorrido mixto usa 7.749 tiles compute frente a
11.937 del recorrido compute. Estos resultados delimitan una diferencia GS, pero
las deformaciones grandes también aparecen en CPU y todavía requieren investigar
los datos anteriores al backend. Esta captura opcional serializada no mide FPS.

El renderer CPU se estabiliza con `ps2recomp-gs-cpu-rounding.patch`: cada `Submit`
usa redondeo SSE al más cercano y restaura el modo del llamador, incluidas las
llamadas en la cola GS. Mantiene FTZ/DAZ, máscaras y flags; los modos EE/VU continúan
con su semántica anterior. Dos regresiones fallan sin este aislamiento y comparan
VRAM completa para gradiente, UV y STQ bajo los cuatro modos MXCSR. No sustituye
una implementación precisa de la interpolación del GS.

Las capturas anteriores pertenecen a la versión CPU que las produjo: después de
cambiar su rasterizado hay que capturar de nuevo. La verificación de VRAM final
de la herramienta rechaza certificarlas con una versión que ya no las reproduce.

Con el arreglo de libm `3f349b2` y los 36 parches se captura una entrada nueva:
53.016 dibujos, tres presentaciones y estado GS final exacto al repetir en CPU.
OpenGL compute y mixto divergen ya en el sprite 510 (917 bytes); sus finales
difieren en 387.242 y 386.914 bytes. Este control conjunta el arreglo de cámara y
el aislamiento SSE. Las imágenes CPU muestran el barco y los acantilados
reconocibles, aunque una imagen posterior conserva deformaciones y todavía no
certifica a Kratos. Se usa como nueva referencia para las siguientes correcciones
GS; la captura opcional no sirve para medir rendimiento.

Dos parches posteriores delimitan fallos GS independientes: `gs-triangle-precision`
conserva recíproco y numeradores en double antes del peso float, igualando la
referencia CPU en la regresión de Z32/Z24 para triángulos grandes; `gs-packed-depth`
evita perder bits de Z32 en PACKED XYZ2/XYZ3 antes de llegar al backend. Se prueban
por separado antes y después del arreglo y mantienen el renderer CPU para comparar.
El trabajo FP64 adicional requiere un perfil posterior para valorar su coste.

`repetir_gs` compara y exporta únicamente la región visible de `PresentationFrame`:
CPU reserva filas de 640×512 y GPU usa 640×alto visible. El helper
`tools/render/gs_frame_pixels.h` requiere indicar el layout y evita interpretar
el relleno como diferencias de imagen. `scripts\compilar_replay_gs.cmd` ejecuta
también `tests/gs_frame_pixels_test.cpp`, con layouts, padding, truncamiento,
exportación PPM y una presentación real de CPU. Una diferencia de VRAM sigue
siendo independiente de este ajuste de diagnóstico.

Para comprobar si un mismo backend repite el resultado, usar varias pasadas:

```powershell
.\logs\repetir_gs.exe .\logs\tramo_gs.bin hardware --repeticiones 8 logs\estabilidad_gs
```

Las instancias CPU/GPU y sus vectores VRAM se mantienen. Antes de cada pasada se
espera FINISH, se copian los bytes iniciales y se reimporta y verifica todo el estado:
CLUT, transferencias, carry CT24, lectura local y caché CPU. La caché CPU ausente en
GPU se identifica explícitamente y sigue rechazándose una página inicial obsoleta.
CPU debe reproducir exactamente el End de la captura en todas las pasadas.

La paridad CPU/candidato y la estabilidad entre candidatos consecutivos se informan
por separado. Se comparan VRAM, estado y todos los cuadros visibles, con bytes y
primer índice distinto por cuadro. Los contadores se muestran como deltas de cada
pasada: «hardware solicitado» no garantiza que las variantes estén listas; observar
primitivas y cero tiles compute permite reconocer pasadas sin ese fallback. Totales
iguales no certifican que toda la ruta sea idéntica. El historial exacto se limita
a 64 MiB visibles por pasada; si se supera, devuelve 2 y requiere un tramo menor.

Para localizar variación intermedia entre pasadas, añadir `--checkpoints-sync`:

```powershell
.\logs\repetir_gs.exe .\logs\tramo_gs.bin compute --snapshot-feedback --repeticiones 3 --checkpoints-sync logs\controles_gs
```

Registra huellas FNV-1a64 de toda la VRAM en las fronteras Flush, Sync, Present y
End. Informa el primer registro/op/dibujos que cambia, y también rechaza paridad
si la diferencia intermedia desaparece antes del End. No guarda otra copia de
4 MiB por control: el historial admite 4096 huellas y se comprueba el límite
antes de crear el backend. Conserva las comparaciones exactas finales y de las
imágenes. Una huella igual no certifica identidad byte a byte intermedia.
Los comandos elegidos ya drenan lotes; TEXFLUSH queda fuera porque en la GPU
actual no lo hace. Los readbacks añaden espera y la prueba no mide FPS.

Para repetir solo un prefijo, `--hasta-registro R` admite una frontera natural
Flush, Sync, Present o End. `Initial` es el registro 0; los siguientes empiezan
en 1. Por ejemplo, si el primer control variable está en el Flush 36:

```powershell
.\logs\repetir_gs.exe .\logs\tramo_gs.bin compute --hasta-registro 36 --repeticiones 64 --checkpoints-sync logs\prefijo_gs
```

La herramienta valida el índice y su operación antes de crear el backend.
Rechaza Submit y TEXFLUSH para evitar nuevos cortes entre dibujos. Al llegar
al registro seleccionado, compara exactamente los 4 MiB y el estado portable
de CPU/candidato, además de las presentaciones ya ejecutadas. Un prefijo
anterior al End imprime que **no valida el End original ni el resto de la
captura**. Seleccionar el End conserva el oráculo de la captura completa.
El límite de controles sincronizados se comprueba solo para ese prefijo.
Un resultado distinto mantiene salida 1; errores de argumentos/captura,
salida 2; una referencia CPU que no reproduce el End, salida 3.
`tests/gs_replay_cli_test.py` comprueba fronteras, límites, opciones inválidas
y que un End alterado se detecta al repetir el tramo completo.

En el tramo tardío de 146.015 registros, CPU ×3 mantiene iguales los trece
controles, el End, el estado y ambas imágenes. Compute ×3 con snapshot cambia
por primera vez en el Flush del registro 73.288, después de 73.003 dibujos:
ocho de los trece controles varían entre pasadas, con iguales contadores de
raster y las dos imágenes visibles estables. Esta frontera localiza variación
de VRAM anterior al End; sigue pendiente reducir el lote responsable. El
sprite inicial aislado también queda estable en hardware efectivo, con un
dibujo y cero tiles compute en las pasadas calientes, aunque conserva los
1874 bytes distintos de CPU. Son dos diferencias que requieren pruebas propias.

La reducción posterior acota una dependencia color/Z: el prefijo hasta el registro
68.897 permanece estable en cinco pasadas; añadir el sprite siguiente cambia
64–128 bytes entre algunas pasadas. Ambos sprites usan FBP=ZBP=320, FBW=1 y
PSMCT24/PSMZ24, con prueba/escritura Z. Sus rectángulos XY son disjuntos, pero
sus direcciones físicas de color y profundidad se cruzan por el swizzle.
Separarlos elimina esa variación en ocho pasadas del prefijo. La búsqueda por
prefijos no prueba que la variación sea monótona ni que sea el primer fallo global.

`ps2recomp-gs-target-alias.patch` conserva bitsets distintos para las páginas de
color y los accesos de profundidad del lote. Si la siguiente primitiva cruza
color con Z del lote anterior, lo completa antes de añadirla, también cuando Z
solo se lee. Los buffers disjuntos y Z sin lectura/escritura mantienen su lote.
No sustituye el orden interno de un dibujo ni resuelve alias entre píxeles de
una sola primitiva; tampoco implementa la caché GS de 8 KiB. La detección por
página es conservadora y puede añadir sincronizaciones.

El control procedural CT24/Z24 difiere en 6144 bytes con el backend anterior;
el backend integrado separa los dos dibujos y coincide en los 4 MiB con CPU.
La compilación oficial completa y las 582 pruebas nativas pasan, incluidas
veinte pruebas OpenGL con regresiones de alias en compute y hardware efectivo.
El tramo real completo, en compute con cuatro pasadas con snapshot y cuatro
sin él, conserva
los trece controles, toda la VRAM final, el estado y ambas imágenes exactamente
entre pasadas. Sigue difiriendo de CPU en 739.502 bytes y dos presentaciones.
Los lotes pasan de 632 a 648, con las mismas 99.402 primitivas/53.757 tiles: esta
corrección protege el orden y no acredita una mejora de FPS.

El directorio puede ir con o sin `--lockstep`, antes o después de las opciones.
Se crea si falta; un fallo al crear/exportar y las opciones inválidas devuelven 2.
Las imágenes de varias pasadas llevan `replay_pasada_N_` para conservarlas. Si se
omite el directorio, `replay_*.ppm` queda excluido de Git. Las capturas y salidas
del juego siguen siendo exclusivamente locales.

El control FULL45 del primer cuadro histórico reproduce CPU/estado exactamente
en tres pasadas y exporta seis PPM visibles válidas. En ocho pasadas OpenGL, las
dos últimas usan 34 lotes, 734 primitivas y cero tiles compute, pero difieren en
545 bytes de VRAM y 358 visibles, con estado final igual. La herramienta devuelve
1 y muestra ambos resultados; no oculta la diferencia ni la interpreta como FPS.

Los cortes previos localizan esa variación: hasta el registro 519 todo coincide;
el primer sprite de feedback (520) es repetible aunque conserve los 917 bytes de
diferencia CPU/GPU. Añadir el segundo (521) ya produce 36 bytes variables entre
pasadas hardware con restauraciones y estado final exactos. Los 16 sprites leen
y escriben CT32 sobre el mismo framebuffer y su resultado pasa después al cuadro
visible. La instrumentación del ring original observa cero reutilizaciones en
la captura: su reciclado no explica esta variación.

La [especificación de interlock de Khronos](https://registry.khronos.org/OpenGL/extensions/ARB/ARB_fragment_shader_interlock.txt)
garantiza orden y visibilidad de buffers `coherent` dentro de la sección crítica
para fragmentos del mismo píxel; no ordena píxeles distintos ni lecturas anteriores
a esa sección. El shader actual muestrea antes de entrar al interlock. Esto acota
la investigación de feedback, pero no certifica una política de caché GS ni justifica
añadir una barrera o cambiar el filtrado sin un control de referencia.

Para investigar feedback bilineal sin volcados del juego, el mismo script compila
`logs\comparar_feedback_gs.exe`. Ejecutarlo compara un sprite sobre una textura
procedural CT32 de 64×64 con la fuente en el propio framebuffer y con una copia
disjunta, en CPU y OpenGL compute. Imprime diferencias por fila, bytes de VRAM y
repeticiones GPU; requiere una GPU real. El código de salida 0 indica que terminó
la comparación, aunque haya diferencias; 2 indica un control inválido o GPU no
disponible. No certifica cuál salida tiene la semántica del GS.

El mismo helper compila `generar_feedback_gs.exe` y comprueba en CPU tres capturas
procedurales de dos sprites sobre una textura CT32 de 64×416. `self` lee y escribe
el mismo framebuffer con bilinear; `disjoint` conserva el filtro y copia la fuente
a otra región; `nearest` conserva el feedback y cambia solamente el filtro. La
copia comprueba sus 27.588 vecinos tras CLAMP. No requiere archivos del juego:

```powershell
scripts\compilar_replay_gs.cmd
.\logs\repetir_gs.exe logs\feedback_sintetico\feedback_gs_self.bin hardware --repeticiones 12 logs\feedback_sintetico\hw_self
.\logs\repetir_gs.exe logs\feedback_sintetico\feedback_gs_disjoint.bin hardware --repeticiones 12 logs\feedback_sintetico\hw_disjoint
.\logs\repetir_gs.exe logs\feedback_sintetico\feedback_gs_nearest.bin hardware --repeticiones 12 logs\feedback_sintetico\hw_nearest
```

El generador se puede ejecutar aparte con `generar_feedback_gs.exe [directorio] [--pcsx2]`;
las capturas usan la ABI del runtime con que se compiló. En RX 5700 XT, CPU ×3
reproduce los tres End y cuadros exactamente. Hardware ×12 conserva paridad y
estabilidad para `disjoint` y `nearest` (salida 0). `self` devuelve 1: difiere de
CPU y varía también entre pasadas con dos lotes, dos primitivas y cero tiles
compute. Por ejemplo, las pasadas 4→5 difieren en 19 bytes de VRAM y 19 visibles;
7→8, en 34 de cada uno. Restauración y estado portable final permanecen exactos.
La pasada inicial mezcla compute mientras se compila la variante y se informa
por separado. Las cantidades variables no son valores esperados fijos: el caso
reproduce la inestabilidad, sin certificar todavía la política correcta de caché GS.

El [suplemento del manual GS, §§1.2 y 1.4](https://www.scribd.com/document/718537990/GS-Users-Manual-Supplement)
describe un búfer de textura de una página y grupos de 4×2 píxeles para dibujo
texturado; el filtro bilineal puede recargar páginas por sus vecinos. Esto respalda
investigar caché y orden de acceso, pero no fija el resultado del patrón sintético
de feedback. El bucle CPU actual escribe un píxel tras cada muestra y todavía no
modela esos grupos ni su pipeline. La [nota de PCSX2 sobre caché GS](https://github.com/PCSX2/pcsx2/discussions/4311)
también distingue la caché de textura de la de framebuffer. Se necesita un control
de ese patrón para decidir el siguiente cambio.

## Precisión bilineal y referencia independiente

`ps2recomp-gs-bilinear-precision.patch` corrige la interpolación de los canales
RGBA en CPU y OpenGL. El filtro anterior interpolaba en coma flotante y redondeaba
al final. Ahora usa una fracción de cuatro bits y trunca cada etapa horizontal y
la vertical, como el renderer software de
[PCSX2 v2.8.2](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/Renderers/SW/GSDrawScanline.cpp),
con su operación
[`lerp16_4`](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/GSVector8i.h).
No incorpora código de esas funciones: usa pesos enteros positivos para obtener
el mismo truncado sin depender del desplazamiento de enteros negativos.

La referencia se ejecutó con PCSX2 software, sin BIOS ni archivos del juego, sobre
cuatro texels procedurales RGBA y las 256 combinaciones de fracciones UV. Se
verificaron también los texels de entrada. La imagen RGBA de 1024 bytes tiene
SHA256 `9de1ca132c07706433d8e86fedde114379437d2f869884342e2ec0c2353004d6`
y FNV-1a64 `fdde85267aad850d`. El filtro anterior difiere en 780 bytes; el nuevo
coincide en todos. Las regresiones comprueban esa huella externa en CPU directo,
CPU con hilo y OpenGL compute/hardware, con FST y STQ y los cuatro modos de
redondeo SSE, conservando los controles del productor. Fallan las tres antes del
arreglo; después pasan las 568 pruebas, incluidas diez OpenGL con GPU real.
El control literal de textura de una prueba anterior cambia de R/G=44/73 a
43/72 por el truncado; nearest conserva 58/87.

`generar_feedback_gs --pcsx2` exporta también los tres patrones como `.gs`. El
helper los genera en `logs\feedback_sintetico` y ejecuta
`gs_feedback_dump_test`: comprueba el freeze inicial y envía los paquetes A+D
al frontend GIF PATH3, comparando los cuatro MiB de VRAM con el End de la captura
CPU. La serialización propia usa el formato legacy y freeze v8 de
[GSState.cpp](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/GSState.cpp) y
[GSDump.cpp](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/GSDump.cpp).
Es una exportación de estos patrones concretos, no un conversor de trazas del
juego ni de estados GS arbitrarios. Los binarios generados quedan en `logs/`.

La comparación independiente separa la precisión del feedback: nearest ya
coincidía; con el filtro corregido, la fuente disjunta también coincide con PCSX2
software. El feedback bilineal conserva diferencias y requiere decidir la
política de caché y el orden de acceso. PCSX2 software sirve aquí como referencia
ejecutada; no sustituye una captura de una PS2 para certificar ese feedback.
Este cambio no demuestra una mejora de FPS.

## Coordenadas negativas con nearest

`ps2recomp-gs-nearest-stq.patch` corrige la elección del texel en CPU y OpenGL
para coordenadas STQ negativas. El cast directo a entero elegía 0 para una
coordenada como −0,25 en vez del texel −1 que luego envuelve REPEAT. La referencia
software de [PCSX2 v2.8.2](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/Renderers/SW/GSDrawScanline.cpp)
primero convierte a 16.16 y después extrae la parte entera con signo. Se reproduce
esa conversión con truncado y `floor`, sin desplazamientos de enteros negativos.
Aplicar solamente `floor` tampoco basta: con textura 4×4 y REPEAT, −1/65536 elige
el texel 3, mientras −1/131072 pierde su fracción en la conversión y elige el 0.

Dos controles de 16×16, sin feedback, comparan coordenadas negativas en cuartos
de texel y valores próximos al límite 16.16. El original difiere de PCSX2 software
en 624 bytes RGBA/156 píxeles en cada control. Las huellas externas son:

| Control | SHA256 de los 1024 bytes RGBA |
|---|---|
| Negativos | `9d1cc63a5a081dbe2e59c8117fadcd6bd8ae49c87b9a08dc60dcb326239d8c81` |
| Límites | `119eae34f160a97fa9991d028d8a7f514d739f77d1e73f429bd7d854dad22bdc` |

Tres nuevas regresiones fallan antes del ajuste y después pasan las 571 pruebas.
Comprueban ambas huellas en CPU directo, CPU con hilo y OpenGL, para sprites y
triángulos, Q=1/2 y los cuatro modos SSE. El control OpenGL exige además contadores
de las rutas compute y hardware; no basta con tener un contexto creado.

El helper compila también `generar_oraculos_gs.exe [directorio=logs/oraculos_gs]`.
Exporta cuatro patrones de referencia —bilinear, negativos, límites y bilinear STQ— en
capturas de repetición `.bin`, dumps de PCSX2 `.gs` y matrices `.rgba` de 16×16.
Los texels y comandos son procedurales. `gs_feedback_dump_test logs\oraculos_gs --oraculos`
comprueba freeze/GIF/End y el helper repite los cuatro controles CPU ×3. Esto permite
regenerar las entradas de la referencia sin la ISO ni volcados del juego. La
comparación RGBA externa sigue siendo independiente del renderer del port.

Los tres primeros `.gs` generados son idénticos por SHA256 a los ejecutados en la referencia
aislada, y sus matrices CPU tienen las huellas RGBA externas documentadas.
Freeze/GIF/End y CPU ×3 son exactos en los seis patrones del helper; los controles
anteriores de feedback conservan sus bytes de dump. En RX 5700 XT, los tres
oráculos hardware ×8 tienen paridad, estabilidad y estado final exactos; las
pasadas calientes usan 256 primitivas y cero tiles compute. Estos controles no
cambian el resultado pendiente del feedback bilineal sobre el propio destino.

## Conversión STQ bilineal antes del medio texel

`ps2recomp-gs-bilinear-stq.patch` extiende la conversión 16.16 ya usada por nearest
al filtro bilineal, tanto en CPU como en GLSL. Primero trunca la coordenada escalada
y después resta medio texel y extrae los pesos de cuatro bits. Con
u=−1/16−1/131072, convertir antes del desplazamiento elige el peso 7; usar
directamente el float anterior elegía 6. Los datos FST 12.4 ya son representables
exactamente y los resultados nearest mantienen la misma conversión.

La referencia ejecutada de PCSX2 v2.8.2 software usa 16×16 muestras STQ constantes,
una textura RGBA procedural 4×4 disjunta y REPEAT. Se comprueban los 16 texels
RGB/alpha de entrada y que el dump GIF reproduce el End CPU previo byte por byte.
El renderer anterior difiere en **611 bytes RGBA/156 píxeles**. La huella externa
de los 1024 bytes es SHA256
`3566bc0c748d3948c2180c311562175df43c745a28bc8d7ad165d165b57d4e28`,
FNV-1a64 `c6e49fa0342e621f`. La secuencia de conversión y desplazamiento está en
[GSDrawScanline.cpp de PCSX2](https://github.com/PCSX2/pcsx2/blob/v2.8.2/pcsx2/GS/Renderers/SW/GSDrawScanline.cpp).
Es una comparación con esa implementación software; no una captura del GS físico.

Las tres nuevas regresiones fallan antes (**573/576**) y pasan tras el ajuste
(**576/576**, catorce controles OpenGL reales). Comparan la huella externa en
CPU directo, CPU con hilo, compute y hardware, para sprites/triángulos, Q=1/2
y los cuatro modos SSE. Los contadores exigen 256 primitivas por matriz y,
en hardware, al menos una matriz sin tiles compute. El generador público añade
`feedback_gs_oraculo_bilinear_stq` en `.bin`, `.gs` y `.rgba`.

La compilación completa regenera las 6418 unidades y termina con código 0;
49 parches/84 fuentes coinciden y la suite posterior pasa 576/576. Las siete
herramientas pasan los 18 controles de imagen y los trece freeze/GIF/End con
CPU ×3. Los cuatro `.gs` coinciden por SHA256 con las entradas ejecutadas en
PCSX2 y las cuatro matrices `.rgba` coinciden byte por byte con la referencia.
Los seis controles de dumps dañados siguen rechazándose.

El nuevo patrón queda exacto y estable en compute ×8 y hardware ×8, incluida
la VRAM completa, el estado portable y el cuadro visible. Ocho pasadas rápidas
seleccionando hardware terminaron todavía en compute: la compilación asíncrona
de su shader no había terminado. `--pausa-ms 1000` permite esperar entre pasadas
del mismo backend; siete de las ocho repeticiones entonces rasterizan sus
256 primitivas con cero tiles compute y coinciden con el RGB externo. La opción
requiere varias pasadas y una espera de 1..1000 ms; nueve usos inválidos devuelven
2. CPU ×2 con espera queda exacto y feedback opcional con espera mantiene salida
1 por su diferencia conocida con CPU. Estas esperas son un control de la ruta,
no una medida de FPS ni una política del juego.

El control posterior del ejecutable completo dura 510 s en OpenGL, con FMV
omitido y feedback snapshot desactivado. Carga una copia privada de la tarjeta,
sin modificar el original. Las dieciséis capturas 512×448 son distintas; la
última muestra a Kratos durante un ataque, el HUD, estelas de armas, R2 y el
punto de guardado, con estado 11 sin carga pendiente. Las 128 muestras de Clip
son finitas y completas, las 768 primeras tripletas tardías son no nulas y
los 192 contextos de partida no tienen punteros inválidos, ciclos ni truncamientos.
No se registra VU reservada. El mando recibe las tres pulsaciones de cuadrado
previstas; esto verifica la imagen de una animación de ataque, sin certificar
combate contra enemigos ni FPS sostenidos.

## Páginas regionales de textura y lotes OpenGL

`ps2recomp-gs-region-pages.patch` reduce el conjunto conservador de páginas que
puede leer una textura regional. Antes, REGION_CLAMP y REGION_REPEAT declaraban
todo el rango 0..1023 de cada eje: un framebuffer ajeno a los texels accesibles
podía provocar una separación de lotes por feedback inexistente.

REGION_CLAMP válido usa MIN..MAX; REGION_REPEAT, cuyo resultado es
`(coordenada & MIN) | MAX`, queda dentro de MAX..(MIN | MAX). Los huecos de
REGION_REPEAT siguen cubiertos por el rectángulo conservador. MIN>MAX mantiene
el rango completo anterior. REPEAT y CLAMP ordinarios conservan su cobertura.
La clave de la caché del conjunto de páginas incluye ambos extremos de cada
eje, para renovarse también si solo cambia MIN. Esta caché guarda un bitset de
riesgos de acceso; no reproduce los datos de una caché de textura PS2.

El control usa tres fuentes coloreadas fuera del framebuffer y una cuarta
opcional que lee una página ya escrita. En los 13 PSM, nearest/bilinear y caché
del bitset activada/desactivada, los tres dibujos disjuntos pasan de tres lotes
y dos flushes de textura a **un lote y cero flushes**. La cuarta lectura real
conserva la separación necesaria: **dos lotes y un flush**. El control de
REGION_CLAMP mantiene MAX=700 y cambia solo MIN para comprobar esa clave.
Los formatos indexados cargan una paleta CSM2 de colores distintos, evitando
que una imagen vacía esconda fallos.

Otros controles atraviesan bordes de página, usan máscaras REGION_REPEAT no
nulas y bases TBP 0, 31 y 16383, incluida la vuelta de los 4 MiB. Se ejecutan
con feedback snapshot activado y desactivado. Tres sprites de un píxel en una
página realmente leída conservan tres lotes y dos flushes; TEXFLUSH renueva
la fuente del control CPU entre Submits. Todas las comparaciones incluyen los
4 MiB completos, no solo los píxeles visibles.

Son 208 casos de lotes y 384 de bordes por ruta, 1184 combinaciones en compute
y hardware. Se exige el número de primitivas y hardware efectivo sin tiles
compute; crear el contexto o caer al renderer CPU no satisface el control.
Las dos regresiones de lotes fallan con el backend anterior. Un primer intento
coincidió con la compilación de Claude y agotó además dos plazos de shaders;
al repetir los controles aislados con el equipo libre fallan solo los lotes
innecesarios, mientras bordes hardware y feedback externo pasan.

La compilación completa regenera las 6418 unidades y termina con código 0.
La auditoría posterior confirma 50 parches y 84 fuentes idénticas; la suite
final pasa 580/580, con dieciocho controles OpenGL reales. Las siete herramientas
pasan los 18 controles de imagen y los trece patrones freeze/GIF/End con CPU ×3;
se rechazan las seis copias dañadas.

El control posterior dura 510 s en OpenGL, con FMV omitido y snapshot
experimental desactivado. Carga una copia privada de la tarjeta, cuyo original
conserva su SHA256. Las dieciséis capturas 512×448 son distintas; la última
muestra a Kratos atacando con HUD, estelas de armas, R2 y el punto de guardado,
en estado 11 sin carga pendiente y con hardware activo. Se conservan 128
muestras de Clip finitas/completas, 736 tripletas tardías no nulas y 192 contextos
sin punteros inválidos, ciclos ni truncamientos. No aparece VU reservada.
Esto verifica la imagen de un ataque; combate contra enemigos y FPS sostenidos
siguen pendientes.

La mejora demuestra menos envíos en estos patrones; no establece una ganancia
de FPS en el juego ni resuelve la caché del GS físico. El renderer CPU y la
política experimental de feedback se mantienen disponibles para comparar.


## Separación de lotes y fuente protegida opcional

`generar_feedback_gs --pcsx2 --separaciones` conserva los tres patrones anteriores
y añade seis controles. El sufijo `_texflush` inserta TEXFLUSH entre los sprites;
`_scissor` cambia SCISSOR1 de x1=511 a 510 antes del segundo. Ambos sprites siguen
dibujando x=0..63/y=0..415, de modo que ese cambio de estado no recorta la imagen.
`gs_feedback_dump_test [directorio] --separaciones` valida los nueve freeze/GIF/End,
incluidos los registros de separación. También comprueba los bytes completos de
los contextos, las colas GIF vacías, Q=1 y los tres bloques privilegiados; conservar
VRAM no basta si PMODE o DISPLAY fueron dañados. El helper ejecuta CPU ×3 para
cada captura; los archivos generados siguen dentro de `logs/`.

La referencia ejecutada con PCSX2 v2.8.2 software muestra un lote con los dos
sprites para `self` y `self_texflush`, y dos para `self_scissor`. En el primer
caso la imagen coincide con la fuente disjunta; TEXFLUSH conserva ese resultado
en este patrón. El cambio SCISSOR renueva la fuente entre dibujos y cambia
1238 bytes RGB de los 79872 observados. Se comprueba la fuente original del
primer dibujo y, para el segundo, la mitad izquierda ya dibujada más la derecha
original, sin diferencias en los texels muestreados. El RGB final del control
separado tiene SHA256 `75fb49353fd21ec38c8d4b413f657b57d5fc168bb24c9eba8279edc747079197`
y FNV-1a64 `f1dd4b246679e740`. Es evidencia de la agrupación de esta referencia;
no establece una política universal de TEXFLUSH ni reproduce una caché PS2.

`ps2recomp-gs-feedback-snapshot.patch` añade una política **opcional y desactivada
por defecto** para aislar la lectura/escritura simultánea. Antes de una primitiva
que lee páginas que también escribe, completa el lote anterior y copia solamente
esas páginas a la memoria sombra ya usada por las transferencias. Su estado
conserva el epoch anterior a la copia: el sampler lee la fuente protegida y el
raster escribe la VRAM normal. Se aplica a puntos, sprites y triángulos; las
líneas conservan su subdivisión en puntos y protegen la fuente por punto, no
por segmento completo. Los dibujos sin solapamiento siguen la ruta anterior. El interlock del shader
ordena escrituras de un mismo píxel, pero no sus vecinos de textura, por lo que
una barrera entre sprites no resolvía el acceso simultáneo dentro de cada sprite.

En el ejecutable se activa antes del arranque con `PS2X_GS_FEEDBACK_SNAPSHOT=1`.
La herramienta de repetición requiere su opción explícita:

```powershell
.\logs\repetir_gs.exe logs\feedback_sintetico\feedback_gs_self_scissor.bin hardware --snapshot-feedback --repeticiones 12 logs\feedback_sintetico\snapshot_scissor
```

El código de salida sigue comprobando paridad con el renderer CPU, que conserva
una sola página de textura de 8 KiB. Una fuente congelada por primitiva puede
ser estable y coincidir con la referencia separada, y aun así devolver 1 por
diferir de CPU. No convierte esa diferencia en éxito ni cambia el renderer CPU.
La política no congela una fuente común para todos los sprites de un lote y
queda pendiente contrastarla con la caché y el pipeline del GS real antes de
activarla por defecto. Tampoco demuestra una mejora de FPS.

La regresión nativa hardware falla antes del arreglo por RGB y por variación
entre pasadas; la de compute ya pasaba ese patrón. Después pasan ambas contra
la huella externa, con ocho restauraciones por patrón, controles nearest/fuente
disjunta y puntos/triángulos contra una copia CPU disjunta. Se exige al menos una
pasada hardware sin tiles compute; un fallback CPU no cuenta como validación.

Tras la compilación completa, 48 parches y 84 fuentes coinciden exactamente y
la suite vuelve a pasar 573/573, con trece controles OpenGL reales. Las siete
herramientas compilan y pasan los 18 controles de imagen, doce freeze/GIF/End
y CPU ×3. Se rechazan seis copias dañadas: PMODE deshabilitado en sus tres bloques,
TEX0 inicial, una cola GIF pendiente, Q alterado, un byte privilegiado reservado
y EOP ausente. Los tres `.gs` anteriores conservan sus SHA256.

Compute y hardware con snapshot repiten doce veces `self_scissor`, `disjoint`
y `nearest`: 72 pasadas conservan la VRAM completa, el estado portable y el
cuadro visible entre restauraciones; sus regiones RGB 64×416 coinciden con las
tres referencias ejecutadas. Las pasadas hardware calientes tienen dos
primitivas y cero tiles compute. `self_scissor` mantiene salida 1 y 4557 bytes
distintos de CPU, incluso al coincidir con la referencia separada; los otros dos
casos conservan salida 0. Opciones duplicadas y snapshot en modo CPU devuelven 2.

Con el ejecutable completo y la opción activada, un control OpenGL de 390 s
carga una copia privada de la tarjeta guardada. Las quince imágenes 512×448
son distintas; la última muestra a Kratos, el punto de guardado y R2, con
hardware activo y estado 11 sin carga pendiente. Se conservan 128 muestras
de Clip finitas/completas, 416 tripletas tardías no nulas y 192 contextos de
partida sin punteros inválidos, ciclos ni truncamientos; no se registra VU
reservada ni cambia la tarjeta original. La captura final no muestra la barra
de vida y no se ha probado combate ni rendimiento sostenido con esta opción.
El guion previo de 330 s eligió una partida nueva y se repitió retrasando
las pulsaciones; aquella intro no cuenta como carga de una partida guardada.

## Referencia Tobiichi-Port

Se revisa [YYOzcan/Tobiichi-Port](https://github.com/YYOzcan/Tobiichi-Port/tree/9f02797f8ab7481fddad4d2daf7afad82d11699f)
en `9f02797f8ab7481fddad4d2daf7afad82d11699f`. Los cinco archivos comparados
(`gs_cpu_backend.cpp`, `ps2_vif1_interpreter.cpp` y núcleo/instrucciones superiores e
inferiores de VU1) son idénticos a los del PS2Recomp fijado en `c5a9d025`.
Su README declara el menú y la partida pendientes; esto describe lo publicado,
no una prueba ejecutada aquí. Los hooks GoW incluyen objetos/tabla virtual de relleno
y atajos de arranque. No se incorporan como arreglo del renderizado ni se ha probado
su ejecutable. Puede servir para contrastar hipótesis de arranque, pero los archivos
revisados no aportan todavía una solución distinta para GS/VIF/VU1.

## Selección del contexto de modelos

`GOW_MODEL_DIAG=1` registra `[gow-model:server]` a la entrada de
`renModelServer::ProcessServer` (`0x159C58`), con un máximo de 64 muestras previas al estado
11 y otras 64 dentro de él. Observa la tabla, grupo y slot seleccionados, el contexto,
su tabla virtual y el destino/ajuste de la llamada, comprobando los límites de RAM.
Los índices se calculan en 64 bits para evitar envolvimientos.

La misma variable observa la entrada real de `renGROBMasterContext::ProcessServer`
(`0x1511F0`): `[gow-model:grob-master]` resume hasta 256 contextos de su lista, el filtro
no nulo en `cliente+0x2C`, ciclos, punteros inválidos y truncamientos. Conserva el límite
de 64 muestras por fase para cada uno de los primeros ocho contextos distintos;
las primeras ocho muestras detallan cada cliente como
`[gow-model:grob-client]`, con su servidor, vista y método virtual. `validRoute` indica
únicamente que los punteros observados caben en RAM, sin certificar el registro del
método en el runtime ni su posterior invocación. Los nodos se comparan por dirección
física para detectar también ciclos entre alias de RAM.

`[gow-model:context]` observa la entrada de `0x159878`, cuya lista y filtros coinciden
con `renModelServerContext::ProcessServer` de la referencia GoW 2, aunque el mapa retail
no le asigna ese nombre. Registra las máscaras de vista, los modelos candidatos a la
llamada directa y los destinados al árbol estático, con los mismos límites por contexto
y por lista. `[gow-model:client]` detalla las ocho primeras muestras.
`[gow-model:process]` registra hasta 64 entradas por fase en `0x157A60`, equivalente
por estructura a `ProcessModel`, con el modelo y su número de grupos. Estos candidatos
se calculan a partir de la memoria observada: tampoco prueban que los filtros internos
o el árbol de esferas permitan dibujar el modelo.

La entrada de procesamiento también observa el esqueleto, su visibilidad raíz y el
primer bloque de bits de visibilidad de grupos. `[gow-model:clip]` registra hasta 64
llamadas por fase a `renView::Clip` (`0x169120`) procedentes de `0x157FA8`. Conserva los
bits de la esfera y de diez coeficientes/límites de la vista. Solo registra un resultado
como válido cuando el original vuelve a su llamador (`completed=1`); `0x80000000`
es el código que esta ruta usa para descartar. Ninguna sonda cambia los cálculos, los
registros FPU ni los filtros. No recoge aquí otras llamadas a Clip ni todos los
descartes internos de partes/modelos estáticos.

Es una observación de entrada: no certifica que el método se haya invocado, que haya modelos
visibles ni que se haya enviado o dibujado geometría. Conserva los registros y la memoria
del juego y llama siempre al original, también en las reanudaciones. El perfil de rendimiento
elimina la variable para evitar mezclar este diagnóstico con la medición.

## Coordenadas distintas sobre el mismo destino

`ps2recomp-gs-coordinate-alias.patch` ordena primitivas cuyo color o Z
comparten páginas físicas cuando las coordenadas superan el ancho FBW o
las 512 páginas lógicas de VRAM. Por ejemplo, con FBW=1, CT32 `(0,32)` y
`(64,0)` son la misma dirección: ni los tiles compute ni el interlock por
pixel XY protegían ese acceso. Antes del parche, el control procedural
pierde 6144–8192 bytes frente a CPU. Después coinciden los 4 MiB.

La detección es conservadora por página, separa color y profundidad y se
reinicia con cada lote. Conserva lotes de coordenadas normales y páginas
disjuntas, incluso cuando FBP atraviesa el final de VRAM. Dos controles
OpenGL reales cubren CT32/24/16/16S, Z32/Z16, ambos sentidos del alias,
Z inactivo y vuelta de memoria. Fallan con el backend anterior; la suite
nativa integrada pasa 587/587, con 22 controles OpenGL.

En la traza de partida comparada, los End e imágenes quedan exactamente
iguales al backend previo y siguen siendo 648 lotes. No certifica una
ganancia de FPS. El alias dentro de una sola primitiva y la diferencia
de feedback entre CPU y GPU siguen pendientes.

## Ensayo de profundidad de solo lectura

Separar las lecturas de Z de sus escrituras permitió bajar de 648 a 543
lotes en una traza local. El ensayo pasó los controles procedurales y
conservó los End e imágenes en ocho pasadas compute y ocho hardware con
snapshot. No acredita más FPS del juego ni una caché GS fiel al PS2.

Se retiró completo de la cadena publicada: la repetición larga sin
snapshot varió 200 bytes finales, y una versión limitada a snapshot
también varió 128 bytes en su modo habitual. GS56 conserva una limitación
previa: una de 24 presentaciones varió 190 bytes aunque los End fueran
idénticos. Resolver el feedback sigue pendiente. El código y los datos
del ensayo permanecen en `logs/`, fuera de Git.

## Espera del control STQ de hardware

`ps2recomp-gs-stq-hardware-test.patch` da hasta 12 s al compilador
asíncrono de shaders para que el control bilineal STQ use hardware.
Cada matriz repetida conserva sus comparaciones RGBA y controles SSE;
compute por sí solo sigue siendo insuficiente para pasar el test.
El cambio afecta a la validación y conserva el renderer de producción.

## Control integrado con VU1 compilada y planificador IOP

La compilación oficial de `main` en `9f0ebc4` aplica 60 parches y genera/enlaza
VU1 a partir de 501 micromemorias locales. Las 87 fuentes modificadas coinciden
con la cadena publicada; pasan 587/587 pruebas nativas, 22 controles OpenGL
reales y 60 casos VU1 exactos. El control limpio de 430 s produce 15 imágenes
distintas. La última muestra a Kratos y enemigos sobre el barco con lluvia y
HUD, en estado 11, sin carga pendiente y con hardware activo. No se observa
geometría estirada en esa imagen; sigue pendiente comprobar el combate completo
y resolver el feedback. Las capturas y los datos del juego permanecen locales.

## Atribución de tiempos GPU

`PS2X_GS_GPU_PROF=1` activa timestamps y un informe cada cuatro presentaciones.
`ps2recomp-gs-hardware-profile.patch` separa cada variante hardware de un lote
y registra sus primitivas, FBP, formatos y flags. Compute adjunta los datos
antes de resolver la cola de 4096 consultas; antes se perdían los del último
lote. Las dos regresiones opcionales de `GOW_GS_GPU_TEST=1` comprueban esos
casos con OpenGL efectivo y conservan los 4 MiB exactos frente al CPU.

Los grupos son por destino/flags y los tiempos GPU se expresan por frame;
los contadores de la línea `target` suman el intervalo del informe. Hardware
usa el estado de la primera primitiva de cada variante; compute, el del primer
estado del lote. No constituyen atribución por primitiva. El profiler espera
los resultados de las consultas y altera el ritmo del juego: debe desactivarse
al medir FPS. El arreglo mejora el diagnóstico, sin acreditar más rendimiento.
