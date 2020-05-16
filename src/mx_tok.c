#include "ush.h"

char *mx_trim_token(char *str) {
	int len;
	char *dst = NULL;

	if (!str)
		return NULL;
	len = mx_strlen(str);
	while(mx_isspace(str[len-1]) && len > 0) {
        if (len > 1 && str[len-2] == '\\')
            break;
        len--;
    }
	while (mx_isspace(*str) && len > 0) {
		str++;
		len--;
	}
	dst = mx_strnew(len);
	mx_strncpy(dst, str, len);
	return dst;
}

static void auditor(int *bufsize, char ****toks) {
    (*bufsize) += 64;
    **toks = realloc((**toks), (*bufsize) * sizeof(char *));
}

static int tokensize(char *line, char ***toks, int bufsize, int position) {
    char *token = NULL;
    char *line_cp = mx_strtrim(line);
    int check = 0;

    if (line_cp[0] == ';')
        return -1;
    check = mx_check_quotes(&line_cp[check], ';');
    while (check > 0 && check != 100) {
        token = mx_strndup(line_cp, check);
        line_cp = mx_strdup(line_cp + check + 1);
        if (check > 0)
            (*toks)[position++] = mx_trim_token(token);
        if (position >= bufsize)
            auditor(&bufsize, &toks);
        check = mx_check_quotes(line_cp, ';');
    }
    if (check == -1)
        return -1;
    else if (check == 100)
        (*toks)[position] = mx_strdup(mx_trim_token(line_cp));
    return 0;
}

char **mx_tok(char *line) {
    int bufsize = 64;
    int position = 0;
    char **tok = malloc(bufsize * sizeof(char *));
    int check = 0;

    if (!tok) {
        fprintf(stderr, "u$h: allocation errno\n");
        exit (EXIT_FAILURE);
    }
    check = tokensize(line, &tok, bufsize, position);
    if (check == -1) {
        mx_printstr("syntax error\n");
        return NULL;
    }
    if (tok[0] == NULL)
        return NULL;
      /* mx_printstr("Here\n");
        for (int i = 0; tok[i]; i++) {
            mx_printstr(tok[i]);
            mx_printstr("\n");
        }
       */ 
    return tok;
}
