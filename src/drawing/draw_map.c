#include "fdf.h"

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

