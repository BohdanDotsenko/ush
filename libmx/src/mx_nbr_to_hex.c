#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
	if (nbr == 0)
		return "0";
	int i = 0;
	unsigned long cp_nbr = nbr;

	for (i = 0; cp_nbr > 0; i++) 
		cp_nbr = cp_nbr / 16;

	char *hex = mx_strnew(i);

	for (int size = i - 1; size >= 0; size--) {
		int tem = nbr % 16;
		if (tem >= 0 && tem <= 9) 
			hex[size] = tem + 48;
		else if (tem >= 10 && tem <= 15) 
			hex[size] = tem + 87;
		nbr = nbr / 16;
	}
	hex[i] = '\0';
	return hex;
}
