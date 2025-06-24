#include "read_map.h"
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

// iso_projectで camera.offset_x, offset_y, zoom を考慮
t_screen iso_project(t_vec3 pos, t_projinfo *proj, t_camera *cam)
{
    float angle = M_PI / 6.0f;
    float x = (pos.x - pos.y) * cosf(angle);
    float y = (pos.x + pos.y) * sinf(angle) - pos.z * proj->z_scale;

    t_screen result;
    result.x = WIDTH / 2 + (x - proj->offset_x + cam->offset_x) * proj->scale * cam->zoom;
    result.y = HEIGHT / 2 + (y - proj->offset_y + cam->offset_y) * proj->scale * cam->zoom;
    return (result);
}

t_screen perspective_project(t_vec3 pos, t_projinfo *proj, t_camera *cam)
{
    float angle = M_PI / 6.0f;
    // 等角投影と同じ奥行き計算
    float px = (pos.x - pos.y) * cosf(angle);
    float py = (pos.x + pos.y) * sinf(angle);

    // カメラ操作反映
    px = (px - proj->offset_x + cam->offset_x) * proj->scale * cam->zoom;
    py = (py - proj->offset_y + cam->offset_y) * proj->scale * cam->zoom;

    // 透視投影: 奥行き(depth)でスケール
    float camera_z = 1000.0f;
    float fov = 800.0f;
    float depth = camera_z - py; // 奥行きはpyで近似
    if (depth < 1.0f) depth = 1.0f; // 0割防止
    float factor = fov / depth;

    t_screen result;
    result.x = WIDTH / 2 + px * factor;
    // 高さzはy座標に反映
    result.y = HEIGHT / 2 + (py - pos.z * proj->z_scale * proj->scale * cam->zoom) * factor;
    return result;
}

