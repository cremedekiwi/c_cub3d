/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:05:00 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 15:05:24 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall_at(t_data *data, float x, float y)
{
	if (x < 0 || x >= data->map.cols * CUBE_SIZE || y < 0 || y >= data->map.rows * CUBE_SIZE)
		return (1);
	return (data->map.m[(int)floor(y / CUBE_SIZE)][(int)floor(x / CUBE_SIZE)] == '1');
}

