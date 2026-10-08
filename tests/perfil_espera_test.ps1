param([Parameter(Mandatory)][string]$Perfilador,[Parameter(Mandatory)][string]$Fixture)
$ErrorActionPreference='Stop'
$testBase=[IO.Path]::GetFullPath([IO.Path]::GetTempPath())
$testDir=Join-Path $testBase ('gow-sample-'+[Guid]::NewGuid().ToString('N'))
$testProcess=$null
try {
    New-Item -ItemType Directory -Path $testDir | Out-Null
    $testProcess=Start-Process -FilePath (Resolve-Path -LiteralPath $Fixture).Path -WindowStyle Hidden -PassThru
    $testOut=Join-Path $testDir 'out.log';$testErr=Join-Path $testDir 'err.log'
    & $Perfilador $testProcess.Id 2 2 20 > $testOut 2> $testErr
    if($LASTEXITCODE -ne 0){throw 'Fallo el perfilador'}
    $testText=Get-Content -LiteralPath $testOut -Raw
    $testError=Get-Content -LiteralPath $testErr -Raw
    if($testError){throw ('Error de DbgHelp: '+$testError)}
    if($testText -notmatch 'marcos del ejecutable desde DLL:'){throw 'Las pilas recuperadas no se muestran'}
    $testSection=($testText -split 'marcos del ejecutable desde DLL:',2)[1]
    if($testSection -notmatch 'EsperaPerfilProcedural'){throw 'No se recupero el llamador procedural'}
    Write-Output 'Perfilador: una sesion DbgHelp y llamador propio recuperado desde DLL: OK'
}
finally {
    if($null -ne $testProcess -and -not $testProcess.HasExited){Stop-Process -Id $testProcess.Id -Force}
    $testResolved=[IO.Path]::GetFullPath($testDir)
    $testPrefix=$testBase.TrimEnd([IO.Path]::DirectorySeparatorChar,[IO.Path]::AltDirectorySeparatorChar)+[IO.Path]::DirectorySeparatorChar
    if(-not $testResolved.StartsWith($testPrefix,[StringComparison]::OrdinalIgnoreCase) -or
       (Split-Path -Leaf $testResolved) -notmatch '^gow-sample-[a-f0-9]{32}$'){throw 'Destino de limpieza no valido'}
    if(Test-Path -LiteralPath $testResolved){Remove-Item -LiteralPath $testResolved -Recurse -Force}
}
