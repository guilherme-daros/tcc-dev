add_executable(tcc_final "")

execute_process(
    COMMAND
    ${PICO_SDK_PATH}lib/btstack/tool/compile_gatt.py
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.gatt
    ${CMAKE_SOURCE_DIR}/include/physical_activity_monitor.h
    )

pico_set_program_name(tcc_final "tcc_final")
pico_set_program_version(tcc_final "0.1")

include(${CMAKE_SOURCE_DIR}/cmake/tflmicro.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/freertos.cmake)

target_include_directories(
  tcc_final PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/freertos/include
)

add_subdirectory("src")

target_sources(
  tcc_final
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  tcc_final
  pico_runtime
  tflmicro
  pico_cyw43_arch_none
  pico_btstack_cyw43
  pico_btstack_ble
  FreeRTOS
)

pico_enable_stdio_usb(tcc_final 1)
pico_enable_stdio_uart(tcc_final 0)


pico_add_extra_outputs(tcc_final)

install(TARGETS tcc_final
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

