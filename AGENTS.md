# Guía para agentes y colaboradores

Port de *God of War* (PS2, `SCUS-97399`) por recompilación estática con
[PS2Recomp](https://github.com/ran-j/PS2Recomp), sobre el runtime de
[Waffle565/God-Of-War-Native-Port](https://github.com/Waffle565/God-Of-War-Native-Port). Este repositorio no contiene
archivos del juego ni el C++ generado. Estado de la versión: [`docs/ULTIMATE.md`](docs/ULTIMATE.md).

## Dónde va cada cosa

| Cambio | Dónde |
|---|---|
| Reemplazos y diagnósticos de funciones del juego | `src/gow_overrides.cpp` (el instalador lo copia a `PS2Recomp/ps2xRuntime/src/runner/`) |
| Funciones de Tobiichi Port (lanzador, panorámico, trucos, fijar objetivo, combate) | `PS2Recomp/ps2xRuntime/src/lib/gow_*.cpp`, conectadas en `gow_integracion.cpp` |
| Runtime, IOP, recompilador | `PS2Recomp/` (en el árbol; ya no hay parches aparte) |
| Funciones, stubs y parches del recompilador | `config/recomp.template.toml`, `config/funcmap.csv` |
| Lanzador | `launcher/` (Qt 6) |
| Instalación | `instalar.sh` (Linux), `instalar.ps1` + `instalar.cmd` (Windows) |
| Documentación | los tres README (deben decir lo mismo), `docs/ULTIMATE.md`, `docs/ESTADO.md` |

## Reglas

- Marca los cambios en el código heredado con un comentario `// GOW-Port:`.
- No edites a mano los archivos generados (`PS2Recomp/ps2xRuntime/src/runner/*.cpp`, `ps2xIOP/src/native/iopn_*`,
  `build/*/vu1_generado`, `vu1n_generado`): se regeneran.
- Cambiar una cabecera incluida por el código generado (`ps2_runtime.h`, `ps2_memory.h`, `ps2_perf.h`...) recompila
  las ~6.400 unidades: evítalo si un `.cpp` basta.
- Los overrides llaman a la función original para todo lo que no reemplazan y respetan las reanudaciones tras un
  checkpoint (`ctx->pc` distinto de la entrada: llamar al original sin más).
- Diagnósticos opcionales con una variable de entorno (`GOW_*_DIAG`) y una etiqueta `[gow-xxx]` en el registro.
- Documentación y comentarios en español; los commits pueden ir en español o en inglés.

## Compilar y probar

`./instalar.sh` (o `instalar.cmd`) hace todo; para iterar, desde `PS2Recomp/`: `ninja -C build ps2EntryRunner`.
Pruebas con el juego: `./run_gow.sh` con `GOW_PAD_TEST=1 GOW_PAD_GUION="5:start,12:x,20:x"` (pulsaciones),
`GOW_PAD_CAPTURAS=...` (capturas del GS) y `GOW_HOST_SHOT=<cuadro>` (captura de la ventana).

## Legal

Nunca subas archivos del juego (ELF, IRX, ISO, `.PAK`), código generado a partir de él, capturas de RAM/VRAM ni
el microcódigo de VU1 capturado. `game/`, `capturas_vu1/`, `build-gen/` y `logs/` están en `.gitignore`.
