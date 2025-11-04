/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:01:01 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/20 18:42:27 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This functions copies bytes just like f_memcpy, but in a "non-destructive
manner" according to the manual. This is ensured by checking that the address
of destination is smaller (i.e. located before) or equal to the source. If that
is not the case, the copy is made backwards to avoid data loss. */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c_src;
	char	*c_dst;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	c_src = (char *) src;
	c_dst = (char *) dst;
	i = 0;
	if (c_dst > c_src)
		while (len-- > 0)
			c_dst[len] = c_src[len];
	else
	{
		while (i < len)
		{
			c_dst[i] = c_src[i];
			i++;
		}
	}
	return (dst);
}

/*
int	main(void)
{
	char *dst;
	dst = (char *)malloc(sizeof(char) * 23);
	if (!dst)
		return (1);
	ft_strlcpy(dst, "loremipsum dolor sit a", 23);
	ft_memmove(NULL, "dolor", 10);
	write(1, dst, 22);
	free(dst);
	return (0);
}*/
