/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale_and_offset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:00:28 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 10:15:47 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale_and_offset(t_projinfo *proj, t_bounds *bounds)
{
	float	proj_w;
	float	proj_h;
	float	scale_x;
	float	scale_y;

	proj_w = bounds->max_px - bounds->min_px;
	proj_h = bounds->max_py - bounds->min_py;
	if (proj_w < 1.0f)
		proj_w = 1.0f;
	if (proj_h < 1.0f)
		proj_h = 1.0f;
	scale_x = (WIDTH * 0.9f) / proj_w;
	scale_y = (HEIGHT * 0.9f) / proj_h;
	if (scale_x < scale_y)
		proj->scale = scale_x;
	else
		proj->scale = scale_y;
	proj->offset_x = (bounds->min_px + bounds->max_px) * 0.5f;
	proj->offset_y = (bounds->min_py + bounds->max_py) * 0.5f;
}
