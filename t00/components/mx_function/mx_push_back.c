#include "mx_function.h"

void mx_push_back(t_list **list, t_dht11 data) {
    t_list *new = mx_create_node(data);

    if(*list == NULL)
        *list = new;
    else {
        t_list *lol = *list;
        while (lol->next != NULL)
            lol = lol->next; 
        lol->next = new;
    }
 }



