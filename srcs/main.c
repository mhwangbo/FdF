/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:07:34 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/14 19:46:00 by mhwangbo         ###   ########.fr       */
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
	char	**tmp_t;
	int		x;

	line_i = ft_memalloc(sizeof(int) * e->x_max + 1);
	tmp = ft_strsplit(line, ' ');
	x = -1;
	while (++x < e->x_max)
	{
		if (ft_strchr(tmp[x], ','))
		{
			tmp_t = ft_strsplit(tmp[x], ',');
		line_i[x] = ft_atoi(tmp[x]);
		free(tmp[x]);
	}
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

	y = -1;
	i = 0;
	e.pos = ft_memalloc(sizeof(t_pos) * (e.y_max * e.x_max) + 1);
	ft_bzero(e.pos, sizeof(t_pos) * (e.y_max * e.x_max) + 1);
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

void	fdf_draw_y(t_env *e, int i, int tmp_gap)
{
	if ((i + e->x_max) < (e->x_max * e->y_max))
	{
		e->pos->x_a[0] = ((e->pos[i].x * e->gap) + e->gap / 2) +
			(e->pos[i].z * e->z_scale);
		e->pos->x_a[1] = e->pos->x_a[0];
		e->pos->x_a[2] = ((e->pos[i + (e->x_max)].x * e->gap) +
				e->gap / 2) + (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[0] = ((e->pos[i].y * e->gap) + tmp_gap / 2) -
			(e->pos[i].z * e->z_scale);
		e->pos->y_a[2] = ((e->pos[i + (e->x_max)].y * e->gap) +
				tmp_gap / 2) - (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[1] = e->pos->y_a[0];
		while (e->pos->y_a[0] <= e->pos->y_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, ((e->pos->x_a[2] -
							e->pos->x_a[1]) / (e->pos->y_a[2] - e->pos->y_a[1]))
					* (e->pos->y_a[0] - e->pos->y_a[1]) + e->pos->x_a[1],
					e->pos->y_a[0], 0xFFFFFF);
			e->pos->y_a[0]++;
		}
	}
}

void	fdf_draw_s(t_env *e, int i, int tmp_gap)
{
	e->pos->x_a[0] = ((e->pos[i].x * e->gap) + e->gap / 2) +
		(e->pos[i].z * e->z_scale);
	e->pos->x_a[1] = e->pos->x_a[0];
	e->pos->x_a[2] = ((e->pos[i + 1].x * e->gap) + e->gap / 2)
		+ (e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[0] = ((e->pos[i].y * e->gap) + tmp_gap / 2) -
		(e->pos[i].z * e->z_scale);
	e->pos->y_a[2] = ((e->pos[i + 1].y * e->gap) + tmp_gap / 2) -
		(e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[1] = e->pos->y_a[0];
}

void	fdf_draw(t_env *e)
{
	int		i;
	int		tmp_gap;

	i = -1;
	e->gap = e->win_x / e->x_max;
	tmp_gap = e->win_y - (e->gap * (e->y_max - 1));
	while (++i < (e->y_max * e->x_max))
	{
		fdf_draw_s(e, i, tmp_gap);
		while (e->pos->x_a[0] <= e->pos->x_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, e->pos->x_a[0],
					((e->pos->y_a[2] - e->pos->y_a[1]) /
					(e->pos->x_a[2] - e->pos->x_a[1])) *
					(e->pos->x_a[0] - e->pos->x_a[1]) +
					e->pos->y_a[1], 0xFFFFFF);
			e->pos->x_a[0]++;
		}
		fdf_draw_y(e, i, tmp_gap);
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
	return (0);
}
