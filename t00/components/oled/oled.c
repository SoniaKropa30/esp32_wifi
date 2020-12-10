#include "oled.h"
#include "font6x8.h"
#include "font8x16.h"

//first simbol from font6x8.h is the 32th of ascii table
// every simbol in ascii is 6 byte

void AsciiStr_to_font6x8(char *str, t_display *display) {
    int font_str_intdex = ((SCREEN_WIDTH - strlen(str) * 6) / 2);
    int index_of_simbol = 0;

    for (int i = 0; i < strlen(str); i++) {
        index_of_simbol = (str[i] - 32) * 6;
        for (int j = 0; j < 6; j++) {
            display->font_str[font_str_intdex] = font6x8[index_of_simbol++];
            font_str_intdex++;
        }
    }
}

void AsciiStr_to_font8x16(char *str, t_display *display, int shift, int font_str_intdex) {
    int index_of_simbol = 0;

    for (int i = 0; i < strlen(str); i++) {
        index_of_simbol = (str[i] - 32) * 16;
        for (int j = 0; j < 8; j++) {
            display->font_str[font_str_intdex] = font8x16[shift + index_of_simbol++];
            font_str_intdex++;
        }
    }

}


void write_to_buffer(char *str, t_display *display) {
    int mid_str = (SCREEN_WIDTH - strlen(str) * 8);
    int font_str_intdex = mid_str > 0 ?  (mid_str / 2) + SCREEN_WIDTH * 2 : SCREEN_WIDTH * 2;

    AsciiStr_to_font8x16(str, display, 0, font_str_intdex);
    AsciiStr_to_font8x16(str, display, 8, font_str_intdex + SCREEN_WIDTH);
}

void send_to_oled(t_display *display, char *str) {
    if(str) {
        write_to_buffer(str, display);
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, 0x80, true); // single command
        i2c_master_write_byte(cmd, 0x00, true);
        i2c_master_write_byte(cmd, 0x40, true); // data stream
        i2c_master_write(cmd, display->font_str, 128 * 8, true);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
    }
}

void oled_update(t_display *display, char *str) {
    send_to_oled(display, str);
}

void oled_clear(t_display *display) {
    memset(display->font_str, 0, SCREEN_SIZE);
}

void oled_initialization(t_display *display) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (display->addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x0, true); // command stream
    i2c_master_write_byte(cmd, 0xAE, true); // off
    i2c_master_write_byte(cmd, 0xD5, true); // clock div
    i2c_master_write_byte(cmd, 0x80, true);
    i2c_master_write_byte(cmd, 0xA8, true); // multiplex
    i2c_master_write_byte(cmd, 0xFF, true);
    i2c_master_write_byte(cmd, 0x8D, true); // charge pump
    i2c_master_write_byte(cmd, 0x14, true);
    i2c_master_write_byte(cmd, 0x20, true); // for horizontal view
    i2c_master_write_byte(cmd, 0x00, true);
    i2c_master_write_byte(cmd, 0x10, true); // high column
    i2c_master_write_byte(cmd, 0xB0, true);
    i2c_master_write_byte(cmd, 0xC8, true);
    i2c_master_write_byte(cmd, 0x0, true); // low column
    i2c_master_write_byte(cmd, 0x10, true);
    i2c_master_write_byte(cmd, 0x40, true);
    i2c_master_write_byte(cmd, 0xA1, true); // segment remap
    i2c_master_write_byte(cmd, 0xA6, true);
    i2c_master_write_byte(cmd, 0x81, true); // contrast
    i2c_master_write_byte(cmd, 0xFF, true);
    i2c_master_write_byte(cmd, 0xAF, true); // on
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(display->port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void oled_config(t_display *display) {
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_32, 1));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_PIN,
            .scl_io_num = SCL_PIN,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = 1000000
    };
    i2c_param_config(I2C_PORT, &i2c_config);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
    display->addr = I2C_ADDR;
    display->port = I2C_PORT;
    oled_initialization(display);
}