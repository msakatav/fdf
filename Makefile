# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 02:14:38 by msakata           #+#    #+#              #
#    Updated: 2025/06/21 05:47:44 by msakata          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./src -lXext -lX11 -lm -lz

SRC =	src/put_pixel/draw_line_lerp.c \
		src/put_pixel/draw_map.c \
		src/put_pixel/get_map_bounds.c \
		src/put_pixel/get_projected_bounds.c \
		src/put_pixel/iso_project.c \
		src/put_pixel/lerp_color.c \
		src/put_pixel/main.c \
		src/put_pixel/put_pixel.c \
		src/read_map/parse_int_hex.c \
		src/read_map/read_map.c

OBJS = $(SRC:.c=.o)

LIBS = libmlx_Linux.a libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re