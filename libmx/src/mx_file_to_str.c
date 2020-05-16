#include "libmx.h"

char *mx_file_to_str(const char *filename) {
	if (!filename) 
		return NULL;

	int fd = open(filename, O_RDONLY);
	if (fd < 0) 
		return NULL;

	int len = 0;
	char buf[1];

	while (read(fd, buf, 1) && buf[0] != EOF) 
		len++;

	if (len < 0)
		return NULL;
	close(fd);
	
	char *result = mx_strnew(len);
	if (!result) return NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0) return NULL;

	read(fd, result, len);
	result[len] = '\0';
	close(fd);
	return result;
	
}

