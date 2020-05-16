#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) { // шукаємо перше входження підстроки needle в строці haystac
	if (mx_strlen(haystack) < mx_strlen(needle)) {
		return NULL;
	}
	if (!needle || !haystack) {
		return NULL;
	}
	if (!mx_strlen(needle)) {
		return (char *)haystack;
	}
	 int i = mx_strlen(needle);

	while (*haystack) {
		if (mx_strchr(haystack, *needle) == haystack) {
			if (mx_strncmp(haystack, needle, i)== 0) {
				return (char *)haystack;
			}
		}
		haystack++;
	}
	return NULL;
} 


