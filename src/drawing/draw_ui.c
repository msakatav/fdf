/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:28:53 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:28:55 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_ui(t_ui *ui)
{
    // UI全体再描画: ウィンドウクリア→文字/string表示
    mlx_clear_window(ui->mlx, ui->win);

    // --- キーバインド一覧 ---
    mlx_string_put(ui->mlx, ui->win, 20, 30, 0xFFFFFF, "Key Bindings:");
    mlx_string_put(ui->mlx, ui->win, 20, 60, 0xFFFFFF, "W/A/S/D : Move camera");
    mlx_string_put(ui->mlx, ui->win, 20, 90, 0xFFFFFF, "Mouse Wheel : Zoom");
    // mlx_string_put(ui->mlx, ui->win, 20, 120, 0xFFFFFF, "C : Toggle Cube Mode");
    // mlx_string_put(ui->mlx, ui->win, 20, 150, 0xFFFFFF, "G : Toggle Grid/Sphere Mode");
    // mlx_string_put(ui->mlx, ui->win, 20, 180, 0xFFFFFF, "P : Play/Stop Rotation");
    // mlx_string_put(ui->mlx, ui->win, 20, 210, 0xFFFFFF, "Left/Right : Change Map");
    mlx_string_put(ui->mlx, ui->win, 20, 120, 0xFFFFFF, "ESC : Exit");

    // image placeholder
    mlx_string_put(ui->mlx, ui->win, 900, 360, 0xFFFFFF, "image");

    // file list (display only)
    int i = 0;
    int wpase = 0;
    while (i < ui->maps->count)
    {
        mlx_string_put(ui->mlx, ui->win, 1650, 100 + wpase, 0xFFFFFF, ui->maps->maps[i].filename);
        wpase += 60;
        i++;
    }
    // mlx_string_put(ui->mlx, ui->win, 1650, 100, 0xFFFFFF, "sample.fdf");
    // mlx_string_put(ui->mlx, ui->win, 1650, 160, 0xFFFFFF, "42.fdf");

    // current file
    mlx_string_put(ui->mlx, ui->win, 850, 750, 0xFFFFFF, ui->maps->maps[ui->maps->current].filename);

    // slider
    draw_slider(ui);

    // buttons
    for (int i = 0; i < ui->button_count; i++) {
        t_button *b = &ui->buttons[i];
        int is_active = 0;
        if ((b->on_click == on_cube && ui->cube_mode == MODE_CUBE) ||
            (b->on_click == on_play && ui->mode == MODE_PLAY) ||
            (b->on_click == on_grid && ui->grid_mode == MODE_GRID))
            is_active = 1;
        if (is_active && b->img_active)
            mlx_put_image_to_window(ui->mlx, ui->win, b->img_active, b->x, b->y);
        else if (b->img)
            mlx_put_image_to_window(ui->mlx, ui->win, b->img, b->x, b->y);
        // 画像がない場合は文字で
        else
            mlx_string_put(ui->mlx, ui->win, b->x + 10, b->y + 20, 0x00FF00, b->label);
    }
}