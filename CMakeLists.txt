
cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/pico-sdk")
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-tflu C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

pico_sdk_init()

include(tflmicro.cmake)

add_subdirectory("apps")