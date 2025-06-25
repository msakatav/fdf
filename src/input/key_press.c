/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:07:28 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:07:29 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * キー入力で平行移動 (WASD) と ESC 
 *  (メイン側で mlx_hook または mlx_key_hook などで登録してください)
 */
int key_press(int keycode, void *param)
{
    t_ui *ui = (t_ui *)param;
    if (keycode == 65307) // ESC
    {
        mlx_destroy_window(ui->mlx, ui->win);
        exit(0);
    }
    else if (keycode == 'w')
        ui->camera.offset_y -= 10.0f;
    else if (keycode == 's')
        ui->camera.offset_y += 10.0f;
    else if (keycode == 'a')
        ui->camera.offset_x -= 10.0f;
    else if (keycode == 'd')
        ui->camera.offset_x += 10.0f;

    // 再描画 (イメージ破棄→新規イメージ→マップ描画→ウィンドウに出力)
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