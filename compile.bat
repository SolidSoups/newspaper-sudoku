@echo off
setlocal

REM Clear caches
if exist build (
    echo Cleaning build directory
    rmdir /s/q .\build
    mkdir build
)
if exist cmake-build-debug (
    echo Cleaning cmake-build-debug directory
    rmdir /s/q .\cmake-build-debug
)

echo Configuring cmake project...
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
