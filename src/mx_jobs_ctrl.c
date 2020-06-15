#include "ush.h"

int mx_free_job(t_job *job) {
    if (job == NULL) {
        return 1;
    }
    mx_strdel(&job->cmd);
    free(job);
    return 0;
}

int mx_pop_front_job(t_list **jobs) {
    t_list *cur = *jobs;

    kill(((t_job*)((*jobs)->data))->pid, SIGCONT);
    *jobs = (*jobs)->next; 
    mx_free_job((t_job*)cur->data);
    free(cur);
    return 0;
}

int mx_pop_job(t_list **jobs, int num) {
    if (jobs == NULL || *jobs == NULL)
        return 0;
    t_list *cur = *jobs;
    t_list *bef = NULL;

    if (num == 1)
        return mx_pop_front_job(jobs);
    for (int i = 1; cur != NULL && i <= num; i++) {
        // printf("pid is %d\n", ((t_job*)((*jobs)->data))->pid);
        if (i == num) {
            bef->next = cur->next;
            mx_free_job((t_job*)cur->data);
            free(cur);
            return 0;
        }
        bef = cur;
        cur = cur->next;
    }
    return 1;
}

int mx_jobs(t_list **jobs) {
   if (jobs == NULL || *jobs == NULL)
      return 0;
    t_list *tj = *jobs;
    t_job *cast = NULL;
 
    for (int i = 1; tj != NULL; tj = tj->next, i++) {
        printf("[%d] ", i);
        cast = (t_job*)tj->data;         
        mx_printint(cast->pid);
        mx_printstr(" ");
        mx_printstr(cast->cmd);
        mx_printstr("\n");
    }
    return 0;
}
