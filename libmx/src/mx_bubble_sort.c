#include "libmx.h"

int mx_strcmp(const char *s1, const char *s2);

int mx_bubble_sort(char **arr, int size) {
	int c = 0;

	if (size < 0) 
		return 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (mx_strcmp(arr[i], arr[j]) > 0) {
				char *box = arr[i];
				arr[i] = arr[j];
				arr[j] = box;
				c++;
			}
		}
	}
	return c;
}

