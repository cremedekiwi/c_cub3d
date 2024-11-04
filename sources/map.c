/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:11:12 by habernar          #+#    #+#             */
/*   Updated: 2024/11/04 17:02:27 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map(char *str)
{
	int	count1;
	int	count0;

	count0 = 0;
	count1 = 0;
	while (*str)
	{
		if (!(*str == '1' || *str == '0' || *str == ' ' || *str == '\n'))
			return (0);
		if (*str == '1')
			count1++;
		if (*str == '0')
			count0++;
		str++;
	}
	return (count1 || count0);
}

void	get_map_dimension(t_data *data, char **tab)
{
	int	i;
	int	max_length;
	int	curr_length;

	i = 0;
	max_length = INT_MIN;
	while (tab && tab[i])
	{
		curr_length = ft_strlen(tab[i]);
		if (curr_length > max_length)
			max_length = curr_length;
		i++;
	}
	data->map.rows = i;
	data->map.cols = max_length - 1;
}

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

void	remove_cardinal(t_data *data)
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

int	flood_fill(t_data *data, char **m, int i, int j)
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

void	is_map_open(t_data *data)
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

int invalid_char(char c)
{
	if (c == ' ' || c == '\n' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0);
	return (1);
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
	i = 0;
	while (data->map.m && data->map.m[i])
	{
		printf("%s\n", data->map.m[i]);
		i++;
	}
}

void	get_map(t_data *data, char *str, int fd)
{
	char	**tab;

	tab = 0;
	while (str)
	{
		tab = tab_append(tab, str);
		if (!tab)
			return (free(str), close(fd), exit_game(data));
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	get_map_dimension(data, tab);
	copy_tab(data, tab);
	get_player_position(data);
	verify_arguments(data);
}
