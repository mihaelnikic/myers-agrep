#include <cstdio>
#include <unistd.h>

#include "basic_algorithm.hpp"
#include "globals.hpp"

using namespace std;

uint64_t Peq[SIGMA];
char buffer[MAX_BUF];

void basic_precompute(const char P[]) {
    uint64_t bitPos = 1;
    for (int i = 0; P[i] != '\0'; ++i) {
        Peq[P[i]] |= bitPos;
        bitPos = bitPos << 1;
    }
}

void basic_search(int fd, int k, int m) {
    int score = m;
    uint64_t Mbit = ONE << (m - 1);
    uint64_t Pv = (uint64_t)-1;
    uint64_t Mv = 0;

    uint64_t Eq;
    uint64_t Xv, Xh;
    uint64_t Ph, Mh;
    ssize_t bytes_num;
    for (int buff = 1; (bytes_num = read(fd, buffer, MAX_BUF)) > 0; buff += bytes_num) {
        for (int i = 0; i < bytes_num; ++i) {

            Eq = Peq[buffer[i]];
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
                printf("Match at: %d\n", buff + i);
            }
        }
    }
}
