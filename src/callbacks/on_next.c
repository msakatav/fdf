#include "fdf.h"

void on_next(void *p)
{
    t_ui *ui = (t_ui *)p;
    if (!ui->maps) return;

    if (ui->maps->current < ui->maps->count - 1)
        ui->maps->current++;
    else
        ui->maps->current = 0;

        // カメラをリセット
    ui->camera.offset_x = 0.0f;
    ui->camera.offset_y = 0.0f;
    ui->camera.zoom     = 1.0f;

    // ★ ここで新しいマップに対して再度スケール等を計算する
    // イメージを初期化し直す (古いイメージ破棄、再作成)
    if (ui->image.img)
        mlx_destroy_image(ui->mlx, ui->image.img);
    ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
    ui->image.img_data = mlx_get_data_addr(
        ui->image.img, &ui->image.bpp,
        &ui->image.size_lien, &ui->image.endian);

    // スケール計算
    adjust_z_scale(&ui->maps->maps[ui->maps->current], &ui->proj);
    float min_px, max_px, min_py, max_py;
    get_projected_bounds(&ui->maps->maps[ui->maps->current], &ui->proj,
                         &min_px, &max_px, &min_py, &max_py);
    set_scale_and_offset(&ui->proj, min_px, max_px, min_py, max_py);

    // 再描画
    draw_map(ui, &ui->maps->maps[ui->maps->current]);
    draw_ui(ui);
    mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);
}