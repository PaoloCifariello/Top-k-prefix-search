cmake_minimum_required(VERSION 3.0)
project(Top-k-prefix-search)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE sources lib/*.hpp lib/*.cpp src/*.cpp src/*.hpp test/*.cpp test/*.hpp)

add_executable(Top-k-prefix-search ${sources})
target_compile_options(Top-k-prefix-search PUBLIC -std=c++14 -O3 -Wall -Wfloat-conversion)