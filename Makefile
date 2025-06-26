# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 20:55:41 by msakata           #+#    #+#              #
#    Updated: 2025/06/26 09:38:26 by msakata          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC =	src/gnl/get_next_line.c \
		src/gnl/get_next_line_utils.c \
		src/callbacks/on_cube.c \
		src/callbacks/on_grid.c \
		src/callbacks/on_next.c \
		src/callbacks/on_play.c \
		src/callbacks/on_prev.c \
		src/drawing/draw_line_lerp.c \
		src/drawing/draw_map.c \
		src/drawing/draw_map_utils.c \
		src/drawing/draw_slider.c \
		src/drawing/draw_ui.c \
		src/drawing/put_pixel.c \
		src/input/key_press.c \
		src/load_map/parse_int_hex.c \
		src/load_map/read_map.c \
		src/load_map/read_map_utils.c \
		src/math/lerp_color.c \
		src/mouse/add_button.c \
		src/mouse/mouse_click.c \
		src/mouse/mouse_scroll.c \
		src/playback/play_loop.c \
		src/projection/get_projected_bounds.c \
		src/projection/iso_project.c \
		src/projection/perspective_project.c \
		src/transform/adjust_z_scale.c \
		src/transform/set_scale_and_offset.c \
		src/transform/sphere_map_transform.c \
		src/main.c

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