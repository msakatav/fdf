/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:47:25 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 16:39:47 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_z_angle_and_slider(t_ui *ui)
{
	ui->proj.z_angle += 0.5f;
	if (ui->proj.z_angle >= 360.0f)
		ui->proj.z_angle -= 360.0f;
	ui->slider.value = (int)ui->proj.z_angle;
}

static void	redraw_play_frame(t_ui *ui)
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

int	play_loop(void *param)
{
	t_ui	*ui;

	ui = (t_ui *)param;
	if (ui->mode == MODE_PLAY)
	{
		update_z_angle_and_slider(ui);
		redraw_play_frame(ui);
	}
	return (0);
}
