/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:27:32 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/16 19:16:11 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/Libft/libft.h"
# include <math.h>
# include <mlx.h>

typedef struct		s_pos
{
	int				x;
	int				y;
	int				z;
	int				z_sav;
	float			x_a[3];
	float			y_a[3];
	int				color;
}					t_pos;

typedef struct		s_env
{
	int				win_x;
	int				win_y;
	int				x_max;
	int				y_max;
	float			z_inc;
	int				gap;
	float			x_gap;
	float			y_gap;
	int				z_scale;
	int				color;
	int				color_c;
	int				i;
	float			zoom;
	void			*mlx_ptr;
	void			*win_ptr;
	int				nine;
	t_pos			*pos;
}					t_env;

/*
** fdf_draw
*/
void				fdf_draw(t_env *e);
void				fdf_draw_s(t_env *e, int i, int x_gap, int y_gap);
void				fdf_draw_y(t_env *e, int i, int x_gap, int y_gap);

/*
** fdf_read
*/
void				fdf_put_struct(int **line, t_env *e);
int					**fdf_read(char *av, t_env *e);
int					*fdf_split(char *line, t_env *e);
void				fdf_find_max(char *av, t_env *e);
#endif
