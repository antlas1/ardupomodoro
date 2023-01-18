cmake_minimum_required(VERSION 3.11)

project(PomodoroArduino VERSION "1.0" LANGUAGES C CXX)
        
option(BUILD_ARDUINO "Build for arduino board" OFF)
if (BUILD_ARDUINO)
message("Use arduino build.")
endif()

set(HEADERS
iformatedoutput.h
ikeyboard.h
ipomodorologic.h
keys.h
app_entry.h
)

if (BUILD_ARDUINO)
   set(PLATFORM_SOURCES
      arduino/platform.cpp
   )
else()
   set(PLATFORM_SOURCES
   host/stdio_platform.cpp
)
endif()

set(SOURCES 
    portable_app.cpp
    pomodorologic.cpp
    #arduino/main_example_lcd.cpp
    ${PLATFORM_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if (BUILD_ARDUINO)
# Arduino.h is included in hello_world.cpp, so link with Arduino core
target_link_arduino_libraries(${PROJECT_NAME} PRIVATE core SpinTimer LcdKeypad)

# This is needed for generation of HEX image and uploading it
target_enable_arduino_upload(${PROJECT_NAME})
endif()