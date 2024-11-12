/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:02 by habernar          #+#    #+#             */
/*   Updated: 2024/11/12 22:46:19 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
