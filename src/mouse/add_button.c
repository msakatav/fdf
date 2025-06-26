/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:27:17 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:36:51 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_button(t_ui *ui, t_button_param *param)
{
	t_button	*b;

	b = &ui->buttons[ui->button_count++];
	b->x = param->x;
	b->y = param->y;
	b->w = 60;
	b->h = 60;
	b->label = param->label;
	b->on_click = param->cb;
	b->img = mlx_xpm_file_to_image(ui->mlx, param->img_path, &b->w, &b->h);
	b->img_active = mlx_xpm_file_to_image(ui->mlx, param->img_active_path, &b->w, &b->h);
}