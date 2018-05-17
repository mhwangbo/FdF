/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:40:51 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 14:58:15 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_key_up_down(int key, t_env *e)
{
	int		i;

	i = -1;
	key == 116 ? (e->z_inc += 0.5) : 0;
	key == 121 ? (e->z_inc -= 0.5) : 0;
	while (++i < (e->x_max * e->y_max))
		e->pos[i].z = e->pos[i].z_sav;
	i = -1;
	while (++i < (e->x_max * e->y_max))
		e->pos[i].z += (e->pos[i].z * e->z_inc);
	return (0);
}

int		fdf_key_color(int key, t_env *e)
{
	if (key == 7 && e->color == 1 && e->color_tmp == 1)
		e->color = 0;
	else if (key == 7 && e->color == 0 && e->color_tmp == 1)
		e->color = 1;
	else if (key == 8 && e->color == 0 && e->color_c < 3)
		e->color_c += 1;
	else if (key == 8 && e->color == 0 && e->color_c == 3)
		e->color_c = 0;
	return (0);
}
