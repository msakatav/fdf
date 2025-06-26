#include "fdf.h"

int	is_fdf_file(const char *filename)
{
    size_t	len = ft_strlen(filename);
    if (len < 4)
        return (0);
    return (ft_strcmp(filename + len - 4, ".fdf") == 0);
}

int	close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    t_maps maps;
    if (argc < 2)
    {
        ft_printf("Usage: %s map1.fdf [map2.fdf ...]\n", argv[0]);
        return 1;
    }

    // .fdfファイルのみ抽出
    char *fdf_argv[argc];
    int   fdf_argc = 1; // argv[0]はプログラム名
    fdf_argv[0] = argv[0];
    for (int i = 1; i < argc; i++)
    {
        if (is_fdf_file(argv[i]))
        {
            fdf_argv[fdf_argc] = argv[i];
            fdf_argc++;
        }
    }
    if (fdf_argc == 1)
    {
        ft_printf("No .fdf files specified.\n");
        return 1;
    }
    load_maps_from_args(fdf_argc, fdf_argv, &maps);

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
    t_button_param btns[] = {
        {400, 900, "[■]", "./icon/cube.xpm", "./icon/cube.xpm", on_cube},
        {650, 900, "[<<]", "./icon/prev.xpm", "./icon/prev.xpm", on_prev},
        {1650/2, 900, "[>]", "./icon/play.xpm", "./icon/pause.xpm", on_play},
        {1000, 900, "[>>]", "./icon/next.xpm", "./icon/next.xpm", on_next},
        {1250, 900, "[#]", "./icon/grid.xpm", "./icon/radio.xpm", on_grid}
    };
    for (int i = 0; i < 5; i++)
        add_button(&ui, &btns[i]);

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
    t_bounds bounds;
    get_projected_bounds(&maps.maps[maps.current], &ui.proj, &bounds);

    // 3. スケール・オフセット決定
    set_scale_and_offset(&ui.proj, &bounds);
    // 4. マップ描画
    draw_map(&ui, &maps.maps[maps.current]);

    // UI描画
    draw_ui(&ui);
    mlx_put_image_to_window(ui.mlx, ui.win, ui.image.img, 500, 100);

    ui.proj.z_angle = 0.0f;
    mlx_loop_hook(ui.mlx, play_loop, &ui);
    // イベントフック
    mlx_hook(ui.win, 5, 1L << 3, mouse_click, &ui);
    // キー入力(押下)をフック
    mlx_hook(ui.win, 2, 1L << 0, key_press, &ui);
    mlx_hook(ui.win, 4, 1L << 2, mouse_scroll, &ui);
    // バツボタンで終了
    mlx_hook(ui.win, 17, 1L << 17, close_window, &ui);

    mlx_loop(ui.mlx);
    return 0;
}