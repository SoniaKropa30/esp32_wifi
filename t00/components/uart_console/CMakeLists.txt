idf_component_register(SRCS "data_from_uart.c"
						REQUIRES wifi
						REQUIRES include
						REQUIRES mx_function
						REQUIRES console

						INCLUDE_DIRS "."
										)