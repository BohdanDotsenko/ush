#include "ush.h"

void mx_ex_join(char **res, char *full_str, int *r) {

    for (int i = 0; full_str[i]; i++) {
        (*res)[(*r)] = full_str[i];
        (*r) += 1;
        (*res)[(*r)] = '\0';
    }
}
