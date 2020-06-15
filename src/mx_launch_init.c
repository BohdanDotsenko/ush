#include "ush.h"

static void auditor(int *bufsize, char ****toks) {
    (*bufsize) += 64;
    **toks = realloc((**toks), (*bufsize) * sizeof(char *));
    if (!(**toks)) {
        fprintf(stderr, "u$h: allocation error\n");
        exit(EXIT_FAILURE);
    }
}

static void tokensize(char *line, char ***toks, int bufsize, int position) {
    char *token = NULL;
    char *line_cp = mx_strtrim(line);
    int check = 0;

    check = mx_check_quotes(&line_cp[check], ' ');
    while (check > 0 && check != 100) {
        token = mx_strndup(line_cp, check);
        line_cp = mx_strdup(line_cp + check + 1);
        if (check > 0)
            (*toks)[position++] = mx_trim_token(token);
        if (position >= bufsize)
            auditor(&bufsize, &toks);
        check = mx_check_quotes(line_cp, ' ');
    }
    if (check == -1)
        return;
    else if (check == 100) {
        (*toks)[position] = mx_strdup(mx_trim_token(line_cp));
    }
    else if ((*toks))
        mx_strdel(&line); mx_strdel(&line_cp);
    (*toks)[position + 1] = NULL;
}


st_launch *mx_launch_init(char *cmd, t_shell *shell) {

    st_launch *l_inf = malloc(sizeof(st_launch)); // в отдельную функцию 
    l_inf->filepath = NULL;
    l_inf->cmd_arr = NULL;
    l_inf->par = NULL;
    char **command = NULL;
    command = malloc(64 * sizeof(char *));
// exp params
    cmd = mx_ex_param(cmd); // &
    if (!cmd) {
        mx_printerr("error param ${}\n");
        return NULL;
    }
// create_arr_args
    tokensize(cmd, &command, 64, 0);
    mx_open_doll_trim_quotes(&command);
    l_inf->cmd_arr = command;
//find cmd 
    if (l_inf->cmd_arr)
        mx_check_builtin(l_inf, shell); // 1 = builtin
    // add free alocated memmory because builtin already executed.
    //mx_printstr(l_inf->cmd_arr[0]);
    return NULL;
}
