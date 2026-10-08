# Entrada del mando y pruebas del menú

God of War usa **libpad2** (sockets), mientras que el backend de entrada de PS2Recomp entrega paquetes
de libpad (puerto/slot). Los overrides de `src/gow_overrides.cpp` conectan ambas interfaces para el
primer puerto. El segundo puerto permanece desconectado; todavía no hay vibración.

## Teclado

Cuando no hay un gamepad conectado al backend:

| Control de PS2 | Tecla |
|---|---|
| Stick izquierdo | WASD |
| Stick derecho | IJKL |
| Cruceta | Flechas (WASD también activa la cruceta del backend) |
| X | X o Espacio |
| Círculo | C |
| Cuadrado | Z o numérico 0 |
| Triángulo | V o numérico 1 |
| L1 / R1 | Q / E |
| L2 / R2 | Shift izquierdo / derecho |
| Start / Select | Enter / Tab |

El backend usa el gamepad de índice 0 cuando está disponible. Sus botones, sticks y gatillos se
adaptan al paquete libpad2. Las presiones se simulan como 0 o 255 según el botón esté suelto o pulsado.

## Validación

`scripts\probar_pad2.cmd` compila y ejecuta una prueba independiente del juego. Comprueba el orden
de bytes de X/Start, ambos sticks y las doce presiones contra la tabla que usa el ejecutable de
SCUS-97399. Requiere las mismas herramientas de C++ que la compilación normal.

Después de compilar el port, se puede repetir la prueba de navegación:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 115
```

La prueba activa temporalmente `GOW_PAD_TEST=1`: pulsa Start a los 5 segundos desde la primera lectura
del mando y X a los 12, 20, 28, 36, 52, 60, 68, 76, 84, 100, 116 y 132 segundos. Guarda hasta diecisiete imágenes PPM del framebuffer del GS en
`logs\`, junto con `ejecutar.log` y `ejecutar_err.log`. La secuencia es un diagnóstico; no detecta qué
pantalla está activa y **no certifica que se haya iniciado una partida jugable**. La ejecución normal
no inyecta botones. Hay que revisar las imágenes y los registros.

`GOW_PAD_GUION` sustituye esa secuencia por otra: una lista `segundo:botón` separada por comas, con
pulsaciones de 0,7 s. Botones: `start`, `select`, `arriba`, `abajo`, `izquierda`, `derecha`, `x`,
`circulo`, `cuadrado`, `triangulo`, `l1`, `r1`, `l2`, `r2`. Por ejemplo, para abrir Cargar en el menú:

```powershell
$env:GOW_PAD_GUION = '5:start,13:abajo,20:x'
```

Para investigar búsquedas de nodos durante las transiciones:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -DiagnosticoRutas
```

`GOW_PATH_DIAG=1` registra `[gow-path]` y guarda `gow_path_failure.bin` junto al ejecutable si se intenta
adjuntar un nodo NULL. El volcado contiene la RAM del juego y no debe publicarse.

## Dispatcher y checkpoints

`patches/ps2recomp-checkpoint.patch` se aplica después del parche principal del runtime. Evita tratar
una cesión del EE en el punto de entrada de una función como un retorno implícito. El fallo se
reprodujo al navegar desde el menú: una copia parcial dejó `goimation` en lugar de `goHero` y la
búsqueda del nodo terminó en una llamada virtual a NULL (`0x00180D30`). El parche incluye una prueba
de regresión en `ps2_runtime_expansion_tests.cpp`.

## Inicialización del IPU

El stub genérico de `sceIpuInit` intentaba llamar a `0x00126428` y leer tablas de otro ejecutable.
En SCUS-97399 esa dirección es una continuación de `FilteredCopyTile`: al elegir dificultad, la
llamada ejecutaba el bucle de dibujo con registros de inicialización y bloqueaba el EE.
`gowIpuInit` reproduce las escrituras de inicialización en MMIO y usa las tablas del juego en
`0x002A1610` y `0x002A1660`, sin esa llamada a código ajeno. Esto no implementa la decodificación de FMV.

Para investigar la carga del nivel sin esperar al decodificador, `GOW_SKIP_FMV=1` omite las películas
en la API de carga del juego, antes de reservar buffers y abrir el flujo. Sus consultas de
buffer listo/fin devuelven verdadero. La opción está desactivada por defecto y no implementa vídeos.

