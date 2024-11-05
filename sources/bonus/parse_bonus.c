/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:06:18 by habernar          #+#    #+#             */
/*   Updated: 2024/11/05 14:18:35 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	get_color(t_data *data, char *str, char c, int fd)
{
	int		r;
	int		g;
	int		b;
	char	*head;

	head = str++;
	r = ft_atoi(str);
	str = ft_strchr(str, ',');
	if (!str)
		return (free(head), close(fd), exit_error(data, MAP_ARGS));
	g = ft_atoi(++str);
	str = ft_strchr(str, ',');
	if (!str)
		return (free(head), close(fd), exit_error(data, MAP_ARGS));
	b = ft_atoi(++str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free(head), close(fd), exit_error(data, COLOR));
	if (c == 'C')
		data->color_ceiling = (r << 16) | (g << 8) | b;
	else if (c == 'F')
		data->color_floor = (r << 16) | (g << 8) | b;
}

int	is_last_argument(t_data *data)
{
	if (data->color_floor != INT_MIN && data->color_ceiling != INT_MIN
		&& data->text_no && data->text_so && data->text_ea
		&& data->text_we)
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

void	parse_map(t_data *data, char *str)
{
	int		fd;
	char	*line;

	check_extension(data, str);
	fd = open(str, O_RDONLY);
	if (fd <= 0)
		exit_error(data, FD);
	line = get_next_line(fd);
	if (!line)
		exit_error(data, EMPTY_FILE);
	while (line)
	{
		if (is_texture(line))
			get_texture(data, line, fd);
		else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			get_color(data, line, line[0], fd);
		else if (is_map(line) && is_last_argument(data))
			return (get_map(data, line, fd));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!(data->color_floor != INT_MIN && data->color_ceiling != INT_MIN
		&& data->text_no && data->text_so && data->text_ea
		&& data->text_we && data->map.m))
		exit_error(data, MAP_ARGS);

}
