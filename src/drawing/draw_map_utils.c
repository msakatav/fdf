/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:04:10 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 13:07:57 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_transformed_point(const t_draw_map_ctx *ctx, int x,
	int y, t_vec3 *out)
{
	t_vec3				orig;
	t_sphere_map_param	param;

	orig = ctx->map->points[y][x].pos;
	if (ctx->is_grid)
	{
		param.x = x;
		param.y = y;
		param.w = ctx->map->width;
		param.h = ctx->map->height;
		param.radius = ctx->radius;
		param.height = orig.z * ctx->ui->proj.z_scale;
		sphere_map_transform(&param, out);
	}
	else
	{
		out->x = orig.x - ctx->center_x;
		out->y = orig.y - ctx->center_y;
		out->z = orig.z;
	}
}

void	rotate_z(t_vec3 *v, float cosz, float sinz)
{
	float	x;
	float	y;

	x = v->x;
	y = v->y;
	v->x = x * cosz - y * sinz;
	v->y = x * sinz + y * cosz;
}

void	restore_center(t_vec3 *v, const t_draw_map_ctx *ctx)
{
	if (!ctx->is_grid)
	{
		v->x += ctx->center_x;
		v->y += ctx->center_y;
	}
}

t_screen	project_point(const t_draw_map_ctx *ctx, t_vec3 v)
{
	if (ctx->ui->cube_mode == MODE_CUBE)
		return (perspective_project(v, &ctx->ui->proj, &ctx->ui->camera));
	else
		return (iso_project(v, &ctx->ui->proj, &ctx->ui->camera));
}

void	draw_map_line(const t_draw_map_ctx *ctx, const t_line_info *info)
{
	t_draw_line_param	param;

	param.data = ctx->ui->image.img_data;
	param.a = info->a;
	param.b = info->b;
	param.color_a = info->color_a;
	param.color_b = info->color_b;
	param.size_lien = ctx->ui->image.size_lien;
	param.bpp = ctx->ui->image.bpp;
	draw_line_lerp(&param);
}
