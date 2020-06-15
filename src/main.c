#include "ush.h"


int main(int args, char* argv[]) {
    t_head head;

    memset(&head, 0, sizeof(t_head));
    if (args && argv) {
    //    mx_loop(&head);
    (!(isatty(0))) ? mx_loop_echo(&head) : mx_loop(&head);
    }
}
