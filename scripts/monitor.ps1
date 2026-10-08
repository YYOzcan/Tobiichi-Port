# Registra cada 30 s el estado de los procesos de compilacion en logs\monitor.log
# Se puede cerrar en cualquier momento; no afecta a la compilacion.
$log = Join-Path (Split-Path -Parent $PSScriptRoot) 'logs\monitor.log'
New-Item -ItemType Directory -Force -Path (Split-Path $log) | Out-Null
$cores = [Environment]::ProcessorCount
$prev = @{}
while ($true) {
    $os = Get-CimInstance Win32_OperatingSystem
    $libre = [math]::Round($os.FreePhysicalMemory / 1MB, 1)
    $procs = Get-Process -Name link, cl, ninja, cmake -ErrorAction SilentlyContinue
    $lineas = @()
    foreach ($p in $procs) {
        $cpu = $p.TotalProcessorTime.TotalSeconds
        $uso = if ($prev.ContainsKey($p.Id)) { [math]::Round((($cpu - $prev[$p.Id]) / 30) * 100 / $cores, 1) } else { '?' }
        $prev[$p.Id] = $cpu
        $lineas += ('{0}(pid {1}): CPU {2}%  RAM {3} GB  tiempo CPU {4} min' -f $p.Name, $p.Id, $uso,
                    [math]::Round($p.WorkingSet64 / 1GB, 2), [math]::Round($cpu / 60, 1))
    }
    if (-not $lineas) { $lineas = @('ningun proceso de compilacion activo') }
    $txt = "[{0}] RAM libre: {1} GB | {2}" -f (Get-Date -Format 'HH:mm:ss'), $libre, ($lineas -join ' | ')
    Write-Host $txt
    Add-Content -LiteralPath $log -Value $txt
    Start-Sleep -Seconds 30
}
