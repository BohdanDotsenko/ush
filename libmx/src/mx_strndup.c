#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {

	char *st = mx_strnew(n);
	return mx_strncpy(st, s1, n);
}
