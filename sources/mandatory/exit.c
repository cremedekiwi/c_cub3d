/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:22 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:27:16 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture(void *mlx_ptr, t_img *img)
{
	if (img)
	{
		if (img->path)
			free(img->path);
		mlx_destroy_image(mlx_ptr, img->mlx_img);
		free(img);
	}
}

static void	free_ressources(t_data *data)
{
	if (data->mlx_ptr)
	{
		free_texture(data->mlx_ptr, data->text_no);
		free_texture(data->mlx_ptr, data->text_ea);
		free_texture(data->mlx_ptr, data->text_we);
		free_texture(data->mlx_ptr, data->text_so);
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
	exit(0);
}
