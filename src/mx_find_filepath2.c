#include "ush.h"

char *mx_find_filepath2() {
    char *pathbuf;
           size_t n;

    n = confstr(_CS_PATH, NULL, (size_t) 0);
    pathbuf = malloc(n);
    if (pathbuf == NULL)
            mx_printerr("Eror filepath\n");
    confstr(_CS_PATH, pathbuf, n);
    return pathbuf;
}
