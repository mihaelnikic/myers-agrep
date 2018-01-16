//
// Created by Luka Dulčić on 16/01/2018.
//

#include "agrep.hpp"
#include "globals.hpp"
#include "basic_algorithm.hpp"
#include "block_algorithm.hpp"

char buffer[MAX_BUF];

void search(const char *pattern, int m, int k, int fd) {
    if (m <= w) {
        basic_precompute(pattern, m);
        basic_search(fd, k, m);
    } else {
        block_precompute(pattern, m);
        block_search(fd, k, m);
    }
}
