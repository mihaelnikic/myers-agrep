cmake_minimum_required(VERSION 3.8)
project(bioinformatics)

set(CMAKE_CXX_STANDARD 14)

#src/basic_algorithm.cpp
set(SOURCE_FILES src/block_algorithm.cpp src/main.cpp)
add_executable(bioinformatics ${SOURCE_FILES})