/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:07:34 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/16 19:22:33 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		fdf_color_s(t_env *e, int i, int z_max)
{
	int		r;
	int		g;
	int		b;

	r = 255;
	g = 255;
	b = 255;
	if (e->color_c == 3)
		return (0xFFFFFF);
	if (((z_max - e->pos[i].z) * 10) <= 255)
	{
		e->color_c == 0 ? (r = r - ((z_max - e->pos[i].z) * 10)) : 0;
		e->color_c == 1 ? (g = g - ((z_max - e->pos[i].z) * 10)) : 0;
		e->color_c == 2 ? (b = b - ((z_max - e->pos[i].z) * 10)) : 0;
	}
	else
	{
		e->color_c == 0 ? (r = 0) : 0;
		e->color_c == 1 ? (g = 0) : (b = 0);
		if (((z_max - e->pos[i].z) * 10) <= 510)
		{
			e->color_c == 0 ? (g = g - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
			e->color_c == 1 ? (b = b - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
			e->color_c == 2 ? (r = r - (((z_max - e->pos[i].z) * 10) - 255)) : 0;
		}
		else
		{
			e->color_c == 0 ? (g = 0) : 0;
			e->color_c == 1 ? (b = 0) : (r = 0);
			e->color_c == 0 ? (b = b - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
			e->color_c == 1 ? (r = r - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
			e->color_c == 0 ? (g = g - (((z_max - e->pos[i].z) * 10) - 510)) : 0;
		}
	}
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
}

int		fdf_color(t_env *e, int i)
{
	int		j;
	int		z_max;
	int		z_min;
	
	j = -1;
	z_max = -2147483648;
	z_min = 2147483647;
	while (++j < (e->x_max * e->y_max))
	{
		if (e->pos[j].z > z_max)
			z_max = e->pos[j].z;
		if (e->pos[j].z < z_min)
			z_min = e->pos[j].z;
	}
	if (z_max != z_min)
	{
		if (e->color_c == 0)
			return(fdf_color_s(e, i, z_max));
		else if (e->color_c == 1)
			return (fdf_color_s(e, i, z_max));
		else if (e->color_c == 2)
			return (fdf_color_s(e, i, z_max));
	}
	return (0xFFFFFF);
}

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

void	fdf_draw_y(t_env *e, int i, int x_gap, int y_gap)
{
	if ((i + e->x_max) < (e->x_max * e->y_max))
	{
		e->pos->x_a[0] = ((e->pos[i].x * e->gap) + x_gap / 2) +
			(e->pos[i].z * e->z_scale);
		e->pos->x_a[1] = e->pos->x_a[0];
		e->pos->x_a[2] = ((e->pos[i + (e->x_max)].x * e->gap) +
				x_gap / 2) + (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[0] = ((e->pos[i].y * e->gap) + y_gap / 2) -
			(e->pos[i].z * e->z_scale);
		e->pos->y_a[2] = ((e->pos[i + (e->x_max)].y * e->gap) +
				y_gap / 2) - (e->pos[i + (e->x_max)].z * e->z_scale);
		e->pos->y_a[1] = e->pos->y_a[0];
		while (e->pos->y_a[0] <= e->pos->y_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, (((e->pos->x_a[2] -
							e->pos->x_a[1]) / (e->pos->y_a[2] - e->pos->y_a[1]))
					* (e->pos->y_a[0] - e->pos->y_a[1]) + e->pos->x_a[1])
					, e->pos->y_a[0], (e->color == 1) ?
					e->pos[i].color : fdf_color(e, i));
			e->pos->y_a[0]++;
		}
	}
}

void	fdf_draw_s(t_env *e, int i, int x_gap, int y_gap)
{
	e->pos->x_a[0] = ((e->pos[i].x * e->gap) + x_gap / 2) +
		(e->pos[i].z * e->z_scale);
	e->pos->x_a[1] = e->pos->x_a[0];
	e->pos->x_a[2] = ((e->pos[i + 1].x * e->gap) + x_gap / 2)
		+ (e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[0] = ((e->pos[i].y * e->gap) + y_gap / 2) -
		(e->pos[i].z * e->z_scale);
	e->pos->y_a[2] = ((e->pos[i + 1].y * e->gap) + y_gap / 2) -
		(e->pos[i + 1].z * e->z_scale);
	e->pos->y_a[1] = e->pos->y_a[0];
}

void	fdf_draw(t_env *e)
{
	int		i;
	int		x_gap;
	int		y_gap;

	i = -1;
	(e->x_max >= e->y_max) ?
		(e->gap = (e->win_x / e->x_max) / e->zoom) : (e->gap = (e->win_y / e->y_max) / e->zoom);
	(e->x_max >= e->y_max) ? (x_gap = e->win_x - (e->gap * (e->x_max - 1))) :
		(x_gap = (e->win_x - (e->gap * (e->x_max - 1))));
	(e->x_max >= e->y_max) ? (y_gap = e->win_y - (e->gap * (e->y_max - 1))) :
		(y_gap = e->win_y - (e->gap * (e->y_max - 1)));
	x_gap += e->x_gap;
	y_gap += e->y_gap;
	while (++i < (e->y_max * e->x_max))
	{
		fdf_draw_s(e, i, x_gap, y_gap);
		while (e->pos->x_a[0] <= e->pos->x_a[2])
		{
			mlx_pixel_put(e->mlx_ptr, e->win_ptr, e->pos->x_a[0],
					(((e->pos->y_a[2] - e->pos->y_a[1]) /
					(e->pos->x_a[2] - e->pos->x_a[1])) *
					(e->pos->x_a[0] - e->pos->x_a[1]) +
					e->pos->y_a[1]), (e->color == 1) ?
					e->pos[i].color : fdf_color(e, i));
			e->pos->x_a[0]++;
		}
		fdf_draw_y(e, i, x_gap, y_gap);
	}
}

void	fdf_win_message(t_env *e)
{
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 5, 0xFFFFFF, "[ESC] to exit");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 25, 0xFFFFFF, "[Q] to zoom-in");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 45, 0xFFFFFF, "[W] to zoom-out");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 65, 0xFFFFFF, "ARROW KEY to move");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 85, 0xFFFFFF, "[R] to reset");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 105, 0xFFFFFF, "[Page Up] to increase z");
	mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 125, 0xFFFFFF, "[Page Down] to decrease z");
	if (e->color == 0)
		mlx_string_put(e->mlx_ptr, e->win_ptr, 5, 145, 0xFFFFFF, "[C] to change color");
}

