@echo off
setlocal enabledelayedexpansion
title Doc Converter - Offline TXT to HTML

echo.
echo ================================================================
echo   DOC CONVERTER  //  Offline TXT to Styled HTML
echo ================================================================
echo.

:: Check Python
python --version >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Python not found. Download from https://www.python.org
    pause
    exit /b 1
)

:: Get input file — support drag and drop onto bat
if "%~1"=="" (
    set /p INPUT_FILE="TXT file path: "
) else (
    set INPUT_FILE=%~1
)

set INPUT_FILE=!INPUT_FILE:"=!

if not exist "!INPUT_FILE!" (
    echo.
    echo [ERROR] File not found: !INPUT_FILE!
    pause
    exit /b 1
)

:: Get script location (same folder as this bat)
set SCRIPT_DIR=%~dp0
set PY_SCRIPT=!SCRIPT_DIR!doc_converter.py

if not exist "!PY_SCRIPT!" (
    echo.
    echo [ERROR] doc_converter.py not found next to this bat file.
    echo         Make sure both files are in the same folder.
    pause
    exit /b 1
)

:: Run converter
echo [INFO] Converting: !INPUT_FILE!
echo.
python "!PY_SCRIPT!" "!INPUT_FILE!"

if errorlevel 1 (
    echo.
    echo [ERROR] Conversion failed.
    pause
    exit /b 1
)

:: Get output path (same name, .html extension)
for %%F in ("!INPUT_FILE!") do set OUTPUT_FILE=%%~dpnF.html

echo.
echo ================================================================
echo   SUCCESS!
echo   Output: !OUTPUT_FILE!
echo ================================================================
echo.

set /p OPEN_FILE="Open in browser now? (y/n): "
if /i "!OPEN_FILE!"=="y" (
    start "" "!OUTPUT_FILE!"
)

pause
exit /b 0
