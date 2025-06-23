#ifndef READ_MAP_H
# define READ_MAP_H

#define MAX_MAPS 10

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_point
{
	t_vec3 pos;
	int color;
}	t_point;

typedef struct s_map
{
	char filename[256];
	int width;
	int height;
	t_point **points;
}	t_map;

typedef struct s_maps
{
	t_map maps[MAX_MAPS];
	int count;
	int current;
}	t_maps;

int load_map(const char *filename, t_map *map);
int load_maps_from_args(int argc, char **argv, t_maps *maps);
int	ft_parse_int_hex(const char *str, int *z, int *color);

#endif