/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:27:03 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_at(t_data *data, float x, float y)
{
	int	idx;
	int	idy;

	if (x < 0 || x >= data->map.cols * CUBE_SIZE
		|| y < 0 || y >= data->map.rows * CUBE_SIZE)
		return (1);
	idy = floor(y / CUBE_SIZE);
	idx = floor(x / CUBE_SIZE);
	return (data->map.m[idy][idx] == '1');
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
			render_info->texture = data->text_ea;
		else
			render_info->texture = data->text_we;
		render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.y, \
		render_info->texture->width));
	}
	else
	{
		if (data->rays[ray_index].rayfacingup)
			render_info->texture = data->text_so;
		else
			render_info->texture = data->text_no;
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
