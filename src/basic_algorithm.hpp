//
// Created by Martin Gluhak.
//

#ifndef BIOINFORMATICS_BASIC_ALGORITHM_H
#define BIOINFORMATICS_BASIC_ALGORITHM_H

/**
 * Precomputes Eq vectors for given pattern and ASCII alphabet.
 *
 * @param pattern pointer to pattern.
 * @param m pattern length.
 */
void basic_precompute(const char *pattern, int m);

/**
 * Searches for matches with minimal edit distance using basic version of myers algorithm which works for pattern
 * lengths <= size of machine word.
 *
 * @param fd input file descriptor.
 * @param k minimal edit distance
 * @param m pattern length
 * @return minimal edit distance found in input file for pattern. If there is no matches for edit distance <= k returns -1.
 */
int basic_search(int fd, int k, int m);

#endif //BIOINFORMATICS_BASIC_ALGORITHM_H
