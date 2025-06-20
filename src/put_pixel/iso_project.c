/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:27:49 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 16:28:00 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 投影関数（zが高さ、zスケールなし）
t_screen	iso_project(t_vec3 pos, t_projinfo *proj)
{
    float		angle;
    float		x;
    float		y;
    t_screen	result;

    angle = M_PI / 6.0;
    x = (pos.x - pos.y) * cos(angle);
    y = (pos.x + pos.y) * sin(angle) - pos.z;
    result.x = WIDTH / 2 + (x - proj->offset_x) * proj->scale;
    result.y = HEIGHT / 2 + (y - proj->offset_y) * proj->scale;
    return (result);
}