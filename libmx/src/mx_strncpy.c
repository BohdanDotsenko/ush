#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
	char *ss = dst;
	while (len > 0 && *src != '\0') {
		*ss++ = *src++;
		len--;	
	}
	while (len > 0) {
		*ss = '\0';
		len--;
	}
	return dst;
}
