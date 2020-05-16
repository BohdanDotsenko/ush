#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	if (str == NULL || sub == NULL)
		return -2;
	int len_sub = mx_strlen(sub);

	for (int i = 0; str[i] != '\0'; i++) {
		char tem[len_sub + 1];
		for (int j = 0; j < len_sub; j++) {
			tem[j] = str[i + j];
			if (str[i + j] == '\0') 
				return -1;
		}
		tem[len_sub] = '\0';
		if (mx_strcmp(tem, sub) == 0)
			return i;
	}
	return -1;
}

