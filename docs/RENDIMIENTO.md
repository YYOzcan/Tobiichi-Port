# Rendimiento

## Seleccionar ventanas de partida cargada

El menú y las pantallas de carga también llaman a `vid::Flip`; contar esas entradas no demuestra
FPS de partida. `tools/rendimiento/resumir.py --partida` conserva únicamente ventanas completas
encerradas por informes `[gow-pad2:state]` con `state=11`, `pending=0` y `levelReady=1`. Excluye las
ventanas que tocan una transición observada y falla si no queda ninguna. Los relojes del mando y
del perfil arrancan en momentos distintos: la selección usa el orden de las líneas del registro.

```powershell
.\scripts\probar_rendimiento.ps1 -Renderer opengl -Segundos 240 -Etiqueta partida
python tools/rendimiento/resumir.py logs/perf_partida.log --partida --desde 100 --hasta 220
```

Este filtro comprueba estados muestreados; todavía hay que comprobar la escena, usar el mismo
ejecutable y evitar compilaciones u otras partidas durante la comparación. Sin `--partida` se
conserva la selección anterior por tiempo, útil también para estudiar la carga. Nueve controles
procedurales verifican carga, transiciones, ambos límites, relojes distintos, redondeo, la CLI
y el rechazo de pasadas invalidadas.
El script retira también `PS2X_GS_DISCARD_DRAWS` y los diagnósticos de GS/VU1 durante el perfil,
y restaura sus valores al terminar.

## Perfil por muestreo (`tools/perfil/muestrear.cpp`)

`GOW_PERF_DIAG` reparte el tiempo por subsistema, pero no dice qué función lo consume. Este
perfilador externo suspende cada hilo del juego cada ~1 ms, lee su contador de programa y agrupa
las muestras por función con DbgHelp. No modifica el juego.

Para ver nombres, el ejecutable necesita su PDB. En una carpeta de trabajo propia (`GOW_WORK`), tras
`scripts\2_compilar.cmd`, se puede reconfigurar con información de depuración sin regenerar el C++:

```bat
cmake -S %GOW_WORK%\PS2Recomp -B %GOW_WORK%\PS2Recomp\out\build "-DCMAKE_CXX_FLAGS=/Zi /DWIN32 /D_WINDOWS /EHsc" "-DCMAKE_C_FLAGS=/Zi /DWIN32 /D_WINDOWS" "-DCMAKE_EXE_LINKER_FLAGS=/DEBUG"
cmake --build %GOW_WORK%\PS2Recomp\out\build --target ps2EntryRunner
cl /nologo /O2 /EHsc /utf-8 /std:c++20 tools\perfil\muestrear.cpp /Fe:logs\muestrear.exe /Fo:logs\muestrear.obj
logs\muestrear.exe <pid de ps2EntryRunner> 30
```

Las unidades de C++ generado deben recompilarse para incluir la información de depuración (tocar los
archivos `Unity\*.cxx` de `ps2EntryRunner`, como hace `2_recompilar_rapido.cmd`). Las muestras en
DLLs del sistema se atribuyen, cuando la pila se puede recorrer, al primer marco del ejecutable.

El perfilador imprime esa atribución en `marcos del ejecutable desde DLL`:
es una segunda vista de las muestras, con el porcentaje respecto al total
del mismo hilo, y no tiempo adicional ni CPU exclusiva. Conserva también
la vista del contador de programa. La revisión corrige la inicialización
duplicada de DbgHelp (error 87) y la omisión de esos marcos en la salida.
`scripts\probar_perfil.cmd` ejecuta una regresión Windows sin el juego: una
espera en una DLL recupera el llamador procedural propio. Falla con el
perfilador anterior y pasa con ambos arreglos.

## getenv en bucles calientes (2026-10-07)

Con OpenGL, `GOW_SKIP_FMV=1` y `GOW_FAST_BOOT=1`, el perfil de la partida mostraba un **38 % del
hilo del juego en `ucrtbase!strchr`**. Era `getenv`, que recorre todo el entorno en cada llamada:

- el bucle ocioso del IOP (`iop_emulator.cpp`, sin hilos listos) consultaba `PS2X_IOP_PC_EVERY`
  en cada vuelta;
- cada XGKICK de VU1 consultaba `GOW_XGKICK_IMMEDIATE`;
- algunos overrides llamados a menudo (`GOW_FAST_BOOT`, `GOW_PATH_DIAG`, `GOW_ANM_DIAG`,
  `GOW_EE_PRIM_DIAG`).

