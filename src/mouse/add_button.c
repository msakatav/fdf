/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:27:17 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:27:19 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ---------------- Helpers ------------------
// add_button を修正して画像を読み込む
void add_button(t_ui *ui, int x, int y, char *label, char *img_path, char *img_active_path, void (*cb)(void *))
{
    t_button *b = &ui->buttons[ui->button_count++];
    b->x = x; b->y = y; b->w = 60; b->h = 60; b->label = label; b->on_click = cb;
    b->img = mlx_xpm_file_to_image(ui->mlx, img_path, &b->w, &b->h);
    b->img_active = mlx_xpm_file_to_image(ui->mlx, img_active_path, &b->w, &b->h);
}