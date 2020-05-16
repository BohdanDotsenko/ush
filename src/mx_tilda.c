#include "ush.h"

static void tilda_minus(char **line) {
    char *oldpwd = getenv("OLDPWD");
    char *res = mx_strnew(mx_strlen(oldpwd) + mx_strlen((*line)) - 2);
    int r = 0;

    if (oldpwd != NULL) {
        mx_ex_join(&res, oldpwd, &r);
        for (int i = 2; (*line)[i]; i++)
            res[r++] = (*line)[i];  
        mx_strdel(line);
        (*line) = res;
    } 
}

static void tilda_plus(char **line) {
    char *pwd = getenv("PWD");
    char *res = mx_strnew(mx_strlen(pwd) + mx_strlen((*line)) - 2);
    int r = 0;

    if (pwd != NULL) {
        mx_ex_join(&res, pwd, &r);
        for (int i = 2; (*line)[i]; i++)
            res[r++] = (*line)[i];  
        mx_strdel(line);
        (*line) = res;
    }
}

static void tilda(char **line) {
    char *home = getenv("HOME");
    char *res = mx_strnew(mx_strlen(home) + mx_strlen((*line)) - 2);
    int r = 0;

    if (home != NULL) {
        mx_ex_join(&res, home, &r); 
        for (int i = 1; (*line)[i]; i++)
            res[r++] = (*line)[i];  
        mx_strdel(line);
        (*line) = res;
    }
}

static void tilda_user(char **line) {
    char *user = getenv("USER");
    char *res = mx_strnew(mx_strlen(user) + mx_strlen((*line) -1));
    int r = 0;

    if (mx_strncmp(user, &(*line)[1], mx_strlen(user)) == 0) {
        mx_ex_join(&res, "/Users/", &r);
        for (int i = 1; (*line)[i]; i++)
            res[r++] = (*line)[i];  
        mx_strdel(line);
        (*line) = res;
        //mx_strdel(&res); probably we  have leaks
    }
}

void mx_tilda(char **s) {
   // int value = 0;

    if ((*s)[0] == '~') {
        if (!mx_strncmp("~-/", (*s), 3) || !mx_strncmp("~-\n", (*s), 3))
            tilda_minus(s);
        else if (!mx_strncmp("~+/", (*s), 3) || !mx_strncmp("~+\n", (*s), 3))
            tilda_plus(s);
        else if (!mx_strncmp("~/", (*s), 2) || !mx_strncmp("~\n", (*s), 2))
            tilda(s);
        else if (mx_get_char_index((*s), '/'))
            tilda_user(s);
    }
   // while (mx_back_slesh(s, &value))
   //     mx_back_slesh(s, &value);
    mx_printstr((*s)); mx_printchar('\n'); /// example
}
