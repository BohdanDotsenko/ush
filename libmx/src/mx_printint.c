#include "libmx.h"

void mx_printchar(char x);

void mx_printint(int n) {
	if (n == -2147483648) {
		mx_printint(-214748364);
		mx_printchar(8 + '0');
	}	

    else {
		if(n < 0) {
			mx_printchar('-');
			n = n * -1;
		}
		if(n >= 0 && n <= 9) {
			mx_printchar(n + 48);
		}
		else {	
			mx_printint(n / 10);
			mx_printchar(n % 10 + 48); 
		}
	}	
}

