#include "ush.h"

static char **mx_init_builtin() {
    char **builtins = malloc(8 * sizeof(char *));

    builtins[0] = "pwd";
    builtins[1] = "cd";
    builtins[2] = "env";
    builtins[3] = NULL;
    return builtins;
}

int ush_pwd(char **cmd_arr) {
    mx_printstr(cmd_arr[0]);
    mx_printchar('\n');
    return 0;
}
int ush_cd(char **cmd_arr) {
    if (false)
    mx_printstr(cmd_arr[0]);
    mx_ush_cd();
    return 1;
}
int ush_env(char **cmd_arr) {
    mx_printstr(cmd_arr[0]);
    mx_printchar('\n');
    return 2;
}
int mx_launch_builtin(st_launch *l_inf) {
    int (*builtin_f[]) (char **) = {
        &ush_pwd,
        &ush_cd,
        &ush_env
    };
    char **builtins = mx_init_builtin();
    int status;

    for (int i = 0; builtins[i]; i++) {
        if (strcmp(l_inf->cmd_arr[0], builtins[i]) == 0) {
            status = builtin_f[i](l_inf->cmd_arr);
            // mx_printint(status);
        }
    }
    return 0;
}

int mx_launcher(st_launch *l_inf) {
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (l_inf->type == 1)
            mx_launch_builtin(l_inf);
        if (l_inf->type == 2)
            if (execvp(l_inf->filepath, l_inf->cmd_arr) == -1) {
                perror("ush mx_launch_binary: 51");
            }
        exit(errno);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        wpid = waitpid(pid, &status, WUNTRACED);
    }
    return WEXITSTATUS(status);
}
