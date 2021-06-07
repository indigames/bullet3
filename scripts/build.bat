@echo off

set CALL_DIR=%CD%
set PROJECT_DIR=%~dp0..

cd %PROJECT_DIR%
python ./scripts/build.py

cd %CALL_DIR%
