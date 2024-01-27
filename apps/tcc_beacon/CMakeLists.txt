add_executable(tcc_beacon "")

execute_process(
    COMMAND
    ${PICO_SDK_PATH}lib/btstack/tool/compile_gatt.py
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.gatt
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.h
    )

pico_set_program_name(tcc_beacon "tcc_beacon")
pico_set_program_version(tcc_beacon "0.1")

include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)

target_include_directories(
  tcc_beacon PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/freertos/include
)

add_subdirectory("src")

target_sources(
  tcc_beacon
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  tcc_beacon
  pico_runtime
  pico_stdlib
  pico_cyw43_arch_none
  pico_btstack_cyw43
  pico_btstack_ble
)

pico_enable_stdio_usb(tcc_beacon 1)
pico_enable_stdio_uart(tcc_beacon 0)


pico_add_extra_outputs(tcc_beacon)

install(TARGETS tcc_beacon
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

