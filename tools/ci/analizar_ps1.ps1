# Analiza sintacticamente todos los .ps1 del repositorio con el parser de PowerShell (no los ejecuta).
# Uso: pwsh -NoProfile -File tools/ci/analizar_ps1.ps1
$raiz = Resolve-Path (Join-Path $PSScriptRoot '..\..')
$fallos = 0
$archivos = Get-ChildItem -Path $raiz -Recurse -Filter *.ps1 -File | Where-Object { $_.FullName -notmatch '[\\/]\.git[\\/]' }
foreach ($archivo in $archivos) {
    $tokens = $null
    $errores = $null
    [System.Management.Automation.Language.Parser]::ParseFile($archivo.FullName, [ref]$tokens, [ref]$errores) | Out-Null
    $relativo = [System.IO.Path]::GetRelativePath($raiz, $archivo.FullName)
    if ($errores.Count -gt 0) {
        foreach ($e in $errores) {
            Write-Host ("::error file={0},line={1}::{2}" -f $relativo, $e.Extent.StartLineNumber, $e.Message)
        }
        $fallos += $errores.Count
    } else {
        Write-Host "ok  $relativo"
    }
}
Write-Host ("{0} scripts, {1} errores" -f $archivos.Count, $fallos)
if ($fallos -gt 0) { exit 1 }
