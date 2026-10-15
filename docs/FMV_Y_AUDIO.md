# FMV y audio (2026-10-07)

## FMV

Sin `GOW_SKIP_FMV`, el juego se quedaba en el estado 4 (`movie=10`) esperando en
`sceMpegGetPicture`: el decodificador recibía datos PSS válidos (`00 00 01 BA`) pero no producía
cuadros. God of War demultiplexa el primer bloque del vídeo (que lleva la cabecera de secuencia
MPEG-2, `00 00 01 B3`) **antes** de llamar a `sceMpegCreate`, y la implementación del runtime
reiniciaba ahí el estado de reproducción. Como el vídeo no repite la cabecera, el decodificador
esperaba una que no llegaba.

`patches/ps2recomp-mpeg-create.patch` conserva la entrada ya demultiplexada del flujo en curso al
crear el decodificador (si aún no se ha servido ninguna imagen y el flujo no ha terminado). La
regresión `sceMpegCreate keeps a sequence header demuxed before it` falla sin el cambio; la suite pasa
**548/548**. En el juego, sin `GOW_SKIP_FMV`, el vídeo de la intro (Kratos en el acantilado) se
decodifica y se presenta.

Aparte: la implementación de `sceMpegCreate`/`sceMpegReset` heredada escribe en direcciones fijas
(`0x1717BC`, `0x171800`…, `0x171904`) que corresponden a otro juego. En SCUS-97399 caen en el código,
así que no parecen afectar al recompilado, pero conviene retirarlas.

## FMV completas: fin del vídeo, imagen y sonido (2026-10-13)

La intro (`Kratos en el acantilado` → "Three Weeks Earlier") se reproduce ahora entera, con imagen y sonido, y el juego
pasa a la cubierta del barco. Cinco fallos, cada uno con su comprobación:

1. **El vídeo no terminaba.** El reproductor del juego (`0x189B00`, `0x18A298`) pregunta `sceMpegIsEnd` (`0x26FF70`),
   que no tenía stub: el código original devuelve `*(mp->sys + 0)`, que solo escribe el decodificador de Sony. Con el
   decodificador HLE quedaba a 0 y, al acabar, el juego pedía cuadros para siempre (pantalla negra, EE al 96 %).
   `gow_peliculas.cpp` redirige `0x26FF70` al `sceMpegIsEnd` del runtime, y este acepta como fin el código de fin de
   programa del PSS (`0x000001B9`): God of War lee el PSS con su propio lector, sin `sceCdSt*`, así que nunca hay EOF
   del productor.
2. **Imagen.** La ventana muestra el cuadro que decodifica FFmpeg mientras `0x29C838 != 0` (el truco del GS con el que
   el juego redibuja la imagen RGB32 no se reproduce). Las retrollamadas de flujo son síncronas, como en libmpeg, para
   que el juego lea el tamaño (640×480) antes de reservar su búfer.
3. **Cada paquete se entregaba dos veces.** El juego llama dos veces a `sceMpegCreate` al abrir un vídeo y registra
   sus retrollamadas de flujo (`0x18A6A8`) tras cada una. libmpeg tiene una retrollamada por flujo (tipo y canal);
   el HLE las acumulaba. Resultado: el anillo de audio del juego (`0x19000` bytes) se llenaba al doble de ritmo,
   rechazaba paquetes y el audio salía duplicado. `sceMpegAddStrCallback` sustituye ahora la anterior del mismo flujo.
4. **Sin sonido: ADMA.** El audio del PSS (`SShd`: PCM16LE, 48 kHz, estéreo, interleave 0x200) pasa del anillo del
   juego (`0x188380` → `0x188688`) a un búfer de 16 KB en el IOP (RPC de SMPD `0x3B`/`0x3E`/`0x40`), y 989snd lo
   envía con `sceSdBlockTrans` en modo ADMA al núcleo 1 (MMIX `0x0FCF`, BVOL `0x7FFE`). El SPU2 rechazaba los DMA en
   ADMA y el DMA terminaba al instante (≈8.800 DMA/s en vano). Ahora (`spu2.cpp`) cada bloque de 1 KB (256 muestras
   izquierdas + 256 derechas) se lee de la RAM del IOP cuando hace falta, se mezcla con BVOL (s16, no el formato de
   15 bits de las voces) y la interrupción de fin de DMA llega cuando se lee su último bloque (`iop_memory.cpp`). Los
   DMA que empiezan antes de que se lea el anterior se encolan: sustituirlo perdía 1 de cada 8 bloques.
5. **Verificación del sonido.** `GOW_FMV_AUDIO_REF=<archivo>` guarda el audio que recibe el juego y
   `GOW_AUDIO_VOLCADO=<archivo>` la salida del SPU2. Comparados bloque a bloque (correlación normalizada): 8.567
   bloques de 256 muestras idénticos a la referencia (ncc 1,00), sin silencios, con desfase constante durante los
   47 s, salvo un salto de 85 ms (un búfer del IOP) hacia los 57 s de la ejecución.

Diagnóstico: `GOW_FMV_DIAG=1` (reproductor, `sceMpegIsEnd`, retrollamada de audio y su anillo, estado de la ventana) y
`GOW_SPU2_DIAG=1` (ahora con DMA ADMA por segundo, BVOL/AVOL y pico de la entrada ADMA).

Regresiones nuevas: `sceMpegIsEnd reports the end after the PSS program end code without a CD stream`,
`sceMpegAddStrCallback replaces the callback of the same stream`, `ADMA input is read in 1 KB left/right blocks at
48 kHz and mixed with BVOL` y `an ADMA DMA started before the previous one is read is queued behind it`.

