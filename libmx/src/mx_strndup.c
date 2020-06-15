#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {

	char *st = mx_strnew(n + 1);
	return mx_strncpy(st, s1, n);
}
