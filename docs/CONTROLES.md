# Entrada del mando y pruebas del menú

God of War usa **libpad2** (sockets), mientras que el backend de entrada de PS2Recomp entrega paquetes
de libpad (puerto/slot). Los overrides de `src/gow_overrides.cpp` conectan ambas interfaces para el
primer puerto. El segundo puerto permanece desconectado; todavía no hay vibración.

## Teclado

### Configurable (lanzador)

El lanzador pasa el mapa en `TOBIICHI_TECLAS="accion=codigo,codigo;..."`. Cada acción admite dos teclas; los códigos
son los de raylib/GLFW (posición física) y `1000 + botón` para el ratón (1000 izquierdo, 1001 derecho, 1002 central,
1003/1004 laterales). Shift, Ctrl y Alt valen por el izquierdo y el derecho.

- Acciones: `up down left right cross circle square triangle l1 r1 l2 r2 l3 r3 start select furia` (L3 + R3),
  `li_arriba li_abajo li_izq li_der` (stick izquierdo), `ld_arriba ld_abajo ld_izq ld_der` (stick derecho) y
  `ld_mod`: mientras está pulsado, las teclas del stick izquierdo mueven el derecho.
- Acciones de God of War:
  - `poseidon medusa zeus hades`: cada una pulsa la dirección de la cruceta que elige esa magia;
  - `artemisa`: pulsa L1 + R1 a la vez, lo que saca o guarda la Espada de Artemisa.
- Cruceta y magias, según la tabla de controles del juego (0x29D058). Las direcciones dan los bits 26-29 de la
  entrada del jugador, y 0x1D7250 los convierte en `SelectMagic` 3-6:
  - derecha = Furia de Zeus (3);
  - izquierda = Mirada de Medusa (4);
  - abajo = Ira de Poseidón (5);
  - arriba = Ejército de Hades (6).
- La magia elegida queda en 0x302D3E. Comprobado en partida (`logs/dpad1`): abajo → 5 y derecha → 3.
- La Espada de Artemisa no es una magia elegible: sus golpes (L1 + botón) solo exigen tenerla (bit 0x40 de
  0x302D42, ver 0x2075E8).
- Una tecla que también es `ld_mod` solo cuenta como botón si no se está moviendo. Así Ctrl puede ser R2 y Ctrl +
  WASD esquiva sin lanzar la magia.
- Los botones salen de `ps2_pad.cpp`. Los sticks también, pero `gowPad2Read` (overrides) escribe los suyos fijos;
  con `TOBIICHI_TECLAS`, `ps2_runtime.cpp` envuelve esa función (0x27B9F0) y pone los del mapa en el paquete.

Esquema por defecto del lanzador:

| Tecla | Control de PS2 | En el juego |
|---|---|---|
| WASD | Stick izquierdo | Moverse |
| Ctrl + WASD | Stick derecho (el izquierdo queda centrado) | Esquivar |
| 1 / 2 / 3 / 4 | Cruceta abajo / izquierda / derecha / arriba | Ira de Poseidón / Mirada de Medusa / Furia de Zeus / Ejército de Hades |
| Clic central | L1 + R1 | Sacar / guardar la Espada de Artemisa |
| Flechas | Cruceta | Menús |
| Clic izquierdo | Cuadrado | Ataque ligero |
| Clic derecho | Triángulo | Ataque fuerte |
| F | Círculo | Agarre |
| Espacio | X | Salto |
| Q | L1 | Bloqueo / parada |
| Shift | L2 | Lanzar la magia elegida |
| Ctrl (sin mover) | R2 | Acción, interactuar |
| E | R1 | Acción |
| V | L3 + R3 | Furia de los dioses |
| Enter / Tab | Start / Select | Menú de poderes / Select |
| IJKL | Stick derecho | |

### Fijo (sin `TOBIICHI_TECLAS`)

Disposición anterior, cuando no hay un gamepad conectado (`TOBIICHI_DMC5_CONTROLS` distinto de 0):

