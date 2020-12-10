
#ifndef OLED_H
#define OLED_H

#define SDA_PIN                             GPIO_NUM_21
#define SCL_PIN                             GPIO_NUM_22
#define I2C_ADDR                            0x3C
#define I2C_PORT                            I2C_NUM_0
#define SCREEN_WIDTH                        128
#define PAGE_COUNT                          8
#define SCREEN_SIZE                         1024 // width * number of pages


#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2c.h"
#include <strings.h>
#include <string.h>
#include "components.h"

typedef struct s_display {
    uint8_t             addr;           // I2C address
    i2c_port_t          port;        // I2C interface port
    uint16_t            changes;       // page change bit to optimize writes
    uint8_t *           font_str; // page buffer
} t_display;

void send_to_oled(t_display *display, char *str);
void oled_update(t_display *display, char *str);
void oled_clear(t_display *display);
void oled_initialization(t_display *display);
void data_to_oled(void *arg);
void oled_config(t_display *display);
void AsciiStr_to_font6x8(char *str, t_display *display);
#endif