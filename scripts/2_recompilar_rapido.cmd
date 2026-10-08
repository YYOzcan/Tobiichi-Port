@echo off
rem Recompilacion rapida (~1 min): copia src\gow_overrides.cpp al runtime y compila solo lo que cambio,
rem sin regenerar el C++ del juego. Requiere haber hecho antes scripts\2_compilar.cmd.
cd /d "%~dp0.."
if not exist logs mkdir logs
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VSPATH="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH (
  echo No se encontro Visual Studio con C++. Corre primero scripts\1_instalar_herramientas.cmd
  exit /b 1
)
set VSCMD_SKIP_SENDTELEMETRY=1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vcvars.log 2>&1
rem Misma carpeta de trabajo que scripts\common.ps1 (Get-GowWorkDir)
if defined GOW_WORK (set "WORK=%GOW_WORK%") else (set "WORK=%~d0\gowport")
copy /y "src\gow_overrides.cpp" "%WORK%\PS2Recomp\ps2xRuntime\src\runner\gow_overrides.cpp" >nul
if errorlevel 1 exit /b 1
copy /y "src\*.h" "%WORK%\PS2Recomp\ps2xRuntime\src\runner\" >nul
if errorlevel 1 exit /b 1
rem Con MSVC en espanol ("Nota: inclusion del archivo:") ninja no registra las dependencias de /showIncludes,
rem asi que un cambio en gow_overrides.cpp (incluido desde un archivo unity) no recompila nada.
rem Tocamos el archivo unity que lo incluye para forzarlo.
powershell -NoProfile -Command "$unityDir = Join-Path $env:WORK 'PS2Recomp\out\build\ps2xRuntime\CMakeFiles\ps2EntryRunner.dir\Unity'; Get-ChildItem -LiteralPath $unityDir -Filter '*.cxx' -File | Where-Object { Select-String -LiteralPath $_.FullName -SimpleMatch 'gow_overrides.cpp' -Quiet } | ForEach-Object { $_.LastWriteTime = Get-Date }"
if errorlevel 1 exit /b 1
cmake --build "%WORK%\PS2Recomp\out\build" --target ps2EntryRunner > logs\2_recompilar_rapido.log 2>&1
set "RC=%errorlevel%"
echo [codigo final %RC%] >> logs\2_recompilar_rapido.log
echo Termino (codigo %RC%). Revisa logs\2_recompilar_rapido.log
exit /b %RC%
