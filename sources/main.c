/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:35:26 by habernar          #+#    #+#             */
/*   Updated: 2024/11/01 20:43:33 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_values(t_data *data)
{
	data->mlx_ptr = 0;
	data->mlx_win = 0;
	data->text_no = 0;
	data->text_so = 0;
	data->text_we = 0;
	data->text_ea = 0;
	data->color_floor = -1;
	data->color_ceiling = -1;
	data->map.m = 0;
	data->map.rows = 0;
	data->map.cols = 0;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->player.delta_angle = 0;
	data->player.forward = 0;
	data->player.sideway = 0;
	data->player.angle = 0;
}

static void init_game(t_data *data)
{
	init_values(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit_error(data, MLX_PTR);
	data->mlx_win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	if (!data->mlx_win)
		exit_error(data, MLX_WIN);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!data->img.mlx_img)
		exit_error(data, MLX_IMG);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return ((void)ft_putstr_fd(ARGS, 2), 1);
	init_game(&data);
	parse_map(&data, argv[1]);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
}
