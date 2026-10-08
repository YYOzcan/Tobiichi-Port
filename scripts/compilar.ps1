# Clona PS2Recomp, recompila SCUS_973.99 a C++ y compila el ejecutable para PC.
# Lo llama scripts\2_compilar.cmd, que antes carga el entorno de Visual Studio (vcvars64).
param([switch]$Trazas)
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'common.ps1')

$elf  = Get-GowElf
$work = Get-GowWorkDir
New-Item -ItemType Directory -Force -Path $work | Out-Null
$rec  = Join-Path $work 'PS2Recomp'
$gen  = Join-Path $work 'generado'
$bld  = Join-Path $rec 'out\build'

$template  = Join-Path $RepoRoot 'config\recomp.template.toml'
$funcmap   = Join-Path $RepoRoot 'config\funcmap.csv'
$patch     = Join-Path $RepoRoot 'patches\ps2recomp-runtime.patch'
$checkpointPatch = Join-Path $RepoRoot 'patches\ps2recomp-checkpoint.patch'
$xgkickPatch = Join-Path $RepoRoot 'patches\ps2recomp-xgkick.patch'
$vifUnpackPatch = Join-Path $RepoRoot 'patches\ps2recomp-vif-unpack.patch'
$vifDiagnosticPatch = Join-Path $RepoRoot 'patches\ps2recomp-vif-diagnostic.patch'
$heapPatch = Join-Path $RepoRoot 'patches\ps2recomp-heap.patch'
$vuJumpPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu-jump.patch'
$vuEfuPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu-efu.patch'
$mpegNodataPatch = Join-Path $RepoRoot 'patches\ps2recomp-mpeg-nodata.patch'
$spu2Patch = Join-Path $RepoRoot 'patches\ps2recomp-spu2.patch'
$fpuRootsPatch = Join-Path $RepoRoot 'patches\ps2recomp-fpu-roots.patch'
$spu2OutputPatch = Join-Path $RepoRoot 'patches\ps2recomp-spu2-output.patch'
$sio2Patch = Join-Path $RepoRoot 'patches\ps2recomp-sio2.patch'
$perfPatch = Join-Path $RepoRoot 'patches\ps2recomp-perf.patch'
$gsOpenGlPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-opengl.patch'
$eeFixesPatch = Join-Path $RepoRoot 'patches\ps2recomp-ee-fixes.patch'
$gsPresentationPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-presentation.patch'
$vifDirectPatch = Join-Path $RepoRoot 'patches\ps2recomp-vif-direct.patch'
$vifDirectFragmentsPatch = Join-Path $RepoRoot 'patches\ps2recomp-vif-direct-fragments.patch'
$gifOrderPatch = Join-Path $RepoRoot 'patches\ps2recomp-gif-order.patch'
$gifTagSemanticsPatch = Join-Path $RepoRoot 'patches\ps2recomp-gif-tag-semantics.patch'
$gifStreamPatch = Join-Path $RepoRoot 'patches\ps2recomp-gif-stream.patch'
$gifImageOrderPatch = Join-Path $RepoRoot 'patches\ps2recomp-gif-image-order.patch'
$gifImage2Patch = Join-Path $RepoRoot 'patches\ps2recomp-gif-image2.patch'
$gifNativeTagPatch = Join-Path $RepoRoot 'patches\ps2recomp-gif-native-tag.patch'
$gsImageFragmentsPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-image-fragments.patch'
$gsTriangleSamplingPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-triangle-sampling.patch'
$gsSpriteSamplingPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-sprite-sampling.patch'
$iopFastPatch = Join-Path $RepoRoot 'patches\ps2recomp-iop-fast.patch'
$vu0MacroPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu0-macro.patch'
$mmiPatch = Join-Path $RepoRoot 'patches\ps2recomp-mmi.patch'
$gsTriangleConstantsPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-triangle-constants.patch'
$gsTriangleTexcoordsPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-triangle-texcoords.patch'
$vu1EfuOpcodesPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-efu-opcodes.patch'
$gsCpuStatePatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-cpu-state.patch'
$gsCpuRoundingPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-cpu-rounding.patch'
$getenvHotPatch = Join-Path $RepoRoot 'patches\ps2recomp-getenv-hot.patch'
$vu1PerfPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-perf.patch'
$sprChainPatch = Join-Path $RepoRoot 'patches\ps2recomp-spr-chain.patch'
$mpegCreatePatch = Join-Path $RepoRoot 'patches\ps2recomp-mpeg-create.patch'
$audioPcmPatch = Join-Path $RepoRoot 'patches\ps2recomp-audio-pcm.patch'
$iopSoundPatch = Join-Path $RepoRoot 'patches\ps2recomp-iop-sound.patch'
$memcardPatch = Join-Path $RepoRoot 'patches\ps2recomp-memcard.patch'
$gsTrianglePrecisionPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-triangle-precision.patch'
$gsPackedDepthPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-packed-depth.patch'
$gsBilinearPrecisionPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-bilinear-precision.patch'
$gsNearestStqPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-nearest-stq.patch'
$gsFeedbackSnapshotPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-feedback-snapshot.patch'
$gsBilinearStqPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-bilinear-stq.patch'
$gsRegionPagesPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-region-pages.patch'
$gsTargetAliasPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-target-alias.patch'
$vu1DirectPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-direct.patch'
$vu1CompiledPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-compiled.patch'
$vu1BudgetDiagPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-budget-diag.patch'
$vu1StickyPreservePatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-sticky-preserve.patch'
$vu1BlocksPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-blocks.patch'
$vu1RunnerPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-runner.patch'
$iopSchedulerPatch = Join-Path $RepoRoot 'patches\ps2recomp-iop-scheduler.patch'
$vif1UnpackFastPatch = Join-Path $RepoRoot 'patches\ps2recomp-vif1-unpack-fast.patch'
$eeTimersFastPatch = Join-Path $RepoRoot 'patches\ps2recomp-ee-timers-fast.patch'
$vu1SimdPatch = Join-Path $RepoRoot 'patches\ps2recomp-vu1-simd.patch'
$gsCoordinateAliasPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-coordinate-alias.patch'
$gsStqHardwareTestPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-stq-hardware-test.patch'
$gsFinishAsyncPatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-finish-async.patch'
$gsHardwareProfilePatch = Join-Path $RepoRoot 'patches\ps2recomp-gs-hardware-profile.patch'
$overrides = Join-Path $RepoRoot 'src\gow_overrides.cpp'

