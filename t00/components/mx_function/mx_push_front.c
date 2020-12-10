#include "mx_function.h"

void mx_push_front(t_list **list, t_dht11 data) {
    if (list == NULL) return;

    t_list *new_n = mx_create_node(data);
    if (new_n == NULL) return;

    new_n->next = *list;
    *list = new_n;
//    printf("stack = %d  %d %d\n", (*list)->data->temp, (*list)->data->hum, (*list)->data->time);
//    if(mx_list_size(*list) > 1)
//        printf("stack-next = %d  %d %d\n", (*list)->next->data->temp, (*list)->next->data->hum, (*list)->next->data->time);

}



