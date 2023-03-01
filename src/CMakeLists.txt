cmake_minimum_required(VERSION 3.5)

project(TestYadro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_LIST
    "*.h"
    "*.cpp")

add_executable(TestYadro
    ${SRC_LIST})

target_include_directories(TestYadro PUBLIC
    ${INCLUDE_PATH})

message( ${INCLUDE_PATH})
