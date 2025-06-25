/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale_and_offset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:00:28 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:00:51 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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