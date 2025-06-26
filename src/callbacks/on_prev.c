/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_prev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:11:08 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:52:58 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	switch_to_prev_map(t_ui *ui)
{
	if (ui->maps->current > 0)
		ui->maps->current--;
	else
		ui->maps->current = ui->maps->count - 1;
}

static void	reset_camera(t_ui *ui)
{
	ui->camera.offset_x = 0.0f;
	ui->camera.offset_y = 0.0f;
	ui->camera.zoom = 1.0f;
}

static void	reset_image(t_ui *ui)
{
	if (ui->image.img)
		mlx_destroy_image(ui->mlx, ui->image.img);
	ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
	ui->image.img_data = mlx_get_data_addr(
			ui->image.img, &ui->image.bpp,
			&ui->image.size_lien, &ui->image.endian);
}

static void	update_projection_and_draw(t_ui *ui)
{
	float	min_px;
	float	max_px;
	float	min_py;
	float	max_py;
    t_bounds bounds;

	adjust_z_scale(&ui->maps->maps[ui->maps->current], &ui->proj);
    get_projected_bounds(&maps.maps[maps.current], &ui.proj, &bounds);
    set_scale_and_offset(&ui.proj, bounds.min_px, bounds.max_px, bounds.min_py, bounds.max_py);
	draw_map(ui, &ui->maps->maps[ui->maps->current]);
	draw_ui(ui);
	mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);
}

void	on_prev(void *p)
{
	t_ui	*ui;

	ui = (t_ui *)p;
	if (!ui->maps)
		return ;
	switch_to_prev_map(ui);
	reset_camera(ui);
	reset_image(ui);
	update_projection_and_draw(ui);
}
