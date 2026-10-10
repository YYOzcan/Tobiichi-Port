#!/usr/bin/env python3
"""GOW-Port: sincroniza este repositorio con KIexster/god-of-war-recomp (remoto "kiexster").

Los dos repositorios no comparten historia ni estructura:

- kiexster guarda la capa del port (src/, patches/, config/, scripts/, docs/, tests/, tools/) y aplica
  patches/*.patch, en el orden de scripts/compilar.ps1, sobre el commit de PS2Recomp fijado en
  scripts/common.ps1;
- aquí PS2Recomp/ está en el árbol, con esos parches ya aplicados y cambios propios encima.

Por eso no se puede hacer `git merge`. Para cada actualización entre el último punto sincronizado
(.kiexster-sync) y kiexster/<rama>:

1. Capa del port: cada archivo que cambió arriba se fusiona a tres bandas (git merge-file) con base = la
   versión del punto anterior, nuestra copia de trabajo y la versión nueva.
2. PS2Recomp: se reconstruye el árbol completo de kiexster en ambos puntos (commit fijado + cadena de
   parches) en una caché fuera del repositorio, y cada archivo que difiere se fusiona igual sobre
   PS2Recomp/.

No hace commits ni toca la historia: deja los cambios en la copia de trabajo (también funciona con
cambios sin confirmar) y lista los conflictos (marcas <<<<<<< en los archivos). .kiexster-sync solo se
actualiza si no hubo conflictos; tras resolverlos a mano, `--marcar` lo registra.

Uso: tools/sync/sincronizar_kiexster.py [--rama main] [--simular] [--marcar]
"""
from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

REMOTO = "kiexster"
URL = "https://github.com/KIexster/god-of-war-recomp.git"
RAIZ = Path(subprocess.check_output(["git", "rev-parse", "--show-toplevel"], text=True).strip())
ESTADO = RAIZ / ".kiexster-sync"
CACHE = Path(os.environ.get("KIEXSTER_SYNC_CACHE", Path.home() / ".cache" / "tobiichi-sync"))
# Archivos de la capa del port que este repositorio mantiene a su manera (no se fusionan).
PROPIOS = {".kiexster-sync", ".github/workflows/pruebas.yml"}  # su CI espera parches, no PS2Recomp/ en el árbol


def git(*args: str, cwd: Path = RAIZ, check: bool = True, binary: bool = False):
    r = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=not binary)
    if check and r.returncode != 0:
        err = r.stderr if not binary else r.stderr.decode(errors="replace")
        raise SystemExit(f"git {' '.join(args)}: {err.strip()}")
    return r


def show(commit: str, path: str, cwd: Path = RAIZ) -> bytes | None:
    r = git("show", f"{commit}:{path}", cwd=cwd, check=False, binary=True)
    return r.stdout if r.returncode == 0 else None


def fusionar(destino: Path, base: bytes | None, suyo: bytes | None, simular: bool, informe: dict, nombre: str):
    """Fusión a tres bandas de un archivo. Devuelve sin tocar nada en modo simulación."""
    nuestro = destino.read_bytes() if destino.exists() else None
    if suyo == base or suyo == nuestro:
        return  # arriba no cambió respecto a la base, o ya tenemos lo mismo
    if suyo is None:  # borrado arriba
        if nuestro == base:
            informe["borrados"].append(nombre)
            if not simular:
                destino.unlink()
        else:
            informe["conflictos"].append(f"{nombre} (borrado arriba, modificado aquí: se conserva)")
        return
    if nuestro is None:
        if base is None:
            informe["nuevos"].append(nombre)
            if not simular:
                destino.parent.mkdir(parents=True, exist_ok=True)
                destino.write_bytes(suyo)
        else:
            informe["conflictos"].append(f"{nombre} (modificado arriba, no existe aquí)")
        return
    if nuestro == base:  # solo cambió arriba
        informe["actualizados"].append(nombre)
        if not simular:
            destino.write_bytes(suyo)
        return
    with tempfile.TemporaryDirectory() as tmp:
        t = Path(tmp)
        (t / "nuestro").write_bytes(nuestro)
        (t / "base").write_bytes(base or b"")
        (t / "suyo").write_bytes(suyo)
        r = subprocess.run(["git", "merge-file", "-L", "tobiichi", "-L", "base", "-L", "kiexster",
                            str(t / "nuestro"), str(t / "base"), str(t / "suyo")], capture_output=True)
        if r.returncode < 0 or r.returncode > 127:
            informe["conflictos"].append(f"{nombre} (merge-file falló: {r.stderr.decode(errors='replace').strip()})")
            return
        if r.returncode == 0:
            informe["fusionados"].append(nombre)
        else:
            informe["conflictos"].append(f"{nombre} ({r.returncode} conflicto(s))")
        if not simular:
            destino.write_bytes((t / "nuestro").read_bytes())


def lista_parches(commit: str) -> list[str]:
    """Parches en el orden de scripts/compilar.ps1 de ese commit (misma regla que tools/ci/parches.py)."""
    texto = (show(commit, "scripts/compilar.ps1") or b"").decode("utf-8-sig")
    rutas = {m[1].lower(): m[2].replace("\\", "/") for m in re.finditer(
        r"^\s*\$(\w+)\s*=\s*Join-Path\s+\$RepoRoot\s+'(patches[\\/][^']+\.patch)'", texto, re.M | re.I)}
    orden = [m[1].lower() for m in re.finditer(
        r"^\s*Run\s+\$git\s+@\(\s*'apply'[^)]*\$(\w+)\s*\)", texto, re.M | re.I)]
    return [rutas[v] for v in orden if v in rutas]


