#include "ush.h"

static void costil_2(DIR *dptr, char **path) {
    closedir(dptr);
    mx_strdel(path);
}

static bool if_exec(char *filepath) {
    struct stat sb;

    if (stat(filepath, &sb) == 0 && sb.st_mode & S_IXUSR) 
        return true;
    else
        return false;
}

static int costil_auditor(char **fpath, bool *flags, DIR *dptr, char **path) {
    if (flags == NULL) {
        costil_2(dptr, path);
        return 0;
    }
    if (flags[0] == true) {
        if (if_exec(*fpath) == true) {
            mx_printstr(*fpath);
            mx_printchar('\n');
            mx_strdel(fpath);
        }
        return 1;
    }
    else {
        costil_2(dptr, path);
        return 0;
    }
}

static void flag_parser(char **argv, bool *flags, int *i) {
    regex_t preg;
    
    regcomp(&preg, "^-[as]+$", REG_EXTENDED);
    for (; argv[*i]; (*i)++) {
        if (0 == (regexec(&preg, argv[*i], 0, NULL, 0))) {
            for (int j = 1; argv[*i][j] != '\0'; j++) {
                if (argv[*i][j] == 'a')
                  flags[0] = true; 
                else if(argv[*i][j] == 's') {
                  flags[1] = true; 
                  flags[0] = false;
                  break;
                }
            }
        }
        else 
            break;
    }
    regfree(&preg);
}

int mx_find_filepath(char **cmd_arr, char **filepath, void *flags) { 
    char *path = getenv("PATH");
    DIR *dptr;

    if (path == NULL)
        path = mx_find_filepath2();
    if (path != NULL) {
        path = mx_strdup(path);
        for (char *tok = strtok(path, ":"); tok; tok = strtok(NULL, ":")) {
            if ((dptr = opendir(tok)) != NULL) {
                for (struct dirent *ds; (ds = readdir(dptr)) != NULL;) {
                    if (strcmp(ds->d_name, cmd_arr[0]) == 0) {
                        *filepath = mx_three_to_one(tok, "/", ds->d_name);
                        if (costil_auditor(filepath, flags, dptr, &path) == 0)
                            return 1;
                    }
                }
                closedir(dptr);
            }
        }
    }
    mx_strdel(&path);
    return 1;
}

int mx_which(st_launch *l_inf) {
    bool flags[2] = {false}; // -a = 0, -s = 1;
    int i = 1;
    char *filepath = NULL;
    
    flag_parser(l_inf->cmd_arr, flags, &i);
    for (; l_inf->cmd_arr[i]; i++) {
        if (mx_find_filepath(&l_inf->cmd_arr[i], &filepath, flags) != 1) {
            if (flags[1] == true) {
                if (if_exec(filepath) == true)
                    return 0;
            }
            else {
                if (if_exec(filepath) == true) {
                    mx_printstr(filepath);
                    mx_printchar('\n');
                    return 0;
                }
            }
        }
    }
    return 0;
}
