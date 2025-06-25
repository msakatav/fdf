/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slider.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:28:11 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:28:12 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_slider(t_ui *ui) {
    t_slider *s = &ui->slider;
    int knob_x = s->x + (s->value - s->min) * s->w / (s->max - s->min);

    mlx_string_put(ui->mlx, ui->win, s->x - 20, s->y + 5, 0xFFFFFF, "0");
    mlx_string_put(ui->mlx, ui->win, s->x + s->w + 10, s->y + 5, 0xFFFFFF, "360");

    for (int i = 0; i < s->w; i++)
        mlx_pixel_put(ui->mlx, ui->win, s->x + i, s->y, 0xFFFFFF);

    for (int dx = -s->knob_radius; dx <= s->knob_radius; dx++) {
        for (int dy = -s->knob_radius; dy <= s->knob_radius; dy++) {
            if (dx * dx + dy * dy <= s->knob_radius * s->knob_radius)
                mlx_pixel_put(ui->mlx, ui->win, knob_x + dx, s->y + dy, 0xFFFFFF);
        }
    }
}