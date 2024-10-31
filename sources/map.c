/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:11:12 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 20:53:39 by habernar         ###   ########.fr       */
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
				data->player.pos.x = j * CUBE_SIZE;
				data->player.pos.y = i * CUBE_SIZE;
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

void remove_cardinal(t_data *data)
{
	int	i;
	int	j;
	int c;

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

void	is_map_open(t_data *data)
{

}

void	verify_arguments(t_data *data)
{
	int i;
	int j;
	bool	whitespace;

	i = 0;
	is_map_open(data);
	whitespace = 1;
	while (data->map.m && data->map.m[i])
	{
		j = 0;
		while (data->map.m[i][j])
		{
			if (data->map.m[i][j] != ' ')
				whitespace = 0;
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
		/*
		j = 0;
		while (data->map.m[i][j])
		{
			j++;
		}
		*/
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
	get_map_dimension(data, tab);
	copy_tab(data, tab, fd);
	get_player_position(data);
	verify_arguments(data);
}
