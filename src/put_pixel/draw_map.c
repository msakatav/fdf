/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:25:07 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 16:25:28 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// --- マップ描画関数 ---
void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	t_screen	p;
	t_screen	p_right;
	t_screen	p_down;

	y = 0;
	while (y < fdf->mapdata.height)
	{
		x = 0;
		while (x < fdf->mapdata.width)
		{
			p = iso_project(fdf->mapdata.map[y][x].pos, &fdf->projinfo);
			if (x + 1 < fdf->mapdata.width)
			{
				p_right = iso_project(fdf->mapdata.map[y][x + 1].pos, &fdf->projinfo);
				draw_line_lerp(fdf->mlxinfo.img_data, p, p_right,
					fdf->mapdata.map[y][x].color, fdf->mapdata.map[y][x + 1].color,
					fdf->mlxinfo.size_lien, fdf->mlxinfo.bpp);
			}
			if (y + 1 < fdf->mapdata.height)
			{
				p_down = iso_project(fdf->mapdata.map[y + 1][x].pos, &fdf->projinfo);
				draw_line_lerp(fdf->mlxinfo.img_data, p, p_down,
					fdf->mapdata.map[y][x].color, fdf->mapdata.map[y + 1][x].color,
					fdf->mlxinfo.size_lien, fdf->mlxinfo.bpp);
			}
			x++;
		}
		y++;
	}
}