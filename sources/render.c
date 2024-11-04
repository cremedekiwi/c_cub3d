/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:40:01 by habernar          #+#    #+#             */
/*   Updated: 2024/11/04 22:09:38 by habernar         ###   ########.fr       */
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

static void	render_map(t_data *data)
{
	int i;
	int j;

	draw_rect(&data->img, (t_rect){0, 0,
		data->map.rows * CUBE_SIZE * SCALE_MAP,
		data->map.cols * CUBE_SIZE * SCALE_MAP,
		0x000000});
	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			if (data->map.m[i][j] == '1' || data->map.m[i][j] == ' ')
				draw_rect(&data->img, (t_rect){
					j * CUBE_SIZE * SCALE_MAP,
					i * CUBE_SIZE * SCALE_MAP,
					CUBE_SIZE * SCALE_MAP,
					CUBE_SIZE * SCALE_MAP,
					0x787878});
			j++;
		}
		i++;
	}
}

int ft_max(int x, int y)
{
	return (x > y ? x : y);
}

int ft_min(int x, int y)
{
	return (x < y ? x : y);
}
static void render_minimap(t_data *data)
{
    int view_radius = 22; // Nombre de cases visibles autour du joueur
    int player_grid_x = data->player.pos.x / CUBE_SIZE;
    int player_grid_y = data->player.pos.y / CUBE_SIZE;

    // Limites de la zone visible autour du joueur
    int start_x = ft_max(0, player_grid_x - view_radius);
    int end_x = ft_min(data->map.cols - 1, player_grid_x + view_radius);
    int start_y = ft_max(0, player_grid_y - view_radius);
    int end_y = ft_min(data->map.rows - 1, player_grid_y + view_radius);

    // Taille de la minimap en pixels, basée sur un zoom fixe
    int minimap_size = (view_radius * 2 + 1) * CUBE_SIZE * SCALE_MAP;
    draw_rect(&data->img, (t_rect){0, 0, minimap_size, minimap_size, 0x000000});

    // Offset pour centrer la minimap sur le joueur
    float center_offset_x = (view_radius * CUBE_SIZE * SCALE_MAP) - 
                           (data->player.pos.x * SCALE_MAP - start_x * CUBE_SIZE * SCALE_MAP);
    float center_offset_y = (view_radius * CUBE_SIZE * SCALE_MAP) - 
                           (data->player.pos.y * SCALE_MAP - start_y * CUBE_SIZE * SCALE_MAP);

    // Dessin des murs dans la zone visible
    for (int y = start_y; y <= end_y; y++)
    {
        for (int x = start_x; x <= end_x; x++)
        {
            if (data->map.m[y][x] == '1')
            {
                draw_rect(&data->img, (t_rect){
                    (x - start_x) * CUBE_SIZE * SCALE_MAP + center_offset_x,
                    (y - start_y) * CUBE_SIZE * SCALE_MAP + center_offset_y,
                    CUBE_SIZE * SCALE_MAP,
                    CUBE_SIZE * SCALE_MAP,
                    0x787878
                });
            }
        }
    }

    // Dessiner le joueur au centre de la minimap
    draw_rect(&data->img, (t_rect){
        view_radius * CUBE_SIZE * SCALE_MAP - 5 * SCALE_MAP,
        view_radius * CUBE_SIZE * SCALE_MAP - 5 * SCALE_MAP,
        10 * SCALE_MAP,
        10 * SCALE_MAP,
        0xFFFFFF
    });

    // Dessiner les rayons visibles
    int i = 0;
    while (i < NUM_RAYS)
    {
        // Calculer les points de départ et de fin du rayon
        t_vec2 ray_start = (t_vec2){
            view_radius * CUBE_SIZE * SCALE_MAP,
            view_radius * CUBE_SIZE * SCALE_MAP
        };
        t_vec2 ray_end = (t_vec2){
            (data->rays[i].hit.x - data->player.pos.x) * SCALE_MAP + ray_start.x,
            (data->rays[i].hit.y - data->player.pos.y) * SCALE_MAP + ray_start.y
        };

        // Clipper le rayon pour qu'il reste dans le cadre de la minimap
        //if (ray_end.x < 0) ray_end.x = 0;
        //if (ray_end.y < 0) ray_end.y = 0;
        if (ray_end.x > minimap_size) ray_end.x = minimap_size;
        if (ray_end.y > minimap_size) ray_end.y = minimap_size;

        // Dessiner le rayon clippé
        draw_line(data, ray_start.x, ray_start.y, ray_end.x, ray_end.y);
        i++;
    }
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
	if (!data->mlx_win)
		return (1);
	init_rays(data);
	move_player(data, &data->player);
	render_background(&data->img, 0x000000);
	//render_walls(data);
	render_textures_and_colors(data);
	render_map(data);
	draw_rect(&data->img, (t_rect){
			(data->player.pos.x - 5) * SCALE_MAP,
			(data->player.pos.y - 5 ) * SCALE_MAP,
			10 * SCALE_MAP,
			10 * SCALE_MAP,
			0xFFFFFF});
	render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.mlx_img, 0, 0);
	return (0);
}
