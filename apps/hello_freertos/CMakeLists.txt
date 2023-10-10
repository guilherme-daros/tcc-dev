add_executable(hello_freertos "")

target_include_directories(
        hello_freertos 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/lib/freertos/include
)

include(${CMAKE_SOURCE_DIR}/cmake/freertos.cmake)

add_subdirectory("src")

target_sources(
  hello_freertos
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
        hello_freertos 
        pico_stdlib
        FreeRTOS
)

pico_enable_stdio_usb(hello_freertos 1)
pico_enable_stdio_uart(hello_freertos 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_freertos)

install(TARGETS hello_freertos
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)