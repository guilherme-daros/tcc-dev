target_sources(
    tcc_only_model
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/server_functions.cpp
)

add_subdirectory("models")