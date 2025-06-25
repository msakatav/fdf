/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slider.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:28:11 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:39:01 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_slider_labels(t_ui *ui, t_slider *s)
{
	mlx_string_put(ui->mlx, ui->win, s->x - 20, s->y + 5, 0xFFFFFF, "0");
	mlx_string_put(ui->mlx, ui->win, s->x + s->w + 10,
		s->y + 5, 0xFFFFFF, "360");
}

static void	draw_slider_bar(t_ui *ui, t_slider *s)
{
	int	i;

	i = 0;
	while (i < s->w)
	{
		mlx_pixel_put(ui->mlx, ui->win, s->x + i, s->y, 0xFFFFFF);
		i++;
	}
}

static void	draw_slider_knob(t_ui *ui, t_slider *s, int knob_x)
{
	int	dx;
	int	dy;

	dx = -s->knob_radius;
	while (dx <= s->knob_radius)
	{
		dy = -s->knob_radius;
		while (dy <= s->knob_radius)
		{
			if (dx * dx + dy * dy <= s->knob_radius * s->knob_radius)
				mlx_pixel_put(ui->mlx, ui->win, knob_x + dx,
					s->y + dy, 0xFFFFFF);
			dy++;
		}
		dx++;
	}
}

void	draw_slider(t_ui *ui)
{
	t_slider	*s;
	int			knob_x;

	s = &ui->slider;
	knob_x = s->x + (s->value - s->min) * s->w / (s->max - s->min);
	draw_slider_labels(ui, s);
	draw_slider_bar(ui, s);
	draw_slider_knob(ui, s, knob_x);
}
