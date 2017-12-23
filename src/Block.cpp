//
// Created by mihael on 10.12.17..
//

#include <cstdlib>
#include <cstdio>
#include "Block.hpp"

Block::Block(int b_max, int y, const char* pattern) {
    _P = (uint64_t *)malloc(b_max * sizeof(uint64_t));
    _M = (uint64_t*)malloc(b_max * sizeof(uint64_t));

    int w = sizeof(uint64_t)*8;

    this->_Peq = (uint64_t**)malloc(ASCII * sizeof(uint64_t));
    for (int i = 0; i < ASCII; ++i) {
        this->_Peq[i] = (uint64_t*)calloc((unsigned int)b_max, sizeof(uint64_t));
        // calloc - inicijalizira sve elemente na 0, za razliku od mall
    }

    for (int block = 0;block<b_max;++block) {
        //printf ("block:%d\n",block);
        long long bitPos = 1;
        for (int j=block*w;j<(block+1)*w;++j){
            //printf ("j:%d, pattern[%d]=%c\n",j,j,pattern[j]);
            _Peq[ pattern[j] ][block] |= bitPos;
            bitPos = bitPos << 1;
        }
    }
}

uint64_t Block::P(int index) {
    return _P[index];
}

uint64_t Block::M(int index) {
    return _M[index];
}

uint64_t Block::Peq(int i, int j) {
    return _Peq[i][j];
}

int Block::advance_block(int b, char t, int h_in) {
    uint64_t Pv = P(b);
    uint64_t Mv = M(b);
    uint64_t Eq = Peq(t, b);

    printf ("Eq[blok=%d][char=%c]=%llu\n",b,t,Eq);
    printf ("Pv:%llu\nMv:%llu\n",Pv,Mv);

    uint64_t Xv,Xh;
    uint64_t Ph,Mh;

    int w = sizeof(uint64_t)*8;

    int h_out = 0;
    //int h_out = w;

    Xv = Eq | Mv;
    //add 1
    if(h_in < 0) {
        Eq |= 1;
    }
    Xh = ( ( (Eq & Pv) + Pv ) ^ Pv ) | Eq;

    Ph = Mv | ( ~ (Xh | Pv) );
    Mh = Pv & Xh;

    if ( Ph & (1ULL << (w - 1) ) ){
        h_out += 1;
    }
    if ( Mh & (1ULL << (w - 1) ) ){
        h_out -= 1;
    }

    Ph <<= 1;
    Mh <<= 1;
    //add 2.
    if (h_in < 0) {
        Mh |= 1;
    }
    else if(h_in > 0) {
        Ph |= 1;
    }
    Pv = Mh | ( ~ ( Xv | Ph ) );
    Mv = Ph & Xv;

    set_P(b, Pv);
    set_M(b, Mv);

    printf ("advance blok za char %c :%d\n",t,h_out);

    return h_out;
}

void Block::set_P(int index, uint64_t value) {
    _P[index] = value;
}

void Block::set_M(int index, uint64_t value) {
    _M[index] = value;
}

void Block::init_block(int b) {
    set_P(b, ( 1ULL << (unsigned long long)(sizeof(uint64_t)*8) ) - 1);
    set_M(b, 0);
}

Block::~Block() {
    free(_P);
    free(_M);
    free(_Peq);
}
