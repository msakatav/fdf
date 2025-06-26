#ifndef READ_MAP_H
# define READ_MAP_H
# include "structs.h"



int load_map(const char *filename, t_map *map);
int load_maps_from_args(int argc, char **argv, t_maps *maps);
int	ft_parse_int_hex(const char *str, int *z, int *color);
t_point *parse_row(char **tokens, int temp_w, int h);
int get_row_width(char **tokens);

#endif