`patches/ps2recomp-getenv-hot.patch` lee esas variables una vez. Para conservar las pruebas que
cambian `GOW_XGKICK_IMMEDIATE` durante la ejecución, `ps2Vu1ReloadEnvironmentOptions()` vuelve a
leerla. `src/gow_overrides.cpp` guarda sus valores en variables estáticas.

Medición con `scripts\probar_rendimiento.ps1 -Renderer opengl -Segundos 240` (ventanas de 5 s en
estado 11, entre 220 y 235 s):

| | IOP | VU | `vid::Flip`/s |
|---|---:|---:|---:|
| Antes | 2,1–2,3 s | 2,4–2,6 s | 1,6–1,8 |
| Después | 0,26–0,38 s | 3,5–4,2 s | 1,8–2,6 |

El tiempo liberado del IOP pasa a VU1, que ahora ocupa más del 80 % del hilo del juego. En el perfil,
VU1 se reparte entre `commitReadyPipelines`, `normalizeOperand`, `calculatePairReadyCycle`,
`updateFmacFlags` y el resto del intérprete con modelo de latencias. La suite nativa pasa
**545/545** con el parche.

## Intérprete de VU1 (2026-10-07)

`tools/render/repetir_cadena_vif.cpp` acepta `GOW_REPETIR_VECES=N`: repite la cadena VIF1 del cuadro
N veces y mide el tiempo. Con `PS2X_GS_THREAD=1` y `PS2X_GS_DISCARD_DRAWS=1` el rasterizado no
cuenta, así que es un banco de pruebas determinista de VIF1/VU1. Con el cuadro del savestate del
inicio del Egeo (`D6385328`, 1.972 lanzamientos de VU1 por cuadro):

| Cambio (`patches/ps2recomp-vu1-perf.patch`) | ms por cuadro |
|---|---:|
| Antes | 775 |
| `commitReadyPipelines` recorre solo las entradas pendientes (máscara de bits por cola) | 594 |
| `normalizeOperand` en línea | 550 |
| `calculatePairReadyCycle` recorre solo los registros y componentes leídos | 503 |

La imagen resultante es idéntica byte a byte a la de antes de los cambios (mismo cuadro, renderer
CPU) y la suite nativa pasa **545/545**. En el juego la diferencia queda dentro de la variación entre
ventanas (la escena cambia y otros procesos compiten por la CPU); el banco de pruebas es la medida
de referencia. Lo siguiente en el perfil de VU1 es el cálculo de flags de FMAC
(`updateFmacFlags`, `calculateFmacProductSticky`, `calculateFmacExactResult`) y `execUpper`.

## VU1 sin colas de escritura (rama `vu1-rapido`, 2026-10-07)

`patches/ps2recomp-vu1-direct.patch`, con el mismo banco de pruebas (cuadro `D6385328`, 30 pasadas):

| Cambio | ms por cuadro |
|---|---:|
| Antes (main) | 503 |
| VF/VI/ACC se escriben al ejecutar en vez de encolarse con su latencia | 427 |
| `commitReadyPipelines` no hace nada antes del vencimiento más próximo; sin bits pegajosos si nadie lee el estado | 396 |
| La operación FMAC exacta (flags) se decodifica una vez por instrucción, no por componente | 386 |
| Entradas libres y registros VI escritos a partir de máscaras de bits | 339 |
| ADD/SUB/MUL con resultado normal: flags sin el cálculo exacto en long double | 333 |

**Escrituras directas.** Las colas de VF/VI/ACC no cambian el resultado del programa: quien lee un
registro se detiene hasta que está listo (`m_vfReady`, `m_viReady`, `m_accReady`) y solo se confirma
la última escritura emitida. Lo que sí cambia es el estado intermedio que ve quien corta la ejecución
por presupuesto de ciclos (las pruebas del modelo de latencias). Por eso es opcional:
`VU1Interpreter::setDirectRegisterWrites(true)` lo activa y `PS2Runtime` lo hace para VU1 salvo con
`GOW_VU1_COLAS=1`. VU0 sigue con colas (el EE lee sus registros en modo macro). Las colas de flags,
Q, P y stores se mantienen.

**Bits pegajosos.** Si el microcódigo cargado no tiene `FSAND`/`FSEQ`/`FSOR`, no se calculan los
bits pegajosos de los productos (`calculateFmacProductSticky`). Se vuelve a comprobar cada vez que
cambia el microcódigo; un programa posterior que lea el estado vería los pegajosos que no se
calcularon antes (con el microcódigo de este cuadro no ocurre: no hay ninguna de esas instrucciones).

