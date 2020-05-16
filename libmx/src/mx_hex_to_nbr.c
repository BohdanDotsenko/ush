static int ss_strlen(const char *str) {
	int i = 0;
	for (i = 0; str[i] != '\0'; i++) {
	}
	return i;
}

unsigned long mx_hex_to_nbr(const char *hex) {
	unsigned long result = 0;
	int i = ss_strlen(hex) -1;
	unsigned long base = 1;

	for ( ; i >= 0; i--) {
		if (hex[i] >= '0' && hex[i] <= '9') {
			result += (hex[i] - 48) * base;
			base *= 16;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F') {
			result += (hex[i] - 55) * base;
			base *= 16;
		}
		else if (hex[i] >= 'a' && hex[i] <= 'f') {
			result += (hex[i] - 87) * base;
			base *= 16;
		}
	}
	return result;
}