def commit_fijado(commit: str) -> str:
    texto = (show(commit, "scripts/common.ps1") or b"").decode("utf-8-sig")
    m = re.search(r"\$PS2RecompCommit\s*=\s*'([0-9a-f]{40})'", texto)
    if not m:
        raise SystemExit(f"{commit}: no se encontró $PS2RecompCommit en scripts/common.ps1")
    return m[1]


def arbol_ps2recomp(commit: str) -> str:
    """Construye (o reutiliza) en la caché el árbol de PS2Recomp de kiexster en `commit`; devuelve su commit."""
    repo = CACHE / "PS2Recomp"
    if not (repo / ".git").exists():
        CACHE.mkdir(parents=True, exist_ok=True)
        subprocess.run(["git", "clone", "-q", "https://github.com/ran-j/PS2Recomp.git", str(repo)], check=True)
    etiqueta = f"kiexster-{commit[:12]}"
    if git("rev-parse", "-q", "--verify", f"refs/tags/{etiqueta}", cwd=repo, check=False).returncode == 0:
        return git("rev-parse", f"{etiqueta}^{{commit}}", cwd=repo).stdout.strip()
    fijado = commit_fijado(commit)
    if git("cat-file", "-e", f"{fijado}^{{commit}}", cwd=repo, check=False).returncode != 0:
        git("fetch", "-q", "origin", cwd=repo)
    # La caché es un clon propio: aquí sí se puede descartar el estado.
    git("checkout", "-qf", fijado, cwd=repo)
    git("clean", "-fdqx", cwd=repo)
    with tempfile.TemporaryDirectory() as tmp:
        for ruta in lista_parches(commit):
            datos = show(commit, ruta)
            if datos is None:
                raise SystemExit(f"{commit}: falta {ruta}")
            p = Path(tmp) / Path(ruta).name
            p.write_bytes(datos)
            r = git("apply", "--ignore-whitespace", str(p), cwd=repo, check=False)
            if r.returncode != 0:
                raise SystemExit(f"{commit}: {ruta} no se aplica: {r.stderr.strip()}")
    git("add", "-A", cwd=repo)
    git("-c", "user.name=sync", "-c", "user.email=sync@localhost", "commit", "-qm", f"kiexster {commit}",
        "--allow-empty", cwd=repo)
    git("tag", "-f", etiqueta, cwd=repo)
    return git("rev-parse", "HEAD", cwd=repo).stdout.strip()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rama", default="main")
    ap.add_argument("--simular", action="store_true", help="solo informa; no cambia ningún archivo")
    ap.add_argument("--marcar", action="store_true", help="registra kiexster/<rama> como sincronizado")
    a = ap.parse_args()

    if git("remote", "get-url", REMOTO, check=False).returncode != 0:
        git("remote", "add", REMOTO, URL)
    git("fetch", "-q", REMOTO)
    nuevo = git("rev-parse", f"{REMOTO}/{a.rama}").stdout.strip()
    if a.marcar:
        ESTADO.write_text(nuevo + "\n")
        print(f"Registrado {nuevo[:12]} como sincronizado")
        return 0
    if not ESTADO.exists():
        raise SystemExit(f"falta {ESTADO.name}: escribe ahí el commit de kiexster del que parte este repositorio")
    viejo = ESTADO.read_text().split()[0]
    if viejo == nuevo:
        print(f"Ya sincronizado con {REMOTO}/{a.rama} ({nuevo[:12]})")
        return 0
    print(f"Cambios de {REMOTO}/{a.rama} desde {viejo[:12]}:")
    print(git("log", "--oneline", "--no-merges", f"{viejo}..{nuevo}").stdout)

    informe = {k: [] for k in ("actualizados", "fusionados", "nuevos", "borrados", "conflictos")}
    # 1. Capa del port
    for linea in git("diff", "--name-only", "--no-renames", viejo, nuevo).stdout.splitlines():
        if linea in PROPIOS:
            continue
        fusionar(RAIZ / linea, show(viejo, linea), show(nuevo, linea), a.simular, informe, linea)
    # 2. PS2Recomp reconstruido
    repo = CACHE / "PS2Recomp"
    base_arbol = arbol_ps2recomp(viejo)
    nuevo_arbol = arbol_ps2recomp(nuevo)
    for linea in git("diff", "--name-only", "--no-renames", base_arbol, nuevo_arbol, cwd=repo).stdout.splitlines():
        fusionar(RAIZ / "PS2Recomp" / linea, show(base_arbol, linea, repo), show(nuevo_arbol, linea, repo),
                 a.simular, informe, "PS2Recomp/" + linea)

    for k, v in informe.items():
        print(f"{k}: {len(v)}")
        for x in v:
            print(f"   {x}")
    if a.simular:
        print("(simulación: no se cambió nada)")
    elif informe["conflictos"]:
        print("Resuelve los conflictos (marcas <<<<<<<) y ejecuta con --marcar.")
    else:
        ESTADO.write_text(nuevo + "\n")
        print(f"Sincronizado con {nuevo[:12]}")
    return 1 if informe["conflictos"] and not a.simular else 0


if __name__ == "__main__":
    sys.exit(main())
