/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:35:49 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/20 19:08:06 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	l_src;

	l_src = ft_strlen(src);
	if (l_src + 1 < dstsize)
		ft_memcpy(dst, src, l_src + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (l_src);
}

/*
int	main(int ac, char **av)
{
	if (ac == 3)
	{
		printf("src = %s\ndst = %s\n", av[2], av[1]);
		printf("bytes = %zu\n", ft_strlcpy(av[1], av[2], ft_strlen(av[2] + 1)));
		printf("src = %s\ndst = %s\n", av[2], av[1]);
	}
}*/
