/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/11/12 18:05:50 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	determine_texture(t_data *data, int ray_index, t_render *render_info)
{
	if (data->rays[ray_index].hitvertical)
	{
		if (data->rays[ray_index].door)
			render_info->texture = data->text_door;
		else if (data->rays[ray_index].rayfacingleft)
			render_info->texture = data->text_ea;
		else
			render_info->texture = data->text_we;
		render_info->tex_x = (int)(fmod(data->rays[ray_index].hit.y, \
		render_info->texture->width));
	}
	else
	{
		if (data->rays[ray_index].door)
			render_info->texture = data->text_door;
		else if (data->rays[ray_index].rayfacingup)
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
