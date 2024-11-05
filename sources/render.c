/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:01 by habernar          #+#    #+#             */
/*   Updated: 2024/11/06 00:07:14 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	(void)color;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
			img_pix_put(img, j++, i , color);
		i++;
	}
}

t_vec2 vec2_add(t_vec2 v1, t_vec2 v2)
{
	t_vec2	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return (res);
}

t_vec2 vec2_sub(t_vec2 v1, t_vec2 v2)
{
	t_vec2	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return (res);
}

typedef struct s_minimap
{
	int	radius;
	int	size;
	t_vec2 center;
	t_vec2 player;
}	t_minimap;

static void init_minimap(t_data *data, t_minimap *minimap)
{
	minimap->radius = 20;
	minimap->size = (minimap->radius * 2 + 1) * CUBE_SIZE * SCALE_MAP;
	minimap->center = (t_vec2){minimap->size / 2, minimap->size / 2};
	minimap->player.x = data->player.pos.x / CUBE_SIZE;
	minimap->player.y = data->player.pos.y / CUBE_SIZE;
}
static bool is_in_minimap(t_minimap *minimap, t_vec2 v)
{
    return (v.x >= 0 && v.x < minimap->size && v.y >= 0 && v.y < minimap->size);
}

static void draw_visible_walls(t_data *data, t_minimap *minimap)
{
	t_vec2	map;
	t_vec2	screen;
	t_vec2  curr;
    
	curr.y = -minimap->radius - 1;
	while (++curr.y <= minimap->radius)
	{
		curr.x = -minimap->radius - 1;
		while (++curr.x <= minimap->radius)
		{
			map = vec2_add(minimap->player, curr);
			if (map.x >= 0 && map.x <= data->map.cols && map.y >= 0 && map.y <= data->map.rows)
			{
				screen = vec2_add(minimap->center, vec2_scale(curr, CUBE_SIZE * SCALE_MAP));
				if (is_in_minimap(minimap, screen) && data->map.m[(int)map.y][(int)map.x] == '1')
				{
                        draw_rect(&data->img, (t_rect){
                            screen.x,
                            screen.y,
                            CUBE_SIZE * SCALE_MAP,
                            CUBE_SIZE * SCALE_MAP,
                            0x515250
                        });
				}
			}
		}
	}
}
static void draw_player_and_rays(t_data *data, t_minimap *minimap)
{
    draw_rect(&data->img, (t_rect){
		minimap->center.x,
        minimap->center.y,
        10 * SCALE_MAP,
        10 * SCALE_MAP,
        0xFFFFFFFF
    });

}
static void	render_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		t_vec2 scale1 = vec2_scale(data->player.pos, SCALE_MAP);
		t_vec2 scale2 = vec2_scale(data->rays[i].hit, SCALE_MAP);
		draw_line(data,scale1.x, scale1.y, scale2.x, scale2.y);
		i++;
	}
}

void	render_textures_and_colors(t_data *data)
{
	int			i;
	int			j;
	t_render	render_info;

	i = 0;
	while (i < NUM_RAYS)
	{
		calculate_wall_height(&render_info.wall, data->rays[i].distance * \
		cos(data->rays[i].angle - data->player.angle));
		j = 0;
		while (j < render_info.wall.start)
			img_pix_put(&data->img, i, j++, data->color_ceiling);
		determine_texture(data, i, &render_info);
		render_wall(data, i, render_info);
		j = render_info.wall.end;
		while (j < W_HEIGHT)
			img_pix_put(&data->img, i, j++, data->color_floor);
		i++;
	}
}

int	render(t_data *data)
{
    t_minimap minimap;

    init_minimap(data, &minimap);
	if (!data->mlx_win)
		return (1);
	init_rays(data);
	move_player(data, &data->player);
	render_background(&data->img, 0x000000);
	//render_walls(data);
	render_textures_and_colors(data);
    draw_rect(&data->img, (t_rect){0, 0, minimap.size, minimap.size, 0x44000000});
    
    draw_visible_walls(data, &minimap);
    draw_player_and_rays(data, &minimap);
	//render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.mlx_img, 0, 0);
	return (0);
}
