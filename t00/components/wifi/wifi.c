#include "wifi.h"

int check_wifi_arg(char *argv[], int argc, t_app *app) {
    if (argc != 3) {
        if (argc > 3)
            uart_write_bytes(UART_NUM_1, ERR_TO_MANY_ARG, sizeof(ERR_TO_MANY_ARG));
        else
            uart_write_bytes(UART_NUM_1, ERR_TO_MANY_ARG, sizeof(ERR_TO_MANY_ARG));
        return 0;
    }
    else if ((strlen(argv[1]) < 1 || strlen(argv[1]) > 32)
               || (strlen(argv[2]) < 8 || strlen(argv[2]) > 64)) {
        uart_write_bytes(UART_NUM_1, ERR_BAD_ARG, sizeof(ERR_BAD_ARG));
        return 0;
    }
    strcpy(app->wf->ssid, argv[1]);
    strcpy(app->wf->password, argv[2]);
    printf("ssid = %s\n", app->wf->ssid);
    printf("password = %s\n", app->wf->password);
    wifi_init_sta(app);
    return 1;
}


static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(t_app *app) {
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
            .sta = {
                    .ssid = app->wf->ssid,
                    .password = app->wf->password,
                    .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                    .pmf_cfg = {
                            .capable = true,
                            .required = false
                    },
            },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 app->wf->ssid, app->wf->password);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 app->wf->ssid, app->wf->password);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    vEventGroupDelete(s_wifi_event_group);
}


