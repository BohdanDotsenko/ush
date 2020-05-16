#include "libmx.h"
void mx_swap_str_ptrs(char **arg1, char **arg2);
int mx_quicksort(char **arr, int left, int right) {
    if (!arr)
        return -1;
    int mid = left + (right - left) / 2;
    char* pivot = arr[mid];
    int i = left;
    int j = right;
    int counter = 0;
    while (i <= j) {
        while (mx_strlen(arr[i]) < mx_strlen(pivot))
            i++;
        while (mx_strlen(arr[j]) > mx_strlen(pivot))
            j--;
        if (i <= j) {
            if (i != j && (mx_strlen(arr[i]) != mx_strlen(arr[j]))) {
                counter++;
                mx_swap_str_ptrs(&arr[i], &arr[j]);
            }
            i++;
            j--;
        }
    }
    if (left < j)
        counter += mx_quicksort(arr, left, j);
    if (right > i)
        counter += mx_quicksort(arr, i, right);
    return counter;
}