Comprobación: la imagen es idéntica byte a byte con y sin colas en dos cuadros (`vif_pcsx2_inicio2`
de PCSX2 y `vif_port_480s` del port) y en modo con colas coincide con la referencia anterior. La
suite pasa **551/551** con la prueba nueva `direct register writes finish a VU1 program like the
queued model` (mismo resultado, mismos ciclos y mismas escrituras en memoria).

En el juego (OpenGL, ventanas de 5 s entre 220 y 235 s del mismo ejecutable): `vid::Flip` pasa de
2,2–2,4 por segundo con `GOW_VU1_COLAS=1` a 2,4–3,2 sin colas. VU1 sigue ocupando casi todo el hilo;
para llegar a tiempo real hace falta un recompilador de VU1.

## Microcódigo de VU1 compilado: primer prototipo (rama `vu1-compilado`, 2026-10-08)

Datos del cuadro de referencia (`D6385328`): **1.972 lanzamientos de VU1 y 3,34 millones de pares de
instrucciones** (4,40 millones de ciclos con las esperas), 1.188 direcciones distintas. Los bucles más
calientes son `0x2840–0x28E8` (~22 pares × 26.500 vueltas) y `0x2B90–0x2C10` (~19.000 vueltas). A
~330 ms por cuadro, cada par cuesta ~100 ns: para 30 cuadros por segundo haría falta ~10 veces menos.

Comprobaciones:

- **El modelo de tiempos importa.** Sin las esperas por dependencias (`GOW_VU1_SIN_ESPERAS`, solo en el
  experimento) más del 80 % de los píxeles del cuadro cambian: Q, P y los flags llegan en otro ciclo.
  Un recompilador tiene que conservar el mismo modelo de latencias.
- **Retoques del intérprete agotados.** Normalizar operandos con SSE2 y reutilizarlos fue *más lento*
  (369 frente a 336 ms); saltarse `execUpper` en los NOP superiores no cambió nada (330–337 ms).

`patches/ps2recomp-vu1-compiled.patch` separa un paso del intérprete (`stepPair`, en
`ps2_vu1_step.inl`) y permite registrar un despachador compilado. `tools/vu1/generar_vu1.cpp` genera
C++ a partir de micromemorias capturadas con `GOW_VU1_CAPTURA=<carpeta>` (27 imágenes distintas en tres
cuadros: el juego carga varios microprogramas por cuadro). Cada par se compila ya decodificado y el
despachador comprueba en cada par que las dos palabras de la micromemoria son las compiladas; si no,
interpreta ese par. El código generado sale de datos del juego y no se publica.

Resultado: **imagen idéntica byte a byte, pero más lento (525 ms frente a 336)**. Con `stepPair`
copiado en cada uno de los 4.360 pares, el código caliente ocupa varios MB y no cabe en la caché. La suite
pasa 563/563 y, sin código generado enlazado, el intérprete se comporta igual que antes.

Lo que sí haría falta (plan): un recompilador que, como microVU de PCSX2, calcule por bloque las esperas
y la visibilidad de flags/Q/P a partir del estado del pipeline a la entrada, genere solo la aritmética
de cada instrucción (SSE, con las mismas reglas de normalización y redondeo hacia cero) y omita los
flags que nadie lee. Es un trabajo de varios días; el prototipo deja preparados la captura, el generador,
el despachador y la comparación de imágenes.

### Etapa 1 del recompilador (2026-10-08)

- **Aritmética de VU sin `/fp:fast`.** El runtime se compila con `/arch:AVX2 /fp:fast`, y MSVC fusionaba
  `acc + a*b` en FMA o no según el sitio: el microcódigo compilado y el intérprete daban valores
  distintos en 1 ulp y el estado divergía a los 80 lanzamientos. `#pragma float_control(precise)` en los
  archivos de VU (y en `ps2_vu1.h`) redondea el producto y la suma por separado, como las FMAC de la PS2
  y PCSX2. Cambia ~3 % de los píxeles del cuadro en 1–8 niveles (0,3 % más de 8) respecto a la versión
  con FMA; conviene revisarlo con las comparaciones contra PCSX2.
- **Compilado = interpretado, comprobado lanzamiento a lanzamiento.** `GOW_REPETIR_HUELLAS=<archivo>` en
  `repetir_cadena_vif` escribe una huella del estado de VU1 (VF, VI, flags, ciclos y memoria de datos)
  tras cada lanzamiento; las 1.972 huellas del cuadro coinciden entre el código compilado y el
  intérprete. `GOW_VU1C_RANGO=inicio-fin` limita el código compilado a un rango de direcciones para
  acotar una diferencia.
