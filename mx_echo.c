#include "ush.h"

// TODO: fix auditor, delete error handling if needed
static void flag_parser(int argc, char **argv, bool *flags, int *i) {
    regex_t preg;
    int rc = 0;
    
    if (0 != (rc = regcomp(&preg, "^-[nEe]+$", REG_EXTENDED))) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
        exit(rc); // TODO exit function;
    }
    for (; *i < argc; (*i)++) {
        if (0 == (rc = regexec(&preg, argv[*i], 0, NULL, 0))) {
            for (int j = 1; argv[*i][j] != '\0'; j++) {
                if (argv[*i][j] == 'n')
                  flags[0] = true; 
                else if(argv[*i][j] == 'E')
                  flags[1] = true; 
                else if(argv[*i][j] == 'e')
                  flags[2] = true; 
                else {
                    regfree(&preg);
                    return;
                }
            } 
        }
        else if (rc != REG_NOMATCH) {
            printf("regcomp() failed with '%d'\n", rc);
            exit(rc);
        }
        else 
            break;
    }
    regfree(&preg);
}

static bool is_backslash_char(char c) {
    if (c > 97 && c < 102)
        return true;
    else if (c == 'n')
        return true;
    else if (c == 'r')
        return true;
    else if (c == 't')
        return true;
    else if (c == 'v')
        return true;
    return false;
}

static void replace_backslash_char(char c) {
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
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] == '\\') {
                if (is_backslash_char(argv[i][j + 1]) == true) { 
                    replace_backslash_char(argv[i][j + 1]);
                    j++;
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
        mx_printchar(' ');
    }
}

int main(int argc, char **argv) {
    if (argc < 2)
        return 0;
    bool flags[3] = {false}; // 0 is -n, 1 is -E, 2 is -e
    int i = 1;

    flag_parser(argc, argv, flags, &i);
    if (flags[2] == true ||
       (flags[0] == false && flags[1] == false && flags[2] == false))
        print_flag_e(argc, i, argv);
    else 
        while (i < argc) {
            printf("%s ", argv[i++]);
        }
    if (flags[0] == false) 
        printf("\n");
    return 0;
}
