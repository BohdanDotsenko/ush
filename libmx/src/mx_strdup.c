#include "libmx.h"

char *mx_strcpy(char *dst, const char *src);
int mx_strlen(const char *s);
char *mx_strnew(const int size);

char *mx_strdup(const char *str) {
	if (str == NULL) {
		return mx_strnew(0);
	}
	int size = mx_strlen(str);

	char *st = mx_strnew(size + 1);
	
	return mx_strcpy(st, str);
}

