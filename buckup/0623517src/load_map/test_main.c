#include <stdio.h>
#include "read_map.h"

int main(int argc, char **argv)
{
    t_maps maps;
    if (argc < 2)
    {
        printf("Usage: %s map1.fdf [map2.fdf ...]\n", argv[0]);
        return 1;
    }
    int loaded = load_maps_from_args(argc, argv, &maps);


    t_ui ui;
    ui.mlx = mlx_init();
    ui.win = mlx_new_window(ui.mlx, WIN_W, WIN_H, "FDF Viewer UI");
    ui.button_count = 0;

    add_button(&ui, 400, 900, "[■]", on_cube);
    add_button(&ui, 500, 900, "[<<]", on_prev);
    add_button(&ui, 600, 900, "[>]", on_play);
    add_button(&ui, 700, 900, "[>>]", on_next);
    add_button(&ui, 800, 900, "[#]", on_grid);

    ui.slider.x = 400;
    ui.slider.y = 850;
    ui.slider.w = 900;
    ui.slider.min = 0;
    ui.slider.max = 360;
    ui.slider.value = 180;
    ui.slider.knob_radius = 6;

    draw_ui(&ui, &maps.maps[0]);
    mlx_mouse_hook(ui.win, mouse_click, &ui);
    mlx_loop(ui.mlx);

    return 0;
}