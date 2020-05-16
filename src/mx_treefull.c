#include "ush.h"

static char **create_artree(char *tok) {
    int i = 0;
    int count = 1;

    for (; tok[i]; i++) {
        if (tok[i] == '\\' && tok[i+1] != '\'')
            i += 2;
        if (tok[i] == '\'') 
            if (mx_cycle_for_quotes(tok, '\'', &i))
                continue;
        if (tok[i] == '\\' && tok[i+1] != '"')
            i += 2;
        if (tok[i] == '"')
            if (mx_cycle_for_quotes(tok, '"', &i))
                continue;
        if (tok[i] == '\\' && tok[i + 1] == '&')
            continue;
        if (tok[i] == '&' && tok[i + 1] == '&') 
            count += 1;
    }
    return mx_fill_str(tok, count);
}

   /*
    int count = 1;
    int i = 0;
    int j = 0;
    char **tmp = NULL;

    for (i = 0; tok[i]; i++)
        if (tok[i] == '&' && tok[i + 1] == '&')
            count++;
    tmp = malloc((count + 1) * sizeof(char *));
    for (i = 0; tok[i]; i++) {
        if (tok[i] == '&' && tok[i + 1] == '&') {
            tmp[j] = mx_strndup(tok, i);
            tok += i + 2;
            i = 0;
            j++;
        }
    }
    tmp[j] = mx_strndup(tok, i);
    tmp[j+1] = NULL;
    return tmp; */


t_cmd *mx_create_cmd(char *cmd, int i) {
    t_cmd *tr = malloc(sizeof(t_cmd));
    char *temp = NULL;

    if (cmd) {
        temp = mx_strndup(cmd, i);
        tr->cmd = mx_strtrim(temp);
        free(temp);
        temp = NULL;
    }
    else
        tr->cmd = NULL;
    tr->or = NULL;
    tr->and = NULL;
    return tr;
}

static void fillor(char *tok, t_cmd **err) {
    int j = 0;

    for (j = 0; tok[j]; j++) {
        if (tok[j] == '|' && tok[j + 1] == '|') {
            if ((*err)->cmd == NULL)
                (*err)->cmd = mx_strndup(tok, j);
            else {
                (*err)->or = mx_create_cmd(tok, j);
                (*err) = (*err)->or;
            }
            tok += j + 2;
            j = 0;
        }
    }
    if ((*err)->cmd == NULL)
        (*err)->cmd = mx_strndup(tok, j);
    else {
        (*err)->or = mx_create_cmd(tok, j);
        (*err) = (*err)->or;
    }
}

t_cmd *mx_treefull(char *tok) {
    t_cmd *root = mx_create_cmd(NULL, 0);
    t_cmd *leaf = root;
    char **tmp = create_artree(tok);
    int i = 0;

    for (i = 0; tmp[i]; i++) {
        tok = mx_strtrim(tmp[i]); // нужно зафришить  tmp && tok
        fillor(tok, &leaf);
        if (tmp[i + 1]) {
            leaf->and = mx_create_cmd(NULL, 0);
            leaf = leaf->and;
        }
        //mx_printstr(leaf[0].cmd);
    }
    //mx_printstr(root->cmd);
    return root;
}

void mx_pushtree(t_head **forest, char *tok) {
    t_head *new = malloc(sizeof(t_head));
    t_head *tmp = *forest;

    new->command = mx_treefull(tok);
    new->next = NULL;
    if(*forest == NULL) {
        *forest = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}
