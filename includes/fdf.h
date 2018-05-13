/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:27:32 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/12 15:11:19 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "../lib/Libft/libft.h"
#include <math.h>
#include <mlx.h>

typedef struct		s_env
{
	int		win_x;
	int		win_y;
	int		x_max;
	int		y_max;
	int		x;
	int		y;
	void	*mlx_ptr;
	void	*win_ptr;
}					t_env;

#endif
