/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:12:33 by habernar          #+#    #+#             */
/*   Updated: 2024/11/12 16:46:18 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**tab_append(char **tab, char *str)
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

void	copy_tab(t_data *data, char **tab)
{
	int		j;
	int		i;
	char	**new_tab;

	new_tab = (char **)malloc(sizeof(char *) * (data->map.rows + 1));
	if (!new_tab)
		return (free_tab(tab), exit_error(data, MALLOC));
	i = -1;
	while (tab && tab[++i])
	{
		new_tab[i] = (char *)malloc(sizeof(char) * (data->map.cols + 1));
		if (!new_tab[i])
			return (free_tab(tab), free_tab(new_tab),
				exit_error(data, MALLOC));
		j = -1;
		while (tab[i][++j] && tab[i][j] != '\n')
			new_tab[i][j] = tab[i][j];
		while (j < data->map.cols - 1)
			new_tab[i][j++] = ' ';
		new_tab[i][j] = 0;
	}
	return (new_tab[i] = 0, free_tab(tab), data->map.m = new_tab, (void)0);
}
