/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:53 by root              #+#    #+#             */
/*   Updated: 2025/06/20 11:15:34 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_row_width(char **tokens)
{
	int	w;

	w = 0;
	while (tokens[w])
		w++;
	return (w);
}

static t_point	*parse_row(char **tokens, int temp_w, int h)
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
			ft_parse_int_hex(tokens[i], "%d,%x", &z, &color);
		else
			z = ft_atoi(tokens[i]);
		row[i].pos = (t_vec3){i, h, z};
		row[i].color = color;
		i++;
	}
	return (row);
}

static void	expand_map(t_mapinfo *info)
{
	t_point	**new_map;

	info->cap *= 2;
	new_map = (t_point **)ft_realloc((void **)info->map, info->h, info->cap);
	info->map = new_map;
}

static void	process_line(t_mapinfo *info, char *line)
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
	row = parse_row(tokens, temp_w, info->h);
	if (info->w == 0)
		info->w = temp_w;
	if (info->h >= info->cap)
		expand_map(info);
	info->map[info->h++] = row;
	free_split(tokens);
}

t_point	**read_map(const char *filename, int *width, int *height)
{
	int			fd;
	char		*line;
	t_mapinfo	info;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	info.w = 0;
	info.h = 0;
	info.cap = 16;
	info.map = malloc(sizeof(t_point *) * info.cap);
	line = get_next_line(fd);
	while (line)
	{
		process_line(&info, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	*width = info.w;
	*height = info.h;
	return (info.map);
}
