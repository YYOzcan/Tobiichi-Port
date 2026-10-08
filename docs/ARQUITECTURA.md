# Arquitectura

## Pipeline de compilación

`scripts/compilar.ps1` ejecuta estos pasos:

1. **Comprobación de herramientas** — `git`, `cmake`, `ninja` (entorno de MSVC cargado por `2_compilar.cmd`).
2. **PS2Recomp** — clona `ran-j/PS2Recomp` en `<unidad>:\gowport\PS2Recomp`, hace checkout del commit
   `c5a9d02573410a2085a4b4b831b0b68ba3515440` e inicializa submódulos.
3. **Parches** — aplica la lista completa en el orden que define [`scripts/compilar.ps1`](../scripts/compilar.ps1).
   [`tools/ci/parches.py`](../tools/ci/parches.py) obtiene esa misma lista para la CI y comprueba que no
   falte ningún archivo de `patches/`. Desde la raíz, `python tools/ci/parches.py` muestra los parches
   y su orden; esa es la referencia para preparar un cambio sobre el runtime fijado.

   Los temas se mantienen en parches separados: arranque y servicios del runtime, EE/FPU/MMI,
   IOP/audio/memory card, DMA/VIF/GIF/VU y renderizado GS. Los backends CPU/OpenGL, el muestreo,
   la presentación y el feedback opcional se describen en [`RENDERIZADO.md`](RENDERIZADO.md);
   los controles ejecutados y sus límites se registran en [`ESTADO.md`](ESTADO.md).

   Antes de reaplicar la lista, el script retira los archivos que algún parche crea (`new file mode`),
   conservando una limpieza común para nuevos parches. Cada cambio de parches requiere la
   compilación completa con `scripts\2_compilar.cmd`; la compilación rápida solo actualiza los overrides.

4. **Ajustes de CMake** — añade `src/runner` a los includes de `ps2EntryRunner` y desactiva `/GL` y `/LTCG`
   para compilar en paralelo (con LTCG el enlazado de ~6 400 archivos es inviable).
5. **Recompilador** — compila el objetivo `ps2_recomp`.
6. **Generación de C++** — rellena `config/recomp.template.toml` (`@ELF@`, `@MAP@`, `@OUT@`) y ejecuta
   `ps2_recomp` sobre `SCUS_973.99`.
7. **Runtime** — copia el código generado y `src/gow_overrides.cpp` a `ps2xRuntime/src/runner` y compila
   `ps2EntryRunner` (unity build + PCH).

