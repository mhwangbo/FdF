/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:43:48 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 15:44:49 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_color_ss(t_env *e, t_col *a, int i, int z_max)
{
	if (((z_max - e->pos[i].z) * 10) <= 510)
	{
		e->color_c == 0 ?
			(a->g = a->g - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
		e->color_c == 1 ?
			(a->b = a->b - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
		e->color_c == 2 ?
			(a->r = a->r - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
	}
	else
	{
		e->color_c == 0 ? (a->g = 0) : 0;
		if (e->color_c == 1)
			a->b = 0;
		else
			a->r = 0;
		e->color_c == 0 ?
			(a->b = a->b - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
		e->color_c == 1 ?
			(a->r = a->r - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
		e->color_c == 0 ?
			(a->g = a->g - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
	}
}

int		fdf_color_s(t_env *e, int i, int z_max)
{
	t_col	a;

	a.r = 255;
	a.g = 255;
	a.b = 255;
	if (e->color_c == 3)
		return (0xFFFFFF);
	if (((z_max - e->pos[i].z) * 10) <= 255)
	{
		e->color_c == 0 ? (a.r = a.r - ((z_max - e->pos[i].z) * 10)) : 0;
		e->color_c == 1 ? (a.g = a.g - ((z_max - e->pos[i].z) * 10)) : 0;
		e->color_c == 2 ? (a.b = a.b - ((z_max - e->pos[i].z) * 10)) : 0;
	}
	else
	{
		(e->color_c == 0) ? (a.r = 0) : 0;
		if (e->color_c == 1)
			a.g = 0;
		else
			a.b = 0;
		fdf_color_ss(e, &a, i, z_max);
	}
	return (((a.r & 0xFF) << 16) + ((a.g & 0xFF) << 8) + (a.b & 0xFF));
}

int		fdf_color(t_env *e, int i)
{
	int		j;
	int		z_max;
	int		z_min;

	j = -1;
	z_max = -2147483648;
	z_min = 2147483647;
	while (++j < (e->x_max * e->y_max))
	{
		if (e->pos[j].z > z_max)
			z_max = e->pos[j].z;
		if (e->pos[j].z < z_min)
			z_min = e->pos[j].z;
	}
	if (z_max != z_min)
	{
		if (e->color_c == 0)
			return (fdf_color_s(e, i, z_max));
		else if (e->color_c == 1)
			return (fdf_color_s(e, i, z_max));
		else if (e->color_c == 2)
			return (fdf_color_s(e, i, z_max));
	}
	return (0xFFFFFF);
}

int		fdf_draw_color(t_env *e, int i, char c)
{
	if (e->color == 1)
	{
		if (c == 'x' && e->pos[i].z > 0 && e->pos[i + 1].z != e->pos[i].z)
			return (e->pos[i + 1].color);
		else if (c == 'y' && e->pos[i].z > 0 &&
				e->pos[i + e->x_max].z != e->pos[i].z)
			return (e->pos[i + e->x_max].color);
		return (e->pos[i].color);
	}
	else
	{
		if (c == 'x' && e->pos[i].z > 0 && e->pos[i + 1].z != e->pos[i].z)
			return (fdf_color(e, i + 1));
		else if (c == 'y' && e->pos[i].z > 0 &&
				e->pos[i + e->x_max].z != e->pos[i].z)
			return (fdf_color(e, i + e->x_max));
		return (fdf_color(e, i));
	}
}
