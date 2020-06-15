#include "libmx.h"

int mx_strlen(const char *s) {
	int i = 0;
	int len = 0;

	if (!s) 
		return 0;

	while (s[i++]) 
		len++;	
	return len;
}
