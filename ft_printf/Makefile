# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 00:10:08 by msakata           #+#    #+#              #
#    Updated: 2025/05/15 00:10:09 by msakata          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft/libft.a
SRCS =	srcs/ft_printf.c \
		srcs/ft_putchar.c \
		srcs/ft_putstr.c \
		srcs/ft_putptr.c \
		srcs/ft_putnbr.c \
		srcs/ft_putunsigend.c \
		srcs/ft_puthex_lower.c \
		srcs/ft_puthex_upper.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I libft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		cp $(LIBFT) $(NAME)
		ar rcs $(NAME) $(OBJS)

$(LIBFT):
		$(MAKE) -C libft all

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(MAKE) -C libft clean
		rm -f $(OBJS)

fclean: clean
		$(MAKE) -C libft fclean
		rm -f $(NAME)

re: fclean all