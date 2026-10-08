# Rutas compartidas por los scripts de compilacion y ejecucion.
# Se carga con: . (Join-Path $PSScriptRoot 'common.ps1')

$RepoRoot = Split-Path -Parent $PSScriptRoot
$LogsDir  = Join-Path $RepoRoot 'logs'
New-Item -ItemType Directory -Force -Path $LogsDir | Out-Null

# Commit de PS2Recomp sobre el que se aplica patches/ps2recomp-runtime.patch
$PS2RecompUrl    = 'https://github.com/ran-j/PS2Recomp.git'
$PS2RecompCommit = 'c5a9d02573410a2085a4b4b831b0b68ba3515440'

# Carpeta de trabajo: ruta corta para evitar el limite de 260 caracteres de Windows.
# Se puede cambiar con la variable de entorno GOW_WORK.
function Get-GowWorkDir {
    if ($env:GOW_WORK) { return $env:GOW_WORK }
    return Join-Path (Split-Path -Qualifier $RepoRoot) 'gowport'
}

# Ejecutable del juego (SCUS_973.99). Orden de busqueda:
#   1. variable de entorno GOW_ELF
#   2. game\SCUS_973.99 dentro del repositorio
#   3. ..\GOW ISO extraida\SCUS_973.99 junto al repositorio
function Get-GowElf {
    $candidatos = @()
    if ($env:GOW_ELF) { $candidatos += $env:GOW_ELF }
    $candidatos += (Join-Path $RepoRoot 'game\SCUS_973.99')
    $candidatos += (Join-Path (Split-Path -Parent $RepoRoot) 'GOW ISO extraida\SCUS_973.99')
    foreach ($c in $candidatos) {
        if (Test-Path -LiteralPath $c) { return (Resolve-Path -LiteralPath $c).Path }
    }
    throw "No se encontro SCUS_973.99. Copialo en game\ o define GOW_ELF. Buscado en:`n  $($candidatos -join "`n  ")"
}
