/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:26:18 by habernar          #+#    #+#             */
/*   Updated: 2024/11/20 21:06:06 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	found_wall_vertical(t_data *data, int i, int j, bool start)
{
	int	x;
	int	end;

	x = i;
	end = data->map.rows;
	if (start)
	{
		x = -1;
		end = i;
	}
	while (++x < end)
	{
		if (data->map.m[x][j] == '1')
			return (1);
	}
	return (0);
}

static int	found_wall_horizontal(t_data *data, int i, int j, bool start)
{
	int	x;
	int	end;

	x = j;
	end = data->map.cols;
	if (start)
	{
		x = -1;
		end = j;
	}
	while (++x < end)
	{
		if (data->map.m[i][x] == '1')
			return (1);
	}
	return (0);
}

static void	surrounded_by_wall(t_data *data, int i, int j)
{
	if (found_wall_vertical(data, i, j, 1)
		+ found_wall_vertical(data, i, j, 0)
		+ found_wall_horizontal(data, i, j, 1)
		+ found_wall_horizontal(data, i, j, 0) != 4)
	{
		exit_error(data, MAP);
	}
}

void	remove_cardinal(t_data *data)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	c = 0;
	while (++i < data->map.rows)
	{
		j = -1;
		while (data->map.m[i][++j])
		{
			if (data->map.m[i][j] == 'N' || data->map.m[i][j] == 'S'
				|| data->map.m[i][j] == 'W' || data->map.m[i][j] == 'E')
			{
				surrounded_by_wall(data, i, j);
				data->map.m[i][j] = '0';
				c++;
			}
			else if (data->map.m[i][j] == ' ')
				data->map.m[i][j] = '1';
		}
	}
	if (c != 1)
		exit_error(data, CARDINAL);
}
