#include "read_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "ft_printf.h"

static int get_row_width(char **tokens)
{
    int w = 0;
    while (tokens[w])
        w++;
    return (w);
}

static t_point *parse_row(char **tokens, int temp_w, int h)
{
    t_point *row = malloc(sizeof(t_point) * temp_w);
    if (!row)
        return (NULL);
    int i = 0;
    while (i < temp_w)
    {
        int z = 0;
        int color = 0xffffff;
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

static void free_points(t_point **points, int height)
{
    int i = 0;
    while (i < height)
    {
        free(points[i]);
        i++;
    }
    free(points);
}

int load_map(const char *filename, t_map *map)
{
    int fd = open(filename, O_RDONLY);
	if (fd < 0)
        return (0);
    ft_strlcpy(map->filename, filename, 256);
    map->filename[255] = 0;
    map->width = 0;
    map->height = 0;
    int cap = 16;
    t_point **points = malloc(sizeof(t_point *) * cap);
    char *line = get_next_line(fd);
    while (line)
    {
        char **tokens;
        int temp_w;
        t_point *row;

        char *p = ft_strchr(line, '\n');
        if (p)
            *p = '\0';

        tokens = ft_split(line, ' ');
        temp_w = get_row_width(tokens);
        row = parse_row(tokens, temp_w, map->height);
        if (map->width == 0)
            map->width = temp_w;
        if (map->height >= cap)
        {
            cap *= 2;
            points = ft_realloc(points,
                sizeof(t_point *) * map->height, sizeof(t_point *) * cap);
        }
        points[map->height++] = row;
        ft_free_split(tokens);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    map->points = points;
    return (1);
}

// コマンドライン引数からファイル名リストを受け取る
int load_maps_from_args(int argc, char **argv, t_maps *maps)
{
    int i = 0;
    maps->count = 0;
    maps->current = 0;
    // argv[1] から順にファイル名として扱う
    for (i = 1; i < argc && maps->count < MAX_MAPS; i++)
    {
        if (load_map(argv[i], &maps->maps[maps->count]))
            maps->count++;
    }
    return maps->count;
}