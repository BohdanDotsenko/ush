#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
	if (!ptr) 
		return malloc(size);

	void *newptr = malloc(size);
	
	if (!newptr)
 	 	return NULL;
	if (!size) {
		free(ptr);
		return malloc(0);
	}
	
	mx_memcpy(newptr, ptr, size);
	free(ptr);

	return newptr;
}

