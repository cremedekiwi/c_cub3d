/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:35:26 by habernar          #+#    #+#             */
/*   Updated: 2024/10/31 13:34:39 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab && tab[i])
			free(tab[i++]);
		free(tab);
	}
	tab = 0;
}

int is_wall_at(t_data *data, float x, float y)
{
	if (x < 0 || x >= data->map.cols * CUBE_SIZE || y < 0 || y >= data->map.rows * CUBE_SIZE)
		return (1);
	return (data->map.m[(int)floor(y / CUBE_SIZE)][(int)floor(x / CUBE_SIZE)] == '1');
}

void	exit_game(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->img.mlx_img)
			mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		if (data->text_no && data->text_no->mlx_img)
		{
			mlx_destroy_image(data->mlx_ptr, data->text_no->mlx_img);
			free(data->text_no->path);
			free(data->text_no);
		}
		if (data->text_so && data->text_so->mlx_img)
		{
			mlx_destroy_image(data->mlx_ptr, data->text_so->mlx_img);
			free(data->text_so->path);
			free(data->text_so);
		}
		if (data->text_we && data->text_we->mlx_img)
		{
			mlx_destroy_image(data->mlx_ptr, data->text_we->mlx_img);
			free(data->text_we->path);
			free(data->text_we);
		}
		if (data->text_ea && data->text_ea->mlx_img)
		{
			mlx_destroy_image(data->mlx_ptr, data->text_ea->mlx_img);
			free(data->text_ea->path);
			free(data->text_ea);
		}
		if (data->mlx_win)
			mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		if (data->map.m)
			free_tab(data->map.m);
		exit(0);
	}
}

void	init_player(t_data *data)
{
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->player.delta_angle = 0;
	data->player.forward = 0;
	data->player.sideway = 0;
	data->player.angle = 0;
}

int	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	if (!data->mlx_win)
		return (mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), 1);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!data->img.mlx_img)
		return (exit_game(data), 1);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->map.m = 0;
	data->map.rows = 0;
	data->map.cols = 0;
	data->text_no = 0;
	data->text_so = 0;
	data->text_we = 0;
	data->text_ea = 0;
	data->color_floor = -1;
	data->color_ceiling = -1;
	init_player(data);
	return (0);
}

int is_texture(char *str)
{
	if (!ft_strncmp(str, "NO ", 3)
		|| !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3)
		|| !ft_strncmp(str, "EA ", 3))
		return (1);
	return (0);
}

void create_texture(t_data *data, char *str, int fd)
{
	t_img	*img;
	size_t	len;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (free(str), close(fd), exit_game(data));
	img->path = ft_strdup(ft_strchr(str, '.'));
	len = ft_strlen(img->path);
	if (len > 0 && img->path[len - 1] == '\n')
		img->path[len - 1] = '\0';
	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, img->path, &img->width, &img->height);
	if (!img->mlx_img)
		return (printf("error xpm image\n"),free(str), close(fd), exit_game(data));
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
	if (!ft_strncmp(str, "NO", 2))
		data->text_no = img;
	if (!ft_strncmp(str, "SO", 2))
		data->text_so = img;
	if (!ft_strncmp(str, "WE", 2))
		data->text_we = img;
	if (!ft_strncmp(str, "EA", 2))
		data->text_ea = img;
}

void	get_texture(t_data *data, char *str, int fd)
{
	char	*tmp;

	create_texture(data, str, fd);
	/*
	tmp = ft_strchr(str, '.');
	if (!tmp)
	{
		ft_putstr_fd("Error: locating texture\n", 2);
		exit_game(data);
	}
	if (!create_texture(data, tmp, fd))
	{
		ft_putstr_fd("Error: creating texture\n", 2);
		return (free(str), close(fd), exit_game(data));
	}
	*/
}

void get_color(t_data *data, char *str, char c, int fd)
{
	int		r;
	int		g;
	int		b;
	char	*head;

	head = str;
	while (*str && !ft_isdigit(*str))
		str++;
	r = ft_atoi(str);
	str = ft_strchr(str, ',');
	g = ft_atoi(++str);
	str = ft_strchr(str, ',');
	b = ft_atoi(++str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putstr_fd("Error, color values out of range [0, 255]\n", 2);
		return (free(head), close(fd), exit_game(data));
	}
	if (c == 'F')
		data->color_ceiling = (r << 16) | (g << 8) | b;
	else
		data->color_floor = (r << 16) | (g << 8) | b;
}

