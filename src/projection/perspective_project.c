/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_project.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:59:59 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 10:00:00 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_screen	perspective_project(t_vec3 pos, t_projinfo *proj, t_camera *cam)
{
	t_proj_ctx	ctx;

	ctx.angle = M_PI / 6.0f;
	ctx.px = (pos.x - pos.y) * cosf(ctx.angle);
	ctx.py = (pos.x + pos.y) * sinf(ctx.angle);
	ctx.px = (ctx.px - proj->offset_x + cam->offset_x)
		* proj->scale * cam->zoom;
	ctx.py = (ctx.py - proj->offset_y + cam->offset_y)
		* proj->scale * cam->zoom;
	ctx.camera_z = 1000.0f;
	ctx.fov = 800.0f;
	ctx.depth = ctx.camera_z - ctx.py;
	if (ctx.depth < 1.0f)
		ctx.depth = 1.0f;
	ctx.factor = ctx.fov / ctx.depth;
	ctx.result.x = WIDTH / 2 + ctx.px * ctx.factor;
	ctx.result.y = HEIGHT / 2 + (ctx.py - pos.z * proj->z_scale
			* proj->scale * cam->zoom) * ctx.factor;
	return (ctx.result);
}
