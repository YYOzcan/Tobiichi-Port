@echo off
rem Registra cada 30 s el uso de CPU/RAM de la compilacion en logs\monitor.log
cd /d "%~dp0.."
if not exist logs mkdir logs
echo Vigilando la compilacion cada 30 segundos (cierra esta ventana cuando quieras)...
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0monitor.ps1"
