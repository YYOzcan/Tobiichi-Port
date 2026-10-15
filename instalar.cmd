@echo off
rem Tobiichi Port: instalador para Windows. Doble clic o: instalar.cmd [-Iso "C:\ruta\God of War.iso"] [-Herramientas]
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0instalar.ps1" %*
