/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:21:39 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	is_wall_at(t_data *data, float x, float y)
{
	int	idx;
	int	idy;

	if (x < 0 || x >= data->map.cols * CUBE_SIZE
		|| y < 0 || y >= data->map.rows * CUBE_SIZE)
		return (1);
	idy = floor(y / CUBE_SIZE);
	idx = floor(x / CUBE_SIZE);
	return (data->map.m[idy][idx] == '1' || data->map.m[idy][idx] == 'D');
}

int	is_door_hit(t_data *data, int map_x, int map_y)
{
	return ((data->map.m[map_y - 1][map_x] == 'D') ||
			(data->map.m[map_y][map_x - 1] == 'D') ||
			(data->map.m[map_y][map_x] == 'D'));
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
