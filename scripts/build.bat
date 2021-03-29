@echo off
setlocal enabledelayedexpansion

set CALL_DIR=%CD%

if "%IGE_BUILDER%"=="" (
    set IGE_BUILDER=%APPDATA%\indigames\igeBuilder
)

REM if not exist "!IGE_BUILDER!\.git" (
    REM mkdir "!IGE_BUILDER!"
    REM git clone https://github.com/indigames/igeBuilder !IGE_BUILDER!
REM ) else (
    REM cd !IGE_BUILDER!
    REM git fetch --all
    REM git checkout main
    REM git pull
REM )


if not exist "!IGE_BUILDER!\build-lib.bat" (
    echo ERROR: IGE_BUILDER was not found
    goto ERROR
)

if exist "%~dp0..\project.conf" (
    for /f "usebackq delims=" %%a in ("%~dp0..\project.conf") do (
        set ln=%%a
        for /f "tokens=1,2 delims=: " %%b in ("!ln!") do (
                set currkey=%%b
                set currval=%%c
                
                if "!currkey!"=="name" (
                    set PROJECT_NAME=!currval!
                ) else if "!currkey!"=="version" (
                    set PROJECT_VER=!currval!
                )
            )
        )
    )
)

echo !PROJECT_NAME!_!PROJECT_VER!

cd %CALL_DIR%
call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! windows x86
if %ERRORLEVEL% NEQ 0 goto ERROR

call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! windows x86_64
if %ERRORLEVEL% NEQ 0 goto ERROR

call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! android x86
if %ERRORLEVEL% NEQ 0 goto ERROR

call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! android x86_64
if %ERRORLEVEL% NEQ 0 goto ERROR

call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! android armv7
if %ERRORLEVEL% NEQ 0 goto ERROR

call !IGE_BUILDER!\build-lib.bat . !PROJECT_NAME! !PROJECT_VER! android armv8
if %ERRORLEVEL% NEQ 0 goto ERROR

cd %CALL_DIR%
echo ALL DONE!
goto :eof

:ERROR
    cd %CALL_DIR%
    echo ERROR OCCURED DURING COMPILING!
    exit /b 1
