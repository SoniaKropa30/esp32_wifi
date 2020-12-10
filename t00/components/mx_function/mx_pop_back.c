#include "mx_function.h"

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL)
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    t_list *point = *head;
    while(point->next->next != NULL) {
        point = point->next;
    }
    free(point->next);
    point->next = NULL;
    return;
}



