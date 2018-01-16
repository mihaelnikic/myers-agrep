//
// Created by mihael on 16.01.18..
//

//
// Created by mihael on 16.01.18..
//
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <fcntl.h>

#include "../src/basic_algorithm.hpp"
#include "../src/block_algorithm.hpp"
#include "../src/globals.hpp"

char buffer[MAX_BUF];

bool is_integer(const char *num) {
    for (int i = 0; num[i] != '\0' ; ++i) {
        if (!isdigit(num[i])) {
            return false;
        }
    }
    return true;
}
int agrep_test(int argc, char const *argv[]) {
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
    int fd = open(argv[3], O_RDONLY);
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
}

int main(int argc, char const *argv[]) {
    struct rusage usage;
    struct timeval start, end;
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    agrep_test(argc, argv);
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;

    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    printf("Run time: %ld.%lds\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    return 0;
}
