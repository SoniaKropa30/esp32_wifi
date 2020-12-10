idf_component_register(SRCS "mx_strsplit.c"
                        SRCS "mx_pop_front.c"
                        SRCS "mx_pop_back.c"
                        SRCS "mx_list_size.c"
                        SRCS "mx_create_node.c"
                        SRCS "mx_push_back.c"
                        SRCS "mx_push_front.c"
                        SRCS "mx_arr_size.c"
						SRCS "mx_itoa.c"
						SRCS "mx_strnew.c"

						REQUIRES include
						INCLUDE_DIRS "."
										)