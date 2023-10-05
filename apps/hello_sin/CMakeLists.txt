add_executable(hello_sin "")

target_include_directories(hello_sin
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

# set_target_properties(
#   hello_sin
#   PROPERTIES
#   COMPILE_FLAGS -fno-rtti
#   COMPILE_FLAGS -fno-exceptions
#   COMPILE_FLAGS -fno-threadsafe-statics
#   COMPILE_FLAGS -nostdlib
# )

add_subdirectory("src")

target_sources(
  hello_sin
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  hello_sin
  tflmicro
)

pico_enable_stdio_usb(hello_sin 1)
pico_enable_stdio_uart(hello_sin 0)


pico_add_extra_outputs(hello_sin)

install(TARGETS hello_sin
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

