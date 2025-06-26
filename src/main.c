/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:12 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 13:07:13 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_fdf_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".fdf") == 0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	setup_projection_and_draw(t_ui *ui, t_maps *maps)
{
	t_bounds	bounds;

	adjust_z_scale(&maps->maps[maps->current], &ui->proj);
	get_projected_bounds(&maps->maps[maps->current], &ui->proj, &bounds);
	set_scale_and_offset(&ui->proj, &bounds);
	draw_map(ui, &maps->maps[maps->current]);
	draw_ui(ui);
	mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);
}

void	setup_hooks(t_ui *ui)
{
	ui->proj.z_angle = 0.0f;
	mlx_loop_hook(ui->mlx, play_loop, ui);
	mlx_hook(ui->win, 5, 1L << 3, mouse_click, ui);
	mlx_hook(ui->win, 2, 1L << 0, key_press, ui);
	mlx_hook(ui->win, 4, 1L << 2, mouse_scroll, ui);
	mlx_hook(ui->win, 17, 1L << 17, close_window, ui);
}

int	main(int argc, char **argv)
{
	t_maps	maps;
	t_ui	ui;
	char	*fdf_argv[1024];
	int		fdf_argc;

	if (argc < 2)
	{
		ft_printf("Usage: %s map1.fdf [map2.fdf ...]\n", argv[0]);
		return (1);
	}
	fdf_argc = filter_fdf_files(argc, argv, fdf_argv);
	if (fdf_argc == 1)
	{
		ft_printf("No .fdf files specified.\n");
		return (1);
	}
	load_maps_from_args(fdf_argc, fdf_argv, &maps);
	init_ui(&ui, &maps);
	setup_projection_and_draw(&ui, &maps);
	setup_hooks(&ui);
	mlx_loop(ui.mlx);
	return (0);
}
