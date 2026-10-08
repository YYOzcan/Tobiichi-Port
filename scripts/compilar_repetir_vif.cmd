@echo off
rem Compila tools\render\repetir_cadena_vif.cpp contra el runtime ya compilado (scripts\2_compilar.cmd).
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VSPATH="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH exit /b 1
set VSCMD_SKIP_SENDTELEMETRY=1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vcvars_repetir_vif.log 2>&1
if errorlevel 1 exit /b 1
if defined GOW_WORK (set "WORK=%GOW_WORK%") else (set "WORK=%~d0\gowport")
set "BUILD=%WORK%\PS2Recomp\out\build"
if not exist "%BUILD%\ps2xRuntime\ps2_runtime.lib" exit /b 1
cl /nologo /std:c++20 /EHsc /O2 /Zi /MD /utf-8 /I "%WORK%\PS2Recomp\ps2xRuntime\include" /c tools\render\repetir_cadena_vif.cpp /Fo"logs\repetir_cadena_vif.obj" /Fd"logs\repetir_cadena_vif_compile.pdb" > logs\repetir_cadena_vif_build.log 2>&1
if errorlevel 1 exit /b 1
link /nologo /DEBUG /out:"logs\repetir_cadena_vif.exe" "logs\repetir_cadena_vif.obj" "%BUILD%\ps2xRuntime\ps2_runtime.lib" "%BUILD%\_deps\fmt-build\fmt.lib" "%BUILD%\_deps\raylib-build\raylib\raylib.lib" "%BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> logs\repetir_cadena_vif_build.log 2>&1
exit /b %errorlevel%
