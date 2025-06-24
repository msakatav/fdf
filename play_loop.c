#include "fdf.h"
#include "read_map.h"

int play_loop(void *param)
{
    t_ui *ui = (t_ui *)param;
    if (ui->mode == MODE_PLAY) {
        ui->proj.z_angle += 2.0f; // 2度ずつ回転（速度は調整可）
        if (ui->proj.z_angle >= 360.0f)
            ui->proj.z_angle -= 360.0f;

        // 画像再生成・再描画
        if (ui->image.img)
            mlx_destroy_image(ui->mlx, ui->image.img);
        ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
        ui->image.img_data = mlx_get_data_addr(
            ui->image.img, &ui->image.bpp,
            &ui->image.size_lien, &ui->image.endian);

        // 投影パラメータにz_angleを反映
        ui->proj.proj.z_angle = ui->proj.z_angle; // ← draw_mapでこの値を使うようにする

        draw_map(ui, &ui->maps->maps[ui->maps->current]);
        draw_ui(ui);
        mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 500, 100);
    }
    return 0;
}