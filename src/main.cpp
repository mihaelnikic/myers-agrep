//
// Created by Luka Dulčić, Mihael Nikić, Martin Gluhak.
//

#include <cstdio>
#include <cctype>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>

#include "agrep.hpp"
#include "globals.hpp"

/**
 * Returns true if num is integer.
 *
 * @param num pointer to string.
 */
bool is_integer(const char *num) {
    for (int i = 0; num[i] != '\0'; ++i) {
        if (i == 0 && (num[i] == '-' || num[i] == '+')) {
            continue;
        }
        if (!isdigit(num[i])) {
            return false;
        }
    }
    return true;
}

/**
 * Prints minimal edit distance and all positions (0-based) at which those matches exist in input text.
 *
 * @param edit_distance minimal edit distance found by search
 * @param fd output file descriptor.
 */
void print_matches(int edit_distance, FILE *fd) {
    fprintf(fd, "k=%d\n", edit_distance);
    std::vector<int>::iterator it;
    for (it = matches.begin(); it != matches.end(); ++it) {
        fprintf(fd, "%d\n", *it);
    }
}

/**
 * Main function of program, parses and validates arguments, calls agrep search function and print output of search.
 *
 * @return 0 on success
 */
int main(int argc, char const *argv[]) {
    // first 3 arguments are mandatory, [output_file] is optional
    if (argc < 4 || argc > 5) {
        printf("Invalid arguments. Usage: agrep [pattern] [k] [input_file] [output_file]\n");
        return 1;
    }

    // read pattern from args
    const char *pattern = argv[1];
    int m = strlen(pattern);

    // read k from args
    if (!is_integer(argv[2])) {
        printf("Invalid value for k, %s\n", argv[2]);
        return 1;
    }
    int k = atoi(argv[2]);
    k = k == -1 ? m : k; //if k=-1 start with k=m
    if (k > m) {
        printf("k > pattern length\n");
        return 1;
    }

    // read file name from args
    int fin = open(argv[3], O_RDONLY);
    if (fin < 0) {
        perror("Cannot open file!");
        return 1;
    }

    // opens output_file if user provided it, otherwise default output to stdout
    FILE *fout = argc == 5 ? fopen(argv[4], "w") : stdout;

    //search for matches
    int edit_distance = search(pattern, m, k, fin);

    print_matches(edit_distance, fout);

    close(fin);
    // if out file is not stdout
    if (argc == 5) {
        fclose(fout);
    }

    return 0;
}
