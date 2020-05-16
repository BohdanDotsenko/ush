#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
	double i  = 0;
	double sum = 1;

	if(pow == 1) 
		return n;
	
	while (i < pow) {
		sum = sum * n;
		i++;		
	}
		return sum;
}

