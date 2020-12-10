#ifndef RTOS_MX_FUNCTION_H
#define RTOS_MX_FUNCTION_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "components.h"


//typedef struct s_list {
//    void        *data;
//    struct      s_list *next;
//}               t_list;


t_list  *mx_create_node(t_dht11 data);
//void mx_push_front(t_list **list, void *data);
void mx_push_front(t_list **list, t_dht11 data);
//void mx_push_back(t_list **list, t_dht11 *data);
//void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));
char **mx_strsplit(const char *s, char c);
int mx_arr_size(char **arr);
char *mx_itoa(int number);
char *mx_strnew(int size);
#endif
