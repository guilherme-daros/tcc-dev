add_executable(hello_ble gatt_ht_server.c )

pico_set_program_name(hello_ble "hello_ble")
pico_set_program_version(hello_ble "0.1")

pico_enable_stdio_uart(hello_ble 0)
pico_enable_stdio_usb(hello_ble 1)

# Add the standard library to the build
target_link_libraries(hello_ble
    pico_stdlib
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_ble
)

# TODO: THIS DOES NOT WORK
# pico_btstack_make_gatt_header(hello_ble PRIVATE "${CMAKE_CURRENT_LIST_DIR}/gatt_ht-server.gatt")

# Add the standard include files to the build
target_include_directories(hello_ble PRIVATE
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

pico_add_extra_outputs(hello_ble)

install(TARGETS hello_ble
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)