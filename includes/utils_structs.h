/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:44:36 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 08:21:50 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_STRUCTS_H
# define UTILS_STRUCTS_H

typedef struct s_draw_line_param {
    char      *data;
    t_screen   a;
    t_screen   b;
    int        color_a;
    int        color_b;
    int        size_lien;
    int        bpp;
} t_draw_line_param;

typedef struct s_line_state {
    int dx, dy;
    int sx, sy;
    int err;
    int len;
    int step;
    int x, y;
} t_line_state;

typedef struct s_draw_map_ctx {
    t_ui   *ui;
    t_map  *map;
    float   center_x;
    float   center_y;
    float   radius;
    float   cosz;
    float   sinz;
    int     is_grid;
	t_screen	p;
} t_draw_map_ctx;

typedef struct s_line_info {
    t_screen a;
    t_screen b;
    int color_a;
    int color_b;
} t_line_info;

#endif