int		fdf_key_reset(t_env *e)
{
	int		i;

	i = -1;
	e->zoom = 1;
	e->y_gap = 0;
	e->x_gap = 0;
	while (++i < (e->x_max * e->y_max))
		e->pos[i].z = e->pos[i].z_sav;
	return (0);
}

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

int		fdf_key_color(t_env *e)
{
	if (e->color_c < 3)
		e->color_c += 1;
	else if (e->color_c == 3)
		e->color_c = 0;
	return (0);
}

void	fdf_key_nine(int key, t_env *e)
{
	int		tmp;
	int		i;

	if (key == 0 && e->nine < 3)
		e->nine += 1;
	else if (key == 1 && e->nine > 0)
		e->nine -= 1;
	else if (key == 0 && e->nine == 3)
		e->nine = 0;
	else if (key == 1 && e->nine == 0)
		e->nine = 3;
	i = -1;
	if (e->nine == 1)
	{
		while (++i < (e->x_max * e->y_max))
		{
			tmp = e->pos[i].x;
			e->pos[i].x = e->pos[i].y;
			e->pos[i].y = tmp;
		}
	}
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
	key == 8 ? fdf_key_color(e) : 0;
	(key == 0 || key == 1) ? fdf_key_nine(key, e) : 0;
	return (0);
}

int		fdf_key(int key, t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	fdf_key_function(key, e);
	fdf_win_message(e);
	fdf_draw(e);
	mlx_hook(e->win_ptr, 2, 0, fdf_key, e);
	mlx_loop(e->mlx_ptr);
	return (0);
}

void	fdf_window(t_env *e)
{
	fdf_win_message(e);
	fdf_draw(e);
	mlx_hook(e->win_ptr, 2, 0, fdf_key, e);
	mlx_loop(e->mlx_ptr);
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
	e.pos = ft_memalloc(sizeof(t_pos) * (e.y_max * e.x_max) + 1);
	ft_bzero(e.pos, sizeof(t_pos) * (e.y_max * e.x_max) + 1);
	line = fdf_read(av[1], &e);
	fdf_put_struct(line, &e);
	e.mlx_ptr = mlx_init();
	e.win_x = ft_atoi(av[2]);
	e.win_y = ft_atoi(av[3]);
	e.z_scale = 2;
	e.zoom = 1;
	e.win_ptr = mlx_new_window(e.mlx_ptr, e.win_x, e.win_y, "FdF");
	fdf_window(&e);
	return (0);
}
