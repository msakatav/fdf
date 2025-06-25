/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:01:35 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:47:13 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(const t_pixel_info *info, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	index = y * info->size_lien + x * (info->bpp / 8);
	info->data[index + 0] = color & 0xff;
	info->data[index + 1] = (color >> 8) & 0xff;
	info->data[index + 2] = (color >> 16) & 0xff;
}
