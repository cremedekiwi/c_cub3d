/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:09 by habernar          #+#    #+#             */
/*   Updated: 2024/11/07 13:54:14 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	get_ray_orientation(t_ray *ray, float ray_angle)
{
	ray->angle = angle_normalize(ray_angle);
	ray->rayfacingup = (ray->angle >= PI && ray->angle <= 2 * PI);
	ray->rayfacingleft = (ray->angle >= PI / 2 && ray->angle <= 1.5 * PI);
	ray->distance = INT_MAX;
	ray->hit.x = 0;
	ray->hit.y = 0;
	ray->hitvertical = false;
}

static void	find_horizontal_intersection(t_data *data, t_ray *ray)
{
	t_vec2	curr;
	t_vec2	inc;

	curr.y = floor(data->player.pos.y / CUBE_SIZE) * CUBE_SIZE
		+ !ray->rayfacingup * CUBE_SIZE;
	curr.x = data->player.pos.x
		+ (curr.y - data->player.pos.y) / tan(ray->angle);
	inc.y = CUBE_SIZE;
	if (ray->rayfacingup)
		inc.y *= -1;
	inc.x = CUBE_SIZE / tan(ray->angle);
	if ((ray->rayfacingleft && inc.x > 0) || (!ray->rayfacingleft && inc.x < 0))
		inc.x *= -1;
	while (curr.x >= 0 && curr.x <= data->map.cols * CUBE_SIZE
		&& curr.y >= 0 && curr.y <= data->map.rows * CUBE_SIZE)
	{
		if (is_wall_at(data, curr.x, curr.y - ray->rayfacingup))
		{
			ray->hit = curr;
			ray->distance = distance(data->player.pos, curr);
			return ;
		}
		curr.x += inc.x;
		curr.y += inc.y;
	}
}

static void	find_vertical_intersection(t_data *data, t_ray *ray)
{
	t_vec2	curr;
	t_vec2	inc;

	curr.x = floor(data->player.pos.x / CUBE_SIZE) * CUBE_SIZE
		+ !ray->rayfacingleft * CUBE_SIZE;
	curr.y = data->player.pos.y
		+ (curr.x - data->player.pos.x) * tan(ray->angle);
	inc.x = CUBE_SIZE;
	if (ray->rayfacingleft)
		inc.x *= -1;
	inc.y = CUBE_SIZE * tan(ray->angle);
	if ((ray->rayfacingup && inc.y > 0) || (!ray->rayfacingup && inc.y < 0))
		inc.y *= -1;
	while (curr.x >= 0 && curr.x <= data->map.cols * CUBE_SIZE
		&& curr.y >= 0 && curr.y <= data->map.rows * CUBE_SIZE)
	{
		if (is_wall_at(data, curr.x - ray->rayfacingleft, curr.y))
		{
			ray->hit = curr;
			ray->distance = distance(data->player.pos, curr);
			return ;
		}
		curr.x += inc.x;
		curr.y += inc.y;
	}
}

static void	cast_ray(t_data *data, float ray_angle, int i)
{
	t_ray	vertical;
	t_ray	horizontal;

	get_ray_orientation(&data->rays[i], ray_angle);
	vertical = data->rays[i];
	horizontal = data->rays[i];
	find_vertical_intersection(data, &vertical);
	find_horizontal_intersection(data, &horizontal);
	if (vertical.distance < horizontal.distance)
	{
		data->rays[i] = vertical;
		data->rays[i].hitvertical = 1;
	}
	else
	{
		data->rays[i] = horizontal;
		data->rays[i].hitvertical = 0;
	}
}

void	init_rays(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = data->player.angle
			+ atan((i - NUM_RAYS / 2) / ((W_WIDTH / 2) / tan(FOV / 2)));
		cast_ray(data, ray_angle, i++);
	}
}
