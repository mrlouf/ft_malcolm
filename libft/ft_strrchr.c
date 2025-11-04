/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:49:46 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/16 14:07:58 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char) c;
	i = ft_strlen(s);
	if (!cc)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	char c = ' ';

	if (ac == 2)
		ft_strrchr(av[1], c);
	return (0);
}*/
