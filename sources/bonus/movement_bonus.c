/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:02 by habernar          #+#    #+#             */
/*   Updated: 2024/11/04 16:12:15 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	else if (player->sideway != 0) {
		newpos.x += cos(player->angle + player->sideway * PI / 2) * VELOCITY;
		newpos.y += sin(player->angle + player->sideway * PI / 2) * VELOCITY;
	}
	delta = -(float)CUBE_SIZE / 5;
	if (player->pos.y < newpos.y)
		delta *= -1;
	if (!is_wall_at(data, player->pos.x, newpos.y + delta))
		player->pos.y = newpos.y;
	delta = -(float)CUBE_SIZE / 5;
	if (player->pos.x < newpos.x)
		delta *= -1;
	if (!is_wall_at(data, newpos.x + delta, player->pos.y))
		player->pos.x = newpos.x;
}
