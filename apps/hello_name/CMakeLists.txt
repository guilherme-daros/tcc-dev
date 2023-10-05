add_executable(hello_name "")

target_include_directories(
        hello_name 
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory("src")

target_sources(
  hello_name
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
        hello_name 
        pico_stdlib
)

pico_enable_stdio_usb(hello_name 1)
pico_enable_stdio_uart(hello_name 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_name)

install(TARGETS hello_name
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/images
)