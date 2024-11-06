/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:08:55 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 17:17:57 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	init_line(t_dda *line, t_vec2 v0, t_vec2 v1)
{
	line->dx = ft_abs(v1.x - v0.x);
	line->dy = -ft_abs(v1.y - v0.y);
	line->sx = -1;
	if (v0.x < v1.x)
		line->sx = 1;
	line->sy = -1;
	if (v0.y < v1.y)
		line->sy = 1;
	line->err = line->dx + line->dy;
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	t_dda line;

	init_line(&line, (t_vec2){x0, y0}, (t_vec2){x1, y1});
	while (1)
	{
		img_pix_put(&data->img, x0,y0, 0xF7FF73);
		if (x0 == x1 && y0 == y1)
			break;
        line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			y0 += line.sy;
		}
    }
}

/*
void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	t_line line;
	int dx = ft_abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -ft_abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	init_line(&line, (t_vec2){x0, y0}, (t_vec2){x1, y1});
	while (1)
	{
		img_pix_put(&data->img, x0,y0, 0xF7FF73);
		if (x0 == x1 && y0 == y1)
			break;
        e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
    }
}
*/
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
