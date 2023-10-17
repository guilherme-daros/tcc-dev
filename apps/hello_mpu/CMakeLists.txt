add_executable(hello_mpu "")

target_include_directories(
        hello_mpu 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory("src")

target_sources(
  hello_mpu
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
        hello_mpu 
        pico_stdlib
        hardware_i2c
)

pico_enable_stdio_usb(hello_mpu 1)
pico_enable_stdio_uart(hello_mpu 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_mpu)

install(TARGETS hello_mpu
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)