Las trazas `PS2X_ENABLE_RUNTIME_LOGS`, `PS2X_ENABLE_AGRESSIVE_LOGS` y `PS2X_ENABLE_IOP_RPC_TRACE`
se configuran en `OFF` por defecto; `scripts\2_compilar.cmd -Trazas` las activa para investigar.
El perfil `GOW_PERF_DIAG` es independiente de estas opciones de compilación; se describe en
[`ESTADO.md`](ESTADO.md#medicion-de-rendimiento-2026-10-05).

La selección CPU / CPU con hilo / OpenGL, la procedencia GPL-3.0 del fork SotC y sus límites
se describen en [`RENDERIZADO.md`](RENDERIZADO.md). Este parche GS se mantiene separado de los
arreglos EE/FPU/IOP de Opus; no modifica el parche de operandos FPU existente.

## Configuración del recompilador

`config/recomp.template.toml` contiene:

- **`stubs`** — funciones de librerías de Sony (`sceMpeg*`, `sceIpu*`, `sceGs*`, `sceDma*`, `sceCd*`, libc…)
  que el runtime implementa de forma nativa.
- **`skip`** y parches de instrucciones generados con `ps2xAnalyzer` y ajustados a mano.

`config/funcmap.csv` (`Name,Start,End,Size`) define los límites de las 6 414 funciones del ELF.

## Overrides (`src/gow_overrides.cpp`)

Se registran con `PS2_REGISTER_GAME_OVERRIDE` para el ELF `SCUS_973.99` (entry `0x00100008`).

| Dirección | Función | Motivo |
|---|---|---|
| `0x00296C48` | `sceSifInitRpc` | El recompilador la descarta: empieza en el delay slot de un `jr ra` suelto |
| `0x00294990` | `iWakeupThread` | Mismo caso que la anterior |
| `0x0027AB00` | `sceCdReadDvdDualInfo` | Sin handler en el runtime; devuelve doble capa con inicio de capa 1 en LBN `2080544` |
| `0x0026BF28` | `snd_SendIOPCommandAndWait` (`989snd`) | Registra cada comando (`[gow-snd]`) y llama al original; con `GOW_SND_STUB=1` responde 0 sin pasar por el IOP |
| `0x00298CE8` | `sceSifLoadStartModuleBuffer` | Módulo IOP embebido `ck01`: se responde como consola retail (`NO_RESIDENT_END`) |

## Parche del runtime (`patches/ps2recomp-runtime.patch`)

| Archivo | Cambio |
|---|---|
| `ps2xIOP/src/modules/gow_stub_services.cpp` *(nuevo)* | Servicio IOP silencioso para el motor de sonido **989snd** (`989nomid.irx`) |
| `ps2xIOP/src/modules/dbcman.cpp` | Responde a los servidores secundarios de `dbcman` (`0x8000131C/E/F`) |
| `ps2xIOP/src/iop_subsystem.cpp`, `module_factories.h`, `CMakeLists.txt` | Registro del nuevo servicio |
| `ps2xRuntime/src/lib/Kernel/Syscalls/System.cpp` | El juego recibe su propio heap |
| `ps2xRuntime/src/lib/ps2_runtime.cpp` | Heap privado del runtime en `0x000A0000–0x000FF000`; anillo de traza de saltos |
| `ps2xRuntime/src/lib/Kernel/EeScheduler.cpp` | Ajuste en `makeRunning` |

## Integración continua

`.github/workflows/pruebas.yml` se ejecuta en cada push a `main` y en cada PR, sin necesitar el juego:

- **Comprobaciones rápidas** (segundos):
  - `tools/ci/validar_config.py` valida `config/funcmap.csv` (orden, solapes, tamaños, nombres) y
    `config/recomp.template.toml` (marcadores `@ELF@/@MAP@/@OUT@`, formato `nombre@0xDIRECCION`, direcciones
    dentro de alguna función). Los stubs que no empiezan una función y las direcciones repetidas son avisos.
  - `tools/ci/analizar_ps1.ps1` analiza sintácticamente todos los `.ps1` con el parser de PowerShell.
  - Compila y ejecuta `tests/pad2_packet_test.cpp` con GCC.
- **Parches y suite del runtime**: descarga PS2Recomp en el commit de `scripts/common.ps1`, aplica los
  parches en el orden de `compilar.ps1` (`tools/ci/parches.py` los lee de ahí y falla si algún
  `patches/*.patch` no se aplica), comprueba que cada stub de `recomp.template.toml` tiene handler en
  `ps2_call_list.h` (`validar_config.py --runtime`), compila `ps2x_tests` en Linux y ejecuta la suite. También compila
  `src/*.cpp` contra las cabeceras del runtime ya parcheado (declarando las `sub_*` que usan), así un override
  que use una función del runtime que ningún parche define falla aquí y no solo en Windows.
  `tools/ci/comprobar_pruebas.py` solo falla por pruebas que no estén en `tests/fallos_conocidos.txt`
  (hoy vacía: la suite pasa entera). Cuando una prueba de la lista pase, la CI lo avisa para quitarla.
  La CI incluye `tools/ci/pruebas_gs.cmake` en su checkout temporal de PS2Recomp para compilar y
  ejecutar `tests/gs_replay_test.cpp`: captura/replay CPU, parser, truncamiento, opciones inválidas y
  comienzo después de TEXFLUSH, sin el juego ni contexto OpenGL. Los archivos sintéticos quedan
  en el directorio temporal de compilación.
  También compila la CLI `repetir_gs` y ejecuta los controles de
  `tests/gs_replay_checkpoints_test.cpp` y `tests/gs_replay_cli_test.py`:
  variación intermedia aunque el End coincida, argumentos, repetición CPU
  y límite previo de controles sincronizados. No requieren contexto OpenGL.

`.github/workflows/estado.yml` regenera el mapa de estado (`docs/estado/`) cuando cambian sus datos.

Las PR #17/#18 añaden escrituras directas opcionales y un despachador VU1
compilado, en parches separados después de los de GS. La #12 se integra
conservando los arreglos equivalentes actuales y adaptando únicamente el
diagnóstico de presupuesto al nuevo `StepContext`. El microcódigo y el C++
VU1 generado siguen siendo datos privados, fuera del repositorio.
