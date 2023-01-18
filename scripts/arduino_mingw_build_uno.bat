@echo off

SET CMAKE_LOCAL_ROOT=F:/Programs/cmake-3.11.2-win64-x64/bin/
SET ARDUINO_SDK_PATH=F:/Programs/arduino-1.8.1/
SET MINGW_COMPILER_PATH=c:/Qt/Tools/mingw810_32/bin/
set path=%path%;%CMAKE_LOCAL_ROOT%;%ARDUINO_SDK_PATH%;%MINGW_COMPILER_PATH%
 
REM %ARDUINO_SDK_PATH%\hardware\tools\avr\utils\bin
REM -DCMAKE_MAKE_PROGRAM="%ARDUINO_SDK_PATH%/hardware/tools/avr/utils/bin/make.exe"
cd ..
if not exist build_arduino mkdir build_arduino
cd build_arduino
cmake -DBUILD_ARDUINO=ON -DCMAKE_TOOLCHAIN_FILE="../Arduino-CMake-Toolchain/Arduino-toolchain.cmake" -DARDUINO_INSTALL_PATH=%ARDUINO_SDK_PATH% -DARDUINO_BOARD="Arduino Duemilanove or Diecimila [avr.diecimila]" -DARDUINO_AVR_DIECIMILA_MENU_CPU_ATMEGA328=TRUE -G "MinGW Makefiles" -Wno-dev ../src
cmake --build .
PAUSE