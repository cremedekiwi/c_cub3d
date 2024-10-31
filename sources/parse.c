/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:06:18 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 17:31:56 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_color(t_data *data, char *str, char c, int fd)
{
	int		r;
	int		g;
	int		b;
	char	*head;

	head = str++;
	r = ft_atoi(str);
	str = ft_strchr(str, ',');
	g = ft_atoi(++str);
	str = ft_strchr(str, ',');
	b = ft_atoi(++str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free(head), close(fd), exit_error(data, COLOR));
	if (c == 'C')
		data->color_ceiling = (r << 16) | (g << 8) | b;
	else
		data->color_floor = (r << 16) | (g << 8) | b;
}

int	is_last_argument(t_data *data)
{
	if (data->color_floor != -1 && data->color_ceiling != -1
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
	while (line)
	{
		if (is_texture(line))
			get_texture(data, line, fd);
		else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			get_color(data, line, line[0], fd);
		else if (is_last_argument(data) && is_map(line))
		{
			get_map(data, line, fd);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
