/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:00:58 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/12 22:40:32 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief assembles a str in the following format: ./textures/torch_<num>.xpm
 * @brief 1. copy the prefix
 * @brief 2. add the numeric part
 * @brief 3. copy the suffix
 * @brief 4. null terminator
 * @param buffer character array where the formatted string will be stored
 * @param size maximum size of buffer, preventing overflow
 * @param format define the format of the output
 * @param num integer that will be appended as part of the filename
 * @return len, which represents the number of characters written to buffer
 */
int	ft_snprintf(char *buffer, int size, int num)
{
	int			len;
	const char	*prefix;
	const char	*suffix;

	len = 0;
	prefix = "./textures/torch_";
	suffix = ".xpm";
	while (*prefix && len < size - 1)
		buffer[len++] = *prefix++;
	if (len < size - 1)
		buffer[len++] = '0' + (num / 10);
	if (len < size - 1)
		buffer[len++] = '0' + (num % 10);
	while (*suffix && len < size - 1)
		buffer[len++] = *suffix++;
	buffer[len] = '\0';
	return (len);
}

/**
 * @brief loads a series of torch texture
 * @brief 1. loop through frames
 * @brief 2. generate filename
 * @brief 3. allocate memory for each texture
 * @brief 4. load image file
 * @brief 5. retrieve image data
 * @brief 6. init animation frame counters
 * @param data pointer to a structure
 */
void	load_torch_texture(t_data *data)
{
	char	filename[30];
	int		i;

	i = -1;
	while (++i < TORCH_FRAMES)
	{
		ft_snprintf(filename, sizeof(filename), i);
		data->torch[i] = malloc(sizeof(t_img));
		if (!data->torch[i])
			exit_error(data, "Malloc failed.\n");
		data->torch[i]->path = NULL;
		data->torch[i]->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
		filename, &data->torch[i]->width, &data->torch[i]->height);
		if (!data->torch[i]->mlx_img)
		{
			printf("Error loading torch texture frame %d.\n", i);
			exit_error(data, "Failed to load torch texture.\n");
		}
		data->torch[i]->addr = mlx_get_data_addr(data->torch[i]->mlx_img, \
		&data->torch[i]->bpp, &data->torch[i]->line_len, \
		&data->torch[i]->endian);
	}
	data->current_frame = 0;
	data->frame_counter = 0;
}

/**
 * @brief draw a scaled-up version of a pixel in an image
 * @brief 1. outer loop (rows)
 * @brief 2. inner loop (columns)
 * @brief 3. draw each pixel in the block
 * @param img pointer to an image structure
 * @param info structure containing details needed to draw the scaled pixel
 */
void	draw_scaled_pixel(t_img *img, t_torch_info info)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)info.scale)
	{
		j = 0;
		while (j < (int)info.scale)
		{
			img_pix_put(img, info.scaled_x + j, info.scaled_y + i, info.color);
			j++;
		}
		i++;
	}
}

/**
 * @brief designed to draw a scaled-up version of a torch
 * @brief 1. loop through texture pixels
 * @brief 2. retrieve the pixel color
 * @brief 3. transparency check
 * @brief 4. set scaled pixel properties
 * @brief 5. draw the scaled pixel
 * @param img pointer to an image structure
 * @param current_torch pointer to the current torch texture image
 * @param info structure containing details needed to draw the scaled pixel
 */
void	draw_torch_texture(t_img *img, t_img *current_torch, t_torch_info *info)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < current_torch->height)
	{
		x = 0;
		while (x < current_torch->width)
		{
			color = *(int *)(current_torch->addr + \
			(y * current_torch->line_len + x * (current_torch->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
			{
				info->color = color;
				info->scaled_x = info->screen_x + (int)(x * info->scale);
				info->scaled_y = info->screen_y + (int)(y * info->scale);
				draw_scaled_pixel(img, *info);
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief responsible for updating the animation frame of a "torch" texture
 * @brief 1. fram delay config
 * @brief 2. frame counter update
 * @brief 3. select the current frame
 * @brief 4. error checking
 * @brief 5. set drawing info
 * @brief 6. draw the torch texture
 * @param data pointer to a structure
 * @param screen_x x-coordinate on the screen where the torch should be drawn
 * @param screen_y y--coordinate on the screen where the torch should be drawn
 * @param scale scale factor used to draw the torch texture (large or small)
 */
void	update_and_draw_torch(t_data *data, int screen_x, \
int screen_y, float scale)
{
	int				delay_interval;
	t_img			*current_torch;
	t_torch_info	info;

	delay_interval = 15;
	data->frame_counter++;
	if (data->frame_counter >= delay_interval)
	{
		data->current_frame = (data->current_frame + 1) % TORCH_FRAMES;
		data->frame_counter = 0;
	}
	current_torch = data->torch[data->current_frame];
	if (!current_torch || !current_torch->addr)
	{
		printf("Error: Torch texture not loaded properly.\n");
		return ;
	}
	info.screen_x = screen_x;
	info.screen_y = screen_y;
	info.scale = scale;
	draw_torch_texture(&data->img, current_torch, &info);
}
