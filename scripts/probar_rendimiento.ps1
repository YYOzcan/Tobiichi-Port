# Perfil reproducible: cuenta vid::Flip y presentaciones, sin volcados ni capturas del juego.
param(
    [int]$Segundos = 150,
    [switch]$SoloCuadros,
    [ValidateSet('cpu', 'cpu-hilo', 'opengl')][string]$Renderer = 'cpu',
    [ValidatePattern('^[a-zA-Z0-9_-]+$')][string]$Etiqueta = 'limpio'
)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'common.ps1')
$clear = @('GOW_VIF_DIAG', 'GOW_RENDER_DIAG', 'GOW_EE_PRIM_DIAG', 'GOW_MODEL_DIAG', 'GOW_PATH_DIAG', 'GOW_ANM_DIAG', 'GOW_CLIP_TRACE',
           'GOW_GEOM_DIAG', 'GOW_GEOMETRY_DIAG', 'GOW_SIO2_DIAG', 'GOW_GS_GPU_TEST', 'GOW_VU1_BUDGET_DIAG',
           'GOW_REPLAY_TRACE', 'GOW_REPLAY_STEM', 'GOW_GS_REPLAY_TRACE', 'GOW_GS_REPLAY_AFTER',
           'GOW_GS_REPLAY_SECONDS', 'GOW_GS_REPLAY_TEXFLUSH', 'PS2X_GS_DIAG', 'PS2X_GS_TRACE_TBP', 'PS2X_GS_TRACE_AFTER',
           'PS2X_GS_DUMP_SECONDS', 'PS2X_GS_DISCARD_DRAWS', 'PS2X_GS_GPU_STATS', 'PS2X_GS_GPU_PROF',
           'PS2X_GS_HW_LOG', 'PS2X_FRAME_HASH', 'PS2X_IOP_PC_EVERY', 'PS2X_IOP_TRACE', 'PS2X_IOP_TRACE_EVERY',
           'PS2X_IOP_TRACE_NOCLIB', 'PS2X_IOP_TRACE_FROM', 'PS2X_IOP_TRACE_DMA')
$set = @{
    GOW_PERF_DIAG = $(if ($SoloCuadros) { 'frames' } else { '1' })
    GOW_PERF_FRAME_PC = '0x001837B8' # vid::Flip de SCUS-97399; sus reanudaciones no cuentan.
    GOW_PAD_TEST = '1'
    GOW_PAD_TEST_NO_CAPTURE = '1'
    GOW_SKIP_FMV = '1'
    GOW_FAST_BOOT = '1'
    PS2X_GS_GPU = $(if ($Renderer -eq 'opengl') { '1' } else { '0' })
    PS2X_GS_THREAD = $(if ($Renderer -eq 'cpu-hilo') { '1' } else { '0' })
}
$previous = @{}
foreach ($name in @($clear) + @($set.Keys)) { $previous[$name] = [Environment]::GetEnvironmentVariable($name, 'Process') }
try {
    # GOW-Port: otra compilacion o partida invalida la comparacion de FPS desde el inicio.
    $busy = @(Get-Process -Name cl,link,clang,clang-cl,cc1plus,ninja,cmake,ps2EntryRunner -ErrorAction SilentlyContinue)
    if ($busy.Count -gt 0) {
        throw ('Perfil cancelado: hay una compilacion u otra partida activa (' +
               (($busy.ProcessName | Sort-Object -Unique) -join ', ') + '). Repetir cuando termine.')
    }
    # En PowerShell 7.5/.NET 9, pasar $null a SetEnvironmentVariable deja un valor vacío.
    # getenv() aún lo detecta: eliminar la entrada evita activar diagnósticos por presencia.
    foreach ($name in $clear) { Remove-Item -LiteralPath "Env:$name" -ErrorAction SilentlyContinue }
    foreach ($name in $set.Keys) { [Environment]::SetEnvironmentVariable($name, $set[$name], 'Process') }
    Write-Host "Renderer: $Renderer"
    $destination = Join-Path $LogsDir "perf_$Etiqueta.log"
    try {
        & (Join-Path $PSScriptRoot 'ejecutar.ps1') -Segundos $Segundos -VigilarRendimiento
    }
    catch {
        # GOW-Port: conservar el registro marcado, sin anunciarlo como perfil valido.
        $failedLog = Join-Path $LogsDir 'ejecutar_err.log'
        if ((Test-Path -LiteralPath $failedLog) -and
            (Select-String -LiteralPath $failedLog -SimpleMatch '[gow-perf:invalid]' -Quiet)) {
            Copy-Item -LiteralPath $failedLog -Destination $destination -Force
        }
        throw
    }
    Copy-Item -LiteralPath (Join-Path $LogsDir 'ejecutar_err.log') -Destination $destination -Force
    Write-Host "Perfil guardado en $destination"
}
finally {
    foreach ($name in $previous.Keys) {
        if ($null -eq $previous[$name]) { Remove-Item -LiteralPath "Env:$name" -ErrorAction SilentlyContinue }
        else { [Environment]::SetEnvironmentVariable($name, $previous[$name], 'Process') }
    }
}
