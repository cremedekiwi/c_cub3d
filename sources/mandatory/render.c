/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:01 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 20:42:41 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
			img_pix_put(img, j++, i, color);
		i++;
	}
}

static void	render_textures_and_colors(t_data *data)
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

static void	draw_minimap(t_data *data)
{
	t_minimap	minimap;

	init_minimap(data, &minimap);
	draw_rect(&data->img, (t_rect){0, 0, minimap.size, minimap.size, 0x000000});
	draw_minimap_wall(data, &minimap);
	draw_player_and_rays(data, &minimap);
}

int	render(t_data *data)
{
	if (!data->mlx_win)
		return (1);
	init_rays(data);
	move_player(data, &data->player);
	render_background(&data->img, 0x000000);
	render_textures_and_colors(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.mlx_img, 0, 0);
	return (0);
}
