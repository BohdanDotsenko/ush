#include "ush.h"

static int parse_flags(st_launch *l_inf) {
    if (!l_inf->cmd_arr[1] || strcmp(l_inf->cmd_arr[1], "--") == 0)
        return 0;
    if (l_inf->cmd_arr[1][0] == '-' && l_inf->cmd_arr[1][1]) {
        if (mx_get_char_index(l_inf->cmd_arr[1], 'P') != -1) {
            mx_printstr(getcwd(NULL, 0));
            mx_printchar('\n');
        }
        if (mx_get_char_index(l_inf->cmd_arr[1], 'L') != -1) {
            return 0;
        }
    }
    else 
        mx_printerr("pwd: bad option\n");

    return 1;
}

int mx_pwd(st_launch *l_inf) {
    char *pwd = getenv("PWD");

    if (parse_flags(l_inf)) {
        
    }
    else {
        pwd = getenv("PWD");
        mx_printstr(pwd);
        if (pwd)
            mx_printchar('\n');
        return 1;
    }
    return 1;
}
