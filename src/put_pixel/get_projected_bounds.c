/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_projected_bounds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:27:25 by msakata           #+#    #+#             */
/*   Updated: 2025/06/21 06:01:18 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 投影前の座標を計算（zスケールなし）
void	get_projected_bounds(t_mapdata *mapdata, float *min_px, float *max_px, float *min_py, float *max_py)
{
    int		x;
    int		y;
    float	angle;
    float	px;
    float	py;

    angle = M_PI / 6.0;
    *min_px = *min_py = 1e9;
    *max_px = *max_py = -1e9;
    y = 0;
    while (y < mapdata->height)
    {
        x = 0;
        while (x < mapdata->width)
        {
            px = (mapdata->map[y][x].pos.x - mapdata->map[y][x].pos.y)
                * cos(angle);
            py = (mapdata->map[y][x].pos.x + mapdata->map[y][x].pos.y)
                * sin(angle) - mapdata->map[y][x].pos.z;
            if (px < *min_px)
                *min_px = px;
            if (px > *max_px)
                *max_px = px;
            if (py < *min_py)
                *min_py = py;
            if (py > *max_py)
                *max_py = py;
            x++;
        }
        y++;
    }
}