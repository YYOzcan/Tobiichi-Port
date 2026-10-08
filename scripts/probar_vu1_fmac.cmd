@echo off
rem GOW-Port: FMAC SIMD frente al interprete, incluyendo underflow con FTZ/DAZ; sin datos del juego.
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "TASK_FMAC_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "TASK_FMAC_VSPATH="
for /f "usebackq tokens=*" %%i in (`"%TASK_FMAC_VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "TASK_FMAC_VSPATH=%%i"
if not defined TASK_FMAC_VSPATH goto :failed
set VSCMD_SKIP_SENDTELEMETRY=1
call "%TASK_FMAC_VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vu1_fmac_vcvars.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
if defined GOW_WORK (set "TASK_FMAC_WORK=%GOW_WORK%") else (set "TASK_FMAC_WORK=%~d0\gowport")
set "TASK_FMAC_RUNTIME=%TASK_FMAC_WORK%\PS2Recomp"
set "TASK_FMAC_BUILD=%TASK_FMAC_RUNTIME%\out\build"
if not exist "%TASK_FMAC_BUILD%\ps2xRuntime\ps2_runtime.lib" goto :failed
if not exist logs\vu1_fmac mkdir logs\vu1_fmac
call :compile tools\vu1\generar_vu1.cpp vu1_fmac_generator
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
call :compile tests\vu1_fmac_test.cpp vu1_fmac_fixture
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\vu1_fmac_fixture.exe --write logs\vu1_fmac\synthetic.bin
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\vu1_fmac_generator.exe logs\vu1_fmac logs\vu1_fmac\synthetic.bin > logs\vu1_fmac_generator.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /MP4 /I "%TASK_FMAC_RUNTIME%\ps2xRuntime\include" /I "%TASK_FMAC_RUNTIME%\ps2xRuntime\src\lib\vu" /c logs\vu1_fmac\programa*.cpp /Fo"logs\vu1_fmac\\" > logs\vu1_fmac_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
link /nologo /out:logs\vu1_fmac_test.exe logs\vu1_fmac_fixture.obj logs\vu1_fmac\programa*.obj "%TASK_FMAC_BUILD%\ps2xRuntime\ps2_runtime.lib" "%TASK_FMAC_BUILD%\_deps\fmt-build\fmt.lib" "%TASK_FMAC_BUILD%\_deps\raylib-build\raylib\raylib.lib" "%TASK_FMAC_BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> logs\vu1_fmac_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
set GOW_VU1C_DIAG=1
set GOW_VU1C_RANGO=
set GOW_VU1C_SIN_BLOQUES=
set GOW_VU1_SIN_COMPILAR=
logs\vu1_fmac_test.exe 200 > logs\vu1_fmac_test.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
findstr /r /c:"compilados=[1-9]" logs\vu1_fmac_test.log >nul
exit /b %errorlevel%

:compile
cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /I "%TASK_FMAC_RUNTIME%\ps2xRuntime\include" /c "%~1" /Fo"logs\%~2.obj" > "logs\%~2_build.log" 2>&1
if errorlevel 1 exit /b 1
if not errorlevel 0 exit /b 1
link /nologo /out:"logs\%~2.exe" "logs\%~2.obj" "%TASK_FMAC_BUILD%\ps2xRuntime\ps2_runtime.lib" "%TASK_FMAC_BUILD%\_deps\fmt-build\fmt.lib" "%TASK_FMAC_BUILD%\_deps\raylib-build\raylib\raylib.lib" "%TASK_FMAC_BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> "logs\%~2_build.log" 2>&1
exit /b %errorlevel%

:failed
exit /b 1
