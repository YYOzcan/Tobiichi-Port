@echo off
rem Ejecuta el port sin limite de tiempo. Cierralo con la X de la ventana del juego.
cd /d "%~dp0.."
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0ejecutar.ps1" -Segundos 0
