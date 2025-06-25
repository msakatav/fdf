/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_lerp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakata <msakata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:03:35 by msakata           #+#    #+#             */
/*   Updated: 2025/06/26 07:54:14 by msakata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_lerped_color(const t_draw_line_param *p, int step, int len)
{
	float	t;

	if (len != 0)
		t = (float)step / (float)len;
	else
		t = 0.0f;
	return (lerp_color(p->color_a, p->color_b, t));
}

static void	draw_pixel(const t_draw_line_param *p, int x, int y, int color)
{
	put_pixel(p->data, x, y, color, p->size_lien, p->bpp);
}

static void	init_line_state(t_line_state *s, const t_draw_line_param *p)
{
	s->dx = abs(p->b.x - p->a.x);
	s->dy = abs(p->b.y - p->a.y);
	s->err = s->dx - s->dy;
	s->step = 0;
	s->x = p->a.x;
	s->y = p->a.y;
	if (p->a.x < p->b.x)
		s->sx = 1;
	else
		s->sx = -1;
	if (p->a.y < p->b.y)
		s->sy = 1;
	else
		s->sy = -1;
	if (s->dx > s->dy)
		s->len = s->dx;
	else
		s->len = s->dy;
}

static void	draw_line_core(const t_draw_line_param *p)
{
	t_line_state	s;
	int				color;
	int				e2;

	init_line_state(&s, p);
	while (1)
	{
		color = get_lerped_color(p, s.step, s.len);
		draw_pixel(p, s.x, s.y, color);
		if (s.x == p->b.x && s.y == p->b.y)
			break ;
		e2 = 2 * s.err;
		if (e2 > -s.dy)
		{
			s.err -= s.dy;
			s.x += s.sx;
		}
		if (e2 < s.dx)
		{
			s.err += s.dx;
			s.y += s.sy;
		}
		s.step++;
	}
}

void	draw_line_lerp(const t_draw_line_param *p)
{
	draw_line_core(p);
}
