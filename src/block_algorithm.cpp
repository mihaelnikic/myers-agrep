//
// Created by mihael on 10.12.17..
//

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "block_algorithm.hpp"
#include "pattern_parse.hpp"

char buffer[MAX_BUF];
int w;
int b_max;
uint64_t *P;
uint64_t *M;
uint64_t **Peq;
uint64_t Mbit;

static inline int min(const int x, const int y) {
    return x < y ? x : y;
}

int block_precompute(const char pattern[]) {
    int pattern_length = (int) strlen(pattern);
    w = sizeof(uint64_t) * 8;
    b_max = pattern_length / w + (pattern_length % w == 0 ? 0 : 1);
    Mbit = Mbit = ONE << (w - 1);

    P = (uint64_t *) malloc(b_max * sizeof(uint64_t));
    M = (uint64_t *) malloc(b_max * sizeof(uint64_t));

    Peq = (uint64_t **) malloc((SIGMA + 1) * sizeof(uint64_t));
    for (int i = 0; i < SIGMA; ++i) {
        Peq[i] = (uint64_t *) calloc(b_max, sizeof(uint64_t));
        // calloc - inicijalizira sve elemente na 0, za razliku od mall
    }

    for (int block = 0; block < b_max; ++block) {
        //printf ("block:%d\n",block);
        uint64_t bitPos = 1;
        for (int j = block * w; j < min(pattern_length, (block + 1) * w); ++j) {
            //printf ("j:%d, pattern[%d]=%c\n",j,j,pattern[j]);
            Peq[pattern[j]][block] |= bitPos;
            bitPos = bitPos << 1;
        }
    }

    return pattern_length;
}

static inline void init_block(int b) {
    //set_P(b, ( 1ULL << (unsigned long long)(sizeof(uint64_t)*8) ) - 1);
    P[b] = (uint64_t)-1;//TODO provjeri da ovo ni 0 !!!!! (stavi -1 ?)
    M[b] = 0;
}

static inline int advance_block(int b, char c, int h_in) {
    uint64_t Pv = P[b];
    uint64_t Mv = M[b];
    uint64_t Eq = Peq[c][b];

    //printf ("Eq[blok=%d][char=%c]=%llu\n",b,t,Eq);
    //printf ("Pv:%llu\nMv:%llu\n",Pv,Mv);

    uint64_t Xv,Xh;
    uint64_t Ph,Mh;

    int h_out = 0;
    //int h_out = w;

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

    //printf ("advance blok za char %c :%d\n",t,h_out);

    return h_out;
}

static inline int ceilDiv(const int x, const int y) {
    return x % y ? x / y + 1 : x / y;
}

void block_search(int fd, int k, int m) {
    //int y = k / w + (k % w == 0 ? 0 : 1);
    int y = ceilDiv(k, w) - 1;
    printf("y=%d bmax=%d\n", y, b_max);

    auto score = (int *) malloc(b_max * sizeof(int));
    //Block block(b_max, y, P);
    // init block
    for (int b = 0; b <= y; ++b) {
        init_block(b);
        score[b] = (b + 1) * w;
    }

    int W = m % w; //Mozda krivo

    ssize_t bytes_num;
    int carry;
    char c;
    for (int buff = 1; (bytes_num = read(fd, buffer, MAX_BUF)) > 0; buff += bytes_num) {
        for (int i = 0; i < bytes_num; ++i) {
            c = buffer[i];
            //printf("%c", c);
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

//            if (buff + i == 228033) {
//                printf("y=%d, b_max=%d, score=%d", y, b_max, score[y]);
//            }
            if (y == (b_max - 1) && score[y] <= k) {

                printf("%dMatch at: %d\n", score[y], buff + i);
            }
        }
    }

    free(score);
}