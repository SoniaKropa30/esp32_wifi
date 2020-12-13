#include "main.h"


void nvs_initialization(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
}

void app_main(void) {
    t_app *app = (t_app *)malloc(sizeof(t_app));
    if (!app) return;
    init_main_struct_data(app);
    xTaskCreate(&data_from_uart, "data_from_uart", 4096,
                app, 5, NULL );

    nvs_initialization();
}
