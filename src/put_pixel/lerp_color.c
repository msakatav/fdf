/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:11 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 16:26:23 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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