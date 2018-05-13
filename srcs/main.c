/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:07:34 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/12 18:14:29 by mhwangbo         ###   ########.fr       */
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

	printf("LINE: %s\n", line);
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
	while (get_next_line(fd, &line) == 1 && ++y < e->y_max)
	{
		file[y] = fdf_split(line, e);
		free(line);
	}
	file[y] = NULL;
	close(fd);
	return (file);
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
	e.mlx_ptr = mlx_init();
	e.win_x = ft_atoi(av[2]);
	e.win_y = ft_atoi(av[3]);
	e.win_ptr = mlx_new_window(e.mlx_ptr, e.win_x, e.win_y, "FdF");
	mlx_pixel_put(e.mlx_ptr, e.win_ptr, e.win_x/2, e.win_y/2, 0xFFFFFF);
	mlx_loop(e.mlx_ptr);
	return (0);
}
