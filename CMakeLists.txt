cmake_minimum_required (VERSION 3.5)

project (TestYadro LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


set (INCLUDE_PATH
    "${CMAKE_SOURCE_DIR}/includes")

file(COPY "${CMAKE_SOURCE_DIR}/settings"
     DESTINATION "${TestYadro_BINARY_DIR}/src")

add_subdirectory (src)
