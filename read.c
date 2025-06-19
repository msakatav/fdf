#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>




t_point **read_map(const char *filename, int *width, int *height)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    char *line;
    int w = 0, h = 0, cap = 16;
    t_point **map = malloc(sizeof(t_point *) * cap);

    while ((line = get_next_line(fd)))
    {
        // 1. 改行を\0に
        char *p = ft_strchr(line, '\n');
        if (p) *p = '\0';

        // 2. ft_splitで分割
        char **tokens = ft_split(line, ' ');

        // 3. 行の幅を数える
        int temp_w = 0;
        while (tokens[temp_w])
            temp_w++;

        t_point *row = malloc(sizeof(t_point) * temp_w);

        for (int i = 0; i < temp_w; i++)
        {
            int z = 0;
            int color = 0xffffff;
            if (ft_strchr(tokens[i], ','))
            {
                ft_parse_int_hex(tokens[i], "%d,%x", &z, &color);
            }
            else
                z = ft_atoi(tokens[i]);
            row[i].pos = (t_vec3){i, h, z};
            row[i].color = color;
        }

        if (!w)
            w = temp_w;

        // 4. 自作reallocでmapを拡張
        if (h >= cap)
        {
            cap *= 2;
            map = (t_point **)ft_realloc((void **)map, h, cap);
        }
        map[h++] = row;

        free_split(tokens);
        free(line);
    }
    close(fd);
    *width = w;
    *height = h;
    return map;
}
