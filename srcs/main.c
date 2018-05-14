/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:07:34 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/13 20:13:17 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	fdf_find_max(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd < 1)
		ft_putstr("error: cannot open file");
	i = -1;
	while (get_next_line(fd, &line) == 1)
	{
		e->y_max += 1;
		if (e->y_max == 1)
			while (line[++i])
				(line[i] != ' ' && (i - 1 == -1 || line[i - 1] == ' ')) ?
				 e->x_max += 1 : 0;
		free(line);
	}
	close(fd);
}

int		*fdf_split(char *line, t_env *e)
{
	int		*line_i;
	char	**tmp;
	int		x;

	line_i = ft_memalloc(sizeof(int) * e->x_max + 1);
	tmp = ft_strsplit(line, ' ');
	x = -1;
	while (++x < e->x_max)
		line_i[x] = ft_atoi(tmp[x]);
	free(tmp);
	return (line_i);
}

int		**fdf_read(char *av, t_env *e)
{
	int		**file;
	char	*line;
	int		fd;
	int		y;

	fd = open(av, O_RDONLY);
	y = -1;
	file = (int**)malloc(sizeof(int*) * (e->y_max + 1));
	while (get_next_line(fd, &line) > 0 && ++y < e->y_max)
	{
		file[y] = fdf_split(line, e);
		free(line);
	}
	if (get_next_line(fd, &line) == 0 && ++y < e->y_max)
		file[y] = fdf_split(line, e);
	file[y] = NULL;
	close(fd);
	return (file);
}

void	fdf_put_struct(int **line, t_env *e)
{
	int		y;
	int		x;
	int		i;

	e->pos = ft_memalloc(sizeof(t_pos) * (e->y_max * e->x_max) + 1);
	ft_bzero(e->pos, sizeof(t_pos) * (e->y_max * e->x_max) + 1);
	y = -1;
	i = 0;
	while (++y < e->y_max)
	{
		x = -1;
		while (++x < e->x_max)
		{
			e->pos[i].x = x;
			e->pos[i].y = y;
			e->pos[i++].z = line[y][x];
		}
	}
}

/*
void	fdf_draw(t_env *e)
{
	int		i;
	int		tmp_gap;

	i = -1;
	if (e->x_max >= e->y_max)
	{
		e->gap = e->win_x/e->x_max;
		tmp_gap = e->win_y - (e->gap * (e->y_max - 1));
		while (++i < (e->y_max * e->x_max))
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, ((e->pos[i].x * e->gap) + e->gap/2) + (e->pos[i].z * e->z_scale), ((e->pos[i].y * e->gap) + tmp_gap/2) - (e->pos[i].z * e->z_scale), 0xFFFFFF);
		}
	}
	else if (e->y_max > e->x_max)
	{
		e->gap = e->win_y/e->y_max;
		tmp_gap = e->win_x - (e->gap * (e->x_max - 1));
		while (++i < (e->y_max * e->x_max))
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, ((e->pos[i].x * e->gap) + tmp_gap/2) + (e->pos[i].z * e->z_scale), ((e->pos[i].y * e->gap) + e->gap/2) - (e->pos[i].z * e->z_scale), 0xFFFFFF);
		}
	}
}
*/

void	fdf_draw_y(t_env *e, int i, int tmp_gap)
{
	int		x[3];
	int		y[3];

	if ((i + e->x_max) < (e->x_max * e->y_max))
	{
		x[0] = ((e->pos[i].x * e->gap) + e->gap/2) + (e->pos[i].z * e->z_scale);
		x[1] = x[0];
		x[2] = ((e->pos[i + (e->x_max)].x * e->gap) + e->gap/2) + (e->pos[i + (e->x_max)].z * e->z_scale);
		y[0] = ((e->pos[i].y * e->gap) + tmp_gap/2) - (e->pos[i].z * e->z_scale);
		y[2] = ((e->pos[i + (e->x_max)].y * e->gap) + tmp_gap/2) - (e->pos[i + (e->x_max)].z * e->z_scale);
		y[1] = y[0];
		while (y[0] <= y[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, ((x[2] - x[1])/(y[2] - y[1])) * (y[0] - y[1]) + x[1], y[0], 0xFFFFFF);
			y[0]++;
		}
	}
}

void	fdf_draw(t_env *e)
{
	int		x[3];
	int		y[3];
	int		i;
	int		tmp_gap;

	i = -1;
	e->gap = e->win_x/e->x_max;
	tmp_gap = e->win_y - (e->gap * (e->y_max - 1));
	while (++i < (e->y_max * e->x_max))
	{
		if (i + 1 < (e->y_max * e->x_max))
			(e->pos[i].y != e->pos[i + 1].y) ? i++ : 0;
		x[0] = ((e->pos[i].x * e->gap) + e->gap/2) + (e->pos[i].z * e->z_scale);
		x[1] = x[0];
		x[2] = ((e->pos[i + 1].x * e->gap) + e->gap/2) + (e->pos[i + 1].z * e->z_scale);
		y[0] = ((e->pos[i].y * e->gap) + tmp_gap/2) - (e->pos[i].z * e->z_scale);
		y[2] = ((e->pos[i + 1].y * e->gap) + tmp_gap/2) - (e->pos[i + 1].z * e->z_scale);
		y[1] = y[0];
		while (x[0] <= x[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, x[0], ((y[2] - y[1])/(x[2] - x[1])) * (x[0] - x[1]) + y[1], 0xFFFFFF);
			x[0]++;
		}
		while (y[0] <= y[2])
		{
			if (y[2] - y[1] != 0)
				mlx_pixel_put(e->mlx_ptr, e->win_ptr, ((x[2] - x[1])/(y[2] - y[1])) * (y[0] - y[1]) + x[1], y[0], 0xFFFFFF);
			y[0]++;
		}
//		fdf_draw_y(e, i, tmp_gap);
	}
}

int		main(int ac, char **av)
{
	t_env	e;
	int		**line;

	ft_bzero(&e, sizeof(t_env));
	if (ac != 4)
	{
		ft_putstr("usage: ./fdf [map] [win_x] [win_y]\n");
		return (0);
	}
	fdf_find_max(av[1], &e);
	if (e.x_max == 0)
	{
		ft_putstr("error: empty file");
		return (0);
	}
	line = fdf_read(av[1], &e);
	fdf_put_struct(line, &e);
	e.mlx_ptr = mlx_init();
	e.win_x = ft_atoi(av[2]);
	e.win_y = ft_atoi(av[3]);
	e.z_scale = 2;
	e.win_ptr = mlx_new_window(e.mlx_ptr, e.win_x, e.win_y, "FdF");
	fdf_draw(&e);
	mlx_loop(e.mlx_ptr);
	free(line);
	return (0);
}
