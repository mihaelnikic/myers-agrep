//
// Created by mihael on 10.12.17..
//

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "block_algorithm.hpp"
#include "globals.hpp"

char buffer[MAX_BUF];
int w;
int W;
int b_max;
uint64_t *P;
uint64_t *M;
uint64_t **Peq;
uint64_t Mbit;

inline int div_ceil(int x, int y) {
    return x / y + (x % y == 0 ? 0 : 1);
}

int block_precompute(const char pattern[]) {
    int pattern_length = (int) strlen(pattern);
    w = sizeof(uint64_t) * 8;
    b_max = div_ceil(pattern_length, w);
    W = w * b_max - pattern_length;
    Mbit = ONE << (w - 1);

    P = (uint64_t *) malloc(b_max * w);
    M = (uint64_t *) malloc(b_max * w);

    Peq = (uint64_t **) malloc((SIGMA + 1) * sizeof(uint64_t *));

    uint64_t bitPos;
    for (int c = 0; c < SIGMA; ++c) {
        Peq[c] = (uint64_t *) calloc(b_max, w);
        for (int block = 0; block < b_max; ++block) {
            bitPos = (uint64_t) 1;
            for (int i = block * w; i < (block + 1) * w; ++i) {
                if (i >= pattern_length || pattern[i] == c) {
                    Peq[c][block] |= bitPos;
                }
                bitPos <<= 1;
            }
        }
    }

    return pattern_length;
}

inline void init_block(int b) {
    P[b] = (uint64_t)-1;//Ones
    M[b] = 0;
}

inline int advance_block(int b, char c, int h_in) {
    uint64_t Pv = P[b];
    uint64_t Mv = M[b];
    uint64_t Eq = Peq[c][b];

    uint64_t Xv,Xh;
    uint64_t Ph,Mh;

    int h_out = 0;

    Xv = Eq | Mv;
    //add 1
    if(h_in < 0) {
        Eq |= ONE;
    }
    Xh = ( ( (Eq & Pv) + Pv ) ^ Pv ) | Eq;

    Ph = Mv | ( ~ (Xh | Pv) );
    Mh = Pv & Xh;

    if ( Ph & Mbit ){
        h_out += 1;
    }
    if ( Mh & Mbit ){
        h_out -= 1;
    }

    Ph <<= 1;
    Mh <<= 1;
    //add 2.
    if (h_in < 0) {
        Mh |= ONE;
    }
    else if(h_in > 0) {
        Ph |= ONE;
    }
    Pv = Mh | ( ~ ( Xv | Ph ) );
    Mv = Ph & Xv;

    P[b] = Pv;
    M[b] = Mv;

    return h_out;
}

void block_search(int fd, int k, int m) {
    int y = div_ceil(k, w) - 1;

    auto score = (int *) malloc(b_max * sizeof(int));
    for (int b = 0; b <= y; ++b) {
        init_block(b);
        score[b] = (b + 1) * w;
    }

    ssize_t bytes_num;
    int carry;
    char c;
    for (int buff = 1; (bytes_num = read(fd, buffer, MAX_BUF)) > 0; buff += bytes_num) {
        for (int i = 0; i < bytes_num; ++i) {
            c = buffer[i];
            carry = 0;
            for (int b = 0; b <= y; ++b) {
                carry = advance_block(b, c, carry);
                score[b] += carry;
            }

            if ((score[y] - carry <= k) && (y < (b_max - 1)) && ((Peq[c][y + 1] & ONE) || (carry < 0))) {
                y += 1;
                init_block(y);
                score[y] = score[y - 1] + w - carry + advance_block(y, c, carry);
            } else {
                while (score[y] >= (k + w)) {
                    y -= 1;
                }
            }

            if (y == (b_max - 1) && score[y] <= k) {
                printf("Match at: %d\n", buff + i - W);
            }
        }
    }

    free(score);
    free(P);
    free(M);
    free(Peq);
}