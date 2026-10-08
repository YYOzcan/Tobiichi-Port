# GOW-Port: ejecutar los scripts reales con procesos simulados; nunca arrancar ni detener el juego.
$ErrorActionPreference = 'Stop'
$testRepo = Split-Path -Parent $PSScriptRoot
$testTempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath())
$testRoot = Join-Path $testTempRoot ('gow-perf-guard-' + [Guid]::NewGuid().ToString('N'))
$testPrevious = @{}
foreach ($name in @('GOW_WORK','GOW_ELF','GOW_PERF_DIAG','PS2X_GS_GPU_PROF')) {
    $testPrevious[$name] = [Environment]::GetEnvironmentVariable($name,'Process')
}
function Assert-Guard([bool]$condition,[string]$message) {
    if (-not $condition) { throw $message }
}

# Los mocks solo sustituyen procesos. Rutas, redirecciones, scripts y restauracion del entorno son reales.
function global:Get-Process {
    param([string[]]$Name,[string]$ErrorAction)
    $global:GowPerfGuardFixture.snapshots++
    if ($global:GowPerfGuardFixture.scenario -eq 'startup') {
        return [pscustomobject]@{Id=777;ProcessName='cl'}
    }
    if ($global:GowPerfGuardFixture.snapshots -eq 1) { return }
    $global:GowPerfGuardFixture.process
    if ($global:GowPerfGuardFixture.snapshots -ge 3 -and $global:GowPerfGuardFixture.scenario -ne 'quiet') {
        [pscustomobject]@{Id=777;ProcessName=$global:GowPerfGuardFixture.scenario}
    }
}
function global:Start-Process {
    param($FilePath,$ArgumentList,$WorkingDirectory,$RedirectStandardOutput,$RedirectStandardError,
          [switch]$PassThru,$WindowStyle)
    $global:GowPerfGuardFixture.starts++
    Set-Content -LiteralPath $RedirectStandardOutput -Value 'proceso simulado'
    Set-Content -LiteralPath $RedirectStandardError -Value '[gow-perf] t=20.00 window=5.00 guest_flip_hz=10.00'
    $global:GowPerfGuardFixture.process
}
function global:Stop-Process {
    param([int]$Id,[switch]$Force,[string]$ErrorAction)
    Assert-Guard ($Id -eq 4242) 'Se intento detener un proceso ajeno'
    $global:GowPerfGuardFixture.stopped.Add($Id)
    $global:GowPerfGuardFixture.process.HasExited = $true
}
try {
    New-Item -ItemType Directory -Path (Join-Path $testRoot 'scripts') -Force | Out-Null
    foreach ($script in @('common.ps1','ejecutar.ps1','probar_rendimiento.ps1')) {
        Copy-Item -LiteralPath (Join-Path $testRepo "scripts/$script") -Destination (Join-Path $testRoot 'scripts')
    }
    $env:GOW_WORK = Join-Path $testRoot 'work'
    $env:GOW_ELF = Join-Path $testRoot 'SCUS_973.99'
    $env:GOW_PERF_DIAG = 'valor_previo'
    $env:PS2X_GS_GPU_PROF = 'diagnostico_previo'
    New-Item -ItemType Directory -Path (Join-Path $env:GOW_WORK 'PS2Recomp/out/build') -Force | Out-Null
    New-Item -ItemType File -Path $env:GOW_ELF | Out-Null
    New-Item -ItemType File -Path (Join-Path $env:GOW_WORK 'PS2Recomp/out/build/ps2EntryRunner.exe') | Out-Null
    foreach ($scenario in @('startup','cl','ps2EntryRunner','quiet')) {
        $process = [pscustomobject]@{Id=4242;ProcessName='ps2EntryRunner';HasExited=$false;waits=0}
        $process | Add-Member -MemberType ScriptMethod -Name WaitForExit -Value {
            param($milliseconds)
            if ($null -eq $milliseconds) { $this.HasExited=$true;return }
            $this.waits++
            if ($this.waits -ge 2) { $this.HasExited=$true;return $true }
            return $false
        }
        $global:GowPerfGuardFixture = @{
            scenario=$scenario;process=$process;starts=0;snapshots=0
            stopped=[Collections.Generic.List[int]]::new()
        }
        $caught = $null
        try { & (Join-Path $testRoot 'scripts/probar_rendimiento.ps1') -Segundos 5 -Etiqueta $scenario }
        catch { $caught = $_ }
        Assert-Guard ($env:GOW_PERF_DIAG -eq 'valor_previo' -and $env:PS2X_GS_GPU_PROF -eq 'diagnostico_previo') 'No se restauro el entorno'
        $destination = Join-Path $testRoot "logs/perf_$scenario.log"
        if ($scenario -eq 'startup') {
            Assert-Guard ($null -ne $caught -and $global:GowPerfGuardFixture.starts -eq 0) 'No se rechazo la compilacion previa'
            Assert-Guard (-not (Test-Path -LiteralPath $destination)) 'Se guardo un perfil que no empezo'
        }
        elseif ($scenario -eq 'quiet') {
            Assert-Guard ($null -eq $caught -and $global:GowPerfGuardFixture.starts -eq 1) 'El PID propio invalido la pasada limpia'
            Assert-Guard ($global:GowPerfGuardFixture.stopped.Count -eq 0) 'Se detuvo una partida ya terminada'
            Assert-Guard ((Get-Content -LiteralPath $destination -Raw) -notmatch '\[gow-perf:invalid\]') 'Se marco la pasada limpia'
        }
        else {
            Assert-Guard ($null -ne $caught -and $global:GowPerfGuardFixture.starts -eq 1) 'No se rechazo la carga que empezo durante el perfil'
            Assert-Guard ($global:GowPerfGuardFixture.stopped.Count -eq 1 -and $global:GowPerfGuardFixture.stopped[0] -eq 4242) 'No se detuvo exclusivamente la instancia propia'
            Assert-Guard ((Get-Content -LiteralPath $destination -Raw) -match '\[gow-perf:invalid\]') 'Falta la marca en el perfil conservado'
        }
        Write-Host "Control de vigilancia: $scenario OK"
    }
}
finally {
    foreach ($name in $testPrevious.Keys) {
        if ($null -eq $testPrevious[$name]) { Remove-Item -LiteralPath "Env:$name" -ErrorAction SilentlyContinue }
        else { [Environment]::SetEnvironmentVariable($name,$testPrevious[$name],'Process') }
    }
    Remove-Item Function:Get-Process,Function:Start-Process,Function:Stop-Process -ErrorAction SilentlyContinue
    Remove-Variable GowPerfGuardFixture -Scope Global -ErrorAction SilentlyContinue
    # Verificar el destino absoluto antes de limpiar unicamente el directorio temporal creado arriba.
    $resolved = [IO.Path]::GetFullPath($testRoot)
    $prefix = $testTempRoot.TrimEnd([IO.Path]::DirectorySeparatorChar,[IO.Path]::AltDirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar
    if (-not $resolved.StartsWith($prefix,[StringComparison]::OrdinalIgnoreCase) -or
        (Split-Path -Leaf $resolved) -notmatch '^gow-perf-guard-[a-f0-9]{32}$') { throw 'Destino de limpieza no valido' }
    if (Test-Path -LiteralPath $resolved) { Remove-Item -LiteralPath $resolved -Recurse -Force }
}
