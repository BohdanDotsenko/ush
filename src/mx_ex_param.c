#include "ush.h"

static int count_par(char *line) {
    int count = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i+1] && line[i] == '$' && line[i+1] == '{') {
            if (i > 0 && line[i-1] == '\\') //think global
                continue;
            i += 2;
            if (line[i] == '}')
                return -1;
            for ( ; line[i] && line[i] != '}'; i++) {
                 if (line[i] == '`' || line[i] == ' ' || (line[i+1] && line[i] == '$'
                 && (line[i+1] == '{' || line[i+1] == '(')))
                    return -1;
            }
            if (line[i] && line[i] == '}')
                count++;
            else
                return -1;           
        }
    }
    return count;
}

static char* arr_from_j_to_i(char *line, int beg, int end) {
    int len = end - beg;
    char *res = mx_strnew(len);
    char *result = NULL;

    for (int i = 0; i < len;)
        res[i++] = line[beg++];
    result = mx_strtrim(res);
    mx_strdel(&res);
    if (mx_strlen(result) > 0)
        return result;
    return NULL;
}

static char *len_par(char *line, int *len) {
    int beg = 0;
    char *param = NULL;

    for (int i = 0; line[i]; i++) {
        if (line[i+1] && line[i] == '$' && line[i+1] == '{') {
            beg = i + 2;
            while (line[i] && line[i] != '}')
                i++;
            if (line[i] && line[i] == '}') {
                (*len) -= i - beg - 3;
                param = arr_from_j_to_i(line, beg, i);
                if (param && getenv(param)) {
                    (*len) += mx_strlen(getenv(param));
                }
            }
        }
     }
     return param;
}

static void ex_join(char *line, char *old_str, char **new_str) {
    int i = 0;
    char *cup = NULL;

    for (int y = 0; line[y]; y++) {
        if (line[y+1] && line[y] == '$' && line[y+1] == '{') {
            cup = getenv(old_str);
            if (cup != NULL) {
                for (int j = 0; cup[j]; j++)
                    (*new_str)[i++] = cup[j];
                i += mx_strlen(old_str) + 3;
            }
        }
        (*new_str)[i++] = line[y];
    }
}

char *mx_ex_param(char *line) {
    char *res = NULL;
    int len = mx_strlen(line);
    int count = count_par(line);
    char *result = NULL;

    if (count > 0) {
        result = len_par(line, &len);
        if (result) {
            res = mx_strnew(len);
            ex_join(line, result, &res);
        }
    }
    else if (count == -1)
        return NULL;
    else 
        res = line;
    return res;
}
