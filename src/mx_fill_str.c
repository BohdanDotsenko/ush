#include "ush.h"

static void fill_str(char **tok, int *i, char ***tmp, int *j) {
    (*tmp[(*j)]) = mx_strndup((*tok), (*i));
    (*tok) += (*i) + 2;
    (*i) = 0;
    (*j) += 1;
}

static char **get_null(char **tok, char **tmp, int j, int i) {
    if (*tok != NULL) {
        tmp[j] = mx_strndup((*tok), i);
        tmp[j+1] = NULL;
        return tmp;
    }
    else
        return NULL;
}

char **mx_fill_str(char *tok, int count) {
    char **tmp = malloc((count + 1) * sizeof(char *));
    int j = 0;
    int i = 0;

    for (; tok[i]; i++) {
        if (tok[i] == '\\' && tok[i+1] == '\'') {
            i += 1;
            continue;
        }
        if (tok[i] == '\'') 
            if (mx_cycle_for_quotes(tok, '\'', &i))
                continue;
        if (tok[i] == '\\' && tok[i+1] == '"') {
            i += 1;
            continue;
        }
        if (tok[i] == '"')
            if (mx_cycle_for_quotes(tok, '"', &i))
                continue;
        if (tok[i] == '\\' && tok[i + 1] == '&')
            continue;
        if (tok[i] == '&' && tok[i + 1] == '&') {
            fill_str(&tok, &i, &tmp, &j);
            i--;// new i += 2 in fill_str ===> new circle i++;
        }
    }
    return get_null(&tok, tmp, j, i);
}
