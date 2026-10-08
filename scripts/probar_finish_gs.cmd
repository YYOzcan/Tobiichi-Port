@echo off
rem GOW-Port: FINISH, CSR y barrera de lectura; sin GPU ni datos del juego.
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "TASK_FINISH_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "TASK_FINISH_VSPATH="
for /f "usebackq tokens=*" %%i in (`"%TASK_FINISH_VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "TASK_FINISH_VSPATH=%%i"
if not defined TASK_FINISH_VSPATH goto :failed
set VSCMD_SKIP_SENDTELEMETRY=1
call "%TASK_FINISH_VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\gs_finish_vcvars.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
if defined GOW_WORK (set "TASK_FINISH_WORK=%GOW_WORK%") else (set "TASK_FINISH_WORK=%~d0\gowport")
set "TASK_FINISH_RUNTIME=%TASK_FINISH_WORK%\PS2Recomp"
set "TASK_FINISH_BUILD=%TASK_FINISH_RUNTIME%\out\build"
if not exist "%TASK_FINISH_BUILD%\ps2xRuntime\ps2_runtime.lib" goto :failed
cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /I "%TASK_FINISH_RUNTIME%\ps2xRuntime\include" /c tests\gs_finish_async_test.cpp /Fologs\gs_finish_test.obj > logs\gs_finish_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
link /nologo /out:logs\gs_finish_test.exe logs\gs_finish_test.obj "%TASK_FINISH_BUILD%\ps2xRuntime\ps2_runtime.lib" "%TASK_FINISH_BUILD%\_deps\fmt-build\fmt.lib" "%TASK_FINISH_BUILD%\_deps\raylib-build\raylib\raylib.lib" "%TASK_FINISH_BUILD%\ps2xIOP\ps2_iop.lib" glu32.lib winmm.lib opengl32.lib gdi32.lib user32.lib shell32.lib ole32.lib advapi32.lib bcrypt.lib secur32.lib ws2_32.lib >> logs\gs_finish_build.log 2>&1
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\gs_finish_test.exe default
if errorlevel 1 goto :failed
if not errorlevel 0 goto :failed
logs\gs_finish_test.exe async
exit /b %errorlevel%

:failed
exit /b 1
