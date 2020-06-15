#include "ush.h"

int mx_unset(st_launch *l_inf) {
    for (int i = 0; l_inf->cmd_arr[i]; i++){
        unsetenv(l_inf->cmd_arr[i]);
    }
    return 0;
}
