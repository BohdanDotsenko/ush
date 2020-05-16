#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
	int len = 0;
	int j = 0;

	if (!str) 
		return NULL;

	char *box = mx_strtrim(str);
	len = mx_strlen(box);
	for (int i = 0; box[i] != '\0'; i++) {
		if (mx_isspace(box[i]) && mx_isspace(box[i+1])) {
				len--;
			}
	}
	char *string = mx_strnew(len);

	for (int i = 0; box[i] != '\0'; i++) {
		if (mx_isspace(box[i]) && mx_isspace(box[i+1])) {
			continue;
		}
		else  {
			if (mx_isspace(box[i])) 
				box[i] = ' ';
			string[j++] = box[i];
		} 
	}
	string[len] = '\0';
	mx_strdel(&box);
	return string;
}

