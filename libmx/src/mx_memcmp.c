#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
	unsigned char *str1 = (unsigned char *) s1;
	unsigned char *str2 = (unsigned char *) s2;
	size_t num = 0;

	while (num < n) {
		if (str1[num] == str2[num])
			num++;
		else {	
			return str1[num] - str2[num];
		}
	}
	return 0;
}

