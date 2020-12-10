#include "mx_function.h"

void mx_pop_front(t_list **head) {
    if(head == NULL || *head == NULL) 
        return;
    
    t_list *point = (*head)->next;
    free(*head);
    *head = point;
}


