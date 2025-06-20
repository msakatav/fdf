/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:53 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 16:27:03 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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