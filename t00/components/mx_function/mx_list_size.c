#include "mx_function.h"

int mx_list_size(t_list *list) {
    int len = 0;
    if(!list)
        return len;

    t_list *ptr  = list;

    while(ptr) {
        ptr = ptr->next;
        len++;
    }
    return len;
}

