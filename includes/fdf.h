#ifndef FDF_H
# define FDF_H

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../ft_printf/includes/ft_printf.h"
# include "get_next_line.h"
# include "read_map.h"
# include "structs.h"

# define WIN_W 1920
# define WIN_H 1080
# define WIDTH 800
# define HEIGHT 600

void    draw_map(t_ui *ui, t_map *map);
void    draw_ui(t_ui *ui);
int     mouse_click(int btn, int x, int y, void *p);
void	on_cube(void *p);
void 	on_prev(void *p);
void 	on_play(void *p);
void 	on_next(void *p);
void 	on_grid(void *p);
void	adjust_z_scale(t_map *map, t_projinfo *proj);
int key_press(int keycode, void *param);
int mouse_scroll(int button, int x, int y, void *param);
t_screen iso_project(t_vec3 pos, t_projinfo *proj, t_camera *cam);
int play_loop(void *param);
t_screen perspective_project(t_vec3 pos, t_projinfo *proj, t_camera *cam);
int lerp_color(int color1, int color2, float t);
void draw_line_lerp(const t_draw_line_param *p);
void draw_slider(t_ui *ui);
void	get_transformed_point(const t_draw_map_ctx *ctx, int x, int y, t_vec3 *out);
void	rotate_z(t_vec3 *v, float cosz, float sinz);
void	restore_center(t_vec3 *v, const t_draw_map_ctx *ctx);
t_screen	project_point(const t_draw_map_ctx *ctx, t_vec3 v);
void	draw_map_line(const t_draw_map_ctx *ctx, const t_line_info *info);
void	put_pixel(const t_pixel_info *info, int x, int y, int color);
void	add_button(t_ui *ui, t_button_param *param);
void	get_projected_bounds(t_map *map, t_projinfo *proj, t_bounds *bounds);
void	set_scale_and_offset(t_projinfo *proj, t_bounds *bounds);
void sphere_map_transform(const t_sphere_map_param *param, t_vec3 *out);
int	filter_fdf_files(int argc, char **argv, char **fdf_argv);
void	init_ui(t_ui *ui, t_maps *maps);

#endif