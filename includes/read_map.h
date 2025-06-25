#ifndef READ_MAP_H
# define READ_MAP_H
# include "structs.h"
#define MAX_MAPS 10



int load_map(const char *filename, t_map *map);
int load_maps_from_args(int argc, char **argv, t_maps *maps);
int	ft_parse_int_hex(const char *str, int *z, int *color);

#endif