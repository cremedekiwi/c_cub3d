/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:06:18 by habernar          #+#    #+#             */
/*   Updated: 2024/11/21 18:48:30 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_color(t_data *data, char *str, char x, int fd)
{
	char	**tab;
	int		i;
	int		c[3];

	tab = ft_split(str + 1, ',');
	if (!tab)
		return (free_tab(tab), free(str), exit_error(data, COLOR));
	i = 0;
	while (tab[i] && contains_digits(tab[i]))
		i++;
	if (i != 3)
		return (free_tab(tab), free(str), close(fd), exit_error(data, COLOR));
	c[0] = ft_atoi(tab[0]);
	c[1] = ft_atoi(tab[1]);
	c[2] = ft_atoi(tab[2]);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0
		|| c[1] > 255 || c[2] < 0 || c[2] > 255)
		return (free_tab(tab), close(fd), free(str), exit_error(data, COLOR));
	if (x == 'C')
		data->color_ceiling = (c[0] << 16) | (c[1] << 8) | c[2];
	else if (x == 'F')
		data->color_floor = (c[0] << 16) | (c[1] << 8) | c[2];
	free_tab(tab);
}

int	is_last_argument(t_data *data)
{
	if (data->color_floor != INT_MIN && data->color_ceiling != INT_MIN
		&& data->text_no && data->text_so && data->text_ea
		&& data->text_we && data->text_door)
		return (1);
	return (0);
}

void	check_extension(t_data *data, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		exit_error(data, FILEFORMAT);
	if (ft_strncmp(".cub", str + len - 4, 4))
		exit_error(data, FILEFORMAT);
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
	if (str)
		free(str);
	close(fd);
	get_map_dimension(data, tab);
	copy_tab(data, tab);
	get_player_position(data);
	check_doors(data);
	verify_arguments(data);
}

void	parse_map(t_data *data, char *str)
{
	int		fd;
	char	*l;

	check_extension(data, str);
	fd = open(str, O_RDONLY);
	if (fd <= 0)
		exit_error(data, FD);
	l = get_next_line(fd);
	if (!l)
		exit_error(data, EMPTY_FILE);
	while (l)
	{
		if (is_texture(l))
			get_texture(data, l, fd);
		else if (l[0] && l[1] && (l[0] == 'F' || l[0] == 'C') && l[1] == ' ')
			get_color(data, l, l[0], fd);
		else if (is_last_argument(data) && !is_empty_line(l))
			return (get_map(data, l, fd));
		else if (!is_empty_line(l))
			return (free(l), close(fd), exit_error(data, MAP_ARGS));
		free(l);
		l = get_next_line(fd);
	}
	close(fd);
	verify_arguments(data);
}
