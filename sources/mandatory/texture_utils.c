/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:18:48 by jarumuga          #+#    #+#             */
/*   Updated: 2024/11/21 15:20:27 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

void	check_existing_text(int i, t_data *data)
{
	if (i == 0 && data->text_no)
		free_texture(data->mlx_ptr, data->text_no);
	else if (i == 1 && data->text_so)
		free_texture(data->mlx_ptr, data->text_so);
	else if (i == 2 && data->text_we)
		free_texture(data->mlx_ptr, data->text_we);
	else if (i == 3 && data->text_ea)
		free_texture(data->mlx_ptr, data->text_ea);
}

char	*get_text_path(t_data *data, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit_error(data, MALLOC);
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
