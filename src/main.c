#include "ush.h"

char *mx_get_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    return line;
}



int main () {
    int status = 1;
    char *line = NULL;
    t_li *forest = NULL;
    extern char **environ;
    // char **set = NULL;
    // mx_print_strarr(environ, "\n");

    while (status) {
        mx_printstr("u$h> ");
        line = mx_get_line();
        if (line) {
            if (mx_check_line(line) == 1) {
                mx_printerr("syntax error\n");
                status = 258; // errno;
                continue;
            }
            line = mx_exp_param(line);
            forest = mx_create_forest(line);
        }
        mx_launch_cmd(forest);
        //execute aliases
    }
}
