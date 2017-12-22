//
// Created by mihael on 10.12.17..
//

#ifndef BIOINFORMATICS_BLOCK_HPP
#define BIOINFORMATICS_BLOCK_HPP


#include <cstdint>

#define ASCII 130

class Block {
private:
    uint64_t* _P; // 1...bmax
    uint64_t* _M; // 1...bmax
    uint64_t** _Peq; // [ASCII, 1...bmax]
public:
    explicit Block(int b_max, int y, const char* pattern);
    ~Block();
    uint64_t P(int index);
    uint64_t M(int index);
    uint64_t Peq(int i, int j);

    void set_P(int index, uint64_t value);
    void set_M(int index, uint64_t value);

    void init_block(int b);
    int advance_block(int b, char t, int hin);
};


#endif //BIOINFORMATICS_BLOCK_HPP
