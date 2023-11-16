target_sources(
    tcc_final
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/server_functions.cpp
)

add_subdirectory("models")