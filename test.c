#include "fdf.h"
#define WIDTH 800
#define HEIGHT 600

// zスケール値を決定（z範囲から適切な値をセット）
void	set_z_scale(t_mapdata *mapdata, t_projinfo *proj)
{
    int		x;
    int		y;
    float	max_z;
    float	min_z;

    max_z = -1e9;
    min_z = 1e9;
    y = 0;
    while (y < mapdata->height)
    {
        x = 0;
        while (x < mapdata->width)
        {
            if (mapdata->map[y][x].pos.z > max_z)
                max_z = mapdata->map[y][x].pos.z;
            if (mapdata->map[y][x].pos.z < min_z)
                min_z = mapdata->map[y][x].pos.z;
            x++;
        }
        y++;
    }
    if (max_z - min_z == 0)
        proj->z_scale = 1.0;
    else
        proj->z_scale = 1.0; // 初期値。全体スケール決定前なので1.0でOK
}

// 投影関数（zスケール対応）
t_screen	iso_project(t_vec3 pos, t_projinfo *proj)
{
    float		angle;
    float		x;
    float		y;
    t_screen	result;

    angle = M_PI / 6.0;
    x = (pos.x - pos.y) * cos(angle);
    y = (pos.x + pos.y) * sin(angle) - pos.z * proj->z_scale;
    result.x = WIDTH / 2 + (x - proj->offset_x) * proj->scale;
    result.y = HEIGHT / 2 + (y - proj->offset_y) * proj->scale;
    return (result);
}

// 投影後の座標範囲を計算（zスケール済みで）
void	get_projected_bounds(
    t_mapdata *mapdata, t_projinfo *proj,
    float *min_px, float *max_px, float *min_py, float *max_py)
{
    int		x;
    int		y;
    float	angle;
    float	px;
    float	py;

    angle = M_PI / 6.0;
    *min_px = *min_py = 1e9;
    *max_px = *max_py = -1e9;
    y = 0;
    while (y < mapdata->height)
    {
        x = 0;
        while (x < mapdata->width)
        {
            px = (mapdata->map[y][x].pos.x - mapdata->map[y][x].pos.y)
                * cos(angle);
            py = (mapdata->map[y][x].pos.x + mapdata->map[y][x].pos.y)
                * sin(angle) - mapdata->map[y][x].pos.z * proj->z_scale;
            if (px < *min_px)
                *min_px = px;
            if (px > *max_px)
                *max_px = px;
            if (py < *min_py)
                *min_py = py;
            if (py > *max_py)
                *max_py = py;
            x++;
        }
        y++;
    }
}

// 全体スケールとオフセットを決定
void	set_scale_and_offset(t_projinfo *proj)
{
    proj->proj_w = proj->max_px - proj->min_px;
    proj->proj_h = proj->max_py - proj->min_py;
    proj->scale_x = (WIDTH * 0.8) / proj->proj_w;
    proj->scale_y = (HEIGHT * 0.8) / proj->proj_h;
    proj->scale = proj->scale_x < proj->scale_y ? proj->scale_x : proj->scale_y;
    proj->offset_x = (proj->min_px + proj->max_px) / 2.0;
    proj->offset_y = (proj->min_py + proj->max_py) / 2.0;
}

// zスケールを全体スケールに合わせて再調整
void	adjust_z_scale(t_mapdata *mapdata, t_projinfo *proj)
{
    int		x;
    int		y;
    float	max_z;
    float	min_z;

    max_z = -1e9;
    min_z = 1e9;
    y = 0;
    while (y < mapdata->height)
    {
        x = 0;
        while (x < mapdata->width)
        {
            if (mapdata->map[y][x].pos.z > max_z)
                max_z = mapdata->map[y][x].pos.z;
            if (mapdata->map[y][x].pos.z < min_z)
                min_z = mapdata->map[y][x].pos.z;
            x++;
        }
        y++;
    }
    if (max_z - min_z == 0)
        proj->z_scale = 1.0;
    else
        proj->z_scale = proj->scale * 0.5 / (max_z - min_z);
}

// ピクセル描画
void	put_pixel(
    char *data, int x, int y, int color, int size_lien, int bpp)
{
    int	index;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    index = y * size_lien + x * (bpp / 8);
    data[index + 0] = color & 0xff;
    data[index + 1] = (color >> 8) & 0xff;
    data[index + 2] = (color >> 16) & 0xff;
}

// 線形補間（Lerp）で色を混ぜる
int	lerp_color(int color1, int color2, float t)
{
    int	r1;
    int	g1;
    int	b1;
    int	r2;
    int	g2;
    int	b2;
    int	r;
    int	g;
    int	b;

    r1 = (color1 >> 16) & 0xff;
    g1 = (color1 >> 8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2 >> 16) & 0xff;
    g2 = (color2 >> 8) & 0xff;
    b2 = color2 & 0xff;
    r = r1 + (int)((r2 - r1) * t);
    g = g1 + (int)((g2 - g1) * t);
    b = b1 + (int)((b2 - b1) * t);
    return ((r << 16) | (g << 8) | b);
}

// 線描画（色補間対応）
void	draw_line_lerp(
    char *data, t_screen a, t_screen b, int color_a, int color_b,
    int size_lien, int bpp)
{
    int	dx;
    int	dy;
    int	sx;
    int	sy;
    int	err;
    int	len;
    int	step;
    int	x;
    int	y;
    int	e2;
    float	t;
    int	color;

    dx = abs(b.x - a.x);
    dy = abs(b.y - a.y);
    sx = (a.x < b.x) ? 1 : -1;
    sy = (a.y < b.y) ? 1 : -1;
    err = dx - dy;
    len = dx > dy ? dx : dy;
    step = 0;
    x = a.x;
    y = a.y;
    while (1)
    {
        t = len ? (float)step / len : 0.0f;
        color = lerp_color(color_a, color_b, t);
        put_pixel(data, x, y, color, size_lien, bpp);
        if (x == b.x && y == b.y)
            break ;
        e2 = 2 * err;
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
void	draw_map(t_ui *ui, t_map *map)
{
    int			x;
    int			y;
    t_screen	p;
    t_screen	p_right;
    t_screen	p_down;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            // iso_project で ui->proj を使用
            p = iso_project(map->points[y][x].pos, &(ui->proj));
            if (x + 1 < map->width)
            {
                p_right = iso_project(map->points[y][x + 1].pos, &(ui->proj));
                draw_line_lerp(
                    ui->image.img_data,
                    p, p_right,
                    map->points[y][x].color,
                    map->points[y][x + 1].color,
                    ui->image.size_lien,
                    ui->image.bpp
                );
            }
            if (y + 1 < map->height)
            {
                p_down = iso_project(map->points[y + 1][x].pos, &(ui->proj));
                draw_line_lerp(
                    ui->image.img_data,
                    p, p_down,
                    map->points[y][x].color,
                    map->points[y + 1][x].color,
                    ui->image.size_lien,
                    ui->image.bpp
                );
            }
            x++;
        }
        y++;
    }
}

