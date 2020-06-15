#include "ush.h"

int  mx_start_builtin(st_launch *l_inf, t_list **jobs, t_shell *shell) {
    int *exit_st = mx_exit_status();

     for (int i = 0; shell->builtins[i]; i++) {
        if (strcmp(l_inf->cmd_arr[0], shell->builtins[i]) == 0) {
          if (strcmp("env", shell->builtins[i]) == 0)
               return mx_env(l_inf, shell);
          else if (strcmp("echo", shell->builtins[i]) == 0)
               return mx_echo(l_inf->cmd_arr);
          else if (strcmp("pwd", shell->builtins[i]) == 0)
               return mx_pwd(l_inf);
          else if (strcmp("cd", shell->builtins[i]) == 0)
               return mx_cd(l_inf);
          else if (strcmp("which", shell->builtins[i]) == 0)
               return mx_which(l_inf); 
          else if (strcmp("export", shell->builtins[i]) == 0)
               return mx_export(l_inf);
          else if (strcmp("unset", shell->builtins[i]) == 0)
               return mx_unset(l_inf);
          else if (strcmp("fg", shell->builtins[i]) == 0)
               return mx_fg(l_inf, jobs);
          else if (strcmp("jobs", shell->builtins[i]) == 0)
               return mx_jobs(jobs);
          else if (strcmp("exit", shell->builtins[i]) == 0)
               return mx_exit(l_inf);
        }
    }
    return *exit_st;
}
