//
// Created by Luka Dulčić, Mihael Nikić, Martin Gluhak.
//

#include <stdint.h>
#include <cstring>
#include <vector>

#ifndef BIOINFORMATICS_PATTERN_PARSE_H
#define BIOINFORMATICS_PATTERN_PARSE_H

#define SIGMA 128
#define MAX_BUF 2048
static uint64_t ONE = 1;
static int w = sizeof(uint64_t) * 8;
extern char buffer[MAX_BUF];
extern std::vector<int> matches;
#endif //BIOINFORMATICS_PATTERN_PARSE_H
