add_executable(tcc_baseline "")

pico_enable_stdio_uart(tcc_baseline 0)
pico_enable_stdio_usb(tcc_baseline 1)

# Add the standard library to the build
target_link_libraries(tcc_baseline
    pico_stdlib
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_ble
)

include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)

add_subdirectory("src")

target_sources(
    tcc_baseline PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

# Add the standard include files to the build
target_include_directories(
    tcc_baseline PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# TODO: THIS DOES NOT WORK
# pico_btstack_make_gatt_header(tcc_baseline PRIVATE "${CMAKE_CURRENT_LIST_DIR}/gatt_ht_server.gatt" )
execute_process(
    COMMAND
    ${PICO_SDK_PATH}lib/btstack/tool/compile_gatt.py
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.gatt
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.h
    )
    
pico_add_extra_outputs(tcc_baseline)

install(TARGETS tcc_baseline
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)