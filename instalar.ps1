# Tobiichi Port — instalador para Windows (PowerShell 5.1 o 7).
#
#   instalar.cmd [-Iso "C:\ruta\God of War.iso"] [-Herramientas] [-SinOptimizar] [-Optimizar] [-Segundos 240]
#
#   -Herramientas  instala antes Git, Python 3 y Visual Studio 2022 Build Tools (C++, CMake y Ninja) con winget.
#
# Pasos (cada uno se salta si ya está hecho):
#   1. Extrae el disco de la ISO en game\ (con su mapa de sectores, .disc_layout) y prepara game\IOP_MOD.
#   2. Compila el recompilador (ps2_recomp) y traduce SCUS_973.99 a C++ con config\recomp.template.toml.
#   3. Compila el juego (ps2EntryRunner.exe, MSVC + Ninja) y el lanzador (Qt 6; si no está, lo descarga con
#      aqtinstall en herramientas\qt) y copia sus bibliotecas (windeployqt).
#   4. Optimización: arranca el juego unos minutos con pulsaciones automáticas, guarda el microcódigo de VU1 y los
#      módulos del IOP que usa y recompila con ellos como código nativo. Solo la primera vez; -Optimizar lo repite,
#      -SinOptimizar lo omite.
#   5. Acceso directo en el escritorio y en el menú Inicio.
#
# Nada de lo que se genera a partir del juego (disco, código C++, microcódigo) sale de este ordenador.
param(
    [string]$Iso = '',
    [switch]$Herramientas,
    [switch]$SinOptimizar,
    [switch]$Optimizar,
    [int]$Segundos = 240,
    [int]$Jobs = 0
)
$ErrorActionPreference = 'Stop'
$Raiz = $PSScriptRoot
$Rec = Join-Path $Raiz 'PS2Recomp'
$Build = Join-Path $Rec 'build'
$Game = Join-Path $Raiz 'game'
$Vu1 = Join-Path $Raiz 'capturas_vu1'
# Procesos de compilación: uno por núcleo, pero como mucho uno por cada 2 GB de memoria (cada unidad de ~8 archivos
# generados usa 1-2 GB con /O2 /GL). -Jobs N lo fija.
if ($Jobs -le 0) {
    $memGb = [math]::Floor((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB)
    $Jobs = [math]::Max(1, [math]::Min([Environment]::ProcessorCount, [math]::Floor($memGb / 2)))
}
$QtVersion = '6.8.3'

function Paso([string]$t) { Write-Host ''; Write-Host "==> $t" -ForegroundColor Red }
function Aviso([string]$t) { Write-Host "[aviso] $t" -ForegroundColor Yellow }
function Falla([string]$t) { Write-Host "[error] $t" -ForegroundColor Red; Read-Host 'Pulsa Intro para salir'; exit 1 }
function Ejecutar([string]$exe, [string[]]$argumentos) {
    & $exe @argumentos
    if ($LASTEXITCODE -ne 0) { Falla "$exe terminó con el código $LASTEXITCODE" }
}
function Barra([string]$p) { return ($p -replace '\\', '/') }

# --- 0. Herramientas ---------------------------------------------------------------------------------------------
if ($Herramientas) {
    Paso 'Instalando Git, Python 3 y Visual Studio 2022 Build Tools (pide permiso de administrador; 15-30 min)'
    winget install -e --id Git.Git --accept-source-agreements --accept-package-agreements
    winget install -e --id Python.Python.3.12 --accept-source-agreements --accept-package-agreements
    winget install -e --id Microsoft.VisualStudio.2022.BuildTools --accept-source-agreements --accept-package-agreements `
        --override '--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended'
    $env:Path = [Environment]::GetEnvironmentVariable('Path', 'Machine') + ';' + [Environment]::GetEnvironmentVariable('Path', 'User')
}

Paso 'Comprobando herramientas'
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if (-not (Test-Path $vswhere)) { Falla 'No está Visual Studio (Build Tools). Ejecuta: instalar.cmd -Herramientas' }
$vs = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vs) { Falla 'Visual Studio no tiene el compilador de C++ (carga de trabajo "Desarrollo para el escritorio con C++").' }
$vcvars = Join-Path $vs 'VC\Auxiliary\Build\vcvars64.bat'
# Entorno de MSVC (cl, link, cmake y ninja de Visual Studio) en esta sesión de PowerShell. Un .cmd temporal evita los
# problemas de comillas de "cmd /c" con rutas con espacios.
$vcvarsCmd = Join-Path $env:TEMP 'tobiichi_vcvars.cmd'
Set-Content -LiteralPath $vcvarsCmd -Value "@call `"$vcvars`" >nul`r`n@set" -Encoding ASCII
cmd /c $vcvarsCmd | ForEach-Object {
    if ($_ -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($matches[1])" -Value $matches[2] }
}
foreach ($c in @('cl', 'cmake', 'ninja')) {
    if (-not (Get-Command $c -ErrorAction SilentlyContinue)) { Falla "No encuentro $c tras cargar vcvars64.bat ($vcvars)." }
}
$Py = $null
if (Get-Command py -ErrorAction SilentlyContinue) { $Py = @('py', '-3') }
elseif (Get-Command python -ErrorAction SilentlyContinue) { $Py = @('python') }
else { Falla 'No está Python 3. Ejecuta: instalar.cmd -Herramientas' }
function Python([string[]]$argumentos) {
    $exe = $Py[0]; $resto = @($Py | Select-Object -Skip 1) + $argumentos
    Ejecutar $exe $resto
}

# --- 1. Datos del juego -------------------------------------------------------------------------------------------
Paso 'Datos del juego (game\)'
New-Item -ItemType Directory -Force -Path $Game | Out-Null
if (-not (Test-Path (Join-Path $Game 'SCUS_973.99')) -or -not (Test-Path (Join-Path $Game '.disc_layout'))) {
    if (-not $Iso) {
        $c = Get-ChildItem -Path $Game, $Raiz -Filter *.iso -File -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($c) { $Iso = $c.FullName }
    }
    if (-not $Iso -or -not (Test-Path -LiteralPath $Iso)) {
        Falla 'No encuentro la ISO de God of War (USA, SCUS-97399). Ponla en game\ o usa: instalar.cmd -Iso "C:\ruta\God of War.iso"'
    }
    Write-Host "Extrayendo $Iso (unos 8 GB; el juego no necesita la ISO después)..."
    Python @('-I', (Join-Path $Raiz 'tools\waffle\iso_extract.py'), $Iso, $Game, '--layout')
}
$cnf = Join-Path $Game 'SYSTEM.CNF'
if (-not (Test-Path $cnf) -or -not (Select-String -Path $cnf -Pattern 'SCUS_973.99' -Quiet)) {
    Falla 'game\ no es God of War USA (SCUS-97399): SYSTEM.CNF no arranca SCUS_973.99.'
}
$iopMod = Join-Path $Game 'IOP_MOD'
New-Item -ItemType Directory -Force -Path $iopMod | Out-Null
Get-ChildItem -Path $Game -Filter *.IRX -File | ForEach-Object { Copy-Item $_.FullName (Join-Path $iopMod $_.Name) -Force }
Write-Host 'Listo: módulos del IOP en game\IOP_MOD.'

# --- 2. Recompilador y código del juego ---------------------------------------------------------------------------
function Configurar {
    $extra = @()
    if (Get-ChildItem -Path $Vu1 -Filter *.bin -ErrorAction SilentlyContinue | Select-Object -First 1) {
        $extra += "-DPS2X_VU1_MICROCODE_DIR=$(Barra $Vu1)"
        $extra += "-DPS2X_VU1_GENERATOR_SOURCE=$(Barra (Join-Path $Raiz 'tools\vu1\generar_vu1.cpp'))"
        $extra += "-DPS2X_VU1N_GEN_OVERRIDE=$(Barra (Join-Path $Raiz 'tools\vu1\vu1n_gen.py'))"
    }
    Ejecutar 'cmake' (@('-S', $Rec, '-B', $Build, '-G', 'Ninja', '-DCMAKE_BUILD_TYPE=Release',
        '-DPS2X_ENABLE_RUNTIME_LOGS=OFF', '-DPS2X_ENABLE_AGRESSIVE_LOGS=OFF', '-DPS2X_ENABLE_IOP_RPC_TRACE=OFF',
        '-DPS2X_BUILD_STUDIO=OFF', '-DPS2X_BUILD_ANALYZER=OFF', '-DPS2X_BUILD_TEST=OFF', '-DPS2X_SHOW_WINDOWS_CONSOLE=OFF',
        '-DPS2X_RUNNER_UNITY_BUILD_BATCH_SIZE=8') + $extra)
}
Paso 'Configurando la compilación (la primera vez descarga raylib, imgui y toml11)'
Configurar
Paso 'Compilando el recompilador'
Ejecutar 'ninja' @('-C', $Build, "-j$Jobs", 'ps2_recomp')

Paso 'Traduciendo SCUS_973.99 a C++'
# ps2_recomp no abre rutas con caracteres no ASCII: si la carpeta del repositorio los tiene, se trabaja en C:\TobiichiGen.
$Gen = Join-Path $Raiz 'build-gen'
if ($Gen -match '[^\x20-\x7E]') { $Gen = Join-Path $env:SystemDrive 'TobiichiGen' }
$out = Join-Path $Gen 'out'
New-Item -ItemType Directory -Force -Path $out | Out-Null
Copy-Item (Join-Path $Game 'SCUS_973.99') (Join-Path $Gen 'SCUS_973.99') -Force
Copy-Item (Join-Path $Raiz 'config\funcmap.csv') (Join-Path $Gen 'funcmap.csv') -Force
(Get-Content -LiteralPath (Join-Path $Raiz 'config\recomp.template.toml') -Raw) `
    -replace '@ELF@', (Barra (Join-Path $Gen 'SCUS_973.99')) `
    -replace '@MAP@', (Barra (Join-Path $Gen 'funcmap.csv')) `
    -replace '@OUT@', ((Barra $out) + '/') | Set-Content -LiteralPath (Join-Path $Gen 'recomp.toml') -Encoding ASCII
$recompExe = Join-Path $Build 'ps2xRecomp\ps2_recomp.exe'
$recompLog = Join-Path $Gen 'recomp.log'
& $recompExe (Join-Path $Gen 'recomp.toml') *> $recompLog
if ($LASTEXITCODE -ne 0) { Get-Content $recompLog -Tail 20; Falla 'ps2_recomp falló (ver recomp.log)' }
$runner = Join-Path $Rec 'ps2xRuntime\src\runner'
New-Item -ItemType Directory -Force -Path $runner | Out-Null
function CopiarSiCambia([string]$origen, [string]$destino) {
    # Solo lo que cambió: la recompilación sigue siendo incremental.
    if ((Test-Path -LiteralPath $destino) -and
        (Get-FileHash -LiteralPath $origen).Hash -eq (Get-FileHash -LiteralPath $destino).Hash) { return }
    Copy-Item -LiteralPath $origen -Destination $destino -Force
}
Get-ChildItem -Path $out -Filter *.cpp -File | ForEach-Object { CopiarSiCambia $_.FullName (Join-Path $runner $_.Name) }
Get-ChildItem -Path $out -Filter *.h -File | ForEach-Object { CopiarSiCambia $_.FullName (Join-Path $Rec "ps2xRuntime\include\$($_.Name)") }
foreach ($f in @('gow_overrides.cpp', 'gow_pad2_packet.h', 'gow_gs_replay.h')) {
    CopiarSiCambia (Join-Path $Raiz "src\$f") (Join-Path $runner $f)
}

# --- 3. Juego y lanzador -------------------------------------------------------------------------------------------
function CompilarJuego {
    Paso 'Compilando el juego (la primera vez tarda: ~6.400 archivos)'
    Ejecutar 'ninja' @('-C', $Build, "-j$Jobs", 'ps2EntryRunner')
}
Configurar
CompilarJuego
$Juego = Join-Path $Build 'ps2xRuntime\ps2EntryRunner.exe'

Paso 'Compilando el lanzador (Qt 6)'
$qt = $null
if ($env:Qt6_DIR) { $qt = Split-Path (Split-Path (Split-Path $env:Qt6_DIR)) }
if (-not $qt) {
    $c = Get-ChildItem -Path 'C:\Qt', (Join-Path $Raiz 'herramientas\qt') -Directory -Filter '6.*' -ErrorAction SilentlyContinue |
        ForEach-Object { Get-ChildItem $_.FullName -Directory -Filter 'msvc*_64' } | Select-Object -First 1
    if ($c) { $qt = $c.FullName }
}
if (-not $qt) {
    Write-Host "Descargando Qt $QtVersion (aqtinstall) en herramientas\qt..."
    Python @('-m', 'pip', 'install', '--user', '--upgrade', 'aqtinstall')
    Python @('-m', 'aqt', 'install-qt', 'windows', 'desktop', $QtVersion, 'win64_msvc2022_64', '-O', (Join-Path $Raiz 'herramientas\qt'))
    $qt = Join-Path $Raiz "herramientas\qt\$QtVersion\msvc2022_64"
}
$LauncherBuild = Join-Path $Raiz 'launcher\build'
Ejecutar 'cmake' @('-S', (Join-Path $Raiz 'launcher'), '-B', $LauncherBuild, '-G', 'Ninja', '-DCMAKE_BUILD_TYPE=Release', "-DCMAKE_PREFIX_PATH=$(Barra $qt)")
Ejecutar 'ninja' @('-C', $LauncherBuild, "-j$Jobs")
$Lanzador = Join-Path $LauncherBuild 'tobiichi-launcher.exe'
Ejecutar (Join-Path $qt 'bin\windeployqt.exe') @('--release', '--qmldir', (Join-Path $Raiz 'launcher\qml'), $Lanzador)

# --- 4. Optimización (VU1 e IOP nativos) -----------------------------------------------------------------------------
$hayVu1 = [bool](Get-ChildItem -Path $Vu1 -Filter *.bin -ErrorAction SilentlyContinue | Select-Object -First 1)
if ($Optimizar -or (-not $SinOptimizar -and -not $hayVu1)) {
    Paso "Optimización: el juego se abre $Segundos s solo (no toques el teclado); se guarda el código de VU1 y del IOP"
    $mods = Join-Path $Gen 'iop_mods'
    New-Item -ItemType Directory -Force -Path $Vu1, $mods | Out-Null
    $vars = @{
        GOW_VU1_CAPTURA = $Vu1; PS2X_IOP_DUMP_MODULES = $mods; GOW_SKIP_FMV = '1'; GOW_PAD_TEST = '1';
        GOW_PAD_TEST_NO_CAPTURE = '1'; GOW_MC0 = (Join-Path $Gen 'optimizar.ps2'); PS2X_GS_WORKER = '1'; GOW_GS_FINISH_ASINCRONO = '1';
        GOW_PAD_GUION = '5:start,12:x,20:x,28:x,40:cuadrado,41:cuadrado,42:cuadrado,44:triangulo,48:lup*3,52:x,55:cuadrado,56:triangulo,60:circulo,64:r1,70:lleft*2,74:cuadrado,76:cuadrado,80:triangulo,90:lup*4,96:x,100:cuadrado,104:l1,110:lright*2,120:cuadrado,125:triangulo,140:lup*5,150:cuadrado,160:triangulo,180:lup*5,200:cuadrado'
    }
    foreach ($k in $vars.Keys) { Set-Item -Path "env:$k" -Value $vars[$k] }
    $p = Start-Process -FilePath $Juego -ArgumentList "`"$(Join-Path $Game 'SCUS_973.99')`"" -WorkingDirectory $Rec -PassThru
    if (-not $p.WaitForExit($Segundos * 1000)) { Stop-Process -Id $p.Id -Force }
    foreach ($k in $vars.Keys) { Remove-Item -Path "env:$k" -ErrorAction SilentlyContinue }
    $nVu1 = (Get-ChildItem -Path $Vu1 -Filter *.bin -ErrorAction SilentlyContinue).Count
    $nIop = (Get-ChildItem -Path $mods -Filter *.bin -ErrorAction SilentlyContinue).Count
    Write-Host "VU1: $nVu1 micromemorias; IOP: $nIop módulos."
    if ($nIop -gt 0) { Python @('-I', (Join-Path $Raiz 'tools\iop\iopn_gen.py'), $mods, (Join-Path $Rec 'ps2xIOP\src\native')) }
    Configurar
    CompilarJuego
}

# --- 5. Accesos directos --------------------------------------------------------------------------------------------
Paso 'Accesos directos'
$shell = New-Object -ComObject WScript.Shell
foreach ($carpeta in @([Environment]::GetFolderPath('Desktop'), [Environment]::GetFolderPath('Programs'))) {
    $lnk = $shell.CreateShortcut((Join-Path $carpeta 'God Of War - Tobiichi Port.lnk'))
    $lnk.TargetPath = $Lanzador
    $lnk.WorkingDirectory = $LauncherBuild
    $lnk.Save()
}

Paso 'Listo'
Write-Host "  Lanzador: $Lanzador (acceso directo en el escritorio y en el menú Inicio)"
Write-Host '  Más código nativo tras jugar zonas nuevas: instalar.cmd -Optimizar'
Read-Host 'Pulsa Intro para salir'