$git = 'git'
if (-not (Get-Command git -ErrorAction SilentlyContinue)) { $git = Join-Path $env:ProgramFiles 'Git\cmd\git.exe' }

function Run([string]$exe, [string[]]$a) {
    Write-Host ">> $exe $($a -join ' ')"
    & $exe @a
    if ($LASTEXITCODE -ne 0) { throw "Fallo ($LASTEXITCODE): $exe" }
}
function Paso([string]$t) { Write-Host ''; Write-Host "==== [$(Get-Date -Format HH:mm:ss)] $t ====" }

Paso 'Herramientas'
Write-Host "ELF:     $elf"
Write-Host "Trabajo: $work"
Run $git @('--version'); Run 'cmake' @('--version'); Run 'ninja' @('--version')

if (-not (Test-Path -LiteralPath (Join-Path $rec '.git'))) {
    Paso 'Clonando PS2Recomp'
    Run $git @('clone', $PS2RecompUrl, $rec)
}
Push-Location $rec
Run $git @('fetch', 'origin', $PS2RecompCommit)
Run $git @('checkout', '-f', $PS2RecompCommit)
Run $git @('submodule', 'update', '--init', '--recursive')
# checkout -f no retira los archivos nuevos que crearon los parches en una compilacion anterior, y git apply
# fallaria al volver a crearlos. Se borran todos los que crea algun parche de patches\ ("new file mode").
foreach ($patchFile in Get-ChildItem -LiteralPath (Join-Path $RepoRoot 'patches') -Filter '*.patch' -File) {
    $created = $null
    foreach ($line in Get-Content -LiteralPath $patchFile.FullName) {
        if ($line -match '^diff --git a/(\S+) b/') { $created = $Matches[1] }
        elseif ($created -and $line -like 'new file mode*') {
            $extra = Join-Path $rec ($created -replace '/', '\')
            if (Test-Path -LiteralPath $extra) { Remove-Item -LiteralPath $extra -Force }
        }
    }
}
Run $git @('apply', '--ignore-whitespace', '--verbose', $patch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $checkpointPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $xgkickPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vifUnpackPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vifDiagnosticPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $heapPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vuJumpPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vuEfuPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $mpegNodataPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $spu2Patch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $fpuRootsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $spu2OutputPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $sio2Patch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $perfPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsOpenGlPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $eeFixesPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsPresentationPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vifDirectPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vifDirectFragmentsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifOrderPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifTagSemanticsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifStreamPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifImageOrderPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifImage2Patch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gifNativeTagPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsImageFragmentsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsTriangleSamplingPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsSpriteSamplingPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $iopFastPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu0MacroPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $mmiPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsTriangleConstantsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsTriangleTexcoordsPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1EfuOpcodesPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsCpuStatePatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsCpuRoundingPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $getenvHotPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1PerfPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $sprChainPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $mpegCreatePatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $audioPcmPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $iopSoundPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $memcardPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsTrianglePrecisionPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsPackedDepthPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsBilinearPrecisionPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsNearestStqPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsFeedbackSnapshotPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsBilinearStqPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsRegionPagesPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsTargetAliasPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1DirectPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1CompiledPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1BudgetDiagPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1StickyPreservePatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1BlocksPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1RunnerPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $iopSchedulerPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vif1UnpackFastPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $eeTimersFastPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $vu1SimdPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsCoordinateAliasPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsStqHardwareTestPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsFinishAsyncPatch)
Run $git @('apply', '--ignore-whitespace', '--verbose', $gsHardwareProfilePatch)
Pop-Location

# El codigo generado incluye <ps2_recompiled_functions.h> desde src/runner
$cm = Join-Path $rec 'ps2xRuntime\CMakeLists.txt'
if (-not (Select-String -LiteralPath $cm -Pattern 'GOW-Port include' -Quiet)) {
    Add-Content -LiteralPath $cm "`n# GOW-Port include`ntarget_include_directories(ps2EntryRunner PRIVATE `${CMAKE_CURRENT_SOURCE_DIR}/src/runner)"
}

# Optimizado en paralelo: /O2 en cada archivo, sin optimizacion global del enlazador (/GL, /LTCG)
$rm = Join-Path $rec 'ps2xRuntime\cmake\ReleaseMode.cmake'
$t = Get-Content -LiteralPath $rm -Raw
$t2 = $t -replace '(?m)^\s*/GL\b.*\r?\n', '' -replace '(?m)^\s*/LTCG\b.*\r?\n', '' `
         -replace 'set_property\(TARGET \$\{TargetName\} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE\)', '# IPO desactivado (GOW-Port)'
if ($t2 -ne $t) { Set-Content -LiteralPath $rm -Value $t2 -NoNewline; Write-Host 'ReleaseMode.cmake: LTCG desactivado' }

Paso 'Configurando CMake'
# Las trazas por función vacían el archivo en cada entrada/salida. Activarlas solo para investigar.
$logsEnabled = if ($Trazas) { 'ON' } else { 'OFF' }
Run 'cmake' @('-S', $rec, '-B', $bld, '-G', 'Ninja', '-DCMAKE_BUILD_TYPE=Release', '-DCMAKE_INTERPROCEDURAL_OPTIMIZATION=OFF',
              "-DPS2X_ENABLE_RUNTIME_LOGS=$logsEnabled", "-DPS2X_ENABLE_AGRESSIVE_LOGS=$logsEnabled", "-DPS2X_ENABLE_IOP_RPC_TRACE=$logsEnabled",
              '-DPS2X_ENABLE_RUNNER_UNITY_BUILD=ON', '-DPS2X_ENABLE_RUNNER_PCH=ON')
# VU1 compilada (opcional): GOW_VU1_MICROCODIGO es una carpeta local con micromemorias capturadas con
# GOW_VU1_CAPTURA. Sin ella (o vacía) el juego usa el intérprete. Ver docs\RENDIMIENTO.md.
$vu1Micro = if ($env:GOW_VU1_MICROCODIGO) { (Resolve-Path -LiteralPath $env:GOW_VU1_MICROCODIGO).Path -replace '\\', '/' } else { '' }
$vu1Gen = if ($vu1Micro) { (Join-Path $RepoRoot 'tools\vu1\generar_vu1.cpp') -replace '\\', '/' } else { '' }
Run 'cmake' @('-S', $rec, '-B', $bld, "-DPS2X_VU1_MICROCODE_DIR=$vu1Micro", "-DPS2X_VU1_GENERATOR_SOURCE=$vu1Gen")

Paso 'Compilando el recompilador'
Run 'cmake' @('--build', $bld, '--target', 'ps2_recomp')

Paso 'Generando C++ desde SCUS_973.99'
if (Test-Path $gen) { Remove-Item $gen -Recurse -Force }
New-Item -ItemType Directory $gen | Out-Null
$fw = { param($p) $p -replace '\\', '/' }
# ps2_recomp no abre rutas con caracteres no ASCII (p. ej. acentos en la carpeta del repositorio):
# copiamos el ELF y el mapa de funciones a la carpeta de trabajo, que tiene una ruta corta.
$elfWork = Join-Path $work 'SCUS_973.99'
$mapWork = Join-Path $work 'funcmap.csv'
Copy-Item -LiteralPath $elf -Destination $elfWork -Force
Copy-Item -LiteralPath $funcmap -Destination $mapWork -Force
(Get-Content -LiteralPath $template -Raw) `
    -replace '@ELF@', (& $fw $elfWork) `
    -replace '@MAP@', (& $fw $mapWork) `
    -replace '@OUT@', ((& $fw $gen) + '/') |
    Set-Content -LiteralPath (Join-Path $work 'config.toml') -Encoding ASCII
$recompExe = Get-ChildItem $bld -Recurse -Filter 'ps2_recomp.exe' | Select-Object -First 1
Run $recompExe.FullName @((Join-Path $work 'config.toml')) | Select-Object -Last 5
Write-Host ("Archivos generados: {0}" -f (Get-ChildItem $gen).Count)

Paso 'Copiando codigo generado al runtime'
$runner = Join-Path $rec 'ps2xRuntime\src\runner'
Get-ChildItem $runner -File | Remove-Item -Force
Get-ChildItem -LiteralPath $gen -File | Copy-Item -Destination $runner
Copy-Item -LiteralPath $overrides -Destination (Join-Path $runner 'gow_overrides.cpp')
Get-ChildItem -LiteralPath (Join-Path $RepoRoot 'src') -Filter '*.h' -File | Copy-Item -Destination $runner
# Con MSVC en espanol ninja no registra las dependencias /showIncludes: los .cpp incluidos desde los
# archivos unity (codigo generado, register_functions.cpp, overrides) no fuerzan recompilacion. Borramos
# los objetos unity para que se recompilen siempre con el codigo recien generado.
$unityDir = Join-Path $bld 'ps2xRuntime\CMakeFiles\ps2EntryRunner.dir\Unity'
if (Test-Path -LiteralPath $unityDir) { Get-ChildItem -LiteralPath $unityDir -Filter '*.obj' | Remove-Item -Force }
Run 'cmake' @('-S', $rec, '-B', $bld)

Paso 'Compilando el juego optimizado en paralelo'
Run 'cmake' @('--build', $bld, '--target', 'ps2EntryRunner')

$exe = Get-ChildItem $bld -Recurse -Filter 'ps2EntryRunner.exe' | Select-Object -First 1
Paso "OK: $($exe.FullName)"
