CC=gcc

agrep: src/main.cpp src/basic_algorithm.cpp src/block_algorithm.cpp
	$(CC) -O -o agrep src/main.cpp src/basic_algorithm.cpp src/block_algorithm.cpp