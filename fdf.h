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
} t_ui;

typedef struct s_screen
{
    int	x;
    int y;
}	t_screen;

void    draw_map(t_ui *ui, t_map *map);
void    draw_ui(t_ui *ui, t_map *map);
void    add_button(t_ui *ui, int x, int y, char *label, void (*cb)(void *));
int     mouse_click(int btn, int x, int y, void *p);

#endif