```powershell
$env:GOW_SKIP_FMV = '1'
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 230
Remove-Item Env:GOW_SKIP_FMV
```

`GOW_FAST_BOOT=1` permite repetir diagnósticos sin esperar la animación de entrada: solo su consulta
de finalización (`ra=0x0021E714`) devuelve la duración total cuando el nivel ya está cargado.
La opción está desactivada por defecto. La prueba sin ella llegó al estado de partida después de
varios minutos; no es necesario usarla para completar esa transición.

`GOW_ANM_DIAG=1` registra tiempos de animación y condiciones de pausa. `GOW_RENDER_DIAG=1` registra
los contextos y las primitivas recientes del GS, y al entrar en el estado de partida guarda
`gow_vu1_code.bin`, `gow_vu1_data.bin` y `gow_render_ram.bin` junto al ejecutable. Esos volcados
contienen datos del juego y no deben publicarse.

`GOW_VU1_BUDGET_DIAG=1` (`ps2recomp-vu1-budget-diag.patch`) registra `[gow-vu1-budget]` cuando un programa
VU1 lanzado por MSCAL/MSCNT agota el tope fijo de 65536 ciclos sin llegar a su bit E: muestra la dirección
de entrada, el PC donde se cortó y el contador. Escribe las 32 primeras apariciones y después una de cada 1024.
Si no aparece ninguna línea en la partida, el tope no está cortando programas.

## Prueba aislada de XGKICK

