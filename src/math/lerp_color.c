/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:02:29 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:33:59 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_rgb	int_to_rgb(int color)
{
	t_rgb	c;

	c.r = (color >> 16) & 0xff;
	c.g = (color >> 8) & 0xff;
	c.b = color & 0xff;
	return (c);
}

static int	rgb_to_int(t_rgb c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

int	lerp_color(int color1, int color2, float t)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	res;

	c1 = int_to_rgb(color1);
	c2 = int_to_rgb(color2);
	res.r = c1.r + (int)((c2.r - c1.r) * t);
	res.g = c1.g + (int)((c2.g - c1.g) * t);
	res.b = c1.b + (int)((c2.b - c1.b) * t);
	return (rgb_to_int(res));
}
