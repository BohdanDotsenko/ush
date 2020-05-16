#include "libmx.h"

static int i_count_bytes(char **data, char **lineptr, char delim, int fd) {
	int len = 0;
	char *tmp = NULL;

	while (data[fd][len] != delim && data[fd][len] != '\0')
			len++;
	if (data[fd][len] == delim) {
		*lineptr = mx_strndup(data[fd], len);
		tmp = mx_strdup(data[fd] + ++len);
		mx_strdel(&data[fd]);
		data[fd] = tmp;
		if (data[fd][0] == '\0')
			mx_strdel(&data[fd]);
		return mx_strlen(*lineptr);
	}
	else if (data[fd][0] == '\0') {
		*lineptr = mx_strdup(data[fd]);
		mx_strdel(&data[fd]);
	}
	return -1;
}

static int i_check_data(int nbytes, char **data, const int fd) {
	if (nbytes == 0 && (!data[fd] || data[fd][0] == '\0'))
		return -1;
	return 0;
}
static int i_read(char **data, const int fd, size_t buf_size, char delim) {
	char buf[buf_size];
	char *temp = NULL;
	int nbytes = 0;

	while ((nbytes = read(fd, buf, buf_size)) > 0) {
    	buf[nbytes] = '\0';
        temp = mx_strjoin(data[fd], buf);
		free(data[fd]);
        data[fd] = temp;
        if (mx_strchr(buf, delim))
        	break;
    }
	return nbytes;
}
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
	static char *data[255];
	int nbytes = 0;
	if (fd < 0 || fd > 255)
		return -2;

	if (!data[fd])
		data[fd] = mx_strnew(0);

	nbytes = i_read(data, fd, buf_size, delim);
	if ((i_check_data(nbytes, data, fd) == -1))
			return -1;
	return i_count_bytes(data, lineptr, delim, fd);
}


