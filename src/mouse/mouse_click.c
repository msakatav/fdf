#include "fdf.h"

int mouse_click(int btn, int x, int y, void *p)
{
    // ボタン等の当たり判定
    t_ui *ui = (t_ui *)p;
    t_slider *s = &ui->slider;

    if (btn == 1 && y >= s->y - 10 && y <= s->y + 10 && x >= s->x && x <= s->x + s->w) {
        s->value = (x - s->x) * (s->max - s->min) / s->w + s->min;
        ui->proj.z_angle = (float)s->value;
        printf("angle: %d\n", s->value);
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
        return 0;
    }
    for (int i = 0; i < ui->button_count; i++)
    {
        t_button *b = &ui->buttons[i];
        if (x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h)
        {
            b->on_click(ui);
            break; 
        }
    }
    return 0;
}


