#ifndef FDF_H
# define FDF_H

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "ft_printf/includes/ft_printf.h"
# include "get_next_line.h"
# include "read_map.h"

# define WIN_W 1920
# define WIN_H 1080
# define WIDTH 800
# define HEIGHT 600

typedef struct s_projinfo {
    float offset_x;
    float offset_y;
    float scale;
    float z_scale;
} t_projinfo;

typedef struct s_button {
    int x, y, w, h;
    char *label;
    void (*on_click)(void *);
    void *img; // 画像ポインタを追加
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

void    draw_map(t_ui *ui, t_map *map);
void    draw_ui(t_ui *ui);
void add_button(t_ui *ui, int x, int y, char *label, char *img_path, void (*cb)(void *));
int     mouse_click(int btn, int x, int y, void *p);
void	on_cube(void *p);
void 	on_prev(void *p);
void 	on_play(void *p);
void 	on_next(void *p);
void 	on_grid(void *p);
void	adjust_z_scale(t_map *map, t_projinfo *proj);
void	set_scale_and_offset(t_projinfo *proj,
    float min_px, float max_px, float min_py, float max_py);
void	get_projected_bounds(t_map *map, t_projinfo *proj,
    float *min_px, float *max_px, float *min_py, float *max_py);
#endif