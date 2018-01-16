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

bool is_integer(const char *num) {
    for (int i = 0; num[i] != '\0' ; ++i) {
        if (!isdigit(num[i])) {
            return false;
        }
    }
    return true;
}

void print_matches(int edit_distance, FILE *fd) {
    fprintf(fd, "k=%d\n", edit_distance);
    std::vector<int >::iterator it;
    for (it = matches.begin(); it != matches.end(); ++it) {
        fprintf(fd, "%d\n", *it);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 3 || argc > 5) {
        printf("Invalid arguments. Usage: agrep [pattern] [k] [input_file] [output_file]\n");
        return 1;
    }

    // read pattern from args
    const char *pattern = argv[1];
    size_t m = strlen(pattern);

    // read k from args or default it to 0 if it's not provided
    if (!is_integer(argv[2])) {
        printf("Invalid value for k, %s\n", argv[2]);
        return 1;
    }
    int k = atoi(argv[2]);
    if (k >= m) {
        printf("k > pattern length\n");
        return 1;
    }

    // read file name from args
    int fin = open(argv[3], O_RDONLY);
    if (fin < 0) {
        perror("Cannot open file!");
        return 1;
    }

    FILE *fout = argc == 5 ? fopen(argv[4], "w") : stdout;

    //search for matches
    int edit_distance = search(pattern, m, k, fin);

    print_matches(edit_distance, fout);

    close(fin);
    //if out file is not stdout
    if (argc == 5) {
        fclose(fout);
    }

    return 0;
}
