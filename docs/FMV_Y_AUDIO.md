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
