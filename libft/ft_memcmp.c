/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:26:18 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/24 18:59:57 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned char	*cpy1;
	unsigned char	*cpy2;
	size_t			i;

	i = 0;
	cpy1 = (unsigned char *)b1;
	cpy2 = (unsigned char *)b2;
	while (i < len)
	{
		if (cpy1[i] != cpy2[i])
			return (cpy1[i] - cpy2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%d\n", ft_memcmp("abc", "abc", 7));
	printf("%d\n", memcmp("abc", "abc", 7));
	return (0);
}*/
