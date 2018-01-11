#include <iostream>
#include <fcntl.h>

#include "basic_algorithm.hpp"
#include "block_algorithm.hpp"

int main(int argc, char const *argv[]) {
    //printf("%zu", sizeof(unsigned long long) * 8);
    const char P[] = "UYoqkaSnKqrcNAAIO21I0kWNMaNw@Ua5x5TRlbz8l6Z0odxP0zyFsGyhoXj5mLAg";
    int fd = open("../files/DATA.16", O_RDONLY);
    if (fd < 0) {
        printf("error!");
        exit(1);
    }
    int m = block_precompute(P);
    block_search(fd, 51, m);

//    basic_precompute(P);
//    basic_search(fd, 51, strlen(P));
    return 0;
}