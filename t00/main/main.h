#ifndef MAIN_H
#define MAIN_H

#include "mx_function.h"
#include "components.h"
#include "uart_console.h"

#define EXAMPLE_ESP_WIFI_SSID      "iPhone"
#define EXAMPLE_ESP_WIFI_PASS      "kropa301999"
#define EXAMPLE_ESP_MAXIMUM_RETRY   3000



#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

const char *TAG = "wifi station";
int s_retry_num = 0;



EventGroupHandle_t s_wifi_event_group;

#endif
