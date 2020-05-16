#include "libmx.h"
int mx_intlen(int number) {
	int i = 0;

	while (number) {
		number = number / 10;
		i++;
	}
	return i;
}
