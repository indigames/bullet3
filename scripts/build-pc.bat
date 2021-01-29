@echo off

SET LIB_NAME=bullet

SET BUILD_DEBUG=0

echo COMPILING ...
SET PROJECT_DIR=%~dp0..

SET BUILD_DIR=%~dp0..\build\pc
SET OUTPUT_DIR=%IGE_LIBS%\%LIB_NAME%
SET OUTPUT_LIBS_DEBUG=%OUTPUT_DIR%\libs\pc\Debug
SET OUTPUT_LIBS_RELEASE=%OUTPUT_DIR%\libs\pc

SET CALL_DIR=%CD%

echo Compiling %LIB_NAME% ...

if not exist %OUTPUT_DIR% (
    mkdir %OUTPUT_DIR%
)

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

echo Cleaning up...
    if [%BUILD_DEBUG%]==[1] (
        if exist %OUTPUT_LIBS_DEBUG% (
            rmdir /s /q %OUTPUT_LIBS_DEBUG%
        )
        mkdir %OUTPUT_LIBS_DEBUG%
    )

    if exist %OUTPUT_LIBS_RELEASE% (
        rmdir /s /q %OUTPUT_LIBS_RELEASE%
    )
    mkdir %OUTPUT_LIBS_RELEASE%

cd %PROJECT_DIR%
echo Compiling x86...
    if not exist %BUILD_DIR%\x86 (
        mkdir %BUILD_DIR%\x86
    )
    echo Generating x86 CMAKE project ...
    cd %BUILD_DIR%\x86
    cmake %PROJECT_DIR% -A Win32 -DAPP_STYLE=STATIC
    if %ERRORLEVEL% NEQ 0 goto ERROR

    if [%BUILD_DEBUG%]==[1] (
        echo Compiling x86 - Debug...
        cmake --build . --config Debug -- -m
        if %ERRORLEVEL% NEQ 0 goto ERROR
        for /r %CD% %%f in (*.lib) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x86\
    )

    echo Compiling x86 - Release...
    cmake --build . --config Release -- -m
    if %ERRORLEVEL% NEQ 0 goto ERROR
    for /r %CD% %%f in (*.lib) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x86\
echo Compiling x86 DONE

cd %PROJECT_DIR%
echo Compiling x64...
    if not exist %BUILD_DIR%\x64 (
        mkdir %BUILD_DIR%\x64
    )
    echo Generating x64 CMAKE project ...
    cd %BUILD_DIR%\x64
    cmake %PROJECT_DIR% -A x64 -DAPP_STYLE=STATIC
    if %ERRORLEVEL% NEQ 0 goto ERROR

    if [%BUILD_DEBUG%]==[1] (
        echo Compiling x64 - Debug...
        cmake --build . --config Debug -- -m
        if %ERRORLEVEL% NEQ 0 goto ERROR
        for /r %CD% %%f in (*.lib) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x64\
    )

    echo Compiling x64 - Release...
    cmake --build . --config Release -- -m
    if %ERRORLEVEL% NEQ 0 goto ERROR
    for /r %CD% %%f in (*.lib) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x64\
echo Compiling x64 DONE

goto ALL_DONE

:ERROR
    echo ERROR OCCURED DURING COMPILING!

:ALL_DONE
    cd %CALL_DIR%
    echo COMPILING DONE!