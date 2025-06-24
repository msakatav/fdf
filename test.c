#include "fdf.h"

#define WIDTH 800
#define HEIGHT 600

// ----------------------- zスケール自動調整 -----------------------
void adjust_z_scale(t_map *map, t_projinfo *proj)
{
    float x_range = map->width  > 1 ? map->width  - 1 : 1;
    float y_range = map->height > 1 ? map->height - 1 : 1;

    float min_z = 1e9, max_z = -1e9;
    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
        {
            float z = map->points[y][x].pos.z;
            if (z < min_z) min_z = z;
            if (z > max_z) max_z = z;
        }
    float z_range = (max_z - min_z);
    if (z_range < 1e-6) z_range = 1.0f;

    float xy_range = (x_range + y_range) / 2.0f;
    proj->z_scale = xy_range / z_range * 0.5f; // 0.5fは調整用
    if (proj->z_scale > 10.0f) proj->z_scale = 10.0f;
    if (proj->z_scale < 0.05f) proj->z_scale = 0.05f;
}


// ----------------------- 投影後の座標範囲を取得 -----------------------
void get_projected_bounds(t_map *map, t_projinfo *proj,
                          float *min_px, float *max_px,
                          float *min_py, float *max_py)
{
    float angle = M_PI / 6.0f;
    *min_px = *min_py = 1e9;
    *max_px = *max_py = -1e9;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            float px = (map->points[y][x].pos.x - map->points[y][x].pos.y) * cosf(angle);
            float py = (map->points[y][x].pos.x + map->points[y][x].pos.y) * sinf(angle)
                       - map->points[y][x].pos.z * proj->z_scale;
            if (px < *min_px) *min_px = px;
            if (px > *max_px) *max_px = px;
            if (py < *min_py) *min_py = py;
            if (py > *max_py) *max_py = py;
        }
    }
}

// ----------------------- 全体スケールとオフセットを決定 -----------------------
void set_scale_and_offset(t_projinfo *proj,
                          float min_px, float max_px,
                          float min_py, float max_py)
{
    float proj_w = max_px - min_px;
    float proj_h = max_py - min_py;

    if (proj_w < 1.0f) proj_w = 1.0f;
    if (proj_h < 1.0f) proj_h = 1.0f;

    float scale_x = (WIDTH * 0.9f) / proj_w;   // 0.9fで余白
    float scale_y = (HEIGHT * 0.9f) / proj_h;

    proj->scale = (scale_x < scale_y) ? scale_x : scale_y;

    proj->offset_x = (min_px + max_px) * 0.5f;
    proj->offset_y = (min_py + max_py) * 0.5f;
}

// ----------------------- ピクセル & 線描画など -----------------------
void put_pixel(char *data, int x, int y, int color,
               int size_lien, int bpp)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    int index = y * size_lien + x * (bpp / 8);
    data[index + 0] = color & 0xff;
    data[index + 1] = (color >> 8) & 0xff;
    data[index + 2] = (color >> 16) & 0xff;
}

int lerp_color(int color1, int color2, float t)
{
    int r1 = (color1 >> 16) & 0xff;
    int g1 = (color1 >> 8) & 0xff;
    int b1 = color1 & 0xff;
    int r2 = (color2 >> 16) & 0xff;
    int g2 = (color2 >> 8) & 0xff;
    int b2 = color2 & 0xff;

    int r = r1 + (int)((r2 - r1) * t);
    int g = g1 + (int)((g2 - g1) * t);
    int b = b1 + (int)((b2 - b1) * t);
    return ((r << 16) | (g << 8) | b);
}

void draw_line_lerp(char *data, t_screen a, t_screen b,
                    int color_a, int color_b,
                    int size_lien, int bpp)
{
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = (a.x < b.x) ? 1 : -1;
    int sy = (a.y < b.y) ? 1 : -1;
    int err = dx - dy;
    int len = (dx > dy) ? dx : dy;
    int step = 0;
    int x = a.x, y = a.y;

    while (1)
    {
        float t = (len != 0) ? (float)step / (float)len : 0.0f;
        int color = lerp_color(color_a, color_b, t);
        put_pixel(data, x, y, color, size_lien, bpp);

        if (x == b.x && y == b.y)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx)  { err += dx; y += sy; }
        step++;
    }
}

// 球面座標変換（x, y → θ, φ → X, Y, Z）
void sphere_map_transform(int x, int y, int w, int h, float radius, float height, float *out_x, float *out_y, float *out_z)
{
    // θ: 経度 [0, 2π], φ: 緯度 [0, π]
    float theta = 2.0f * M_PI * x / (float)(w - 1);      // 0〜2π
    float phi   = M_PI * y / (float)(h - 1);             // 0〜π

    // 標高(height)を球面の法線方向に加算
    float r = radius + height;

    *out_x = r * sinf(phi) * cosf(theta);
    *out_y = r * sinf(phi) * sinf(theta);
    *out_z = r * cosf(phi);
}

