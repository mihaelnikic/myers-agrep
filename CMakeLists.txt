cmake_minimum_required(VERSION 3.8)
project(bioinformatics)

set(CMAKE_CXX_STANDARD 14)

set(G++_EDLIB_LINK_FLAGS "-ledlib")
set(CMAKE_EXE_LINKER_FLAGS "${G++_EDLIB_LINK_FLAGS}" )

set(SOURCE_FILES src/basic_algorithm.cpp src/block_algorithm.cpp src/main.cpp src/agrep.cpp src/agrep.hpp)
set(EDLIB_FILES tests/edlib.cpp)
add_executable(bioinformatics ${SOURCE_FILES})
add_executable(edlib ${EDLIB_FILES})