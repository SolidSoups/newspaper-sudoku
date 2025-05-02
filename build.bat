@echo off
setlocal

echo Building cmake project...
cmake --build build

.\copy_assets.bat
