/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:41:07 by habernar          #+#    #+#             */
/*   Updated: 2024/07/30 17:34:15 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	char	*p;

	p = dst;
	while (n && *p)
	{
		n--;
		p++;
	}
	while (n-- > 1)
	{
		if (!*src)
		{
			*p = 0;
			return (p - dst);
		}
		*p++ = *src++;
		*p = 0;
	}
	return (p - dst + ft_strlen(src));
}
