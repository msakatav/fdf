/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:25:56 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:32:16 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_row_width(char **tokens)
{
	int	w;

	w = 0;
	while (tokens[w])
		w++;
	return (w);
}

t_point	*parse_row(char **tokens, int temp_w, int h)
{
	t_point	*row;
	int		i;
	int		z;
	int		color;

	row = malloc(sizeof(t_point) * temp_w);
	if (!row)
		return (NULL);
	i = 0;
	while (i < temp_w)
	{
		z = 0;
		color = 0xffffff;
		if (ft_strchr(tokens[i], ','))
			ft_parse_int_hex(tokens[i], &z, &color);
		else
			z = ft_atoi(tokens[i]);
		row[i].pos = (t_vec3){i, h, z};
		row[i].color = color;
		i++;
	}
	return (row);
}

int	load_maps_from_args(int argc, char **argv, t_maps *maps)
{
	int	i;

	i = 1;
	maps->count = 0;
	maps->current = 0;
	while (i < argc && maps->count < MAX_MAPS)
	{
		if (load_map(argv[i], &maps->maps[maps->count]))
			maps->count++;
		i++;
	}
	return (maps->count);
}
