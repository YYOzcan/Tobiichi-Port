@echo off
rem Instala Git y Visual Studio 2022 Build Tools (C++, CMake y Ninja incluidos).
cd /d "%~dp0.."
if not exist logs mkdir logs
echo ==========================================================
echo  Instalando Git y Visual Studio 2022 Build Tools (C++)
echo  Windows te va a pedir permiso de administrador: acepta.
echo  Puede tardar 15-30 minutos. No cierres esta ventana.
echo ==========================================================
echo [%date% %time%] Inicio > logs\1_instalar.log
winget install -e --id Git.Git --accept-source-agreements --accept-package-agreements >> logs\1_instalar.log 2>&1
echo [git] codigo %errorlevel% >> logs\1_instalar.log
winget install -e --id Microsoft.VisualStudio.2022.BuildTools --accept-source-agreements --accept-package-agreements --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended" >> logs\1_instalar.log 2>&1
echo [vs] codigo %errorlevel% >> logs\1_instalar.log
echo [%date% %time%] FIN >> logs\1_instalar.log
echo.
echo Listo. Revisa logs\1_instalar.log
pause
