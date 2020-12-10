idf_component_register(SRCS "main.c"
                        SRCS "data_from_uart.c"
                        INCLUDE_DIRS "."
                        REQUIRES mx_function
                        REQUIRES timer
                        REQUIRES include
                        REQUIRES nvs_flash
#                        REQUIRES oled
                        )