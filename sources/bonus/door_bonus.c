/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:20:30 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/20 16:54:12 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_door_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->door_map = malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		map->door_map[i] = malloc(sizeof(char) * map->cols);
		j = 0;
		while (j < map->cols)
		{
			if (map->m[i][j] == 'D')
				map->door_map[i][j] = 'D';
			else
				map->door_map[i][j] = '0';
			j++;
		}
		i++;
	}
}

static void	toggle_door_state(t_map *map, int x, int y)
{
	if (map->m[y][x] == 'D')
		map->m[y][x] = '0';
	else if (map->m[y][x] == '0')
		map->m[y][x] = 'D';
}

static int	is_player_in_front_of_door(t_player *player, int nx, int ny)
{
	double	door_center_x;
	double	door_center_y;
	double	distance;

	door_center_x = nx * CUBE_SIZE + (CUBE_SIZE / 2);
	door_center_y = ny * CUBE_SIZE + (CUBE_SIZE / 2);
	distance = sqrt(pow(player->pos.x - door_center_x, 2) \
	+ pow(player->pos.y - door_center_y, 2));
	if (distance > (CUBE_SIZE / 2) && distance < (CUBE_SIZE * 1.5))
		return (1);
	return (0);
}

void	toggle_door(t_map *map, t_player *player)
{
	int	dx;
	int	dy;
	int	nx;
	int	ny;

	dx = -1;
	dy = -1;
	while (dy <= 1)
	{
		nx = floor(player->pos.x / CUBE_SIZE) + dx;
		ny = floor(player->pos.y / CUBE_SIZE) + dy;
		if (nx >= 0 && nx < map->cols && ny >= 0 && ny < map->rows)
		{
			if (map->door_map[ny][nx] == 'D' && \
			is_player_in_front_of_door(player, nx, ny))
				return (toggle_door_state(map, nx, ny), (void)0);
		}
		dx++;
		if (dx > 1)
		{
			dx = -1;
			dy++;
		}
	}
}
