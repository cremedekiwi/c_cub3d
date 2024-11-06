/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:27 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 17:18:14 by habernar         ###   ########.fr       */
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
# define FOV 60 * PI / 180
# define PI 3.14159265
# define NUM_RAYS W_WIDTH
# define SCALE_MAP 0.2
# define VELOCITY 1
# define ANGULAR_VELOCITY PI / 200
# define MLX_PTR "Error: mlx_init failed\n"
# define MLX_WIN "Error: mlx_new_window() failed\n"
# define MLX_IMG "Error: mlx_new_image() failed\n"
# define MLX_TEXT "Error: mlx_xpm_to_image() failed\n"
# define MALLOC "Error: malloc() failed\n"
# define ARGS "Error: you must provide one argument\n"
# define FD "Error: you could not open file\n"
# define MAP_NOT_LAST "Error: .cub invalid map should be last\n"
# define COLOR "Error, color values out of range [0, 255]\n"
# define FILEFORMAT "Error, file must be .cub\n"
# define CARDINAL "Error, must be one cardinal point\n"
# define EMPTY_LINE "Error, empty line in map\n"
# define EMPTY_FILE "Error, empty file\n"
# define MAP "Error, file contains an open map\n"
# define MAP_ARGS "Error, file does not contain every arguments\n"
# define MAP_CHAR "Error, file does contain invalid char\n"

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_dda
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int err;
	int e2;
}	t_dda;

typedef struct s_minimap
{
	int		radius;
	int		size;
	t_vec2	center;
	t_vec2	player;
}	t_minimap;

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

typedef struct s_render
{
    t_wall    wall;
    t_img    *texture;
    int        tex_x;
}    t_render;

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

int	cursor_motion(int x, int y, t_data *data);
/* map */
int		is_map(char *str);
void	get_map_dimension(t_data *data, char **tab);
void	get_player_position(t_data *data);
void	get_map(t_data *data, char *str, int fd);
/* tab */
void	free_tab(char **tab);
char	**tab_append(char **tab, char *str);
void	copy_tab(t_data *data, char **tab);
/* texture */
int		is_texture(char *str);
void	create_texture(t_data *data, char *str, int fd, t_img *img);
void	get_texture(t_data *data, char *str, int fd);
/* exit */
void	exit_error(t_data *data, char *msg);
void	exit_game(t_data *data);

t_vec2	vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2);

/* parse */
void	parse_map(t_data *data, char *str);
/* wall */
void	get_wall_parameters(t_wall *wall, t_ray *ray, float proj_dist);
void	calculate_wall_height(t_wall *wall, float corrected_distance);
void	determine_texture(t_data *data, int ray_index, t_render *render_info);
void	render_wall(t_data *data, int ray_index, t_render render_info);
/* map utils */
int	is_map(char *str);
int	invalid_char(char c);
int	ft_isspace(char c);
int	is_empty_line(char *str);
void	get_map_dimension(t_data *data, char **tab);
/* map */
void	get_player_position(t_data *data);
void	verify_arguments(t_data *data);
/* minimap */
void	init_minimap(t_data *data, t_minimap *minimap);
bool	is_in_minimap(t_minimap *minimap, t_vec2 v);
void	draw_minimap_wall(t_data *data, t_minimap *minimap);
void draw_player_and_rays(t_data *data, t_minimap *minimap);
void	render_rays(t_data *data);

#endif 
