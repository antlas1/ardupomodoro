@echo off

SET MINGW_COMPILER_PATH=c:/Qt/Tools/mingw810_32/bin/
set path=%path%;%MINGW_COMPILER_PATH%

cd ../build_arduino
mingw32-make upload-PomodoroArduino SERIAL_PORT=COM5
pause