#include "ush.h"

static char *read_line(void) {
    char *tmp = NULL;
    size_t bufsize = 0;
    int i = 0;
    int rc;

    if (getline(&tmp, &bufsize, stdin) < 0) {
        mx_printchar('\n');
        exit(0);
    }
    return tmp;
}

static void signal_for_parent(void) {
    signal(SIGINT, SIG_IGN); // C-c
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN); // for move of terminals
    signal(SIGTTOU, SIG_IGN);
}

void mx_loop_echo(t_head *head) {
    char *line = NULL;
    t_shell *shell = (t_shell *)malloc(sizeof(t_shell));
    bzero(shell, sizeof(t_shell));

    mx_init_shell(shell);
    line = read_line();
        // printf("%s len=%d\n", line, mx_strlen(line));

    if (!mx_strtrim(line))
        return;
    line[strlen(line)-1] = '\0';
    if (line) {
        if (mx_check_line(line) == 1) {
            mx_printstr("syntax error\n");
        }
        mx_pwd_replace(&line);
    
        head = mx_create_head(line);
        
    if (!head) { 
        }
        if (line != NULL && head) {
            mx_launch_cmd(head, shell);
        }

    }
}

void mx_loop(t_head *head) {
    char *line = NULL;
    int status = 0;
    t_shell *shell = (t_shell*)malloc(sizeof(t_shell));
    bzero(shell, sizeof(t_shell));
    setvbuf(stdout, NULL, _IONBF, 0); //for printf

    mx_init_shell(shell);
    signal_for_parent();
    while (1) {
        mx_printstr("u$h> ");
        line = read_line();
        if (!mx_strtrim(line))// new
            continue;// new
        line[strlen(line) - 1] = '\0';
        if (line) {
            if (mx_check_line(line) == 1) {
                mx_printstr("syntax error\n");
                status = 258;// errno
                continue;
            }
            mx_pwd_replace(&line);
        
            head = mx_create_head(line);
            
            //mx_printforest(head);
            if (!head) { // new
                continue;
            }
            if (line != NULL && head) {
                mx_launch_cmd(head, shell);
                continue;
            }

        }
    }
}