- `stepPairT<par>` (en `ps2_vu1_compiled.inl`) resuelve al compilar todo lo que depende de la
  decodificación y especializa las operaciones FMAC; las demás llaman al intérprete.
- Intérprete: cola circular para los flags (se confirman en orden de emisión), atajo exacto para
  `acc ± producto` y comprobaciones baratas antes de llamar a `commitReadyPipelines`/`progressXgkick`.

Tiempos (cuadro `D6385328`, 30 pasadas): intérprete 304 ms, compilado 304 ms. Medido con contadores de
ciclos, cada par cuesta ~170 ciclos repartidos entre esperas (~20), instrucción superior (~65),
inferior (~35) y contabilidad del ciclo (~50). El código por par ya no es el problema: hace falta la
etapa siguiente, con las esperas y la visibilidad de flags/Q/P calculadas por bloque en variables
locales, los flags que nadie lee eliminados y las instrucciones inferiores especializadas.


### Etapa 2 del recompilador (2026-10-08)

- **Bloques.** El generador agrupa los pares en bloques (cortan en destinos de salto, ranuras de retardo,
  bit E y bits D/T). Un bloque entra solo si sus palabras coinciden con la micromemoria, no hay salto ni
  fin pendientes y queda presupuesto de ciclos; si no, se ejecuta par a par.
- **Flags que nadie lee.** Una FMAC cuyos flags MAC pisa otra FMAC posterior del mismo bloque sin que
  nadie lea MAC entre medias (FMAND/FMEQ/FMOR) no los calcula; si el programa no usa FSAND/FSEQ/FSOR/FSSET,
  solo acumula los bits pegajosos del status.
- **Instrucciones inferiores especializadas.** LQ, SQ, ILW, ISW, IADDIU/ISUBIU, B, IBxx, IADD/ISUB/IADDI,
  IAND/IOR, MOVE, MR32, LQI, SQI, WAITQ, MTIR y MFIR se generan con los campos ya resueltos; el resto
  llama al intérprete.

Tiempos (mismo cuadro): intérprete 304 ms, compilado 237 ms con bloques y flags muertos, 224 ms con las
inferiores especializadas. Las 1.972 huellas siguen idénticas al intérprete y la suite pasa 563/563.

### Integración y flags persistentes (8 de octubre)

La PR #18 incluye #17 y se integra después de los parches actuales de GS.
Al revisarla, un MADD cuyo producto subdesborda y cuya suma queda normal
conserva `status=0x140` con colas, pero daba `0x000` con escrituras directas si
el microprograma no contenía FSAND/FSEQ/FSOR. La ausencia de lectores en el
programa actual no garantiza que un programa posterior no observe esos bits.

`ps2recomp-vu1-sticky-preserve.patch` conserva el cálculo de los flags del
producto en el intérprete y en los pares compilados; los bloques que eliminan
MAC/estado temporal acumulan también los bits persistentes del producto.
Una regresión ejecuta el producto y luego un programa lector distinto. Los
tiempos anteriores describen la rama original: hay que volver a medir con
esta corrección antes de atribuirlos al ejecutable integrado.

`tests/vu1_compiled_test.cpp` construye microcódigo procedural, lo pasa por
el generador real y compara **60 casos** con el intérprete: bloques, salto con
retardo, stores, palabras modificadas, instrucción reservada, presupuestos
cero/corto y reanudación. Coinciden VF/VI/ACC, escalares, flags, ciclos, PC y
memoria de datos. En Windows se ejecutan 139 pares compilados y 22 interpretados;
la CLI exige que ambas rutas se utilicen. Ejecutar `scripts\probar_vu1_compilada.cmd`
y, con Python, `tests/vu1_compiled_cli_test.py logs/vu1_compiled_test.exe`.
La CI incluye el generador, las trece unidades generadas procedurales y el
control de rutas; no enlaza ni publica microcódigo del juego.

La compilación oficial añade la infraestructura y las escrituras directas.
El despachador necesita generar y enlazar C++ a partir de microprogramas
locales para acelerar el juego; sin esas unidades utiliza el intérprete.

### Etapa 2b: un bloque, una función (8 de octubre)

`ps2recomp-vu1-blocks.patch` y el generador escriben cada bloque como una sola función con los pasos en
línea, en el mismo archivo que sus pares (antes, cada par era una llamada a otro archivo). Los pares
intermedios que no saltan ni terminan (`stepPairT<..., Plain=true>`) solo avanzan el PC: al entrar al
bloque no había salto, bit E ni final pendientes, y solo el último par puede crearlos.

