/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:34:25 by habernar          #+#    #+#             */
/*   Updated: 2024/11/07 13:48:54 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_a)
		data->player.sideway = 0;
	if (keysym == XK_d)
		data->player.sideway = 0;
	if (keysym == XK_w)
		data->player.forward = 0;
	if (keysym == XK_s)
		data->player.forward = 0;
	if (keysym == XK_Left)
		data->player.delta_angle = 0;
	if (keysym == XK_Right)
		data->player.delta_angle = 0;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit_game(data);
	if (keysym == XK_a)
		data->player.sideway -= 1;
	if (keysym == XK_d)
		data->player.sideway += 1;
	if (keysym == XK_w)
		data->player.forward += 1;
	if (keysym == XK_s)
		data->player.forward -= 1;
	if (keysym == XK_Left)
		data->player.delta_angle -= 1;
	if (keysym == XK_Right)
		data->player.delta_angle += 1;
	return (0);
}
