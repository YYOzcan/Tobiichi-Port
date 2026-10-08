# Memory card (2026-10-07)

## Estado

Con una copia de una tarjeta de PCSX2 (`Mcd001.ps2`, 8 MB con ECC) que tiene una partida de God of War:

- el menú **Cargar** lista las partidas con su miniatura, zona, fecha, dificultad y tiempo;
- **cargar** la partida termina en "Load Complete" y el juego aparece en el punto de guardado de los
  muelles de Atenas;
- **guardar** en el altar ("Zeus has given you the opportunity…", sobrescribir) termina en "Save
  Complete"; el sistema de archivos de la tarjeta sigue siendo válido y el port vuelve a cargar la
  partida guardada (con el tiempo de juego nuevo).

La tarjeta se elige con `GOW_MC0=<ruta>` (por defecto `Mcd001.ps2` junto al ELF). Para probar sin
riesgo conviene usar una copia: el juego escribe en el archivo.

## Fallos corregidos (`patches/ps2recomp-memcard.patch`)

God of War usa `MC2_D.IRX` sobre `DBCMAN.IRX`/`SIO2D.IRX`: libmc2 del EE manda cada orden con
`sceDbcSendData3` (RPC al servidor `0x8000131c` de dbcman), mc2_d la ejecuta con transferencias del
SIO2 y contesta con DMA al EE. Antes el juego decía "No MEMORY CARD found in MEMORY CARD Slot 1". Había
cuatro fallos en el emulador del IOP:

1. **`sceSifSetDmaIntr` (sifman 32) no hacía nada.** dbcman contesta al EE con esa función y espera su
   callback de fin de DMA (que libera un semáforo) antes de enviar la siguiente respuesta. Ahora copia
   igual que `sceSifSetDma` y programa `func(data)` como un callback de interrupción. smpd también la
   usa: sus callbacks ahora se ejecutan (el sonido y los vídeos siguen funcionando).
2. **`WaitEventFlag` sin hilo actual fallaba en el acto** (`KE_EVF_COND`). mc2_d hace las transferencias
   del SIO2 desde el servidor RPC de dbcman, y sio2man espera el fin de cada una con `WaitEventFlag`:
   leía la respuesta antes de que llegara (`GetSpecs` fallaba). Ahora, como `WaitSema`
   (`ps2recomp-iop-sound.patch`), corren los demás hilos del IOP hasta que se cumple la condición.
3. **LWL/LWR seguidas sobre el mismo registro.** En el R3000 la segunda combina con el valor que aún
   está en el hueco de retardo de carga de la primera; el intérprete usaba el valor anterior. mc2_d
   copia así las especificaciones de la tarjeta (tamaño de página, de bloque y de tarjeta), que llegaban
   al EE como basura.
4. **`sceCdReadClock` del IOP (cdvdman 24) no existía.** mc2_d la usa para la fecha de las partidas
   ("??? 95, 2000 12:00:00"). Ahora devuelve la hora en BCD y, como el reloj de la PS2, en hora de
   Japón (UTC+9): el juego le resta 9 horas y suma la zona horaria de la configuración del sistema, que
   el runtime toma del host, así que la partida muestra la hora local. (El `sceCdReadClock` del EE del
   runtime devuelve la hora local; God of War no lo usa para las partidas.)

Pruebas de regresión nuevas en `ps2xTest/src/ps2_iop_tests.cpp` (una por fallo); la suite pasa
**555/555**.

## Cómo se probó

`GOW_PAD_GUION` (ver `docs/CONTROLES.md`) guía el menú sin mando. Con `GOW_SKIP_FMV=1`, cargar y guardar
en la misma ejecución:

```powershell
$env:GOW_MC0 = 'C:\ruta\copia_de_Mcd001.ps2'
$env:GOW_PAD_GUION = '5:start,13:abajo,20:x,62:x,75:x,90:x,230:r2,250:x,270:x,295:arriba,310:x'
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 420
```

Los tiempos dependen de la velocidad de la emulación (la partida va a ~2–3 cuadros por segundo). Falta
comprobar que PCSX2 abre la tarjeta escrita por el port y crear una partida en una tarjeta vacía
(formateo).
