@echo off
rem God of War (USA) native port - play launcher. No diagnostics, release settings.
rem   play.cmd            16:9, 1920x1080 window (the only mode)
rem Needs: the disc extracted to disc-usa\ (tools\iso_extract.py --layout) and the built runner. No ISO is read.
setlocal
set "ROOT=%~dp0"
set "EXE_DIR=%ROOT%ext\PS2Recomp-kl\out\build-kl\ps2xRuntime\Release"
if not exist "%EXE_DIR%\ps2EntryRunner.exe" (echo Runner not built: %EXE_DIR% & exit /b 1)
if not exist "%ROOT%disc-usa\play.mcd" (
  if exist "%ROOT%ref\saves\Mcd002.ps2" (copy /y "%ROOT%ref\saves\Mcd002.ps2" "%ROOT%disc-usa\play.mcd" >nul) else (echo No memory card found; the game will create one.)
)
set PS2X_GS_WORKER=1
set GOW_GS_FINISH_ASINCRONO=1
rem sound on the system default output (test runs use the device in %LOCALAPPDATA%\GodOfWarNative\audio_device.txt)
set GOW_AUDIO_DEVICE=default
set "GOW_MC0=%ROOT%disc-usa\play.mcd"
cd /d "%EXE_DIR%"
"%EXE_DIR%\ps2EntryRunner.exe" "%ROOT%disc-usa\SCUS_973.99"
endlocal
