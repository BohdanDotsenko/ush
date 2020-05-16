#include "ush.h"

void mx_printforest(t_head *forest) {
    while (forest) {
        while (forest->command) {
            if (forest->command->cmd) {
                mx_printstr(forest->command->cmd);
                mx_printchar('\n');
            }
            if (forest->command->or != NULL) {
                forest->command = forest->command->or;
                continue;
            }
            else {
                forest->command = forest->command->and;
                continue;
            }
        }
        forest = forest->next;
    }
}

t_head *mx_create_head(char *line) {
    char **tok = NULL;
    t_head *forest = NULL;

    tok = mx_tok(line); // разбиваем строчку на ;

    if (tok) {
        for (int i = 0; tok[i]; i++) {
            if (forest == NULL) {
                forest = malloc(sizeof(t_head));
                forest->command = mx_treefull(tok[i]);
                forest->next = NULL;
            }
            else
                mx_pushtree(&forest, tok[i]);
        }
    }
    //mx_printforest(forest);
    return forest;
}
