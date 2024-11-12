/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:20:30 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/12 22:05:31 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_doors(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.rows)
	{
		j = -1;
		while (++j < data->map.cols)
		{
			if (data->map.m[i][j] == 'D' &&
				((i == 0 || j == 0 || i == data->map.rows - 1 \
				|| j == data->map.cols - 1) \
				|| !((data->map.m[i][j - 1] == '1' \
				&& data->map.m[i][j + 1] == '1') \
				|| (data->map.m[i - 1][j] == '1' \
				&& data->map.m[i + 1][j] == '1'))))
				exit_error(data, DOOR_LOCATION);
		}
	}
}

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

void	free_door_map(char **door_map, int rows)
{
	int	i;

	if (door_map)
	{
		i = 0;
		while (i < rows)
		{
			free(door_map[i]);
			i++;
		}
		free(door_map);
	}
}

static void	toggle_door_state(t_map *map, int x, int y)
{
	if (map->m[y][x] == 'D')
		map->m[y][x] = '0';
	else if (map->m[y][x] == '0')
		map->m[y][x] = 'D';
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
			if (map->door_map[ny][nx] == 'D')
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
