#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char *s1 = (unsigned char *) s;
	unsigned char del = (unsigned char) c;
	size_t i = 0;

	while (i < n) {
		if (*s1 == del)
			return s1;
		s1++;
		i++;
	}
	return NULL;
}

