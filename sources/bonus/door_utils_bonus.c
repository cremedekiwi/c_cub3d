/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:52 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/20 16:50:18 by jarumuga         ###   ########.fr       */
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
