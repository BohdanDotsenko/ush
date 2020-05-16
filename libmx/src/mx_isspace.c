#include "libmx.h"
	bool mx_isspace(int c) {
		if (c == '\t' || c == '\f' || c == '\n' || c == ' ' || c == '\v' || c == '\r') {
			return true;
	}
	return false;
}

