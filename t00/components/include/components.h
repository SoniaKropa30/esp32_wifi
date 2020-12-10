#ifndef RTOS_COMPONENTS_H
#define RTOS_COMPONENTS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_system.h"
#include "driver/gpio.h"


#define UART_TX_PIN                     17
#define UART_RX_PIN                     16
#define BUF_SIZE                        1024

#define ERR_COMM_NOT_FOUND              "\x1b[31mrtos: command not found\n\r\x1b[0m"
#define ERR_TO_MANY_ARG                 "\x1b[31mrtos: too many arguments\n\r\x1b[0m"
#define ERR_BAD_ARG                     "\x1b[31mrtos: bad argument\n\r\x1b[0m"
#define ERR_ADD_PARAM                   "\x1b[31mrtos: please add parameters\n\r\x1b[0m"


#define SIZE_STR_FOR_EXECUTE            120
#define ENTER                           13
#define MAX_SIZE_BUF                    120
#define DELETE                          127

typedef struct s_dht11 {
    int temp;
    int hum;
    uint64_t time;
} t_dht11;

typedef struct s_list {
    t_dht11     data;
    struct      s_list *next;
}               t_list;

typedef struct s_app {
    uint8_t *buf;
    char *str_for_execute;
    int iterator;
    int len;
    int history_iterator;
    t_list *stack;
    char time[9];
    xTaskHandle clock;
} t_app;


void timer_initialise ();

#endif
