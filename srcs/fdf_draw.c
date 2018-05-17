/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:41 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 16:38:07 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_y(t_env *e, int i, int x_gap, int y_gap)
{
	if ((i + e->x_max) < (e->x_max * e->y_max))
	{
		e->pos->x_a[0] = ((e->pos[i].x * e->gap) + x_gap / 2) +
			(e->pos[i].z * e->z_scale);
		e->pos->x_a[1] = e->pos->x_a[0];
		e->pos->x_a[2] = ((e->pos[i + (e->x_max)].x * e->gap) +
				x_gap / 2) + (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[0] = ((e->pos[i].y * e->gap) + y_gap / 2) -
			(e->pos[i].z * e->z_scale);
		e->pos->y_a[2] = ((e->pos[i + (e->x_max)].y * e->gap) +
				y_gap / 2) - (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[1] = e->pos->y_a[0];
		while (e->pos->y_a[0] <= e->pos->y_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, (((e->pos->x_a[2] -
					e->pos->x_a[1]) / (e->pos->y_a[2] - e->pos->y_a[1]))
					* (e->pos->y_a[0] - e->pos->y_a[1]) + e->pos->x_a[1])
					, e->pos->y_a[0], fdf_draw_color(e, i, 'y'));
			e->pos->y_a[0]++;
		}
	}
}

void	fdf_draw_s(t_env *e, int i, int x_gap, int y_gap)
{
	e->pos->x_a[0] = ((e->pos[i].x * e->gap) + x_gap / 2) +
		(e->pos[i].z * e->z_scale);
	e->pos->x_a[1] = e->pos->x_a[0];
	e->pos->x_a[2] = ((e->pos[i + 1].x * e->gap) + x_gap / 2)
		+ (e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[0] = ((e->pos[i].y * e->gap) + y_gap / 2) -
		(e->pos[i].z * e->z_scale);
	e->pos->y_a[2] = ((e->pos[i + 1].y * e->gap) + y_gap / 2) -
		(e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[1] = e->pos->y_a[0];
}

void	fdf_draw_cal(t_env *e, int *x_gap, int *y_gap)
{
	e->gap = (e->x_max >= e->y_max) ? ((e->win_x / e->x_max) / e->zoom) :
		((e->win_y / e->y_max) / e->zoom);
	(e->x_max >= e->y_max) ? (*x_gap = e->win_x - (e->gap * (e->x_max - 1))) :
		(*x_gap = (e->win_x - (e->gap * (e->x_max - 1))));
	(e->x_max >= e->y_max) ? (*y_gap = e->win_y - (e->gap * (e->y_max - 1))) :
		(*y_gap = e->win_y - (e->gap * (e->y_max - 1)));
}

void	fdf_draw(t_env *e)
{
	int		i;
	int		x_gap;
	int		y_gap;

	i = -1;
	fdf_draw_cal(e, &x_gap, &y_gap);
	x_gap += e->x_gap;
	y_gap += e->y_gap;
	while (++i < (e->y_max * e->x_max))
	{
		fdf_draw_s(e, i, x_gap, y_gap);
		while (e->pos->x_a[0] <= e->pos->x_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, e->pos->x_a[0],
				(((e->pos->y_a[2] - e->pos->y_a[1]) /
				(e->pos->x_a[2] - e->pos->x_a[1])) *
				(e->pos->x_a[0] - e->pos->x_a[1]) +
				e->pos->y_a[1]), fdf_draw_color(e, i, 'x'));
			e->pos->x_a[0]++;
		}
		fdf_draw_y(e, i, x_gap, y_gap);
	}
}