Tiempos con la cadena actual de main, que ya incluye la corrección de flags persistentes (cuadro
`D6385328`, 30 pasadas): intérprete 357 ms, compilado antes de esta etapa 233 ms y con ella 206 ms. Las
huellas por lanzamiento de `vif_pcsx2_inicio2` (1.972) y `vif_port_480s` (1.986) coinciden con el
intérprete, `scripts\probar_vu1_compilada.cmd` da 60 casos exactos y la suite pasa 565/565.

**Flags persistentes del producto sin `long double`.** `productStickyFlags` obtiene los flags Z/S/U/O
del producto exacto: si el producto ya redondeado es normal y lejos de los extremos, son solo su signo;
si no, se calcula en `double` (el producto de dos `float` cabe exacto). Da lo mismo que
`normalizeFmacExactResult` (huellas idénticas a las de antes del cambio). Los pares compilados lo
calculan en la misma componente, con los operandos ya cargados. Medido alternando los dos ejecutables
(20 pasadas, mediana): compilado 203 → 180 ms, intérprete 357 → 346 ms.

**Expansión en línea.** Un perfil por muestreo del cuadro mostró que, dentro de las funciones de bloque
(grandes), MSVC agotaba su presupuesto de expansión y llamaba a `normalizeOperand`,
`productSumFlagsFast`, `productStickyFlags` y `applyDest` (~12 % del tiempo). Ahora son
`__forceinline` (`VU1_HOT_INLINE`), `applyDest` tiene una versión con la máscara constante en los pares
compilados, y las funciones generadas llevan `__declspec(safebuffers)` (sin la comprobación `/GS` de sus
arreglos locales de tamaño fijo). Medido alternando ejecutables: 180 → 168 ms. Huellas idénticas.

**Más casos sin el intérprete.** Un perfilador por muestreo (RIP del hilo principal cada milisegundo,
con los símbolos del PDB) señaló `execUpper` (~6 %) y `commitReadyPipelines` (~7 %). ITOF, FTOI, ABS y CLIP
se generan ahora con los campos resueltos (antes `execUpper` normalizaba 12 operandos por cada una), y
`commitReadyPipelines` tiene un camino para cuando solo hay flags pendientes, el caso del código FMAC
denso con escrituras directas. Medido alternando ejecutables: 168 → 158 → 154 ms. Huellas idénticas.

En el mismo perfil, ~15 % del hilo principal es la espera de `GSThreadedBackend::Drain` en el
hilo del GS; eso no es VU1.

**XGKICK sin borrar 64 KB.** `m_xgkick = {}` ponía a cero el búfer de 64 KB del paquete en cada XGKICK y
en cada `resetScheduler` (~2.000 veces por cuadro). Ahora `XgkickPipeline::reset()` reinicia solo los
contadores: del búfer solo se leen bytes ya copiados (los GIFtags y el envío hasta `totalBytes`, que no
pasa de `copiedBytes`). El qword se copia de una vez cuando no da la vuelta a la memoria de datos, y las
entradas de flags confirmadas solo se invalidan (`pushFlagEntry` ya inicializa todos los campos). Medido
alternando ejecutables: compilado 156 → 128 ms, intérprete 337 → 308 ms. Huellas e imágenes idénticas.
Esto también acelera el intérprete que usa hoy el juego.

### VU1 compilada en el juego (8 de octubre)

`ps2recomp-vu1-runner.patch` añade a la compilación del juego el C++ generado: con la variable
`GOW_VU1_MICROCODIGO=<carpeta>` (micromemorias capturadas con `GOW_VU1_CAPTURA=<carpeta>`), `compilar.ps1`
pasa la carpeta a CMake, que compila `tools/vu1/generar_vu1.cpp`, genera `programa0..12.cpp` en la carpeta
de compilación y los enlaza en `ps2EntryRunner`. Sin la variable el juego usa el intérprete, como antes.
`GOW_VU1_SIN_COMPILAR=1` desactiva el código compilado al ejecutar. Las micromemorias y el C++ generado son
datos del juego: no se publican.

El juego sube microcódigo distinto casi en cada cuadro: 90 s de juego dieron 474 micromemorias distintas,
pero solo ~6.000 pares distintos (11 MB de C++). Para capturarlas:

