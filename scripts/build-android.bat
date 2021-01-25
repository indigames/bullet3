@echo off
setlocal enabledelayedexpansion

SET LIB_NAME=bullet

SET BUILD_DEBUG=0

echo COMPILING ...
SET PROJECT_DIR=%~dp0..

SET BUILD_DIR=%~dp0..\build\android
SET OUTPUT_DIR=%IGE_LIBS%\%LIB_NAME%
SET OUTPUT_LIBS_DEBUG=%OUTPUT_DIR%\libs\android\Debug
SET OUTPUT_LIBS_RELEASE=%OUTPUT_DIR%\libs\android

SET CALL_DIR=%CD%

if not exist "%ANDROID_SDK_ROOT%" (
    if exist "%ANDROID_HOME%" (
        set ANDROID_SDK_ROOT=%ANDROID_HOME%
    ) else (
        if exist "%USERPROFILE%\AppData\Local\Android\sdk" (
            set ANDROID_SDK_ROOT=%USERPROFILE%\AppData\Local\Android\sdk
        ) else (
            echo ERROR: SDK NOT FOUND!
            goto ERROR
        )
    )
)
echo SDK: !ANDROID_SDK_ROOT!

if not exist "%ANDROID_NDK_ROOT%" (
    if exist "%ANDROID_SDK_ROOT%\ndk-bundle" (
        set ANDROID_NDK_ROOT=%ANDROID_SDK_ROOT%\ndk-bundle
    ) else (
        for /d %%D in (%ANDROID_SDK_ROOT%\ndk\*) do (
            set ANDROID_NDK_ROOT=%%~fD
        )
    )
)

if not exist "%ANDROID_NDK_ROOT%" (
    echo ERROR: NDK NOT FOUND!
    goto ERROR
)
echo NDK: !ANDROID_NDK_ROOT!

set ANDROID_TOOLCHAIN=!ANDROID_NDK_ROOT!\build\cmake\android.toolchain.cmake

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
echo Compiling arm64-v8a...
    if [%BUILD_DEBUG%]==[1] (
        if not exist %BUILD_DIR%\arm64-v8a\Debug (
            mkdir %BUILD_DIR%\arm64-v8a\Debug
        )
        cd %BUILD_DIR%\arm64-v8a\Debug
        echo Generating arm64-v8a Debug CMAKE project ...
        cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=!ANDROID_TOOLCHAIN! -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21 -DANDROID_ARM_MODE=arm -DANDROID_ARM_NEON=TRUE -DCMAKE_BUILD_TYPE=Debug %PROJECT_DIR%
        if %ERRORLEVEL% NEQ 0 goto ERROR

        echo Compiling arm64-v8a - Debug...
        cmake --build .
        if %ERRORLEVEL% NEQ 0 goto ERROR
        for /r %CD% %%f in (*.a) do xcopy /y %%f %OUTPUT_LIBS_DEBUG%\arm64-v8a\
        for /r %CD% %%f in (*.so) do xcopy /y %%f %OUTPUT_LIBS_DEBUG%\arm64-v8a\
    )

    if not exist %BUILD_DIR%\arm64-v8a\Release (
        mkdir %BUILD_DIR%\arm64-v8a\Release
    )
    cd %BUILD_DIR%\arm64-v8a\Release
    echo Generating arm64-v8a Release CMAKE project ...
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=!ANDROID_TOOLCHAIN! -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21 -DCMAKE_BUILD_TYPE=Release %PROJECT_DIR%

    echo Compiling arm64-v8a - Release...
    cmake --build .
    if %ERRORLEVEL% NEQ 0 goto ERROR
    for /r %CD% %%f in (*.a) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\arm64-v8a\
    for /r %CD% %%f in (*.so) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\arm64-v8a\
echo Compiling arm64-v8a DONE

cd %PROJECT_DIR%
echo Compiling x86_64...
    if [%BUILD_DEBUG%]==[1] (
        if not exist %BUILD_DIR%\x86_64\Debug (
            mkdir %BUILD_DIR%\x86_64\Debug
        )
        cd %BUILD_DIR%\x86_64\Debug
        echo Generating x86_64 Debug CMAKE project ...
        cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=!ANDROID_TOOLCHAIN! -DANDROID_ABI=x86_64 -DANDROID_PLATFORM=android-21 -DCMAKE_BUILD_TYPE=Debug %PROJECT_DIR%
        if %ERRORLEVEL% NEQ 0 goto ERROR

        echo Compiling x86_64 - Debug...
        cmake --build .
        if %ERRORLEVEL% NEQ 0 goto ERROR
        for /r %CD% %%f in (*.a) do xcopy /y %%f %OUTPUT_LIBS_DEBUG%\x86_64\
        for /r %CD% %%f in (*.so) do xcopy /y %%f %OUTPUT_LIBS_DEBUG%\x86_64\
    )

    if not exist %BUILD_DIR%\x86_64\Release (
        mkdir %BUILD_DIR%\x86_64\Release
    )
    cd %BUILD_DIR%\x86_64\Release
    echo Generating x86_64 Release CMAKE project ...
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=!ANDROID_TOOLCHAIN! -DANDROID_ABI=x86_64 -DANDROID_PLATFORM=android-21 -DCMAKE_BUILD_TYPE=Release %PROJECT_DIR%

    echo Compiling x86_64 - Release...
    cmake --build .
    if %ERRORLEVEL% NEQ 0 goto ERROR
    for /r %CD% %%f in (*.a) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x86_64\
    for /r %CD% %%f in (*.so) do xcopy /y %%f %OUTPUT_LIBS_RELEASE%\x86_64\
echo Compiling x86_64 DONE

goto ALL_DONE

:ERROR
    echo ERROR OCCURED DURING COMPILING!

:ALL_DONE
    cd %CALL_DIR%
    echo COMPILING DONE!