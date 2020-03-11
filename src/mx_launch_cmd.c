#include "ush.h"

static int mx_launch_menu(char *cmd) {
    st_launch *l_inf = mx_launch_init(cmd); // create cmd_arr // create param_arr // find type // find filepath 
    int status = 0;

    if (l_inf) {
        if (l_inf->type == 1 || l_inf->type == 2)
            status = mx_launcher(l_inf);
    }
    else
        status = 127; // echo $?;
    return status;
}

void mx_launch_cmd(t_li *forest) {
    int status;

    while(forest) {
        while (forest->command) {
            if (forest->command->cmd)
                status = mx_launch_menu(forest->command->cmd); // LAUNCHING CMD
            if (forest->command->or != NULL && status != 0) {
                forest->command = forest->command->or;
                continue;
            }
            else if (status == 0) {
                forest->command = forest->command->and;
                continue;
            }
            else
                break;
        }
        forest = forest->next;
    }
}
