/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:08:16 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:08:19 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * マウスホイールでズーム (上下ホイール)
 *  (メイン側で mlx_mouse_hook などで登録してください)
 */
int mouse_scroll(int button, int x, int y, void *param)
{
    t_ui *ui = (t_ui *)param;
    (void)x; 
    (void)y;

    // ズーム倍率の上限・下限
    const float ZOOM_MIN = 0.2f;
    const float ZOOM_MAX = 5.0f;

    if (button == 4) // ホイールアップ
    {
        ui->camera.zoom *= 1.1f;
        if (ui->camera.zoom > ZOOM_MAX)
            ui->camera.zoom = ZOOM_MAX;
    }
    else if (button == 5) // ホイールダウン
    {
        ui->camera.zoom *= 0.9f;
        if (ui->camera.zoom < ZOOM_MIN)
            ui->camera.zoom = ZOOM_MIN;
    }

    // ズーム後、再描画
    if (ui->image.img)
        mlx_destroy_image(ui->mlx, ui->image.img);
    ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
    ui->image.img_data = mlx_get_data_addr(
        ui->image.img, &ui->image.bpp, &ui->image.size_lien, &ui->image.endian);

    draw_map(ui, &ui->maps->maps[ui->maps->current]);
    draw_ui(ui);
    mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);

    return (0);
}