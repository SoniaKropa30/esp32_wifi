#include "mx_function.h"

char *mx_strnew(int size) {
    if (size < 0) return NULL;

    char *t = (char*) malloc((size + 1)* sizeof(char));
    if (!t) 
        return 0;
   memset(t, 0, size + 1);
//    for (int i = 0; i < size + 1; i++)
//        t[i] = '\0';
    return t;
}


