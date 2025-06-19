#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vec3
{
    float x, y, z;
}	t_vec3;

typedef struct s_point
{
    t_vec3 pos;
    int	color;
}	t_point;

typedef struct s_screen
{
    int	x, y;
}	t_screen;

// --- read_mapのプロトタイプ宣言 ---
t_point **read_map(const char *filename, int *width, int *height);

// マップの最大範囲を調べる
void get_map_bounds(t_point **map, int width, int height, float *max_x, float *max_y, float *min_x, float *min_y)
{
    *max_x = *max_y = -1e9;
    *min_x = *min_y = 1e9;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x].pos.x > *max_x) *max_x = map[y][x].pos.x;
            if (map[y][x].pos.x < *min_x) *min_x = map[y][x].pos.x;
            if (map[y][x].pos.y > *max_y) *max_y = map[y][x].pos.y;
            if (map[y][x].pos.y < *min_y) *min_y = map[y][x].pos.y;
        }
    }
}

// グローバル変数でスケールとオフセットを保持
float g_scale = 1.0;
float g_z_scale = 1.0;
float g_offset_x = 0.0;
float g_offset_y = 0.0;

// 投影
t_screen iso_project(t_vec3 pos)
{
    float angle = M_PI / 6.0;
    float x = (pos.x - pos.z * g_z_scale) * cos(angle);
    float y = pos.y + (pos.x + pos.z * g_z_scale) * sin(angle);

    // 中心をオフセット
    t_screen result;
    result.x = WIDTH / 2 + (x - g_offset_x) * g_scale;
    result.y = HEIGHT / 2 - (y - g_offset_y) * g_scale;
    return result;
}

// ピクセル描画
void put_pixel(char *data, int x, int y, int color, int size_lien, int bpp)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;

    int index = y * size_lien + x * (bpp / 8);
    data[index + 0] = color & 0xff;
    data[index + 1] = (color >> 8) & 0xff;
    data[index + 2] = (color >> 16) & 0xff;
}

// 線形補間（Lerp）で色を混ぜる
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

    return (r << 16) | (g << 8) | b;
}

// 線描画（色補間対応）
void draw_line_lerp(char *data, t_screen a, t_screen b, int color_a, int color_b, int size_lien, int bpp)
{
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = (a.x < b.x) ? 1 : -1;
    int sy = (a.y < b.y) ? 1 : -1;
    int err = dx - dy;
    int len = dx > dy ? dx : dy;
    int step = 0;

    int x = a.x, y = a.y;
    while (1)
    {
        float t = len ? (float)step / len : 0.0f;
        int color = lerp_color(color_a, color_b, t);
        put_pixel(data, x, y, color, size_lien, bpp);
        if (x == b.x && y == b.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
        step++;
    }
}

// --- マップ描画関数 ---
void draw_map(char *img_data, t_point **map, int width, int height, int size_lien, int bpp)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            t_screen p = iso_project(map[y][x].pos);
            // 右隣と線を引く
            if (x + 1 < width)
            {
                t_screen p_right = iso_project(map[y][x + 1].pos);
                draw_line_lerp(img_data, p, p_right, map[y][x].color, map[y][x + 1].color, size_lien, bpp);
            }
            // 下隣と線を引く
            if (y + 1 < height)
            {
                t_screen p_down = iso_project(map[y + 1][x].pos);
                draw_line_lerp(img_data, p, p_down, map[y][x].color, map[y + 1][x].color, size_lien, bpp);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <mapfile>\n", argv[0]);
        return 1;
    }

    int width = 0, height = 0;
    t_point **map = read_map(argv[1], &width, &height);
    if (!map)
    {
        printf("Failed to read map.\n");
        return 1;
    }

    // --- スケール値を決定 ---
    float max_x, max_y, min_x, min_y;
    get_map_bounds(map, width, height, &max_x, &max_y, &min_x, &min_y);

    float map_w = max_x - min_x + 1;
    float map_h = max_y - min_y + 1;
    float scale_x = (WIDTH * 0.8) / map_w;
    float scale_y = (HEIGHT * 0.8) / map_h;
    g_scale = scale_x < scale_y ? scale_x : scale_y;

    // z値のスケールも調整
    float max_z = -1e9, min_z = 1e9;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            if (map[y][x].pos.z > max_z) max_z = map[y][x].pos.z;
            if (map[y][x].pos.z < min_z) min_z = map[y][x].pos.z;
        }
    float map_z = max_z - min_z;
    if (map_z == 0) map_z = 1;
    g_z_scale = g_scale * 0.5 / map_z;

    // --- マップ中心を計算 ---
    float center_x = (min_x + max_x) / 2.0;
    float center_y = (min_y + max_y) / 2.0;
    float center_z = (min_z + max_z) / 2.0;

    // 中心点を投影空間に変換してオフセットに使う
    float angle = M_PI / 6.0;
    g_offset_x = (center_x - center_z * g_z_scale) * cos(angle);
    g_offset_y = center_y + (center_x + center_z * g_z_scale) * sin(angle);

    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "fdf");

    int bpp, size_lien, endian;
    void *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &bpp, &size_lien, &endian);

    draw_map(img_data, map, width, height, size_lien, bpp);

    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);

    // メモリ解放
    for (int y = 0; y < height; y++)
        free(map[y]);
    free(map);

    return 0;
}