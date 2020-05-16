#include "ush.h"

/*
while (mx_back_slesh(s, &value)) {        ----->you need use it with function
         mx_back_slesh(s, &value);
    }
    */
   
static int get_char_index(const char *str, char c, int *value) {
	if (str == NULL)
		return -2;
	if (str) {
		for (int i = (*value); str[i] != '\0'; i++) {
			if (str[i] == c) { 
				return i;
			}
		}
        return -1;
	}
	else  {
		return -2;
	}
}

int mx_back_slesh(char **str, int* value) {
    char *new_str = NULL;
    int check = 0;
    static int flag = 0;

    check = get_char_index((*str), '\\', value);
    if (check >= 0) {
        new_str = mx_strnew(mx_strlen((*str)));
        mx_strncpy(new_str, (*str), get_char_index((*str), '\\', value));
            if (flag == 0) {
                mx_strcpy(&new_str[mx_strlen(new_str)], &(*str)[check + 1]);
                flag += 1;
            }
            else
                mx_strcpy(&new_str[mx_strlen(new_str)], &(*str)[check +1 ]);
        mx_strdel(str);
        (*str) = new_str;
        (*value) = check + 1;
        return 1;
    }
    else
        return 0;
}

