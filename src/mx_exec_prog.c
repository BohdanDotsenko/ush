#include "ush.h"

void mx_set_ctrl_term(pid_t pid) {
    if (!isatty(0))
        return;
    if (tcsetpgrp(0, pid) < 0) {
        mx_printstr(strerror(errno));
        mx_printstr(" tcsetpgrp\n");
    }
    if (tcsetpgrp(1, pid) < 0) {
        mx_printstr(strerror(errno));
        mx_printstr(" tcsetpgrp\n");
    }
}

static void print_error(st_launch *l_inf) {                                       
    struct stat path_stat;                                                        
                                  
    stat(l_inf->cmd_arr[0], &path_stat);                                          
    if (S_ISDIR(path_stat.st_mode)) {                                             
        mx_printerr("ush: ");                                                     
        mx_printerr(l_inf->cmd_arr[0]);                                           
        mx_printerr(": Is a directory\n");                                        
    }                                                                             
    else if (errno == ENOENT) {                                                   
        mx_printerr("ush: command ");                                             
        mx_printerr(l_inf->cmd_arr[0]);                                           
        mx_printerr(" not found\n");                                              
    }                                                                             
    else {                                                                        
        mx_printerr("ush: ");                                                     
        mx_printstr(strerror(errno));                                             
        mx_printchar('\n');                                                       
    }                                                                             
}

void signal_for_child(void) {
    signal(SIGINT, SIG_DFL); // C-c
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL); // for move of terminals
}

int mx_exec_prog(st_launch *l_inf, t_list **jobs) {
    int status = 0;
    pid_t pid;
    char *fp = (l_inf->filepath != NULL) ? l_inf->filepath : l_inf->cmd_arr[0];

    pid = fork();
    if (pid == 0) { // Child process
        signal_for_child();
        setpgid(getpid(), getpid());
        mx_set_ctrl_term(getpid());
        if (execve(fp, l_inf->cmd_arr, environ) == -1) { 
            print_error(l_inf);
            exit(-1);
        }
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        mx_set_ctrl_term(getpid());
        if (WIFSTOPPED(status) == true)
            mx_add_to_list(l_inf, pid, jobs, status);
    }
    return WEXITSTATUS(status);
}
