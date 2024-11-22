/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:01 by habernar          #+#    #+#             */
/*   Updated: 2024/11/21 18:24:34 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	invalid_char(char c)
{
	if (c == ' ' || c == '\n' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_empty_line(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	get_map_dimension(t_data *data, char **tab)
{
	int	i;
	int	max_length;
	int	curr_length;

	i = 0;
	curr_length = -1;
	max_length = INT_MIN;
	while (tab && tab[i])
	{
		curr_length = ft_strlen(tab[i]);
		if (curr_length > max_length)
			max_length = curr_length;
		i++;
	}
	data->map.rows = i;
	if (tab[i] && curr_length >= 0 && tab[i][curr_length] == '\n')
		data->map.cols = max_length - 1;
	else
		data->map.cols = max_length;
}
