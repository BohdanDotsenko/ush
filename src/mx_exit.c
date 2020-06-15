#include "ush.h"

static bool is_dig_str(char *str) {
    int i;

    for (i = 0; str[i] && isdigit(str[i]); i++);
    if (!str[i])
        return true;
    return false;

}

int mx_exit(st_launch *l_inf) {
    int *exit_st = mx_exit_status();

    if (!l_inf->cmd_arr[1]) {
        exit(*exit_st);
    }
    if (l_inf->cmd_arr[2]){
        mx_printerr("exit: too many arguments\n");
        return 1;
    }
    if (l_inf->cmd_arr[1] && is_dig_str(l_inf->cmd_arr[1])) {
        exit(atoi(l_inf->cmd_arr[1]));
    }
    
    return 0;
}
