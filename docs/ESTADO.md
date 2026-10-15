# Estado del proyecto

_Última actualización: 8 de octubre de 2026_

## Qué funciona

- La compilación completa termina sin errores (~11 min de compilación del juego en un equipo de 8+ núcleos).
- `scripts\2_recompilar_rapido.cmd` recompila solo `src/gow_overrides.cpp` en ~1 minuto.
- `ps2EntryRunner.exe` arranca, inicializa raylib 5.5 / OpenGL 3.3 y abre la ventana (640×448).
- **El IOP ejecuta los IRX originales del juego** en el intérprete R3000A de `ps2xIOP`: `sio2man`,
  `dbcman`, `sio2d`, `mc2_d`, `ds2u_d`, `libsd`, `989nomid` (989snd) y **`smpd_iop`** (el cargador de
  datos). `scripts\ejecutar.ps1` los copia a `IOP_MOD\` junto al ELF la primera vez.
- El IOP lee la **ISO original** (`God of War.iso` junto a la carpeta del ELF, o la variable `GOW_ISO`).
- smpd se inicializa: lee el directorio ISO9660 y `GODOFWAR.TOC`, y crea sus hilos.
- **La configuración se carga desde el disco**: la petición `SMPD 0xF "R_Perm"` devuelve el handle 0
  y `HERO_HEAP_SIZE` / `SLOT_HEAP_SIZE` / `UPGRADE_HEAP_SIZE` se encuentran (la guardia provisional del
  diccionario NULL dejó de saltar y se ha retirado).
- **`R_PERM.WAD` se carga entero en streaming** (smpd lee 16 sectores por llamada a `sceCdRead` y los
  envía al EE en bloques de `0x20000` que se alternan entre `0x530640` y `0x550640`).
- 989snd arranca sin errores (antes, 15 × `cause 7` por un `argv` mal construido).
- **El juego entra en su bucle principal (`sys::GameLoop`) y dibuja sus primeras pantallas**: la pantalla
  legal *"Sony Computer Entertainment America presents"*, la de *"Please insert a DUALSHOCK®2…"* y el logo
  de *God of War* de la pantalla de título. A algunos textos les faltan letras.
- El depurador del runtime se muestra/oculta con **F1**.
- El HLE de **libpad2** conecta el primer puerto al backend del runtime: teclado o gamepad, botones,
  ambos sticks y presiones digitales. La navegación llega al **menú principal y la selección de dificultad**.
  Los controles y la prueba reproducible están en [CONTROLES.md](CONTROLES.md).
- El dispatcher conserva los checkpoints que ceden en la entrada de una función. Esto elimina la copia
  parcial de `Animation/goHero` y la llamada virtual a NULL al avanzar desde el menú.
- `gowIpuInit` corrige la inicialización del IPU: el stub genérico saltaba a una dirección de otro
  ejecutable y ejecutaba `FilteredCopyTile` con registros incorrectos. Ahora se alcanza la carga del FMV.
- Con `GOW_SKIP_FMV=1` se alcanza el **estado 11 de partida**, con `pending=0` y el hilo principal activo.
  Tras integrar los arreglos de Claude, el control OpenGL de 330 segundos carga una copia de su tarjeta
  y muestra a Kratos, el escenario, el HUD y la indicación R2 en «Docks of Athens». El rendimiento sigue
  bajo; faltan controles de combate, otros escenarios y rendimiento sostenido.

## Símbolos

Los mapas de nombres de `01-retail-usa-SCUS97399/` (exportación de Ghidra, casados con la demo del E3
y la demo europea) **coinciden con las direcciones de nuestro ELF**. Algunas confirmadas:

| Dirección | Nombre |
|---|---|
| `0x0026BF28` | `snd_SendIOPCommandAndWait` |
| `0x0026C940` | `snd_DoExternCall` |
| `0x00186710` | `wadContext::FindData` |
| `0x00175890` | `stdDynaStringDB::GetDynaStringNode` |
| `0x0017A940` | `sys::Boot2` |
| `0x00239F90` | `stdCList<wadCleanupData, …>` |
| `0x00299D08` | `cbTimerHandler` (alarmas de libkernel) |
| `0x0016AFD8` | `memcpy_asm` |
| `0x0016B120` | `ringBuffer::GetBytes` |
| `0x00183878` | `vid::WaitForDMAComplete` |

`GOW-Port/sym.py <direcciones>` (fuera del repositorio) traduce direcciones con estos mapas.

## Cronología de la investigación del arranque

### 1. El cuelgue en `0x00176A80` no era una espera

`sub_001769F8(raiz, clave)` es la búsqueda en un **árbol binario** de nodos de 16 bytes guardados en un
pool (creado por `sub_00175CD0`, 8000 nodos):

| Campo | Significado |
|---|---|
| `nodo+0x0` | clave (hash) |
| `nodo+0x4` | valor |
| `nodo+0xA` / `nodo+0xC` | hijo izquierdo / derecho (índice u16 en el pool) |
| `*0x29C4BC` | base del pool (`hijo = base + índice*16`) |
| `*0x29C4B4` | nodo centinela (fin de rama) |
| `*0x29C4B8` | handle del pool |

`GetDynaStringNode` (`0x175890`) recibía un diccionario **NULL** desde `wadContext::FindData`
(`0x186710`), que buscaba `HERO_HEAP_SIZE`, `SLOT_HEAP_SIZE` y `UPGRADE_HEAP_SIZE`. La raíz se leía en
la dirección `0x4` y esa basura formaba un ciclo. El diccionario es `nodo+0x4C` del contexto del WAD
`R_Perm`, que no se había cargado.

### 2. La configuración vive en `R_PERM.WAD` y la carga smpd

`R_PERM.WAD` es el primer archivo de `PART1.PAK` (sector 0, `0x378530` bytes). Las variables son
registros de tipo `0x18` del grupo `WAD_R_Perm`:

| Variable | Valor |
|---|---|
| `HERO_HEAP_SIZE` | `0x1EC800` |
| `SLOT_HEAP_SIZE` | `0x100000` |
| `UPGRADE_HEAP_SIZE` | `0x14BC00` |

`GODOFWAR.TOC` es una tabla de entradas de 24 bytes con el formato `nombre[12]`, `u32`, `u32 tamaño`,
`u32 sector`.

El EE no lee el disco: lo hace **`SMPD_IOP.IRX`** ("smpd file streamer"), un plugin de 989snd.

### 3. Protocolo EE ↔ 989snd ↔ smpd

`snd_SendIOPCommandAndWait(cmd, tamaño, datos)` hace `sceSifCallRpc(sid 0x123456, rpc = cmd)`: envía
`tamaño` bytes desde `0x305640` y recibe 12 bytes en `0x305600`. Devuelve la palabra 1 de la respuesta.

El comando **`0x68`** es un mensaje para un plugin: `{u32 plugin, u32 tipo, u32 len, u32 ptr}` más `len`
bytes copiados de `ptr`. Para smpd, `plugin = 0x534D5044` (`'SMPD'`).

| # | cmd | Contenido | Significado | Respuesta |
|---|---|---|---|---|
| 1 | `0x0` | `{0x30A1C0, 0}` | inicialización de 989snd | 0 |
| 2 | `0x68` SMPD `1` | `{modo, estado, 0x20, tabla, 0x280, …}` | inicializar smpd (búferes del EE, ver abajo) | 0 |
| 3–17 | `0xA` | `{0}` … `{14}` | 15 comandos de 989snd | `0x400` |
| 18 | `0x68` SMPD `0xF` | `"R_Perm"` + `0x10000210, 0, 1` | **cargar el WAD `R_Perm`** (flag `0x200` = síncrono) | handle `0` |
| 19… | `0x4C` | 0x1C bytes | `snd_DoExternCall` | `0x20000` |

Búferes de smpd en el EE (`sub_001389D8`, la inicialización): `*0x29BE4C` = estado (0x20 bytes) y
`*0x29BE50` = tabla (0x280 bytes). Se acceden sin caché (`| 0x20000000`) porque smpd los escribe por
DMA (`sceSifSetDma`). La tabla tiene una cabecera de 0x100 bytes y 8 ranuras de 0x30 bytes. En la carga
síncrona, `sub_0017AD70` lee `tabla + 0x12C + handle*0x30` (campo `+0x2C` de la ranura) y
`sub_00185F28` lo guarda en `nodo+0x4C`.

### 4. Ejecutar los IRX originales en lugar de reimplementarlos

`ps2xIOP` está diseñado para ejecutar los IRX del juego ("Game-specific IOP code executes from IRX
modules"). No se cargaban solo porque el juego los pide como `IOP_MOD/xxx.irx`. Una vez disponibles
aparecieron cuatro fallos del emulador, todos corregidos en `patches/ps2recomp-runtime.patch`:

| Fallo | Síntoma | Arreglo |
|---|---|---|
| Heap del IOP de solo 832 KB (`HeapBase = 0x120000`) | smpd: "failed to allocate memory" (pide `0x11ADF8` bytes) | `HeapBase = 0x70000` (los módulos acaban hacia `0x56000`) |
| Tope de 2 M instrucciones por llamada síncrona (`kMaxCallInstructions`) | la inicialización de smpd, ejecutada dentro del RPC de 989snd, se cortaba **en silencio** a mitad del TOC y el EE esperaba para siempre | tope de 400 M y aviso `[IOP] guest call … exceeded its budget` |
| `sprintf`/`vsprintf` de sysclib copiaban el formato literal | smpd hacía `sprintf("%s.wad", nombre)` y buscaba `%S.WAD` → `R_Perm` devolvía -1 | formateador real con argumentos o32 (`iop_format.h`), usado también por `printf` |
| Sin imagen de disco | smpd lee por número de sector | `configureGowCdImage` en `src/gow_overrides.cpp` usa la ISO original |

### 5. Métodos virtuales sin punto de entrada

`sub_0023A000` hace una llamada virtual a `0x239FD0`, un método vacío (`jr ra`) al que solo se llega
por vtable. Ni nuestro mapa de funciones ni Ghidra lo tenían como función: quedaba dentro de
`sub_00239F90` y el runtime lo daba por inexistente (`[guest-branch:missing-target]`). Recorriendo las
vtables del ELF (entradas `{s16 ajuste, s16 índice, u32 función}`) salieron **24 destinos** así. Ahora
están en `entry_points` de `config/recomp.template.toml` (`vfunc_XXXXXXXX`), y el recompilador les crea
un punto de entrada dentro de la función que los contiene.

### 6. El hilo principal moría: una copia de 205 MB

Con lo anterior, el juego avanzaba hasta que **el hilo principal moría** (`Dormant`, `pc=0`) por una
llamada a un callback NULL en `cbTimerHandler`. La lista de alarmas de libkernel (`0x2A5B08`–`0x2A5B14`)
aparecía llena de datos de `R_PERM.WAD`. El culpable era
`memcpy_asm(dst=0x6C190, src=0x530640, n=0xC478000)`, llamado desde `ringBuffer::GetBytes` por el
cargador de WAD: el búfer de streaming estaba **a cero**, así que el cargador leía un tamaño basura.

Los datos sí llegaban por `sceSifSetDma`, pero **al búfer de la petición siguiente**. En el IOP real,
el servidor RPC de 989snd despierta al hilo lector de smpd (de más prioridad), que se ejecuta y apunta
el destino antes de que el hilo RPC conteste. El emulador ejecutaba el servidor RPC como una llamada
síncrona y contestaba en el acto, así que el hilo lector tomaba el destino de la petición siguiente.
**Arreglo:** tras cada RPC, el emulador deja correr a los hilos del IOP que estén listos
(`runReadyThreads`, tope de 4 M ciclos) antes de copiar la respuesta.

### 7. La espera de vídeo: la interrupción del GS

`vid::WaitForDMAComplete` (`0x183878`) espera mientras `*0x29C7D0 == 1`. La bandera la pone a 1 quien lanza
la cadena DMA (`svrEpilogue::FlipAndKick`, `fxCameraFilter`…) y solo la cambia el **manejador de la
interrupción del GS** (`0x182DD8`, código que Ghidra no marcó como función): lee `GS_CSR`, y si `FINISH`
está activo pone la bandera a 2 y borra el bit. El runtime marcaba `CSR.FINISH` pero **nunca lanzaba la
interrupción INTC 0**. Arreglo: `EeScheduler::pollGsInterrupt()` la lanza en el flanco de subida de
`CSR.SIGNAL/FINISH` no enmascarados en `IMR`.

### 8. Las interrupciones pisaban la pila del hilo principal

Con la interrupción del GS activa, el hilo principal moría saltando a `0xF82`. Las pilas de los manejadores
de interrupción se reservan desde lo alto de la RAM (`0x1FFFFF0`) hacia abajo, **justo donde
`SetupThread` coloca la pila del hilo principal**: cada interrupción machacaba sus marcos más antiguos.
Arreglo: `SetupThread` baja el techo de esa zona por debajo de la pila principal
(`PS2Runtime::limitAsyncCallbackStackTop`; ahora empiezan en `0x1FE8000`).

### 9. Otros arreglos del emulador del IOP

- Los módulos arrancaban con `start(tamaño, texto)` en lugar de `start(argc, argv)`; ahora `argv` es
  `[ruta, arg1, …, NULL]`, como en `loadcore`.

Además, el override de `snd_SendIOPCommandAndWait` ya no descarta los comandos: los registra (`[gow-snd]`)
y llama al original. `GOW_SND_STUB=1` recupera el comportamiento antiguo.

## Herramientas de diagnóstico

| Herramienta | Uso |
|---|---|
| `[gow-snd]` | comandos enviados a 989snd/smpd y su respuesta |
| `PS2X_IOP_TRACE=N` (+ `PS2X_IOP_TRACE_FROM=M`) | registra N llamadas a importaciones del IOP a partir de la M |
| `PS2X_IOP_TRACE_NOCLIB=1` | omite `sysclib` en esa traza |
| `PS2X_IOP_TRACE_EVERY=N` | muestreo: una de cada N llamadas |
| `PS2X_IOP_PC_EVERY=N` | PC del IOP cada N instrucciones y aviso cuando no hay hilos listos |
| `PS2X_IOP_TRACE_DMA=1` | cada transferencia `sceSifSetDma` IOP → EE (origen, destino, tamaño, primeros bytes) |
| `[run:thread]` | estado de todos los hilos del EE cada ~10 s (en `ejecutar.log`) |

Los diagnósticos provisionales de las secciones 1, 5 y 6 (`[gow-tree]`, `[gow-dict]`, `[gow-23a000]`,
`[gow-timer]`, `[gow-watch]`) se retiraron de `src/gow_overrides.cpp` una vez resueltos esos problemas;
siguen en el historial de git por si hiciera falta recuperarlos.

## Problemas conocidos

| Problema | Detalle |
|---|---|
| Texto con letras de menos | algunas fuentes/texturas se dibujan incompletas (pantalla del mando, menú) |
| Imagen de partida | se alcanza el estado 11 con los FMV omitidos, pero el framebuffer queda negro |
| Mando | libpad2 funciona por HLE para el primer puerto; presiones 0/255 y sin vibración. En el SIO2 emulado los puertos de mando se ven vacíos |
| Memory card sin verificar | el SIO2 y la tarjeta están emulados (`ps2recomp-sio2.patch`, archivo `Mcd001.ps2`), pero falta probarlo con el juego |
| Audio sin verificar | el SPU2 emulado ya sale por el audio del PC (`ps2recomp-spu2-output.patch`), pero falta probarlo con el juego; sin reverb ni ADMA |
| Sin vídeo FMV | `sceMpeg*` / `sceIpu*` son stubs |
| Dependencias de ninja | Con MSVC en español no se registran las dependencias `/showIncludes`: `2_recompilar_rapido.cmd` toca el archivo unity de los overrides y `compilar.ps1` borra los objetos unity tras regenerar (los cambios en cabeceras del runtime requieren tocar los `.cpp` que las incluyen) |
| Rutas con acentos | `ps2_recomp` no abre rutas no ASCII: `compilar.ps1` copia el ELF y el mapa a la carpeta de trabajo |

## Próximos pasos

1. Investigar VIF/VU→GIF: en el estado 11 los contextos del GS siguen con `FBP=0`, sin primitivas
   en la traza reciente, mientras se presenta `FBP=208`. XGKICK rechaza paquetes por exceder
   su búfer o por el formato de la cabecera. Los avisos `0xFFFFFFFB` y `0xFFFFFFF8` son códigos
   internos del runtime, no instrucciones inválidas del microcódigo. `GOW_RENDER_DIAG=1`
   permite guardar el microcódigo y la RAM para compararlos.
   La recompilación completa reproduce el problema. Una traza temporal de XGKICK confirmó
   paquetes correctos al principio y luego datos de vértices interpretados como cabeceras
   (`source=0x2AB0`, segunda cabecera en `offset=0x10`). Revisar preparación/rotación de buffers
   y UNPACK antes de ampliar el búfer del runtime.
   Se probó por separado la transferencia inmediata usada por SOCOM Unzipped:
   `GOW_XGKICK_IMMEDIATE=1` alcanza el estado 11, pero no resuelve la imagen negra y siguen
   los errores XGKICK. El parche queda opcional; la transferencia por ciclos sigue siendo el valor
   por defecto. Ver la comparación en [CONTROLES.md](CONTROLES.md#prueba-aislada-de-xgkick).
   La comprobación del bit I registró **196608 comandos y cero solicitudes de interrupción VIF1**
   hasta el estado 11 (FMV omitidos, entrada rápida). El mecanismo de pausa/reanudación de
   [SOCOM Unzipped](https://github.com/Scotho/socom-unzipped/blob/main/third_party/ps2recomp/ps2xRuntime/src/lib/ps2_vif1_interpreter.cpp#L15-L20)
   no explica el fallo observado en esa prueba. No se ha habilitado.
   `-DiagnosticoVif` compara las cabeceras antes de MSCAL y durante XGKICK, distingue los paquetes
   vacíos de los rechazos reales y guarda los buffers de dibujo al alcanzar la partida.
   Los contextos FBP=0 tienen datos, pero sus capturas no muestran una escena 3D; FBP=208 sigue
   negro. La traza de escrituras encontró bucles de transformación que recorrían los buffers y
   sobrescribían sus cabeceras. `ps2recomp-vu-jump.patch` corrige la lectura de JR/JALR: usaban
   el valor anterior de VI, aunque ese retraso corresponde a las comparaciones de ramas condicionales.
   Con el arreglo, la prueba de 140 s llegó al estado 11 y registró 212992 comandos VIF sin
   rechazos XGKICK ni instrucciones VU reservadas. La pantalla de partida todavía es negra y los
   contextos de dibujo no muestran una escena 3D. La siguiente comprobación es la transformación
   de coordenadas y la interpretación de los registros/paquetes GIF ahora que sus cabeceras se conservan.
   Ver [CONTROLES.md](CONTROLES.md#diagnóstico-de-vif-y-buffers-de-dibujo).
2. Resolver la espera de MPEG (`sceMpegGetPicture`, `0x0018A3D8`) y corregir el renderizado de
   fuentes/3D. `GOW_SKIP_FMV=1` permite investigar la partida mientras el decodificador está pendiente.
   Hipótesis en curso (`ps2recomp-mpeg-nodata.patch`): el stub de `sceMpegGetPicture` esperaba
   fotogramas sin llamar nunca al callback `sceMpegCbNodata` que el juego registra con
   `sceMpegAddCallback`. En la libmpeg original ese callback es el que lee del anillo y llama a
   `sceMpegDemuxPssRing`, así que nadie alimentaba al decodificador (bloqueo mutuo). El parche lo llama
   en el hilo que pide la imagen; si no aporta datos, reintenta en el siguiente VSync. Dos pruebas de
   regresión lo cubren (sin el parche la suite se cuelga en la primera). **Falta comprobarlo con el
   juego:** ejecutar sin `GOW_SKIP_FMV` y buscar en `ejecutar_err.log` las líneas
   `[MPEG:AddCallback] ... type=1` (el juego registra el callback) y si la espera desaparece.
3. Memory card (SIO2 / `MC2_D.IRX`). **`ps2recomp-sio2.patch`:** antes los registros del SIO2
   (0x1F808200-0x1F8082FF) eran simples latches, `dmacman` no hacía nada y no había interrupción 17, así que
   `sio2man` esperaba para siempre cada transferencia. Ahora el IOP emula el SIO2: cola de comandos (SEND3),
   FIFO de entrada y salida, DMA 11/12 (`sceSetSliceDMA`/`sceStartDMA` de `dmacman` para esos dos canales),
   `RECV1-3`, `ISTAT` e IRQ 17 al poner `CTRL` bit 0. Los comandos de mando y multitap responden como puerto
   vacío (libpad2 sigue por HLE en el EE). La memory card implementa el protocolo de PS2 de PCSX2 (sondeo,
   páginas de 512 + 16 bytes, borrado de bloques de 16 páginas, lectura/escritura, terminador, especificaciones
   y los pasos de autenticación sin cifrado); `SecrAuthCard` de secrman devuelve éxito. Las páginas se guardan
   en bruto en `Mcd001.ps2` junto al ELF, el mismo formato de 8 MB que usa PCSX2 (se pueden intercambiar
   partidas). Si el archivo no existe, la tarjeta empieza sin formatear y se crea en la primera escritura.
   Variables: `GOW_MC0=<ruta>` (otra tarjeta; `GOW_MC0=0` deja el puerto vacío), `GOW_MC1=<ruta>` (segundo
   puerto, vacío por defecto), `GOW_SIO2_DIAG=1` (registra cada comando de tarjeta como `[SIO2] mc0 cmd=0x..`)
   y `GOW_SIO2=0` (vuelve al comportamiento anterior). El protocolo se probó contra `mcman` de ps2sdk; God of
   War usa `MC2_D.IRX` de Sony, que no se ha podido revisar. **Falta comprobarlo con el juego:** si al guardar o
   al arrancar aparece el aviso de tarjeta sin formatear, si el formateo y el guardado terminan, y si
   `Mcd001.ps2` se puede abrir en PCSX2.
4. Audio sobre 989snd / SPU2. **Fase 1 (`ps2recomp-spu2.patch`):** el IOP emula el SPU2: 2 MB de RAM de
   sonido, registros de 16 bits de los dos núcleos, puerto de datos manual, DMA de los canales 4 y 7 que ahora
   copia los datos (antes solo marcaba la transferencia como hecha; el bit `STATX` 0x80 y la interrupción
   diferida no cambian), voces ADPCM con tono, ADSR, volumen fijo y mezcla seca, `ENDX`/`ENVX`/`NAX` legibles
   e IRQ 9 al alcanzar `IRQA`. `GOW_SPU2_IRQ=0` desactiva esa IRQ por si el juego cambia de comportamiento.
   **Fase 2 (`ps2recomp-spu2-output.patch`):** la mezcla de 48 kHz del SPU2 sale por un `AudioStream` de raylib
   (estéreo, 16 bits). El IOP produce las muestras en el hilo del EE y el hilo de audio las consume con un mutex;
   si se acumulan más de 100 ms se descartan las más antiguas, y si faltan se rellena con silencio (si la
   emulación va más lenta que el tiempo real se oirán cortes). `runCycles` avanza el SPU2 hasta el último ciclo
   ejecutado aunque el IOP esté en espera. `GOW_AUDIO=0` desactiva la salida (el SPU2 sigue emulándose). En el
   registro aparece `[SPU2] salida de audio a 48 kHz activa`. Sin verificar con el juego: hay que comprobar si se
   oye la música del menú y si suena a la velocidad correcta.
   Falta: reverb, barrido de volumen, ADMA (PCM en streaming) e interpolación gaussiana.

## Auditoría del intérprete de VU1

Se revisaron, instrucción por instrucción, las unidades superior e inferior de VU1
(`ps2_vu1_upper.cpp`, `ps2_vu1_lower.cpp`) contra la especificación y contra PCSX2 (`VUops.cpp`):
FMAC con broadcast, acumulador y `OPMULA`/`OPMSUB`, `CLIP`, `FTOI`/`ITOF`, `DIV`/`SQRT`/`RSQRT` (con la
latencia de `Q`), flags (`FSAND`, `FMAND`, `FCAND`…), ramas y enlaces, cargas y almacenamientos con
autoincremento, `MTIR`/`MFIR`, el generador `R` y la EFU. La única discrepancia fue una errata en un
coeficiente de la serie de `EATAN` (`-0.1308…` en vez de `-0.1390…`), corregida en
`ps2recomp-vu-efu.patch` con su prueba. La semántica de esas instrucciones no explica la imagen negra
de la partida. Fuera de esta revisión quedan las latencias por instrucción y los riesgos del pipeline.

## Validación del avance al menú

- `scripts\probar_pad2.cmd`: pasa la prueba de bytes de botones, sticks y las doce presiones.
- Compilación de `ps2EntryRunner` y `ps2x_tests`: correcta.
- Suite del runtime desde su directorio raíz: **435/437**. Fallan dos pruebas previas:
  `setup heap and allocator primitives track end-of-heap` y
  `IOP heap DMA uses private backing instead of aliasing EE RDRAM`.
- Al retirar únicamente la corrección del dispatcher, la nueva prueba de checkpoint falla y el total
  baja a **434/437**; los mismos dos fallos de heap/DMA permanecen.
- `ps2recomp-checkpoint.patch` se comprobó sobre la revisión fijada más el parche original del proyecto.
- La prueba de 200 segundos con el IPU corregido llegó a elegir dificultad y después esperó en MPEG.
  Las capturas y registros son evidencia del menú, **no de una partida jugable**.
- La prueba de 600 segundos omitiendo FMV llegó al estado 11 sin omitir la animación de entrada,
  con `pending=0`; las capturas de partida son negras. `GOW_FAST_BOOT=1` repite la transición
  en aproximadamente 70 s desde la primera lectura del mando.
- Con el parche experimental XGKICK, la suite completa da **436/438**: pasa la nueva prueba
  de sobrescritura del buffer y permanecen los mismos dos fallos previos de heap/DMA.
- `ps2recomp-xgkick.patch` aplica correctamente sobre la revisión fijada del runtime.
- `ps2recomp-vif-unpack.patch` corrige la expansión XYXY de V2 y los bits de color/alfa V4-5.
  Sus tres regresiones fallan antes del arreglo (**436/441**) y pasan después (**439/441**),
  manteniendo los dos fallos previos. El parche aplica sobre la revisión fijada.
  La prueba del juego alcanza el estado 11; los defectos del menú y la imagen negra permanecen.

- `ps2recomp-vu-jump.patch` conserva el valor actual de VI para JR/JALR, incluido el caso en que
  JALR reutiliza el registro de destino para su enlace. Mantiene la ranura de retardo y las reglas
  existentes de ramas condicionales. Se sustituyó una expectativa incorrecta del test JR y se añadió
  cobertura JALR: ambas regresiones fallan antes (**438/442**) y pasan después (**440/442**),
  con los mismos dos fallos conocidos. El parche aplica sobre la revisión fijada más los anteriores.
  El ejecutable se compiló y la prueba de 140 s confirmó el avance al estado 11 sin rechazos GIF
  ni instrucciones VU reservadas; las capturas siguen sin acreditar una partida jugable.

- Al integrar los cambios publicados en paralelo de `ps2recomp-heap.patch`, la suite pasa
  **443/443**. El heap privado conserva el rango de God of War y la prueba de DMA usa el límite
  real del heap del IOP. Los resultados 440/442 anteriores corresponden al árbol previo a esa integración.
- Se corrigió la recompilación completa repetida: `checkout -f` no eliminaba `iop_format.h`, creado
  por el parche del runtime, y `git apply` fallaba con `already exists in working directory`.
  `compilar.ps1` retira ahora ese archivo junto a `gow_stub_services.cpp` antes de reaplicar los parches.

- La compilación completa (`scripts\2_compilar.cmd`) regeneró las 6418 unidades del juego,
  reaplicó los siete parches y enlazó `ps2EntryRunner.exe` correctamente. Se verificó por separado
  que los siete parches aplican, en ese orden, sobre la revisión fijada y producen las fuentes usadas
  por la compilación. Tras reconstruir, la suite sigue pasando **443/443**; la configuración tiene
  cero errores (cuatro avisos conocidos), los ocho scripts PowerShell se analizan sin errores y la
  prueba independiente de libpad2 pasa.

- Con el ejecutable completo y el heap integrado, la segunda prueba de 140 s volvió a alcanzar
  el estado 11 en 70,32 s desde la lectura del mando. Registró 217088 comandos VIF1 sin rechazos
  XGKICK ni instrucciones VU reservadas. Las capturas de 90 y 110 s son negras; los contextos de
  dibujo conservan el fondo oscuro. La partida todavía no es jugable.

## Investigación del renderizado 3D: raíces de COP1 (5 de octubre de 2026)

El diagnóstico local de VU1 en el estado 11 encontró una matriz de transformación que ya llegaba
con `NaN` en sus componentes XYZ. Después de transformarse, los paquetes de geometría contenían
coordenadas XYZ nulas y el bit ADC de descarte activado. Los registros del GS mostraban las copias
entre buffers, pero no acreditaban que los triángulos de la partida se dibujaran correctamente.

Al seguir los cálculos de cámara se identificaron dos errores del recompilador COP1:

- `SQRT.S` del R5900 obtiene el radicando de **FT**, pero se emitía una lectura de FS. Con FS=0,
  las funciones de cámara calculaban raíces del registro F0 en lugar de sus sumas de cuadrados.
- `RSQRT.S` calcula **FS / sqrt(FT)**; se emitía **1 / sqrt(FS)**, perdiendo ambos operandos.

`ps2recomp-fpu-roots.patch` corrige la selección de operandos y añade dos regresiones que decodifican
las instrucciones binarias y comprueban el código emitido, incluyendo destinos que coinciden con
las fuentes. Ambas fallan antes del arreglo (**443/445**) y pasan después (**445/445**, antes de
integrar las nuevas pruebas EFU/MPEG). Referencia de contraste:
[implementación COP1 de PCSX2](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/FPU.cpp#L316-L344).
Este parche no implementa todavía las particularidades de flags y saturación de la FPU del R5900.

Una prueba separada inicializando `VF0.w=1` en los hilos EE nuevos no eliminó los `NaN` de la matriz.
Se retiró ese cambio experimental. Los volcados de memoria, microcódigo y capturas usados para
este diagnóstico permanecen locales en las carpetas ignoradas; no forman parte del parche.

La reconstrucción completa con los diez parches regeneró las 6418 unidades y enlazó correctamente
el ejecutable. La suite integrada, incluidas las pruebas EFU/MPEG publicadas en paralelo, pasa
**448/448**. Los diez parches aplican en orden sobre la revisión fijada; configuración y handlers
sin errores (cuatro avisos conocidos), ocho scripts PowerShell sin errores de sintaxis y prueba
independiente de libpad2 correcta.

Dos ejecuciones de 140 y 165 segundos con `GOW_SKIP_FMV=1` y `GOW_FAST_BOOT=1` alcanzaron el estado 11.
La matriz que antes contenía `NaN` ahora contiene valores finitos y aparecen coordenadas de vértices
distintas de cero. El GS registra miles de primitivas de triángulos durante la partida. La captura
presentada a los 90 segundos muestra un fondo oscuro, sin una escena reconocible ni Kratos: esto
**no acredita una partida jugable**. Los buffers de geometría inspeccionados todavía contienen
vértices con ADC activado; el siguiente paso es correlacionar proyección/recorte VU1 con los paquetes
que realmente recibe el GS. Las trazas temporales añadidas para inspeccionar las matrices se retiraron
y se volvió a enlazar el ejecutable; el parche publicado solo cambia los operandos COP1 y sus pruebas.

Antes de publicar se integró mediante merge `ps2recomp-spu2.patch`, publicado por Opus durante estas
pruebas. Se conservaron ambos parches en `compilar.ps1`; se reconstruyeron el IOP, el ejecutable y las
pruebas afectadas. La suite pasa **456/456** y los once parches aplican en una copia aislada de la revisión
fijada. La nueva ejecución con SPU2 vuelve a alcanzar el estado 11. La traza de vértices de la textura
13264 confirma que llegan coordenadas finitas al GS, pero incluye vértices con `draw=0`; habrá que
correlacionarlos con el recorte y con las primitivas que sí se dibujan, sin asumir que todo descarte sea
un error (pueden estar fuera de la vista).

### Seguimiento de las posiciones antes de la proyección (2026-10-05)

Se integraron las publicaciones de Claude hasta `a401182` (salida SPU2 y SIO2) antes de editar el
proyecto. Los diagnósticos siguientes se ejecutaron con el binario anterior a esas dos integraciones,
con la corrección COP1 y SPU2 fase 1, para conservar una referencia comparable.

Tres ejecuciones de 135/140 segundos, con `GOW_SKIP_FMV=1` y `GOW_FAST_BOOT=1`, alcanzaron el estado 11.
Se instrumentaron temporalmente CLIP/FCGET y la entrada de las transformaciones VU1:

- CLIP recibe coordenadas finitas; en la muestra examinada, los puntos exceden los límites de los
  planos. FCGET observa las actualizaciones con la latencia esperada. Esto no demuestra que todo el
  recorte sea correcto, pero no justifica borrar ADC ni forzar el dibujo de los vértices descartados.
- La prueba de inicializar `VF0.w=1` en hilos EE nuevos se repitió con las raíces COP1 ya corregidas.
  No cambió el resultado visual; se retiró nuevamente.
- Un flujo VIF1 completo capturado durante el estado 11 contiene 141 lanzamientos y usa UNPACK S,
  V2 y V4 en modos 0 y 1. No contiene V3 ni STMOD modo 3. Las diferencias detectadas en esos dos
  caminos del runtime no explican este flujo y no se modificaron como supuesto arreglo del juego.
- En un lote de la rutina situada en `0x3230`, las posiciones XYZ cargadas para `ITOF4` ya están en
  cero. La matriz de cámara es finita y la transformación posterior repite su término de traslación.
  Se conservó un volcado anterior a la entrada de esa rutina para distinguir los datos de entrada de
  los paquetes sobrescritos durante su ejecución. Falta identificar la escritura que produce esos
  ceros; todavía no se atribuyen a un fallo concreto del intérprete ni del juego.

El export de Ghidra de GoW2 Europe Demo proporcionado como referencia sirve para identificar las
funciones de cámara, viewport y recorte; sus tipos y pseudocódigo se contrastan con las instrucciones
de GoW1. No se publica el export, el código generado, los flujos VIF ni los volcados de memoria.
Las trazas temporales se retiraron del runtime. La escena sigue sin ser reconocible: no se acredita
una partida jugable. El siguiente paso es rastrear el productor del buffer de posiciones de ese lote,
incluyendo las escrituras anteriores a la proyección, antes de cambiar su consumidor.

Después se aplicaron SPU2 salida y SIO2 al runtime local, se recompilaron las fuentes afectadas y
se enlazaron el ejecutable y las pruebas. La suite integrada pasa **465/465**. Los **13 parches**
aplican en orden sobre la revisión fijada; las **41 fuentes** `.cpp`/`.h` comparadas coinciden con
el runtime local (se excluye el registro de funciones específico de la compilación del juego).
La ejecución integrada de 150 segundos vuelve a alcanzar el estado 11; la captura presentada
mantiene el fondo oscuro y no muestra una escena 3D reconocible. La configuración pasa sin errores,
con los cuatro avisos ya documentados. El merge de Claude `a401182` tiene sus verificaciones de
GitHub completadas correctamente.

<a id="medicion-de-rendimiento-2026-10-05"></a>

## Medición de rendimiento (2026-10-05)

La compilación Release conservaba activadas las trazas generales, las entradas/salidas de cada
función y las trazas RPC del IOP. El registro de funciones vacía el archivo en cada mensaje; una
ejecución de 150 segundos dejó unos 204 MB. `compilar.ps1` configura ahora las tres opciones en
`OFF` por defecto. `scripts\2_compilar.cmd -Trazas` permite activarlas para investigar.

`ps2recomp-perf.patch` añade un perfil opcional, independiente de esas trazas:

- `GOW_PERF_DIAG=1`: emite una línea `[gow-perf]` cada cinco segundos con tiempos transcurridos
  exclusivos de EE, VU, procesamiento GIF/GS, llamadas al IOP y espera del scheduler. Las llamadas
  al GS anidadas en VU se descuentan de VU; no se suman dos veces.
- Los tiempos de subida de imagen y `EndDrawing` pertenecen al hilo de presentación y se informan
  por separado. `EndDrawing` incluye la limitación de refresco y las esperas del host.
- `GOW_PERF_FRAME_PC=0x001837B8` cuenta entradas a `vid::Flip` de este ELF, tanto desde el scheduler
  como desde llamadas directas. Sus reanudaciones no cuentan. `guest_flip_hz` mide esas entradas;
  `host_hz` mide los refrescos de la ventana. Ninguno acredita por sí mismo cuadros 3D correctos.
- `GOW_PERF_DIAG=frames` conserva ambos contadores sin temporizadores por subsistema, para comprobar
  el coste del perfil; los campos de tiempo quedan en cero porque no se miden. Sin `GOW_PERF_DIAG`,
  no lee relojes ni acumula estos contadores.
- Los tiempos incluyen esperas de mutex y del sistema operativo; **no son porcentajes de uso de
  CPU**. El trabajo de un scope todavía abierto se contabiliza al cambiar de scope, por lo que
  conviene comparar varias ventanas completas, no una sola línea.

Prueba reproducible, sin volcados VIF/RAM/VRAM ni capturas periódicas:

```powershell
powershell -File scripts\probar_rendimiento.ps1 -Segundos 150 -Etiqueta limpio
python tools\rendimiento\resumir.py logs\perf_limpio.log --desde 100 --hasta 145
powershell -File scripts\probar_rendimiento.ps1 -Segundos 150 -SoloCuadros -Etiqueta cuadros
python tools\rendimiento\resumir.py logs\perf_cuadros.log --desde 100 --hasta 145
```

El script conserva las pulsaciones de `GOW_PAD_TEST`, desactiva las capturas con
`GOW_PAD_TEST_NO_CAPTURE=1` y restaura el entorno al terminar. Usa `GOW_SKIP_FMV=1` y `GOW_FAST_BOOT=1`;
estas mediciones no evalúan reproducción FMV ni una partida completa. Los registros quedan locales
en `logs/`. Una línea `[gow-pad2:state]` informa del estado aproximadamente cada cinco segundos
sin escribir imágenes. El resumen separa el hilo del juego del de presentación.

Se compararon tres ejecuciones de 150 s, resumiendo ocho ventanas completas entre los segundos
100 y 145 del reloj del perfil (unos 40 s por muestra). En ese tramo se verificó el estado 11:

| Compilación / medición | Entradas a `vid::Flip` por segundo | Refrescos de ventana por segundo |
|---|---:|---:|
| Trazas activadas, perfil completo | 2,19 | 57,25 |
| Trazas desactivadas, perfil completo | 2,37 | 56,60 |
| Trazas desactivadas, solo contadores | 2,40 | 56,45 |

La diferencia observada respecto a la referencia es de aproximadamente un 8 %. La referencia
conservaba las capturas periódicas del mando; las dos mediciones nuevas las desactivan. Son muestras
individuales y no aíslan toda la variación entre ejecuciones, por lo que no acreditan una mejora
garantizada de FPS. La diferencia entre perfil completo y solo contadores ronda el 1 % en esta
muestra: el coste de los temporizadores no parece explicar el bajo rendimiento observado.

Con trazas desactivadas, el tiempo exclusivo contabilizado en el hilo del juego se reparte en
**IOP 61,26 %, GIF/GS 27,94 %, VU 8,72 % y EE 2,08 %**. La espera del scheduler es nula en esas
ventanas. Es un reparto de tiempo transcurrido de los caminos instrumentados, no uso de CPU ni
una separación interna de CPU/SPU2 dentro del IOP. El próximo perfil del IOP debe distinguir
intérprete, servicios y mezcla SPU2; optimizar únicamente VU tendría un margen pequeño en esta escena.

La reconstrucción completa regeneró las 6418 unidades del juego. Los 14 parches aplican en orden
en una copia aislada y sus 42 fuentes `.cpp`/`.h` comparadas coinciden con el runtime compilado.
La suite integrada pasa **467/467**, incluidas dos comprobaciones de contabilidad exclusiva y
anidamiento del perfil. Configuración y handlers sin errores (cuatro avisos conocidos), scripts
PowerShell sin errores y prueba independiente de libpad2 correcta.

La comprobación visual final, separada de las mediciones y usando el mismo salto de FMV/arranque
rápido, vuelve a alcanzar el estado 11. La captura presentada a los 110 s desde la lectura del mando
muestra el fondo oscuro con ondas, sin una escena 3D reconocible ni Kratos. El perfil y la retirada
de trazas mejoran la observación y reducen costes, pero **no acreditan todavía una partida jugable**.

### Posiciones presentes en el flujo VIF anterior

Se revisó fuera de línea el flujo VIF completo capturado anteriormente en el estado 11. Un UNPACK
`V4_32`, con 120 vectores y `STCYCL=0x0102`, ya contiene en su payload los 120 valores
`(0,0,0,32768)`, antes de que VIF/VU1 los interpreten. El mismo comando seguido del payload aparece
en varios buffers del volcado EE. Otros lotes `V4_16` de 81 vértices contienen posiciones XYZ
distintas de cero. Esto acota los ceros de aquel lote a los datos de entrada EE/DMA; no demuestra
todavía qué productor falla ni que una plantilla vacía sea incorrecta en ese momento.

Los símbolos y el export de referencia ayudan a seguir `renEEPrim::InitUNPACKData`, `InitChunk` y
`GetUpdateAddress`. La primera prepara instrucciones y offsets, reservando espacio para los datos;
hay que identificar y comprobar la rutina que posteriormente rellena las posiciones. No se cambia
el recorte ni se sustituye geometría con datos inventados. Los exports, flujos y volcados permanecen
locales y no se publican.

### Referencia del port de Shadow of the Colossus

El usuario aportó [sotc-vibe-pc](https://github.com/LightVelox/sotc-vibe-pc). Se revisaron su
arquitectura, resultados de rendimiento y el runtime exacto que fija su submódulo:
[`LightVelox/PS2Recomp`, `ac9efa070638ad3b3accd284de6f898d5ab271d1`](https://github.com/LightVelox/PS2Recomp/tree/ac9efa070638ad3b3accd284de6f898d5ab271d1).
La copia de referencia queda en una carpeta local ignorada; el runtime de GoW conserva su revisión
fijada y los parches integrados de este proyecto.

Hallazgos concretos para la siguiente etapa:

- La interfaz `GSRasterBackend` coincide con la nuestra. El fork aporta `GSGpuBackend`, un wrapper
  `GSThreadedBackend`, rasterizado OpenGL y pruebas de referencia/replay. Esto permite estudiar una
  incorporación por módulos conservando el renderer CPU para comparar resultados. La interfaz común
  no basta para garantizar compatibilidad de memoria, sincronización, transferencias o presentación.
- Aporta VU1 recompilada con fallback al intérprete y herramientas de verificación. En nuestra muestra
  VU supone menos del 9 % del tiempo instrumentado, por lo que no es la primera optimización de FPS.
- El IOP y el reloj de audio también tienen cambios. Hay que comparar por separado el intérprete,
  scheduler y SPU2 con los cambios de Claude antes de trasladar cualquier arreglo de ese ámbito.
- Sus [resultados publicados](https://github.com/LightVelox/sotc-vibe-pc/blob/main/Docs/PERFORMANCE_RESULTS.md)
  separan campos emulados, actualizaciones del juego, imágenes distintas y swaps del host. Registran
  mejoras concretas de presentación, pero no acreditan 60 actualizaciones reales por segundo en las
  muestras del santuario. Se usa como referencia de implementación y validación, sin trasladar esa
  cifra de rendimiento a GoW.

Prioridad: contrastar los datos y la salida del renderizado con una referencia correcta; después
adaptar backend GS y mejoras genéricas en parches independientes, con pruebas y comparación visual.

### Adaptación del backend GS de SotC (2026-10-05)

Se incorpora `patches/ps2recomp-gs-opengl.patch` como parche independiente después del perfil.
Adapta `GSGpuBackend`, `GSThreadedBackend`, shaders, contexto WGL y tablas de direccionamiento
de VRAM del commit `ac9efa070638ad3b3accd284de6f898d5ab271d1` de Taylor N. Albarnaz / LightVelox,
bajo GPL-3.0. Los archivos importados llevan el comentario `GOW-Port` y su procedencia.
Selección, créditos, pruebas y límites: [`RENDERIZADO.md`](RENDERIZADO.md).

Se conserva el renderer CPU original como predeterminado y como referencia. El GPU funciona
en el hilo GS; vuelve a CPU si no inicializa el contexto o los shaders. Las lecturas y FINISH
esperan los comandos previos, Flush publica y completa su bloque, y el cierre drena comandos
antes de destruir el contexto en su hilo. La presentación compacta del fork se adapta al
stride de 640 píxeles de nuestro frontend. Las tablas VRAM se inicializan una sola vez.
La presentación GL compartida se deja para una etapa posterior.

La suite nativa pasa **474/474**: cinco nuevas pruebas normales y dos pruebas opcionales con
GPU real. En una AMD Radeon RX 5700 XT se verifica OpenGL 4.6 con compute forzado y con
rasterizado gráfico activo. Se comparan transferencias partidas/alineadas, clear, sprites,
VRAM completa y presentación; también se comprueban interior/exterior de un triángulo plano
y textura CT32. Sin las tres correcciones de la cola, sus regresiones fallan: **469/472**.
Las 45 pruebas separadas de caché/CLUT/memoria GS pasan con la integración nueva.

La reconstrucción completa genera las 6418 unidades del juego. Los 15 parches aplican en un
árbol aislado y sus 61 fuentes `.cpp`/`.h` comparadas coinciden con el runtime local.
Configuración y handlers: cero errores, cuatro avisos conocidos; PowerShell y libpad2 correctos.

Se añade `GOW_EE_PRIM_DIAG=1` para observar `renEEPrim::InitUNPACKData` y `GetUpdateAddress`
sin modificar datos ni su ejecución. Registra los callers y los buffers devueltos; el mando
automático puede releer hasta 16 direcciones cada 5 s. Esas direcciones pueden reutilizarse,
por lo que una lectura tardía necesita comprobar su propiedad antes de atribuir el contenido
a un productor. El diagnóstico de VRAM existente usa ahora el snapshot público para leer
también la memoria del backend GPU actualizada.

El alcance respeta el reparto: no se cambia recompilador, FPU, IOP, VIF ni VU1. El parche
`ps2recomp-fpu-roots.patch` permanece intacto. Se detectó una rama remota adicional de Claude
con arreglos EE/DMA/VIF/VU0 y se mantiene separada; no se incorpora a `main` por esta tarea.
Repetir la prueba de posiciones cuando Opus integre sus cambios EE/FPU precede a decidir
si la recompilación de VU1 aporta una mejora útil.

Comparación local sin capturas, con el mismo binario/ELF/ISO y tres ventanas completas de
5 s en estado 11, dentro de `120–136 s`: CPU directo **2,40 `vid::Flip`/s**, CPU con hilo
**2,39**, OpenGL con hilo **3,26**. Presentaciones del host: **56,33 / 55,68 / 59,12 Hz**.
La mejora de OpenGL es aproximadamente **36 %** en esta muestra corta; no se mide variabilidad
ni se certifican cuadros distintos. La GPU real inicializa sin fallback. Las capturas se
toman en ejecuciones separadas de 155 s: ambos modos muestran agua oscura sin Kratos ni la
escena completa. Las tardías del CPU cambian; las de OpenGL de `56–130 s` son idénticas.
Queda pendiente contrastar la selección de framebuffer/presentación del CPU (`preferredSource`)
con CRTC del GPU, además de la geometría. El CPU conserva su papel de referencia predeterminada.

La traza nueva registra **64 inicializaciones, 298 retornos y 192 lecturas posteriores**.
El caller `0x12E258`, en `LoadClient` (`0x12DE70`), obtiene 40 buffers; las 14 direcciones
de ese caller conservadas por la sonda muestran después `(0,0,0,0x8000)`. Se comprueba en
el MIPS original que el bucle `0x12E270–0x12E288` **escribe deliberadamente esa plantilla**.
La reserva inicial incluye los chunks relacionados con el UNPACK V4-32 de XYZ cero anterior.
Esto corrige la hipótesis de que esos ceros, por sí solos, prueben un productor EE roto:
son una inicialización explícita; queda por seguir su transformación y uso en VU1/GIF.
El caller `0x1FB800` (función `0x1FB4B8`) devuelve dos buffers con XYZ no nulo y cambiante,
también en las lecturas posteriores. No se observan retornos desde los dos productores
`goWater` estudiados en esta muestra. No se altera ADC ni se rellenan posiciones artificiales.

### Arreglos del EE tomados del fork de SotC (2026-10-06)

Con autorización del usuario se incorporan, en `ps2recomp-ee-fixes.patch` (aplicado tras
`ps2recomp-gs-opengl.patch`), los arreglos del EE del fork de SotC (TaylorNAlbarnaz/PS2Recomp, rama
`sotc-port`), marcados con `// GOW-Port:` y el commit de origen:

