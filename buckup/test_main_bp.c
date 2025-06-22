#include <stdio.h>
#include "read_map.h"

int main(int argc, char **argv)
{
    t_maps maps;
    if (argc < 2)
    {
        printf("Usage: %s map1.fdf [map2.fdf ...]\n", argv[0]);
        return 1;
    }
    int loaded = load_maps_from_args(argc, argv, &maps);
    printf("Loaded %d map(s)\n", loaded);

    for (int m = 0; m < maps.count; m++)
    {
        t_map *map = &maps.maps[m];
        printf("Map %d: %s (%d x %d)\n", m + 1, map->filename, map->width, map->height);
        for (int y = 0; y < map->height; y++)
        {
            for (int x = 0; x < map->width; x++)
            {
                printf("%3.0f", map->points[y][x].pos.z);
                // 色がデフォルト(0xffffff)でなければ色も表示
                if (map->points[y][x].color != 0xffffff)
                    printf("(%06X)", map->points[y][x].color);
                if (x < map->width - 1)
                    printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}