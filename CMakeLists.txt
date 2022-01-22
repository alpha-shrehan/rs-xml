cmake_minimum_required(VERSION 3.0.0)
project(rsxml VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_compile_definitions(RSXML_EXPORTS)

add_library(
    rsxml SHARED
    "./rsxml.c"
    "./src/attr_t.c"
    "./src/rsutils.c"
    "./src/xml_t.c"
    "./src/xml_lexer.c"
)

add_custom_command(TARGET rsxml POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/build/librsxml.dll"
        ${CMAKE_CURRENT_BINARY_DIR}/tests/librsxml.dll)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
