function(my_pico_btstack_make_gatt_header TARGET_LIB TARGET_TYPE GATT_FILE)
        find_package (Python3 REQUIRED COMPONENTS Interpreter)
        get_filename_component(GATT_NAME "${GATT_FILE}" NAME_WE)
        get_filename_component(GATT_PATH "${GATT_FILE}" PATH)
        set(GATT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
        set(GATT_HEADER "${GATT_BINARY_DIR}/${GATT_NAME}.h")
        set(TARGET_GATT "${TARGET_LIB}_gatt_header")

        add_custom_target(${TARGET_GATT} DEPENDS ${GATT_HEADER})
        add_custom_command(
                OUTPUT ${GATT_HEADER}
                DEPENDS ${GATT_FILE}
                WORKING_DIRECTORY ${GATT_PATH}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${GATT_BINARY_DIR} &&
                        ${Python3_EXECUTABLE} ${PICO_SDK_PATH}/lib/btstack/tool/compile_gatt.py ${GATT_FILE} ${GATT_HEADER} ${ARGN}
                VERBATIM)
        add_dependencies(${TARGET_LIB}
                ${TARGET_GATT}
                )
        target_include_directories(${TARGET_LIB} ${TARGET_TYPE}
                ${GATT_BINARY_DIR}
                )
endfunction()