/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:27:32 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/17 20:49:11 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../lib/Libft/libft.h"
# include <math.h>
# include <mlx.h>

typedef struct		s_pos
{
	float			x;
	float			y;
	float			z;
	float			z_sav;
	float			x_a[3];
	float			y_a[3];
	int				color;
}					t_pos;

typedef struct		s_col
{
	int				r;
	int				g;
	int				b;
}					t_col;

typedef struct		s_env
{
	int				win_x;
	int				win_y;
	float			x_angle;
	float			y_angle;
	float			z_angle;
	int				x_max;
	int				y_max;
	float			z_inc;
	int				gap;
	float			x_gap;
	float			y_gap;
	int				z_scale;
	int				color;
	int				color_tmp;
	int				color_c;
	int				i;
	float			zoom;
	void			*mlx_ptr;
	void			*win_ptr;
	int				nine;
	t_pos			*pos;
	t_pos			*tmp;
}					t_env;

/*
** fdf_struct
*/
void				fdf_put_struct(int **line, t_env *e);

/*
** fdf_color
*/
void				fdf_color_ss(t_env *e, t_col *a, int i, int z_max);
int					fdf_color_s(t_env *e, int i, int z_max);
int					fdf_color(t_env *e, int i);
int					fdf_draw_color(t_env *e, int i, char c);

/*
** fdf_draw
*/
void				fdf_draw(t_env *e);
void				fdf_raw_cal(t_env *e, int *x_gap, int *y_gap);
void				fdf_draw_s(t_env *e, int i, int x_gap, int y_gap);
void				fdf_draw_y(t_env *e, int i, int x_gap, int y_gap);

/*
** fdf_read
*/
void				fdf_put_struct(int **line, t_env *e);
int					**fdf_read(char *av, t_env *e);
int					*fdf_split(char *line, t_env *e);
void				fdf_find_max(char *av, t_env *e);

/*
** fdf_key_etc
*/
int					fdf_key_up_down(int key, t_env *e);
int					fdf_key_color(int key, t_env *e);

/*
** fdf_key_nine
*/
void				fdf_key_nine_one_s(t_env *e, t_pos *tmp_p);
void				fdf_key_nine_one_ss(t_env *e, t_pos *tmp_p, int *i, int x);
void				fdf_key_nine_one(t_env *e);
void				fdf_key_nine(int key, t_env *e);

/*
** fdf_key
*/
int					fdf_key_reset(t_env *e);
int					fdf_key_function(int key, t_env *e);
int					fdf_key(int key, t_env *e);

/*
** fdf_key_rotate
*/
void				fdf_key_rotate(int key, t_env *e);

/*
** main
*/
void				fdf_win_message(t_env *e);
void				fdf_window(t_env *e);
void				fdf_error(int i);
int					main(int ac, char **av);
#endif
