/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:38:39 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 20:46:03 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_key_reset(t_env *e)
{
	int		i;

	i = -1;
	while (++i < (e->x_max * e->y_max))
		e->pos[i] = e->tmp[i];
	while (e->nine != 0)
		fdf_key_nine(0, e);
	e->zoom = 1;
	e->y_gap = 0;
	e->x_gap = 0;
	e->color_c = 0;
	e->color = e->color_tmp;
	i = -1;
	while (++i < (e->x_max * e->y_max))
		e->pos[i].z = e->pos[i].z_sav;
	e->z_inc = 0;
	return (0);
}

int		fdf_key_function(int key, t_env *e)
{
	key == 53 ? exit(0) : 0;
	key == 12 ? (e->zoom -= 0.1) : 0;
	key == 13 ? (e->zoom += 0.1) : 0;
	key == 126 ? (e->y_gap -= 10) : 0;
	key == 125 ? (e->y_gap += 10) : 0;
	key == 124 ? (e->x_gap += 10) : 0;
	key == 123 ? (e->x_gap -= 10) : 0;
	key == 15 ? fdf_key_reset(e) : 0;
	(key == 116 || key == 121) ? fdf_key_up_down(key, e) : 0;
	(key == 8 || key == 7) ? fdf_key_color(key, e) : 0;
	(key == 0 || key == 1) ? fdf_key_nine(key, e) : 0;
	((key >= 83 && key <= 85) || key == 87 ||
	 key == 89 || key == 91) ? fdf_key_rotate(key, e) : 0;
	return (0);
}

int		fdf_key(int key, t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	fdf_key_function(key, e);
	fdf_draw(e);
	fdf_win_message(e);
	mlx_hook(e->win_ptr, 2, 2, fdf_key, e);
	mlx_loop(e->mlx_ptr);
	return (0);
}
