#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
	char *psDest = (char *) dst;
	const char *psSrc = (const char *) src;
	
	while (n--) 
		*(psDest++) = *(psSrc++);
	return dst;
}

