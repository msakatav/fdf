#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_vec3
{
	float x, y, z;
}	t_vec3;

typedef struct s_point
{
	t_vec3 pos;
	int	color;
}	t_point;

t_point **read_map(const char *filename, int *width, int *height)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    char *line;
    int w = 0, h = 0;
    t_point **map = NULL;

    while (line = get_next_line(fd))
    {
        int temp_w = 0;
        char *token = strtok(line, " \n");
        t_point *row = malloc(sizeof(t_point) * 1024);

        while (token)
        {
            int z = 0;
            int color = 0xffffff;

            if (strchr(token, ','))
            {
                sscanf(token, "%d,%x", &z, &color);
            }
            else
                z = atoi(token);

            row[temp_w].pos = (t_vec3){temp_w, h, z};
            row[temp_w].color = color;

            temp_w++;
            token = strtok(NULL, " \n");
        }

        if (!w)
            w = temp_w;

        map = realloc(map, sizeof(t_point *) * (h + 1));
        map[h++] = row;

        free(line);
    }
    close(fd);
    *width = w;
    *height = h;
    return map;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <mapfile>\n", argv[0]);
        return 1;
    }

    int width = 0, height = 0;
    t_point **map = read_map(argv[1], &width, &height);

    if (!map)
    {
        printf("Failed to read map.\n");
        return 1;
    }

    printf("Map size: %d x %d\n", width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            printf("(%d,%d,%d) color: %#06x  ", 
                (int)map[y][x].pos.x, 
                (int)map[y][x].pos.y, 
                (int)map[y][x].pos.z, 
                map[y][x].color);
        }
        printf("\n");
        free(map[y]);
    }
    free(map);
    return 0;
}