#ifndef USH_H
#define USH_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libmx.h"
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <math.h>
#include <dirent.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

extern char **environ;

#define BUFSIZE 1024
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)

extern char **environ;

typedef struct s_variables {
    char *name;
    char *value;
    struct s_variables *next;
}                t_variables;    

typedef struct s_shell {
    t_variables *variables;
    t_variables *export_variables;
    char *pwd;
    int status;
    char **builtins;
    char **env;
}               t_shell;

typedef struct s_cmd {
    char *cmd;
    struct s_cmd *or;
    struct s_cmd *and;
}              t_cmd;

typedef struct s_head {
    struct s_cmd *command;
    struct s_head *next;
}               t_head;

typedef struct s_launch {
    char *filepath; //path to binary;
    char **cmd_arr; // env -ppp
    char **par; // a=b b=c ..
    int type; // no cmd found , builtin, binary      (alias, shell func)
}              st_launch;

typedef struct s_job {
    char *cmd;
    pid_t pid;
    int status;
}               t_job;


void mx_loop(t_head *head);
t_head *mx_create_head(char *line);
char **mx_tok(char *line);
void mx_loop_echo(t_head *head);
// void mx_first_cat(char *line);

t_cmd *mx_treefull(char *line);
t_cmd *mx_create_cmd(char *cmd, int i);
void mx_pushtree(t_head **forest, char *tok);
void mx_printforest(t_head *forest);
int mx_check_line(char *line);
char *mx_ex_param(char *line);
void mx_tilda(char **line);
void mx_ex_join(char **res, char *full_str, int *r);
int mx_back_slesh(char **str, int* value);
int mx_check_quotes(char *line, char delim);
int mx_cycle_for_quotes(char *line, char delim, int *i);
char *mx_trim_token(char *str);
char **mx_fill_str(char *tok, int count);
void mx_launch_cmd(t_head *forest, t_shell *shell);
st_launch *mx_launch_init(char *cmd, t_shell *shell);
char *mx_three_to_one(char *first_part, char *text, char *second_part);
char *mx_dollar(char *line);
void mx_pwd_replace(char **iline);
void mx_open_doll_trim_quotes(char ***command);

//builtins
int mx_check_builtin(st_launch *l_inf, t_shell *shell);
void mx_start(st_launch *l_inf, t_shell *shell); // builtins and path
int  mx_start_builtin(st_launch *l_inf, t_list **jobs, t_shell *shell);

// env
int mx_env(st_launch *l_inf, t_shell *shell);
void print_env();

// pwd
int mx_pwd(st_launch *l_inf);

//cd
int mx_cd(st_launch *l_inf);
char *mx_build_path(char *pwd, char *fname);
int mx_strarr_len(char **strarr);
char *mx_strarr_to_str(char **strarr, char *delim);
char mx_check_link(char **path, char *full_path);
char *path_constructor(char *path, char *fname);
char *includes_link_P(char *destination);

// init t_shell info
void mx_init_shell(t_shell *shell);
void mx_push_variable(t_variables **list, void *name, void *value);

// fork and exec
int mx_exec_prog(st_launch *l_inf, t_list **jobs);

// echo
int mx_echo(char **argv);
bool is_backslash_char(char c);
int mx_print_exit(void);

// export, import and exit
int mx_export(st_launch *l_inf);
int mx_unset(st_launch *l_inf);
int mx_exit(st_launch *l_inf);

// which
int mx_which(st_launch *l_inf);
int mx_find_filepath(char **cmd_arr, char **filepath, void *flags);
char *mx_find_filepath2();

int mx_fg(st_launch *l_inf, t_list **jobs);
t_list** mx_jobs_list(void);
int mx_free_job(t_job *job);
int mx_jobs(t_list **jobs);
void mx_add_to_list(st_launch *l_inf, pid_t pid, t_list **jobs, int status);
void mx_set_ctrl_term(pid_t pid);
int mx_pop_job(t_list **jobs, int num);
int mx_cont_job_by_name(t_list **jobs, char *cmd);

// exit
int *mx_exit_status(void);

#endif
