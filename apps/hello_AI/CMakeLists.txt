add_executable(hello_AI "")

target_include_directories(hello_AI
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

# set_target_properties(
#   hello_AI
#   PROPERTIES
#   COMPILE_FLAGS -fno-rtti
#   COMPILE_FLAGS -fno-exceptions
#   COMPILE_FLAGS -fno-threadsafe-statics
#   COMPILE_FLAGS -nostdlib
# )

include(${CMAKE_SOURCE_DIR}/cmake/tflmicro.cmake)

add_subdirectory("src")

target_sources(
  hello_AI
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  hello_AI
  tflmicro
)

pico_enable_stdio_usb(hello_AI 1)
pico_enable_stdio_uart(hello_AI 0)


pico_add_extra_outputs(hello_AI)

install(TARGETS hello_AI
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)

