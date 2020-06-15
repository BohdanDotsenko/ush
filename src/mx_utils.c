#include "ush.h"

int mx_print_exit(void) {
    int *exit_st = mx_exit_status();

    mx_printint(*exit_st);
    mx_printchar('\n');
    return 0;
}

bool is_backslash_char(char c) {
    if (c > 97 && c < 102)
        return true;
    else if (c == 'n')
        return true;
    else if (c == 'r')
        return true;
    else if (c == 't')
        return true;
    else if (c == 'v')
        return true;
    return false;
}
