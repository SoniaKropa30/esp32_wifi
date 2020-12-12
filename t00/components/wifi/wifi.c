#include "wifi.h"

int check_wifi_arg(char *argv[], int argc, t_app *app) {
    if (argc != 3) {
        if (argc > 3)
            uart_write_bytes(UART_NUM_1, ERR_TO_MANY_ARG, sizeof(ERR_TO_MANY_ARG));
        else
            uart_write_bytes(UART_NUM_1, ERR_TO_MANY_ARG, sizeof(ERR_TO_MANY_ARG));
        return 0;
    } else if ((strlen(argv[1]) < 1 || strlen(argv[1]) > 32)
               || (strlen(argv[2]) < 8 || strlen(argv[2]) > 64)) {
        uart_write_bytes(UART_NUM_1, ERR_BAD_ARG, sizeof(ERR_BAD_ARG));
        return 0;
    }
    strcpy(app->wf.ssid, argv[1]);
    strcpy(app->wf.password, argv[2]);
    return 1;
}

