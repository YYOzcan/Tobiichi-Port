# Guía para agentes y colaboradores

Port de *God of War* (PS2, `SCUS-97399`) por recompilación estática con
[PS2Recomp](https://github.com/ran-j/PS2Recomp). Este repositorio no contiene archivos del juego ni el C++
generado: solo lo específico de God of War. Estado e investigación: [`docs/ESTADO.md`](docs/ESTADO.md).
Arquitectura y CI: [`docs/ARQUITECTURA.md`](docs/ARQUITECTURA.md).

Varios agentes trabajan a la vez sobre `main`. Antes de empezar, `git pull`; antes de subir, vuelve a
traer `main` e integra los cambios (merge, nunca reescribas historia publicada).

## Dónde va cada cosa

| Cambio | Dónde |
|---|---|
| Reemplazos y diagnósticos de funciones del juego | `src/gow_overrides.cpp` (`applyGowOverrides`) |
| Cambios al runtime/IOP de PS2Recomp | un parche por tema en `patches/` |
| Funciones, stubs y entry points del recompilador | `config/recomp.template.toml`, `config/funcmap.csv` |
| Pruebas independientes del juego | `tests/` (las del runtime van dentro del parche, en `ps2xTest/`) |
| Estado del port (mapa del README) | `docs/estado/datos.toml` |
| Registro de la investigación | `docs/ESTADO.md` y `docs/CONTROLES.md` |

## Parches de PS2Recomp

- Se aplican sobre el commit fijado en `scripts/common.ps1` (`$PS2RecompCommit`), **en el orden de
  `scripts/compilar.ps1`**, con `git apply --ignore-whitespace`. Cada parche se genera contra el árbol con
  los anteriores ya aplicados.
- **Parche nuevo:** añade en `scripts/compilar.ps1` su variable (`$xxxPatch = Join-Path $RepoRoot
  'patches\ps2recomp-xxx.patch'`) y su línea `Run $git @('apply', ...)`. La CI lee la lista de ahí
  (`tools/ci/parches.py`) y falla si un `patches/*.patch` no se aplica.
- Prefiere un parche nuevo por tema a ampliar `ps2recomp-runtime.patch`: los cambios de otros agentes
  chocan menos.
- **Editar un parche existente** (`N` = el que cambias), desde la raíz del repositorio (`PS2Recomp/` está en
  `.gitignore`):

  ```sh
  git clone https://github.com/ran-j/PS2Recomp.git PS2Recomp   # solo la primera vez
  git -C PS2Recomp checkout -qf <commit fijado> && git -C PS2Recomp clean -fdq
  # aplica, en orden, los parches anteriores a N y haz un commit "base"
  git -C PS2Recomp apply --ignore-whitespace "$PWD/patches/<parche anterior>"   # uno por parche
  git -C PS2Recomp -c user.name=x -c user.email=x commit -qam base
  git -C PS2Recomp apply --ignore-whitespace "$PWD/patches/<N>"
  # ... edita ...
  git -C PS2Recomp diff > patches/<N>
  ```

  Después comprueba que los parches posteriores a `N` siguen aplicando.
- Marca los cambios con un comentario `// GOW-Port:` para distinguirlos del código original.
- Un cambio de comportamiento del runtime lleva una prueba de regresión en `ps2xTest/` que falle sin el
  cambio. Si cambias a propósito algo que una prueba existente comprobaba, ajusta la prueba y explica por qué.
- Los cambios en parches requieren `scripts\2_compilar.cmd`; `2_recompilar_rapido.cmd` solo copia
  `src/gow_overrides.cpp` y `src/*.h`.

## Overrides (`src/gow_overrides.cpp`)

- Llama a la función original para todo lo que no reemplaces, y respeta las reanudaciones tras un
  checkpoint (`ctx->pc` distinto de la dirección de entrada: llama al original sin más).
- Los diagnósticos son opcionales: actívalos con una variable de entorno (`GOW_*_DIAG`) o con un límite de
  mensajes, y usa una etiqueta `[gow-xxx]` en el registro. Documenta la variable en `docs/ESTADO.md` o
  `docs/CONTROLES.md`, y retira el diagnóstico cuando el problema esté resuelto.
- Si usas una función nueva del runtime, debe existir en algún parche: la CI compila `src/*.cpp` contra el
  runtime parcheado.

## Comprobaciones (CI: `.github/workflows/pruebas.yml`)

En cada push a `main` y en cada PR, sin el juego. Deben quedar en verde:

- `python3 tools/ci/validar_config.py`: `funcmap.csv` y `recomp.template.toml`.
- `pwsh -File tools/ci/analizar_ps1.ps1`: sintaxis de los `.ps1`.
- `tests/pad2_packet_test.cpp` (en Windows: `scripts\probar_pad2.cmd`).
- Los parches aplican, cada stub tiene handler en el runtime, `src/*.cpp` compila contra el runtime
  parcheado y la suite `ps2x_tests` pasa entera. `tests/fallos_conocidos.txt` está vacío: no añadas una
  prueba ahí para tapar una regresión, arréglala.

La suite se puede reproducir en Linux (o WSL): aplica los parches como arriba y luego

```sh
cmake -S PS2Recomp -B PS2Recomp/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DPS2X_BUILD_STUDIO=OFF \
  -DCMAKE_C_FLAGS=-march=x86-64-v2 -DCMAKE_CXX_FLAGS=-march=x86-64-v2
ninja -C PS2Recomp/build ps2x_tests
PS2Recomp/build/ps2xTest/ps2x_tests 2>/dev/null | python3 tools/ci/comprobar_pruebas.py tests/fallos_conocidos.txt
```

(paquetes de Ubuntu: los de "Instalar dependencias" en `pruebas.yml`).

## Probar con el juego (Windows)

Lo que la CI no puede comprobar: hace falta el ELF, los IRX y la ISO (ver README).

1. `scripts\2_compilar.cmd` (o `2_recompilar_rapido.cmd` si solo cambiaste `src/`).
2. `scripts\probar_menu.ps1 -Segundos 115`: avanza por el menú y guarda capturas del GS en `logs\`.
3. Revisa `logs\ejecutar_err.log` y las capturas. Una captura no negra o un registro limpio no prueban que
   se pueda jugar: anota en `docs/ESTADO.md` exactamente qué se verificó.

## Documentación y estado

- `docs/ESTADO.md` es el registro de la investigación: añade lo que se probó, con qué resultado y los
  próximos pasos. No borres hallazgos; corrígelos si resultan equivocados.
- Si un componente o librería cambia de estado (funciona / parcial / pendiente), actualiza
  `docs/estado/datos.toml` y ejecuta `python tools/estado/generar.py` (la acción "Mapa de estado" lo hace
  también al subir a `main`).
- Los tres README (`README.md`, `README.es.md`, `README.pt-BR.md`) deben decir lo mismo.
- Documentación y comentarios en español; los commits pueden ir en español o en inglés.

## Legal

Nunca subas archivos del juego (ELF, IRX, ISO, `.PAK`, `.WAD`), código generado a partir de él, capturas de
RAM/VRAM ni volcados del microcódigo. `game/` y `logs/` están en `.gitignore`.
