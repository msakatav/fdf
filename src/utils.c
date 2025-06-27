/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:00:41 by msakata           #+#    #+#             */
/*   Updated: 2025/06/27 12:38:18 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	filter_fdf_files(int argc, char **argv, char **fdf_argv)
{
	int	i;
	int	fdf_argc;

	fdf_argc = 1;
	fdf_argv[0] = argv[0];
	i = 1;
	while (i < argc)
	{
		if (is_fdf_file(argv[i]))
		{
			fdf_argv[fdf_argc] = argv[i];
			fdf_argc++;
		}
		i++;
	}
	return (fdf_argc);
}

static void	init_ui_proj_and_camera(t_ui *ui, t_maps *maps)
{
	ui->button_count = 0;
	ui->proj.offset_x = 0;
	ui->proj.offset_y = 0;
	ui->proj.scale = 1.0f;
	ui->proj.z_scale = 1.0f;
	ui->maps = maps;
	ui->camera.offset_x = 0.0f;
	ui->camera.offset_y = 0.0f;
	ui->camera.zoom = 1.0f;
}

static void	init_ui_buttons(t_ui *ui)
{
	int				i;
	t_button_param	btns[5];

	btns[0] = (t_button_param){400, 900, "[■]", "./icon/cube.xpm",
		"./icon/cube.xpm", on_cube};
	btns[1] = (t_button_param){650, 900, "[<<]", "./icon/prev.xpm",
		"./icon/prev.xpm", on_prev};
	btns[2] = (t_button_param){1650 / 2, 900, "[>]", "./icon/play.xpm",
		"./icon/pause.xpm", on_play};
	btns[3] = (t_button_param){1000, 900, "[>>]", "./icon/next.xpm",
		"./icon/next.xpm", on_next};
	btns[4] = (t_button_param){1250, 900, "[#]", "./icon/grid.xpm",
		"./icon/radio.xpm", on_grid};
	i = 0;
	while (i < 5)
	{
		add_button(ui, &btns[i]);
		i++;
	}
}

static void	init_ui_slider_and_image(t_ui *ui)
{
	ui->slider.x = 400;
	ui->slider.y = 850;
	ui->slider.w = 900;
	ui->slider.min = 0;
	ui->slider.max = 360;
	ui->slider.value = 180;
	ui->slider.knob_radius = 6;
	ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
	ui->image.img_data = mlx_get_data_addr(
			ui->image.img, &ui->image.bpp, &ui->image.size_lien,
			&ui->image.endian);
}

void	init_ui(t_ui *ui, t_maps *maps)
{
	ui->mlx = mlx_init();
	if (ui->mlx == NULL)
		exit(1);
	ui->win = mlx_new_window(ui->mlx, WIN_W, WIN_H, "FDF Viewer");
	init_ui_proj_and_camera(ui, maps);
	init_ui_buttons(ui);
	init_ui_slider_and_image(ui);
}
