/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:07:34 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 19:26:57 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	fdf_win_message(t_env *e)
{
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 5, 0xFFFFFF, "[ESC] : exit");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 25, 0xFFFFFF, "[Q] : zoom-in");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 45, 0xFFFFFF, "[W] : zoom-out");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 65, 0xFFFFFF, "ARROW KEY : move");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 85, 0xFFFFFF, "[R] : reset");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 105, 0xFFFFFF,
			"[Page Up] : z increase");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 125, 0xFFFFFF,
			"[Page Down] : z decrease");
	if (e->color == 0)
		mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 145, 0xFFFFFF, "[C] : color");
	if (e->color_tmp == 1)
		mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 165, 0xFFFFFF,
				"[X] : custom color");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 185, 0xFFFFFF, "[A] : clockwise");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 205, 0xFFFFFF,
			"[S] : counter clockwise");
}

void	fdf_window(t_env *e)
{
	fdf_win_message(e);
	fdf_draw(e);
	mlx_hook(e->win_ptr, 2, 2, fdf_key, e);
	mlx_loop(e->mlx_ptr);
}

void	fdf_error(int i)
{
	if (i == 0)
		ft_putstr("usage: ./fdf [map] [win_x] [win_y]\n");
	else if (i == 1)
		ft_putstr("error: empty file");
	else if (i == 2)
		ft_putstr("error: cannot open file");
	else if (i == 3)
		ft_putstr("error: not a valid map");
	exit(0);
}

void	fdf_copy(t_env *e)
{
	int	i;
	
	i = -1;
	e->tmp = ft_memalloc(sizeof(t_pos) * (e->y_max * e->x_max) + 1);
	while (++i < (e->y_max * e->x_max))
		e->tmp[i] = e->pos[i];
}

int		main(int ac, char **av)
{
	t_env	e;
	int		**line;

	ft_bzero(&e, sizeof(t_env));
	if (ac != 4)
		fdf_error(0);
	fdf_find_max(av[1], &e);
	if (e.x_max == 0)
		fdf_error(1);
	e.pos = ft_memalloc(sizeof(t_pos) * (e.y_max * e.x_max) + 1);
	ft_bzero(e.pos, sizeof(t_pos) * (e.y_max * e.x_max) + 1);
	line = fdf_read(av[1], &e);
	fdf_put_struct(line, &e);
	e.win_x = ft_atoi(av[2]);
	e.win_y = ft_atoi(av[3]);
	e.z_scale = 2;
	e.zoom = 1;
	e.mlx_ptr = mlx_init();
	e.win_ptr = mlx_new_window(e.mlx_ptr, e.win_x, e.win_y, "FdF");
	fdf_copy(&e);
	fdf_window(&e);
	return (0);
}
