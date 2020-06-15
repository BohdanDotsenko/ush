#include "libmx.h"


char *mx_strtrim(const char *str) {
    int begin = 0;
    int end = 0;
    char *result = NULL;

    if (str == NULL)
        return NULL;
    for (begin = 0; mx_isspace(str[begin]) == true &&
         str[begin] != '\0'; begin++);
    for (end = mx_strlen(str); mx_isspace(str[end - 1]) == true && end >= 0; end--);
    for (int i = 0; mx_isspace(str[i]) == true; i++) {
        if (str[i + 1] == '\0')
            return NULL;
    }
    result = mx_strnew((end - begin) + 1);
    result = mx_strncpy(result, str + begin, end - begin);
    return result;
}
/*
char *mx_strtrim(const char *str) {
	int len;
	char *dst = NULL;

	if (!str)
		return NULL;
	len = mx_strlen(str);
	while(mx_isspace(str[len-1]) && len > 0) {
        len--;
    }
	while (mx_isspace(*str) && len > 0) {
		str++;
		len--;
	}
	dst = mx_strnew(len+1);
	mx_strncpy(dst, str, len+1);

	return dst;
}

*/
/////////////////

// char *mx_strtrim(const char *str) {
// 	if (!str) 
// 		return NULL;
	
// 	int cw = 0;
// 	int size = mx_strlen(str);

// 	while (mx_isspace(str[size-1])) {
// 		size--;
// 		cw++;
// 	}

// 	while (mx_isspace(*str)) {
// 			str++;
// 			size--;
// 			cw++;
// 	}

// 	char *src = mx_strnew(size);
// 	src = mx_strncpy(src, str, size);

// 	if (cw <= 0)
// 		return NULL;
// 	return src;
// }

