#include "ush.h"

void tokenize(char *line, char ***tokens, int bufsize, int position) {
    char *token = NULL;

    token = strtok(line, ";");
    while (token != NULL) {
        if (token[0] == '\n' && token[1] == '\0') {
            token = strtok(NULL, ";");
            continue;
        }
        (*tokens)[position++] = mx_strtrim(token); // check for escape space;
        if (position >= bufsize) {
            bufsize += 64;
            *tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!(*tokens)) {
                fprintf(stderr, "u$h: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, ";");
    }
    (*tokens)[position] = NULL;
}

char **mx_tokcoma(char *line) {
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    // char *token;

    if (!tokens) {
        fprintf(stderr, "u$h: allocation error\n");
        exit(EXIT_FAILURE);
    }
    tokenize(line, &tokens, bufsize, position);
    if (tokens[0] == NULL) //free tokens;
        return NULL;
    return tokens;
}
