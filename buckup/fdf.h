/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 07:14:35 by root              #+#    #+#             */
/*   Updated: 2025/06/22 09:36:31 by msakata          ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/includes/ft_printf.h"

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

typedef struct s_mapdata
{
    t_point	**map;
    int		width;
    int		height;
}	t_mapdata;

typedef struct s_projinfo
{
    float	min_px;
    float	max_px;
    float	min_py;
    float	max_py;
    float	proj_w;
    float	proj_h;
    float	scale_x;
    float	scale_y;
    float	scale;
    float	offset_x;
    float	offset_y;
    float	z_scale; // 追加
}	t_projinfo;

typedef struct s_mlxinfo
{
    void	*mlx;
    void	*win;
    void	*img;
    char	*img_data;
    int		bpp;
    int		size_lien;
    int		endian;
}	t_mlxinfo;

typedef struct s_fdf
{
    t_mapdata	mapdata;
    t_projinfo	projinfo;
    t_mlxinfo	mlxinfo;
}	t_fdf;

t_point	**read_map(const char *filename, int *width, int *height);
static void	process_line(t_mapinfo *info, char *line);
static void	expand_map(t_mapinfo *info);
static t_point	*parse_row(char **tokens, int temp_w, int h);
static int	get_row_width(char **tokens);
int	ft_parse_int_hex(const char *str, int *z, int *color);
static int	parse_hex(const char *str, int *i);
static int	parse_decimal(const char *str, int *i);
static int	parse_sign(const char *str, int *i);
void	put_pixel(char *data, int x, int y, int color, int size_lien, int bpp);
int	lerp_color(int color1, int color2, float t);
t_screen	iso_project(t_vec3 pos, t_projinfo *proj);
void	get_projected_bounds(t_mapdata *mapdata, t_projinfo *proj,
            float *min_px, float *max_px, float *min_py, float *max_py);
void	set_z_scale(t_mapdata *mapdata, t_projinfo *proj);
void	draw_map(t_fdf *fdf);
void	draw_line_lerp(char *data, t_screen a, t_screen b, int color_a, int color_b, int size_lien, int bpp);


#endif