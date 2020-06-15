#include "ush.h"

static void check_dollar(char *str, int *kk) {
    int i = mx_check_quotes(str, '$');

    if (i > 0 && i != 100) {
        (*kk) += 1;
        check_dollar(&str[i + 1], &(*kk));
    }
    if ((*kk) == 0 || str[0] == '&') 
        (*kk) += 1;
}

static char *trim_dquotes(const char *str) {
    int begin = 0;
    int end = 0;
    char *result = NULL;

    if (str == NULL)
        return NULL;
    for (begin = 0; str[begin] == '"' && str[begin] != '\0'; begin++)
    ;
    for (end = mx_strlen(str);end > 0 && str[end - 1] == '"'; end--)
    ;

    for (int i = 0; str[i] == '"'; i++) {
        if (str[i + 1] == '\0')
            return NULL;
    }
    result = mx_strnew((end - begin) + 1);
    result = mx_strncpy(result, str + begin, end - begin);
    return result;
}

void mx_open_doll_trim_quotes(char ***command) {
    int kk = 0;

    for (int k = 0; (*command)[k]; k++) {
        char *str = mx_strtrim((trim_dquotes((*command)[k])));
        mx_strdel(&(*command)[k]);
        kk = 0;
        check_dollar(str, &kk);
        while (kk) {
            char *tmp = NULL;
            tmp = mx_dollar(str);////////NEWs
            // mx_printstr(tmp);
            //mx_printchar('\n');
            //mx_strdel(&cmd);
            str = mx_strdup(tmp);
            //mx_strdel(&tmp);
            //mx_printstr(cmd);
            //mx_printchar('\n');
            kk--;
        }
        (*command)[k] = mx_strdup(str);
        mx_strdel(&str);
        }
}
