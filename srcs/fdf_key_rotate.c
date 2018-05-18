/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:21:09 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 20:49:09 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_key_rotate_x(t_env *e)
{
	float	y;
	float	z;
	int		i;

	i = -1;
	while (++i < (e->y_max * e->x_max))
	{
		y = e->pos[i].y;
		z = e->pos[i].z;
		e->pos[i].y = (y * cos(e->x_angle)) - (z * sin(e->x_angle));
		e->pos[i].z = (y * sin(e->x_angle)) + (z * cos(e->x_angle));
	}
}

void	fdf_key_rotate_y(t_env *e)
{
	float	x;
	float	z;
	int		i;

	i = -1;
	while (++i < (e->y_max * e->x_max))
	{
		x = e->pos[i].x;
		z = e->pos[i].z;
		e->pos[i].x = (z * sin(e->y_angle)) + (x * cos(e->y_angle));
		e->pos[i].z = (z * cos(e->y_angle)) - (x * sin(e->y_angle));
	}
}

void	fdf_key_rotate_z(t_env *e)
{
	float	x;
	float	y;
	int		i;

	i = -1;
	while (++i < (e->y_max * e->x_max))
	{
		x = e->pos[i].x;
		y = e->pos[i].y;
		e->pos[i].x = (x * cos(e->z_angle)) - (y * sin(e->z_angle));
		e->pos[i].y = (x * sin(e->z_angle)) + (y * cos(e->z_angle));
	}
}

void	fdf_key_rotate(int key, t_env *e)
{
	key == 84 ? e->x_angle -= M_PI / 60 : 0;
	key == 87 ? e->x_angle += M_PI / 60 : 0;
	key == 83 ? e->y_angle -= M_PI / 120 : 0;
	key == 85 ? e->y_angle += M_PI / 120 : 0;
	key == 89 ? e->z_angle -= M_PI / 90 : 0;
	key == 91 ? e->z_angle += M_PI / 90 : 0;
	(key == 87 || key == 84) ? fdf_key_rotate_x(e) : 0;
	(key == 83 || key == 85) ? fdf_key_rotate_y(e) : 0;
	(key == 89 || key == 91) ? fdf_key_rotate_z(e) : 0;
	e->x_angle = 0;
	e->y_angle = 0;
	e->z_angle = 0;
}
