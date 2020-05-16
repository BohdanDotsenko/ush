#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	int count = 0;
	int len = 0;
	char *cp1 = NULL;
	char *cp2 = NULL;
	if (!replace)
		return NULL; 

	count = mx_count_substr(str, sub);
	len = mx_strlen(str) - (mx_strlen(sub) * count) + (mx_strlen(replace) * count);
	cp1 = mx_strnew(len);
	cp2 = cp1;

	while (*str) {
		if (str != mx_strstr(str, sub)) {
			*cp2++ = *str++;
		}
		if (str == mx_strstr(str, sub)) {
			mx_strncpy(cp2, replace, mx_strlen(replace));
			cp2 += mx_strlen(replace);
			str += mx_strlen(sub);
		}
	}
	return cp1;
}

