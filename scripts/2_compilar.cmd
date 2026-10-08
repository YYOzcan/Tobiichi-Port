@echo off
rem Carga el entorno de Visual Studio y ejecuta scripts\compilar.ps1.
cd /d "%~dp0.."
if not exist logs mkdir logs
echo ==========================================================
echo  Compilando el port. Puede tardar bastante (unos 20-40 min).
echo  El progreso se guarda en logs\2_compilar.log
echo ==========================================================
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VSPATH="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH (
  echo No se encontro Visual Studio con C++. > logs\2_compilar.log
  echo No se encontro Visual Studio con C++. Corre primero scripts\1_instalar_herramientas.cmd
  pause
  exit /b 1
)
set VSCMD_SKIP_SENDTELEMETRY=1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" > logs\vcvars.log 2>&1
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0compilar.ps1" %* > logs\2_compilar.log 2>&1
set "RC=%errorlevel%"
echo [codigo final %RC%] >> logs\2_compilar.log
echo.
echo Termino (codigo %RC%). Revisa logs\2_compilar.log
pause