```powershell
$env:GOW_VU1_CAPTURA = 'D:\vu1_micro'   # carpeta local
.\scripts\probar_rendimiento.ps1 -Segundos 90 -Renderer opengl -Etiqueta captura
Remove-Item Env:GOW_VU1_CAPTURA
$env:GOW_VU1_MICROCODIGO = 'D:\vu1_micro'
.\scripts\2_compilar.cmd
```

Medido en el juego (`probar_rendimiento.ps1 -Renderer opengl`, cuadros por segundo del juego, entre los
10 y los 35 s):

| VU1 | cuadros/s | VU (ms cada 5 s) |
|---|---|---|
| intérprete | 5,6–5,8 | ~3.450 |
| compilada, 27 micromemorias de las grabaciones | 6,8–7,4 | ~3.050 |
| compilada, 501 micromemorias (grabaciones + 90 s de juego) | 9,6–10,0 | ~2.430 |

Con el renderizador por CPU (`cpu-hilo`) el GS limita (~2,2 cuadros/s en ambos casos).

## Planificador del IOP (8 de octubre)

Un perfil por muestreo de todos los hilos del juego (renderizador OpenGL, VU1 compilada) mostró el 41 %
del hilo principal en `IopKernel::beginNextReady` y `nextWakeCycle`. El EE avanza el IOP ~1,5 millones
de veces por segundo de a ~4 ciclos y casi siempre no hay hilos listos, pero cada llamada recorría dos
veces los 21 hilos (un `std::map`) y una tercera para el próximo despertar.

`ps2recomp-iop-scheduler.patch`: `beginNextReady` hace un solo recorrido (despertar los Delay vencidos y
elegir el listo de menor prioridad e id no dependen del orden) y, si no hay ninguno listo, recuerda el
primer despertar. Cada operación del núcleo que puede cambiar los hilos incrementa `m_version`; mientras
no cambie y no llegue ese despertar, `beginNextReady` devuelve lo mismo sin recorrer y `nextWakeCycle`
usa el valor guardado. El resultado es idéntico por construcción; la suite pasa 565/565.

En el juego, `iop_ms` baja de ~1.300–1.500 a ~570–650 ms cada 5 s y las dos funciones desaparecen del
perfil. Los cuadros por segundo no se pudieron comparar bien: otra compilación ocupaba la máquina.

## FINISH del GS asíncrono (opcional, 8 de octubre)

Con el renderizador OpenGL, cada escritura del registro FINISH hace `Flush` y `Sync` síncronos y
`glFinish`: el hilo del juego espera a que el hilo del GS y la GPU terminen. En el perfil del juego eso era
el 14 % del hilo principal. `GOW_GS_FINISH_ASINCRONO=1` (`ps2recomp-gs-finish-async.patch`, desactivado
por defecto) encola FINISH en el hilo del GS y el EE ve el bit enseguida; el hilo del GS mantiene el orden
y las lecturas de VRAM desde el EE siguen sincronizando. Medido en el juego alternando la variable: 12,1 →
12,7–13,1 cuadros/s. Queda por decidir si es seguro activarlo siempre.

`tests/gs_finish_async_test.cpp` controla ambos modos en procesos separados: un backend procedural
retiene FINISH, comprueba cuándo vuelve la escritura y cuándo se publica CSR, y exige que una lectura
de VRAM espere. Los dibujos, FINISH y la lectura deben conservar el orden. Con el runtime anterior a
la PR #22, el control default pasa y el control async falla. Ejecutar en Windows
`scripts\probar_finish_gs.cmd`. Este control no acredita el momento de terminación de una GPU real:
el modo opcional publica FINISH antes de completarla y continúa desactivado por defecto.

## Perfil de partida integrada sin otros compiladores (8 de octubre)

El ejecutable de `9f0ebc4` (60 parches, GS56, VU1 compilada con 501 micromemorias y planificador IOP),
OpenGL y FINISH síncrono, se prueba durante 180 s con FMV omitido y una copia privada de tarjeta.
Se vigilan cada segundo compiladores, enlazadores, Ninja/CMake y otras instancias del juego. No se
detectan durante la primera pasada; la segunda no comienza porque aparece otra compilación.

El selector `--partida` conserva 12 ventanas completas entre 104,79 y 164,84 s, 60,04 s en total,
encerradas por estados 11 sin carga pendiente y con el nivel listo. Media ponderada: **7,13
`vid::Flip`/s**; presentaciones del host: **58,45/s**. Son contadores distintos. El tiempo transcurrido
exclusivo del hilo del juego se reparte así:

