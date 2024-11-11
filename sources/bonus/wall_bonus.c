/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:20:32 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	set_vertical_texture(t_data *data, int ray_index, \
t_render *render_info, int is_door)
{
	if (is_door)
		render_info->texture = data->text_door;
	else if (data->rays[ray_index].rayfacingleft)
		render_info->texture = data->text_ea;
	else
		render_info->texture = data->text_we;
	render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.y, \
	render_info->texture->width));
}

static void	set_horizontal_texture(t_data *data, int ray_index, \
t_render *render_info, int is_door)
{
	if (is_door)
		render_info->texture = data->text_door;
	else if (data->rays[ray_index].rayfacingup)
		render_info->texture = data->text_so;
	else
		render_info->texture = data->text_no;
	render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.x, \
	render_info->texture->width));
}

void	determine_texture(t_data *data, int ray_index, t_render *render_info)
{
	float	hit_x;
	float	hit_y;
	int		map_x;
	int		map_y;
	int		is_door;

	hit_x = data->rays[ray_index].hit.x;
	hit_y = data->rays[ray_index].hit.y;
	map_x = (int)floor(hit_x / CUBE_SIZE);
	map_y = (int)floor(hit_y / CUBE_SIZE);
	is_door = is_door_hit(data, map_x, map_y);
	if (data->rays[ray_index].hitvertical)
		set_vertical_texture(data, ray_index, render_info, is_door);
	else
		set_horizontal_texture(data, ray_index, render_info, is_door);
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
