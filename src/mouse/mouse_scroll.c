/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:08:16 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:47:08 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_zoom(t_ui *ui, int button)
{
	const float	zoom_min = 0.2f;
	const float	zoom_max = 5.0f;

	if (button == 4)
	{
		ui->camera.zoom *= 1.1f;
		if (ui->camera.zoom > zoom_max)
			ui->camera.zoom = zoom_max;
	}
	else if (button == 5)
	{
		ui->camera.zoom *= 0.9f;
		if (ui->camera.zoom < zoom_min)
			ui->camera.zoom = zoom_min;
	}
}

static void	redraw_after_zoom(t_ui *ui)
{
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

int	mouse_scroll(int button, int x, int y, void *param)
{
	t_ui	*ui;

	(void)x;
	(void)y;
	ui = (t_ui *)param;
	update_zoom(ui, button);
	redraw_after_zoom(ui);
	return (0);
}
