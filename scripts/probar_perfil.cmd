@echo off
rem GOW-Port: regresion de DbgHelp y pilas recuperadas, sin el juego.
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "TASK_PROFILE_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "TASK_PROFILE_VSPATH="
for /f "usebackq tokens=*" %%i in (`"%TASK_PROFILE_VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "TASK_PROFILE_VSPATH=%%i"
if not defined TASK_PROFILE_VSPATH goto :failed
set VSCMD_SKIP_SENDTELEMETRY=1
call "%TASK_PROFILE_VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\perfil_vcvars.log 2>&1
if errorlevel 1 goto :failed
cl /nologo /O2 /EHsc /MD /utf-8 /std:c++20 tools\perfil\muestrear.cpp /Fe:logs\muestrear.exe /Fo:logs\muestrear.obj > logs\perfil_build.log 2>&1
if errorlevel 1 goto :failed
cl /nologo /O2 /EHsc /MD /Zi /utf-8 /std:c++20 tests\perfil_espera_fixture.cpp /Fe:logs\perfil_espera.exe /Fo:logs\perfil_espera.obj /Fd:logs\perfil_compiler.pdb /link /DEBUG /PDB:logs\perfil_espera.pdb >> logs\perfil_build.log 2>&1
if errorlevel 1 goto :failed
set "TASK_PROFILE_PS=powershell.exe"
where pwsh.exe > nul 2>&1
if not errorlevel 1 set "TASK_PROFILE_PS=pwsh.exe"
"%TASK_PROFILE_PS%" -NoProfile -ExecutionPolicy Bypass -File tests\perfil_espera_test.ps1 -Perfilador "%CD%\logs\muestrear.exe" -Fixture "%CD%\logs\perfil_espera.exe" > logs\perfil_test.log 2>&1
if errorlevel 1 goto :failed
type logs\perfil_test.log
exit /b 0
:failed
exit /b 1