// ----------------------- マップ描画関数（カメラ対応） -----------------------
void draw_map(t_ui *ui, t_map *map)
{
    float rad = ui->proj.z_angle * M_PI / 180.0f;
    float cosz = cosf(rad);
    float sinz = sinf(rad);

    float center_x = (map->width - 1) / 2.0f;
    float center_y = (map->height - 1) / 2.0f;

    // 球面用の半径（マップサイズに応じて調整）
    float radius = (map->width < map->height ? map->width : map->height) * 0.4f;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            t_vec3 orig = map->points[y][x].pos;
            t_vec3 tmp;

            if (ui->grid_mode == MODE_GRID) {
                // 球面座標変換
                sphere_map_transform(x, y, map->width, map->height, radius, orig.z * ui->proj.z_scale, &tmp.x, &tmp.y, &tmp.z);
            } else {
                // 通常
                tmp.x = orig.x - center_x;
                tmp.y = orig.y - center_y;
                tmp.z = orig.z;
            }

            // z軸回転
            t_vec3 rot;
            rot.x = tmp.x * cosz - tmp.y * sinz;
            rot.y = tmp.x * sinz + tmp.y * cosz;
            rot.z = tmp.z;

            // 元の位置に戻す（球面時は不要だが通常時のため残す）
            if (ui->grid_mode != MODE_GRID) {
                rot.x += center_x;
                rot.y += center_y;
            }

            t_screen p;
            if (ui->cube_mode == MODE_CUBE)
                p = perspective_project(rot, &ui->proj, &ui->camera);
            else
                p = iso_project(rot, &ui->proj, &ui->camera);

            // 右隣
            if (x + 1 < map->width)
            {
                t_vec3 orig_r = map->points[y][x + 1].pos;
                t_vec3 tmp_r;
                if (ui->grid_mode == MODE_GRID) {
                    sphere_map_transform(x + 1, y, map->width, map->height, radius, orig_r.z * ui->proj.z_scale, &tmp_r.x, &tmp_r.y, &tmp_r.z);
                } else {
                    tmp_r.x = orig_r.x - center_x;
                    tmp_r.y = orig_r.y - center_y;
                    tmp_r.z = orig_r.z;
                }
                t_vec3 rot_r;
                rot_r.x = tmp_r.x * cosz - tmp_r.y * sinz;
                rot_r.y = tmp_r.x * sinz + tmp_r.y * cosz;
                rot_r.z = tmp_r.z;
                if (ui->grid_mode != MODE_GRID) {
                    rot_r.x += center_x;
                    rot_r.y += center_y;
                }
                t_screen p_right;
                if (ui->cube_mode == MODE_CUBE)
                    p_right = perspective_project(rot_r, &ui->proj, &ui->camera);
                else
                    p_right = iso_project(rot_r, &ui->proj, &ui->camera);

                draw_line_lerp(ui->image.img_data, p, p_right,
                               map->points[y][x].color,
                               map->points[y][x + 1].color,
                               ui->image.size_lien, ui->image.bpp);
            }
            // 下隣
            if (y + 1 < map->height)
            {
                t_vec3 orig_d = map->points[y + 1][x].pos;
                t_vec3 tmp_d;
                if (ui->grid_mode == MODE_GRID) {
                    sphere_map_transform(x, y + 1, map->width, map->height, radius, orig_d.z * ui->proj.z_scale, &tmp_d.x, &tmp_d.y, &tmp_d.z);
                } else {
                    tmp_d.x = orig_d.x - center_x;
                    tmp_d.y = orig_d.y - center_y;
                    tmp_d.z = orig_d.z;
                }
                t_vec3 rot_d;
                rot_d.x = tmp_d.x * cosz - tmp_d.y * sinz;
                rot_d.y = tmp_d.x * sinz + tmp_d.y * cosz;
                rot_d.z = tmp_d.z;
                if (ui->grid_mode != MODE_GRID) {
                    rot_d.x += center_x;
                    rot_d.y += center_y;
                }
                t_screen p_down;
                if (ui->cube_mode == MODE_CUBE)
                    p_down = perspective_project(rot_d, &ui->proj, &ui->camera);
                else
                    p_down = iso_project(rot_d, &ui->proj, &ui->camera);

                draw_line_lerp(ui->image.img_data, p, p_down,
                               map->points[y][x].color,
                               map->points[y + 1][x].color,
                               ui->image.size_lien, ui->image.bpp);
            }
        }
    }
}

