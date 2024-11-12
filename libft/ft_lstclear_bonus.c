/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:41:42 by habernar          #+#    #+#             */
/*   Updated: 2024/07/30 17:29:50 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	if (!lst || !*lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head;
		head = head->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = 0;
}
