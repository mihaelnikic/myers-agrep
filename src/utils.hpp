//
// Created by mihael on 10.12.17..
//

#ifndef BIOINFORMATICS_UTILS_HPP
#define BIOINFORMATICS_UTILS_HPP
#define BUFFER_SIZE 128
#define NEW_LINE '\n'

#define PATTERN_ARG 1
#define K_ARG 2
#define TEXT_ARG 3
#define LETTER(x) ((x) == PATTERN_ARG ? "pattern" : ( (x) == K_ARG ? "k" : "text"))


int int_ceil(int k, int w) {
    return (k + w - 1) / w;
}

char* read_input(FILE *fp = stdin)
{
    char* input = NULL;
    char buffer[BUFFER_SIZE];

    size_t input_len = 0;
    size_t buffer_len = 0;

    do {
        fgets(buffer, BUFFER_SIZE, fp);

        buffer_len += strlen(buffer);
        input_len += buffer_len;

        input = (char*)realloc(input, input_len+1);
        strcat(input, buffer);

    } while ((buffer_len == BUFFER_SIZE - 1) && (buffer[BUFFER_SIZE - 2] != NEW_LINE));
    return input;
}

const char* read_arg_or_prompt(int index, int argc, char const *argv[], FILE *fp = stdin) {
    if (index < argc) { // TODO: random pattern kao što piše u README napraviti ako treba
        return argv[index];
    }
    char *input = (char*)malloc(300*sizeof(char));
    scanf ("%s",input);
    return input;

    //printf("Unesi vrijednost za %s\n", LETTER(index));
    return read_input(fp);
}

//int int_arg_or_prompt(int index, int argc, char const *argv[]) {
//    if (index <= argc) { // TODO: random pattern kao što piše u README napraviti ako treba
//        return atoi(argv[index]);
//    }
//    int k;
//    scanf ("%d", &k);
//    return k;
//}



#endif //BIOINFORMATICS_UTILS_HPP
