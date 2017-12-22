//
// Created by mihael on 10.12.17..
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "utils.hpp"
#include "Block.hpp"

#define PATTERN_ARG 1
#define K_ARG 2
#define TEXT_ARG 3


int main(int argc, char const *argv[]) {
    auto pattern = read_arg_or_prompt(PATTERN_ARG, argc, argv);
    int k = atoi(read_arg_or_prompt(K_ARG, argc, argv));
    auto T = read_arg_or_prompt(TEXT_ARG, argc, argv); // TODO: napraviti da čita iz fajla

    //Ucita i \n !!!
    int n = strlen(T)-1;
    int m = strlen(pattern)-1;

    //T[n-1] = '\0';
    //pattern[m-1] = '\0';

    printf ("Pattern:%s\n",pattern);
    printf ("k:%d\n",k);
    printf ("Text:%s\n",T);


    printf ("%d %d\n",n,m);

    int w = sizeof(long long)*8;
    int y = int_ceil(k, w); // ceil
    if (y == 0){
        y = 1;
    }
    int b_max = int_ceil(m, w); // ceil
    printf ("w:%d\n",w);
    printf ("bmax:%d\n",b_max);
    printf ("y:%d\n",y);

    auto score = (int*)malloc(b_max * sizeof(int));
    for (int b = 0; b < y; ++b) {
        score[b] = b * w; // TODO: ili samo b ili nesto trece?
    }

    Block block(b_max, y);
    // init block
    for (int b = 0; b < y; ++b) {
        block.init_block(b);
    }

    printf ("Pocinje petlja\n");

    int W = m % w; //Mozda krivo
    printf ("Izracunat W:%d\n",W);

    for (int j = 0; j < n + W; ++j) { //TODO: w isto što i veliko W? Nije isto
        printf ("T[j]=%c\n",T[j]);
        int carry = 0;
        for (int b = 0; b < y; ++b) { // TODO: y ukljucen ili ne?
            score[b] += (carry = block.advance_block(b, T[j], carry)); // TODO: znak pridruživanja ili ==?
        }

        if ((score[y - 1] - carry <= k) && (y < b_max) && ((block.Peq(T[j], y) & 1) || (carry < 0))) {
            y += 1;
            block.init_block(y - 1);
            score[y - 1] = score[y - 2] + w - carry + block.advance_block(y - 1, T[j], carry);
        }
        else {
            while (score[y - 1] >= (k + w)) {
                y -= 1;
            }
        }

        if ((y == b_max) && (score[y - 1] <= k)) { // TODO: znak pridruživanja ili ==? | y == b_max ILI (y-1) == bmax
            printf("Match at: %d\n", j - w); //TODO: w isto što i veliko W?
        }
    }

    free(score);
    return 0;
}