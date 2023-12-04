add_executable(hello_lp "")

target_include_directories(
        hello_lp 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory("src")

target_sources(
  hello_lp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
        hello_lp 
        pico_stdlib
        hardware_sleep
        pico_cyw43_arch_none

)

pico_enable_stdio_usb(hello_lp 1)
pico_enable_stdio_uart(hello_lp 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_lp)

install(TARGETS hello_lp
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)