cmake_minimum_required(VERSION 3.8)
project(bioinformatics)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/ukkonen_algorithm.cpp src/utils.hpp src/Block.cpp src/Block.hpp)
add_executable(bioinformatics ${SOURCE_FILES})