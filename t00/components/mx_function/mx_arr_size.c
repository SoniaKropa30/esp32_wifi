#include "mx_function.h"

int mx_arr_size(char **arr) {
    int i = 0;
    if(arr) {
        while (arr[i] != NULL)
            i++;
    }
    return i;
}
