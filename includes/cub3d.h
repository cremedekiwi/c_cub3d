/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:27 by habernar          #+#    #+#             */
/*   Updated: 2024/10/28 12:50:27 by habernar         ###   ########.fr       */
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

# define MAP_ROWS 13
# define MAP_COLS 20
# define CUBE_SIZE 64
# define W_WIDTH (MAP_COLS * CUBE_SIZE)
# define W_HEIGHT (MAP_ROWS * CUBE_SIZE)
# define FOV (60 * (PI / 180))
# define PI 3.14159265
# define NUM_RAYS W_WIDTH
# define SCALE_MAP 0.2
# define VELOCITY 3
# define ANGULAR_VELOCITY (PI / 180)

extern int  map[MAP_ROWS][MAP_COLS];

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
}	t_img;

typedef struct s_map
{
	int		**m;
	void	*text_north;
	void	*text_south;
	void	*text_est;
	void	*text_west;
	// color ceiling;
	// color floor;
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
	t_map		map;
	t_player	player;
	t_ray		rays[W_WIDTH];
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
void	move_player(t_player *player);
int		ft_abs(int x);
float	angle_normalize(float angle);
float	distance(t_vec2 v1, t_vec2 v2);
void	exit_game(t_data *data);
int		is_wall_at(float x, float y);
void	init_rays(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
//void	draw_line(t_data *data, t_vec2 v1, t_vec2 v2);
void	draw_line(t_data *data, int x0, int y0, int x1, int y1);
int		draw_rect(t_img *img, t_rect rect);
t_vec2	vec2_scale(t_vec2 v, float scale);

#endif 
