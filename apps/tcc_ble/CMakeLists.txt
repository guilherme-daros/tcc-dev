add_executable(tcc_ble "")

pico_set_program_name(tcc_ble "tcc_ble")
pico_set_program_version(tcc_ble "0.1")

pico_enable_stdio_uart(tcc_ble 0)
pico_enable_stdio_usb(tcc_ble 1)

# Add the standard library to the build
target_link_libraries(tcc_ble
    pico_stdlib
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_ble
)

include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)

add_subdirectory("src")

target_sources(
    tcc_ble PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

# Add the standard include files to the build
target_include_directories(
    tcc_ble PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# TODO: THIS DOES NOT WORK
# pico_btstack_make_gatt_header(tcc_ble PRIVATE "${CMAKE_CURRENT_LIST_DIR}/gatt_ht_server.gatt" )
    
pico_add_extra_outputs(tcc_ble)

install(TARGETS tcc_ble
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)