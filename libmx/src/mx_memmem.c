#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	const char *b = (const char *) big;
	const char *li = (const char *) little;

	if (big_len < little_len || !little_len || !big_len) 
		return NULL;

	if (little_len == 0) 
		return (void *)big;	

	const char* cb = mx_strndup(b, big_len);
	const char* cli = mx_strndup(li, little_len);
	
	if (mx_strstr(cb, cli)) return mx_strstr(cb, cli);

	return NULL;
}

