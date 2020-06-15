#include "ush.h"

static char *get_pwd(void) {
    char *cur_dir = getcwd(NULL, 1024);
    char *pwd = getenv("PWD");
    char *readlink = realpath(pwd, NULL);

    if (readlink && strcmp(readlink, cur_dir) == 0) {
        pwd = strdup(getenv("PWD"));
        free(cur_dir);
        free(readlink);
    }
    else {
        pwd = strdup(cur_dir);
        free(cur_dir);
    }
    return pwd;
}

static char *strfdup(char *str, int n) {
    char *res = malloc(strlen(str) - n + 1);
    int y = 0;

    for (int i = n; str[i]; i++) {
        res[y] = str[i];
        y++;
    }
    res[y] = '\0';
    return res;
}

static t_variables *get_variables(void) {
    t_variables *variables = NULL;
    extern char **environ;
    char *name = NULL;
    char *value = NULL;

    for (int i = 0; environ[i]; i++) {
        name = strndup(environ[i], mx_get_char_index(environ[i], '='));
        value = strfdup(environ[i], mx_get_char_index(environ[i], '=') + 1);
        mx_push_variable(&variables, name, value);
    }
    mx_push_variable(&variables, "?", "0");
    return variables;
}

static t_variables *get_export(void) {
    t_variables *variables = NULL;
    extern char **environ;
    char *name = NULL;
    char *value = NULL;

    for (int i = 0; environ[i]; i++) {
        name = strndup(environ[i], mx_get_char_index(environ[i], '='));
        value = strfdup(environ[i], mx_get_char_index(environ[i], '=') + 1);
        mx_push_variable(&variables, name, value);
    }
    return variables;
}

static void init_shlvl(t_shell *shell) {
    char *shlvl = getenv("SHLVL");
    char *result = NULL;
    int lvl = 0;

    if (shlvl == NULL)
        result = strdup("1");
    else {
        lvl = atoi(shlvl) + 1;
        result = mx_itoa(lvl);
    }
    mx_push_variable(&shell->variables, "SHLVL", result);
    setenv("SHLVL", result, 1);
}

static char **mx_init_builtin() {
    char **builtins = malloc(11 * sizeof(char *));

    builtins[0] = "pwd";
    builtins[1] = "env";
    builtins[2] = "which";
    builtins[3] = "echo";
	builtins[4] = "cd";
    builtins[5] = "fg";
    builtins[6] = "export";
    builtins[7] = "unset";
    builtins[8] = "exit";
    builtins[9] = "jobs";
    builtins[10] = NULL;
    return builtins;
}

void mx_init_shell(t_shell *shell) {
    setenv("PWD", getcwd(NULL, 0), 0); // инициализация pwd
    shell->env = environ;
    shell->pwd = get_pwd();
    shell->variables = get_variables();
    shell->export_variables = get_export();
    init_shlvl(shell);
    shell->builtins = mx_init_builtin();
    //printf("SHLVL %s\n", getenv("SHLVL"));
    //printf("PWD- %s\n", shell->pwd);
}
