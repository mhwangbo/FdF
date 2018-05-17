/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:21:09 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 16:38:46 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_key_rotate(int key, t_env *e)
{
	key == 83 ? e->x_angle -= M_PI / 60 : 0;
	key == 85 ? e->x_angle += M_PI / 60 : 0;
	key == 87 ? e->y_angle -= M_PI / 60 : 0;
	key == 84 ? e->y_angle += M_PI / 60 : 0;
	key == 89 ? e->z_angle -= M_PI / 60 : 0;
	key == 91 ? e->z_angle += M_PI / 60 : 0;
//	(key == 83 || key == 85) ? fdf_key_rotate_x(e) : 0;
//	(key == 87 || key == 84) ? fdf_key_rotate_y(e) : 0;
//	(key == 89 || key == 91) ? fdf_key_rotate_z(e) : 0;
}
