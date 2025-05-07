cmake_minimum_required(VERSION 3.31)
project(Game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Game)

add_subdirectory(vendor)
add_subdirectory(src)