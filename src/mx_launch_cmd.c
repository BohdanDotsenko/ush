#include "ush.h"

void mx_launch_cmd(t_head *forest, t_shell *shell) {
    while(forest) {
        while (forest->command) {
            if (forest->command->cmd)
                mx_launch_init(forest->command->cmd, shell); // LAUNCHING CMD
            if (forest->command->or != NULL && shell->status != 0) {
                forest->command = forest->command->or;
               continue;
            }
            else if (shell->status == 0) {
                if (forest->command->and && !forest->command->or)
                    forest->command = forest->command->and;
                else if (!forest->command->and && forest->command->or) {
                    while (forest->command && !forest->command->and)
                        forest->command = forest->command->or;
                    if (forest->command)
                        forest->command = forest->command->and;
                }
                else if (!forest->command->and && !forest->command->or)
                    forest->command = NULL;
                continue;
            }
            else
                break;
        }
        forest = forest->next;
    }
}