- **FPU (COP1) con la semántica del PS2** (8b51cb9, 9bb389e, c419f26): la FPU del EE no tiene NaN ni
  infinitos. ADD/SUB/MUL saturan a ±`FLT_MAX`; ADD/SUB alinean los operandos sin bits de guarda (como
  PCSX2); `DIV.S` por cero da ±`FLT_MAX` y pone D o I en FCR31; `SQRT.S`/`RSQRT.S` usan |FT| y redondean
  al más cercano; `CVT.W.S` satura; las comparaciones `C.*.S` comparan el patrón de bits y nunca dan
  "desordenado". Antes una división por cero o un desbordamiento producía infinitos o NaN que se
  propagaban, por ejemplo a matrices de cámara. `ps2recomp-fpu-roots.patch` no cambia: sus dos pruebas
  ahora esperan las llamadas `ps2FpuSqrt`/`ps2FpuRsqrt`, que conservan los mismos operandos (FT para
  `SQRT.S`, FS/sqrt(FT) para `RSQRT.S`).
- **VU0 en modo macro:** VADD/VSUB/VMUL/VMULQ saturan; `VDIV`, `VSQRT` y `VRSQRT` usan las mismas reglas
  con los flags del registro de estado. `VRSQRT` calculaba 1/sqrt(FT) e **ignoraba FS**; ahora es
  FS/sqrt(|FT|).
- **LQ/SQ/LQC2/SQC2 ignoran los 4 bits bajos de la dirección** (9bb389e).
- **BLEZ/BGTZ/BLTZ/BGEZ (y sus variantes) comparan el registro de 64 bits**, no los 32 bits bajos (3c46932).
- **Salto final a la entrada de la función llamada** (c4c20e8): `dispatchGuestBranch` tomaba una llamada
  que volvía con el PC en su propia entrada como un retorno implícito; si dentro hubo un salto (`j` de
  vuelta a la función), el llamador continuaba con la pila de la otra función. Ahora solo se aplica si no
  se despachó ningún salto dentro, además de la condición del checkpoint que ya existía.

No se incorporan todavía la entrega de cada desbordamiento de los temporizadores del EE (d328765), que
depende de otros cambios del fork, ni la propagación de constantes con relocalizaciones (019867b), que
afecta a módulos reubicados que God of War no usa.

Pruebas: 6 pruebas nuevas (comparaciones, suma con alineación, división y raíz con redondeo, LQ/SQ,
salto final, unidad Q de VU0) y la de ramas de 64 bits del fork; la suite pasa **479/479** con los 16
parches. **Falta comprobarlo con el juego:** hace falta `scripts\2_compilar.cmd` (cambia el código que
genera el recompilador y las 6 418 unidades se regeneran). Repetir la prueba de posiciones y de la matriz
de cámara del estado 11 y comparar las capturas.

### Presentación OpenGL y campos entrelazados (2026-10-05)

Se añade `ps2recomp-gs-presentation.patch` después del backend OpenGL, sin modificar el
parche importado ni los ámbitos EE/FPU/IOP/VIF/VU1 de la otra tarea.

La primera diferencia encontrada fue `preferredSource`: el GPU no respetaba la fuente
seleccionada por el frontend. Se corrige conservando sus unidades de **bloques de 256 B**,
distintas de las páginas de **8 KB** de DISPFB, con su formato, stride y origen. La prueba
usa una base no alineada a páginas y los cuatro formatos de color. Esa corrección no bastó
para la muestra del juego: la traza confirmó **dos circuitos activos y ninguna fuente
preferida**.

Un diagnóstico temporal comparó el compositor CPU con OpenGL sobre **la misma VRAM obtenida
del GPU**. El juego usa `PMODE=0x8023`, CT24 y modo de campos (`SMODE2 & 3 == 1`), con un
desplazamiento vertical de una fila entre circuitos. El CPU seleccionaba y duplicaba las
filas del campo par/impar; el shader omitía esa paridad. Así se localiza una diferencia
en presentación sin atribuirla a VU1 ni a ceros de los vértices.

El shader incorpora el campo seleccionado por `vsyncTick & 1`, incluyendo la paridad en
la clave de presentación compartida. En modo progresivo no se fuerza alternancia. También
se corrige la salida de un solo circuito para mostrar su RGB sin mezclar contra el fondo
por el alfa del píxel. El readback diferido conserva la fuente y el destino de cada imagen.
Los diagnósticos temporales se retiraron tras localizar la causa.

Las dos pruebas GPU fallan antes de los arreglos (**472/474**) y pasan después (**474/474**),
tanto con compute como con rasterizado gráfico. Comparan campos par/impar y modo progresivo,
alfa cero, selección de fuente y píxeles completos con el CPU. Incluyen los registros de
temporización de GoW con un patrón sintético **512×448**, sin datos del juego. Los 16 parches
aplican en un árbol aislado y sus 61 fuentes comparadas coinciden con el runtime local.

La reconstrucción completa del arreglo regenera las 6418 unidades y enlaza correctamente.
En una ejecución separada de 155 s, OpenGL se inicializa en la RX 5700 XT sin fallback y
alcanza el estado 11. Las cuatro capturas de `70–130 s` son distintas; siguen mostrando
agua oscura, sin Kratos ni el entorno completo. Son resultados anteriores a la integración
de EE/FPU: no se atribuye ese cambio visual a los arreglos posteriores de Opus.

Antes de publicar se integra `main` actualizado por Opus (`d3fcfa9`, con
`ps2recomp-ee-fixes.patch`). Se conservan ambos parches y se reconstruyen de nuevo las
6418 unidades. La suite nativa combinada pasa **481/481**, incluidas las dos pruebas GPU
reales; las pruebas separadas de caché GS pasan **45/45**. Los **17 parches** aplican en
orden y las **65 fuentes** comparadas coinciden con el runtime local. Configuración y
handlers sin errores (cuatro avisos conocidos); nueve scripts sin errores de sintaxis.

La ejecución combinada de 155 s, con diagnósticos de posiciones y render activados,
inicializa OpenGL sin fallback y alcanza el estado 11. Guarda tres capturas tardías
distintas a `94,85 / 95,19 / 110,10 s`; no llega a guardar la cuarta antes del límite.
Se ve agua y algunos artefactos, sin Kratos ni el escenario completo. Esa ejecución con
diagnósticos no es una medida de rendimiento y no cambia la comparación inicial de FPS.

La sonda registra **64 inicializaciones, 298 retornos y 128 lecturas posteriores**:
las 14 direcciones del caller `0x12E258` conservan la plantilla `(0,0,0,0x8000)` en
112 lecturas; las dos de `0x1FB800` tienen XYZ no nulo y cambiante en las otras 16.
Los arreglos EE/FPU no eliminan esa plantilla deliberada del loader. En el snapshot VU1
del estado 11, los 16 floats de la matriz en `0x1060` son finitos; esta comprobación
de una matriz no certifica todas las transformaciones. Sigue pendiente correlacionar
los buffers escritos por sus productores con VIF/VU1 y los triángulos recibidos por GS.
Los snapshots y las capturas permanecen en `logs/`, ignorados por Git.

### Procedencia de posiciones y paquetes PATH1 (2026-10-05)

Se sigue el recorrido RAM → DMA/VIF → VU1 → GIF sobre `12d5da0`, con los arreglos EE/FPU
de Opus ya integrados. Dos ejecuciones instrumentadas de **165 s y 105 s** llegan al
estado 11 con OpenGL. Las sondas locales conservan los primeros ocho streams VIF1,
48 estados de entrada de VU1 y 256 paquetes PATH1 completos de ese estado. La segunda
ejecución observa además la procedencia de cada tramo DMA, sin cambiar sus datos ni
la ejecución de EE/FPU/IOP. Esas sondas y el test de replay se retiran al terminar;
los volcados permanecen exclusivamente en `logs/`.

En el stream VIF1 número 1, de **481.064 B**, el comando `0x6C788002` en `0x62104`
desempaqueta 120 vectores V4-32. Su payload en `0x62108` ya contiene 120 copias de
`(0,0,0,0x8000)`. La traza DMA lo sitúa en RAM **`0x812390`**: el tramo empieza en
`0x620E8`, procede de `0x812370` y contiene 3.904 B. Esa dirección es exactamente la
devuelta al caller `0x12E258` de `LoadClient`, para el objeto `0x8084C0`, chunk 0,
buffer 1. Se vincula así la plantilla con su origen, sin deducirlo solo de su contenido.

| Payload en el stream 1 | Dirección RAM | Caller observado | Chunk / buffer |
|---|---|---|---|
| `0x62108` | `0x812390` | `0x12E258` | 0 / 1 |
| `0x6BAD0` | `0x7F3220` | `0x12E258` | 0 / 1 |

Hay ocho payloads de ese tamaño y con esa plantilla en el stream 1; reaparecen con
los mismos orígenes en los streams 3, 5 y 7. Las lecturas observadas en VU1, PC byte
`0x3240`, también encuentran la plantilla en memoria de datos antes de transformarla.
Los ceros de estas muestras ya existen antes del UNPACK: no los introduce el renderer
GS. Esto no demuestra que todos esos buffers deban contener geometría visible ni
descarta problemas posteriores de selección o transformación.

En cambio, las direcciones no nulas `0x7FCEB0` y `0x81C020`, actualizadas por `0x1FB800`,
no aparecen como origen de payload en las ocho cadenas DMA muestreadas. La muestra
es limitada; todavía hay que identificar su selección y envío antes de vincularlas
con un paquete de salida. No se fuerza un cambio de buffer ni se escriben posiciones.

El inspector nuevo, `tools/gs/inspeccionar_paquetes.py`, valida límites de etiquetas y
payloads y cuenta XYZ, ADC/XYZ3 y rangos de coordenadas. Ambas capturas PATH1 dan
**2.654 vértices: 337 con kick y 2.317 sin kick**, en 256 paquetes; 220 no contienen XYZ.
Un kick solicita dibujo, pero no equivale por sí solo a un triángulo válido. Los paquetes
252 y 254 tienen 120 XYZ idénticos cada uno, con ADC activo en todos ellos. Otros paquetes
tienen posiciones distintas y kicks habilitados. El descarte de esta muestra ya figura
en la salida de VU1, antes de procesarla el backend GS; no se ha demostrado que todos
esos descartes sean incorrectos ni que expliquen por sí solos la escena ausente.

Una reproducción local desde el estado de entrada VU1 número 5 genera exactamente el
paquete original número 11: SHA-256
`3c6dab3532d876d6b914213fc96cb89af6cfdf92697d6fb0051532b82dff57cb4`.
La suite con ese test temporal pasa **480/480** (479 normales y el replay, sin las dos
pruebas GPU). Esto permite reproducir el resultado del intérprete; no certifica su
equivalencia con hardware PS2. La traza Q muestra divisiones y consumos posteriores;
el valor inicial Q=2 observado antes de DIV no prueba que la perspectiva esté detenida.

El inspector incluye ocho pruebas sintéticas de disposición PACKED/REGLIST/A+D,
ADC frente a fog/XYZ3, PRE, NREG=0, IMAGE, padding y truncamiento; se ejecutan también
en CI. No incluye datos del juego. Uso y alcance: [`RENDERIZADO.md`](RENDERIZADO.md).
El siguiente paso es correlacionar un paquete no degenerado descartado con sus entradas
de transformación/CLIP y seguir el envío de los buffers actualizados. No se publica
un arreglo de comportamiento con esta investigación ni se acredita una escena 3D completa.

Tras retirar las sondas se recompilan sus fuentes y se enlazan de nuevo los ejecutables
del juego y de pruebas; ninguno conserva las opciones temporales de captura/replay.
La suite nativa vuelve a pasar **481/481**, incluidas las dos pruebas GPU reales.
Los 17 parches aplican y las 65 fuentes auditadas coinciden con el runtime local.
El inspector pasa 8/8, configuración y handlers no tienen errores (cuatro avisos
conocidos), los nueve scripts PowerShell y libpad2 pasan sus comprobaciones.

### Ampliación de la procedencia y recorte VU1 (2026-10-06)

Una ejecución de 175 s con `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1`, OpenGL y sondas temporales
alcanza el estado 11. Amplía la muestra a **128 cadenas VIF1 y 15.798 tramos DMA**.
Ningún payload observado incluye `0x7FCEB0` o `0x81C020`, los dos buffers con XYZ cambiante.
Sus objetos (`0x7FCCC0`, `0x81BE30`) mantienen `updated=0`, `rendered=1`, `view=1` en
las 128 muestras. Ambos buffers DMA son no nulos. Es una observación de esta muestra,
no una prueba de que nunca se envíen ni de que deban dibujar una parte concreta de la escena.

La inspección del MIPS de `renEEPrimContext::ProcessServer` (`0x141B78`) sitúa la selección
en `0x141C18–0x141C34`: lee el índice actualizado de `objeto+0x146`, selecciona el DMA
y lo copia a `objeto+0x147` antes del filtro de vista del objeto. Falta observar si el
contexto recorre esos objetos y qué filtros aplica; no se fuerza el intercambio de buffers.

La traza del replay VU1 número 5 observa los operandos **después del stall de emisión**.
Conserva el SHA-256 del paquete original número 11 y registra 1.576 pares de instrucciones.
Los 86 CLIP se reparten entre PC byte `0xD28` y `0xD30`; FT.w es negativo en todos
(-427,592 a -75,934). Se ven cambios de CLIP con su latencia. Esto no demuestra un fallo
del recorte: primero hay que comprobar el espacio y el signo esperados de la transformación.
Los enteros empaquetados que se muestran como NaN al leerlos como floats tampoco prueban
un error de posiciones. Las sondas y el replay se retiran; los datos quedan en `logs/`.

### Continuación DIRECT y separación de IMAGE/VIF (2026-10-06)

