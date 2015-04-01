@echo off
@setlocal enableextensions
@cd /d "%~dp0"

:: Stop the MongoDB windows service.
NET STOP MongoDB

:: Check for errors.
IF ERRORLEVEL 1 (
	echo.
	echo ERROR: An error occurred while attempting to stop the MongoDB service.
	echo ERROR: See messages above for details.
	echo.
)

:: Press any key to continue...
pause
