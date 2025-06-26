/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:47:25 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:47 by msakata          ###   ########.fr       */
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
	ft_memset(ui->image.img_data, 0, WIDTH * HEIGHT * (ui->image.bpp / 8));
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
