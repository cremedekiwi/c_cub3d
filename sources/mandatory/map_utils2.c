/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:26:18 by habernar          #+#    #+#             */
/*   Updated: 2024/11/21 18:23:09 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_open(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || i == data->map.rows - 1 || j == data->map.cols - 1)
		exit_error(data, MAP);
	if (found_wall_vertical(data, i, j, 1)
		+ found_wall_vertical(data, i, j, 0)
		+ found_wall_horizontal(data, i, j, 1)
		+ found_wall_horizontal(data, i, j, 0) != 4)
	{
		exit_error(data, MAP);
	}
}

int	contains_digits(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			return (1);
		str++;
	}
	return (0);
}

void	check_args(t_data *data)
{
	if (!data->text_ea && !data->text_no && !data->text_so
		&& !data->text_we
		&& data->color_floor == INT_MIN
		&& data->color_ceiling == INT_MIN && !data->map.m)
		exit_error(data, EMPTY_FILE);
	if (!data->text_ea || !data->text_no || !data->text_so
		|| !data->text_we)
		exit_error(data, TEXT);
}
