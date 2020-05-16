#include "libmx.h"

int mx_strcmp(const char *s1, const char *s2);

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int left = 0;
	int end = size - 1;
	int mid;

	*count = 0;
	while (left <= end) {
		*count += 1;
		mid = (left + end) / 2;
		if (mx_strcmp(s, arr[mid]) > 0)
			left = mid + 1;
		else if (mx_strcmp(s, arr[mid]) < 0) 
			end = mid - 1;
		else 
			return mid;
	}
	*count = 0;
	return -1;
}

