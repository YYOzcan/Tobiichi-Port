# Prueba de arranque: pulsa Start y X en intervalos prefijados y guarda frames del GS.
# No certifica una partida jugable: hay que revisar las imagenes y el log.
param([int]$Segundos = 115, [switch]$DiagnosticoRutas, [switch]$DiagnosticoVif)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'common.ps1')
$previousTest = $env:GOW_PAD_TEST
$previousPaths = $env:GOW_PATH_DIAG
$previousVif = $env:GOW_VIF_DIAG
$previousRender = $env:GOW_RENDER_DIAG
try {
    $env:GOW_PAD_TEST = '1'
    if ($DiagnosticoRutas) { $env:GOW_PATH_DIAG = '1' }
    if ($DiagnosticoVif) { $env:GOW_VIF_DIAG = '1'; $env:GOW_RENDER_DIAG = '1' }
    Get-ChildItem -LiteralPath $LogsDir -Filter 'gow_pad_test_*.ppm' -File | Remove-Item -Force
    & (Join-Path $PSScriptRoot 'ejecutar.ps1') -Segundos $Segundos
    $build = Join-Path (Get-GowWorkDir) 'PS2Recomp\out\build'
    Get-ChildItem -LiteralPath $build -Recurse -Filter 'gow_pad_test_*.ppm' -File |
        Copy-Item -Destination $LogsDir -Force
    Write-Host "Revisa ejecutar.log, ejecutar_err.log y gow_pad_test_*.ppm en $LogsDir"
}
finally {
    $env:GOW_PAD_TEST = $previousTest
    $env:GOW_PATH_DIAG = $previousPaths
    $env:GOW_VIF_DIAG = $previousVif
    $env:GOW_RENDER_DIAG = $previousRender
}
