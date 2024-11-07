/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:01:12 by habernar          #+#    #+#             */
/*   Updated: 2024/11/07 16:16:28 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_minimap(t_data *data, t_minimap *minimap)
{
	minimap->radius = 20;
	//minimap->pos = (t_vec2){}
	minimap->size = (minimap->radius * 2 + 1) * CUBE_SIZE * SCALE_MAP;
	minimap->center = (t_vec2){minimap->size / 2, minimap->size / 2};
	minimap->player.x = data->player.pos.x / CUBE_SIZE;
	minimap->player.y = data->player.pos.y / CUBE_SIZE;
}

bool	is_wall_minimap(t_data *data, t_minimap *minimap, t_vec2 sc, t_vec2 map)
{
	return (sc.x >= 0 && sc.x < minimap->size
		&& sc.y >= 0 && sc.y < minimap->size
		&& data->map.m[(int)map.y][(int)map.x] == '0');
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
				if (is_wall_minimap(data, minimap, screen, map))
				{
					draw_rect(&data->img, (t_rect){screen.x, screen.y,
						CUBE_SIZE * SCALE_MAP, CUBE_SIZE * SCALE_MAP,
						0x515250});
				}
			}
		}
	}
}

static void	render_rays(t_data *data, t_minimap *minimap)
{
	int		i;
	float	distance;
	t_vec2	hit;
	t_vec2	dist;

	i = -1;
	while (++i < NUM_RAYS)
	{
		hit.x = minimap->center.x + (data->rays[i].hit.x
				- data->player.pos.x + CUBE_SIZE / 2) * SCALE_MAP;
		hit.y = minimap->center.y + (data->rays[i].hit.y
				- data->player.pos.y + CUBE_SIZE / 2) * SCALE_MAP;
		dist.x = hit.x - minimap->center.x;
		dist.y = hit.y - minimap->center.y;
		distance = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (distance > 0 && distance > minimap->radius * CUBE_SIZE * SCALE_MAP)
		{
			hit.x = minimap->center.x
				+ dist.x * (minimap->radius * CUBE_SIZE * SCALE_MAP) / distance;
			hit.y = minimap->center.y
				+ dist.y * (minimap->radius * CUBE_SIZE * SCALE_MAP) / distance;
		}
		draw_line(data, minimap->center, hit);
	}
}

void	draw_player_and_rays(t_data *data, t_minimap *minimap)
{
	render_rays(data, minimap);
	draw_rect(&data->img, (t_rect){
		minimap->center.x,
		minimap->center.y,
		CUBE_SIZE / 2 * SCALE_MAP,
		CUBE_SIZE / 2 * SCALE_MAP,
		0xFFFFFFFF
	});
}