Se integra en un parche propio la corrección de Claude
[`540defd`](https://github.com/KIexster/god-of-war-recomp/commit/540defd), sin incorporar
los cambios EE/IOP de su rama. Antes, una IMAGE pendiente de GIF PATH2 consumía los comandos
VIF que seguían al DIRECT como si fueran píxeles. Ahora solo toma los payloads de los
siguientes DIRECT/DIRECTHL, mantiene MARK/STCYCL/ITOP y procesa los GIFtags posteriores
a la imagen. La prioridad corresponde al DIRECT actual. Dos pruebas antiguas se corrigen
porque esperaban píxeles sin el siguiente comando DIRECT.

La nueva regresión y esas dos pruebas fallan antes del arreglo (**477/480**) y pasan después
(**480/480**); al añadir la prueba de prioridad, la suite normal pasa **481/481**.

Se detecta además que DIRECT recortaba su tamaño al bloque disponible y perdía el resto.
`ps2recomp-vif-direct-fragments.patch` conserva el payload incompleto y DIRECTHL entre
bloques, sin copiar los payloads completos y con un límite de 1 MiB. Seis regresiones nuevas
fallan sin ese cambio (**481/487**) y pasan con él. Incluyen todos los cortes de byte de
PACKED/REGLIST de 32 B, FIFO, IMAGE con comprobación de VRAM, prioridad, IMMEDIATE=0 y reset.
La suite con OpenGL real pasa **489/489**. Los **19 parches** aplican y sus **67 fuentes**
auditadas coinciden con el runtime local. Configuración y handlers sin errores (cuatro
avisos conocidos), inspector GIF 8/8 y scripts PowerShell sin errores de sintaxis.

Alcance, referencia primaria, crédito y diagnóstico opcional: [`RENDERIZADO.md`](RENDERIZADO.md#transferencias-direct-de-path2).
La reconstrucción completa regenera las **6.418 unidades** y termina correctamente. Tras ella,
la suite nativa vuelve a pasar **489/489**, incluidas las dos pruebas GPU. Libpad2 también pasa.
Una partida de **175 s**, con `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1` y `GOW_VIF_DIAG=1`,
inicializa OpenGL en la RX 5700 XT sin fallback y llega al estado 11 con `pending=0`,
`levelReady=1` y `flashReady=1`. Guarda dos capturas tardías distintas a **90,27 y 110,04 s**;
no guarda la de 130 s antes de terminar. Se ve agua oscura, sin Kratos ni el escenario completo.

No aparecen mensajes `[gow-vif-direct]` en esa ejecución: **no se observan DIRECT truncados**
en la muestra. Las regresiones demuestran los defectos del runtime, pero esta prueba no prueba
que hayan causado la escena ausente ni permite atribuirles una mejora visual o de FPS.
Las capturas y registros permanecen en `logs/`; las sondas temporales de geometría ya no están
en el ejecutable reconstruido. El siguiente paso es observar la membresía de los buffers
actualizados en `renEEPrimContext::ProcessServer`.

### Pertenencia al contexto de render (2026-10-06)

Se amplía el diagnóstico opcional `GOW_EE_PRIM_DIAG=1` para observar la lista de
`renEEPrimContext::ProcessServer` a la entrada, sin escribir memoria ni cambiar la
ejecución original. La reconstrucción de `src/` termina correctamente. Se registran
hasta 64 entradas antes del estado 11 y otras 64 en él, con 256 nodos como máximo por
entrada y detección de punteros fuera de RAM, ciclos y truncamiento.

Una ejecución de **175 s** con OpenGL, `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1` y mando
automático sin capturas alcanza el estado 11. Las **64 muestras** de ese estado pertenecen
al contexto `0x7B8DC0`: vista `0x75CD70`, ID `0x45`, máscara de contexto `0x3` y cámara
`0x7A3950`. Su lista contiene **dos objetos** y termina sin ciclo, puntero inválido ni
truncamiento. Ambos pasan los primeros filtros observados; eso no acredita dibujo ni
los filtros de material y transformación posteriores.

Los objetos `0x7FCCC0` y `0x81BE30`, actualizados por el caller `0x1FB800`, **no pertenecen
a esa lista en ninguna de las 64 muestras**. Sus enlaces `objeto+8` son cero y conservan
`updated=0`, `rendered=1`. El productor sigue obteniendo ambos buffers con XYZ cambiante.
Esto explica por qué ese contexto no alterna sus índices en la muestra; no demuestra
que deban estar registrados en él ni que su ausencia cause la falta de Kratos.

El siguiente paso es identificar quién crea y registra esos clientes, y correlacionar
los dos objetos que sí recibe el contexto con las entradas VU1. No se fuerza su registro
ni el cambio de buffer. Los resultados permanecen en `logs/`. La CI del commit VIF
`f5711bd` pasa tanto las comprobaciones rápidas como la compilación y suite Linux del runtime:
[ejecución 37457211736](https://github.com/KIexster/god-of-war-recomp/actions/runs/37457211736).

### Orden FIFO y DIRECTHL en el GIF (2026-10-06)

La comparación de `GifArbiter::drain` mezclaba la prioridad numérica del path con una
excepción DIRECTHL/IMAGE dentro de `std::stable_sort`. DIRECT y DIRECTHL del mismo path
resultaban equivalentes, pero tenían relaciones distintas con una IMAGE de PATH3: el
comparador no era un orden débil estricto. En las regresiones, esto permite cambiar el
orden de un mismo canal o servir DIRECTHL antes de la IMAGE pendiente.

`ps2recomp-gif-order.patch` agrupa solo por path, manteniendo la estabilidad, y arbitra
entre las cabeceras de PATH2/PATH3 después de PATH1. La excepción ya no entra en el
comparador de ordenación. Conserva también los paquetes añadidos por un callback para
procesarlos en la siguiente tanda. No cambia los backends CPU/OpenGL ni la semántica EE/IOP.

Las dos regresiones prueban todas las permutaciones de DIRECTHL/DIRECT/IMAGE y de
DIRECTHL/setup/IMAGE. Fallan antes (**487/489**, suite normal) y pasan después. La suite
con las dos pruebas OpenGL reales pasa **491/491**. Los **20 parches** aplican en orden
y sus **68 fuentes** auditadas coinciden con el runtime local. Alcance y referencia:
[`RENDERIZADO.md`](RENDERIZADO.md#orden-de-los-paquetes-gif).

La CI del diagnóstico de contexto `f8a851a` también pasa:
[ejecución 37458210600](https://github.com/KIexster/god-of-war-recomp/actions/runs/37458210600).
La reconstrucción completa regenera las **6.418 unidades** y termina correctamente. Tras
ella, la suite vuelve a pasar **491/491**, incluidas las dos pruebas OpenGL, y una nueva
auditoría confirma las **68 fuentes** de los **20 parches** sin diferencias.

Una partida de **175 s** con OpenGL, `GOW_SKIP_FMV=1`, `GOW_FAST_BOOT=1`,
`GOW_EE_PRIM_DIAG=1` y `GOW_ANM_DIAG=1` inicializa la RX 5700 XT sin fallback y alcanza
el estado 11 con `pending=0`, `levelReady=1` y `flashReady=1`. Las capturas tardías de
**110,19 y 130,27 s** son distintas y muestran agua oscura; siguen ausentes Kratos y el
escenario completo. Las **64 muestras** de contexto repiten la lista válida de dos objetos
y la ausencia de `0x7FCCC0`/`0x81BE30`. No se atribuye al nuevo orden una mejora visual ni
de FPS. Capturas y registros permanecen en `logs/`.

La CI del arreglo GIF `701da8d` pasa:
[ejecución 37461636026](https://github.com/KIexster/god-of-war-recomp/actions/runs/37461636026).

El control de **600 s** sin `GOW_FAST_BOOT`, con el mismo ejecutable, `GOW_SKIP_FMV` y
las mismas sondas, muestra avance de la introducción hasta **11,75 s** de animación en
los mensajes conservados y después llega al estado 11. Las **64 muestras** repiten el
contexto, cámara y lista válida de dos objetos; `0x7FCCC0` y `0x81BE30` siguen ausentes.
Las capturas de **360,28 y 480,20 s** son distintas y muestran agua oscura, sin Kratos.
Este control no aporta evidencia de que el arranque acelerado cause esa ausencia en
el contexto observado. No acredita el registro de todos los demás objetos del nivel
ni permite comparar FPS bajo diagnóstico.

### Efectos de las etiquetas GIF vacías (2026-10-06)

Al revisar el parser se detecta que aplicaba PRE y reiniciaba Q aunque `NLOOP=0`.
Aplicar PRIM también descartaba los vértices pendientes, incluso con la misma topología.
REGLIST e IMAGE aplicaban indebidamente PRE. Se corrigen el parser general y la ruta
PACKED nativa en `ps2recomp-gif-tag-semantics.patch`, conservando el frontend común a CPU
y OpenGL. El atajo de subida IMAGE omitía a su vez PRE del setup PACKED y el reinicio de
Q de las etiquetas no vacías; se corrige sin cambiar los bytes de la imagen.

Las tres primeras regresiones fallan antes (**489/492**, suite normal). Tras esos arreglos,
la nueva regresión de la subida IMAGE todavía falla (**492/493**), antes de corregir ese
atajo. Cubren ambas rutas, etiquetas vacías con y sin PRE entre vértices, Q, modos que
ignoran PRE y controles no vacíos. Alcance y referencia primaria:
[`RENDERIZADO.md`](RENDERIZADO.md#etiquetas-gif-vacías-y-pre).

La revisión de las dos capturas locales anteriores de 256 paquetes PATH1 encuentra en
cada una **205 etiquetas vacías, 90 con PRE=1 y PRIM=0x5C**, sin truncamientos de paquete.
Es el mismo caso que el arreglo convierte en una etiqueta sin emisiones al GS; eso no
demuestra por sí solo que causara la escena ausente. La suite con OpenGL real pasa
**495/495**. Los **21 parches** aplican y sus **68 fuentes** auditadas coinciden con el
runtime local. Configuración/handlers sin errores (cuatro avisos conocidos) y PowerShell
sin errores de sintaxis. La reconstrucción completa regenera las **6.418 unidades** y
termina correctamente. Tras ella, la suite vuelve a pasar **495/495** y la nueva auditoría
confirma las **68 fuentes** de los **21 parches** sin diferencias.

La partida de **175 s** con las mismas opciones OpenGL/SKIP_FMV/FAST_BOOT y sondas de
contexto/animación inicializa el rasterizado de hardware en la RX 5700 XT sin fallback y
llega al estado 11 con `pending=0`, `levelReady=1` y `flashReady=1`. Las capturas de
**110,24 y 130,14 s** muestran agua oscura y son distintas, pero siguen ausentes Kratos
y el escenario completo. Las **64 muestras** conservan la lista válida de dos objetos y
los buffers dinámicos fuera de ella. El arreglo corrige los efectos de las etiquetas;
esta ejecución no acredita una mejora visual ni de FPS. Los datos del juego permanecen
en `logs/`.

### Identificación del productor de los buffers dinámicos (2026-10-06)

El MIPS retail de `0x1FA8A8` llama a `0x1FB4B8` con cinco vectores y después a
`attachment::tChained::Connect` (`0x1FCD48`, nombre del mapa de símbolos) y a otra rutina
con cuatro vectores. La rutina de cinco vectores obtiene tipos 3 y 0 del mismo `renEEPrim`,
elige el índice opuesto al mostrado y escribe siete coordenadas UV con las mismas
constantes que `attachment::tChained::DrawGapFiller` en la referencia GoW 2 con símbolos.

Estas coincidencias vinculan probablemente los buffers de `0x1FB800` con el relleno de
las cadenas de los attachments. No confirman el nombre retail ni que esos objetos deban
registrarse en el contexto observado. Las estructuras difieren entre versiones; no se
cambia `funcmap.csv` ni se sustituye código del juego. El cuerpo del escenario y de Kratos
debe seguirse también por la ruta de modelos. Se localiza `renModelServer::ProcessServer`
en `0x159C58` (nombre del mapa): selecciona un contexto de una tabla y llama a su método
virtual antes de enviar la cadena DMA. El siguiente diagnóstico observará esa selección
y el descarte de modelos, conservando la ejecución original.

### Selección del contexto por el servidor de modelos (2026-10-06)

Se añade `GOW_MODEL_DIAG=1` como observación opcional de `0x159C58`. La recompilación de
`src/` termina correctamente y PowerShell pasa sin errores. La sonda conserva los
checkpoints y llama siempre al original; no escribe registros ni memoria del juego.
El perfil elimina la variable. Alcance: [`RENDERIZADO.md`](RENDERIZADO.md#selección-del-contexto-de-modelos).

Una partida de **175 s** con OpenGL, SKIP_FMV, FAST_BOOT y las sondas de contexto/animación
registra **64 muestras en el estado 3 y 64 en el estado 11**. Todas observan el servidor
`0x59D878`, tabla `0x59DBA8`, grupo/slot `0/0`, array `0x59DBC0`, contexto `0x59DDC8`
y tabla virtual `0x2C2468`, con punteros dentro de RAM. El ajuste de `this` es cero y el
destino seleccionado es `0x1511F0`, identificado por el mapa como
`renGROBMasterContext::ProcessServer`. La referencia GoW 2 también llama a un contexto
maestro GROB desde esta ruta: el destino observado no demuestra una selección incorrecta.

Las capturas de **110,16 y 130,04 s** vuelven a mostrar agua oscura, sin Kratos ni el
escenario completo. Los registros mantienen `pending=0`, `levelReady=1` y `flashReady=1`.
La observación de entrada no certifica las llamadas posteriores ni el culling de los
modelos. El siguiente paso es seguir los contextos e instancias que recorre ese maestro,
y correlacionar sus descartes con los paquetes VU1. Capturas y registros siguen en `logs/`.

La CI del arreglo de etiquetas `f385fcc` pasa:
[ejecución 37465434359](https://github.com/KIexster/god-of-war-recomp/actions/runs/37465434359).

### Recorrido real del maestro GROB y listas de modelos (2026-10-06)

Se amplía `GOW_MODEL_DIAG=1` para observar la entrada del maestro `0x1511F0`, las
listas de `0x159878` y las llamadas a `0x157A60`. El mapa retail deja estas dos últimas
como funciones sin nombre; su estructura coincide respectivamente con
`renModelServerContext::ProcessServer` y `ProcessModel` en la referencia GoW 2.
Los offsets de los filtros se comprueban en el MIPS retail, sin copiar su código
generado. Alcance y límites: [`RENDERIZADO.md`](RENDERIZADO.md#selección-del-contexto-de-modelos).

La primera prueba de **175 s** confirma que el maestro es compartido por varios
servidores. Se limita después cada contexto por separado para que otros servidores
no agoten las muestras de modelos. La segunda prueba, también de **175 s**, registra
en el estado 11 cuatro contextos activos de modelos. `0x1111B98` contiene **14 modelos**:
uno no pasa la máscara de vista, ocho son candidatos al árbol estático y cinco a la
llamada directa. Los otros contextos contienen **1, 1 y 2 modelos**, todos candidatos
a la llamada directa en las muestras observadas. Se verifican **64 entradas reales**
a la rutina de procesamiento en esta fase, repartidas entre nueve modelos distintos,
con un grupo cada uno. Las listas observadas no presentan ciclos, punteros inválidos
ni truncamientos.

Durante las primeras 64 muestras del maestro de modelos, la lista crece de ocho a
trece contextos y después queda en once, con tres activos. El contexto de 14 modelos
se observa en **21 llamadas** antes de esa reducción. Es una transición del estado
observado; no identifica por sí misma un fallo de registro ni cuáles son los modelos
de Kratos. Las capturas de **110,25 y 130,21 s** continúan mostrando agua oscura sin
Kratos ni el escenario completo. No se fuerzan registros, visibilidad ni índices.

La siguiente observación registra la visibilidad raíz del esqueleto y el retorno de
`renView::Clip` procedente del procesamiento de modelos. Una entrada en esa rutina
todavía no prueba que el modelo pase sus filtros internos ni que emita geometría.

### PEXEW duplica Y en la Z de las esferas de visibilidad (2026-10-06)

La tercera partida de **175 s** añade la observación de visibilidad y Clip. Las **64
entradas de procesamiento** en el estado 11 tienen raíz de esqueleto válida y visible,
y el primer bloque de visibilidad de grupos vale `0xFFFFFFFF`. En las **64 llamadas
observadas a Clip**, correspondientes a siete modelos distintos, los cuatro argumentos
son finitos, Y y Z tienen los mismos bits y el retorno real es **`0x80000000`**, descarte.
Antes del estado 11 se registran 49 descartes y 15 retornos `0x20`. Estos límites no
cubren todos los modelos ni todos los descartes de la escena.

Se localiza una causa concreta de los argumentos duplicados: en `0x157F94`, PROT3W
extrae Y para `f13`; en `0x157FA0`, PEXEW debería extraer Z para `f14`. La macro actual
`PS2_PEXEW` usa `_MM_SHUFFLE(2,3,0,1)`, que copia también Y a la palabra baja.
Una reproducción nativa aislada con palabras **[11,22,33,44]**, ajena al juego, confirma
la permutación incorrecta. También detecta que PROT3W rota las cuatro palabras, cuando
debería conservar la cuarta. Se contrasta la semántica con
[PEXEW y PROT3W de PCSX2, commit 32ac6e2](https://github.com/PCSX2/pcsx2/blob/32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e/pcsx2/MMI.cpp#L1435).

| Instrucción | Resultado actual, de palabra baja a alta | Resultado esperado |
|---|---|---|
| PEXEW | [22,11,44,33] | [33,22,11,44] |
| PROT3W | [22,33,44,11] | [22,33,11,44] |

**Resuelto en `ps2recomp-mmi.patch` (ver "Auditoría de las instrucciones MMI").** Pendiente original: corregir PEXEW en `ps2_runtime_macros.h`
(`_MM_SHUFFLE(3,0,1,2)`) y PROT3W tanto allí como en la emisión de
`mmi_translation_helpers.cpp` (`_MM_SHUFFLE(3,0,2,1)`), con regresiones de las cuatro
palabras, alias origen/destino y registro cero. PROT3W se emite en línea y requiere
regenerar las funciones; cambiar solo la macro no corrige el ejecutable. Este turno
no modifica el recompilador, FPU, IOP ni los parches de EE.

La macro incorrecta explica la Z mal extraída; todavía no se ha probado cuánto cambia
el descarte ni la imagen tras corregirla. Las capturas de **110,04 y 130,22 s** siguen
mostrando agua sin Kratos ni el escenario completo, con OpenGL de hardware y estado 11.
Las sondas compilan en Windows y los datos/reproducciones quedan en `logs/`. La siguiente
prueba de render debe repetir estas sondas tras integrar el arreglo EE y después seguir
los modelos que pasen Clip hasta las partes y los paquetes VU1.

### Continuaciones GIF y equivalencia del atajo DMA (2026-10-06)

Se añaden cuatro parches al final de la lista de compilación, sin modificar los parches
del EE, la FPU, el recompilador o el IOP:

| Parche | Cambio comprobado |
|---|---|
| `ps2recomp-gif-stream.patch` | Cursores PACKED/REGLIST/IMAGE por PATH; conserva registros, Q, padding y pixels entre bloques y DIRECT distintos; VIF entrega bytes originales sin wrappers IMAGE. |
| `ps2recomp-gif-image-order.patch` | DIRECTHL reconoce continuaciones IMAGE y etiquetas tras setup; no confunde registros o relleno con etiquetas ni bloquea por una IMAGE vacía. |
| `ps2recomp-gif-image2.patch` | FLG=3 consume el payload IMAGE2 en las rutas general/nativa y conserva su clasificación en el árbitro. |
| `ps2recomp-gif-native-tag.patch` | El atajo DMA de texturas conserva PRE del setup, reinicia Q y acepta IMAGE2 después de validar toda la cadena; rechazo sin efectos en el GS. |

Los fallos se reproducen antes de corregir cada tema: **4** pruebas de fragmentación,
**4** de clasificación, **3** de IMAGE2 y **1** del estado del atajo DMA. Se añaden
**20 regresiones** en total, con controles de reset, PATH intercalados, NREG=0 y cadena
rechazada. La suite nativa pasa **515/515**, incluidas dos pruebas con OpenGL real.
Se ajusta la expectativa de un wrapper IMAGE antiguo y cuatro fixtures de prioridad
que usaban imágenes vacías; las razones se detallan en
[`RENDERIZADO.md`](RENDERIZADO.md#continuidad-del-flujo-gif-por-path).

La auditoría aplica **25 parches** sobre el commit fijado y compara **71 fuentes**,
sin diferencias respecto al árbol probado, también después de la compilación completa
con **6.418 unidades generadas** y resultado cero. Se repite la suite **515/515** con
OpenGL real. Una partida de **175 s** con SKIP_FMV, FAST_BOOT y las sondas de modelos
llega al estado 11, `pending=0`, `levelReady=1` y `flashReady=1`, sin fallback CPU.
Las capturas de **90,13 y 110,09 s** muestran agua, sin Kratos ni el escenario completo.
Las **64 llamadas observadas a Clip** en esa fase siguen descartando los modelos con
`0x80000000`; Y y Z mantienen los mismos bits y los argumentos son finitos.

No se acredita una mejora de FPS ni la aparición de Kratos. El arbitraje sigue trabajando
con bloques completos, sin reproducir todos los ciclos o preempciones del hardware.
Las posiciones y los descartes de modelos deberán repetirse tras el arreglo MMI pendiente
en el EE. Durante la validación se reproduce otro problema separado en CPU y OpenGL:
48 bytes CT24 juntos producen 16 pixels, pero en tres bloques de 16 B producen solo 15
y dejan la transferencia abierta. Se continúa con la conservación de ese pixel parcial;
los datos sintéticos y las capturas permanecen en `logs/`.

La CI de `1f009b4` pasa:
[`Pruebas`, ejecución 37497401093](https://github.com/KIexster/god-of-war-recomp/actions/runs/37497401093).

### Pixels CT24/Z24 divididos entre cargas IMAGE (2026-10-06)

`ps2recomp-gs-image-fragments.patch` conserva como máximo dos bytes pendientes por
backend. Completa el pixel con la carga siguiente y pasa el resto directamente a la
subida existente, sin retener una copia de la textura. Se limpia el acumulador al
reiniciar o empezar otra transferencia; exportar/importar el estado OpenGL lo conserva.
Los formatos distintos de CT24/Z24 siguen usando la ruta anterior.

La suite reproduce **tres fallos** antes del cambio: cargas CPU, cargas OpenGL y
exportación de un pixel parcial. Con el cambio pasan **519/519 pruebas**, incluidas
cuatro con OpenGL real. Se comparan VRAM completa y contador de pixels en todos los
cortes de una carga de 48 B, además de cargas repetidas de 1 B y 16 B, byte alto preservado
en CT24/Z24, reset/nueva transferencia y exportación/restauración. Las pruebas contienen
datos sintéticos. La auditoría aplica **26 parches** y reproduce exactamente **73 fuentes**.
La compilación completa termina con **6.418 unidades generadas** y código cero;
se repiten las **519/519 pruebas** con OpenGL real y la auditoría exacta de fuentes.
El control de partida de **175 s** llega al estado 11, `pending=0`, `levelReady=1`
y `flashReady=1`, sin fallback CPU. Las capturas de **90,15 y 110,13 s** siguen
mostrando agua sin Kratos ni el escenario completo. Las **64 llamadas observadas a Clip**
en el estado 11 descartan con `0x80000000`, con Y/Z idénticas y argumentos finitos.
Este arreglo corrige las cargas fragmentadas; no acredita mejora de FPS ni resuelve
el descarte de modelos que se investiga por separado en el EE.

La CI de `0a4f66c` pasa:
[`Pruebas`, ejecución 37501053476](https://github.com/KIexster/god-of-war-recomp/actions/runs/37501053476).

### Centros y bordes de triángulos en el renderer CPU (2026-10-06)

`ps2recomp-gs-triangle-sampling.patch` comparte con OpenGL las reglas de triángulos
adaptadas del fork SotC: centro entero, XYOFFSET completo 12.4 y borde compartido
dibujado una sola vez. El CPU anterior desplazaba medio pixel la muestra, truncaba
el offset y aceptaba ambos lados de una arista. Tres regresiones reproducen esos
fallos; OpenGL compute/hardware ya las pasaban. Ahora pasan **523/523 pruebas**,
incluidas cinco con OpenGL real. Se ajustan tres fixtures antiguos por las razones
documentadas en [`RENDERIZADO.md`](RENDERIZADO.md#triangulos-cpu-como-referencia-para-opengl).

La comparación independiente de VRAM completa en **48 casos** de triángulos planos/IIP,
cuatro modos de prueba Z y valores Z32 `7`, `0x80000001` y `0xffffff01`, en las dos
rutas OpenGL, pasa de **12 diferencias** a **cero**. Esto mejora la referencia CPU para
comparar el renderer GPU; no prueba que todos los efectos GS sean equivalentes.
La compilación completa termina con **6.418 unidades generadas** y código cero;
se repiten las **523/523 pruebas** con OpenGL real. La auditoría reproduce **27 parches
y 74 fuentes** exactamente. El control de partida de **175 s** llega al estado 11,
`pending=0`, `levelReady=1` y `flashReady=1`, sin fallback CPU. Las capturas de **90,02
y 110,00 s** siguen mostrando agua sin Kratos ni el escenario completo; las 64 llamadas
observadas a Clip en esa fase mantienen descarte `0x80000000`, Y/Z idénticas y valores
finitos. La comparación sintética mejora; la partida jugable y los FPS quedan sin acreditar.

También se revisa [Tobiichi-Port en `9f02797f`](https://github.com/YYOzcan/Tobiichi-Port/tree/9f02797f8ab7481fddad4d2daf7afad82d11699f).
Los cinco archivos GS/VIF/VU1 comparados coinciden con nuestro runtime base fijado.
Su README mantiene menú y partida pendientes; los atajos GoW de arranque no se
incorporan como solución de renderizado. Se documenta la revisión sin afirmar que
su ejecutable se haya probado aquí.

La CI de `5ada6aa` pasa:
[`Pruebas`, ejecución 37504095195](https://github.com/KIexster/god-of-war-recomp/actions/runs/37504095195).

### Cobertura e interpolación de sprites CPU (2026-10-06)

`ps2recomp-gs-sprite-sampling.patch` conserva las fracciones de XYOFFSET/UV y comparte
con OpenGL los ejes firmados del fork SotC. El CPU deja de dibujar áreas vacías y
mantiene el origen de textura al invertir los ejes o recortar con scissor. Cuatro
regresiones reproducen los fallos antes del arreglo. La comparación sintética de
VRAM completa pasa de **14 diferencias a cero en 16 casos** con compute/hardware;
la suite pasa **528/528**, incluidas seis pruebas con OpenGL real.

Se ajustan ocho fixtures antiguos que dibujaban sprites vacíos: pasan a usar un
rectángulo de 1×1 conservando sus comprobaciones de alias CT32, CLUT, alpha y scissor.
La prueba nueva verifica que ancho/alto cero no cambie ningún byte de VRAM. Los
motivos y la procedencia se detallan en
[`RENDERIZADO.md`](RENDERIZADO.md#sprites-cpu-como-referencia-para-opengl).
La compilación completa termina con **6.418 unidades generadas** y código cero;
se repiten las **528/528 pruebas** con OpenGL real. La auditoría reproduce **28 parches
y 74 fuentes** exactamente. El control de partida de **175 s con el renderer CPU**
llega al estado 11, `pending=0`, `levelReady=1` y `flashReady=1`.
Las capturas de **90,18 y 110,11 s** siguen mostrando agua sin Kratos ni el escenario
completo, y las 64 llamadas observadas a Clip en esa fase descartan con `0x80000000`,
con Y/Z idénticas y argumentos finitos. El mismo bloqueo se observa con CPU y OpenGL;
estos controles no acreditan una partida jugable ni una mejora de FPS.

### Interpolación de atributos constantes y alpha-test (2026-10-06)

`ps2recomp-gs-triangle-constants.patch` calcula RGBA Gouraud y F por diferencias
entre vértices en CPU y OpenGL compute/hardware. La suma redondeada de los pesos
reducía valores constantes; alpha 128 podía quedar en 127 y fallar GEQUAL 128,
dejando huecos en el triángulo. En la sonda de 17×19 pixels fallan 17 centros de
color y 8 de niebla en CPU, y 151/110 en cada ruta OpenGL. Para F se usa como
referencia un punto con los mismos atributos, sin interpolación.

Dos pruebas CPU y una con OpenGL real reproducen el fallo antes del cambio; después
pasan **531/531 pruebas**, incluidas siete con OpenGL. Se comparan los centros
interiores y ambos sentidos de giro; la prueba de color activa GEQUAL 128 para
detectar también los huecos. La auditoría reproduce **29 parches y 74 fuentes**.
La sonda independiente pasa **6/6 casos**: CPU, OpenGL compute y hardware, con color
o F constantes. La comparación de gradientes y profundidad conserva **48/48 casos**
iguales entre CPU y ambas rutas OpenGL. La compilación completa regeneró las 6418
unidades y terminó con código 0; la suite posterior vuelve a pasar **531/531**.

El control de 175 s usa OpenGL real, sin fallback CPU. Las capturas de **90,21 y
110,23 s** muestran agua sin Kratos; se alcanza el estado 11 con `pending=0`,
`levelReady=1` y `flashReady=1`. Las 64 llamadas observadas a Clip en esa fase siguen
descartando con `0x80000000`, argumentos finitos y Y/Z iguales. La corrección de
atributos constantes queda verificada; todavía falta la escena 3D completa.
Este control usa el IOP anterior al parche de aceleración incorporado por Opus;
la integración y su perfil se registrarán por separado.

La CI del parche anterior de sprites también terminó en verde:
[ejecución 37507078237](https://github.com/KIexster/god-of-war-recomp/actions/runs/37507078237).

### Rendimiento del intérprete del IOP (2026-10-06)

El perfil de la medición de rendimiento atribuye al IOP el 61 % del hilo del juego. Un IOP sin hilos
listos cuesta poco (unos 7 ms por segundo emulado, incluido el SPU2), así que ese tiempo es de hilos del
IOP ejecutando instrucciones. El intérprete hacía unos **55 M instrucciones/s** en la máquina de la CI;
el IOP real va a 36,8 MHz, por lo que un IOP ocupado necesita casi dos tercios de un núcleo para ir a
tiempo real. Con callgrind, cada instrucción emulada costaba unas 245 instrucciones del host.

`ps2recomp-iop-fast.patch` (tras `ps2recomp-gs-sprite-sampling.patch`) quita costes por instrucción sin
cambiar el comportamiento:

- La búsqueda de stubs de importación (`IopImportRegistry::decode`) se hacía en **cada** instrucción;
  ahora solo cuando la instrucción es `jr ra`, que es como empiezan los stubs.
- Lectura de instrucciones y cargas/escrituras en RAM con camino rápido en línea (`fetch32`, `load*`,
  `store*`); los registros de hardware, la scratchpad, el SPU2 y el SIO2 siguen por `read*`/`write*`.
  Las escrituras siguen marcando la RAM ocupada como antes.
- La comprobación de DMA pendiente es una marca en línea; `PS2X_IOP_PC_EVERY` se lee al crear el IOP en
  lugar de con un `static` local en cada instrucción; `physicalAddress` pasa a la cabecera.

Medido con callgrind (instrucciones del host para el mismo programa del IOP): bucle aritmético
737 → 452 M (−39 %), bucle con LW/SW 1513 → 907 M (−40 %), es decir, unas **1,65 veces más rápido**. La
nueva prueba "IOP fast loads and stores match the generic memory paths" fija que los accesos rápidos
equivalen a los genéricos (espejos KSEG0/KSEG1, marca de RAM escrita, registros de hardware y FIFO del
SIO2). La suite pasa **523/523** con los 29 parches.

Siguiente paso: averiguar qué hilos del IOP están ocupados en la partida. Si son bucles de espera
activa (sondeo de un registro o de memoria), saltarlos rendiría mucho más que acelerar el intérprete.
Para ello basta una ejecución con `PS2X_IOP_PC_EVERY=1000000`: el registro mostrará `[IOP:pc]` con los
PC más repetidos. **Falta medirlo con el juego:** repetir `scripts\probar_rendimiento.ps1` y comparar el
porcentaje del IOP y las llamadas a `vid::Flip` por segundo.

### Coordenadas constantes e integración del IOP rápido (2026-10-06)

Se integra `origin/main` con el parche IOP de Opus mediante merge, sin modificar su
implementación. Se conservan los dos registros de investigación y se ordena el IOP
rápido después de sprites y antes de los nuevos parches de atributos de triángulos.

`ps2recomp-gs-triangle-texcoords.patch` corrige UV/STQ constantes en CPU y ambas
rutas OpenGL. La regresión incluye Q=1,5: requiere también refinar el recíproco GPU,
porque el texel anterior se seleccionaba incluso en el primer centro. Antes fallan
las tres pruebas nuevas; después pasa la suite integrada **535/535**, incluidas
ocho pruebas con OpenGL real. Las restas de UV son firmadas y se conserva la
interpolación homogénea antes de dividir por Q.

La sonda independiente verifica **24/24 casos de atributos constantes**: UV o STQ
con Q=1,5, nearest/lineal, ambos sentidos y CPU/OpenGL compute/hardware. Conserva
otros 12 casos exploratorios con Q variable y S/T proporcionales a Q sobre fronteras
exactas de texel: todavía difieren del control constante, tanto en CPU como en GPU.
No se consideran resueltos por este parche. El gradiente de la regresión evita esas
fronteras y comprueba que se mantiene la división después de interpolar.

Las variantes hardware se compilan de forma asíncrona y pueden usar compute al
principio. La sonda espera de forma acotada y confirma cada dibujo hardware mediante
los contadores existentes: aumentan primitivas y batches sin aumentar tiles compute.
Así se verifican también los ocho casos constantes por la ruta hardware ejecutada,
no solo con esa ruta habilitada.

La auditoría reproduce **31 parches y 75 fuentes sin diferencias**; los 14 scripts
PowerShell se analizan sin errores. La compilación completa termina con código 0,
regenera las 6418 unidades y la suite posterior vuelve a pasar **535/535**.
El control adicional de RGBA/alpha-test y F pasa **6/6**, confirmando también hardware
con los contadores después de terminar las variantes asíncronas.

El primer control del juego quedó interrumpido al alcanzarse el límite de uso de
la revisión automática de aprobación; solo registró el arranque y no llegó a guardar
el control visual de la escena. Se repetirá tras incorporar las correcciones MMI y
VU0 publicadas por Opus durante esa pausa. El renderer sigue en estado parcial.

### VU0 en modo macro y cadenas DMA largas (2026-10-06)

`ps2recomp-vu0-macro.patch` (tras `ps2recomp-iop-fast.patch`) incorpora, con la autorización ya dada para el
fork de SotC, dos commits más que afectan al código del EE:

- **03d18df — VU0 en modo macro usa su memoria de datos.** `VLQI`/`VSQI`/`VLQD`/`VSQD` y `VILWR`/`VISWR`
  leían y escribían la **RAM del EE desde la dirección 0** (`READ128((vi & 0x3FF) << 4)`) en lugar de la
  memoria de datos de VU0 (`(vi & 0xFF) << 4` dentro de sus 4 KB); además `VSQI`/`VSQD` tenían intercambiados
  los campos Fs e It, y VI0/VF0 podían escribirse. En SotC esto rompía la pila de matrices
  (push/pop) y desaparecían los personajes. Si God of War usa esas instrucciones, estaba leyendo y
  pisando los primeros 16 KB de la RAM del EE.
- **e36fbf1 — cadenas DMA de más de 4096 tags.** El recorrido de cadenas se cortaba a los 4096 tags y
  perdía el final: el GIF quedaba en modo IMAGE y se tragaba la configuración A+D del cuadro siguiente.
  El límite pasa a 2^20 tags y avisa (`[dma] chain on ... stopped after ... tags`) si se alcanza. El mismo
  commit corrige `VRNEXT`/`VRINIT`/`VRXOR`/`VRGET` (LFSR del registro R), `VFTOI` (saturación) y `VABS`
  (denormales), y comparte el registro R de VU0 entre hilos en `EeScheduler`. La herramienta opcional
  `vu0_audit` del fork no se incorpora (depende de su renderer de referencia).

La suite pasa **528/528** con los 30 parches (pruebas del fork que decodifican las instrucciones
`vsqi`/`vlqd`, cadena DMA larga, números aleatorios, `VFTOI`/`VABS`). **Falta comprobarlo con el juego:**
requiere `scripts\2_compilar.cmd` (cambia el código generado). Conviene repetir la captura del estado 11
y, si aparece, buscar `[dma] chain` en el registro.

### Auditoría de las instrucciones MMI (2026-10-06)

A raíz del hallazgo de PEXEW/PROT3W en la esfera de visibilidad (sección "PEXEW duplica Y en la Z de las
esferas de visibilidad"), se comparó el código que emite el recompilador para **60 instrucciones MMI**
(aritméticas, comparaciones, saturación, permutaciones, empaquetado y desplazamientos) con la semántica de
[PCSX2 `MMI.cpp`](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/MMI.cpp). Una prueba diferencial local
(se volcó con `CodeGenerator::translateInstruction` el código de cada instrucción y se compiló contra
`ps2_runtime_macros.h`) lo ejecutó con 2000 pares de valores aleatorios y de borde, con destino distinto y
con destino igual a cada fuente, frente a una referencia escrita a partir de PCSX2. **15 instrucciones no coincidían:**

| Instrucción | Fallo |
|---|---|
| PEXEW, PROT3W, PEXCW | palabras mal ordenadas (PEXEW copiaba Y en la Z de las esferas de visibilidad) |
| PEXEH, PREVH, PEXCH | medias palabras mal ordenadas (PREVH invertía las 8 en vez de cada mitad) |
| PINTH, PINTEH | intercalaban la mitad equivocada de rs |
| PABSW, PABSH | leían rs en vez de rt y no saturaban 0x80000000 / 0x8000 |
| PADDUH, PSUBUH | sumaban/restaban sin saturar |
| PSLLVW, PSRLVW, PSRAVW | desplazaban rs (no rt) y en las cuatro palabras, sin extender el signo a 64 bits |

`ps2recomp-mmi.patch` (tras `ps2recomp-vu0-macro.patch`) corrige las macros de `ps2_runtime_macros.h` y la
emisión de `mmi_translation_helpers.cpp`. Con el parche, las 60 instrucciones coinciden con PCSX2 en todas
las variantes. La suite gana `PS2Mmi` (permutaciones con [11,22,33,44], saturación de PABS, desplazamientos
y formas emitidas) y pasa **533/533** con los 31 parches.

**Falta comprobarlo con el juego** (requiere `scripts\2_compilar.cmd`, cambia el código generado): repetir
las sondas de Clip del estado 11. Con PEXEW corregido, Y y Z de la esfera deberían dejar de coincidir y
algunos modelos deberían pasar Clip.

### Control integrado de GS, MMI y VU0 (2026-10-06)

Se integra `origin/main` en `0421ec4` mediante merge, conservando los parches de Opus
y los dos nuevos parches GS de constantes y coordenadas. Los 33 parches reproducen
exactamente las 78 fuentes modificadas del runtime. Se regeneran las 6418 unidades
y se recompila el ejecutable completo. MSVC interrumpe inicialmente `libsd.cpp` sin
emitir diagnóstico; la reanudación compila esa unidad y enlaza correctamente sin
cambiar fuentes. La suite nativa integrada pasa **545/545**, incluidas ocho pruebas
OpenGL en Windows; la configuración y los 14 scripts PowerShell pasan sus controles.

El control OpenGL de 175 s alcanza el estado 11. En sus primeras 64 llamadas a Clip
desde ProcessModel, las esferas son finitas y **ninguna tiene Y y Z con bits iguales**.
**30 devuelven `0` y 34 devuelven `0x80000000`**, frente a 64 rechazos y 64 pares Y/Z
idénticos en el control previo. La muestra abarca once modelos; no es un censo de
toda la escena. El modelo `0xD51C80`, grupo `0xD599C0`, pasa Clip en sus cinco muestras.
Los descartes restantes pueden corresponder a objetos fuera de la vista y no se fuerzan.

Las posiciones observadas también cambian: se actualizan buffers de primitivas que
sí pertenecen a los contextos, desde llamadas como `0x1644E0`, con datos no nulos.
Esto supera el diagnóstico anterior limitado a la plantilla del loader y a los
buffers de `0x1FB800`; no certifica que toda la geometría enviada sea correcta.

La captura a 138,75 s del reloj PAD está en estado 11 (`pending=0`, `levelReady=1`,
`flashReady=0`) y muestra polígonos/texturas deformados. La de 110,02 s aún está en
estado 4 y muestra textura naranja y triángulos grandes. Se inicializa OpenGL real
en la RX 5700 XT, sin fallback. **Kratos y la escena completa siguen pendientes**;
pasar Clip no equivale a una partida jugable. Los registros y capturas quedan solo
en `logs/integrated_mmi_gs_game/`, excluidos del repositorio.

El siguiente control detecta paradas de VU1 en `pc=0x288`, instrucción `0x8040FFFE`.
La tabla LowerOP de [PCSX2 fijada en `32ac6e2`](https://github.com/PCSX2/pcsx2/blob/32ac6e23e4aaf8c8c5e74a6c1ed750ee7672120e/pcsx2/VUops.cpp)
la identifica como EEXP; el runtime la considera reservada. También están cruzados
los códigos de ERSQRT, ESIN y EATAN. Se preparará un parche VU1 separado con pruebas
de instrucciones binarias explícitas, sin modificar las fórmulas EFU existentes.
El perfil previo a ese arreglo incluye los errores emitidos por esas paradas y
no debe describirse como rendimiento de una escena renderizada correctamente.

El script de rendimiento elimina también variables de diagnósticos experimentales
de geometría y replay, y restaura sus valores al terminar.

El perfil OpenGL de 240 s, sin capturas ni diagnósticos opcionales y sin otras pruebas
o compilaciones concurrentes, confirma estado 11 antes del intervalo medido. Sus ocho
ventanas completas de 180,31 a 220,38 s dan **1,00 llamadas a `vid::Flip`/s** y
**59,11 presentaciones/s**. El tiempo exclusivo transcurrido del hilo del juego se
reparte en IOP 53,18 %, VU 40,59 %, EE 3,69 % y envío GS 2,53 %. Incluye los errores
VU1 emitidos por defecto; GS no mide aquí la ejecución del worker OpenGL. No son
porcentajes de utilización de CPU/GPU. El control antiguo de 3,45 Flip/s descartaba
todos los modelos observados: el trabajo ejecutado ahora cambió y no permite atribuir
la diferencia al parche IOP. Se repetirá el perfil después de corregir EFU.

### Decodificación EFU de VU1 (2026-10-06)

`ps2recomp-vu1-efu-opcodes.patch` separa un fallo anterior del intérprete: según la
tabla LowerOP de PCSX2 enlazada arriba, ERSQRT usa `0x79`, ESIN `0x7C`, EATAN `0x7D`
y EEXP `0x7E`; `0x77` está reservado. El runtime utilizaba respectivamente `0x77`,
`0x79`, `0x7C` y `0x7D`. Esto detenía los microprogramas de GoW que ejecutan EEXP en
`pc=0x288` y seleccionaba otra fórmula para las tres instrucciones anteriores.

Se corrigen tanto la ejecución como la decodificación usada por la caché y el
scheduler, con las latencias de las operaciones ya existentes. Se conservan las
fórmulas, el acceso a P y la restricción de EFU en VU0. Tres regresiones nuevas usan
palabras binarias explícitas: comprueban resultados y WAITP/continuación de las cuatro
instrucciones, el rechazo de `0x77` y que EEXP siga reservado en VU0. Dos fixtures
anteriores de EATAN y latencias EFU se ajustan a las codificaciones correctas sin
relajar sus aserciones. Con esos fixtures, cuatro pruebas fallan antes del cambio;
con el arreglo pasan **540/540** sin activar las ocho pruebas OpenGL.

La compilación completa con los 34 parches vuelve a regenerar las 6418 unidades y
termina correctamente. La auditoría posterior compara 78 fuentes sin diferencias;
la suite nativa pasa **548/548**, incluidas las ocho pruebas OpenGL. Los cuatro fallos
previos quedan corregidos y los casos de instrucciones reservadas siguen cubiertos.

El control OpenGL de 300 s llega a estado 11 y registra **cero instrucciones VU1
reservadas** durante toda la ejecución. Conserva los resultados de las 64 muestras
de Clip (30 pasan, 34 descartadas; todas finitas, sin Y/Z duplicadas). Guarda 14
capturas distintas; las de 190,71 y 240,36 s del reloj PAD están en estado 11, con
`pending=0`, `levelReady=1` y `flashReady=0`. Muestran más geometría y texturas que
el control anterior, pero con polígonos enormes, franjas y deformaciones. Kratos
no es reconocible y la escena completa sigue pendiente. Los datos quedan en
`logs/vu1_efu_opcodes_game/`, excluidos de Git.

El perfil posterior de 240 s, sin capturas ni diagnósticos opcionales y sin otras
compilaciones/pruebas concurrentes, mide ocho ventanas completas de 180,06 a 220,07 s
en estado 11: **1,25 Flip/s y 59,99 presentaciones/s**. El tiempo exclusivo transcurrido
del hilo del juego es VU 52,36 %, IOP 41,25 %, GS frontend 3,77 % y EE 2,62 %. Este
control ejecuta más geometría y elimina las paradas/errores VU1 anteriores; el 1,00
Flip/s previo no corresponde a una escena correcta. Se confirma el coste del perfil
con una segunda ejecución de contadores de cuadros y se conserva CPU como siguiente
control para localizar las deformaciones frente a OpenGL.

La repetición contando solo cuadros (`GOW_PERF_DIAG=frames`) también está en estado
11 durante el intervalo: ocho ventanas completas de 180,05 a 220,06 s, con **1,275
Flip/s y 59,99 presentaciones/s**. Son 51 Flip en 40 s frente a 50 con el perfil completo;
esta diferencia pequeña entre ejecuciones no permite medir un overhead exacto, pero
descarta que la instrumentación opcional explique por sí sola la baja frecuencia
observada. Los tiempos en cero de este modo significan contadores desactivados,
no ausencia de trabajo. Los dos registros se conservan en `logs/vu1_efu_opcodes_perf/`
y `logs/vu1_efu_opcodes_frames/`.

El control CPU posterior de 300 s también llega a estado 11 y no registra
instrucciones VU1 reservadas. Conserva las mismas 64 observaciones de Clip (30
pasan, 34 descartadas, todas finitas, sin Y/Z duplicadas). Las capturas tardías
siguen mostrando polígonos desproporcionados y superficies deformadas; Kratos no
es reconocible. Este fallo también ocurre con CPU, aunque las imágenes de dos
ejecuciones independientes no permiten una comparación por pixel ni excluyen un
problema en el frontend GS común. El siguiente control debe repetir los mismos
comandos y el mismo estado inicial en ambos backends. Datos privados:
`logs/vu1_efu_opcodes_cpu_game/`. La CI del commit `94c9389` termina en verde.

### Estado CPU y repetición de comandos GS (2026-10-06)

Para comparar la misma geometría y los mismos comandos se añade
`ps2recomp-gs-cpu-state.patch`, separado de los arreglos anteriores. El CPU original
no implementaba `GSBackendStateAccess`: guardar solo su VRAM perdía paleta, caché
de textura, transferencia y readback. Se adapta la exportación/importación de
Taylor N. Albarnaz / LightVelox, fork SotC `ac9efa0` (GPL-3.0), conservando la caché
original y los bytes CT24 pendientes de este port. La importación valida antes de
modificar el destino; una página fuera de VRAM, desalineada, un pixel CT24 inválido
o un cursor fuera del buffer se rechazan.

Tres regresiones fallan antes del cambio (**540/543**): transferencia CT24 cortada
en dos bytes con CPU directo y con hilo, paleta/caché/readback conservados y rechazo
sin modificar el estado. Tras el arreglo pasan **551/551**, incluidas las ocho
pruebas OpenGL. La sonda de caché usa TBP0 en bloques de 256 B y comprueba un texel
cacheado distinto del contenido de VRAM; el arreglo no invalida esa página para
disimular diferencias. La auditoría previa verifica **35 parches y 79 fuentes**
exactamente. La compilación completa y el control del juego se verifican abajo.

La compilación completa posterior regenera las 6418 unidades y termina correctamente;
la auditoría vuelve a comparar las 79 fuentes sin diferencias. La suite nativa sobre
ese runtime pasa **551/551**. El diagnóstico final inicia la captura únicamente desde
comandos de dibujo/transferencia del EE, para evitar leer sus variables desde el hilo
de presentación. Tras ese ajuste de `src/`, la recompilación rápida y el test sintético
también pasan. Las rutas Unicode absolutas se verifican en Windows.

La captura sintética coincide también con OpenGL real: cero bytes distintos tanto con
compute como con la opción hardware habilitada. Esta muestra pequeña suma un tile
compute en ambas ejecuciones: no demuestra que el segundo control use rasterizado
hardware. Los registros quedan en `logs/gs_replay_synthetic_*`; la captura del tramo
real de GoW se verifica a continuación.

El diagnóstico opcional de `src/gow_gs_replay.h` conserva los comandos, MXCSR,
paleta, transferencia y VRAM inicial/final. La herramienta independiente repite
esa entrada en CPU y OpenGL y puede localizar la primera divergencia. Tiene
límite de tamaño/duración y no se instala sin `GOW_GS_REPLAY_TRACE`; el perfil
elimina esa variable. El test sintético verifica captura completa, parser y rechazo
de truncamiento, y la repetición CPU obtiene **cero bytes distintos**. El estado
completo, uso y límites del formato se describen en `RENDERIZADO.md`.

El control CPU de 200 s llega a estado 11 y guarda una captura completa de comandos
de 23,89 MB. Repite **47.207 envíos de primitivas y dos presentaciones** con cero
bytes distintos respecto a la VRAM final original; también coinciden paleta,
transferencia, bytes CT24 pendientes y readback. Repetirla nuevamente en CPU conserva
las dos imágenes sin diferencias. La página de textura inicial está invalidada,
por lo que no hay una página CPU antigua que impida importar esta entrada en GPU.

OpenGL real en la RX 5700 XT diverge por primera vez en el **registro 577, dibujo
561**, un triángulo texturado con STQ y PSMT8: solo tres bytes de VRAM difieren en
ese punto. Al final difieren **166.763 bytes con compute** y **164.227 con hardware
habilitado**; las dos presentaciones difieren. El segundo recorrido mezcla hardware
y compute (7.749 tiles compute frente a 11.937 del primero), y el log confirma que
hardware se activa. No se interpreta esta ejecución mixta como uso exclusivo de
rasterizado hardware. Estos códigos de salida 1 indican una divergencia localizada,
no un fallo del parser ni pérdida de la captura.

Las 12 capturas del control siguen mostrando polígonos enormes y franjas; Kratos
no es reconocible. Las 64 muestras de Clip siguen finitas, con 30 aceptadas y 34
descartadas, sin Y/Z duplicadas, y no hay instrucciones VU1 reservadas. La repetición
permite aislar precisión/interpolación en GS; no demuestra que esas diferencias
expliquen toda la deformación que también aparece en CPU. El siguiente paso es
comprobar el efecto del modo de redondeo del host y reducir el primer dibujo distinto
a una prueba sintética. Los comandos, coordenadas, VRAM e imágenes originales quedan
únicamente en `logs/gs_cpu_state_game/`, excluidos de Git.

La CI del commit `681c257` pasa ambos jobs. La captura y repetición ya se pueden
reproducir con la herramienta pública, sin publicar los volcados originales.

### Aislamiento del redondeo SSE en el renderer CPU (2026-10-06)

Se confirma una dependencia del backend CPU respecto al modo MXCSR del productor.
VU ejecuta con redondeo hacia cero y envía comandos GS dentro de esa ejecución;
la cola GS también conserva MXCSR. En la captura anterior **46.950 de los 47.207
dibujos** llegan con ese modo, incluido el primero que difiere de OpenGL. Una sonda
sintética de 24 combinaciones de gradiente/UV/STQ, CPU directo/con hilo y cuatro
modos falla en cuatro casos de gradiente: cambian 178 bytes de color por caso.
UV/STQ de esa muestra no cambian; no se generaliza ese resultado a toda textura.

Se aísla además el dibujo real 561 tras repetir todos sus comandos anteriores.
La página CPU cacheada coincide con VRAM. Cambiar únicamente el modo CPU modifica
cuatro bytes entre más cercano y hacia cero; OpenGL compute difiere en un byte
respecto al CPU con más cercano. Esto confirma la influencia de MXCSR en ese
dibujo, pero todavía queda una diferencia de precisión y no se certifica paridad
completa. Las ejecuciones con hardware habilitado de esta sonda pequeña usan
compute (129 tiles); el control mixto completo anterior sigue siendo el que
verifica activación hardware.

`ps2recomp-gs-cpu-rounding.patch` delimita el modo SSE al entrar en `Submit`: usa
el redondeo habitual al más cercano del rasterizador CPU y restaura el del llamador
al salir. Conserva máscaras, FTZ/DAZ y flags; no cambia EE, FPU, IOP ni la ejecución
VU. Es una estabilización del renderer aproximado, no una afirmación de que la
interpolación actual tenga la precisión exacta del GS de PS2. Dos regresiones nuevas
comprueban independencia con CPU directo y con hilo, y conservación del control
MXCSR. Antes del arreglo fallan ambas (**543/545** sin OpenGL); después pasan
**553/553**, incluidas las ocho pruebas OpenGL. La auditoría verifica **36 parches
y 79 fuentes** sin diferencias; los scripts y la configuración pasan, con los
cuatro avisos conocidos.

La compilación completa de los 36 parches termina correctamente y vuelve a generar
las 6418 unidades. La auditoría posterior conserva las 79 fuentes exactas y la suite
nativa pasa **553/553**. La sonda independiente de 24 combinaciones pasa ahora todas,
sin alterar el modo del llamador; la herramienta de captura se reconstruye y su
test sintético también pasa. El primer control de 200 s no llega a iniciar la
captura en estado 11 y queda inconcluso; no sirve para comparar renderers.

Tras el arreglo de libm de Claude (`3f349b2`), la compilación completa conjunta
vuelve a aplicar los 36 parches y ejecuta las funciones originales double de
`sin`, `fabs` y `floor`. La auditoría verifica las 79 fuentes exactas. El control
CPU de 330 s alcanza estado 11 con `pending=0` y guarda una captura completa de
**53.016 dibujos y tres presentaciones**. Repetirla con CPU reproduce exactamente
VRAM final, estado GS y las presentaciones. Compute y el recorrido mixto divergen
primero en un sprite (dibujo 510, registro 520), con 917 bytes distintos; al final
difieren en 387.242 y 386.914 bytes respectivamente y en las tres presentaciones.
El recorrido mixto activa hardware y ejecuta 17.679 tiles compute, frente a 42.001
en compute puro. Son comparaciones de la misma entrada; no son mediciones de FPS.

Las imágenes CPU de 160,48 y 191,27 s muestran cubierta, acantilados, cielo y lluvia
reconocibles, mejorando claramente el control anterior a libm. Una imagen posterior
vuelve a mostrar deformaciones; todavía no se verifican Kratos ni una partida
jugable. Se mantienen los controles originales en `logs/gs_camera_libm_cpu_game/`,
excluidos de Git, y se continúa investigando los desacuerdos GS y los modelos.

El análisis completo de la captura anterior verifica 141.396 vértices finitos. Hay
5.284 primitivas con XYZ completamente en cero, todas con estado PSMT8; los Q de
magnitud mayor de `1e10` usados por STQ aparecen solo en 5.260 de estas primitivas
degeneradas. Esto localiza posiciones cero en la salida final GS, pero no identifica
todavía su contexto de modelo ni demuestra que deban dibujarse. También se observan
210 vértices STQ con Q negativo; no se fuerza su signo. Las observaciones anteriores
de Clip y de miembros no nulos siguen válidas para los contextos que se midieron.

Una sonda privada de 12 triángulos sintéticos grandes reproduce diferencias de Z en
tres casos con el shader actual. Un borrador que conserva el recíproco y los
numeradores enteros en double antes de obtener pesos float elimina esas diferencias
en los 12 casos y en el dibujo real aislado 561. Ese borrador todavía no forma parte
del ejecutable de ese control; se convierte después en el parche separado que se
describe a continuación.

### Precisión de pesos OpenGL y profundidad PACKED Z32 (2026-10-06)

`ps2recomp-gs-triangle-precision.patch` conserva el recíproco del área en double en
dos palabras libres del registro de primitiva. El shader común reconstruye los
numeradores enteros en double dentro del dominio GS y convierte los pesos a float
solo después de multiplicar por ese recíproco, como CPU. `Submit` prepara primitivas
con redondeo SSE al más cercano y restaura los controles del productor. Se conserva
el stride de 40 palabras y el shader hardware generado usa el mismo cálculo.
La regresión compara VRAM completa CPU/OpenGL para dos áreas grandes, dos XYOFFSET,
Z32/Z24 y cuatro modos SSE, con compute y hardware permitido. Falla en el renderer
anterior (**553/554**) y pasa con el arreglo (**554/554**). La sonda privada de doce
casos y el triángulo real aislado anterior también dejan de diferir. Esto mejora
la precisión de GS; todavía no demuestra una ganancia de FPS ni elimina todos los
desacuerdos de la nueva captura.

`ps2recomp-gs-packed-depth.patch` corrige otro fallo antes del backend: PACKED XYZ2
y XYZ3 convertían su Z32 a float antes de almacenarlo en `GSVertex.z` (double).
Por ejemplo, `0x01000001` perdía un bit y `0xFFFFFFFF` acababa escribiéndose como
cero. Ambas rutas convierten directamente a double; XYZF de 24 bits, REGLIST y A+D
conservan su comportamiento. Dos regresiones comprueban cuatro profundidades en
la ruta nativa y en los 33 cortes de bytes del paquete, además de la cola de XYZ3
y XYZ2 con ADC sin dibujo prematuro. Antes del arreglo fallan ambas (**545/547**
sin las pruebas OpenGL); después pasan **556/556**, incluidas las nueve OpenGL.
La auditoría integrada reconstruye **38 parches y 79 fuentes exactas**;
configuración y 14 scripts pasan con los cuatro avisos conocidos. La compilación
completa conjunta termina correctamente, genera las 6418 unidades y conserva las
79 fuentes exactas al auditarlas después de compilar. Sigue el control del juego.

La suite reconstruida después de esa compilación pasa **556/556**. El helper público
compila las tres herramientas y pasa la captura/repetición sintética. CPU reproduce
de nuevo los 53.016 dibujos originales sin diferencias. Compute termina con
386.873 bytes distintos, frente a 387.242 antes; el recorrido mixto termina con
390.713, frente a 386.914. Ambos conservan la primera diferencia de feedback (917
bytes en el sprite 510) y las tres presentaciones distintas. La mezcla de rutas
hardware/compute también cambia (17.783 tiles compute frente a 17.679 antes): no
se atribuye su variación final exclusivamente a precisión ni se declara paridad
hardware. El control OpenGL del juego usa el ejecutable completo de estos cambios.

El control OpenGL de 330 s alcanza estado 11 con `pending=0` y `levelReady=1`,
en RX 5700 XT con hardware activo y sin fallback. La única PPM de partida es la
de 249,35 s: se reconocen cielo, lluvia y escenario al fondo, pero un objeto oscuro
grande tapa el centro y Kratos no es identificable. Las anteriores permanecen en
menú o transición; no se comparan como la misma fase del control CPU de 160/191 s.
Las 64 muestras de Clip conservan los resultados anteriores y los 66 buffers
tardíos observados tienen primeras tripletas no nulas. No aparecen instrucciones
VU reservadas, rutas inválidas, ciclos ni truncamientos. Sigue sin certificar una
partida jugable o una mejora de FPS.

La revisión final protege también los diagnósticos frente al fallback GPU: la cola
puede destruir el backend OpenGL al sustituirlo por CPU, por lo que las herramientas
y la nueva regresión verifican primero `Inner()` antes de consultar `IsReady()`.
No cambia el rasterizado. La segunda compilación completa requerida para publicar
la corrección del test termina correctamente; la suite vuelve a pasar **556/556**
y la auditoría posterior conserva las 79 fuentes exactas.

El control de cámara conjunta muestra 64 Clips finitos y completos: 22 resultados
`0`, seis `20` y 36 descartes `80000000`, sin Y/Z duplicados. Las 544 sondas tardías
de `InitUNPACKData` tienen una primera tripleta no nula. Hay 10.520 primitivas
degeneradas con todos sus XYZ cero; los S enormes aparecen exclusivamente en ellas,
sin XYZ no finitos. Esto no respalda forzar posiciones a otro valor. No aparecen
rutas inválidas ni ciclos en las muestras de modelos/GROB. Los planos oscuros de
240,85 s quedan pendientes de comparar con el mismo cuadro de referencia para
distinguir encuadre, oclusión y geometría defectuosa.

La primera diferencia de la nueva traza se reduce a un sprite bilineal que lee y
escribe el mismo framebuffer CT32. La sonda privada aislada reproduce los 917 bytes
en 476 píxeles de 24 filas, concentrados junto a límites de página; repetirla da el
mismo resultado. Con nearest no difiere, TEXFLUSH previo conserva la diferencia,
y copiar la fuente a una región disjunta la elimina. Esto localiza una diferencia
de feedback/caché CPU frente a OpenGL. La referencia PCSX2 distingue explícitamente
estos casos de lectura del destino, pero no demuestra cuál de nuestras salidas
reproduce el GS; no se fuerza paridad cambiando el filtrado ni anulando la caché.

El caso se reduce además a una textura procedural CT32 de 64×64: CPU y GPU
difieren en 63 píxeles (186 bytes), únicamente en las filas 32 y 33. CPU mutable
difiere igual de su control con fuente disjunta, mientras OpenGL coincide con
ese control en las dos repeticiones. Los 53.248 vecinos bilineales del caso real
también se verifican después de CLAMP, incluidos los negativos remapeados a cero.
La nueva herramienta pública `tools/render/comparar_feedback_gs.cpp` reproduce
el caso sintético y se compila con `scripts\compilar_replay_gs.cmd`; no utiliza
datos del juego. El siguiente paso requiere una referencia GS para este patrón
de lectura y escritura antes de cambiar la política de caché.

### Revisión del trabajo de Claude y comparación visible (2026-10-07)

El checkout `E:\gowclaude\repo` está limpio en `1bdcd72` y coincide con el nuevo
`origin/main`: siete commits posteriores a `1968f03`. Son cambios separados de
getenv en bucles calientes, rendimiento VU1, DMA del scratchpad, entrada MPEG,
diagnóstico PCM, sonido IOP y memory card. La mejora VU1 tiene un banco de pruebas
del mismo cuadro y salida idéntica: 775 a 503 ms; no equivale a una mejora del 35 %
de FPS de la partida. El arreglo de scratchpad explica la paleta de huesos de
Kratos que llegaba cero a VU1. Las capturas locales de Claude muestran a Kratos,
enemigos y HUD con formas reconocibles, y las del guardado llegan a «Save Complete».
Sus resultados y controles están en `COMPARACION_PCSX2.md`, `RENDIMIENTO.md`,
`FMV_Y_AUDIO.md` y `MEMORY_CARD.md`. Falta verificar el ejecutable conjunto con
los dos nuevos arreglos GS; se conserva la referencia anterior como histórica.

La revisión de `repetir_gs` detecta además que CPU reserva filas de 640×512 y GPU
devuelve filas de 640×alto visible. Comparar los vectores brutos podía marcar una
diferencia de tamaño aunque los píxeles visibles fueran iguales, y el exportador
rechazaba la PPM de CPU. `gs_frame_pixels.h` exige el layout explícito del backend,
extrae solo la imagen visible y rechaza buffers truncados o ambiguos. Dieciocho
controles sintéticos, incluido `GSCpuBackend::Present` real de 64×64 y la PPM RGB,
pasan; la captura/repetición CPU sintética vuelve a quedar exacta. Las cifras de
VRAM anteriores no cambian; las comparaciones de presentación brutas se vuelven
a comprobar con esta herramienta antes de considerarlas diferencias de imagen.
La repetición compute completa de la traza histórica confirma ahora tres imágenes
visibles distintas, y exporta tanto CPU como GPU (cuatro PPM válidas). CPU vuelve a
reproducir VRAM final exactamente. Este control usa el modo por lotes: sus 387.310
bytes finales no se comparan como si fuera la ejecución con sincronización por
dibujo anterior. En modo por lotes se etiqueta el primer control de VRAM distinto,
sin presentarlo como la posición de la primera divergencia real.

La integración conserva los siete parches de Claude antes de los dos arreglos GS:
**45 parches y 84 fuentes exactas** al reconstruir y comparar el árbol. La
compilación completa regenera las 6418 unidades y termina correctamente. Después
pasan **565/565 pruebas**, incluidas las nueve OpenGL y las nuevas regresiones de
SPR, MPEG, sonido y tarjeta. Las cuatro herramientas de renderizado se recompilan;
sus 18 controles de imágenes, captura/repetición CPU sintética y sonda de feedback
procedural conservan los resultados esperados.

El control conjunto OpenGL de 225 s carga una partida de «Docks of Athens» desde
una **copia** de la tarjeta ECC de Claude, con el original comprobado por SHA256
sin cambios. RX 5700 XT usa hardware sin fallback. La última captura de 512×448
muestra a Kratos en el punto de guardado, el HUD y la indicación R2; alcanza
estado 11 sin carga pendiente. No prueba todavía combate, rendimiento sostenido
ni todos los escenarios. Las 128 muestras de Clip entre menú y partida son finitas
y completas; las 144 sondas tardías de `InitUNPACKData` tienen una primera tripleta
no nula. Los 64 contextos de modelos de partida no contienen direcciones inválidas,
ciclos ni truncamientos, y no se registran instrucciones VU reservadas.

El treemap de SDK y hardware y los tres README reflejan ahora estos controles:
MPEG/IPU pasan a parcial por la intro decodificada; tarjeta y audio detallan qué se
verificó y qué falta. GS queda parcial por las diferencias CPU/OpenGL todavía
abiertas. El 65,4 % de librerías y 60,5 % de hardware representan las ponderaciones
del mapa, no el porcentaje del juego completado ni su velocidad.

La repetición hardware con tres pasadas en una sola instancia GL certifica la
restauración antes de comparar: VRAM inicial, CLUT/CBP, transferencias y estado
portable exactos en las tres; CPU inicial/final con caché exacta y CPU frente a la
captura final sin diferencias. Las dos pasadas calientes usan ambas 373 lotes,
33.445 primitivas y cero tiles compute, pero difieren entre sí en **4617 bytes de
VRAM** y en **344/298/296 bytes de las tres imágenes visibles**. Ya no se trata de
comparar tamaños distintos de buffers. La pasada fría mezcla compute durante la
compilación de variantes, por lo que no se usa como control de la misma ruta.
Sigue la investigación del orden de acceso a VRAM y de los buffers de subida;
estos tiempos de repetición tampoco son una medición de FPS del juego.

El nuevo `repetir_gs --repeticiones N` lleva ese control al tool público. Reutiliza
las mismas instancias, comprueba la restauración completa y compara VRAM, estado
y todos los cuadros visibles entre pasadas consecutivas. Los deltas de raster
distinguen las pasadas que aún usan compute mientras compilan variantes. Se
corrige también el directorio de salida como tercer argumento y se detectan
opciones inválidas y fallos al exportar, manteniendo los códigos de salida.
El helper completo y sus 18 controles pasan; CPU sintético ×3, compute ×3 y
hardware ×8 conservan paridad y estabilidad. CPU del primer cuadro real ×3 es
exacto y exporta seis PPM válidas; hardware ×8 detecta 545 bytes VRAM y 358 visibles
distintos entre las dos últimas, ambas con cero tiles compute.

La búsqueda con cortes CPU válidos estrecha el caso al segundo sprite de feedback:
519 (antes) y 520 (primer sprite) son repetibles; al incluir 521 aparecen 36 bytes
variables con 3 lotes, 192 primitivas y cero tiles compute. La restauración y el
estado portable final siguen exactos. La diferencia CPU/GPU de 917 bytes del primer
sprite es estable y se distingue de esta variación. Cero reutilizaciones del ring
de subida en la captura descartan ese reciclado como causa; todavía se necesita
una referencia para decidir el tratamiento correcto de lecturas del destino.

Cuatro capturas procedurales comprueban también estados iniciales que el control
simple no cubría: dos bytes CT24 pendientes, lectura local con cursor 7 y nueve
bytes pendientes, página de caché fresca y página con un byte obsoleto. Las cuatro
son exactas en CPU ×3, incluida la imagen visible; las tres compatibles con GPU
son exactas en compute ×3 y la obsoleta se rechaza con código 2 antes de crear GL.
El directorio como argumento 3 exporta las imágenes correctas; un archivo usado
como directorio y nueve variantes de opciones inválidas también devuelven 2.

El nuevo generador `tools/render/generar_feedback_gs.cpp` reduce la inestabilidad
a dos sprites sobre texels procedurales de 64×416, sin archivos del juego. Genera
feedback bilineal, fuente disjunta y feedback nearest, verificando los 27.588
vecinos copiados. El helper recompila ahora cinco herramientas, pasa los 18
controles de imágenes y repite las tres capturas en CPU ×3 con End, VRAM y cuadro
exactos. En RX 5700 XT, hardware ×12 de fuente disjunta y nearest conserva paridad
y estabilidad; feedback bilineal devuelve 1 y varía entre pasadas hardware con
dos lotes, dos primitivas y cero tiles compute (19 bytes VRAM/visibles en 4→5 y
34 en 7→8). Restauración y estado portable final permanecen exactos. Así se puede
reproducir el problema independientemente del juego antes de elegir un arreglo;
no se cambia todavía la política del renderer ni se atribuye una mejora de FPS.

La referencia independiente de PCSX2 v2.8.2 software descubre otro problema:
el filtro bilineal redondeaba al final, mientras la referencia usa fracciones de
cuatro bits y trunca cada etapa. `ps2recomp-gs-bilinear-precision.patch` cambia
solo GS CPU/GLSL y añade tres regresiones con una huella RGBA externa de 256
fracciones UV, también para STQ y cuatro modos SSE. Las tres fallan antes del
arreglo y después pasan **568/568**, incluidas diez OpenGL reales. El control
literal bilineal de una prueba anterior se ajusta al truncado documentado;
nearest no cambia. La compilación completa de las 6418 unidades termina bien
y el árbol reconstruido coincide en sus **46 parches y 84 fuentes**.

El helper recompila seis herramientas y conserva los 18 controles de imágenes
y las tres repeticiones CPU ×3 exactas. `generar_feedback_gs --pcsx2` añade
exportación procedural GS freeze v8/PATH3; la nueva prueba comprueba el freeze
inicial y reproduce los comandos GIF con VRAM final exacta en los tres casos.
Los `.gs` exportados son idénticos por SHA256 a los usados en la referencia
aislada, sin BIOS ni datos del juego. La comparación con PCSX2 software queda
exacta para nearest y, tras el arreglo, para bilinear con fuente disjunta.
Los detalles y fuentes están en [RENDERIZADO.md](RENDERIZADO.md).

En RX 5700 XT, hardware ×12 sigue exacto y estable para fuente disjunta y nearest.
Feedback bilineal aún devuelve 1 y varía: las dos últimas pasadas difieren en
89 bytes de VRAM y de imagen visible, con dos lotes, dos primitivas, cero tiles
compute y estado portable final igual. No se cambia la política de caché ni
se atribuye una mejora de FPS. El treemap incorpora la precisión verificada
y conserva GS/texturas en parcial y sus porcentajes de cobertura anteriores.

El control OpenGL final de 330 s carga «Docks of Athens» desde una copia privada
de la tarjeta ECC, cuyo original sigue idéntico por SHA256. Las 14 capturas son
distintas y válidas; la última muestra a Kratos, el HUD, el punto de guardado y R2,
en estado 11 sin carga pendiente. Las 128 muestras de Clip son finitas y completas;
las 352 sondas tardías de `InitUNPACKData` tienen una primera tripleta no nula,
y las 192 muestras de contextos de partida no contienen punteros inválidos,
ciclos ni truncamientos. No aparecen instrucciones VU reservadas. No prueba
todavía combate ni FPS sostenidos. Se retrasan las pulsaciones del guion privado:
el primer control de 225 s perdió el Start inicial y acabó en la intro de partida
nueva, por lo que no se usa como prueba de carga guardada.

El siguiente control de referencia confirma un fallo distinto con nearest STQ:
el cast directo a entero pierde el signo de las fracciones negativas. El nuevo
`ps2recomp-gs-nearest-stq.patch` convierte primero a 16.16 y extrae la parte entera
con signo, tanto en CPU como en GLSL. Dos matrices de 16×16 procedurales comparan
cuartos de texel negativos y los límites próximos a cero: el original difiere
de PCSX2 software en 624 bytes RGBA/156 píxeles en cada una. Usar solamente
`floor` falla en los valores que pierden la fracción durante la conversión fija.
Las tres regresiones nuevas fallan antes y pasan después para sprites/triángulos,
Q=1/2 y los cuatro modos SSE. Se confirman también las rutas OpenGL por contadores.

La compilación completa vuelve a regenerar las 6418 unidades y termina bien;
**47 parches y 84 fuentes** coinciden, y la suite posterior pasa **571/571** con
once controles OpenGL reales. El helper compila siete herramientas: conserva
los 18 controles de imágenes y añade un generador público de los tres oráculos.
Sus `.gs` son idénticos por SHA256 a los usados en PCSX2 software; sus matrices
CPU coinciden byte por byte con las tres referencias RGBA externas. Los seis
patrones pasan freeze/GIF/End y CPU ×3. Hardware ×8 de los tres oráculos queda
exacto y estable, con 256 primitivas y cero tiles compute en las pasadas calientes.
Los tres dumps anteriores de feedback conservan sus bytes. El treemap refleja
ambos arreglos de muestreo sin cambiar la cobertura parcial ni atribuir FPS.

El control final OpenGL de 330 s con este ejecutable carga de nuevo la copia
privada de «Docks of Athens», con hardware activo y la tarjeta original intacta.
Las 14 capturas son distintas; la última muestra a Kratos, HUD, R2 y punto de
guardado en estado 11 sin carga pendiente. Se conservan 128 muestras de Clip
finitas/completas, 352 primeras tripletas tardías no nulas y 192 contextos de
partida sin punteros inválidos, ciclos ni truncamientos. No se registra VU
reservada. Combate, rendimiento sostenido y feedback bilineal siguen pendientes.

### Feedback GS: controles separados y fuente protegida opcional (7 de octubre)

Se conserva la rama experimental VU1 de Opus sin integrarla ni modificar EE/IOP.
El generador GS añade seis controles a los tres patrones procedurales anteriores:
TEXFLUSH o SCISSOR1 fuera del área dibujada entre dos sprites. Los nueve pasan
freeze/GIF/End y CPU ×3. La validación del dump comprueba ahora también el freeze
completo y los tres bloques privilegiados, para detectar cambios en PMODE,
DISPLAY, contextos, colas GIF y Q que no alterarían la VRAM final.

PCSX2 software v2.8.2 conserva una fuente común en `self`/`self_texflush`; cambiar
SCISSOR1 fuerza dos dibujos y renueva la fuente. Las fuentes de ambos dibujos se
verifican contra el patrón y el primer framebuffer, respectivamente. El resultado
separado difiere en 1238 bytes RGB, demostrando que copiar por primitiva no equivale
a congelar un lote entero. Este control no certifica el pipeline del GS real.

El nuevo parche `ps2recomp-gs-feedback-snapshot.patch` conserva la fuente antes
de cada primitiva con lectura/escritura solapada, usando las páginas sombra del
backend OpenGL y el epoch anterior a la copia. Es opcional, desactivado por
defecto, y se selecciona con `PS2X_GS_FEEDBACK_SNAPSHOT=1` en el ejecutable o
`--snapshot-feedback` en la herramienta de repetición. El renderer CPU conserva
su caché de una página de 8 KiB; la herramienta sigue denunciando sus diferencias.

Antes del cambio, la nueva regresión hardware falla tanto por RGB como por
variación entre pasadas (572/573); compute ya pasa ese patrón. Después pasa
573/573 con trece controles OpenGL reales. Ambas rutas reproducen la huella externa
del caso separado, mantienen estable toda la VRAM restaurada, conservan alpha
y la fuente disjunta y pasan los controles de puntos/triángulos contra la copia
CPU disjunta. El modo experimental todavía no está habilitado por defecto y
no demuestra un aumento de FPS. El treemap conserva cobertura parcial y pesos.

La compilación completa regenera las 6418 unidades y termina con código 0.
La auditoría posterior confirma los 48 parches/84 fuentes, y la suite vuelve
a pasar 573/573. El helper compila siete herramientas y valida los 18 controles
de imagen y los doce patrones freeze/GIF/End con CPU ×3; seis dumps dañados se
rechazan. Los tres dumps originales siguen idénticos por SHA256.

Las 72 pasadas de repetición opcional (compute/hardware × tres patrones ×12)
mantienen VRAM, estado y cuadro visible idénticos entre restauraciones y coinciden
con las tres regiones RGB de referencia. Hardware caliente confirma dos
primitivas y cero tiles compute. El caso separado conserva su salida 1 por los
4557 bytes que difieren de la caché CPU; nearest y fuente disjunta conservan
salida 0. Se rechazan también la opción duplicada y su uso en modo CPU.

El control del juego con la opción activada dura 390 s y carga una copia privada
de la tarjeta de Claude, cuyo original conserva su SHA256. Las quince capturas
son distintas y válidas (512×448); la última muestra a Kratos, el punto de guardado
y R2, en estado 11 sin carga pendiente y con hardware activo. Las 128 muestras
de Clip son finitas y completas, las 416 primeras tripletas tardías de
`InitUNPACKData` son no nulas y los 192 contextos de partida no presentan punteros
inválidos, ciclos ni truncamientos. No se registra VU reservada. La barra de vida
no aparece en esta captura final; combate y FPS sostenidos siguen sin comprobar.
El primer guion de 330 s perdió la selección «Load» y llegó a la intro de una
partida nueva: no se usa como evidencia de carga guardada. Solo se retrasaron
las pulsaciones del control privado para repetirlo.

### STQ bilineal: convertir antes de restar medio texel (7 de octubre)

La siguiente comparación procedural con PCSX2 v2.8.2 software confirma un fallo
de precisión distinto: bilinear restaba medio texel a la coordenada float antes
de cuantizarla, aunque nearest ya usaba 16.16. Una matriz 16×16 con texels RGBA
4×4 disjuntos y valores próximos a los límites signed difiere en 611 bytes
RGBA/156 píxeles. La entrada RGB/alpha de los 16 texels y freeze/GIF/End se
comprueban exactos antes de atribuir la diferencia al filtro.

`ps2recomp-gs-bilinear-stq.patch` realiza la conversión antes del medio texel
en CPU y GLSL. Las tres regresiones nuevas fallan antes (573/576) y pasan
después (576/576, catorce controles OpenGL reales). Usan la huella RGBA externa,
sin repetir la fórmula del filtro en el test, para sprites/triángulos, Q=1/2
y cuatro modos SSE. Hardware tiene que rasterizar al menos una matriz sin
tiles compute. El generador público exporta ahora también el control bilinear
STQ; los detalles y la referencia están en [RENDERIZADO.md](RENDERIZADO.md).

La compilación completa regenera las 6418 unidades y termina con código 0.
La auditoría confirma 49 parches/84 fuentes y la suite posterior pasa 576/576.
El helper compila siete herramientas y valida trece patrones freeze/GIF/End
con CPU ×3, además de los 18 controles de imagen y seis corrupciones rechazadas.
Los cuatro dumps son idénticos a los ejecutados en PCSX2 por SHA256 y sus
matrices CPU coinciden con los 1024 bytes RGBA de cada referencia.

Compute ×8 y hardware ×8 del nuevo patrón conservan VRAM, estado y cuadro
visible entre restauraciones, con RGB externo exacto. Las ocho pasadas rápidas
seleccionando hardware usaban aún compute mientras compilaba su shader.
La nueva opción `--pausa-ms 1000` deja terminar esa compilación entre pasadas
sin cambiar las comparaciones: siete de las ocho repeticiones usan hardware
con 256 primitivas y cero tiles compute. Se rechazan nueve argumentos inválidos;
CPU ×2 con pausa mantiene salida 0 y feedback opcional mantiene su salida 1.
La espera de diagnóstico no interviene en el juego ni mide rendimiento.

El control final de 510 s usa OpenGL, omite FMV y mantiene desactivado el snapshot
experimental. Carga una copia privada de la tarjeta de Claude; el original
conserva su SHA256. Las dieciséis imágenes 512×448 son distintas y válidas.
La última muestra a Kratos durante un ataque, con HUD, estelas de armas, R2 y
punto de guardado, en estado 11 sin carga pendiente. Se reciben las tres
pulsaciones de cuadrado; las 128 muestras de Clip son finitas/completas, las
768 tripletas tardías son no nulas y los 192 contextos de partida no presentan
punteros inválidos, ciclos ni truncamientos. No aparece VU reservada. La imagen
de ataque queda comprobada; combate contra enemigos y rendimiento sostenido
siguen pendientes. La documentación de arquitectura enlaza ahora la lista
de parches de `scripts/compilar.ps1`, para evitar otra lista manual incompleta.

### Páginas regionales: reducir sincronizaciones sin perder feedback (7 de octubre)

`ps2recomp-gs-region-pages.patch` delimita las lecturas de REGION_CLAMP y
REGION_REPEAT y guarda ambos extremos U/V en la clave del bitset. En los
controles procedurales, tres fuentes disjuntas pasan de tres lotes/dos flushes
a uno/cero; la cuarta lectura de una página escrita conserva dos/uno.
Se comparan los 4 MiB completos con CPU en los 13 PSM, con paletas CSM2
coloreadas, nearest/bilinear y caché del bitset activada/desactivada. Cambiar
solo MIN en REGION_CLAMP prueba que la clave se renueva correctamente.

Los controles de bordes incluyen bases TBP desalineadas, cruces de páginas,
vuelta de VRAM y máscaras no nulas, con y sin snapshot. Mantienen las
sincronizaciones reales y exigen hardware efectivo sin tiles compute.
Son 1184 combinaciones entre ambas rutas. Las regresiones nuevas de lotes
fallan antes; los controles aislados con el equipo libre descartan los plazos
de shaders agotados durante una primera ejecución junto a la compilación de
Claude. Los detalles están en [RENDERIZADO.md](RENDERIZADO.md).

La compilación completa termina con código 0; 50 parches/84 fuentes coinciden
y la suite final pasa 580/580, con dieciocho controles OpenGL. Las siete
herramientas pasan 18 controles de imagen y trece freeze/GIF/End con CPU ×3;
los seis dumps dañados siguen rechazándose. La reducción de envíos es un
resultado sintético; faltan medir su efecto en FPS y comprobar la caché GS real.

El control posterior dura 510 s en OpenGL, con FMV omitido y snapshot
experimental desactivado. Carga una copia privada de la tarjeta, cuyo original
conserva su SHA256. Las dieciséis capturas 512×448 son distintas; la última
muestra a Kratos atacando con HUD, estelas de armas, R2 y el punto de guardado,
en estado 11 sin carga pendiente y con hardware activo. Se conservan 128
muestras de Clip finitas/completas, 736 tripletas tardías no nulas y 192 contextos
sin punteros inválidos, ciclos ni truncamientos. No aparece VU reservada.
Esto verifica la imagen de un ataque; combate contra enemigos y FPS sostenidos
siguen pendientes.

### Captura GS tardía desde TEXFLUSH (7 de octubre)

El diagnóstico permite elegir espera y duración con `GOW_GS_REPLAY_AFTER` y
`GOW_GS_REPLAY_SECONDS`. `GOW_GS_REPLAY_TEXFLUSH=1` inicia el tramo después del
primer TEXFLUSH del juego en estado 11 que cumpla el plazo. No añade una
invalidación: conserva los comandos anteriores en el estado inicial y los
posteriores en la traza. Sin archivo de captura no se instala el wrapper;
las opciones inválidas se rechazan antes de abrirlo. El perfil limpia las
cuatro variables. Valores y límites: [CONTROLES.md](CONTROLES.md#captura-de-comandos-gs).

La regresión falla con el comportamiento de inicio anterior y pasa con la
frontera. Comprueba caché antigua sin borrar antes de tiempo, TEXFLUSH del menú
y anterior al plazo, presentación sin inicio, bytes CT24 pendientes, comandos
previos excluidos de la traza y repetición exacta de toda la VRAM final.
La prueba cierra sus lectores antes de borrar los archivos en Windows. El
helper ahora rechaza también errores negativos de proceso: `ERRORLEVEL 1`
por sí solo dejó pasar el cierre anómalo de una primera versión de este test.
La CI compila **y ejecuta** el control CPU sin el juego ni OpenGL.

Tras `2_recompilar_rapido.cmd`, el control CPU de 520 s carga una copia privada
de la tarjeta de Claude, con FMV omitido. El original conserva su SHA256.
Las dieciséis imágenes son distintas; la última muestra a Kratos atacando
junto al punto de guardado, con HUD y estelas. Estado final 11 sin carga
pendiente, 128 Clip finitos/completos, 368 tripletas tardías no nulas y 192
contextos sin punteros inválidos, ciclos ni truncamientos; cero VU reservada.

Con espera 470 s y duración 3 s, el inicio ocurre a 470,287 s desde el backend,
después de TEXFLUSH. El archivo completo ocupa 54.535.037 bytes: 146.015
registros, 145.469 dibujos y dos presentaciones. CPU ×3 reproduce el End, toda
la VRAM, el estado y ambas imágenes exactamente, entre pasadas y frente al
original. La página inicial está invalidada y permite importar el estado en GPU.

Compute sigue divergiendo: el primer dibujo es un sprite UV PSMCT32 de 32×416,
con 1874 bytes distintos desde la dirección 65540. La primera divergencia está
en el registro 3; los finales y las dos presentaciones difieren de CPU. Las
tres pasadas conservan los contadores de raster pero varían algunos bytes
de VRAM, y una transición cambia también el primer cuadro visible. Esta traza
delimita un fallo de GS en una escena tardía; no acredita paridad GPU ni FPS.
Los datos de juego y las imágenes permanecen bajo `logs/`, excluidos de Git.

El sprite se redujo a una traza local de un dibujo: TBP=0/FBP=0, TBW=FBW=8,
CLAMP en ambos ejes, bilinear, textura declarada 1024×1024 y máscara de alpha.
CPU ×3 queda exacto. Compute ×3, con y sin snapshot de feedback, conserva
la misma diferencia de 1874 bytes y permanece estable entre pasadas. La
presentación reducida sigue idéntica porque esa escritura no cambia el buffer
visible actual. Proteger la fuente de toda la primitiva no resuelve este caso;
queda por contrastar el orden de lectura de páginas y la caché CPU de 8 KiB.

### Controles intermedios de variación OpenGL (7 de octubre)

`repetir_gs --checkpoints-sync --repeticiones N` compara huellas de los 4 MiB
en Flush, Sync, Present y End. El informe identifica el primer control que
varía entre pasadas. Los comandos elegidos ya drenan lotes; TEXFLUSH no lo
hace en GPU y queda fuera de esta sonda. Se mantiene la comparación exacta
del End, estado e imágenes. El historial se limita a 4096 controles, con
rechazo previo al replay. Añade readback, no mide FPS ni certifica igualdad
byte a byte intermedia cuando coinciden las huellas.

La CLI pública pasa cinco argumentos inválidos, tres recorridos CPU y el
rechazo del exceso antes de dibujar. Una regresión C++ usa la comparación
real del tool: una diferencia intermedia debe fallar aunque el End sea
idéntico. También verifica cantidad y metadatos. Ambas se ejecutan en CI
sin datos del juego; el helper Windows compila y ejecuta la regresión C++.

El tramo real CPU ×3 pasa sus trece controles y conserva igualdad exacta
final y visible. Compute ×3 con snapshot muestra el primer control variable
en el Flush del registro 73.288, tras 73.003 dibujos; ocho controles varían,
las dos imágenes visibles entre pasadas siguen idénticas y los contadores
son 632 lotes/99.402 primitivas/53.757 tiles en las tres pasadas. Los End GPU
consecutivos difieren en 4296 y 3977 bytes. No acredita estabilidad de toda
la VRAM ni paridad con CPU. El control reducido al primer sprite conserva
1874 bytes de diferencia también en hardware caliente, con cero tiles
compute; ese dibujo aislado permanece estable entre pasadas.

El control privado que elimina la caché de lectura del CPU altera 34.262
bytes del End de ese sprite y tampoco iguala OpenGL: no se incorporó al
runtime. Próximo paso: reducir el lote anterior al primer Flush variable y
contrastarlo con fuentes protegidas y formatos de VRAM, conservando CPU.

### Dependencia de color y profundidad en lotes OpenGL (7 de octubre)

La reducción mediante End derivados de CPU acota la variación observada a
los prefijos 68.897/68.898: el primero queda estable en cinco pasadas y el
segundo cambia 64–128 bytes entre algunas pasadas. El nuevo sprite pertenece
a una pareja que usa FBP=ZBP=320, FBW=1, PSMCT24/PSMZ24 y Z activo. Aunque
los rectángulos XY son disjuntos, color y Z reinterpretan la misma memoria.
Completar el lote antes del segundo sprite elimina la variación en ocho
pasadas. Esta bisección no certifica monotonicidad ni primer fallo global.

El caso procedural independiente del juego difiere de CPU en 6144 bytes
antes del cambio y coincide en los 4 MiB después. El nuevo parche
`ps2recomp-gs-target-alias.patch` separa lotes cuando páginas de color y
profundidad se cruzan entre primitivas. Conserva el renderer CPU y se aplica
después de los cincuenta parches anteriores. La detección es conservadora;
el alias interno de una sola primitiva sigue fuera del arreglo.

Tras la compilación oficial completa (código 0), el backend integrado repite el
tramo real en compute cuatro veces con snapshot y cuatro sin él: trece controles estables, End, estado y ambas imágenes exactamente
iguales entre pasadas. Son 648 lotes frente a los 632 anteriores y se
conservan 99.402 primitivas/53.757 tiles. Todavía difiere de CPU en 739.502
bytes y las dos presentaciones. No acredita paridad ni mejoras de FPS.

Validación integrada: **582/582** pruebas nativas, incluidas veinte pruebas
OpenGL; los controles nuevos cubren CT24/Z24 y CT32/Z32 compartidos, Z de
solo lectura, Z inactivo y buffers disjuntos, en compute y hardware efectivo.
También pasan las herramientas GS y las pruebas de argumentos/controles de la CLI.
El modo por defecto conserva trece controles estables igual que el snapshot.

### Integración de las PR #12, #17 y #18 (8 de octubre)

La #18 (`bfee1bb`) contiene todos los commits de la #17 (`b3d8cd6`). Se
conservan sus dos parches VU1 después de los 51 actuales, incluido el arreglo
GS de alias color/Z. La fusión de la #12 (`927c7b93`) conserva las versiones
actuales de DMA, VIF DIRECT, ramas EE, VU0, FPU y salto de cola: ya estaban
incorporadas en `ps2recomp-vu0-macro.patch`, `ps2recomp-vif-direct.patch` y
`ps2recomp-ee-fixes.patch`; no se añaden copias antiguas.

La pieza nueva de #12 es `ps2recomp-vu1-budget-diag.patch`, adaptada a
`StepContext` de #18. `GOW_VU1_BUDGET_DIAG=1` informa de cortes por presupuesto
con mensajes limitados; no aumenta los 65536 ciclos ni modifica el programa.
La regresión cubre presupuesto corto/cero, reanudación hasta E y reset, con
escrituras directas y con colas. El generador requiere datos locales del
usuario y el C++ derivado del juego nunca se publica.

La revisión detectó un fallo de flags persistentes en #17/#18: MADD con
producto subnormal y suma normal daba `status=0x000` con escrituras directas
y `0x140` con colas. `ps2recomp-vu1-sticky-preserve.patch` conserva los flags
del producto tanto en el intérprete como en los pares/bloques compilados.
La prueba nueva verifica también que un microprograma lector posterior los
observe. Se conserva el análisis de flags MAC temporales que nadie lee.

Resultado integrado: **55 parches** aplican en orden y sus **85 fuentes**
comparadas coinciden con el runtime compilado; `scripts\2_compilar.cmd`
termina con código 0 y actualiza el ejecutable. La suite nativa pasa
**565/565**, sin excluir fallos, y el generador pasa **60 casos procedurales**
con 139 pares compilados y 22 interpretados reales. CI recibe el mismo
control del generador; la validación GS anterior pasó además veinte pruebas
OpenGL opcionales. Dos cadenas VIF históricas del juego (`vif_pcsx2_inicio2`
y `vif_port_480s`) producen imágenes exactamente iguales con colas y
escrituras directas en el runtime integrado. Esta comparación no acredita
paridad con PCSX2 ni los FPS de una partida; las imágenes históricas no
son una referencia equivalente al nuevo modo aritmético.

La compilación oficial usa el intérprete si no se enlaza C++ VU1 derivado
de microprogramas locales. La infraestructura compilada queda verificada
con código procedural; falta integrarla en el flujo de compilación local
y repetir las medidas de rendimiento con los flags corregidos.

### Alias de coordenadas por ancho y vuelta de VRAM (8 de octubre)

El siguiente control procedural detecta un riesgo distinto del cruce color/Z:
con FBW=1, `(0,32)` y `(64,0)` de CT32 apuntan al mismo pixel. También se
repite una dirección al superar las 512 páginas de los 4 MiB. Compute ordena
primitivas por XY dentro de un tile; el interlock hardware también se aplica
al pixel XY. Ninguno ordenaba esos dos XY distintos del mismo destino.

Un lote con 64 sprites sobre el primer XY y otro sobre su alias pierde
6144 bytes en CT32/CT24 o 8192 en CT16/CT16S frente a CPU. Los controles
con páginas disjuntas y coordenadas repetidas dentro del ancho coinciden.
La base FBP=511 permite comprobar además el cruce del final de VRAM.

`ps2recomp-gs-coordinate-alias.patch`, aplicado al final de los 55 anteriores,
conserva por separado el riesgo de coordenadas en color y profundidad.
Completa el lote si el destino actual comparte páginas con uno anterior y
alguno supera el ancho de fila o las 512 páginas lógicas. La base FBP por
sí sola no activa el riesgo. La detección es conservadora por página: dos
escrituras fuera del dominio normal pueden separar lotes aunque sus pixels
sean distintos. No ordena alias internos de una sola primitiva.

Las dos regresiones opcionales cubren cuatro formatos de color, ambos
sentidos del alias, vuelta de VRAM, Z32/Z16 con color disjunto, Z inactivo
y controles que mantienen un único lote. Comparan los 4 MiB y comprueban
los contadores de rasterizado, sin aceptar fallback CPU como OpenGL.
El candidato pasa **587/587** pruebas nativas, incluidas 22 de OpenGL real.
Ambas regresiones fallan, también por los bytes de VRAM, al enlazarlas con
el backend anterior y el mismo resto del runtime.

La compilación oficial completa termina con código 0. Los **56 parches**
aplican en orden y las **85 fuentes** auditadas coinciden. La repetición
CPU ×2 conserva los trece controles, End y ambas imágenes exactos. Compute
×4 sin snapshot y ×4 con él también quedan estables; los 4 MiB del End y
las imágenes coinciden byte a byte con el backend anterior. No añade lotes
a esa traza: mantiene 648, con 99.402 primitivas/53.757 tiles y los mismos
contadores de CLUT y sincronización. Sigue difiriendo de CPU en 739.502
bytes y dos presentaciones; este arreglo no acredita paridad ni más FPS.

El control del ejecutable GS56 dura 510 s, con OpenGL, FMV omitido, VU1
directa por defecto y copia privada de la tarjeta guardada. Las 16 imágenes
512×448 son distintas; se observa a Kratos con forma correcta, ataques y
HUD con barras verde/azul, 87 orbes y R2 visible. El estado final es 11 sin carga
pendiente. Hay 128 muestras Clip finitas/completas, 848 tripletas tardías
no nulas y 192 contextos sin errores; no se registra VU reservada. La
tarjeta original conserva su SHA256. Estas capturas no certifican combate
completo ni FPS sostenidos.

### Ensayo de Z de solo lectura retenido (8 de octubre)

`writePages` incluye las páginas consultadas por el test Z aun con
ZMASK=1. Un ensayo local separó lecturas y escrituras para que textura/CLUT
y profundidad pudieran compartir un lote sin modificar esas páginas.
Sus controles procedurales pasaron en CPU, compute y hardware, incluidas
subidas sobre Z y escrituras antes/después de lectores.

En la traza real, el ensayo reduce 648 a 543 lotes y 53.757 a 46.543 tiles
compute, conservando 99.402 primitivas. Ocho pasadas compute y ocho
hardware con snapshot conservan End e imágenes anteriores. Estos
contadores no miden FPS ni certifican la caché física del PS2.

Sin embargo, el prototipo sin snapshot varió 200 bytes finales y una
presentación en una de 24 pasadas. Limitarlo a snapshot y conservar los
cortes anteriores en el modo habitual tampoco bastó: otra prueba larga
varió 128 bytes finales y una presentación, desde el registro 73.326,
Flush tras 73.036 envíos. **Se retiró la optimización completa de la
cadena publicada**, incluidas sus dos pruebas; código y datos quedan en
`logs/`, excluidos de Git. No se anuncia una mejora de FPS por este ensayo.

El control largo del GS56 real también varía una presentación (190 bytes)
en una de 24 pasadas; su primer control distinto está en el registro 36,
Flush tras 33 envíos. El End y el estado final son idénticos en las 24.
Hay feedback bilineal sobre el framebuffer en los tramos investigados,
pero la causa exacta sigue pendiente. Cuatro pasadas iguales no
certifican estabilidad. La referencia anterior al control largo no
incluía aún el parche de alias de coordenadas; aquí sí se enlaza GS56.

### Control STQ de hardware e integración de VU1 (8 de octubre)

El control STQ bilineal terminaba sus 16 matrices antes de que el
compilador asíncrono de shaders ofreciera hardware. Los píxeles y SSE
eran correctos, pero el control de hardware falló. El nuevo parche
`ps2recomp-gs-stq-hardware-test.patch` repite las matrices durante un
máximo de 12 s, conservando todos los oráculos RGBA, controles SSE y la
exigencia de hardware sin tiles compute. Un resultado correcto solo en
compute sigue fallando; no se modifica el renderer de producción.

Se integraron los siete commits terminados de Opus hasta `e507ac6`,
con sus bloques compilados, helpers, XGKICK y enlace opcional de VU1.
La compilación oficial final utiliza sus 501 micromemorias locales,
sin modificar ni publicar esos datos.

La compilación oficial final termina con código 0: **59 parches** en
orden y **87 fuentes** (`cpp/h/inl`) auditadas sin diferencias con el
runtime. Pasa **587/587** pruebas nativas, con **22 controles OpenGL
efectivos**, **60 casos VU1 exactos** (139 pares compilados y 22
interpretados), PAD2 y los controles de configuración, scripts, GIF y
selección VIF. La medición de FPS de Opus se conserva como resultado
de su tramo, sin extrapolarla al juego completo.

### Integración del planificador y control de partida (8 de octubre)

Se incorpora el `main` de la PR #20, `9f0ebc4`, conservando GS56, la prueba STQ de
hardware y la VU1 compilada. La compilación oficial termina con código 0, con
**60 parches**, las 501 micromemorias locales y un ejecutable de 67.710.976 bytes.
Las **87 fuentes** modificadas (`cpp/h/inl`) coinciden con la aplicación ordenada
de los parches sobre el commit fijado. Pasan **587/587** pruebas nativas, con
**22 controles OpenGL reales**, los **60 casos VU1 exactos** (139 pares compilados
y 22 interpretados), PAD2, configuración, sintaxis PowerShell, inspector GIF
(8 casos) y selección VIF (11 casos).

Un control limpio de 430 s, sin diagnósticos de geometría y con copia privada de
la tarjeta, produce **15 capturas distintas de 512×448**. La última, a 360,10 s
del reloj del mando, muestra a Kratos y varios enemigos en el barco, lluvia,
fondo y HUD; no se observan polígonos estirados en esa captura. El estado es
11, sin carga pendiente y con el nivel listo. OpenGL usa hardware y no aparece
VU reservada. La tarjeta original conserva su SHA256. La prueba anterior del
ejecutable de 59 parches también muestra esa escena con VU1 compilada.

Se descarta una comparación anterior de FPS: coincidió con otra compilación y
sus ventanas correspondían a estado 3 con carga pendiente. El nuevo selector
`resumir.py --partida`, cubierto por siete pruebas, exige informes de partida
cargada a ambos lados de las ventanas sin igualar los relojes del perfil y del
mando. Estos controles verifican integración y la escena observada; todavía
no certifican rendimiento sostenido, combate completo ni feedback GS fiel.

### Validación de 61 parches y reducción del feedback (8 de octubre)

La compilación oficial de `main` en `63c8a02` termina con código 0, con
**61 parches**, 501 micromemorias locales y un ejecutable de 67.710.976 bytes.
Las **87 fuentes** auditadas coinciden con la cadena publicada. FINISH sigue
síncrono por defecto; el test con backend retenido pasa en modo default y en
modo opcional asíncrono. Pasan también PAD2 y los **60 casos VU1 exactos**,
con 139 pares compilados y 22 interpretados.

El primer control local OpenGL pasa 584/587: tres casos coinciden en píxeles
pero no alcanzan su requisito de hardware efectivo. Se conserva ese registro.
Una repetición posterior pasa **587/587**, incluidas las **22 pruebas OpenGL**;
sus variantes se compilan en menos de dos segundos. No se amplían los plazos
ni se cambia el renderer para aceptar el primer fallo. La causa del fallo
intermitente de hardware todavía no se ha demostrado.

`repetir_gs --hasta-registro R` permite detener una traza en un Flush, Sync,
Present o End ya registrado. Compara exactamente los 4 MiB y el estado portable
CPU/candidato al terminar el prefijo, sin validar el End original cuando no se
ejecuta. Rechaza otros comandos e índices fuera del archivo antes de crear el
backend. El límite de 4096 controles se aplica al prefijo. Los controles CLI
cubren once argumentos inválidos, fronteras, un End alterado y límites.

El prefijo hasta el Flush **36**, después de **33 envíos**, reproduce la
referencia CPU y queda idéntico en CPU ×2. Se hacen 64 pasadas por política,
con restauración inicial exacta, los mismos 33 lotes y readback sincronizado:

| Ruta | Comparaciones consecutivas de la misma ruta | Comparaciones con VRAM distinta |
|---|---:|---:|
| Compute habitual | 63 | 4 (59 o 890 bytes) |
| Compute con snapshot | 63 | 0 |
| Hardware habitual, shaders listos | 61 | 61 |
| Hardware con snapshot, shaders listos | 48 | 0 |

Las pasadas compute tienen 544 primitivas/1760 tiles; las de hardware caliente,
544 primitivas/cero tiles. Las primeras 2 pasadas hardware habituales y las
primeras 15 con snapshot usan compute durante la compilación de shaders; se
excluyen de esas dos filas, junto con la transición a hardware. Las políticas
con snapshot conservan **515.877 bytes distintos
de CPU**, por lo que siguen devolviendo 1: estabilidad no implica paridad ni
fidelidad a la caché PS2. En este prefijo no se presenta ningún cuadro y los
readbacks/pausas no miden FPS. El corte reduce la investigación del feedback
de 146.015 registros a 36, sin publicar la traza ni alterar el modo habitual.

### VIF1/temporizadores y VU1 SIMD integrados (8 de octubre)

Se integran los dos commits terminados de la PR #21 (`8841ef0`, `b280247`) y
el primer commit SIMD de la PR #23 (`5e09b12`), conservando sus autores e
historia. Los conflictos de documentación y orden de parches se resuelven
incluyendo los tres cambios. La revisión detecta y corrige en `247a9b3` un
flag de underflow perdido por ADD/SUB SIMD cuando el PC usa FTZ/DAZ: cero
redondeado no implica cancelación exacta. La regresión dirigida falla antes
del arreglo con `status=1c0/c0` y pasa después; los valores de los registros
ya coincidían, por lo que comprobar solo la imagen no detectaba este fallo.

La compilación oficial de `247a9b3` termina con código 0: **64 parches**,
501 micromemorias locales y ejecutable de **70.182.400 bytes**, SHA256
`82ECCA22A4F4600FA60DB255D45176178971D60FF94382CC12D2E08BFC807074`.
Las **87 fuentes** auditadas coinciden con la cadena. Pasan **587/587 pruebas
nativas**, las **22 OpenGL efectivas**, los **60 casos VU1**, **100.800 casos
FMAC aleatorios y 2.016 FTZ/DAZ dirigidos**, PAD2 y ambos controles FINISH.
La prueba FMAC utiliza 359.856 pares compilados sin fallback al intérprete.
Configuración y sintaxis PowerShell también quedan correctas.

Un perfil limpio de 180,55 s, con FINISH síncrono, renderer OpenGL y copia
privada de la tarjeta, no observa compiladores ni otra partida en su vigilancia
cada segundo. Doce ventanas completas de partida cargada (60,04 s entre
103,06 y 163,12 del reloj del perfil) miden **7,58 vid::Flip/s**, con **57,71
presentaciones/s**. Los tiempos exclusivos del hilo del juego son VU **43,24 %**,
GS **38,20 %** (incluidas esperas), EE **12,20 %** e IOP **6,36 %**. La tarjeta
original conserva su SHA256. No se atribuye una ganancia a SSE por comparar
esta única pasada con otra escena; falta una comparación controlada y separar
el trabajo del GS de sus esperas. El treemap refleja SIMD y la reducción del
feedback, manteniendo GS y VIF1/VU1 parciales en los tres idiomas.

Durante estas pruebas Opus añade `754c970` (DIV compilada) a la PR #23 y abre
la rama de flags perezosos. **Esos cambios posteriores todavía no están en
este ejecutable**: requieren una revisión e integración propias. No se altera
el árbol de trabajo de Opus ni se anuncia que toda la PR #23 esté aplicada.

El control limpio del mismo ejecutable de 64 parches dura 430 s y conserva
**15 capturas distintas de 512×448**. La última, a **360,14 s** del reloj del
mando, muestra a Kratos, varios enemigos, barco, lluvia, fondo y HUD, sin
polígonos estirados visibles. Sigue en estado 11, `pending=0`, `levelReady=1`,
con hardware activo y sin instrucciones VU reservadas en el registro.
La tarjeta original conserva su SHA256; se utiliza una copia privada.
Es una comprobación de esa escena, con FMV omitido, y queda pendiente
verificar combate completo, otros escenarios y rendimiento sostenido.

### Atribución del profiler OpenGL (8 de octubre)

El diagnóstico GPU de 180 s sobre el ejecutable de 64 parches descubre que
los lotes hardware imprimen FBP, flags y primitivas como cero. Una consulta
engloba varias variantes de shader sin adjuntar su estado; esas líneas no
permiten identificar el destino que consume tiempo. En compute, el último
lote del umbral de 4096 consultas también pierde datos al resolverse la cola.
Esta ejecución sincroniza timestamps y añade registros: no mide FPS limpios.

`ps2recomp-gs-hardware-profile.patch` atribuye una consulta a cada variante
hardware y adjunta los datos compute antes de resolver las consultas.
El trabajo CPU de preparar esos datos queda fuera del intervalo GPU. Sin
`PS2X_GS_GPU_PROF=1`, las consultas siguen desactivadas. Dos regresiones
OpenGL reales fallan con el backend anterior y pasan con el borrador corregido:
dos variantes dentro del mismo lote y la frontera de 4096 lotes compute.
En ambos casos conservan exactamente los 4 MiB frente al CPU y exigen la ruta
GPU efectiva. La compilación oficial integrada se valida por separado.

La compilación oficial de `23fbce4` termina con código 0: **65 parches**,
501 micromemorias locales y ejecutable de **70.182.912 bytes**, SHA256
`6D7BA3034436D28141D4F429BD3D42ABD7BBA5F79166808CBD8410902F5736A1`.
Las **87 fuentes** auditadas coinciden con la cadena. Pasan **589/589 pruebas
nativas**, incluidas **24 OpenGL efectivas**, los 60 casos VU1, 100.800 FMAC
aleatorios y 2.016 dirigidos FTZ/DAZ, PAD2 y los dos modos FINISH.
El renderer CPU y la política habitual de feedback se conservan.

El diagnóstico corregido de **240,21 s**, con copia privada de la tarjeta y
sin compiladores ni otras partidas observados, alcanza estado 11 con el nivel
listo. La tarjeta original conserva su SHA256. Se seleccionan **280 informes
GPU completos**, encerrados por muestras de ese estado. El promedio de
timestamps raster es **39,26 ms/frame del profiler**; el grupo FBP=0,
flags=`4b` (textura, IIP, mezcla alfa y bilineal) acumula **30,13 ms/frame**.
Los siguientes grupos son `5a` (2,15 ms), `12` (2,08 ms) y `c8` (1,81 ms),
todos en FBP=0. La selección contiene también algunos lotes compute mientras
se preparan variantes. Es una pista para investigar shaders; no equivale a
FPS limpios, tiempo exclusivo de CPU ni atribución por primitiva. No se
compara esta cifra con el profiler anterior, que agrupaba datos vacíos.

Un ensayo privado elimina la llamada previa a `coversPixel` del fragment
hardware, porque las funciones de sombreado ya comprueban cobertura y bordes.
El control procedural alterna original/candidato/original: **8,80 / 9,01 /
8,75 ms** de mediana, 20 lotes por ejecución, 2000 triángulos IIP/STQ/
bilineal/ABE por lote, hardware efectivo y 4 MiB exactos frente al CPU.
Incluye envío y readback sincronizado; no mide FPS de partida. No demuestra
una ganancia, por lo que no se incorpora ni se añade a la cadena de parches.
Las fuentes y registros del ensayo quedan en `logs/` y el ejecutable publicado
conserva los 65 parches verificados.

La herramienta pública de rendimiento amplía el control previo a una
vigilancia cada segundo durante toda la pasada. Ante otra compilación o
partida, cierra solo su instancia, marca el registro como inválido y restaura
el entorno; el selector impide usarlo para calcular FPS o exportar JSON.
Pasan cuatro controles de scripts con procesos simulados y nueve del selector,
sin lanzar ni detener juegos o compiladores ajenos.

El siguiente diagnóstico de CPU utiliza una copia privada enlazada con
símbolos públicos a partir de los objetos optimizados. No sustituye el EXE
normal ni sirve para comparar FPS. El muestreo de 30 s en estado 11 muestra
esperas en el hilo principal y el del GS, pero descubre dos problemas de la
herramienta: inicialización duplicada de DbgHelp (error 87) y marcos de
llamadores recogidos sin imprimirlos. Se corrige el perfilador para mostrar
esa segunda vista y cerrar sus handles de hilos. La espera procedural de
`scripts\probar_perfil.cmd` falla antes de los cambios y pasa después, sin
usar el juego. Falta repetir el muestreo con esa atribución para distinguir
esperas de cola, driver y sincronización; no se asigna todavía una causa.

### Revisión de DIV compilado y PR #23 (8 de octubre)

La parte FMAC SSE de `5e09b12` ya estaba integrada; la novedad de la PR es
`754c970`, que especializa la instrucción inferior DIV. Se resuelven sus conflictos
con `main` conservando el arreglo FTZ/DAZ de `247a9b3` y los cambios posteriores.
No se incluye la optimización separada de flags de `df8c740`.

Los 60 controles anteriores no ejercitaban DIV. Se añaden **38.144 casos**:
16 selectores de componentes, valores límite y aleatorios, Q antes y después de
WAITQ, flags D/I, escrituras directas/con colas y cortes/reanudaciones, con y sin
FTZ/DAZ. Registros, Q y memoria coinciden bit a bit; flags y ciclos también.
Un fallo inyectado solo en una copia privada (latencia 6 en lugar de 7) falla en
el primer caso: Q y flags coinciden, pero los ciclos son `19/18`.

La compilación oficial integrada termina con código 0, **65 parches** y las
501 micromemorias locales. El ejecutable tiene **70.226.432 bytes**, SHA256
`EB8479487D9E572250BE1FFE618E2A8110386B5B1A14423A2AF924C45410068F`.
La auditoría de las **87 fuentes** no encuentra diferencias con los parches.
Pasan **589/589 pruebas nativas**, incluidas **24 OpenGL efectivas**, los 60 casos
VU1 anteriores y los nuevos de DIV, **100.800 FMAC aleatorios**, **2.016 FTZ/DAZ**,
PAD2 y FINISH default/asíncrono. La CI de la integración también pasa en Linux.
Las cifras de mejora de Opus pertenecen a sus capturas; esta revisión valida
paridad y compilación y no certifica nuevos FPS de la partida cargada.

### Linux: VU1 compilada sin activar, VBlank a 60 Hz y MADD sin FMA (10 de octubre)

- **VU1 compilada nunca se usaba.** En la fusión de Linux se perdió de `PS2Runtime::PS2Runtime()` la llamada
  `m_vu1.setDirectRegisterWrites(...)` (`ps2recomp-vu1-direct.patch`) y `setCompiledProgramsEnabled`
  (`ps2recomp-vu1-runner.patch`). Sin escrituras directas `compiledProgramFor()` devuelve siempre nulo:
  el intérprete con colas ejecutaba todo VU1. Restauradas ambas.
- **Microcódigo regenerado.** Los `programa*.cpp` del árbol venían de una versión antigua del generador
  (sin bloques). Con el generador actual y 1157 micromemorias: 5766 pares, 1360 bloques. En Linux
  (GCC 16, `-O3 -march=native`), `vu1_compiled_test` da 60 casos y 38.144 DIV exactos.
- **MADD sin FMA.** La reescritura SIMD de `execUpper` usaba `_mm_fmadd_ps` en MADD/MADDA (MSUB no), y GCC
  con `-mfma` fusionaba además `a*b+c` (`-ffp-contract=fast` por defecto). La FMAC de la PS2 redondea
  producto y suma por separado: ahora `mul`+`add` y `-ffp-contract=off` en los archivos de VU (fuera de
  MSVC). Instrucciones FMA en los objetos de VU: 52 → 0. `vu1_fmac_test 200`: antes fallaba con 1 ulp en
  un MADD normal; ahora solo en un caso de desbordamiento (intérprete `ff7ffffe`, compilado `ff7fffff`)
  que también falla con el `execUpper` escalar anterior: pendiente (posible `long double` de 80 bits en GCC).
- **VBlank a 60 Hz.** `run_gow.sh` pasa a `GOW_TARGET_FPS=60` y `GOW_UNLOCKED_FPS=0`. El modo
  desbloqueado adelanta ciclos del EE/IOP sin esperar al reloj (`accountCycles` → `advanceIopEeCycles`),
  y con ellos el SPU2.

Medición (`run_gow.sh`, `GOW_PERF_DIAG=1 GOW_PAD_TEST=1`, 150 s, media de las 10 últimas ventanas):

| | `vid::Flip`/s | VU ms por cuadro | IOP ms por cuadro |
|---|---:|---:|---:|
| Antes | 4,97 | 182 | 4,1 |
| VU1 compilada activada | 13,83 | 53 | 4,6 |
| + microcódigo regenerado, 60 Hz, sin FMA | 16,70 | 36 | 8,0 |

No se verificó la imagen ni el audio en esta pasada. Siguiente: el IOP por cuadro se duplicó.

**Corrección (mismo día):** las dos últimas filas de la tabla se midieron con la imagen rota. Con VU1
compilada el juego pintaba personajes blancos y sin texturas: `stepPairT` (`ps2_vu1_compiled.inl`) solo
restauraba VF0 si `vfWrite.reg == 0`, condición que nunca se cumple (`addVfWrite` ignora VF0), y nunca
restauraba VI0, mientras que `execUpper`/`execLower` y el LQ especializado escriben VF0/VI0 sin
comprobarlo. En una racha de pares compilados VF0/VI0 quedaban con basura (VI0 es la base de casi todos los
LQ/SQ) y los programas hacían menos trabajo, por eso parecían más rápidos. Se localizó con
`GOW_VU1C_RANGO` (0–1F8 y 200–3F8 por separado bien, juntos mal) y se arregla restaurando VF0/VI0 en cada
par, como `stepPair`. Regresión nueva en `tests/vu1_compiled_test.cpp` (LQ a VF00 y luego ADD con VF00):
falla sin el arreglo (`vf4=0,0,0,2/6,10,14,18`) y pasa con él.

Medición correcta (misma pasada de 150 s, 10 últimas ventanas; capturas comprobadas: menú, cubierta del
barco, Kratos, HUD y enemigos con texturas y colores correctos):

| | `vid::Flip`/s | VU ms por cuadro | IOP ms por cuadro |
|---|---:|---:|---:|
| Antes | 4,97 | 182 | 4,1 |
| Intérprete con escrituras directas (`GOW_VU1_SIN_COMPILAR=1`) | 5,57 | 152 | 7,7 |
| VU1 compilada con VF0/VI0 corregidos | 8,24 | 83 | 11,1 |

**Audio:** `ps2xRuntime/src/lib/spu2_time_stretch.h` (WSOLA: segmentos de 40 ms, solape de 8 ms,
búsqueda de ±7,5 ms) alarga la salida del SPU2 sin cambiar el tono cuando la emulación va más lenta que el
tiempo real, con un colchón de 100–300 ms que crece si la entrada llega a ráfagas. `GOW_AUDIO_STRETCH=0`
vuelve a la salida directa. Pruebas en `ps2xTest/src/ps2_spu2_tests.cpp`: sin huecos, 440 Hz conservados
a 0,3x y en ráfagas, sin saltos en las uniones, latencia acotada y silencio al cortarse la entrada.

### Linux: perfil por muestreo, despachador de VU1 con caché y contador de FPS (10 de octubre)

- **Perfil.** Sin `perf` (y con `ptrace_scope=1`), un muestreador propio que lanza el juego como hijo y lee el
  RIP de cada hilo con `ptrace` cada 2 ms (40 s de partida, 266.580 muestras). Hilo del juego: VU1 compilada
  39 %, ayudantes del intérprete de VU1 llamados desde ella 18 % (`commitReadyPipelines`, `updateFmacFlags`,
  `normalizeFmacExactResult`, `calculateFmacProductSticky`), IOP 11 %, VIF/GIF/GS 8 %, `accountCycles` y
  puntos de control 6 %, libc 6 %, código del EE recompilado 5 %. El hilo del GS espera el 90 % del tiempo.
- **Despachador con caché.** El `run()` generado probaba en cada entrada todos los bloques candidatos de la
  dirección y cada uno comparaba sus palabras con la micromemoria (`memcmp`; con 1157 micromemorias hay muchos
  candidatos por dirección). Ahora `tools/vu1/generar_vu1.cpp` genera tablas de candidatos y una resolución por
  dirección que se repite solo cuando cambia `VU1CompiledAccess::epoch()` (lo incrementa `compiledProgramFor`
  con cada versión nueva de la micromemoria o intérprete nuevo). Se conserva el orden de prueba (hasta 4
  bloques coincidentes; si hay más, se compara como antes) y los bloques solo comprueban las condiciones
  dinámicas (`blockReady`). `vu1_compiled_test`: 60 + 2 + 38.144 casos exactos.
- **`long double` → `double`** en el resultado exacto de las FMAC (`calculateFmacExactResult` y los pares
  compilados): en MSVC ya era `double`; con GCC era x87 de 80 bits. Mismo resultado en las pruebas; ganancia
  dentro del ruido (8,75 → 9,01 en la misma ventana). El caso de desbordamiento de `vu1_fmac_test` sigue
  pendiente: no lo causaba `long double`.
- **Contador de FPS en el panel F1**: cuadros del juego (entradas a `GOW_PERF_FRAME_PC`, independiente de
  `GOW_PERF_DIAG`), ms por cuadro, FPS de la ventana, historial de 60 s y, con `GOW_PERF_DIAG=1`, el reparto
  EE/VU/GS/IOP del hilo del juego.
- **`scripts/linux_perf_guard.sh`**: pasada con `GOW_PAD_TEST`, comprueba fuego en el menú y que no haya
  personajes blancos en las capturas 6/8/10, y da la mediana de las ventanas de 5 s desde t ≥ 60 s (la media
  de las últimas ventanas se inflaba con cargas a ~50 cuadros/s).

| Ejecutable (Linux, mediana t ≥ 60 s) | `vid::Flip`/s | VU ms por cuadro |
|---|---:|---:|
| VU1 compilada con VF0/VI0 corregidos | 8,78 | 79 |
| + despachador con caché y `double` | 13,38 | 46 |

Capturas comprobadas a ojo (menú, menú de mejoras, Kratos, HUD, enemigos y efectos).

### Linux: VBlank al reloj real, IOP en tandas y sincronización con KIexster (10 de octubre)

- **Cámara lenta.** Un VBlank esperaba a la vez a su ciclo del EE y a su hora del host: a ~20 cuadros/s solo había
  ~20 VBlank por segundo y el juego, que avanza su reloj por VBlank (paso en `0x29C64C`), iba al 38-43 % del
  tiempo real. `GOW_VBLANK_REALTIME=1` (ahora por defecto en `run_gow.sh`): al acabar cada rodaja del EE se mira el
  reloj y, si la hora del VBlank ya pasó, se adelantan los ciclos del EE (temporizadores, IOP y SPU2 incluidos) hasta
  él; con más de 200 ms de retraso (cargas) se descartan los VBlank perdidos. Medido con `GOW_DELTA_DIAG=1`
  (velocidad = tiempo de juego / tiempo real): 0,38-0,43 → 0,90-1,00, con 10-15 cuadros/s. El panel F1 muestra la
  velocidad ("Game speed").
- **`GOW_IOP_BATCH=1024`** (por defecto en `run_gow.sh`): el IOP avanza en tandas de 1024 ciclos del EE (como mucho
  ~3,4 µs por detrás) en vez de en cada punto de control: IOP 9,2 → 1,7 ms por cuadro, 13,3 → 15,8 cuadros/s.
- **Flags FMAC en línea** en el camino SSE de los pares compilados (sin llamar a `updateFmacFlags`): mediana de la
  partida 15,8 → 22,7 cuadros/s, VU 46 → 30 ms por cuadro, capturas correctas. Conjunto de diferencias de
  `vu1_fmac_test` (sin abortar) idéntico antes y después. Ese recuento muestra 8.115 de 100.800 casos distintos entre
  intérprete y compilado en Linux (sobre todo el bit O persistente con productos que desbordan): pendiente.
- **KIexster.** `tools/sync/sincronizar_kiexster.py` sincroniza con el remoto `kiexster` (historias distintas: allí
  parches, aquí PS2Recomp en el árbol) a tres bandas por archivo; `.kiexster-sync` guarda el punto (`a42d77f`). La
  primera fusión completa (hasta `947ebdd`, con `PS2X_VU1_HILO`/`PS2X_GS_FRENTE`) salió más lenta en esta máquina
  (16,4 cuadros/s) y se revirtió; queda guardada fuera del repositorio para incorporarla por partes, midiendo cada una.

### Reproducción de VU1, parches de KIexster uno a uno, PGO y controles de teclado (10 de octubre)

- **Banco de VU1.** `GOW_RENDER_DIAG=1` vuelca un cuadro de partida; `tools/render/extraer_cadena_vif.py --volcado ...
  --inicio 0x450C00` prepara la cadena (1502 etiquetas, 1,1 MB) y `repetir_cadena_vif` la repite sin ventana, fijado a
  un núcleo (`taskset`), con las variables de cola del GS de `run_gow.sh`. Huellas de VU1 (`GOW_REPETIR_HUELLAS`, 766
  lanzamientos) e imagen como control de igualdad bit a bit. El perfil de esta reproducción sin la escritura final
  del PPM (que vacía la cola del GS en cada píxel) es casi todo bloques de VU1 compilados.
- **Parches de KIexster aplicados uno a uno** (`tools/sync/sincronizar_kiexster.py --parche`), en su orden, con
  paridad (`vu1_compiled_test`: 60 + 2 + 38.144 casos) y banco tras cada uno: lazy-flags 34,2 → 34,0 ms;
  fast-flags 34,1 (neutro: ya estaban los flags en línea); zero-factor 33,9; direct-store 31,4; cold-scalar 30,8;
  simd-zero 29,5; xgkick-flush neutro; vif1-ee-timers-fast + vif1-unpack-formats 29,9 → 28,8 (con VIF1/memoria del
  árbol); chained-steps 28,3 (con el cambio equivalente en nuestro generador). dma-iop-timers-cache solo se mide en
  partida. block-check-cache no hace falta: nuestro despachador ya no compara palabras. Huellas e imagen idénticas a
  las del inicio de la sesión en todos los pasos.
- **PGO de VU1.** Clang compila VU1 algo más rápido (27,5 frente a 29,1 ms) pero el EE recompilado con Clang fue 15
  veces más lento en partida (3,8 cuadros/s): descartado. PGO de GCC (perfil de la reproducción con
  `-fprofile-generate`, `.gcda` colocados con la ruta de cada objeto de `build/`, opción `PS2X_VU1_GCC_PGO_DIR`):
  18,6 → 16,0 ms en la misma tanda, igual que Clang+PGO, huellas idénticas. En partida (`scripts/linux_perf_guard.sh`,
  ahora solo ventanas en estado 11): 21,1 cuadros/s de mediana con velocidad de juego 1,0, capturas correctas.
- **Teclado y ratón** (`ps2_pad.cpp`, `gowPad2Read`): ver `docs/CONTROLES.md`.
- **VIF1/VU1 en hilo propio** (`ps2recomp-vu1-thread`, `ps2recomp-gs-front-thread`, `PS2X_VU1_HILO=1`,
  `PS2X_GS_FRENTE=1`, desactivados por defecto) incorporados para medir en partida.

### Linux: VU1 con tiempos estáticos por bloque y parche fast-pairs de KIexster (10 de octubre)

- **Tiempos estáticos (etapa 1 del recompilador de VU1).** `tools/vu1/generar_vu1.cpp` calcula para cada par
  de un bloque el ciclo de emisión relativo a la entrada (mismas reglas que `readyCycleT`: latencias de
  VF/VI/ACC y FDIV escritas dentro del bloque). Lo que el bloque lee de fuera se comprueba al entrar; lo que
  lee el primer par se espera con `advanceTo` igual que el modelo dinámico. Si una guarda falla, o el bloque
  usa EFU/XGKICK/WAITP, se usa la versión dinámica (`<bloque>_d`, fría). Los ciclos "listo" se escriben al
  salir (solo el último valor de cada hueco; `flushS` para salidas a mitad de bloque). 1336 de 1360 bloques
  con tiempos estáticos; la versión dinámica es ~5 % del hilo de VU1 en la reproducción.
- **Parche `ps2recomp-vu1-fast-pairs` de KIexster (95e7a30)** integrado a mano (3 trozos no aplicaban):
  escrituras de VF de 16 bytes con blend, MAC/estado por tabla, `recordViWriteForBranch` en línea y sin
  `m_state.cycles` por par (`run()` lo fija al terminar). En GCC es neutro (su -15 % venía sobre todo del
  despachador que MSVC no optimizaba); se mantiene por coincidir con su `main`.
- Medido en la reproducción de un cuadro de partida (núcleo fijo, mediana de 5): 18,4 → 16,1 ms sin PGO;
  con PGO regenerado 16,3 → 14,8 ms. Huellas de VU1 (`8c71fe9fb9754a73`), imagen (`189611644956d250`),
  `vu1_compiled_test` (60 + 2 + 38144) y el recuento FMAC (8115 diferencias previas, ninguna nueva)
  idénticos.
- Probado y descartado: `commitReadyFlags` en línea en `pushFmacFlags` (más lento).

### Linux: etapa 2 de VU1 (guardas) y ronda 2 de KIexster (11 de octubre)

- **Guardas mínimas.** `generar_vu1` barre el decodificador con todos los códigos de operación y obtiene la
  latencia máxima con la que algo deja listo un VF (4), un VI (4) o el FDIV (13). Un "listo" se fija como
  emisión + latencia con la emisión anterior a la entrada del bloque, así que una guarda con límite >= L - 1 no
  puede fallar y no se emite; tampoco las de VF0 (nunca se marca). 26 326 → 8 261 comparaciones. Los cuatro
  componentes de un VF con el mismo límite o el mismo "listo" final se comprueban / escriben con una operación
  de 32 bytes (`vfReady4After`, `setVfReady4`). Reproducción: 16,3 → 15,5 ms (solo guardas), huellas e imagen
  idénticas.
- **Cotas medidas** (incorrectas a propósito, solo para decidir): sin normalizar operandos de FMAC
  15,6 → 14,4 ms; sin cola de flags el resultado no sirve (los saltos por flags cambian el recorrido).
- **KIexster 353ac83** integrado: `vu1-lazy-decode` (sustituye a la decodificación incremental), PATH1 por
  eventos (`vu1-path1-events`, también en `stepS`), FLG=3 como IMAGE en XGKICK y `gif-arbiter-buffers`.
  Su despacho por "última variante" no se toma: el despachador de Linux ya resuelve el bloque de cada dirección
  una vez por versión de la micromemoria.
- Resultado en el juego (`scripts/linux_perf_guard.sh`, 150 s, mismas condiciones; binario anterior frente al
  nuevo con PGO regenerado): VU1 30 → 20 ms por cuadro, EE 39 → 29 ms, flip mediano 23,6 → 30,8 cuadros/s;
  capturas 6/8/10 sin personajes blancos. La reproducción (PATH1 inmediato, una sola carga de microcódigo)
  solo mostraba 16,3 → 15,2 ms: la decodificación perezosa y PATH1 por eventos pesan más en partida.
  Pendiente: compilar `ps2x_tests` con la prueba nueva de FLG=3.

### Linux: perfil en partida, despachador compacto y normalize4 sin blendv (11 de octubre)

- **Perfil en partida** (GOW_PAD_TEST + muestreo, 30 cuadros/s): hilo de VU1 66 % ocupado (~22 ms por cuadro),
  EE 48 % (~16 ms), frente GS 13 %. Para 60 cuadros/s ambos deben bajar de 16,7 ms. En el EE, ~18 % de su tiempo
  ocupado es `accountCycles` (el IOP/SPU2 y los temporizadores puestos al día tras cada espera) y otro ~23 % el
  IOP/SPU2: candidato a un hilo propio.
- **Despachador:** entrada de resolución de 32 bytes (dos por línea de caché) con el primer bloque y el par a
  mano; los demás bloques que coinciden van aparte. Reproducción 15,3 → 15,1 ms.
- **PATH1:** dentro del cuerpo de una GIFtag los qwords que alcanza el crédito se copian de una vez (tramos
  contiguos; el último de la etiqueta sigue por el camino de siempre). Huellas iguales con XGKICK inmediato y
  ciclo a ciclo (`7b38ffbbc80e3eb4`). Neutro en la reproducción; en partida `xgkickCopy` era ~2,6 % del hilo.
- **normalize4 sin blendv:** con a = |bits|, `min(a, 0x7F7FFFFF) & (a > 0x007FFFFF)` y el signo: 6 operaciones
  simples. Comprobado igual en los 2^32 patrones. 15,15 → 14,9 ms.
- **Probado y retirado:** saltar la normalización de operandos que una FMAC del mismo bloque dejó normalizados
  (parámetro Known de `upperT`). La ruta escalar puede dejar un subnormal en un caso extremo (cancelación en
  MADD sin FTZ), así que hace falta una comprobación en tiempo de ejecución, y esa comprobación se come la
  ganancia (15,2 → 15,3 ms con ella; 14,8 sin ella, que no sería exacto). Queda la prueba nueva de
  `tests/vu1_compiled_test.cpp` (FMAC escalar con producto que desborda y lectura en el mismo bloque).
- **ITOF/FTOI/ABS con SSE** (`upperT`): los cuatro carriles a la vez. El escalado es por potencias de dos
  (exacto salvo desbordar), `cvt` usa el redondeo del MXCSR como `static_cast` y `cvttps` da INT_MIN fuera de
  rango; el lado positivo se corrige a INT_MAX. Comprobado contra `vu1c::floatToInt` y el ITOF escalar en
  160 M casos (límites y aleatorios) con redondeo al más cercano y hacia cero: 0 diferencias. Reproducción
  15,05 → 14,43 ms, huellas e imagen idénticas.

### Linux: ronda 3 de KIexster y el flag O con redondeo hacia cero (11 de octubre, tarde)

- **KIexster a279888 (ronda 3 de VU1)** integrado en parte: `vu1-static-stores` (VF0/VI0 solo si el par puede
  escribirlos; también en `stepS`; la lista `lowerInline` coincide con la cadena de `lowerT`, comprobado caso a
  caso), `vu1-lower-specials`, `vu1-advance-events` (en el `advanceTo` de Linux, solo la rama con PATH1 activo) y
  `vif1-unpack-mask-sse`, más su programa de 936 casos en `tests/vu1_compiled_test.cpp` (en 0x1000; las pruebas
  de VF0 y de FMAC escalar pasan a 0x1200 y 0x1300). No se toman `vu1-simd-specials` ni `vu1-xgkick-bulk`
  (Linux ya tenía su equivalente) ni su despacho por "último bloque" (el de Linux resuelve por versión).
  `gs-source-address` integrado. `ee-cop0-count` no: cambia la traducción del EE (`cop0_translator`) y haría
  falta regenerar el código del juego.
- **Flag O en Linux:** `run()` pone redondeo hacia cero con `fesetround`; en Linux eso también cambia el MXCSR, y
  un producto o suma que desborda da el máximo finito (exponente 0xFE), no Inf. El camino rápido del intérprete
  (`normalizeFmacResult`) solo excluía el exponente 0xFF y perdía el flag O; el código compilado ya excluía 0xFE.
  Con `exp < 0xFE` en el intérprete, las diferencias FMAC intérprete/compilado bajan de 8115 a 80 y la prueba de
  especiales (que tenía un MUL que desborda) pasa. Las 80 restantes son OPMSUB/MADD/MSUB con operandos Inf/máximo
  cuyo producto desborda: el intérprete satura la suma exacta y el compilado no; quedan anotadas.
  `productSumFlagsFast` excluye también ep > 0xFD como el camino SSE.
- Reproducción: 14,4 → 13,9 ms con la ronda 3; huellas iguales en los dos modos de XGKICK.
- Las herramientas de medida (reproducción, huellas, pruebas, generador, perfiles) están ahora en
  `logs/herramientas/` (no se publica; `logs/` está en `.gitignore`).

### Linux: 30 cuadros/s por ciclos del EE, GPU llena y ventana a 6 cuadros/s (11 de octubre, noche)

- **Ventana a 6-10 cuadros/s con el juego a 50-60:** `latchHostPresentationFrame` hacía Flush + Sync + Present con
  `RunOnWorker` en cada VSync y esperaba a que el hilo del GS vaciara su cola. Nuevo buzón de presentación
  (`PS2X_GS_PRESENT_BUZON=1`, por defecto en `run_gow.sh`; sin contexto GL compartido): Present y Sync se encolan
  en orden, el hilo del GS deja el cuadro en el buzón y el hilo principal muestra el último sin esperar.
- **`GOW_FRAME_DIAG=1`:** por cuadro del juego, ciclos emulados, VBlanks, espera de ritmo y ciclos de alcance.
  En partida: ~10 M ciclos y 2 VBlanks por cuadro (VBlank = 4,92 M) con el EE esperando al reloj ~540 ms/s: el
  juego iba a 30 por la cuenta de ciclos (32 por vuelta de bucle, 8 por llamada), no por el host.
- **`GOW_EE_CICLOS` (por ciento, 50 en `run_gow.sh`):** escala los ciclos que cobra el código del juego (el "EE
  cycle rate" de PCSX2). Con el VBlank al reloj real la velocidad del juego queda en 1,00 (`GOW_DELTA_DIAG`).
  Medido al 50 %: 30 → 38-43 cuadros/s en partida, 1,4-1,6 VBlanks por cuadro.
- **La GPU (Radeon 680M) queda al 100 %:** el rasterizado por hardware necesita
  `GL_ARB_fragment_shader_interlock`, que radeonsi no ofrece, así que en AMD/Mesa todo va por el rasterizador de
  cómputo: 10-13 ms de GPU por cuadro (`PS2X_GS_GPU_PROF`), 60-200 dispatches y tiles con hasta ~1800 primitivas.
  Con la GPU llena el hilo del GS iba decenas de ms por delante (esperas del anillo de 30-90 ms) y el intercambio
  de la ventana esperaba detrás.
- Cambios (sin medir todavía):
  - Tiles de 8x8 en el rasterizador de cómputo (`PS2X_GS_TILE=16` vuelve a 16x16): cada pixel recorre solo las
    primitivas que tocan su tile de 8x8 y los tiles muy cargados se reparten en cuatro. Mismo orden por pixel. El
    dispatch se parte en trozos de 65535 grupos (`uRaster.y` = primer tile).
  - Como mucho 2 presentaciones de trabajo pendiente en la GPU (`PS2X_GS_GPU_CUADROS`, 0 desactiva): el hilo del
    GS espera la valla de hace dos presentaciones (100 ms como mucho).

### Linux: RTX 4050, sonido "en bucle" y límite de ventana a 120 (12 de octubre, madrugada)

- **GPU dedicada:** con el portátil en modo híbrido `run_gow.sh` usa la NVIDIA (PRIME offload) si `nvidia-smi`
  responde (`TOBIICHI_GPU=integrada` para la AMD). La NVIDIA tiene `GL_ARB_fragment_shader_interlock`. En partida el
  rasterizado cuesta 4-7 ms de GPU por cuadro del juego (en la 680M 20-26 ms): la GPU deja de limitar.
  - Corrección (12 de octubre, mañana): la NVIDIA ya no es la opción por defecto. `run_gow.sh` usa la GPU del
    sistema (la integrada AMD, rasterizador de cómputo puro) y `TOBIICHI_GPU=nvidia` activa el PRIME offload.
- **Sonido "en bucle":** con `GOW_AUDIO_DIAG=1` (nuevo; tramas llegadas/sacadas, tempo, colchón, vaciados por
  segundo) se vio que el estirado no se vaciaba nunca pero su tempo oscilaba entre ~0,82 y ~1,28 cada 20 ms: la
  entrada llega a ráfagas y cada segmento de 40 ms repetía o saltaba hasta un 25 %. Dos causas y sus arreglos:
  - `TimeStretch::pull`: zona muerta. Cerca del tiempo real y con el colchón en 0,5-2,5 veces el objetivo, tempo
    exactamente 1 y el segmento siguiente es la continuación natural (sin búsqueda): la salida es la entrada.
    Fuera del margen, corrección suave (±5 %); el estirado fuerte solo si la emulación va lenta o falta poco
    para vaciarse. Prueba nueva en `ps2_spu2_tests.cpp` (rampa a ráfagas: sin muestras repetidas ni saltadas;
    falla con el código anterior).
  - Reloj del IOP ~2 % por delante del EE: `runCycles` avanzaba "posición actual + ciclos" y lo que el IOP corre
    durante una RPC del EE (`runReadyThreads`, `waitOutsideThread`) y el exceso de cada tramo de CPU nunca se
    descontaba (el SPU2 daba ~49.100 muestras/s). `IopEmulator::runEeCycles` lleva ahora la cuenta de ciclos
    concedidos por el EE y devuelve el adelanto (deuda máxima 1/30 s; `GOW_IOP_RITMO=0` lo desactiva).
  - Además el salto ocioso del IOP se limita a 32 muestras del SPU2 (`GOW_SPU2_PASO`) para que su IRQ (rellenado
    del búfer de streaming del driver de sonido) no llegue con hasta un VBlank de retraso.
  - Resultado en partida: llegada 48.097 muestras/s, tempo exactamente 1,00 en 145 de 146 segundos, sin vaciados.
- **Ventana a 120 cuadros/s** (`TOBIICHI_VENTANA_FPS`, 120 por defecto): la pantalla del portátil es de 144 Hz.
- **Compilación:** el `.ninja_deps` se había corrompido (dos compilaciones a la vez) y cada cambio recompilaba los
  937 objetos (~17 min); tras `ninja -t recompact` y una compilación completa, un cambio de un archivo tarda ~9 s.
- Suite `ps2x_tests`: 562 pasan; fallan las 3 de siempre (UV/STQ de triángulos en CPU, división/raíz del FPU con
  MXCSR hacia cero). Se quitó `forceReadback` de una prueba de `gs-source-address` (no existe en Linux).
- **Dónde está el límite de cuadros (NVIDIA):** en partida el EE termina su trabajo y espera (sondeando) a que
  VU1/GS acaben el cuadro; con `GOW_EE_CICLOS` al 50 % los ciclos por cuadro siguen en ~9,8 M (2 VBlanks), así que
  no es trabajo del EE sino la espera. El hilo de VU1 (VIF1 + VU1) tarda ~16-27 ms por cuadro según la escena:
  por debajo de 16,7 ms el juego pasa de 30 a 60.
- **VIF1 UNPACK:** sin división por vector para la posición en el ciclo (CL/WL contados a mano, en el camino rápido
  y en el de máscara SSE) y lectura de 16 bytes de una vez en el de máscara cuando cabe en el paquete (antes un
  `memcpy` de tamaño variable por vector, una llamada a libc). En partida VIF1 pasó de ~12 % a ~3 % del hilo de VU1.
  Reproducción 13,9 → 13,4 ms.
- **Pares "libres de PC" en los bloques estáticos:** un par intermedio con las dos instrucciones en línea no escribe
  `m_state.pc` (el último par del bloque nunca lo es; si el bloque se para antes, la salida lo escribe) ni mira
  `programEnded`, y el borrado de la copia de VI para saltos se decide al generar (idea de KIexster). 13,4 → 12,8 ms.
- **`commitReadyPipelines`:** el camino rápido (solo flags) cubre también un FDIV pendiente (uno por vértice en la
  perspectiva), con el mismo orden y el mismo siguiente ciclo que el camino general. 12,8 → 12,6 ms.
- Huellas (`8c71fe9fb9754a73` / `7b38ffbbc80e3eb4`), imagen, pruebas de VU1 compilada (incluidos los 936 especiales)
  y recuento FMAC (80) iguales en cada paso. PGO regenerado.
- **Saltos IBxx:** `readBranchVi` (en `ps2_vu1_core.cpp`, una llamada por salto de bucle) en línea dentro de `lowerT`, y
  la máscara de la micromemoria como constante de VU1 (el código compilado solo corre en VU1). 12,6 → 12,3 ms.
- **Probado y descartado esta noche:** bucles de un bloque sobre sí mismo sin pasar por `run()` (199 bloques, exactos,
  sin ganancia medible: la llamada indirecta se predice bien); MAC/estado/CLIP en variables locales en
  `commitReadyFlags` (algo más lento). Cota: quitando del todo las llamadas frías de cada par (commit, PATH1, ruta
  escalar; resultado incorrecto) la reproducción baja solo un 12 %: no compensa reestructurar los bloques con
  salidas a la versión dinámica.
- **Resultado en partida** (`logs/herramientas/prueba_partida.sh`, NVIDIA, perfil de energía "balanced"): mediana
  de cuadros del juego 30 → ~55; gran parte de la partida a 54-60; las escenas más pesadas siguen a 30 (VU1 ~26 ms
  por cuadro allí). Ventana a 120, velocidad del juego 1,00-1,03, sonido sin estirar.
- **Dónde se va el tiempo en una escena pesada (30 cuadros/s):** el hilo de VU1 está ocupado ~76 % (~25 ms por
  cuadro; 78 % de eso es código compilado) y el resto espera datos del EE: `GOW_VU1_SYNC_DIAG=1` da 0 esperas del
  EE por VU1, así que no hay serialización EE↔VU1. Contadores de hardware (`logs/herramientas/contadores`, con
  `perf_event_open`, sin la herramienta perf): IPC ~3,1 y 0,5 % de saltos fallados; el coste lo pone el número de
  instrucciones (~90 por par en un bloque FMAC). 60 cuadros/s ahí piden ~1,5 veces más velocidad de VU1.
- **FMAC (camino rápido), todo bit a bit igual:**
  - MADD/MSUB: primera criba barata (rango del resultado y del producto, factor cero); la de factor ±1 y
    cancelación exacta solo se calcula si algún carril no pasa.
  - Rangos de exponente sobre `|bits|` con una suma y una comparación con signo; factor cero con `cmpeq_ps`.
  - Con flags muertos y estado sin leer, los bits pegajosos S/Z salen de un `movemask` cada uno.
  - `m_currentUpperInstruction` solo se escribe en la ruta escalar (es la única que lo lee).
  - Sin `normalize4` sobre ACC, Q e I: en VU1 solo los escriben resultados ya normalizados (FMAC, `queueQ`, LOI).
    El recuento FMAC con valores aleatorios en ACC/Q/I da más diferencias (valores imposibles en hardware); con
    `FMAC_ACC_NORMAL=1` (ACC/Q/I normalizados) sigue en 80, igual que antes del cambio.
  - CLIP: las seis comparaciones con dos `cmpgt` y una tabla, y `queueClip`/`pushFlagEntry` en línea; los
    lectores de flags (FCAND, FMEQ, FMAND, FCGET) no llaman a `commitReadyFlags` si la cabeza de la cola no está
    lista.
  - DIV: `normalizeResult` y `queueQ` en línea (dos llamadas por DIV).
  - Sin escribir `m_currentUpperInstruction` en NOP ni en los especiales.
  - Reproducción 12,35 → ~10,9 ms; instrucciones −8,8 %, ciclos −10,5 %. En la noche entera, 13,9 → ~10,9 ms.
- **Probado sin ganancia:** fijar los hilos (VU1, EE, frente del GS, GS) a núcleos físicos distintos con `taskset`
  (el planificador casi nunca junta VU1 con otro hilo ocupado en el mismo núcleo: 2 de 75 muestras).
- **Probado sin ganancia:** `-O2` en el código de VU1 (texto −3 %, +1 % de ciclos, más fallos de L1i); escribir el
  estado pegajoso y la copia de VI para saltos solo si cambian (+4 % de ciclos con las mismas instrucciones). Las
  diferencias de ±4 % entre compilaciones sin PGO pueden ser de colocación del código: para cambios pequeños, mirar
  instrucciones y ciclos (`contadores`) además del tiempo.
- **Cola de flags (para decidir el siguiente paso):** en la reproducción, de 14,7 M pares el 53 % son FMAC del
  camino rápido, el 30 % con flags muertos y estado sin leer (solo bits pegajosos), el 21 % encola flags de FMAC y el
  2,4 % de CLIP: ~0,24 entradas por par, ~27 instrucciones cada una (encolar y confirmar), ~7 % del tiempo de VU1.
  Una cola de flags estática en los bloques ganaría como mucho ~5 %. No sirve quitar la cola para medir una cota:
  los flags (CLIP/FCAND) deciden saltos del microprograma y el trabajo cambia.
- **Estado al final de la noche:** binario instalado = PGO de esta versión (copia en
  `~/.cache/tobiichi-sync/ps2EntryRunner.final_10120432`). En partida: imagen correcta, sonido a tempo 1,00, velocidad
  1,00, ventana 120; 60 cuadros/s en escenas ligeras y medias, 30-34 en las más pesadas (VU1 ~19-21 ms por cuadro;
  para 60 hacen falta ≤ ~15 ms).

### Lanzador "God Of War: Tobiichi Launcher" y pantalla panorámica (12 de octubre, mañana)

- **GPU por defecto:** `run_gow.sh` ya no elige la NVIDIA sola (ver la corrección de arriba).
- **Lanzador** (`launcher/`, Qt 6 Quick, turco/inglés/español): tarjeta gráfica, modo de pantalla y resolución,
  aspecto (panorámica Hor+), escalado (FSR 1.0 / bilineal / píxel, FXAA, nitidez), límite de FPS, VSync,
  contador, rutas del juego con comprobación (CRC del ELF, ISO o archivos extraídos, ejecutor), controles y
  opciones. Arranca `ps2EntryRunner` con las variables `TOBIICHI_*`; detalle en [`LANZADOR.md`](LANZADOR.md).
- **Runtime (sin las variables nuevas todo queda igual):**
  - pantalla completa con el modo de vídeo actual (`ToggleBorderlessWindowed` dejaba la ventana en 922x1074 con
    KWin/XWayland);
  - proporción configurable y escalado AMD FSR 1.0 (EASU + RCAS) / FXAA en el hilo principal;
  - contador de FPS en la imagen;
  - título, icono y Escape configurables;
  - panel F1 oculto con `TOBIICHI_PANEL=0`;
  - capturas de la ventana para pruebas (`TOBIICHI_CAPTURAS`).
- **Panorámica:** parche "Widescreen 16:9" de PCSX2 (nemesis2000 y CRASHARKI) aplicado al recompilar
  (`config/recomp.template.toml`: `sub_00169238` y 0x21E4F0, con F y el indicador de vídeo leídos de 0x7F00/0x7F04).
  El runtime escribe esas palabras en cada VBlank (`gowPanoramicoVBlank`). Sin `TOBIICHI_PANORAMICO`, F × aspecto =
  1,0 exacto (0,75 × 4/3 y 0,5625 × 16/9 dan `0x3F800000`), así que la proyección es la del original bit a bit.
  - El template reproduce exactamente `generated2` (6418 archivos, 0 diferencias). Copia de los tres archivos
    anteriores en `~/.cache/tobiichi-sync/generated2_antes_panoramico/`.
- **Verificado** (Radeon 680M, 1920x1200), `logs/perf_lanzador2`, 150 s con las variables del lanzador:
  - guarda de imagen OK;
  - velocidad 1,00;
  - ventana 105-120;
  - juego 60 en menús y 30 en partida (la integrada al 90-100 %);
  - sonido a tempo 1,00;
  - capturas 1920x1200 en 16:10 con personajes en proporción (Hor+) y HUD estirado.

  El lanzador de punta a punta (`--jugar`) encontró los archivos y arrancó el juego a pantalla completa.
- **No hecho:** resolución interna 2×-4×. El GS se emula a su resolución sobre la VRAM entrelazada; haría falta
  una VRAM supermuestreada (como paraLLEl-GS), y el rasterizado costaría ~4× a 2×.

### Sonido: bucles que vuelven al principio y voces que no se apagan (12 de octubre, tarde)

- **Síntoma:** música, diálogos y efectos "se repiten", no fluyen. La salida al host ya estaba a tempo 1,00, así que
  el fallo estaba en lo que producía el SPU2.
- **Diagnóstico nuevo, opcional:**
  - `GOW_SPU2_DIAG=1`: por segundo de audio emulado imprime voces activas, KON, fin de bloque con/sin repetir, IRQ,
    ADMA, barridos, NON/PMON, ATTR, MMIX y ADMAS.
  - `GOW_SPU2_PCM=<archivo>`: guarda la mezcla en s16le estéreo.
  - En partida: sin IRQ del SPU2 (ATTR sin bit 6), sin ADMA, sin barridos de voz ni NON/PMON. El núcleo 1 tiene la
    reverb activada (ATTR `c081`), que aún no se emula.
- **Dos fallos, ambos frente a PCSX2:**
  1. **KON ponía LSA = SSA.** El driver escribe la dirección de bucle antes de KON (2-12 veces por segundo) y se
     perdía: los sonidos con bucle volvían a su principio en lugar de a su bucle. KON ahora conserva LSA, como
     `V_Voice::Start`; la marca de inicio de bucle de los datos sigue mandando mientras no se reescriba el registro.
  2. **Bajada exponencial del ADSR con división** (redondeo hacia cero). En las tasas lentas el paso se quedaba en 0
     por debajo de ~0x1000 y la voz no se apagaba nunca: seguía repitiendo su bucle al ~12 %. Ahora es un desplazamiento
     aritmético, como `V_ADSR::Calculate`, y el sustain que baja a 0 apaga la voz.
- **También:** una IRQ del SPU2 que llega mientras se atiende otra ya no se pierde. Hoy no influye, el juego no usa
  la IRQ.
- **Resultado** (100 s con `GOW_PAD_TEST`, mismas condiciones):
  - voces activas de media 26,7 → 17,8;
  - finales de bloque que vuelven al bucle 25,5 → 16,6 por segundo; sonidos que terminan 7,9 → 23,2 por segundo;
  - segundos con repetición casi exacta de la mezcla (correlación > 0,995 con algo de hasta 0,5 s antes) 7 → 2. Los
    2 que quedan son el bucle de 350 ms del fuego del menú, a volumen bajo, que también está en el original.
  - Tempo 1,00 y guarda de imagen sin cambios (capturas 0/6/8 bien; la 10 no existe en 100 s).
- **Pruebas:**
  - nuevas: "key on keeps a loop start written before it" y "a slow exponential release reaches silence"; las dos
    fallan con el código anterior;
  - "an active voice is mixed into the stereo output" usa ahora la marca de inicio de bucle (0x07): dependía de
    LSA = SSA;
  - suite: 564/567, las 3 de siempre.
- **Pendiente:** reverb del SPU2 (efectos y voces más secos que en la consola), barrido de volumen e interpolación
  gaussiana.
- **Causa real de la música "en bucle" (misma tarde): NAX.**
  - Traza de la voz de la música (`GOW_SPU2_TRAZA=10`, núcleo 1 voz 0: eventos KON/KOFF, LSA/SSA, fin de bloque y
    lecturas de NAX). El driver de streaming usa un búfer doble por canal (L: 0x2820 y 0x7820; R: +0x800) con marca
    fin + repetir en el último bloque de cada trozo, y escribe LSA para que la voz salte al otro trozo.
  - La voz saltaba bien de A a B, pero casi nunca de B a A. Al decodificar el último bloque de B, nuestro NAX ya
    valía "bloque + 8" (0x8020, el trozo del canal derecho). El driver, que lee NAX sin parar, creía que la voz se
    había salido, hacía KOFF y relanzaba la música desde A cada ~0,35 s (el bucle que se oía). La marca de fin sí
    estaba en los datos (cabecera 0x0312).
  - Arreglo:
    - el fin de bloque (ENDX, salto a LSA o parada) se resuelve al tocar su última muestra;
    - NAX se lee como en el hardware: la media palabra en curso dentro del bloque que suena y, terminado el bloque,
      el siguiente (LSA si había fin) pasada su cabecera;
    - nunca sale del trozo.
  - Con el arreglo la voz alterna A ↔ B cada ~7.800 muestras sin KOFF/KON. Lo mismo vale para diálogos y ambiente
    (mismo driver). El usuario lo confirmó escuchando: la música suena entera.
  - Prueba nueva "NAX stays inside the playing block until the loop jump" (falla con el código anterior). Suite
    565/568, las 3 de siempre.
- **Diagnóstico** (todo opcional):
  - `GOW_SPU2_DIAG=1`: además de lo anterior, bloques de streaming nuevos/viejos por voz (contador de escrituras
    DMA por bloque), tono medio aplicado y saltos de bucle.
  - `GOW_SPU2_TRAZA=<núcleo><voz>`: hasta 700 eventos de una voz.

### Lanzador: controles configurables y L2 (12 de octubre, tarde)

- **Pestaña "Controles" nueva:**
  - dos teclas o botones del ratón por acción, en grupos (movimiento, combate, poderes, menús, avanzado);
  - captura a toda la ventana; Escape cancela, clic derecho borra;
  - conflictos en ámbar, "Teclas por defecto";
  - esquema del mando (moderno/clásico) aparte.
- **Esquema por defecto (el del usuario):** WASD mover; Ctrl + WASD esquivar; 1-4 poderes (cruceta); clic izquierdo
  y derecho ataques; F agarrar; Q L1 (parada); Shift L2 (antes no había L2 en el teclado); Ctrl R2; E R1; V L3 + R3;
  flechas cruceta; Enter Start; Tab Select.
- **Juego:** `TOBIICHI_TECLAS` (`ps2_pad.cpp`) para botones y sticks. `ps2_runtime.cpp` envuelve `scePad2Read`
  (0x27B9F0, `gowPad2Read`) para sustituir sus sticks fijos sin tocar los overrides.
  - Una tecla que es a la vez el modificador del stick derecho y un botón solo cuenta como botón si no se mueve
    (Ctrl = R2 y Ctrl + WASD = esquiva).
  - Sin la variable, el teclado sigue como antes.
- **Verificado:**
  - `logs/perf_teclas1`, 75 s con `GOW_PAD_TEST` y el mapa por defecto: envoltorio instalado, partida alcanzada,
    lecturas del mando normales;
  - pruebas QML del lanzador 7/7 (`launcher/pruebas/tst_teclas.qml`).
  - No probado con teclas reales en partida (no hay herramienta de entrada sintética en el sistema).
- **Pendiente:** remapear el mando (solo hay dos esquemas fijos).

### Rendimiento: carga de VU1, dependencias entre programas y fallo de NVIDIA (12 de octubre, tarde)

- **Fallo** (coredump 10:58, NVIDIA): SIGSEGV en `libnvidia-glcore` desde `rlDrawRenderBatch` ← `EndShaderMode` ←
  `PS2Runtime::run` (presentación FSR). El binario de entonces ya ponía la pantalla completa con `ToggleFullscreen`;
  con GLFW_AUTO_ICONIFY la ventana se minimiza al perder el foco y se dibuja con un framebuffer de 0.
  - Ahora: sin auto-minimizar en pantalla completa (`glfwSetWindowAttrib`) y, con la ventana minimizada o de tamaño
    0, ni pasos fuera de pantalla ni dibujo.
  - No se ha podido reproducir el fallo.
  - Comprobado (`logs/perf_guardas1`, 680M, pantalla completa + FSR + FXAA, 150 s): guarda de imagen OK.
- **Carga de VU1 en partida** (`GOW_VU1_PERFIL=1`, nuevo; por segundo, ejecuciones, ciclos, cortes y entradas):
  - ~57.000 ejecuciones/s, unas 1.900 por cuadro, de 3 entradas (0x0018 43 %, 0x0000 35 %, 0x0030 21 %), ~1.800 ciclos de
    VU de media, sin cortes por presupuesto;
  - ~102 M ciclos de VU/s a 30 cuadros/s, es decir ~3,4 M ciclos por cuadro;
  - una VU1 real (150 MHz) tardaría ~22,7 ms en ese trabajo: esas escenas no caben en 60 ni en la consola;
  - aquí cuestan ~8,2 ns por ciclo de VU (~1,2 veces la consola).
- **Dependencias** (`GOW_VU1_DEPS=1` con `GOW_VU1_SIN_COMPILAR=1`, nuevo): por ejecución, registros leídos antes de
  escribirlos (por carriles) y lecturas de memoria de VU escritas por otro programa. La memoria que escribe el VIF se
  detecta comparando con la del final del programa anterior.
  - Resultado: prácticamente todas dependen de la ejecución **inmediatamente anterior**:
    - VF5 en ~92 %, VF4 ~35 %, VF29/15/16, VI9 y Q;
    - memoria escrita por el programa anterior ~97 %;
    - distancia a la dependencia más cercana = 1 en >99,9 %.
  - Los programas son una cadena: repartir VU1 en varios hilos no es viable (tampoco lo hace PCSX2).
- **Muestreo en partida** (`logs/muestrear_linux`, 680M):
  - hilo de VU1 ocupado ~88 %: bloques compilados 67 %, `commitReadyPipelines` 5 %, despachador 5 %, VIF 4 %,
    `commitReadyFlags` 2 %;
  - hilo del EE ocupado ~64 %: ~33 % esperando y ~27 % en contabilidad del planificador (`accountCycles` 19,5 %,
    probablemente el bucle de sondeo mientras espera a VU1/GS);
  - hilo del GS ~49 % (envío, binning y páginas);
  - frente del GS ~19 %.
  - Para 60 en esas escenas, VU1 tiene que ir ~1,75 veces más rápido, por encima de la propia consola. Requiere
    rediseñar el código generado de VU1 (registros en locales a lo largo de los bloques, menos maquinaria por par);
    los retoques sobre el diseño actual ya se agotaron.

### Menú de trucos (F2) y pestaña "Trucos" del lanzador (12 de octubre, tarde)

Petición: un entrenador con inmortalidad, muerte de un golpe, todas las mejoras y poderes y todo desbloqueado.
Los códigos CodeBreaker/GameShark que circulan están cifrados, así que las direcciones salen del propio ELF:

- **Variables de la interfaz**: 0x1B5D70 registra ~190 variables con nombre (`HealthMeter_Value`, `PowerOrb_Count`,
  `Blades_Level`...) dentro del objeto de 0x15B0 bytes apuntado por 0x29CB94. Son la copia de la interfaz.
  - El estado de verdad está en 0x302CC0: 0x1D6AB8 lo copia a la interfaz al abrir el menú de mejoras, y
    0x1D6B40 / 0x1D6CD0 lo devuelven al cerrarlo.
  - Desglose de campos y topes en [`CONTROLES.md`](CONTROLES.md#menú-de-trucos-f2).
- **Ajustes del jugador** (0x3028E0, registro en 0x1D4410):
  - `Max Hit Points Level 0-4` = 100, 125, 150, 175, 200;
  - `Max Magic Level 0-5` = 0, 100, 125, 150, 175, 200;
  - umbrales del Modo Dios en +0x300 / +0x304;
  - 6 niveles de arma de 0x50 bytes desde +0x60 (`Allow God Mode`, `God Mode Meter Drain`...).
- **Vida**:
  - Kratos es `*(*0x29CD58)`, como comprueba 0x1E0BC0;
  - el HUD (0x1D6588) lee su vida en +0x178 y la máxima en +0x17C;
  - todas las escrituras de la vida pasan por 0x1E0A80, salvo 0x1EE860, que pone -2;
  - 0x1E0A98 resta daño y antes avisa de los umbrales cruzados (lista en +0x1B0).
- **Extras**: 0x22F4B0 guarda en 0x2A12C8 las partidas terminadas, que salen de la partida guardada:
  - bits 0-2: fácil, normal y difícil; bit 3: Modo Dios; bit 4: Desafío de los Dioses;
  - de ahí la interfaz saca `HardMode_Unlocked` y `Costumes_Unlocked`;
  - las consultas de extras (0x1BA9B8) miran directamente esos bits.

Implementación:

- `src/lib/gow_trucos.cpp`: envoltorios de 0x1E0A80 / 0x1E0A98 instalados con `replaceFunction` tras
  `applyMatching`, valores fijados en cada VBlank (`EeScheduler`, junto al panorámico) y el menú dibujado con raylib
  sobre la imagen.
- El envoltorio de scePad2Read (0x27B9F0) se instala ahora siempre en God of War, no solo con `TOBIICHI_TECLAS`:
  con el menú abierto deja el paquete en reposo.
- Lanzador: pestaña "Trucos" (`PaginaTrucos.qml`, ajuste `trucos`), `TOBIICHI_TRUCOS` y `TOBIICHI_IDIOMA`; F2 en
  la tabla de atajos. Las pestañas miden lo que su texto (con seis, repartidas a partes iguales se solapaban).

Verificado (680M, `GOW_PAD_TEST`, `TOBIICHI_TRUCOS_DIAG=1`):

- `logs/trucos1`, todos los trucos activos:
  - en partida `kratos=795800 vida=200/200 plausible=1`, magia 200, furia 100, orbes 60000;
  - niveles vida 4, magia 5, magias 2, espadas 4; objetos 0x017C; terminadas 0x1F;
  - tablas como arriba.
- `logs/trucos3`, inmortalidad + un golpe, cuadrado/triángulo forzados con `GOW_FORCE_PAD`, primer combate del
  barco:
  - los no muertos (vida 35) reciben 2 de daño → `restar ... -> 36`, `fijar ... -> 0`: mueren al primer golpe;
  - Kratos recibe 3 → `restar ... (Kratos) ... -> 0`, la vida sigue en 100.
- `logs/trucos2`: captura del menú abierto (`TOBIICHI_TRUCOS_ABRIR_EN=9`), textos turcos con DejaVu Sans.
- Lanzador: capturas de la pestaña en tr/en/es (fuera de pantalla), con un ajuste `trucos` guardado entre comillas
  como lo escribe QSettings.
- Durante las pruebas el usuario jugó en la ventana (WASD, clics) y la cerró hacia los 40-60 s, así que las capturas
  de 60 s en adelante no se hicieron.
- No comprobado en partida: abrir el menú real con F2 y que el ratón funcione en él, los extras desbloqueados
  vistos desde el menú principal, y la muerte de un golpe en jefes con fases (Hidra, Ares).

### Teclas de las magias y de la Espada de Artemisa (12 de octubre, tarde)

Petición: 1 Ira de Poseidón, 2 Mirada de Medusa, 3 Furia de Zeus, 4 Ejército de Hades, clic central Espada de
Artemisa. Antes 1-4 eran cruceta arriba/derecha/abajo/izquierda.

- **Qué dirección elige cada magia:**
  - 0x1D7250 lee los bits "recién pulsados" de la entrada del jugador (+0x10 / +0x14 del objeto de control):
    0x04000000 → `SelectMagic(3)` Zeus, 0x08000000 → 4 Medusa, 0x20000000 → 5 Poseidón, 0x10000000 → 6 Hades;
  - esa entrada sale de la tabla de controles 0x29CF38 (entradas de 8 bytes: bit del mando → bit de acción;
    17B92C la aplica);
  - en esa tabla, derecha → 26, izquierda → 27, arriba → 28, abajo → 29.
  - La magia elegida queda en 0x302D3E.
  - En partida (`logs/dpad1`, con `TOBIICHI_TRUCOS=poderes`): abajo → 5 y derecha → 3. El usuario jugaba en la
    ventana, así que solo esas dos pulsaciones son atribuibles.
- **Espada de Artemisa:** no se elige como las magias; los movimientos con requisito 7 solo exigen tenerla
  (0x2075E8, bit 0x40 de 0x302D42). Según la lista de controles (PSXDataCenter):
  - sacarla o guardarla: L1 + R1 mantenidos;
  - sus golpes: L1 + X / Cuadrado / Triángulo / Círculo;
  - L2 lanza la magia elegida y R2 es la acción o interacción. Las etiquetas del lanzador decían lo contrario y se
    han corregido.
- **Cambios:**
  - `ps2_pad.cpp`: acciones `poseidon medusa zeus hades artemisa`. `kBitAccion` pasa a máscaras: artemisa =
    L1 | R1, furia = L3 | R3.
  - Lanzador: `Teclas.js` añade esas acciones; la cruceta pasa al grupo "Menús" con solo las flechas; los mapas
    antiguos se migran en `leer`.
  - Prueba nueva `test_mapaAntiguo`; `tst_teclas` 8/8.
  - Captura de la pestaña con el mapa guardado del usuario: R2 sigue en el botón lateral, 1-4 en las magias y la
    cruceta solo con flechas.
- **No comprobado:** pulsar 1-4 y el clic central de verdad en partida (no hay forma de inyectar teclas aquí), y
  cuánto hay que mantener L1 + R1 para que saque la espada.

### Rendimiento con la RTX 4050: dónde está el límite, medido otra vez (12 de octubre, tarde-noche)

Sin cambios en el binario: las medidas no dejaron ninguna mejora segura que compense. Binario de referencia en
`~/.cache/tobiichi-sync/ps2EntryRunner.antes_opt_10121700`.

- **Partida** (`scripts/linux_perf_guard.sh base4050`, `TOBIICHI_GPU=nvidia`, barco con lluvia):
  - flip mediano 30,00;
  - por cuadro: VU 22 ms, EE 32 ms (incluye la espera), GS ~8 ms;
  - imagen OK.
  - Igual que la noche anterior, así que los trucos y las teclas no han tenido coste.
- **Línea de tiempo por hilo** (muestreador con salida cruda, ~0,8 ms por ronda, 20 s):
  - VU1 ocupado ~84 %;
  - el EE espera (ocioso o sondeando en `accountCycles`) el 46 % del tiempo con VU1 ocupado, y trabaja con VU1
    parado solo el 3,8 %;
  - los huecos de VU1 duran 1,5-4 ms, uno por cuadro, casi siempre con el EE también parado: es la espera del
    VBlank, no la latencia de despertar el hilo;
  - el camino crítico es VU1.
- **Hilo de VU1 en partida:**
  - bloques compilados 61 %;
  - `run()` 4,9 %, `commitReadyPipelines` 4,2 %, `commitReadyFlags` 2,7 %, `advanceTo` 1,2 %;
  - VIF 3 %, `memcpy` 2 %;
  - sin pares interpretados.
- **Coste por ciclo de VU:**
  - en partida, `GOW_VU1_PERFIL` da ~102 M ciclos/s en ~614 ms, es decir 6,0 ns por ciclo (~20 ms por cuadro);
  - en la reproducción (`logs/bench_gece2`, 10,9 ms por pasada, huellas `8c71fe9fb9754a73` / `189611644956d250`),
    6,3 ns;
  - no hay pérdida por el entorno (frecuencia, cachés compartidas, SMT).
  - El núcleo de VU1 va a 4,4-4,6 GHz con el perfil de energía "performance" (ya activo).
- **Contadores de la reproducción** (diferencia entre 61 y 1 pasadas):
  - por pasada, 183 M instrucciones y 50 M ciclos;
  - IPC 3,6, paradas frontales 5,6 %, fallos de iTLB despreciables;
  - es puro número de instrucciones, así que páginas grandes o alineación de código no ayudarían.
- **Perfil por líneas de la reproducción** (`-g1`): plano.
  - `upperT` ~20 % de las muestras; `normalize4` ~2,6 % (ya son 6 operaciones simples); commits ~5 %; despachador 3 %.
  - La comprobación de `m_stopRequested` en cada par solo la activa la propia VU1 (instrucción reservada);
    quitarla daría ~1-2 %: no compensa regenerar el PGO.
- **Conclusión:** en esta escena, para 60 cuadros/s VU1 tiene que bajar de ~20-25 ms a ≤ ~14 ms (hay ~3 ms de hueco
  al empezar el cuadro), ~1,5 veces.
  - Con la emulación bit a bit actual (~27 ciclos del host por ciclo de VU), eso pide rediseñar el generador:
    - VF en variables locales a lo largo del bloque;
    - ciclos y commits estáticos;
    - normalizar solo los operandos que vienen de memoria.
  - La otra vía es un modo de VU1 con la precisión de PCSX2 (clamping en lugar de resultado exacto). PCSX2 dibuja
    bien God of War así, pero la validación sería visual, no por huellas.
  - Las dos son trabajo de varios días.

### Modo rápido de VU1 con la precisión de PCSX2: 30 → 60 cuadros/s en el barco (12 de octubre, noche)

El usuario eligió la vía 2 (precisión de PCSX2 en vez de la exacta). Opción de CMake `PS2X_VU1_RAPIDO` (por defecto
OFF: el modo exacto y sus huellas no cambian; en nuestra compilación, ON). Cambios, todos bajo
`#if PS2X_VU1_RAPIDO`:

- **FMAC del código compilado** (`ps2_vu1_compiled.inl`, `upperT`):
  - en SSE con el MXCSR de `run()`: redondeo hacia cero, como antes, más DAZ/FTZ, que `run()` pone solo en VU1 y
    restaura después;
  - sin normalizar operandos, sin las cribas de rango del camino exacto y sin la ruta escalar exacta;
  - el resultado se limita a ±máximo (como el clamping "Normal" de PCSX2), así que un operando Inf/NaN no se propaga.
  - Quedan igual: MAX/MINI, CLIP, ITOF/FTOI/ABS (FTOI sin `normalize4`: DAZ y la saturación ya cubren esos casos),
    la temporización y los demás pipelines.
- **Flags:**
  - El estado no se calcula. En los 990 pares inferiores distintos del código compilado no hay ningún
    FSAND/FSEQ/FSOR/FSSET; los pares MAC/estado de cada micromemoria se miraron con un escaneo de las 1157 capturas.
  - MAC perezoso (`ps2_vu1_step.inl`, `Vu1MacRapido`): cada FMAC con flags vivos solo guarda Z/S y el ciclo en que se
    ven en una cola de 8. FMEQ/FMAND (en línea) y FMEQ/FMAND/FMOR (`execLower`) toman la entrada visible más nueva
    si es posterior al último MAC confirmado desde `m_flagPipeline` (resto de FMAC: intérprete, ruta escalar).
  - Con `DeadFlags` no se guarda nada.
  - `resetScheduler` resuelve y vacía la cola, como hace con las entradas listas de la cola normal; `run()` deja el
    MAC resuelto al terminar.
  - Sin U/O ni los bits pegajosos del producto (PCSX2 tampoco).
- **Reproducción** (`logs/bench_gece2`, sin PGO, mediana de 5):
  - exacto: 10,9 ms;
  - FMAC rápida: 9,7 ms;
  - sin normalizar operandos y sin flags muertos: 8,9 ms;
  - MAC perezoso: 7,4 ms (1,47 veces).
  - Imagen del cuadro reproducido (`img_x1_despues.ppm`) idéntica píxel a píxel a la exacta en los tres pasos
    (`logs/herramientas/comparar_img.py`). Las huellas de VU1 cambian, como se esperaba.
  - Cota medida antes de hacer el MAC perezoso: sin flags de FMAC en absoluto, 7,6 ms, pero la imagen se rompe (46 %
    de píxeles distintos): el juego sí lee el MAC.
  - Ojo: `huellas.sh` imprime el hash de `img_x1_antes.ppm`; para la imagen hay que comparar `img_x1_despues.ppm`.
- **PGO:** regenerado con el modo rápido (`logs/herramientas/pgo_vu1.sh logs/vu1_gcc_pgo_rapido -DPS2X_VU1_RAPIDO=1`,
  nuevo). `PS2X_VU1_GCC_PGO_DIR` apunta ahí; el perfil exacto sigue en `logs/vu1_gcc_pgo`.
- **En partida** (`scripts/linux_perf_guard.sh rapido4050`, RTX 4050, barco con lluvia):
  - flip mediano 30,00 → 59,93;
  - VU por cuadro 22 → 13 ms, EE 32 → 16 ms;
  - todas las ventanas de 5 s a partir de t = 30 s entre 56,2 y 60,1 (antes 30 salvo dos tramos);
  - guarda de imagen OK.
  - Durante la prueba el usuario jugó (cuadrado y stick), así que las capturas son de combate y del principio de la
    Hidra, también correctas.
- **Binarios:** el exacto en `~/.cache/tobiichi-sync/ps2EntryRunner.antes_opt_10121700`, el rápido en
  `ps2EntryRunner.rapido_10121836`.
- **Pendiente:**
  - comparar más escenas con el modo exacto;
  - los 80 casos FMAC con operandos extremos y los resultados subnormales dan distinto por diseño;
  - `tests/vu1_compiled_test` cubre solo el modo exacto.

### Linux: vídeos (FMV) completos y PMULTH de KIexster (13 de octubre)

- **Intro de punta a punta** (`logs/fmv7`, `logs/fmv16`–`fmv20`, RTX 4050): el vídeo se ve entero en la ventana, suena,
  termina (`sceMpegIsEnd=1` tras 1.383 cuadros) y el juego pasa a la cinemática en el motor y a la partida a 60 Hz.
  Antes, al acabar el vídeo, pantalla negra con el EE al 96 % y el proceso se cerraba hacia los 113 s.
- Cinco correcciones, detalladas en [`FMV_Y_AUDIO.md`](FMV_Y_AUDIO.md):
  - `sceMpegIsEnd` (`0x26FF70`, sin stub) redirigido al HLE; el fin de programa del PSS cuenta como fin.
  - Retrollamadas de flujo síncronas y cuadro de FFmpeg presentado en la ventana mientras dura el vídeo.
  - `sceMpegAddStrCallback` sustituye la retrollamada del mismo flujo: el juego registra las suyas dos veces y cada
    paquete de audio y vídeo llegaba duplicado.
  - ADMA en el SPU2: el sonido de los vídeos (PCM 48 kHz por `sceSdBlockTrans`, núcleo 1) se rechazaba; ahora se lee
    por bloques de 1 KB a su ritmo, con BVOL como s16, y el fin de DMA se retrasa hasta leer el último bloque.
  - Los DMA ADMA que se solapan se encolan (sustituir perdía 1 de cada 8 bloques).
- **Comprobado:** salida del SPU2 contra el audio que recibe el juego, 8.567 bloques idénticos, sin silencios; un
  salto de 85 ms. Guardas de imagen no ejecutadas en esta tanda; capturas de ventana revisadas a mano.
- **Lanzador y `run_gow.sh`:** los vídeos se reproducen por defecto (`saltarVideos=false`, `GOW_SKIP_FMV=0`).
- **Diagnósticos:** `GOW_FMV_DIAG=1`, `GOW_FMV_AUDIO_REF=<archivo>`, `GOW_AUDIO_VOLCADO=<archivo>` y `GOW_SPU2_DIAG=1`
  (ahora con DMA ADMA, BVOL/AVOL y pico ADMA).
- **PMULTH (KIexster #67, `ps2recomp-ee-pmulth.patch`)** integrado con `tools/sync/sincronizar_kiexster.py --parche
  ee-pmulth`, sin conflictos:
  - El recompilador sumaba los ocho productos de PMULTH en un escalar; los decodificadores de animación de
    `sub_00115978`, `sub_00115D00` y `sub_00116280` (cuatro PMULTH) daban matrices erróneas.
  - En el port de KIexster eso eran los espasmos de Kratos y de los NPC.
  - Regenerado con el template: solo esos tres archivos cambian respecto a `generated2` (copia anterior en
    `~/.cache/tobiichi-sync/generated2_antes_pmulth/`).
  - `ps2_runtime_macros.h` cambia, así que el ejecutable se recompila entero (~15 min con `-j3`).
- **No integrado aún de KIexster** (de `a42d77f` a `08103d1`, 213 commits): la sincronización completa da 21
  archivos en conflicto, 17 de ellos en `ps2_vu1_compiled.inl` contra el modo VU1 rápido.
  - Pendientes con efecto en el juego: `ee-cop0-count` (cambia `ps2_runtime.h` y el recompilador), niebla del GS
    (`gs-fog-latch`, `gs-fog-math`), `gs-discard-uncovered`, `vu1-block-check-cache` y `vu1-xgkick-bulk`.
  - El resto es sobre todo el espejo DX11 de PCSX2, la presentación compartida y diagnósticos para Windows.
- **Pruebas** (`ps2x_tests` en Linux): 571 de 574.
  - Fallan las mismas tres de antes: dos de UV/STQ del GS por CPU y la de redondeo de div/sqrt de la FPU del EE.
  - Pasan las nuevas: `sceMpegIsEnd …program end…`, `sceMpegAddStrCallback replaces…`, las dos de ADMA y las dos de
    PMULTH.
  - `sceMpegDemuxPssRing dispatches registered video and audio stream callbacks` fallaba desde que las retrollamadas
    de flujo son síncronas: el stub salta a la retrollamada y la prueba lo llamaba fuera del planificador. Ahora lo
    llama desde una función invitada (`demuxEnPlanificador`), igual que las pruebas de `sceMpegCbNodata`, y la
    retrollamada de prueba vuelve a quien la llamó en vez de parar el runtime.
  - Que las pruebas nuevas fallen sin la corrección se razona por el código; no se ejecutaron contra el binario anterior.
- **Partida con el ejecutable nuevo** (`logs/pmulth1`, 115 s, RTX 4050), revisado en capturas a mano:
  - intro con sonido y fin;
  - cinemática en el motor y combate en la cubierta a 60 Hz;
  - Kratos y los no muertos con poses normales.
  - No se ha hecho una comparación aislada antes/después de las animaciones.

### Linux: apertura de los vídeos, audio sin huecos y niebla del GS (13 de octubre, tarde)

- **Queja del usuario:** "salta directamente, Kratos no llega a decir *the gods have abandoned me*; la frase del
  principio está cortada".
  - Causa: `GOW_FAST_BOOT=1`, activado por defecto en el lanzador y en `run_gow.sh`.
  - Tras abrir el vídeo, el juego espera una animación de 13,3 s con el primer cuadro en pantalla y una voz de
    22,05 kHz (núcleo 1, voces 4/5).
  - `GOW_FAST_BOOT` da la animación por terminada en cuanto el nivel está cargado.
  - Ojo: las pruebas anteriores "sin arranque rápido" no lo eran, porque `run_gow.sh` exportaba `GOW_FAST_BOOT=1`
    de forma fija y pisaba la variable.
  - Ahora está desactivado por defecto. El lanzador lo desactiva una vez en los ajustes guardados
    (`versionAjustes=2`) y su descripción avisa de que corta la apertura.
  - Verificado con el entorno exacto del lanzador y los ajustes del usuario (16:10, trucos), en `logs/lanzador_e2e`:
    - voz y espera;
    - vídeo entero con sonido;
    - partida a 57-60 Hz.
- **Audio de los vídeos sin huecos:** retrollamada de audio en el host con cola y 30 cuadros decodificados por
  delante; detalle en [`FMV_Y_AUDIO.md`](FMV_Y_AUDIO.md).
  - Antes había 85 ms repetidos a los 35 s del vídeo, y el sonido quedaba retrasado desde ahí.
  - Ahora no hay ningún salto respecto al audio del PSS.
- **Lo que no era la causa:**
  - Ningún botón salta la intro: se probaron X, Start, Select, triángulo, círculo, cuadrado, L1/R1 y L2/R2.
  - Los ajustes del usuario (trucos, 16:10, FSR) no cambian el vídeo.
  - El flujo de voz posterior (núcleo 1, voz 7) no se corta con KOFF.
- **KIexster, solo tres parches del GS** (`--parche`), con los conflictos de registro de pruebas resueltos a mano:
  - `gs-fog-latch`: XYZF actualiza `m_curFog` para el XYZ siguiente.
  - `gs-fog-math`: mezcla de niebla con pesos que suman 256 y un solo truncamiento, en CPU y en el shader.
  - `gs-discard-uncovered`: descarte previo al interlock en el raster hardware; `PS2X_GS_HW_DISCARD_UNCOVERED=0`
    vuelve al shader anterior.
  - De sus pruebas se trae solo `uncoveredTriangles` (las demás dependen de herramientas de perfil que aquí no
    hay).
- **Pruebas:**
  - Suite: 578 de 581; fallan las mismas tres de siempre.
  - Con `GOW_GS_GPU_TEST=1` en la RTX 4050 pasa la nueva de triángulos finos.
  - En modo GPU hay además fallos que salen igual con el descarte activado y desactivado: UV/STQ constante, el
    mismo problema que en CPU, y otras pruebas no gráficas.
- **Partida:**
  - Niebla y lluvia de la cubierta correctas a simple vista.
  - 57-60 cuadros/s con la caché de shaders llena.
  - La primera ejecución tras cambiar los shaders compila y baja a 38-58 durante un par de minutos.
- **No integrado:**
  - `vu1-block-check-cache`: ya hay caché propia en el despachador.
  - `vu1-xgkick-bulk`: conflicto con el VU1 rápido.
  - `ee-cop0-count`: cambia `ps2_runtime.h` y el recompilador, y su efecto no está demostrado.
- **Otras comprobaciones:**
  - El CPU de respaldo sin OpenGL 4.6 no se cuelga (simulado con `MESA_GL_VERSION_OVERRIDE=3.3`), pero va a ~3 fps.
- **Copia de seguridad previa:** `~/.cache/tobiichi-sync/yedek_10131626/` (diff de trabajo, archivos sin seguimiento,
  ejecutables, `Launcher.conf` y los archivos del GS antes de los parches).
- **Vídeos con el escalado del juego:** el cuadro del vídeo pasa por el mismo `Presentador` que el juego (FXAA y FSR
  EASU+RCAS si están activos), a 4:3 con bandas. Antes se ampliaba con un bilineal simple. Comprobado con los ajustes
  del usuario (`logs/fsr_fmv`): vídeo visible y vuelta a la partida sin problemas.
- **Motivo de cierre en el registro:** líneas `[cierre]` cuando:
  - la ventana pide cerrarse;
  - termina el hilo del juego;
  - el juego llama a `exit()`;
  - aparece una función inexistente con la política Stop.

  Una ejecución de prueba se cerró sola a los 92 s y no se reprodujo; con esto, la próxima vez quedará el motivo.
- **Caché de sombreadores del lanzador** (`~/.cache/Tobiichi/Launcher/sombreadores`): calentada con los shaders nuevos de
  niebla (199 → 380 archivos), para que la primera partida no compile durante el juego.
- **Prueba de reinicio desde el último punto de control** (`logs/reinicio`): sin resultado.
  - La ventana se cerró a los ~100 s por una petición de cierre (`[cierre] la ventana pidió cerrarse`), antes de
    llegar a la pantalla de muerte.
  - Lo mismo explica el cierre a los 92 s de `logs/calentar`: el usuario estaba usando el equipo durante las pruebas.
  - Queda pendiente.

## Resolución interna e imagen nítida (13 de octubre de 2026)

Petición: dibujar a más resolución, con una opción en el lanzador que por defecto siga a la pantalla, y quitar el
aspecto borroso de la PS2. Detalles técnicos en [`RENDERIZADO.md`](RENDERIZADO.md#resolución-interna-supermuestreo)
y [`LANZADOR.md`](LANZADOR.md#resolución-de-dibujo-e-imagen-nítida-13-de-octubre-de-2026).

- **Supermuestreo del GS** (`PS2X_GS_ESCALA`, 1..8): un plano de VRAM por posición de muestra. Las lecturas usan el
  plano nativo.
  - Los sprites no se desplazan. Antes daban columnas verdes cada 8 píxeles y una imagen doble en los pasos de
    posprocesado del juego (`logs/escala3b` → `logs/escala3c`).
- **Imagen nítida** (`PS2X_GS_NITIDO`): sin duplicar las líneas del campo y sin el antiparpadeo de dos circuitos
  (DBY 1/0, ALP 0x80). Con `PS2X_GS_CRTC_DIAG` (ya retirado) se vio `pmode=8023 smode2=21fed1`, los dos circuitos
  sobre FBP 208 y DBY 1 y 0.
  - Comparación a 1×: `logs/escala1b` (antes) frente a `logs/nitido1`.
- **Rendimiento**, RTX 4050 Laptop, cubierta del barco, `GOW_PERF_DIAG`:

  | Escala | Antes | Ahora |
  |---|---|---|
  | 1× | 60 cuadros/s, hilo del GS 2,4 s/5 s | 60 cuadros/s, hilo del GS 1,25 s/5 s |
  | 2× | 38 | 40-60 |
  | 3× | 28 sin imagen nítida (17-24 con ella) | 18-24 |

  - Mejora: no se recompone ni se vuelve a leer un cuadro sin cambios, y no se vuelve a copiar ni a subir uno ya
    entregado.
  - A 2× y 3× la GPU está al 100 % (`nvidia-smi`); a 1×, al 23 %. Eso es el límite: el GS se emula por software en
    la GPU, y cada muestra cuesta lo mismo que un píxel nativo.
  - 8K no es realista en esta GPU. 8× existe (4096×3584), pero solo para GPUs muy grandes.
- **Presentación**: si la imagen es mayor que la ventana, se reduce por área (`kReducir`) en lugar de EASU. Verificado
  a 3× en una ventana de 922×1074 (`logs/reducir3b`).
- **Lanzador**: "Resolución de dibujo" (automática según la altura de la pantalla, o 1×-8×) e "Imagen nítida"
  (activada).
  - Con los ajustes guardados del usuario, la próxima partida usará 2× (pantalla de 1200 líneas). Para 60 FPS fijos en
    este portátil, hay que elegir 1×; la imagen nítida sigue activa.
- **Configuración regional tr_TR**: GLFW ponía `LC_CTYPE` del sistema y `tolower('I')` dejaba la `I`.
  - Fallaban las claves de módulos IRX y las búsquedas de archivos con `i`/`I`. Se restaura `"C"` tras inicializar
    GLFW.
  - Con `GOW_GS_GPU_TEST=1` desaparecen cinco fallos del IOP.
- **Pruebas**:
  - `ps2x_tests`: 579/582 (los 3 fallos conocidos).
  - Con `GOW_GS_GPU_TEST=1` en la NVIDIA: 591/595.
    - Los 4 fallos son conocidos: el control de UV/STQ constante, que falla igual en CPU y OpenGL, y la FPU del EE.
    - En la iGPU fallan además dos comprobaciones de "hardware efectivo", porque no tiene `fragment_shader_interlock`.
  - Nuevas: `presentation mailbox delivers each frame once` y `OpenGL sharp image shows every buffer line without
    anti-flicker`.
- **Pendiente**: quedan uniones tenues entre tiras de posprocesado en la niebla a 2× y 3×; a simple vista son menores.
  Ideas:
  - una revisión por tipo de primitiva del coste de GPU;
  - dibujar los S² planos en una sola pasada en lugar de S² dibujos.

### Resolución dinámica y 2× por defecto (13 de octubre de 2026)

Petición: 60 FPS en cualquier condición y 2× por defecto. Con el GS emulado por software en la GPU, el coste
crece con S².
- 8× a 60 FPS en una GPU débil no es posible con esta arquitectura. Haría falta un renderizador por hardware, como
  el de PCSX2: render targets como texturas nativas, mezcla y profundidad de la GPU y caché de texturas. Es un
  proyecto aparte y grande.
- 120 FPS de juego no son posibles sin romperlo: la lógica va ligada al VBlank de 60 Hz. La ventana ya presenta a
  120 Hz.
- Hecho:
  - escala dinámica (`PS2X_GS_ESCALA_DINAMICA`, detalles en `RENDERIZADO.md`);
  - lanzador con 2× por defecto y la dinámica activada (ajustes v3);
  - corrección de un desbordamiento al bajar de escala;
  - textura de presentación a tamaño exacto.
- Resultado: `logs/dinamica2` y `logs/dinamica4b`, sin cierres; 60 cuadros/s en la batalla de la cubierta a 1× efectivo.
- Pruebas: 579/582 y, con la GPU NVIDIA, 591/595. Los fallos son los conocidos.
- Limitación: la Radeon 680M tarda 20-26 ms por cuadro ya a 1×, así que no llega a 60 en las escenas pesadas.

### Renderizador por hardware y escaneo progresivo (13 de octubre de 2026)

- **Renderizador por hardware de triángulos** (`PS2X_GS_HW`; en el lanzador, "Renderizador por hardware
  (experimental)", activado): ver `RENDERIZADO.md`.
  - Medido en la RTX 4050 Laptop: 2× a 60 FPS con la GPU al 49 % (antes 40 FPS, GPU al 100 %) y 3× a 47-57 FPS
    (antes 18-24).
  - Corregido además un SIGSEGV al cerrar la ventana.
- **Escaneo progresivo siempre activado** (`gow_video.cpp`, `GOW_PROGRESIVO=0` lo desactiva). El usuario comprobó
  que la opción "Progressive Scan" del menú de pausa quita el desenfoque.
  - El ajuste vive en 0x29CC94 (registro de ajustes de `func_1B5D70`: WideScreen 0x29CC90, ProgressiveScan
    0x29CC94, DeFlicker 0x29CC98).
  - `func_21FDA0` lo aplica cada cuadro con `func_1830D8` (descriptor 0x2FD938 = 480p).
  - Se escribe 1 al entrar en `func_21FDA0`. El juego cambia de modo por su camino y la imagen pasa a 640×448.
  - La opción del menú queda sin efecto pero sigue visible. Quitarla exige modificar el menú, que es un archivo
    tipo Flash dentro de los datos del juego: las variables `_level0/:ProgressiveScan_State` y
    `EnableProgressiveButton` y el botón de confirmación con temporizador de 480p.

### 60 FPS en iGPU con ahorro de energía (13 de octubre de 2026)

Detalle en `RENDIMIENTO.md` ("Portátil en ahorro de energía con la iGPU"). Radeon 680M, perfil `power-saver`,
vídeos desactivados por petición del usuario (`GOW_SKIP_FMV=1` por defecto en `run_gow.sh` y en el lanzador, ajustes
v5; se retomarán después).

- **Espera del cuadro del EE sin girar** (`gow_espera.cpp`): 28-31 → 51-60 cuadros/s en la cubierta. Audio y ritmo
  sin cambios.
- **Escala dinámica:** también baja si el juego cae de 55 cuadros/s; en APU la resolución quita potencia a la CPU.
- **Fijar objetivo:** Alt cuenta al soltarse, si se pulsó solo y con la ventana activa. Hubo una fijación sin
  ninguna pulsación en una prueba desatendida.
- **Pendiente:** el combate más cargado queda en 45-50, limitado por VU1 (~20 ms de CPU por cuadro a ese reloj).
- **Herramientas nuevas:**
  - `GOW_MUESTREO` (perfil por muestreo);
  - `GOW_ESPERA_DIAG` (espera del EE y llegada/duración de los envíos de VU1);
  - `GOW_AFINIDAD`.
- **Pruebas:** 579/582. Con `GOW_GS_GPU_TEST=1` en la 680M, 590/596; los fallos son conocidos, más los dos de
  "hardware efectivo" que esa GPU no tiene.
- La NVIDIA no aparecía (`nvidia-smi`: "No devices found") con el perfil de ahorro de energía.

### Parches de GS de KIexster hasta `80f4214` (14 de octubre)

Con `tools/sync/sincronizar_kiexster.py --parche`, uno a uno y en su orden, se revisaron los parches de GS de
KIexster. La mayoría ya estaban (fusión sin cambios). Tienen código nuevo en el runtime:

- `gs-bilinear-stq`: el filtro bilinear también convierte STQ a 16.16 antes del medio texel (CPU y GLSL).
- `gs-coordinate-alias`: el lote de la GPU se parte cuando el mismo color o Z se repite por el ancho de fila o por la
  vuelta de la VRAM.
- `gs-zte`: con ZTE=0 no hay prueba ni escritura de Z (CPU y GLSL). Aplicado también en el renderizador por hardware
  propio (`gs_hw_render.cpp`, `admite` y `dibujar`).
- `gs-cpu-colclamp`: con COLCLAMP=0 la mezcla en CPU se desborda a 8 bits en lugar de saturar.
- `gs-texa-depth`: TEXA también al muestrear alias de profundidad (Z24/Z16/Z16S). El renderizador por hardware no
  acepta texturas Z, así que esas texturas van por la ruta software.

Pruebas:

- Las pruebas de estos parches se añadieron a mano en `ps2_gs_backend_tests.cpp`, porque nuestro archivo es
  distinto. A la de alias se le quitó `SetFeedbackSnapshotEnabled`, que no existe aquí. También se añadieron
  `ps2_gs_zte_tests.cpp`, `ps2_gs_cpu_colclamp_tests.cpp` y `ps2_gs_texa_depth_tests.cpp`.
- `GOW_GS_GPU_TEST=1` en la Radeon 680M: 603 de 613.
  - Las 3 de siempre fallan: triángulos CPU UV/STQ y redondeo FPU del EE.
  - Fallan otras 6 de "hardware". Lo único que no cumplen es la condición de que se observe el rasterizado por
    hardware: la 680M no tiene fragment interlock. Los píxeles coinciden.
  - Falla además la variante con control de triángulos UV/STQ, el mismo fallo de los triángulos CPU.
- RTX 4050: no se pudo probar, porque con el perfil de ahorro de energía `nvidia-smi` responde "No devices found".
- En partida (680M, 2× dinámica, renderizador por hardware y de cómputo): las capturas del combate de la cubierta
  son correctas.

`.kiexster-sync` no cambia: los parches que no son de GS (`vu1-thread`, `gs-front-thread`, `upload-ring`...) siguen
sin integrar o integrados a mano, como antes.

### Combate ágil: cancelación de animaciones de Kratos (14 de octubre)

Petición: cortar los ataques para hacer, por ejemplo, un bloqueo o una parada en mitad del combo.

- **Medido:** el juego ya lo hace. L1 o la evasión cortan cualquier ataque en uno o dos cuadros: primer cuadrado a
  los 0,11 s, triángulo, cuarto cuadrado y remate del combo.
- **Lo que obligaba a esperar:**
  - Atacar desde una evasión: 0,61 s.
  - La pulsación perdida al soltar L1 y atacar en el mismo cuadro.
  - Los golpes recibidos.
- **Cómo funciona el juego** (detalle en `docs/CONTROLES.md`, "Cancelar animaciones"):
  - Las pulsaciones encolan transiciones `{transición, umbral}` en el controlador de movimientos (`*(Kratos+0x324)`,
    +0x1C0).
  - `0x2048F8` las empieza con `0x2088E8` cuando el avance del movimiento actual llega al umbral.
- **Nuevo** (`gow_cancelar.cpp`, activado por defecto, opción "Combate ágil" del lanzador):
  - En una evasión, el umbral máximo es 0,2: el ataque sale a los 0,29 s en lugar de 0,61 s.
  - Búfer de entrada: la pulsación perdida al soltar L1 da el ataque a los 0,08 s.
  - Factor del combo opcional (`GOW_CANCELAR_COMBO`, 1 por defecto). Con 0,6 salen 5 golpes en 0,9 s en lugar
    de 3. No se comprobó que no se pierdan impactos: el contador de golpes (+0x64 del objeto de control) depende de
    dónde estén los enemigos.
  - Los golpes recibidos no se tocan: no encolan transiciones.
- **Comprobado** en partida (`logs/cancelar_final`, cubierta, 680M en ahorro de energía, 2× dinámica):
  - Evasión → ataque a los 0,29 s, dos veces.
  - Bloqueo → soltar L1 + cuadrado → ataque a los 0,08 s.
  - □□□△ con su remate.
  - 59,2-60 FPS y sin fallos.
- **Descartado:** escribir la máscara +0x70. `0x207EF8` la recalcula en cada cuadro y no es la puerta.
- **Herramientas nuevas:**
  - `GOW_CANCELAR_VIGILAR`: vigilancia de escrituras con mprotect y un paso con TF; da la función recompilada que
    escribe una dirección de la RAM del EE.
  - `GOW_CANCELAR_TRAMO`.
  - `GOW_CANCELAR_DIAG`.
  - `tools/perfil/linea_cancelar.py`.
  - Desensamblado del ELF con `llvm-objdump --triple=mipsel-unknown-linux --mcpu=mips3`.
- **Fallo visto una vez** (`logs/cancelar14`, no se repitió en cuatro intentos con y sin los diagnósticos):
  - Tras un combo de cinco cuadrados, el hilo del EE saltó a 0x0 (`JALR` en `0x149390`).
  - Esa función recorre una lista de objetos (a0+0x20, entradas de 8 bytes) y llama a su método +0xC; un objeto
    era nulo.
  - Pendiente, por si vuelve a aparecer.
- **Pruebas sin mando:** con la ventana enfocada, el clic del ratón llega como cuadrado y se mezcla con
  `GOW_FORCE_PAD`. En esta sesión aparecieron pulsaciones que no estaban en el guion.

### Iconos de botones según el dispositivo (14 de octubre)

**Petición:** que los iconos de PlayStation pasen a ser la tecla asignada con teclado y ratón, o el botón del mando
Xbox, en los menús, los textos y los minijuegos, con un diseño fiel al del juego.

- **Investigación.**
  1. Las texturas del GS: los iconos no son texturas. Se escribieron `GOW_TEXTURAS` y `texturas_gs` para ver las
     texturas de cada cuadro.
  2. Los textos guardan `[XButton]`, `[L1Button]`... La película de Flash del HUD tiene esos símbolos.
  3. El reproductor de Flash del juego: estructura de la película, símbolos y funciones de dibujo (`GOW_SONDEO` sobre
     0x13C000-0x150000, ocultar formas y comparar capturas). Las formas son mallas vectoriales para VU1.
- **Hecho** (`gow_iconos.cpp`):
  - El juego no dibuja la forma del símbolo del botón. La ventana pone encima el icono del dispositivo, en el centro y
    con el tamaño de la caja de la malla del fondo, con su oscurecido y transparencia.
  - Teclas: la del lanzador. Xbox: según el esquema DMC5 o el clásico.
  - Opción "Iconos de botones" en el lanzador: automático, teclado, Xbox o PlayStation.
- **Detalles en** `docs/CONTROLES.md`, "Iconos de botones según el dispositivo": formato de la película, reglas para
  reconocer cada botón y lo comprobado.
- **Pendiente:**
  - Comprobar los avisos de los minijuegos (marco griego, giros del stick).
  - El círculo 3D sobre los enemigos (modelo `goMiniGameCircle`): es una textura del mundo, no Flash.

### Rendimiento a 3× y 4× con la GPU integrada (15 de octubre)

**Petición:** 60 FPS a 3× y 4× con la Radeon 680M, también en modo de bajo consumo.

**Resultado** (modo rendimiento, partida): 1× 60 FPS (antes 53-56); 3× de 17 a 31-32 FPS; 4× de 10 a 18-19 FPS.
No llega a 60.

**Hecho:**

- Sprites y posprocesado de GoW en el renderizador por hardware: movimientos de canales CT16, DATE, mezcla con Ad,
  lecturas Z16, copias entre objetivos.
- Modo exacto de triángulos.
- Cargas parciales y volcados por páginas sucias.
- Presentación compartida sin lectura a la RAM (por defecto en Linux).

**Detalles, medidas y pendientes** en `docs/RENDERIZADO.md`, "Sprites por hardware, canales de GoW y presentación
compartida".

**Pruebas nuevas:**

- `OpenGL hardware sprites match the software path at 1x and 3x`.
- `OpenGL hardware channel shuffles match the software path at 1x and 3x`.

**Comprobado en capturas:** imagen correcta a 3× en la cubierta del barco (`logs/bench_fix3`).

**Fallo encontrado y corregido:** antes de esa captura salía una niebla verde, porque los sprites que leen su propio
objetivo solo copiaban la zona del primero del lote.

### Rama `ultimate`: runtime de Waffle565 con las funciones de Tobiichi Port (15 de octubre)

Integrado [Waffle565/God-Of-War-Native-Port](https://github.com/Waffle565/God-Of-War-Native-Port) (ramas `runtime` y
`main`) tomando su runtime como base: GS nativo por render targets, IOP compilado, VU1 nativa, vídeos con libmpeg2.
Detalle completo en `docs/ULTIMATE.md`.

**Comprobado:**
- Compila en Linux (GCC 16, LTO) tras portar el contexto GL a GLFW y tres ajustes de compilación.
- Arranca, carga y llega a la partida (estado 11) desde la ISO, con los 8 IRX en código nativo.
- La imagen del barco y del menú de título es correcta a 2x, con presentación compartida.
- Se cargan las funciones de Tobiichi (iconos, fijar objetivo, combate ágil, vídeo progresivo); los iconos se ven en
  el menú de pausa y en el de título, con la corrección vertical del modo 16:9 del juego.
- Cuadros del juego por segundo: 1x 50-56, 2x 46-47, 3x 35 (la ventana a 13 Hz).

**Sin comprobar:** menú de trucos y fijar objetivo en partida, QTE, lanzador recompilado, Windows.