`patches/ps2recomp-xgkick.patch` añade `GOW_XGKICK_IMMEDIATE=1`: copia y envía el paquete GIF
al emitir XGKICK, antes de que instrucciones posteriores sobrescriban el buffer VU.
Con la variable ausente o con `0` se conserva la transferencia por ciclos.
La idea procede del [runtime de SOCOM Unzipped](https://github.com/Scotho/socom-unzipped/blob/main/third_party/ps2recomp/ps2xRuntime/src/lib/vu/ps2_vu1_core.cpp#L1074-L1083).
La adaptación usa el parser acotado y el manejo de memoria circular existentes; no importa
programas VU nativos ni direcciones específicas de SOCOM.

```powershell
$env:GOW_SKIP_FMV = '1'
$env:GOW_FAST_BOOT = '1'
$env:GOW_RENDER_DIAG = '1'
$env:GOW_XGKICK_IMMEDIATE = '1'
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 140
# Guardar los logs/capturas antes de repetir: la siguiente ejecución los reemplaza.
$env:GOW_XGKICK_IMMEDIATE = '0'
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 140
Remove-Item Env:GOW_XGKICK_IMMEDIATE, Env:GOW_SKIP_FMV, Env:GOW_FAST_BOOT, Env:GOW_RENDER_DIAG
```

Las ejecuciones de 140 segundos con el mismo ejecutable, opción `1` y `0`, llegan al estado 11.
Las capturas de partida a los 90 segundos desde la primera lectura del mando son idénticas:
todos sus píxeles son negros. Persisten errores de paquetes XGKICK y los defectos del menú.
La opción queda como experimento desactivado por defecto.
Una regresión sintética comprueba que un SQ posterior sobrescribe la memoria VU, mientras el paquete
ya enviado conserva sus bytes originales. La prueba existente del modo por ciclos sigue pasando.

## Correcciones de UNPACK VIF

`patches/ps2recomp-vif-unpack.patch` corrige dos formatos del intérprete:

- V2-32/16/8 escribe `X,Y,X,Y` en lugar de conservar las componentes Z/W anteriores.
  La expansión ocurre antes de aplicar las máscaras y las sumas STMOD.
- V4-5 expande RGB a los bits 3..7 y alfa al bit 7. Por ejemplo, `31,17,9,1`
  produce `248,136,72,128`. Este formato sigue ignorando STMOD.

Referencias: [PCSX2 Vif_Unpack.cpp](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/Vif_Unpack.cpp)
y [SOCOM Unzipped](https://github.com/Scotho/socom-unzipped/blob/main/third_party/ps2recomp/ps2xRuntime/src/lib/ps2_vif1_interpreter.cpp).
Estas correcciones se aplican en la compilación normal.

Tres pruebas sintéticas fallaban antes del arreglo y pasan después: cubren las tres anchuras V2,
extensión con/sin signo, máscaras, protección de escritura, suma por componente y alfa V4-5
encendido/apagado. La suite cambia de 436/441 a 439/441; los dos fallos restantes son los previos.
La ejecución del juego con FMV omitidos sigue alcanzando el estado 11, con defectos del menú
y la imagen de partida negra. No se atribuye una mejora visual a estas correcciones.

## Diagnóstico de VIF y buffers de dibujo

`patches/ps2recomp-vif-diagnostic.patch` añade trazas optativas y acotadas; no altera la ejecución
de VIF ni de VU. Para repetirlas:

```powershell
$env:GOW_SKIP_FMV = '1'
$env:GOW_FAST_BOOT = '1'
powershell -NoProfile -ExecutionPolicy Bypass -File scripts\probar_menu.ps1 -Segundos 140 -DiagnosticoVif
Remove-Item Env:GOW_SKIP_FMV, Env:GOW_FAST_BOOT
```

El script restaura las variables de diagnóstico al terminar. En `logs\ejecutar_err.log`:

- `[gow-vif]` cuenta comandos y solicitudes de interrupción (bit I).
- `[gow-vif-launch]` compara TOP/ITOP y la cabecera en memoria antes de los primeros 24 MSCAL.
- `[gow-xgkick]` muestra las primeras 96 cabeceras GIF y una muestra cada 4096.
- `[gow-xgkick:reject]` identifica los primeros 32 rechazos por formato, longitud o búfer lleno.
  Una cabecera con NLOOP=0 puede ser válida; no debe contarse como un rechazo por sí sola.
- `[gow-gs:buffer]` registra formato, dirección y píxeles con RGB distinto de cero de cada contexto.

Al alcanzar por primera vez el estado 11, `GOW_RENDER_DIAG` guarda también `gow_render_vram.bin`
y `gow_render_context_0.ppm` / `gow_render_context_1.ppm` junto al ejecutable. Las imágenes de
contextos solo se generan para PSMCT32/24 y FBW distinto de cero. Leen la memoria con el direccionamiento
del GS, sin cambiar el framebuffer presentado. Los archivos contienen datos del juego: conservarlos
localmente y no publicarlos.

La prueba de 140 segundos registró 196608 comandos VIF1 sin solicitudes de interrupción y llegó
al estado 11. Los dos contextos dibujaban en FBP=0, FBW=8, PSMCT32, mientras la pantalla presentaba
FBP=208. Sus capturas tenían 212992 píxeles con RGB distinto de cero, pero solo mostraban un fondo
oscuro y puntos dispersos: no apareció una escena 3D oculta en esos buffers. La pantalla seguía negra.
La suite conserva 439/441 pruebas aprobadas y los mismos dos fallos conocidos.

### Corrección de saltos por registro de VU1

`patches/ps2recomp-vu-jump.patch` corrige JR y JALR para leer el valor actual del registro VI.
La copia anterior usada para comparar ramas condicionales no debe determinar estos destinos.
El comportamiento se contrastó con [JR/JALR de PCSX2](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/x86/microVU_Lower.inl)
y su [análisis de saltos](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/x86/microVU_Analyze.inl).
La regresión también cubre JALR cuando el registro de destino y el de enlace coinciden.

Repetir la prueba anterior de 140 s con este parche registra 212992 comandos VIF1, llega al
estado 11 en aproximadamente 70 s desde la primera lectura del mando y no produce mensajes
`[gow-xgkick:reject]` ni `[VU1 reserved lower]`. Antes se observaban paquetes rechazados por
longitud y bucles de vértices que sobrescribían las cabeceras en 0xF60 y 0x24B0.

La pantalla presentada sigue negra. El contexto 0 conserva 212992 píxeles no negros, pero su
imagen sigue siendo un fondo oscuro con puntos. Esta corrección elimina un fallo de ejecución
VU1; todavía hay que resolver el renderizado de la escena. La suite queda en 440/442, con los
dos fallos previos de heap/DMA. Las trazas temporales de escrituras se han retirado del runtime.

Tras integrar también `ps2recomp-heap.patch`, el conjunto pasa 443/443 pruebas. Los resultados
440/442 de arriba documentan la comparación antes de integrar esa corrección de heap/DMA.

### Captura de comandos GS

Para elegir un tramo de comandos del GS, `GOW_GS_REPLAY_TRACE` indica el archivo
local de salida. `GOW_GS_REPLAY_AFTER` fija la espera desde la instalación del
backend (0..3600 segundos, 150 por defecto); `GOW_GS_REPLAY_SECONDS` fija la
duración (0,1..60 segundos, 3 por defecto). Los valores usan punto decimal.
`GOW_GS_REPLAY_TEXFLUSH=1` exige además un TEXFLUSH del juego en estado 11 y guarda
el estado inicial después de esa invalidación. Por defecto vale `0`. No fuerza
una invalidación ni una transición del juego. Los comandos de presentación no
inician la captura. El límite sigue siendo 64 MiB y puede cerrar el tramo antes
del plazo. Las opciones mal formadas desactivan la captura con un mensaje antes
de abrir el archivo; sin `GOW_GS_REPLAY_TRACE` no se instala el diagnóstico.
El perfil limpia las cuatro variables. Esta captura serializa el GS y no sirve
para medir FPS; los volcados permanecen en `logs/`, excluidos de Git.
Ejemplo y repetición: [RENDERIZADO.md](RENDERIZADO.md#repetición-local-de-comandos-gs).

### Control experimental del feedback OpenGL

`PS2X_GS_FEEDBACK_SNAPSHOT=1`, establecido antes de lanzar el ejecutable, protege
la fuente de textura cuando una primitiva escribe en sus mismas páginas. Queda
desactivado por defecto. Congela la fuente por primitiva y sirve para contrastar
la inestabilidad de OpenGL; la caché GS de 8 KiB y los lotes compatibles todavía
requieren verificación. El renderer CPU conserva su comportamiento.

Los controles sin el juego y sus límites están en
[RENDERIZADO.md](RENDERIZADO.md#separación-de-lotes-y-fuente-protegida-opcional).
`repetir_gs` selecciona explícitamente esta política con `--snapshot-feedback`
en modo compute/hardware. Continúa señalando las diferencias con CPU mediante
salida 1, aunque la imagen GPU se mantenga estable entre repeticiones.

`--pausa-ms M` añade una espera de 1..1000 ms entre pasadas de `repetir_gs`;
requiere `--repeticiones N` con N mayor que 1. Permite que el compilador de
shaders termine mientras se conserva el mismo backend. Ocho pasadas sin espera
pueden completar sus imágenes en compute antes de que hardware esté listo:
se deben comprobar `prims` y `tiles`, además del código de salida. La espera
no cambia el estado inicial ni las comparaciones y no mide los FPS del juego.

`--checkpoints-sync`, junto a `--repeticiones N` con N mayor que 1, compara
huellas FNV-1a64 de los 4 MiB de VRAM después de Flush, Sync, Present y End.
Indica el primer control que varía entre pasadas, con registro, operación y
dibujos acumulados. Las comparaciones exactas del End, estado y cuadros se
mantienen. Una huella distinta también produce salida 1, aunque el End coincida.
El historial está limitado a 4096 controles y un exceso se rechaza antes de
repetir dibujos. Añade readbacks y puede cambiar los tiempos: no mide FPS.
Se excluye TEXFLUSH porque no drena un lote GPU en el backend actual; observarlo
con readback introduciría un corte nuevo. Las huellas sirven para localizar
variación y no certifican igualdad byte a byte de los estados intermedios.

`--hasta-registro R` termina la repetición en un Flush, Sync, Present o End
registrado, con `Initial=0`. Permite reducir una diferencia a un tramo corto
sin añadir un corte entre dibujos. Comprueba la frontera antes de crear el
backend; rechaza Submit, TEXFLUSH, índices inexistentes y opciones duplicadas.
En un prefijo compara exactamente los 4 MiB y el estado CPU/candidato y las
presentaciones que ya ocurrieron. El End original y el resto de la captura
quedan sin validar; seleccionar su registro End conserva la comprobación
completa. El límite de 4096 controles se aplica solo al tramo seleccionado.
