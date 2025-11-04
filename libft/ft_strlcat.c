/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:50:13 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/20 14:33:53 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The variable size should be the total length of destination + source
 *	including the terminating null byte.				*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

/*
int	main(int ac, char **av)
{
	if (ac == 3)
	{
		printf("dst = %s\nsrc = %s\n", av[1], av[2]);
		printf("bytes = %zu\n", ft_strlcat(av[1], av[2], ft_strlen(av[2])));
		printf("dst = %s\nsrc = %s\n", av[1], av[2]);
	}
	return (0);
}*/
