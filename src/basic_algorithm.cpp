#include <cstdio>
#include <unistd.h>

#include "basic_algorithm.hpp"
#include "pattern_parse.hpp"

#define MAX_BUF 2048

using namespace std;

unsigned WORD Peq[SIGMA];
char buffer[MAX_BUF];
unsigned WORD ONE = 1;

void precompute(const char P[]) {
    long long bitPos = 1;
    for (int i = 0; P[i] != '\0'; ++i) {
        Peq[P[i]] |= bitPos;
        bitPos = bitPos << 1;
    }
}

void search(int fd, int k, int m) {
    int score = m;
    unsigned WORD Mbit = ONE << (m - 1);
    WORD Pv = (ONE << m) - 1;
    WORD Mv = 0;

    WORD Eq;
    WORD Xv, Xh;
    WORD Ph, Mh;
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
