/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:48:30 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/20 17:19:09 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <string.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("len = %zu\n", ft_strlen(av[1]));
		printf("len = %zu\n", strlen(av[1]));
	}
	return (0);
}*/
