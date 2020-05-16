#include "ush.h" 

static int valid_operator(char *line, int i) {
    int t = 0;
    int b = 0;
    
    for (int j = i; line[j] && line[j] == '|'; j++)
        t++;
    if (t && t != 2)
        return 1;
    for (int j = i; line[j] && line[j] == '&'; j++) {
        b++;
    if (b && t != 2)
        return 1;
    }
    if ((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|' && line[i + 1] == '|'))
        return 1;
    return 0;
}

int mx_check_line(char *line) {
    int flag = 0;

    for (int i = 0; line[i]; i++) {
        if (mx_isspace(line[i]))
            continue;
        if ((valid_operator(line, i) == 1) && flag == 0) {
            return 1;
        }
        else if ((valid_operator(line, i) == 1) && flag == 1) {
            i++;
            flag = 0;
            continue;
        }
        flag = 1;
    }
    return 0;
}