- WASD: stick izquierdo; Ctrl + WASD: stick derecho.
- Clic izquierdo: Cuadrado; clic derecho: Triángulo.
- F: Círculo; Espacio: X; Shift: L1; Q: R2; E: R1; V: L3 + R3.
- Flechas: cruceta; Enter / Tab: Start / Select.
- Sin L2.

Con `TOBIICHI_DMC5_CONTROLS=0`:

- WASD también mueve la cruceta.
- X / C / Z / V para los botones.
- Q / E = L1 / R1.
- Shift izquierdo / derecho = L2 / R2.

El backend usa el gamepad de índice 0 cuando está disponible. Sus botones, sticks y gatillos se
adaptan al paquete libpad2. Las presiones se simulan como 0 o 255 según el botón esté suelto o pulsado.

## Menú de trucos (F2)

`PS2Recomp/ps2xRuntime/src/lib/gow_trucos.cpp`. **F2** abre y cierra el menú durante la partida:

- ↑↓ (o W/S) para elegir, Enter / Espacio / ←→ para activar, F2 / Esc / Retroceso para cerrar.
- El ratón también funciona: pasar por encima elige, clic izquierdo activa.
- Con mando: cruceta, X activa, Círculo cierra. El menú no se abre desde el mando.
- Con el menú abierto el juego recibe el mando en reposo: el envoltorio de scePad2Read pone botones sueltos,
  sticks centrados y presión 0. El juego sigue corriendo.
- Al cerrar, el juego sigue sin recibir nada hasta que se suelta la tecla que lo cerró (Esc es Círculo con el
  teclado clásico).
- Mientras está abierto, Escape no cierra el juego (`SetExitKey(KEY_NULL)`).
- Textos en turco, inglés o español (`TOBIICHI_IDIOMA`), con una fuente del sistema: DejaVu / Noto / Liberation,
  o Segoe UI / Arial en Windows. `TOBIICHI_FUENTE_MENU=<ttf>` fuerza otra fuente; sin ninguna, se usa la de raylib.

`TOBIICHI_TRUCOS` (lista separada por comas) da el estado inicial:

| Id | Truco | Cómo |
|---|---|---|
| `inmortal` | Inmortalidad | Envoltorios de 0x1E0A80 (fija la vida: no baja para Kratos) y 0x1E0A98 (resta daño: 0 para Kratos); en cada VBlank rellena la vida si sigue vivo |
| `un_golpe` | Muerte de un golpe | 0x1E0A98: el daño a otra criatura cubre toda su vida, así se avisan todos los umbrales (fases de jefes); 0x1E0A80: una bajada deja la vida en 0 |
| `magia` | Magia infinita | Magia (0x302D1C) = máximo de su nivel (0x3028F4 + 4 × nivel) |
| `furia` | Furia de los Dioses infinita | Medidor (0x302D20) = 100, el tope de AddRage (0x1DA938) |
| `orbes` | Orbes rojos al máximo | 0x302D28 = 60000, el tope de SetOrbs (0x1DB250) |
| `mejoras` | Todas las mejoras | Niveles 0x302D38-0x302D3C ≥ 2 (magias, Artemisa) y 0x302D3D ≥ 4 (Espadas del Caos): lo que 0x1D8CB8 da por completo |
| `poderes` | Todos los poderes y armas | 0x302D42 \|= 0x017C (Zeus, Medusa, Poseidón, Hades, Artemisa, tridente) |
| `medidores` | Vida y magia al máximo | Nivel de vida 0x302D36 = 4 y de magia 0x302D37 = 5, los topes de 0x1D8200; vida máxima de Kratos = 0x3028F0 |
| `extras` | Desbloquear todos los extras | 0x2A12C8 \|= 0x1F (partidas terminadas en cada dificultad + Desafío de los Dioses). Es lo que miran los extras, los trajes y la dificultad Modo Dios. Al guardar queda en la tarjeta |

Antes de escribir en Kratos (`*(*0x29CD58)`) se comprueba que su vida máxima (+0x17C) sea una de la tabla de
niveles: así no se escribe en un objeto liberado durante una carga. Si no hay Kratos, los envoltorios no tocan nada.
Así la muerte de un golpe no le alcanza aunque el puntero falle.

