@echo off
@setlocal enableextensions
@cd /d "%~dp0"

:: Stop the MongoDB windows service.
NET STOP MongoDB

:: Remove the MongoDB windows service.
"%CD%\mongodb\bin\mongod.exe" --remove

:: Check for errors.
IF ERRORLEVEL 1 (
	echo.
	echo ERROR: An error occurred while attempting to uninstall the MongoDB service. See messages above for details.
	echo.
)

:: Press any key to continue...
pause
