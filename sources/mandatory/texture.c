/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:25:58 by habernar          #+#    #+#             */
/*   Updated: 2024/11/07 15:48:28 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture(char *str)
{
	static const char	*tok[] = {
		"NO", "N", "SO", "S", "WE", "W",
		"EA", "E", 0
	};
	int					i;
	int					len;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (i < 8)
	{
		if (ft_strlen(str) > ft_strlen(tok[i])
			&& !ft_strncmp(tok[i], str, ft_strlen(tok[i])))
		{
			len = ft_strlen(str);
			if (!ft_strncmp(".xpm\n", str + len - 5, 5))
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

void	assign_texture(t_data *data, char *str, t_img *img)
{
	static const char	*tok[] = {
		"NO", "N", "SO", "S", "WE", "W",
		"EA", "E", 0
	};
	int					i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(tok[i], str, ft_strlen(tok[i])))
		{
			if (i < 2)
				data->text_no = img;
			else if (i < 4)
				data->text_so = img;
			else if (i < 6)
				data->text_we = img;
			else if (i < 8)
				data->text_ea = img;
			return ;
		}
		i++;
	}
}

void	create_texture(t_data *data, char *str, int fd, t_img *img)
{
	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
			img->path,
			&img->width,
			&img->height
			);
	if (!img->mlx_img)
		return (free(str), free(img->path), free(img),
			close(fd), exit_error(data, MLX_TEXT));
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bpp,
			&img->line_len,
			&img->endian
			);
	assign_texture(data, str, img);
}

void	get_texture(t_data *data, char *str, int fd)
{
	t_img	*img;
	size_t	len;
	char	*head;

	head = str;
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (free(str), close(fd), exit_error(data, MALLOC));
	while (ft_isalpha(*str))
		str++;
	while (*str == ' ' || *str == '\t')
		str++;
	img->path = ft_strdup(str);
	if (!img->path)
		return (free(head), close(fd), exit_error(data, MALLOC));
	len = ft_strlen(img->path);
	if (len > 0)
		img->path[ft_strlen(img->path) - 1] = 0;
	create_texture(data, head, fd, img);
}
