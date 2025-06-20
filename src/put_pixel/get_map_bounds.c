/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bounds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:28:15 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 16:28:24 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// マップの最大範囲を調べる
void	get_map_bounds(
    t_mapdata *mapdata, float *max_x, float *max_y, float *min_x, float *min_y)
{
    int	x;
    int	y;

    *max_x = *max_y = -1e9;
    *min_x = *min_y = 1e9;
    y = 0;
    while (y < mapdata->height)
    {
        x = 0;
        while (x < mapdata->width)
        {
            if (mapdata->map[y][x].pos.x > *max_x)
                *max_x = mapdata->map[y][x].pos.x;
            if (mapdata->map[y][x].pos.x < *min_x)
                *min_x = mapdata->map[y][x].pos.x;
            if (mapdata->map[y][x].pos.y > *max_y)
                *max_y = mapdata->map[y][x].pos.y;
            if (mapdata->map[y][x].pos.y < *min_y)
                *min_y = mapdata->map[y][x].pos.y;
            x++;
        }
        y++;
    }
}