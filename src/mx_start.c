#include "ush.h"

void mx_start_builtin(st_launch *l_inf, t_shell *shell) {
     for (int i = 0; shell->builtins[i]; i++) {
        if (strcmp(l_inf->cmd_arr[0], shell->builtins[i]) == 0) { // find biultin in finction (mx_init_shell)    // add your builtins
           // shell->status = your_function(l_inf->cmd_arr, shell); // your function where you work with builtins/   you need return shell->statur = 0; if Ok!
           mx_printstr("Builtins");
        }
    }
}


void mx_start(st_launch *l_inf, t_shell *shell) { 
    if (l_inf->type == 1)
        mx_start_builtin(l_inf, shell);
}
