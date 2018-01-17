//
// Created by Martin Gluhak.
//

/**
 * Basic version of Myers agrep which works when pattern length is <= size of machine word.
 */

#include <cstdio>
#include <unistd.h>

#include "basic_algorithm.hpp"
#include "globals.hpp"

using namespace std;

uint64_t Peqb[SIGMA];

void basic_precompute(const char *pattern, int m) {
    uint64_t bitPos = 1;
    for (int i = 0; pattern[i] != '\0'; ++i) {
        Peqb[pattern[i]] |= bitPos;
        bitPos = bitPos << 1;
    }
}

int basic_search(int fd, int k, int m) {
    int score = m;
    uint64_t Mbit = ONE << (m - 1);
    uint64_t Pv = (uint64_t) -1;
    uint64_t Mv = 0;

    uint64_t Eq;
    uint64_t Xv, Xh;
    uint64_t Ph, Mh;
    ssize_t bytes_num;
    for (int buff = 0; (bytes_num = read(fd, buffer, MAX_BUF)) > 0; buff += bytes_num) {
        for (int i = 0; i < bytes_num; ++i) {
            Eq = Peqb[buffer[i]];
            Xv = Eq | Mv;
            Xh = (((Eq & Pv) + Pv) ^ Pv) | Eq;

            Ph = Mv | (~(Xh | Pv));
            Mh = Pv & Xh;

            if (Ph & Mbit) {
                score += 1;
            }
            if (Mh & Mbit) {
                score -= 1;
            }

            Ph <<= 1;
            Mh <<= 1;
            Pv = Mh | (~(Xv | Ph));
            Mv = Ph & Xv;

            if (score <= k) {
                if (score < k) {
                    k = score;
                    matches.clear();
                }
                matches.push_back(buff + i);
            }
        }
    }

    return k;
}
