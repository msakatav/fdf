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

// 投影
t_screen iso_project(t_vec3 pos)
{
	float angle = M_PI / 6.0;
	float scale = 80.0;
	float x = (pos.x - pos.z) * cos(angle);
	float y = pos.y + (pos.x + pos.z) * sin(angle);

	t_screen result;
	result.x = WIDTH / 2 + x * scale;
	result.y = HEIGHT / 2 - y * scale;
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

int main ()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "Iso Cube");

    int bpp, size_lien, endian;
    void *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &bpp, &size_lien, &endian);

    // 立方体の頂点（色を変えてみる例）
    t_point vertices[8] = {
        {{-1, -1, -1}, 0xff0000},
        {{ 1, -1, -1}, 0x00ff00},
        {{ 1,  1, -1}, 0x0000ff},
        {{-1,  1, -1}, 0xffff00},
        {{-1, -1,  1}, 0xff00ff},
        {{ 1, -1,  1}, 0x00ffff},
        {{ 1,  1,  1}, 0xffffff},
        {{-1,  1,  1}, 0x000000},
    };
    int vertex_count = sizeof(vertices) / sizeof(vertices[0]);

    // 頂点情報から隣接する頂点同士を自動で線描画（色補間）
    for (int i = 0; i < vertex_count; i++) {
        for (int j = i + 1; j < vertex_count; j++) {
            int diff = 0;
            if (vertices[i].pos.x != vertices[j].pos.x) diff++;
            if (vertices[i].pos.y != vertices[j].pos.y) diff++;
            if (vertices[i].pos.z != vertices[j].pos.z) diff++;
            if (diff == 1) { // 1軸だけ異なる＝隣接
                t_screen p1 = iso_project(vertices[i].pos);
                t_screen p2 = iso_project(vertices[j].pos);
                draw_line_lerp(img_data, p1, p2, vertices[i].color, vertices[j].color, size_lien, bpp);
            }
        }
    }

    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
}