int	is_last_argument(t_data *data)
{
	if (data->color_floor != -1 && data->color_ceiling != -1
		&& data->text_no && data->text_so && data->text_ea
		&& data->text_we)
		return (1);
	return (0);
}

int is_map(char *str)
{
	int	count1;
	int	count0;

	count0 = 0;
	count1 = 0;
	while (*str)
	{
		if (!(*str == '1' || *str == '0' || *str == ' ' || *str == '\n'))
			return (0);
		if (*str == '1')
			count1++;
		if (*str == '0')
			count0++;
		str++;
	}
	return (count1 || count0);
}


char **tab_append(char **tab, char *str)
{
	char	**new;
	char	*cp;
	int		i;

	cp = ft_strdup(str);
	if (!cp)
		return (free_tab(tab), (char **)0);
	i = 0;
	while (tab && tab[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (free_tab(tab), free(cp), (char **)0);
	i = 0;
	while (tab && tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	new[i++] = cp;
	new[i] = 0;
	free(tab);
	return (new);
}

void get_map_dimension(t_data *data, char **tab)
{
	int i;
	int max_length;
	int curr_length;

	i = 0;
	max_length = INT_MIN;
	while (tab && tab[i])
	{
		curr_length = ft_strlen(tab[i]);
		if (curr_length > max_length)
			max_length = curr_length;
		i++;
	}
	data->map.rows = i;
	data->map.cols = max_length - 1;
}

void get_player_position(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map.m[i])
	{
		j = 0;
		while (data->map.m[i][j])
		{
			if (data->map.m[i][j] == 'N' || data->map.m[i][j] == 'S' || data->map.m[i][j] == 'W' || data->map.m[i][j] == 'E')
			{
				data->player.pos.x = j * CUBE_SIZE;
				data->player.pos.y = i * CUBE_SIZE;
			}
			if (data->map.m[i][j] == 'N')
				data->player.angle = - PI / 2;
			else if (data->map.m[i][j] == 'S')
				data->player.angle = PI / 2;
			else if (data->map.m[i][j] == 'W')
				data->player.angle = PI;
			else if (data->map.m[i][j] == 'E')
				data->player.angle = 0;
			j++;
		}
		i++;
	}
}

void copy_tab(t_data *data, char **tab)
{
	int j;
	int i;
	char **new_tab;

	new_tab = (char **)malloc(sizeof(char *) * (data->map.rows + 1));
	if (!new_tab)
		return (free_tab(tab), exit_game(data));
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = (char *)malloc(sizeof(char) * (data->map.cols + 1));
		if (!new_tab[i])
			return (free_tab(tab), free_tab(new_tab), exit_game(data));
		j = 0;
		while (tab[i][j] && j < data->map.cols)
		{
			new_tab[i][j] = tab[i][j];
			j++;
		}
		while (j < data->map.cols)
			new_tab[i][j++] = ' ';
		new_tab[i][j] = 0;
		i++;
	}
	new_tab[i] = 0;
	free_tab(tab);
	data->map.m = new_tab;
}

void get_map(t_data *data, char *str, int fd)
{
	char **tab;

	tab = 0;
	while (str)
	{
		tab = tab_append(tab, str);
		if (!tab)
			return (free(str), close(fd), exit_game(data));
		free(str);
		str = get_next_line(fd);
	}
	get_map_dimension(data, tab);
	copy_tab(data, tab);
	get_player_position(data);
}

void	parse_map(t_data *data, char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd <= 0)
	{
		ft_putstr_fd("Error: could not open file", 2);
		exit_game(data);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture(line))
			get_texture(data, line, fd);
		else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			get_color(data, line, line[0], fd);
		/*
		if (is_last_argument(data) && is_map(line))
		*/
		else if (is_map(line))
		{
			get_map(data, line, fd);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		return ((void)printf("You must provide a map.cub\n"), 1);
	if (init_game(&data))
		return (1);
	parse_map(&data, argv[1]);
	/*
	int i = 0;
	while (data.map.m[i])
	{
		printf("%s", data.map.m[i]);
		i++;
	}
	*/
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
}
