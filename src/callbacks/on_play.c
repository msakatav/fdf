/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:25:09 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 07:10:09 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	on_play(void *p)
{
	t_ui	*ui;

	ui = (t_ui *)p;
	if (ui->mode == MODE_PLAY)
		ui->mode = MODE_NONE;
	else
		ui->mode = MODE_PLAY;
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
