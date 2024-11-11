/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:25:58 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 17:52:17 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief checks if a given string str is a valid texture identifier
 * @brief 1. loop through tokens
 * @brief 2. string comparison (length check ; prefix match)
 * @param str represents the string being evaluated
 * @return boolean
 */
int	is_texture(char *str)
{
	static const char	*tok[] = {
		"NO", "N", "SO", "S", "WE", "W",
		"EA", "E", "DO", "D", 0
	};
	int					i;
	int					len;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (i < 10)
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

/**
 * @brief assigns a given texture image
 * @brief 1. loop through texture identifiers
 * @brief 2. check for prefix match
 * @brief 3. assign the texture
 * @param data pointer to a structure
 * @param str string that indicates the direction of the texture
 * @param img pointer to an image structure
 */
void	assign_texture(t_data *data, char *str, t_img *img)
{
	static const char	*tok[] = {
		"NO", "N", "SO", "S", "WE", "W",
		"EA", "E", "DO", "D", 0
	};
	int					i;

	i = 0;
	while (i < 10)
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
			else
				data->text_door = img;
			return ;
		}
		i++;
	}
}

/**
 * @brief initializes and assigns a texture image
 * @brief 1. load the texture image
 * @brief 2. error handling
 * @brief 3. get image data address
 * @brief 4. assign the texture
 * @param data pointer to a structure
 * @param str string that indicates the direction of the texture
 * @param fd fd associated with a file being read
 * @param img pointer to an image structure
 */
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

/**
 * @brief responsible for extracting a texture file path from a given string
 * @brief 1. initialize and allocate t_img structure
 * @brief 2. error handling for malloc
 * @brief 3. extract the file path from str
 * @brief 4. duplicate the file path into img->path
 * @param data pointer to a structure
 * @param str string that indicates the direction of the texture
 * @param fd fd associated with a file being read
 * @param img pointer to an image structure
 */
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
