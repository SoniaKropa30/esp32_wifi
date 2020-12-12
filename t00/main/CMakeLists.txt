idf_component_register(SRCS "main.c"
                        INCLUDE_DIRS "."
                        REQUIRES mx_function
                        REQUIRES include
                        REQUIRES uart_console
                        REQUIRES wifi
                        )