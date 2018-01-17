//
// Created by Luka Dulčić, Mihael Nikić.
//

#ifndef BIOINFORMATICS_BLOCK_ALGORITHM_H
#define BIOINFORMATICS_BLOCK_ALGORITHM_H

/**
 * Precomputes Eq vectors for given pattern and ASCII alphabet for all possible blocks.
 *
 * @param pattern pointer to pattern.
 * @param m pattern length.
 */
void block_precompute(const char *pattern, int m);

/**
 * Searches for matches with minimal edit distance using block version of myers algorithm which works for all possible
 * pattern lengths.
 *
 * @param fd input file descriptor.
 * @param k minimal edit distance
 * @param m pattern length
 * @return minimal edit distance found in input file for pattern. If there is no matches for edit distance <= k returns -1.
 */
int block_search(int fd, int k, int m);

#endif //BIOINFORMATICS_BLOCK_ALGORITHM_H