Diagnóstico: `TOBIICHI_TRUCOS_DIAG=1` escribe el estado cada 2 s (`[trucos]`) y las primeras 400 llamadas a la vida
(`[trucos:vida]`). `TOBIICHI_TRUCOS_ABRIR_EN=<s>` abre el menú a esa hora (capturas de prueba sin teclado).

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

## Fijar objetivo (Alt)

`PS2Recomp/ps2xRuntime/src/lib/gow_fijar.cpp`. Funciona como el bloqueo de objetivo de los God of War modernos.
`GOW_FIJAR=0` lo desactiva.

| Entrada | Efecto |
|---|---|
| Alt (izquierdo o derecho), pulsado y soltado solo | Fija el enemigo actual: el más cercano a Kratos, favoreciendo el centro de la pantalla, hasta 1500 unidades. Otra pulsación lo suelta. |
| Mover el ratón a izquierda o derecha (60 px) | Pasa al siguiente enemigo visible en ese lado de la pantalla. |

- Alt cuenta al soltarse, si se pulsó solo, menos de 0,6 s y con la ventana activa: Alt+Tab y las pulsaciones
  fantasma al cambiar el foco no fijan nada.
- Sus ataques van al objetivo fijado. El juego ya tiene puntería automática: `0x1D78B0` elige el objetivo con
  `0x1D90F0` (o `0x1D9750` en modo manual) y guarda su identificador en el estado del ataque. Aquí se envuelven las
  dos funciones: tras la elección del juego devuelven el identificador del enemigo fijado.
- Si el objetivo muere o se aleja más de 3000 unidades, se pasa al enemigo más cercano. Sin enemigos, se suelta.
- Un rombo rojo marca el pecho del objetivo: su posición más 0,55 veces su alto, proyectada con la matriz de la
  cámara.
- **Comprobado** (`logs/fijar7`, cubierta del barco, ataques sin mover el stick):
  - Fijado un legionario que no era el más cercano (42 unidades; había otro a 22).
  - En los dos volcados, el eje −Z de Kratos (−(+0xB0)) apunta a él (cos = −0,99 y −1,00), y su vida baja de 35
    a 31.
  - El cambio con el ratón y la marca se comprobaron en capturas (`logs/fijar5`, `logs/fijar6`).
- **No hay:**
  - Cámara fija al objetivo: la cámara de God of War es de guion y no se controla.
  - Desplazamiento lateral alrededor del objetivo.
  - Botón del mando: L3 + R3 ya es la Furia de los Dioses.

### Datos del juego

| Dirección | Contenido |
|---|---|
| `*(*0x29CD58)` | Kratos (criatura de 0x360 bytes): pies +0xC0, ejes +0x90/+0xA0/+0xB0 (de frente: −(+0xB0)), vida +0x178, máxima +0x17C, alto +0x124 |
| `*0x29E414` | Reserva de criaturas del área: cabecera `0x31415927`; 32 entradas de 0x20 desde +0x20; viva: criatura en +0x00 y `0x2B95E8` en +0x18; libre: enlace a la siguiente |
| `*0x29D2AC` | Tabla de identificadores: entradas de 12 bytes desde +8 `{identificador, clase, objeto}`, índice = identificador >> 23 |
| `*0x35FA98` | Cámara: matriz del mundo +0x00, vista-proyección +0x40 (vector fila, `clip = (x, y, z, 1) * M`, y de pantalla hacia abajo) |
| `0x30290C` / `0x302910` | "Targeting Range" / "Manual Targeting Range" (ajustes del jugador 0x3028E0 + 0x2C / + 0x30) |

### Herramientas de investigación

- `GOW_FIJAR_STICK="t0:dur:lx:ly;..."`: fuerza el stick izquierdo.
- `GOW_FIJAR_VOLCADO="t1,..."`: guarda la RAM del EE en `fijar_ram_<t>.bin`. Solo en local; nunca se sube.
- `GOW_FIJAR_PRUEBA="t:alt;t:der;t:izq"`: simula Alt y el ratón.
- `GOW_FIJAR_DIAG=1`: registra los cambios de objetivo y las proyecciones.
- `TOBIICHI_CERRAR_TRAS=N`: cierra la ventana a los N segundos.

