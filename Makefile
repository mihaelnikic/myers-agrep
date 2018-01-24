CC=g++

agrep: src/main.cpp src/basic_algorithm.cpp src/block_algorithm.cpp
	$(CC) -O -o agrep -std=c++11 src/main.cpp src/basic_algorithm.cpp src/block_algorithm.cpp src/agrep.cpp
