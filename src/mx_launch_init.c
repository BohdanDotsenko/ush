#include "ush.h"

static void tokenspace(char *line, char ***tokens, int bufsize, int position) {
    char *token = NULL;

    token = strtok(line, " ");
    while (token != NULL) {
        if (token[0] == '\n' && token[1] == '\0') {
            token = strtok(NULL, " ");
            continue;
        }
        (*tokens)[position++] = mx_strtrim(token); // check for escape space;
        if (position >= bufsize) {
            bufsize += 64;
            *tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!(*tokens)) {
                fprintf(stderr, "u$h: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }
    (*tokens)[position] = NULL;
}

static char **create_arr_cmd(char **command, int index) {
    char **cmd = NULL;
    int count = 0;
    int i = index;
    int n = 0;

    if (index >= 0) {
        for (; command[i]; i++)
            count++;
        cmd = malloc((count + 1) * sizeof(char *));
        for (i = index; command[i]; i++) {
            cmd[n++] = mx_strdup(command[i]);
        }
        cmd[n] = NULL;
    }
    return cmd;
}

st_launch *mx_launch_init(char *cmd) {
    int index = -1;
    // int ex;
    st_launch *l_inf = malloc(sizeof(st_launch));
    l_inf->filepath = NULL;
    l_inf->cmd_arr = NULL;
    l_inf->par = NULL;
    l_inf->type = -1;
    char **command = NULL;
    
    command = malloc(64 * sizeof(char *));

//create_arr_args
    tokenspace(cmd, &command, 64, 0);

    if (command[0] != NULL) {
        index = mx_index_cmd(command);
        // if (index == -1) 
            // mx_create_param (&st_launch->par);
        l_inf->cmd_arr = create_arr_cmd(command, index);
    }
//find cmd
    if (l_inf->cmd_arr) {
        if ((l_inf->type = mx_check_builtin(l_inf->cmd_arr)) == 1)
            return l_inf;
        else if ((l_inf->type = mx_find_filepath(l_inf->cmd_arr, &l_inf->filepath)) == 2)
            return l_inf;
        else {
            mx_printerr("ush: command ");
            mx_printerr(l_inf->cmd_arr[0]);
            mx_printerr("not found\n");
        }
    }
    return NULL;
}
