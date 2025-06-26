/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:04:26 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 10:19:23 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	sphere_map_transform(const t_sphere_map_param *param, t_vec3 *out)
{
	float	theta;
	float	phi;
	float	r;

	theta = 2.0f * M_PI * param->x / (float)(param->w - 1);
	phi = M_PI * param->y / (float)(param->h - 1);
	r = param->radius + param->height;
	out->x = r * sinf(phi) * cosf(theta);
	out->y = r * sinf(phi) * sinf(theta);
	out->z = r * cosf(phi);
}
