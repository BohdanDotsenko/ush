#include "libmx.h"
	
void mx_del_strarr(char ***arr) {
	char **str = *arr;

	while (*str) {
		mx_strdel(str);
		str++;
	}
	free(*arr);
	*arr = NULL;
}
