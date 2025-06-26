/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_projected_bounds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 02:55:04 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:56:56 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bounds(t_bounds *bounds)
{
	bounds->min_px = 1e9;
	bounds->min_py = 1e9;
	bounds->max_px = -1e9;
	bounds->max_py = -1e9;
}

static void	update_bounds(t_bounds *bounds, float px, float py)
{
	if (px < bounds->min_px)
		bounds->min_px = px;
	if (px > bounds->max_px)
		bounds->max_px = px;
	if (py < bounds->min_py)
		bounds->min_py = py;
	if (py > bounds->max_py)
		bounds->max_py = py;
}

static void	process_point(t_point_ctx *ctx, int x, int y)
{
	float	px;
	float	py;

	px = (ctx->map->points[y][x].pos.x - ctx->map->points[y][x].pos.y)
		* cosf(ctx->angle);
	py = (ctx->map->points[y][x].pos.x + ctx->map->points[y][x].pos.y)
		* sinf(ctx->angle) - ctx->map->points[y][x].pos.z * ctx->proj->z_scale;
	update_bounds(ctx->bounds, px, py);
}

void	get_projected_bounds(t_map *map, t_projinfo *proj, t_bounds *bounds)
{
	t_point_ctx	ctx;
	int			y;
	int			x;

	ctx.map = map;
	ctx.proj = proj;
	ctx.bounds = bounds;
	ctx.angle = M_PI / 6.0f;
	init_bounds(bounds);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			process_point(&ctx, x, y);
			x++;
		}
		y++;
	}
}
