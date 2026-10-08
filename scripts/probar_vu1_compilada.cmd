@echo off
rem GOW-Port: valida el generador de PR18 con microcodigo procedural, sin datos del juego.
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "TASK_VU1_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "TASK_VU1_VSPATH="
for /f "usebackq tokens=*" %%i in (`"%TASK_VU1_VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "TASK_VU1_VSPATH=%%i"
if not defined TASK_VU1_VSPATH goto :failed
set VSCMD_SKIP_SENDTELEMETRY=1
call "%TASK_VU1_VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vu1_procedural_vcvars.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
if defined GOW_WORK (set "TASK_VU1_WORK=%GOW_WORK%") else (set "TASK_VU1_WORK=%~d0\gowport")
set "TASK_VU1_RUNTIME=%TASK_VU1_WORK%\PS2Recomp"
set "TASK_VU1_BUILD=%TASK_VU1_RUNTIME%\out\build"
if not exist "%TASK_VU1_BUILD%\ps2xRuntime\ps2_runtime.lib" goto :failed
if not exist logs\vu1_procedural mkdir logs\vu1_procedural
call :compile tools\vu1\generar_vu1.cpp vu1_generator
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
call :compile tests\vu1_compiled_test.cpp vu1_fixture
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\vu1_fixture.exe --write logs\vu1_procedural\synthetic.bin
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\vu1_generator.exe logs\vu1_procedural logs\vu1_procedural\synthetic.bin > logs\vu1_procedural_generator.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /I "%TASK_VU1_RUNTIME%\ps2xRuntime\include" /I "%TASK_VU1_RUNTIME%\ps2xRuntime\src\lib\vu" /c logs\vu1_procedural\programa*.cpp /Fo"logs\vu1_procedural\\" > logs\vu1_procedural_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
link /nologo /out:logs\vu1_compiled_test.exe logs\vu1_fixture.obj logs\vu1_procedural\programa*.obj "%TASK_VU1_BUILD%\ps2xRuntime\ps2_runtime.lib" "%TASK_VU1_BUILD%\_deps\fmt-build\fmt.lib" "%TASK_VU1_BUILD%\_deps\raylib-build\raylib\raylib.lib" "%TASK_VU1_BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> logs\vu1_procedural_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
set GOW_VU1C_DIAG=1
set GOW_VU1C_RANGO=
set GOW_VU1C_SIN_BLOQUES=
set GOW_VU1_SIN_COMPILAR=
logs\vu1_compiled_test.exe > logs\vu1_procedural_test.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
findstr /r /c:"compilados=[1-9]" logs\vu1_procedural_test.log >nul
exit /b %errorlevel%

:compile
cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /I "%TASK_VU1_RUNTIME%\ps2xRuntime\include" /c "%~1" /Fo"logs\%~2.obj" > "logs\%~2_build.log" 2>&1
if errorlevel 1 exit /b 1
if not errorlevel 0 exit /b 1
link /nologo /out:"logs\%~2.exe" "logs\%~2.obj" "%TASK_VU1_BUILD%\ps2xRuntime\ps2_runtime.lib" "%TASK_VU1_BUILD%\_deps\fmt-build\fmt.lib" "%TASK_VU1_BUILD%\_deps\raylib-build\raylib\raylib.lib" "%TASK_VU1_BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> "logs\%~2_build.log" 2>&1
exit /b %errorlevel%

:failed
exit /b 1
