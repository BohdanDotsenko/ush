#include "ush.h"

void print_env() {
    int i = 0;
    if (environ == NULL)
        return;
    while (environ[i]) {
        mx_printstr(environ[i]);
        mx_printchar('\n');
        i++;
    }
}
