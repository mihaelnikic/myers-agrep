#include <iostream>
#include <fcntl.h>
#include <zconf.h>

#include "basic_algorithm.hpp"
#include "block_algorithm.hpp"
#include "globals.hpp"

char buffer[MAX_BUF];

bool is_integer(const char *num) {
    for (int i = 0; num[i] != '\0' ; ++i) {
        if (!isdigit(num[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Invalid arguments. Usage: agrep [pattern] [k] [input_file]\n");
        return 1;
    }

    // read pattern from args
    const char *pattern = argv[1];
    size_t m = strlen(pattern);

    // read k from args or default it to 0 if it's not provided
    if (!is_integer(argv[2])) {
        printf("Invalid value for k, %s\n", argv[2]);
        return 1;
    }
    int k = atoi(argv[2]);
    if (k > m) {
        printf("k > pattern length\n");
        return 1;
    }

    // if there is no file name in args default input to stdin (assume input is piped)
    int fd = argc == 4 ? open(argv[3], O_RDONLY) : STDIN_FILENO;
    if (fd < 0) {
        perror("Cannot open file!");
        return 1;
    }

    if (m <= w) {
        basic_precompute(pattern, m);
        basic_search(fd, k, m);
    } else {
        block_precompute(pattern, m);
        block_search(fd, k, m);
    }

    return 0;
}