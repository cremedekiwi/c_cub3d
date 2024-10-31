/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:01 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 23:35:07 by jarumuga         ###   ########.fr       */
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
			img_pix_put(img, j++, i, color);
		i++;
	}
}

static void	render_map(t_data *data)
{
	int	i;
	int	j;

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
					0xFFFFFF});
			j++;
		}
		i++;
	}
}

static void	render_rays(t_data *data)
{
	int		i;
	t_vec2	scale1;
	t_vec2	scale2;

	i = 0;
	while (i < NUM_RAYS)
	{
		scale1 = vec2_scale(data->player.pos, SCALE_MAP);
		scale2 = vec2_scale(data->rays[i].hit, SCALE_MAP);
		draw_line(data, scale1.x, scale1.y, scale2.x, scale2.y);
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

int	render(t_data *data)
{
	if (!data->mlx_win)
		return (1);
	init_rays(data);
	move_player(data, &data->player);
	render_background(&data->img, 0x000000);
	render_textures_and_colors(data);
	render_map(data);
	draw_rect(&data->img, (t_rect){(data->player.pos.x - 5) * SCALE_MAP, \
		(data->player.pos.y - 5) * SCALE_MAP, \
		10 * SCALE_MAP, \
		10 * SCALE_MAP, \
		0xFFFFFF});
	render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
	data->img.mlx_img, 0, 0);
	return (0);
}
