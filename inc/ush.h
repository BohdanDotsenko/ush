#ifndef USH_HEADER_H
#define USH_HEADER_H

#include "libmx.h"
// #include <dirent.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <sys/xattr.h>
// #include <sys/acl.h>
// #include <sys/ioctl.h>
// #include <pwd.h>
// #include <grp.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>


#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"

typedef struct s_cmd {
    char *cmd;
    struct s_cmd *or;
    struct s_cmd *and;
}              t_cmd;

typedef struct s_li {
    struct s_cmd *command; //tree
    struct s_li *next;
}              t_li;

typedef struct launch {
    char *filepath; //path to binary;
    char **cmd_arr; // env -ppp
    char **par; // a=b b=c ..
    int type; // no cmd found , builtin, binary      (alias, shell func)
}              st_launch;

int mx_check_line(char *line);
char *mx_exp_param(char *line);

void mx_printforest(t_li *forest);
t_li *mx_create_forest(char *line);
char **mx_tokcoma(char *line);

t_cmd *mx_treefill(char *token);
t_cmd *mx_create_cmd(char *cmd, int i);
void mx_pushtree(t_li **forest, char *tokcoma);

void mx_launch_cmd(t_li *forest);
st_launch *mx_launch_init(char *cmd);

//launch_init_utils
int mx_index_cmd(char **cmd);
int mx_check_builtin(char **cmd_arr);
int mx_find_filepath(char **cmd_arr, char **filepath);

//launchers
int mx_launch_builtin(st_launch *l_inf);
int mx_launcher(st_launch *l_inf); // for binary and builtin

void mx_ush_cd();

#endif
