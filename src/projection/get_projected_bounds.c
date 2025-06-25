/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_projected_bounds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 02:55:04 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 02:55:07 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ----------------------- 投影後の座標範囲を取得 -----------------------
void get_projected_bounds(t_map *map, t_projinfo *proj,
                          float *min_px, float *max_px,
                          float *min_py, float *max_py)
{
    float angle = M_PI / 6.0f;
    *min_px = *min_py = 1e9;
    *max_px = *max_py = -1e9;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            float px = (map->points[y][x].pos.x - map->points[y][x].pos.y) * cosf(angle);
            float py = (map->points[y][x].pos.x + map->points[y][x].pos.y) * sinf(angle)
                       - map->points[y][x].pos.z * proj->z_scale;
            if (px < *min_px) *min_px = px;
            if (px > *max_px) *max_px = px;
            if (py < *min_py) *min_py = py;
            if (py > *max_py) *max_py = py;
        }
    }
}