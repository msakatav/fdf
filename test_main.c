#include "read_map.h"
#include "fdf.h"

int main(int argc, char **argv)
{
    t_maps maps;
    if (argc < 2)
    {
        printf("Usage: %s map1.fdf [map2.fdf ...]\n", argv[0]);
        return 1;
    }
    load_maps_from_args(argc, argv, &maps);

    // UI構造体
    t_ui ui;
    ui.mlx = mlx_init();
    ui.win = mlx_new_window(ui.mlx, WIN_W, WIN_H, "FDF Viewer UI");
    ui.button_count = 0;
    ui.proj.offset_x = 0;
    ui.proj.offset_y = 0;
    ui.proj.scale = 1.0f;
    ui.proj.z_scale = 1.0f;
    ui.maps = &maps;

    // カメラ初期値
    ui.camera.offset_x = 0.0f;
    ui.camera.offset_y = 0.0f;
    ui.camera.zoom     = 1.0f;

    // ボタン
    add_button(&ui, 400, 900, "[■]", "./icon/cube.xpm", "./icon/cube.xpm", on_cube);
    add_button(&ui, 650, 900, "[<<]", "./icon/prev.xpm", "./icon/prev.xpm", on_prev);
    add_button(&ui, 1650/2, 900, "[>]", "./icon/play.xpm", "./icon/pause.xpm", on_play);
    add_button(&ui, 1000, 900, "[>>]", "./icon/next.xpm", "./icon/next.xpm", on_next);
    add_button(&ui, 1250, 900, "[#]", "./icon/grid.xpm", "./icon/radio.xpm", on_grid);

    // スライダー
    ui.slider.x = 400;
    ui.slider.y = 850;
    ui.slider.w = 900;
    ui.slider.min = 0;
    ui.slider.max = 360;
    ui.slider.value = 180;
    ui.slider.knob_radius = 6;

    // イメージバッファ
    ui.image.img = mlx_new_image(ui.mlx, WIDTH, HEIGHT);
    ui.image.img_data = mlx_get_data_addr(
        ui.image.img, &ui.image.bpp, &ui.image.size_lien, &ui.image.endian);

    // --- スケール計算と描画 ---
    // 1. zスケール自動調整
    adjust_z_scale(&maps.maps[maps.current], &ui.proj);

    // 2. 投影範囲取得
    float min_px, max_px, min_py, max_py;
    get_projected_bounds(&maps.maps[maps.current], &ui.proj,
                         &min_px, &max_px, &min_py, &max_py);

    // 3. スケール・オフセット決定
    set_scale_and_offset(&ui.proj, min_px, max_px, min_py, max_py);

    // 4. マップ描画
    draw_map(&ui, &maps.maps[maps.current]);

    // UI描画
    draw_ui(&ui);
    mlx_put_image_to_window(ui.mlx, ui.win, ui.image.img, 500, 100);

    // イベントフック
    mlx_hook(ui.win, 5, 1L << 3, mouse_click, &ui);
    // キー入力(押下)をフック
    mlx_hook(ui.win, 2, 1L << 0, key_press, &ui);
    mlx_hook(ui.win, 4, 1L << 2, mouse_scroll, &ui);
    mlx_loop(ui.mlx);
    return 0;
}