/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:11:26 by habernar          #+#    #+#             */
/*   Updated: 2024/07/30 17:30:59 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*head;

	if (!dest && !src)
		return (0);
	head = dest;
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (head);
}
