/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:41:44 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:44:28 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_slider_and_redraw(t_ui *ui, t_slider *s, int x)
{
	s->value = (x - s->x) * (s->max - s->min) / s->w + s->min;
	ui->proj.z_angle = (float)s->value;
	if (ui->image.img)
		mlx_destroy_image(ui->mlx, ui->image.img);
	ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
	ui->image.img_data = mlx_get_data_addr(
			ui->image.img, &ui->image.bpp,
			&ui->image.size_lien, &ui->image.endian);
	draw_map(ui, &ui->maps->maps[ui->maps->current]);
	draw_ui(ui);
	mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);
}

static int	is_slider_clicked(t_slider *s, int x, int y)
{
	return (y >= s->y - 10 && y <= s->y + 10
		&& x >= s->x && x <= s->x + s->w);
}

static int	try_slider_click(int btn, int x, int y, t_ui *ui)
{
	t_slider	*s;

	s = &ui->slider;
	if (btn == 1 && is_slider_clicked(s, x, y))
	{
		update_slider_and_redraw(ui, s, x);
		return (1);
	}
	return (0);
}

static void	try_button_click(int x, int y, t_ui *ui)
{
	int			i;
	t_button	*b;

	i = 0;
	while (i < ui->button_count)
	{
		b = &ui->buttons[i];
		if (x >= b->x && x <= b->x + b->w
			&& y >= b->y && y <= b->y + b->h)
		{
			b->on_click(ui);
			break ;
		}
		i++;
	}
}

int	mouse_click(int btn, int x, int y, void *p)
{
	t_ui	*ui;

	ui = (t_ui *)p;
	if (try_slider_click(btn, x, y, ui))
		return (0);
	try_button_click(x, y, ui);
	return (0);
}
