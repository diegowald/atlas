@echo off
@setlocal enableextensions
@cd /d "%~dp0"

:: Install the Windows Service.
set InstallWindowsService=true

@call MongoDB.bat

:: Press any key to continue...
pause
