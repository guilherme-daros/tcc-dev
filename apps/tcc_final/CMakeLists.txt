add_executable(tcc_final "")

target_include_directories(
  tcc_final PRIVATE
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/include
)

pico_set_program_name(tcc_final "tcc_final")
pico_set_program_version(tcc_final "0.1")

# set_target_properties(
#   tcc_final
#   PROPERTIES
#   COMPILE_FLAGS -fno-rtti
#   COMPILE_FLAGS -fno-exceptions
#   COMPILE_FLAGS -fno-threadsafe-statics
#   COMPILE_FLAGS -nostdlib
# )

include(${CMAKE_SOURCE_DIR}/cmake/tflmicro.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ble.cmake)

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
)

pico_enable_stdio_usb(tcc_final 1)
pico_enable_stdio_uart(tcc_final 0)


pico_add_extra_outputs(tcc_final)

install(TARGETS tcc_final
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

