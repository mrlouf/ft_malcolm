/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:11:22 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 19:47:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned char	*cpy1;
	unsigned char	*cpy2;
	size_t			i;

	cpy1 = (unsigned char *)s1;
	cpy2 = (unsigned char *)s2;
	i = 0;
	if (len == 0)
		return (0);
	while ((cpy1[i] || cpy2[i]) && i < len)
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
	printf("%d\n", ft_strncmp("abcdefgh", "abcdwxyz", 4));
}*/
