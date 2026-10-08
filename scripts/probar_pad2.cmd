@echo off
setlocal
cd /d "%~dp0.."
if not exist logs mkdir logs
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VSPATH="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH exit /b 1
set VSCMD_SKIP_SENDTELEMETRY=1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vcvars_pad_test.log 2>&1
if errorlevel 1 exit /b 1
cl /nologo /EHsc /std:c++20 tests\pad2_packet_test.cpp /Fologs\pad2_packet_test.obj /Felogs\pad2_packet_test.exe
if errorlevel 1 exit /b 1
logs\pad2_packet_test.exe
exit /b %errorlevel%
