/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:01 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 14:13:16 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	(void)color;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
			img_pix_put(img, j++, i , color);
		i++;
	}
}

static void	render_map(t_data *data)
{
	int i;
	int j;

	draw_rect(&data->img, (t_rect){0, 0,
		data->map.rows * CUBE_SIZE * SCALE_MAP,
		data->map.cols * CUBE_SIZE * SCALE_MAP,
		0x000000});
	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			if (data->map.m[i][j] == '1' || data->map.m[i][j] == ' ')
				draw_rect(&data->img, (t_rect){
					j * CUBE_SIZE * SCALE_MAP,
					i * CUBE_SIZE * SCALE_MAP,
					CUBE_SIZE * SCALE_MAP,
					CUBE_SIZE * SCALE_MAP,
					0xFF00FF});
			j++;
		}
		i++;
	}
}

static void	render_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		t_vec2 scale1 = vec2_scale(data->player.pos, SCALE_MAP);
		t_vec2 scale2 = vec2_scale(data->rays[i].hit, SCALE_MAP);
		draw_line(data,scale1.x, scale1.y, scale2.x, scale2.y);
		i++;
	}
}

void	get_wall_parameters(t_wall *wall, t_ray *ray, float proj_dist)
{
	wall->height = (CUBE_SIZE / ray->distance) * proj_dist;
	wall->start = (W_HEIGHT / 2) - (wall->height / 2);
	wall->end = (W_HEIGHT / 2) + (wall->height / 2);
	if (wall->start < 0)
		wall->start = 0;
	if (wall->end > W_HEIGHT)
		wall->end = W_HEIGHT;
}

// void render_walls(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	t_wall	wall;
// 	float	proj_dist;

// 	proj_dist = (W_WIDTH / 2) / tan(FOV / 2);
// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		get_wall_parameters(&wall, &data->rays[i], proj_dist);
// 		j = 0;
// 		while (j < wall.start)
// 			img_pix_put(&data->img, i, j++, 0x87CEEB);
// 		while (j < wall.end)
// 		{
// 			if (data->rays[i].hitvertical)
// 				img_pix_put(&data->img, i, j++, 0xFFFFAa);
// 			else
// 			img_pix_put(&data->img, i, j++, 0xFFFFe0);
// 		}
// 		while (j < W_HEIGHT)
// 			img_pix_put(&data->img, i, j++, 0x808080);
// 		i++;
// 	}
// }

void render_walls(t_data *data)
{
	int		i;
	int		j;
	t_wall	wall;
	float	proj_dist;
	int		tex_x, tex_y;
	char	*pixel;
	t_img	*texture;

	proj_dist = (W_WIDTH / 2) / tan(FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		get_wall_parameters(&wall, &data->rays[i], proj_dist);
		j = 0;
		while (j < wall.start)
			img_pix_put(&data->img, i, j++, 0x87CEEB);
		if (data->rays[i].hitvertical)
			texture = data->rays[i].rayfacingleft ? data->text_we : data->text_ea;
		else
			texture = data->rays[i].rayfacingup ? data->text_no : data->text_so;
		while (j < wall.end)
		{
			tex_x = (int)((i % texture->width) * texture->width / W_WIDTH);
			tex_y = (int)(((j - wall.start) * texture->height) / (wall.end - wall.start));
			pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
			img_pix_put(&data->img, i, j++, *(unsigned int *)pixel);
		}
		while (j < W_HEIGHT)
			img_pix_put(&data->img, i, j++, 0x808080);
		i++;
	}
}

int	render(t_data *data)
{
	if (!data->mlx_win)
		return (1);
	init_rays(data);
	move_player(data, &data->player);
	render_background(&data->img, 0x000000);
	render_walls(data);
	render_map(data);
	draw_rect(&data->img, (t_rect){
			(data->player.pos.x - 5) * SCALE_MAP,
			(data->player.pos.y - 5 ) * SCALE_MAP,
			10 * SCALE_MAP,
			10 * SCALE_MAP,
			0xFFFFFF});
	render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.mlx_img, 0, 0);
	return (0);
}