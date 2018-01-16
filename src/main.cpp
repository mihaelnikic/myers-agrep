#include <cstdio>
#include <cctype>
#include <fcntl.h>
#include <cstdlib>

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

int main(int argc, char const *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Invalid arguments. Usage: agrep [pattern] [k] [input_file]\n");
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
    if (k > m) {
        printf("k > pattern length\n");
        return 1;
    }

    // if there is no file name in args default input to stdin (assume input is piped)
    int fd = open(argv[3], O_RDONLY);
    if (fd < 0) {
        perror("Cannot open file!");
        return 1;
    }
    
    search(pattern, m, k, fd);

    return 0;
}
