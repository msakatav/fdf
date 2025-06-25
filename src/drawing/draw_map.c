/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:59:01 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:22:52 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_map_right(const t_draw_map_ctx *ctx, int x, int y)
{
	t_vec3		tmp_r;
	t_screen	p_right;
	t_line_info	info;

	get_transformed_point(ctx, x + 1, y, &tmp_r);
	rotate_z(&tmp_r, ctx->cosz, ctx->sinz);
	restore_center(&tmp_r, ctx);
	p_right = project_point(ctx, tmp_r);
	info.a = ctx->p;
	info.b = p_right;
	info.color_a = ctx->map->points[y][x].color;
	info.color_b = ctx->map->points[y][x + 1].color;
	draw_map_line(ctx, &info);
}

static void	draw_map_down(const t_draw_map_ctx *ctx, int x, int y)
{
	t_vec3		tmp_d;
	t_screen	p_down;
	t_line_info	info;

	get_transformed_point(ctx, x, y + 1, &tmp_d);
	rotate_z(&tmp_d, ctx->cosz, ctx->sinz);
	restore_center(&tmp_d, ctx);
	p_down = project_point(ctx, tmp_d);
	info.a = ctx->p;
	info.b = p_down;
	info.color_a = ctx->map->points[y][x].color;
	info.color_b = ctx->map->points[y + 1][x].color;
	draw_map_line(ctx, &info);
}

static void	draw_map_point(t_draw_map_ctx *ctx, int x, int y)
{
	t_vec3	tmp;

	get_transformed_point(ctx, x, y, &tmp);
	rotate_z(&tmp, ctx->cosz, ctx->sinz);
	restore_center(&tmp, ctx);
	ctx->p = project_point(ctx, tmp);
	if (x + 1 < ctx->map->width)
		draw_map_right(ctx, x, y);
	if (y + 1 < ctx->map->height)
		draw_map_down(ctx, x, y);
}

static void	init_draw_map_ctx(t_draw_map_ctx *ctx, t_ui *ui, t_map *map)
{
	float	rad;

	ctx->ui = ui;
	ctx->map = map;
	ctx->center_x = (map->width - 1) / 2.0f;
	ctx->center_y = (map->height - 1) / 2.0f;
	ctx->is_grid = (ui->grid_mode == MODE_GRID);
	if (map->width < map->height)
		ctx->radius = map->width * 0.4f;
	else
		ctx->radius = map->height * 0.4f;
	rad = ui->proj.z_angle * M_PI / 180.0f;
	ctx->cosz = cosf(rad);
	ctx->sinz = sinf(rad);
}

void	draw_map(t_ui *ui, t_map *map)
{
	t_draw_map_ctx	ctx;
	int				y;
	int				x;

	init_draw_map_ctx(&ctx, ui, map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_map_point(&ctx, x, y);
			x++;
		}
		y++;
	}
}
