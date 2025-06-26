/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:56:32 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 09:30:45 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_width(t_map *map, int temp_w)
{
	if (map->width == 0)
		map->width = temp_w;
}

static void	expand_points_array(t_point ***points, int *cap, int height)
{
	if (height >= *cap)
	{
		*cap *= 2;
		*points = ft_realloc(*points,
				sizeof(t_point *) * height,
				sizeof(t_point *) * (*cap));
	}
}

static void	process_line(char *line, t_map *map, t_point ***points, int *cap)
{
	char	**tokens;
	int		temp_w;
	t_point	*row;
	char	*p;

	p = ft_strchr(line, '\n');
	if (p)
		*p = '\0';
	tokens = ft_split(line, ' ');
	temp_w = get_row_width(tokens);
	row = parse_row(tokens, temp_w, map->height);
	update_map_width(map, temp_w);
	expand_points_array(points, cap, map->height);
	(*points)[map->height++] = row;
	ft_free_split(tokens);
}

int	load_map(const char *filename, t_map *map)
{
	int			fd;
	int			cap;
	char		*line;
	t_point		**points;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_strlcpy(map->filename, filename, 256);
	map->filename[255] = 0;
	map->width = 0;
	map->height = 0;
	cap = 16;
	points = malloc(sizeof(t_point *) * cap);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, map, &points, &cap);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->points = points;
	return (1);
}
