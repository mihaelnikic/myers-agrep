#include <iostream>
#include <fcntl.h>

#include "basic_algorithm.hpp"

int main(int argc, char const *argv[]) {
    const char P[] = "iihggbcndk";
    int fd = open("../files/DATA.16", O_RDONLY);
    if (fd < 0) {
        printf("error!");
        exit(1);
    }
    precompute(P);
    search(fd, 3, strlen(P));
    return 0;
}