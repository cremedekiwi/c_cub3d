/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:22 by habernar          #+#    #+#             */
/*   Updated: 2024/11/21 12:54:00 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_texture(void *mlx_ptr, t_img *img)
{
	if (img)
	{
		if (img->path)
			free(img->path);
		if (img->mlx_img)
			mlx_destroy_image(mlx_ptr, img->mlx_img);
		free(img);
	}
}

static void	free_ressources(t_data *data)
{
	int	i;

	i = -1;
	if (data->mlx_ptr)
	{
		free_texture(data->mlx_ptr, data->text_no);
		free_texture(data->mlx_ptr, data->text_ea);
		free_texture(data->mlx_ptr, data->text_we);
		free_texture(data->mlx_ptr, data->text_so);
		free_texture(data->mlx_ptr, data->text_door);
		while (++i < TORCH_FRAMES)
			free_texture(data->mlx_ptr, data->torch[i]);
		if (data->img.mlx_img)
			mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->map.m)
		free_tab(data->map.m);
}

void	exit_error(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	free_ressources(data);
	exit(1);
}

void	exit_game(t_data *data)
{
	free_ressources(data);
	if (data->map.door_map)
	{
		free_door_map(data->map.door_map, data->map.rows);
		data->map.door_map = NULL;
	}
	exit(0);
}

int	handle_exit(t_data *data)
{
	exit_game(data);
	return (0);
}
