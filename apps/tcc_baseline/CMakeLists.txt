add_executable(tcc_baseline "")

execute_process(
    COMMAND
    ${PICO_SDK_PATH}lib/btstack/tool/compile_gatt.py
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.gatt
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.h
    )

pico_set_program_name(tcc_baseline "tcc_baseline")
pico_set_program_version(tcc_baseline "0.1")

include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)

target_include_directories(
  tcc_baseline PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory("src")

target_sources(
  tcc_baseline
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  tcc_baseline
  pico_runtime
  pico_stdlib
  pico_cyw43_arch_none
  pico_btstack_cyw43
  pico_btstack_ble
)

pico_enable_stdio_usb(tcc_baseline 1)
pico_enable_stdio_uart(tcc_baseline 0)


pico_add_extra_outputs(tcc_baseline)

install(TARGETS tcc_baseline
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

