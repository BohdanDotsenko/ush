#include"ush.h"

char *path_constructor(char *path, char *fname) {
    int len = mx_strlen(fname);
    char *path_with_slash = mx_strjoin(path, "/");
    char tmp[len];
    char *res = NULL;

    if (fname[len - 1] != '/')
        res = mx_strjoin(path_with_slash, fname);
    else {
        mx_strncpy(tmp, fname, len - 1);
        tmp[len - 1] = '\0';
        res = mx_strjoin(path_with_slash, tmp);
    }

    mx_strdel(&path_with_slash);
    return res;
}

int mx_strarr_len(char **strarr) {
    int len = 0;

    if (!strarr)
        return len;
    while (strarr[len])
        len++;
    return len;
}

char *mx_build_path(char *pwd, char *fname) {
    char *full_path = NULL;

    if (fname[0] == '/')
        full_path = mx_strdup(fname);
    else
        full_path = path_constructor(pwd, fname);

    return full_path;
}


char *mx_strarr_to_str(char **strarr, char *delim) {
    char *str = NULL;
    char *tmp = NULL;

    for (int i = 0; strarr && strarr[i]; i++) {
        tmp = mx_strjoin(str, strarr[i]);
        mx_strdel(&str);
        if (strarr[i + 1]) {
            str = mx_strjoin(tmp, delim);
            mx_strdel(&tmp);
        }
        else
            str = tmp;
    }

    return str;
}

char  *includes_link_P(char *destination) {
    char **split = mx_strsplit(destination, '/');
    char *path = NULL;
    char *full_path = NULL;

    while (split[0]) {
        path = mx_strarr_to_str(split, "/");
        if (destination[0] == '/')
            full_path = mx_strjoin("/", path);
        else
            full_path = mx_build_path(getenv("PWD"), path);
        if (mx_check_link(&path, full_path)) {
            mx_del_strarr(&split);
            return full_path;
        }
        mx_strdel(&split[mx_strarr_len(split) - 1]);
        mx_strdel(&full_path);
    }
    free(split);
    return NULL;
}