| Subsistema | Porcentaje |
|---|---:|
| VU1 | 49,08 % |
| GS, incluidas sus esperas | 31,08 % |
| EE | 13,71 % |
| IOP | 6,13 % |

La escena cambia durante el tramo; esta pasada no demuestra una ganancia frente a otro ejecutable
ni FPS sostenidos del juego completo. El siguiente perfil debe separar el trabajo del GS de su
espera y repetir el mismo tramo después de cada mejora.

## Desempaquetado de VIF1 (8 de octubre)

`ps2recomp-vif1-unpack-fast.patch`: en UNPACK sin máscara, con datos y sin STMOD que sume la fila, cada
componente es el valor descomprimido; se escribe el qword de una vez en lugar del bucle por componente.
Mismo resultado: huellas de VU1 e imágenes de `vif_pcsx2_inicio2` y `vif_port_480s` idénticas, suite
565/565. Reproducción alternando ejecutables: 136 → 133 ms por cuadro.

**Temporizadores del EE.** `advanceEeTimers` se llama en cada punto de control del código recompilado
(~1,5 millones de veces por segundo) y buscaba GIF_STAT en el `unordered_map` de registros cada vez.
`ps2recomp-ee-timers-fast.patch` guarda la dirección del elemento (los elementos de un `unordered_map` no se
mueven; solo `clear()` en la inicialización la invalida). Mismo comportamiento; suite 565/565.

## FMAC de VU1 con SSE (8 de octubre)

`ps2recomp-vu1-simd.patch`: los pares compilados calculan las cuatro componentes de una FMAC (ADD, SUB, MUL,
MADD, MSUB, MAX, MINI, OPMULA y OPMSUB sin la componente w, con sus variantes bc/q/i/A) con SSE: la misma
normalización de operandos, y cada producto y suma redondeados por separado con el MXCSR del VU, así que el
resultado es el mismo bit a bit que en `fmacLaneT`. Los flags se calculan en vector cuando todos los carriles
activos están en el camino rápido del intérprete (resultado y producto lejos de cero y de los extremos, o
resultado exactamente cero); si no, se rehace la instrucción con el código escalar. Sin SSE4.1 (GCC sin
`-msse4.1`) se compila solo el escalar.

Comprobación: huellas por lanzamiento idénticas en las dos reproducciones, la prueba de 60 casos de GPT y
una prueba nueva, `tests/vu1_fmac_test.cpp`, que compila las 252 variantes de FMAC (todas las fuentes, tres
máscaras DEST, cruzadas) y las compara con el intérprete con valores límite aleatorios (ceros con signo,
subnormales, FLT_MIN/FLT_MAX, Inf/NaN y patrones de bits cualesquiera): 504.000 casos exactos con 1.000
ensayos. Un fallo inyectado a propósito (el flag Z del producto) lo detecta en el primer ensayo. La CI la
ejecuta con 200 ensayos.

Mediciones de Opus en sus tramos, alternando ejecutables: 131 → ~100 ms por cuadro
en la reproducción; en el juego con OpenGL, 11,5–12,0 → 13,2–14,4 cuadros/s.
Son segmentos distintos del perfil de partida cargada documentado arriba.

La revisión de integración encuentra un caso adicional: con FTZ/DAZ del PC
activado, ADD/SUB pueden redondear una cancelación subnormal a cero sin que
la operación exacta sea cero. El atajo SIMD omitía entonces el flag U
persistente de VU1. Un ensayo aleatorio lo detecta en el ensayo 15; la
regresión dirigida falla antes del arreglo con `status=1c0/c0`, aunque los
valores de los registros coincidan.

El parche exige operandos opuestos/iguales para reconocer un cero exacto
de ADD/SUB y conserva la ruta escalar para esos underflows. La prueba añade
2016 casos dirigidos con FTZ/DAZ, ambos signos y escrituras directas/con colas,
y restaura el MXCSR del proceso. Pasan esos casos y 100.800 casos aleatorios
con el código corregido, enlazados contra el runtime local. No se cambia la
FPU del EE ni se activa FINISH asíncrono por defecto.

En Windows, después de compilar el runtime parcheado, se reproduce con
`scripts\probar_vu1_fmac.cmd`; la salida queda en `logs/vu1_fmac_test.log`.

`scripts\probar_rendimiento.ps1` rechaza el inicio del perfil si observa una
compilación u otra instancia del juego y vigila esos procesos cada segundo
durante la ejecución. Si aparece carga externa, cierra únicamente su PID,
conserva el perfil con la marca `[gow-perf:invalid]`, restaura el entorno y
termina con error. El selector rechaza toda la pasada marcada, incluso si se
solicitan ventanas anteriores a la interferencia, y no exporta un resumen.
Los controles privados que sustentan las cifras anteriores de este documento
también vigilan procesos cada segundo. Es una vigilancia por muestreo; una
carga externa más corta que el intervalo puede pasar inadvertida.

