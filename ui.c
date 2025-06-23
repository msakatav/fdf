// fdf_ui_template.c
#include "fdf.h"
#include "read_map.h"

// ---------------- Callbacks ------------------
void on_cube(void *p) { printf("[cube]\n"); }
void on_prev(void *p)
{
    t_ui *ui = (t_ui *)p;
    if (!ui->maps) return;

    if (ui->maps->current > 0)
        ui->maps->current--;
    else
        ui->maps->current = ui->maps->count - 1;

    if (ui->image.img)
        mlx_destroy_image(ui->mlx, ui->image.img);
    ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
    ui->image.img_data = mlx_get_data_addr(
        ui->image.img, &ui->image.bpp,
        &ui->image.size_lien, &ui->image.endian);

    // スケール計算
    float min_px, max_px, min_py, max_py;
    get_projected_bounds(&ui->maps->maps[ui->maps->current], &ui->proj,
                         &min_px, &max_px, &min_py, &max_py);
    set_scale_and_offset(&ui->proj, min_px, max_px, min_py, max_py);
    adjust_z_scale(&ui->maps->maps[ui->maps->current], &ui->proj);

    // 再描画
    draw_map(ui, &ui->maps->maps[ui->maps->current]);
    draw_ui(ui);
    mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 400, 100);
}
void on_play(void *p) { printf("[play]\n"); }
void on_next(void *p)
{
    t_ui *ui = (t_ui *)p;
    if (!ui->maps) return;

    if (ui->maps->current < ui->maps->count - 1)
        ui->maps->current++;
    else
        ui->maps->current = 0;

    // ★ ここで新しいマップに対して再度スケール等を計算する
    // イメージを初期化し直す (古いイメージ破棄、再作成)
    if (ui->image.img)
        mlx_destroy_image(ui->mlx, ui->image.img);
    ui->image.img = mlx_new_image(ui->mlx, WIDTH, HEIGHT);
    ui->image.img_data = mlx_get_data_addr(
        ui->image.img, &ui->image.bpp,
        &ui->image.size_lien, &ui->image.endian);

    // スケール計算
    float min_px, max_px, min_py, max_py;
    get_projected_bounds(&ui->maps->maps[ui->maps->current], &ui->proj,
                         &min_px, &max_px, &min_py, &max_py);
    set_scale_and_offset(&ui->proj, min_px, max_px, min_py, max_py);
    adjust_z_scale(&ui->maps->maps[ui->maps->current], &ui->proj);

    // 再描画
    draw_map(ui, &ui->maps->maps[ui->maps->current]);
    draw_ui(ui);
    mlx_put_image_to_window(ui->mlx, ui->win, ui->image.img, 400, 100);
}
void on_grid(void *p) { printf("[grid]\n"); }

// ---------------- Helpers ------------------
void add_button(t_ui *ui, int x, int y, char *label, void (*cb)(void *)) {
    t_button *b = &ui->buttons[ui->button_count++];
    b->x = x; b->y = y; b->w = 60; b->h = 60; b->label = label; b->on_click = cb;
}

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

void draw_ui(t_ui *ui)
{
    // UI全体再描画: ウィンドウクリア→文字/string表示
    mlx_clear_window(ui->mlx, ui->win);
    mlx_string_put(ui->mlx, ui->win, 20, 30, 0xFFFFFF, "info");
    mlx_string_put(ui->mlx, ui->win, 20, 70, 0xFFFFFF, "size: x=42, y=20");
    mlx_string_put(ui->mlx, ui->win, 20, 100, 0xFFFFFF, "vertices: 840");
    mlx_string_put(ui->mlx, ui->win, 20, 130, 0xFFFFFF, "z_max: 128");
    mlx_string_put(ui->mlx, ui->win, 20, 160, 0xFFFFFF, "z_min: -16");

    // image placeholder
    mlx_string_put(ui->mlx, ui->win, 900, 360, 0xFFFFFF, "image");

    // file list (display only)
    mlx_string_put(ui->mlx, ui->win, 1650, 100, 0xFFFFFF, "sample.fdf");
    mlx_string_put(ui->mlx, ui->win, 1650, 160, 0xFFFFFF, "42.fdf");

    // current file
    mlx_string_put(ui->mlx, ui->win, 850, 750, 0xFFFFFF, "sample.fdf");

    // slider
    draw_slider(ui);

    // buttons
    for (int i = 0; i < ui->button_count; i++) {
        t_button *b = &ui->buttons[i];
        mlx_string_put(ui->mlx, ui->win, b->x + 10, b->y + 20, 0x00FF00, b->label);
    }
}

int mouse_click(int btn, int x, int y, void *p)
{
    // ボタン等の当たり判定
    t_ui *ui = (t_ui *)p;
    t_slider *s = &ui->slider;

    if (btn == 1 && y >= s->y - 10 && y <= s->y + 10 && x >= s->x && x <= s->x + s->w) {
        s->value = (x - s->x) * (s->max - s->min) / s->w + s->min;
        printf("angle: %d\n", s->value);
        draw_ui(ui);
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


