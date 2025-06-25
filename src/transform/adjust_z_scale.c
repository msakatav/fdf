/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_z_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 02:49:54 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 02:49:57 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ----------------------- zスケール自動調整 -----------------------
void adjust_z_scale(t_map *map, t_projinfo *proj)
{
    float x_range;
    float y_range;
    float min_z;
    float max_z;

    if (map->width  > 1)
        x_range =  map->width  - 1;
    else
        x_range =  1;
    if ( map->height > 1)
        y_range = map->height - 1;
    else
        y_range = 1;

    min_z = 1e9;
    max_z = -1e9;

    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
        {
            float z = map->points[y][x].pos.z;
            if (z < min_z) min_z = z;
            if (z > max_z) max_z = z;
        }
    float z_range = (max_z - min_z);
    if (z_range < 1e-6) z_range = 1.0f;

    float xy_range = (x_range + y_range) / 2.0f;
    proj->z_scale = xy_range / z_range * 0.5f; // 0.5fは調整用
    if (proj->z_scale > 10.0f) proj->z_scale = 10.0f;
    if (proj->z_scale < 0.05f) proj->z_scale = 0.05f;
}