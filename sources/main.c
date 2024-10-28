/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:35:26 by habernar          #+#    #+#             */
/*   Updated: 2024/10/27 14:38:51 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int	is_wall_at(float x, float y)
{
	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return (1);
	if (map[(int)floor(y / CUBE_SIZE)][(int)floor(x / CUBE_SIZE)])
		return (1);
	return (0);
}

void	exit_game(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->img.mlx_img)
			mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
}

void	init_player(t_data *data)
{
	data->player.pos.x = W_WIDTH / 2;
	data->player.pos.y = W_HEIGHT / 2;
	data->player.delta_angle = 0;
	data->player.forward = 0;
	data->player.sideway = 0;
	data->player.angle = 0;
}

int	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	if (!data->mlx_win)
		return (mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), 1);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	init_player(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (init_game(&data))
		return (1);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
}
