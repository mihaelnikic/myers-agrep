//
// Created by Luka Dulčić.
//

#include <vector>
#include "agrep.hpp"
#include "globals.hpp"
#include "basic_algorithm.hpp"
#include "block_algorithm.hpp"

char buffer[MAX_BUF];
std::vector<int> matches;

int search(const char *pattern, int m, int k, int fd) {
    int edit_distance = k;
    if (m <= w) {
        basic_precompute(pattern, m);
        edit_distance = basic_search(fd, k, m);
    } else {
        block_precompute(pattern, m);
        edit_distance = block_search(fd, k, m);
    }
    return edit_distance;
}
