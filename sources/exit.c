/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:22 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:12 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void free_textures(t_data *data)
{
	if (data->text_no && data->text_no->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->text_no->mlx_img);
		free(data->text_no->path);
		free(data->text_no);
	}
	if (data->text_so && data->text_so->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->text_so->mlx_img);
		free(data->text_so->path);
		free(data->text_so);
	}
	if (data->text_we && data->text_we->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->text_we->mlx_img);
		free(data->text_we->path);
		free(data->text_we);
	}
	if (data->text_ea && data->text_ea->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->text_ea->mlx_img);
		free(data->text_ea->path);
		free(data->text_ea);
	}
}

static void	free_ressources(t_data *data)
{
	if (data->mlx_ptr)
	{
		free_textures(data);
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
