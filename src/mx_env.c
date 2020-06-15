#include "ush.h"

static int reparse(st_launch *l_inf, t_shell *shell, int n) {
    int i = n; 

    if (!l_inf->cmd_arr[i])
        return 1;
    for (int j = 0; j < i; j++)
        free(l_inf->cmd_arr[j]);
    while (l_inf->cmd_arr[i]) {
        l_inf->cmd_arr[i - n] = l_inf->cmd_arr[i];
        i++;
    }
    while (l_inf->cmd_arr[i - n]) {
        l_inf->cmd_arr[i - n] = NULL;
        i++;
    }
    mx_check_builtin(l_inf, shell);
    return 0;

}

static int flag_u(st_launch *l_inf) {
    if (!l_inf->cmd_arr[2]) {
        mx_printerr("usage: env [-u name] [arguments]\n");
        return -1;
    }
    if (getenv(l_inf->cmd_arr[2])) {
        unsetenv(l_inf->cmd_arr[2]);
        if (!l_inf->cmd_arr[3]) {
            print_env();
        }
        else
            return 3;        
    }
    return -1;
}

static int flag_P(st_launch *l_inf) {
    if (l_inf->cmd_arr[2] && l_inf->cmd_arr[3]) {
        setenv("PATH", l_inf->cmd_arr[2], 1);
        return 3;
    }
    else
       mx_printerr("usage: env [-P utilpath] [command]\n"); 
    return -1;
}

static int parse_flags(st_launch *l_inf) {
    if (l_inf->cmd_arr[1][0] != '-')
        return 1;
    if (strcmp(l_inf->cmd_arr[1], "--") == 0) {
        return 2;
    }
    if (mx_get_char_index(l_inf->cmd_arr[1], 'u') != -1) {
        return flag_u(l_inf);
    }
    else if (mx_get_char_index(l_inf->cmd_arr[1], 'i') != -1) {
        environ = NULL;
        return 2;
    }
    else if (mx_get_char_index(l_inf->cmd_arr[1], 'P') != -1) {
        return flag_P(l_inf);
    }
    return -1;
}

int mx_env(st_launch *l_inf, t_shell *shell) {
    char **new_env = environ;
    char *new_path = NULL;
    int n = 0;

    if (getenv("PATH"))
        new_path = strdup(getenv("PATH"));
    if (!l_inf->cmd_arr[1]) 
        print_env();
    else {
        n = parse_flags(l_inf);
        if (n > 0 && l_inf->cmd_arr[1])
            reparse(l_inf, shell, n);
    }
    environ = new_env;
    if (getenv("PATH"))
        setenv("PATH", new_path, 1);
    if (new_path)
        free(new_path);
    if (n < 0)
        return 1;
    return 0;
}
