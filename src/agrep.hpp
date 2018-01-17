//
// Created by Luka Dulčić.
//

#ifndef BIOINFORMATICS_AGREP_H
#define BIOINFORMATICS_AGREP_H

/**
 * Searches for matches of pattern in input file with minimal edit distance where edit distance is <= k.
 *
 * @param pattern pointer to pattern
 * @param m pattern length
 * @param k minimal edit distance
 * @param fd input file descriptor
 * @return minimal edit distance found in input file for pattern. If there is no matches for edit distance <= k returns -1.
 */
int search(const char *pattern, int m, int k, int fd);

#endif //BIOINFORMATICS_AGREP_H
