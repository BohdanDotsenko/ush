#include "libmx.h"


static int numlen(long long value) {
    int length = 0;
    int copy_value = value;

    while (copy_value) {
        length++;
        copy_value /= 10;
    }
    return value < 0 ? length + 1 : length;
}

char *mx_itoa(int number) {
    int length = numlen(number);
    char *str_integer = NULL;

    if ((number != 0) && (number != -2147483648)) {
        str_integer = mx_strnew(length);
        for (int i = 0; i < length; i++) {
            if (number < 0) {
                str_integer[length] = '-';
                number *= -1;
            }
            str_integer[i] = (number % 10) + 48;
            number /= 10;
        }
        mx_str_reverse(str_integer);
        return str_integer;
    }
    return (number == 0) ? mx_strdup("0") : mx_strdup("-2147483648");
}
