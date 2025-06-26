/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_z_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 02:49:54 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 10:12:20 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_z_range(t_map *map, float *min_z, float *max_z)
{
	int		x;
	int		y;
	float	z;

	*min_z = 1e9;
	*max_z = -1e9;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->points[y][x].pos.z;
			if (z < *min_z)
				*min_z = z;
			if (z > *max_z)
				*max_z = z;
			x++;
		}
		y++;
	}
}

void	adjust_z_scale(t_map *map, t_projinfo *proj)
{
	t_scaleinfo	s;

	if (map->width > 1)
		s.x_range = map->width - 1;
	else
		s.x_range = 1;
	if (map->height > 1)
		s.y_range = map->height - 1;
	else
		s.y_range = 1;
	get_z_range(map, &s.min_z, &s.max_z);
	s.z_range = s.max_z - s.min_z;
	if (s.z_range < 1e-6)
		s.z_range = 1.0f;
	s.xy_range = (s.x_range + s.y_range) / 2.0f;
	proj->z_scale = s.xy_range / s.z_range * 0.5f;
	if (proj->z_scale > 10.0f)
		proj->z_scale = 10.0f;
	if (proj->z_scale < 0.05f)
		proj->z_scale = 0.05f;
}