Así se encontraron los datos: volcados de RAM con el stick forzado; búsqueda de la posición de Kratos y de criaturas
con la misma estructura; punteros a la reserva y a la tabla; búsqueda por fuerza bruta de una matriz que pone a
Kratos y a los enemigos en el sitio de la captura.

## Cancelar animaciones (combate ágil)

`PS2Recomp/ps2xRuntime/src/lib/gow_cancelar.cpp`. Está activado por defecto. Se desactiva con `GOW_CANCELAR=0` o
con la opción del lanzador "Combate ágil".

**Lo que el juego ya hace.** Un ataque se corta en el cuadro siguiente con el bloqueo (L1) o con la evasión (stick
derecho), también en mitad del combo y en el triángulo. Medido con L1 a los 0,11 s del primer golpe, con el ataque
fuerte y con el cuarto cuadrado: el bloqueo (`0x30`) empieza uno o dos cuadros después.

**Lo que obligaba a esperar** (medido en la cubierta del barco):

| Caso | Original | Con el cambio |
|---|---|---|
| Atacar desde una evasión | La pulsación se acepta pero espera al 50 % de la voltereta: el ataque sale a los 0,61 s | Espera al 20 %: sale a los 0,29 s |
| Soltar L1 y pulsar cuadrado o triángulo en el mismo cuadro | La pulsación se pierde: no sale el ataque | Búfer de entrada: el ataque sale a los 0,07-0,08 s |
| Golpe recibido (`0x64`-`0x6C`) | No acepta ninguna transición | Igual: no se cambia |
| Combo de cuadrado | Cada golpe espera al 27/35/47/37 % del anterior | Igual por defecto. Con `GOW_CANCELAR_COMBO=<factor>` se multiplica; con 0,6 salen 5 golpes en 0,9 s en vez de 3, pero no se comprobó que no se pierdan impactos |

Variables:

- `GOW_CANCELAR_EVASION=<0..1>`: umbral máximo en una evasión. Por defecto, 0,2.
- `GOW_CANCELAR_COMBO=<0..1>`: factor de los umbrales entre ataques. Por defecto, 1.
- `GOW_CANCELAR_BUFER=0`: sin búfer de entrada.

**Búfer de entrada.**

- Una pulsación de cuadrado o triángulo que el juego no aceptó se repite: un cuadro suelto y otro pulsado.
- Se repite cada 35 ms, como mucho 3 veces y durante 0,35 s.
- Se deja de repetir en cuanto aparece una transición en la cola, una petición en `+0x44` o un ataque nuevo.

### Datos del juego

| Dirección | Contenido |
|---|---|
| `*(Kratos+0x324)` | Controlador de movimientos (`0x79F300` en la cubierta). Los de los enemigos van a continuación, cada 0x210. |
| controlador +0x44 | Siguiente golpe del combo pedido (puntero; 0 si no hay). |
| controlador +0x4C / +0x54 | Transición en curso / registro del movimiento en la tabla del nivel (0x18 bytes: hash, identificador, desplazamientos, banderas). |
| controlador +0x50 | Contador de movimientos (+1 cada vez que empieza uno). |
| controlador +0x58 | Identificador del movimiento (ver la tabla siguiente). |
| controlador +0x70 | Máscara recalculada en cada cuadro por `0x207EF8`. Escribirla no cambia nada. |
| controlador +0x78 | Bits de eventos de la animación ya pasados. |
| controlador +0x1AC | Estado: 1 normal, 3 al empezar una evasión, 0x18 atacando, 0x19 bloqueando. |
| controlador +0x1C0 | Cola de transiciones pedidas: `{+0 puntero, +4 u8 tamaño (8), +5 u8 lectura (0xFF vacía), +6 u8 escritura}`. Entradas de 8 bytes `{transición, umbral (float)}`. |
| `0x2048F8` | Saca la transición de la cola cuando el avance normalizado del movimiento actual llega al umbral. |
| `0x2088E8` | `(controlador, transición)`: empieza un movimiento. Escribe +0x4C…+0x60, +0x70 = −1 y +0x78 = 0. |
| `0x203F90` | Transiciones al acabar una animación y golpes recibidos. Llama a `0x2088E8` desde `0x2046C8`. |
| `0x205488` | Actualización del controlador en cada cuadro: +0x44, +0x78. |

