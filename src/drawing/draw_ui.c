/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:28:53 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:40:58 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_key_bindings(t_ui *ui)
{
	mlx_string_put(ui->mlx, ui->win, 20, 30, 0xFFFFFF, "Key Bindings:");
	mlx_string_put(ui->mlx, ui->win, 20, 60, 0xFFFFFF, "W/A/S/D : Move camera");
	mlx_string_put(ui->mlx, ui->win, 20, 90, 0xFFFFFF, "Mouse Wheel : Zoom");
	mlx_string_put(ui->mlx, ui->win, 20, 120, 0xFFFFFF, "ESC : Exit");
}

static void	draw_file_list(t_ui *ui)
{
	int	i;
	int	wpase;

	i = 0;
	wpase = 0;
	while (i < ui->maps->count)
	{
		mlx_string_put(ui->mlx, ui->win, 1650, 100 + wpase,
			0xFFFFFF, ui->maps->maps[i].filename);
		wpase += 60;
		i++;
	}
}

static void	draw_buttons(t_ui *ui)
{
	int			i;
	t_button	*b;
	int			is_active;

	i = 0;
	while (i < ui->button_count)
	{
		b = &ui->buttons[i];
		is_active = 0;
		if ((b->on_click == on_cube && ui->cube_mode == MODE_CUBE)
			|| (b->on_click == on_play && ui->mode == MODE_PLAY)
			|| (b->on_click == on_grid && ui->grid_mode == MODE_GRID))
			is_active = 1;
		if (is_active && b->img_active)
			mlx_put_image_to_window(ui->mlx, ui->win, b->img_active,
				b->x, b->y);
		else if (b->img)
			mlx_put_image_to_window(ui->mlx, ui->win, b->img, b->x, b->y);
		else
			mlx_string_put(ui->mlx, ui->win, b->x + 10, b->y + 20,
				0x00FF00, b->label);
		i++;
	}
}

void	draw_ui(t_ui *ui)
{
	mlx_clear_window(ui->mlx, ui->win);
	draw_key_bindings(ui);
	mlx_string_put(ui->mlx, ui->win, 900, 360, 0xFFFFFF, "image");
	draw_file_list(ui);
	mlx_string_put(ui->mlx, ui->win, 850, 750, 0xFFFFFF,
		ui->maps->maps[ui->maps->current].filename);
	draw_slider(ui);
	draw_buttons(ui);
}
