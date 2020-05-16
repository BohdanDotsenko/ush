#include "libmx.h"

void mx_str_reverse(char *s) {
	int i = mx_strlen(s) - 1;

	if (s == NULL) 
		return;

	for (int o = 0; i > o; i--) {
		char k = s[o];
		s[o] = s[i];
		s[i] = k;
		o++;
	}
}
