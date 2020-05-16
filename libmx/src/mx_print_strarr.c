#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
	if (!arr || !delim) 
		return;

	for (int i = 0; arr[i]; i++) {
		mx_printstr(arr[i]);
		if (arr[i+1] != NULL)
			mx_printstr(delim);
		else if (arr[i+1] == NULL)
			mx_printchar('\n');
	}
}

