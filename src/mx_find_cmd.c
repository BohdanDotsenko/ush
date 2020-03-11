#include "ush.h"

int mx_check_builtin(char **cmd_arr) {
    char *builtins[8];

    builtins[0] = NULL;
    builtins[0] = "pwd";
    builtins[1] = "cd";
    builtins[2] = "env";
    builtins[3] = NULL;

    for(int i = 0; builtins[i]; i++)
        if (strcmp(builtins[i], cmd_arr[0]) == 0) {
            return 1;
        }
    return -1;
}

int mx_find_filepath(char **cmd_arr, char **filepath) {
    char *path = mx_strdup(getenv("PATH"));
    char *token = NULL;
    DIR *dptr;
    struct dirent *ds;

    if (path)
        token = strtok(path, ":");
    for (; token; token = strtok(NULL, ":")) {
        if ((dptr = opendir(token)) != NULL) {
            for (; (ds = readdir(dptr)) != NULL;) {
                if (strcmp(ds->d_name, cmd_arr[0]) == 0) { // mx_strcmp ne rabotaet na tochke;
                    *filepath = mx_strjoin(token, "/");
                    *filepath = mx_strjoin(*filepath, ds->d_name); // need free in mx_strjoin;
                    return 2; // 2 means == type = binary;
                }
            }
        closedir(dptr);
        }
    }
    return -1;
}
