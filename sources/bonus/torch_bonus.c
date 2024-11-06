/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:00:58 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/06 16:30:06 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_snprintf(char *buffer, size_t size, const char *format, int num)
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

void	load_torch_texture(t_data *data)
{
	char	filename[30];
	int		i;

	i = -1;
	while (++i < TORCH_FRAMES)
	{
		ft_snprintf(filename, sizeof(filename), "./textures/torch_%02d.xpm", i);
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
