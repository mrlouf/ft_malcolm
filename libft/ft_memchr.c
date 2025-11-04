/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:09 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/16 19:12:03 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	const unsigned char	*cpy;
	unsigned char		cc;

	cpy = (const unsigned char *)s;
	cc = (unsigned char)c;
	while (len > 0)
	{
		if (*cpy == cc)
			return ((void *)cpy);
		cpy++;
		len--;
	}
	return (NULL);
}
