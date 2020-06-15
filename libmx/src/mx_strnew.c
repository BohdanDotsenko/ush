#include "libmx.h"

char *mx_strnew(const int size) {
	char* str = 0;	

	if (size < 0) 
		return NULL; 
	str = (char *)malloc(size * sizeof(char));
	if (str == NULL)
		return NULL;
	for (int i = 0; i < size; i++) 
		str[i] = '\0';
	return str;
}
