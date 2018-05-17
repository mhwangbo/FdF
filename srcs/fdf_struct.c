/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:45:09 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 15:30:21 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_find_max(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;
	int		tmp_max;

	fd = open(av, O_RDONLY);
	(fd < 1) ? fdf_error(2) : 0;
	i = -1;
	while (get_next_line(fd, &line) == 1)
	{
		e->y_max += 1;
		if (e->y_max == 1)
			while (line[++i])
				(line[i] != ' ' && (i - 1 == -1 || line[i - 1] == ' ')) ?
					e->x_max += 1 : 0;
		i = -1;
		tmp_max = 0;
		while (e->y_max != 1 && line[++i])
			(line[i] != ' ' && (i - 1 == -1 || line[i - 1] == ' ')) ?
				tmp_max += 1 : 0;
		(tmp_max != e->x_max && e->y_max != 1) ? fdf_error(3) : 0;
		free(line);
	}
	close(fd);
}

int		*fdf_split(char *line, t_env *e)
{
	int		*line_i;
	char	**tmp;
	char	*tmp_t;
	char	*tmp_t_t;
	int		x;

	line_i = ft_memalloc(sizeof(int) * e->x_max + 1);
	tmp = ft_strsplit(line, ' ');
	x = -1;
	while (++x < e->x_max)
	{
		if ((tmp_t = ft_strchr(tmp[x], ',')))
		{
			tmp_t_t = tmp_t + 1;
			e->color = 1;
			e->color_tmp = 1;
			e->pos[(e->x_max * (e->i - 1)) + x].color = ft_atoi_base(tmp_t_t);
		}
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
		e->i++;
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
	while (++y < e->y_max)
	{
		x = -1;
		while (++x < e->x_max)
		{
			(e->pos[i].color == 0) ? e->pos[i].color = 0xFFFFFF : 0;
			e->pos[i].x = x;
			e->pos[i].y = y;
			e->pos[i].z_sav = line[y][x];
			e->pos[i++].z = line[y][x];
		}
	}
}
