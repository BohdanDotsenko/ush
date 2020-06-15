#include "ush.h"

int mx_cont_job_by_name(t_list **jobs, char *cmd) {
    int len = strlen(&cmd[1]);
    t_list *cur = *jobs;
    int status;

    for (int i = 1; cur != NULL; i++) {
        if (strncmp(&cmd[1], ((t_job*)(cur->data))->cmd, len) == 0) {
            kill(((t_job*)(cur->data))->pid, SIGCONT);
            mx_set_ctrl_term(((t_job*)(cur->data))->pid);
            waitpid(((t_job*)(cur->data))->pid, &status, WUNTRACED);
            mx_set_ctrl_term(getpid());
            if (WIFSTOPPED(status) == true)
                return 0;
            else if (WIFEXITED(status) == true) {
                mx_pop_job(jobs, i);
                return 0;
            }
        }
        cur = cur->next;
    }
    return -1;
}

int mx_cont_job(t_list **jobs, int num) {
    t_list *cur = *jobs;
    int status = 0;

    for (int i = 1; cur != NULL && i <= num; i++) {
        if (i == num) {
            kill(((t_job*)(cur->data))->pid, SIGCONT);
            mx_set_ctrl_term(((t_job*)(cur->data))->pid);
            waitpid(((t_job*)(cur->data))->pid, &status, WUNTRACED);
            mx_set_ctrl_term(getpid());
            if (WIFSTOPPED(status) == true)
                return 0;
            else if (WIFEXITED(status) == true) {
                mx_pop_job(jobs, i);
                return 0;
            }
        }
        cur = cur->next;
    }
    return 1;
}

int mx_fg(st_launch *l_inf, t_list **jobs) {
    if (jobs == NULL || *jobs == NULL)
        return 0;
    if (l_inf->cmd_arr[1] == NULL)
        return mx_cont_job(jobs, 1);
    if (l_inf->cmd_arr[1][0] != '%')
       return 0; 
    else if(isdigit(l_inf->cmd_arr[1][1]) == true)
        return mx_cont_job(jobs, atoi(&l_inf->cmd_arr[1][1]));
    else if(l_inf->cmd_arr[1][1])
        return mx_cont_job_by_name(jobs, l_inf->cmd_arr[1]);
    else
        return 0;
}


t_job *mx_create_job(st_launch *l_inf, pid_t pid, int status) {
    t_job *job = (t_job*)malloc(sizeof(t_job));
    char *cmd = NULL;
    int len = 0;
    int i;

    for (i = 0; l_inf->cmd_arr[i]; i++)
        len += mx_strlen(l_inf->cmd_arr[i]);
    cmd = mx_strnew(len + i + 1); // printf fails without +1, but printstr not
    for (i = 0, len = 0; l_inf->cmd_arr[i]; i++) {
        for (int j = 0; l_inf->cmd_arr[i][j]; j++) {
            cmd[len++] = l_inf->cmd_arr[i][j];
        }
        cmd[len++] = ' ';
    }
    job->cmd = cmd;
    job->pid = pid;
    job->status = status;
    return job;
}

void mx_add_to_list(st_launch *l_inf, pid_t pid, t_list **jobs, int status) {
    t_job *job = mx_create_job(l_inf, pid, status);
    int i = 0;

    mx_push_back(jobs, job);
    for(t_list *j = *jobs; j; j = j->next, i++);
    printf("[%d]  + %d suspended %s\n", i, job->pid, job->cmd);
}