Pendiente: comprobar uno a uno los demás vídeos (las cinemáticas de cada nivel y los extras usan el mismo reproductor).

## Audio

`patches/ps2recomp-audio-pcm.patch` añade `GOW_AUDIO_PCM=<archivo>`: guarda las muestras emuladas del
SPU2 (s16le, estéreo, 48 kHz) sin los silencios de relleno, para comprobar el audio aunque la
emulación vaya más lenta que el tiempo real.

Antes de los arreglos de abajo, en 23 s de audio emulado (menú, intro y partida) la salida era
silencio absoluto: ningún banco de sonido llegaba a la RAM del SPU2.

`patches/ps2recomp-iop-sound.patch` corrige dos fallos del emulador del IOP:

1. **`sceSifGetOtherData` (sifcmd, ordinal 23) no copiaba nada.** smpd y 989snd lo usan para traer
   desde la RAM del EE los bancos que el juego ya tiene cargados (`GENERAL`, `Title01`, `AthnA01`,
   `SKS_Skel1`…, comando `SMPD` de tipo `0xD`). Ahora copia `size` bytes del EE a la RAM del IOP y
   rellena el `SifRpcReceiveData_t` (origen, destino y tamaño desde `+0x10`). Con esto suenan los
   primeros segundos (el sonido del menú).
2. **`WaitSema` sin hilo actual fingía éxito.** Los servidores RPC se ejecutan como llamadas sueltas
   (sin hilo), y si el semáforo estaba a cero se devolvía 0 sin tomarlo. 989snd protege su tick con un
   candado (`gLockMasterTick`, semáforo y dueño = `GetThreadId()`): el servidor RPC lo "tomaba"
   mientras lo tenía el hilo del tick, quedaba como dueño el hilo 0 y el tick ya no podía soltarlo
   (error `0x7B`). Desde ahí el IOP imprimía cada 2 s `Sound System Tick locked out for 2 seconds` y
   el sonido se paraba. Ahora, sin hilo actual, `WaitSema` deja correr a los demás hilos del IOP hasta
   que el semáforo se libera (máximo ~1 s de reloj del IOP; si se agota devuelve `KE_SEMA_ZERO`).

Resultado con `GOW_SKIP_FMV=1` y 240 s de ejecución: 19,7 s de audio emulado con sonido continuo
(antes 5 s de sonido y luego silencio) y ningún aviso de tick bloqueado. Regresiones nuevas en
`ps2xTest/src/ps2_iop_tests.cpp`: `WaitSema outside a thread waits for the semaphore instead of
faking success` y `sceSifGetOtherData copies EE memory into IOP RAM`; la suite pasa **550/550**
(ejecutada desde `ps2xTest`, que es donde la prueba de VU0 encuentra `instructions.h`).

El audio sigue el reloj emulado: con la partida a ~2 fps se oye a trozos. Llegará a tiempo real
cuando VU1 deje de ser el cuello de botella (ver `docs/RENDIMIENTO.md`).

## Apertura completa y audio de los vídeos sin huecos (2026-10-13, tarde)

- **La frase inicial de Kratos se cortaba por `GOW_FAST_BOOT=1`.** El juego abre el vídeo (`0x21E510` →
  `0x188CA0`), muestra su primer cuadro y espera a que termine una animación de 13,3 s (`0x21E700`: tiempo de
  `0x100C50` contra duración de `0x100BF0`). Mientras, suena un flujo de voz (núcleo 1, voces 4/5 a 22,05 kHz) y
  solo después empiezan el vídeo y su sonido (ADMA). `GOW_FAST_BOOT=1` (en `runner/gow_overrides.cpp`, de cuando el
  juego iba a 2 fps) devuelve la duración como tiempo en cuanto el nivel está cargado (`0x29E584 == 1`), así que la
  espera y la voz se saltaban. Venía activado en el lanzador y en `run_gow.sh`; ahora no (`versionAjustes=2` lo
  desactiva una vez en los ajustes guardados). Comprobado con el entorno exacto del lanzador
  (`logs/lanzador_e2e`): cuadro 0 del vídeo, 11,9 s con la voz, y después vídeo y sonido.
- **Audio del vídeo sin pérdidas.** El demux HLE consume todo lo que recibe, y libmpeg en cambio se para cuando
  una retrollamada devuelve 0. Con 8 cuadros decodificados por delante, en el tramo del PSS en que el vídeo va por
  delante del audio (hacia los 35 s) el juego se quedaba sin audio: el anillo del IOP (16 KB, 85 ms) repetía datos
  y el sonido quedaba 85 ms retrasado. Con más margen de vídeo, el anillo de audio del juego (0x19000 bytes) se
  llenaba y los paquetes rechazados se perdían. Ahora `gow_peliculas.cpp` reimplementa la retrollamada de audio
  (`0x18A8F8`, misma cabecera y anillo) con una cola en el host delante del anillo, que se rellena también desde
  `0x189A88` en cada cuadro, y `kMaxDecodedPicturesAhead` pasa de 8 a 30 (~1 s, ~37 MB). Comprobado contra el
  audio del PSS (`GOW_FMV_AUDIO_REF`, ya sin la cabecera de 40 bytes): ningún salto en los 47 s.
- Las primeras ~0,75 s del vídeo se mezclan con el final de la música del menú, que el juego baja con
  `snd989:32` y para después de empezar el vídeo. Es el comportamiento del juego, no se toca.
