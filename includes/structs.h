/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:44:36 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 10:17:00 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_STRUCTS_H
# define UTILS_STRUCTS_H
#define MAX_MAPS 10

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_point
{
	t_vec3 pos;
	int color;
}	t_point;

typedef struct s_map
{
	char filename[256];
	int width;
	int height;
	t_point **points;
}	t_map;

typedef struct s_maps
{
	t_map maps[MAX_MAPS];
	int count;
	int current;
}	t_maps;

typedef enum
{
    MODE_NONE,
    MODE_CUBE,
    MODE_PLAY,
    MODE_GRID
}   t_mode;

typedef struct s_projinfo {
    float offset_x;
    float offset_y;
    float scale;
    float z_scale;
    float z_angle;
} t_projinfo;

typedef struct s_button {
    int x, y, w, h;
    char *label;
    void (*on_click)(void *);
    void *img; // 画像ポインタを追加
    void *img_active;
} t_button;

typedef struct s_slider {
    int x, y, w;
    int min, max;
    int value;
    int knob_radius;
} t_slider;

typedef struct s_image {
    void    *img;
    char    *img_data;
    int     bpp;
    int     size_lien;
    int     endian;
}   t_image;

// カメラ構造体
typedef struct s_camera {
    float offset_x;
    float offset_y;
    float zoom;
} t_camera;

typedef struct s_ui {
    void        *mlx;
    void        *win;
    t_button    buttons[5];
    int         button_count;
    t_mode      mode;
    t_mode      cube_mode;
    t_mode      grid_mode;
    t_slider    slider;
    int         angle;
    t_image     image;
    t_projinfo  proj;
    t_maps      *maps;   // 追加: マップ一覧へのポインタ
	t_camera	camera;
} t_ui;

typedef struct s_screen
{
    int	x;
    int y;
}	t_screen;

typedef struct s_draw_line_param {
    char      *data;
    t_screen   a;
    t_screen   b;
    int        color_a;
    int        color_b;
    int        size_lien;
    int        bpp;
} t_draw_line_param;

typedef struct s_line_state {
    int dx, dy;
    int sx, sy;
    int err;
    int len;
    int step;
    int x, y;
} t_line_state;

typedef struct s_draw_map_ctx {
    t_ui   *ui;
    t_map  *map;
    float   center_x;
    float   center_y;
    float   radius;
    float   cosz;
    float   sinz;
    int     is_grid;
	t_screen	p;
} t_draw_map_ctx;

typedef struct s_line_info {
    t_screen a;
    t_screen b;
    int color_a;
    int color_b;
} t_line_info;

typedef struct s_pixel_info
{
    char *data;
    int size_lien;
    int bpp;
}	t_pixel_info;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_button_param
{
    int		x;
    int		y;
    char	*label;
    char	*img_path;
    char	*img_active_path;
    void	(*cb)(void *);
}	t_button_param;

typedef struct s_bounds
{
    float min_px;
    float max_px;
    float min_py;
    float max_py;
}	t_bounds;

typedef struct s_point_ctx
{
    t_map		*map;
    t_projinfo	*proj;
    t_bounds	*bounds;
    float		angle;
}	t_point_ctx;

typedef struct s_proj_ctx
{
    float	angle;
    float	px;
    float	py;
    float	camera_z;
    float	fov;
    float	depth;
    float	factor;
    t_screen result;
}	t_proj_ctx;

typedef struct s_scaleinfo
{
    float	x_range;
    float	y_range;
    float	min_z;
    float	max_z;
    float	z_range;
    float	xy_range;
}	t_scaleinfo;

typedef struct s_sphere_map_param
{
    int   x;
    int   y;
    int   w;
    int   h;
    float radius;
    float height;
}	t_sphere_map_param;

#endif