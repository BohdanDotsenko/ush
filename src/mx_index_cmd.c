#include "ush.h"

int mx_index_cmd(char **cmd) {
    int flag = 0;
    int len;
    //find command in array
    for (int index = 0; cmd[index]; index++) {
        len = mx_strlen(cmd[index]);
        if (/*!mx_isspace(cmd[index][0]) && */cmd[index][0] != '=') {
            for (int j = 1; j < len; j++) {
                if (cmd[index][j] == '=') {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                flag = 0;
                continue;
            }
        }
        return index;
    }
    //find cmd[index] in builtins, programs
    return -1;
}
