/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 07:14:35 by root              #+#    #+#             */
/*   Updated: 2025/06/20 11:16:09 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vec3
{
	float   x;
	float   y;
	float   z;
}	t_vec3;

typedef struct s_point
{
	t_vec3  pos;
	int     color;
}	t_point;

typedef struct s_screen
{
	int	x;
	int y;
}	t_screen;

typedef struct s_mapinfo
{
	t_point	**map;
	int		w;
	int		h;
	int		cap;
}	t_mapinfo;


#endif