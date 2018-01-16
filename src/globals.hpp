//
// Created by Luka Dulčić on 05/01/2018.
//

#include <stdint.h>
#include <cstring>

#ifndef BIOINFORMATICS_PATTERN_PARSE_H
#define BIOINFORMATICS_PATTERN_PARSE_H

#define SIGMA 128
#define MAX_BUF 2048
static uint64_t ONE = 1;
static int w = sizeof(uint64_t) * 8;
extern char buffer[MAX_BUF];

#endif //BIOINFORMATICS_PATTERN_PARSE_H
