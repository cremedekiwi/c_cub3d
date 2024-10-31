/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:27 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 16:52:02 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../includes/libft.h"
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include <limits.h>

# define W_WIDTH 1200
# define W_HEIGHT 800
# define CUBE_SIZE 32
# define FOV (60 * (PI / 180))
# define PI 3.14159265
# define NUM_RAYS W_WIDTH
# define SCALE_MAP 0.3
# define VELOCITY 2
# define ANGULAR_VELOCITY (PI / 200)

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_mat2
{
	float	m[2][2];
}	t_mat2;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
	char	*path;
}	t_img;

typedef struct s_map
{
	char	**m;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	int		delta_angle;
	int		forward;
	int		sideway;
	float	angle;
}	t_player;

typedef struct s_wall
{
	int		start;
	int		end;
	float	proj_dist;
	float	height;
}	t_wall;

typedef struct s_ray
{
	t_vec2	hit;
	float	angle;
	float	distance;
	bool	hitvertical;;
	bool	rayfacingup;
	bool	rayfacingleft;
	int		value;
}	t_ray;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;
	t_img		*text_no;
	t_img		*text_so;
	t_img		*text_we;
	t_img		*text_ea;
	t_map		map;
	t_player	player;
	t_ray		rays[W_WIDTH];
	int			color_ceiling;
	int			color_floor;
}	t_data;

typedef struct s_rect
{
	int x;
	int y;
	int height;
	int width;
	int color;
}	t_rect;

int		handle_keyrelease(int keysym, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);
void	move_player(t_data *data, t_player *player);
int		ft_abs(int x);
float	angle_normalize(float angle);
float	distance(t_vec2 v1, t_vec2 v2);
void	exit_game(t_data *data);
int		is_wall_at(t_data *data,float x, float y);
void	init_rays(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
//void	draw_line(t_data *data, t_vec2 v1, t_vec2 v2);
void	draw_line(t_data *data, int x0, int y0, int x1, int y1);
int		draw_rect(t_img *img, t_rect rect);
t_vec2	vec2_scale(t_vec2 v, float scale);

#endif
