# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 20:55:41 by msakata           #+#    #+#              #
#    Updated: 2025/06/24 21:38:16 by msakata          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC =	src/gnl/get_next_line.c \
		src/gnl/get_next_line_utils.c \
		src/ui/ui.c \
		src/camera.c \
		src/parse_int_hex.c \
		src/play_loop.c \
		src/read_map.c \
		src/test.c \
		src/test_main.c


INCLUDES = -Iincludes -Imlx_linux
LINKER = -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
MINILIBX_DIR = ./minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a
OBJS = $(SRC:.c=.o)

all: $(PRINTF) $(MINILIBX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF) $(MINILIBX) $(LINKER)
	
$(PRINTF):
	make -C $(PRINTF_DIR)
	
$(MINILIBX):
	make -C $(MINILIBX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(PRINTF_DIR) clean
	make -C $(MINILIBX_DIR) clean
	
fclean: clean
	rm -f $(NAME)
	make -C $(PRINTF_DIR) fclean
	
re: fclean all

.PHONY: all clean fclean re