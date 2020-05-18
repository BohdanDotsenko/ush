#include "ush.h"

static char *read_line(void) {
    char *tmp = NULL;
    size_t bufsize = 0;

    getline(&tmp, &bufsize, stdin);
    return tmp;
}
void mx_loop(t_head *head) {
    char *line = NULL;
    int status = 0;
    t_shell *shell = (t_shell *)malloc(sizeof(t_shell));

    // mx_init_shell(shell);
    while (1) {
        mx_printstr("u$h> ");
        line = read_line(); 
        line[strlen(line)-1] = '\0';
        if (line) {
            if (mx_check_line(line) == 1) {
                mx_printstr("syntax error\n");
                status = 258;// errno
                continue;
            }
        // line = valid ${}
            line = mx_ex_param(line);
            if (!line) {
                mx_printerr("error param {}\n");// after error
                continue;
            }
           //mx_tilda(&line);
           //mx_printstr(line);
            head = mx_create_head(line);
            
            //mx_printforest(head);
            if (line != NULL) {
                mx_launch_cmd(head, shell);
                continue;
            }
        }
    }
}
