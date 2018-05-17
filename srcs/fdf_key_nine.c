/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_nine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:39:44 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 15:55:27 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_key_nine_one_s(t_env *e, t_pos *tmp_p)
{
	int		i;

	i = -1;
	while (++i < (e->x_max * e->y_max))
	{
		e->pos[i].x = tmp_p[i].x;
		e->pos[i].y = tmp_p[i].y;
		e->pos[i].z = tmp_p[i].z;
		e->pos[i].color = tmp_p[i].color;
	}
}

void	fdf_key_nine_one_ss(t_env *e, t_pos *tmp_p, int *i, int x)
{
	int		y;
	int		y_tmp;
	int		j;

	y = e->x_max;
	y_tmp = 0;
	while (--y > -1)
	{
		j = -1;
		while (++j < (e->x_max * e->y_max))
			if (e->pos[j].x == x && e->pos[j].y == y)
			{
				tmp_p[*i].x = y_tmp++;
				tmp_p[*i].y = x;
				tmp_p[*i].z = e->pos[j].z;
				tmp_p[*i].color = e->pos[j].color;
				*i += 1;
			}
	}
}

void	fdf_key_nine_one(t_env *e)
{
	int		i;
	int		x;
	int		tmp;
	t_pos	*tmp_p;

	i = 0;
	tmp_p = ft_memalloc(sizeof(t_pos) * (e->x_max * e->y_max));
	tmp = e->y_max;
	e->y_max = e->x_max;
	e->x_max = tmp;
	while (i < (e->x_max * e->y_max))
	{
		x = -1;
		while (++x < e->y_max)
			fdf_key_nine_one_ss(e, tmp_p, &i, x);
	}
	fdf_key_nine_one_s(e, tmp_p);
}

void	fdf_key_nine(int key, t_env *e)
{
	int	i;

	i = 4;
	if (key == 0 && e->nine < 3)
	{
		e->nine += 1;
		fdf_key_nine_one(e);
	}
	else if (key == 1 && e->nine > 0)
	{
		e->nine -= 1;
		while (--i)
			fdf_key_nine_one(e);
	}
	else if (key == 0 && e->nine == 3)
	{
		e->nine = 0;
		fdf_key_nine_one(e);
	}
	else if (key == 1 && e->nine == 0)
	{
		e->nine = 3;
		while (--i)
			fdf_key_nine_one(e);
	}
}
