/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:36:27 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/20 18:42:52 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dst == (void *)0 && src == (void *)0)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char	*dst;
	dst = (char *)malloc(sizeof(char) * 23);
	
	if (!dst)
		return (1);
	//ft_strlcpy(dst, "loremipsum dolor sit a", 23);
	//ft_memcpy(dst, "ASDEWQ", 10);
	//write(1, dst, 22);
	//write(1, "\n", 1);
	ft_strlcpy(dst, "loremipsum dolor sit a", 23);
	memcpy(dst, "ASDEWQ", 10);
	write(1, dst, 22);
	free(dst);
	return (0);
}*/
