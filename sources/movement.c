/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:25:02 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 17:06:52 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (player->sideway != 0)
	{
		newpos.x += cos(player->angle + player->sideway * PI / 2) * VELOCITY;
		newpos.y += sin(player->angle + player->sideway * PI / 2) * VELOCITY;
	}
	if (!is_wall_at(data, newpos.x, newpos.y))
		player->pos = newpos;
}
