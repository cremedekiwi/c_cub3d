/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 18:05:39 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall_at(t_data *data, float x, float y)
{
	if (x < 0 || x >= data->map.cols * CUBE_SIZE || y < 0 \
	|| y >= data->map.rows * CUBE_SIZE)
		return (1);
	return (data->map.m[(int)floor(y / CUBE_SIZE)][(int)floor(x / CUBE_SIZE)] \
	== '1');
}

void	calculate_wall_height(t_wall *wall, float corrected_distance)
{
	float	proj_dist;

	proj_dist = (W_WIDTH / 2) / tan(FOV / 2);
	wall->height = (CUBE_SIZE / corrected_distance) * proj_dist;
	wall->start = (W_HEIGHT / 2) - (wall->height / 2);
	wall->end = wall->start + wall->height;
}

void	determine_texture(t_data *data, int ray_index, t_render *render_info)
{
	if (data->rays[ray_index].hitvertical)
	{
		if (data->rays[ray_index].rayfacingleft)
			render_info->texture = data->text_we;
		else
			render_info->texture = data->text_ea;
		render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.y, \
		render_info->texture->width));
	}
	else
	{
		if (data->rays[ray_index].rayfacingup)
			render_info->texture = data->text_no;
		else
			render_info->texture = data->text_so;
		render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.x, \
		render_info->texture->width));
	}
}

void	render_wall(t_data *data, int ray_index, t_render render_info)
{
	int		j;
	char	*pixel;
	int		tex_y;

	j = render_info.wall.start;
	while (j < render_info.wall.end && j < W_HEIGHT)
	{
		tex_y = (int)(((j - render_info.wall.start) * \
		render_info.texture->height) / render_info.wall.height);
		pixel = render_info.texture->addr + (tex_y * \
		render_info.texture->line_len + render_info.tex_x \
		* (render_info.texture->bpp / 8));
		img_pix_put(&data->img, ray_index, j++, *(unsigned int *)pixel);
	}
}

void	render_textures_and_colors(t_data *data)
{
	int			i;
	int			j;
	t_render	render_info;

	i = 0;
	while (i < NUM_RAYS)
	{
		calculate_wall_height(&render_info.wall, data->rays[i].distance * \
		cos(data->rays[i].angle - data->player.angle));
		j = 0;
		while (j < render_info.wall.start)
			img_pix_put(&data->img, i, j++, data->color_ceiling);
		determine_texture(data, i, &render_info);
		render_wall(data, i, render_info);
		j = render_info.wall.end;
		while (j < W_HEIGHT)
			img_pix_put(&data->img, i, j++, data->color_floor);
		i++;
	}
}
