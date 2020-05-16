#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {

	unsigned char *psd = (unsigned char *) dst;
	const char *pss = (const char *) src;
	size_t i = 0;

	for (; i < n && *pss != c; i++) {
		*psd++ = *pss++;
	}
	if (*pss == c) {
		*psd++ = *pss++;
		return psd;	
		}
	return NULL;
}

