#include "ush.h"

static int comparecoma(char *line, int index) {
    if (line[index] != ';')
        return 0;
    return 1;
}


static int comparestr(char *line, int index) {
    if ((line[index] == '&' && line[index + 1] == '&') || (line[index] == '|' && line[index + 1] == '|'))
        return 1;
    return 0;
}

static int checkback(char *line) {
    for (int i = mx_strlen(line) - 1; line[i]; i--) {
        if (mx_isspace(line[i]))
            continue;
        if (i > 0 && comparestr(line, i - 1) == 1)
            return 1;
        else
            return 0;
    }
    return 0;
}

int mx_check_line(char *line) {
    int flag = 0;

    for (int i = 0; line[i]; i++) {
        if (mx_isspace(line[i]))
            continue;
        if ((comparestr(line, i) == 1 || comparecoma(line, i) == 1) && flag == 0)
            return 1;
        else if ((comparestr(line, i) == 1 || comparecoma(line, i) == 1) && flag == 1) {
            if (comparestr(line, i) == 1)
                i++;
            flag = 0;
            continue;
        }
        flag = 1;
    }
    return checkback(line);
}