Cuatro controles de PowerShell, sin ejecutar el juego, comprueban compilación
previa, compilación iniciada durante el perfil, otra partida y el PID propio
sin interferencia. Verifican el registro marcado, la restauración del entorno
y que solo se detiene el proceso propio. Dos controles adicionales del selector
verifican el rechazo del perfil y de la exportación JSON: nueve en total.

Con la integración comprobada de 64 parches (`247a9b3`, incluido el arreglo
FTZ), una pasada privada de 180,55 s con OpenGL y FINISH síncrono conserva
doce ventanas completas en estado 11, sin carga pendiente y con el nivel
listo: **7,58 vid::Flip/s** y **57,71 presentaciones/s**, durante 60,04 s
(103,06–163,12 del reloj del perfil). La vigilancia cada segundo no observa
compilaciones ni otra partida. Distribución exclusiva del hilo del juego:

| Área | Tiempo transcurrido |
|---|---:|
| VU | 43,24 % |
| GS, incluidas esperas | 38,20 % |
| EE | 12,20 % |
| IOP | 6,36 % |

Es una sola pasada con escena cambiante. No demuestra una ganancia atribuible
a SIMD frente al perfil anterior ni sustituye las mediciones de Opus. El
siguiente diagnóstico debe separar coste de envío, esperas del GS y GPU.

El primer diagnóstico de timestamps (180 s con el mismo ejecutable) confirma
una limitación de atribución: los lotes hardware se agrupaban bajo FBP=0,
flags=0 y cero primitivas aunque se estuviera dibujando la partida. El parche
de [atribución GPU](RENDERIZADO.md#atribución-de-tiempos-gpu) conserva el estado
por variante y corrige también la frontera de 4096 consultas compute.
Las cifras de ese diagnóstico se conservan localmente; no se interpretan
como FPS ni se utilizan sus grupos vacíos para elegir una optimización.

Con el profiler corregido del ejecutable de 65 parches, un diagnóstico de
240,21 s conserva 280 informes GPU completos encerrados por estados de
partida cargada. Las consultas raster promedian 39,26 ms/frame del profiler.
Los principales grupos observados son:

| FBP (hex) | Flags (hex) | Timestamp GPU medio por frame |
|---|---|---:|
| 0 | 4b | 30,13 ms |
| 0 | 5a | 2,15 ms |
| 0 | 12 | 2,08 ms |
| 0 | c8 | 1,81 ms |

`4b` combina IIP, textura, mezcla alfa y filtrado bilineal. El diagnóstico
incluye algunos lotes compute durante la preparación de shaders. La vigilancia
no observa compiladores ni otra partida y la tarjeta original queda intacta.
Estas cifras proceden de consultas sincronizadas, con registros adicionales
y escena cambiante. Sirven para elegir dónde investigar; no acreditan FPS ni
una mejora de rendimiento y no se comparan con el profiler anterior.

### Integracion de DIV compilado (PR #23)

La especialización de `DIV` del commit `754c970` conserva los selectores de componentes,
la normalización del intérprete, la saturación con signo, los flags D/I y `queueQ(..., 7, ...)`.
Opus informa de huellas idénticas y 98 → 96 ms en su reproducción alternando ejecutables.
Esta cifra pertenece a su captura y no se extrapola al perfil de partida cargada.
La integración conserva el arreglo FTZ/DAZ de `247a9b3` y sus 2016 casos dirigidos.

El control anterior de 60 casos no ejecutaba `DIV`. Se amplía con **38.144 casos**
que comparan registros bit a bit, Q, flags, ciclos y memoria entre compilado e
intérprete: los 16 selectores, ceros con signo, subnormales, límites, Inf/NaN,
patrones aleatorios, WAITQ y cortes/reanudaciones, con FTZ/DAZ activado y desactivado.
Un fallo privado que cambia siete por seis ciclos falla en el primer caso, con
`cycles=19/18`, aunque Q y flags finales coincidan. El generador compila tanto
bloques como pares reales; la CLI exige que aparezca el control DIV completo.
Se reproduce con `scripts\probar_vu1_compilada.cmd` en Windows o en la CI.
Pasar estas pruebas confirma paridad semántica en esos casos; no mide una ganancia de FPS.
