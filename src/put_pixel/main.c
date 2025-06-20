/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:38:53 by msakata           #+#    #+#             */
/*   Updated: 2025/06/20 11:52:54 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_mapdata
{
    t_point	**map;
    int		width;
    int		height;
}	t_mapdata;

typedef struct s_projinfo
{
    float	min_px;
    float	max_px;
    float	min_py;
    float	max_py;
    float	proj_w;
    float	proj_h;
    float	scale_x;
    float	scale_y;
    float	scale;
    float	offset_x;
    float	offset_y;
}	t_projinfo;

typedef struct s_mlxinfo
{
    void	*mlx;
    void	*win;
    void	*img;
    char	*img_data;
    int		bpp;
    int		size_lien;
    int		endian;
}	t_mlxinfo;

typedef struct s_fdf
{
    t_mapdata	mapdata;
    t_projinfo	projinfo;
    t_mlxinfo	mlxinfo;
}	t_fdf;

static int	is_fdf_file(const char *filename)
{
    int	len;

    len = ft_strlen(filename);
    if (len < 5)
        return (0);
    return (ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

static int	init_mapdata(t_mapdata *mapdata, char *filename)
{
    mapdata->width = 0;
    mapdata->height = 0;
    mapdata->map = read_map(filename, &mapdata->width, &mapdata->height);
    if (!mapdata->map)
    {
        ft_printf("Failed to read map.\n");
        return (0);
    }
    return (1);
}

static void	init_projinfo(t_projinfo *proj, t_mapdata *mapdata)
{
    get_projected_bounds(mapdata, &proj->min_px, &proj->max_px,
        &proj->min_py, &proj->max_py);
    proj->proj_w = proj->max_px - proj->min_px;
    proj->proj_h = proj->max_py - proj->min_py;
    proj->scale_x = (WIDTH * 0.8) / proj->proj_w;
    proj->scale_y = (HEIGHT * 0.8) / proj->proj_h;
    proj->scale = proj->scale_x < proj->scale_y ? proj->scale_x : proj->scale_y;
    proj->offset_x = (proj->min_px + proj->max_px) / 2.0;
    proj->offset_y = (proj->min_py + proj->max_py) / 2.0;
}

static void	init_mlxinfo(t_mlxinfo *mlxinfo)
{
    mlxinfo->mlx = mlx_init();
    mlxinfo->win = mlx_new_window(mlxinfo->mlx, WIDTH, HEIGHT, "fdf");
    mlxinfo->img = mlx_new_image(mlxinfo->mlx, WIDTH, HEIGHT);
    mlxinfo->img_data = mlx_get_data_addr(mlxinfo->img,
            &mlxinfo->bpp, &mlxinfo->size_lien, &mlxinfo->endian);
}

static void	free_map(t_mapdata *mapdata)
{
    int	y;

    y = 0;
    while (y < mapdata->height)
        free(mapdata->map[y++]);
    free(mapdata->map);
}

int	main(int argc, char **argv)
{
    t_fdf	fdf;

    if (argc != 2)
    {
        ft_printf("Usage: %s <mapfile.fdf>\n", argv[0]);
        return (1);
    }
    if (!is_fdf_file(argv[1]))
    {
        ft_printf("Error: Only .fdf files are supported.\n");
        return (1);
    }
    if (!init_mapdata(&fdf.mapdata, argv[1]))
        return (1);
    init_projinfo(&fdf.projinfo, &fdf.mapdata);
    init_mlxinfo(&fdf.mlxinfo);
    draw_map(&fdf);
    mlx_put_image_to_window(fdf.mlxinfo.mlx, fdf.mlxinfo.win,
        fdf.mlxinfo.img, 0, 0);
    mlx_loop(fdf.mlxinfo.mlx);
    free_map(&fdf.mapdata);
    return (0);
}