Identificadores de movimiento (+0x58):

| Identificador | Movimiento |
|---|---|
| 0x50 | De pie |
| 0x47, 0x48, 0x49, 0x4A, 0x4B | Combo de cuadrado (los registros de la tabla, cada 0x18 bytes) |
| 0x20 | Triángulo |
| 0x30 | Entrada al bloqueo desde un ataque o de pie |
| 0x21 | Bloqueo mantenido |
| 0x22 | Bloqueo recibiendo un golpe |
| 0x201-0x208 | Evasiones (0x202 y 0x205 con el stick derecho a la derecha) |
| 0x64-0x6C | Golpes recibidos |

Umbrales vistos en la cola:

| Transición | Umbral |
|---|---|
| Bloqueo y evasión desde cualquier ataque | 0 |
| Cuadrado tras cuadrado | 0,27 / 0,35 / 0,47 / 0,37 / 0,45 |
| Ataque desde una evasión | 0,5 |
| Bloqueo mantenido desde la entrada | 1,0 |
| Tras el golpe 0x69 | 0,8 |

### Herramientas de investigación

Todas son locales; los volcados contienen RAM del juego y nunca se suben.

- `GOW_CANCELAR_DIAG=1`: registra cada movimiento que empieza (`[gow-cancelar] mov`, con `$ra` y la transición),
  cada transición que entra en la cola con su umbral y lo que hace el búfer.
- `GOW_CANCELAR_TRAMO="t:dur:ini-fin,..."`: guarda regiones de RAM en cada lectura del mando.
  `tools/perfil/linea_cancelar.py <tramo.bin> t0 t1` muestra el controlador, con la región `79f300-79f500`.
- `GOW_CANCELAR_EJE="t:dur:byte:valor;..."`: fuerza un byte del búfer de libpad2. Los bytes 0-1 son los botones,
  2/3 el stick derecho X/Y y 4/5 el izquierdo.
- `GOW_CANCELAR_VOLCADO="t1,..."`: guarda la RAM del EE.
- `GOW_CANCELAR_VIGILAR="dir:bytes:t:dur"` (Linux x86-64): protege contra escritura la página de RAM del EE y
  apunta el RIP de cada escritura. Así se encontró `0x2088E8`: `nm` sobre `ps2EntryRunner` da
  `sub_002088E8_0x2088e8`.

**Cómo se encontró:**

1. Volcados de RAM de pie, atacando y bloqueando.
2. Registro por cuadro de 1,1 MB alrededor de los componentes de Kratos, buscando campos que cambian con las
   pulsaciones.
3. El controlador apuntado por Kratos+0x324.
4. Vigilancia de escrituras sobre su +0x54/+0x58.
5. Envoltorio de `0x2088E8`, que da los `$ra` de las llamadas.
6. Desensamblado de `0x2048F8` con `llvm-objdump --triple=mipsel-unknown-linux --mcpu=mips3`.

**Pruebas.** Las pruebas sin mando físico pueden recibir pulsaciones reales: si la ventana tiene el foco, el clic
del ratón es cuadrado. Por eso hay que mirar solo los instantes del guion (`GOW_FORCE_PAD`).

## Iconos de botones según el dispositivo

`PS2Recomp/ps2xRuntime/src/lib/gow_iconos.cpp`. Los iconos de botones del juego (X, círculo, L1...) se cambian por los
del dispositivo con el que se juega:

