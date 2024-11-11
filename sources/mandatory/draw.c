/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:08:55 by habernar          #+#    #+#             */
/*   Updated: 2024/11/11 18:27:11 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	init_line(t_dda *line, t_vec2 v0, t_vec2 v1)
{
	line->dx = ft_abs((int)v1.x - v0.x);
	line->dy = -ft_abs((int)v1.y - v0.y);
	line->sx = -1;
	if (v0.x < v1.x)
		line->sx = 1;
	line->sy = -1;
	if (v0.y < v1.y)
		line->sy = 1;
	line->err = line->dx + line->dy;
}

void	draw_line(t_data *data, t_vec2 v0, t_vec2 v1)
{
	t_dda	line;

	init_line(&line, v0, v1);
	while (1)
	{
		img_pix_put(&data->img, (int)v0.x, (int)v0.y, 0xF7FF73);
		if ((int)v0.x == (int)v1.x && (int)v0.y == (int)v1.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			v0.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			v0.y += line.sy;
		}
	}
}

int	draw_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i <= rect.y + rect.height)
	{
		j = rect.x;
		while (j <= rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		i++;
	}
	return (0);
}
