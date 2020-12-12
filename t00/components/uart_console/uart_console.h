#ifndef UART_CONSOLE_H
#define UART_CONSOLE_H

#include "mx_function.h"
#include "components.h"
#include "wifi.h"

QueueHandle_t uart_queue;

void data_from_uart(void *data);
void  init_main_struct_data(t_app *app);

#endif