/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:29:37 by habernar          #+#    #+#             */
/*   Updated: 2024/11/05 14:18:26 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

float	angle_normalize(float angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle = PI * 2 + angle;
	return (angle);
}

float	distance(t_vec2 v1, t_vec2 v2)
{
	return (sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2)));
}

t_vec2	vec2_scale(t_vec2 v, float scale)
{
	t_vec2	res;

	res.x = v.x * scale;
	res.y = v.y * scale;
	return (res);
}
