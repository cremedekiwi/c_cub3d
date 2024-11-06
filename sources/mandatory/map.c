/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:11:12 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 19:59:43 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.m[++i])
	{
		j = -1;
		while (data->map.m[i][++j])
		{
			if (data->map.m[i][j] == 'N' || data->map.m[i][j] == 'S'
				|| data->map.m[i][j] == 'W' || data->map.m[i][j] == 'E')
			{
				data->player.pos.x = j * CUBE_SIZE + (float)CUBE_SIZE / 2;
				data->player.pos.y = i * CUBE_SIZE + (float)CUBE_SIZE / 2;
			}
			if (data->map.m[i][j] == 'N')
				data->player.angle = -PI / 2;
			else if (data->map.m[i][j] == 'S')
				data->player.angle = PI / 2;
			else if (data->map.m[i][j] == 'W')
				data->player.angle = PI;
			else if (data->map.m[i][j] == 'E')
				data->player.angle = 0;
		}
	}
}

static void	remove_cardinal(t_data *data)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	c = 0;
	while (data->map.m[++i])
	{
		j = -1;
		while (data->map.m[i][++j])
		{
			if (data->map.m[i][j] == 'N' || data->map.m[i][j] == 'S'
				|| data->map.m[i][j] == 'W' || data->map.m[i][j] == 'E')
			{
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

static int	flood_fill(t_data *data, char **m, int i, int j)
{
	if (i < 0 || j < 0 || j == data->map.cols || i == data->map.rows)
		return (false);
	else if ((i == 0 || i == data->map.rows - 1
			|| j == 0 || j == data->map.cols - 1)
		&& (m[i][j] == '0' || m[i][j] == ' '))
		return (true);
	else if (m[i][j] == '1')
		return (false);
	m[i][j] = '1';
	return (flood_fill(data, m, i + 1, j)
		|| flood_fill(data, m, i - 1, j)
		|| flood_fill(data, m, i, j + 1)
		|| flood_fill(data, m, i, j - 1));
}

static void	is_map_open(t_data *data)
{
	int		i;
	int		j;
	char	**m;

	m = (char **)malloc(sizeof(char *) * (data->map.rows + 1));
	if (!m)
		exit_error(data, MALLOC);
	i = -1;
	while (data->map.m[++i])
		m[i] = ft_strdup(data->map.m[i]);
	m[i] = 0;
	i = -1;
	while (++i < data->map.rows)
	{
		j = -1;
		while (++j < data->map.cols)
		{
			if (m[i][j] == '0' && flood_fill(data, m, i, j))
				return (free_tab(m), exit_error(data, MAP), (void)0);
		}
	}
	free_tab(m);
}

void	verify_arguments(t_data *data)
{
	int		i;
	int		j;
	bool	whitespace;

	i = 0;
	whitespace = 1;
	is_map_open(data);
	while (data->map.m && data->map.m[i])
	{
		j = 0;
		while (data->map.m[i][j])
		{
			if (data->map.m[i][j] != ' ')
				whitespace = 0;
			if (invalid_char(data->map.m[i][j]))
				exit_error(data, MAP_CHAR);
			j++;
		}
		if (whitespace == 1)
			exit_error(data, EMPTY_LINE);
		whitespace = 1;
		i++;
	}
	remove_cardinal(data);
}
