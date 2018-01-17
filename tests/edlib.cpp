//
// Created by Luka Dulčić.
//

/**
 * Since edlibAligner didn't suite us much to compare our agrep and edlib we created this file which is a simple wrapper
 * of edlibAlign function so we can invoke edlibAlign from command line in same fashion as agrep.
 */

#include <cstdio>
#include <cstring>
#include <edlib.h>
#include <cstdlib>
#include <vector>

int main(int argc, char const *argv[]) {
    int k = atoi(argv[2]);

    //read data
    FILE *file = fopen(argv[3], "r");
    const int buffSize = 4096;
    char buffer[buffSize];
    std::vector<char> data;
    int read;
    while (!feof(file)) {
        read = fread(buffer, sizeof(char), buffSize, file);
        for (int i = 0; i < read; ++i) {
            data.push_back(buffer[i]);
        }
    }

    FILE *out = argc == 5 ? fopen(argv[4], "w") : stdout;

    EdlibAlignResult result = edlibAlign(argv[1], strlen(argv[1]), data.data(), data.size(), edlibNewAlignConfig(k, EDLIB_MODE_HW, EDLIB_TASK_DISTANCE, NULL, 0));
    if (result.status == EDLIB_STATUS_ERROR) {
        printf("ERROR");
        return 1;
    }

    fprintf(out, "k=%d\n", result.editDistance);
    for (int j = 0; j < result.numLocations; ++j) {
        fprintf(out, "%d\n", result.endLocations[j]);
    }

    edlibFreeAlignResult(result);
    fclose(file);
    if (argc == 5) {
        fclose(out);
    }
}

