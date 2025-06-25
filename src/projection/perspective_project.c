#include "fdf.h"

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

