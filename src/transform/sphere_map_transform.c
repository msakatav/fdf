/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:04:26 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 03:04:27 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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