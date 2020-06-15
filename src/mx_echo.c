#include "ush.h"

/* 
/ Deleted all checks due to auditor
*/ 
static void flag_parser(int argc, char **argv, bool *flags, int *i) {
    regex_t preg;
    
    regcomp(&preg, "^-[nEe]+$", REG_EXTENDED);
    for (; *i < argc; (*i)++) {
        if (0 == (regexec(&preg, argv[*i], 0, NULL, 0))) {
            for (int j = 1; argv[*i][j] != '\0'; j++) {
                if (argv[*i][j] == 'n')
                  flags[0] = true; 
                else if(argv[*i][j] == 'E')
                  flags[1] = true; 
                else if(argv[*i][j] == 'e')
                  flags[2] = true; 
                }
            } 
        else 
            break;
    }
    if (flags[1] == false && flags[2] == false)
        flags[1] = true;
    regfree(&preg);
}

static void replace_backslash_char(char c, int *j) {
    if (c == '\\') 
        mx_printchar('\\');
    else if (c == 'a') 
        mx_printchar('\a');
    else if (c == 'b') 
        mx_printchar('\b');
    else if (c == 'c') 
        exit(0);
    else if (c == 'f') 
        mx_printchar('\f');
    else if (c == 'n') 
        mx_printchar('\n');
    else if (c == 'r') 
        mx_printchar('\r');
    else if (c == 't') 
        mx_printchar('\t');
    else if (c == 'v') 
        mx_printchar('\v');
    *j += 1;    
}

static void print_octal(const char *str, int *j) {
    int result = 0;

    (*j)++; // before j == '\'
    for (int x = 0; str[*j] != '\0' && (str[*j] > 47 && str[*j] < 57) && x < 3;
         x++, (*j)++)
    {
        result += (str[*j] - 48) * pow(8, x);
    }
    mx_printchar(result);
    (*j)--; // high level loop will increment value again, rewrite this shit
}

static void print_hex(const char *str, int *j) {
    int result = 0;
    int val = 0;

    (*j)++; // before j == '\'
    for (int x = 0; str[*j] != '\0' && x < 3; x++, (*j)++) {
        if (str[*j] >= '0' && str[*j] <= '9')
            val = str[*j] - 48;
        if (str[*j] >= 'a' && str[*j] <= 'f')
            val = str[*j] - 87;
        if (str[*j] >= 'A' && str[*j] <= 'F')
            val = str[*j] - 55;
        result += val * pow(16, x);
    }
    mx_printchar(result);
    (*j)--; // high level loop will increment value again, rewrite this shit
}



static void print_flag_e(int argc, int i, char **argv) {
    for (; i < argc; i++) { 
        for (int j = 0; argv[i] && argv[i][j] != '\0'; j++) {
            if (argv[i][j] == '\\') { 
                if (is_backslash_char(argv[i][j + 1]) == true) { 
                    replace_backslash_char(argv[i][j + 1], &j);
                    continue;
                }
                else if (argv[i][j + 1] == '0') {
                    print_octal(argv[i], &j);
                    continue;
                }
                else if (argv[i][j + 1] == 'x') {
                    print_hex(argv[i], &j);
                    continue;
                }
            }
            mx_printchar(argv[i][j]);
        }
        if (argv[i + 1])
            mx_printchar(' ');
    }
}

int mx_echo(char **argv) { // to many functions in file
    bool flags[3] = {false}; // 0 is -n, 1 is -E, 2 is -e
    int i = 1;
    int argc = 0;

    if (argv && argv[1] && argv[1][0] == '?')
        return mx_print_exit();
    for (; argv[argc] != NULL; argc++);
    if (argc < 2)
        return 0;
    flag_parser(argc, argv, flags, &i);
    if (flags[2] == true) 
        print_flag_e(argc, i, argv);
    else 
        while (i < argc) {
            mx_printstr(argv[i++]);
            if (i != argc)
                mx_printchar(' ');
        }
    if (flags[0] == false) 
        mx_printchar('\n');
    return 0;
}
