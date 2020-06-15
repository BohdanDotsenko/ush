#include "ush.h"

char *mx_three_to_one(char *first_part, char *text, char *second_part) {
    int len1 = mx_strlen(first_part);
    int len2 = mx_strlen(text);
    int len3 = mx_strlen(second_part);
    char *result = mx_strnew(len1 + len2 + len3);

    mx_strcat(result, first_part);
    mx_strcat(result, text);
    mx_strcat(result, second_part);
    return result;
}

t_list **mx_jobs_list(void) {
   static t_list *jobs = NULL; 

   return &jobs;
}

int *mx_exit_status(void) {
    static int exit_status = 0;

    return &exit_status;
}

int mx_check_builtin(st_launch *l_inf, t_shell *shell) {
    int *exit_st = mx_exit_status();
    t_list **jobs = mx_jobs_list();

    for(int i = 0; shell->builtins[i]; i++)
        if (strcmp(shell->builtins[i], l_inf->cmd_arr[0]) == 0) {
            *exit_st = mx_start_builtin(l_inf, jobs, shell);
            return 0;
        }
    mx_find_filepath(l_inf->cmd_arr, &l_inf->filepath, NULL);
    if (l_inf->filepath == NULL && l_inf->cmd_arr != NULL) {
        for (int i = 0; l_inf->cmd_arr[0][i]; i++) {
            if (l_inf->cmd_arr[0][i] == '/') {
                *exit_st = mx_exec_prog(l_inf, jobs);
                return -1;
            }
        }
    }
    *exit_st = mx_exec_prog(l_inf, jobs);
    return -1;
}