- Mando de PlayStation (DualShock, DualSense...): los originales, sin cambios.
- Otro mando: el botón del mando Xbox que da esa acción con el esquema activo. Con el esquema DMC5 por defecto, el aspa
  es A, el triángulo B, el círculo X, el cuadrado Y, L1 LB y R2 LT.
- Sin mando: la tecla o el botón del ratón asignados en el lanzador (`TOBIICHI_TECLAS`; sin la variable, el esquema
  fijo).
  - Espacio, Mayúsculas, Intro y Tab llevan su símbolo (⎵ ⇧ ↵ ⇥).
  - Los botones del ratón, el dibujo del ratón con el botón marcado.
  - Las letras, el nombre de la distribución activa (GLFW), también ı, ş, ğ.

Como en `ps2_pad.cpp`, con un mando conectado se usa el mando. Para elegir el estilo:

- `GOW_ICONOS_ESTILO=teclado|xbox|original` fuerza uno (opción "Iconos de botones" del lanzador).
- `GOW_ICONOS=0` lo desactiva.

**Diseño.** El juego reserva en el texto el sitio de un botón redondo. Por eso los iconos ocupan ese sitio:

- tecla cuadrada de piedra oscura con borde claro (algo más ancha solo para CTRL, ESC, F10...);
- disco para el mando Xbox, con la letra en su color;
- marco dorado en los avisos de los minijuegos.

El rótulo usa Cinzel (romana de inscripción, como la letra de los menús; OFL, `assets/fuentes/`, incrustada al
compilar). Los iconos se dibujan a resolución de la ventana y respetan el oscurecido y la transparencia del menú (cxform).

### Cómo dibuja el juego los iconos

- Los menús, los textos con `[XButton]`, `[L1Button]`... y los avisos de los minijuegos son películas de su
  reproductor de Flash (`renFlashServer`). Los iconos no son texturas: son formas vectoriales trianguladas para VU1.
- **Película en la RAM.** Cabecera: `0x21, 0x1E000004, 0x25803200` (escenario de 640 × 480 en twips).

  | Desplazamiento | Contenido |
  |---|---|
  | +0x0C/+0x10 | Caracteres: u32, índice << 16 \| tipo (1 forma, 3 fuente, 4 texto estático, 5, 6, 7 sprite) |
  | +0x14/+0x18 | Formas: 8 bytes, {u16 malla, u16 rellenos, puntero a los rellenos {color AARRGGBB, material}} |
  | +0x1C/+0x20 | Fuentes: 40 bytes; +0x14 formas de los glifos, +0x18 avances, +0x1C mapa carácter → glifo (u16) |
  | +0x3C/+0x40 | Sprites: 24 bytes; +0x02 número de listas, +0x10 listas {u16 tipo, u16 n, puntero} a registros de 10 bytes {profundidad, carácter, matriz, ?, cxform} |
  | +0x48 | Número de matrices |
  | +0x58/+0x5C | Almacén de cadenas |

  Los nombres de símbolo ("XButton", "XButtonGreek", "360CW"...) están en registros de colocación
  {u16 carácter, matriz, cxform, nombre, profundidad}.
- **Dibujo de una forma:** `0x149FA0(forma, ctx, id, matriz, cxform)`.
  - La matriz es 4 × 4 (escala en [0]/[5], traslación en [12]/[13]) en un espacio a medio píxel:
    x = 320 + tx / 2, y = 240 − ty / 2.
  - El cxform son multiplicadores 8.8: u16 r, g, b, a en las dos primeras palabras.
  - La malla: `*(*(ctx + 0xCE4) + 0xE4)` es la base. `base + 0x50` es la tabla de desplazamientos por número de
    malla. En la malla hay etiquetas DMA "ref" (id 3) hasta "ret", con `UNPACK V4-16` (0x6D) de vértices x, y en
    16 bits.
  - Con la caja de la malla se sacan el centro y el tamaño del icono.
- **Otras funciones:** `0x146FB8` dibuja un sprite, `0x149958` un campo de texto, `0x147520` recorre la lista de
  visualización.
