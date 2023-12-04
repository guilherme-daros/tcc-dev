cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/pico-sdk")
set(PICO_BOARD pico_w CACHE STRING "Board type")

include(${CMAKE_SOURCE_DIR}/cmake/pico_sdk_import.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/pico_extras_import.cmake)


if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(tcc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory("apps")