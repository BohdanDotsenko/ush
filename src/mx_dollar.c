#include "ush.h"

static bool alphabet(char x) {
    if ((x >= 60 && x <= 90)
    || (x >= 97 && x <= 122)) {
        return true;
    }
    else 
        return false;
}

static char *open_dollar(char *old_str) {
    char *env = NULL;
    char *resul_env = NULL;
    char *return_env = NULL;
    int i = 0;

    for (; alphabet(old_str[i]) == 1; i++);
    env = mx_strnew(i);
    for (int i = 0; alphabet(old_str[i]) == 1; i++) {
        env[i] = old_str[i];
    }
    if (env) {
        resul_env = getenv(env);
        if (resul_env != NULL) {
            return_env = mx_three_to_one(mx_strtrim(resul_env), " ", mx_strtrim(&old_str[i]));
            mx_strdel(&env);
            return return_env;
        }
    }
    return old_str;
}

char *mx_dollar(char *line) {
    int count = -1;
    char *work_str = NULL;
    char *env = NULL;
    char *full_str = NULL;

    if (line && mx_strlen(line) > 1) {
        count = mx_check_quotes(line, '$');

        if (count == 100)
            return line;
        if (count >= 0) {
            if (count > 0)
                work_str = mx_strndup(line, count -1);
            env = open_dollar(&line[count + 1]);
            if (work_str && env) {
                full_str = mx_three_to_one(mx_strtrim(work_str), " ", mx_strtrim(env));
                return full_str;
            }
            else if (!work_str) {
                full_str = mx_strdup(mx_strtrim(env));
                return full_str;
            }
        }
    }
    return line;
}