- `0x14AB38` busca un símbolo por nombre. El texto con `[Nombre]` lo coloca en línea con `0x1491C8`, en
  `0x1494B0`: `[` y `]`, y `[*N]` cambia el color.

### Cómo se reconocen

- **Botones de cara.** Son un fondo y, encima, el símbolo con un solo relleno de color. El color es el mismo en todas
  las películas, también en las copias sin nombre de los menús (el "X = Select" del título):

  | Color | Botón |
  |---|---|
  | `FF9999FF` | Aspa |
  | `FFCC6400`, `FFCC4B00` | Círculo |
  | `FFCC3C28`, `FFFF6699` | Cuadrado |
  | `FF009955` | Triángulo |

  - Hace falta que el centro de su caja caiga dentro del fondo dibujado justo antes.
  - Ese fondo decide la variante: disco oscuro (2 rellenos, `xx191919`) en los menús, marco blanco (1 relleno) en los
    minijuegos.
  - El símbolo no se dibuja; el fondo sí, y lo tapa el icono.
- **Botones con rótulo** (L1, R2, START...). Son un fondo con rellenos `xx232323` y blanco, con el rótulo en glifos de
  la fuente encima.
  - Se leen las letras que caen dentro del fondo; cada glifo llega dos veces, contorno y relleno.
  - El icono tapa el fondo y el rótulo.
- **Cruceta, stick y avisos de los minijuegos.** Por el nombre del sprite: formas propias de un solo botón, y se
  descartan los aciertos de nombre sueltos.
- **Pestañas L1/R1 de la pausa.** Son un dibujo con el botón pintado: entrada fija de la película del HUD (936
  caracteres, 220 formas; formas 110 y 109).

**Comprobado** en el título, la elección de dificultad, la pausa (Power Up y Moves) y la ventana de información, con
teclado y con el estilo Xbox forzado:

- "Press ⎵ to funnel...", "⎵ = Power Up", ratón = Back.
- "Tap ⇧" (Hades Reverse, L1), "Tap F", "Hold" + ratón derecho.
- Pestañas ⇧/E y LB/RB.

**Rendimiento.** Medido en los primeros 70 s de partida: igual con los iconos y sin ellos (34-35 FPS con el
renderizador por software, 59-60 con el de hardware). La búsqueda de películas tarda ~6 ms y solo se hace al cargar una
película nueva.

**Sin comprobar:**

- Los avisos de los minijuegos: no se llega a ellos con el mando simulado.
- El círculo 3D sobre los enemigos (`goMiniGameCircle`, un modelo con textura, no Flash): sigue con el icono de
  PlayStation.

### Herramientas de investigación

- `GOW_ICONOS_DIAG=1`: cada forma dibujada la primera vez (malla, rellenos, colores, centro y radio), las películas
  encontradas, los rótulos leídos y los iconos sustituidos.
- `GOW_ICONOS_OCULTAR="a,b"`: no dibuja esas formas (entrada o id, en hex). Sirve para ver en una captura qué forma es
  cada cosa.
- `GOW_ICONOS_VOLCAR="t:carpeta"`: las texturas de Flash de la RAM, en PNG (subidas como CT32 y leídas como T8/T4).
- `GOW_ICONOS_TAMANO=f`: factor del tamaño de los iconos.
- `GOW_SONDEO="código_ini-código_fin:datos_ini-datos_fin:t:dur"` (`gow_sondeo.cpp`): envuelve todas las funciones
  recompiladas de un rango y cuenta las llamadas con algún argumento en un rango de datos. `sondeo.txt` trae
  ejemplos de argumentos. Así se encontraron las funciones del reproductor.
- `GOW_TEXTURAS="t:dur:carpeta"` (`gow_captura_gs.cpp`): cada textura distinta que dibuja el GS en ese tramo, en
  cualquier estado del juego, decodificada al dibujarla. Necesita `PS2X_GS_GPU=0 PS2X_GS_THREAD=0`.
- `GOW_GS_REPLAY_TRACE` se instala ahora también desde el runtime. `tools/render/texturas_gs.cpp` (objetivo
  `texturas_gs`) saca a PNG las texturas de una captura.
