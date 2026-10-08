@echo off
rem Ejecuta el port durante 60 segundos y guarda la salida en logs\.
cd /d "%~dp0.."
echo Ejecutando el port durante 60 segundos (se cierra solo)...
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0ejecutar.ps1" -Segundos 60
echo Listo. Salida en logs\ejecutar.log y logs\ejecutar_err.log
timeout /t 15 >nul
