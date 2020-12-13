#ifndef WIFI_H
#define WIFI_H

#include "mx_function.h"
#include "components.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#define EXAMPLE_ESP_MAXIMUM_RETRY   3000

const char *TAG = "wifi station";
int s_retry_num = 0;


EventGroupHandle_t s_wifi_event_group;


int check_wifi_arg(char *argv[], int argc, t_app *app);
void wifi_init_sta(t_app *app);
#endif