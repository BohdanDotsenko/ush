#include"ush.h"

char mx_check_link(char **path, char *full_path) {
    struct stat st;

    mx_strdel(path);
    if (lstat(full_path, &st) != -1 && MX_IS_LNK(st.st_mode))
        return 1;

    return 0;
}

static char includes_link(char *destination) {
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
            mx_strdel(&full_path);
            return 1;
        }
        mx_strdel(&split[mx_strarr_len(split) - 1]);
        mx_strdel(&full_path);
    }
    free(split);
    return 0;
}


static int change_dir(st_launch *l_inf, char *path) {
    char *link = NULL;
    if (!chdir(path)) {
        if (getenv("OLDPWD") && getenv("PWD") && strcmp(getenv("OLDPWD"), getenv("PWD")) != 0)
            setenv("OLDPWD", getenv("PWD"), 1);
        if (getcwd(NULL, 0))
            setenv("PWD", getcwd(NULL, 0), 1);
        if (strcmp(l_inf->cmd_arr[1], "-P") != 0 &&
            strcmp(l_inf->cmd_arr[1], "-") != 0 && includes_link(path)){
            link = mx_strdup(includes_link_P(path));
            setenv("PWD", link, 1);
            free(link);
        }
        return 0;
    }
    else {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        return 1;
    }
}

static int old_cd(st_launch *l_inf) {
    if (getenv("OLDPWD")) {
            mx_printstr(getenv("OLDPWD"));
            mx_printchar('\n');
            return change_dir(l_inf, getenv("OLDPWD"));
    }   
    else {
        mx_printerr("cd: OLDPWD not set\n");
        return 1;
    }
}

int mx_cd(st_launch *l_inf) {
    if (!l_inf->cmd_arr[1] || l_inf->cmd_arr[1][0] == '~'){
        if (getenv("HOME"))
            return change_dir(l_inf, getenv("HOME"));
    }
    else if (strcmp(l_inf->cmd_arr[1], "-") == 0) {
        return old_cd(l_inf);
    }
    else if (strcmp(l_inf->cmd_arr[1], "-s") == 0){
        if (includes_link(l_inf->cmd_arr[2])) {
            mx_printerr("cd: not a directory\n"); 
            return 1;
        }
        else 
            return change_dir(l_inf, l_inf->cmd_arr[2]);
    }
    else if (l_inf->cmd_arr[1] && strcmp(l_inf->cmd_arr[1], "-P") ==0)
        return change_dir(l_inf, l_inf->cmd_arr[2]);
    return change_dir(l_inf, l_inf->cmd_arr[1]);
}
