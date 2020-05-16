#include "libmx.h"

void mx_swap_str_ptrs(char **arg1, char **arg2)
{
    char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}

