/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:07:28 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:53:45 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_move_keys(int keycode, t_ui *ui)
{
	if (keycode == 'w')
		ui->camera.offset_y -= 10.0f;
	else if (keycode == 's')
		ui->camera.offset_y += 10.0f;
	else if (keycode == 'a')
		ui->camera.offset_x -= 10.0f;
	else if (keycode == 'd')
		ui->camera.offset_x += 10.0f;
}

static void	redraw_all(t_ui *ui)
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

int	key_press(int keycode, void *param)
{
	t_ui	*ui;

	ui = (t_ui *)param;
	if (keycode == 65307)
	{
		mlx_destroy_window(ui->mlx, ui->win);
		exit(0);
	}
	handle_move_keys(keycode, ui);
	redraw_all(ui);
	return (0);
}
