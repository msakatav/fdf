/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:08:55 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:08:58 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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