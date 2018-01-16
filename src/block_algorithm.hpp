//
// Created by Luka Dulčić, Mihael Nikić.
//

#ifndef BIOINFORMATICS_BLOCK_ALGORITHM_H
#define BIOINFORMATICS_BLOCK_ALGORITHM_H

void block_precompute(const char *pattern, int m);
int block_search(int fd, int k, int m);

#endif //BIOINFORMATICS_BLOCK_ALGORITHM_H
