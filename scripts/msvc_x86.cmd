@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"

REM Сборка
cd ..
if not exist build_msvc mkdir build_msvc
cd build_msvc
cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019"  -A "Win32" ../src
cmake --build .
pause