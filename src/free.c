/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:18:02 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 16:51:30 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ui(t_ui *ui)
{
    int	i;

    if (!ui)
        return ;
    if (ui->image.img)
        mlx_destroy_image(ui->mlx, ui->image.img);
    if (ui->win)
        mlx_destroy_window(ui->mlx, ui->win);
    i = 0;
    while (i < ui->button_count)
    {
        if (ui->buttons[i].img)
            mlx_destroy_image(ui->mlx, ui->buttons[i].img);
        if (ui->buttons[i].img_active)
            mlx_destroy_image(ui->mlx, ui->buttons[i].img_active);
        i++;
    }
    if (ui->mlx)
	{
        mlx_destroy_display(ui->mlx);
		free(ui->mlx);
	}
}

void	free_maps(t_maps *maps)
{
    int	i;
    int	y;

    if (!maps)
        return ;
    i = 0;
    while (i < maps->count)
    {
        if (maps->maps[i].points)
        {
            y = 0;
            while (y < maps->maps[i].height)
            {
                if (maps->maps[i].points[y])
                    free(maps->maps[i].points[y]);
                y++;
            }
            free(maps->maps[i].points);
        }
        i++;
    }
}

void	free_all(t_ui *ui)
{
    if (ui)
    {
        free_ui(ui);
        if (ui->maps)
            free_maps(ui->maps);
    }
}
