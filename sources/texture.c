/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:25:58 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 16:28:01 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_texture(char *str)
{
	if (!ft_strncmp(str, "NO ", 3)
		|| !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3)
		|| !ft_strncmp(str, "EA ", 3))
		return (1);
	return (0);
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
	if (!ft_strncmp(str, "NO", 2))
		data->text_no = img;
	if (!ft_strncmp(str, "SO", 2))
		data->text_so = img;
	if (!ft_strncmp(str, "WE", 2))
		data->text_we = img;
	if (!ft_strncmp(str, "EA", 2))
		data->text_ea = img;
}

void	get_texture(t_data *data, char *str, int fd)
{
	t_img	*img;
	size_t	len;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (free(str), close(fd), exit_error(data, MALLOC));
	img->path = ft_strdup(ft_strchr(str, '.'));
	if (!img->path)
		return (free(str), close(fd), exit_error(data, MALLOC));
	len = ft_strlen(img->path);
	if (len > 0)
		img->path[ft_strlen(img->path) - 1] = 0;
	create_texture(data, str, fd, img);
}
