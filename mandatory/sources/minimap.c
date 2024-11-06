/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:01:12 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 17:17:31 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_minimap(t_data *data, t_minimap *minimap)
{
	minimap->radius = 20;
	minimap->size = (minimap->radius * 2 + 1) * CUBE_SIZE * SCALE_MAP;
	minimap->center = (t_vec2){minimap->size / 2, minimap->size / 2};
	minimap->player.x = data->player.pos.x / CUBE_SIZE;
	minimap->player.y = data->player.pos.y / CUBE_SIZE;
}

bool	is_in_minimap(t_minimap *minimap, t_vec2 v)
{
	return (v.x >= 0 && v.x < minimap->size && v.y >= 0 && v.y < minimap->size);
}

void	draw_minimap_wall(t_data *data, t_minimap *minimap)
{
	t_vec2	map;
	t_vec2	screen;
	t_vec2	curr;

	curr.y = -minimap->radius - 1;
	while (++curr.y <= minimap->radius)
	{
		curr.x = -minimap->radius - 1;
		while (++curr.x <= minimap->radius)
		{
			map = vec2_add(minimap->player, curr);
			if (map.x >= 0 && map.x < data->map.cols
				&& map.y >= 0 && map.y < data->map.rows)
			{
				screen = vec2_add(minimap->center,
						vec2_scale(curr, CUBE_SIZE * SCALE_MAP));
				if (is_in_minimap(minimap, screen)
					&& data->map.m[(int)map.y][(int)map.x] == '1')
				{
					draw_rect(&data->img, (t_rect){screen.x, screen.y,
						CUBE_SIZE * SCALE_MAP, CUBE_SIZE * SCALE_MAP,
						0x515250});
				}
			}
		}
	}
}

void	draw_player_and_rays(t_data *data, t_minimap *minimap)
{
    draw_rect(&data->img, (t_rect){
		minimap->center.x,
        minimap->center.y,
        10 * SCALE_MAP,
        10 * SCALE_MAP,
        0xFFFFFFFF
    });

}
void	render_rays(t_data *data)
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
