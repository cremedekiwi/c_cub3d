/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:02 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:30:49 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	valid_move(t_data *data, t_vec2 newpos)
{
	float	delta;

	delta = -(float)CUBE_SIZE / 4;
	if (data->player.pos.y < newpos.y)
		delta *= -1;
	if (!is_wall_at(data, data->player.pos.x, newpos.y + delta))
		data->player.pos.y = newpos.y;
	delta = -(float)CUBE_SIZE / 4;
	if (data->player.pos.x < newpos.x)
		delta *= -1;
	if (!is_wall_at(data, newpos.x + delta, data->player.pos.y))
		data->player.pos.x = newpos.x;
}

void	move_player(t_data *data, t_player *player)
{
	t_vec2	newpos;
	float	delta;

	newpos = player->pos;
	if (player->delta_angle != 0)
		player->angle += player->delta_angle * ANGULAR_VELOCITY;
	if (player->forward != 0)
	{
		newpos.x += cos(player->angle) * player->forward * VELOCITY;
		newpos.y += sin(player->angle) * player->forward * VELOCITY;
	}
	else if (player->sideway != 0)
	{
		newpos.x += cos(player->angle + player->sideway * PI / 2) * VELOCITY;
		newpos.y += sin(player->angle + player->sideway * PI / 2) * VELOCITY;
	}
	valid_move(data, newpos);
}

// recenter the mouse only when it moves too far within the window
	// x < W_WIDTH / 4
		// checks if the cursor’s x pos is in the leftmost 25% of the window
	// x > 3 * W_WIDTH / 4
		// checks if the cursor’s x pos is in the rightmost 25% of the window
int	cursor_motion(int x, int y, t_data *data)
{
	static int	prev_x = W_WIDTH / 2;
	static int	prev_y = W_HEIGHT / 2;

	mlx_mouse_hide(data->mlx_ptr, data->mlx_win);
	if (x < prev_x)
		data->player.angle -= 0.02;
	else if (x > prev_x)
		data->player.angle += 0.02;
	if (x < W_WIDTH / 4 || x > 3 * W_WIDTH / 4 \
	|| y < W_HEIGHT / 4 || y > 3 * W_HEIGHT / 4)
	{
		mlx_mouse_move(data->mlx_ptr, data->mlx_win, W_WIDTH / 2, W_HEIGHT / 2);
		prev_x = W_WIDTH / 2;
		prev_y = W_HEIGHT / 2;
	}
	else
	{
		prev_x = x;
		prev_y = y;
	}
	return (0);
}
