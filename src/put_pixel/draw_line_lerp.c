/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_lerp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:25:42 by msakata           #+#    #+#             */
/*   Updated: 2025/06/21 06:02:08 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 線描画（色補間対応）
void	draw_line_lerp(char *data, t_screen a, t_screen b, int color_a, int color_b, int size_lien, int bpp)
{
    int	dx;
    int	dy;
    int	sx;
    int	sy;
    int	err;
    int	len;
    int	step;
    int	x;
    int	y;
    int	e2;
    float	t;
    int	color;

    dx = abs(b.x - a.x);
    dy = abs(b.y - a.y);
    sx = (a.x < b.x) ? 1 : -1;
    sy = (a.y < b.y) ? 1 : -1;
    err = dx - dy;
    len = dx > dy ? dx : dy;
    step = 0;
    x = a.x;
    y = a.y;
    while (1)
    {
        t = len ? (float)step / len : 0.0f;
        color = lerp_color(color_a, color_b, t);
        put_pixel(data, x, y, color, size_lien, bpp);
        if (x == b.x && y == b.y)
            break ;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
        step++;
    }
}