/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:21:58 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:22:00 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ---------------- Callbacks ------------------
void on_cube(void *p)
{
    t_ui *ui = (t_ui *)p;
    if (ui->cube_mode == MODE_CUBE)
        ui->cube_mode = MODE_NONE;
    else
        ui->cube_mode = MODE_CUBE;
        // ★ 画像再生成・マップ再描画
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